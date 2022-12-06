A test system interface definition is identical to a component definition, i.e. it is a list of
all possible communication ports through which the test case is connected to the SUT.

A component type definition is used to define the test system interface because, conceptually, component type
definitions and test system interface definitions have the same form (both are collections of ports defining possible
connection points). When used as test system interfaces, components cannot make use of any constants, variables and
timers declared in the component type.


operation returning the component reference of the test system interface is system. 