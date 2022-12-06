#include "spdlog/spdlog.h"
#include "maintestcomponent.hpp"
#include "paralleltestcomponent.hpp"
#include "testsysteminterface.hpp"
#include "port.hpp"

#define SLOGW(msg) spdlog::warn("{0} {1}: {2}", __FILE__, __LINE__, msg)
#define SLOGI(msg) spdlog::info("{0} {1}: {2}", __FILE__, __LINE__, msg)
#define SLOGE(msg) spdlog::error("{0} {1}: {2}", __FILE__, __LINE__, msg)
#define SLOGD(msg) spdlog::debug("{0} {1}: {2}", __FILE__, __LINE__, msg)

int main(int argc, char **argv)
{
  (void)argc;
  (void)argv;
  SLOGI("start test: execution");

  SLOGI("end test: execution");
  return 0;
}