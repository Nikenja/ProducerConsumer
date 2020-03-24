#include "consumer_routine.h"
#include <time.h>
#include "waiting_time_getter.h"
#include "log_msg.h"

namespace RoutineNs
{

ConsumerRoutine::ConsumerRoutine(
    CondVarNs::CondVar& condVar,
    ThreadSafeNs::SafeQueue<ExchangeDataNs::IExchangeDataPtr>& eventsQueue) :
        m_condVar(condVar), m_eventsQueue(eventsQueue)
{
    log_msg(__PRETTY_FUNCTION__, __LINE__);
}

ConsumerRoutine::~ConsumerRoutine()
{
}

void ConsumerRoutine::doRun()
{
    timespec condVarWatingTime;
    if (!TimeHelperNs::try_get_monotonic_waiting_time(0, 100000000, condVarWatingTime))
    {
        log_msg(__PRETTY_FUNCTION__, __LINE__);
        return;
    }

    while (GetRunState())
    {
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

}
