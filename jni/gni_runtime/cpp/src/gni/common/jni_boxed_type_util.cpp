#include "gni/common/jni_boxed_type_util.h"

#include <jni.h>
#include <stdlib.h>

#include "gni/common/logger.h"
#include "gni/gni.hpp"

namespace gni {
namespace common {
namespace jni_boxed_type_util {
namespace {

constexpr char kLogTag[] = "JniBoxedType";

// A helper class for getting a value from Java boxed primitive types. This
// class is intended to be used internally, referenced by a function-scoped
// static pointer. Once an object of this class is created, it never gets
// destroyed and a global reference to the corresponding Java boxed primitive is
// never deleted.
template <typename T>
class JniBoxedType final {
 public:
  using JniEnvValueGetter = T (JNIEnv::*)(jobject, jmethodID, ...);

  JniBoxedType(const char* java_type_name, const char* java_getter_name,
               const char* java_getter_sig,
               JniEnvValueGetter jni_env_value_getter)
      : jni_env_value_getter_(jni_env_value_getter) {
    cls_ = GniCore::GetInstance()->GetClassGlobalRef(java_type_name);
    if (cls_ == nullptr) {
      // This situation is unlikely because we are querying classes form
      // build-in java.lang.* package.
      ::gni::common::LogE(kLogTag, "Class reference invalid.");
      abort();
    }

    getter_method_id_ = GniCore::GetInstance()->GetJniEnv()->GetMethodID(
        cls_, java_getter_name, java_getter_sig);
    if (getter_method_id_ == nullptr) {
      ::gni::common::LogE(kLogTag, "Getter method reference invalid.");
      abort();
    }
  }

  T GetValue(jobject jobj) const {
    if (jobj == nullptr) {
      ::gni::common::LogE(kLogTag, "Invalid instance reference.");
      abort();
    }

    return (GniCore::GetInstance()->GetJniEnv()->*jni_env_value_getter_)(
        jobj, getter_method_id_);
  }

 private:
  JniEnvValueGetter jni_env_value_getter_;
  jclass cls_;
  jmethodID getter_method_id_;
};

}  // namespace

bool GetBoolean(jobject jobj) {
  static const auto* const boxed_type = new JniBoxedType<uint8_t>(
      "java/lang/Boolean", "booleanValue", "()Z", &JNIEnv::CallBooleanMethod);

  return boxed_type->GetValue(jobj);
}

int8_t GetByte(jobject jobj) {
  static const auto* const boxed_type = new JniBoxedType<int8_t>(
      "java/lang/Byte", "byteValue", "()B", &JNIEnv::CallByteMethod);

  return boxed_type->GetValue(jobj);
}

uint16_t GetCharacter(jobject jobj) {
  static const auto* const boxed_type = new JniBoxedType<uint16_t>(
      "java/lang/Character", "charValue", "()C", &JNIEnv::CallCharMethod);

  return boxed_type->GetValue(jobj);
}

int16_t GetShort(jobject jobj) {
  static const auto* const boxed_type = new JniBoxedType<int16_t>(
      "java/lang/Short", "shortValue", "()S", &JNIEnv::CallShortMethod);

  return boxed_type->GetValue(jobj);
}

int32_t GetInteger(jobject jobj) {
  static const auto* const boxed_type = new JniBoxedType<int32_t>(
      "java/lang/Integer", "intValue", "()I", &JNIEnv::CallIntMethod);

  return boxed_type->GetValue(jobj);
}

int64_t GetLong(jobject jobj) {
  static const auto* const boxed_type = new JniBoxedType<int64_t>(
      "java/lang/Long", "longValue", "()J", &JNIEnv::CallLongMethod);

  return boxed_type->GetValue(jobj);
}

float GetFloat(jobject jobj) {
  static const auto* const boxed_type = new JniBoxedType<float>(
      "java/lang/Float", "floatValue", "()F", &JNIEnv::CallFloatMethod);

  return boxed_type->GetValue(jobj);
}

double GetDouble(jobject jobj) {
  static const auto* const boxed_type = new JniBoxedType<double>(
      "java/lang/Double", "doubleValue", "()D", &JNIEnv::CallDoubleMethod);

  return boxed_type->GetValue(jobj);
}

}  // namespace jni_boxed_type_util
}  // namespace common
}  // namespace gni
