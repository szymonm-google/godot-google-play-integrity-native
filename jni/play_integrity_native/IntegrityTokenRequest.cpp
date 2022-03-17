#include "IntegrityTokenRequest.hpp"
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
jobject CreateJavaIntegrityTokenRequestObject() {
  JNIEnv *env = gni::GniCore::GetInstance()->GetJniEnv();
  static const jmethodID method_id = env->GetMethodID(IntegrityTokenRequest::GetClass(), "<init>", "()V");
  return env->NewObject(IntegrityTokenRequest::GetClass(), method_id);
}

jobject CreateJavaIntegrityTokenRequestBuilderObject() {
  JNIEnv *env = gni::GniCore::GetInstance()->GetJniEnv();
  static const jmethodID method_id = env->GetMethodID(IntegrityTokenRequest::Builder::GetClass(), "<init>", "()V");
  return env->NewObject(IntegrityTokenRequest::Builder::GetClass(), method_id);
}
}

jclass IntegrityTokenRequest::GetClass()
{
  static const jclass cached_class = gni::GniCore::GetInstance()->GetClassGlobalRef("com/google/android/play/core/integrity/IntegrityTokenRequest");
  return cached_class;
}

void IntegrityTokenRequest::destroy(const IntegrityTokenRequest* object)
{
  delete object;
}

IntegrityTokenRequest::IntegrityTokenRequest() : Object(gni::common::ScopedLocalRef<jobject>(gni::GniCore::GetInstance()->GetJniEnv(), CreateJavaIntegrityTokenRequestObject()).Get()) {}

const char* IntegrityTokenRequest::nonce() const
{
  JNIEnv *env = gni::GniCore::GetInstance()->GetJniEnv();
  static const jmethodID method_id = env->GetMethodID(GetClass(), "nonce", "()Ljava/lang/String;");
  const char* ret = gni::GniCore::GetInstance()->ConvertString(env->CallObjectMethod(::gni::Object::GetImpl(), method_id));
  return ret;
}

//int64_t IntegrityTokenRequest::cloudProjectNumber() const
//{
//  JNIEnv *env = gni::GniCore::GetInstance()->GetJniEnv();
//  static const jmethodID method_id = env->GetMethodID(GetClass(), "cloudProjectNumber", "()Ljava/lang/Long;");
//  int64_t ret = env->CallObjectMethod(::gni::Object::GetImpl(), method_id);
//  return ret;
//}

::com::google::android::play::core::integrity::IntegrityTokenRequest::Builder& IntegrityTokenRequest::builder() 
{
  JNIEnv *env = gni::GniCore::GetInstance()->GetJniEnv();
  static const jmethodID method_id = env->GetStaticMethodID(GetClass(), "builder", "()Lcom/google/android/play/core/integrity/IntegrityTokenRequest$Builder;");
  ::com::google::android::play::core::integrity::IntegrityTokenRequest::Builder* ret = new ::com::google::android::play::core::integrity::IntegrityTokenRequest::Builder(gni::common::ScopedLocalRef<jobject>(env, env->CallStaticObjectMethod(GetClass(), method_id)).Get());
  return *ret;
}

jclass IntegrityTokenRequest::Builder::GetClass()
{
  static const jclass cached_class = gni::GniCore::GetInstance()->GetClassGlobalRef("com/google/android/play/core/integrity/IntegrityTokenRequest$Builder");
  return cached_class;
}

void IntegrityTokenRequest::Builder::destroy(const IntegrityTokenRequest::Builder* object)
{
  delete object;
}

IntegrityTokenRequest::Builder::Builder() : Object(gni::common::ScopedLocalRef<jobject>(gni::GniCore::GetInstance()->GetJniEnv(), CreateJavaIntegrityTokenRequestBuilderObject()).Get()) {}

::com::google::android::play::core::integrity::IntegrityTokenRequest::Builder& IntegrityTokenRequest::Builder::setNonce(const char* nonce) const
{
  JNIEnv *env = gni::GniCore::GetInstance()->GetJniEnv();
  static const jmethodID method_id = env->GetMethodID(GetClass(), "setNonce", "(Ljava/lang/String;)Lcom/google/android/play/core/integrity/IntegrityTokenRequest$Builder;");
  ::com::google::android::play::core::integrity::IntegrityTokenRequest::Builder* ret = new ::com::google::android::play::core::integrity::IntegrityTokenRequest::Builder(gni::common::ScopedLocalRef<jobject>(env, env->CallObjectMethod(::gni::Object::GetImpl(), method_id, gni::GniCore::GetInstance()->ConvertString(nonce).GetImpl())).Get());
  return *ret;
}

::com::google::android::play::core::integrity::IntegrityTokenRequest::Builder& IntegrityTokenRequest::Builder::setCloudProjectNumber(jlong cloudProjectNumber) const
{
  JNIEnv *env = gni::GniCore::GetInstance()->GetJniEnv();
  static const jmethodID method_id = env->GetMethodID(GetClass(), "setCloudProjectNumber", "(J)Lcom/google/android/play/core/integrity/IntegrityTokenRequest$Builder;");
  ::com::google::android::play::core::integrity::IntegrityTokenRequest::Builder* ret = new ::com::google::android::play::core::integrity::IntegrityTokenRequest::Builder(gni::common::ScopedLocalRef<jobject>(env, env->CallObjectMethod(::gni::Object::GetImpl(), method_id, gni::GniCore::GetInstance()->Convert(cloudProjectNumber))).Get());
  return *ret;
}

::com::google::android::play::core::integrity::IntegrityTokenRequest& IntegrityTokenRequest::Builder::build() const
{
  JNIEnv *env = gni::GniCore::GetInstance()->GetJniEnv();
  static const jmethodID method_id = env->GetMethodID(GetClass(), "build", "()Lcom/google/android/play/core/integrity/IntegrityTokenRequest;");
  ::com::google::android::play::core::integrity::IntegrityTokenRequest* ret = new ::com::google::android::play::core::integrity::IntegrityTokenRequest(gni::common::ScopedLocalRef<jobject>(env, env->CallObjectMethod(::gni::Object::GetImpl(), method_id)).Get());
  return *ret;
}

}  // end namespace integrity
}  // end namespace core
}  // end namespace play
}  // end namespace android
}  // end namespace google
}  // end namespace com

