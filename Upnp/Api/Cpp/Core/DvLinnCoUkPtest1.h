#ifndef HEADER_DVLINNCOUKPTEST1
#define HEADER_DVLINNCOUKPTEST1

#include <ZappTypes.h>
#include <Buffer.h>
#include <Core/DvDevice.h>
#include <DvService.h>

namespace Zapp {

class PropertyInt;
class PropertyUint;
class PropertyBool;
class PropertyString;
class PropertyBinary;

/**
 * Base Device for linn.co.uk:Ptest:1
 */
class DvServiceLinnCoUkPtest1 : public DvService
{
public:
    virtual ~DvServiceLinnCoUkPtest1() {}
protected:
    DvServiceLinnCoUkPtest1(DvDevice& aDevice);
    void EnableActionTestComPort();
    void EnableActionLedsOn();
    void EnableActionLedsOff();
private:
    virtual void TestComPort(IInvocationResponse& aResponse, TUint aVersion, TUint aaPort, IInvocationResponseBool& aaResult);
    virtual void LedsOn(IInvocationResponse& aResponse, TUint aVersion);
    virtual void LedsOff(IInvocationResponse& aResponse, TUint aVersion);
private:
    DvServiceLinnCoUkPtest1();
    void DoTestComPort(IDvInvocation& aInvocation, TUint aVersion);
    void DoLedsOn(IDvInvocation& aInvocation, TUint aVersion);
    void DoLedsOff(IDvInvocation& aInvocation, TUint aVersion);
private:
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKPTEST1

