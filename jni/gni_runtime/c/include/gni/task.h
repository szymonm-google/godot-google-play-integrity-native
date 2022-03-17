#ifndef C_GNI_TASK_H_
#define C_GNI_TASK_H_

#include "gni/task_error_codes.h"

#ifdef __cplusplus
extern "C" {
#endif

// An opaque struct used to represent an async operation.
typedef struct GniTask_ GniTask;

// A declaration of a callback that GniTask calls when the async task finishes.
// It's safe to destroy the GniTask struct inside the callback. The user_data
// has the same value as the user_data provided to
// GniTask_addOnCompleteCallback().
typedef void (*OnCompleteCallback)(GniTask* task, void* user_data);

// Returns true if the GniTask is complete; false otherwise.
bool GniTask_isComplete(const GniTask* task);

// Helper function that returns true if the task has finished successfully.
// The function is most useful when called from inside `OnCompleteCallback`.
bool GniTask_isSuccessful(const GniTask* task);

/// Sets the callback which will be called when the task completes (either
/// successfully or not). The callback will be called on the main thread. If the
/// task has already completed, a call to the callback will be immediately
/// scheduled.
/// @param task A task where the callback will be registered.
/// @param callback A callback that GniTask calls when the async task finishes.
/// @param user_data A user-defined pointer that will be forwarded to the
/// callback.
/// @return
/// GNI_TASK_SUCCESS - no error occurred
/// GNI_TASK_INVALID_TASK_POINTER - task is null or already destroyed.
/// GNI_TASK_INVALID_ARGUMENT - on_complete_callback is null.
GniTaskErrorCode GniTask_addOnCompleteCallback(
    GniTask* task, OnCompleteCallback on_complete_callback, void* user_data);

// Returns an error code for a task that failed, i.e. a task's status is
// `GNI_TASK_FAILED`.
GniTaskErrorCode GniTask_getErrorCode(const GniTask* task);

// Fills the argument `out_error_message` with an error message for a task that
// failed, i.e. a task's status is `GNI_TASK_FAILED`. A caller owns the returned
// string and needs to destroy it with GniString_destroy(). `out_error_message`
// will be null if there is no error message.
void GniTask_getErrorMessage(const GniTask* task,
                             const char** out_error_message);

// Destroys a task and all related resources.
void GniTask_destroy(GniTask* task);

#ifdef __cplusplus
};  // extern "C"
#endif

#endif  // C_GNI_TASK_H_
