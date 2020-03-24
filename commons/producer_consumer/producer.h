#ifndef PRODUCER_H
#define PRODUCER_H

#include <pthread.h>
#include "safe_queue.h"
#include "cond_var.h"
#include "log_msg.h"

namespace RoutineNs
{

template <typename T>
class Producer
{
public:
    Producer(CondVarNs::CondVar& condVar, SafeContainersNs::SafeQueue<T>& eventsQueue);
    void ProduceEvent(const T& event);
private:
    CondVarNs::CondVar& m_condVar;
    SafeContainersNs::SafeQueue<T>& m_eventsQueue;
};

template <typename T>
Producer<T>::Producer(
    CondVarNs::CondVar& condVar, SafeContainersNs::SafeQueue<T>& eventsQueue) :
        m_condVar(condVar), m_eventsQueue(eventsQueue)
{
}

template <typename T>
void Producer<T>::ProduceEvent(const T& event)
{
    log_msg(__PRETTY_FUNCTION__, __LINE__);
    pthread_mutex_lock(&m_condVar.GetCondVarMutex());
    m_eventsQueue.Push(event);
    pthread_cond_signal(&m_condVar.GetCondVar());
    pthread_mutex_unlock(&m_condVar.GetCondVarMutex());
}

}

#endif // PRODUCER_H
