module Ref {
    @ Dummy component to test Filesystem operations
    active component FsComp {

        # One async command/port is required for active components
        # This should be overridden by the developers with a useful command/port
        async command LIST_DIR(path: string) opcode 0
        async command RENAME_FILE(in: string, out: string) opcode 1
        async command OPEN_READ_10CHAR(path: string) opcode 2

        event NumDirs(num: FwSizeType, path: string) \
            severity activity high \
            format "Found {} files in {}"

        event DirErrorStatus(status: Os.DirectoryStatus) \
            severity activity high \
            format "Status {}"

        event FsErrorStatus(status: Os.FileSystemStatus) \
            severity activity high \
            format "Status {}"

        event FileErrorStatus(status: Os.FileStatus) \
            severity activity high \
            format "Status {}"

        event ReadFile(content: string, path: string) \
            severity activity high \
            format "content={} |||| filepath={}"

        ###############################################################################
        # Standard AC Ports: Required for Channels, Events, Commands, and Parameters  #
        ###############################################################################
        @ Port for requesting the current time
        time get port timeCaller

        @ Enables command handling
        import Fw.Command

        @ Enables event handling
        import Fw.Event

        @ Enables telemetry channels handling
        import Fw.Channel

    }
}
