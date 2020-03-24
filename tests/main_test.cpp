#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MainTestModule
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <boost/test/unit_test.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include "iroutine.h"
#include "autots_routine.h"
#include "ithread.h"
#include "cond_var.h"
#include "safe_queue.h"
#include "producer.h"
#include "iexchange_data.h"

typedef boost::shared_ptr< RoutineNs::Producer<ExchangeDataNs::IExchangeDataPtr> > ProducerPtr;

class ProducerConsumerFixture
{
public:
    ProducerPtr m_producer;
    RoutineNs::IRoutinePtr m_autoTsConsumer;

    ProducerConsumerFixture()
    {
        m_producer = boost::make_shared< RoutineNs::Producer<ExchangeDataNs::IExchangeDataPtr> >(
            m_condVar, m_eventsQueue
        );
        m_autoTsConsumer = boost::make_shared<RoutineNs::AutoTsRoutine>(m_condVar, m_eventsQueue);
    }
    ~ProducerConsumerFixture()
    {
    }
private:
    CondVarNs::CondVar m_condVar;
    SafeContainersNs::SafeQueue<ExchangeDataNs::IExchangeDataPtr> m_eventsQueue;
};

BOOST_FIXTURE_TEST_CASE(StartStopRoutine, ProducerConsumerFixture)
{
    ThreadNs::IThread thread;
    thread.StartRoutine(m_autoTsConsumer);

    sleep(2);

    std::system("sleep 60");
    std::system("ps -T -C main_test > StartStopRoutineResult.txt");

    // ExchangeDataNs::IExchangeDataPtr event =
    //     boost::make_shared<ExchangeDataNs::IExchangeData>();

    // producer.ProduceEvent(event);

    // sleep(5);

    // добавить проверку перед тем, как останавливать
    thread.StopRoutine();

    sleep(2);

    std::system("ps -T -C main_test >> StartStopRoutineResult.txt");    
}
