#ifndef THREAD_JOIN_TIMEOUT_H
#define THREAD_JOIN_TIMEOUT_H

#include <pthread.h>

namespace ThreadNs
{

int thread_join_timeout(pthread_t thread, const unsigned int msecs);

} // namespace ThreadNs

#endif // THREAD_JOIN_TIMEOUT_H
