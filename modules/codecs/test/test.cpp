#include "slac_type.hpp"
#include "spdlog/spdlog.h"
using namespace TestLib::DataStructure_SLAC;

#define SLOGW(msg) spdlog::warn("{0} {1}: {2}", __FILE__, __LINE__, msg)
#define SLOGI(msg) spdlog::info("{0} {1}: {2}", __FILE__, __LINE__, msg)
#define SLOGE(msg) spdlog::error("{0} {1}: {2}", __FILE__, __LINE__, msg)
#define SLOGD(msg) spdlog::debug("{0} {1}: {2}", __FILE__, __LINE__, msg)

using namespace std::literals;

MME_Payload md_CMN_CMN_CmSlacMatchReq_001(const SLAC_Header &v_slac_header,
  const MACAddress_TYPE &v_pevmac, const MACAddress_TYPE &v_evsemac,
  const RunID_TYPE &v_runid)
{
  MME_Payload tmplPayload;
  tmplPayload.payload.cm_slac_match_req = {
      .slac_header = v_slac_header,
      .mvflength = 0x003E,
      .pevid = "0103FF00000000000000000000000000FF"sv,
      .pevmac = v_pevmac,
      .evseid = "EF0000000000000000CC000000000000FE"sv,
      .evsemac = v_evsemac,
      .runid = v_runid,
      .res0 = "0F000000100000F0"sv};
  return tmplPayload;
}
SLAC_Header m_CMN_CMN_SlacPayloadHeader_001()
{
  return (SLAC_Header){.application_type = 0x00, .security_type = 0x00};
}

MACAddress_TYPE vc_sut_mac({0, 1, 2, 3, 4, 5});
MACAddress_TYPE par_testSystem_mac({1, 2, 1, 2, 1});
RunID_TYPE vc_RunID({1, 1, 1, 1, 1, 1, 1, 1});
int main(int argc, char **argv)
{
  (void)argc;
  (void)argv;
  SLOGI("start test: codecs - slac_type");
  MME_Payload temp = md_CMN_CMN_CmSlacMatchReq_001(m_CMN_CMN_SlacPayloadHeader_001(), vc_sut_mac, par_testSystem_mac, vc_RunID);
  SLOGI("end test: codecs - slac_type");
  return 0;
}