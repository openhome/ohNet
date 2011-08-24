#ifndef HEADER_DVAVOPENHOMEORGINFO1
#define HEADER_DVAVOPENHOMEORGINFO1

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Core/DvDevice.h>
#include <OpenHome/Net/Core/DvProvider.h>

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
class DvProviderAvOpenhomeOrgInfo1 : public DvProvider
{
public:
    virtual ~DvProviderAvOpenhomeOrgInfo1() {}
    /**
     * Set the value of the TrackCount property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyTrackCount(TUint aValue);
    /**
     * Get a copy of the value of the TrackCount property
     */
    void GetPropertyTrackCount(TUint& aValue);
    /**
     * Set the value of the DetailsCount property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyDetailsCount(TUint aValue);
    /**
     * Get a copy of the value of the DetailsCount property
     */
    void GetPropertyDetailsCount(TUint& aValue);
    /**
     * Set the value of the MetatextCount property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyMetatextCount(TUint aValue);
    /**
     * Get a copy of the value of the MetatextCount property
     */
    void GetPropertyMetatextCount(TUint& aValue);
    /**
     * Set the value of the Uri property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyUri(const Brx& aValue);
    /**
     * Get a copy of the value of the Uri property
     */
    void GetPropertyUri(Brhz& aValue);
    /**
     * Set the value of the Metadata property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyMetadata(const Brx& aValue);
    /**
     * Get a copy of the value of the Metadata property
     */
    void GetPropertyMetadata(Brhz& aValue);
    /**
     * Set the value of the Duration property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyDuration(TUint aValue);
    /**
     * Get a copy of the value of the Duration property
     */
    void GetPropertyDuration(TUint& aValue);
    /**
     * Set the value of the BitRate property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyBitRate(TUint aValue);
    /**
     * Get a copy of the value of the BitRate property
     */
    void GetPropertyBitRate(TUint& aValue);
    /**
     * Set the value of the BitDepth property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyBitDepth(TUint aValue);
    /**
     * Get a copy of the value of the BitDepth property
     */
    void GetPropertyBitDepth(TUint& aValue);
    /**
     * Set the value of the SampleRate property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertySampleRate(TUint aValue);
    /**
     * Get a copy of the value of the SampleRate property
     */
    void GetPropertySampleRate(TUint& aValue);
    /**
     * Set the value of the Lossless property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyLossless(TBool aValue);
    /**
     * Get a copy of the value of the Lossless property
     */
    void GetPropertyLossless(TBool& aValue);
    /**
     * Set the value of the CodecName property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyCodecName(const Brx& aValue);
    /**
     * Get a copy of the value of the CodecName property
     */
    void GetPropertyCodecName(Brhz& aValue);
    /**
     * Set the value of the Metatext property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyMetatext(const Brx& aValue);
    /**
     * Get a copy of the value of the Metatext property
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
    void DoCounters(IDviInvocation& aInvocation, TUint aVersion);
    void DoTrack(IDviInvocation& aInvocation, TUint aVersion);
    void DoDetails(IDviInvocation& aInvocation, TUint aVersion);
    void DoMetatext(IDviInvocation& aInvocation, TUint aVersion);
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

