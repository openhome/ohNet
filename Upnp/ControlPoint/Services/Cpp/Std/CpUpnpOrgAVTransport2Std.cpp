#include <Std/CpUpnpOrgAVTransport2.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Buffer.h>
#include <Std/CpDevice.h>

#include <string>

using namespace Zapp;


class SyncSetAVTransportURIUpnpOrgAVTransport2Cpp : public SyncProxyAction
{
public:
    SyncSetAVTransportURIUpnpOrgAVTransport2Cpp(CpProxyUpnpOrgAVTransport2Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport2Cpp& iService;
};

SyncSetAVTransportURIUpnpOrgAVTransport2Cpp::SyncSetAVTransportURIUpnpOrgAVTransport2Cpp(CpProxyUpnpOrgAVTransport2Cpp& aService)
    : iService(aService)
{
}

void SyncSetAVTransportURIUpnpOrgAVTransport2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetAVTransportURI(aAsync);
}


class SyncSetNextAVTransportURIUpnpOrgAVTransport2Cpp : public SyncProxyAction
{
public:
    SyncSetNextAVTransportURIUpnpOrgAVTransport2Cpp(CpProxyUpnpOrgAVTransport2Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport2Cpp& iService;
};

SyncSetNextAVTransportURIUpnpOrgAVTransport2Cpp::SyncSetNextAVTransportURIUpnpOrgAVTransport2Cpp(CpProxyUpnpOrgAVTransport2Cpp& aService)
    : iService(aService)
{
}

void SyncSetNextAVTransportURIUpnpOrgAVTransport2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetNextAVTransportURI(aAsync);
}


class SyncGetMediaInfoUpnpOrgAVTransport2Cpp : public SyncProxyAction
{
public:
    SyncGetMediaInfoUpnpOrgAVTransport2Cpp(CpProxyUpnpOrgAVTransport2Cpp& aService, uint32_t& aNrTracks, std::string& aMediaDuration, std::string& aCurrentURI, std::string& aCurrentURIMetaData, std::string& aNextURI, std::string& aNextURIMetaData, std::string& aPlayMedium, std::string& aRecordMedium, std::string& aWriteStatus);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport2Cpp& iService;
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

SyncGetMediaInfoUpnpOrgAVTransport2Cpp::SyncGetMediaInfoUpnpOrgAVTransport2Cpp(CpProxyUpnpOrgAVTransport2Cpp& aService, uint32_t& aNrTracks, std::string& aMediaDuration, std::string& aCurrentURI, std::string& aCurrentURIMetaData, std::string& aNextURI, std::string& aNextURIMetaData, std::string& aPlayMedium, std::string& aRecordMedium, std::string& aWriteStatus)
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

void SyncGetMediaInfoUpnpOrgAVTransport2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetMediaInfo(aAsync, iNrTracks, iMediaDuration, iCurrentURI, iCurrentURIMetaData, iNextURI, iNextURIMetaData, iPlayMedium, iRecordMedium, iWriteStatus);
}


class SyncGetMediaInfo_ExtUpnpOrgAVTransport2Cpp : public SyncProxyAction
{
public:
    SyncGetMediaInfo_ExtUpnpOrgAVTransport2Cpp(CpProxyUpnpOrgAVTransport2Cpp& aService, std::string& aCurrentType, uint32_t& aNrTracks, std::string& aMediaDuration, std::string& aCurrentURI, std::string& aCurrentURIMetaData, std::string& aNextURI, std::string& aNextURIMetaData, std::string& aPlayMedium, std::string& aRecordMedium, std::string& aWriteStatus);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport2Cpp& iService;
    std::string& iCurrentType;
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

SyncGetMediaInfo_ExtUpnpOrgAVTransport2Cpp::SyncGetMediaInfo_ExtUpnpOrgAVTransport2Cpp(CpProxyUpnpOrgAVTransport2Cpp& aService, std::string& aCurrentType, uint32_t& aNrTracks, std::string& aMediaDuration, std::string& aCurrentURI, std::string& aCurrentURIMetaData, std::string& aNextURI, std::string& aNextURIMetaData, std::string& aPlayMedium, std::string& aRecordMedium, std::string& aWriteStatus)
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

void SyncGetMediaInfo_ExtUpnpOrgAVTransport2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetMediaInfo_Ext(aAsync, iCurrentType, iNrTracks, iMediaDuration, iCurrentURI, iCurrentURIMetaData, iNextURI, iNextURIMetaData, iPlayMedium, iRecordMedium, iWriteStatus);
}


class SyncGetTransportInfoUpnpOrgAVTransport2Cpp : public SyncProxyAction
{
public:
    SyncGetTransportInfoUpnpOrgAVTransport2Cpp(CpProxyUpnpOrgAVTransport2Cpp& aService, std::string& aCurrentTransportState, std::string& aCurrentTransportStatus, std::string& aCurrentSpeed);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport2Cpp& iService;
    std::string& iCurrentTransportState;
    std::string& iCurrentTransportStatus;
    std::string& iCurrentSpeed;
};

SyncGetTransportInfoUpnpOrgAVTransport2Cpp::SyncGetTransportInfoUpnpOrgAVTransport2Cpp(CpProxyUpnpOrgAVTransport2Cpp& aService, std::string& aCurrentTransportState, std::string& aCurrentTransportStatus, std::string& aCurrentSpeed)
    : iService(aService)
    , iCurrentTransportState(aCurrentTransportState)
    , iCurrentTransportStatus(aCurrentTransportStatus)
    , iCurrentSpeed(aCurrentSpeed)
{
}

void SyncGetTransportInfoUpnpOrgAVTransport2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetTransportInfo(aAsync, iCurrentTransportState, iCurrentTransportStatus, iCurrentSpeed);
}


class SyncGetPositionInfoUpnpOrgAVTransport2Cpp : public SyncProxyAction
{
public:
    SyncGetPositionInfoUpnpOrgAVTransport2Cpp(CpProxyUpnpOrgAVTransport2Cpp& aService, uint32_t& aTrack, std::string& aTrackDuration, std::string& aTrackMetaData, std::string& aTrackURI, std::string& aRelTime, std::string& aAbsTime, int32_t& aRelCount, int32_t& aAbsCount);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport2Cpp& iService;
    uint32_t& iTrack;
    std::string& iTrackDuration;
    std::string& iTrackMetaData;
    std::string& iTrackURI;
    std::string& iRelTime;
    std::string& iAbsTime;
    int32_t& iRelCount;
    int32_t& iAbsCount;
};

SyncGetPositionInfoUpnpOrgAVTransport2Cpp::SyncGetPositionInfoUpnpOrgAVTransport2Cpp(CpProxyUpnpOrgAVTransport2Cpp& aService, uint32_t& aTrack, std::string& aTrackDuration, std::string& aTrackMetaData, std::string& aTrackURI, std::string& aRelTime, std::string& aAbsTime, int32_t& aRelCount, int32_t& aAbsCount)
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

void SyncGetPositionInfoUpnpOrgAVTransport2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetPositionInfo(aAsync, iTrack, iTrackDuration, iTrackMetaData, iTrackURI, iRelTime, iAbsTime, iRelCount, iAbsCount);
}


class SyncGetDeviceCapabilitiesUpnpOrgAVTransport2Cpp : public SyncProxyAction
{
public:
    SyncGetDeviceCapabilitiesUpnpOrgAVTransport2Cpp(CpProxyUpnpOrgAVTransport2Cpp& aService, std::string& aPlayMedia, std::string& aRecMedia, std::string& aRecQualityModes);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport2Cpp& iService;
    std::string& iPlayMedia;
    std::string& iRecMedia;
    std::string& iRecQualityModes;
};

SyncGetDeviceCapabilitiesUpnpOrgAVTransport2Cpp::SyncGetDeviceCapabilitiesUpnpOrgAVTransport2Cpp(CpProxyUpnpOrgAVTransport2Cpp& aService, std::string& aPlayMedia, std::string& aRecMedia, std::string& aRecQualityModes)
    : iService(aService)
    , iPlayMedia(aPlayMedia)
    , iRecMedia(aRecMedia)
    , iRecQualityModes(aRecQualityModes)
{
}

void SyncGetDeviceCapabilitiesUpnpOrgAVTransport2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetDeviceCapabilities(aAsync, iPlayMedia, iRecMedia, iRecQualityModes);
}


class SyncGetTransportSettingsUpnpOrgAVTransport2Cpp : public SyncProxyAction
{
public:
    SyncGetTransportSettingsUpnpOrgAVTransport2Cpp(CpProxyUpnpOrgAVTransport2Cpp& aService, std::string& aPlayMode, std::string& aRecQualityMode);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport2Cpp& iService;
    std::string& iPlayMode;
    std::string& iRecQualityMode;
};

SyncGetTransportSettingsUpnpOrgAVTransport2Cpp::SyncGetTransportSettingsUpnpOrgAVTransport2Cpp(CpProxyUpnpOrgAVTransport2Cpp& aService, std::string& aPlayMode, std::string& aRecQualityMode)
    : iService(aService)
    , iPlayMode(aPlayMode)
    , iRecQualityMode(aRecQualityMode)
{
}

void SyncGetTransportSettingsUpnpOrgAVTransport2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetTransportSettings(aAsync, iPlayMode, iRecQualityMode);
}


class SyncStopUpnpOrgAVTransport2Cpp : public SyncProxyAction
{
public:
    SyncStopUpnpOrgAVTransport2Cpp(CpProxyUpnpOrgAVTransport2Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport2Cpp& iService;
};

SyncStopUpnpOrgAVTransport2Cpp::SyncStopUpnpOrgAVTransport2Cpp(CpProxyUpnpOrgAVTransport2Cpp& aService)
    : iService(aService)
{
}

void SyncStopUpnpOrgAVTransport2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndStop(aAsync);
}


class SyncPlayUpnpOrgAVTransport2Cpp : public SyncProxyAction
{
public:
    SyncPlayUpnpOrgAVTransport2Cpp(CpProxyUpnpOrgAVTransport2Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport2Cpp& iService;
};

SyncPlayUpnpOrgAVTransport2Cpp::SyncPlayUpnpOrgAVTransport2Cpp(CpProxyUpnpOrgAVTransport2Cpp& aService)
    : iService(aService)
{
}

void SyncPlayUpnpOrgAVTransport2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndPlay(aAsync);
}


class SyncPauseUpnpOrgAVTransport2Cpp : public SyncProxyAction
{
public:
    SyncPauseUpnpOrgAVTransport2Cpp(CpProxyUpnpOrgAVTransport2Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport2Cpp& iService;
};

SyncPauseUpnpOrgAVTransport2Cpp::SyncPauseUpnpOrgAVTransport2Cpp(CpProxyUpnpOrgAVTransport2Cpp& aService)
    : iService(aService)
{
}

void SyncPauseUpnpOrgAVTransport2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndPause(aAsync);
}


class SyncRecordUpnpOrgAVTransport2Cpp : public SyncProxyAction
{
public:
    SyncRecordUpnpOrgAVTransport2Cpp(CpProxyUpnpOrgAVTransport2Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport2Cpp& iService;
};

SyncRecordUpnpOrgAVTransport2Cpp::SyncRecordUpnpOrgAVTransport2Cpp(CpProxyUpnpOrgAVTransport2Cpp& aService)
    : iService(aService)
{
}

void SyncRecordUpnpOrgAVTransport2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndRecord(aAsync);
}


class SyncSeekUpnpOrgAVTransport2Cpp : public SyncProxyAction
{
public:
    SyncSeekUpnpOrgAVTransport2Cpp(CpProxyUpnpOrgAVTransport2Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport2Cpp& iService;
};

SyncSeekUpnpOrgAVTransport2Cpp::SyncSeekUpnpOrgAVTransport2Cpp(CpProxyUpnpOrgAVTransport2Cpp& aService)
    : iService(aService)
{
}

void SyncSeekUpnpOrgAVTransport2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSeek(aAsync);
}


class SyncNextUpnpOrgAVTransport2Cpp : public SyncProxyAction
{
public:
    SyncNextUpnpOrgAVTransport2Cpp(CpProxyUpnpOrgAVTransport2Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport2Cpp& iService;
};

SyncNextUpnpOrgAVTransport2Cpp::SyncNextUpnpOrgAVTransport2Cpp(CpProxyUpnpOrgAVTransport2Cpp& aService)
    : iService(aService)
{
}

void SyncNextUpnpOrgAVTransport2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndNext(aAsync);
}


class SyncPreviousUpnpOrgAVTransport2Cpp : public SyncProxyAction
{
public:
    SyncPreviousUpnpOrgAVTransport2Cpp(CpProxyUpnpOrgAVTransport2Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport2Cpp& iService;
};

SyncPreviousUpnpOrgAVTransport2Cpp::SyncPreviousUpnpOrgAVTransport2Cpp(CpProxyUpnpOrgAVTransport2Cpp& aService)
    : iService(aService)
{
}

void SyncPreviousUpnpOrgAVTransport2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndPrevious(aAsync);
}


class SyncSetPlayModeUpnpOrgAVTransport2Cpp : public SyncProxyAction
{
public:
    SyncSetPlayModeUpnpOrgAVTransport2Cpp(CpProxyUpnpOrgAVTransport2Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport2Cpp& iService;
};

SyncSetPlayModeUpnpOrgAVTransport2Cpp::SyncSetPlayModeUpnpOrgAVTransport2Cpp(CpProxyUpnpOrgAVTransport2Cpp& aService)
    : iService(aService)
{
}

void SyncSetPlayModeUpnpOrgAVTransport2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetPlayMode(aAsync);
}


class SyncSetRecordQualityModeUpnpOrgAVTransport2Cpp : public SyncProxyAction
{
public:
    SyncSetRecordQualityModeUpnpOrgAVTransport2Cpp(CpProxyUpnpOrgAVTransport2Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport2Cpp& iService;
};

SyncSetRecordQualityModeUpnpOrgAVTransport2Cpp::SyncSetRecordQualityModeUpnpOrgAVTransport2Cpp(CpProxyUpnpOrgAVTransport2Cpp& aService)
    : iService(aService)
{
}

void SyncSetRecordQualityModeUpnpOrgAVTransport2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetRecordQualityMode(aAsync);
}


class SyncGetCurrentTransportActionsUpnpOrgAVTransport2Cpp : public SyncProxyAction
{
public:
    SyncGetCurrentTransportActionsUpnpOrgAVTransport2Cpp(CpProxyUpnpOrgAVTransport2Cpp& aService, std::string& aActions);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport2Cpp& iService;
    std::string& iActions;
};

SyncGetCurrentTransportActionsUpnpOrgAVTransport2Cpp::SyncGetCurrentTransportActionsUpnpOrgAVTransport2Cpp(CpProxyUpnpOrgAVTransport2Cpp& aService, std::string& aActions)
    : iService(aService)
    , iActions(aActions)
{
}

void SyncGetCurrentTransportActionsUpnpOrgAVTransport2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetCurrentTransportActions(aAsync, iActions);
}


class SyncGetDRMStateUpnpOrgAVTransport2Cpp : public SyncProxyAction
{
public:
    SyncGetDRMStateUpnpOrgAVTransport2Cpp(CpProxyUpnpOrgAVTransport2Cpp& aService, std::string& aCurrentDRMState);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport2Cpp& iService;
    std::string& iCurrentDRMState;
};

SyncGetDRMStateUpnpOrgAVTransport2Cpp::SyncGetDRMStateUpnpOrgAVTransport2Cpp(CpProxyUpnpOrgAVTransport2Cpp& aService, std::string& aCurrentDRMState)
    : iService(aService)
    , iCurrentDRMState(aCurrentDRMState)
{
}

void SyncGetDRMStateUpnpOrgAVTransport2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetDRMState(aAsync, iCurrentDRMState);
}


class SyncGetStateVariablesUpnpOrgAVTransport2Cpp : public SyncProxyAction
{
public:
    SyncGetStateVariablesUpnpOrgAVTransport2Cpp(CpProxyUpnpOrgAVTransport2Cpp& aService, std::string& aStateVariableValuePairs);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport2Cpp& iService;
    std::string& iStateVariableValuePairs;
};

SyncGetStateVariablesUpnpOrgAVTransport2Cpp::SyncGetStateVariablesUpnpOrgAVTransport2Cpp(CpProxyUpnpOrgAVTransport2Cpp& aService, std::string& aStateVariableValuePairs)
    : iService(aService)
    , iStateVariableValuePairs(aStateVariableValuePairs)
{
}

void SyncGetStateVariablesUpnpOrgAVTransport2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetStateVariables(aAsync, iStateVariableValuePairs);
}


class SyncSetStateVariablesUpnpOrgAVTransport2Cpp : public SyncProxyAction
{
public:
    SyncSetStateVariablesUpnpOrgAVTransport2Cpp(CpProxyUpnpOrgAVTransport2Cpp& aService, std::string& aStateVariableList);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgAVTransport2Cpp& iService;
    std::string& iStateVariableList;
};

SyncSetStateVariablesUpnpOrgAVTransport2Cpp::SyncSetStateVariablesUpnpOrgAVTransport2Cpp(CpProxyUpnpOrgAVTransport2Cpp& aService, std::string& aStateVariableList)
    : iService(aService)
    , iStateVariableList(aStateVariableList)
{
}

void SyncSetStateVariablesUpnpOrgAVTransport2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetStateVariables(aAsync, iStateVariableList);
}


CpProxyUpnpOrgAVTransport2Cpp::CpProxyUpnpOrgAVTransport2Cpp(CpDeviceCpp& aDevice)
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
    functor = MakeFunctor(*this, &CpProxyUpnpOrgAVTransport2Cpp::LastChangePropertyChanged);
    iLastChange = new PropertyString("LastChange", functor);
    iService->AddProperty(iLastChange);
    functor = MakeFunctor(*this, &CpProxyUpnpOrgAVTransport2Cpp::DRMStatePropertyChanged);
    iDRMState = new PropertyString("DRMState", functor);
    iService->AddProperty(iDRMState);
}

CpProxyUpnpOrgAVTransport2Cpp::~CpProxyUpnpOrgAVTransport2Cpp()
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

void CpProxyUpnpOrgAVTransport2Cpp::SyncSetAVTransportURI(uint32_t aInstanceID, const std::string& aCurrentURI, const std::string& aCurrentURIMetaData)
{
    SyncSetAVTransportURIUpnpOrgAVTransport2Cpp sync(*this);
    BeginSetAVTransportURI(aInstanceID, aCurrentURI, aCurrentURIMetaData, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport2Cpp::BeginSetAVTransportURI(uint32_t aInstanceID, const std::string& aCurrentURI, const std::string& aCurrentURIMetaData, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgAVTransport2Cpp::EndSetAVTransportURI(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetAVTransportURI"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgAVTransport2Cpp::SyncSetNextAVTransportURI(uint32_t aInstanceID, const std::string& aNextURI, const std::string& aNextURIMetaData)
{
    SyncSetNextAVTransportURIUpnpOrgAVTransport2Cpp sync(*this);
    BeginSetNextAVTransportURI(aInstanceID, aNextURI, aNextURIMetaData, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport2Cpp::BeginSetNextAVTransportURI(uint32_t aInstanceID, const std::string& aNextURI, const std::string& aNextURIMetaData, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgAVTransport2Cpp::EndSetNextAVTransportURI(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetNextAVTransportURI"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgAVTransport2Cpp::SyncGetMediaInfo(uint32_t aInstanceID, uint32_t& aNrTracks, std::string& aMediaDuration, std::string& aCurrentURI, std::string& aCurrentURIMetaData, std::string& aNextURI, std::string& aNextURIMetaData, std::string& aPlayMedium, std::string& aRecordMedium, std::string& aWriteStatus)
{
    SyncGetMediaInfoUpnpOrgAVTransport2Cpp sync(*this, aNrTracks, aMediaDuration, aCurrentURI, aCurrentURIMetaData, aNextURI, aNextURIMetaData, aPlayMedium, aRecordMedium, aWriteStatus);
    BeginGetMediaInfo(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport2Cpp::BeginGetMediaInfo(uint32_t aInstanceID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgAVTransport2Cpp::EndGetMediaInfo(IAsync& aAsync, uint32_t& aNrTracks, std::string& aMediaDuration, std::string& aCurrentURI, std::string& aCurrentURIMetaData, std::string& aNextURI, std::string& aNextURIMetaData, std::string& aPlayMedium, std::string& aRecordMedium, std::string& aWriteStatus)
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

void CpProxyUpnpOrgAVTransport2Cpp::SyncGetMediaInfo_Ext(uint32_t aInstanceID, std::string& aCurrentType, uint32_t& aNrTracks, std::string& aMediaDuration, std::string& aCurrentURI, std::string& aCurrentURIMetaData, std::string& aNextURI, std::string& aNextURIMetaData, std::string& aPlayMedium, std::string& aRecordMedium, std::string& aWriteStatus)
{
    SyncGetMediaInfo_ExtUpnpOrgAVTransport2Cpp sync(*this, aCurrentType, aNrTracks, aMediaDuration, aCurrentURI, aCurrentURIMetaData, aNextURI, aNextURIMetaData, aPlayMedium, aRecordMedium, aWriteStatus);
    BeginGetMediaInfo_Ext(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport2Cpp::BeginGetMediaInfo_Ext(uint32_t aInstanceID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgAVTransport2Cpp::EndGetMediaInfo_Ext(IAsync& aAsync, std::string& aCurrentType, uint32_t& aNrTracks, std::string& aMediaDuration, std::string& aCurrentURI, std::string& aCurrentURIMetaData, std::string& aNextURI, std::string& aNextURIMetaData, std::string& aPlayMedium, std::string& aRecordMedium, std::string& aWriteStatus)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetMediaInfo_Ext"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aCurrentType.assign((const char*)val.Ptr(), val.Bytes());
    }
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

void CpProxyUpnpOrgAVTransport2Cpp::SyncGetTransportInfo(uint32_t aInstanceID, std::string& aCurrentTransportState, std::string& aCurrentTransportStatus, std::string& aCurrentSpeed)
{
    SyncGetTransportInfoUpnpOrgAVTransport2Cpp sync(*this, aCurrentTransportState, aCurrentTransportStatus, aCurrentSpeed);
    BeginGetTransportInfo(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport2Cpp::BeginGetTransportInfo(uint32_t aInstanceID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgAVTransport2Cpp::EndGetTransportInfo(IAsync& aAsync, std::string& aCurrentTransportState, std::string& aCurrentTransportStatus, std::string& aCurrentSpeed)
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

void CpProxyUpnpOrgAVTransport2Cpp::SyncGetPositionInfo(uint32_t aInstanceID, uint32_t& aTrack, std::string& aTrackDuration, std::string& aTrackMetaData, std::string& aTrackURI, std::string& aRelTime, std::string& aAbsTime, int32_t& aRelCount, int32_t& aAbsCount)
{
    SyncGetPositionInfoUpnpOrgAVTransport2Cpp sync(*this, aTrack, aTrackDuration, aTrackMetaData, aTrackURI, aRelTime, aAbsTime, aRelCount, aAbsCount);
    BeginGetPositionInfo(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport2Cpp::BeginGetPositionInfo(uint32_t aInstanceID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgAVTransport2Cpp::EndGetPositionInfo(IAsync& aAsync, uint32_t& aTrack, std::string& aTrackDuration, std::string& aTrackMetaData, std::string& aTrackURI, std::string& aRelTime, std::string& aAbsTime, int32_t& aRelCount, int32_t& aAbsCount)
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

void CpProxyUpnpOrgAVTransport2Cpp::SyncGetDeviceCapabilities(uint32_t aInstanceID, std::string& aPlayMedia, std::string& aRecMedia, std::string& aRecQualityModes)
{
    SyncGetDeviceCapabilitiesUpnpOrgAVTransport2Cpp sync(*this, aPlayMedia, aRecMedia, aRecQualityModes);
    BeginGetDeviceCapabilities(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport2Cpp::BeginGetDeviceCapabilities(uint32_t aInstanceID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgAVTransport2Cpp::EndGetDeviceCapabilities(IAsync& aAsync, std::string& aPlayMedia, std::string& aRecMedia, std::string& aRecQualityModes)
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

void CpProxyUpnpOrgAVTransport2Cpp::SyncGetTransportSettings(uint32_t aInstanceID, std::string& aPlayMode, std::string& aRecQualityMode)
{
    SyncGetTransportSettingsUpnpOrgAVTransport2Cpp sync(*this, aPlayMode, aRecQualityMode);
    BeginGetTransportSettings(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport2Cpp::BeginGetTransportSettings(uint32_t aInstanceID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgAVTransport2Cpp::EndGetTransportSettings(IAsync& aAsync, std::string& aPlayMode, std::string& aRecQualityMode)
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

void CpProxyUpnpOrgAVTransport2Cpp::SyncStop(uint32_t aInstanceID)
{
    SyncStopUpnpOrgAVTransport2Cpp sync(*this);
    BeginStop(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport2Cpp::BeginStop(uint32_t aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionStop, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionStop->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->Invoke();
}

void CpProxyUpnpOrgAVTransport2Cpp::EndStop(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Stop"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgAVTransport2Cpp::SyncPlay(uint32_t aInstanceID, const std::string& aSpeed)
{
    SyncPlayUpnpOrgAVTransport2Cpp sync(*this);
    BeginPlay(aInstanceID, aSpeed, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport2Cpp::BeginPlay(uint32_t aInstanceID, const std::string& aSpeed, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgAVTransport2Cpp::EndPlay(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Play"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgAVTransport2Cpp::SyncPause(uint32_t aInstanceID)
{
    SyncPauseUpnpOrgAVTransport2Cpp sync(*this);
    BeginPause(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport2Cpp::BeginPause(uint32_t aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionPause, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionPause->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->Invoke();
}

void CpProxyUpnpOrgAVTransport2Cpp::EndPause(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Pause"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgAVTransport2Cpp::SyncRecord(uint32_t aInstanceID)
{
    SyncRecordUpnpOrgAVTransport2Cpp sync(*this);
    BeginRecord(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport2Cpp::BeginRecord(uint32_t aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionRecord, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionRecord->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->Invoke();
}

void CpProxyUpnpOrgAVTransport2Cpp::EndRecord(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Record"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgAVTransport2Cpp::SyncSeek(uint32_t aInstanceID, const std::string& aUnit, const std::string& aTarget)
{
    SyncSeekUpnpOrgAVTransport2Cpp sync(*this);
    BeginSeek(aInstanceID, aUnit, aTarget, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport2Cpp::BeginSeek(uint32_t aInstanceID, const std::string& aUnit, const std::string& aTarget, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgAVTransport2Cpp::EndSeek(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Seek"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgAVTransport2Cpp::SyncNext(uint32_t aInstanceID)
{
    SyncNextUpnpOrgAVTransport2Cpp sync(*this);
    BeginNext(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport2Cpp::BeginNext(uint32_t aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionNext, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionNext->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->Invoke();
}

void CpProxyUpnpOrgAVTransport2Cpp::EndNext(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Next"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgAVTransport2Cpp::SyncPrevious(uint32_t aInstanceID)
{
    SyncPreviousUpnpOrgAVTransport2Cpp sync(*this);
    BeginPrevious(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport2Cpp::BeginPrevious(uint32_t aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionPrevious, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionPrevious->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->Invoke();
}

void CpProxyUpnpOrgAVTransport2Cpp::EndPrevious(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Previous"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgAVTransport2Cpp::SyncSetPlayMode(uint32_t aInstanceID, const std::string& aNewPlayMode)
{
    SyncSetPlayModeUpnpOrgAVTransport2Cpp sync(*this);
    BeginSetPlayMode(aInstanceID, aNewPlayMode, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport2Cpp::BeginSetPlayMode(uint32_t aInstanceID, const std::string& aNewPlayMode, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgAVTransport2Cpp::EndSetPlayMode(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetPlayMode"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgAVTransport2Cpp::SyncSetRecordQualityMode(uint32_t aInstanceID, const std::string& aNewRecordQualityMode)
{
    SyncSetRecordQualityModeUpnpOrgAVTransport2Cpp sync(*this);
    BeginSetRecordQualityMode(aInstanceID, aNewRecordQualityMode, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport2Cpp::BeginSetRecordQualityMode(uint32_t aInstanceID, const std::string& aNewRecordQualityMode, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgAVTransport2Cpp::EndSetRecordQualityMode(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetRecordQualityMode"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgAVTransport2Cpp::SyncGetCurrentTransportActions(uint32_t aInstanceID, std::string& aActions)
{
    SyncGetCurrentTransportActionsUpnpOrgAVTransport2Cpp sync(*this, aActions);
    BeginGetCurrentTransportActions(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport2Cpp::BeginGetCurrentTransportActions(uint32_t aInstanceID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgAVTransport2Cpp::EndGetCurrentTransportActions(IAsync& aAsync, std::string& aActions)
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

void CpProxyUpnpOrgAVTransport2Cpp::SyncGetDRMState(uint32_t aInstanceID, std::string& aCurrentDRMState)
{
    SyncGetDRMStateUpnpOrgAVTransport2Cpp sync(*this, aCurrentDRMState);
    BeginGetDRMState(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport2Cpp::BeginGetDRMState(uint32_t aInstanceID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgAVTransport2Cpp::EndGetDRMState(IAsync& aAsync, std::string& aCurrentDRMState)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetDRMState"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aCurrentDRMState.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyUpnpOrgAVTransport2Cpp::SyncGetStateVariables(uint32_t aInstanceID, const std::string& aStateVariableList, std::string& aStateVariableValuePairs)
{
    SyncGetStateVariablesUpnpOrgAVTransport2Cpp sync(*this, aStateVariableValuePairs);
    BeginGetStateVariables(aInstanceID, aStateVariableList, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport2Cpp::BeginGetStateVariables(uint32_t aInstanceID, const std::string& aStateVariableList, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetStateVariables, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetStateVariables->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    {
        Brn buf((const TByte*)aStateVariableList.c_str(), aStateVariableList.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetStateVariables->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyUpnpOrgAVTransport2Cpp::EndGetStateVariables(IAsync& aAsync, std::string& aStateVariableValuePairs)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetStateVariables"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aStateVariableValuePairs.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyUpnpOrgAVTransport2Cpp::SyncSetStateVariables(uint32_t aInstanceID, const std::string& aAVTransportUDN, const std::string& aServiceType, const std::string& aServiceId, const std::string& aStateVariableValuePairs, std::string& aStateVariableList)
{
    SyncSetStateVariablesUpnpOrgAVTransport2Cpp sync(*this, aStateVariableList);
    BeginSetStateVariables(aInstanceID, aAVTransportUDN, aServiceType, aServiceId, aStateVariableValuePairs, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport2Cpp::BeginSetStateVariables(uint32_t aInstanceID, const std::string& aAVTransportUDN, const std::string& aServiceType, const std::string& aServiceId, const std::string& aStateVariableValuePairs, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetStateVariables, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetStateVariables->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    {
        Brn buf((const TByte*)aAVTransportUDN.c_str(), aAVTransportUDN.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aServiceType.c_str(), aServiceType.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aServiceId.c_str(), aServiceId.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aStateVariableValuePairs.c_str(), aStateVariableValuePairs.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionSetStateVariables->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyUpnpOrgAVTransport2Cpp::EndSetStateVariables(IAsync& aAsync, std::string& aStateVariableList)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetStateVariables"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aStateVariableList.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyUpnpOrgAVTransport2Cpp::SetPropertyLastChangeChanged(Functor& aFunctor)
{
    iLock->Wait();
    iLastChangeChanged = aFunctor;
    iLock->Signal();
}

void CpProxyUpnpOrgAVTransport2Cpp::SetPropertyDRMStateChanged(Functor& aFunctor)
{
    iLock->Wait();
    iDRMStateChanged = aFunctor;
    iLock->Signal();
}

void CpProxyUpnpOrgAVTransport2Cpp::PropertyLastChange(std::string& aLastChange) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iLastChange->Value();
    aLastChange.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyUpnpOrgAVTransport2Cpp::PropertyDRMState(std::string& aDRMState) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iDRMState->Value();
    aDRMState.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyUpnpOrgAVTransport2Cpp::LastChangePropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iLastChangeChanged != NULL) {
        iLastChangeChanged();
    }
}

void CpProxyUpnpOrgAVTransport2Cpp::DRMStatePropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iDRMStateChanged != NULL) {
        iDRMStateChanged();
    }
}

