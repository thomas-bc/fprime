
register_os_implementation("File;FileSystem;Directory" Multi)

register_fprime_module(
    Os_Generic_OsalRegistry
  SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/OsalRegistry.cpp"
  HEADERS
    "${CMAKE_CURRENT_LIST_DIR}/OsalRegistry.hpp"
  DEPENDS
    Fw_Types
)

# register_fprime_implementation(
#     Os_Generic_MultiFileSystem
#   SOURCES
#     "${CMAKE_CURRENT_LIST_DIR}/DefaultFileSystem.cpp"
#   IMPLEMENTS
#     Os_FileSystem
#   DEPENDS
#     Fw_Types
#     Os_Generic_MultiFileSystem_Implementation
# )

# register_fprime_ut(
#     MultiDirectoryTest
#   SOURCES
#     "${CMAKE_CURRENT_LIST_DIR}/test/ut/MultiDirectoryTests.cpp"
#     "${CMAKE_CURRENT_LIST_DIR}/../../test/ut/directory/CommonTests.cpp"
#     "${CMAKE_CURRENT_LIST_DIR}/../../test/ut/directory/FilesystemRules.cpp"
#   DEPENDS
#     Fw_Types
#     Fw_Time
#     Os
#     STest
#   CHOOSES_IMPLEMENTATIONS
#     Os_Generic_MultiFileSystem
# )
