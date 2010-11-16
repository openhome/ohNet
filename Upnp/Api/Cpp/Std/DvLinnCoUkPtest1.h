#ifndef HEADER_DVLINNCOUKPTEST1CPP
#define HEADER_DVLINNCOUKPTEST1CPP

#include <ZappTypes.h>
#include <Buffer.h>
#include <Std/DvDevice.h>
#include <DvProvider.h>

#include <string>

namespace Zapp {

class IDviInvocation;
class PropertyInt;
class PropertyUint;
class PropertyBool;
class PropertyString;
class PropertyBinary;

/**
 * Base Device for linn.co.uk:Ptest:1
 */
class DvProviderLinnCoUkPtest1Cpp : public DvProvider
{
public:
    virtual ~DvProviderLinnCoUkPtest1Cpp() {}
protected:
    DvProviderLinnCoUkPtest1Cpp(DvDeviceStd& aDevice);
    void EnableActionTestComPort();
    void EnableActionLedsOn();
    void EnableActionLedsOff();
private:
    virtual void TestComPort(uint32_t aVersion, uint32_t aaPort, bool& aaResult);
    virtual void LedsOn(uint32_t aVersion);
    virtual void LedsOff(uint32_t aVersion);
private:
    DvProviderLinnCoUkPtest1Cpp();
    void DoTestComPort(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoLedsOn(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoLedsOff(IDviInvocation& aInvocation, uint32_t aVersion);
private:
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKPTEST1CPP

