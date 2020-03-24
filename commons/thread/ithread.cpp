#include "ithread.h"
#include <string.h>
#include <signal.h>
#include "thread_defs.h"
#include "thread_join_timeout.h"
#include "isignal_handler.h"
#include "log_msg.h"

namespace ThreadNs
{

IThread::IThread(const RoutineNs::IRoutinePtr& routine) : m_routine(routine)
{
    log_msg(__PRETTY_FUNCTION__, __LINE__);
    SignalHandlerNs::set_signal_handler_for(SIGUSR1);

    if (m_routine == NULL)
    {
        log_msg(__PRETTY_FUNCTION__, __LINE__);
        return;
    }
    m_routine->SetRunState(true);
    const int result = pthread_create(&m_routineId, NULL, &IThread::StartRoutine, this);
    if (result != 0)
    {
        log_msg(__PRETTY_FUNCTION__, __LINE__);
    }
}

IThread::~IThread()
{
    log_msg(__PRETTY_FUNCTION__, __LINE__);
}

bool IThread::TryStopRoutine()
{
    log_msg(__PRETTY_FUNCTION__, __LINE__);
    if (m_routine == NULL)
    {
        log_msg(__PRETTY_FUNCTION__, __LINE__);
        return false;
    }

    // 1 solution
    if (TryStopRoutineThroughFlag())
    {
        m_routine = NULL;
        return true;
    }
    // 2 solution
    if (TryStopRoutineThroughCancel())
    {
        m_routine = NULL;
        return true;
    }
    // 3 solution
    if (TryStopRoutineThroughKill())
    {
        m_routine = NULL;
        return true;
    }

    return false;
}

void* IThread::StartRoutine(void* parameter)
{
    log_msg(__PRETTY_FUNCTION__, __LINE__);
    log_msg("pthread_self()", pthread_self());

    IThread* thread = static_cast<IThread*>(parameter);
    thread->m_routine->Run();
    
    // TODO mey be this solution ?
    // IRoutine* rotine = static_cast<IRoutine*>(parameter);
    // rotine->Run();

    return NULL;
}

bool IThread::TryStopRoutineThroughFlag()
{
    log_msg(__PRETTY_FUNCTION__, __LINE__);
    m_routine->Stop();
    const int resultJoinTimeout = thread_join_timeout(m_routineId, THREAD_JOIN_TIMEOUT);
    log_msg("resultJoinTimeout", resultJoinTimeout);

    return (resultJoinTimeout == 0);
}

bool IThread::TryStopRoutineThroughCancel()
{
    log_msg(__PRETTY_FUNCTION__, __LINE__);
    const int cancelResult = pthread_cancel(m_routineId);
    if (cancelResult != 0)
    {
        log_msg(__PRETTY_FUNCTION__, __LINE__);
        return false;
    }
    const int resultJoinTimeout = thread_join_timeout(m_routineId, THREAD_JOIN_TIMEOUT);
    log_msg("resultJoinTimeout", resultJoinTimeout);

    return (resultJoinTimeout == 0);
}

bool IThread::TryStopRoutineThroughKill()
{
    log_msg(__PRETTY_FUNCTION__, __LINE__);
    const int killResult = pthread_kill(m_routineId, SIGUSR1);
    if (killResult != 0)
    {
        log_msg(__PRETTY_FUNCTION__, __LINE__);
        return false;
    }
    const int resultJoinTimeout = pthread_join(m_routineId, NULL);
    log_msg("resultJoinTimeout", resultJoinTimeout);

    return (resultJoinTimeout == 0);
}

} // namespace ThreadNs
