#ifndef HEADER_DVLINNCOUKMEDIATIME1
#define HEADER_DVLINNCOUKMEDIATIME1

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
 * Base Device for linn.co.uk:MediaTime:1
 */
class DvServiceLinnCoUkMediaTime1 : public DvService
{
public:
    virtual ~DvServiceLinnCoUkMediaTime1() {}
    void SetPropertySeconds(TUint aValue);
    void GetPropertySeconds(TUint& aValue);
protected:
    DvServiceLinnCoUkMediaTime1(DvDevice& aDevice);
    void EnableActionSeconds();
private:
    virtual void Seconds(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaSeconds);
private:
    DvServiceLinnCoUkMediaTime1();
    void DoSeconds(IDvInvocation& aInvocation, TUint aVersion);
private:
    PropertyUint* iPropertySeconds;
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKMEDIATIME1

