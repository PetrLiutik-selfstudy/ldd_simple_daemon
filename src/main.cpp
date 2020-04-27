#include <fstream>
#include <iostream>
#include <thread>

#include <stdlib.h>
#include <syslog.h>

#include "daemon.h"

static constexpr auto TEST_FILE_PATH = "/tmp/simple_daemon_test.txt";

int main(int argc, char *argv[]) {
    int result = EXIT_SUCCESS;
    bool is_daemon = false;
 
    // Open syslog for parent process.
    ::openlog(argv[0], LOG_PID | LOG_CONS, LOG_USER);
    ::syslog(LOG_INFO, "trying to start a daemon");

    // Daemonizing process.
    std::tie(result, is_daemon) = simple_daemon::daemonize();
    if (result != EXIT_SUCCESS) {
        ::syslog(LOG_ERR, "failed to start the daemon");
        return result;
    }

    if (is_daemon) {
        // Daemon started.
        // Reopening syslog for the child process.
        ::openlog(argv[0], LOG_PID | LOG_CONS, LOG_DAEMON);
        ::syslog(LOG_INFO, "the daemon started");

        // Opening test file.
        std::fstream fs(TEST_FILE_PATH, std::ios_base::trunc | std::ios_base::out);
        if (!fs.is_open()) {
            ::syslog(LOG_ERR, "failed to open file %s", TEST_FILE_PATH);
            return EXIT_FAILURE;
        }
        fs << "the daemon started" << std::endl;

        // Daemon endless loop.
        for(int i = 0;;++i) {
            ::syslog(LOG_INFO, "test counter value: %d", i);
            fs << "test counter value: " << i << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(30));
        }
    } else {
        // Just exit the parent process.
        ::syslog(LOG_INFO, "exiting the parent process");
    }
    return result; 
}
