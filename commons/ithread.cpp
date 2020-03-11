#include "ithread.h"
#include <string.h>
#include <signal.h>
#include "log_msg.h"

namespace ThreadNs
{

IThread::IThread() : m_alreadyCreated(false)
{
    log_msg(__PRETTY_FUNCTION__, __LINE__);
}

IThread::~IThread()
{
    log_msg(__PRETTY_FUNCTION__, __LINE__);
}

void IThread::StartThread()
{
    if (m_alreadyCreated)
    {
        return;
    }

    const int result = pthread_create(&m_thread, NULL, &IThread::StartRoutine, this);

    if (result != 0)
    {
        log_msg(__PRETTY_FUNCTION__, __LINE__);        
    }

    m_alreadyCreated = true;
}

void IThread::StopThread()
{
    log_msg(__PRETTY_FUNCTION__, __LINE__);
    if (m_alreadyCreated != true)
    {
        return;
    }

    pthread_kill(m_thread, SIGCHLD);

    pthread_join(m_thread, NULL);

    // const int cancelResult = pthread_cancel(m_thread);
    // if (cancelResult != 0)
    // {
    //     log_msg(__PRETTY_FUNCTION__, __LINE__);
    // }
    // log_msg(__PRETTY_FUNCTION__, __LINE__);

    // timespec waitingTime;
    // if (clock_gettime(CLOCK_REALTIME, &waitingTime) == -1)
    // {
    //     log_msg(__PRETTY_FUNCTION__, __LINE__);
    // }
    // waitingTime.tv_sec += 1;
    // // waitingTime.tv_nsec += 1000000;
    
    // const int timedjoinResult = pthread_timedjoin_np(m_thread, NULL, &waitingTime);
    // if (timedjoinResult != 0)
    // {
    //     log_msg(__PRETTY_FUNCTION__, __LINE__);
    //     log_msg("error: ", strerror(timedjoinResult));
    // }
}

// void* IThread::StartRoutine(void* self)
// {
//     IThread* thread = reinterpret_cast<IThread*>(self);

//     // const int result = pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);
    
//     // if (result != 0)
//     // {
//         // log_msg(__PRETTY_FUNCTION__, __LINE__);
//     // }

//     thread->doRoutine();
//     thread->doOnEndRoutine();

//     return NULL;
// }

}
