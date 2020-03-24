#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE IHTREAD_TRY_STOP_ROUTINE_THROUGH_KILL_MODULE
#include <boost/test/unit_test.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include "ithread.h"
#include "iroutine.h"
#include "stop_routine_through_signal_fixture.h"

/**
 * Stop routine through pthread_kill.
 */

BOOST_FIXTURE_TEST_CASE(StopRoutineThroughSignalCase, StopRoutineThroughSignalFixture)
{
    ThreadNs::IThread thread(m_routine);

    sleep(2);

    BOOST_CHECK_EQUAL(thread.TryStopRoutine(), true);
}
