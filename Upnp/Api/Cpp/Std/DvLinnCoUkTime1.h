#ifndef HEADER_DVLINNCOUKTIME1CPP
#define HEADER_DVLINNCOUKTIME1CPP

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
 * Base Device for linn.co.uk:Time:1
 */
class DvProviderLinnCoUkTime1Cpp : public DvProvider
{
public:
    virtual ~DvProviderLinnCoUkTime1Cpp() {}
    bool SetPropertyTrackCount(uint32_t aValue);
    void GetPropertyTrackCount(uint32_t& aValue);
    bool SetPropertyDuration(uint32_t aValue);
    void GetPropertyDuration(uint32_t& aValue);
    bool SetPropertySeconds(uint32_t aValue);
    void GetPropertySeconds(uint32_t& aValue);
protected:
    DvProviderLinnCoUkTime1Cpp(DvDeviceStd& aDevice);
    void EnableActionTime();
private:
    virtual void Time(uint32_t aVersion, uint32_t& aaTrackCount, uint32_t& aaDuration, uint32_t& aaSeconds);
private:
    DvProviderLinnCoUkTime1Cpp();
    void DoTime(IDviInvocation& aInvocation, uint32_t aVersion);
private:
    PropertyUint* iPropertyTrackCount;
    PropertyUint* iPropertyDuration;
    PropertyUint* iPropertySeconds;
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKTIME1CPP

