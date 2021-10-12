#include "thread.hpp"
#include <thread>
#include <pthread.h>
namespace TestLib
{
  uint64_t Thread::get_thread_id(void)
  {
    return (uint64_t)pthread_self();
  }
} // namespace TestLib
