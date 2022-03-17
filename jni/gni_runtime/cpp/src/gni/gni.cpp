#include "gni/gni.hpp"

#include <pthread.h>
#include <stdlib.h>

#include <cstring>

#include "gni/common/jni_helper.h"
#include "gni/common/logger.h"

namespace gni {

namespace {
constexpr char kLogTag[] = "GniCore";
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
bool initialized;
GniCore* gni_core_instance;

common::JniHelper* GetJniHelper() {
  // Passing nullptr arguments because they are not used except in a very first
  // call, which was already made in Init() method.
  return common::JniHelper::GetInstance(nullptr, nullptr);
}
}  // namespace

// Initializes the GniCore in a test environment. Call it instead of
// GniCore::Init() when testing.
void InitGniCoreForTests(GniCore* gni_core) {
  gni_core_instance = gni_core;
  initialized = true;
}

void GniCore::Init(JavaVM* java_vm, jobject android_context) {
  pthread_mutex_lock(&lock);
  if (!initialized) {
    // Immediately initialize JniHelper singleton, so we don't have to store
    // java_vm and android_context.
    common::JniHelper::GetInstance(java_vm, android_context);
    initialized = true;
  }
  pthread_mutex_unlock(&lock);
}

GniCore* GniCore::GetInstance() {
  pthread_mutex_lock(&lock);
  if (gni_core_instance == nullptr) {
    if (!initialized) {
      pthread_mutex_unlock(&lock);
      common::LogE(kLogTag, "Call GniCore::Init() first.");
      return nullptr;
    }
    gni_core_instance = new GniCore();
  }
  pthread_mutex_unlock(&lock);
  return gni_core_instance;
}

jclass GniCore::GetClassGlobalRef(const char* class_name) const {
  return GetJniHelper()->GetClassGlobalRef(class_name);
}

JNIEnv* GniCore::GetJniEnv() const { return GetJniHelper()->GetEnv(); }

const char* GniCore::ConvertString(jstring rhs) const {
  JNIEnv* env = GetJniEnv();
  const char* temp_string = env->GetStringUTFChars(rhs, nullptr);
  const char* ret = strdup(temp_string);
  env->ReleaseStringUTFChars(rhs, temp_string);
  return ret;
}

const char* GniCore::ConvertString(jobject rhs) const {
  return ConvertString(reinterpret_cast<jstring>(rhs));
}

Object GniCore::ConvertString(const char* rhs) const {
  return Object(GetJniEnv()->NewStringUTF(rhs));
}

const char* GniCore::ConvertUri(jobject rhs) const {
  JNIEnv* env = GetJniEnv();

  static jclass uri_class = GetClassGlobalRef("android/net/Uri");
  static jmethodID to_string_method_id =
      env->GetMethodID(uri_class, "toString", "()Ljava/lang/String;");

  jstring uri_string = reinterpret_cast<jstring>(
      env->CallObjectMethod(rhs, to_string_method_id));

  const char* ret = ConvertString(uri_string);

  env->DeleteLocalRef(uri_string);

  return ret;
}

Object GniCore::Convert(jobject rhs) const { return Object(rhs); }

jint GniCore::Convert(jint rhs) const { return rhs; }

extern "C" void GniString_destroy(const char* value) {
  free(const_cast<char*>(value));
}

}  // namespace gni
