#ifndef STOP_ROUTINE_THROUGH_FLAG_H
#define STOP_ROUTINE_THROUGH_FLAG_H

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include "iroutine.h"

class StopRoutineThroughFlag : public RoutineNs::IRoutine
{
public:
    virtual ~StopRoutineThroughFlag() {}
private:
    void doRun()
    {
        while (GetRunState())
        {
            sleep(2);
        }
    }
};

class StopRoutineThroughFlagFixture
{
public:
    StopRoutineThroughFlagFixture()
    {
        m_routine = boost::make_shared<StopRoutineThroughFlag>();
    }
    RoutineNs::IRoutinePtr m_routine;
};

#endif // STOP_ROUTINE_THROUGH_FLAG_H
