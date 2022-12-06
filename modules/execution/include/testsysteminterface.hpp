#ifndef __TESTSYSTEMINTERFACE_H__
#define __TESTSYSTEMINTERFACE_H__

/****************************************************************************/
/********************** Test System Interface Component *********************/
/****************************************************************************/
/* singleton - statically define for SUT */
namespace TestLib
{
class SystemSECC 
{
private:

public:
  SystemSECC() {}
  ~SystemSECC() {}
};

class SystemEVCC
{
private:

public:
  SystemEVCC() {}
  ~SystemEVCC() {}
};
}
#endif // __TESTSYSTEMINTERFACE_H__