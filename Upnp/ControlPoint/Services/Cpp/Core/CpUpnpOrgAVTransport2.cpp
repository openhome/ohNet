#include <Core/CpUpnpOrgAVTransport2.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Core/CpDevice.h>

using namespace Zapp;


class SyncSetAVTransportURIUpnpOrgAVTransport2 : public SyncProxyAction
{
public:
    SyncSetAVTransportURIUpnpOrgAVTransport2(CpProxyUpnpOrgAVTransport2& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport2& iService;
};

SyncSetAVTransportURIUpnpOrgAVTransport2::SyncSetAVTransportURIUpnpOrgAVTransport2(CpProxyUpnpOrgAVTransport2& aService)
    : iService(aService)
{
}

void SyncSetAVTransportURIUpnpOrgAVTransport2::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetAVTransportURI(aAsync);
}


class SyncSetNextAVTransportURIUpnpOrgAVTransport2 : public SyncProxyAction
{
public:
    SyncSetNextAVTransportURIUpnpOrgAVTransport2(CpProxyUpnpOrgAVTransport2& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport2& iService;
};

SyncSetNextAVTransportURIUpnpOrgAVTransport2::SyncSetNextAVTransportURIUpnpOrgAVTransport2(CpProxyUpnpOrgAVTransport2& aService)
    : iService(aService)
{
}

void SyncSetNextAVTransportURIUpnpOrgAVTransport2::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetNextAVTransportURI(aAsync);
}


class SyncGetMediaInfoUpnpOrgAVTransport2 : public SyncProxyAction
{
public:
    SyncGetMediaInfoUpnpOrgAVTransport2(CpProxyUpnpOrgAVTransport2& aService, TUint& aNrTracks, Brh& aMediaDuration, Brh& aCurrentURI, Brh& aCurrentURIMetaData, Brh& aNextURI, Brh& aNextURIMetaData, Brh& aPlayMedium, Brh& aRecordMedium, Brh& aWriteStatus);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport2& iService;
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

SyncGetMediaInfoUpnpOrgAVTransport2::SyncGetMediaInfoUpnpOrgAVTransport2(CpProxyUpnpOrgAVTransport2& aService, TUint& aNrTracks, Brh& aMediaDuration, Brh& aCurrentURI, Brh& aCurrentURIMetaData, Brh& aNextURI, Brh& aNextURIMetaData, Brh& aPlayMedium, Brh& aRecordMedium, Brh& aWriteStatus)
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

void SyncGetMediaInfoUpnpOrgAVTransport2::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetMediaInfo(aAsync, iNrTracks, iMediaDuration, iCurrentURI, iCurrentURIMetaData, iNextURI, iNextURIMetaData, iPlayMedium, iRecordMedium, iWriteStatus);
}


class SyncGetMediaInfo_ExtUpnpOrgAVTransport2 : public SyncProxyAction
{
public:
    SyncGetMediaInfo_ExtUpnpOrgAVTransport2(CpProxyUpnpOrgAVTransport2& aService, Brh& aCurrentType, TUint& aNrTracks, Brh& aMediaDuration, Brh& aCurrentURI, Brh& aCurrentURIMetaData, Brh& aNextURI, Brh& aNextURIMetaData, Brh& aPlayMedium, Brh& aRecordMedium, Brh& aWriteStatus);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport2& iService;
    Brh& iCurrentType;
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

SyncGetMediaInfo_ExtUpnpOrgAVTransport2::SyncGetMediaInfo_ExtUpnpOrgAVTransport2(CpProxyUpnpOrgAVTransport2& aService, Brh& aCurrentType, TUint& aNrTracks, Brh& aMediaDuration, Brh& aCurrentURI, Brh& aCurrentURIMetaData, Brh& aNextURI, Brh& aNextURIMetaData, Brh& aPlayMedium, Brh& aRecordMedium, Brh& aWriteStatus)
    : iService(aService)
    , iCurrentType(aCurrentType)
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

void SyncGetMediaInfo_ExtUpnpOrgAVTransport2::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetMediaInfo_Ext(aAsync, iCurrentType, iNrTracks, iMediaDuration, iCurrentURI, iCurrentURIMetaData, iNextURI, iNextURIMetaData, iPlayMedium, iRecordMedium, iWriteStatus);
}


class SyncGetTransportInfoUpnpOrgAVTransport2 : public SyncProxyAction
{
public:
    SyncGetTransportInfoUpnpOrgAVTransport2(CpProxyUpnpOrgAVTransport2& aService, Brh& aCurrentTransportState, Brh& aCurrentTransportStatus, Brh& aCurrentSpeed);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport2& iService;
    Brh& iCurrentTransportState;
    Brh& iCurrentTransportStatus;
    Brh& iCurrentSpeed;
};

SyncGetTransportInfoUpnpOrgAVTransport2::SyncGetTransportInfoUpnpOrgAVTransport2(CpProxyUpnpOrgAVTransport2& aService, Brh& aCurrentTransportState, Brh& aCurrentTransportStatus, Brh& aCurrentSpeed)
    : iService(aService)
    , iCurrentTransportState(aCurrentTransportState)
    , iCurrentTransportStatus(aCurrentTransportStatus)
    , iCurrentSpeed(aCurrentSpeed)
{
}

void SyncGetTransportInfoUpnpOrgAVTransport2::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetTransportInfo(aAsync, iCurrentTransportState, iCurrentTransportStatus, iCurrentSpeed);
}


class SyncGetPositionInfoUpnpOrgAVTransport2 : public SyncProxyAction
{
public:
    SyncGetPositionInfoUpnpOrgAVTransport2(CpProxyUpnpOrgAVTransport2& aService, TUint& aTrack, Brh& aTrackDuration, Brh& aTrackMetaData, Brh& aTrackURI, Brh& aRelTime, Brh& aAbsTime, TInt& aRelCount, TInt& aAbsCount);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport2& iService;
    TUint& iTrack;
    Brh& iTrackDuration;
    Brh& iTrackMetaData;
    Brh& iTrackURI;
    Brh& iRelTime;
    Brh& iAbsTime;
    TInt& iRelCount;
    TInt& iAbsCount;
};

SyncGetPositionInfoUpnpOrgAVTransport2::SyncGetPositionInfoUpnpOrgAVTransport2(CpProxyUpnpOrgAVTransport2& aService, TUint& aTrack, Brh& aTrackDuration, Brh& aTrackMetaData, Brh& aTrackURI, Brh& aRelTime, Brh& aAbsTime, TInt& aRelCount, TInt& aAbsCount)
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

void SyncGetPositionInfoUpnpOrgAVTransport2::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetPositionInfo(aAsync, iTrack, iTrackDuration, iTrackMetaData, iTrackURI, iRelTime, iAbsTime, iRelCount, iAbsCount);
}


class SyncGetDeviceCapabilitiesUpnpOrgAVTransport2 : public SyncProxyAction
{
public:
    SyncGetDeviceCapabilitiesUpnpOrgAVTransport2(CpProxyUpnpOrgAVTransport2& aService, Brh& aPlayMedia, Brh& aRecMedia, Brh& aRecQualityModes);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport2& iService;
    Brh& iPlayMedia;
    Brh& iRecMedia;
    Brh& iRecQualityModes;
};

SyncGetDeviceCapabilitiesUpnpOrgAVTransport2::SyncGetDeviceCapabilitiesUpnpOrgAVTransport2(CpProxyUpnpOrgAVTransport2& aService, Brh& aPlayMedia, Brh& aRecMedia, Brh& aRecQualityModes)
    : iService(aService)
    , iPlayMedia(aPlayMedia)
    , iRecMedia(aRecMedia)
    , iRecQualityModes(aRecQualityModes)
{
}

void SyncGetDeviceCapabilitiesUpnpOrgAVTransport2::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetDeviceCapabilities(aAsync, iPlayMedia, iRecMedia, iRecQualityModes);
}


class SyncGetTransportSettingsUpnpOrgAVTransport2 : public SyncProxyAction
{
public:
    SyncGetTransportSettingsUpnpOrgAVTransport2(CpProxyUpnpOrgAVTransport2& aService, Brh& aPlayMode, Brh& aRecQualityMode);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport2& iService;
    Brh& iPlayMode;
    Brh& iRecQualityMode;
};

SyncGetTransportSettingsUpnpOrgAVTransport2::SyncGetTransportSettingsUpnpOrgAVTransport2(CpProxyUpnpOrgAVTransport2& aService, Brh& aPlayMode, Brh& aRecQualityMode)
    : iService(aService)
    , iPlayMode(aPlayMode)
    , iRecQualityMode(aRecQualityMode)
{
}

void SyncGetTransportSettingsUpnpOrgAVTransport2::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetTransportSettings(aAsync, iPlayMode, iRecQualityMode);
}


class SyncStopUpnpOrgAVTransport2 : public SyncProxyAction
{
public:
    SyncStopUpnpOrgAVTransport2(CpProxyUpnpOrgAVTransport2& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport2& iService;
};

SyncStopUpnpOrgAVTransport2::SyncStopUpnpOrgAVTransport2(CpProxyUpnpOrgAVTransport2& aService)
    : iService(aService)
{
}

void SyncStopUpnpOrgAVTransport2::CompleteRequest(IAsync& aAsync)
{
    iService.EndStop(aAsync);
}


class SyncPlayUpnpOrgAVTransport2 : public SyncProxyAction
{
public:
    SyncPlayUpnpOrgAVTransport2(CpProxyUpnpOrgAVTransport2& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport2& iService;
};

SyncPlayUpnpOrgAVTransport2::SyncPlayUpnpOrgAVTransport2(CpProxyUpnpOrgAVTransport2& aService)
    : iService(aService)
{
}

void SyncPlayUpnpOrgAVTransport2::CompleteRequest(IAsync& aAsync)
{
    iService.EndPlay(aAsync);
}


class SyncPauseUpnpOrgAVTransport2 : public SyncProxyAction
{
public:
    SyncPauseUpnpOrgAVTransport2(CpProxyUpnpOrgAVTransport2& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport2& iService;
};

SyncPauseUpnpOrgAVTransport2::SyncPauseUpnpOrgAVTransport2(CpProxyUpnpOrgAVTransport2& aService)
    : iService(aService)
{
}

void SyncPauseUpnpOrgAVTransport2::CompleteRequest(IAsync& aAsync)
{
    iService.EndPause(aAsync);
}


class SyncRecordUpnpOrgAVTransport2 : public SyncProxyAction
{
public:
    SyncRecordUpnpOrgAVTransport2(CpProxyUpnpOrgAVTransport2& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport2& iService;
};

SyncRecordUpnpOrgAVTransport2::SyncRecordUpnpOrgAVTransport2(CpProxyUpnpOrgAVTransport2& aService)
    : iService(aService)
{
}

void SyncRecordUpnpOrgAVTransport2::CompleteRequest(IAsync& aAsync)
{
    iService.EndRecord(aAsync);
}


class SyncSeekUpnpOrgAVTransport2 : public SyncProxyAction
{
public:
    SyncSeekUpnpOrgAVTransport2(CpProxyUpnpOrgAVTransport2& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport2& iService;
};

SyncSeekUpnpOrgAVTransport2::SyncSeekUpnpOrgAVTransport2(CpProxyUpnpOrgAVTransport2& aService)
    : iService(aService)
{
}

void SyncSeekUpnpOrgAVTransport2::CompleteRequest(IAsync& aAsync)
{
    iService.EndSeek(aAsync);
}


class SyncNextUpnpOrgAVTransport2 : public SyncProxyAction
{
public:
    SyncNextUpnpOrgAVTransport2(CpProxyUpnpOrgAVTransport2& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport2& iService;
};

SyncNextUpnpOrgAVTransport2::SyncNextUpnpOrgAVTransport2(CpProxyUpnpOrgAVTransport2& aService)
    : iService(aService)
{
}

void SyncNextUpnpOrgAVTransport2::CompleteRequest(IAsync& aAsync)
{
    iService.EndNext(aAsync);
}


class SyncPreviousUpnpOrgAVTransport2 : public SyncProxyAction
{
public:
    SyncPreviousUpnpOrgAVTransport2(CpProxyUpnpOrgAVTransport2& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport2& iService;
};

SyncPreviousUpnpOrgAVTransport2::SyncPreviousUpnpOrgAVTransport2(CpProxyUpnpOrgAVTransport2& aService)
    : iService(aService)
{
}

void SyncPreviousUpnpOrgAVTransport2::CompleteRequest(IAsync& aAsync)
{
    iService.EndPrevious(aAsync);
}


class SyncSetPlayModeUpnpOrgAVTransport2 : public SyncProxyAction
{
public:
    SyncSetPlayModeUpnpOrgAVTransport2(CpProxyUpnpOrgAVTransport2& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport2& iService;
};

SyncSetPlayModeUpnpOrgAVTransport2::SyncSetPlayModeUpnpOrgAVTransport2(CpProxyUpnpOrgAVTransport2& aService)
    : iService(aService)
{
}

void SyncSetPlayModeUpnpOrgAVTransport2::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetPlayMode(aAsync);
}


class SyncSetRecordQualityModeUpnpOrgAVTransport2 : public SyncProxyAction
{
public:
    SyncSetRecordQualityModeUpnpOrgAVTransport2(CpProxyUpnpOrgAVTransport2& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport2& iService;
};

SyncSetRecordQualityModeUpnpOrgAVTransport2::SyncSetRecordQualityModeUpnpOrgAVTransport2(CpProxyUpnpOrgAVTransport2& aService)
    : iService(aService)
{
}

void SyncSetRecordQualityModeUpnpOrgAVTransport2::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetRecordQualityMode(aAsync);
}


class SyncGetCurrentTransportActionsUpnpOrgAVTransport2 : public SyncProxyAction
{
public:
    SyncGetCurrentTransportActionsUpnpOrgAVTransport2(CpProxyUpnpOrgAVTransport2& aService, Brh& aActions);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport2& iService;
    Brh& iActions;
};

SyncGetCurrentTransportActionsUpnpOrgAVTransport2::SyncGetCurrentTransportActionsUpnpOrgAVTransport2(CpProxyUpnpOrgAVTransport2& aService, Brh& aActions)
    : iService(aService)
    , iActions(aActions)
{
}

void SyncGetCurrentTransportActionsUpnpOrgAVTransport2::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetCurrentTransportActions(aAsync, iActions);
}


class SyncGetDRMStateUpnpOrgAVTransport2 : public SyncProxyAction
{
public:
    SyncGetDRMStateUpnpOrgAVTransport2(CpProxyUpnpOrgAVTransport2& aService, Brh& aCurrentDRMState);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport2& iService;
    Brh& iCurrentDRMState;
};

SyncGetDRMStateUpnpOrgAVTransport2::SyncGetDRMStateUpnpOrgAVTransport2(CpProxyUpnpOrgAVTransport2& aService, Brh& aCurrentDRMState)
    : iService(aService)
    , iCurrentDRMState(aCurrentDRMState)
{
}

void SyncGetDRMStateUpnpOrgAVTransport2::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetDRMState(aAsync, iCurrentDRMState);
}


class SyncGetStateVariablesUpnpOrgAVTransport2 : public SyncProxyAction
{
public:
    SyncGetStateVariablesUpnpOrgAVTransport2(CpProxyUpnpOrgAVTransport2& aService, Brh& aStateVariableValuePairs);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport2& iService;
    Brh& iStateVariableValuePairs;
};

SyncGetStateVariablesUpnpOrgAVTransport2::SyncGetStateVariablesUpnpOrgAVTransport2(CpProxyUpnpOrgAVTransport2& aService, Brh& aStateVariableValuePairs)
    : iService(aService)
    , iStateVariableValuePairs(aStateVariableValuePairs)
{
}

void SyncGetStateVariablesUpnpOrgAVTransport2::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetStateVariables(aAsync, iStateVariableValuePairs);
}


class SyncSetStateVariablesUpnpOrgAVTransport2 : public SyncProxyAction
{
public:
    SyncSetStateVariablesUpnpOrgAVTransport2(CpProxyUpnpOrgAVTransport2& aService, Brh& aStateVariableList);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport2& iService;
    Brh& iStateVariableList;
};

SyncSetStateVariablesUpnpOrgAVTransport2::SyncSetStateVariablesUpnpOrgAVTransport2(CpProxyUpnpOrgAVTransport2& aService, Brh& aStateVariableList)
    : iService(aService)
    , iStateVariableList(aStateVariableList)
{
}

void SyncSetStateVariablesUpnpOrgAVTransport2::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetStateVariables(aAsync, iStateVariableList);
}


CpProxyUpnpOrgAVTransport2::CpProxyUpnpOrgAVTransport2(CpDevice& aDevice)
{
    iService = new CpiService("schemas-upnp-org", "AVTransport", 2, aDevice.Device());
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

    iActionGetMediaInfo_Ext = new Action("GetMediaInfo_Ext");
    param = new Zapp::ParameterUint("InstanceID");
    iActionGetMediaInfo_Ext->AddInputParameter(param);
    index = 0;
    allowedValues = new TChar*[3];
    allowedValues[index++] = (TChar*)"NO_MEDIA";
    allowedValues[index++] = (TChar*)"TRACK_AWARE";
    allowedValues[index++] = (TChar*)"TRACK_UNAWARE";
    param = new Zapp::ParameterString("CurrentType", allowedValues, 3);
    iActionGetMediaInfo_Ext->AddOutputParameter(param);
    delete[] allowedValues;
    param = new Zapp::ParameterUint("NrTracks", 0, 0);
    iActionGetMediaInfo_Ext->AddOutputParameter(param);
    param = new Zapp::ParameterString("MediaDuration");
    iActionGetMediaInfo_Ext->AddOutputParameter(param);
    param = new Zapp::ParameterString("CurrentURI");
    iActionGetMediaInfo_Ext->AddOutputParameter(param);
    param = new Zapp::ParameterString("CurrentURIMetaData");
    iActionGetMediaInfo_Ext->AddOutputParameter(param);
    param = new Zapp::ParameterString("NextURI");
    iActionGetMediaInfo_Ext->AddOutputParameter(param);
    param = new Zapp::ParameterString("NextURIMetaData");
    iActionGetMediaInfo_Ext->AddOutputParameter(param);
    param = new Zapp::ParameterString("PlayMedium");
    iActionGetMediaInfo_Ext->AddOutputParameter(param);
    param = new Zapp::ParameterString("RecordMedium");
    iActionGetMediaInfo_Ext->AddOutputParameter(param);
    param = new Zapp::ParameterString("WriteStatus");
    iActionGetMediaInfo_Ext->AddOutputParameter(param);

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

    iActionGetDRMState = new Action("GetDRMState");
    param = new Zapp::ParameterUint("InstanceID");
    iActionGetDRMState->AddInputParameter(param);
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"OK";
    param = new Zapp::ParameterString("CurrentDRMState", allowedValues, 1);
    iActionGetDRMState->AddOutputParameter(param);
    delete[] allowedValues;

    iActionGetStateVariables = new Action("GetStateVariables");
    param = new Zapp::ParameterUint("InstanceID");
    iActionGetStateVariables->AddInputParameter(param);
    param = new Zapp::ParameterString("StateVariableList");
    iActionGetStateVariables->AddInputParameter(param);
    param = new Zapp::ParameterString("StateVariableValuePairs");
    iActionGetStateVariables->AddOutputParameter(param);

    iActionSetStateVariables = new Action("SetStateVariables");
    param = new Zapp::ParameterUint("InstanceID");
    iActionSetStateVariables->AddInputParameter(param);
    param = new Zapp::ParameterString("AVTransportUDN");
    iActionSetStateVariables->AddInputParameter(param);
    param = new Zapp::ParameterString("ServiceType");
    iActionSetStateVariables->AddInputParameter(param);
    param = new Zapp::ParameterString("ServiceId");
    iActionSetStateVariables->AddInputParameter(param);
    param = new Zapp::ParameterString("StateVariableValuePairs");
    iActionSetStateVariables->AddInputParameter(param);
    param = new Zapp::ParameterString("StateVariableList");
    iActionSetStateVariables->AddOutputParameter(param);

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyUpnpOrgAVTransport2::LastChangePropertyChanged);
    iLastChange = new PropertyString("LastChange", functor);
    iService->AddProperty(iLastChange);
    functor = MakeFunctor(*this, &CpProxyUpnpOrgAVTransport2::DRMStatePropertyChanged);
    iDRMState = new PropertyString("DRMState", functor);
    iService->AddProperty(iDRMState);
}

CpProxyUpnpOrgAVTransport2::~CpProxyUpnpOrgAVTransport2()
{
    delete iService;
    delete iActionSetAVTransportURI;
    delete iActionSetNextAVTransportURI;
    delete iActionGetMediaInfo;
    delete iActionGetMediaInfo_Ext;
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
    delete iActionGetDRMState;
    delete iActionGetStateVariables;
    delete iActionSetStateVariables;
}

void CpProxyUpnpOrgAVTransport2::SyncSetAVTransportURI(TUint aInstanceID, const Brx& aCurrentURI, const Brx& aCurrentURIMetaData)
{
    SyncSetAVTransportURIUpnpOrgAVTransport2 sync(*this);
    BeginSetAVTransportURI(aInstanceID, aCurrentURI, aCurrentURIMetaData, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport2::BeginSetAVTransportURI(TUint aInstanceID, const Brx& aCurrentURI, const Brx& aCurrentURIMetaData, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetAVTransportURI, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetAVTransportURI->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aCurrentURI));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aCurrentURIMetaData));
    invocation->Invoke();
}

void CpProxyUpnpOrgAVTransport2::EndSetAVTransportURI(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetAVTransportURI"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgAVTransport2::SyncSetNextAVTransportURI(TUint aInstanceID, const Brx& aNextURI, const Brx& aNextURIMetaData)
{
    SyncSetNextAVTransportURIUpnpOrgAVTransport2 sync(*this);
    BeginSetNextAVTransportURI(aInstanceID, aNextURI, aNextURIMetaData, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport2::BeginSetNextAVTransportURI(TUint aInstanceID, const Brx& aNextURI, const Brx& aNextURIMetaData, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetNextAVTransportURI, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetNextAVTransportURI->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aNextURI));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aNextURIMetaData));
    invocation->Invoke();
}

void CpProxyUpnpOrgAVTransport2::EndSetNextAVTransportURI(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetNextAVTransportURI"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgAVTransport2::SyncGetMediaInfo(TUint aInstanceID, TUint& aNrTracks, Brh& aMediaDuration, Brh& aCurrentURI, Brh& aCurrentURIMetaData, Brh& aNextURI, Brh& aNextURIMetaData, Brh& aPlayMedium, Brh& aRecordMedium, Brh& aWriteStatus)
{
    SyncGetMediaInfoUpnpOrgAVTransport2 sync(*this, aNrTracks, aMediaDuration, aCurrentURI, aCurrentURIMetaData, aNextURI, aNextURIMetaData, aPlayMedium, aRecordMedium, aWriteStatus);
    BeginGetMediaInfo(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport2::BeginGetMediaInfo(TUint aInstanceID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgAVTransport2::EndGetMediaInfo(IAsync& aAsync, TUint& aNrTracks, Brh& aMediaDuration, Brh& aCurrentURI, Brh& aCurrentURIMetaData, Brh& aNextURI, Brh& aNextURIMetaData, Brh& aPlayMedium, Brh& aRecordMedium, Brh& aWriteStatus)
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

void CpProxyUpnpOrgAVTransport2::SyncGetMediaInfo_Ext(TUint aInstanceID, Brh& aCurrentType, TUint& aNrTracks, Brh& aMediaDuration, Brh& aCurrentURI, Brh& aCurrentURIMetaData, Brh& aNextURI, Brh& aNextURIMetaData, Brh& aPlayMedium, Brh& aRecordMedium, Brh& aWriteStatus)
{
    SyncGetMediaInfo_ExtUpnpOrgAVTransport2 sync(*this, aCurrentType, aNrTracks, aMediaDuration, aCurrentURI, aCurrentURIMetaData, aNextURI, aNextURIMetaData, aPlayMedium, aRecordMedium, aWriteStatus);
    BeginGetMediaInfo_Ext(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport2::BeginGetMediaInfo_Ext(TUint aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetMediaInfo_Ext, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetMediaInfo_Ext->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetMediaInfo_Ext->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
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

void CpProxyUpnpOrgAVTransport2::EndGetMediaInfo_Ext(IAsync& aAsync, Brh& aCurrentType, TUint& aNrTracks, Brh& aMediaDuration, Brh& aCurrentURI, Brh& aCurrentURIMetaData, Brh& aNextURI, Brh& aNextURIMetaData, Brh& aPlayMedium, Brh& aRecordMedium, Brh& aWriteStatus)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetMediaInfo_Ext"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aCurrentType);
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

void CpProxyUpnpOrgAVTransport2::SyncGetTransportInfo(TUint aInstanceID, Brh& aCurrentTransportState, Brh& aCurrentTransportStatus, Brh& aCurrentSpeed)
{
    SyncGetTransportInfoUpnpOrgAVTransport2 sync(*this, aCurrentTransportState, aCurrentTransportStatus, aCurrentSpeed);
    BeginGetTransportInfo(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport2::BeginGetTransportInfo(TUint aInstanceID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgAVTransport2::EndGetTransportInfo(IAsync& aAsync, Brh& aCurrentTransportState, Brh& aCurrentTransportStatus, Brh& aCurrentSpeed)
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

void CpProxyUpnpOrgAVTransport2::SyncGetPositionInfo(TUint aInstanceID, TUint& aTrack, Brh& aTrackDuration, Brh& aTrackMetaData, Brh& aTrackURI, Brh& aRelTime, Brh& aAbsTime, TInt& aRelCount, TInt& aAbsCount)
{
    SyncGetPositionInfoUpnpOrgAVTransport2 sync(*this, aTrack, aTrackDuration, aTrackMetaData, aTrackURI, aRelTime, aAbsTime, aRelCount, aAbsCount);
    BeginGetPositionInfo(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport2::BeginGetPositionInfo(TUint aInstanceID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgAVTransport2::EndGetPositionInfo(IAsync& aAsync, TUint& aTrack, Brh& aTrackDuration, Brh& aTrackMetaData, Brh& aTrackURI, Brh& aRelTime, Brh& aAbsTime, TInt& aRelCount, TInt& aAbsCount)
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

void CpProxyUpnpOrgAVTransport2::SyncGetDeviceCapabilities(TUint aInstanceID, Brh& aPlayMedia, Brh& aRecMedia, Brh& aRecQualityModes)
{
    SyncGetDeviceCapabilitiesUpnpOrgAVTransport2 sync(*this, aPlayMedia, aRecMedia, aRecQualityModes);
    BeginGetDeviceCapabilities(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport2::BeginGetDeviceCapabilities(TUint aInstanceID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgAVTransport2::EndGetDeviceCapabilities(IAsync& aAsync, Brh& aPlayMedia, Brh& aRecMedia, Brh& aRecQualityModes)
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

void CpProxyUpnpOrgAVTransport2::SyncGetTransportSettings(TUint aInstanceID, Brh& aPlayMode, Brh& aRecQualityMode)
{
    SyncGetTransportSettingsUpnpOrgAVTransport2 sync(*this, aPlayMode, aRecQualityMode);
    BeginGetTransportSettings(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport2::BeginGetTransportSettings(TUint aInstanceID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgAVTransport2::EndGetTransportSettings(IAsync& aAsync, Brh& aPlayMode, Brh& aRecQualityMode)
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

void CpProxyUpnpOrgAVTransport2::SyncStop(TUint aInstanceID)
{
    SyncStopUpnpOrgAVTransport2 sync(*this);
    BeginStop(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport2::BeginStop(TUint aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionStop, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionStop->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->Invoke();
}

void CpProxyUpnpOrgAVTransport2::EndStop(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Stop"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgAVTransport2::SyncPlay(TUint aInstanceID, const Brx& aSpeed)
{
    SyncPlayUpnpOrgAVTransport2 sync(*this);
    BeginPlay(aInstanceID, aSpeed, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport2::BeginPlay(TUint aInstanceID, const Brx& aSpeed, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionPlay, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionPlay->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aSpeed));
    invocation->Invoke();
}

void CpProxyUpnpOrgAVTransport2::EndPlay(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Play"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgAVTransport2::SyncPause(TUint aInstanceID)
{
    SyncPauseUpnpOrgAVTransport2 sync(*this);
    BeginPause(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport2::BeginPause(TUint aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionPause, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionPause->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->Invoke();
}

void CpProxyUpnpOrgAVTransport2::EndPause(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Pause"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgAVTransport2::SyncRecord(TUint aInstanceID)
{
    SyncRecordUpnpOrgAVTransport2 sync(*this);
    BeginRecord(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport2::BeginRecord(TUint aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionRecord, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionRecord->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->Invoke();
}

void CpProxyUpnpOrgAVTransport2::EndRecord(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Record"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgAVTransport2::SyncSeek(TUint aInstanceID, const Brx& aUnit, const Brx& aTarget)
{
    SyncSeekUpnpOrgAVTransport2 sync(*this);
    BeginSeek(aInstanceID, aUnit, aTarget, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport2::BeginSeek(TUint aInstanceID, const Brx& aUnit, const Brx& aTarget, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSeek, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSeek->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aUnit));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aTarget));
    invocation->Invoke();
}

void CpProxyUpnpOrgAVTransport2::EndSeek(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Seek"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgAVTransport2::SyncNext(TUint aInstanceID)
{
    SyncNextUpnpOrgAVTransport2 sync(*this);
    BeginNext(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport2::BeginNext(TUint aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionNext, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionNext->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->Invoke();
}

void CpProxyUpnpOrgAVTransport2::EndNext(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Next"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgAVTransport2::SyncPrevious(TUint aInstanceID)
{
    SyncPreviousUpnpOrgAVTransport2 sync(*this);
    BeginPrevious(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport2::BeginPrevious(TUint aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionPrevious, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionPrevious->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->Invoke();
}

void CpProxyUpnpOrgAVTransport2::EndPrevious(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Previous"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgAVTransport2::SyncSetPlayMode(TUint aInstanceID, const Brx& aNewPlayMode)
{
    SyncSetPlayModeUpnpOrgAVTransport2 sync(*this);
    BeginSetPlayMode(aInstanceID, aNewPlayMode, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport2::BeginSetPlayMode(TUint aInstanceID, const Brx& aNewPlayMode, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetPlayMode, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetPlayMode->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aNewPlayMode));
    invocation->Invoke();
}

void CpProxyUpnpOrgAVTransport2::EndSetPlayMode(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetPlayMode"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgAVTransport2::SyncSetRecordQualityMode(TUint aInstanceID, const Brx& aNewRecordQualityMode)
{
    SyncSetRecordQualityModeUpnpOrgAVTransport2 sync(*this);
    BeginSetRecordQualityMode(aInstanceID, aNewRecordQualityMode, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport2::BeginSetRecordQualityMode(TUint aInstanceID, const Brx& aNewRecordQualityMode, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetRecordQualityMode, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetRecordQualityMode->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aNewRecordQualityMode));
    invocation->Invoke();
}

void CpProxyUpnpOrgAVTransport2::EndSetRecordQualityMode(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetRecordQualityMode"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgAVTransport2::SyncGetCurrentTransportActions(TUint aInstanceID, Brh& aActions)
{
    SyncGetCurrentTransportActionsUpnpOrgAVTransport2 sync(*this, aActions);
    BeginGetCurrentTransportActions(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport2::BeginGetCurrentTransportActions(TUint aInstanceID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgAVTransport2::EndGetCurrentTransportActions(IAsync& aAsync, Brh& aActions)
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

void CpProxyUpnpOrgAVTransport2::SyncGetDRMState(TUint aInstanceID, Brh& aCurrentDRMState)
{
    SyncGetDRMStateUpnpOrgAVTransport2 sync(*this, aCurrentDRMState);
    BeginGetDRMState(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport2::BeginGetDRMState(TUint aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetDRMState, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetDRMState->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetDRMState->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyUpnpOrgAVTransport2::EndGetDRMState(IAsync& aAsync, Brh& aCurrentDRMState)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetDRMState"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aCurrentDRMState);
}

void CpProxyUpnpOrgAVTransport2::SyncGetStateVariables(TUint aInstanceID, const Brx& aStateVariableList, Brh& aStateVariableValuePairs)
{
    SyncGetStateVariablesUpnpOrgAVTransport2 sync(*this, aStateVariableValuePairs);
    BeginGetStateVariables(aInstanceID, aStateVariableList, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport2::BeginGetStateVariables(TUint aInstanceID, const Brx& aStateVariableList, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetStateVariables, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetStateVariables->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aStateVariableList));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetStateVariables->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyUpnpOrgAVTransport2::EndGetStateVariables(IAsync& aAsync, Brh& aStateVariableValuePairs)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetStateVariables"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aStateVariableValuePairs);
}

void CpProxyUpnpOrgAVTransport2::SyncSetStateVariables(TUint aInstanceID, const Brx& aAVTransportUDN, const Brx& aServiceType, const Brx& aServiceId, const Brx& aStateVariableValuePairs, Brh& aStateVariableList)
{
    SyncSetStateVariablesUpnpOrgAVTransport2 sync(*this, aStateVariableList);
    BeginSetStateVariables(aInstanceID, aAVTransportUDN, aServiceType, aServiceId, aStateVariableValuePairs, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport2::BeginSetStateVariables(TUint aInstanceID, const Brx& aAVTransportUDN, const Brx& aServiceType, const Brx& aServiceId, const Brx& aStateVariableValuePairs, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetStateVariables, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetStateVariables->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aAVTransportUDN));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aServiceType));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aServiceId));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aStateVariableValuePairs));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionSetStateVariables->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyUpnpOrgAVTransport2::EndSetStateVariables(IAsync& aAsync, Brh& aStateVariableList)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetStateVariables"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aStateVariableList);
}

void CpProxyUpnpOrgAVTransport2::SetPropertyLastChangeChanged(Functor& aFunctor)
{
    iLock->Wait();
    iLastChangeChanged = aFunctor;
    iLock->Signal();
}

void CpProxyUpnpOrgAVTransport2::SetPropertyDRMStateChanged(Functor& aFunctor)
{
    iLock->Wait();
    iDRMStateChanged = aFunctor;
    iLock->Signal();
}

void CpProxyUpnpOrgAVTransport2::PropertyLastChange(Brhz& aLastChange) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aLastChange.Set(iLastChange->Value());
}

void CpProxyUpnpOrgAVTransport2::PropertyDRMState(Brhz& aDRMState) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aDRMState.Set(iDRMState->Value());
}

void CpProxyUpnpOrgAVTransport2::LastChangePropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iLastChangeChanged != NULL) {
        iLastChangeChanged();
    }
}

void CpProxyUpnpOrgAVTransport2::DRMStatePropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iDRMStateChanged != NULL) {
        iDRMStateChanged();
    }
}

