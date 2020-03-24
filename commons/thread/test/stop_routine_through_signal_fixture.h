#ifndef STOP_ROUTINE_THROUGH_SIGNAL_FIXTURE_H
#define STOP_ROUTINE_THROUGH_SIGNAL_FIXTURE_H

#include <pthread.h>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include "iroutine.h"

class StopRoutineThroughSignal : public RoutineNs::IRoutine
{
public:
    StopRoutineThroughSignal() : m_mutex(PTHREAD_MUTEX_INITIALIZER)
    {
        pthread_mutex_lock(&m_mutex);
    }
    virtual ~StopRoutineThroughSignal() {}
private:
    pthread_mutex_t m_mutex;
    void doRun()
    {
        pthread_mutex_lock(&m_mutex);
    }
};

class StopRoutineThroughSignalFixture
{
public:
    StopRoutineThroughSignalFixture()
    {
        m_routine = boost::make_shared<StopRoutineThroughSignal>();
    }
    RoutineNs::IRoutinePtr m_routine;
};

#endif // STOP_ROUTINE_THROUGH_SIGNAL_FIXTURE_H
