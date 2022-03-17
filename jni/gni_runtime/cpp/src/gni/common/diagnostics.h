#ifndef GNI_COMMON_DIAGNOSTICS_H_
#define GNI_COMMON_DIAGNOSTICS_H_

namespace gni {
namespace common {

// Dumps the contents of the VM reference tables (e.g. JNI locals and globals)
// of the current thread to the log file.
void DumpReferenceTables();

}  // namespace common
}  // namespace gni

#endif  // GNI_COMMON_DIAGNOSTICS_H_
