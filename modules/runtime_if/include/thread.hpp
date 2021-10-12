#ifndef __THREAD_H__
#define __THREAD_H__
#include <cstdint>

namespace TestLib
{

/* Static class with api for manipulation thread activities */
class Thread
{
private:
  /* data */
public:
  Thread() = delete;
  Thread(const Thread&) = delete;
  Thread(Thread&&) = delete;
  ~Thread() = delete;
  Thread& operator=(const Thread&) = delete;
  Thread& operator=(Thread&&) = delete;

  static uint64_t get_thread_id(void);
};

} // namespace TestLib


#endif // __THREAD_H__