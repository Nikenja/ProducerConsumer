#include <iostream>
#include <unistd.h>
#include <boost/make_shared.hpp>
#include "iexchange_data.h"
#include "events_producer.h"
#include "events_producer_consumer.h"
#include "autots_consumer.h"

using namespace EventsProducerConsumerNs;
using namespace ExchangeDataNs;
using namespace AutoTsNs;

int main(int argc, char** argv)
{
    EventsProducerConsumer<EventsProducer<IExchangeDataPtr>, AutoTsConsumer, IExchangeDataPtr> autots;

    autots.StartProduceConsume();

    ExchangeDataNs::IExchangeDataPtr event1 = boost::make_shared<IExchangeData>();
    autots.ProduceEvent(event1);

    sleep(1);

    ExchangeDataNs::IExchangeDataPtr event2 = boost::make_shared<IExchangeData>();
    autots.ProduceEvent(event2);

    sleep(1);

    autots.StopProduceConsume();

    sleep(5);

    return 0;
}
