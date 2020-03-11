#ifndef EVENTS_PRODUCER_H
#define EVENTS_PRODUCER_H

#include <pthread.h>
#include "safe_queue.h"
#include "cond_var.h"
#include "log_msg.h"

namespace EventsProducerConsumerNs
{

template <typename T>
class EventsProducer
{
public:
    EventsProducer(const CondVarNs::CondVarPtr& condVar);
    void ProduceEvent(const T& event, SafeContainersNs::SafeQueue<T>& eventsQueue);
private:
    CondVarNs::CondVarPtr m_condVar;
};

template <typename T>
EventsProducer<T>::EventsProducer(const CondVarNs::CondVarPtr& condVar) : m_condVar(condVar) {}

template <typename T>
void EventsProducer<T>::ProduceEvent(
    const T& event, SafeContainersNs::SafeQueue<T>& eventsQueue)
{
    log_msg(__PRETTY_FUNCTION__, __LINE__);
    pthread_mutex_lock(&m_condVar->GetCondVarMutex());
    eventsQueue.Push(event);
    pthread_cond_signal(&m_condVar->GetCondVar());
    pthread_mutex_unlock(&m_condVar->GetCondVarMutex());
}

}

#endif // EVENTS_PRODUCER_H
