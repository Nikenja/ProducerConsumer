#include "isignal_handler.h"
#include <signal.h>
#include "log_msg.h"

namespace SignalHandlerNs
{

void signal_handler(int /*signal*/)
{
    pthread_exit(NULL);
}

bool set_signal_handler_for(const int signal)
{
    log_msg(__PRETTY_FUNCTION__, __LINE__);
    
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, signal);
    
    struct sigaction action;
    action.sa_flags = 0;
    action.sa_mask = set;
    action.sa_handler = signal_handler;
    if (sigaction(signal, &action, NULL) != 0)
    {
        log_msg(__PRETTY_FUNCTION__, __LINE__);

        return false;
    }

    return true;
}

} // namespace SignalHandlerNs
