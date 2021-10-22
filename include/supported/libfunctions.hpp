#ifndef __LIBFUNCTIONS_H__
#define __LIBFUNCTIONS_H__

#include <vector>
#include "datatype.hpp"
#include "slac_type.hpp"

namespace TestLib
{
  namespace LibFunctions_15118_3
  {
    namespace generalFunctions
    {
      void fx_logToFile(std::vector<float> &v_listOfFloat, std::vector<boolean> &v_listOfBoolean);
      hexstring(10) fx_generateNID(hexstring(10) &nmk);
      void fx_captureTraffic(int v_interfaceIdx);
      void fx_stopCapturing(void);
      std::vector<uint8_t> f_randomHexStringGen(int hexLength);
      void sleep(float time);
    } // namespace generalFunctions
  } // namespace LibFunctions_15118_3
} // namespace TestLib

#endif // __LIBFUNCTIONS_H__