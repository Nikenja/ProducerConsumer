#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE IHTREAD_TEST_MODULE
#include <boost/test/unit_test.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include "ithread.h"
#include "iroutine.h"
#include "routine_fixture.h"
#include "stop_routine_through_flag_fixture.h"
#include "stop_routine_through_cancel_fixture.h"

/**
 * Common tests for IThread class.
 */
BOOST_AUTO_TEST_SUITE(IThreadClass)

BOOST_AUTO_TEST_CASE(IThreadConstructor)
{
    ThreadNs::IThread thread(NULL);
    BOOST_CHECK_EQUAL(thread.TryStopRoutine(), false);
}

BOOST_AUTO_TEST_SUITE_END()

/**
 * Common tests for IRoutine class.
 */
BOOST_FIXTURE_TEST_SUITE(IRoutineClass, RoutineFixture)

BOOST_AUTO_TEST_CASE(TryStopRoutine)
{
    ThreadNs::IThread thread(m_routine);

    BOOST_CHECK_EQUAL(thread.TryStopRoutine(), true);
}

BOOST_AUTO_TEST_CASE(TwiceCallTryStopRoutine)
{
    ThreadNs::IThread thread(m_routine);
    thread.TryStopRoutine();

    BOOST_CHECK_EQUAL(thread.TryStopRoutine(), false);
}

BOOST_AUTO_TEST_CASE(CheckRoutineRunStateWhenRoutineCreate)
{
    BOOST_CHECK_EQUAL(m_routine->GetRunState(), false);
}

BOOST_AUTO_TEST_CASE(CheckRoutineRunStateWhenRoutineRun)
{
    ThreadNs::IThread thread(m_routine);
    
    BOOST_CHECK_EQUAL(m_routine->GetRunState(), true);
    
    thread.TryStopRoutine();  
}

BOOST_AUTO_TEST_SUITE_END()


/**
 * Stop routine different ways.
 */
BOOST_AUTO_TEST_SUITE(RoutineWithDifferentStops)

BOOST_FIXTURE_TEST_CASE(StopRoutineThroughFlag, StopRoutineThroughFlagFixture)
{
    ThreadNs::IThread thread(m_routine);

    BOOST_CHECK_EQUAL(thread.TryStopRoutine(), true);
}

BOOST_FIXTURE_TEST_CASE(StopRoutineThroughCancel, StopRoutineThroughCancelFixture)
{
    ThreadNs::IThread thread(m_routine);

    BOOST_CHECK_EQUAL(thread.TryStopRoutine(), true);
}

BOOST_AUTO_TEST_SUITE_END()
