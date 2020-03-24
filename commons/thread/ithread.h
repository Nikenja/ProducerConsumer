#ifndef ITHREAD_H
#define ITHREAD_H

#include <pthread.h>
#include "iroutine.h"

namespace ThreadNs
{

class IThread
{
public:
    IThread(const RoutineNs::IRoutinePtr& routine);
    virtual ~IThread();
    /**
     * Stop routine through 3 ways.
     * 1 way. Main thread set routine run state to false and try pthread_join with timeout.
     * If 1 way did not work when:
     * 2 way. Main thread call pthread_cancel for routine and try pthread_join with timeout.
     * If 2 way did not work when:
     *
     * WARNING: https://stackoverflow.com/questions/13687985/pthread-exit-in-signal-handler
     * 3 way. Main thread call pthread_kill with SIGUSR1. Signal handler call pthread_exit and
     * main thread try pthread_join (blocking call).
     */
    bool TryStopRoutine();
private:
    pthread_t m_routineId;
    RoutineNs::IRoutinePtr m_routine;

    IThread(const IThread& thread);
    IThread& operator=(const IThread& thread);

    static void* StartRoutine(void* parameter);

    bool TryStopRoutineThroughFlag();
    bool TryStopRoutineThroughCancel();
    bool TryStopRoutineThroughKill();
};

} // namespace ThreadNs

#endif // ITHREAD_H
