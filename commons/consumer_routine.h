#ifndef CONSUMER_ROUTINE_H
#define CONSUMER_ROUTINE_H

#include "iroutine.h"
#include "cond_var.h"
#include "safe_queue.h"
#include "iexchange_data.h"

namespace RoutineNs
{

class ConsumerRoutine : public IRoutine
{
public:
    ConsumerRoutine(
        CondVarNs::CondVar& condVar,
        SafeContainersNs::SafeQueue<ExchangeDataNs::IExchangeDataPtr>& eventsQueue);

    virtual ~ConsumerRoutine();
private:
    CondVarNs::CondVar& m_condVar;
    SafeContainersNs::SafeQueue<ExchangeDataNs::IExchangeDataPtr>& m_eventsQueue;

    void doRun();
    virtual void doConsumeEvent(const ExchangeDataNs::IExchangeDataPtr& event) = 0;

    bool TrySettingSigmask(sigset_t& sigSet) const;
    bool CatchSignal(sigset_t& sigSet, timespec& signalWaitingTime) const;
};

}

#endif // CONSUMER_ROUTINE_H
