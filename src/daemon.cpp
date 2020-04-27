#include "daemon.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

namespace simple_daemon {
  
    std::pair<int, bool> daemonize() {
        // Forking off the parent process.
        auto pid = ::fork();
        if (pid < 0) {
            return std::make_pair(EXIT_FAILURE, false);
        }

        // Exiting the parent process.
        if (pid > 0) {
            return std::make_pair(EXIT_SUCCESS, false);
        }

        // Changing the file mode mask.
        ::umask(0);

        // Creating a new session ID.
        auto sid = ::setsid();
        if (sid < 0) {
            return std::make_pair(EXIT_FAILURE, true);
        }

        // Changing the current working directory.
        if ((::chdir("/")) < 0) {
            return std::make_pair(EXIT_FAILURE, true);
        }

        // Closing standard file descriptors.
        ::close(STDIN_FILENO);
        ::close(STDOUT_FILENO);
        ::close(STDERR_FILENO);

        return std::make_pair(EXIT_SUCCESS, true);
    }
    
}