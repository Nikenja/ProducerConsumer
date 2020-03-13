#include "consumer_routine.h"
#include <signal.h>
#include <time.h>
#include "waiting_time_getter.h"
#include "log_msg.h"

namespace RoutineNs
{

ConsumerRoutine::ConsumerRoutine(
    CondVarNs::CondVar& condVar,
    SafeContainersNs::SafeQueue<ExchangeDataNs::IExchangeDataPtr>& eventsQueue) :
        m_condVar(condVar), m_eventsQueue(eventsQueue)
{
    log_msg(__PRETTY_FUNCTION__, __LINE__);
}

ConsumerRoutine::~ConsumerRoutine()
{
}

void ConsumerRoutine::doRun()
{
    sigset_t sigSet;
    if (!TrySettingSigmask(sigSet))
    {
        log_msg(__PRETTY_FUNCTION__, __LINE__);
        return;
    }

    timespec signalWaitingTime;
    if (!WaitingTimeGetterNs::try_get_monotonic_waiting_time(0, 100000000, signalWaitingTime))
    {
        log_msg(__PRETTY_FUNCTION__, __LINE__);
        return;
    }

    timespec condVarWatingTime;
    if (!WaitingTimeGetterNs::try_get_monotonic_waiting_time(0, 300000000, condVarWatingTime))
    {
        log_msg(__PRETTY_FUNCTION__, __LINE__);
        return;
    }

    while (IsRun())
    {
        if (CatchSignal(sigSet, signalWaitingTime))
        {
            log_msg(__PRETTY_FUNCTION__, __LINE__);
            pthread_exit(NULL);
        }

        log_msg(__PRETTY_FUNCTION__, __LINE__);
        pthread_mutex_lock(&m_condVar.GetCondVarMutex());
        log_msg(__PRETTY_FUNCTION__, __LINE__);
        pthread_cond_timedwait(&m_condVar.GetCondVar(), &m_condVar.GetCondVarMutex(), &condVarWatingTime);
        pthread_mutex_unlock(&m_condVar.GetCondVarMutex());
        log_msg(__PRETTY_FUNCTION__, __LINE__);

        ExchangeDataNs::IExchangeDataPtr event;
        while (m_eventsQueue.TryPop(event))
        {
            doConsumeEvent(event);
        }
        log_msg(__PRETTY_FUNCTION__, __LINE__);
    }
    log_msg(__PRETTY_FUNCTION__, __LINE__);
}

bool ConsumerRoutine::TrySettingSigmask(sigset_t& sigSet) const
{
    sigemptyset(&sigSet);
    sigaddset(&sigSet, SIGTERM);

    const int sigmaskResult = pthread_sigmask(SIG_BLOCK, &sigSet, NULL);
    if (sigmaskResult != 0)
    {
        log_msg(__PRETTY_FUNCTION__, __LINE__);
        return false;
    }

    return true;
}

bool ConsumerRoutine::CatchSignal(sigset_t& sigSet, timespec& signalWaitingTime) const
{
    siginfo_t receivedSignal;
    log_msg(__PRETTY_FUNCTION__, __LINE__);
    const int sigwaitResult = sigtimedwait(&sigSet, &receivedSignal, &signalWaitingTime);
    log_msg("sigwaitResult: ", sigwaitResult);
    switch (sigwaitResult)
    {
        case -1:
        {
            return false;
        }
        case SIGTERM:
        {
            return true;
        }
        default:
        {
            return false;
        }
    }
}

}
