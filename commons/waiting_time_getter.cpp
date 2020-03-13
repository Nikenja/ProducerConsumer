#include "waiting_time_getter.h"
#include "log_msg.h"

namespace WaitingTimeGetterNs
{

unsigned int MAX_NSECS_DELAY = 1000000000;

void add_time(const unsigned int secDelay, const unsigned int nsecDelay, timespec& waitingTime)
{
    waitingTime.tv_sec += secDelay;
    if (nsecDelay)
    {
        waitingTime.tv_nsec += nsecDelay;
        if (waitingTime.tv_nsec >= MAX_NSECS_DELAY)
        {
            waitingTime.tv_nsec -= MAX_NSECS_DELAY;
            ++waitingTime.tv_sec;
        }
    }    
}

bool try_get_monotonic_waiting_time(
    const unsigned int secDelay, const unsigned int nsecDelay, timespec& waitingTime)
{
    if (nsecDelay >= MAX_NSECS_DELAY)
    {
        return false;
    }

    waitingTime.tv_sec = secDelay;
    waitingTime.tv_nsec = nsecDelay;

    log_msg("waitingTime.tv_sec", waitingTime.tv_sec);
    log_msg("waitingTime.tv_nsec", waitingTime.tv_nsec);

    return true;
}

}
