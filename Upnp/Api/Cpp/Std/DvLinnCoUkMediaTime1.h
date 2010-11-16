#ifndef HEADER_DVLINNCOUKMEDIATIME1CPP
#define HEADER_DVLINNCOUKMEDIATIME1CPP

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
 * Base Device for linn.co.uk:MediaTime:1
 */
class DvProviderLinnCoUkMediaTime1Cpp : public DvProvider
{
public:
    virtual ~DvProviderLinnCoUkMediaTime1Cpp() {}
    bool SetPropertySeconds(uint32_t aValue);
    void GetPropertySeconds(uint32_t& aValue);
protected:
    DvProviderLinnCoUkMediaTime1Cpp(DvDeviceStd& aDevice);
    void EnableActionSeconds();
private:
    virtual void Seconds(uint32_t aVersion, uint32_t& aaSeconds);
private:
    DvProviderLinnCoUkMediaTime1Cpp();
    void DoSeconds(IDviInvocation& aInvocation, uint32_t aVersion);
private:
    PropertyUint* iPropertySeconds;
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKMEDIATIME1CPP

