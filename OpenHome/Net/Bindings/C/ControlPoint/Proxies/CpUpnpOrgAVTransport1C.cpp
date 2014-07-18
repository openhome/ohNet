#include "CpUpnpOrgAVTransport1.h"
#include <OpenHome/Net/Core/CpDevice.h>
#include <OpenHome/Net/C/CpProxyCPrivate.h>
#include <OpenHome/Net/Core/FunctorAsync.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Net/Core/CpProxy.h>
#include <OpenHome/Net/Private/CpiService.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Net/Private/AsyncPrivate.h>
#include <OpenHome/Net/Core/CpDevice.h>
#include <OpenHome/Net/Private/CpiDevice.h>

using namespace OpenHome;
using namespace OpenHome::Net;

class CpProxyUpnpOrgAVTransport1C : public CpProxyC
{
public:
    CpProxyUpnpOrgAVTransport1C(CpDeviceC aDevice);
    ~CpProxyUpnpOrgAVTransport1C();
    //CpProxyUpnpOrgAVTransport1* Proxy() { return static_cast<CpProxyUpnpOrgAVTransport1*>(iProxy); }

    void SyncSetAVTransportURI(TUint aInstanceID, const Brx& aCurrentURI, const Brx& aCurrentURIMetaData);
    void BeginSetAVTransportURI(TUint aInstanceID, const Brx& aCurrentURI, const Brx& aCurrentURIMetaData, FunctorAsync& aFunctor);
    void EndSetAVTransportURI(IAsync& aAsync);

    void SyncSetNextAVTransportURI(TUint aInstanceID, const Brx& aNextURI, const Brx& aNextURIMetaData);
    void BeginSetNextAVTransportURI(TUint aInstanceID, const Brx& aNextURI, const Brx& aNextURIMetaData, FunctorAsync& aFunctor);
    void EndSetNextAVTransportURI(IAsync& aAsync);

    void SyncGetMediaInfo(TUint aInstanceID, TUint& aNrTracks, Brh& aMediaDuration, Brh& aCurrentURI, Brh& aCurrentURIMetaData, Brh& aNextURI, Brh& aNextURIMetaData, Brh& aPlayMedium, Brh& aRecordMedium, Brh& aWriteStatus);
    void BeginGetMediaInfo(TUint aInstanceID, FunctorAsync& aFunctor);
    void EndGetMediaInfo(IAsync& aAsync, TUint& aNrTracks, Brh& aMediaDuration, Brh& aCurrentURI, Brh& aCurrentURIMetaData, Brh& aNextURI, Brh& aNextURIMetaData, Brh& aPlayMedium, Brh& aRecordMedium, Brh& aWriteStatus);

    void SyncGetTransportInfo(TUint aInstanceID, Brh& aCurrentTransportState, Brh& aCurrentTransportStatus, Brh& aCurrentSpeed);
    void BeginGetTransportInfo(TUint aInstanceID, FunctorAsync& aFunctor);
    void EndGetTransportInfo(IAsync& aAsync, Brh& aCurrentTransportState, Brh& aCurrentTransportStatus, Brh& aCurrentSpeed);

    void SyncGetPositionInfo(TUint aInstanceID, TUint& aTrack, Brh& aTrackDuration, Brh& aTrackMetaData, Brh& aTrackURI, Brh& aRelTime, Brh& aAbsTime, TInt& aRelCount, TInt& aAbsCount);
    void BeginGetPositionInfo(TUint aInstanceID, FunctorAsync& aFunctor);
    void EndGetPositionInfo(IAsync& aAsync, TUint& aTrack, Brh& aTrackDuration, Brh& aTrackMetaData, Brh& aTrackURI, Brh& aRelTime, Brh& aAbsTime, TInt& aRelCount, TInt& aAbsCount);

    void SyncGetDeviceCapabilities(TUint aInstanceID, Brh& aPlayMedia, Brh& aRecMedia, Brh& aRecQualityModes);
    void BeginGetDeviceCapabilities(TUint aInstanceID, FunctorAsync& aFunctor);
    void EndGetDeviceCapabilities(IAsync& aAsync, Brh& aPlayMedia, Brh& aRecMedia, Brh& aRecQualityModes);

    void SyncGetTransportSettings(TUint aInstanceID, Brh& aPlayMode, Brh& aRecQualityMode);
    void BeginGetTransportSettings(TUint aInstanceID, FunctorAsync& aFunctor);
    void EndGetTransportSettings(IAsync& aAsync, Brh& aPlayMode, Brh& aRecQualityMode);

    void SyncStop(TUint aInstanceID);
    void BeginStop(TUint aInstanceID, FunctorAsync& aFunctor);
    void EndStop(IAsync& aAsync);

    void SyncPlay(TUint aInstanceID, const Brx& aSpeed);
    void BeginPlay(TUint aInstanceID, const Brx& aSpeed, FunctorAsync& aFunctor);
    void EndPlay(IAsync& aAsync);

    void SyncPause(TUint aInstanceID);
    void BeginPause(TUint aInstanceID, FunctorAsync& aFunctor);
    void EndPause(IAsync& aAsync);

    void SyncRecord(TUint aInstanceID);
    void BeginRecord(TUint aInstanceID, FunctorAsync& aFunctor);
    void EndRecord(IAsync& aAsync);

    void SyncSeek(TUint aInstanceID, const Brx& aUnit, const Brx& aTarget);
    void BeginSeek(TUint aInstanceID, const Brx& aUnit, const Brx& aTarget, FunctorAsync& aFunctor);
    void EndSeek(IAsync& aAsync);

    void SyncNext(TUint aInstanceID);
    void BeginNext(TUint aInstanceID, FunctorAsync& aFunctor);
    void EndNext(IAsync& aAsync);

    void SyncPrevious(TUint aInstanceID);
    void BeginPrevious(TUint aInstanceID, FunctorAsync& aFunctor);
    void EndPrevious(IAsync& aAsync);

    void SyncSetPlayMode(TUint aInstanceID, const Brx& aNewPlayMode);
    void BeginSetPlayMode(TUint aInstanceID, const Brx& aNewPlayMode, FunctorAsync& aFunctor);
    void EndSetPlayMode(IAsync& aAsync);

    void SyncSetRecordQualityMode(TUint aInstanceID, const Brx& aNewRecordQualityMode);
    void BeginSetRecordQualityMode(TUint aInstanceID, const Brx& aNewRecordQualityMode, FunctorAsync& aFunctor);
    void EndSetRecordQualityMode(IAsync& aAsync);

    void SyncGetCurrentTransportActions(TUint aInstanceID, Brh& aActions);
    void BeginGetCurrentTransportActions(TUint aInstanceID, FunctorAsync& aFunctor);
    void EndGetCurrentTransportActions(IAsync& aAsync, Brh& aActions);

    void SetPropertyLastChangeChanged(Functor& aFunctor);

    void PropertyLastChange(Brhz& aLastChange) const;
private:
    void LastChangePropertyChanged();
private:
    Mutex iLock;
    Action* iActionSetAVTransportURI;
    Action* iActionSetNextAVTransportURI;
    Action* iActionGetMediaInfo;
    Action* iActionGetTransportInfo;
    Action* iActionGetPositionInfo;
    Action* iActionGetDeviceCapabilities;
    Action* iActionGetTransportSettings;
    Action* iActionStop;
    Action* iActionPlay;
    Action* iActionPause;
    Action* iActionRecord;
    Action* iActionSeek;
    Action* iActionNext;
    Action* iActionPrevious;
    Action* iActionSetPlayMode;
    Action* iActionSetRecordQualityMode;
    Action* iActionGetCurrentTransportActions;
    PropertyString* iLastChange;
    Functor iLastChangeChanged;
};


class SyncSetAVTransportURIUpnpOrgAVTransport1C : public SyncProxyAction
{
public:
    SyncSetAVTransportURIUpnpOrgAVTransport1C(CpProxyUpnpOrgAVTransport1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetAVTransportURIUpnpOrgAVTransport1C() {};
private:
    CpProxyUpnpOrgAVTransport1C& iService;
};

SyncSetAVTransportURIUpnpOrgAVTransport1C::SyncSetAVTransportURIUpnpOrgAVTransport1C(CpProxyUpnpOrgAVTransport1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetAVTransportURIUpnpOrgAVTransport1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetAVTransportURI(aAsync);
}


class SyncSetNextAVTransportURIUpnpOrgAVTransport1C : public SyncProxyAction
{
public:
    SyncSetNextAVTransportURIUpnpOrgAVTransport1C(CpProxyUpnpOrgAVTransport1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetNextAVTransportURIUpnpOrgAVTransport1C() {};
private:
    CpProxyUpnpOrgAVTransport1C& iService;
};

SyncSetNextAVTransportURIUpnpOrgAVTransport1C::SyncSetNextAVTransportURIUpnpOrgAVTransport1C(CpProxyUpnpOrgAVTransport1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetNextAVTransportURIUpnpOrgAVTransport1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetNextAVTransportURI(aAsync);
}


class SyncGetMediaInfoUpnpOrgAVTransport1C : public SyncProxyAction
{
public:
    SyncGetMediaInfoUpnpOrgAVTransport1C(CpProxyUpnpOrgAVTransport1C& aProxy, TUint& aNrTracks, Brh& aMediaDuration, Brh& aCurrentURI, Brh& aCurrentURIMetaData, Brh& aNextURI, Brh& aNextURIMetaData, Brh& aPlayMedium, Brh& aRecordMedium, Brh& aWriteStatus);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetMediaInfoUpnpOrgAVTransport1C() {};
private:
    CpProxyUpnpOrgAVTransport1C& iService;
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

SyncGetMediaInfoUpnpOrgAVTransport1C::SyncGetMediaInfoUpnpOrgAVTransport1C(CpProxyUpnpOrgAVTransport1C& aProxy, TUint& aNrTracks, Brh& aMediaDuration, Brh& aCurrentURI, Brh& aCurrentURIMetaData, Brh& aNextURI, Brh& aNextURIMetaData, Brh& aPlayMedium, Brh& aRecordMedium, Brh& aWriteStatus)
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

void SyncGetMediaInfoUpnpOrgAVTransport1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetMediaInfo(aAsync, iNrTracks, iMediaDuration, iCurrentURI, iCurrentURIMetaData, iNextURI, iNextURIMetaData, iPlayMedium, iRecordMedium, iWriteStatus);
}


class SyncGetTransportInfoUpnpOrgAVTransport1C : public SyncProxyAction
{
public:
    SyncGetTransportInfoUpnpOrgAVTransport1C(CpProxyUpnpOrgAVTransport1C& aProxy, Brh& aCurrentTransportState, Brh& aCurrentTransportStatus, Brh& aCurrentSpeed);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetTransportInfoUpnpOrgAVTransport1C() {};
private:
    CpProxyUpnpOrgAVTransport1C& iService;
    Brh& iCurrentTransportState;
    Brh& iCurrentTransportStatus;
    Brh& iCurrentSpeed;
};

SyncGetTransportInfoUpnpOrgAVTransport1C::SyncGetTransportInfoUpnpOrgAVTransport1C(CpProxyUpnpOrgAVTransport1C& aProxy, Brh& aCurrentTransportState, Brh& aCurrentTransportStatus, Brh& aCurrentSpeed)
    : iService(aProxy)
    , iCurrentTransportState(aCurrentTransportState)
    , iCurrentTransportStatus(aCurrentTransportStatus)
    , iCurrentSpeed(aCurrentSpeed)
{
}

void SyncGetTransportInfoUpnpOrgAVTransport1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetTransportInfo(aAsync, iCurrentTransportState, iCurrentTransportStatus, iCurrentSpeed);
}


class SyncGetPositionInfoUpnpOrgAVTransport1C : public SyncProxyAction
{
public:
    SyncGetPositionInfoUpnpOrgAVTransport1C(CpProxyUpnpOrgAVTransport1C& aProxy, TUint& aTrack, Brh& aTrackDuration, Brh& aTrackMetaData, Brh& aTrackURI, Brh& aRelTime, Brh& aAbsTime, TInt& aRelCount, TInt& aAbsCount);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetPositionInfoUpnpOrgAVTransport1C() {};
private:
    CpProxyUpnpOrgAVTransport1C& iService;
    TUint& iTrack;
    Brh& iTrackDuration;
    Brh& iTrackMetaData;
    Brh& iTrackURI;
    Brh& iRelTime;
    Brh& iAbsTime;
    TInt& iRelCount;
    TInt& iAbsCount;
};

SyncGetPositionInfoUpnpOrgAVTransport1C::SyncGetPositionInfoUpnpOrgAVTransport1C(CpProxyUpnpOrgAVTransport1C& aProxy, TUint& aTrack, Brh& aTrackDuration, Brh& aTrackMetaData, Brh& aTrackURI, Brh& aRelTime, Brh& aAbsTime, TInt& aRelCount, TInt& aAbsCount)
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

void SyncGetPositionInfoUpnpOrgAVTransport1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetPositionInfo(aAsync, iTrack, iTrackDuration, iTrackMetaData, iTrackURI, iRelTime, iAbsTime, iRelCount, iAbsCount);
}


class SyncGetDeviceCapabilitiesUpnpOrgAVTransport1C : public SyncProxyAction
{
public:
    SyncGetDeviceCapabilitiesUpnpOrgAVTransport1C(CpProxyUpnpOrgAVTransport1C& aProxy, Brh& aPlayMedia, Brh& aRecMedia, Brh& aRecQualityModes);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetDeviceCapabilitiesUpnpOrgAVTransport1C() {};
private:
    CpProxyUpnpOrgAVTransport1C& iService;
    Brh& iPlayMedia;
    Brh& iRecMedia;
    Brh& iRecQualityModes;
};

SyncGetDeviceCapabilitiesUpnpOrgAVTransport1C::SyncGetDeviceCapabilitiesUpnpOrgAVTransport1C(CpProxyUpnpOrgAVTransport1C& aProxy, Brh& aPlayMedia, Brh& aRecMedia, Brh& aRecQualityModes)
    : iService(aProxy)
    , iPlayMedia(aPlayMedia)
    , iRecMedia(aRecMedia)
    , iRecQualityModes(aRecQualityModes)
{
}

void SyncGetDeviceCapabilitiesUpnpOrgAVTransport1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetDeviceCapabilities(aAsync, iPlayMedia, iRecMedia, iRecQualityModes);
}


class SyncGetTransportSettingsUpnpOrgAVTransport1C : public SyncProxyAction
{
public:
    SyncGetTransportSettingsUpnpOrgAVTransport1C(CpProxyUpnpOrgAVTransport1C& aProxy, Brh& aPlayMode, Brh& aRecQualityMode);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetTransportSettingsUpnpOrgAVTransport1C() {};
private:
    CpProxyUpnpOrgAVTransport1C& iService;
    Brh& iPlayMode;
    Brh& iRecQualityMode;
};

SyncGetTransportSettingsUpnpOrgAVTransport1C::SyncGetTransportSettingsUpnpOrgAVTransport1C(CpProxyUpnpOrgAVTransport1C& aProxy, Brh& aPlayMode, Brh& aRecQualityMode)
    : iService(aProxy)
    , iPlayMode(aPlayMode)
    , iRecQualityMode(aRecQualityMode)
{
}

void SyncGetTransportSettingsUpnpOrgAVTransport1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetTransportSettings(aAsync, iPlayMode, iRecQualityMode);
}


class SyncStopUpnpOrgAVTransport1C : public SyncProxyAction
{
public:
    SyncStopUpnpOrgAVTransport1C(CpProxyUpnpOrgAVTransport1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncStopUpnpOrgAVTransport1C() {};
private:
    CpProxyUpnpOrgAVTransport1C& iService;
};

SyncStopUpnpOrgAVTransport1C::SyncStopUpnpOrgAVTransport1C(CpProxyUpnpOrgAVTransport1C& aProxy)
    : iService(aProxy)
{
}

void SyncStopUpnpOrgAVTransport1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndStop(aAsync);
}


class SyncPlayUpnpOrgAVTransport1C : public SyncProxyAction
{
public:
    SyncPlayUpnpOrgAVTransport1C(CpProxyUpnpOrgAVTransport1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncPlayUpnpOrgAVTransport1C() {};
private:
    CpProxyUpnpOrgAVTransport1C& iService;
};

SyncPlayUpnpOrgAVTransport1C::SyncPlayUpnpOrgAVTransport1C(CpProxyUpnpOrgAVTransport1C& aProxy)
    : iService(aProxy)
{
}

void SyncPlayUpnpOrgAVTransport1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndPlay(aAsync);
}


class SyncPauseUpnpOrgAVTransport1C : public SyncProxyAction
{
public:
    SyncPauseUpnpOrgAVTransport1C(CpProxyUpnpOrgAVTransport1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncPauseUpnpOrgAVTransport1C() {};
private:
    CpProxyUpnpOrgAVTransport1C& iService;
};

SyncPauseUpnpOrgAVTransport1C::SyncPauseUpnpOrgAVTransport1C(CpProxyUpnpOrgAVTransport1C& aProxy)
    : iService(aProxy)
{
}

void SyncPauseUpnpOrgAVTransport1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndPause(aAsync);
}


class SyncRecordUpnpOrgAVTransport1C : public SyncProxyAction
{
public:
    SyncRecordUpnpOrgAVTransport1C(CpProxyUpnpOrgAVTransport1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncRecordUpnpOrgAVTransport1C() {};
private:
    CpProxyUpnpOrgAVTransport1C& iService;
};

SyncRecordUpnpOrgAVTransport1C::SyncRecordUpnpOrgAVTransport1C(CpProxyUpnpOrgAVTransport1C& aProxy)
    : iService(aProxy)
{
}

void SyncRecordUpnpOrgAVTransport1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndRecord(aAsync);
}


class SyncSeekUpnpOrgAVTransport1C : public SyncProxyAction
{
public:
    SyncSeekUpnpOrgAVTransport1C(CpProxyUpnpOrgAVTransport1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSeekUpnpOrgAVTransport1C() {};
private:
    CpProxyUpnpOrgAVTransport1C& iService;
};

SyncSeekUpnpOrgAVTransport1C::SyncSeekUpnpOrgAVTransport1C(CpProxyUpnpOrgAVTransport1C& aProxy)
    : iService(aProxy)
{
}

void SyncSeekUpnpOrgAVTransport1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSeek(aAsync);
}


class SyncNextUpnpOrgAVTransport1C : public SyncProxyAction
{
public:
    SyncNextUpnpOrgAVTransport1C(CpProxyUpnpOrgAVTransport1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncNextUpnpOrgAVTransport1C() {};
private:
    CpProxyUpnpOrgAVTransport1C& iService;
};

SyncNextUpnpOrgAVTransport1C::SyncNextUpnpOrgAVTransport1C(CpProxyUpnpOrgAVTransport1C& aProxy)
    : iService(aProxy)
{
}

void SyncNextUpnpOrgAVTransport1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndNext(aAsync);
}


class SyncPreviousUpnpOrgAVTransport1C : public SyncProxyAction
{
public:
    SyncPreviousUpnpOrgAVTransport1C(CpProxyUpnpOrgAVTransport1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncPreviousUpnpOrgAVTransport1C() {};
private:
    CpProxyUpnpOrgAVTransport1C& iService;
};

SyncPreviousUpnpOrgAVTransport1C::SyncPreviousUpnpOrgAVTransport1C(CpProxyUpnpOrgAVTransport1C& aProxy)
    : iService(aProxy)
{
}

void SyncPreviousUpnpOrgAVTransport1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndPrevious(aAsync);
}


class SyncSetPlayModeUpnpOrgAVTransport1C : public SyncProxyAction
{
public:
    SyncSetPlayModeUpnpOrgAVTransport1C(CpProxyUpnpOrgAVTransport1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetPlayModeUpnpOrgAVTransport1C() {};
private:
    CpProxyUpnpOrgAVTransport1C& iService;
};

SyncSetPlayModeUpnpOrgAVTransport1C::SyncSetPlayModeUpnpOrgAVTransport1C(CpProxyUpnpOrgAVTransport1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetPlayModeUpnpOrgAVTransport1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetPlayMode(aAsync);
}


class SyncSetRecordQualityModeUpnpOrgAVTransport1C : public SyncProxyAction
{
public:
    SyncSetRecordQualityModeUpnpOrgAVTransport1C(CpProxyUpnpOrgAVTransport1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetRecordQualityModeUpnpOrgAVTransport1C() {};
private:
    CpProxyUpnpOrgAVTransport1C& iService;
};

SyncSetRecordQualityModeUpnpOrgAVTransport1C::SyncSetRecordQualityModeUpnpOrgAVTransport1C(CpProxyUpnpOrgAVTransport1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetRecordQualityModeUpnpOrgAVTransport1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetRecordQualityMode(aAsync);
}


class SyncGetCurrentTransportActionsUpnpOrgAVTransport1C : public SyncProxyAction
{
public:
    SyncGetCurrentTransportActionsUpnpOrgAVTransport1C(CpProxyUpnpOrgAVTransport1C& aProxy, Brh& aActions);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetCurrentTransportActionsUpnpOrgAVTransport1C() {};
private:
    CpProxyUpnpOrgAVTransport1C& iService;
    Brh& iActions;
};

SyncGetCurrentTransportActionsUpnpOrgAVTransport1C::SyncGetCurrentTransportActionsUpnpOrgAVTransport1C(CpProxyUpnpOrgAVTransport1C& aProxy, Brh& aActions)
    : iService(aProxy)
    , iActions(aActions)
{
}

void SyncGetCurrentTransportActionsUpnpOrgAVTransport1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetCurrentTransportActions(aAsync, iActions);
}

CpProxyUpnpOrgAVTransport1C::CpProxyUpnpOrgAVTransport1C(CpDeviceC aDevice)
    : CpProxyC("schemas-upnp-org", "AVTransport", 1, *reinterpret_cast<CpiDevice*>(aDevice))
    , iLock("MPCS")
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
    functor = MakeFunctor(*this, &CpProxyUpnpOrgAVTransport1C::LastChangePropertyChanged);
    iLastChange = new PropertyString(reinterpret_cast<CpiDevice*>(aDevice)->GetCpStack().Env(), "LastChange", functor);
    AddProperty(iLastChange);
}

CpProxyUpnpOrgAVTransport1C::~CpProxyUpnpOrgAVTransport1C()
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

void CpProxyUpnpOrgAVTransport1C::SyncSetAVTransportURI(TUint aInstanceID, const Brx& aCurrentURI, const Brx& aCurrentURIMetaData)
{
    SyncSetAVTransportURIUpnpOrgAVTransport1C sync(*this);
    BeginSetAVTransportURI(aInstanceID, aCurrentURI, aCurrentURIMetaData, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport1C::BeginSetAVTransportURI(TUint aInstanceID, const Brx& aCurrentURI, const Brx& aCurrentURIMetaData, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetAVTransportURI, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetAVTransportURI->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aCurrentURI));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aCurrentURIMetaData));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgAVTransport1C::EndSetAVTransportURI(IAsync& aAsync)
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

void CpProxyUpnpOrgAVTransport1C::SyncSetNextAVTransportURI(TUint aInstanceID, const Brx& aNextURI, const Brx& aNextURIMetaData)
{
    SyncSetNextAVTransportURIUpnpOrgAVTransport1C sync(*this);
    BeginSetNextAVTransportURI(aInstanceID, aNextURI, aNextURIMetaData, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport1C::BeginSetNextAVTransportURI(TUint aInstanceID, const Brx& aNextURI, const Brx& aNextURIMetaData, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetNextAVTransportURI, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetNextAVTransportURI->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aNextURI));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aNextURIMetaData));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgAVTransport1C::EndSetNextAVTransportURI(IAsync& aAsync)
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

void CpProxyUpnpOrgAVTransport1C::SyncGetMediaInfo(TUint aInstanceID, TUint& aNrTracks, Brh& aMediaDuration, Brh& aCurrentURI, Brh& aCurrentURIMetaData, Brh& aNextURI, Brh& aNextURIMetaData, Brh& aPlayMedium, Brh& aRecordMedium, Brh& aWriteStatus)
{
    SyncGetMediaInfoUpnpOrgAVTransport1C sync(*this, aNrTracks, aMediaDuration, aCurrentURI, aCurrentURIMetaData, aNextURI, aNextURIMetaData, aPlayMedium, aRecordMedium, aWriteStatus);
    BeginGetMediaInfo(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport1C::BeginGetMediaInfo(TUint aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetMediaInfo, aFunctor);
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
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgAVTransport1C::EndGetMediaInfo(IAsync& aAsync, TUint& aNrTracks, Brh& aMediaDuration, Brh& aCurrentURI, Brh& aCurrentURIMetaData, Brh& aNextURI, Brh& aNextURIMetaData, Brh& aPlayMedium, Brh& aRecordMedium, Brh& aWriteStatus)
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
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aMediaDuration);
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aCurrentURI);
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aCurrentURIMetaData);
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aNextURI);
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aNextURIMetaData);
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aPlayMedium);
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aRecordMedium);
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aWriteStatus);
}

void CpProxyUpnpOrgAVTransport1C::SyncGetTransportInfo(TUint aInstanceID, Brh& aCurrentTransportState, Brh& aCurrentTransportStatus, Brh& aCurrentSpeed)
{
    SyncGetTransportInfoUpnpOrgAVTransport1C sync(*this, aCurrentTransportState, aCurrentTransportStatus, aCurrentSpeed);
    BeginGetTransportInfo(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport1C::BeginGetTransportInfo(TUint aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetTransportInfo, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetTransportInfo->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetTransportInfo->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgAVTransport1C::EndGetTransportInfo(IAsync& aAsync, Brh& aCurrentTransportState, Brh& aCurrentTransportStatus, Brh& aCurrentSpeed)
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
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aCurrentTransportState);
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aCurrentTransportStatus);
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aCurrentSpeed);
}

void CpProxyUpnpOrgAVTransport1C::SyncGetPositionInfo(TUint aInstanceID, TUint& aTrack, Brh& aTrackDuration, Brh& aTrackMetaData, Brh& aTrackURI, Brh& aRelTime, Brh& aAbsTime, TInt& aRelCount, TInt& aAbsCount)
{
    SyncGetPositionInfoUpnpOrgAVTransport1C sync(*this, aTrack, aTrackDuration, aTrackMetaData, aTrackURI, aRelTime, aAbsTime, aRelCount, aAbsCount);
    BeginGetPositionInfo(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport1C::BeginGetPositionInfo(TUint aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetPositionInfo, aFunctor);
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
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgAVTransport1C::EndGetPositionInfo(IAsync& aAsync, TUint& aTrack, Brh& aTrackDuration, Brh& aTrackMetaData, Brh& aTrackURI, Brh& aRelTime, Brh& aAbsTime, TInt& aRelCount, TInt& aAbsCount)
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
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aTrackDuration);
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aTrackMetaData);
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aTrackURI);
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aRelTime);
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aAbsTime);
    aRelCount = ((ArgumentInt*)invocation.OutputArguments()[index++])->Value();
    aAbsCount = ((ArgumentInt*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgAVTransport1C::SyncGetDeviceCapabilities(TUint aInstanceID, Brh& aPlayMedia, Brh& aRecMedia, Brh& aRecQualityModes)
{
    SyncGetDeviceCapabilitiesUpnpOrgAVTransport1C sync(*this, aPlayMedia, aRecMedia, aRecQualityModes);
    BeginGetDeviceCapabilities(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport1C::BeginGetDeviceCapabilities(TUint aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetDeviceCapabilities, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetDeviceCapabilities->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetDeviceCapabilities->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgAVTransport1C::EndGetDeviceCapabilities(IAsync& aAsync, Brh& aPlayMedia, Brh& aRecMedia, Brh& aRecQualityModes)
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
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aPlayMedia);
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aRecMedia);
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aRecQualityModes);
}

void CpProxyUpnpOrgAVTransport1C::SyncGetTransportSettings(TUint aInstanceID, Brh& aPlayMode, Brh& aRecQualityMode)
{
    SyncGetTransportSettingsUpnpOrgAVTransport1C sync(*this, aPlayMode, aRecQualityMode);
    BeginGetTransportSettings(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport1C::BeginGetTransportSettings(TUint aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetTransportSettings, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetTransportSettings->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetTransportSettings->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgAVTransport1C::EndGetTransportSettings(IAsync& aAsync, Brh& aPlayMode, Brh& aRecQualityMode)
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
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aPlayMode);
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aRecQualityMode);
}

void CpProxyUpnpOrgAVTransport1C::SyncStop(TUint aInstanceID)
{
    SyncStopUpnpOrgAVTransport1C sync(*this);
    BeginStop(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport1C::BeginStop(TUint aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionStop, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionStop->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgAVTransport1C::EndStop(IAsync& aAsync)
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

void CpProxyUpnpOrgAVTransport1C::SyncPlay(TUint aInstanceID, const Brx& aSpeed)
{
    SyncPlayUpnpOrgAVTransport1C sync(*this);
    BeginPlay(aInstanceID, aSpeed, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport1C::BeginPlay(TUint aInstanceID, const Brx& aSpeed, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionPlay, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionPlay->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aSpeed));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgAVTransport1C::EndPlay(IAsync& aAsync)
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

void CpProxyUpnpOrgAVTransport1C::SyncPause(TUint aInstanceID)
{
    SyncPauseUpnpOrgAVTransport1C sync(*this);
    BeginPause(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport1C::BeginPause(TUint aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionPause, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionPause->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgAVTransport1C::EndPause(IAsync& aAsync)
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

void CpProxyUpnpOrgAVTransport1C::SyncRecord(TUint aInstanceID)
{
    SyncRecordUpnpOrgAVTransport1C sync(*this);
    BeginRecord(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport1C::BeginRecord(TUint aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionRecord, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionRecord->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgAVTransport1C::EndRecord(IAsync& aAsync)
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

void CpProxyUpnpOrgAVTransport1C::SyncSeek(TUint aInstanceID, const Brx& aUnit, const Brx& aTarget)
{
    SyncSeekUpnpOrgAVTransport1C sync(*this);
    BeginSeek(aInstanceID, aUnit, aTarget, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport1C::BeginSeek(TUint aInstanceID, const Brx& aUnit, const Brx& aTarget, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSeek, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSeek->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aUnit));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aTarget));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgAVTransport1C::EndSeek(IAsync& aAsync)
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

void CpProxyUpnpOrgAVTransport1C::SyncNext(TUint aInstanceID)
{
    SyncNextUpnpOrgAVTransport1C sync(*this);
    BeginNext(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport1C::BeginNext(TUint aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionNext, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionNext->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgAVTransport1C::EndNext(IAsync& aAsync)
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

void CpProxyUpnpOrgAVTransport1C::SyncPrevious(TUint aInstanceID)
{
    SyncPreviousUpnpOrgAVTransport1C sync(*this);
    BeginPrevious(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport1C::BeginPrevious(TUint aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionPrevious, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionPrevious->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgAVTransport1C::EndPrevious(IAsync& aAsync)
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

void CpProxyUpnpOrgAVTransport1C::SyncSetPlayMode(TUint aInstanceID, const Brx& aNewPlayMode)
{
    SyncSetPlayModeUpnpOrgAVTransport1C sync(*this);
    BeginSetPlayMode(aInstanceID, aNewPlayMode, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport1C::BeginSetPlayMode(TUint aInstanceID, const Brx& aNewPlayMode, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetPlayMode, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetPlayMode->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aNewPlayMode));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgAVTransport1C::EndSetPlayMode(IAsync& aAsync)
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

void CpProxyUpnpOrgAVTransport1C::SyncSetRecordQualityMode(TUint aInstanceID, const Brx& aNewRecordQualityMode)
{
    SyncSetRecordQualityModeUpnpOrgAVTransport1C sync(*this);
    BeginSetRecordQualityMode(aInstanceID, aNewRecordQualityMode, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport1C::BeginSetRecordQualityMode(TUint aInstanceID, const Brx& aNewRecordQualityMode, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetRecordQualityMode, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetRecordQualityMode->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aNewRecordQualityMode));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgAVTransport1C::EndSetRecordQualityMode(IAsync& aAsync)
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

void CpProxyUpnpOrgAVTransport1C::SyncGetCurrentTransportActions(TUint aInstanceID, Brh& aActions)
{
    SyncGetCurrentTransportActionsUpnpOrgAVTransport1C sync(*this, aActions);
    BeginGetCurrentTransportActions(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport1C::BeginGetCurrentTransportActions(TUint aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetCurrentTransportActions, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetCurrentTransportActions->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetCurrentTransportActions->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgAVTransport1C::EndGetCurrentTransportActions(IAsync& aAsync, Brh& aActions)
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
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aActions);
}

void CpProxyUpnpOrgAVTransport1C::SetPropertyLastChangeChanged(Functor& aFunctor)
{
    iLock.Wait();
    iLastChangeChanged = aFunctor;
    iLock.Signal();
}

void CpProxyUpnpOrgAVTransport1C::PropertyLastChange(Brhz& aLastChange) const
{
    AutoMutex a(GetPropertyReadLock());
    ASSERT(IsSubscribed());
    aLastChange.Set(iLastChange->Value());
}

void CpProxyUpnpOrgAVTransport1C::LastChangePropertyChanged()
{
    ReportEvent(iLastChangeChanged);
}


THandle STDCALL CpProxyUpnpOrgAVTransport1Create(CpDeviceC aDevice)
{
    return new CpProxyUpnpOrgAVTransport1C(aDevice);
}

void STDCALL CpProxyUpnpOrgAVTransport1Destroy(THandle aHandle)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    delete proxyC;
}

int32_t STDCALL CpProxyUpnpOrgAVTransport1SyncSetAVTransportURI(THandle aHandle, uint32_t aInstanceID, const char* aCurrentURI, const char* aCurrentURIMetaData)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aCurrentURI(aCurrentURI);
    Brh buf_aCurrentURIMetaData(aCurrentURIMetaData);
    int32_t err = 0;
    try {
        proxyC->SyncSetAVTransportURI(aInstanceID, buf_aCurrentURI, buf_aCurrentURIMetaData);
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgAVTransport1BeginSetAVTransportURI(THandle aHandle, uint32_t aInstanceID, const char* aCurrentURI, const char* aCurrentURIMetaData, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aCurrentURI(aCurrentURI);
    Brh buf_aCurrentURIMetaData(aCurrentURIMetaData);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSetAVTransportURI(aInstanceID, buf_aCurrentURI, buf_aCurrentURIMetaData, functor);
}

int32_t STDCALL CpProxyUpnpOrgAVTransport1EndSetAVTransportURI(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetAVTransportURI(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyUpnpOrgAVTransport1SyncSetNextAVTransportURI(THandle aHandle, uint32_t aInstanceID, const char* aNextURI, const char* aNextURIMetaData)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aNextURI(aNextURI);
    Brh buf_aNextURIMetaData(aNextURIMetaData);
    int32_t err = 0;
    try {
        proxyC->SyncSetNextAVTransportURI(aInstanceID, buf_aNextURI, buf_aNextURIMetaData);
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgAVTransport1BeginSetNextAVTransportURI(THandle aHandle, uint32_t aInstanceID, const char* aNextURI, const char* aNextURIMetaData, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aNextURI(aNextURI);
    Brh buf_aNextURIMetaData(aNextURIMetaData);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSetNextAVTransportURI(aInstanceID, buf_aNextURI, buf_aNextURIMetaData, functor);
}

int32_t STDCALL CpProxyUpnpOrgAVTransport1EndSetNextAVTransportURI(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetNextAVTransportURI(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyUpnpOrgAVTransport1SyncGetMediaInfo(THandle aHandle, uint32_t aInstanceID, uint32_t* aNrTracks, char** aMediaDuration, char** aCurrentURI, char** aCurrentURIMetaData, char** aNextURI, char** aNextURIMetaData, char** aPlayMedium, char** aRecordMedium, char** aWriteStatus)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aMediaDuration;
    Brh buf_aCurrentURI;
    Brh buf_aCurrentURIMetaData;
    Brh buf_aNextURI;
    Brh buf_aNextURIMetaData;
    Brh buf_aPlayMedium;
    Brh buf_aRecordMedium;
    Brh buf_aWriteStatus;
    int32_t err = 0;
    try {
        proxyC->SyncGetMediaInfo(aInstanceID, *aNrTracks, buf_aMediaDuration, buf_aCurrentURI, buf_aCurrentURIMetaData, buf_aNextURI, buf_aNextURIMetaData, buf_aPlayMedium, buf_aRecordMedium, buf_aWriteStatus);
        *aMediaDuration = buf_aMediaDuration.Extract();
        *aCurrentURI = buf_aCurrentURI.Extract();
        *aCurrentURIMetaData = buf_aCurrentURIMetaData.Extract();
        *aNextURI = buf_aNextURI.Extract();
        *aNextURIMetaData = buf_aNextURIMetaData.Extract();
        *aPlayMedium = buf_aPlayMedium.Extract();
        *aRecordMedium = buf_aRecordMedium.Extract();
        *aWriteStatus = buf_aWriteStatus.Extract();
    }
    catch (ProxyError& ) {
        err = -1;
        *aNrTracks = 0;
        *aMediaDuration = NULL;
        *aCurrentURI = NULL;
        *aCurrentURIMetaData = NULL;
        *aNextURI = NULL;
        *aNextURIMetaData = NULL;
        *aPlayMedium = NULL;
        *aRecordMedium = NULL;
        *aWriteStatus = NULL;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgAVTransport1BeginGetMediaInfo(THandle aHandle, uint32_t aInstanceID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetMediaInfo(aInstanceID, functor);
}

int32_t STDCALL CpProxyUpnpOrgAVTransport1EndGetMediaInfo(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aNrTracks, char** aMediaDuration, char** aCurrentURI, char** aCurrentURIMetaData, char** aNextURI, char** aNextURIMetaData, char** aPlayMedium, char** aRecordMedium, char** aWriteStatus)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aMediaDuration;
    *aMediaDuration = NULL;
    Brh buf_aCurrentURI;
    *aCurrentURI = NULL;
    Brh buf_aCurrentURIMetaData;
    *aCurrentURIMetaData = NULL;
    Brh buf_aNextURI;
    *aNextURI = NULL;
    Brh buf_aNextURIMetaData;
    *aNextURIMetaData = NULL;
    Brh buf_aPlayMedium;
    *aPlayMedium = NULL;
    Brh buf_aRecordMedium;
    *aRecordMedium = NULL;
    Brh buf_aWriteStatus;
    *aWriteStatus = NULL;
    try {
        proxyC->EndGetMediaInfo(*async, *aNrTracks, buf_aMediaDuration, buf_aCurrentURI, buf_aCurrentURIMetaData, buf_aNextURI, buf_aNextURIMetaData, buf_aPlayMedium, buf_aRecordMedium, buf_aWriteStatus);
        *aMediaDuration = buf_aMediaDuration.Extract();
        *aCurrentURI = buf_aCurrentURI.Extract();
        *aCurrentURIMetaData = buf_aCurrentURIMetaData.Extract();
        *aNextURI = buf_aNextURI.Extract();
        *aNextURIMetaData = buf_aNextURIMetaData.Extract();
        *aPlayMedium = buf_aPlayMedium.Extract();
        *aRecordMedium = buf_aRecordMedium.Extract();
        *aWriteStatus = buf_aWriteStatus.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyUpnpOrgAVTransport1SyncGetTransportInfo(THandle aHandle, uint32_t aInstanceID, char** aCurrentTransportState, char** aCurrentTransportStatus, char** aCurrentSpeed)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aCurrentTransportState;
    Brh buf_aCurrentTransportStatus;
    Brh buf_aCurrentSpeed;
    int32_t err = 0;
    try {
        proxyC->SyncGetTransportInfo(aInstanceID, buf_aCurrentTransportState, buf_aCurrentTransportStatus, buf_aCurrentSpeed);
        *aCurrentTransportState = buf_aCurrentTransportState.Extract();
        *aCurrentTransportStatus = buf_aCurrentTransportStatus.Extract();
        *aCurrentSpeed = buf_aCurrentSpeed.Extract();
    }
    catch (ProxyError& ) {
        err = -1;
        *aCurrentTransportState = NULL;
        *aCurrentTransportStatus = NULL;
        *aCurrentSpeed = NULL;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgAVTransport1BeginGetTransportInfo(THandle aHandle, uint32_t aInstanceID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetTransportInfo(aInstanceID, functor);
}

int32_t STDCALL CpProxyUpnpOrgAVTransport1EndGetTransportInfo(THandle aHandle, OhNetHandleAsync aAsync, char** aCurrentTransportState, char** aCurrentTransportStatus, char** aCurrentSpeed)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aCurrentTransportState;
    *aCurrentTransportState = NULL;
    Brh buf_aCurrentTransportStatus;
    *aCurrentTransportStatus = NULL;
    Brh buf_aCurrentSpeed;
    *aCurrentSpeed = NULL;
    try {
        proxyC->EndGetTransportInfo(*async, buf_aCurrentTransportState, buf_aCurrentTransportStatus, buf_aCurrentSpeed);
        *aCurrentTransportState = buf_aCurrentTransportState.Extract();
        *aCurrentTransportStatus = buf_aCurrentTransportStatus.Extract();
        *aCurrentSpeed = buf_aCurrentSpeed.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyUpnpOrgAVTransport1SyncGetPositionInfo(THandle aHandle, uint32_t aInstanceID, uint32_t* aTrack, char** aTrackDuration, char** aTrackMetaData, char** aTrackURI, char** aRelTime, char** aAbsTime, int32_t* aRelCount, int32_t* aAbsCount)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aTrackDuration;
    Brh buf_aTrackMetaData;
    Brh buf_aTrackURI;
    Brh buf_aRelTime;
    Brh buf_aAbsTime;
    int32_t err = 0;
    try {
        proxyC->SyncGetPositionInfo(aInstanceID, *aTrack, buf_aTrackDuration, buf_aTrackMetaData, buf_aTrackURI, buf_aRelTime, buf_aAbsTime, *aRelCount, *aAbsCount);
        *aTrackDuration = buf_aTrackDuration.Extract();
        *aTrackMetaData = buf_aTrackMetaData.Extract();
        *aTrackURI = buf_aTrackURI.Extract();
        *aRelTime = buf_aRelTime.Extract();
        *aAbsTime = buf_aAbsTime.Extract();
    }
    catch (ProxyError& ) {
        err = -1;
        *aTrack = 0;
        *aTrackDuration = NULL;
        *aTrackMetaData = NULL;
        *aTrackURI = NULL;
        *aRelTime = NULL;
        *aAbsTime = NULL;
        *aRelCount = 0;
        *aAbsCount = 0;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgAVTransport1BeginGetPositionInfo(THandle aHandle, uint32_t aInstanceID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetPositionInfo(aInstanceID, functor);
}

int32_t STDCALL CpProxyUpnpOrgAVTransport1EndGetPositionInfo(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aTrack, char** aTrackDuration, char** aTrackMetaData, char** aTrackURI, char** aRelTime, char** aAbsTime, int32_t* aRelCount, int32_t* aAbsCount)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aTrackDuration;
    *aTrackDuration = NULL;
    Brh buf_aTrackMetaData;
    *aTrackMetaData = NULL;
    Brh buf_aTrackURI;
    *aTrackURI = NULL;
    Brh buf_aRelTime;
    *aRelTime = NULL;
    Brh buf_aAbsTime;
    *aAbsTime = NULL;
    try {
        proxyC->EndGetPositionInfo(*async, *aTrack, buf_aTrackDuration, buf_aTrackMetaData, buf_aTrackURI, buf_aRelTime, buf_aAbsTime, *aRelCount, *aAbsCount);
        *aTrackDuration = buf_aTrackDuration.Extract();
        *aTrackMetaData = buf_aTrackMetaData.Extract();
        *aTrackURI = buf_aTrackURI.Extract();
        *aRelTime = buf_aRelTime.Extract();
        *aAbsTime = buf_aAbsTime.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyUpnpOrgAVTransport1SyncGetDeviceCapabilities(THandle aHandle, uint32_t aInstanceID, char** aPlayMedia, char** aRecMedia, char** aRecQualityModes)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aPlayMedia;
    Brh buf_aRecMedia;
    Brh buf_aRecQualityModes;
    int32_t err = 0;
    try {
        proxyC->SyncGetDeviceCapabilities(aInstanceID, buf_aPlayMedia, buf_aRecMedia, buf_aRecQualityModes);
        *aPlayMedia = buf_aPlayMedia.Extract();
        *aRecMedia = buf_aRecMedia.Extract();
        *aRecQualityModes = buf_aRecQualityModes.Extract();
    }
    catch (ProxyError& ) {
        err = -1;
        *aPlayMedia = NULL;
        *aRecMedia = NULL;
        *aRecQualityModes = NULL;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgAVTransport1BeginGetDeviceCapabilities(THandle aHandle, uint32_t aInstanceID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetDeviceCapabilities(aInstanceID, functor);
}

int32_t STDCALL CpProxyUpnpOrgAVTransport1EndGetDeviceCapabilities(THandle aHandle, OhNetHandleAsync aAsync, char** aPlayMedia, char** aRecMedia, char** aRecQualityModes)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aPlayMedia;
    *aPlayMedia = NULL;
    Brh buf_aRecMedia;
    *aRecMedia = NULL;
    Brh buf_aRecQualityModes;
    *aRecQualityModes = NULL;
    try {
        proxyC->EndGetDeviceCapabilities(*async, buf_aPlayMedia, buf_aRecMedia, buf_aRecQualityModes);
        *aPlayMedia = buf_aPlayMedia.Extract();
        *aRecMedia = buf_aRecMedia.Extract();
        *aRecQualityModes = buf_aRecQualityModes.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyUpnpOrgAVTransport1SyncGetTransportSettings(THandle aHandle, uint32_t aInstanceID, char** aPlayMode, char** aRecQualityMode)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aPlayMode;
    Brh buf_aRecQualityMode;
    int32_t err = 0;
    try {
        proxyC->SyncGetTransportSettings(aInstanceID, buf_aPlayMode, buf_aRecQualityMode);
        *aPlayMode = buf_aPlayMode.Extract();
        *aRecQualityMode = buf_aRecQualityMode.Extract();
    }
    catch (ProxyError& ) {
        err = -1;
        *aPlayMode = NULL;
        *aRecQualityMode = NULL;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgAVTransport1BeginGetTransportSettings(THandle aHandle, uint32_t aInstanceID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetTransportSettings(aInstanceID, functor);
}

int32_t STDCALL CpProxyUpnpOrgAVTransport1EndGetTransportSettings(THandle aHandle, OhNetHandleAsync aAsync, char** aPlayMode, char** aRecQualityMode)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aPlayMode;
    *aPlayMode = NULL;
    Brh buf_aRecQualityMode;
    *aRecQualityMode = NULL;
    try {
        proxyC->EndGetTransportSettings(*async, buf_aPlayMode, buf_aRecQualityMode);
        *aPlayMode = buf_aPlayMode.Extract();
        *aRecQualityMode = buf_aRecQualityMode.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyUpnpOrgAVTransport1SyncStop(THandle aHandle, uint32_t aInstanceID)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncStop(aInstanceID);
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgAVTransport1BeginStop(THandle aHandle, uint32_t aInstanceID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginStop(aInstanceID, functor);
}

int32_t STDCALL CpProxyUpnpOrgAVTransport1EndStop(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndStop(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyUpnpOrgAVTransport1SyncPlay(THandle aHandle, uint32_t aInstanceID, const char* aSpeed)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aSpeed(aSpeed);
    int32_t err = 0;
    try {
        proxyC->SyncPlay(aInstanceID, buf_aSpeed);
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgAVTransport1BeginPlay(THandle aHandle, uint32_t aInstanceID, const char* aSpeed, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aSpeed(aSpeed);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginPlay(aInstanceID, buf_aSpeed, functor);
}

int32_t STDCALL CpProxyUpnpOrgAVTransport1EndPlay(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndPlay(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyUpnpOrgAVTransport1SyncPause(THandle aHandle, uint32_t aInstanceID)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncPause(aInstanceID);
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgAVTransport1BeginPause(THandle aHandle, uint32_t aInstanceID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginPause(aInstanceID, functor);
}

int32_t STDCALL CpProxyUpnpOrgAVTransport1EndPause(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndPause(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyUpnpOrgAVTransport1SyncRecord(THandle aHandle, uint32_t aInstanceID)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncRecord(aInstanceID);
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgAVTransport1BeginRecord(THandle aHandle, uint32_t aInstanceID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginRecord(aInstanceID, functor);
}

int32_t STDCALL CpProxyUpnpOrgAVTransport1EndRecord(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndRecord(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyUpnpOrgAVTransport1SyncSeek(THandle aHandle, uint32_t aInstanceID, const char* aUnit, const char* aTarget)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aUnit(aUnit);
    Brh buf_aTarget(aTarget);
    int32_t err = 0;
    try {
        proxyC->SyncSeek(aInstanceID, buf_aUnit, buf_aTarget);
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgAVTransport1BeginSeek(THandle aHandle, uint32_t aInstanceID, const char* aUnit, const char* aTarget, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aUnit(aUnit);
    Brh buf_aTarget(aTarget);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSeek(aInstanceID, buf_aUnit, buf_aTarget, functor);
}

int32_t STDCALL CpProxyUpnpOrgAVTransport1EndSeek(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSeek(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyUpnpOrgAVTransport1SyncNext(THandle aHandle, uint32_t aInstanceID)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncNext(aInstanceID);
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgAVTransport1BeginNext(THandle aHandle, uint32_t aInstanceID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginNext(aInstanceID, functor);
}

int32_t STDCALL CpProxyUpnpOrgAVTransport1EndNext(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndNext(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyUpnpOrgAVTransport1SyncPrevious(THandle aHandle, uint32_t aInstanceID)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncPrevious(aInstanceID);
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgAVTransport1BeginPrevious(THandle aHandle, uint32_t aInstanceID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginPrevious(aInstanceID, functor);
}

int32_t STDCALL CpProxyUpnpOrgAVTransport1EndPrevious(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndPrevious(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyUpnpOrgAVTransport1SyncSetPlayMode(THandle aHandle, uint32_t aInstanceID, const char* aNewPlayMode)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aNewPlayMode(aNewPlayMode);
    int32_t err = 0;
    try {
        proxyC->SyncSetPlayMode(aInstanceID, buf_aNewPlayMode);
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgAVTransport1BeginSetPlayMode(THandle aHandle, uint32_t aInstanceID, const char* aNewPlayMode, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aNewPlayMode(aNewPlayMode);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSetPlayMode(aInstanceID, buf_aNewPlayMode, functor);
}

int32_t STDCALL CpProxyUpnpOrgAVTransport1EndSetPlayMode(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetPlayMode(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyUpnpOrgAVTransport1SyncSetRecordQualityMode(THandle aHandle, uint32_t aInstanceID, const char* aNewRecordQualityMode)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aNewRecordQualityMode(aNewRecordQualityMode);
    int32_t err = 0;
    try {
        proxyC->SyncSetRecordQualityMode(aInstanceID, buf_aNewRecordQualityMode);
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgAVTransport1BeginSetRecordQualityMode(THandle aHandle, uint32_t aInstanceID, const char* aNewRecordQualityMode, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aNewRecordQualityMode(aNewRecordQualityMode);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSetRecordQualityMode(aInstanceID, buf_aNewRecordQualityMode, functor);
}

int32_t STDCALL CpProxyUpnpOrgAVTransport1EndSetRecordQualityMode(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetRecordQualityMode(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyUpnpOrgAVTransport1SyncGetCurrentTransportActions(THandle aHandle, uint32_t aInstanceID, char** aActions)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aActions;
    int32_t err = 0;
    try {
        proxyC->SyncGetCurrentTransportActions(aInstanceID, buf_aActions);
        *aActions = buf_aActions.Extract();
    }
    catch (ProxyError& ) {
        err = -1;
        *aActions = NULL;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgAVTransport1BeginGetCurrentTransportActions(THandle aHandle, uint32_t aInstanceID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetCurrentTransportActions(aInstanceID, functor);
}

int32_t STDCALL CpProxyUpnpOrgAVTransport1EndGetCurrentTransportActions(THandle aHandle, OhNetHandleAsync aAsync, char** aActions)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aActions;
    *aActions = NULL;
    try {
        proxyC->EndGetCurrentTransportActions(*async, buf_aActions);
        *aActions = buf_aActions.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgAVTransport1SetPropertyLastChangeChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyLastChangeChanged(functor);
}

void STDCALL CpProxyUpnpOrgAVTransport1PropertyLastChange(THandle aHandle, char** aLastChange)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aLastChange;
    proxyC->PropertyLastChange(buf_aLastChange);
    *aLastChange = buf_aLastChange.Transfer();
}

