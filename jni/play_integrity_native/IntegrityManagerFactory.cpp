#include "IntegrityManagerFactory.hpp"
#include <memory>
#include "gni/common/scoped_local_ref.h"
#include "gni/gni.hpp"
#include "gni/object.hpp"
#include "android/content/Context.hpp"
#include "IntegrityManager.hpp"

namespace com {
namespace google {
namespace android {
namespace play {
namespace core {
namespace integrity {

namespace {

}

jclass IntegrityManagerFactory::GetClass()
{
  static const jclass cached_class = gni::GniCore::GetInstance()->GetClassGlobalRef("com/google/android/play/core/integrity/IntegrityManagerFactory");
  return cached_class;
}

void IntegrityManagerFactory::destroy(const IntegrityManagerFactory* object)
{
  delete object;
}

::com::google::android::play::core::integrity::IntegrityManager& IntegrityManagerFactory::create(const ::android::content::Context& applicationContext) 
{
  JNIEnv *env = gni::GniCore::GetInstance()->GetJniEnv();
  static const jmethodID method_id = env->GetStaticMethodID(GetClass(), "create", "(Landroid/content/Context;)Lcom/google/android/play/core/integrity/IntegrityManager;");
  ::com::google::android::play::core::integrity::IntegrityManager* ret = new ::com::google::android::play::core::integrity::IntegrityManager(gni::common::ScopedLocalRef<jobject>(env, env->CallStaticObjectMethod(GetClass(), method_id, applicationContext.GetImpl())).Get());
  return *ret;
}
}  // end namespace integrity
}  // end namespace core
}  // end namespace play
}  // end namespace android
}  // end namespace google
}  // end namespace com

