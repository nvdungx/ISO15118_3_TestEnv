#ifndef __PLATFORM_ADAPTER_H__
#define __PLATFORM_ADAPTER_H__

#include <cstdint>
#include <vector>

namespace TestLib
{
  /* provide general timer operation */
  class PlatformAdapter
  {
  private:
    /* data */
  public:
    PlatformAdapter(/* args */) {}
    ~PlatformAdapter() {}
  };
  uint32_t get_crc32(const std::vector<uint8_t> &dataArr);
  uint32_t get_crc32_tb(const std::vector<uint8_t> &dataArr);

} // namespace TestLib
#endif // __PLATFORM_ADAPTER_H__