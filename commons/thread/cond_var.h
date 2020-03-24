#ifndef CONDVAR_H
#define CONDVAR_H

#include <pthread.h>
#include <boost/shared_ptr.hpp>

namespace CondVarNs
{

class CondVar
{
public:
    CondVar();
    virtual ~CondVar();
    pthread_cond_t& GetCondVar();
    pthread_mutex_t& GetCondVarMutex();
private:
    pthread_cond_t m_condVar;
    pthread_mutex_t m_condVarMutex;
};

typedef boost::shared_ptr<CondVar> CondVarPtr;

}

#endif // CONDVAR_H
