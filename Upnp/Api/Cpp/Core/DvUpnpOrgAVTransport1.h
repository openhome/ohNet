#ifndef HEADER_DVUPNPORGAVTRANSPORT1
#define HEADER_DVUPNPORGAVTRANSPORT1

#include <ZappTypes.h>
#include <Buffer.h>
#include <Core/DvDevice.h>
#include <DvService.h>

namespace Zapp {

class PropertyInt;
class PropertyUint;
class PropertyBool;
class PropertyString;
class PropertyBinary;

/**
 * Base Device for upnp.org:AVTransport:1
 */
class DvServiceUpnpOrgAVTransport1 : public DvService
{
public:
    virtual ~DvServiceUpnpOrgAVTransport1() {}
    void SetPropertyLastChange(const Brx& aValue);
    void GetPropertyLastChange(Brhz& aValue);
protected:
    DvServiceUpnpOrgAVTransport1(DvDevice& aDevice);
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
    virtual void SetAVTransportURI(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aCurrentURI, const Brx& aCurrentURIMetaData);
    virtual void SetNextAVTransportURI(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aNextURI, const Brx& aNextURIMetaData);
    virtual void GetMediaInfo(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aNrTracks, IInvocationResponseString& aMediaDuration, IInvocationResponseString& aCurrentURI, IInvocationResponseString& aCurrentURIMetaData, IInvocationResponseString& aNextURI, IInvocationResponseString& aNextURIMetaData, IInvocationResponseString& aPlayMedium, IInvocationResponseString& aRecordMedium, IInvocationResponseString& aWriteStatus);
    virtual void GetTransportInfo(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseString& aCurrentTransportState, IInvocationResponseString& aCurrentTransportStatus, IInvocationResponseString& aCurrentSpeed);
    virtual void GetPositionInfo(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aTrack, IInvocationResponseString& aTrackDuration, IInvocationResponseString& aTrackMetaData, IInvocationResponseString& aTrackURI, IInvocationResponseString& aRelTime, IInvocationResponseString& aAbsTime, IInvocationResponseInt& aRelCount, IInvocationResponseInt& aAbsCount);
    virtual void GetDeviceCapabilities(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseString& aPlayMedia, IInvocationResponseString& aRecMedia, IInvocationResponseString& aRecQualityModes);
    virtual void GetTransportSettings(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseString& aPlayMode, IInvocationResponseString& aRecQualityMode);
    virtual void Stop(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID);
    virtual void Play(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aSpeed);
    virtual void Pause(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID);
    virtual void Record(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID);
    virtual void Seek(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aUnit, const Brx& aTarget);
    virtual void Next(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID);
    virtual void Previous(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID);
    virtual void SetPlayMode(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aNewPlayMode);
    virtual void SetRecordQualityMode(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aNewRecordQualityMode);
    virtual void GetCurrentTransportActions(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseString& aActions);
private:
    DvServiceUpnpOrgAVTransport1();
    void DoSetAVTransportURI(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetNextAVTransportURI(IDvInvocation& aInvocation, TUint aVersion);
    void DoGetMediaInfo(IDvInvocation& aInvocation, TUint aVersion);
    void DoGetTransportInfo(IDvInvocation& aInvocation, TUint aVersion);
    void DoGetPositionInfo(IDvInvocation& aInvocation, TUint aVersion);
    void DoGetDeviceCapabilities(IDvInvocation& aInvocation, TUint aVersion);
    void DoGetTransportSettings(IDvInvocation& aInvocation, TUint aVersion);
    void DoStop(IDvInvocation& aInvocation, TUint aVersion);
    void DoPlay(IDvInvocation& aInvocation, TUint aVersion);
    void DoPause(IDvInvocation& aInvocation, TUint aVersion);
    void DoRecord(IDvInvocation& aInvocation, TUint aVersion);
    void DoSeek(IDvInvocation& aInvocation, TUint aVersion);
    void DoNext(IDvInvocation& aInvocation, TUint aVersion);
    void DoPrevious(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetPlayMode(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetRecordQualityMode(IDvInvocation& aInvocation, TUint aVersion);
    void DoGetCurrentTransportActions(IDvInvocation& aInvocation, TUint aVersion);
private:
    PropertyString* iPropertyLastChange;
};

} // namespace Zapp

#endif // HEADER_DVUPNPORGAVTRANSPORT1

