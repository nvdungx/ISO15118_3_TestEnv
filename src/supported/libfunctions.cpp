#include "supported/libfunctions.hpp"

namespace TestLib {
namespace LibFunctions_15118_3
{
namespace generalFunctions
{
void fx_logToFile(std::vector<float> &v_listOfFloat, std::vector<boolean> &v_listOfBoolean)
{
}
hexstring(10) fx_generateNID(hexstring(10) &nmk)
{
}
void fx_captureTraffic(int v_interfaceIdx)
{
}
void fx_stopCapturing(void)
{
}
std::vector<uint8_t> f_randomHexStringGen(int hexLength)
{
  /* std::vector<uint8_t> randomHex{};
  for (int i = 0; i < hexLength / 2; i++)
  {
    float rndFloat = -1.0;
    while ((rndFloat < 0.0) || (rndFloat > 255.0))
    {
      rndFloat = rnd(rnd());
      rndFloat = rndFloat * 10E2;
    }
    hexstring randomHexByte = int2hex(float2int(rndFloat), 2);
    randomHex = randomHex & randomHexByte;
  }
  return randomHex; */
}
void sleep(float time)
{
  // timer t := time;
  // t.start;
  // t.timeout;
}
}
}
}