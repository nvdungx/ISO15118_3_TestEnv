#ifndef __POSTCONDITIONS_H__
#define __POSTCONDITIONS_H__

#include "datatype.hpp"
#include "execution/paralleltestcomponent.hpp"

namespace TestLib
{
extern void all_timer_stop(void);

class PostConditions_SECC_15118_3
{
private:
  PostConditions_SECC_15118_3(/* args */)
  {
  }
public:
  PostConditions_SECC_15118_3(const PostConditions_SECC_15118_3&) = delete;
  PostConditions_SECC_15118_3& operator=(const PostConditions_SECC_15118_3&) = delete;
  ~PostConditions_SECC_15118_3()
  {
  }

  static PostConditions_SECC_15118_3 &get_instance() {
    static PostConditions_SECC_15118_3 instance;
    return instance;
  }
  void f_SECC_CMN_PO_InitialState_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener);
};

class PostConditions_EVCC_15118_3
{
private:
  PostConditions_EVCC_15118_3(/* args */)
  {
  }
public:
  PostConditions_EVCC_15118_3(const PostConditions_EVCC_15118_3&) = delete;
  PostConditions_EVCC_15118_3& operator=(const PostConditions_EVCC_15118_3&) = delete;
  ~PostConditions_EVCC_15118_3()
  {
  }

  static PostConditions_EVCC_15118_3 &get_instance() {
    static PostConditions_EVCC_15118_3 instance;
    return instance;
  }
  void f_EVCC_CMN_PO_InitialState_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener);
};
} // namespace TestLib

#endif // __POSTCONDITIONS_H__