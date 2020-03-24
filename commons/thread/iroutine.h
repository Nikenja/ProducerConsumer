#ifndef IROUTINE_H
#define IROUTINE_H

#include <pthread.h>
#include <boost/shared_ptr.hpp>
#include "safe_state.h"

namespace RoutineNs
{

class IRoutine
{
public:
    IRoutine();
    virtual ~IRoutine();
    void Run();
    void Stop();
    bool GetRunState();
    void SetRunState(const bool runState);

private:
    ThreadSafeNs::SafeState m_runState;

    virtual void doRun() = 0;
};

typedef boost::shared_ptr<IRoutine> IRoutinePtr;

} // namespace RoutineNs

#endif // IROUTINE_H
