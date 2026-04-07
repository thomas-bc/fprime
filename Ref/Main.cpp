// ======================================================================
// \title  Main.cpp
// \author mstarch
// \brief main program for reference application. Intended for CLI-based systems (Linux, macOS)
//
// \copyright
// Copyright 2009-2022, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================
// Used to access topology functions
#include <Ref/Top/RefTopology.hpp>
// Used for signal handling shutdown
#include <signal.h>
// Used for command line argument processing
#include <getopt.h>
// Used for printf functions
#include <cstdlib>
// Used to get the Os::Console
#include <Os/Os.hpp>

#include "Os/Delegate.hpp"
#include "Os/Generic/MultiFileSystem/OsalRegistry.hpp"
#include "Os/Posix/Directory.hpp"
#include "Os/Posix/File.hpp"
#include "Os/Posix/FileSystem.hpp"
#include "Os/Stub/Directory.hpp"
#include "Os/Stub/File.hpp"
#include "Os/Stub/FileSystem.hpp"

// ------------------------------------------------------------
// Quirks
// ------------------------------------------------------------
// - MultiFsFileInterfaceStorage thing, because one FileInterface needs to contain another
// - This whole file/dir factory business... should OSALs provide a .clone() method?
//
// Generally have a weird feeling where I'm re-implementing most of the architecture/concept of the lower-level
// OSAL architecutre, but re-implementing here myself. See e.g.:
// - MultiFsFileInterfaceStorage
// - Factory functions / makeDelegate
// - testing; I want to test the "interface" just like in StubFile tests

// Static (global) storage for filesystem implementations
static Os::Posix::FileSystem::PosixFileSystem s_posixFileSystem;
static Os::Stub::FileSystem::StubFileSystem s_stubFileSystem;

static Os::Generic::OsalImplSet s_posixImplSet = {
    &s_posixFileSystem,
    Os::Delegate::makeDelegate<Os::FileInterface, Os::Posix::File::PosixFile, Os::Generic::MultiFsFileInterfaceStorage>,
    Os::Delegate::makeDelegate<Os::DirectoryInterface,
                               Os::Posix::Directory::PosixDirectory,
                               Os::Generic::MultiFsDirectoryInterfaceStorage>,
};

static Os::Generic::OsalImplSet s_stubImplSet = {
    &s_stubFileSystem,
    Os::Delegate::makeDelegate<Os::FileInterface, Os::Stub::File::StubFile, Os::Generic::MultiFsFileInterfaceStorage>,
    Os::Delegate::makeDelegate<Os::DirectoryInterface,
                               Os::Stub::Directory::StubDirectory,
                               Os::Generic::MultiFsDirectoryInterfaceStorage>,
};

static Os::Generic::OsalImplMapping s_stubImplMapping = {
    .mount_path = "/mnt/stub",
    .impl_set = &s_stubImplSet,
};

// static Os::Generic::OsalImplMapping s_posixImplMapping = {
//     .mount_path = "/mnt/p",
//     .impl_set = &s_posixImplSet,
// };

/**
 * \brief print commandline help message
 *
 * This will print a command line help message including the available command line arguments.
 *
 * @param app: name of application
 */
void print_usage(const char* app) {
    (void)printf("Usage: ./%s [options]\n-a\thostname/IP address\n-p\tport_number\n", app);
}

/**
 * \brief shutdown topology cycling on signal
 *
 * The reference topology allows for a simulated cycling of the rate groups. This simulated cycling needs to be stopped
 * in order for the program to shutdown. This is done via handling signals such that it is performed via Ctrl-C
 *
 * @param signum
 */
static void signalHandler(int signum) {
    Ref::stopRateGroups();
}

/**
 * \brief execute the program
 *
 * This F´ program is designed to run in standard environments (e.g. Linux/macOs running on a laptop). Thus it uses
 * command line inputs to specify how to connect.
 *
 * @param argc: argument count supplied to program
 * @param argv: argument values supplied to program
 * @return: 0 on success, something else on failure
 */
int main(int argc, char* argv[]) {
    Os::init();
    U16 port_number = 0;
    I32 option = 0;
    char* hostname = nullptr;

    // Loop while reading the getopt supplied options
    while ((option = getopt(argc, argv, "hp:a:")) != -1) {
        switch (option) {
            // Handle the -a argument for address/hostname
            case 'a':
                hostname = optarg;
                break;
            // Handle the -p port number argument
            case 'p':
                port_number = static_cast<U16>(atoi(optarg));
                break;
            // Cascade intended: help output
            case 'h':
            // Cascade intended: help output
            case '?':
            // Default case: output help and exit
            default:
                print_usage(argv[0]);
                return (option == 'h') ? 0 : 1;
        }
    }

    Os::Generic::OsalRegistry::registerRootImplementation(&s_posixImplSet);
    Os::Generic::OsalRegistry::registerMountedImplementation(&s_stubImplMapping);

    // Object for communicating state to the reference topology
    Ref::TopologyState inputs;
    inputs.hostname = hostname;
    inputs.port = port_number;

    // Setup program shutdown via Ctrl-C
    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);
    (void)printf("Hit Ctrl-C to quit\n");

    // Setup, cycle, and teardown topology
    Ref::setupTopology(inputs);
    Ref::startRateGroups(Fw::TimeInterval(1, 0));  // Program loop cycling rate groups at 1Hz
    Ref::teardownTopology(inputs);
    (void)printf("Exiting...\n");
    return 0;
}
