#ifndef __DATATYPE_H__
#define __DATATYPE_H__
#include <vector>
#include <array>
#include <unordered_map>
#include <string>
#include <iostream>
#include <memory>
#include <string_view>
#include <functional>

namespace TestLib
{

typedef bool boolean;
typedef signed int integer;

typedef struct stSignature
{
  std::string_view name;
  std::function<void()> wrapper;
} Signature;

typedef int PortAddress;
typedef enum class enPortType
{
  message = 0,
  procedure
} PortType;

typedef enum enStdStatus
{
  STD_OK = 1,
  STD_ERROR = 0
} StdStatus;

class TestObj
{
protected:
  std::string _name;
  size_t _id;
public:
  TestObj(void) {};
  ~TestObj(void) {};
  virtual std::string &get_name(void) = 0;
  virtual void set_name(const std::string &Name) = 0;
  virtual size_t get_id(void) = 0;
  virtual void set_id(size_t Id) = 0;
};

/* const string table for logging/debug */
class EnumMap
{
private:
  std::vector<const char *> table;
  const char *ERROR_STRING = "OUT_OF_RANGE";

public:
  EnumMap(std::vector<const char *> &&input_table)
      : table(std::move(input_table))
  {
  }
  ~EnumMap() {}
  const char *operator[](ssize_t idx) const noexcept
  {
    if ((idx < 0) || ((size_t)idx > table.size()))
    {
      return ERROR_STRING;
    }
    else
    {
      return table[idx];
    }
  }
};

/* const string table for logging/debug */
class EnumUnorderedMap
{
private:
  // unordered_map to store the const string for enum map
  std::unordered_map<int, const char *> table;
  // string to print when input enum value is not existed
  const char *ERROR_STRING = "OUT_OF_RANGE";

public:
  // && is rvalue reference, specify rvalue because we initialize
  // the string vector table with rvalue
  EnumUnorderedMap(std::unordered_map<int, const char *> &&input_table)
      : table(std::move(input_table)) {}
  ~EnumUnorderedMap() {}

  // override the operator []
  const char *operator[](ssize_t idx) const noexcept
  {
    // index checking
    if (0 == table.count(idx))
    {
      // return ERROR string incase of input value is not exist in enum type
      return ERROR_STRING;
    }
    else
    {
      // return corresponding string
      return table.at(idx);
    }
  }
};

/* namespace for test verification data type */
namespace DataStructure_TestVerification
{
  const EnumMap VERDICT_RESULT({"NONE", "PASS", "INCONCLUSION", "FAIL", "ERROR"});
  // Table 29: Overwriting rules for the verdict
  // Current value     New verdict assignment value
  //  of Verdict
  //   ----              pass    inconc  fail  none
  //   None              pass    inconc  fail  none
  //   Pass              pass    inconc  fail  pass
  //   Inconc            inconc  inconc  fail  inconc
  //   Fail              fail    fail    fail  fail
  typedef enum enVerdictValue
  {
    none = 0,
    pass = 1,
    inconc = 2,
    fail = 3,
    error = 4
  } VerdictValue;
  class VerdictType
  {
  private:
    VerdictValue value;
    std::vector<std::string> msg_list;

  public:
    VerdictType()
    {
      value = none;
    }
    VerdictType(VerdictValue val)
    {
      value = val;
    }
    VerdictType(VerdictValue val, const std::string &_msg)
    {
      value = val;
      msg_list.push_back(_msg);
    }
    VerdictType(const VerdictType &obj)
    {
      this->value = obj.value;
      this->msg_list = obj.msg_list;
    }
    VerdictType(const VerdictType &&obj)
    {
      this->value = std::move(obj.value);
      this->msg_list = std::move(obj.msg_list);
    }
    ~VerdictType(){};
    std::string to_string(void)
    {
      std::string str_result = std::string("VERDICT: ") + VERDICT_RESULT[this->value] + "\n";
      for (auto &&msg : this->msg_list)
      {
        str_result.push_back('\n');
        str_result.append(msg);
      }
      return str_result;
    }
    VerdictType &operator=(const VerdictType &&rho)
    {
      if (rho.value > this->value)
      {
        this->value = rho.value;
      }
      this->msg_list.insert(this->msg_list.end(), rho.msg_list.begin(), rho.msg_list.end());
      return *this;
    }
    VerdictType &operator=(const VerdictType &rho)
    {
      if (this != &rho)
      {
        if (rho.value > this->value)
        {
          this->value = rho.value;
        }
        this->msg_list.insert(this->msg_list.end(), rho.msg_list.begin(), rho.msg_list.end());
      }
      return *this;
    }
    VerdictType &operator=(VerdictValue rhv)
    {
      if (rhv > this->value)
      {
        this->value = rhv;
      }
      return *this;
    }
    bool operator==(const VerdictType &rho)
    {
      return (this->value == rho.value);
    }
    bool operator==(const VerdictValue rhv)
    {
      return (this->value == rhv);
    }
  };
}

typedef enum enSUTType
{
  EVCC = 0,
  SECC
} SUTType;

namespace DataStructure_HAL_61851
{
  typedef enum enIEC_61851_States
  {
    A = 0,
    B,
    C,
    D,
    E,
    F,
    NA,
    none_
  } IEC_61851_States;
  typedef enum enIEC_61851_ErrStates
  {
    LOST_CP = 0,
    LOST_PE,
    LOST_DIODE,
    SHORT_CP_PE
  } IEC_61851_ErrStates;
  typedef enum enHAL_61851_PwmMode_Type
  {
    FIX_5_PERCENT = 0,
    NOMINAL
  } HAL_61851_PwmMode_Type;

  /* callback on change events */
  typedef enum enCallbackType
  {
    STATE = 0,
    PROXIMITY,
    DUTY,
    FREQ,
    ISR
  } CallbackType;
  /* callback functor for basic signaling event from IEC61851 SUT Inteface */
  class BasicSignalCallback
  {
  public:
    BasicSignalCallback(CallbackType type) : _type(type) {}
    ~BasicSignalCallback() {}
    CallbackType get_type() { return _type; }
    // call operator for state change event
    virtual void operator()(IEC_61851_States new_state) { (void)new_state; }
    // call operator for duty/freq/proximity value change, void cast to avoid warning
    virtual void operator()(float new_val) { (void)new_val; }
    // call operator for button isr
    virtual void operator()(void) {}

  private:
    CallbackType _type;
  };
}

/* protocol implementation conformance statements */
namespace DataStructure_PICS_15118
{
  typedef enum class enChargingMode
  {
    aC,
    dC
  } ChargingMode;
  typedef enum class enIdentificationMode
  {
    pnC,
    eIM
  } IdentificationMode;
  typedef enum class enPlugType
  {
    type1,
    type2
  } PlugType;
  typedef enum class enCableCapabilityACType
  {
    capability13A,
    capability20A,
    capability32A,
    capability63A,
    capability70A
  } CableCapabilityACType;
  typedef enum class enEIMDone
  {
    beforePlugin,
    afterPlugin,
    duringSlac,
    v2gAuthorization
  } EIMDone;
  typedef enum class enZeroPow
  {
    sleepWithoutCharge,
    sleepAfterCharge,
    none_
  } ZeroPow;
}
/* protocol implementation conformance statements */
namespace DataStructure_PICS_15118_2
{
  typedef enum class enPkiType
  {
    PKI_1,
    PKI_2,
    PKI_3,
    PKI_4,
    PKI_5,
    PKI_6,
    PKI_7
  } PkiType;
}

/* protocol implementation extra information for testing */
namespace DataStructure_PIXIT_15118
{
  typedef enum class enPause
  {
    pause,
    unknown,
    none_
  } Pause;
}
/* protocol implementation extra information for testing */
namespace DataStructure_PIXIT_15118_2
{
  typedef enum class enCertificateHandlingEVCC
  {
    none_,
    certInstall,
    certUpdate,
    unknown
  } CertificateHandlingEVCC;
  typedef enum class enCertificateHandlingSECC
  {
    none_,
    certInstall,
    certUpdate
  } CertificateHandlingSECC;
  typedef enum class enVASEVCC
  {
    none_,
    serviceDetail,
    unknown
  } VASEVCC;
  typedef enum class enVASSECC
  {
    none_,
    serviceDetail
  } VASSECC;
  typedef enum class enWeldingDetection
  {
    none_,
    weldingDetection,
    unknown
  } WeldingDetection;
  typedef enum class enTLS
  {
    none_,
    tls,
    unknown
  } TLS;
  typedef enum class enPkiType
  {
    PKI_1,
    PKI_2,
    PKI_3,
    PKI_4,
    PKI_5,
    PKI_6,
    PKI_7,
    PKI_Ext,
    PKI_1_Testival,
    PKI_2_Testival
  } PkiType;
  typedef enum class enSalesTariff
  {
    salesTariff,
    unknown
  } SalesTariff;
  typedef enum class enInternetAccess
  {
    internetAccess,
    unknown
  } InternetAccess;
  typedef enum class enOngoing
  {
    ongoing,
    unknown
  } Ongoing;
  typedef enum class enRenegotiation
  {
    renegotiation,
    unknown
  } Renegotiation;
  typedef enum class enDepartureTime
  {
    departureTime,
    unknown,
    none_
  } DepartureTime;
  typedef enum class enMeterInfo
  {
    meterInfo,
    unknown
  } MeterInfo;
  typedef enum class enMeterReading
  {
    meterReading,
    unknown
  } MeterReading;
  typedef enum class enMaxNumberOfPhasesInUse
  {
    maxNumberOfPhasesInUse,
    unknown
  } MaxNumberOfPhasesInUse;
  typedef enum class enChargingProfileOpt
  {
    optimization,
    unknown,
    none_
  } ChargingProfileOpt;
  typedef enum class enNewSAScheduleTupleID
  {
    newSAScheduleTupleID,
    unknown
  } NewSAScheduleTupleID;
  typedef enum class enSAScheduleTupleIDMR
  {
    sAScheduleTupleID,
    unknown
  } SAScheduleTupleIDMR;
  typedef enum class enPaymentOption
  {
    externalPayment,
    contract
  } PaymentOption;
}
/* protocol implementation extra information for testing */
namespace DataStructure_PIXIT_15118_3
{
  typedef enum class enCmValidateEVCC
  {
    none_,
    cmValidate,
    unknown
  } CmValidateEVCC;
  typedef enum class enCmValidateSECC
  {
    none_,
    cmValidate
  } CmValidateSECC;
  typedef enum class enDutyCycle
  {
    dc5,
    dc100
  } DutyCycle;
  typedef enum class enValidationFallbackHandling
  {
    continue_,
    skip,
    terminate,
    unknown
  } ValidationFallbackHandling;
  typedef enum class enConcurrentValidationHandling
  {
    retry,
    iterate,
    unknown
  } ConcurrentValidationHandling;
  typedef enum class enCLHandling
  {
    optionA,
    optionB
  } CLHandling;
}

typedef enum enDLinkStatusType
{
  NO_LINK = 0,
  LINK_ESTABLISHED
} DLinkStatusType;

} // namespace TestLib

#endif // __DATATYPE_H__