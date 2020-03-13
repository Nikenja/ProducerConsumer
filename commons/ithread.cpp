#include "ithread.h"
#include <string.h>
#include <signal.h>
#include "log_msg.h"
#include "pthread_join_timeout.h"

namespace ThreadNs
{

IThread::IThread() : m_alreadyStarted(false)
{
    log_msg(__PRETTY_FUNCTION__, __LINE__);
}

IThread::~IThread()
{
    log_msg(__PRETTY_FUNCTION__, __LINE__);
}

// TODO подумать на переносом StartRoutine в IThread()
void IThread::StartRoutine(const RoutineNs::IRoutinePtr& routine)
{
    log_msg(__PRETTY_FUNCTION__, __LINE__);
    if (m_alreadyStarted)
    {
        return;
    }

    if (routine == NULL)
    {
        return;
    }

    m_routine = routine;

    const int result = pthread_create(&m_routineId, NULL, &IThread::StartRoutine, m_routine.get());
    if (result != 0)
    {
        log_msg(__PRETTY_FUNCTION__, __LINE__);        
    }

    m_alreadyStarted = true;
}

void IThread::StopRoutine()
{
    if (m_alreadyStarted != true)
    {
        return;
    }

    // 1 solution
    if (TryStopRoutineThroughFlag())
    {
        log_msg(__PRETTY_FUNCTION__, __LINE__);
        return;
    }
    // 2 solution
    if (TryStopRoutineThroughCancel())
    {
        log_msg(__PRETTY_FUNCTION__, __LINE__);
        return;
    }
    // 3 solution
    TryStopRoutineThroughKill();
    log_msg(__PRETTY_FUNCTION__, __LINE__);
}

void* IThread::StartRoutine(void* parameter)
{
    log_msg(__PRETTY_FUNCTION__, __LINE__);
    RoutineNs::IRoutine* routine = static_cast<RoutineNs::IRoutine*>(parameter);

    routine->Run();

    return NULL;
}

bool IThread::TryStopRoutineThroughFlag()
{
    m_routine->Stop();
    const int resultJoinTimeout = pthread_join_timeout(m_routineId, 10000);
    log_msg("resultJoinTimeout", resultJoinTimeout);

    return (resultJoinTimeout == 0);
}

bool IThread::TryStopRoutineThroughCancel()
{
    const int cancelResult = pthread_cancel(m_routineId);
    if (cancelResult != 0)
    {
        log_msg(__PRETTY_FUNCTION__, __LINE__);
        return false;
    }
    const int resultJoinTimeout = pthread_join_timeout(m_routineId, 10000);
    log_msg("resultJoinTimeout", resultJoinTimeout);

    return (resultJoinTimeout == 0);
}

bool IThread::TryStopRoutineThroughKill()
{
    const int killResult = pthread_kill(m_routineId, SIGTERM);
    if (killResult != 0)
    {
        log_msg(__PRETTY_FUNCTION__, __LINE__);
        return false;
    }
    const int resultJoinTimeout = pthread_join(m_routineId, NULL);
    log_msg("resultJoinTimeout", resultJoinTimeout);

    return (resultJoinTimeout == 0);
}

}
