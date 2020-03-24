#include "cond_var.h"
#include <time.h>

namespace CondVarNs
{

CondVar::CondVar() : m_condVarMutex(PTHREAD_MUTEX_INITIALIZER)
{
    pthread_condattr_t condVarAttr;
    pthread_condattr_init(&condVarAttr);
    pthread_condattr_setclock(&condVarAttr, CLOCK_MONOTONIC);
    pthread_cond_init(&m_condVar, &condVarAttr);
}

CondVar::~CondVar()
{
    pthread_cond_destroy(&m_condVar);
}

pthread_cond_t& CondVar::GetCondVar()
{
    return m_condVar;
}

pthread_mutex_t& CondVar::GetCondVarMutex()
{
    return m_condVarMutex;
}

}
