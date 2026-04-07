// ======================================================================
// \title  FsComp.cpp
// \author chammard
// \brief  cpp file for FsComp component implementation class
// ======================================================================

#include "Ref/FsComp/FsComp.hpp"
#include "Os/Directory.hpp"
#include "Os/File.hpp"
#include "Os/FileSystem.hpp"

namespace Ref {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

FsComp ::FsComp(const char* const compName) : FsCompComponentBase(compName) {}

FsComp ::~FsComp() {}

// ----------------------------------------------------------------------
// Handler implementations for commands
// ----------------------------------------------------------------------

void FsComp ::LIST_DIR_cmdHandler(FwOpcodeType opCode, U32 cmdSeq, const Fw::CmdStringArg& path) {
    Os::Directory dir;
    Os::Directory::Status status = dir.open(path.toChar(), Os::DirectoryInterface::OpenMode::READ);
    if (status != Os::DirectoryInterface::Status::OP_OK) {
        this->log_ACTIVITY_HI_DirErrorStatus(static_cast<Os::DirectoryStatus::T>(status));
        this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::EXECUTION_ERROR);
        return;
    }
    FwSizeType count = 0;
    status = dir.getFileCount(count);
    if (status != Os::DirectoryInterface::Status::OP_OK) {
        this->log_ACTIVITY_HI_DirErrorStatus(static_cast<Os::DirectoryStatus::T>(status));
        this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::EXECUTION_ERROR);
        return;
    }
    this->log_ACTIVITY_HI_NumDirs(count, path);
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

void FsComp ::RENAME_FILE_cmdHandler(FwOpcodeType opCode,
                                     U32 cmdSeq,
                                     const Fw::CmdStringArg& in,
                                     const Fw::CmdStringArg& out) {
    Os::FileSystem::Status status = Os::FileSystem::rename(in.toChar(), out.toChar());
    if (status != Os::FileSystem::Status::OP_OK) {
        this->log_ACTIVITY_HI_FsErrorStatus(static_cast<Os::FileSystemStatus::T>(status));
        this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::EXECUTION_ERROR);
    } else {
        this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
    }
}

void FsComp ::OPEN_READ_10CHAR_cmdHandler(FwOpcodeType opCode, U32 cmdSeq, const Fw::CmdStringArg& path) {
    Os::File file;
    Os::File::Status status = file.open(path.toChar(), Os::FileInterface::Mode::OPEN_READ);
    if (status != Os::File::Status::OP_OK) {
        this->log_ACTIVITY_HI_FileErrorStatus(static_cast<Os::FileStatus::T>(status));
        this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::EXECUTION_ERROR);
    } else {
        U8 buffer[11];
        FwSizeType size = 10;
        status = file.read(buffer, size);
        if (status != Os::File::Status::OP_OK) {
            this->log_ACTIVITY_HI_FileErrorStatus(static_cast<Os::FileStatus::T>(status));
            this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::EXECUTION_ERROR);
            return;
        }
        buffer[size] = '\0';  // Null-terminate the buffer

        Fw::String read_str(reinterpret_cast<const char*>(buffer));
        this->log_ACTIVITY_HI_ReadFile(read_str, path);
        this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
    }
}

}  // namespace Ref
