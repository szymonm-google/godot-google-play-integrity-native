#ifndef CPP_ANDROID_CONTENT_CONTEXT
#define CPP_ANDROID_CONTENT_CONTEXT

#include <memory>
#include "gni/common/scoped_local_ref.h"
#include "gni/gni.hpp"
#include "gni/object.hpp"

namespace android {
namespace content {

class Context : public ::gni::Object
{
public:
    static jclass GetClass();
    static void destroy(const Context* object);
    explicit Context(jobject jobj) : Object(jobj) {}
    virtual ~Context() {}

    // Copy constructor: copy reference
    Context(const Context &other)
        : Object(other.GetImpl()) {}

};

}  // end namespace content
}  // end namespace android

#endif  // CPP_ANDROID_CONTENT_CONTEXT
