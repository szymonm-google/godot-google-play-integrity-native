#include "gni/gni.h"

#include "gni/gni.hpp"

void GniCore_init(JavaVM* java_vm, jobject android_context) {
  gni::GniCore::Init(java_vm, android_context);
}
