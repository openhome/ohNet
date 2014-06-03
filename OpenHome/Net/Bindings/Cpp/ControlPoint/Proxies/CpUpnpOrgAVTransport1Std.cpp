#include "CpUpnpOrgAVTransport1.h"
#include <OpenHome/Net/Core/CpProxy.h>
#include <OpenHome/Net/Private/CpiService.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Net/Private/AsyncPrivate.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Cpp/CpDevice.h>
#include <OpenHome/Net/Private/CpiDevice.h>

#include <string>

using namespace OpenHome;
using namespace OpenHome::Net;


class SyncSetAVTransportURIUpnpOrgAVTransport1Cpp : public SyncProxyAction
{
public:
    SyncSetAVTransportURIUpnpOrgAVTransport1Cpp(CpProxyUpnpOrgAVTransport1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetAVTransportURIUpnpOrgAVTransport1Cpp() {}
private:
    CpProxyUpnpOrgAVTransport1Cpp& iService;
};

SyncSetAVTransportURIUpnpOrgAVTransport1Cpp::SyncSetAVTransportURIUpnpOrgAVTransport1Cpp(CpProxyUpnpOrgAVTransport1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncSetAVTransportURIUpnpOrgAVTransport1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetAVTransportURI(aAsync);
}


class SyncSetNextAVTransportURIUpnpOrgAVTransport1Cpp : public SyncProxyAction
{
public:
    SyncSetNextAVTransportURIUpnpOrgAVTransport1Cpp(CpProxyUpnpOrgAVTransport1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetNextAVTransportURIUpnpOrgAVTransport1Cpp() {}
private:
    CpProxyUpnpOrgAVTransport1Cpp& iService;
};

SyncSetNextAVTransportURIUpnpOrgAVTransport1Cpp::SyncSetNextAVTransportURIUpnpOrgAVTransport1Cpp(CpProxyUpnpOrgAVTransport1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncSetNextAVTransportURIUpnpOrgAVTransport1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetNextAVTransportURI(aAsync);
}


class SyncGetMediaInfoUpnpOrgAVTransport1Cpp : public SyncProxyAction
{
public:
    SyncGetMediaInfoUpnpOrgAVTransport1Cpp(CpProxyUpnpOrgAVTransport1Cpp& aProxy, uint32_t& aNrTracks, std::string& aMediaDuration, std::string& aCurrentURI, std::string& aCurrentURIMetaData, std::string& aNextURI, std::string& aNextURIMetaData, std::string& aPlayMedium, std::string& aRecordMedium, std::string& aWriteStatus);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetMediaInfoUpnpOrgAVTransport1Cpp() {}
private:
    CpProxyUpnpOrgAVTransport1Cpp& iService;
    uint32_t& iNrTracks;
    std::string& iMediaDuration;
    std::string& iCurrentURI;
    std::string& iCurrentURIMetaData;
    std::string& iNextURI;
    std::string& iNextURIMetaData;
    std::string& iPlayMedium;
    std::string& iRecordMedium;
    std::string& iWriteStatus;
};

SyncGetMediaInfoUpnpOrgAVTransport1Cpp::SyncGetMediaInfoUpnpOrgAVTransport1Cpp(CpProxyUpnpOrgAVTransport1Cpp& aProxy, uint32_t& aNrTracks, std::string& aMediaDuration, std::string& aCurrentURI, std::string& aCurrentURIMetaData, std::string& aNextURI, std::string& aNextURIMetaData, std::string& aPlayMedium, std::string& aRecordMedium, std::string& aWriteStatus)
    : iService(aProxy)
    , iNrTracks(aNrTracks)
    , iMediaDuration(aMediaDuration)
    , iCurrentURI(aCurrentURI)
    , iCurrentURIMetaData(aCurrentURIMetaData)
    , iNextURI(aNextURI)
    , iNextURIMetaData(aNextURIMetaData)
    , iPlayMedium(aPlayMedium)
    , iRecordMedium(aRecordMedium)
    , iWriteStatus(aWriteStatus)
{
}

void SyncGetMediaInfoUpnpOrgAVTransport1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetMediaInfo(aAsync, iNrTracks, iMediaDuration, iCurrentURI, iCurrentURIMetaData, iNextURI, iNextURIMetaData, iPlayMedium, iRecordMedium, iWriteStatus);
}


class SyncGetTransportInfoUpnpOrgAVTransport1Cpp : public SyncProxyAction
{
public:
    SyncGetTransportInfoUpnpOrgAVTransport1Cpp(CpProxyUpnpOrgAVTransport1Cpp& aProxy, std::string& aCurrentTransportState, std::string& aCurrentTransportStatus, std::string& aCurrentSpeed);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetTransportInfoUpnpOrgAVTransport1Cpp() {}
private:
    CpProxyUpnpOrgAVTransport1Cpp& iService;
    std::string& iCurrentTransportState;
    std::string& iCurrentTransportStatus;
    std::string& iCurrentSpeed;
};

SyncGetTransportInfoUpnpOrgAVTransport1Cpp::SyncGetTransportInfoUpnpOrgAVTransport1Cpp(CpProxyUpnpOrgAVTransport1Cpp& aProxy, std::string& aCurrentTransportState, std::string& aCurrentTransportStatus, std::string& aCurrentSpeed)
    : iService(aProxy)
    , iCurrentTransportState(aCurrentTransportState)
    , iCurrentTransportStatus(aCurrentTransportStatus)
    , iCurrentSpeed(aCurrentSpeed)
{
}

void SyncGetTransportInfoUpnpOrgAVTransport1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetTransportInfo(aAsync, iCurrentTransportState, iCurrentTransportStatus, iCurrentSpeed);
}


class SyncGetPositionInfoUpnpOrgAVTransport1Cpp : public SyncProxyAction
{
public:
    SyncGetPositionInfoUpnpOrgAVTransport1Cpp(CpProxyUpnpOrgAVTransport1Cpp& aProxy, uint32_t& aTrack, std::string& aTrackDuration, std::string& aTrackMetaData, std::string& aTrackURI, std::string& aRelTime, std::string& aAbsTime, int32_t& aRelCount, int32_t& aAbsCount);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetPositionInfoUpnpOrgAVTransport1Cpp() {}
private:
    CpProxyUpnpOrgAVTransport1Cpp& iService;
    uint32_t& iTrack;
    std::string& iTrackDuration;
    std::string& iTrackMetaData;
    std::string& iTrackURI;
    std::string& iRelTime;
    std::string& iAbsTime;
    int32_t& iRelCount;
    int32_t& iAbsCount;
};

SyncGetPositionInfoUpnpOrgAVTransport1Cpp::SyncGetPositionInfoUpnpOrgAVTransport1Cpp(CpProxyUpnpOrgAVTransport1Cpp& aProxy, uint32_t& aTrack, std::string& aTrackDuration, std::string& aTrackMetaData, std::string& aTrackURI, std::string& aRelTime, std::string& aAbsTime, int32_t& aRelCount, int32_t& aAbsCount)
    : iService(aProxy)
    , iTrack(aTrack)
    , iTrackDuration(aTrackDuration)
    , iTrackMetaData(aTrackMetaData)
    , iTrackURI(aTrackURI)
    , iRelTime(aRelTime)
    , iAbsTime(aAbsTime)
    , iRelCount(aRelCount)
    , iAbsCount(aAbsCount)
{
}

void SyncGetPositionInfoUpnpOrgAVTransport1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetPositionInfo(aAsync, iTrack, iTrackDuration, iTrackMetaData, iTrackURI, iRelTime, iAbsTime, iRelCount, iAbsCount);
}


class SyncGetDeviceCapabilitiesUpnpOrgAVTransport1Cpp : public SyncProxyAction
{
public:
    SyncGetDeviceCapabilitiesUpnpOrgAVTransport1Cpp(CpProxyUpnpOrgAVTransport1Cpp& aProxy, std::string& aPlayMedia, std::string& aRecMedia, std::string& aRecQualityModes);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetDeviceCapabilitiesUpnpOrgAVTransport1Cpp() {}
private:
    CpProxyUpnpOrgAVTransport1Cpp& iService;
    std::string& iPlayMedia;
    std::string& iRecMedia;
    std::string& iRecQualityModes;
};

SyncGetDeviceCapabilitiesUpnpOrgAVTransport1Cpp::SyncGetDeviceCapabilitiesUpnpOrgAVTransport1Cpp(CpProxyUpnpOrgAVTransport1Cpp& aProxy, std::string& aPlayMedia, std::string& aRecMedia, std::string& aRecQualityModes)
    : iService(aProxy)
    , iPlayMedia(aPlayMedia)
    , iRecMedia(aRecMedia)
    , iRecQualityModes(aRecQualityModes)
{
}

void SyncGetDeviceCapabilitiesUpnpOrgAVTransport1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetDeviceCapabilities(aAsync, iPlayMedia, iRecMedia, iRecQualityModes);
}


class SyncGetTransportSettingsUpnpOrgAVTransport1Cpp : public SyncProxyAction
{
public:
    SyncGetTransportSettingsUpnpOrgAVTransport1Cpp(CpProxyUpnpOrgAVTransport1Cpp& aProxy, std::string& aPlayMode, std::string& aRecQualityMode);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetTransportSettingsUpnpOrgAVTransport1Cpp() {}
private:
    CpProxyUpnpOrgAVTransport1Cpp& iService;
    std::string& iPlayMode;
    std::string& iRecQualityMode;
};

SyncGetTransportSettingsUpnpOrgAVTransport1Cpp::SyncGetTransportSettingsUpnpOrgAVTransport1Cpp(CpProxyUpnpOrgAVTransport1Cpp& aProxy, std::string& aPlayMode, std::string& aRecQualityMode)
    : iService(aProxy)
    , iPlayMode(aPlayMode)
    , iRecQualityMode(aRecQualityMode)
{
}

void SyncGetTransportSettingsUpnpOrgAVTransport1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetTransportSettings(aAsync, iPlayMode, iRecQualityMode);
}


class SyncStopUpnpOrgAVTransport1Cpp : public SyncProxyAction
{
public:
    SyncStopUpnpOrgAVTransport1Cpp(CpProxyUpnpOrgAVTransport1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncStopUpnpOrgAVTransport1Cpp() {}
private:
    CpProxyUpnpOrgAVTransport1Cpp& iService;
};

SyncStopUpnpOrgAVTransport1Cpp::SyncStopUpnpOrgAVTransport1Cpp(CpProxyUpnpOrgAVTransport1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncStopUpnpOrgAVTransport1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndStop(aAsync);
}


class SyncPlayUpnpOrgAVTransport1Cpp : public SyncProxyAction
{
public:
    SyncPlayUpnpOrgAVTransport1Cpp(CpProxyUpnpOrgAVTransport1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncPlayUpnpOrgAVTransport1Cpp() {}
private:
    CpProxyUpnpOrgAVTransport1Cpp& iService;
};

SyncPlayUpnpOrgAVTransport1Cpp::SyncPlayUpnpOrgAVTransport1Cpp(CpProxyUpnpOrgAVTransport1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncPlayUpnpOrgAVTransport1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndPlay(aAsync);
}


class SyncPauseUpnpOrgAVTransport1Cpp : public SyncProxyAction
{
public:
    SyncPauseUpnpOrgAVTransport1Cpp(CpProxyUpnpOrgAVTransport1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncPauseUpnpOrgAVTransport1Cpp() {}
private:
    CpProxyUpnpOrgAVTransport1Cpp& iService;
};

SyncPauseUpnpOrgAVTransport1Cpp::SyncPauseUpnpOrgAVTransport1Cpp(CpProxyUpnpOrgAVTransport1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncPauseUpnpOrgAVTransport1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndPause(aAsync);
}


class SyncRecordUpnpOrgAVTransport1Cpp : public SyncProxyAction
{
public:
    SyncRecordUpnpOrgAVTransport1Cpp(CpProxyUpnpOrgAVTransport1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncRecordUpnpOrgAVTransport1Cpp() {}
private:
    CpProxyUpnpOrgAVTransport1Cpp& iService;
};

SyncRecordUpnpOrgAVTransport1Cpp::SyncRecordUpnpOrgAVTransport1Cpp(CpProxyUpnpOrgAVTransport1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncRecordUpnpOrgAVTransport1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndRecord(aAsync);
}


class SyncSeekUpnpOrgAVTransport1Cpp : public SyncProxyAction
{
public:
    SyncSeekUpnpOrgAVTransport1Cpp(CpProxyUpnpOrgAVTransport1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSeekUpnpOrgAVTransport1Cpp() {}
private:
    CpProxyUpnpOrgAVTransport1Cpp& iService;
};

SyncSeekUpnpOrgAVTransport1Cpp::SyncSeekUpnpOrgAVTransport1Cpp(CpProxyUpnpOrgAVTransport1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncSeekUpnpOrgAVTransport1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSeek(aAsync);
}


class SyncNextUpnpOrgAVTransport1Cpp : public SyncProxyAction
{
public:
    SyncNextUpnpOrgAVTransport1Cpp(CpProxyUpnpOrgAVTransport1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncNextUpnpOrgAVTransport1Cpp() {}
private:
    CpProxyUpnpOrgAVTransport1Cpp& iService;
};

SyncNextUpnpOrgAVTransport1Cpp::SyncNextUpnpOrgAVTransport1Cpp(CpProxyUpnpOrgAVTransport1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncNextUpnpOrgAVTransport1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndNext(aAsync);
}


class SyncPreviousUpnpOrgAVTransport1Cpp : public SyncProxyAction
{
public:
    SyncPreviousUpnpOrgAVTransport1Cpp(CpProxyUpnpOrgAVTransport1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncPreviousUpnpOrgAVTransport1Cpp() {}
private:
    CpProxyUpnpOrgAVTransport1Cpp& iService;
};

SyncPreviousUpnpOrgAVTransport1Cpp::SyncPreviousUpnpOrgAVTransport1Cpp(CpProxyUpnpOrgAVTransport1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncPreviousUpnpOrgAVTransport1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndPrevious(aAsync);
}


class SyncSetPlayModeUpnpOrgAVTransport1Cpp : public SyncProxyAction
{
public:
    SyncSetPlayModeUpnpOrgAVTransport1Cpp(CpProxyUpnpOrgAVTransport1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetPlayModeUpnpOrgAVTransport1Cpp() {}
private:
    CpProxyUpnpOrgAVTransport1Cpp& iService;
};

SyncSetPlayModeUpnpOrgAVTransport1Cpp::SyncSetPlayModeUpnpOrgAVTransport1Cpp(CpProxyUpnpOrgAVTransport1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncSetPlayModeUpnpOrgAVTransport1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetPlayMode(aAsync);
}


class SyncSetRecordQualityModeUpnpOrgAVTransport1Cpp : public SyncProxyAction
{
public:
    SyncSetRecordQualityModeUpnpOrgAVTransport1Cpp(CpProxyUpnpOrgAVTransport1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetRecordQualityModeUpnpOrgAVTransport1Cpp() {}
private:
    CpProxyUpnpOrgAVTransport1Cpp& iService;
};

SyncSetRecordQualityModeUpnpOrgAVTransport1Cpp::SyncSetRecordQualityModeUpnpOrgAVTransport1Cpp(CpProxyUpnpOrgAVTransport1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncSetRecordQualityModeUpnpOrgAVTransport1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetRecordQualityMode(aAsync);
}


class SyncGetCurrentTransportActionsUpnpOrgAVTransport1Cpp : public SyncProxyAction
{
public:
    SyncGetCurrentTransportActionsUpnpOrgAVTransport1Cpp(CpProxyUpnpOrgAVTransport1Cpp& aProxy, std::string& aActions);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetCurrentTransportActionsUpnpOrgAVTransport1Cpp() {}
private:
    CpProxyUpnpOrgAVTransport1Cpp& iService;
    std::string& iActions;
};

SyncGetCurrentTransportActionsUpnpOrgAVTransport1Cpp::SyncGetCurrentTransportActionsUpnpOrgAVTransport1Cpp(CpProxyUpnpOrgAVTransport1Cpp& aProxy, std::string& aActions)
    : iService(aProxy)
    , iActions(aActions)
{
}

void SyncGetCurrentTransportActionsUpnpOrgAVTransport1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetCurrentTransportActions(aAsync, iActions);
}


CpProxyUpnpOrgAVTransport1Cpp::CpProxyUpnpOrgAVTransport1Cpp(CpDeviceCpp& aDevice)
    : CpProxy("schemas-upnp-org", "AVTransport", 1, aDevice.Device())
{
    OpenHome::Net::Parameter* param;
    TChar** allowedValues;
    TUint index;

    iActionSetAVTransportURI = new Action("SetAVTransportURI");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionSetAVTransportURI->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("CurrentURI");
    iActionSetAVTransportURI->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("CurrentURIMetaData");
    iActionSetAVTransportURI->AddInputParameter(param);

    iActionSetNextAVTransportURI = new Action("SetNextAVTransportURI");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionSetNextAVTransportURI->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("NextURI");
    iActionSetNextAVTransportURI->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("NextURIMetaData");
    iActionSetNextAVTransportURI->AddInputParameter(param);

    iActionGetMediaInfo = new Action("GetMediaInfo");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionGetMediaInfo->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("NrTracks", 0, 2147483647);
    iActionGetMediaInfo->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("MediaDuration");
    iActionGetMediaInfo->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("CurrentURI");
    iActionGetMediaInfo->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("CurrentURIMetaData");
    iActionGetMediaInfo->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("NextURI");
    iActionGetMediaInfo->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("NextURIMetaData");
    iActionGetMediaInfo->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("PlayMedium");
    iActionGetMediaInfo->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("RecordMedium");
    iActionGetMediaInfo->AddOutputParameter(param);
    index = 0;
    allowedValues = new TChar*[5];
    allowedValues[index++] = (TChar*)"WRITABLE";
    allowedValues[index++] = (TChar*)"PROTECTED";
    allowedValues[index++] = (TChar*)"NOT_WRITABLE";
    allowedValues[index++] = (TChar*)"UNKNOWN";
    allowedValues[index++] = (TChar*)"NOT_IMPLEMENTED";
    param = new OpenHome::Net::ParameterString("WriteStatus", allowedValues, 5);
    iActionGetMediaInfo->AddOutputParameter(param);
    delete[] allowedValues;

    iActionGetTransportInfo = new Action("GetTransportInfo");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionGetTransportInfo->AddInputParameter(param);
    index = 0;
    allowedValues = new TChar*[7];
    allowedValues[index++] = (TChar*)"STOPPED";
    allowedValues[index++] = (TChar*)"PLAYING";
    allowedValues[index++] = (TChar*)"TRANSITIONING";
    allowedValues[index++] = (TChar*)"PAUSED_PLAYBACK";
    allowedValues[index++] = (TChar*)"PAUSED_RECORDING";
    allowedValues[index++] = (TChar*)"RECORDING";
    allowedValues[index++] = (TChar*)"NO_MEDIA_PRESENT";
    param = new OpenHome::Net::ParameterString("CurrentTransportState", allowedValues, 7);
    iActionGetTransportInfo->AddOutputParameter(param);
    delete[] allowedValues;
    index = 0;
    allowedValues = new TChar*[2];
    allowedValues[index++] = (TChar*)"OK";
    allowedValues[index++] = (TChar*)"ERROR_OCCURRED";
    param = new OpenHome::Net::ParameterString("CurrentTransportStatus", allowedValues, 2);
    iActionGetTransportInfo->AddOutputParameter(param);
    delete[] allowedValues;
    param = new OpenHome::Net::ParameterString("CurrentSpeed");
    iActionGetTransportInfo->AddOutputParameter(param);

    iActionGetPositionInfo = new Action("GetPositionInfo");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionGetPositionInfo->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("Track", 0, 2147483647, 1);
    iActionGetPositionInfo->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("TrackDuration");
    iActionGetPositionInfo->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("TrackMetaData");
    iActionGetPositionInfo->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("TrackURI");
    iActionGetPositionInfo->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("RelTime");
    iActionGetPositionInfo->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("AbsTime");
    iActionGetPositionInfo->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterInt("RelCount");
    iActionGetPositionInfo->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterInt("AbsCount");
    iActionGetPositionInfo->AddOutputParameter(param);

    iActionGetDeviceCapabilities = new Action("GetDeviceCapabilities");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionGetDeviceCapabilities->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("PlayMedia");
    iActionGetDeviceCapabilities->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("RecMedia");
    iActionGetDeviceCapabilities->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("RecQualityModes");
    iActionGetDeviceCapabilities->AddOutputParameter(param);

    iActionGetTransportSettings = new Action("GetTransportSettings");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionGetTransportSettings->AddInputParameter(param);
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"NORMAL";
    param = new OpenHome::Net::ParameterString("PlayMode", allowedValues, 1);
    iActionGetTransportSettings->AddOutputParameter(param);
    delete[] allowedValues;
    param = new OpenHome::Net::ParameterString("RecQualityMode");
    iActionGetTransportSettings->AddOutputParameter(param);

    iActionStop = new Action("Stop");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionStop->AddInputParameter(param);

    iActionPlay = new Action("Play");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionPlay->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Speed");
    iActionPlay->AddInputParameter(param);

    iActionPause = new Action("Pause");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionPause->AddInputParameter(param);

    iActionRecord = new Action("Record");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionRecord->AddInputParameter(param);

    iActionSeek = new Action("Seek");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionSeek->AddInputParameter(param);
    index = 0;
    allowedValues = new TChar*[8];
    allowedValues[index++] = (TChar*)"TRACK_NR";
    allowedValues[index++] = (TChar*)"ABS_TIME";
    allowedValues[index++] = (TChar*)"REL_TIME";
    allowedValues[index++] = (TChar*)"ABS_COUNT";
    allowedValues[index++] = (TChar*)"REL_COUNT";
    allowedValues[index++] = (TChar*)"CHANNEL_FREQ";
    allowedValues[index++] = (TChar*)"TAPE-INDEX";
    allowedValues[index++] = (TChar*)"FRAME";
    param = new OpenHome::Net::ParameterString("Unit", allowedValues, 8);
    iActionSeek->AddInputParameter(param);
    delete[] allowedValues;
    param = new OpenHome::Net::ParameterString("Target");
    iActionSeek->AddInputParameter(param);

    iActionNext = new Action("Next");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionNext->AddInputParameter(param);

    iActionPrevious = new Action("Previous");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionPrevious->AddInputParameter(param);

    iActionSetPlayMode = new Action("SetPlayMode");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionSetPlayMode->AddInputParameter(param);
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"NORMAL";
    param = new OpenHome::Net::ParameterString("NewPlayMode", allowedValues, 1);
    iActionSetPlayMode->AddInputParameter(param);
    delete[] allowedValues;

    iActionSetRecordQualityMode = new Action("SetRecordQualityMode");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionSetRecordQualityMode->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("NewRecordQualityMode");
    iActionSetRecordQualityMode->AddInputParameter(param);

    iActionGetCurrentTransportActions = new Action("GetCurrentTransportActions");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionGetCurrentTransportActions->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Actions");
    iActionGetCurrentTransportActions->AddOutputParameter(param);

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyUpnpOrgAVTransport1Cpp::LastChangePropertyChanged);
    iLastChange = new PropertyString(aDevice.Device().GetCpStack().Env(), "LastChange", functor);
    AddProperty(iLastChange);
}

CpProxyUpnpOrgAVTransport1Cpp::~CpProxyUpnpOrgAVTransport1Cpp()
{
    DestroyService();
    delete iActionSetAVTransportURI;
    delete iActionSetNextAVTransportURI;
    delete iActionGetMediaInfo;
    delete iActionGetTransportInfo;
    delete iActionGetPositionInfo;
    delete iActionGetDeviceCapabilities;
    delete iActionGetTransportSettings;
    delete iActionStop;
    delete iActionPlay;
    delete iActionPause;
    delete iActionRecord;
    delete iActionSeek;
    delete iActionNext;
    delete iActionPrevious;
    delete iActionSetPlayMode;
    delete iActionSetRecordQualityMode;
    delete iActionGetCurrentTransportActions;
}

void CpProxyUpnpOrgAVTransport1Cpp::SyncSetAVTransportURI(uint32_t aInstanceID, const std::string& aCurrentURI, const std::string& aCurrentURIMetaData)
{
    SyncSetAVTransportURIUpnpOrgAVTransport1Cpp sync(*this);
    BeginSetAVTransportURI(aInstanceID, aCurrentURI, aCurrentURIMetaData, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport1Cpp::BeginSetAVTransportURI(uint32_t aInstanceID, const std::string& aCurrentURI, const std::string& aCurrentURIMetaData, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetAVTransportURI, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetAVTransportURI->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    {
        Brn buf((const TByte*)aCurrentURI.c_str(), (TUint)aCurrentURI.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aCurrentURIMetaData.c_str(), (TUint)aCurrentURIMetaData.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgAVTransport1Cpp::EndSetAVTransportURI(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetAVTransportURI"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgAVTransport1Cpp::SyncSetNextAVTransportURI(uint32_t aInstanceID, const std::string& aNextURI, const std::string& aNextURIMetaData)
{
    SyncSetNextAVTransportURIUpnpOrgAVTransport1Cpp sync(*this);
    BeginSetNextAVTransportURI(aInstanceID, aNextURI, aNextURIMetaData, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport1Cpp::BeginSetNextAVTransportURI(uint32_t aInstanceID, const std::string& aNextURI, const std::string& aNextURIMetaData, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetNextAVTransportURI, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetNextAVTransportURI->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    {
        Brn buf((const TByte*)aNextURI.c_str(), (TUint)aNextURI.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aNextURIMetaData.c_str(), (TUint)aNextURIMetaData.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgAVTransport1Cpp::EndSetNextAVTransportURI(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetNextAVTransportURI"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgAVTransport1Cpp::SyncGetMediaInfo(uint32_t aInstanceID, uint32_t& aNrTracks, std::string& aMediaDuration, std::string& aCurrentURI, std::string& aCurrentURIMetaData, std::string& aNextURI, std::string& aNextURIMetaData, std::string& aPlayMedium, std::string& aRecordMedium, std::string& aWriteStatus)
{
    SyncGetMediaInfoUpnpOrgAVTransport1Cpp sync(*this, aNrTracks, aMediaDuration, aCurrentURI, aCurrentURIMetaData, aNextURI, aNextURIMetaData, aPlayMedium, aRecordMedium, aWriteStatus);
    BeginGetMediaInfo(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport1Cpp::BeginGetMediaInfo(uint32_t aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetMediaInfo, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetMediaInfo->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetMediaInfo->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgAVTransport1Cpp::EndGetMediaInfo(IAsync& aAsync, uint32_t& aNrTracks, std::string& aMediaDuration, std::string& aCurrentURI, std::string& aCurrentURIMetaData, std::string& aNextURI, std::string& aNextURIMetaData, std::string& aPlayMedium, std::string& aRecordMedium, std::string& aWriteStatus)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetMediaInfo"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aNrTracks = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aMediaDuration.assign((const char*)val.Ptr(), val.Bytes());
    }
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aCurrentURI.assign((const char*)val.Ptr(), val.Bytes());
    }
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aCurrentURIMetaData.assign((const char*)val.Ptr(), val.Bytes());
    }
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aNextURI.assign((const char*)val.Ptr(), val.Bytes());
    }
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aNextURIMetaData.assign((const char*)val.Ptr(), val.Bytes());
    }
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aPlayMedium.assign((const char*)val.Ptr(), val.Bytes());
    }
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aRecordMedium.assign((const char*)val.Ptr(), val.Bytes());
    }
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aWriteStatus.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyUpnpOrgAVTransport1Cpp::SyncGetTransportInfo(uint32_t aInstanceID, std::string& aCurrentTransportState, std::string& aCurrentTransportStatus, std::string& aCurrentSpeed)
{
    SyncGetTransportInfoUpnpOrgAVTransport1Cpp sync(*this, aCurrentTransportState, aCurrentTransportStatus, aCurrentSpeed);
    BeginGetTransportInfo(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport1Cpp::BeginGetTransportInfo(uint32_t aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetTransportInfo, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetTransportInfo->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetTransportInfo->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgAVTransport1Cpp::EndGetTransportInfo(IAsync& aAsync, std::string& aCurrentTransportState, std::string& aCurrentTransportStatus, std::string& aCurrentSpeed)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetTransportInfo"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aCurrentTransportState.assign((const char*)val.Ptr(), val.Bytes());
    }
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aCurrentTransportStatus.assign((const char*)val.Ptr(), val.Bytes());
    }
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aCurrentSpeed.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyUpnpOrgAVTransport1Cpp::SyncGetPositionInfo(uint32_t aInstanceID, uint32_t& aTrack, std::string& aTrackDuration, std::string& aTrackMetaData, std::string& aTrackURI, std::string& aRelTime, std::string& aAbsTime, int32_t& aRelCount, int32_t& aAbsCount)
{
    SyncGetPositionInfoUpnpOrgAVTransport1Cpp sync(*this, aTrack, aTrackDuration, aTrackMetaData, aTrackURI, aRelTime, aAbsTime, aRelCount, aAbsCount);
    BeginGetPositionInfo(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport1Cpp::BeginGetPositionInfo(uint32_t aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetPositionInfo, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetPositionInfo->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetPositionInfo->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentInt(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentInt(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgAVTransport1Cpp::EndGetPositionInfo(IAsync& aAsync, uint32_t& aTrack, std::string& aTrackDuration, std::string& aTrackMetaData, std::string& aTrackURI, std::string& aRelTime, std::string& aAbsTime, int32_t& aRelCount, int32_t& aAbsCount)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetPositionInfo"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aTrack = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aTrackDuration.assign((const char*)val.Ptr(), val.Bytes());
    }
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aTrackMetaData.assign((const char*)val.Ptr(), val.Bytes());
    }
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aTrackURI.assign((const char*)val.Ptr(), val.Bytes());
    }
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aRelTime.assign((const char*)val.Ptr(), val.Bytes());
    }
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aAbsTime.assign((const char*)val.Ptr(), val.Bytes());
    }
    aRelCount = ((ArgumentInt*)invocation.OutputArguments()[index++])->Value();
    aAbsCount = ((ArgumentInt*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgAVTransport1Cpp::SyncGetDeviceCapabilities(uint32_t aInstanceID, std::string& aPlayMedia, std::string& aRecMedia, std::string& aRecQualityModes)
{
    SyncGetDeviceCapabilitiesUpnpOrgAVTransport1Cpp sync(*this, aPlayMedia, aRecMedia, aRecQualityModes);
    BeginGetDeviceCapabilities(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport1Cpp::BeginGetDeviceCapabilities(uint32_t aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetDeviceCapabilities, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetDeviceCapabilities->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetDeviceCapabilities->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgAVTransport1Cpp::EndGetDeviceCapabilities(IAsync& aAsync, std::string& aPlayMedia, std::string& aRecMedia, std::string& aRecQualityModes)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetDeviceCapabilities"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aPlayMedia.assign((const char*)val.Ptr(), val.Bytes());
    }
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aRecMedia.assign((const char*)val.Ptr(), val.Bytes());
    }
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aRecQualityModes.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyUpnpOrgAVTransport1Cpp::SyncGetTransportSettings(uint32_t aInstanceID, std::string& aPlayMode, std::string& aRecQualityMode)
{
    SyncGetTransportSettingsUpnpOrgAVTransport1Cpp sync(*this, aPlayMode, aRecQualityMode);
    BeginGetTransportSettings(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport1Cpp::BeginGetTransportSettings(uint32_t aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetTransportSettings, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetTransportSettings->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetTransportSettings->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgAVTransport1Cpp::EndGetTransportSettings(IAsync& aAsync, std::string& aPlayMode, std::string& aRecQualityMode)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetTransportSettings"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aPlayMode.assign((const char*)val.Ptr(), val.Bytes());
    }
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aRecQualityMode.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyUpnpOrgAVTransport1Cpp::SyncStop(uint32_t aInstanceID)
{
    SyncStopUpnpOrgAVTransport1Cpp sync(*this);
    BeginStop(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport1Cpp::BeginStop(uint32_t aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionStop, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionStop->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgAVTransport1Cpp::EndStop(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Stop"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgAVTransport1Cpp::SyncPlay(uint32_t aInstanceID, const std::string& aSpeed)
{
    SyncPlayUpnpOrgAVTransport1Cpp sync(*this);
    BeginPlay(aInstanceID, aSpeed, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport1Cpp::BeginPlay(uint32_t aInstanceID, const std::string& aSpeed, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionPlay, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionPlay->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    {
        Brn buf((const TByte*)aSpeed.c_str(), (TUint)aSpeed.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgAVTransport1Cpp::EndPlay(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Play"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgAVTransport1Cpp::SyncPause(uint32_t aInstanceID)
{
    SyncPauseUpnpOrgAVTransport1Cpp sync(*this);
    BeginPause(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport1Cpp::BeginPause(uint32_t aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionPause, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionPause->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgAVTransport1Cpp::EndPause(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Pause"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgAVTransport1Cpp::SyncRecord(uint32_t aInstanceID)
{
    SyncRecordUpnpOrgAVTransport1Cpp sync(*this);
    BeginRecord(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport1Cpp::BeginRecord(uint32_t aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionRecord, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionRecord->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgAVTransport1Cpp::EndRecord(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Record"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgAVTransport1Cpp::SyncSeek(uint32_t aInstanceID, const std::string& aUnit, const std::string& aTarget)
{
    SyncSeekUpnpOrgAVTransport1Cpp sync(*this);
    BeginSeek(aInstanceID, aUnit, aTarget, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport1Cpp::BeginSeek(uint32_t aInstanceID, const std::string& aUnit, const std::string& aTarget, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSeek, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSeek->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    {
        Brn buf((const TByte*)aUnit.c_str(), (TUint)aUnit.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aTarget.c_str(), (TUint)aTarget.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgAVTransport1Cpp::EndSeek(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Seek"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgAVTransport1Cpp::SyncNext(uint32_t aInstanceID)
{
    SyncNextUpnpOrgAVTransport1Cpp sync(*this);
    BeginNext(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport1Cpp::BeginNext(uint32_t aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionNext, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionNext->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgAVTransport1Cpp::EndNext(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Next"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgAVTransport1Cpp::SyncPrevious(uint32_t aInstanceID)
{
    SyncPreviousUpnpOrgAVTransport1Cpp sync(*this);
    BeginPrevious(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport1Cpp::BeginPrevious(uint32_t aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionPrevious, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionPrevious->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgAVTransport1Cpp::EndPrevious(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Previous"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgAVTransport1Cpp::SyncSetPlayMode(uint32_t aInstanceID, const std::string& aNewPlayMode)
{
    SyncSetPlayModeUpnpOrgAVTransport1Cpp sync(*this);
    BeginSetPlayMode(aInstanceID, aNewPlayMode, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport1Cpp::BeginSetPlayMode(uint32_t aInstanceID, const std::string& aNewPlayMode, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetPlayMode, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetPlayMode->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    {
        Brn buf((const TByte*)aNewPlayMode.c_str(), (TUint)aNewPlayMode.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgAVTransport1Cpp::EndSetPlayMode(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetPlayMode"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgAVTransport1Cpp::SyncSetRecordQualityMode(uint32_t aInstanceID, const std::string& aNewRecordQualityMode)
{
    SyncSetRecordQualityModeUpnpOrgAVTransport1Cpp sync(*this);
    BeginSetRecordQualityMode(aInstanceID, aNewRecordQualityMode, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport1Cpp::BeginSetRecordQualityMode(uint32_t aInstanceID, const std::string& aNewRecordQualityMode, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetRecordQualityMode, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetRecordQualityMode->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    {
        Brn buf((const TByte*)aNewRecordQualityMode.c_str(), (TUint)aNewRecordQualityMode.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgAVTransport1Cpp::EndSetRecordQualityMode(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetRecordQualityMode"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgAVTransport1Cpp::SyncGetCurrentTransportActions(uint32_t aInstanceID, std::string& aActions)
{
    SyncGetCurrentTransportActionsUpnpOrgAVTransport1Cpp sync(*this, aActions);
    BeginGetCurrentTransportActions(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport1Cpp::BeginGetCurrentTransportActions(uint32_t aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetCurrentTransportActions, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetCurrentTransportActions->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetCurrentTransportActions->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgAVTransport1Cpp::EndGetCurrentTransportActions(IAsync& aAsync, std::string& aActions)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetCurrentTransportActions"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aActions.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyUpnpOrgAVTransport1Cpp::SetPropertyLastChangeChanged(Functor& aFunctor)
{
    iLock->Wait();
    iLastChangeChanged = aFunctor;
    iLock->Signal();
}

void CpProxyUpnpOrgAVTransport1Cpp::PropertyLastChange(std::string& aLastChange) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iLastChange->Value();
    aLastChange.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyUpnpOrgAVTransport1Cpp::LastChangePropertyChanged()
{
    ReportEvent(iLastChangeChanged);
}

