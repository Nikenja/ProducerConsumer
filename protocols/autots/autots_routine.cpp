#include "autots_routine.h"
#include "log_msg.h"

namespace RoutineNs
{

AutoTsRoutine::AutoTsRoutine(
    CondVarNs::CondVar& condVar,
    SafeContainersNs::SafeQueue<ExchangeDataNs::IExchangeDataPtr>& eventsQueue) :
        ConsumerRoutine(condVar, eventsQueue)
{
}

void AutoTsRoutine::doConsumeEvent(const ExchangeDataNs::IExchangeDataPtr& event)
{
    log_msg(__PRETTY_FUNCTION__, __LINE__);
}

}
