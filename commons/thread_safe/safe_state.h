#ifndef SAFE_STATE_H
#define SAFE_STATE_H

#include <pthread.h>

namespace ThreadSafeNs
{

class SafeState
{
public:
    SafeState();
    bool GetState();
    void SetState(const bool state);
private:
    bool m_state;
    pthread_mutex_t m_stateMutex;
};

}

#endif // SAFE_STATE_H
