#ifndef HEADER_DVLINNCOUKMEDIATIME1
#define HEADER_DVLINNCOUKMEDIATIME1

#include <ZappTypes.h>
#include <Buffer.h>
#include <Core/DvDevice.h>
#include <DvProvider.h>

namespace Zapp {

class PropertyInt;
class PropertyUint;
class PropertyBool;
class PropertyString;
class PropertyBinary;

/**
 * Base Device for linn.co.uk:MediaTime:1
 */
class DvProviderLinnCoUkMediaTime1 : public DvProvider
{
public:
    virtual ~DvProviderLinnCoUkMediaTime1() {}
    TBool SetPropertySeconds(TUint aValue);
    void GetPropertySeconds(TUint& aValue);
protected:
    DvProviderLinnCoUkMediaTime1(DvDevice& aDevice);
    void EnableActionSeconds();
private:
    virtual void Seconds(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaSeconds);
private:
    DvProviderLinnCoUkMediaTime1();
    void DoSeconds(IDvInvocation& aInvocation, TUint aVersion);
private:
    PropertyUint* iPropertySeconds;
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKMEDIATIME1

