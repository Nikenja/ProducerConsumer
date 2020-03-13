#ifndef PTHREAD_JOIN_TIMEOUT_H
#define PTHREAD_JOIN_TIMEOUT_H

#include <pthread.h>
#include "safe_state.h"

namespace ThreadNs
{

class JoinPthreadData
{
public:
    JoinPthreadData(const pthread_t joinPthreadId) : m_joinPthreadId(joinPthreadId) {}

    bool IsJoinState() { return m_joinState.GetState(); }
    void SetJoinState(const bool joinState) { m_joinState.SetState(joinState); }

    pthread_t GetJoinPthreadId() const { return m_joinPthreadId; }
private:
    pthread_t m_joinPthreadId;
    RoutineNs::SafeState m_joinState;
};

int pthread_join_timeout(pthread_t thread, unsigned int msecs);

}

#endif // PTHREAD_JOIN_TIMEOUT_H
