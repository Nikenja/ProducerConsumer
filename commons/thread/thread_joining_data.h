#ifndef THREAD_JOINING_DATA_H
#define THREAD_JOINING_DATA_H

#include <pthread.h>
#include "safe_state.h"

namespace ThreadNs
{

class ThreadJoiningData
{
public:
    ThreadJoiningData(const pthread_t joinPthreadId);

    bool IsJoinState();
    void SetJoinState(const bool joinState);

    pthread_t GetJoinPthreadId() const;
private:
    pthread_t m_joinPthreadId;
    ThreadSafeNs::SafeState m_joinState;
};

} // namespace ThreadNs

#endif // THREAD_JOINING_DATA_H
