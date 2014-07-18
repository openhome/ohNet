#include "CpUpnpOrgAVTransport2.h"
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

class CpProxyUpnpOrgAVTransport2C : public CpProxyC
{
public:
    CpProxyUpnpOrgAVTransport2C(CpDeviceC aDevice);
    ~CpProxyUpnpOrgAVTransport2C();
    //CpProxyUpnpOrgAVTransport2* Proxy() { return static_cast<CpProxyUpnpOrgAVTransport2*>(iProxy); }

    void SyncSetAVTransportURI(TUint aInstanceID, const Brx& aCurrentURI, const Brx& aCurrentURIMetaData);
    void BeginSetAVTransportURI(TUint aInstanceID, const Brx& aCurrentURI, const Brx& aCurrentURIMetaData, FunctorAsync& aFunctor);
    void EndSetAVTransportURI(IAsync& aAsync);

    void SyncSetNextAVTransportURI(TUint aInstanceID, const Brx& aNextURI, const Brx& aNextURIMetaData);
    void BeginSetNextAVTransportURI(TUint aInstanceID, const Brx& aNextURI, const Brx& aNextURIMetaData, FunctorAsync& aFunctor);
    void EndSetNextAVTransportURI(IAsync& aAsync);

    void SyncGetMediaInfo(TUint aInstanceID, TUint& aNrTracks, Brh& aMediaDuration, Brh& aCurrentURI, Brh& aCurrentURIMetaData, Brh& aNextURI, Brh& aNextURIMetaData, Brh& aPlayMedium, Brh& aRecordMedium, Brh& aWriteStatus);
    void BeginGetMediaInfo(TUint aInstanceID, FunctorAsync& aFunctor);
    void EndGetMediaInfo(IAsync& aAsync, TUint& aNrTracks, Brh& aMediaDuration, Brh& aCurrentURI, Brh& aCurrentURIMetaData, Brh& aNextURI, Brh& aNextURIMetaData, Brh& aPlayMedium, Brh& aRecordMedium, Brh& aWriteStatus);

    void SyncGetMediaInfo_Ext(TUint aInstanceID, Brh& aCurrentType, TUint& aNrTracks, Brh& aMediaDuration, Brh& aCurrentURI, Brh& aCurrentURIMetaData, Brh& aNextURI, Brh& aNextURIMetaData, Brh& aPlayMedium, Brh& aRecordMedium, Brh& aWriteStatus);
    void BeginGetMediaInfo_Ext(TUint aInstanceID, FunctorAsync& aFunctor);
    void EndGetMediaInfo_Ext(IAsync& aAsync, Brh& aCurrentType, TUint& aNrTracks, Brh& aMediaDuration, Brh& aCurrentURI, Brh& aCurrentURIMetaData, Brh& aNextURI, Brh& aNextURIMetaData, Brh& aPlayMedium, Brh& aRecordMedium, Brh& aWriteStatus);

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

    void SyncGetDRMState(TUint aInstanceID, Brh& aCurrentDRMState);
    void BeginGetDRMState(TUint aInstanceID, FunctorAsync& aFunctor);
    void EndGetDRMState(IAsync& aAsync, Brh& aCurrentDRMState);

    void SyncGetStateVariables(TUint aInstanceID, const Brx& aStateVariableList, Brh& aStateVariableValuePairs);
    void BeginGetStateVariables(TUint aInstanceID, const Brx& aStateVariableList, FunctorAsync& aFunctor);
    void EndGetStateVariables(IAsync& aAsync, Brh& aStateVariableValuePairs);

    void SyncSetStateVariables(TUint aInstanceID, const Brx& aAVTransportUDN, const Brx& aServiceType, const Brx& aServiceId, const Brx& aStateVariableValuePairs, Brh& aStateVariableList);
    void BeginSetStateVariables(TUint aInstanceID, const Brx& aAVTransportUDN, const Brx& aServiceType, const Brx& aServiceId, const Brx& aStateVariableValuePairs, FunctorAsync& aFunctor);
    void EndSetStateVariables(IAsync& aAsync, Brh& aStateVariableList);

    void SetPropertyLastChangeChanged(Functor& aFunctor);
    void SetPropertyDRMStateChanged(Functor& aFunctor);

    void PropertyLastChange(Brhz& aLastChange) const;
    void PropertyDRMState(Brhz& aDRMState) const;
private:
    void LastChangePropertyChanged();
    void DRMStatePropertyChanged();
private:
    Mutex iLock;
    Action* iActionSetAVTransportURI;
    Action* iActionSetNextAVTransportURI;
    Action* iActionGetMediaInfo;
    Action* iActionGetMediaInfo_Ext;
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
    Action* iActionGetDRMState;
    Action* iActionGetStateVariables;
    Action* iActionSetStateVariables;
    PropertyString* iLastChange;
    PropertyString* iDRMState;
    Functor iLastChangeChanged;
    Functor iDRMStateChanged;
};


class SyncSetAVTransportURIUpnpOrgAVTransport2C : public SyncProxyAction
{
public:
    SyncSetAVTransportURIUpnpOrgAVTransport2C(CpProxyUpnpOrgAVTransport2C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetAVTransportURIUpnpOrgAVTransport2C() {};
private:
    CpProxyUpnpOrgAVTransport2C& iService;
};

SyncSetAVTransportURIUpnpOrgAVTransport2C::SyncSetAVTransportURIUpnpOrgAVTransport2C(CpProxyUpnpOrgAVTransport2C& aProxy)
    : iService(aProxy)
{
}

void SyncSetAVTransportURIUpnpOrgAVTransport2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetAVTransportURI(aAsync);
}


class SyncSetNextAVTransportURIUpnpOrgAVTransport2C : public SyncProxyAction
{
public:
    SyncSetNextAVTransportURIUpnpOrgAVTransport2C(CpProxyUpnpOrgAVTransport2C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetNextAVTransportURIUpnpOrgAVTransport2C() {};
private:
    CpProxyUpnpOrgAVTransport2C& iService;
};

SyncSetNextAVTransportURIUpnpOrgAVTransport2C::SyncSetNextAVTransportURIUpnpOrgAVTransport2C(CpProxyUpnpOrgAVTransport2C& aProxy)
    : iService(aProxy)
{
}

void SyncSetNextAVTransportURIUpnpOrgAVTransport2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetNextAVTransportURI(aAsync);
}


class SyncGetMediaInfoUpnpOrgAVTransport2C : public SyncProxyAction
{
public:
    SyncGetMediaInfoUpnpOrgAVTransport2C(CpProxyUpnpOrgAVTransport2C& aProxy, TUint& aNrTracks, Brh& aMediaDuration, Brh& aCurrentURI, Brh& aCurrentURIMetaData, Brh& aNextURI, Brh& aNextURIMetaData, Brh& aPlayMedium, Brh& aRecordMedium, Brh& aWriteStatus);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetMediaInfoUpnpOrgAVTransport2C() {};
private:
    CpProxyUpnpOrgAVTransport2C& iService;
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

SyncGetMediaInfoUpnpOrgAVTransport2C::SyncGetMediaInfoUpnpOrgAVTransport2C(CpProxyUpnpOrgAVTransport2C& aProxy, TUint& aNrTracks, Brh& aMediaDuration, Brh& aCurrentURI, Brh& aCurrentURIMetaData, Brh& aNextURI, Brh& aNextURIMetaData, Brh& aPlayMedium, Brh& aRecordMedium, Brh& aWriteStatus)
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

void SyncGetMediaInfoUpnpOrgAVTransport2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetMediaInfo(aAsync, iNrTracks, iMediaDuration, iCurrentURI, iCurrentURIMetaData, iNextURI, iNextURIMetaData, iPlayMedium, iRecordMedium, iWriteStatus);
}


class SyncGetMediaInfo_ExtUpnpOrgAVTransport2C : public SyncProxyAction
{
public:
    SyncGetMediaInfo_ExtUpnpOrgAVTransport2C(CpProxyUpnpOrgAVTransport2C& aProxy, Brh& aCurrentType, TUint& aNrTracks, Brh& aMediaDuration, Brh& aCurrentURI, Brh& aCurrentURIMetaData, Brh& aNextURI, Brh& aNextURIMetaData, Brh& aPlayMedium, Brh& aRecordMedium, Brh& aWriteStatus);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetMediaInfo_ExtUpnpOrgAVTransport2C() {};
private:
    CpProxyUpnpOrgAVTransport2C& iService;
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

SyncGetMediaInfo_ExtUpnpOrgAVTransport2C::SyncGetMediaInfo_ExtUpnpOrgAVTransport2C(CpProxyUpnpOrgAVTransport2C& aProxy, Brh& aCurrentType, TUint& aNrTracks, Brh& aMediaDuration, Brh& aCurrentURI, Brh& aCurrentURIMetaData, Brh& aNextURI, Brh& aNextURIMetaData, Brh& aPlayMedium, Brh& aRecordMedium, Brh& aWriteStatus)
    : iService(aProxy)
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

void SyncGetMediaInfo_ExtUpnpOrgAVTransport2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetMediaInfo_Ext(aAsync, iCurrentType, iNrTracks, iMediaDuration, iCurrentURI, iCurrentURIMetaData, iNextURI, iNextURIMetaData, iPlayMedium, iRecordMedium, iWriteStatus);
}


class SyncGetTransportInfoUpnpOrgAVTransport2C : public SyncProxyAction
{
public:
    SyncGetTransportInfoUpnpOrgAVTransport2C(CpProxyUpnpOrgAVTransport2C& aProxy, Brh& aCurrentTransportState, Brh& aCurrentTransportStatus, Brh& aCurrentSpeed);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetTransportInfoUpnpOrgAVTransport2C() {};
private:
    CpProxyUpnpOrgAVTransport2C& iService;
    Brh& iCurrentTransportState;
    Brh& iCurrentTransportStatus;
    Brh& iCurrentSpeed;
};

SyncGetTransportInfoUpnpOrgAVTransport2C::SyncGetTransportInfoUpnpOrgAVTransport2C(CpProxyUpnpOrgAVTransport2C& aProxy, Brh& aCurrentTransportState, Brh& aCurrentTransportStatus, Brh& aCurrentSpeed)
    : iService(aProxy)
    , iCurrentTransportState(aCurrentTransportState)
    , iCurrentTransportStatus(aCurrentTransportStatus)
    , iCurrentSpeed(aCurrentSpeed)
{
}

void SyncGetTransportInfoUpnpOrgAVTransport2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetTransportInfo(aAsync, iCurrentTransportState, iCurrentTransportStatus, iCurrentSpeed);
}


class SyncGetPositionInfoUpnpOrgAVTransport2C : public SyncProxyAction
{
public:
    SyncGetPositionInfoUpnpOrgAVTransport2C(CpProxyUpnpOrgAVTransport2C& aProxy, TUint& aTrack, Brh& aTrackDuration, Brh& aTrackMetaData, Brh& aTrackURI, Brh& aRelTime, Brh& aAbsTime, TInt& aRelCount, TInt& aAbsCount);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetPositionInfoUpnpOrgAVTransport2C() {};
private:
    CpProxyUpnpOrgAVTransport2C& iService;
    TUint& iTrack;
    Brh& iTrackDuration;
    Brh& iTrackMetaData;
    Brh& iTrackURI;
    Brh& iRelTime;
    Brh& iAbsTime;
    TInt& iRelCount;
    TInt& iAbsCount;
};

SyncGetPositionInfoUpnpOrgAVTransport2C::SyncGetPositionInfoUpnpOrgAVTransport2C(CpProxyUpnpOrgAVTransport2C& aProxy, TUint& aTrack, Brh& aTrackDuration, Brh& aTrackMetaData, Brh& aTrackURI, Brh& aRelTime, Brh& aAbsTime, TInt& aRelCount, TInt& aAbsCount)
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

void SyncGetPositionInfoUpnpOrgAVTransport2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetPositionInfo(aAsync, iTrack, iTrackDuration, iTrackMetaData, iTrackURI, iRelTime, iAbsTime, iRelCount, iAbsCount);
}


class SyncGetDeviceCapabilitiesUpnpOrgAVTransport2C : public SyncProxyAction
{
public:
    SyncGetDeviceCapabilitiesUpnpOrgAVTransport2C(CpProxyUpnpOrgAVTransport2C& aProxy, Brh& aPlayMedia, Brh& aRecMedia, Brh& aRecQualityModes);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetDeviceCapabilitiesUpnpOrgAVTransport2C() {};
private:
    CpProxyUpnpOrgAVTransport2C& iService;
    Brh& iPlayMedia;
    Brh& iRecMedia;
    Brh& iRecQualityModes;
};

SyncGetDeviceCapabilitiesUpnpOrgAVTransport2C::SyncGetDeviceCapabilitiesUpnpOrgAVTransport2C(CpProxyUpnpOrgAVTransport2C& aProxy, Brh& aPlayMedia, Brh& aRecMedia, Brh& aRecQualityModes)
    : iService(aProxy)
    , iPlayMedia(aPlayMedia)
    , iRecMedia(aRecMedia)
    , iRecQualityModes(aRecQualityModes)
{
}

void SyncGetDeviceCapabilitiesUpnpOrgAVTransport2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetDeviceCapabilities(aAsync, iPlayMedia, iRecMedia, iRecQualityModes);
}


class SyncGetTransportSettingsUpnpOrgAVTransport2C : public SyncProxyAction
{
public:
    SyncGetTransportSettingsUpnpOrgAVTransport2C(CpProxyUpnpOrgAVTransport2C& aProxy, Brh& aPlayMode, Brh& aRecQualityMode);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetTransportSettingsUpnpOrgAVTransport2C() {};
private:
    CpProxyUpnpOrgAVTransport2C& iService;
    Brh& iPlayMode;
    Brh& iRecQualityMode;
};

SyncGetTransportSettingsUpnpOrgAVTransport2C::SyncGetTransportSettingsUpnpOrgAVTransport2C(CpProxyUpnpOrgAVTransport2C& aProxy, Brh& aPlayMode, Brh& aRecQualityMode)
    : iService(aProxy)
    , iPlayMode(aPlayMode)
    , iRecQualityMode(aRecQualityMode)
{
}

void SyncGetTransportSettingsUpnpOrgAVTransport2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetTransportSettings(aAsync, iPlayMode, iRecQualityMode);
}


class SyncStopUpnpOrgAVTransport2C : public SyncProxyAction
{
public:
    SyncStopUpnpOrgAVTransport2C(CpProxyUpnpOrgAVTransport2C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncStopUpnpOrgAVTransport2C() {};
private:
    CpProxyUpnpOrgAVTransport2C& iService;
};

SyncStopUpnpOrgAVTransport2C::SyncStopUpnpOrgAVTransport2C(CpProxyUpnpOrgAVTransport2C& aProxy)
    : iService(aProxy)
{
}

void SyncStopUpnpOrgAVTransport2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndStop(aAsync);
}


class SyncPlayUpnpOrgAVTransport2C : public SyncProxyAction
{
public:
    SyncPlayUpnpOrgAVTransport2C(CpProxyUpnpOrgAVTransport2C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncPlayUpnpOrgAVTransport2C() {};
private:
    CpProxyUpnpOrgAVTransport2C& iService;
};

SyncPlayUpnpOrgAVTransport2C::SyncPlayUpnpOrgAVTransport2C(CpProxyUpnpOrgAVTransport2C& aProxy)
    : iService(aProxy)
{
}

void SyncPlayUpnpOrgAVTransport2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndPlay(aAsync);
}


class SyncPauseUpnpOrgAVTransport2C : public SyncProxyAction
{
public:
    SyncPauseUpnpOrgAVTransport2C(CpProxyUpnpOrgAVTransport2C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncPauseUpnpOrgAVTransport2C() {};
private:
    CpProxyUpnpOrgAVTransport2C& iService;
};

SyncPauseUpnpOrgAVTransport2C::SyncPauseUpnpOrgAVTransport2C(CpProxyUpnpOrgAVTransport2C& aProxy)
    : iService(aProxy)
{
}

void SyncPauseUpnpOrgAVTransport2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndPause(aAsync);
}


class SyncRecordUpnpOrgAVTransport2C : public SyncProxyAction
{
public:
    SyncRecordUpnpOrgAVTransport2C(CpProxyUpnpOrgAVTransport2C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncRecordUpnpOrgAVTransport2C() {};
private:
    CpProxyUpnpOrgAVTransport2C& iService;
};

SyncRecordUpnpOrgAVTransport2C::SyncRecordUpnpOrgAVTransport2C(CpProxyUpnpOrgAVTransport2C& aProxy)
    : iService(aProxy)
{
}

void SyncRecordUpnpOrgAVTransport2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndRecord(aAsync);
}


class SyncSeekUpnpOrgAVTransport2C : public SyncProxyAction
{
public:
    SyncSeekUpnpOrgAVTransport2C(CpProxyUpnpOrgAVTransport2C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSeekUpnpOrgAVTransport2C() {};
private:
    CpProxyUpnpOrgAVTransport2C& iService;
};

SyncSeekUpnpOrgAVTransport2C::SyncSeekUpnpOrgAVTransport2C(CpProxyUpnpOrgAVTransport2C& aProxy)
    : iService(aProxy)
{
}

void SyncSeekUpnpOrgAVTransport2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSeek(aAsync);
}


class SyncNextUpnpOrgAVTransport2C : public SyncProxyAction
{
public:
    SyncNextUpnpOrgAVTransport2C(CpProxyUpnpOrgAVTransport2C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncNextUpnpOrgAVTransport2C() {};
private:
    CpProxyUpnpOrgAVTransport2C& iService;
};

SyncNextUpnpOrgAVTransport2C::SyncNextUpnpOrgAVTransport2C(CpProxyUpnpOrgAVTransport2C& aProxy)
    : iService(aProxy)
{
}

void SyncNextUpnpOrgAVTransport2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndNext(aAsync);
}


class SyncPreviousUpnpOrgAVTransport2C : public SyncProxyAction
{
public:
    SyncPreviousUpnpOrgAVTransport2C(CpProxyUpnpOrgAVTransport2C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncPreviousUpnpOrgAVTransport2C() {};
private:
    CpProxyUpnpOrgAVTransport2C& iService;
};

SyncPreviousUpnpOrgAVTransport2C::SyncPreviousUpnpOrgAVTransport2C(CpProxyUpnpOrgAVTransport2C& aProxy)
    : iService(aProxy)
{
}

void SyncPreviousUpnpOrgAVTransport2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndPrevious(aAsync);
}


class SyncSetPlayModeUpnpOrgAVTransport2C : public SyncProxyAction
{
public:
    SyncSetPlayModeUpnpOrgAVTransport2C(CpProxyUpnpOrgAVTransport2C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetPlayModeUpnpOrgAVTransport2C() {};
private:
    CpProxyUpnpOrgAVTransport2C& iService;
};

SyncSetPlayModeUpnpOrgAVTransport2C::SyncSetPlayModeUpnpOrgAVTransport2C(CpProxyUpnpOrgAVTransport2C& aProxy)
    : iService(aProxy)
{
}

void SyncSetPlayModeUpnpOrgAVTransport2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetPlayMode(aAsync);
}


class SyncSetRecordQualityModeUpnpOrgAVTransport2C : public SyncProxyAction
{
public:
    SyncSetRecordQualityModeUpnpOrgAVTransport2C(CpProxyUpnpOrgAVTransport2C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetRecordQualityModeUpnpOrgAVTransport2C() {};
private:
    CpProxyUpnpOrgAVTransport2C& iService;
};

SyncSetRecordQualityModeUpnpOrgAVTransport2C::SyncSetRecordQualityModeUpnpOrgAVTransport2C(CpProxyUpnpOrgAVTransport2C& aProxy)
    : iService(aProxy)
{
}

void SyncSetRecordQualityModeUpnpOrgAVTransport2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetRecordQualityMode(aAsync);
}


class SyncGetCurrentTransportActionsUpnpOrgAVTransport2C : public SyncProxyAction
{
public:
    SyncGetCurrentTransportActionsUpnpOrgAVTransport2C(CpProxyUpnpOrgAVTransport2C& aProxy, Brh& aActions);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetCurrentTransportActionsUpnpOrgAVTransport2C() {};
private:
    CpProxyUpnpOrgAVTransport2C& iService;
    Brh& iActions;
};

SyncGetCurrentTransportActionsUpnpOrgAVTransport2C::SyncGetCurrentTransportActionsUpnpOrgAVTransport2C(CpProxyUpnpOrgAVTransport2C& aProxy, Brh& aActions)
    : iService(aProxy)
    , iActions(aActions)
{
}

void SyncGetCurrentTransportActionsUpnpOrgAVTransport2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetCurrentTransportActions(aAsync, iActions);
}


class SyncGetDRMStateUpnpOrgAVTransport2C : public SyncProxyAction
{
public:
    SyncGetDRMStateUpnpOrgAVTransport2C(CpProxyUpnpOrgAVTransport2C& aProxy, Brh& aCurrentDRMState);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetDRMStateUpnpOrgAVTransport2C() {};
private:
    CpProxyUpnpOrgAVTransport2C& iService;
    Brh& iCurrentDRMState;
};

SyncGetDRMStateUpnpOrgAVTransport2C::SyncGetDRMStateUpnpOrgAVTransport2C(CpProxyUpnpOrgAVTransport2C& aProxy, Brh& aCurrentDRMState)
    : iService(aProxy)
    , iCurrentDRMState(aCurrentDRMState)
{
}

void SyncGetDRMStateUpnpOrgAVTransport2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetDRMState(aAsync, iCurrentDRMState);
}


class SyncGetStateVariablesUpnpOrgAVTransport2C : public SyncProxyAction
{
public:
    SyncGetStateVariablesUpnpOrgAVTransport2C(CpProxyUpnpOrgAVTransport2C& aProxy, Brh& aStateVariableValuePairs);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetStateVariablesUpnpOrgAVTransport2C() {};
private:
    CpProxyUpnpOrgAVTransport2C& iService;
    Brh& iStateVariableValuePairs;
};

SyncGetStateVariablesUpnpOrgAVTransport2C::SyncGetStateVariablesUpnpOrgAVTransport2C(CpProxyUpnpOrgAVTransport2C& aProxy, Brh& aStateVariableValuePairs)
    : iService(aProxy)
    , iStateVariableValuePairs(aStateVariableValuePairs)
{
}

void SyncGetStateVariablesUpnpOrgAVTransport2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetStateVariables(aAsync, iStateVariableValuePairs);
}


class SyncSetStateVariablesUpnpOrgAVTransport2C : public SyncProxyAction
{
public:
    SyncSetStateVariablesUpnpOrgAVTransport2C(CpProxyUpnpOrgAVTransport2C& aProxy, Brh& aStateVariableList);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetStateVariablesUpnpOrgAVTransport2C() {};
private:
    CpProxyUpnpOrgAVTransport2C& iService;
    Brh& iStateVariableList;
};

SyncSetStateVariablesUpnpOrgAVTransport2C::SyncSetStateVariablesUpnpOrgAVTransport2C(CpProxyUpnpOrgAVTransport2C& aProxy, Brh& aStateVariableList)
    : iService(aProxy)
    , iStateVariableList(aStateVariableList)
{
}

void SyncSetStateVariablesUpnpOrgAVTransport2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetStateVariables(aAsync, iStateVariableList);
}

CpProxyUpnpOrgAVTransport2C::CpProxyUpnpOrgAVTransport2C(CpDeviceC aDevice)
    : CpProxyC("schemas-upnp-org", "AVTransport", 2, *reinterpret_cast<CpiDevice*>(aDevice))
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

    iActionGetMediaInfo_Ext = new Action("GetMediaInfo_Ext");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionGetMediaInfo_Ext->AddInputParameter(param);
    index = 0;
    allowedValues = new TChar*[3];
    allowedValues[index++] = (TChar*)"NO_MEDIA";
    allowedValues[index++] = (TChar*)"TRACK_AWARE";
    allowedValues[index++] = (TChar*)"TRACK_UNAWARE";
    param = new OpenHome::Net::ParameterString("CurrentType", allowedValues, 3);
    iActionGetMediaInfo_Ext->AddOutputParameter(param);
    delete[] allowedValues;
    param = new OpenHome::Net::ParameterUint("NrTracks", 0, 2147483647);
    iActionGetMediaInfo_Ext->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("MediaDuration");
    iActionGetMediaInfo_Ext->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("CurrentURI");
    iActionGetMediaInfo_Ext->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("CurrentURIMetaData");
    iActionGetMediaInfo_Ext->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("NextURI");
    iActionGetMediaInfo_Ext->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("NextURIMetaData");
    iActionGetMediaInfo_Ext->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("PlayMedium");
    iActionGetMediaInfo_Ext->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("RecordMedium");
    iActionGetMediaInfo_Ext->AddOutputParameter(param);
    index = 0;
    allowedValues = new TChar*[5];
    allowedValues[index++] = (TChar*)"WRITABLE";
    allowedValues[index++] = (TChar*)"PROTECTED";
    allowedValues[index++] = (TChar*)"NOT_WRITABLE";
    allowedValues[index++] = (TChar*)"UNKNOWN";
    allowedValues[index++] = (TChar*)"NOT_IMPLEMENTED";
    param = new OpenHome::Net::ParameterString("WriteStatus", allowedValues, 5);
    iActionGetMediaInfo_Ext->AddOutputParameter(param);
    delete[] allowedValues;

    iActionGetTransportInfo = new Action("GetTransportInfo");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionGetTransportInfo->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("CurrentTransportState");
    iActionGetTransportInfo->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("CurrentTransportStatus");
    iActionGetTransportInfo->AddOutputParameter(param);
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
    allowedValues = new TChar*[7];
    allowedValues[index++] = (TChar*)"NORMAL";
    allowedValues[index++] = (TChar*)"SHUFFLE";
    allowedValues[index++] = (TChar*)"REPEAT_ONE";
    allowedValues[index++] = (TChar*)"REPEAT_ALL";
    allowedValues[index++] = (TChar*)"RANDOM";
    allowedValues[index++] = (TChar*)"DIRECT_1";
    allowedValues[index++] = (TChar*)"INTRO";
    param = new OpenHome::Net::ParameterString("PlayMode", allowedValues, 7);
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
    allowedValues[index++] = (TChar*)"ABS_TIME";
    allowedValues[index++] = (TChar*)"REL_TIME";
    allowedValues[index++] = (TChar*)"ABS_COUNT";
    allowedValues[index++] = (TChar*)"REL_COUNT";
    allowedValues[index++] = (TChar*)"TRACK_NR";
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
    allowedValues = new TChar*[7];
    allowedValues[index++] = (TChar*)"NORMAL";
    allowedValues[index++] = (TChar*)"SHUFFLE";
    allowedValues[index++] = (TChar*)"REPEAT_ONE";
    allowedValues[index++] = (TChar*)"REPEAT_ALL";
    allowedValues[index++] = (TChar*)"RANDOM";
    allowedValues[index++] = (TChar*)"DIRECT_1";
    allowedValues[index++] = (TChar*)"INTRO";
    param = new OpenHome::Net::ParameterString("NewPlayMode", allowedValues, 7);
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

    iActionGetDRMState = new Action("GetDRMState");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionGetDRMState->AddInputParameter(param);
    index = 0;
    allowedValues = new TChar*[8];
    allowedValues[index++] = (TChar*)"OK";
    allowedValues[index++] = (TChar*)"UNKNOWN";
    allowedValues[index++] = (TChar*)"PROCESSING_CONTENT_KEY";
    allowedValues[index++] = (TChar*)"CONTENT_KEY_FAILURE";
    allowedValues[index++] = (TChar*)"ATTEMPTING_AUTHENTICATION";
    allowedValues[index++] = (TChar*)"FAILED_AUTHENTICATION";
    allowedValues[index++] = (TChar*)"NOT_AUTHENTICATED";
    allowedValues[index++] = (TChar*)"DEVICE_REVOCATION";
    param = new OpenHome::Net::ParameterString("CurrentDRMState", allowedValues, 8);
    iActionGetDRMState->AddOutputParameter(param);
    delete[] allowedValues;

    iActionGetStateVariables = new Action("GetStateVariables");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionGetStateVariables->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("StateVariableList");
    iActionGetStateVariables->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("StateVariableValuePairs");
    iActionGetStateVariables->AddOutputParameter(param);

    iActionSetStateVariables = new Action("SetStateVariables");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionSetStateVariables->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("AVTransportUDN");
    iActionSetStateVariables->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("ServiceType");
    iActionSetStateVariables->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("ServiceId");
    iActionSetStateVariables->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("StateVariableValuePairs");
    iActionSetStateVariables->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("StateVariableList");
    iActionSetStateVariables->AddOutputParameter(param);

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyUpnpOrgAVTransport2C::LastChangePropertyChanged);
    iLastChange = new PropertyString(reinterpret_cast<CpiDevice*>(aDevice)->GetCpStack().Env(), "LastChange", functor);
    AddProperty(iLastChange);
    functor = MakeFunctor(*this, &CpProxyUpnpOrgAVTransport2C::DRMStatePropertyChanged);
    iDRMState = new PropertyString(reinterpret_cast<CpiDevice*>(aDevice)->GetCpStack().Env(), "DRMState", functor);
    AddProperty(iDRMState);
}

CpProxyUpnpOrgAVTransport2C::~CpProxyUpnpOrgAVTransport2C()
{
    DestroyService();
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

void CpProxyUpnpOrgAVTransport2C::SyncSetAVTransportURI(TUint aInstanceID, const Brx& aCurrentURI, const Brx& aCurrentURIMetaData)
{
    SyncSetAVTransportURIUpnpOrgAVTransport2C sync(*this);
    BeginSetAVTransportURI(aInstanceID, aCurrentURI, aCurrentURIMetaData, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport2C::BeginSetAVTransportURI(TUint aInstanceID, const Brx& aCurrentURI, const Brx& aCurrentURIMetaData, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetAVTransportURI, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetAVTransportURI->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aCurrentURI));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aCurrentURIMetaData));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgAVTransport2C::EndSetAVTransportURI(IAsync& aAsync)
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

void CpProxyUpnpOrgAVTransport2C::SyncSetNextAVTransportURI(TUint aInstanceID, const Brx& aNextURI, const Brx& aNextURIMetaData)
{
    SyncSetNextAVTransportURIUpnpOrgAVTransport2C sync(*this);
    BeginSetNextAVTransportURI(aInstanceID, aNextURI, aNextURIMetaData, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport2C::BeginSetNextAVTransportURI(TUint aInstanceID, const Brx& aNextURI, const Brx& aNextURIMetaData, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetNextAVTransportURI, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetNextAVTransportURI->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aNextURI));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aNextURIMetaData));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgAVTransport2C::EndSetNextAVTransportURI(IAsync& aAsync)
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

void CpProxyUpnpOrgAVTransport2C::SyncGetMediaInfo(TUint aInstanceID, TUint& aNrTracks, Brh& aMediaDuration, Brh& aCurrentURI, Brh& aCurrentURIMetaData, Brh& aNextURI, Brh& aNextURIMetaData, Brh& aPlayMedium, Brh& aRecordMedium, Brh& aWriteStatus)
{
    SyncGetMediaInfoUpnpOrgAVTransport2C sync(*this, aNrTracks, aMediaDuration, aCurrentURI, aCurrentURIMetaData, aNextURI, aNextURIMetaData, aPlayMedium, aRecordMedium, aWriteStatus);
    BeginGetMediaInfo(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport2C::BeginGetMediaInfo(TUint aInstanceID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgAVTransport2C::EndGetMediaInfo(IAsync& aAsync, TUint& aNrTracks, Brh& aMediaDuration, Brh& aCurrentURI, Brh& aCurrentURIMetaData, Brh& aNextURI, Brh& aNextURIMetaData, Brh& aPlayMedium, Brh& aRecordMedium, Brh& aWriteStatus)
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

void CpProxyUpnpOrgAVTransport2C::SyncGetMediaInfo_Ext(TUint aInstanceID, Brh& aCurrentType, TUint& aNrTracks, Brh& aMediaDuration, Brh& aCurrentURI, Brh& aCurrentURIMetaData, Brh& aNextURI, Brh& aNextURIMetaData, Brh& aPlayMedium, Brh& aRecordMedium, Brh& aWriteStatus)
{
    SyncGetMediaInfo_ExtUpnpOrgAVTransport2C sync(*this, aCurrentType, aNrTracks, aMediaDuration, aCurrentURI, aCurrentURIMetaData, aNextURI, aNextURIMetaData, aPlayMedium, aRecordMedium, aWriteStatus);
    BeginGetMediaInfo_Ext(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport2C::BeginGetMediaInfo_Ext(TUint aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetMediaInfo_Ext, aFunctor);
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
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgAVTransport2C::EndGetMediaInfo_Ext(IAsync& aAsync, Brh& aCurrentType, TUint& aNrTracks, Brh& aMediaDuration, Brh& aCurrentURI, Brh& aCurrentURIMetaData, Brh& aNextURI, Brh& aNextURIMetaData, Brh& aPlayMedium, Brh& aRecordMedium, Brh& aWriteStatus)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetMediaInfo_Ext"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
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

void CpProxyUpnpOrgAVTransport2C::SyncGetTransportInfo(TUint aInstanceID, Brh& aCurrentTransportState, Brh& aCurrentTransportStatus, Brh& aCurrentSpeed)
{
    SyncGetTransportInfoUpnpOrgAVTransport2C sync(*this, aCurrentTransportState, aCurrentTransportStatus, aCurrentSpeed);
    BeginGetTransportInfo(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport2C::BeginGetTransportInfo(TUint aInstanceID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgAVTransport2C::EndGetTransportInfo(IAsync& aAsync, Brh& aCurrentTransportState, Brh& aCurrentTransportStatus, Brh& aCurrentSpeed)
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

void CpProxyUpnpOrgAVTransport2C::SyncGetPositionInfo(TUint aInstanceID, TUint& aTrack, Brh& aTrackDuration, Brh& aTrackMetaData, Brh& aTrackURI, Brh& aRelTime, Brh& aAbsTime, TInt& aRelCount, TInt& aAbsCount)
{
    SyncGetPositionInfoUpnpOrgAVTransport2C sync(*this, aTrack, aTrackDuration, aTrackMetaData, aTrackURI, aRelTime, aAbsTime, aRelCount, aAbsCount);
    BeginGetPositionInfo(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport2C::BeginGetPositionInfo(TUint aInstanceID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgAVTransport2C::EndGetPositionInfo(IAsync& aAsync, TUint& aTrack, Brh& aTrackDuration, Brh& aTrackMetaData, Brh& aTrackURI, Brh& aRelTime, Brh& aAbsTime, TInt& aRelCount, TInt& aAbsCount)
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

void CpProxyUpnpOrgAVTransport2C::SyncGetDeviceCapabilities(TUint aInstanceID, Brh& aPlayMedia, Brh& aRecMedia, Brh& aRecQualityModes)
{
    SyncGetDeviceCapabilitiesUpnpOrgAVTransport2C sync(*this, aPlayMedia, aRecMedia, aRecQualityModes);
    BeginGetDeviceCapabilities(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport2C::BeginGetDeviceCapabilities(TUint aInstanceID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgAVTransport2C::EndGetDeviceCapabilities(IAsync& aAsync, Brh& aPlayMedia, Brh& aRecMedia, Brh& aRecQualityModes)
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

void CpProxyUpnpOrgAVTransport2C::SyncGetTransportSettings(TUint aInstanceID, Brh& aPlayMode, Brh& aRecQualityMode)
{
    SyncGetTransportSettingsUpnpOrgAVTransport2C sync(*this, aPlayMode, aRecQualityMode);
    BeginGetTransportSettings(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport2C::BeginGetTransportSettings(TUint aInstanceID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgAVTransport2C::EndGetTransportSettings(IAsync& aAsync, Brh& aPlayMode, Brh& aRecQualityMode)
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

void CpProxyUpnpOrgAVTransport2C::SyncStop(TUint aInstanceID)
{
    SyncStopUpnpOrgAVTransport2C sync(*this);
    BeginStop(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport2C::BeginStop(TUint aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionStop, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionStop->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgAVTransport2C::EndStop(IAsync& aAsync)
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

void CpProxyUpnpOrgAVTransport2C::SyncPlay(TUint aInstanceID, const Brx& aSpeed)
{
    SyncPlayUpnpOrgAVTransport2C sync(*this);
    BeginPlay(aInstanceID, aSpeed, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport2C::BeginPlay(TUint aInstanceID, const Brx& aSpeed, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionPlay, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionPlay->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aSpeed));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgAVTransport2C::EndPlay(IAsync& aAsync)
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

void CpProxyUpnpOrgAVTransport2C::SyncPause(TUint aInstanceID)
{
    SyncPauseUpnpOrgAVTransport2C sync(*this);
    BeginPause(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport2C::BeginPause(TUint aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionPause, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionPause->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgAVTransport2C::EndPause(IAsync& aAsync)
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

void CpProxyUpnpOrgAVTransport2C::SyncRecord(TUint aInstanceID)
{
    SyncRecordUpnpOrgAVTransport2C sync(*this);
    BeginRecord(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport2C::BeginRecord(TUint aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionRecord, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionRecord->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgAVTransport2C::EndRecord(IAsync& aAsync)
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

void CpProxyUpnpOrgAVTransport2C::SyncSeek(TUint aInstanceID, const Brx& aUnit, const Brx& aTarget)
{
    SyncSeekUpnpOrgAVTransport2C sync(*this);
    BeginSeek(aInstanceID, aUnit, aTarget, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport2C::BeginSeek(TUint aInstanceID, const Brx& aUnit, const Brx& aTarget, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSeek, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSeek->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aUnit));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aTarget));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgAVTransport2C::EndSeek(IAsync& aAsync)
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

void CpProxyUpnpOrgAVTransport2C::SyncNext(TUint aInstanceID)
{
    SyncNextUpnpOrgAVTransport2C sync(*this);
    BeginNext(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport2C::BeginNext(TUint aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionNext, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionNext->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgAVTransport2C::EndNext(IAsync& aAsync)
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

void CpProxyUpnpOrgAVTransport2C::SyncPrevious(TUint aInstanceID)
{
    SyncPreviousUpnpOrgAVTransport2C sync(*this);
    BeginPrevious(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport2C::BeginPrevious(TUint aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionPrevious, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionPrevious->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgAVTransport2C::EndPrevious(IAsync& aAsync)
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

void CpProxyUpnpOrgAVTransport2C::SyncSetPlayMode(TUint aInstanceID, const Brx& aNewPlayMode)
{
    SyncSetPlayModeUpnpOrgAVTransport2C sync(*this);
    BeginSetPlayMode(aInstanceID, aNewPlayMode, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport2C::BeginSetPlayMode(TUint aInstanceID, const Brx& aNewPlayMode, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetPlayMode, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetPlayMode->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aNewPlayMode));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgAVTransport2C::EndSetPlayMode(IAsync& aAsync)
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

void CpProxyUpnpOrgAVTransport2C::SyncSetRecordQualityMode(TUint aInstanceID, const Brx& aNewRecordQualityMode)
{
    SyncSetRecordQualityModeUpnpOrgAVTransport2C sync(*this);
    BeginSetRecordQualityMode(aInstanceID, aNewRecordQualityMode, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport2C::BeginSetRecordQualityMode(TUint aInstanceID, const Brx& aNewRecordQualityMode, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetRecordQualityMode, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetRecordQualityMode->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aNewRecordQualityMode));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgAVTransport2C::EndSetRecordQualityMode(IAsync& aAsync)
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

void CpProxyUpnpOrgAVTransport2C::SyncGetCurrentTransportActions(TUint aInstanceID, Brh& aActions)
{
    SyncGetCurrentTransportActionsUpnpOrgAVTransport2C sync(*this, aActions);
    BeginGetCurrentTransportActions(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport2C::BeginGetCurrentTransportActions(TUint aInstanceID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgAVTransport2C::EndGetCurrentTransportActions(IAsync& aAsync, Brh& aActions)
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

void CpProxyUpnpOrgAVTransport2C::SyncGetDRMState(TUint aInstanceID, Brh& aCurrentDRMState)
{
    SyncGetDRMStateUpnpOrgAVTransport2C sync(*this, aCurrentDRMState);
    BeginGetDRMState(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport2C::BeginGetDRMState(TUint aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetDRMState, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetDRMState->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetDRMState->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgAVTransport2C::EndGetDRMState(IAsync& aAsync, Brh& aCurrentDRMState)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetDRMState"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aCurrentDRMState);
}

void CpProxyUpnpOrgAVTransport2C::SyncGetStateVariables(TUint aInstanceID, const Brx& aStateVariableList, Brh& aStateVariableValuePairs)
{
    SyncGetStateVariablesUpnpOrgAVTransport2C sync(*this, aStateVariableValuePairs);
    BeginGetStateVariables(aInstanceID, aStateVariableList, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport2C::BeginGetStateVariables(TUint aInstanceID, const Brx& aStateVariableList, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetStateVariables, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetStateVariables->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aStateVariableList));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetStateVariables->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgAVTransport2C::EndGetStateVariables(IAsync& aAsync, Brh& aStateVariableValuePairs)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetStateVariables"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aStateVariableValuePairs);
}

void CpProxyUpnpOrgAVTransport2C::SyncSetStateVariables(TUint aInstanceID, const Brx& aAVTransportUDN, const Brx& aServiceType, const Brx& aServiceId, const Brx& aStateVariableValuePairs, Brh& aStateVariableList)
{
    SyncSetStateVariablesUpnpOrgAVTransport2C sync(*this, aStateVariableList);
    BeginSetStateVariables(aInstanceID, aAVTransportUDN, aServiceType, aServiceId, aStateVariableValuePairs, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgAVTransport2C::BeginSetStateVariables(TUint aInstanceID, const Brx& aAVTransportUDN, const Brx& aServiceType, const Brx& aServiceId, const Brx& aStateVariableValuePairs, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetStateVariables, aFunctor);
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
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgAVTransport2C::EndSetStateVariables(IAsync& aAsync, Brh& aStateVariableList)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetStateVariables"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aStateVariableList);
}

void CpProxyUpnpOrgAVTransport2C::SetPropertyLastChangeChanged(Functor& aFunctor)
{
    iLock.Wait();
    iLastChangeChanged = aFunctor;
    iLock.Signal();
}

void CpProxyUpnpOrgAVTransport2C::SetPropertyDRMStateChanged(Functor& aFunctor)
{
    iLock.Wait();
    iDRMStateChanged = aFunctor;
    iLock.Signal();
}

void CpProxyUpnpOrgAVTransport2C::PropertyLastChange(Brhz& aLastChange) const
{
    AutoMutex a(GetPropertyReadLock());
    ASSERT(IsSubscribed());
    aLastChange.Set(iLastChange->Value());
}

void CpProxyUpnpOrgAVTransport2C::PropertyDRMState(Brhz& aDRMState) const
{
    AutoMutex a(GetPropertyReadLock());
    ASSERT(IsSubscribed());
    aDRMState.Set(iDRMState->Value());
}

void CpProxyUpnpOrgAVTransport2C::LastChangePropertyChanged()
{
    ReportEvent(iLastChangeChanged);
}

void CpProxyUpnpOrgAVTransport2C::DRMStatePropertyChanged()
{
    ReportEvent(iDRMStateChanged);
}


THandle STDCALL CpProxyUpnpOrgAVTransport2Create(CpDeviceC aDevice)
{
    return new CpProxyUpnpOrgAVTransport2C(aDevice);
}

void STDCALL CpProxyUpnpOrgAVTransport2Destroy(THandle aHandle)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    delete proxyC;
}

int32_t STDCALL CpProxyUpnpOrgAVTransport2SyncSetAVTransportURI(THandle aHandle, uint32_t aInstanceID, const char* aCurrentURI, const char* aCurrentURIMetaData)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
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

void STDCALL CpProxyUpnpOrgAVTransport2BeginSetAVTransportURI(THandle aHandle, uint32_t aInstanceID, const char* aCurrentURI, const char* aCurrentURIMetaData, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aCurrentURI(aCurrentURI);
    Brh buf_aCurrentURIMetaData(aCurrentURIMetaData);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSetAVTransportURI(aInstanceID, buf_aCurrentURI, buf_aCurrentURIMetaData, functor);
}

int32_t STDCALL CpProxyUpnpOrgAVTransport2EndSetAVTransportURI(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgAVTransport2SyncSetNextAVTransportURI(THandle aHandle, uint32_t aInstanceID, const char* aNextURI, const char* aNextURIMetaData)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
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

void STDCALL CpProxyUpnpOrgAVTransport2BeginSetNextAVTransportURI(THandle aHandle, uint32_t aInstanceID, const char* aNextURI, const char* aNextURIMetaData, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aNextURI(aNextURI);
    Brh buf_aNextURIMetaData(aNextURIMetaData);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSetNextAVTransportURI(aInstanceID, buf_aNextURI, buf_aNextURIMetaData, functor);
}

int32_t STDCALL CpProxyUpnpOrgAVTransport2EndSetNextAVTransportURI(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgAVTransport2SyncGetMediaInfo(THandle aHandle, uint32_t aInstanceID, uint32_t* aNrTracks, char** aMediaDuration, char** aCurrentURI, char** aCurrentURIMetaData, char** aNextURI, char** aNextURIMetaData, char** aPlayMedium, char** aRecordMedium, char** aWriteStatus)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
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

void STDCALL CpProxyUpnpOrgAVTransport2BeginGetMediaInfo(THandle aHandle, uint32_t aInstanceID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetMediaInfo(aInstanceID, functor);
}

int32_t STDCALL CpProxyUpnpOrgAVTransport2EndGetMediaInfo(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aNrTracks, char** aMediaDuration, char** aCurrentURI, char** aCurrentURIMetaData, char** aNextURI, char** aNextURIMetaData, char** aPlayMedium, char** aRecordMedium, char** aWriteStatus)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgAVTransport2SyncGetMediaInfo_Ext(THandle aHandle, uint32_t aInstanceID, char** aCurrentType, uint32_t* aNrTracks, char** aMediaDuration, char** aCurrentURI, char** aCurrentURIMetaData, char** aNextURI, char** aNextURIMetaData, char** aPlayMedium, char** aRecordMedium, char** aWriteStatus)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aCurrentType;
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
        proxyC->SyncGetMediaInfo_Ext(aInstanceID, buf_aCurrentType, *aNrTracks, buf_aMediaDuration, buf_aCurrentURI, buf_aCurrentURIMetaData, buf_aNextURI, buf_aNextURIMetaData, buf_aPlayMedium, buf_aRecordMedium, buf_aWriteStatus);
        *aCurrentType = buf_aCurrentType.Extract();
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
        *aCurrentType = NULL;
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

void STDCALL CpProxyUpnpOrgAVTransport2BeginGetMediaInfo_Ext(THandle aHandle, uint32_t aInstanceID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetMediaInfo_Ext(aInstanceID, functor);
}

int32_t STDCALL CpProxyUpnpOrgAVTransport2EndGetMediaInfo_Ext(THandle aHandle, OhNetHandleAsync aAsync, char** aCurrentType, uint32_t* aNrTracks, char** aMediaDuration, char** aCurrentURI, char** aCurrentURIMetaData, char** aNextURI, char** aNextURIMetaData, char** aPlayMedium, char** aRecordMedium, char** aWriteStatus)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aCurrentType;
    *aCurrentType = NULL;
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
        proxyC->EndGetMediaInfo_Ext(*async, buf_aCurrentType, *aNrTracks, buf_aMediaDuration, buf_aCurrentURI, buf_aCurrentURIMetaData, buf_aNextURI, buf_aNextURIMetaData, buf_aPlayMedium, buf_aRecordMedium, buf_aWriteStatus);
        *aCurrentType = buf_aCurrentType.Extract();
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

int32_t STDCALL CpProxyUpnpOrgAVTransport2SyncGetTransportInfo(THandle aHandle, uint32_t aInstanceID, char** aCurrentTransportState, char** aCurrentTransportStatus, char** aCurrentSpeed)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
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

void STDCALL CpProxyUpnpOrgAVTransport2BeginGetTransportInfo(THandle aHandle, uint32_t aInstanceID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetTransportInfo(aInstanceID, functor);
}

int32_t STDCALL CpProxyUpnpOrgAVTransport2EndGetTransportInfo(THandle aHandle, OhNetHandleAsync aAsync, char** aCurrentTransportState, char** aCurrentTransportStatus, char** aCurrentSpeed)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgAVTransport2SyncGetPositionInfo(THandle aHandle, uint32_t aInstanceID, uint32_t* aTrack, char** aTrackDuration, char** aTrackMetaData, char** aTrackURI, char** aRelTime, char** aAbsTime, int32_t* aRelCount, int32_t* aAbsCount)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
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

void STDCALL CpProxyUpnpOrgAVTransport2BeginGetPositionInfo(THandle aHandle, uint32_t aInstanceID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetPositionInfo(aInstanceID, functor);
}

int32_t STDCALL CpProxyUpnpOrgAVTransport2EndGetPositionInfo(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aTrack, char** aTrackDuration, char** aTrackMetaData, char** aTrackURI, char** aRelTime, char** aAbsTime, int32_t* aRelCount, int32_t* aAbsCount)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgAVTransport2SyncGetDeviceCapabilities(THandle aHandle, uint32_t aInstanceID, char** aPlayMedia, char** aRecMedia, char** aRecQualityModes)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
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

void STDCALL CpProxyUpnpOrgAVTransport2BeginGetDeviceCapabilities(THandle aHandle, uint32_t aInstanceID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetDeviceCapabilities(aInstanceID, functor);
}

int32_t STDCALL CpProxyUpnpOrgAVTransport2EndGetDeviceCapabilities(THandle aHandle, OhNetHandleAsync aAsync, char** aPlayMedia, char** aRecMedia, char** aRecQualityModes)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgAVTransport2SyncGetTransportSettings(THandle aHandle, uint32_t aInstanceID, char** aPlayMode, char** aRecQualityMode)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
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

void STDCALL CpProxyUpnpOrgAVTransport2BeginGetTransportSettings(THandle aHandle, uint32_t aInstanceID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetTransportSettings(aInstanceID, functor);
}

int32_t STDCALL CpProxyUpnpOrgAVTransport2EndGetTransportSettings(THandle aHandle, OhNetHandleAsync aAsync, char** aPlayMode, char** aRecQualityMode)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgAVTransport2SyncStop(THandle aHandle, uint32_t aInstanceID)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
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

void STDCALL CpProxyUpnpOrgAVTransport2BeginStop(THandle aHandle, uint32_t aInstanceID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginStop(aInstanceID, functor);
}

int32_t STDCALL CpProxyUpnpOrgAVTransport2EndStop(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgAVTransport2SyncPlay(THandle aHandle, uint32_t aInstanceID, const char* aSpeed)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
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

void STDCALL CpProxyUpnpOrgAVTransport2BeginPlay(THandle aHandle, uint32_t aInstanceID, const char* aSpeed, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aSpeed(aSpeed);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginPlay(aInstanceID, buf_aSpeed, functor);
}

int32_t STDCALL CpProxyUpnpOrgAVTransport2EndPlay(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgAVTransport2SyncPause(THandle aHandle, uint32_t aInstanceID)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
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

void STDCALL CpProxyUpnpOrgAVTransport2BeginPause(THandle aHandle, uint32_t aInstanceID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginPause(aInstanceID, functor);
}

int32_t STDCALL CpProxyUpnpOrgAVTransport2EndPause(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgAVTransport2SyncRecord(THandle aHandle, uint32_t aInstanceID)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
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

void STDCALL CpProxyUpnpOrgAVTransport2BeginRecord(THandle aHandle, uint32_t aInstanceID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginRecord(aInstanceID, functor);
}

int32_t STDCALL CpProxyUpnpOrgAVTransport2EndRecord(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgAVTransport2SyncSeek(THandle aHandle, uint32_t aInstanceID, const char* aUnit, const char* aTarget)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
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

void STDCALL CpProxyUpnpOrgAVTransport2BeginSeek(THandle aHandle, uint32_t aInstanceID, const char* aUnit, const char* aTarget, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aUnit(aUnit);
    Brh buf_aTarget(aTarget);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSeek(aInstanceID, buf_aUnit, buf_aTarget, functor);
}

int32_t STDCALL CpProxyUpnpOrgAVTransport2EndSeek(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgAVTransport2SyncNext(THandle aHandle, uint32_t aInstanceID)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
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

void STDCALL CpProxyUpnpOrgAVTransport2BeginNext(THandle aHandle, uint32_t aInstanceID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginNext(aInstanceID, functor);
}

int32_t STDCALL CpProxyUpnpOrgAVTransport2EndNext(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgAVTransport2SyncPrevious(THandle aHandle, uint32_t aInstanceID)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
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

void STDCALL CpProxyUpnpOrgAVTransport2BeginPrevious(THandle aHandle, uint32_t aInstanceID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginPrevious(aInstanceID, functor);
}

int32_t STDCALL CpProxyUpnpOrgAVTransport2EndPrevious(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgAVTransport2SyncSetPlayMode(THandle aHandle, uint32_t aInstanceID, const char* aNewPlayMode)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
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

void STDCALL CpProxyUpnpOrgAVTransport2BeginSetPlayMode(THandle aHandle, uint32_t aInstanceID, const char* aNewPlayMode, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aNewPlayMode(aNewPlayMode);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSetPlayMode(aInstanceID, buf_aNewPlayMode, functor);
}

int32_t STDCALL CpProxyUpnpOrgAVTransport2EndSetPlayMode(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgAVTransport2SyncSetRecordQualityMode(THandle aHandle, uint32_t aInstanceID, const char* aNewRecordQualityMode)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
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

void STDCALL CpProxyUpnpOrgAVTransport2BeginSetRecordQualityMode(THandle aHandle, uint32_t aInstanceID, const char* aNewRecordQualityMode, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aNewRecordQualityMode(aNewRecordQualityMode);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSetRecordQualityMode(aInstanceID, buf_aNewRecordQualityMode, functor);
}

int32_t STDCALL CpProxyUpnpOrgAVTransport2EndSetRecordQualityMode(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgAVTransport2SyncGetCurrentTransportActions(THandle aHandle, uint32_t aInstanceID, char** aActions)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
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

void STDCALL CpProxyUpnpOrgAVTransport2BeginGetCurrentTransportActions(THandle aHandle, uint32_t aInstanceID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetCurrentTransportActions(aInstanceID, functor);
}

int32_t STDCALL CpProxyUpnpOrgAVTransport2EndGetCurrentTransportActions(THandle aHandle, OhNetHandleAsync aAsync, char** aActions)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgAVTransport2SyncGetDRMState(THandle aHandle, uint32_t aInstanceID, char** aCurrentDRMState)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aCurrentDRMState;
    int32_t err = 0;
    try {
        proxyC->SyncGetDRMState(aInstanceID, buf_aCurrentDRMState);
        *aCurrentDRMState = buf_aCurrentDRMState.Extract();
    }
    catch (ProxyError& ) {
        err = -1;
        *aCurrentDRMState = NULL;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgAVTransport2BeginGetDRMState(THandle aHandle, uint32_t aInstanceID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetDRMState(aInstanceID, functor);
}

int32_t STDCALL CpProxyUpnpOrgAVTransport2EndGetDRMState(THandle aHandle, OhNetHandleAsync aAsync, char** aCurrentDRMState)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aCurrentDRMState;
    *aCurrentDRMState = NULL;
    try {
        proxyC->EndGetDRMState(*async, buf_aCurrentDRMState);
        *aCurrentDRMState = buf_aCurrentDRMState.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyUpnpOrgAVTransport2SyncGetStateVariables(THandle aHandle, uint32_t aInstanceID, const char* aStateVariableList, char** aStateVariableValuePairs)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aStateVariableList(aStateVariableList);
    Brh buf_aStateVariableValuePairs;
    int32_t err = 0;
    try {
        proxyC->SyncGetStateVariables(aInstanceID, buf_aStateVariableList, buf_aStateVariableValuePairs);
        *aStateVariableValuePairs = buf_aStateVariableValuePairs.Extract();
    }
    catch (ProxyError& ) {
        err = -1;
        *aStateVariableValuePairs = NULL;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgAVTransport2BeginGetStateVariables(THandle aHandle, uint32_t aInstanceID, const char* aStateVariableList, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aStateVariableList(aStateVariableList);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetStateVariables(aInstanceID, buf_aStateVariableList, functor);
}

int32_t STDCALL CpProxyUpnpOrgAVTransport2EndGetStateVariables(THandle aHandle, OhNetHandleAsync aAsync, char** aStateVariableValuePairs)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aStateVariableValuePairs;
    *aStateVariableValuePairs = NULL;
    try {
        proxyC->EndGetStateVariables(*async, buf_aStateVariableValuePairs);
        *aStateVariableValuePairs = buf_aStateVariableValuePairs.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyUpnpOrgAVTransport2SyncSetStateVariables(THandle aHandle, uint32_t aInstanceID, const char* aAVTransportUDN, const char* aServiceType, const char* aServiceId, const char* aStateVariableValuePairs, char** aStateVariableList)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aAVTransportUDN(aAVTransportUDN);
    Brh buf_aServiceType(aServiceType);
    Brh buf_aServiceId(aServiceId);
    Brh buf_aStateVariableValuePairs(aStateVariableValuePairs);
    Brh buf_aStateVariableList;
    int32_t err = 0;
    try {
        proxyC->SyncSetStateVariables(aInstanceID, buf_aAVTransportUDN, buf_aServiceType, buf_aServiceId, buf_aStateVariableValuePairs, buf_aStateVariableList);
        *aStateVariableList = buf_aStateVariableList.Extract();
    }
    catch (ProxyError& ) {
        err = -1;
        *aStateVariableList = NULL;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgAVTransport2BeginSetStateVariables(THandle aHandle, uint32_t aInstanceID, const char* aAVTransportUDN, const char* aServiceType, const char* aServiceId, const char* aStateVariableValuePairs, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aAVTransportUDN(aAVTransportUDN);
    Brh buf_aServiceType(aServiceType);
    Brh buf_aServiceId(aServiceId);
    Brh buf_aStateVariableValuePairs(aStateVariableValuePairs);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSetStateVariables(aInstanceID, buf_aAVTransportUDN, buf_aServiceType, buf_aServiceId, buf_aStateVariableValuePairs, functor);
}

int32_t STDCALL CpProxyUpnpOrgAVTransport2EndSetStateVariables(THandle aHandle, OhNetHandleAsync aAsync, char** aStateVariableList)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aStateVariableList;
    *aStateVariableList = NULL;
    try {
        proxyC->EndSetStateVariables(*async, buf_aStateVariableList);
        *aStateVariableList = buf_aStateVariableList.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgAVTransport2SetPropertyLastChangeChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyLastChangeChanged(functor);
}

void STDCALL CpProxyUpnpOrgAVTransport2SetPropertyDRMStateChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyDRMStateChanged(functor);
}

void STDCALL CpProxyUpnpOrgAVTransport2PropertyLastChange(THandle aHandle, char** aLastChange)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aLastChange;
    proxyC->PropertyLastChange(buf_aLastChange);
    *aLastChange = buf_aLastChange.Transfer();
}

void STDCALL CpProxyUpnpOrgAVTransport2PropertyDRMState(THandle aHandle, char** aDRMState)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aDRMState;
    proxyC->PropertyDRMState(buf_aDRMState);
    *aDRMState = buf_aDRMState.Transfer();
}

