#ifndef HEADER_DVLINNCOUKTIME1
#define HEADER_DVLINNCOUKTIME1

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
 * Base Device for linn.co.uk:Time:1
 */
class DvServiceLinnCoUkTime1 : public DvService
{
public:
    virtual ~DvServiceLinnCoUkTime1() {}
    TBool SetPropertyTrackCount(TUint aValue);
    void GetPropertyTrackCount(TUint& aValue);
    TBool SetPropertyDuration(TUint aValue);
    void GetPropertyDuration(TUint& aValue);
    TBool SetPropertySeconds(TUint aValue);
    void GetPropertySeconds(TUint& aValue);
protected:
    DvServiceLinnCoUkTime1(DvDevice& aDevice);
    void EnableActionTime();
private:
    virtual void Time(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaTrackCount, IInvocationResponseUint& aaDuration, IInvocationResponseUint& aaSeconds);
private:
    DvServiceLinnCoUkTime1();
    void DoTime(IDvInvocation& aInvocation, TUint aVersion);
private:
    PropertyUint* iPropertyTrackCount;
    PropertyUint* iPropertyDuration;
    PropertyUint* iPropertySeconds;
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKTIME1

