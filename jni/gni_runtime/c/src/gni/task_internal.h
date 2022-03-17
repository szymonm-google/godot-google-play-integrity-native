#ifndef C_GNI_TASK_INTERNAL_H_
#define C_GNI_TASK_INTERNAL_H_

#include <jni.h>

#include "gni/task.h"
#include "gni/task_error_codes.h"

// Returns a `jobject` which represents the result of the successfully finished
// task. For internal use only.
GniTaskErrorCode GniTask_getResult(const GniTask* task,
                                   jobject* out_result_object);

#endif  // C_GNI_TASK_INTERNAL_H_
