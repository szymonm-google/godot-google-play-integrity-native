#include "IntegrityManager.hpp"
#include <memory>
#include "gni/common/scoped_local_ref.h"
#include "gni/gni.hpp"
#include "gni/object.hpp"
#include "gni/task.hpp"
#include "IntegrityTokenRequest.hpp"

namespace com {
namespace google {
namespace android {
namespace play {
namespace core {
namespace integrity {

namespace {

}

jclass IntegrityManager::GetClass()
{
  static const jclass cached_class = gni::GniCore::GetInstance()->GetClassGlobalRef("com/google/android/play/core/integrity/IntegrityManager");
  return cached_class;
}

void IntegrityManager::destroy(const IntegrityManager* object)
{
  delete object;
}

::gni::Task& IntegrityManager::requestIntegrityToken(const ::com::google::android::play::core::integrity::IntegrityTokenRequest& request) const
{
  JNIEnv *env = gni::GniCore::GetInstance()->GetJniEnv();
  static const jmethodID method_id = env->GetMethodID(GetClass(), "requestIntegrityToken", "(Lcom/google/android/play/core/integrity/IntegrityTokenRequest;)Lcom/google/android/gms/tasks/Task;");
  ::gni::Task* ret = new ::gni::Task(gni::common::ScopedLocalRef<jobject>(env, env->CallObjectMethod(::gni::Object::GetImpl(), method_id, request.GetImpl())).Get());
  return *ret;
}
}  // end namespace integrity
}  // end namespace core
}  // end namespace play
}  // end namespace android
}  // end namespace google
}  // end namespace com

