#include <Std/CpUpnpOrgAVTransport1.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Buffer.h>
#include <Std/CpDevice.h>

#include <string>

using namespace Zapp;


class SyncSetAVTransportURIUpnpOrgAVTransport1Cpp : public SyncProxyAction
{
public:
    SyncSetAVTransportURIUpnpOrgAVTransport1Cpp(CpProxyUpnpOrgAVTransport1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport1Cpp& iService;
};

SyncSetAVTransportURIUpnpOrgAVTransport1Cpp::SyncSetAVTransportURIUpnpOrgAVTransport1Cpp(CpProxyUpnpOrgAVTransport1Cpp& aService)
    : iService(aService)
{
}

void SyncSetAVTransportURIUpnpOrgAVTransport1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetAVTransportURI(aAsync);
}


class SyncSetNextAVTransportURIUpnpOrgAVTransport1Cpp : public SyncProxyAction
{
public:
    SyncSetNextAVTransportURIUpnpOrgAVTransport1Cpp(CpProxyUpnpOrgAVTransport1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport1Cpp& iService;
};

SyncSetNextAVTransportURIUpnpOrgAVTransport1Cpp::SyncSetNextAVTransportURIUpnpOrgAVTransport1Cpp(CpProxyUpnpOrgAVTransport1Cpp& aService)
    : iService(aService)
{
}

void SyncSetNextAVTransportURIUpnpOrgAVTransport1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetNextAVTransportURI(aAsync);
}


class SyncGetMediaInfoUpnpOrgAVTransport1Cpp : public SyncProxyAction
{
public:
    SyncGetMediaInfoUpnpOrgAVTransport1Cpp(CpProxyUpnpOrgAVTransport1Cpp& aService, uint32_t& aNrTracks, std::string& aMediaDuration, std::string& aCurrentURI, std::string& aCurrentURIMetaData, std::string& aNextURI, std::string& aNextURIMetaData, std::string& aPlayMedium, std::string& aRecordMedium, std::string& aWriteStatus);
    virtual void CompleteRequest(IAsync& aAsync);
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

SyncGetMediaInfoUpnpOrgAVTransport1Cpp::SyncGetMediaInfoUpnpOrgAVTransport1Cpp(CpProxyUpnpOrgAVTransport1Cpp& aService, uint32_t& aNrTracks, std::string& aMediaDuration, std::string& aCurrentURI, std::string& aCurrentURIMetaData, std::string& aNextURI, std::string& aNextURIMetaData, std::string& aPlayMedium, std::string& aRecordMedium, std::string& aWriteStatus)
    : iService(aService)
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
    SyncGetTransportInfoUpnpOrgAVTransport1Cpp(CpProxyUpnpOrgAVTransport1Cpp& aService, std::string& aCurrentTransportState, std::string& aCurrentTransportStatus, std::string& aCurrentSpeed);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport1Cpp& iService;
    std::string& iCurrentTransportState;
    std::string& iCurrentTransportStatus;
    std::string& iCurrentSpeed;
};

SyncGetTransportInfoUpnpOrgAVTransport1Cpp::SyncGetTransportInfoUpnpOrgAVTransport1Cpp(CpProxyUpnpOrgAVTransport1Cpp& aService, std::string& aCurrentTransportState, std::string& aCurrentTransportStatus, std::string& aCurrentSpeed)
    : iService(aService)
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
    SyncGetPositionInfoUpnpOrgAVTransport1Cpp(CpProxyUpnpOrgAVTransport1Cpp& aService, uint32_t& aTrack, std::string& aTrackDuration, std::string& aTrackMetaData, std::string& aTrackURI, std::string& aRelTime, std::string& aAbsTime, int32_t& aRelCount, int32_t& aAbsCount);
    virtual void CompleteRequest(IAsync& aAsync);
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

SyncGetPositionInfoUpnpOrgAVTransport1Cpp::SyncGetPositionInfoUpnpOrgAVTransport1Cpp(CpProxyUpnpOrgAVTransport1Cpp& aService, uint32_t& aTrack, std::string& aTrackDuration, std::string& aTrackMetaData, std::string& aTrackURI, std::string& aRelTime, std::string& aAbsTime, int32_t& aRelCount, int32_t& aAbsCount)
    : iService(aService)
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
    SyncGetDeviceCapabilitiesUpnpOrgAVTransport1Cpp(CpProxyUpnpOrgAVTransport1Cpp& aService, std::string& aPlayMedia, std::string& aRecMedia, std::string& aRecQualityModes);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport1Cpp& iService;
    std::string& iPlayMedia;
    std::string& iRecMedia;
    std::string& iRecQualityModes;
};

SyncGetDeviceCapabilitiesUpnpOrgAVTransport1Cpp::SyncGetDeviceCapabilitiesUpnpOrgAVTransport1Cpp(CpProxyUpnpOrgAVTransport1Cpp& aService, std::string& aPlayMedia, std::string& aRecMedia, std::string& aRecQualityModes)
    : iService(aService)
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
    SyncGetTransportSettingsUpnpOrgAVTransport1Cpp(CpProxyUpnpOrgAVTransport1Cpp& aService, std::string& aPlayMode, std::string& aRecQualityMode);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport1Cpp& iService;
    std::string& iPlayMode;
    std::string& iRecQualityMode;
};

SyncGetTransportSettingsUpnpOrgAVTransport1Cpp::SyncGetTransportSettingsUpnpOrgAVTransport1Cpp(CpProxyUpnpOrgAVTransport1Cpp& aService, std::string& aPlayMode, std::string& aRecQualityMode)
    : iService(aService)
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
    SyncStopUpnpOrgAVTransport1Cpp(CpProxyUpnpOrgAVTransport1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport1Cpp& iService;
};

SyncStopUpnpOrgAVTransport1Cpp::SyncStopUpnpOrgAVTransport1Cpp(CpProxyUpnpOrgAVTransport1Cpp& aService)
    : iService(aService)
{
}

void SyncStopUpnpOrgAVTransport1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndStop(aAsync);
}


class SyncPlayUpnpOrgAVTransport1Cpp : public SyncProxyAction
{
public:
    SyncPlayUpnpOrgAVTransport1Cpp(CpProxyUpnpOrgAVTransport1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport1Cpp& iService;
};

SyncPlayUpnpOrgAVTransport1Cpp::SyncPlayUpnpOrgAVTransport1Cpp(CpProxyUpnpOrgAVTransport1Cpp& aService)
    : iService(aService)
{
}

void SyncPlayUpnpOrgAVTransport1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndPlay(aAsync);
}


class SyncPauseUpnpOrgAVTransport1Cpp : public SyncProxyAction
{
public:
    SyncPauseUpnpOrgAVTransport1Cpp(CpProxyUpnpOrgAVTransport1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport1Cpp& iService;
};

SyncPauseUpnpOrgAVTransport1Cpp::SyncPauseUpnpOrgAVTransport1Cpp(CpProxyUpnpOrgAVTransport1Cpp& aService)
    : iService(aService)
{
}

void SyncPauseUpnpOrgAVTransport1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndPause(aAsync);
}


class SyncRecordUpnpOrgAVTransport1Cpp : public SyncProxyAction
{
public:
    SyncRecordUpnpOrgAVTransport1Cpp(CpProxyUpnpOrgAVTransport1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport1Cpp& iService;
};

SyncRecordUpnpOrgAVTransport1Cpp::SyncRecordUpnpOrgAVTransport1Cpp(CpProxyUpnpOrgAVTransport1Cpp& aService)
    : iService(aService)
{
}

void SyncRecordUpnpOrgAVTransport1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndRecord(aAsync);
}


class SyncSeekUpnpOrgAVTransport1Cpp : public SyncProxyAction
{
public:
    SyncSeekUpnpOrgAVTransport1Cpp(CpProxyUpnpOrgAVTransport1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport1Cpp& iService;
};

SyncSeekUpnpOrgAVTransport1Cpp::SyncSeekUpnpOrgAVTransport1Cpp(CpProxyUpnpOrgAVTransport1Cpp& aService)
    : iService(aService)
{
}

void SyncSeekUpnpOrgAVTransport1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSeek(aAsync);
}


class SyncNextUpnpOrgAVTransport1Cpp : public SyncProxyAction
{
public:
    SyncNextUpnpOrgAVTransport1Cpp(CpProxyUpnpOrgAVTransport1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport1Cpp& iService;
};

SyncNextUpnpOrgAVTransport1Cpp::SyncNextUpnpOrgAVTransport1Cpp(CpProxyUpnpOrgAVTransport1Cpp& aService)
    : iService(aService)
{
}

void SyncNextUpnpOrgAVTransport1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndNext(aAsync);
}


class SyncPreviousUpnpOrgAVTransport1Cpp : public SyncProxyAction
{
public:
    SyncPreviousUpnpOrgAVTransport1Cpp(CpProxyUpnpOrgAVTransport1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport1Cpp& iService;
};

SyncPreviousUpnpOrgAVTransport1Cpp::SyncPreviousUpnpOrgAVTransport1Cpp(CpProxyUpnpOrgAVTransport1Cpp& aService)
    : iService(aService)
{
}

void SyncPreviousUpnpOrgAVTransport1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndPrevious(aAsync);
}


class SyncSetPlayModeUpnpOrgAVTransport1Cpp : public SyncProxyAction
{
public:
    SyncSetPlayModeUpnpOrgAVTransport1Cpp(CpProxyUpnpOrgAVTransport1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport1Cpp& iService;
};

SyncSetPlayModeUpnpOrgAVTransport1Cpp::SyncSetPlayModeUpnpOrgAVTransport1Cpp(CpProxyUpnpOrgAVTransport1Cpp& aService)
    : iService(aService)
{
}

void SyncSetPlayModeUpnpOrgAVTransport1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetPlayMode(aAsync);
}


class SyncSetRecordQualityModeUpnpOrgAVTransport1Cpp : public SyncProxyAction
{
public:
    SyncSetRecordQualityModeUpnpOrgAVTransport1Cpp(CpProxyUpnpOrgAVTransport1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport1Cpp& iService;
};

SyncSetRecordQualityModeUpnpOrgAVTransport1Cpp::SyncSetRecordQualityModeUpnpOrgAVTransport1Cpp(CpProxyUpnpOrgAVTransport1Cpp& aService)
    : iService(aService)
{
}

void SyncSetRecordQualityModeUpnpOrgAVTransport1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetRecordQualityMode(aAsync);
}


class SyncGetCurrentTransportActionsUpnpOrgAVTransport1Cpp : public SyncProxyAction
{
public:
    SyncGetCurrentTransportActionsUpnpOrgAVTransport1Cpp(CpProxyUpnpOrgAVTransport1Cpp& aService, std::string& aActions);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport1Cpp& iService;
    std::string& iActions;
};

SyncGetCurrentTransportActionsUpnpOrgAVTransport1Cpp::SyncGetCurrentTransportActionsUpnpOrgAVTransport1Cpp(CpProxyUpnpOrgAVTransport1Cpp& aService, std::string& aActions)
    : iService(aService)
    , iActions(aActions)
{
}

void SyncGetCurrentTransportActionsUpnpOrgAVTransport1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetCurrentTransportActions(aAsync, iActions);
}


CpProxyUpnpOrgAVTransport1Cpp::CpProxyUpnpOrgAVTransport1Cpp(CpDeviceCpp& aDevice)
{
    iService = new CpiService("schemas-upnp-org", "AVTransport", 1, aDevice.Device());
    Zapp::Parameter* param;
    TChar** allowedValues;
    TUint index;

    iActionSetAVTransportURI = new Action("SetAVTransportURI");
    param = new Zapp::ParameterUint("InstanceID");
    iActionSetAVTransportURI->AddInputParameter(param);
    param = new Zapp::ParameterString("CurrentURI");
    iActionSetAVTransportURI->AddInputParameter(param);
    param = new Zapp::ParameterString("CurrentURIMetaData");
    iActionSetAVTransportURI->AddInputParameter(param);

    iActionSetNextAVTransportURI = new Action("SetNextAVTransportURI");
    param = new Zapp::ParameterUint("InstanceID");
    iActionSetNextAVTransportURI->AddInputParameter(param);
    param = new Zapp::ParameterString("NextURI");
    iActionSetNextAVTransportURI->AddInputParameter(param);
    param = new Zapp::ParameterString("NextURIMetaData");
    iActionSetNextAVTransportURI->AddInputParameter(param);

    iActionGetMediaInfo = new Action("GetMediaInfo");
    param = new Zapp::ParameterUint("InstanceID");
    iActionGetMediaInfo->AddInputParameter(param);
    param = new Zapp::ParameterUint("NrTracks", 0, 0);
    iActionGetMediaInfo->AddOutputParameter(param);
    param = new Zapp::ParameterString("MediaDuration");
    iActionGetMediaInfo->AddOutputParameter(param);
    param = new Zapp::ParameterString("CurrentURI");
    iActionGetMediaInfo->AddOutputParameter(param);
    param = new Zapp::ParameterString("CurrentURIMetaData");
    iActionGetMediaInfo->AddOutputParameter(param);
    param = new Zapp::ParameterString("NextURI");
    iActionGetMediaInfo->AddOutputParameter(param);
    param = new Zapp::ParameterString("NextURIMetaData");
    iActionGetMediaInfo->AddOutputParameter(param);
    param = new Zapp::ParameterString("PlayMedium");
    iActionGetMediaInfo->AddOutputParameter(param);
    param = new Zapp::ParameterString("RecordMedium");
    iActionGetMediaInfo->AddOutputParameter(param);
    param = new Zapp::ParameterString("WriteStatus");
    iActionGetMediaInfo->AddOutputParameter(param);

    iActionGetTransportInfo = new Action("GetTransportInfo");
    param = new Zapp::ParameterUint("InstanceID");
    iActionGetTransportInfo->AddInputParameter(param);
    index = 0;
    allowedValues = new TChar*[2];
    allowedValues[index++] = (TChar*)"STOPPED";
    allowedValues[index++] = (TChar*)"PLAYING";
    param = new Zapp::ParameterString("CurrentTransportState", allowedValues, 2);
    iActionGetTransportInfo->AddOutputParameter(param);
    delete[] allowedValues;
    index = 0;
    allowedValues = new TChar*[2];
    allowedValues[index++] = (TChar*)"OK";
    allowedValues[index++] = (TChar*)"ERROR_OCCURRED";
    param = new Zapp::ParameterString("CurrentTransportStatus", allowedValues, 2);
    iActionGetTransportInfo->AddOutputParameter(param);
    delete[] allowedValues;
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"1";
    param = new Zapp::ParameterString("CurrentSpeed", allowedValues, 1);
    iActionGetTransportInfo->AddOutputParameter(param);
    delete[] allowedValues;

    iActionGetPositionInfo = new Action("GetPositionInfo");
    param = new Zapp::ParameterUint("InstanceID");
    iActionGetPositionInfo->AddInputParameter(param);
    param = new Zapp::ParameterUint("Track", 0, 0, 1);
    iActionGetPositionInfo->AddOutputParameter(param);
    param = new Zapp::ParameterString("TrackDuration");
    iActionGetPositionInfo->AddOutputParameter(param);
    param = new Zapp::ParameterString("TrackMetaData");
    iActionGetPositionInfo->AddOutputParameter(param);
    param = new Zapp::ParameterString("TrackURI");
    iActionGetPositionInfo->AddOutputParameter(param);
    param = new Zapp::ParameterString("RelTime");
    iActionGetPositionInfo->AddOutputParameter(param);
    param = new Zapp::ParameterString("AbsTime");
    iActionGetPositionInfo->AddOutputParameter(param);
    param = new Zapp::ParameterInt("RelCount");
    iActionGetPositionInfo->AddOutputParameter(param);
    param = new Zapp::ParameterInt("AbsCount");
    iActionGetPositionInfo->AddOutputParameter(param);

    iActionGetDeviceCapabilities = new Action("GetDeviceCapabilities");
    param = new Zapp::ParameterUint("InstanceID");
    iActionGetDeviceCapabilities->AddInputParameter(param);
    param = new Zapp::ParameterString("PlayMedia");
    iActionGetDeviceCapabilities->AddOutputParameter(param);
    param = new Zapp::ParameterString("RecMedia");
    iActionGetDeviceCapabilities->AddOutputParameter(param);
    param = new Zapp::ParameterString("RecQualityModes");
    iActionGetDeviceCapabilities->AddOutputParameter(param);

    iActionGetTransportSettings = new Action("GetTransportSettings");
    param = new Zapp::ParameterUint("InstanceID");
    iActionGetTransportSettings->AddInputParameter(param);
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"NORMAL";
    param = new Zapp::ParameterString("PlayMode", allowedValues, 1);
    iActionGetTransportSettings->AddOutputParameter(param);
    delete[] allowedValues;
    param = new Zapp::ParameterString("RecQualityMode");
    iActionGetTransportSettings->AddOutputParameter(param);

    iActionStop = new Action("Stop");
    param = new Zapp::ParameterUint("InstanceID");
    iActionStop->AddInputParameter(param);

    iActionPlay = new Action("Play");
    param = new Zapp::ParameterUint("InstanceID");
    iActionPlay->AddInputParameter(param);
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"1";
    param = new Zapp::ParameterString("Speed", allowedValues, 1);
    iActionPlay->AddInputParameter(param);
    delete[] allowedValues;

    iActionPause = new Action("Pause");
    param = new Zapp::ParameterUint("InstanceID");
    iActionPause->AddInputParameter(param);

    iActionRecord = new Action("Record");
    param = new Zapp::ParameterUint("InstanceID");
    iActionRecord->AddInputParameter(param);

    iActionSeek = new Action("Seek");
    param = new Zapp::ParameterUint("InstanceID");
    iActionSeek->AddInputParameter(param);
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"TRACK_NR";
    param = new Zapp::ParameterString("Unit", allowedValues, 1);
    iActionSeek->AddInputParameter(param);
    delete[] allowedValues;
    param = new Zapp::ParameterString("Target");
    iActionSeek->AddInputParameter(param);

    iActionNext = new Action("Next");
    param = new Zapp::ParameterUint("InstanceID");
    iActionNext->AddInputParameter(param);

    iActionPrevious = new Action("Previous");
    param = new Zapp::ParameterUint("InstanceID");
    iActionPrevious->AddInputParameter(param);

    iActionSetPlayMode = new Action("SetPlayMode");
    param = new Zapp::ParameterUint("InstanceID");
    iActionSetPlayMode->AddInputParameter(param);
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"NORMAL";
    param = new Zapp::ParameterString("NewPlayMode", allowedValues, 1);
    iActionSetPlayMode->AddInputParameter(param);
    delete[] allowedValues;

    iActionSetRecordQualityMode = new Action("SetRecordQualityMode");
    param = new Zapp::ParameterUint("InstanceID");
    iActionSetRecordQualityMode->AddInputParameter(param);
    param = new Zapp::ParameterString("NewRecordQualityMode");
    iActionSetRecordQualityMode->AddInputParameter(param);

    iActionGetCurrentTransportActions = new Action("GetCurrentTransportActions");
    param = new Zapp::ParameterUint("InstanceID");
    iActionGetCurrentTransportActions->AddInputParameter(param);
    param = new Zapp::ParameterString("Actions");
    iActionGetCurrentTransportActions->AddOutputParameter(param);

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyUpnpOrgAVTransport1Cpp::LastChangePropertyChanged);
    iLastChange = new PropertyString("LastChange", functor);
    iService->AddProperty(iLastChange);
}

CpProxyUpnpOrgAVTransport1Cpp::~CpProxyUpnpOrgAVTransport1Cpp()
{
    delete iService;
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
        Brn buf((const TByte*)aCurrentURI.c_str(), aCurrentURI.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aCurrentURIMetaData.c_str(), aCurrentURIMetaData.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    invocation->Invoke();
}

void CpProxyUpnpOrgAVTransport1Cpp::EndSetAVTransportURI(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetAVTransportURI"));

    if (invocation.Error()) {
        THROW(ProxyError);
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
        Brn buf((const TByte*)aNextURI.c_str(), aNextURI.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aNextURIMetaData.c_str(), aNextURIMetaData.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    invocation->Invoke();
}

void CpProxyUpnpOrgAVTransport1Cpp::EndSetNextAVTransportURI(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetNextAVTransportURI"));

    if (invocation.Error()) {
        THROW(ProxyError);
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
    invocation->Invoke();
}

void CpProxyUpnpOrgAVTransport1Cpp::EndGetMediaInfo(IAsync& aAsync, uint32_t& aNrTracks, std::string& aMediaDuration, std::string& aCurrentURI, std::string& aCurrentURIMetaData, std::string& aNextURI, std::string& aNextURIMetaData, std::string& aPlayMedium, std::string& aRecordMedium, std::string& aWriteStatus)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetMediaInfo"));

    if (invocation.Error()) {
        THROW(ProxyError);
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
    invocation->Invoke();
}

void CpProxyUpnpOrgAVTransport1Cpp::EndGetTransportInfo(IAsync& aAsync, std::string& aCurrentTransportState, std::string& aCurrentTransportStatus, std::string& aCurrentSpeed)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetTransportInfo"));

    if (invocation.Error()) {
        THROW(ProxyError);
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
    invocation->Invoke();
}

void CpProxyUpnpOrgAVTransport1Cpp::EndGetPositionInfo(IAsync& aAsync, uint32_t& aTrack, std::string& aTrackDuration, std::string& aTrackMetaData, std::string& aTrackURI, std::string& aRelTime, std::string& aAbsTime, int32_t& aRelCount, int32_t& aAbsCount)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetPositionInfo"));

    if (invocation.Error()) {
        THROW(ProxyError);
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
    invocation->Invoke();
}

void CpProxyUpnpOrgAVTransport1Cpp::EndGetDeviceCapabilities(IAsync& aAsync, std::string& aPlayMedia, std::string& aRecMedia, std::string& aRecQualityModes)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetDeviceCapabilities"));

    if (invocation.Error()) {
        THROW(ProxyError);
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
    invocation->Invoke();
}

void CpProxyUpnpOrgAVTransport1Cpp::EndGetTransportSettings(IAsync& aAsync, std::string& aPlayMode, std::string& aRecQualityMode)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetTransportSettings"));

    if (invocation.Error()) {
        THROW(ProxyError);
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
    invocation->Invoke();
}

void CpProxyUpnpOrgAVTransport1Cpp::EndStop(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Stop"));

    if (invocation.Error()) {
        THROW(ProxyError);
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
        Brn buf((const TByte*)aSpeed.c_str(), aSpeed.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    invocation->Invoke();
}

void CpProxyUpnpOrgAVTransport1Cpp::EndPlay(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Play"));

    if (invocation.Error()) {
        THROW(ProxyError);
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
    invocation->Invoke();
}

void CpProxyUpnpOrgAVTransport1Cpp::EndPause(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Pause"));

    if (invocation.Error()) {
        THROW(ProxyError);
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
    invocation->Invoke();
}

void CpProxyUpnpOrgAVTransport1Cpp::EndRecord(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Record"));

    if (invocation.Error()) {
        THROW(ProxyError);
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
        Brn buf((const TByte*)aUnit.c_str(), aUnit.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aTarget.c_str(), aTarget.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    invocation->Invoke();
}

void CpProxyUpnpOrgAVTransport1Cpp::EndSeek(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Seek"));

    if (invocation.Error()) {
        THROW(ProxyError);
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
    invocation->Invoke();
}

void CpProxyUpnpOrgAVTransport1Cpp::EndNext(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Next"));

    if (invocation.Error()) {
        THROW(ProxyError);
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
    invocation->Invoke();
}

void CpProxyUpnpOrgAVTransport1Cpp::EndPrevious(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Previous"));

    if (invocation.Error()) {
        THROW(ProxyError);
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
        Brn buf((const TByte*)aNewPlayMode.c_str(), aNewPlayMode.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    invocation->Invoke();
}

void CpProxyUpnpOrgAVTransport1Cpp::EndSetPlayMode(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetPlayMode"));

    if (invocation.Error()) {
        THROW(ProxyError);
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
        Brn buf((const TByte*)aNewRecordQualityMode.c_str(), aNewRecordQualityMode.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    invocation->Invoke();
}

void CpProxyUpnpOrgAVTransport1Cpp::EndSetRecordQualityMode(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetRecordQualityMode"));

    if (invocation.Error()) {
        THROW(ProxyError);
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
    invocation->Invoke();
}

void CpProxyUpnpOrgAVTransport1Cpp::EndGetCurrentTransportActions(IAsync& aAsync, std::string& aActions)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetCurrentTransportActions"));

    if (invocation.Error()) {
        THROW(ProxyError);
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
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iLastChange->Value();
    aLastChange.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyUpnpOrgAVTransport1Cpp::LastChangePropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iLastChangeChanged != NULL) {
        iLastChangeChanged();
    }
}

