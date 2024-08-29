// ======================================================================
// \title Os/test/ut/directory/RulesHeaders.hpp
// \brief rule definitions for common testing
// ======================================================================

#ifndef __RULES_HEADERS__
#define __RULES_HEADERS__
#include <gtest/gtest.h>
#include "Os/Directory.hpp"
#include "STest/Rule/Rule.hpp"
#include "STest/Scenario/BoundedScenario.hpp"
#include "STest/Scenario/RandomScenario.hpp"
#include "STest/Scenario/Scenario.hpp"

namespace Os {
namespace Test {
namespace Directory {

struct Tester {
    //! State representation of a Directory.
    //!
    enum DirectoryState {
        UNINITIALIZED,  //!< Directory is uninitialized
        OPEN,   //!< Directory is open
        CLOSED  //!< Directory is closed
    };

    //! Assert in Directory.cpp for searching death text
    static constexpr const char* ASSERT_IN_directory_CPP = "Assert: \".*/Os/.*/Directory\\.cpp:[0-9]+\"";

    // Constructors that ensures the directory is always valid
    Tester() = default;

    // Destructor must be virtual
    virtual ~Tester() = default;

    //! Directory under test
    Os::Directory m_directory;

    //! Currently opened path
    std::string m_path;

    //! Check if the back-end tester is fully functional (i.e. not a stub)
    //! \return true if functional, false otherwise
    //!
    // virtual bool functional() const = 0;

    //! Directory state, for testing purposes
    DirectoryState m_state = UNINITIALIZED;

// Do NOT alter, adds rules to Tester as inner classes
#include "DirectoryRules.hpp"
};

}  // namespace Directory
}  // namespace Test
}  // namespace Os
#endif  // __RULES_HEADERS__
