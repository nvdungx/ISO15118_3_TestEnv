TTCN-3 Control Interface (TCI)
Test Management (TM)
Overall management of the test system, test system user interface, execution of tests, provider of parameters
Note: Provided by most commercial TTCN-3 tools
Test Logging (TL)
Handling of all log events of the test system
Note: Provided by most commercial TTCN-3 tools
Coding and Decoding (CD)
Encoding and decoding data associated with message based or
procedure based communication within the TE
Component Handling (CH)
Distributing and communication between parallel test components
Note: Provided by most commercial TTCN-3 tools
TTCN-3 Runtime Interface (TRI)
System Adaptor (SA)
Adapts message based or
procedure based communication to and from the SUT, and SUT action operations
Platform Adaptor (PA)
Implements TTCN-3 external functions and provides a TTCN-3 test system with a single notion of time
Note: Timing provided by most commercial TTCN-3 tools

https://www.boost.org/doc/libs/1_76_0/more/getting_started/unix-variants.html
wget https://boostorg.jfrog.io/artifactory/main/release/1.76.0/source/boost_1_76_0.tar.gz
tar -xf boost_1_76_0.tar.gz
cd boost_1_76_0/
./bootstrap.sh --prefix=/usr/local/ --with-libraries=all
./b2 install

wget https://github.com/protocolbuffers/protobuf/releases/download/v3.17.3/protobuf-cpp-3.17.3.tar.gz

sudo apt install gpiod libgpiod-dev libgpiod-doc

dpkg-query -L libgpiod-dev

## libs
asio > static lib
fmt > static lib
## modules
reused interface, codecs(msg serializer/deserializer)
iec61851 basic signalling interface (basic signalling I/O: handle control, checking status on Control Pilot line)
platform interface (external function(control external load during testing), timer)
iso15118-3 plc_interface (green plug home physical layer - logical link communication)
codecs (HPGY msgs)
## sources


CMAKE: Build system generator

Directories (CMakeLists.txt):
file may contain the entire build specification or use the add_subdirectory() command to add subdirectories to the build.
source directory whose CMakeLists.txt file is processed CMake generates a corresponding directory in the build tree
Scripts (<script>.cmake), and:
using the cmake(1) command-line tool with the -P option
Modules (<module>.cmake):
use the include() command to load a <module>.cmake source file in the scope of the including context

all values in CMake are stored as strings.
A list of elements is represented as a string by concatenating the elements separated by ; or <space>
set(x a "b;c") # sets "x" to "a;b;c", not "a;b\;c"
set(srcs a.c b.c c.c) # sets "srcs" to "a.c;b.c;c.c"

Variables:values are always of string type, Variables have dynamic scope. Each variable "set" or "unset" creates a binding in the current scope
Function Scope, Directory Scope
variable "set" or "unset" not inside a function call binds to the current directory scope.

Environment variable: $ENV{<variable>}.

variable reference has the form ${<variable>}, is replaced by the value of the variable, or by the empty string if the variable is not set.


system:
SUT Interface: IEC61851(ControlPilot), ISO15118(HPGP Plc - logical link)
TestSystem Timer, external system control function
Encode/Decode, DataType
io_service: for asynchronous operation during testing runtime (timer, send/receive event, ControlPilot io event, tester control input)
