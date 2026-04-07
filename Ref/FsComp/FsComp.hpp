// ======================================================================
// \title  FsComp.hpp
// \author chammard
// \brief  hpp file for FsComp component implementation class
// ======================================================================

#ifndef Ref_FsComp_HPP
#define Ref_FsComp_HPP

#include "Ref/FsComp/FsCompComponentAc.hpp"

namespace Ref {

class FsComp final : public FsCompComponentBase {
  public:
    // ----------------------------------------------------------------------
    // Component construction and destruction
    // ----------------------------------------------------------------------

    //! Construct FsComp object
    FsComp(const char* const compName  //!< The component name
    );

    //! Destroy FsComp object
    ~FsComp();

  private:
    // ----------------------------------------------------------------------
    // Handler implementations for commands
    // ----------------------------------------------------------------------

    //! Handler implementation for command LIST_DIR
    void LIST_DIR_cmdHandler(FwOpcodeType opCode,  //!< The opcode
                             U32 cmdSeq,           //!< The command sequence number
                             const Fw::CmdStringArg& path) override;

    //! Handler implementation for command RENAME_FILE
    void RENAME_FILE_cmdHandler(FwOpcodeType opCode,  //!< The opcode
                                U32 cmdSeq,           //!< The command sequence number
                                const Fw::CmdStringArg& in,
                                const Fw::CmdStringArg& out) override;

    //! Handler implementation for command OPEN_READ_10CHAR
    void OPEN_READ_10CHAR_cmdHandler(FwOpcodeType opCode,  //!< The opcode
                                     U32 cmdSeq,           //!< The command sequence number
                                     const Fw::CmdStringArg& path) override;
};

}  // namespace Ref

#endif
