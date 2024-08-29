// ======================================================================
// \title Os/Stub/FileSystem.hpp
// \brief stub fileSystem definitions for Os::FileSystem
// ======================================================================
#include "Os/FileSystem.hpp"

#ifndef OS_STUB_FILESYSTEM_HPP
#define OS_STUB_FILESYSTEM_HPP
namespace Os {
namespace Stub {
namespace FileSystem {

struct StubFileSystemHandle : public FileSystemHandle {};

//! \brief stub implementation of Os::FileSystem
//!
//! Stub implementation of `FileSystemInterface` for use as a delegate class handling error-only fileSystem operations.
//!
class StubFileSystem : public FileSystemInterface {
  public:
    //! \brief constructor
    //!
    StubFileSystem() = default;

    //! \brief destructor
    //!
    ~StubFileSystem() override = default;

    // ------------------------------------
    // Functions overrides
    // ------------------------------------

    //! \brief create a new directory at location path
    Status _createDirectory(const char* path) override;
    //! \brief remove a directory at location path
    Status _removeDirectory(const char* path) override;
    //! \brief removes a file at location path
    Status _removeFile(const char* path) override;
    //! \brief moves a file from origin to destination
    Status _moveFile(const char* originPath, const char* destPath) override;
    //! \brief copies a file from origin to destination
    // Status _copyFile(const char* originPath, const char* destPath) override;
    //! \brief append file origin to destination file. If boolean true, creates a brand new file if the destination doesn't exist.
    // Status _appendFile(const char* originPath, const char* destPath, bool createMissingDest=false) override;
    //! \brief gets the size of the file (in bytes) = 0 at location path
    Status _getFileSize(const char* path, FwSignedSizeType& size) override;
    //! \brief move current directory to path
    Status _changeWorkingDirectory(const char* path) override;
    //! \brief get FS free and total space in bytes on filesystem containing path
    Status _getFreeSpace(const char* path, FwSizeType& totalBytes, FwSizeType& freeBytes) override;



    //! \brief returns the raw fileSystem handle
    //!
    //! Gets the raw fileSystem handle from the implementation. Note: users must include the implementation specific
    //! header to make any real use of this handle. Otherwise it//!must* be passed as an opaque type.
    //!
    //! \return raw fileSystem handle
    //!
    FileSystemHandle *getHandle() override;


private:
    //! FileSystem handle for PosixFileSystem
    StubFileSystemHandle m_handle;
};

} // namespace FileSystem
} // namespace Stub
} // namespace Os
#endif // OS_STUB_FILESYSTEM_HPP
