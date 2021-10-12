#include "slac_type.hpp"

#define SLOGW(msg) spdlog::warn("{0} {1}: {2}", __FILE__, __LINE__, msg)
#define SLOGI(msg) spdlog::info("{0} {1}: {2}", __FILE__, __LINE__, msg)
#define SLOGE(msg) spdlog::error("{0} {1}: {2}", __FILE__, __LINE__, msg)
#define SLOGD(msg) spdlog::debug("{0} {1}: {2}", __FILE__, __LINE__, msg)

namespace TestLib {
// define global constant value here
hexstring(6) par_slac_node2_mac;
hexstring(6) par_slac_node3_mac;
hexstring(6) par_slac_node4_mac;
hexstring(6) par_slac_node5_mac;
// define encoding/decoding api here
}