#include "platform_adapter.hpp"
#include "spdlog/spdlog.h"
#include "service.hpp"

using namespace TestLib;

int main(int argc, char **argv)
{
  (void)argc;
  (void)argv;
  spdlog::set_level(spdlog::level::level_enum::debug);
  auto temp = get_crc32({0x12, 0x34, 0x56, 0x78});
  auto temp2 = get_crc32_tb({0x12, 0x34, 0x56, 0x78});
  spdlog::debug("{:X}", temp);
  spdlog::debug("{:X}", temp2);



  return 0;
}