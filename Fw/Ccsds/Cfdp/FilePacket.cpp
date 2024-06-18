//! ============================================================================
//! @file   FilePacket.cpp
//! @brief  cpp file for a CFDP PDU file packet.
//! @author chownw
//! ============================================================================

#include <FpConfig.hpp>
#include <Fw/Buffer/Buffer.hpp>
#include <Fw/Ccsds/Cfdp/FilePacket.hpp>
#include <Fw/Ccsds/Cfdp/Header.hpp>

namespace Fw
{

namespace Cfdp
{

void FilePacket::serialize(Fw::Buffer& buf)
{
  // this->header.serialize();
}

void FilePacket::deserialize(Fw::Buffer& buf)
{
  // this->header.deserialize();
}

} // namespace Cfdp

} // namespace Fw
