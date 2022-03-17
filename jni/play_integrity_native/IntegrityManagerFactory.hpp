#ifndef CPP_COM_GOOGLE_ANDROID_PLAY_CORE_INTEGRITY_INTEGRITYMANAGERFACTORY
#define CPP_COM_GOOGLE_ANDROID_PLAY_CORE_INTEGRITY_INTEGRITYMANAGERFACTORY

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

class IntegrityManagerFactory : public ::gni::Object
{
public:
    static jclass GetClass();
    static void destroy(const IntegrityManagerFactory* object);
    explicit IntegrityManagerFactory(jobject jobj) : Object(jobj) {}
    virtual ~IntegrityManagerFactory() {}

    // Copy constructor: copy reference
    IntegrityManagerFactory(const IntegrityManagerFactory &other)
        : Object(other.GetImpl()) {}

    static ::com::google::android::play::core::integrity::IntegrityManager& create(const ::android::content::Context& applicationContext) ;
};

}  // end namespace integrity
}  // end namespace core
}  // end namespace play
}  // end namespace android
}  // end namespace google
}  // end namespace com

#endif  // CPP_COM_GOOGLE_ANDROID_PLAY_CORE_INTEGRITY_INTEGRITYMANAGERFACTORY
