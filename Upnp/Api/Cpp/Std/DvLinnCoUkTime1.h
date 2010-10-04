#ifndef HEADER_DVLINNCOUKTIME1CPP
#define HEADER_DVLINNCOUKTIME1CPP

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
 * Base Device for linn.co.uk:Time:1
 */
class DvServiceLinnCoUkTime1Cpp : public DvService
{
public:
    virtual ~DvServiceLinnCoUkTime1Cpp() {}
    void SetPropertyTrackCount(uint32_t aValue);
    void GetPropertyTrackCount(uint32_t& aValue);
    void SetPropertyDuration(uint32_t aValue);
    void GetPropertyDuration(uint32_t& aValue);
    void SetPropertySeconds(uint32_t aValue);
    void GetPropertySeconds(uint32_t& aValue);
protected:
    DvServiceLinnCoUkTime1Cpp(DvDeviceStd& aDevice);
    void EnableActionTime();
private:
    virtual void Time(uint32_t aVersion, uint32_t& aaTrackCount, uint32_t& aaDuration, uint32_t& aaSeconds);
private:
    DvServiceLinnCoUkTime1Cpp();
    void DoTime(IDvInvocation& aInvocation, uint32_t aVersion);
private:
    PropertyUint* iPropertyTrackCount;
    PropertyUint* iPropertyDuration;
    PropertyUint* iPropertySeconds;
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKTIME1CPP

