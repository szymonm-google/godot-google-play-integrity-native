#ifndef CPP_GNI_COMMON_JNI_BOXED_TYPE_UTIL_H_
#define CPP_GNI_COMMON_JNI_BOXED_TYPE_UTIL_H_

#include <jni.h>

#include <cstdint>

namespace gni {
namespace common {
namespace jni_boxed_type_util {

// This file contains helper functions that get value from Java boxed types,
// such as Integer, Boolean, etc.
//
// Functions don't validate provided `jobj` argument against its
// referenced Java type, e.g. `GetLong(jobj)` can only be called with `jobj`
// referencing Java `Long` type. Calling a function with the wrong argument
// throws `NoSuchMethodError` in Java runtime.
//
// An app aborts when `jobj` is `nullptr`.

bool GetBoolean(jobject jobj);
int8_t GetByte(jobject jobj);
uint16_t GetCharacter(jobject jobj);
int16_t GetShort(jobject jobj);
int32_t GetInteger(jobject jobj);
int64_t GetLong(jobject jobj);
float GetFloat(jobject jobj);
double GetDouble(jobject jobj);

}  // namespace jni_boxed_type_util
}  // namespace common
}  // namespace gni

#endif  // CPP_GNI_COMMON_JNI_BOXED_TYPE_UTIL_H_
