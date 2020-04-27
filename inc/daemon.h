#ifndef __DAEMON_H__
#define __DAEMON_H__

#include <tuple>

namespace simple_daemon {

    /**
     * @brief Daemonizes process.
     * @return result of the daemonization, true - it's a daemon, false - it's a parent to exit.
     */
    std::pair<int, bool> daemonize();

}

#endif //__DAEMON_H__
