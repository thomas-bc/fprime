//! ============================================================================
//! @file   TestFilePacketMain.cpp
//! @brief  CFDP file packet main test file.
//! @author chownw
//! ============================================================================

#include <gtest/gtest.h>

namespace Fw
{

namespace Cfdp
{

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

} // namespace Cfdp

} // namespace Fw
