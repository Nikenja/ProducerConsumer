#ifndef STOP_ROUTINE_THROUGH_CANCEL_FIXTURE_H
#define STOP_ROUTINE_THROUGH_CANCEL_FIXTURE_H

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include "iroutine.h"

class StopRoutineThroughCancel : public RoutineNs::IRoutine
{
public:
    virtual ~StopRoutineThroughCancel() {}
private:
    void doRun()
    {
        while (true)
        {
            sleep(2);
        }
    }
};

class StopRoutineThroughCancelFixture
{
public:
    StopRoutineThroughCancelFixture()
    {
        m_routine = boost::make_shared<StopRoutineThroughCancel>();
    }
    RoutineNs::IRoutinePtr m_routine;
};

#endif // STOP_ROUTINE_THROUGH_CANCEL_FIXTURE_H
