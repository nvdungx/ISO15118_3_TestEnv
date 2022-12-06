------------- PORT -----------
In general PORT shall be a queue(message or procedure)
message: Receiver message queue - Provider(map or connect to Receiver) send msg to Receiver queue
        Receiver: rx, tx
        Provider: tx, rx
procedure: Server service queue - Client(map or connect to Server) trigger/call sync/async procedure provide by Server
           Client queue - receive response data from Server 
  Server: rx queue, Client: rx queue

The operations on these ports provide both message-based and procedure-based communication capabilities. Procedure calls may be used for testing implementations which are not message based

SLAC_Port: This port is used to send/receive SLAC messages defined in ISO 15118‐3 to/from the EVCC/SECC.

HAL_61851_Port: This port is used to interact with an IEC 61851 signalling unit.
The unit will set the corresponding signalling to the SUT (SECC/EVCC).
The specification of the IEC 61851 signalling unit is out of scope of this standard.

HAL_61851_Internal_Port: This port is used to synchronize the status of the IEC 61851‐1 PWM signal
between the MTC (SECC_Tester or EVCC_Tester) and PTC (HAL_61851_Listener_Port).

communication port: abstract mechanism facilitating communication between test components

Ports facilitate communication between test components and between test components and the test system interface
=> message-based and procedure-based ports
* Message-based ports shall be identified by the keyword message
* Procedure-based ports shall be identified by the keyword procedure

Ports are bidirectional
procedure incoming port list are getcall, reply and raise
          outcoming port list are call, getreply and catch.

test interface port operation:
receive, trigger, getcall, reply or raise
send,             call, getreply or catch

Each port type definition shall have *one or more lists indicating the allowed collection of (message) types or procedure signatures* together with the allowed communication direction

allows to bind an address type to a port.

Each port is modelled as an infinite FIFO queue which stores the incoming messages or procedure calls until they are processed by the component owning that port (see figure 5).
NOTE: While TTCN-3 ports are infinite in principle in a real test system they may overflow. This is to be treated as a test case error
One-to-many connections are also allowed

22.1.1 Principles of message-based communication
Message-based communication is communication based on an asynchronous message exchange
=> Message-based communication is non-blocking on the send operation, SENDER continues immediately after the send operation occurs
=> The RECEIVER is blocked on the receive operation until it processes the received message.
=> trigger operation that filters messages with certain matching criteria from a stream of received messages on a given incoming port
Messages at the top of the queue that do not fulfil the matching criteria are removed from the port without any further action

22.1.2 Principles of procedure-based communication
Blocking procedure-based communication is blocking on the calling and the called side, whereas non-blocking procedure-based communication is only blocking on the called side