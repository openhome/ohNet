#ifndef HEADER_DVAVOPENHOMEORGINFO1
#define HEADER_DVAVOPENHOMEORGINFO1

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Core/DvDevice.h>
#include <OpenHome/Net/Core/DvProvider.h>

namespace OpenHome {
namespace Net {

class DviDevice;
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
class DvProviderAvOpenhomeOrgInfo1 : public DvProvider
{
public:
    virtual ~DvProviderAvOpenhomeOrgInfo1() {}
    /**
     * Set the value of the TrackCount property
     *
     * Can only be called if EnablePropertyTrackCount has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyTrackCount(TUint aValue);
    /**
     * Get a copy of the value of the TrackCount property
     *
     * Can only be called if EnablePropertyTrackCount has previously been called.
     */
    void GetPropertyTrackCount(TUint& aValue);
    /**
     * Set the value of the DetailsCount property
     *
     * Can only be called if EnablePropertyDetailsCount has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyDetailsCount(TUint aValue);
    /**
     * Get a copy of the value of the DetailsCount property
     *
     * Can only be called if EnablePropertyDetailsCount has previously been called.
     */
    void GetPropertyDetailsCount(TUint& aValue);
    /**
     * Set the value of the MetatextCount property
     *
     * Can only be called if EnablePropertyMetatextCount has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyMetatextCount(TUint aValue);
    /**
     * Get a copy of the value of the MetatextCount property
     *
     * Can only be called if EnablePropertyMetatextCount has previously been called.
     */
    void GetPropertyMetatextCount(TUint& aValue);
    /**
     * Set the value of the Uri property
     *
     * Can only be called if EnablePropertyUri has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyUri(const Brx& aValue);
    /**
     * Get a copy of the value of the Uri property
     *
     * Can only be called if EnablePropertyUri has previously been called.
     */
    void GetPropertyUri(Brhz& aValue);
    /**
     * Set the value of the Metadata property
     *
     * Can only be called if EnablePropertyMetadata has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyMetadata(const Brx& aValue);
    /**
     * Get a copy of the value of the Metadata property
     *
     * Can only be called if EnablePropertyMetadata has previously been called.
     */
    void GetPropertyMetadata(Brhz& aValue);
    /**
     * Set the value of the Duration property
     *
     * Can only be called if EnablePropertyDuration has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyDuration(TUint aValue);
    /**
     * Get a copy of the value of the Duration property
     *
     * Can only be called if EnablePropertyDuration has previously been called.
     */
    void GetPropertyDuration(TUint& aValue);
    /**
     * Set the value of the BitRate property
     *
     * Can only be called if EnablePropertyBitRate has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyBitRate(TUint aValue);
    /**
     * Get a copy of the value of the BitRate property
     *
     * Can only be called if EnablePropertyBitRate has previously been called.
     */
    void GetPropertyBitRate(TUint& aValue);
    /**
     * Set the value of the BitDepth property
     *
     * Can only be called if EnablePropertyBitDepth has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyBitDepth(TUint aValue);
    /**
     * Get a copy of the value of the BitDepth property
     *
     * Can only be called if EnablePropertyBitDepth has previously been called.
     */
    void GetPropertyBitDepth(TUint& aValue);
    /**
     * Set the value of the SampleRate property
     *
     * Can only be called if EnablePropertySampleRate has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertySampleRate(TUint aValue);
    /**
     * Get a copy of the value of the SampleRate property
     *
     * Can only be called if EnablePropertySampleRate has previously been called.
     */
    void GetPropertySampleRate(TUint& aValue);
    /**
     * Set the value of the Lossless property
     *
     * Can only be called if EnablePropertyLossless has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyLossless(TBool aValue);
    /**
     * Get a copy of the value of the Lossless property
     *
     * Can only be called if EnablePropertyLossless has previously been called.
     */
    void GetPropertyLossless(TBool& aValue);
    /**
     * Set the value of the CodecName property
     *
     * Can only be called if EnablePropertyCodecName has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyCodecName(const Brx& aValue);
    /**
     * Get a copy of the value of the CodecName property
     *
     * Can only be called if EnablePropertyCodecName has previously been called.
     */
    void GetPropertyCodecName(Brhz& aValue);
    /**
     * Set the value of the Metatext property
     *
     * Can only be called if EnablePropertyMetatext has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyMetatext(const Brx& aValue);
    /**
     * Get a copy of the value of the Metatext property
     *
     * Can only be called if EnablePropertyMetatext has previously been called.
     */
    void GetPropertyMetatext(Brhz& aValue);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderAvOpenhomeOrgInfo1(DvDevice& aDevice);
    /**
     * Constructor.  Not for external use.
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderAvOpenhomeOrgInfo1(DviDevice& aDevice);
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
    virtual void Counters(IDvInvocation& aInvocation, IDvInvocationResponseUint& aTrackCount, IDvInvocationResponseUint& aDetailsCount, IDvInvocationResponseUint& aMetatextCount);
    /**
     * Track action.
     *
     * Will be called when the device stack receives an invocation of the
     * Track action for the owning device.
     * Must be implemented iff EnableActionTrack was called.
     */
    virtual void Track(IDvInvocation& aInvocation, IDvInvocationResponseString& aUri, IDvInvocationResponseString& aMetadata);
    /**
     * Details action.
     *
     * Will be called when the device stack receives an invocation of the
     * Details action for the owning device.
     * Must be implemented iff EnableActionDetails was called.
     */
    virtual void Details(IDvInvocation& aInvocation, IDvInvocationResponseUint& aDuration, IDvInvocationResponseUint& aBitRate, IDvInvocationResponseUint& aBitDepth, IDvInvocationResponseUint& aSampleRate, IDvInvocationResponseBool& aLossless, IDvInvocationResponseString& aCodecName);
    /**
     * Metatext action.
     *
     * Will be called when the device stack receives an invocation of the
     * Metatext action for the owning device.
     * Must be implemented iff EnableActionMetatext was called.
     */
    virtual void Metatext(IDvInvocation& aInvocation, IDvInvocationResponseString& aValue);
private:
    DvProviderAvOpenhomeOrgInfo1();
    void Construct();
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

#endif // HEADER_DVAVOPENHOMEORGINFO1

