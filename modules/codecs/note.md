# this module contain data structure for slac msg (decode, encode operations)

TBD: for the message structure -> need to optimize with the move sematic/constructor for template usage

ispresent: check if specific field of a data structure is available
ischosen: specific to union, to check whether data objects is in used by union
isvalue: check whether the object is initialized.
isbound: checks whether a referenced data object is at least partially initialized

A codec is responsible for the external encoding and decoding of TTCN‐3 values into bit strings suitable
to be sent to the SUT. The Test Execution (TE) determines which codec shall be used and passes the
TTCN‐3 data to the appropriate encoder to obtain the encoded data. Received data is decoded in this
entity by using the appropriate decoder, which translates the received data into TTCN‐3 values cf.
ETSI ES 201 873‐6 V4.6.1 that can be matched against expected values or templates.
[V2G5-006] All codecs in this document shall implement the TCI‐CD interface as defined in
ETSI ES 201 873‐6 V4.6.1, 7.3.2.
NOTE 1 For ISO 15118‐3 conformance testing the SLAC codec (see Figure 1) is used to encode or decode
messages consumable by the tester into bit strings consumable by the SUT.

[V2G5-007] The SLAC codec shall encode TTCN‐3 values as defined in G.3 into corresponding MME
frames as defined in ISO 15118‐3:2015, A.9 and HomePlug GreenPHY Spec. 1.1.1, July
4, 2013.
[V2G5-008] The SLAC codec shall decode MME frames as defined in G.3 into TTCN‐3 values as
defined in ISO 15118‐3:2015, A.9 and HomePlug GreenPHY Spec. 1.1.1, July 4, 2013.