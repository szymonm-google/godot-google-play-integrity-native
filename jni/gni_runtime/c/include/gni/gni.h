#ifndef C_GNI_H_
#define C_GNI_H_

#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

/// Initializes the GNI runtime. Call this function before calling other
/// GNI functions.
void GniCore_init(JavaVM* java_vm, jobject android_context);

/// Frees the specified string that was previously allocated by a GNI API call.
void GniString_destroy(const char* value);

#ifdef __cplusplus
};  // extern "C"
#endif

#endif  // C_GNI_H_
