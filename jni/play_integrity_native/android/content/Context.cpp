#include "android/content/Context.hpp"
#include <memory>
#include "gni/common/scoped_local_ref.h"
#include "gni/gni.hpp"
#include "gni/object.hpp"

namespace android {
namespace content {

namespace {

}

jclass Context::GetClass()
{
  static const jclass cached_class = gni::GniCore::GetInstance()->GetClassGlobalRef("android/content/Context");
  return cached_class;
}

void Context::destroy(const Context* object)
{
  delete object;
}
}  // end namespace content
}  // end namespace android

