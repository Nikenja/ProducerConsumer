#include "safe_state.h"

namespace ThreadSafeNs
{

SafeState::SafeState() :
    m_state(false), m_stateMutex(PTHREAD_MUTEX_INITIALIZER)
{
}

bool SafeState::GetState()
{
    pthread_mutex_lock(&m_stateMutex);
    const bool state = m_state;
    pthread_mutex_unlock(&m_stateMutex);

    return state;
}

void SafeState::SetState(const bool state)
{
    pthread_mutex_lock(&m_stateMutex);
    m_state = state;
    pthread_mutex_unlock(&m_stateMutex);
}

}
