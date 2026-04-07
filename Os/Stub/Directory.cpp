// ======================================================================
// \title Os/Stub/Directory.cpp
// \brief stub implementation for Os::Directory
// ======================================================================
#include "Os/Stub/Directory.hpp"
#include <cstdio>

namespace Os {
namespace Stub {
namespace Directory {

StubDirectory::Status StubDirectory::open(const char* path, OpenMode mode) {
    printf("STUB DIRECTORY: open() called with path %s and mode %d but not supported in stub implementation\n", path,
           mode);
    return Status::NOT_SUPPORTED;
}

StubDirectory::Status StubDirectory::rewind() {
    printf("STUB DIRECTORY: rewind() called but not supported in stub implementation\n");
    return Status::NOT_SUPPORTED;
}

StubDirectory::Status StubDirectory::read(char* fileNameBuffer, FwSizeType bufSize) {
    printf("STUB DIRECTORY: read() called but not supported in stub implementation\n");
    return Status::NOT_SUPPORTED;
}

void StubDirectory::close() {
    printf("STUB DIRECTORY: close() called but not supported in stub implementation\n");
    // no-op
}

DirectoryHandle* StubDirectory::getHandle() {
    return &this->m_handle;
}

}  // namespace Directory
}  // namespace Stub
}  // namespace Os
