#ifndef CPP_JAVA_LANG_THROWABLE
#define CPP_JAVA_LANG_THROWABLE

#include <memory>
#include "gni/common/scoped_local_ref.h"
#include "gni/gni.hpp"
#include "gni/object.hpp"

namespace java {
namespace lang {

class Throwable : public ::gni::Object
{
public:
    static jclass GetClass();
    static void destroy(const Throwable* object);
    explicit Throwable(jobject jobj) : Object(jobj) {}
    virtual ~Throwable() {}

    // Copy constructor: copy reference
    Throwable(const Throwable &other)
        : Object(other.GetImpl()) {}

};

}  // end namespace lang
}  // end namespace java

#endif  // CPP_JAVA_LANG_THROWABLE
