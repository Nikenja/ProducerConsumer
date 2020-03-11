#ifndef AUTOTS_CONSUMER_H
#define AUTOTS_CONSUMER_H

#include "iexchange_data.h"
#include "events_consumer.h"
#include "cond_var.h"
#include "log_msg.h"

namespace AutoTsNs
{

class AutoTsConsumer : public EventsProducerConsumerNs::EventsConsumer<ExchangeDataNs::IExchangeDataPtr>
{
public:
    AutoTsConsumer(
        const CondVarNs::CondVarPtr& condVar,
        SafeContainersNs::SafeQueue<ExchangeDataNs::IExchangeDataPtr>& eventsQueue
    );
private:
    virtual void doConsumeEvent(const ExchangeDataNs::IExchangeDataPtr& event);
};

}

#endif // AUTOTS_CONSUMER_H
