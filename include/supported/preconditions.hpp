#ifndef __PRECONDITIONS_H__
#define __PRECONDITIONS_H__

#include "datatype.hpp"
#include <thread>
#include <mutex>

namespace TestLib
{
  class PreConditions_SECC_15118_3
  {
  private:
    PreConditions_SECC_15118_3() {

    }
  public:
    PreConditions_SECC_15118_3(const PreConditions_SECC_15118_3&) = delete;
    PreConditions_SECC_15118_3& operator=(const PreConditions_SECC_15118_3&) = delete;

    static PreConditions_SECC_15118_3 &get_instance() {
      static PreConditions_SECC_15118_3 instance;
      return instance;
    }
  };

  class PreConditions_EVCC_15118_3
  {
  private:
    /* data */
  public:
    PreConditions_EVCC_15118_3(/* args */) {}
    ~PreConditions_EVCC_15118_3() {}
  };

} // namespace TestLib


#endif // __PRECONDITIONS_H__