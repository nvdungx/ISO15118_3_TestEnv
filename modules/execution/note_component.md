------------ COMPONENT --------

SECC_Tester (MTC): This component type is the main type for the tests of an SECC.
A SLAC_Port, HAL_61851_Port and a HAL_61851_Internal_Port (see Table 5) are assigned to this component type.

EVCC_Tester (MTC): This component type is the main type for the tests of an EVCC.
A SLAC_Port, HAL_61851_Port and a HAL_61851_Internal_Port (see Table 5) are assigned to this component type.

HAL_61851_Listener (PTC): The HAL_61851_Listener is responsible for watching the correct IEC 61851
behavior and is used in the form of a parallel test component (PTC).
This component uses the HAL_61851_Port (see Table 5) to communicate with an
IEC 61851‐1 SUT Adapter and the HAL_61851_Internal_Port to communicate with the MTC.

test system interface
TSI
test component that provides a mapping of the ports available in the (abstract) TTCN‐3 test system to
those offered by a real test system

A module consists of a set of definitions that define test components, communication ports, other kinds of types (see
clause 6), constants, test data templates,
functions including the module control function, signatures for procedure calls at ports, test cases, etc.

A special kind of data structure called a template provides parameterization and matching mechanisms for specifying
test data to be sent or received over the test ports.

It is also possible to declare constants, variables, templates and timers local to a particular component type. These
declarations are visible to all testcases, functions and altsteps that run on an instance of the given component type. This
shall be explicitly stated using the runs on keyword (see clause 15.12) in the testcase, function or altstep header

Within every configuration there shall be one (and only one) Main Test Component (MTC).
Test components that are not MTCs are called parallel test components or PTCs

The MTC shall be created by the system automatically at the start of each test case execution. The behaviour defined in the body of the test case shall execute on this component.
During execution of a test case, other components can be created dynamically by the explicit use of the create operation.