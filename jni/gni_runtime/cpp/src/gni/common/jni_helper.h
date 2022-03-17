#ifndef GNI_COMMON_JNI_HELPER_H_
#define GNI_COMMON_JNI_HELPER_H_

#include <jni.h>

namespace gni {
namespace common {

// Helper that enables JNI access across multiple threads by attaching
// the JNIEnv when necessary.
class JniHelper {
 public:
  // Returns the single instance for JniHelper, or nullptr if it failed to
  // initialize. Note: this object allocates relatively little Java or native
  // memory, so once created it's never destroyed.
  static JniHelper* GetInstance(JavaVM* jvm, jobject android_context);

  virtual ~JniHelper() = default;

  // Returns a JNIEnv pointer appropriate for the current thread.
  virtual JNIEnv* GetEnv() const = 0;

  // Returns a local reference to a jclass for the specified class name,
  // or nullptr if the class isn't found.
  virtual jclass GetClass(const char* class_name) const = 0;

  // Returns a global reference to a jclass for the specified class name,
  // or nullptr if the class isn't found.
  virtual jclass GetClassGlobalRef(const char* class_name) const = 0;

 protected:
  JniHelper() = default;

 private:
  JniHelper(const JniHelper&) = delete;
  JniHelper(JniHelper&&) = delete;
  JniHelper& operator=(const JniHelper&) = delete;
  JniHelper& operator=(JniHelper&&) = delete;
};

}  // namespace common
}  // namespace gni

#endif  // GNI_COMMON_JNI_HELPER_H_
