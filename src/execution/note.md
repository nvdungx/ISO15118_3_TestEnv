SECC_Tester	(MTC): This	component	type	is	the	main	type	for	the	tests	of	an	SECC.	A	SLAC_Port,
HAL_61851_Port	and	a	HAL_61851_Internal_Port	(see	Table	5)	are	assigned	to
this	component	type.

EVCC_Tester	(MTC): This	component	type	is	the	main	type	for	the	tests	of	an	EVCC.	A	SLAC_Port,
HAL_61851_Port	and	a	HAL_61851_Internal_Port	(see	Table	5)	are	assigned	to
this	component	type.
HAL_61851_Listener	(PTC): The	HAL_61851_Listener	is	responsible	for	watching	the	correct	IEC	61851
behavior	and	is	used	in	the	form	of	a	parallel	test	component	(PTC).	This
component	uses	the	HAL_61851_Port	(see	Table	5)	to	communicate	with	an
IEC	61851‐1	SUT	Adapter	and	the	HAL_61851_Internal_Port	to	communicate
with	the	MTC.

SLAC_Port: This	port	is	used	to	send/receive	SLAC	messages	defined	in	ISO	15118‐3
to/from	the	EVCC/SECC.

HAL_61851_Port: This	port	is	used	to	interact	with	an	IEC	61851	signalling	unit.	The	unit	will
set	the	corresponding	signalling	to	the	SUT	(SECC/EVCC).	The	specification
of	the	IEC	61851	signalling	unit	is	out	of	scope	of	this	standard.

HAL_61851_Internal_Port: This	port	is	used	to	synchronize	the	status	of	the	IEC	61851‐1	PWM	signal
between	the	MTC	(SECC_Tester	or	EVCC_Tester)	and	PTC
(HAL_61851_Listener_Port).