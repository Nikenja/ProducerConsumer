#ifndef ITHREAD_H
#define ITHREAD_H

#include <pthread.h>
#include "iroutine.h"

namespace ThreadNs
{

class IThread
{
public:
    IThread();
    virtual ~IThread();

    void StartRoutine(const RoutineNs::IRoutinePtr& routine);
    /**
     * Stop routine through 3 solutions.
     * 1 solution. Maint thread set routine run state to false and try pthread_join with timeout.
     * If 1 solution did not work when:
     * 2 solution. Maint thread call pthread_cancel and try pthread_join with timeout
     * If 2 solution did not work when:
     * 3 solution. Maint thread call pthread_kill with SIGTERM. Routine call pthread_exit and
     * main thread try pthread_join as mach as possible.
     */
    void StopRoutine();
private:
    pthread_t m_routineId;
    bool m_alreadyStarted;
    RoutineNs::IRoutinePtr m_routine;

    static void* StartRoutine(void* parameter);

    bool TryStopRoutineThroughFlag();
    bool TryStopRoutineThroughCancel();
    bool TryStopRoutineThroughKill();
};

}

#endif // ITHREAD_H
