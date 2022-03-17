#include "gni/task.h"

#include "gni/common/logger.h"
#include "gni/task.hpp"
#include "gni/task_internal.h"

using ::gni::Task;

const char kGniTaskLogTag[] = "GniTask";

void GniTask_destroy(GniTask* task) {
  Task::Destroy(reinterpret_cast<Task*>(task));
}

bool GniTask_isComplete(const GniTask* task) {
  if (task == nullptr) {
    gni::common::LogW(kGniTaskLogTag, "The argument \"task\" is nullptr.");
    return false;
  }

  return reinterpret_cast<const Task*>(task)->IsComplete();
}

bool GniTask_isSuccessful(const GniTask* task) {
  if (task == nullptr) {
    gni::common::LogW(kGniTaskLogTag, "The argument \"task\" is nullptr.");
    return false;
  }

  return reinterpret_cast<const Task*>(task)->IsSuccessful();
}

GniTaskErrorCode GniTask_getErrorCode(const GniTask* task) {
  if (task == nullptr) {
    return GNI_TASK_INVALID_TASK_POINTER;
  }

  return reinterpret_cast<const Task*>(task)->GetErrorCode();
}

void GniTask_getErrorMessage(const GniTask* task,
                             const char** out_error_message) {
  if (task == nullptr) {
    *out_error_message = nullptr;
    return;
  }

  *out_error_message = reinterpret_cast<const Task*>(task)->GetErrorMessage();
}

GniTaskErrorCode GniTask_addOnCompleteCallback(
    GniTask* task, OnCompleteCallback on_complete_callback, void* user_data) {
  if (task == nullptr) {
    return GNI_TASK_INVALID_TASK_POINTER;
  }

  if (on_complete_callback == nullptr) {
    return GNI_TASK_INVALID_ARGUMENT;
  }

  Task* cpp_task = reinterpret_cast<Task*>(task);

  cpp_task->AddOnCompleteCallback(
      // Functions Task::OnCompleteCallback and OnCompleteCallback have the same
      // signature, but are represented by a different typedefs.
      reinterpret_cast<Task::OnCompleteCallback>(on_complete_callback),
      user_data);

  return GNI_TASK_SUCCESS;
}

GniTaskErrorCode GniTask_getResult(const GniTask* task,
                                   jobject* out_result_object) {
  if (task == nullptr) {
    return GNI_TASK_INVALID_TASK_POINTER;
  }

  const Task* cpp_task = reinterpret_cast<const Task*>(task);

  if (!cpp_task->IsComplete()) {
    return GNI_TASK_STILL_RUNNING;
  }

  *out_result_object = cpp_task->GetResultObject();

  return GNI_TASK_SUCCESS;
}
