#ifndef HEADER_DVAVOPENHOMEORGINFO1CPP
#define HEADER_DVAVOPENHOMEORGINFO1CPP

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Cpp/DvDevice.h>
#include <OpenHome/Net/Core/DvProvider.h>
#include <OpenHome/Net/Cpp/DvInvocation.h>

#include <string>

namespace OpenHome {
namespace Net {

class IDviInvocation;
class PropertyInt;
class PropertyUint;
class PropertyBool;
class PropertyString;
class PropertyBinary;

/**
 * Provider for the av.openhome.org:Info:1 UPnP service
 * @ingroup Providers
 */
class DvProviderAvOpenhomeOrgInfo1Cpp : public DvProvider
{
public:
    virtual ~DvProviderAvOpenhomeOrgInfo1Cpp() {}
    /**
     * Set the value of the TrackCount property
     *
     * Can only be called if EnablePropertyTrackCount has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyTrackCount(uint32_t aValue);
    /**
     * Get a copy of the value of the TrackCount property
     *
     * Can only be called if EnablePropertyTrackCount has previously been called.
     */
    void GetPropertyTrackCount(uint32_t& aValue);
    /**
     * Set the value of the DetailsCount property
     *
     * Can only be called if EnablePropertyDetailsCount has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyDetailsCount(uint32_t aValue);
    /**
     * Get a copy of the value of the DetailsCount property
     *
     * Can only be called if EnablePropertyDetailsCount has previously been called.
     */
    void GetPropertyDetailsCount(uint32_t& aValue);
    /**
     * Set the value of the MetatextCount property
     *
     * Can only be called if EnablePropertyMetatextCount has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyMetatextCount(uint32_t aValue);
    /**
     * Get a copy of the value of the MetatextCount property
     *
     * Can only be called if EnablePropertyMetatextCount has previously been called.
     */
    void GetPropertyMetatextCount(uint32_t& aValue);
    /**
     * Set the value of the Uri property
     *
     * Can only be called if EnablePropertyUri has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyUri(const std::string& aValue);
    /**
     * Get a copy of the value of the Uri property
     *
     * Can only be called if EnablePropertyUri has previously been called.
     */
    void GetPropertyUri(std::string& aValue);
    /**
     * Set the value of the Metadata property
     *
     * Can only be called if EnablePropertyMetadata has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyMetadata(const std::string& aValue);
    /**
     * Get a copy of the value of the Metadata property
     *
     * Can only be called if EnablePropertyMetadata has previously been called.
     */
    void GetPropertyMetadata(std::string& aValue);
    /**
     * Set the value of the Duration property
     *
     * Can only be called if EnablePropertyDuration has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyDuration(uint32_t aValue);
    /**
     * Get a copy of the value of the Duration property
     *
     * Can only be called if EnablePropertyDuration has previously been called.
     */
    void GetPropertyDuration(uint32_t& aValue);
    /**
     * Set the value of the BitRate property
     *
     * Can only be called if EnablePropertyBitRate has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyBitRate(uint32_t aValue);
    /**
     * Get a copy of the value of the BitRate property
     *
     * Can only be called if EnablePropertyBitRate has previously been called.
     */
    void GetPropertyBitRate(uint32_t& aValue);
    /**
     * Set the value of the BitDepth property
     *
     * Can only be called if EnablePropertyBitDepth has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyBitDepth(uint32_t aValue);
    /**
     * Get a copy of the value of the BitDepth property
     *
     * Can only be called if EnablePropertyBitDepth has previously been called.
     */
    void GetPropertyBitDepth(uint32_t& aValue);
    /**
     * Set the value of the SampleRate property
     *
     * Can only be called if EnablePropertySampleRate has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertySampleRate(uint32_t aValue);
    /**
     * Get a copy of the value of the SampleRate property
     *
     * Can only be called if EnablePropertySampleRate has previously been called.
     */
    void GetPropertySampleRate(uint32_t& aValue);
    /**
     * Set the value of the Lossless property
     *
     * Can only be called if EnablePropertyLossless has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyLossless(bool aValue);
    /**
     * Get a copy of the value of the Lossless property
     *
     * Can only be called if EnablePropertyLossless has previously been called.
     */
    void GetPropertyLossless(bool& aValue);
    /**
     * Set the value of the CodecName property
     *
     * Can only be called if EnablePropertyCodecName has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyCodecName(const std::string& aValue);
    /**
     * Get a copy of the value of the CodecName property
     *
     * Can only be called if EnablePropertyCodecName has previously been called.
     */
    void GetPropertyCodecName(std::string& aValue);
    /**
     * Set the value of the Metatext property
     *
     * Can only be called if EnablePropertyMetatext has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyMetatext(const std::string& aValue);
    /**
     * Get a copy of the value of the Metatext property
     *
     * Can only be called if EnablePropertyMetatext has previously been called.
     */
    void GetPropertyMetatext(std::string& aValue);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderAvOpenhomeOrgInfo1Cpp(DvDeviceStd& aDevice);
    /**
     * Enable the TrackCount property.
     */
    void EnablePropertyTrackCount();
    /**
     * Enable the DetailsCount property.
     */
    void EnablePropertyDetailsCount();
    /**
     * Enable the MetatextCount property.
     */
    void EnablePropertyMetatextCount();
    /**
     * Enable the Uri property.
     */
    void EnablePropertyUri();
    /**
     * Enable the Metadata property.
     */
    void EnablePropertyMetadata();
    /**
     * Enable the Duration property.
     */
    void EnablePropertyDuration();
    /**
     * Enable the BitRate property.
     */
    void EnablePropertyBitRate();
    /**
     * Enable the BitDepth property.
     */
    void EnablePropertyBitDepth();
    /**
     * Enable the SampleRate property.
     */
    void EnablePropertySampleRate();
    /**
     * Enable the Lossless property.
     */
    void EnablePropertyLossless();
    /**
     * Enable the CodecName property.
     */
    void EnablePropertyCodecName();
    /**
     * Enable the Metatext property.
     */
    void EnablePropertyMetatext();
    /**
     * Signal that the action Counters is supported.
     * The action's availability will be published in the device's service.xml.
     * Counters must be overridden if this is called.
     */
    void EnableActionCounters();
    /**
     * Signal that the action Track is supported.
     * The action's availability will be published in the device's service.xml.
     * Track must be overridden if this is called.
     */
    void EnableActionTrack();
    /**
     * Signal that the action Details is supported.
     * The action's availability will be published in the device's service.xml.
     * Details must be overridden if this is called.
     */
    void EnableActionDetails();
    /**
     * Signal that the action Metatext is supported.
     * The action's availability will be published in the device's service.xml.
     * Metatext must be overridden if this is called.
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
    virtual void Counters(IDvInvocationStd& aInvocation, uint32_t& aTrackCount, uint32_t& aDetailsCount, uint32_t& aMetatextCount);
    /**
     * Track action.
     *
     * Will be called when the device stack receives an invocation of the
     * Track action for the owning device.
     * Must be implemented iff EnableActionTrack was called.
     */
    virtual void Track(IDvInvocationStd& aInvocation, std::string& aUri, std::string& aMetadata);
    /**
     * Details action.
     *
     * Will be called when the device stack receives an invocation of the
     * Details action for the owning device.
     * Must be implemented iff EnableActionDetails was called.
     */
    virtual void Details(IDvInvocationStd& aInvocation, uint32_t& aDuration, uint32_t& aBitRate, uint32_t& aBitDepth, uint32_t& aSampleRate, bool& aLossless, std::string& aCodecName);
    /**
     * Metatext action.
     *
     * Will be called when the device stack receives an invocation of the
     * Metatext action for the owning device.
     * Must be implemented iff EnableActionMetatext was called.
     */
    virtual void Metatext(IDvInvocationStd& aInvocation, std::string& aValue);
private:
    DvProviderAvOpenhomeOrgInfo1Cpp();
    void DoCounters(IDviInvocation& aInvocation);
    void DoTrack(IDviInvocation& aInvocation);
    void DoDetails(IDviInvocation& aInvocation);
    void DoMetatext(IDviInvocation& aInvocation);
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

} // namespace Net
} // namespace OpenHome

#endif // HEADER_DVAVOPENHOMEORGINFO1CPP

