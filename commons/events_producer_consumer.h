#ifndef EVENTS_PRODUCER_CONSUMER_H
#define EVENTS_PRODUCER_CONSUMER_H

#include <pthread.h>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include "ithread.h"
#include "iexchange_data.h"
#include "safe_queue.h"
#include "cond_var.h"

namespace EventsProducerConsumerNs
{

template <typename P, typename C, typename E>
class EventsProducerConsumer
{
public:
    EventsProducerConsumer();
    void StartProduceConsume();
    void StopProduceConsume();
    void ProduceEvent(const E& event);
private:
    CondVarNs::CondVarPtr m_condVar;
    SafeContainersNs::SafeQueue<E> m_eventsQueue;
    boost::shared_ptr<P> m_producer;
    boost::shared_ptr<C> m_consumer;
};

template <typename P, typename C, typename E>
EventsProducerConsumer<P, C, E>::EventsProducerConsumer()
{
    m_condVar = boost::make_shared<CondVarNs::CondVar>();
    m_producer = boost::make_shared<P>(m_condVar);
    m_consumer = boost::make_shared<C>(m_condVar, m_eventsQueue);
}

template <typename P, typename C, typename E>
void EventsProducerConsumer<P, C, E>::StartProduceConsume()
{
    m_consumer->StartConsume();
}

template <typename P, typename C, typename E>
void EventsProducerConsumer<P, C, E>::StopProduceConsume()
{
    m_consumer->StopConsume();
}

template <typename P, typename C, typename E>
void EventsProducerConsumer<P, C, E>::ProduceEvent(const E& event)
{
    m_producer->ProduceEvent(event, m_eventsQueue);
}

}

#endif // EVENTS_PRODUCER_CONSUMER_H
