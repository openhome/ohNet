#ifndef HEADER_DVLINNCOUKMEDIATIME1CPP
#define HEADER_DVLINNCOUKMEDIATIME1CPP

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
 * Base Device for linn.co.uk:MediaTime:1
 */
class DvServiceLinnCoUkMediaTime1Cpp : public DvService
{
public:
    virtual ~DvServiceLinnCoUkMediaTime1Cpp() {}
    void SetPropertySeconds(uint32_t aValue);
    void GetPropertySeconds(uint32_t& aValue);
protected:
    DvServiceLinnCoUkMediaTime1Cpp(DvDeviceStd& aDevice);
    void EnableActionSeconds();
private:
    virtual void Seconds(uint32_t aVersion, uint32_t& aaSeconds);
private:
    DvServiceLinnCoUkMediaTime1Cpp();
    void DoSeconds(IDvInvocation& aInvocation, uint32_t aVersion);
private:
    PropertyUint* iPropertySeconds;
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKMEDIATIME1CPP

