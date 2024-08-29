#ifndef _OS_FILESYSTEM_HPP_
#define _OS_FILESYSTEM_HPP_

#include <FpConfig.hpp>
#include <config/FppConstantsAc.hpp>
#include <Os/Os.hpp>
#include <Os/Directory.hpp>
#include <Os/File.hpp>

#define FILE_SYSTEM_CHUNK_SIZE (256u)

namespace Os {

struct FileSystemHandle {};

class FileSystemInterface {
  public:
    static constexpr FwSizeType FPP_CONFIG_FILENAME_MAX_SIZE = FppConstant_FileNameStringSize::FileNameStringSize;

    typedef enum {
        OP_OK, //!<  Operation was successful
        ALREADY_EXISTS, //!<  File already exists
        NO_SPACE, //!<  No space left
        NO_PERMISSION, //!<  No permission to write
        NOT_DIR, //!<  Path is not a directory
        IS_DIR, //!< Path is a directory
        NOT_EMPTY, //!<  directory is not empty
        INVALID_PATH, //!< Path is too long, too many sym links, doesn't exist, ect
        FILE_LIMIT, //!< Too many files or links
        BUSY, //!< Operand is in use by the system or by a process
        DIR_DOESNT_EXIST, //!<  Directory doesn't exist
        DIR_NOT_OPENED, //!<  Directory hasn't been opened yet
        NO_MORE_FILES, //!<  Directory stream has no more files
        NOT_SUPPORTED, //!<  Operation is not supported by the current implementation
        OTHER_ERROR, //!<  other OS-specific error
    } Status;

    //! \brief default constructor
    FileSystemInterface() = default;

    //! \brief default virtual destructor
    virtual ~FileSystemInterface() = default;

    //! \brief copy constructor is forbidden
    FileSystemInterface(const FileSystemInterface& other) = delete;

    //! \brief assignment operator is forbidden
    FileSystemInterface& operator=(const FileSystemInterface& other) = delete;

    //! \brief return the underlying FileSystem handle (implementation specific)
    //! \return internal FileSystem handle representation
    virtual FileSystemHandle* getHandle() = 0;

    //! \brief provide a pointer to a FileSystem delegate object
    static FileSystemInterface* getDelegate(HandleStorage& aligned_new_memory);


    //------------ Os-specific FileSystem Functions ------------

    //! \brief create a new directory at location path
    virtual Status _createDirectory(const char* path) = 0;
    //! \brief remove a directory at location path
    virtual Status _removeDirectory(const char* path) = 0;
    //! \brief removes a file at location path
    virtual Status _removeFile(const char* path) = 0;
    //! \brief moves a file from source to destination
    virtual Status _moveFile(const char* sourcePath, const char* destPath) = 0;
    //! \brief copies a file from source to destination
    // virtual Status _copyFile(const char* sourcePath, const char* destPath) = 0;
    //! \brief append file source to destination file. If boolean true, creates a brand new file if the destination doesn't exist.
    // virtual Status _appendFile(const char* sourcePath, const char* destPath, bool createMissingDest=false) = 0;
    //! \brief gets the size of the file (in bytes) = 0 at location path
    virtual Status _getFileSize(const char* path, FwSignedSizeType& size) = 0;
    //! \brief move current directory to path
    virtual Status _changeWorkingDirectory(const char* path) = 0;
    //! \brief get FS free and total space in bytes on filesystem containing path
    virtual Status _getFreeSpace(const char* path, FwSizeType& totalBytes, FwSizeType& freeBytes) = 0;

};


class FileSystem final : public FileSystemInterface {
  private:
    FileSystem();         //!<  Constructor (private because singleton pattern)
  public:
    ~FileSystem() final;  //!<  Destructor

    //! \brief return the underlying FileSystem handle (implementation specific)
    //! \return internal FileSystem handle representation
    FileSystemHandle* getHandle() override;

    //! \brief create a new directory at location path
    Status _createDirectory(const char* path) override;
    //! \brief remove a directory at location path
    Status _removeDirectory(const char* path) override;
    //! \brief removes a file at location path
    Status _removeFile(const char* path) override;
    //! \brief moves a file from source to destination
    Status _moveFile(const char* sourcePath, const char* destPath) override;
    //! \brief copies a file from source to destination
    // Status _copyFile(const char* sourcePath, const char* destPath) override;
    //! \brief append file source to destination file. If boolean true, creates a brand new file if the destination doesn't exist.
    // Status _appendFile(const char* sourcePath, const char* destPath, bool createMissingDest=false) override;
    //! \brief gets the size of the file (in bytes) = 0 at location path
    Status _getFileSize(const char* path, FwSignedSizeType& size) override;
    //! \brief move current directory to path
    Status _changeWorkingDirectory(const char* path) override;
    //! \brief get FS free and total space in bytes on filesystem containing path
    Status _getFreeSpace(const char* path, FwSizeType& totalBytes, FwSizeType& freeBytes) override;



    //! \brief create a new directory at location path
    static Status createDirectory(const char* path);
    //! \brief remove a directory at location path
    static Status removeDirectory(const char* path);
    //! \brief removes a file at location path
    static Status removeFile(const char* path);
    //! \brief moves a file from source to destination
    static Status moveFile(const char* sourcePath, const char* destPath);
    //! \brief gets the size of the file (in bytes) = 0 at location path
    static Status getFileSize(const char* path, FwSignedSizeType& size);
    //! \brief move current directory to path
    static Status changeWorkingDirectory(const char* path);
    //! \brief get FS free and total space in bytes on filesystem containing path
    static Status getFreeSpace(const char* path, FwSizeType& totalBytes, FwSizeType& freeBytes);


    //! \brief append file source to destination file. If boolean true, creates a brand new file if the destination doesn't exist.
    static Status appendFile(const char* sourcePath, const char* destPath, bool createMissingDest=false);
    //! \brief copies a file from source to destination
    static Status copyFile(const char* sourcePath, const char* destPath);

    // TODO: reimplement at the interface level: 
    // copyFile, appendFile, using Os::Directory / Os::File
    // TODO:  copyFileData helper as well, and probably other helpers
    // TOOD: add touchFile and .exists() that takes an enum ref to return the type of file (file, dir, other)


    //! \brief read the contents of a directory.  Size of fileArray should be maxNum. Cleaner implementation found in Directory.hpp
    // static Status readDirectory(const char* path,  const U32 maxNum, Fw::String fileArray[], U32& numFiles);
    // TODO: move readDirectory and getFileCount to the Os::Directory interface


  public:
    //! \brief initialize singleton
    static void init();

    //! \brief get a reference to singleton
    //! \return reference to singleton
    static FileSystem& getSingleton();

  private:
    // ---- Helper functions ----
    //! \brief Convert a File::Status to a FileSystem::Status
    static Status handleFileError(File::Status fileStatus);
    /**
     * A helper function that writes all the file information in the source
     * file to the destination file (replaces/appends to end/etc. depending
     * on destination file mode).
     *
     * Files must already be open and will remain open after this function
     * completes.
     *
     * @param source File to copy data from
     * @param destination File to copy data to
     * @param size The number of bytes to copy
     */
    static Status copyFileData(File& source, File& destination, FwSignedSizeType size);


    static FileSystem* s_singleton;

    // This section is used to store the implementation-defined FileSystem handle. To Os::FileSystem and fprime, this type is
    // opaque and thus normal allocation cannot be done. Instead, we allow the implementor to store then handle in
    // the byte-array here and set `handle` to that address for storage.
    //
    alignas(FW_HANDLE_ALIGNMENT) HandleStorage m_handle_storage;  //!< FileSystem handle storage
    FileSystemInterface& m_delegate;          
};



}

#endif
