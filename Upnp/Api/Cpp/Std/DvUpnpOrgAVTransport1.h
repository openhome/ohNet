#ifndef HEADER_DVUPNPORGAVTRANSPORT1CPP
#define HEADER_DVUPNPORGAVTRANSPORT1CPP

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
 * Base Device for upnp.org:AVTransport:1
 */
class DvProviderUpnpOrgAVTransport1Cpp : public DvProvider
{
public:
    virtual ~DvProviderUpnpOrgAVTransport1Cpp() {}
    bool SetPropertyLastChange(const std::string& aValue);
    void GetPropertyLastChange(std::string& aValue);
protected:
    DvProviderUpnpOrgAVTransport1Cpp(DvDeviceStd& aDevice);
    void EnableActionSetAVTransportURI();
    void EnableActionSetNextAVTransportURI();
    void EnableActionGetMediaInfo();
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
private:
    virtual void SetAVTransportURI(uint32_t aVersion, uint32_t aInstanceID, const std::string& aCurrentURI, const std::string& aCurrentURIMetaData);
    virtual void SetNextAVTransportURI(uint32_t aVersion, uint32_t aInstanceID, const std::string& aNextURI, const std::string& aNextURIMetaData);
    virtual void GetMediaInfo(uint32_t aVersion, uint32_t aInstanceID, uint32_t& aNrTracks, std::string& aMediaDuration, std::string& aCurrentURI, std::string& aCurrentURIMetaData, std::string& aNextURI, std::string& aNextURIMetaData, std::string& aPlayMedium, std::string& aRecordMedium, std::string& aWriteStatus);
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

} // namespace Zapp

#endif // HEADER_DVUPNPORGAVTRANSPORT1CPP

