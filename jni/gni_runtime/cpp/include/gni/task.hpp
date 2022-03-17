#ifndef CPP_GNI_TASK_H_
#define CPP_GNI_TASK_H_

#include <jni.h>
#include <pthread.h>

#include "gni/task_error_codes.h"

namespace gni {

// A native wrapper for Java com.google.android.gms.tasks.Task class.
class Task {
 public:
  using OnCompleteCallback = void (*)(Task* task, void* user_data);

  // Destroys the task. C APIs should use this method instead of destroying a
  // task object explicitly by using delete or free().
  static void Destroy(Task* task);

  explicit Task(jobject task_object);
  virtual ~Task();
  Task(const Task&) = delete;
  Task& operator=(const Task&) = delete;

  /// Registers on-complete callback.
  /// @param on_complete_callback A callback that Task calls when the async
  /// task finishes.
  /// @param user_data A user-defined pointer that will be forwarded to the
  /// on_complete_callback.
  virtual void AddOnCompleteCallback(OnCompleteCallback on_complete_callback,
                                     void* user_data);

  // Java calls this method indirectly when the managed Task finishes.
  // `error_message` needs to be encoded in true, unmodified UTF-8.
  virtual void HandleOnComplete(jobject result_object, bool is_successful,
                                bool is_canceled, jstring error_message);

  // Returns true if the Task is complete; false otherwise.
  virtual bool IsComplete() const;

  // Returns true if the Task is complete and succesful; false otherwise.
  virtual bool IsSuccessful() const;

  // Returns true if the Task was cancelled; false otherwise.
  virtual bool IsCanceled() const;

  // Returns a global reference to Task result. Returns nullptr if the task
  // hasn't completed, failed or was canceled.
  virtual jobject GetResultObject() const;

  // Returns an error message for the task that has failed; empty string
  // otherwise. A caller owns the returned string and needs to destroy it with
  // GniString_destroy().
  virtual const char* GetErrorMessage() const;

  // Returns an error code for the task that has failed.
  virtual GniTaskErrorCode GetErrorCode() const;

 protected:
  Task() = default;

 private:
  // Returns a value pointed by the variable_ptr. The mutex protects the access
  // to the *variable_ptr during the read.
  template <typename T>
  T AtomicGet(T* variable_ptr) const {
    pthread_mutex_lock(&instance_mutex_);
    T value = *variable_ptr;
    pthread_mutex_unlock(&instance_mutex_);
    return value;
  }

  mutable pthread_mutex_t instance_mutex_;

  // A callback that is called when the Task finishes (successfully or not).
  OnCompleteCallback on_complete_callback_;

  // A stored user data provided to AddOnCompleteCallback() function. The
  // variable is an argument in on_complete_callback_ call.
  void* user_data_ = nullptr;

  // A global reference to Java Task object.
  jobject task_object_ = nullptr;

  bool is_complete_ = false;
  bool is_successful_ = false;
  bool is_canceled_ = false;
  jobject result_object_ = nullptr;
  const char* error_message_ = nullptr;
  GniTaskErrorCode error_code_ = GNI_TASK_STILL_RUNNING;
};

}  // namespace gni

#endif  // CPP_GNI_TASK_H_
