#ifndef EVENTS_CONSUMER_H
#define EVENTS_CONSUMER_H

#include <pthread.h>
#include <signal.h>
#include "ithread.h"
#include "safe_queue.h"
#include "cond_var.h"
#include "log_msg.h"

namespace EventsProducerConsumerNs
{

template <typename T>
class EventsConsumer : public ThreadNs::IThread
{
public:
    EventsConsumer(const CondVarNs::CondVarPtr& condVar, SafeContainersNs::SafeQueue<T>& eventsQueue);
    virtual ~EventsConsumer();

    void StartConsume();
    void StopConsume();
private:
    CondVarNs::CondVarPtr m_condVar;
    SafeContainersNs::SafeQueue<T>& m_eventsQueue;

    virtual void doStartConsume();
    virtual void doStopConsume();

    virtual void doRoutine();
    virtual void doOnEndRoutine();
    virtual void doConsumeEvent(const T& event) = 0;
};

template <typename T>
EventsConsumer<T>::EventsConsumer(
    const CondVarNs::CondVarPtr& condVar, SafeContainersNs::SafeQueue<T>& eventsQueue) :
        m_condVar(condVar), m_eventsQueue(eventsQueue) {}

template <typename T>
EventsConsumer<T>::~EventsConsumer() {}

template <typename T>
void EventsConsumer<T>::StartConsume()
{
    doStartConsume();
}

template <typename T>
void EventsConsumer<T>::StopConsume()
{
    doStopConsume();
}

template <typename T>
void EventsConsumer<T>::doStartConsume()
{
    ThreadNs::IThread::StartThread();
}

template <typename T>
void EventsConsumer<T>::doStopConsume()
{
    ThreadNs::IThread::StopThread();
}

template <typename T>
void EventsConsumer<T>::doRoutine()
{
    sigset_t sigSet;
    sigemptyset(&sigSet);
    sigaddset(&sigSet, SIGTERM);

    int sigmaskResult = pthread_sigmask(SIG_BLOCK, &sigSet, NULL);
    if (sigmaskResult != 0)
    {
        log_msg(__PRETTY_FUNCTION__, __LINE__);
    }

    timespec waitingTime;
    if (clock_gettime(CLOCK_MONOTONIC, &waitingTime) == -1)
    {
        log_msg(__PRETTY_FUNCTION__, __LINE__);
    }

    waitingTime.tv_sec = 0;
    waitingTime.tv_nsec = 300000000;

    while (true)
    {
        siginfo_t receivedSignal;
        const int sigwaitResult = sigtimedwait(&sigSet, &receivedSignal, &waitingTime);
        log_msg("sigwaitResult: ", sigwaitResult);
        switch (sigwaitResult)
        {
            case -1:
            {
                break;
            }
            case SIGTERM:
            {
                pthread_exit(NULL);
            }
            default:
            {
                // pthread_exit(NULL);
            }
        }
        pthread_mutex_lock(&m_condVar->GetCondVarMutex());
        log_msg(__PRETTY_FUNCTION__, __LINE__);
        pthread_cond_timedwait(&m_condVar->GetCondVar(), &m_condVar->GetCondVarMutex(), &waitingTime);
        pthread_mutex_unlock(&m_condVar->GetCondVarMutex());

        T event;
        while (m_eventsQueue.TryPop(event))
        {
            doConsumeEvent(event);
        }
    }
}

template <typename T>
void EventsConsumer<T>::doOnEndRoutine() {}

}

#endif // EVENTS_CONSUMER_H
