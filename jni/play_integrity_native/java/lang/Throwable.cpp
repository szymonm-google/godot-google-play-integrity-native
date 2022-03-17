#include "java/lang/Throwable.hpp"
#include <memory>
#include "gni/common/scoped_local_ref.h"
#include "gni/gni.hpp"
#include "gni/object.hpp"

namespace java {
namespace lang {

namespace {

}

jclass Throwable::GetClass()
{
  static const jclass cached_class = gni::GniCore::GetInstance()->GetClassGlobalRef("java/lang/Throwable");
  return cached_class;
}

void Throwable::destroy(const Throwable* object)
{
  delete object;
}
}  // end namespace lang
}  // end namespace java

