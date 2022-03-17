#include "gni/common/jni_helper_impl.h"

#include <pthread.h>
#include <sys/types.h>

#include "gni/common/logger.h"

namespace gni {
namespace common {

namespace {
constexpr char kContext[] = "android/content/Context";
constexpr char kContext_getApplicationContext[] = "getApplicationContext";
constexpr char kContext_getApplicationContext_void[] =
    "()Landroid/content/Context;";
constexpr char kContext_getClassLoader[] = "getClassLoader";
constexpr char kContext_getClassLoader_void[] = "()Ljava/lang/ClassLoader;";
constexpr char kClassLoader_loadClass[] = "loadClass";
constexpr char kClassLoader_loadClass_String[] =
    "(Ljava/lang/String;)Ljava/lang/Class;";

constexpr char kLogTag[] = "JniHelper";

// The single instance of this class and lock/boolean that protects it.
JniHelperImpl instance_;
pthread_mutex_t instance_lock_ = PTHREAD_MUTEX_INITIALIZER;
bool instance_initialized_ = false;

// State needed to call DetachCurrentThread() when a thread finishes.
pthread_key_t jni_env_key;
pthread_once_t pthread_key_initialized = PTHREAD_ONCE_INIT;

// Wrapper for AttachCurrentThread() that handles signature differences.
jint AttachCurrentThread(JavaVM *jvm, JNIEnv **env) {
#ifdef __ANDROID__
  return jvm->AttachCurrentThread(env, nullptr);
#else
  return jvm->AttachCurrentThread(reinterpret_cast<void **>(env), nullptr);
#endif
}

// Function called from the thread destructor to detach the JVM.
// See https://developer.android.com/training/articles/perf-jni#threads_1
void DetachThreadFromJvm(void *stored_java_vm) {
  LogD(kLogTag, "Detaching thread from JavaVM...");
  JNIEnv *env;
  JavaVM *jvm = static_cast<JavaVM *>(stored_java_vm);
  // AttachCurrentThread does nothing if we're already attached, but
  // calling it ensures that DetachCurrentThread() doesn't fail.
  jint attach_status = AttachCurrentThread(jvm, &env);
  if (attach_status == JNI_OK) {
    jvm->DetachCurrentThread();
    LogD(kLogTag, "Detached thread from JavaVM.");
  } else {
    LogE(kLogTag, "Skipping JNI thread detach since attach status=%d",
         attach_status);
  }
}

void SetupJvmDetachOnThreadDestruction() {
  pthread_key_create(&jni_env_key, DetachThreadFromJvm);
}
}  // namespace

JniHelper *JniHelper::GetInstance(JavaVM *jvm, jobject android_context) {
  pthread_mutex_lock(&instance_lock_);

  if (!instance_initialized_ && instance_.Initialize(jvm, android_context)) {
    instance_initialized_ = true;
  }

  pthread_mutex_unlock(&instance_lock_);

  return instance_initialized_ ? &instance_ : nullptr;
}

bool JniHelperImpl::Initialize(JavaVM *jvm, jobject android_context) {
  if (jvm == nullptr) {
    LogE(kLogTag, "\"jvm\" must not be null.");
    return false;
  }
  jvm_ = jvm;

  if (android_context == nullptr) {
    LogE(kLogTag, "\"android_context\" must not be null.");
    return false;
  }

  JNIEnv *env = GetEnv();
  jclass android_context_class = env->FindClass(kContext);
  if (android_context_class == nullptr) {
    LogE(kLogTag, "\"android_context\" class is null.");
    return false;
  }
  if (!env->IsInstanceOf(android_context, android_context_class)) {
    LogE(kLogTag,
         "\"android_context\" must be an instance of android.content.Context.");
    return false;
  }

  jclass context_class = env->GetObjectClass(android_context);

  // Get the Application Context so that we can obtain its ClassLoader. If
  // android_context is an Activity, it'd probably be fine to use its
  // ClassLoader directly, but this is extra defense against a memory leak.
  jmethodID get_application_context_mid =
      env->GetMethodID(context_class, kContext_getApplicationContext,
                       kContext_getApplicationContext_void);
  jobject application_context =
      env->CallObjectMethod(android_context, get_application_context_mid);

  // Obtain a global reference to the Application Context's ClassLoader object.
  jmethodID get_class_loader_mid = env->GetMethodID(
      context_class, kContext_getClassLoader, kContext_getClassLoader_void);
  class_loader_.object = env->NewGlobalRef(
      env->CallObjectMethod(application_context, get_class_loader_mid));

  // According to NDK documentation "method IDs are guaranteed valid until the
  // class is unloaded". The class_loader_.object global reference will keep the
  // class loaded.
  jclass class_loader_clazz = env->GetObjectClass(class_loader_.object);
  class_loader_.load_class_mid =
      env->GetMethodID(class_loader_clazz, kClassLoader_loadClass,
                       kClassLoader_loadClass_String);
  return true;
}

JNIEnv *JniHelperImpl::GetEnv() const {
  JNIEnv *env;
  jint status = jvm_->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6);
  if (status == JNI_OK) {
    return env;
  }

  // Since we're calling AttachCurrentThread(), we're causing the JVM to be
  // associated with this thread. Accordingly, set up a thread destructor to
  // call DetachCurrentThread().
  LogD(kLogTag, "Attaching thread to JavaVM...");
  pthread_once(&pthread_key_initialized, SetupJvmDetachOnThreadDestruction);
  pthread_setspecific(jni_env_key, jvm_);

  status = AttachCurrentThread(jvm_, &env);
  if (status == JNI_OK) {
    LogD(kLogTag, "Attached thread to JavaVM.");
    return env;
  }

  LogE(kLogTag, "Failed to attach thread to JavaVM: %d", status);
  return nullptr;
}

jclass JniHelperImpl::GetClass(const char *class_name) const {
  return GetClass(GetEnv(), class_name);
}

jclass JniHelperImpl::GetClassGlobalRef(const char *class_name) const {
  JNIEnv *env = GetEnv();
  return static_cast<jclass>(env->NewGlobalRef(GetClass(env, class_name)));
}

jclass JniHelperImpl::GetClass(JNIEnv *env, const char *class_name) const {
  jstring name = env->NewStringUTF(class_name);
  jobject clazz = env->CallObjectMethod(class_loader_.object,
                                        class_loader_.load_class_mid, name);
  env->DeleteLocalRef(name);
  jthrowable throwable = env->ExceptionOccurred();
  if (throwable != nullptr) {
    env->ExceptionClear();
    jclass class_not_found_exception =
        env->FindClass("java/lang/ClassNotFoundException");
    if (env->IsInstanceOf(throwable, class_not_found_exception)) {
      LogE(kLogTag, "ClassNotFoundException: %s", class_name);
    } else {
      // Any exception other than ClassNotFoundException is unexpected,
      // so rethrow, likely crashing the app.
      env->Throw(throwable);
    }
    return nullptr;
  }
  return static_cast<jclass>(clazz);
}

}  // namespace common
}  // namespace gni
