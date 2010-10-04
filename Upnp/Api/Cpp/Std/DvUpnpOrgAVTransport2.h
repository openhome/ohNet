#ifndef HEADER_DVUPNPORGAVTRANSPORT2CPP
#define HEADER_DVUPNPORGAVTRANSPORT2CPP

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
 * Base Device for upnp.org:AVTransport:2
 */
class DvServiceUpnpOrgAVTransport2Cpp : public DvService
{
public:
    virtual ~DvServiceUpnpOrgAVTransport2Cpp() {}
    void SetPropertyLastChange(const std::string& aValue);
    void GetPropertyLastChange(std::string& aValue);
    void SetPropertyDRMState(const std::string& aValue);
    void GetPropertyDRMState(std::string& aValue);
protected:
    DvServiceUpnpOrgAVTransport2Cpp(DvDeviceStd& aDevice);
    void EnableActionSetAVTransportURI();
    void EnableActionSetNextAVTransportURI();
    void EnableActionGetMediaInfo();
    void EnableActionGetMediaInfo_Ext();
    void EnableActionGetTransportInfo();
    void EnableActionGetPositionInfo();
    void EnableActionGetDeviceCapabilities();
    void EnableActionGetTransportSettings();
    void EnableActionStop();
    void EnableActionPlay();
    void EnableActionPause();
    void EnableActionRecord();
    void EnableActionSeek();
    void EnableActionNext();
    void EnableActionPrevious();
    void EnableActionSetPlayMode();
    void EnableActionSetRecordQualityMode();
    void EnableActionGetCurrentTransportActions();
    void EnableActionGetDRMState();
    void EnableActionGetStateVariables();
    void EnableActionSetStateVariables();
private:
    virtual void SetAVTransportURI(uint32_t aVersion, uint32_t aInstanceID, const std::string& aCurrentURI, const std::string& aCurrentURIMetaData);
    virtual void SetNextAVTransportURI(uint32_t aVersion, uint32_t aInstanceID, const std::string& aNextURI, const std::string& aNextURIMetaData);
    virtual void GetMediaInfo(uint32_t aVersion, uint32_t aInstanceID, uint32_t& aNrTracks, std::string& aMediaDuration, std::string& aCurrentURI, std::string& aCurrentURIMetaData, std::string& aNextURI, std::string& aNextURIMetaData, std::string& aPlayMedium, std::string& aRecordMedium, std::string& aWriteStatus);
    virtual void GetMediaInfo_Ext(uint32_t aVersion, uint32_t aInstanceID, std::string& aCurrentType, uint32_t& aNrTracks, std::string& aMediaDuration, std::string& aCurrentURI, std::string& aCurrentURIMetaData, std::string& aNextURI, std::string& aNextURIMetaData, std::string& aPlayMedium, std::string& aRecordMedium, std::string& aWriteStatus);
    virtual void GetTransportInfo(uint32_t aVersion, uint32_t aInstanceID, std::string& aCurrentTransportState, std::string& aCurrentTransportStatus, std::string& aCurrentSpeed);
    virtual void GetPositionInfo(uint32_t aVersion, uint32_t aInstanceID, uint32_t& aTrack, std::string& aTrackDuration, std::string& aTrackMetaData, std::string& aTrackURI, std::string& aRelTime, std::string& aAbsTime, int32_t& aRelCount, int32_t& aAbsCount);
    virtual void GetDeviceCapabilities(uint32_t aVersion, uint32_t aInstanceID, std::string& aPlayMedia, std::string& aRecMedia, std::string& aRecQualityModes);
    virtual void GetTransportSettings(uint32_t aVersion, uint32_t aInstanceID, std::string& aPlayMode, std::string& aRecQualityMode);
    virtual void Stop(uint32_t aVersion, uint32_t aInstanceID);
    virtual void Play(uint32_t aVersion, uint32_t aInstanceID, const std::string& aSpeed);
    virtual void Pause(uint32_t aVersion, uint32_t aInstanceID);
    virtual void Record(uint32_t aVersion, uint32_t aInstanceID);
    virtual void Seek(uint32_t aVersion, uint32_t aInstanceID, const std::string& aUnit, const std::string& aTarget);
    virtual void Next(uint32_t aVersion, uint32_t aInstanceID);
    virtual void Previous(uint32_t aVersion, uint32_t aInstanceID);
    virtual void SetPlayMode(uint32_t aVersion, uint32_t aInstanceID, const std::string& aNewPlayMode);
    virtual void SetRecordQualityMode(uint32_t aVersion, uint32_t aInstanceID, const std::string& aNewRecordQualityMode);
    virtual void GetCurrentTransportActions(uint32_t aVersion, uint32_t aInstanceID, std::string& aActions);
    virtual void GetDRMState(uint32_t aVersion, uint32_t aInstanceID, std::string& aCurrentDRMState);
    virtual void GetStateVariables(uint32_t aVersion, uint32_t aInstanceID, const std::string& aStateVariableList, std::string& aStateVariableValuePairs);
    virtual void SetStateVariables(uint32_t aVersion, uint32_t aInstanceID, const std::string& aAVTransportUDN, const std::string& aServiceType, const std::string& aServiceId, const std::string& aStateVariableValuePairs, std::string& aStateVariableList);
private:
    DvServiceUpnpOrgAVTransport2Cpp();
    void DoSetAVTransportURI(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetNextAVTransportURI(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoGetMediaInfo(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoGetMediaInfo_Ext(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoGetTransportInfo(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoGetPositionInfo(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoGetDeviceCapabilities(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoGetTransportSettings(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoStop(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoPlay(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoPause(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoRecord(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSeek(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoNext(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoPrevious(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetPlayMode(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetRecordQualityMode(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoGetCurrentTransportActions(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoGetDRMState(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoGetStateVariables(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetStateVariables(IDvInvocation& aInvocation, uint32_t aVersion);
private:
    PropertyString* iPropertyLastChange;
    PropertyString* iPropertyDRMState;
};

} // namespace Zapp

#endif // HEADER_DVUPNPORGAVTRANSPORT2CPP

