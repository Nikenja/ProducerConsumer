#include "pthread_join_timeout.h"
#include <stdint.h>
#include <time.h>
#include <errno.h>
#include "log_msg.h"

namespace ThreadNs
{

uint64_t get_time_in_ms()
{
    timespec currentTime;
    if (clock_gettime(CLOCK_MONOTONIC, &currentTime) == -1)
    {
        return -1;
    }

    return (currentTime.tv_sec * 1000 + static_cast<uint64_t>(currentTime.tv_nsec / 1000000));
}


bool is_timeout(const uint64_t startTimeInMsec, unsigned int timeoutInMsec)
{
    return ((get_time_in_ms() - startTimeInMsec) >= timeoutInMsec);
}

void* pthread_join_routine(void* arg)
{
    JoinPthreadData* data = reinterpret_cast<JoinPthreadData*>(arg);
    pthread_join(data->GetJoinPthreadId(), NULL);
    data->SetJoinState(true);
    
    return NULL;
}

int pthread_join_timeout(pthread_t joinPthreadId, unsigned int timeoutInMsec)
{
    if (timeoutInMsec < 10 && timeoutInMsec > 10000)
    {
        return -1;
    }

    JoinPthreadData data(joinPthreadId);
    pthread_t supportThreadId;
    int createResult = pthread_create(&supportThreadId, NULL, pthread_join_routine, &data);
    if (createResult != 0)
    {
        return createResult;
    }

    bool result = false;
    timespec sleepTime;
    sleepTime.tv_sec = 0;
    sleepTime.tv_nsec = 10000000;
    uint64_t startTimeInMsec = get_time_in_ms();
    do {
        if (data.IsJoinState())
        {
            result = true;
            break;
        }
        clock_nanosleep(CLOCK_MONOTONIC, 0, &sleepTime, NULL);
    } while (!is_timeout(startTimeInMsec, timeoutInMsec));

    if (result == false)
    {
        const int cancelResult = pthread_cancel(supportThreadId);
        if (cancelResult != 0)
        {
            log_msg(__PRETTY_FUNCTION__, __LINE__);
        }
    }
 
    pthread_join(supportThreadId, NULL);

    return (result ? 0 : ETIMEDOUT);
}

}
