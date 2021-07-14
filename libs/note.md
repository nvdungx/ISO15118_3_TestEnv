The following libraries must be available in order to link programs that use Asio:

Boost.Coroutine (optional) if you use spawn() to launch coroutines.
Boost.Regex (optional) if you use any of the read_until() or async_read_until() overloads that take a boost::regex parameter.
OpenSSL (optional) if you use Asio's SSL support.
Furthermore, some of the examples also require Boost.Date_Time or Boost.Serialization libraries.

git clone https://kernel.googlesource.com/pub/scm/libs/libgpiod/libgpiod.git
sudo apt-get install libtool autoconf
./autogen.sh --enable-tools=yes --prefix=/usr/local