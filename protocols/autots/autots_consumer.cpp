#include "autots_consumer.h"

namespace AutoTsNs
{

AutoTsConsumer::AutoTsConsumer(
    const CondVarNs::CondVarPtr& condVar,
    SafeContainersNs::SafeQueue<ExchangeDataNs::IExchangeDataPtr>& eventsQueue) :
        EventsProducerConsumerNs::EventsConsumer<ExchangeDataNs::IExchangeDataPtr>(condVar, eventsQueue)
{
}

void AutoTsConsumer::doConsumeEvent(const ExchangeDataNs::IExchangeDataPtr& event)
{
    log_msg(__PRETTY_FUNCTION__, __LINE__);
}

}
