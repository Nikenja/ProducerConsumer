#include "thread_joining_data.h"

namespace ThreadNs
{

ThreadJoiningData::ThreadJoiningData(const pthread_t joinPthreadId) : m_joinPthreadId(joinPthreadId)
{
}

bool ThreadJoiningData::IsJoinState()
{
    return m_joinState.GetState();
}

void ThreadJoiningData::SetJoinState(const bool joinState)
{
    m_joinState.SetState(joinState);
}

pthread_t ThreadJoiningData::GetJoinPthreadId() const
{
    return m_joinPthreadId;
}

} // namespace ThreadNs
