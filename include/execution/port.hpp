#ifndef __PORT_H__
#define __PORT_H__

namespace TestLib
{
/* communication port: abstract mechanism facilitating communication between test components
  NOTE: A communication port is modelled as a FIFO queue in the receiving direction. Ports can be
message-based or procedure-based. */

class SLAC_Port
{
private:
  /* data */
public:
  SLAC_Port(/* args */) {}
  ~SLAC_Port() {}
};

class HAL_61851_Port
{
private:
  /* data */
public:
  HAL_61851_Port(/* args */) {}
  ~HAL_61851_Port() {}
};

class HAL_61851_Internal_Port
{
private:
  /* data */
public:
  HAL_61851_Internal_Port(/* args */) {}
  ~HAL_61851_Internal_Port() {}
};

} // namespace TestLib


#endif // __PORT_H__