#ifndef HEADER_DVLINNCOUKDS1
#define HEADER_DVLINNCOUKDS1

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
 * Provider for the linn.co.uk:Ds:1 UPnP service
 * @ingroup Providers
 */
class DvProviderLinnCoUkDs1 : public DvProvider
{
public:
    virtual ~DvProviderLinnCoUkDs1() {}
    /**
     * Set the value of the SupportedProtocols property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertySupportedProtocols(const Brx& aValue);
    /**
     * Get a copy of the value of the SupportedProtocols property
     */
    void GetPropertySupportedProtocols(Brhz& aValue);
    /**
     * Set the value of the TrackDuration property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyTrackDuration(TUint aValue);
    /**
     * Get a copy of the value of the TrackDuration property
     */
    void GetPropertyTrackDuration(TUint& aValue);
    /**
     * Set the value of the TrackBitRate property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyTrackBitRate(TUint aValue);
    /**
     * Get a copy of the value of the TrackBitRate property
     */
    void GetPropertyTrackBitRate(TUint& aValue);
    /**
     * Set the value of the TrackLossless property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyTrackLossless(TBool aValue);
    /**
     * Get a copy of the value of the TrackLossless property
     */
    void GetPropertyTrackLossless(TBool& aValue);
    /**
     * Set the value of the TrackBitDepth property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyTrackBitDepth(TUint aValue);
    /**
     * Get a copy of the value of the TrackBitDepth property
     */
    void GetPropertyTrackBitDepth(TUint& aValue);
    /**
     * Set the value of the TrackSampleRate property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyTrackSampleRate(TUint aValue);
    /**
     * Get a copy of the value of the TrackSampleRate property
     */
    void GetPropertyTrackSampleRate(TUint& aValue);
    /**
     * Set the value of the TrackCodecName property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyTrackCodecName(const Brx& aValue);
    /**
     * Get a copy of the value of the TrackCodecName property
     */
    void GetPropertyTrackCodecName(Brhz& aValue);
    /**
     * Set the value of the TrackId property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyTrackId(TUint aValue);
    /**
     * Get a copy of the value of the TrackId property
     */
    void GetPropertyTrackId(TUint& aValue);
    /**
     * Set the value of the TransportState property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyTransportState(const Brx& aValue);
    /**
     * Get a copy of the value of the TransportState property
     */
    void GetPropertyTransportState(Brhz& aValue);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderLinnCoUkDs1(DvDevice& aDevice);
    /**
     * Signal that the action Play is supported.
     * The action's availability will be published in the device's service.xml.
     * Play must be overridden if this is called.
     */
    void EnableActionPlay();
    /**
     * Signal that the action Pause is supported.
     * The action's availability will be published in the device's service.xml.
     * Pause must be overridden if this is called.
     */
    void EnableActionPause();
    /**
     * Signal that the action Stop is supported.
     * The action's availability will be published in the device's service.xml.
     * Stop must be overridden if this is called.
     */
    void EnableActionStop();
    /**
     * Signal that the action SeekSecondAbsolute is supported.
     * The action's availability will be published in the device's service.xml.
     * SeekSecondAbsolute must be overridden if this is called.
     */
    void EnableActionSeekSecondAbsolute();
    /**
     * Signal that the action SeekSecondRelative is supported.
     * The action's availability will be published in the device's service.xml.
     * SeekSecondRelative must be overridden if this is called.
     */
    void EnableActionSeekSecondRelative();
    /**
     * Signal that the action SeekTrackId is supported.
     * The action's availability will be published in the device's service.xml.
     * SeekTrackId must be overridden if this is called.
     */
    void EnableActionSeekTrackId();
    /**
     * Signal that the action SeekTrackAbsolute is supported.
     * The action's availability will be published in the device's service.xml.
     * SeekTrackAbsolute must be overridden if this is called.
     */
    void EnableActionSeekTrackAbsolute();
    /**
     * Signal that the action SeekTrackRelative is supported.
     * The action's availability will be published in the device's service.xml.
     * SeekTrackRelative must be overridden if this is called.
     */
    void EnableActionSeekTrackRelative();
    /**
     * Signal that the action State is supported.
     * The action's availability will be published in the device's service.xml.
     * State must be overridden if this is called.
     */
    void EnableActionState();
    /**
     * Signal that the action ProtocolInfo is supported.
     * The action's availability will be published in the device's service.xml.
     * ProtocolInfo must be overridden if this is called.
     */
    void EnableActionProtocolInfo();
private:
    /**
     * Play action.
     *
     * Will be called when the device stack receives an invocation of the
     * Play action for the owning device.
     * Must be implemented iff EnableActionPlay was called.
     */
    virtual void Play(IInvocationResponse& aResponse, TUint aVersion);
    /**
     * Pause action.
     *
     * Will be called when the device stack receives an invocation of the
     * Pause action for the owning device.
     * Must be implemented iff EnableActionPause was called.
     */
    virtual void Pause(IInvocationResponse& aResponse, TUint aVersion);
    /**
     * Stop action.
     *
     * Will be called when the device stack receives an invocation of the
     * Stop action for the owning device.
     * Must be implemented iff EnableActionStop was called.
     */
    virtual void Stop(IInvocationResponse& aResponse, TUint aVersion);
    /**
     * SeekSecondAbsolute action.
     *
     * Will be called when the device stack receives an invocation of the
     * SeekSecondAbsolute action for the owning device.
     * Must be implemented iff EnableActionSeekSecondAbsolute was called.
     */
    virtual void SeekSecondAbsolute(IInvocationResponse& aResponse, TUint aVersion, TUint aaSecond);
    /**
     * SeekSecondRelative action.
     *
     * Will be called when the device stack receives an invocation of the
     * SeekSecondRelative action for the owning device.
     * Must be implemented iff EnableActionSeekSecondRelative was called.
     */
    virtual void SeekSecondRelative(IInvocationResponse& aResponse, TUint aVersion, TInt aaSecond);
    /**
     * SeekTrackId action.
     *
     * Will be called when the device stack receives an invocation of the
     * SeekTrackId action for the owning device.
     * Must be implemented iff EnableActionSeekTrackId was called.
     */
    virtual void SeekTrackId(IInvocationResponse& aResponse, TUint aVersion, TUint aaTrackId);
    /**
     * SeekTrackAbsolute action.
     *
     * Will be called when the device stack receives an invocation of the
     * SeekTrackAbsolute action for the owning device.
     * Must be implemented iff EnableActionSeekTrackAbsolute was called.
     */
    virtual void SeekTrackAbsolute(IInvocationResponse& aResponse, TUint aVersion, TUint aaTrack);
    /**
     * SeekTrackRelative action.
     *
     * Will be called when the device stack receives an invocation of the
     * SeekTrackRelative action for the owning device.
     * Must be implemented iff EnableActionSeekTrackRelative was called.
     */
    virtual void SeekTrackRelative(IInvocationResponse& aResponse, TUint aVersion, TInt aaTrack);
    /**
     * State action.
     *
     * Will be called when the device stack receives an invocation of the
     * State action for the owning device.
     * Must be implemented iff EnableActionState was called.
     */
    virtual void State(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaTransportState, IInvocationResponseUint& aaTrackDuration, IInvocationResponseUint& aaTrackBitRate, IInvocationResponseBool& aaTrackLossless, IInvocationResponseUint& aaTrackBitDepth, IInvocationResponseUint& aaTrackSampleRate, IInvocationResponseString& aaTrackCodecName, IInvocationResponseUint& aaTrackId);
    /**
     * ProtocolInfo action.
     *
     * Will be called when the device stack receives an invocation of the
     * ProtocolInfo action for the owning device.
     * Must be implemented iff EnableActionProtocolInfo was called.
     */
    virtual void ProtocolInfo(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaSupportedProtocols);
private:
    DvProviderLinnCoUkDs1();
    void DoPlay(IDviInvocation& aInvocation, TUint aVersion);
    void DoPause(IDviInvocation& aInvocation, TUint aVersion);
    void DoStop(IDviInvocation& aInvocation, TUint aVersion);
    void DoSeekSecondAbsolute(IDviInvocation& aInvocation, TUint aVersion);
    void DoSeekSecondRelative(IDviInvocation& aInvocation, TUint aVersion);
    void DoSeekTrackId(IDviInvocation& aInvocation, TUint aVersion);
    void DoSeekTrackAbsolute(IDviInvocation& aInvocation, TUint aVersion);
    void DoSeekTrackRelative(IDviInvocation& aInvocation, TUint aVersion);
    void DoState(IDviInvocation& aInvocation, TUint aVersion);
    void DoProtocolInfo(IDviInvocation& aInvocation, TUint aVersion);
private:
    PropertyString* iPropertySupportedProtocols;
    PropertyUint* iPropertyTrackDuration;
    PropertyUint* iPropertyTrackBitRate;
    PropertyBool* iPropertyTrackLossless;
    PropertyUint* iPropertyTrackBitDepth;
    PropertyUint* iPropertyTrackSampleRate;
    PropertyString* iPropertyTrackCodecName;
    PropertyUint* iPropertyTrackId;
    PropertyString* iPropertyTransportState;
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKDS1

