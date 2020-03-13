#ifndef SAFE_EVENT_QUEUE_H
#define SAFE_EVENT_QUEUE_H

#include <deque>
#include <pthread.h>

namespace SafeContainersNs
{

template <typename T>
class SafeQueue
{
public:
    SafeQueue();
    void Push(T event);
    bool TryPop(T& dest);
private:
    pthread_mutex_t m_queueMutex;
    std::deque<T> m_queue; 
};

template <typename T>
SafeQueue<T>::SafeQueue() : m_queueMutex(PTHREAD_MUTEX_INITIALIZER) {}

template <typename T>
void SafeQueue<T>::Push(T event)
{
    pthread_mutex_lock(&m_queueMutex);
    m_queue.push_back(event);
    pthread_mutex_unlock(&m_queueMutex);
}

template <typename T>
bool SafeQueue<T>::TryPop(T& dest)
{
    bool result = false;
    pthread_mutex_lock(&m_queueMutex);
    if (m_queue.size() != 0)
    {
        dest = m_queue.front();
        m_queue.pop_front();
        result = true;
    }
    pthread_mutex_unlock(&m_queueMutex);
    return result;
}

}

#endif // SAFE_EVENT_QUEUE_H
