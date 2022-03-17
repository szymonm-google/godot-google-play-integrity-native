#ifndef CPP_COM_GOOGLE_ANDROID_PLAY_CORE_INTEGRITY_INTEGRITYTOKENRESPONSE
#define CPP_COM_GOOGLE_ANDROID_PLAY_CORE_INTEGRITY_INTEGRITYTOKENRESPONSE

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

class IntegrityTokenResponse : public ::gni::Object
{
public:
    static jclass GetClass();
    static void destroy(const IntegrityTokenResponse* object);
    explicit IntegrityTokenResponse(jobject jobj) : Object(jobj) {}
    virtual ~IntegrityTokenResponse() {}

    // Copy constructor: copy reference
    IntegrityTokenResponse(const IntegrityTokenResponse &other)
        : Object(other.GetImpl()) {}

    explicit IntegrityTokenResponse();
    virtual const char* token() const;

    class Builder : public ::gni::Object
    {
    public:
        static jclass GetClass();
        static void destroy(const Builder* object);
        explicit Builder(jobject jobj) : Object(jobj) {}
        virtual ~Builder() {}

        // Copy constructor: copy reference
        Builder(const Builder &other)
            : Object(other.GetImpl()) {}

    };
};

}  // end namespace integrity
}  // end namespace core
}  // end namespace play
}  // end namespace android
}  // end namespace google
}  // end namespace com

#endif  // CPP_COM_GOOGLE_ANDROID_PLAY_CORE_INTEGRITY_INTEGRITYTOKENRESPONSE
