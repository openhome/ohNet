#ifndef HEADER_DVLINNCOUKDELAY1
#define HEADER_DVLINNCOUKDELAY1

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
 * Base Device for linn.co.uk:Delay:1
 */
class DvServiceLinnCoUkDelay1 : public DvService
{
public:
    virtual ~DvServiceLinnCoUkDelay1() {}
    void SetPropertyPresetXml(const Brx& aValue);
    void GetPropertyPresetXml(Brhz& aValue);
    void SetPropertyPresetIndex(TUint aValue);
    void GetPropertyPresetIndex(TUint& aValue);
protected:
    DvServiceLinnCoUkDelay1(DvDevice& aDevice);
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
    DvServiceLinnCoUkDelay1();
    void DoPresetXml(IDvInvocation& aInvocation, TUint aVersion);
    void DoPresetIndex(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetPresetIndex(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetPresetDelay(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetPresetVisible(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetPresetName(IDvInvocation& aInvocation, TUint aVersion);
    void DoDelayMinimum(IDvInvocation& aInvocation, TUint aVersion);
    void DoDelayMaximum(IDvInvocation& aInvocation, TUint aVersion);
    void DoPresetCount(IDvInvocation& aInvocation, TUint aVersion);
private:
    PropertyString* iPropertyPresetXml;
    PropertyUint* iPropertyPresetIndex;
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKDELAY1

