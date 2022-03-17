#include "gni/task.hpp"

#include <stdlib.h>
#include <string.h>

#include "gni/common/logger.h"
#include "gni/gni.h"
#include "gni/gni.hpp"

namespace gni {

namespace {

constexpr char kLogTag[] = "Task";

constexpr char kJavaNativeOnComplete[] = "nativeOnComplete";
constexpr char kJavaNativeOnComplete_Sig[] =
    "(JLjava/lang/Object;ZZLjava/lang/String;)V";
constexpr char kNativeOnCompleteListener[] =
    "com/google/android/gms/tasks/NativeOnCompleteListener";
constexpr char kNativeOnCompleteListener_createAndAddCallback[] =
    "createAndAddCallback";
constexpr char kNativeOnCompleteListener_createAndAddCallback_Sig[] =
    "(Lcom/google/android/gms/tasks/Task;J)V";

void NativeOnComplete(JNIEnv* env, jobject object, jlong task_pointer,
                      jobject result_object, bool is_successful,
                      bool is_canceled, jstring error_message) {
  if (task_pointer == 0) {
    return;
  }

  reinterpret_cast<Task*>(task_pointer)
      ->HandleOnComplete(result_object, is_successful, is_canceled,
                         error_message);
}

// A helper class for managing JNI resources related to Java
// com.google.android.gms.tasks.Task class.
class TaskJniHelper {
 public:
  TaskJniHelper() {
    // TODO(b/194924169):
    // The Taks uses a dedicated listener implemented on the Java side:
    // com.google.android.gms.tasks.NativeOnCompleteListener.java. This class
    // can be removed after implementing a more universal mechanism, which is
    // described here: b/195128685.

    JNIEnv* env = GniCore::GetInstance()->GetJniEnv();

    native_on_complete_listener_class_ =
        GniCore::GetInstance()->GetClassGlobalRef(kNativeOnCompleteListener);
    if (native_on_complete_listener_class_ == nullptr) {
      gni::common::LogE(kLogTag, "Couldn't get a global reference of %s",
                        kNativeOnCompleteListener);
      abort();
    }

    JNINativeMethod native_method = {
        .name = const_cast<char*>(kJavaNativeOnComplete),
        .signature = const_cast<char*>(kJavaNativeOnComplete_Sig),
        .fnPtr = reinterpret_cast<void*>(&NativeOnComplete),
    };

    if (env->RegisterNatives(native_on_complete_listener_class_, &native_method,
                             1) != JNI_OK) {
      gni::common::LogE(kLogTag, "Couldn't register a native callback.");
      abort();
    }

    create_and_add_callback_mid_ = env->GetStaticMethodID(
        native_on_complete_listener_class_,
        kNativeOnCompleteListener_createAndAddCallback,
        kNativeOnCompleteListener_createAndAddCallback_Sig);
    if (create_and_add_callback_mid_ == nullptr) {
      gni::common::LogE(kLogTag, "Couldn't get a static method %s",
                        kNativeOnCompleteListener_createAndAddCallback);
      abort();
    }
  }

  // Returns a JNI reference to
  // com.google.android.gms.tasks.NativeOnCompleteListener.
  jclass GetListenerClass() const { return native_on_complete_listener_class_; }

  // Returns a JNI method id of
  // com.google.android.gms.tasks.NativeOnCompleteListener.createAndAddCallback().
  jmethodID GetCallbackMid() const { return create_and_add_callback_mid_; }

 private:
  jclass native_on_complete_listener_class_;
  jmethodID create_and_add_callback_mid_;
};

const TaskJniHelper& GetTaskJniHelper() {
  static const TaskJniHelper* task_jni_helper_ = new TaskJniHelper();
  return *task_jni_helper_;
}

}  // namespace

void Task::Destroy(Task* task) { delete task; }

Task::Task(jobject task_object) {
  pthread_mutex_init(&instance_mutex_, nullptr);

  task_object_ = GniCore::GetInstance()->GetJniEnv()->NewGlobalRef(task_object);
}

Task::~Task() {
  if (task_object_ != nullptr) {
    GniCore::GetInstance()->GetJniEnv()->DeleteGlobalRef(task_object_);
  }

  pthread_mutex_lock(&instance_mutex_);

  if (result_object_ != nullptr) {
    GniCore::GetInstance()->GetJniEnv()->DeleteGlobalRef(result_object_);
  }

  if (error_message_ != nullptr) {
    GniString_destroy(error_message_);
  }

  pthread_mutex_unlock(&instance_mutex_);

  pthread_mutex_destroy(&instance_mutex_);
}

void Task::AddOnCompleteCallback(OnCompleteCallback on_complete_callback,
                                 void* user_data) {
  {
    pthread_mutex_lock(&instance_mutex_);
    on_complete_callback_ = on_complete_callback;
    user_data_ = user_data;
    pthread_mutex_unlock(&instance_mutex_);
  }

  const auto& task_jni_helper = GetTaskJniHelper();

  GniCore::GetInstance()->GetJniEnv()->CallStaticVoidMethod(
      task_jni_helper.GetListenerClass(), task_jni_helper.GetCallbackMid(),
      task_object_, reinterpret_cast<jlong>(this));
}

void Task::HandleOnComplete(jobject result_object, bool is_successful,
                            bool is_canceled, jstring error_message) {
  OnCompleteCallback callback;

  pthread_mutex_lock(&instance_mutex_);

  is_complete_ = true;
  is_successful_ = is_successful;
  is_canceled_ = is_canceled;

  if (is_successful) {
    error_code_ = GNI_TASK_SUCCESS;
    if (result_object != nullptr) {
      result_object_ =
          GniCore::GetInstance()->GetJniEnv()->NewGlobalRef(result_object);
    }
  } else {
    error_code_ = is_canceled ? GNI_TASK_CANCELED : GNI_TASK_UNKNOWN_ERROR;
    if (error_message != nullptr) {
      error_message_ = GniCore::GetInstance()->ConvertString(error_message);
    }
  }

  // Store the callback inside the mutex-protected scope.
  callback = on_complete_callback_;

  pthread_mutex_unlock(&instance_mutex_);

  if (callback != nullptr) {
    callback(this, user_data_);
  }
}

bool Task::IsComplete() const { return AtomicGet(&is_complete_); }

bool Task::IsSuccessful() const { return AtomicGet(&is_successful_); }

bool Task::IsCanceled() const { return AtomicGet(&is_canceled_); }

jobject Task::GetResultObject() const { return AtomicGet(&result_object_); }

const char* Task::GetErrorMessage() const {
  pthread_mutex_lock(&instance_mutex_);

  if (error_message_ == nullptr) {
    pthread_mutex_unlock(&instance_mutex_);
    return nullptr;
  }

  char* error_message = new char[strlen(error_message_) + 1];
  strcpy(error_message, error_message_);  // NOLINT

  pthread_mutex_unlock(&instance_mutex_);

  return error_message;
}

GniTaskErrorCode Task::GetErrorCode() const { return AtomicGet(&error_code_); }

}  // namespace gni
