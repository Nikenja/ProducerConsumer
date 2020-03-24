#include "iroutine.h"
#include <signal.h>
#include <boost/make_shared.hpp>
#include "isignal_handler.h"
#include "log_msg.h"

namespace RoutineNs
{

IRoutine::IRoutine()
{
}

IRoutine::~IRoutine()
{
    log_msg(__PRETTY_FUNCTION__, __LINE__);
}

void IRoutine::Run()
{
    doRun();
    SetRunState(false);
}

void IRoutine::Stop()
{
    SetRunState(false);
    log_msg(__PRETTY_FUNCTION__, __LINE__);
}

bool IRoutine::GetRunState()
{
    return m_runState.GetState();
}

void IRoutine::SetRunState(const bool runState)
{
    m_runState.SetState(runState);
}

} // namespace RoutineNs
