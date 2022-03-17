#include "gni/object.hpp"

#include <assert.h>

#include "gni/gni.hpp"

namespace gni {

Object::Object(jobject object) {
  assert(object != nullptr);
  object_ = GniCore::GetInstance()->GetJniEnv()->NewGlobalRef(object);
}

Object::Object(Object&& object) {
  object_ = object.object_;
  object.object_ = nullptr;
}

Object::~Object() {
  GniCore::GetInstance()->GetJniEnv()->DeleteGlobalRef(object_);
}

}  // namespace gni
