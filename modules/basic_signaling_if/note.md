# this module shall responsible for change voltage level, pwm duty/frequency, CP state control, detect state change, create abnormal CP condition
# BASIC CHARGING Control operation

> REF: IEC61851-1, ISO15118-3, DIN70121

[V2G5-004] The IEC 61851‐1 SUT adapter shall adapt the HAL 61851‐1 functions to a PWM Signal defined in 7.7.7
NOTE 2  The IEC 61851‐1 SUT adapter can need additional hardware for adapting the HAL 61851‐1 functions
to PWM Signalling according to IEC 61851‐1:2017, Annex A.


sudo apt-get install autoconf autoconf-archive libtool libkmod-dev pkg-config

tar -xzf libgpiod-1.1.1.tar.gz
./autogen.sh --prefix=/usr/local --enable-tools=yes --enable-bindings-cxx=yes
make
make install

https://git.kernel.org/pub/scm/libs/libgpiod/libgpiod.git


sudo apt install gpiod libgpiod-dev libgpiod-doc


* gpiodetect - list all gpiochips present on the system, their names, labels
               and number of GPIO lines

* gpioinfo   - list all lines of specified gpiochips, their names, consumers,
               direction, active state and additional flags

* gpioget    - read values of specified GPIO lines

* gpioset    - set values of specified GPIO lines, potentially keep the lines
               exported and wait until timeout, user input or signal

* gpiofind   - find the gpiochip name and line offset given the line name

* gpiomon    - wait for events on GPIO lines, specify which events to watch,
               how many events to process before exiting or if the events
               should be reported to the console