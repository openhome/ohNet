#ifndef HEADER_DVUPNPORGAVTRANSPORT2
#define HEADER_DVUPNPORGAVTRANSPORT2

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
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyLastChange(const Brx& aValue);
    /**
     * Get a copy of the value of the LastChange property
     */
    void GetPropertyLastChange(Brhz& aValue);
    /**
     * Set the value of the DRMState property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyDRMState(const Brx& aValue);
    /**
     * Get a copy of the value of the DRMState property
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
     * Signal that the action SetAVTransportURI is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetAVTransportURI must be overridden if this is called.
     */
    void EnableActionSetAVTransportURI();
    /**
     * Signal that the action SetNextAVTransportURI is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetNextAVTransportURI must be overridden if this is called.
     */
    void EnableActionSetNextAVTransportURI();
    /**
     * Signal that the action GetMediaInfo is supported.
     * The action's availability will be published in the device's service.xml.
     * DoGetMediaInfo must be overridden if this is called.
     */
    void EnableActionGetMediaInfo();
    /**
     * Signal that the action GetMediaInfo_Ext is supported.
     * The action's availability will be published in the device's service.xml.
     * DoGetMediaInfo_Ext must be overridden if this is called.
     */
    void EnableActionGetMediaInfo_Ext();
    /**
     * Signal that the action GetTransportInfo is supported.
     * The action's availability will be published in the device's service.xml.
     * DoGetTransportInfo must be overridden if this is called.
     */
    void EnableActionGetTransportInfo();
    /**
     * Signal that the action GetPositionInfo is supported.
     * The action's availability will be published in the device's service.xml.
     * DoGetPositionInfo must be overridden if this is called.
     */
    void EnableActionGetPositionInfo();
    /**
     * Signal that the action GetDeviceCapabilities is supported.
     * The action's availability will be published in the device's service.xml.
     * DoGetDeviceCapabilities must be overridden if this is called.
     */
    void EnableActionGetDeviceCapabilities();
    /**
     * Signal that the action GetTransportSettings is supported.
     * The action's availability will be published in the device's service.xml.
     * DoGetTransportSettings must be overridden if this is called.
     */
    void EnableActionGetTransportSettings();
    /**
     * Signal that the action Stop is supported.
     * The action's availability will be published in the device's service.xml.
     * DoStop must be overridden if this is called.
     */
    void EnableActionStop();
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
     * Signal that the action Record is supported.
     * The action's availability will be published in the device's service.xml.
     * DoRecord must be overridden if this is called.
     */
    void EnableActionRecord();
    /**
     * Signal that the action Seek is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSeek must be overridden if this is called.
     */
    void EnableActionSeek();
    /**
     * Signal that the action Next is supported.
     * The action's availability will be published in the device's service.xml.
     * DoNext must be overridden if this is called.
     */
    void EnableActionNext();
    /**
     * Signal that the action Previous is supported.
     * The action's availability will be published in the device's service.xml.
     * DoPrevious must be overridden if this is called.
     */
    void EnableActionPrevious();
    /**
     * Signal that the action SetPlayMode is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetPlayMode must be overridden if this is called.
     */
    void EnableActionSetPlayMode();
    /**
     * Signal that the action SetRecordQualityMode is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetRecordQualityMode must be overridden if this is called.
     */
    void EnableActionSetRecordQualityMode();
    /**
     * Signal that the action GetCurrentTransportActions is supported.
     * The action's availability will be published in the device's service.xml.
     * DoGetCurrentTransportActions must be overridden if this is called.
     */
    void EnableActionGetCurrentTransportActions();
    /**
     * Signal that the action GetDRMState is supported.
     * The action's availability will be published in the device's service.xml.
     * DoGetDRMState must be overridden if this is called.
     */
    void EnableActionGetDRMState();
    /**
     * Signal that the action GetStateVariables is supported.
     * The action's availability will be published in the device's service.xml.
     * DoGetStateVariables must be overridden if this is called.
     */
    void EnableActionGetStateVariables();
    /**
     * Signal that the action SetStateVariables is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetStateVariables must be overridden if this is called.
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
    virtual void SetAVTransportURI(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aCurrentURI, const Brx& aCurrentURIMetaData);
    /**
     * SetNextAVTransportURI action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetNextAVTransportURI action for the owning device.
     * Must be implemented iff EnableActionSetNextAVTransportURI was called.
     */
    virtual void SetNextAVTransportURI(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aNextURI, const Brx& aNextURIMetaData);
    /**
     * GetMediaInfo action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetMediaInfo action for the owning device.
     * Must be implemented iff EnableActionGetMediaInfo was called.
     */
    virtual void GetMediaInfo(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aNrTracks, IInvocationResponseString& aMediaDuration, IInvocationResponseString& aCurrentURI, IInvocationResponseString& aCurrentURIMetaData, IInvocationResponseString& aNextURI, IInvocationResponseString& aNextURIMetaData, IInvocationResponseString& aPlayMedium, IInvocationResponseString& aRecordMedium, IInvocationResponseString& aWriteStatus);
    /**
     * GetMediaInfo_Ext action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetMediaInfo_Ext action for the owning device.
     * Must be implemented iff EnableActionGetMediaInfo_Ext was called.
     */
    virtual void GetMediaInfo_Ext(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseString& aCurrentType, IInvocationResponseUint& aNrTracks, IInvocationResponseString& aMediaDuration, IInvocationResponseString& aCurrentURI, IInvocationResponseString& aCurrentURIMetaData, IInvocationResponseString& aNextURI, IInvocationResponseString& aNextURIMetaData, IInvocationResponseString& aPlayMedium, IInvocationResponseString& aRecordMedium, IInvocationResponseString& aWriteStatus);
    /**
     * GetTransportInfo action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetTransportInfo action for the owning device.
     * Must be implemented iff EnableActionGetTransportInfo was called.
     */
    virtual void GetTransportInfo(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseString& aCurrentTransportState, IInvocationResponseString& aCurrentTransportStatus, IInvocationResponseString& aCurrentSpeed);
    /**
     * GetPositionInfo action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetPositionInfo action for the owning device.
     * Must be implemented iff EnableActionGetPositionInfo was called.
     */
    virtual void GetPositionInfo(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aTrack, IInvocationResponseString& aTrackDuration, IInvocationResponseString& aTrackMetaData, IInvocationResponseString& aTrackURI, IInvocationResponseString& aRelTime, IInvocationResponseString& aAbsTime, IInvocationResponseInt& aRelCount, IInvocationResponseInt& aAbsCount);
    /**
     * GetDeviceCapabilities action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetDeviceCapabilities action for the owning device.
     * Must be implemented iff EnableActionGetDeviceCapabilities was called.
     */
    virtual void GetDeviceCapabilities(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseString& aPlayMedia, IInvocationResponseString& aRecMedia, IInvocationResponseString& aRecQualityModes);
    /**
     * GetTransportSettings action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetTransportSettings action for the owning device.
     * Must be implemented iff EnableActionGetTransportSettings was called.
     */
    virtual void GetTransportSettings(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseString& aPlayMode, IInvocationResponseString& aRecQualityMode);
    /**
     * Stop action.
     *
     * Will be called when the device stack receives an invocation of the
     * Stop action for the owning device.
     * Must be implemented iff EnableActionStop was called.
     */
    virtual void Stop(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID);
    /**
     * Play action.
     *
     * Will be called when the device stack receives an invocation of the
     * Play action for the owning device.
     * Must be implemented iff EnableActionPlay was called.
     */
    virtual void Play(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aSpeed);
    /**
     * Pause action.
     *
     * Will be called when the device stack receives an invocation of the
     * Pause action for the owning device.
     * Must be implemented iff EnableActionPause was called.
     */
    virtual void Pause(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID);
    /**
     * Record action.
     *
     * Will be called when the device stack receives an invocation of the
     * Record action for the owning device.
     * Must be implemented iff EnableActionRecord was called.
     */
    virtual void Record(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID);
    /**
     * Seek action.
     *
     * Will be called when the device stack receives an invocation of the
     * Seek action for the owning device.
     * Must be implemented iff EnableActionSeek was called.
     */
    virtual void Seek(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aUnit, const Brx& aTarget);
    /**
     * Next action.
     *
     * Will be called when the device stack receives an invocation of the
     * Next action for the owning device.
     * Must be implemented iff EnableActionNext was called.
     */
    virtual void Next(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID);
    /**
     * Previous action.
     *
     * Will be called when the device stack receives an invocation of the
     * Previous action for the owning device.
     * Must be implemented iff EnableActionPrevious was called.
     */
    virtual void Previous(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID);
    /**
     * SetPlayMode action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetPlayMode action for the owning device.
     * Must be implemented iff EnableActionSetPlayMode was called.
     */
    virtual void SetPlayMode(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aNewPlayMode);
    /**
     * SetRecordQualityMode action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetRecordQualityMode action for the owning device.
     * Must be implemented iff EnableActionSetRecordQualityMode was called.
     */
    virtual void SetRecordQualityMode(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aNewRecordQualityMode);
    /**
     * GetCurrentTransportActions action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetCurrentTransportActions action for the owning device.
     * Must be implemented iff EnableActionGetCurrentTransportActions was called.
     */
    virtual void GetCurrentTransportActions(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseString& aActions);
    /**
     * GetDRMState action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetDRMState action for the owning device.
     * Must be implemented iff EnableActionGetDRMState was called.
     */
    virtual void GetDRMState(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseString& aCurrentDRMState);
    /**
     * GetStateVariables action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetStateVariables action for the owning device.
     * Must be implemented iff EnableActionGetStateVariables was called.
     */
    virtual void GetStateVariables(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aStateVariableList, IInvocationResponseString& aStateVariableValuePairs);
    /**
     * SetStateVariables action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetStateVariables action for the owning device.
     * Must be implemented iff EnableActionSetStateVariables was called.
     */
    virtual void SetStateVariables(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aAVTransportUDN, const Brx& aServiceType, const Brx& aServiceId, const Brx& aStateVariableValuePairs, IInvocationResponseString& aStateVariableList);
private:
    DvProviderUpnpOrgAVTransport2();
    void DoSetAVTransportURI(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetNextAVTransportURI(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetMediaInfo(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetMediaInfo_Ext(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetTransportInfo(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetPositionInfo(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetDeviceCapabilities(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetTransportSettings(IDviInvocation& aInvocation, TUint aVersion);
    void DoStop(IDviInvocation& aInvocation, TUint aVersion);
    void DoPlay(IDviInvocation& aInvocation, TUint aVersion);
    void DoPause(IDviInvocation& aInvocation, TUint aVersion);
    void DoRecord(IDviInvocation& aInvocation, TUint aVersion);
    void DoSeek(IDviInvocation& aInvocation, TUint aVersion);
    void DoNext(IDviInvocation& aInvocation, TUint aVersion);
    void DoPrevious(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetPlayMode(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetRecordQualityMode(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetCurrentTransportActions(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetDRMState(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetStateVariables(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetStateVariables(IDviInvocation& aInvocation, TUint aVersion);
private:
    PropertyString* iPropertyLastChange;
    PropertyString* iPropertyDRMState;
};

} // namespace Zapp

#endif // HEADER_DVUPNPORGAVTRANSPORT2

