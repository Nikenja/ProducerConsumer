#ifndef WAITING_TIME_GETTER_H
#define WAITING_TIME_GETTER_H

#include <time.h>

namespace TimeHelperNs
{

extern const unsigned int MAX_NSECS_DELAY;

void add_time(const unsigned int secDelay, const unsigned int nsecDelay, timespec& waitingTime);

bool try_get_monotonic_waiting_time(
    const unsigned int secDelay, const unsigned int nsecDelay, timespec& waitingTime);

} // namespace TimeHelperNs

#endif // WAITING_TIME_GETTER_H
