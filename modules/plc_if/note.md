# this module handle logical link operation (slac,..)

module cover physical layer and data link requirement of ISO15118-3

data link control SAP: service access point which defines the interface between the connection coordination module and the
low-layer communication technology for managing the link status
Connection coordination: entity which provides the whole functionality for EV to EVSE matching and initialization, through the data link control SAP
Control SAP

DATA SAP(Service Access Point): service access point that defines the interface between layer 2 and layer 3 for exchange of v2g-related payload

logical network: set of low-layer communication stations which use the same network key

management message entry MME: messages exchanged between PLC nodes or a PLC node and higher layers for control purposes


The	SUT	adapter	within	the	test	system	adapts	the	TTCN‐3	communication	operations	to	the	SUT	based
on	an	abstract	test	system	interface	and	implements	the	real	test	system	interface.	It	is	responsible	to
propagate	message	 requests	and	procedure	based	 calls	from	the	Test	Execution	(see	Figure	1)	to	the
SUT,	and	to	notify	the	Test	Execution	of	any	received	test	events	by	appending	them	to	its	port	queues.

The	SUT	adapters	of	the	test	system	shall	implement	the	TriCommunicationSA	and	the
TriCommunicationTE	interfaces	as	defined	in	ETSI	ES	201	873‐5	V4.6.1,	6.5.2.

[V2G5-005] The	ISO	15118‐3	SUT	adapter	shall	send/receive	the	encoded	SLAC	request/response
messages	through	raw	Ethernet	frames	to/from	the	SUT	as	defined	in
ISO	15118‐3:2015,	A.6	and	A.9.