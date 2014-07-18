#ifndef HEADER_DVUPNPORGAVTRANSPORT2
#define HEADER_DVUPNPORGAVTRANSPORT2

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
 * Provider for the upnp.org:AVTransport:2 UPnP service
 * @ingroup Providers
 */
class DvProviderUpnpOrgAVTransport2 : public DvProvider
{
public:
    virtual ~DvProviderUpnpOrgAVTransport2() {}
    /**
     * Set the value of the LastChange property
     *
     * Can only be called if EnablePropertyLastChange has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyLastChange(const Brx& aValue);
    /**
     * Get a copy of the value of the LastChange property
     *
     * Can only be called if EnablePropertyLastChange has previously been called.
     */
    void GetPropertyLastChange(Brhz& aValue);
    /**
     * Set the value of the DRMState property
     *
     * Can only be called if EnablePropertyDRMState has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyDRMState(const Brx& aValue);
    /**
     * Get a copy of the value of the DRMState property
     *
     * Can only be called if EnablePropertyDRMState has previously been called.
     */
    void GetPropertyDRMState(Brhz& aValue);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderUpnpOrgAVTransport2(DvDevice& aDevice);
    /**
     * Constructor.  Not for external use.
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderUpnpOrgAVTransport2(DviDevice& aDevice);
    /**
     * Enable the LastChange property.
     */
    void EnablePropertyLastChange();
    /**
     * Enable the DRMState property.
     */
    void EnablePropertyDRMState();
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
     * Signal that the action GetMediaInfo_Ext is supported.
     * The action's availability will be published in the device's service.xml.
     * GetMediaInfo_Ext must be overridden if this is called.
     */
    void EnableActionGetMediaInfo_Ext();
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
    /**
     * Signal that the action GetDRMState is supported.
     * The action's availability will be published in the device's service.xml.
     * GetDRMState must be overridden if this is called.
     */
    void EnableActionGetDRMState();
    /**
     * Signal that the action GetStateVariables is supported.
     * The action's availability will be published in the device's service.xml.
     * GetStateVariables must be overridden if this is called.
     */
    void EnableActionGetStateVariables();
    /**
     * Signal that the action SetStateVariables is supported.
     * The action's availability will be published in the device's service.xml.
     * SetStateVariables must be overridden if this is called.
     */
    void EnableActionSetStateVariables();
private:
    /**
     * SetAVTransportURI action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetAVTransportURI action for the owning device.
     * Must be implemented iff EnableActionSetAVTransportURI was called.
     */
    virtual void SetAVTransportURI(IDvInvocation& aInvocation, TUint aInstanceID, const Brx& aCurrentURI, const Brx& aCurrentURIMetaData);
    /**
     * SetNextAVTransportURI action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetNextAVTransportURI action for the owning device.
     * Must be implemented iff EnableActionSetNextAVTransportURI was called.
     */
    virtual void SetNextAVTransportURI(IDvInvocation& aInvocation, TUint aInstanceID, const Brx& aNextURI, const Brx& aNextURIMetaData);
    /**
     * GetMediaInfo action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetMediaInfo action for the owning device.
     * Must be implemented iff EnableActionGetMediaInfo was called.
     */
    virtual void GetMediaInfo(IDvInvocation& aInvocation, TUint aInstanceID, IDvInvocationResponseUint& aNrTracks, IDvInvocationResponseString& aMediaDuration, IDvInvocationResponseString& aCurrentURI, IDvInvocationResponseString& aCurrentURIMetaData, IDvInvocationResponseString& aNextURI, IDvInvocationResponseString& aNextURIMetaData, IDvInvocationResponseString& aPlayMedium, IDvInvocationResponseString& aRecordMedium, IDvInvocationResponseString& aWriteStatus);
    /**
     * GetMediaInfo_Ext action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetMediaInfo_Ext action for the owning device.
     * Must be implemented iff EnableActionGetMediaInfo_Ext was called.
     */
    virtual void GetMediaInfo_Ext(IDvInvocation& aInvocation, TUint aInstanceID, IDvInvocationResponseString& aCurrentType, IDvInvocationResponseUint& aNrTracks, IDvInvocationResponseString& aMediaDuration, IDvInvocationResponseString& aCurrentURI, IDvInvocationResponseString& aCurrentURIMetaData, IDvInvocationResponseString& aNextURI, IDvInvocationResponseString& aNextURIMetaData, IDvInvocationResponseString& aPlayMedium, IDvInvocationResponseString& aRecordMedium, IDvInvocationResponseString& aWriteStatus);
    /**
     * GetTransportInfo action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetTransportInfo action for the owning device.
     * Must be implemented iff EnableActionGetTransportInfo was called.
     */
    virtual void GetTransportInfo(IDvInvocation& aInvocation, TUint aInstanceID, IDvInvocationResponseString& aCurrentTransportState, IDvInvocationResponseString& aCurrentTransportStatus, IDvInvocationResponseString& aCurrentSpeed);
    /**
     * GetPositionInfo action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetPositionInfo action for the owning device.
     * Must be implemented iff EnableActionGetPositionInfo was called.
     */
    virtual void GetPositionInfo(IDvInvocation& aInvocation, TUint aInstanceID, IDvInvocationResponseUint& aTrack, IDvInvocationResponseString& aTrackDuration, IDvInvocationResponseString& aTrackMetaData, IDvInvocationResponseString& aTrackURI, IDvInvocationResponseString& aRelTime, IDvInvocationResponseString& aAbsTime, IDvInvocationResponseInt& aRelCount, IDvInvocationResponseInt& aAbsCount);
    /**
     * GetDeviceCapabilities action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetDeviceCapabilities action for the owning device.
     * Must be implemented iff EnableActionGetDeviceCapabilities was called.
     */
    virtual void GetDeviceCapabilities(IDvInvocation& aInvocation, TUint aInstanceID, IDvInvocationResponseString& aPlayMedia, IDvInvocationResponseString& aRecMedia, IDvInvocationResponseString& aRecQualityModes);
    /**
     * GetTransportSettings action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetTransportSettings action for the owning device.
     * Must be implemented iff EnableActionGetTransportSettings was called.
     */
    virtual void GetTransportSettings(IDvInvocation& aInvocation, TUint aInstanceID, IDvInvocationResponseString& aPlayMode, IDvInvocationResponseString& aRecQualityMode);
    /**
     * Stop action.
     *
     * Will be called when the device stack receives an invocation of the
     * Stop action for the owning device.
     * Must be implemented iff EnableActionStop was called.
     */
    virtual void Stop(IDvInvocation& aInvocation, TUint aInstanceID);
    /**
     * Play action.
     *
     * Will be called when the device stack receives an invocation of the
     * Play action for the owning device.
     * Must be implemented iff EnableActionPlay was called.
     */
    virtual void Play(IDvInvocation& aInvocation, TUint aInstanceID, const Brx& aSpeed);
    /**
     * Pause action.
     *
     * Will be called when the device stack receives an invocation of the
     * Pause action for the owning device.
     * Must be implemented iff EnableActionPause was called.
     */
    virtual void Pause(IDvInvocation& aInvocation, TUint aInstanceID);
    /**
     * Record action.
     *
     * Will be called when the device stack receives an invocation of the
     * Record action for the owning device.
     * Must be implemented iff EnableActionRecord was called.
     */
    virtual void Record(IDvInvocation& aInvocation, TUint aInstanceID);
    /**
     * Seek action.
     *
     * Will be called when the device stack receives an invocation of the
     * Seek action for the owning device.
     * Must be implemented iff EnableActionSeek was called.
     */
    virtual void Seek(IDvInvocation& aInvocation, TUint aInstanceID, const Brx& aUnit, const Brx& aTarget);
    /**
     * Next action.
     *
     * Will be called when the device stack receives an invocation of the
     * Next action for the owning device.
     * Must be implemented iff EnableActionNext was called.
     */
    virtual void Next(IDvInvocation& aInvocation, TUint aInstanceID);
    /**
     * Previous action.
     *
     * Will be called when the device stack receives an invocation of the
     * Previous action for the owning device.
     * Must be implemented iff EnableActionPrevious was called.
     */
    virtual void Previous(IDvInvocation& aInvocation, TUint aInstanceID);
    /**
     * SetPlayMode action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetPlayMode action for the owning device.
     * Must be implemented iff EnableActionSetPlayMode was called.
     */
    virtual void SetPlayMode(IDvInvocation& aInvocation, TUint aInstanceID, const Brx& aNewPlayMode);
    /**
     * SetRecordQualityMode action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetRecordQualityMode action for the owning device.
     * Must be implemented iff EnableActionSetRecordQualityMode was called.
     */
    virtual void SetRecordQualityMode(IDvInvocation& aInvocation, TUint aInstanceID, const Brx& aNewRecordQualityMode);
    /**
     * GetCurrentTransportActions action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetCurrentTransportActions action for the owning device.
     * Must be implemented iff EnableActionGetCurrentTransportActions was called.
     */
    virtual void GetCurrentTransportActions(IDvInvocation& aInvocation, TUint aInstanceID, IDvInvocationResponseString& aActions);
    /**
     * GetDRMState action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetDRMState action for the owning device.
     * Must be implemented iff EnableActionGetDRMState was called.
     */
    virtual void GetDRMState(IDvInvocation& aInvocation, TUint aInstanceID, IDvInvocationResponseString& aCurrentDRMState);
    /**
     * GetStateVariables action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetStateVariables action for the owning device.
     * Must be implemented iff EnableActionGetStateVariables was called.
     */
    virtual void GetStateVariables(IDvInvocation& aInvocation, TUint aInstanceID, const Brx& aStateVariableList, IDvInvocationResponseString& aStateVariableValuePairs);
    /**
     * SetStateVariables action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetStateVariables action for the owning device.
     * Must be implemented iff EnableActionSetStateVariables was called.
     */
    virtual void SetStateVariables(IDvInvocation& aInvocation, TUint aInstanceID, const Brx& aAVTransportUDN, const Brx& aServiceType, const Brx& aServiceId, const Brx& aStateVariableValuePairs, IDvInvocationResponseString& aStateVariableList);
private:
    DvProviderUpnpOrgAVTransport2();
    void Construct();
    void DoSetAVTransportURI(IDviInvocation& aInvocation);
    void DoSetNextAVTransportURI(IDviInvocation& aInvocation);
    void DoGetMediaInfo(IDviInvocation& aInvocation);
    void DoGetMediaInfo_Ext(IDviInvocation& aInvocation);
    void DoGetTransportInfo(IDviInvocation& aInvocation);
    void DoGetPositionInfo(IDviInvocation& aInvocation);
    void DoGetDeviceCapabilities(IDviInvocation& aInvocation);
    void DoGetTransportSettings(IDviInvocation& aInvocation);
    void DoStop(IDviInvocation& aInvocation);
    void DoPlay(IDviInvocation& aInvocation);
    void DoPause(IDviInvocation& aInvocation);
    void DoRecord(IDviInvocation& aInvocation);
    void DoSeek(IDviInvocation& aInvocation);
    void DoNext(IDviInvocation& aInvocation);
    void DoPrevious(IDviInvocation& aInvocation);
    void DoSetPlayMode(IDviInvocation& aInvocation);
    void DoSetRecordQualityMode(IDviInvocation& aInvocation);
    void DoGetCurrentTransportActions(IDviInvocation& aInvocation);
    void DoGetDRMState(IDviInvocation& aInvocation);
    void DoGetStateVariables(IDviInvocation& aInvocation);
    void DoSetStateVariables(IDviInvocation& aInvocation);
private:
    PropertyString* iPropertyLastChange;
    PropertyString* iPropertyDRMState;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_DVUPNPORGAVTRANSPORT2

