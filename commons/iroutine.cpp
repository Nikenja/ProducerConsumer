#include "iroutine.h"
#include "log_msg.h"

namespace RoutineNs
{

IRoutine::~IRoutine()
{
}

void IRoutine::Run()
{
    m_runState.SetState(true);
    doRun();
    m_runState.SetState(false);
}

void IRoutine::Stop()
{
    m_runState.SetState(false);
}

bool IRoutine::IsRun()
{
    log_msg(__PRETTY_FUNCTION__, __LINE__);
    return m_runState.GetState();
}

}
