#include <Core/CpUpnpOrgAVTransport1.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Core/CpDevice.h>

using namespace Zapp;


class SyncSetAVTransportURIUpnpOrgAVTransport1 : public SyncProxyAction
{
public:
    SyncSetAVTransportURIUpnpOrgAVTransport1(CpProxyUpnpOrgAVTransport1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport1& iService;
};

SyncSetAVTransportURIUpnpOrgAVTransport1::SyncSetAVTransportURIUpnpOrgAVTransport1(CpProxyUpnpOrgAVTransport1& aService)
    : iService(aService)
{
}

void SyncSetAVTransportURIUpnpOrgAVTransport1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetAVTransportURI(aAsync);
}


class SyncSetNextAVTransportURIUpnpOrgAVTransport1 : public SyncProxyAction
{
public:
    SyncSetNextAVTransportURIUpnpOrgAVTransport1(CpProxyUpnpOrgAVTransport1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport1& iService;
};

SyncSetNextAVTransportURIUpnpOrgAVTransport1::SyncSetNextAVTransportURIUpnpOrgAVTransport1(CpProxyUpnpOrgAVTransport1& aService)
    : iService(aService)
{
}

void SyncSetNextAVTransportURIUpnpOrgAVTransport1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetNextAVTransportURI(aAsync);
}


class SyncGetMediaInfoUpnpOrgAVTransport1 : public SyncProxyAction
{
public:
    SyncGetMediaInfoUpnpOrgAVTransport1(CpProxyUpnpOrgAVTransport1& aService, TUint& aNrTracks, Brh& aMediaDuration, Brh& aCurrentURI, Brh& aCurrentURIMetaData, Brh& aNextURI, Brh& aNextURIMetaData, Brh& aPlayMedium, Brh& aRecordMedium, Brh& aWriteStatus);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport1& iService;
    TUint& iNrTracks;
    Brh& iMediaDuration;
    Brh& iCurrentURI;
    Brh& iCurrentURIMetaData;
    Brh& iNextURI;
    Brh& iNextURIMetaData;
    Brh& iPlayMedium;
    Brh& iRecordMedium;
    Brh& iWriteStatus;
};

SyncGetMediaInfoUpnpOrgAVTransport1::SyncGetMediaInfoUpnpOrgAVTransport1(CpProxyUpnpOrgAVTransport1& aService, TUint& aNrTracks, Brh& aMediaDuration, Brh& aCurrentURI, Brh& aCurrentURIMetaData, Brh& aNextURI, Brh& aNextURIMetaData, Brh& aPlayMedium, Brh& aRecordMedium, Brh& aWriteStatus)
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

void SyncGetMediaInfoUpnpOrgAVTransport1::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetMediaInfo(aAsync, iNrTracks, iMediaDuration, iCurrentURI, iCurrentURIMetaData, iNextURI, iNextURIMetaData, iPlayMedium, iRecordMedium, iWriteStatus);
}


class SyncGetTransportInfoUpnpOrgAVTransport1 : public SyncProxyAction
{
public:
    SyncGetTransportInfoUpnpOrgAVTransport1(CpProxyUpnpOrgAVTransport1& aService, Brh& aCurrentTransportState, Brh& aCurrentTransportStatus, Brh& aCurrentSpeed);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport1& iService;
    Brh& iCurrentTransportState;
    Brh& iCurrentTransportStatus;
    Brh& iCurrentSpeed;
};

SyncGetTransportInfoUpnpOrgAVTransport1::SyncGetTransportInfoUpnpOrgAVTransport1(CpProxyUpnpOrgAVTransport1& aService, Brh& aCurrentTransportState, Brh& aCurrentTransportStatus, Brh& aCurrentSpeed)
    : iService(aService)
    , iCurrentTransportState(aCurrentTransportState)
    , iCurrentTransportStatus(aCurrentTransportStatus)
    , iCurrentSpeed(aCurrentSpeed)
{
}

void SyncGetTransportInfoUpnpOrgAVTransport1::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetTransportInfo(aAsync, iCurrentTransportState, iCurrentTransportStatus, iCurrentSpeed);
}


class SyncGetPositionInfoUpnpOrgAVTransport1 : public SyncProxyAction
{
public:
    SyncGetPositionInfoUpnpOrgAVTransport1(CpProxyUpnpOrgAVTransport1& aService, TUint& aTrack, Brh& aTrackDuration, Brh& aTrackMetaData, Brh& aTrackURI, Brh& aRelTime, Brh& aAbsTime, TInt& aRelCount, TInt& aAbsCount);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport1& iService;
    TUint& iTrack;
    Brh& iTrackDuration;
    Brh& iTrackMetaData;
    Brh& iTrackURI;
    Brh& iRelTime;
    Brh& iAbsTime;
    TInt& iRelCount;
    TInt& iAbsCount;
};

SyncGetPositionInfoUpnpOrgAVTransport1::SyncGetPositionInfoUpnpOrgAVTransport1(CpProxyUpnpOrgAVTransport1& aService, TUint& aTrack, Brh& aTrackDuration, Brh& aTrackMetaData, Brh& aTrackURI, Brh& aRelTime, Brh& aAbsTime, TInt& aRelCount, TInt& aAbsCount)
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

void SyncGetPositionInfoUpnpOrgAVTransport1::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetPositionInfo(aAsync, iTrack, iTrackDuration, iTrackMetaData, iTrackURI, iRelTime, iAbsTime, iRelCount, iAbsCount);
}


class SyncGetDeviceCapabilitiesUpnpOrgAVTransport1 : public SyncProxyAction
{
public:
    SyncGetDeviceCapabilitiesUpnpOrgAVTransport1(CpProxyUpnpOrgAVTransport1& aService, Brh& aPlayMedia, Brh& aRecMedia, Brh& aRecQualityModes);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport1& iService;
    Brh& iPlayMedia;
    Brh& iRecMedia;
    Brh& iRecQualityModes;
};

SyncGetDeviceCapabilitiesUpnpOrgAVTransport1::SyncGetDeviceCapabilitiesUpnpOrgAVTransport1(CpProxyUpnpOrgAVTransport1& aService, Brh& aPlayMedia, Brh& aRecMedia, Brh& aRecQualityModes)
    : iService(aService)
    , iPlayMedia(aPlayMedia)
    , iRecMedia(aRecMedia)
    , iRecQualityModes(aRecQualityModes)
{
}

void SyncGetDeviceCapabilitiesUpnpOrgAVTransport1::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetDeviceCapabilities(aAsync, iPlayMedia, iRecMedia, iRecQualityModes);
}


class SyncGetTransportSettingsUpnpOrgAVTransport1 : public SyncProxyAction
{
public:
    SyncGetTransportSettingsUpnpOrgAVTransport1(CpProxyUpnpOrgAVTransport1& aService, Brh& aPlayMode, Brh& aRecQualityMode);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport1& iService;
    Brh& iPlayMode;
    Brh& iRecQualityMode;
};

SyncGetTransportSettingsUpnpOrgAVTransport1::SyncGetTransportSettingsUpnpOrgAVTransport1(CpProxyUpnpOrgAVTransport1& aService, Brh& aPlayMode, Brh& aRecQualityMode)
    : iService(aService)
    , iPlayMode(aPlayMode)
    , iRecQualityMode(aRecQualityMode)
{
}

void SyncGetTransportSettingsUpnpOrgAVTransport1::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetTransportSettings(aAsync, iPlayMode, iRecQualityMode);
}


class SyncStopUpnpOrgAVTransport1 : public SyncProxyAction
{
public:
    SyncStopUpnpOrgAVTransport1(CpProxyUpnpOrgAVTransport1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport1& iService;
};

SyncStopUpnpOrgAVTransport1::SyncStopUpnpOrgAVTransport1(CpProxyUpnpOrgAVTransport1& aService)
    : iService(aService)
{
}

void SyncStopUpnpOrgAVTransport1::CompleteRequest(IAsync& aAsync)
{
    iService.EndStop(aAsync);
}


class SyncPlayUpnpOrgAVTransport1 : public SyncProxyAction
{
public:
    SyncPlayUpnpOrgAVTransport1(CpProxyUpnpOrgAVTransport1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport1& iService;
};

SyncPlayUpnpOrgAVTransport1::SyncPlayUpnpOrgAVTransport1(CpProxyUpnpOrgAVTransport1& aService)
    : iService(aService)
{
}

void SyncPlayUpnpOrgAVTransport1::CompleteRequest(IAsync& aAsync)
{
    iService.EndPlay(aAsync);
}


class SyncPauseUpnpOrgAVTransport1 : public SyncProxyAction
{
public:
    SyncPauseUpnpOrgAVTransport1(CpProxyUpnpOrgAVTransport1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport1& iService;
};

SyncPauseUpnpOrgAVTransport1::SyncPauseUpnpOrgAVTransport1(CpProxyUpnpOrgAVTransport1& aService)
    : iService(aService)
{
}

void SyncPauseUpnpOrgAVTransport1::CompleteRequest(IAsync& aAsync)
{
    iService.EndPause(aAsync);
}


class SyncRecordUpnpOrgAVTransport1 : public SyncProxyAction
{
public:
    SyncRecordUpnpOrgAVTransport1(CpProxyUpnpOrgAVTransport1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport1& iService;
};

SyncRecordUpnpOrgAVTransport1::SyncRecordUpnpOrgAVTransport1(CpProxyUpnpOrgAVTransport1& aService)
    : iService(aService)
{
}

void SyncRecordUpnpOrgAVTransport1::CompleteRequest(IAsync& aAsync)
{
    iService.EndRecord(aAsync);
}


class SyncSeekUpnpOrgAVTransport1 : public SyncProxyAction
{
public:
    SyncSeekUpnpOrgAVTransport1(CpProxyUpnpOrgAVTransport1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport1& iService;
};

SyncSeekUpnpOrgAVTransport1::SyncSeekUpnpOrgAVTransport1(CpProxyUpnpOrgAVTransport1& aService)
    : iService(aService)
{
}

void SyncSeekUpnpOrgAVTransport1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSeek(aAsync);
}


class SyncNextUpnpOrgAVTransport1 : public SyncProxyAction
{
public:
    SyncNextUpnpOrgAVTransport1(CpProxyUpnpOrgAVTransport1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport1& iService;
};

SyncNextUpnpOrgAVTransport1::SyncNextUpnpOrgAVTransport1(CpProxyUpnpOrgAVTransport1& aService)
    : iService(aService)
{
}

void SyncNextUpnpOrgAVTransport1::CompleteRequest(IAsync& aAsync)
{
    iService.EndNext(aAsync);
}


class SyncPreviousUpnpOrgAVTransport1 : public SyncProxyAction
{
public:
    SyncPreviousUpnpOrgAVTransport1(CpProxyUpnpOrgAVTransport1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport1& iService;
};

SyncPreviousUpnpOrgAVTransport1::SyncPreviousUpnpOrgAVTransport1(CpProxyUpnpOrgAVTransport1& aService)
    : iService(aService)
{
}

void SyncPreviousUpnpOrgAVTransport1::CompleteRequest(IAsync& aAsync)
{
    iService.EndPrevious(aAsync);
}


class SyncSetPlayModeUpnpOrgAVTransport1 : public SyncProxyAction
{
public:
    SyncSetPlayModeUpnpOrgAVTransport1(CpProxyUpnpOrgAVTransport1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport1& iService;
};

SyncSetPlayModeUpnpOrgAVTransport1::SyncSetPlayModeUpnpOrgAVTransport1(CpProxyUpnpOrgAVTransport1& aService)
    : iService(aService)
{
}

void SyncSetPlayModeUpnpOrgAVTransport1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetPlayMode(aAsync);
}


class SyncSetRecordQualityModeUpnpOrgAVTransport1 : public SyncProxyAction
{
public:
    SyncSetRecordQualityModeUpnpOrgAVTransport1(CpProxyUpnpOrgAVTransport1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport1& iService;
};

SyncSetRecordQualityModeUpnpOrgAVTransport1::SyncSetRecordQualityModeUpnpOrgAVTransport1(CpProxyUpnpOrgAVTransport1& aService)
    : iService(aService)
{
}

void SyncSetRecordQualityModeUpnpOrgAVTransport1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetRecordQualityMode(aAsync);
}


class SyncGetCurrentTransportActionsUpnpOrgAVTransport1 : public SyncProxyAction
{
public:
    SyncGetCurrentTransportActionsUpnpOrgAVTransport1(CpProxyUpnpOrgAVTransport1& aService, Brh& aActions);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport1& iService;
    Brh& iActions;
};

SyncGetCurrentTransportActionsUpnpOrgAVTransport1::SyncGetCurrentTransportActionsUpnpOrgAVTransport1(CpProxyUpnpOrgAVTransport1& aService, Brh& aActions)
    : iService(aService)
    , iActions(aActions)
{
}

void SyncGetCurrentTransportActionsUpnpOrgAVTransport1::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetCurrentTransportActions(aAsync, iActions);
}


CpProxyUpnpOrgAVTransport1::CpProxyUpnpOrgAVTransport1(CpDevice& aDevice)
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
    functor = MakeFunctor(*this, &CpProxyUpnpOrgAVTransport1::LastChangePropertyChanged);
    iLastChange = new PropertyString("LastChange", functor);
    iService->AddProperty(iLastChange);
}

CpProxyUpnpOrgAVTransport1::~CpProxyUpnpOrgAVTransport1()
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

void CpProxyUpnpOrgAVTransport1::SyncSetAVTransportURI(TUint aInstanceID, const Brx& aCurrentURI, const Brx& aCurrentURIMetaData)
{
    SyncSetAVTransportURIUpnpOrgAVTransport1 sync(*this);
    BeginSetAVTransportURI(aInstanceID, aCurrentURI, aCurrentURIMetaData, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport1::BeginSetAVTransportURI(TUint aInstanceID, const Brx& aCurrentURI, const Brx& aCurrentURIMetaData, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetAVTransportURI, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetAVTransportURI->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aCurrentURI));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aCurrentURIMetaData));
    invocation->Invoke();
}

void CpProxyUpnpOrgAVTransport1::EndSetAVTransportURI(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetAVTransportURI"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgAVTransport1::SyncSetNextAVTransportURI(TUint aInstanceID, const Brx& aNextURI, const Brx& aNextURIMetaData)
{
    SyncSetNextAVTransportURIUpnpOrgAVTransport1 sync(*this);
    BeginSetNextAVTransportURI(aInstanceID, aNextURI, aNextURIMetaData, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport1::BeginSetNextAVTransportURI(TUint aInstanceID, const Brx& aNextURI, const Brx& aNextURIMetaData, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetNextAVTransportURI, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetNextAVTransportURI->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aNextURI));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aNextURIMetaData));
    invocation->Invoke();
}

void CpProxyUpnpOrgAVTransport1::EndSetNextAVTransportURI(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetNextAVTransportURI"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgAVTransport1::SyncGetMediaInfo(TUint aInstanceID, TUint& aNrTracks, Brh& aMediaDuration, Brh& aCurrentURI, Brh& aCurrentURIMetaData, Brh& aNextURI, Brh& aNextURIMetaData, Brh& aPlayMedium, Brh& aRecordMedium, Brh& aWriteStatus)
{
    SyncGetMediaInfoUpnpOrgAVTransport1 sync(*this, aNrTracks, aMediaDuration, aCurrentURI, aCurrentURIMetaData, aNextURI, aNextURIMetaData, aPlayMedium, aRecordMedium, aWriteStatus);
    BeginGetMediaInfo(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport1::BeginGetMediaInfo(TUint aInstanceID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgAVTransport1::EndGetMediaInfo(IAsync& aAsync, TUint& aNrTracks, Brh& aMediaDuration, Brh& aCurrentURI, Brh& aCurrentURIMetaData, Brh& aNextURI, Brh& aNextURIMetaData, Brh& aPlayMedium, Brh& aRecordMedium, Brh& aWriteStatus)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetMediaInfo"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aNrTracks = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aMediaDuration);
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aCurrentURI);
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aCurrentURIMetaData);
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aNextURI);
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aNextURIMetaData);
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aPlayMedium);
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aRecordMedium);
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aWriteStatus);
}

void CpProxyUpnpOrgAVTransport1::SyncGetTransportInfo(TUint aInstanceID, Brh& aCurrentTransportState, Brh& aCurrentTransportStatus, Brh& aCurrentSpeed)
{
    SyncGetTransportInfoUpnpOrgAVTransport1 sync(*this, aCurrentTransportState, aCurrentTransportStatus, aCurrentSpeed);
    BeginGetTransportInfo(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport1::BeginGetTransportInfo(TUint aInstanceID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgAVTransport1::EndGetTransportInfo(IAsync& aAsync, Brh& aCurrentTransportState, Brh& aCurrentTransportStatus, Brh& aCurrentSpeed)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetTransportInfo"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aCurrentTransportState);
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aCurrentTransportStatus);
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aCurrentSpeed);
}

void CpProxyUpnpOrgAVTransport1::SyncGetPositionInfo(TUint aInstanceID, TUint& aTrack, Brh& aTrackDuration, Brh& aTrackMetaData, Brh& aTrackURI, Brh& aRelTime, Brh& aAbsTime, TInt& aRelCount, TInt& aAbsCount)
{
    SyncGetPositionInfoUpnpOrgAVTransport1 sync(*this, aTrack, aTrackDuration, aTrackMetaData, aTrackURI, aRelTime, aAbsTime, aRelCount, aAbsCount);
    BeginGetPositionInfo(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport1::BeginGetPositionInfo(TUint aInstanceID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgAVTransport1::EndGetPositionInfo(IAsync& aAsync, TUint& aTrack, Brh& aTrackDuration, Brh& aTrackMetaData, Brh& aTrackURI, Brh& aRelTime, Brh& aAbsTime, TInt& aRelCount, TInt& aAbsCount)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetPositionInfo"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aTrack = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aTrackDuration);
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aTrackMetaData);
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aTrackURI);
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aRelTime);
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aAbsTime);
    aRelCount = ((ArgumentInt*)invocation.OutputArguments()[index++])->Value();
    aAbsCount = ((ArgumentInt*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgAVTransport1::SyncGetDeviceCapabilities(TUint aInstanceID, Brh& aPlayMedia, Brh& aRecMedia, Brh& aRecQualityModes)
{
    SyncGetDeviceCapabilitiesUpnpOrgAVTransport1 sync(*this, aPlayMedia, aRecMedia, aRecQualityModes);
    BeginGetDeviceCapabilities(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport1::BeginGetDeviceCapabilities(TUint aInstanceID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgAVTransport1::EndGetDeviceCapabilities(IAsync& aAsync, Brh& aPlayMedia, Brh& aRecMedia, Brh& aRecQualityModes)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetDeviceCapabilities"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aPlayMedia);
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aRecMedia);
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aRecQualityModes);
}

void CpProxyUpnpOrgAVTransport1::SyncGetTransportSettings(TUint aInstanceID, Brh& aPlayMode, Brh& aRecQualityMode)
{
    SyncGetTransportSettingsUpnpOrgAVTransport1 sync(*this, aPlayMode, aRecQualityMode);
    BeginGetTransportSettings(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport1::BeginGetTransportSettings(TUint aInstanceID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgAVTransport1::EndGetTransportSettings(IAsync& aAsync, Brh& aPlayMode, Brh& aRecQualityMode)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetTransportSettings"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aPlayMode);
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aRecQualityMode);
}

void CpProxyUpnpOrgAVTransport1::SyncStop(TUint aInstanceID)
{
    SyncStopUpnpOrgAVTransport1 sync(*this);
    BeginStop(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport1::BeginStop(TUint aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionStop, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionStop->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->Invoke();
}

void CpProxyUpnpOrgAVTransport1::EndStop(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Stop"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgAVTransport1::SyncPlay(TUint aInstanceID, const Brx& aSpeed)
{
    SyncPlayUpnpOrgAVTransport1 sync(*this);
    BeginPlay(aInstanceID, aSpeed, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport1::BeginPlay(TUint aInstanceID, const Brx& aSpeed, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionPlay, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionPlay->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aSpeed));
    invocation->Invoke();
}

void CpProxyUpnpOrgAVTransport1::EndPlay(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Play"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgAVTransport1::SyncPause(TUint aInstanceID)
{
    SyncPauseUpnpOrgAVTransport1 sync(*this);
    BeginPause(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport1::BeginPause(TUint aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionPause, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionPause->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->Invoke();
}

void CpProxyUpnpOrgAVTransport1::EndPause(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Pause"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgAVTransport1::SyncRecord(TUint aInstanceID)
{
    SyncRecordUpnpOrgAVTransport1 sync(*this);
    BeginRecord(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport1::BeginRecord(TUint aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionRecord, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionRecord->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->Invoke();
}

void CpProxyUpnpOrgAVTransport1::EndRecord(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Record"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgAVTransport1::SyncSeek(TUint aInstanceID, const Brx& aUnit, const Brx& aTarget)
{
    SyncSeekUpnpOrgAVTransport1 sync(*this);
    BeginSeek(aInstanceID, aUnit, aTarget, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport1::BeginSeek(TUint aInstanceID, const Brx& aUnit, const Brx& aTarget, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSeek, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSeek->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aUnit));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aTarget));
    invocation->Invoke();
}

void CpProxyUpnpOrgAVTransport1::EndSeek(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Seek"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgAVTransport1::SyncNext(TUint aInstanceID)
{
    SyncNextUpnpOrgAVTransport1 sync(*this);
    BeginNext(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport1::BeginNext(TUint aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionNext, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionNext->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->Invoke();
}

void CpProxyUpnpOrgAVTransport1::EndNext(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Next"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgAVTransport1::SyncPrevious(TUint aInstanceID)
{
    SyncPreviousUpnpOrgAVTransport1 sync(*this);
    BeginPrevious(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport1::BeginPrevious(TUint aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionPrevious, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionPrevious->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->Invoke();
}

void CpProxyUpnpOrgAVTransport1::EndPrevious(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Previous"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgAVTransport1::SyncSetPlayMode(TUint aInstanceID, const Brx& aNewPlayMode)
{
    SyncSetPlayModeUpnpOrgAVTransport1 sync(*this);
    BeginSetPlayMode(aInstanceID, aNewPlayMode, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport1::BeginSetPlayMode(TUint aInstanceID, const Brx& aNewPlayMode, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetPlayMode, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetPlayMode->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aNewPlayMode));
    invocation->Invoke();
}

void CpProxyUpnpOrgAVTransport1::EndSetPlayMode(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetPlayMode"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgAVTransport1::SyncSetRecordQualityMode(TUint aInstanceID, const Brx& aNewRecordQualityMode)
{
    SyncSetRecordQualityModeUpnpOrgAVTransport1 sync(*this);
    BeginSetRecordQualityMode(aInstanceID, aNewRecordQualityMode, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport1::BeginSetRecordQualityMode(TUint aInstanceID, const Brx& aNewRecordQualityMode, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetRecordQualityMode, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetRecordQualityMode->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aNewRecordQualityMode));
    invocation->Invoke();
}

void CpProxyUpnpOrgAVTransport1::EndSetRecordQualityMode(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetRecordQualityMode"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgAVTransport1::SyncGetCurrentTransportActions(TUint aInstanceID, Brh& aActions)
{
    SyncGetCurrentTransportActionsUpnpOrgAVTransport1 sync(*this, aActions);
    BeginGetCurrentTransportActions(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport1::BeginGetCurrentTransportActions(TUint aInstanceID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgAVTransport1::EndGetCurrentTransportActions(IAsync& aAsync, Brh& aActions)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetCurrentTransportActions"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aActions);
}

void CpProxyUpnpOrgAVTransport1::SetPropertyLastChangeChanged(Functor& aFunctor)
{
    iLock->Wait();
    iLastChangeChanged = aFunctor;
    iLock->Signal();
}

void CpProxyUpnpOrgAVTransport1::PropertyLastChange(Brhz& aLastChange) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aLastChange.Set(iLastChange->Value());
}

void CpProxyUpnpOrgAVTransport1::LastChangePropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iLastChangeChanged != NULL) {
        iLastChangeChanged();
    }
}

