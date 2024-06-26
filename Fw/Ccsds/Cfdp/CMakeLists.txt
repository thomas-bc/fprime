####
# CMakeLists.txt:
#
# Sets up the fprime module build within CMake.
####
set(SOURCE_FILES
    "${CMAKE_CURRENT_LIST_DIR}/FilePacket.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Header.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Metadata.cpp"
)

set(MOD_DEPS
  Fw/Types
  Fw/Buffer
)

register_fprime_module()

set(UT_SOURCE_FILES
    "${CMAKE_CURRENT_LIST_DIR}/test/ut/TestFilePacket.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/test/ut/TestHeader.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/test/ut/TestMetadata.cpp"
)
register_fprime_ut()
