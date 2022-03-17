#include <android/log.h>

#include <cstdarg>

#include "gni/common/logger.h"

namespace gni {
namespace common {

void LogD(const char* tag, const char* format, ...) {
  va_list args;
  va_start(args, format);
  __android_log_vprint(ANDROID_LOG_DEBUG, tag, format, args);
  va_end(args);
}

void LogI(const char* tag, const char* format, ...) {
  va_list args;
  va_start(args, format);
  __android_log_vprint(ANDROID_LOG_INFO, tag, format, args);
  va_end(args);
}

void LogW(const char* tag, const char* format, ...) {
  va_list args;
  va_start(args, format);
  __android_log_vprint(ANDROID_LOG_WARN, tag, format, args);
  va_end(args);
}

void LogE(const char* tag, const char* format, ...) {
  va_list args;
  va_start(args, format);
  __android_log_vprint(ANDROID_LOG_ERROR, tag, format, args);
  va_end(args);
}

}  // namespace common
}  // namespace gni
