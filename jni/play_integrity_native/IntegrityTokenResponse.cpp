#include "IntegrityTokenResponse.hpp"
#include <memory>
#include "gni/common/scoped_local_ref.h"
#include "gni/gni.hpp"
#include "gni/object.hpp"

namespace com {
namespace google {
namespace android {
namespace play {
namespace core {
namespace integrity {

namespace {
jobject CreateJavaIntegrityTokenResponseObject() {
  JNIEnv *env = gni::GniCore::GetInstance()->GetJniEnv();
  static const jmethodID method_id = env->GetMethodID(IntegrityTokenResponse::GetClass(), "<init>", "()V");
  return env->NewObject(IntegrityTokenResponse::GetClass(), method_id);
}


}

jclass IntegrityTokenResponse::GetClass()
{
  static const jclass cached_class = gni::GniCore::GetInstance()->GetClassGlobalRef("com/google/android/play/core/integrity/IntegrityTokenResponse");
  return cached_class;
}

void IntegrityTokenResponse::destroy(const IntegrityTokenResponse* object)
{
  delete object;
}

IntegrityTokenResponse::IntegrityTokenResponse() : Object(gni::common::ScopedLocalRef<jobject>(gni::GniCore::GetInstance()->GetJniEnv(), CreateJavaIntegrityTokenResponseObject()).Get()) {}

const char* IntegrityTokenResponse::token() const
{
  JNIEnv *env = gni::GniCore::GetInstance()->GetJniEnv();
  static const jmethodID method_id = env->GetMethodID(GetClass(), "token", "()Ljava/lang/String;");
  const char* ret = gni::GniCore::GetInstance()->ConvertString(env->CallObjectMethod(::gni::Object::GetImpl(), method_id));
  return ret;
}

jclass IntegrityTokenResponse::Builder::GetClass()
{
  static const jclass cached_class = gni::GniCore::GetInstance()->GetClassGlobalRef("com/google/android/play/core/integrity/IntegrityTokenResponse$Builder");
  return cached_class;
}

void IntegrityTokenResponse::Builder::destroy(const IntegrityTokenResponse::Builder* object)
{
  delete object;
}

}  // end namespace integrity
}  // end namespace core
}  // end namespace play
}  // end namespace android
}  // end namespace google
}  // end namespace com

