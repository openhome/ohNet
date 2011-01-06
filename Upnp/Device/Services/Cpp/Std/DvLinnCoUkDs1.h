#ifndef HEADER_DVLINNCOUKDS1CPP
#define HEADER_DVLINNCOUKDS1CPP

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
 * Provider for the linn.co.uk:Ds:1 UPnP service
 * @ingroup Providers
 */
class DvProviderLinnCoUkDs1Cpp : public DvProvider
{
public:
    virtual ~DvProviderLinnCoUkDs1Cpp() {}
    /**
     * Set the value of the SupportedProtocols property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertySupportedProtocols(const std::string& aValue);
    /**
     * Get a copy of the value of the SupportedProtocols property
     */
    void GetPropertySupportedProtocols(std::string& aValue);
    /**
     * Set the value of the TrackDuration property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyTrackDuration(uint32_t aValue);
    /**
     * Get a copy of the value of the TrackDuration property
     */
    void GetPropertyTrackDuration(uint32_t& aValue);
    /**
     * Set the value of the TrackBitRate property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyTrackBitRate(uint32_t aValue);
    /**
     * Get a copy of the value of the TrackBitRate property
     */
    void GetPropertyTrackBitRate(uint32_t& aValue);
    /**
     * Set the value of the TrackLossless property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyTrackLossless(bool aValue);
    /**
     * Get a copy of the value of the TrackLossless property
     */
    void GetPropertyTrackLossless(bool& aValue);
    /**
     * Set the value of the TrackBitDepth property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyTrackBitDepth(uint32_t aValue);
    /**
     * Get a copy of the value of the TrackBitDepth property
     */
    void GetPropertyTrackBitDepth(uint32_t& aValue);
    /**
     * Set the value of the TrackSampleRate property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyTrackSampleRate(uint32_t aValue);
    /**
     * Get a copy of the value of the TrackSampleRate property
     */
    void GetPropertyTrackSampleRate(uint32_t& aValue);
    /**
     * Set the value of the TrackCodecName property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyTrackCodecName(const std::string& aValue);
    /**
     * Get a copy of the value of the TrackCodecName property
     */
    void GetPropertyTrackCodecName(std::string& aValue);
    /**
     * Set the value of the TrackId property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyTrackId(uint32_t aValue);
    /**
     * Get a copy of the value of the TrackId property
     */
    void GetPropertyTrackId(uint32_t& aValue);
    /**
     * Set the value of the TransportState property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyTransportState(const std::string& aValue);
    /**
     * Get a copy of the value of the TransportState property
     */
    void GetPropertyTransportState(std::string& aValue);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderLinnCoUkDs1Cpp(DvDeviceStd& aDevice);
    /**
     * Signal that the action Play is supported.
     * The action's availability will be published in the device's service.xml.
     * DoPlay must be overridden if this is called.
     */
    void EnableActionPlay();
    /**
     * Signal that the action Pause is supported.
     * The action's availability will be published in the device's service.xml.
     * DoPause must be overridden if this is called.
     */
    void EnableActionPause();
    /**
     * Signal that the action Stop is supported.
     * The action's availability will be published in the device's service.xml.
     * DoStop must be overridden if this is called.
     */
    void EnableActionStop();
    /**
     * Signal that the action SeekSecondAbsolute is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSeekSecondAbsolute must be overridden if this is called.
     */
    void EnableActionSeekSecondAbsolute();
    /**
     * Signal that the action SeekSecondRelative is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSeekSecondRelative must be overridden if this is called.
     */
    void EnableActionSeekSecondRelative();
    /**
     * Signal that the action SeekTrackId is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSeekTrackId must be overridden if this is called.
     */
    void EnableActionSeekTrackId();
    /**
     * Signal that the action SeekTrackAbsolute is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSeekTrackAbsolute must be overridden if this is called.
     */
    void EnableActionSeekTrackAbsolute();
    /**
     * Signal that the action SeekTrackRelative is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSeekTrackRelative must be overridden if this is called.
     */
    void EnableActionSeekTrackRelative();
    /**
     * Signal that the action State is supported.
     * The action's availability will be published in the device's service.xml.
     * DoState must be overridden if this is called.
     */
    void EnableActionState();
    /**
     * Signal that the action ProtocolInfo is supported.
     * The action's availability will be published in the device's service.xml.
     * DoProtocolInfo must be overridden if this is called.
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
    virtual void Play(uint32_t aVersion);
    /**
     * Pause action.
     *
     * Will be called when the device stack receives an invocation of the
     * Pause action for the owning device.
     * Must be implemented iff EnableActionPause was called.
     */
    virtual void Pause(uint32_t aVersion);
    /**
     * Stop action.
     *
     * Will be called when the device stack receives an invocation of the
     * Stop action for the owning device.
     * Must be implemented iff EnableActionStop was called.
     */
    virtual void Stop(uint32_t aVersion);
    /**
     * SeekSecondAbsolute action.
     *
     * Will be called when the device stack receives an invocation of the
     * SeekSecondAbsolute action for the owning device.
     * Must be implemented iff EnableActionSeekSecondAbsolute was called.
     */
    virtual void SeekSecondAbsolute(uint32_t aVersion, uint32_t aaSecond);
    /**
     * SeekSecondRelative action.
     *
     * Will be called when the device stack receives an invocation of the
     * SeekSecondRelative action for the owning device.
     * Must be implemented iff EnableActionSeekSecondRelative was called.
     */
    virtual void SeekSecondRelative(uint32_t aVersion, int32_t aaSecond);
    /**
     * SeekTrackId action.
     *
     * Will be called when the device stack receives an invocation of the
     * SeekTrackId action for the owning device.
     * Must be implemented iff EnableActionSeekTrackId was called.
     */
    virtual void SeekTrackId(uint32_t aVersion, uint32_t aaTrackId);
    /**
     * SeekTrackAbsolute action.
     *
     * Will be called when the device stack receives an invocation of the
     * SeekTrackAbsolute action for the owning device.
     * Must be implemented iff EnableActionSeekTrackAbsolute was called.
     */
    virtual void SeekTrackAbsolute(uint32_t aVersion, uint32_t aaTrack);
    /**
     * SeekTrackRelative action.
     *
     * Will be called when the device stack receives an invocation of the
     * SeekTrackRelative action for the owning device.
     * Must be implemented iff EnableActionSeekTrackRelative was called.
     */
    virtual void SeekTrackRelative(uint32_t aVersion, int32_t aaTrack);
    /**
     * State action.
     *
     * Will be called when the device stack receives an invocation of the
     * State action for the owning device.
     * Must be implemented iff EnableActionState was called.
     */
    virtual void State(uint32_t aVersion, std::string& aaTransportState, uint32_t& aaTrackDuration, uint32_t& aaTrackBitRate, bool& aaTrackLossless, uint32_t& aaTrackBitDepth, uint32_t& aaTrackSampleRate, std::string& aaTrackCodecName, uint32_t& aaTrackId);
    /**
     * ProtocolInfo action.
     *
     * Will be called when the device stack receives an invocation of the
     * ProtocolInfo action for the owning device.
     * Must be implemented iff EnableActionProtocolInfo was called.
     */
    virtual void ProtocolInfo(uint32_t aVersion, std::string& aaSupportedProtocols);
private:
    DvProviderLinnCoUkDs1Cpp();
    void DoPlay(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoPause(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoStop(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSeekSecondAbsolute(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSeekSecondRelative(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSeekTrackId(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSeekTrackAbsolute(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSeekTrackRelative(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoState(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoProtocolInfo(IDviInvocation& aInvocation, uint32_t aVersion);
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

#endif // HEADER_DVLINNCOUKDS1CPP

