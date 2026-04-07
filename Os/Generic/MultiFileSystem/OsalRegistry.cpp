// ======================================================================
// \title Os/Generic/MultiFileSystem/OsalRegistry.cpp
// \brief OsalRegistry implementation for managing OSAL implementations
// ======================================================================

#include "Os/Generic/MultiFileSystem/OsalRegistry.hpp"

namespace Os {
namespace Generic {

// Initialize static registry array
Fw::Array<OsalImplMapping*, OsalRegistry::MAX_FILESYSTEMS> OsalRegistry::s_implMappings = {};
OsalImplSet* OsalRegistry::s_rootImplSet = nullptr;

RegistryStatus OsalRegistry::registerMountedImplementation(OsalImplMapping* implementation_map) {
    //! TODO: assert the implementaton is non-null and complete ?
    // Find the first available slot
    for (FwSizeType i = 0; i < MAX_FILESYSTEMS; i++) {
        if (OsalRegistry::s_implMappings[i] == nullptr) {
            OsalRegistry::s_implMappings[i] = implementation_map;
            return RegistryStatus::SUCCESS;
        }
    }
    // No available slots
    return RegistryStatus::OTHER_ERROR;
}

RegistryStatus OsalRegistry::registerRootImplementation(OsalImplSet* impl_set) {
    if (impl_set == nullptr || impl_set->filesystem == nullptr || impl_set->file_factory == nullptr ||
        impl_set->directory_factory == nullptr) {
        return RegistryStatus::OTHER_ERROR;
    }
    OsalRegistry::s_rootImplSet = impl_set;
    return RegistryStatus::SUCCESS;
}

OsalImplSet* OsalRegistry::routePathToImplementation(const char* path, FwIndexType& prefix_len) {
    if (path == nullptr) {
        return nullptr;
    }

    // NOTE: routing algo works for prototyping, should be tested thoroughly

    //! TODO: should likely pass a path_len parameter not to read out of bounds on path[j]
    //! YES!

    // Iterate through registered implementations and find the first matching path prefix
    for (FwSizeType i = 0; i < MAX_FILESYSTEMS; i++) {
        if (OsalRegistry::s_implMappings[i] == nullptr) {
            break;  // No more registered implementations to check
        }

        OsalImplSet* impl = OsalRegistry::s_implMappings[i]->impl_set;
        if (impl != nullptr && impl->filesystem != nullptr) {
            // Check if path starts with the implementation's path prefix
            // Manual character-by-character comparison to verify prefix match
            const char* prefix = OsalRegistry::s_implMappings[i]->mount_path;
            FwSizeType j = 0;

            // TODO: for-loop instead
            while (j < MAX_MULTIFS_PATH_PREFIX_LENGTH && prefix[j] != '\0') {
                if (path[j] != prefix[j]) {
                    break;
                }
                j++;
            }

            // If we reached the end of prefix (null terminator) and path continues with '/' or ends, it's a match
            if (j < MAX_MULTIFS_PATH_PREFIX_LENGTH && prefix[j] == '\0' && (path[j] == '\0' || path[j] == '/')) {
                FW_ASSERT_NO_OVERFLOW(j, FwIndexType);     // Ensure no overflow in prefix length calculation
                prefix_len = static_cast<FwIndexType>(j);  // Set the output parameter for prefix length
                return impl;
            }
        }
    }

    prefix_len = 0;  // No prefix matched, so prefix length is 0
    // Path does not match any mounted implementation, return root implementation
    return OsalRegistry::s_rootImplSet;
}

}  // namespace Generic
}  // namespace Os
