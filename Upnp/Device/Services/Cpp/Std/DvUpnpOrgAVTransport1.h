#ifndef HEADER_DVUPNPORGAVTRANSPORT1CPP
#define HEADER_DVUPNPORGAVTRANSPORT1CPP

#include <OhNetTypes.h>
#include <Buffer.h>
#include <Std/DvDevice.h>
#include <DvProvider.h>

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
 * Provider for the upnp.org:AVTransport:1 UPnP service
 * @ingroup Providers
 */
class DvProviderUpnpOrgAVTransport1Cpp : public DvProvider
{
public:
    virtual ~DvProviderUpnpOrgAVTransport1Cpp() {}
    /**
     * Set the value of the LastChange property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyLastChange(const std::string& aValue);
    /**
     * Get a copy of the value of the LastChange property
     */
    void GetPropertyLastChange(std::string& aValue);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderUpnpOrgAVTransport1Cpp(DvDeviceStd& aDevice);
    /**
     * Signal that the action SetAVTransportURI is supported.
     * The action's availability will be published in the device's service.xml.
     * SetAVTransportURI must be overridden if this is called.
     */
    void EnableActionSetAVTransportURI();
    /**
     * Signal that the action SetNextAVTransportURI is supported.
     * The action's availability will be published in the device's service.xml.
     * SetNextAVTransportURI must be overridden if this is called.
     */
    void EnableActionSetNextAVTransportURI();
    /**
     * Signal that the action GetMediaInfo is supported.
     * The action's availability will be published in the device's service.xml.
     * GetMediaInfo must be overridden if this is called.
     */
    void EnableActionGetMediaInfo();
    /**
     * Signal that the action GetTransportInfo is supported.
     * The action's availability will be published in the device's service.xml.
     * GetTransportInfo must be overridden if this is called.
     */
    void EnableActionGetTransportInfo();
    /**
     * Signal that the action GetPositionInfo is supported.
     * The action's availability will be published in the device's service.xml.
     * GetPositionInfo must be overridden if this is called.
     */
    void EnableActionGetPositionInfo();
    /**
     * Signal that the action GetDeviceCapabilities is supported.
     * The action's availability will be published in the device's service.xml.
     * GetDeviceCapabilities must be overridden if this is called.
     */
    void EnableActionGetDeviceCapabilities();
    /**
     * Signal that the action GetTransportSettings is supported.
     * The action's availability will be published in the device's service.xml.
     * GetTransportSettings must be overridden if this is called.
     */
    void EnableActionGetTransportSettings();
    /**
     * Signal that the action Stop is supported.
     * The action's availability will be published in the device's service.xml.
     * Stop must be overridden if this is called.
     */
    void EnableActionStop();
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
     * Signal that the action Record is supported.
     * The action's availability will be published in the device's service.xml.
     * Record must be overridden if this is called.
     */
    void EnableActionRecord();
    /**
     * Signal that the action Seek is supported.
     * The action's availability will be published in the device's service.xml.
     * Seek must be overridden if this is called.
     */
    void EnableActionSeek();
    /**
     * Signal that the action Next is supported.
     * The action's availability will be published in the device's service.xml.
     * Next must be overridden if this is called.
     */
    void EnableActionNext();
    /**
     * Signal that the action Previous is supported.
     * The action's availability will be published in the device's service.xml.
     * Previous must be overridden if this is called.
     */
    void EnableActionPrevious();
    /**
     * Signal that the action SetPlayMode is supported.
     * The action's availability will be published in the device's service.xml.
     * SetPlayMode must be overridden if this is called.
     */
    void EnableActionSetPlayMode();
    /**
     * Signal that the action SetRecordQualityMode is supported.
     * The action's availability will be published in the device's service.xml.
     * SetRecordQualityMode must be overridden if this is called.
     */
    void EnableActionSetRecordQualityMode();
    /**
     * Signal that the action GetCurrentTransportActions is supported.
     * The action's availability will be published in the device's service.xml.
     * GetCurrentTransportActions must be overridden if this is called.
     */
    void EnableActionGetCurrentTransportActions();
private:
    /**
     * SetAVTransportURI action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetAVTransportURI action for the owning device.
     * Must be implemented iff EnableActionSetAVTransportURI was called.
     */
    virtual void SetAVTransportURI(uint32_t aVersion, uint32_t aInstanceID, const std::string& aCurrentURI, const std::string& aCurrentURIMetaData);
    /**
     * SetNextAVTransportURI action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetNextAVTransportURI action for the owning device.
     * Must be implemented iff EnableActionSetNextAVTransportURI was called.
     */
    virtual void SetNextAVTransportURI(uint32_t aVersion, uint32_t aInstanceID, const std::string& aNextURI, const std::string& aNextURIMetaData);
    /**
     * GetMediaInfo action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetMediaInfo action for the owning device.
     * Must be implemented iff EnableActionGetMediaInfo was called.
     */
    virtual void GetMediaInfo(uint32_t aVersion, uint32_t aInstanceID, uint32_t& aNrTracks, std::string& aMediaDuration, std::string& aCurrentURI, std::string& aCurrentURIMetaData, std::string& aNextURI, std::string& aNextURIMetaData, std::string& aPlayMedium, std::string& aRecordMedium, std::string& aWriteStatus);
    /**
     * GetTransportInfo action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetTransportInfo action for the owning device.
     * Must be implemented iff EnableActionGetTransportInfo was called.
     */
    virtual void GetTransportInfo(uint32_t aVersion, uint32_t aInstanceID, std::string& aCurrentTransportState, std::string& aCurrentTransportStatus, std::string& aCurrentSpeed);
    /**
     * GetPositionInfo action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetPositionInfo action for the owning device.
     * Must be implemented iff EnableActionGetPositionInfo was called.
     */
    virtual void GetPositionInfo(uint32_t aVersion, uint32_t aInstanceID, uint32_t& aTrack, std::string& aTrackDuration, std::string& aTrackMetaData, std::string& aTrackURI, std::string& aRelTime, std::string& aAbsTime, int32_t& aRelCount, int32_t& aAbsCount);
    /**
     * GetDeviceCapabilities action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetDeviceCapabilities action for the owning device.
     * Must be implemented iff EnableActionGetDeviceCapabilities was called.
     */
    virtual void GetDeviceCapabilities(uint32_t aVersion, uint32_t aInstanceID, std::string& aPlayMedia, std::string& aRecMedia, std::string& aRecQualityModes);
    /**
     * GetTransportSettings action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetTransportSettings action for the owning device.
     * Must be implemented iff EnableActionGetTransportSettings was called.
     */
    virtual void GetTransportSettings(uint32_t aVersion, uint32_t aInstanceID, std::string& aPlayMode, std::string& aRecQualityMode);
    /**
     * Stop action.
     *
     * Will be called when the device stack receives an invocation of the
     * Stop action for the owning device.
     * Must be implemented iff EnableActionStop was called.
     */
    virtual void Stop(uint32_t aVersion, uint32_t aInstanceID);
    /**
     * Play action.
     *
     * Will be called when the device stack receives an invocation of the
     * Play action for the owning device.
     * Must be implemented iff EnableActionPlay was called.
     */
    virtual void Play(uint32_t aVersion, uint32_t aInstanceID, const std::string& aSpeed);
    /**
     * Pause action.
     *
     * Will be called when the device stack receives an invocation of the
     * Pause action for the owning device.
     * Must be implemented iff EnableActionPause was called.
     */
    virtual void Pause(uint32_t aVersion, uint32_t aInstanceID);
    /**
     * Record action.
     *
     * Will be called when the device stack receives an invocation of the
     * Record action for the owning device.
     * Must be implemented iff EnableActionRecord was called.
     */
    virtual void Record(uint32_t aVersion, uint32_t aInstanceID);
    /**
     * Seek action.
     *
     * Will be called when the device stack receives an invocation of the
     * Seek action for the owning device.
     * Must be implemented iff EnableActionSeek was called.
     */
    virtual void Seek(uint32_t aVersion, uint32_t aInstanceID, const std::string& aUnit, const std::string& aTarget);
    /**
     * Next action.
     *
     * Will be called when the device stack receives an invocation of the
     * Next action for the owning device.
     * Must be implemented iff EnableActionNext was called.
     */
    virtual void Next(uint32_t aVersion, uint32_t aInstanceID);
    /**
     * Previous action.
     *
     * Will be called when the device stack receives an invocation of the
     * Previous action for the owning device.
     * Must be implemented iff EnableActionPrevious was called.
     */
    virtual void Previous(uint32_t aVersion, uint32_t aInstanceID);
    /**
     * SetPlayMode action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetPlayMode action for the owning device.
     * Must be implemented iff EnableActionSetPlayMode was called.
     */
    virtual void SetPlayMode(uint32_t aVersion, uint32_t aInstanceID, const std::string& aNewPlayMode);
    /**
     * SetRecordQualityMode action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetRecordQualityMode action for the owning device.
     * Must be implemented iff EnableActionSetRecordQualityMode was called.
     */
    virtual void SetRecordQualityMode(uint32_t aVersion, uint32_t aInstanceID, const std::string& aNewRecordQualityMode);
    /**
     * GetCurrentTransportActions action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetCurrentTransportActions action for the owning device.
     * Must be implemented iff EnableActionGetCurrentTransportActions was called.
     */
    virtual void GetCurrentTransportActions(uint32_t aVersion, uint32_t aInstanceID, std::string& aActions);
private:
    DvProviderUpnpOrgAVTransport1Cpp();
    void DoSetAVTransportURI(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetNextAVTransportURI(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetMediaInfo(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetTransportInfo(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetPositionInfo(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetDeviceCapabilities(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetTransportSettings(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoStop(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoPlay(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoPause(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoRecord(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSeek(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoNext(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoPrevious(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetPlayMode(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetRecordQualityMode(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetCurrentTransportActions(IDviInvocation& aInvocation, uint32_t aVersion);
private:
    PropertyString* iPropertyLastChange;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_DVUPNPORGAVTRANSPORT1CPP

