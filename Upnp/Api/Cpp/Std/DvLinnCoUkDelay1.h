#ifndef HEADER_DVLINNCOUKDELAY1CPP
#define HEADER_DVLINNCOUKDELAY1CPP

#include <ZappTypes.h>
#include <Buffer.h>
#include <Std/DvDevice.h>
#include <DvProvider.h>

#include <string>

namespace Zapp {

class IDvInvocation;
class PropertyInt;
class PropertyUint;
class PropertyBool;
class PropertyString;
class PropertyBinary;

/**
 * Base Device for linn.co.uk:Delay:1
 */
class DvProviderLinnCoUkDelay1Cpp : public DvProvider
{
public:
    virtual ~DvProviderLinnCoUkDelay1Cpp() {}
    bool SetPropertyPresetXml(const std::string& aValue);
    void GetPropertyPresetXml(std::string& aValue);
    bool SetPropertyPresetIndex(uint32_t aValue);
    void GetPropertyPresetIndex(uint32_t& aValue);
protected:
    DvProviderLinnCoUkDelay1Cpp(DvDeviceStd& aDevice);
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
    virtual void PresetXml(uint32_t aVersion, std::string& aaPresetXml);
    virtual void PresetIndex(uint32_t aVersion, uint32_t& aaIndex);
    virtual void SetPresetIndex(uint32_t aVersion, uint32_t aaIndex);
    virtual void SetPresetDelay(uint32_t aVersion, uint32_t aaIndex, uint32_t aaDelay);
    virtual void SetPresetVisible(uint32_t aVersion, uint32_t aaIndex, bool aaVisible);
    virtual void SetPresetName(uint32_t aVersion, uint32_t aaIndex, const std::string& aaName);
    virtual void DelayMinimum(uint32_t aVersion, uint32_t& aaDelay);
    virtual void DelayMaximum(uint32_t aVersion, uint32_t& aaDelay);
    virtual void PresetCount(uint32_t aVersion, uint32_t& aaCount);
private:
    DvProviderLinnCoUkDelay1Cpp();
    void DoPresetXml(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoPresetIndex(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetPresetIndex(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetPresetDelay(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetPresetVisible(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetPresetName(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoDelayMinimum(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoDelayMaximum(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoPresetCount(IDvInvocation& aInvocation, uint32_t aVersion);
private:
    PropertyString* iPropertyPresetXml;
    PropertyUint* iPropertyPresetIndex;
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKDELAY1CPP

