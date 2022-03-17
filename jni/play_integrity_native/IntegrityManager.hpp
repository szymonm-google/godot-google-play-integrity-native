#ifndef CPP_COM_GOOGLE_ANDROID_PLAY_CORE_INTEGRITY_INTEGRITYMANAGER
#define CPP_COM_GOOGLE_ANDROID_PLAY_CORE_INTEGRITY_INTEGRITYMANAGER

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

class IntegrityManager : public ::gni::Object
{
public:
    static jclass GetClass();
    static void destroy(const IntegrityManager* object);
    explicit IntegrityManager(jobject jobj) : Object(jobj) {}
    virtual ~IntegrityManager() {}

    // Copy constructor: copy reference
    IntegrityManager(const IntegrityManager &other)
        : Object(other.GetImpl()) {}

    virtual ::gni::Task& requestIntegrityToken(const ::com::google::android::play::core::integrity::IntegrityTokenRequest& request) const;
};

}  // end namespace integrity
}  // end namespace core
}  // end namespace play
}  // end namespace android
}  // end namespace google
}  // end namespace com

#endif  // CPP_COM_GOOGLE_ANDROID_PLAY_CORE_INTEGRITY_INTEGRITYMANAGER
