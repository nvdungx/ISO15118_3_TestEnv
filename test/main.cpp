#include <boost/regex.hpp>
#include <boost/asio.hpp>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/fmt.h>
#include <array>
#include "basic_signal.hpp"
#include "datatype.hpp"

using namespace TestLib;

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    spdlog::set_level(spdlog::level::level_enum::debug);
    auto io = std::make_shared<boost::asio::io_service>();
    BasicSignalling bc(io, SUTType::SECC);
    bc.start();
    while(1) {
        io->restart();
        io->run();
    }
    std::cin.get();
    return 0;
}