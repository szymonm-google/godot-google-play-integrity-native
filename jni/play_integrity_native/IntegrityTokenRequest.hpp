#ifndef CPP_COM_GOOGLE_ANDROID_PLAY_CORE_INTEGRITY_INTEGRITYTOKENREQUEST
#define CPP_COM_GOOGLE_ANDROID_PLAY_CORE_INTEGRITY_INTEGRITYTOKENREQUEST

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

class IntegrityTokenRequest : public ::gni::Object
{
public:
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

        explicit Builder();
        virtual ::com::google::android::play::core::integrity::IntegrityTokenRequest::Builder& setNonce(const char* nonce) const;
        virtual ::com::google::android::play::core::integrity::IntegrityTokenRequest::Builder& setCloudProjectNumber(jlong cloudProjectNumber) const;
        virtual ::com::google::android::play::core::integrity::IntegrityTokenRequest& build() const;
    };

    static jclass GetClass();
    static void destroy(const IntegrityTokenRequest* object);
    explicit IntegrityTokenRequest(jobject jobj) : Object(jobj) {}
    virtual ~IntegrityTokenRequest() {}

    // Copy constructor: copy reference
    IntegrityTokenRequest(const IntegrityTokenRequest &other)
        : Object(other.GetImpl()) {}

    explicit IntegrityTokenRequest();
    virtual const char* nonce() const;
    // virtual int64_t cloudProjectNumber() const;
    static ::com::google::android::play::core::integrity::IntegrityTokenRequest::Builder& builder() ;
};

}  // end namespace integrity
}  // end namespace core
}  // end namespace play
}  // end namespace android
}  // end namespace google
}  // end namespace com

#endif  // CPP_COM_GOOGLE_ANDROID_PLAY_CORE_INTEGRITY_INTEGRITYTOKENREQUEST
