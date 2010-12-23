#ifndef HEADER_DVLINNCOUKINFO1CPP
#define HEADER_DVLINNCOUKINFO1CPP

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
 * Provider for the linn.co.uk:Info:1 UPnP service
 * @ingroup Providers
 */
class DvProviderLinnCoUkInfo1Cpp : public DvProvider
{
public:
    virtual ~DvProviderLinnCoUkInfo1Cpp() {}
    /**
     * Set the value of the TrackCount property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyTrackCount(uint32_t aValue);
    /**
     * Get a copy of the value of the TrackCount property
     */
    void GetPropertyTrackCount(uint32_t& aValue);
    /**
     * Set the value of the DetailsCount property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyDetailsCount(uint32_t aValue);
    /**
     * Get a copy of the value of the DetailsCount property
     */
    void GetPropertyDetailsCount(uint32_t& aValue);
    /**
     * Set the value of the MetatextCount property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyMetatextCount(uint32_t aValue);
    /**
     * Get a copy of the value of the MetatextCount property
     */
    void GetPropertyMetatextCount(uint32_t& aValue);
    /**
     * Set the value of the Uri property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyUri(const std::string& aValue);
    /**
     * Get a copy of the value of the Uri property
     */
    void GetPropertyUri(std::string& aValue);
    /**
     * Set the value of the Metadata property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyMetadata(const std::string& aValue);
    /**
     * Get a copy of the value of the Metadata property
     */
    void GetPropertyMetadata(std::string& aValue);
    /**
     * Set the value of the Duration property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyDuration(uint32_t aValue);
    /**
     * Get a copy of the value of the Duration property
     */
    void GetPropertyDuration(uint32_t& aValue);
    /**
     * Set the value of the BitRate property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyBitRate(uint32_t aValue);
    /**
     * Get a copy of the value of the BitRate property
     */
    void GetPropertyBitRate(uint32_t& aValue);
    /**
     * Set the value of the BitDepth property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyBitDepth(uint32_t aValue);
    /**
     * Get a copy of the value of the BitDepth property
     */
    void GetPropertyBitDepth(uint32_t& aValue);
    /**
     * Set the value of the SampleRate property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertySampleRate(uint32_t aValue);
    /**
     * Get a copy of the value of the SampleRate property
     */
    void GetPropertySampleRate(uint32_t& aValue);
    /**
     * Set the value of the Lossless property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyLossless(bool aValue);
    /**
     * Get a copy of the value of the Lossless property
     */
    void GetPropertyLossless(bool& aValue);
    /**
     * Set the value of the CodecName property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyCodecName(const std::string& aValue);
    /**
     * Get a copy of the value of the CodecName property
     */
    void GetPropertyCodecName(std::string& aValue);
    /**
     * Set the value of the Metatext property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyMetatext(const std::string& aValue);
    /**
     * Get a copy of the value of the Metatext property
     */
    void GetPropertyMetatext(std::string& aValue);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderLinnCoUkInfo1Cpp(DvDeviceStd& aDevice);
    /**
     * Signal that the action Counters is supported.
     * The action's availability will be published in the device's service.xml.
     * DoCounters must be overridden if this is called.
     */
    void EnableActionCounters();
    /**
     * Signal that the action Track is supported.
     * The action's availability will be published in the device's service.xml.
     * DoTrack must be overridden if this is called.
     */
    void EnableActionTrack();
    /**
     * Signal that the action Details is supported.
     * The action's availability will be published in the device's service.xml.
     * DoDetails must be overridden if this is called.
     */
    void EnableActionDetails();
    /**
     * Signal that the action Metatext is supported.
     * The action's availability will be published in the device's service.xml.
     * DoMetatext must be overridden if this is called.
     */
    void EnableActionMetatext();
private:
    /**
     * Counters action.
     *
     * Will be called when the device stack receives an invocation of the
     * Counters action for the owning device.
     * Must be implemented iff EnableActionCounters was called.
     */
    virtual void Counters(uint32_t aVersion, uint32_t& aaTrackCount, uint32_t& aaDetailsCount, uint32_t& aaMetatextCount);
    /**
     * Track action.
     *
     * Will be called when the device stack receives an invocation of the
     * Track action for the owning device.
     * Must be implemented iff EnableActionTrack was called.
     */
    virtual void Track(uint32_t aVersion, std::string& aaUri, std::string& aaMetadata);
    /**
     * Details action.
     *
     * Will be called when the device stack receives an invocation of the
     * Details action for the owning device.
     * Must be implemented iff EnableActionDetails was called.
     */
    virtual void Details(uint32_t aVersion, uint32_t& aaDuration, uint32_t& aaBitRate, uint32_t& aaBitDepth, uint32_t& aaSampleRate, bool& aaLossless, std::string& aaCodecName);
    /**
     * Metatext action.
     *
     * Will be called when the device stack receives an invocation of the
     * Metatext action for the owning device.
     * Must be implemented iff EnableActionMetatext was called.
     */
    virtual void Metatext(uint32_t aVersion, std::string& aaMetatext);
private:
    DvProviderLinnCoUkInfo1Cpp();
    void DoCounters(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoTrack(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoDetails(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoMetatext(IDviInvocation& aInvocation, uint32_t aVersion);
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

