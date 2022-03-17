#include "gni/common/diagnostics.h"

#include <assert.h>
#include <jni.h>

#include "gni/gni.hpp"

namespace gni {
namespace common {

void DumpReferenceTables() {
  // This global reference is never released.
  static const jclass vm_class =
      gni::GniCore::GetInstance()->GetClassGlobalRef("android/os/Debug");
  assert(vm_class != nullptr);

  JNIEnv* env = gni::GniCore::GetInstance()->GetJniEnv();

  static const jmethodID dump_mid =
      env->GetStaticMethodID(vm_class, "dumpReferenceTables", "()V");
  assert(dump_mid != nullptr);

  env->CallStaticVoidMethod(vm_class, dump_mid);
}

}  // namespace common
}  // namespace gni
