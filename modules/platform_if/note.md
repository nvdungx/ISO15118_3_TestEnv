# this module define general timer, external function (i.e. function interact with external system (load control...))

The platform adapter within the test system is responsible for timers and external functions. Besides
means for timers, which are typically provided as part of the test framework, no external functions are
defined for ISO 15118 conformance testing.

The platform adapter of the test system shall implement the TriPlatformPA and the
TriPlatformTE interfaces as defined in ETSI ES 201 873‐5 V4.6.1, 6.5.3.