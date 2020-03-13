#ifndef AUTOTS_ROUTINE_H
#define AUTOTS_ROUTINE_H

#include "consumer_routine.h"
#include "cond_var.h"
#include "safe_queue.h"
#include "iexchange_data.h"

namespace RoutineNs
{

class AutoTsRoutine : public ConsumerRoutine
{
public:
    AutoTsRoutine(
        CondVarNs::CondVar& condVar,
        SafeContainersNs::SafeQueue<ExchangeDataNs::IExchangeDataPtr>& eventsQueue
    );
private:
    void doConsumeEvent(const ExchangeDataNs::IExchangeDataPtr& event);
};

}

#endif // AUTOTS_ROUTINE_H
