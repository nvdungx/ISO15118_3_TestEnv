#ifndef __PORT_H__
#define __PORT_H__

#include "datatype.hpp"
#include "slac_type.hpp"
#include "service.hpp"
#include "component.hpp"
#include <queue>

namespace TestLib
{
/* communication port: abstract mechanism facilitating communication between test components
  NOTE: A communication port is modelled as a FIFO queue in the receiving direction. Ports can be message-based or procedure-based. */

void activate();
void deactivate();
void all_component_kill();

/* Message-based port:
type port PortTypeIdentifier message "{"
{ (address Type ";") |
(map param "(" { FormalValuePar [","] }+ ")") |
(unmap param "(" { FormalValuePar [","] }+ ")") |
((in | out | inout) { MessageType [ "," ] }+ ";") }
"}"

Procedure-based port:
type port PortTypeIdentifier procedure "{"
{ (address Type ";" ) |
(map param "(" { FormalValuePar [","] }+ ")") |
(unmap param "(" { FormalValuePar [","] }+ ")") |
((in | out | inout) { Signature [ "," ] }+ ";") }
"}" */

/* Port type: message|procedure
    list of port operations:
      receive, trigger, getcall, reply or raise
      send,             call, getreply or catch
    datas:
      collection of message type or procedure signature
 */
using namespace DataStructure_SLAC;
typedef MME MessageType;

class Port : public std::enable_shared_from_this<Port>,
              public TestObj
{
private:
  std::shared_ptr<Component> _ptrParentComp;
  PortAddress _pAddr;
  PortType _pType;

public:
  Port();
  Port(PortType ptype);
  ~Port();

  const std::shared_ptr<Component> &get_parent_comp(void);
  void set_parent_comp(const std::shared_ptr<Component> &parentComp);

  /* -------------- controlling operations -------------- */
  /* Clear port queue */
  virtual void clear();
  /* Clear queue and enable sending and receiving at a port */
  virtual void start();
  /* Disable sending and disallow receiving operations to match at a port */
  virtual void stop();
  /* Disable sending and disallow receiving operations to match new messages/calls */
  virtual void halt();
  /* Check the state of a port */
  virtual void checkstate();

  /* -------------- configuration operations -------------- */
  /* map/unmap between component's port and tsi's port */
  friend void map(const std::shared_ptr<Port> &compPort, const std::shared_ptr<Port> &tsiPort);
  friend void unmap(const std::shared_ptr<Port> &compPort, const std::shared_ptr<Port> &tsiPort);
  /* connect/disconnect between component's port */
  friend void connect(const std::shared_ptr<Port> &compPort, const std::shared_ptr<Port> &targetPort);
  friend void disconnect(const std::shared_ptr<Port> &compPort, const std::shared_ptr<Port> &targetPort);

  /* ------------- Examine top element of incoming port queues ------------- */
  /* Check msg/call/exception/reply received */
  virtual void check(void);
};

class MsgPort : public Port
{
  std::queue<MessageType> _messageQueue;
  /* -------------- message communication operations -------------- */
  /* Send message */
  virtual void send(void);
  /* Receive message */
  virtual void receive(void);
  /* Trigger on message */
  virtual void trigger(void);
};

class PcrPort : public Port
{
  std::queue<Signature> _procedureQueue;
  /* -------------- procedure communication operations -------------- */
  /* Invoke procedure call */
  virtual void call(void);
  /* Accept procedure call from remote entity */
  virtual void getcall(void);
  /* Reply to procedure call from remote entity */
  virtual void reply(void);
  /* Raise exception (to an accepted call) */
  virtual void raise(void);
  /* Handle response from a previous call */
  virtual void getreply(void);
  /* Catch exception (from called entity) */
  virtual void pcatch(void);
};

class SLAC_Port : public Port
{
private:
  /* data */
public:
  SLAC_Port(/* args */) {
  }
  ~SLAC_Port() {}
};

class HAL_61851_Port : public Port
{
private:
  /* data */
public:
  HAL_61851_Port(/* args */) {}
  ~HAL_61851_Port() {}
};

class HAL_61851_Internal_Port : public Port
{
private:
  /* data */
public:
  HAL_61851_Internal_Port(/* args */)  {}
  ~HAL_61851_Internal_Port() {}
};

} // namespace TestLib


#endif // __PORT_H__