#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MainTestModule
#include <iostream>
#include <unistd.h>
#include <boost/test/unit_test.hpp>
#include <boost/make_shared.hpp>
#include "iroutine.h"
#include "autots_routine.h"
#include "ithread.h"
#include "cond_var.h"
#include "safe_queue.h"
#include "producer.h"
#include "iexchange_data.h"

BOOST_AUTO_TEST_SUITE()

BOOST_AUTO_TEST_CASE(FisrtCase)
{
    CondVarNs::CondVar condVar;
    SafeContainersNs::SafeQueue<ExchangeDataNs::IExchangeDataPtr> eventsQueue;

    RoutineNs::Producer<ExchangeDataNs::IExchangeDataPtr> producer(condVar, eventsQueue);

    RoutineNs::IRoutinePtr autoTsRoutine =
        boost::make_shared<RoutineNs::AutoTsRoutine>(condVar, eventsQueue);

    ThreadNs::IThread thread;
    thread.StartRoutine(autoTsRoutine);

    sleep(2);

    // ExchangeDataNs::IExchangeDataPtr event =
    //     boost::make_shared<ExchangeDataNs::IExchangeData>();

    // producer.ProduceEvent(event);

    // sleep(5);

    // добавить проверку перед тем, как останавливать
    thread.StopRoutine();

    sleep(2);
}

BOOST_AUTO_TEST_SUITE_END()

