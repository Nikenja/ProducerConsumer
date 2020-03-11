#ifndef ITHREAD_H
#define ITHREAD_H

#include <pthread.h>

namespace ThreadNs
{

class IThread
{
public:
    IThread();
    virtual ~IThread();

    void StartThread();
    void StopThread();
private:
    pthread_t m_thread;
    bool m_alreadyCreated;

    template <typename T>
    static void* StartRoutine(void* parameter);
};

template <typename T>
void* IThread<T>::StartRoutine(void* parameter)
{
    IRoutineThread
}

}

#endif // ITHREAD_H
