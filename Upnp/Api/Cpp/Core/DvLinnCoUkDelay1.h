#ifndef HEADER_DVLINNCOUKDELAY1
#define HEADER_DVLINNCOUKDELAY1

#include <ZappTypes.h>
#include <Buffer.h>
#include <Core/DvDevice.h>
#include <DvProvider.h>

namespace Zapp {

class IDviInvocation;
class PropertyInt;
class PropertyUint;
class PropertyBool;
class PropertyString;
class PropertyBinary;

/**
 * Base Device for linn.co.uk:Delay:1
 */
class DvProviderLinnCoUkDelay1 : public DvProvider
{
public:
    virtual ~DvProviderLinnCoUkDelay1() {}
    TBool SetPropertyPresetXml(const Brx& aValue);
    void GetPropertyPresetXml(Brhz& aValue);
    TBool SetPropertyPresetIndex(TUint aValue);
    void GetPropertyPresetIndex(TUint& aValue);
protected:
    DvProviderLinnCoUkDelay1(DvDevice& aDevice);
    void EnableActionPresetXml();
    void EnableActionPresetIndex();
    void EnableActionSetPresetIndex();
    void EnableActionSetPresetDelay();
    void EnableActionSetPresetVisible();
    void EnableActionSetPresetName();
    void EnableActionDelayMinimum();
    void EnableActionDelayMaximum();
    void EnableActionPresetCount();
private:
    virtual void PresetXml(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaPresetXml);
    virtual void PresetIndex(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaIndex);
    virtual void SetPresetIndex(IInvocationResponse& aResponse, TUint aVersion, TUint aaIndex);
    virtual void SetPresetDelay(IInvocationResponse& aResponse, TUint aVersion, TUint aaIndex, TUint aaDelay);
    virtual void SetPresetVisible(IInvocationResponse& aResponse, TUint aVersion, TUint aaIndex, TBool aaVisible);
    virtual void SetPresetName(IInvocationResponse& aResponse, TUint aVersion, TUint aaIndex, const Brx& aaName);
    virtual void DelayMinimum(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaDelay);
    virtual void DelayMaximum(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaDelay);
    virtual void PresetCount(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaCount);
private:
    DvProviderLinnCoUkDelay1();
    void DoPresetXml(IDviInvocation& aInvocation, TUint aVersion);
    void DoPresetIndex(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetPresetIndex(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetPresetDelay(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetPresetVisible(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetPresetName(IDviInvocation& aInvocation, TUint aVersion);
    void DoDelayMinimum(IDviInvocation& aInvocation, TUint aVersion);
    void DoDelayMaximum(IDviInvocation& aInvocation, TUint aVersion);
    void DoPresetCount(IDviInvocation& aInvocation, TUint aVersion);
private:
    PropertyString* iPropertyPresetXml;
    PropertyUint* iPropertyPresetIndex;
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKDELAY1

