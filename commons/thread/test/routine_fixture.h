#ifndef ROUTINE_FIXTURE_H
#define ROUTINE_FIXTURE_H

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include "iroutine.h"

class Routine : public RoutineNs::IRoutine
{
public:
    virtual ~Routine() {}
private:
    void doRun()
    {
        while (GetRunState())
        {
            sleep(2);
        }
    }
};

class RoutineFixture
{
public:
    RoutineFixture()
    {
        m_routine = boost::make_shared<Routine>();
    }
    RoutineNs::IRoutinePtr m_routine;
};

#endif // ROUTINE_FIXTURE_H
