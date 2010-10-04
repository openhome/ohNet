#ifndef HEADER_DVLINNCOUKINFO1CPP
#define HEADER_DVLINNCOUKINFO1CPP

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
 * Base Device for linn.co.uk:Info:1
 */
class DvServiceLinnCoUkInfo1Cpp : public DvService
{
public:
    virtual ~DvServiceLinnCoUkInfo1Cpp() {}
    void SetPropertyTrackCount(uint32_t aValue);
    void GetPropertyTrackCount(uint32_t& aValue);
    void SetPropertyDetailsCount(uint32_t aValue);
    void GetPropertyDetailsCount(uint32_t& aValue);
    void SetPropertyMetatextCount(uint32_t aValue);
    void GetPropertyMetatextCount(uint32_t& aValue);
    void SetPropertyUri(const std::string& aValue);
    void GetPropertyUri(std::string& aValue);
    void SetPropertyMetadata(const std::string& aValue);
    void GetPropertyMetadata(std::string& aValue);
    void SetPropertyDuration(uint32_t aValue);
    void GetPropertyDuration(uint32_t& aValue);
    void SetPropertyBitRate(uint32_t aValue);
    void GetPropertyBitRate(uint32_t& aValue);
    void SetPropertyBitDepth(uint32_t aValue);
    void GetPropertyBitDepth(uint32_t& aValue);
    void SetPropertySampleRate(uint32_t aValue);
    void GetPropertySampleRate(uint32_t& aValue);
    void SetPropertyLossless(bool aValue);
    void GetPropertyLossless(bool& aValue);
    void SetPropertyCodecName(const std::string& aValue);
    void GetPropertyCodecName(std::string& aValue);
    void SetPropertyMetatext(const std::string& aValue);
    void GetPropertyMetatext(std::string& aValue);
protected:
    DvServiceLinnCoUkInfo1Cpp(DvDeviceStd& aDevice);
    void EnableActionCounters();
    void EnableActionTrack();
    void EnableActionDetails();
    void EnableActionMetatext();
private:
    virtual void Counters(uint32_t aVersion, uint32_t& aaTrackCount, uint32_t& aaDetailsCount, uint32_t& aaMetatextCount);
    virtual void Track(uint32_t aVersion, std::string& aaUri, std::string& aaMetadata);
    virtual void Details(uint32_t aVersion, uint32_t& aaDuration, uint32_t& aaBitRate, uint32_t& aaBitDepth, uint32_t& aaSampleRate, bool& aaLossless, std::string& aaCodecName);
    virtual void Metatext(uint32_t aVersion, std::string& aaMetatext);
private:
    DvServiceLinnCoUkInfo1Cpp();
    void DoCounters(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoTrack(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoDetails(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoMetatext(IDvInvocation& aInvocation, uint32_t aVersion);
private:
    PropertyUint* iPropertyTrackCount;
    PropertyUint* iPropertyDetailsCount;
    PropertyUint* iPropertyMetatextCount;
    PropertyString* iPropertyUri;
    PropertyString* iPropertyMetadata;
    PropertyUint* iPropertyDuration;
    PropertyUint* iPropertyBitRate;
    PropertyUint* iPropertyBitDepth;
    PropertyUint* iPropertySampleRate;
    PropertyBool* iPropertyLossless;
    PropertyString* iPropertyCodecName;
    PropertyString* iPropertyMetatext;
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKINFO1CPP

