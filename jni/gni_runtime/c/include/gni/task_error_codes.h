#ifndef C_GNI_TASK_ERROR_CODES_H_
#define C_GNI_TASK_ERROR_CODES_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// Represents error codes returned by GniTask functions and related services.
typedef int32_t GniTaskErrorCode;

// An operation finished sucessfully.
extern const GniTaskErrorCode GNI_TASK_SUCCESS;

// A task is still running.
extern const GniTaskErrorCode GNI_TASK_STILL_RUNNING;

// A task was canceled.
extern const GniTaskErrorCode GNI_TASK_CANCELED;

// A unknown error occurred.
extern const GniTaskErrorCode GNI_TASK_UNKNOWN_ERROR;

// One or more arguments are invalid.
extern const GniTaskErrorCode GNI_TASK_INVALID_ARGUMENT;

// GniTask pointer is invalid.
extern const GniTaskErrorCode GNI_TASK_INVALID_TASK_POINTER;

#ifdef __cplusplus
};  // extern "C"
#endif

#endif  // C_GNI_TASK_ERROR_CODES_H_
