#ifndef HEADER_DVLINNCOUKPTEST1CPP
#define HEADER_DVLINNCOUKPTEST1CPP

#include <ZappTypes.h>
#include <Buffer.h>
#include <Std/DvDevice.h>
#include <DvService.h>

#include <string>

namespace Zapp {

class IDvInvocation;
class PropertyInt;
class PropertyUint;
class PropertyBool;
class PropertyString;
class PropertyBinary;

/**
 * Base Device for linn.co.uk:Ptest:1
 */
class DvServiceLinnCoUkPtest1Cpp : public DvService
{
public:
    virtual ~DvServiceLinnCoUkPtest1Cpp() {}
protected:
    DvServiceLinnCoUkPtest1Cpp(DvDeviceStd& aDevice);
    void EnableActionTestComPort();
    void EnableActionLedsOn();
    void EnableActionLedsOff();
private:
    virtual void TestComPort(uint32_t aVersion, uint32_t aaPort, bool& aaResult);
    virtual void LedsOn(uint32_t aVersion);
    virtual void LedsOff(uint32_t aVersion);
private:
    DvServiceLinnCoUkPtest1Cpp();
    void DoTestComPort(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoLedsOn(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoLedsOff(IDvInvocation& aInvocation, uint32_t aVersion);
private:
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKPTEST1CPP

