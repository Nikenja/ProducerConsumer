#ifndef SAFE_STATE_H
#define SAFE_STATE_H

#include <pthread.h>

namespace RoutineNs
{

class SafeState
{
public:
    SafeState();
    bool GetState();
    void SetState(const bool state);
private:
    pthread_mutex_t m_stateMutex;
    bool m_state;
};

}

#endif // SAFE_STATE_H
