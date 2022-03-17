#ifndef GNI_COMMON_JNI_HELPER_IMPL_H_
#define GNI_COMMON_JNI_HELPER_IMPL_H_

#include "gni/common/jni_helper.h"

namespace gni {
namespace common {

class JniHelperImpl : public JniHelper {
 public:
  ~JniHelperImpl() override = default;

  // This method must be called to initialize the instance before any other
  // methods can be called.
  bool Initialize(JavaVM* jvm, jobject android_context);

  JNIEnv* GetEnv() const override;
  jclass GetClass(const char* class_name) const override;
  jclass GetClassGlobalRef(const char* class_name) const override;

 private:
  jclass GetClass(JNIEnv* env, const char* class_name) const;

  JavaVM* jvm_;

  // Holds a global refrence to an Android Application Context's ClassLoader.
  // This global reference is never released.
  struct JavaClassLoader {
    jobject object;
    jmethodID load_class_mid;
  } class_loader_;
};

}  // namespace common
}  // namespace gni

#endif  // GNI_COMMON_JNI_HELPER_IMPL_H_
