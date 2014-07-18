#include "CpAvOpenhomeOrgPlaylist1.h"
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

class CpProxyAvOpenhomeOrgPlaylist1C : public CpProxyC
{
public:
    CpProxyAvOpenhomeOrgPlaylist1C(CpDeviceC aDevice);
    ~CpProxyAvOpenhomeOrgPlaylist1C();
    //CpProxyAvOpenhomeOrgPlaylist1* Proxy() { return static_cast<CpProxyAvOpenhomeOrgPlaylist1*>(iProxy); }

    void SyncPlay();
    void BeginPlay(FunctorAsync& aFunctor);
    void EndPlay(IAsync& aAsync);

    void SyncPause();
    void BeginPause(FunctorAsync& aFunctor);
    void EndPause(IAsync& aAsync);

    void SyncStop();
    void BeginStop(FunctorAsync& aFunctor);
    void EndStop(IAsync& aAsync);

    void SyncNext();
    void BeginNext(FunctorAsync& aFunctor);
    void EndNext(IAsync& aAsync);

    void SyncPrevious();
    void BeginPrevious(FunctorAsync& aFunctor);
    void EndPrevious(IAsync& aAsync);

    void SyncSetRepeat(TBool aValue);
    void BeginSetRepeat(TBool aValue, FunctorAsync& aFunctor);
    void EndSetRepeat(IAsync& aAsync);

    void SyncRepeat(TBool& aValue);
    void BeginRepeat(FunctorAsync& aFunctor);
    void EndRepeat(IAsync& aAsync, TBool& aValue);

    void SyncSetShuffle(TBool aValue);
    void BeginSetShuffle(TBool aValue, FunctorAsync& aFunctor);
    void EndSetShuffle(IAsync& aAsync);

    void SyncShuffle(TBool& aValue);
    void BeginShuffle(FunctorAsync& aFunctor);
    void EndShuffle(IAsync& aAsync, TBool& aValue);

    void SyncSeekSecondAbsolute(TUint aValue);
    void BeginSeekSecondAbsolute(TUint aValue, FunctorAsync& aFunctor);
    void EndSeekSecondAbsolute(IAsync& aAsync);

    void SyncSeekSecondRelative(TInt aValue);
    void BeginSeekSecondRelative(TInt aValue, FunctorAsync& aFunctor);
    void EndSeekSecondRelative(IAsync& aAsync);

    void SyncSeekId(TUint aValue);
    void BeginSeekId(TUint aValue, FunctorAsync& aFunctor);
    void EndSeekId(IAsync& aAsync);

    void SyncSeekIndex(TUint aValue);
    void BeginSeekIndex(TUint aValue, FunctorAsync& aFunctor);
    void EndSeekIndex(IAsync& aAsync);

    void SyncTransportState(Brh& aValue);
    void BeginTransportState(FunctorAsync& aFunctor);
    void EndTransportState(IAsync& aAsync, Brh& aValue);

    void SyncId(TUint& aValue);
    void BeginId(FunctorAsync& aFunctor);
    void EndId(IAsync& aAsync, TUint& aValue);

    void SyncRead(TUint aId, Brh& aUri, Brh& aMetadata);
    void BeginRead(TUint aId, FunctorAsync& aFunctor);
    void EndRead(IAsync& aAsync, Brh& aUri, Brh& aMetadata);

    void SyncReadList(const Brx& aIdList, Brh& aTrackList);
    void BeginReadList(const Brx& aIdList, FunctorAsync& aFunctor);
    void EndReadList(IAsync& aAsync, Brh& aTrackList);

    void SyncInsert(TUint aAfterId, const Brx& aUri, const Brx& aMetadata, TUint& aNewId);
    void BeginInsert(TUint aAfterId, const Brx& aUri, const Brx& aMetadata, FunctorAsync& aFunctor);
    void EndInsert(IAsync& aAsync, TUint& aNewId);

    void SyncDeleteId(TUint aValue);
    void BeginDeleteId(TUint aValue, FunctorAsync& aFunctor);
    void EndDeleteId(IAsync& aAsync);

    void SyncDeleteAll();
    void BeginDeleteAll(FunctorAsync& aFunctor);
    void EndDeleteAll(IAsync& aAsync);

    void SyncTracksMax(TUint& aValue);
    void BeginTracksMax(FunctorAsync& aFunctor);
    void EndTracksMax(IAsync& aAsync, TUint& aValue);

    void SyncIdArray(TUint& aToken, Brh& aArray);
    void BeginIdArray(FunctorAsync& aFunctor);
    void EndIdArray(IAsync& aAsync, TUint& aToken, Brh& aArray);

    void SyncIdArrayChanged(TUint aToken, TBool& aValue);
    void BeginIdArrayChanged(TUint aToken, FunctorAsync& aFunctor);
    void EndIdArrayChanged(IAsync& aAsync, TBool& aValue);

    void SyncProtocolInfo(Brh& aValue);
    void BeginProtocolInfo(FunctorAsync& aFunctor);
    void EndProtocolInfo(IAsync& aAsync, Brh& aValue);

    void SetPropertyTransportStateChanged(Functor& aFunctor);
    void SetPropertyRepeatChanged(Functor& aFunctor);
    void SetPropertyShuffleChanged(Functor& aFunctor);
    void SetPropertyIdChanged(Functor& aFunctor);
    void SetPropertyIdArrayChanged(Functor& aFunctor);
    void SetPropertyTracksMaxChanged(Functor& aFunctor);
    void SetPropertyProtocolInfoChanged(Functor& aFunctor);

    void PropertyTransportState(Brhz& aTransportState) const;
    void PropertyRepeat(TBool& aRepeat) const;
    void PropertyShuffle(TBool& aShuffle) const;
    void PropertyId(TUint& aId) const;
    void PropertyIdArray(Brh& aIdArray) const;
    void PropertyTracksMax(TUint& aTracksMax) const;
    void PropertyProtocolInfo(Brhz& aProtocolInfo) const;
private:
    void TransportStatePropertyChanged();
    void RepeatPropertyChanged();
    void ShufflePropertyChanged();
    void IdPropertyChanged();
    void IdArrayPropertyChanged();
    void TracksMaxPropertyChanged();
    void ProtocolInfoPropertyChanged();
private:
    Mutex iLock;
    Action* iActionPlay;
    Action* iActionPause;
    Action* iActionStop;
    Action* iActionNext;
    Action* iActionPrevious;
    Action* iActionSetRepeat;
    Action* iActionRepeat;
    Action* iActionSetShuffle;
    Action* iActionShuffle;
    Action* iActionSeekSecondAbsolute;
    Action* iActionSeekSecondRelative;
    Action* iActionSeekId;
    Action* iActionSeekIndex;
    Action* iActionTransportState;
    Action* iActionId;
    Action* iActionRead;
    Action* iActionReadList;
    Action* iActionInsert;
    Action* iActionDeleteId;
    Action* iActionDeleteAll;
    Action* iActionTracksMax;
    Action* iActionIdArray;
    Action* iActionIdArrayChanged;
    Action* iActionProtocolInfo;
    PropertyString* iTransportState;
    PropertyBool* iRepeat;
    PropertyBool* iShuffle;
    PropertyUint* iId;
    PropertyBinary* iIdArray;
    PropertyUint* iTracksMax;
    PropertyString* iProtocolInfo;
    Functor iTransportStateChanged;
    Functor iRepeatChanged;
    Functor iShuffleChanged;
    Functor iIdChanged;
    Functor iIdArrayChanged;
    Functor iTracksMaxChanged;
    Functor iProtocolInfoChanged;
};


class SyncPlayAvOpenhomeOrgPlaylist1C : public SyncProxyAction
{
public:
    SyncPlayAvOpenhomeOrgPlaylist1C(CpProxyAvOpenhomeOrgPlaylist1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncPlayAvOpenhomeOrgPlaylist1C() {};
private:
    CpProxyAvOpenhomeOrgPlaylist1C& iService;
};

SyncPlayAvOpenhomeOrgPlaylist1C::SyncPlayAvOpenhomeOrgPlaylist1C(CpProxyAvOpenhomeOrgPlaylist1C& aProxy)
    : iService(aProxy)
{
}

void SyncPlayAvOpenhomeOrgPlaylist1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndPlay(aAsync);
}


class SyncPauseAvOpenhomeOrgPlaylist1C : public SyncProxyAction
{
public:
    SyncPauseAvOpenhomeOrgPlaylist1C(CpProxyAvOpenhomeOrgPlaylist1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncPauseAvOpenhomeOrgPlaylist1C() {};
private:
    CpProxyAvOpenhomeOrgPlaylist1C& iService;
};

SyncPauseAvOpenhomeOrgPlaylist1C::SyncPauseAvOpenhomeOrgPlaylist1C(CpProxyAvOpenhomeOrgPlaylist1C& aProxy)
    : iService(aProxy)
{
}

void SyncPauseAvOpenhomeOrgPlaylist1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndPause(aAsync);
}


class SyncStopAvOpenhomeOrgPlaylist1C : public SyncProxyAction
{
public:
    SyncStopAvOpenhomeOrgPlaylist1C(CpProxyAvOpenhomeOrgPlaylist1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncStopAvOpenhomeOrgPlaylist1C() {};
private:
    CpProxyAvOpenhomeOrgPlaylist1C& iService;
};

SyncStopAvOpenhomeOrgPlaylist1C::SyncStopAvOpenhomeOrgPlaylist1C(CpProxyAvOpenhomeOrgPlaylist1C& aProxy)
    : iService(aProxy)
{
}

void SyncStopAvOpenhomeOrgPlaylist1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndStop(aAsync);
}


class SyncNextAvOpenhomeOrgPlaylist1C : public SyncProxyAction
{
public:
    SyncNextAvOpenhomeOrgPlaylist1C(CpProxyAvOpenhomeOrgPlaylist1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncNextAvOpenhomeOrgPlaylist1C() {};
private:
    CpProxyAvOpenhomeOrgPlaylist1C& iService;
};

SyncNextAvOpenhomeOrgPlaylist1C::SyncNextAvOpenhomeOrgPlaylist1C(CpProxyAvOpenhomeOrgPlaylist1C& aProxy)
    : iService(aProxy)
{
}

void SyncNextAvOpenhomeOrgPlaylist1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndNext(aAsync);
}


class SyncPreviousAvOpenhomeOrgPlaylist1C : public SyncProxyAction
{
public:
    SyncPreviousAvOpenhomeOrgPlaylist1C(CpProxyAvOpenhomeOrgPlaylist1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncPreviousAvOpenhomeOrgPlaylist1C() {};
private:
    CpProxyAvOpenhomeOrgPlaylist1C& iService;
};

SyncPreviousAvOpenhomeOrgPlaylist1C::SyncPreviousAvOpenhomeOrgPlaylist1C(CpProxyAvOpenhomeOrgPlaylist1C& aProxy)
    : iService(aProxy)
{
}

void SyncPreviousAvOpenhomeOrgPlaylist1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndPrevious(aAsync);
}


class SyncSetRepeatAvOpenhomeOrgPlaylist1C : public SyncProxyAction
{
public:
    SyncSetRepeatAvOpenhomeOrgPlaylist1C(CpProxyAvOpenhomeOrgPlaylist1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetRepeatAvOpenhomeOrgPlaylist1C() {};
private:
    CpProxyAvOpenhomeOrgPlaylist1C& iService;
};

SyncSetRepeatAvOpenhomeOrgPlaylist1C::SyncSetRepeatAvOpenhomeOrgPlaylist1C(CpProxyAvOpenhomeOrgPlaylist1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetRepeatAvOpenhomeOrgPlaylist1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetRepeat(aAsync);
}


class SyncRepeatAvOpenhomeOrgPlaylist1C : public SyncProxyAction
{
public:
    SyncRepeatAvOpenhomeOrgPlaylist1C(CpProxyAvOpenhomeOrgPlaylist1C& aProxy, TBool& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncRepeatAvOpenhomeOrgPlaylist1C() {};
private:
    CpProxyAvOpenhomeOrgPlaylist1C& iService;
    TBool& iValue;
};

SyncRepeatAvOpenhomeOrgPlaylist1C::SyncRepeatAvOpenhomeOrgPlaylist1C(CpProxyAvOpenhomeOrgPlaylist1C& aProxy, TBool& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncRepeatAvOpenhomeOrgPlaylist1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndRepeat(aAsync, iValue);
}


class SyncSetShuffleAvOpenhomeOrgPlaylist1C : public SyncProxyAction
{
public:
    SyncSetShuffleAvOpenhomeOrgPlaylist1C(CpProxyAvOpenhomeOrgPlaylist1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetShuffleAvOpenhomeOrgPlaylist1C() {};
private:
    CpProxyAvOpenhomeOrgPlaylist1C& iService;
};

SyncSetShuffleAvOpenhomeOrgPlaylist1C::SyncSetShuffleAvOpenhomeOrgPlaylist1C(CpProxyAvOpenhomeOrgPlaylist1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetShuffleAvOpenhomeOrgPlaylist1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetShuffle(aAsync);
}


class SyncShuffleAvOpenhomeOrgPlaylist1C : public SyncProxyAction
{
public:
    SyncShuffleAvOpenhomeOrgPlaylist1C(CpProxyAvOpenhomeOrgPlaylist1C& aProxy, TBool& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncShuffleAvOpenhomeOrgPlaylist1C() {};
private:
    CpProxyAvOpenhomeOrgPlaylist1C& iService;
    TBool& iValue;
};

SyncShuffleAvOpenhomeOrgPlaylist1C::SyncShuffleAvOpenhomeOrgPlaylist1C(CpProxyAvOpenhomeOrgPlaylist1C& aProxy, TBool& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncShuffleAvOpenhomeOrgPlaylist1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndShuffle(aAsync, iValue);
}


class SyncSeekSecondAbsoluteAvOpenhomeOrgPlaylist1C : public SyncProxyAction
{
public:
    SyncSeekSecondAbsoluteAvOpenhomeOrgPlaylist1C(CpProxyAvOpenhomeOrgPlaylist1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSeekSecondAbsoluteAvOpenhomeOrgPlaylist1C() {};
private:
    CpProxyAvOpenhomeOrgPlaylist1C& iService;
};

SyncSeekSecondAbsoluteAvOpenhomeOrgPlaylist1C::SyncSeekSecondAbsoluteAvOpenhomeOrgPlaylist1C(CpProxyAvOpenhomeOrgPlaylist1C& aProxy)
    : iService(aProxy)
{
}

void SyncSeekSecondAbsoluteAvOpenhomeOrgPlaylist1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSeekSecondAbsolute(aAsync);
}


class SyncSeekSecondRelativeAvOpenhomeOrgPlaylist1C : public SyncProxyAction
{
public:
    SyncSeekSecondRelativeAvOpenhomeOrgPlaylist1C(CpProxyAvOpenhomeOrgPlaylist1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSeekSecondRelativeAvOpenhomeOrgPlaylist1C() {};
private:
    CpProxyAvOpenhomeOrgPlaylist1C& iService;
};

SyncSeekSecondRelativeAvOpenhomeOrgPlaylist1C::SyncSeekSecondRelativeAvOpenhomeOrgPlaylist1C(CpProxyAvOpenhomeOrgPlaylist1C& aProxy)
    : iService(aProxy)
{
}

void SyncSeekSecondRelativeAvOpenhomeOrgPlaylist1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSeekSecondRelative(aAsync);
}


class SyncSeekIdAvOpenhomeOrgPlaylist1C : public SyncProxyAction
{
public:
    SyncSeekIdAvOpenhomeOrgPlaylist1C(CpProxyAvOpenhomeOrgPlaylist1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSeekIdAvOpenhomeOrgPlaylist1C() {};
private:
    CpProxyAvOpenhomeOrgPlaylist1C& iService;
};

SyncSeekIdAvOpenhomeOrgPlaylist1C::SyncSeekIdAvOpenhomeOrgPlaylist1C(CpProxyAvOpenhomeOrgPlaylist1C& aProxy)
    : iService(aProxy)
{
}

void SyncSeekIdAvOpenhomeOrgPlaylist1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSeekId(aAsync);
}


class SyncSeekIndexAvOpenhomeOrgPlaylist1C : public SyncProxyAction
{
public:
    SyncSeekIndexAvOpenhomeOrgPlaylist1C(CpProxyAvOpenhomeOrgPlaylist1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSeekIndexAvOpenhomeOrgPlaylist1C() {};
private:
    CpProxyAvOpenhomeOrgPlaylist1C& iService;
};

SyncSeekIndexAvOpenhomeOrgPlaylist1C::SyncSeekIndexAvOpenhomeOrgPlaylist1C(CpProxyAvOpenhomeOrgPlaylist1C& aProxy)
    : iService(aProxy)
{
}

void SyncSeekIndexAvOpenhomeOrgPlaylist1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSeekIndex(aAsync);
}


class SyncTransportStateAvOpenhomeOrgPlaylist1C : public SyncProxyAction
{
public:
    SyncTransportStateAvOpenhomeOrgPlaylist1C(CpProxyAvOpenhomeOrgPlaylist1C& aProxy, Brh& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncTransportStateAvOpenhomeOrgPlaylist1C() {};
private:
    CpProxyAvOpenhomeOrgPlaylist1C& iService;
    Brh& iValue;
};

SyncTransportStateAvOpenhomeOrgPlaylist1C::SyncTransportStateAvOpenhomeOrgPlaylist1C(CpProxyAvOpenhomeOrgPlaylist1C& aProxy, Brh& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncTransportStateAvOpenhomeOrgPlaylist1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndTransportState(aAsync, iValue);
}


class SyncIdAvOpenhomeOrgPlaylist1C : public SyncProxyAction
{
public:
    SyncIdAvOpenhomeOrgPlaylist1C(CpProxyAvOpenhomeOrgPlaylist1C& aProxy, TUint& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncIdAvOpenhomeOrgPlaylist1C() {};
private:
    CpProxyAvOpenhomeOrgPlaylist1C& iService;
    TUint& iValue;
};

SyncIdAvOpenhomeOrgPlaylist1C::SyncIdAvOpenhomeOrgPlaylist1C(CpProxyAvOpenhomeOrgPlaylist1C& aProxy, TUint& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncIdAvOpenhomeOrgPlaylist1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndId(aAsync, iValue);
}


class SyncReadAvOpenhomeOrgPlaylist1C : public SyncProxyAction
{
public:
    SyncReadAvOpenhomeOrgPlaylist1C(CpProxyAvOpenhomeOrgPlaylist1C& aProxy, Brh& aUri, Brh& aMetadata);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncReadAvOpenhomeOrgPlaylist1C() {};
private:
    CpProxyAvOpenhomeOrgPlaylist1C& iService;
    Brh& iUri;
    Brh& iMetadata;
};

SyncReadAvOpenhomeOrgPlaylist1C::SyncReadAvOpenhomeOrgPlaylist1C(CpProxyAvOpenhomeOrgPlaylist1C& aProxy, Brh& aUri, Brh& aMetadata)
    : iService(aProxy)
    , iUri(aUri)
    , iMetadata(aMetadata)
{
}

void SyncReadAvOpenhomeOrgPlaylist1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndRead(aAsync, iUri, iMetadata);
}


class SyncReadListAvOpenhomeOrgPlaylist1C : public SyncProxyAction
{
public:
    SyncReadListAvOpenhomeOrgPlaylist1C(CpProxyAvOpenhomeOrgPlaylist1C& aProxy, Brh& aTrackList);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncReadListAvOpenhomeOrgPlaylist1C() {};
private:
    CpProxyAvOpenhomeOrgPlaylist1C& iService;
    Brh& iTrackList;
};

SyncReadListAvOpenhomeOrgPlaylist1C::SyncReadListAvOpenhomeOrgPlaylist1C(CpProxyAvOpenhomeOrgPlaylist1C& aProxy, Brh& aTrackList)
    : iService(aProxy)
    , iTrackList(aTrackList)
{
}

void SyncReadListAvOpenhomeOrgPlaylist1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndReadList(aAsync, iTrackList);
}


class SyncInsertAvOpenhomeOrgPlaylist1C : public SyncProxyAction
{
public:
    SyncInsertAvOpenhomeOrgPlaylist1C(CpProxyAvOpenhomeOrgPlaylist1C& aProxy, TUint& aNewId);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncInsertAvOpenhomeOrgPlaylist1C() {};
private:
    CpProxyAvOpenhomeOrgPlaylist1C& iService;
    TUint& iNewId;
};

SyncInsertAvOpenhomeOrgPlaylist1C::SyncInsertAvOpenhomeOrgPlaylist1C(CpProxyAvOpenhomeOrgPlaylist1C& aProxy, TUint& aNewId)
    : iService(aProxy)
    , iNewId(aNewId)
{
}

void SyncInsertAvOpenhomeOrgPlaylist1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndInsert(aAsync, iNewId);
}


class SyncDeleteIdAvOpenhomeOrgPlaylist1C : public SyncProxyAction
{
public:
    SyncDeleteIdAvOpenhomeOrgPlaylist1C(CpProxyAvOpenhomeOrgPlaylist1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncDeleteIdAvOpenhomeOrgPlaylist1C() {};
private:
    CpProxyAvOpenhomeOrgPlaylist1C& iService;
};

SyncDeleteIdAvOpenhomeOrgPlaylist1C::SyncDeleteIdAvOpenhomeOrgPlaylist1C(CpProxyAvOpenhomeOrgPlaylist1C& aProxy)
    : iService(aProxy)
{
}

void SyncDeleteIdAvOpenhomeOrgPlaylist1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndDeleteId(aAsync);
}


class SyncDeleteAllAvOpenhomeOrgPlaylist1C : public SyncProxyAction
{
public:
    SyncDeleteAllAvOpenhomeOrgPlaylist1C(CpProxyAvOpenhomeOrgPlaylist1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncDeleteAllAvOpenhomeOrgPlaylist1C() {};
private:
    CpProxyAvOpenhomeOrgPlaylist1C& iService;
};

SyncDeleteAllAvOpenhomeOrgPlaylist1C::SyncDeleteAllAvOpenhomeOrgPlaylist1C(CpProxyAvOpenhomeOrgPlaylist1C& aProxy)
    : iService(aProxy)
{
}

void SyncDeleteAllAvOpenhomeOrgPlaylist1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndDeleteAll(aAsync);
}


class SyncTracksMaxAvOpenhomeOrgPlaylist1C : public SyncProxyAction
{
public:
    SyncTracksMaxAvOpenhomeOrgPlaylist1C(CpProxyAvOpenhomeOrgPlaylist1C& aProxy, TUint& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncTracksMaxAvOpenhomeOrgPlaylist1C() {};
private:
    CpProxyAvOpenhomeOrgPlaylist1C& iService;
    TUint& iValue;
};

SyncTracksMaxAvOpenhomeOrgPlaylist1C::SyncTracksMaxAvOpenhomeOrgPlaylist1C(CpProxyAvOpenhomeOrgPlaylist1C& aProxy, TUint& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncTracksMaxAvOpenhomeOrgPlaylist1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndTracksMax(aAsync, iValue);
}


class SyncIdArrayAvOpenhomeOrgPlaylist1C : public SyncProxyAction
{
public:
    SyncIdArrayAvOpenhomeOrgPlaylist1C(CpProxyAvOpenhomeOrgPlaylist1C& aProxy, TUint& aToken, Brh& aArray);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncIdArrayAvOpenhomeOrgPlaylist1C() {};
private:
    CpProxyAvOpenhomeOrgPlaylist1C& iService;
    TUint& iToken;
    Brh& iArray;
};

SyncIdArrayAvOpenhomeOrgPlaylist1C::SyncIdArrayAvOpenhomeOrgPlaylist1C(CpProxyAvOpenhomeOrgPlaylist1C& aProxy, TUint& aToken, Brh& aArray)
    : iService(aProxy)
    , iToken(aToken)
    , iArray(aArray)
{
}

void SyncIdArrayAvOpenhomeOrgPlaylist1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndIdArray(aAsync, iToken, iArray);
}


class SyncIdArrayChangedAvOpenhomeOrgPlaylist1C : public SyncProxyAction
{
public:
    SyncIdArrayChangedAvOpenhomeOrgPlaylist1C(CpProxyAvOpenhomeOrgPlaylist1C& aProxy, TBool& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncIdArrayChangedAvOpenhomeOrgPlaylist1C() {};
private:
    CpProxyAvOpenhomeOrgPlaylist1C& iService;
    TBool& iValue;
};

SyncIdArrayChangedAvOpenhomeOrgPlaylist1C::SyncIdArrayChangedAvOpenhomeOrgPlaylist1C(CpProxyAvOpenhomeOrgPlaylist1C& aProxy, TBool& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncIdArrayChangedAvOpenhomeOrgPlaylist1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndIdArrayChanged(aAsync, iValue);
}


class SyncProtocolInfoAvOpenhomeOrgPlaylist1C : public SyncProxyAction
{
public:
    SyncProtocolInfoAvOpenhomeOrgPlaylist1C(CpProxyAvOpenhomeOrgPlaylist1C& aProxy, Brh& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncProtocolInfoAvOpenhomeOrgPlaylist1C() {};
private:
    CpProxyAvOpenhomeOrgPlaylist1C& iService;
    Brh& iValue;
};

SyncProtocolInfoAvOpenhomeOrgPlaylist1C::SyncProtocolInfoAvOpenhomeOrgPlaylist1C(CpProxyAvOpenhomeOrgPlaylist1C& aProxy, Brh& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncProtocolInfoAvOpenhomeOrgPlaylist1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndProtocolInfo(aAsync, iValue);
}

CpProxyAvOpenhomeOrgPlaylist1C::CpProxyAvOpenhomeOrgPlaylist1C(CpDeviceC aDevice)
    : CpProxyC("av-openhome-org", "Playlist", 1, *reinterpret_cast<CpiDevice*>(aDevice))
    , iLock("MPCS")
{
    OpenHome::Net::Parameter* param;
    TChar** allowedValues;
    TUint index;

    iActionPlay = new Action("Play");

    iActionPause = new Action("Pause");

    iActionStop = new Action("Stop");

    iActionNext = new Action("Next");

    iActionPrevious = new Action("Previous");

    iActionSetRepeat = new Action("SetRepeat");
    param = new OpenHome::Net::ParameterBool("Value");
    iActionSetRepeat->AddInputParameter(param);

    iActionRepeat = new Action("Repeat");
    param = new OpenHome::Net::ParameterBool("Value");
    iActionRepeat->AddOutputParameter(param);

    iActionSetShuffle = new Action("SetShuffle");
    param = new OpenHome::Net::ParameterBool("Value");
    iActionSetShuffle->AddInputParameter(param);

    iActionShuffle = new Action("Shuffle");
    param = new OpenHome::Net::ParameterBool("Value");
    iActionShuffle->AddOutputParameter(param);

    iActionSeekSecondAbsolute = new Action("SeekSecondAbsolute");
    param = new OpenHome::Net::ParameterUint("Value");
    iActionSeekSecondAbsolute->AddInputParameter(param);

    iActionSeekSecondRelative = new Action("SeekSecondRelative");
    param = new OpenHome::Net::ParameterInt("Value");
    iActionSeekSecondRelative->AddInputParameter(param);

    iActionSeekId = new Action("SeekId");
    param = new OpenHome::Net::ParameterUint("Value");
    iActionSeekId->AddInputParameter(param);

    iActionSeekIndex = new Action("SeekIndex");
    param = new OpenHome::Net::ParameterUint("Value");
    iActionSeekIndex->AddInputParameter(param);

    iActionTransportState = new Action("TransportState");
    index = 0;
    allowedValues = new TChar*[4];
    allowedValues[index++] = (TChar*)"Playing";
    allowedValues[index++] = (TChar*)"Paused";
    allowedValues[index++] = (TChar*)"Stopped";
    allowedValues[index++] = (TChar*)"Buffering";
    param = new OpenHome::Net::ParameterString("Value", allowedValues, 4);
    iActionTransportState->AddOutputParameter(param);
    delete[] allowedValues;

    iActionId = new Action("Id");
    param = new OpenHome::Net::ParameterUint("Value");
    iActionId->AddOutputParameter(param);

    iActionRead = new Action("Read");
    param = new OpenHome::Net::ParameterUint("Id");
    iActionRead->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Uri");
    iActionRead->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("Metadata");
    iActionRead->AddOutputParameter(param);

    iActionReadList = new Action("ReadList");
    param = new OpenHome::Net::ParameterString("IdList");
    iActionReadList->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("TrackList");
    iActionReadList->AddOutputParameter(param);

    iActionInsert = new Action("Insert");
    param = new OpenHome::Net::ParameterUint("AfterId");
    iActionInsert->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Uri");
    iActionInsert->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Metadata");
    iActionInsert->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("NewId");
    iActionInsert->AddOutputParameter(param);

    iActionDeleteId = new Action("DeleteId");
    param = new OpenHome::Net::ParameterUint("Value");
    iActionDeleteId->AddInputParameter(param);

    iActionDeleteAll = new Action("DeleteAll");

    iActionTracksMax = new Action("TracksMax");
    param = new OpenHome::Net::ParameterUint("Value");
    iActionTracksMax->AddOutputParameter(param);

    iActionIdArray = new Action("IdArray");
    param = new OpenHome::Net::ParameterUint("Token");
    iActionIdArray->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterBinary("Array");
    iActionIdArray->AddOutputParameter(param);

    iActionIdArrayChanged = new Action("IdArrayChanged");
    param = new OpenHome::Net::ParameterUint("Token");
    iActionIdArrayChanged->AddInputParameter(param);
    param = new OpenHome::Net::ParameterBool("Value");
    iActionIdArrayChanged->AddOutputParameter(param);

    iActionProtocolInfo = new Action("ProtocolInfo");
    param = new OpenHome::Net::ParameterString("Value");
    iActionProtocolInfo->AddOutputParameter(param);

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgPlaylist1C::TransportStatePropertyChanged);
    iTransportState = new PropertyString(reinterpret_cast<CpiDevice*>(aDevice)->GetCpStack().Env(), "TransportState", functor);
    AddProperty(iTransportState);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgPlaylist1C::RepeatPropertyChanged);
    iRepeat = new PropertyBool(reinterpret_cast<CpiDevice*>(aDevice)->GetCpStack().Env(), "Repeat", functor);
    AddProperty(iRepeat);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgPlaylist1C::ShufflePropertyChanged);
    iShuffle = new PropertyBool(reinterpret_cast<CpiDevice*>(aDevice)->GetCpStack().Env(), "Shuffle", functor);
    AddProperty(iShuffle);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgPlaylist1C::IdPropertyChanged);
    iId = new PropertyUint(reinterpret_cast<CpiDevice*>(aDevice)->GetCpStack().Env(), "Id", functor);
    AddProperty(iId);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgPlaylist1C::IdArrayPropertyChanged);
    iIdArray = new PropertyBinary(reinterpret_cast<CpiDevice*>(aDevice)->GetCpStack().Env(), "IdArray", functor);
    AddProperty(iIdArray);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgPlaylist1C::TracksMaxPropertyChanged);
    iTracksMax = new PropertyUint(reinterpret_cast<CpiDevice*>(aDevice)->GetCpStack().Env(), "TracksMax", functor);
    AddProperty(iTracksMax);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgPlaylist1C::ProtocolInfoPropertyChanged);
    iProtocolInfo = new PropertyString(reinterpret_cast<CpiDevice*>(aDevice)->GetCpStack().Env(), "ProtocolInfo", functor);
    AddProperty(iProtocolInfo);
}

CpProxyAvOpenhomeOrgPlaylist1C::~CpProxyAvOpenhomeOrgPlaylist1C()
{
    DestroyService();
    delete iActionPlay;
    delete iActionPause;
    delete iActionStop;
    delete iActionNext;
    delete iActionPrevious;
    delete iActionSetRepeat;
    delete iActionRepeat;
    delete iActionSetShuffle;
    delete iActionShuffle;
    delete iActionSeekSecondAbsolute;
    delete iActionSeekSecondRelative;
    delete iActionSeekId;
    delete iActionSeekIndex;
    delete iActionTransportState;
    delete iActionId;
    delete iActionRead;
    delete iActionReadList;
    delete iActionInsert;
    delete iActionDeleteId;
    delete iActionDeleteAll;
    delete iActionTracksMax;
    delete iActionIdArray;
    delete iActionIdArrayChanged;
    delete iActionProtocolInfo;
}

void CpProxyAvOpenhomeOrgPlaylist1C::SyncPlay()
{
    SyncPlayAvOpenhomeOrgPlaylist1C sync(*this);
    BeginPlay(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylist1C::BeginPlay(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionPlay, aFunctor);
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylist1C::EndPlay(IAsync& aAsync)
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

void CpProxyAvOpenhomeOrgPlaylist1C::SyncPause()
{
    SyncPauseAvOpenhomeOrgPlaylist1C sync(*this);
    BeginPause(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylist1C::BeginPause(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionPause, aFunctor);
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylist1C::EndPause(IAsync& aAsync)
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

void CpProxyAvOpenhomeOrgPlaylist1C::SyncStop()
{
    SyncStopAvOpenhomeOrgPlaylist1C sync(*this);
    BeginStop(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylist1C::BeginStop(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionStop, aFunctor);
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylist1C::EndStop(IAsync& aAsync)
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

void CpProxyAvOpenhomeOrgPlaylist1C::SyncNext()
{
    SyncNextAvOpenhomeOrgPlaylist1C sync(*this);
    BeginNext(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylist1C::BeginNext(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionNext, aFunctor);
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylist1C::EndNext(IAsync& aAsync)
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

void CpProxyAvOpenhomeOrgPlaylist1C::SyncPrevious()
{
    SyncPreviousAvOpenhomeOrgPlaylist1C sync(*this);
    BeginPrevious(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylist1C::BeginPrevious(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionPrevious, aFunctor);
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylist1C::EndPrevious(IAsync& aAsync)
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

void CpProxyAvOpenhomeOrgPlaylist1C::SyncSetRepeat(TBool aValue)
{
    SyncSetRepeatAvOpenhomeOrgPlaylist1C sync(*this);
    BeginSetRepeat(aValue, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylist1C::BeginSetRepeat(TBool aValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetRepeat, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetRepeat->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aValue));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylist1C::EndSetRepeat(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetRepeat"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyAvOpenhomeOrgPlaylist1C::SyncRepeat(TBool& aValue)
{
    SyncRepeatAvOpenhomeOrgPlaylist1C sync(*this, aValue);
    BeginRepeat(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylist1C::BeginRepeat(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionRepeat, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionRepeat->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylist1C::EndRepeat(IAsync& aAsync, TBool& aValue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Repeat"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aValue = ((ArgumentBool*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyAvOpenhomeOrgPlaylist1C::SyncSetShuffle(TBool aValue)
{
    SyncSetShuffleAvOpenhomeOrgPlaylist1C sync(*this);
    BeginSetShuffle(aValue, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylist1C::BeginSetShuffle(TBool aValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetShuffle, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetShuffle->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aValue));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylist1C::EndSetShuffle(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetShuffle"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyAvOpenhomeOrgPlaylist1C::SyncShuffle(TBool& aValue)
{
    SyncShuffleAvOpenhomeOrgPlaylist1C sync(*this, aValue);
    BeginShuffle(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylist1C::BeginShuffle(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionShuffle, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionShuffle->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylist1C::EndShuffle(IAsync& aAsync, TBool& aValue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Shuffle"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aValue = ((ArgumentBool*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyAvOpenhomeOrgPlaylist1C::SyncSeekSecondAbsolute(TUint aValue)
{
    SyncSeekSecondAbsoluteAvOpenhomeOrgPlaylist1C sync(*this);
    BeginSeekSecondAbsolute(aValue, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylist1C::BeginSeekSecondAbsolute(TUint aValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSeekSecondAbsolute, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSeekSecondAbsolute->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aValue));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylist1C::EndSeekSecondAbsolute(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SeekSecondAbsolute"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyAvOpenhomeOrgPlaylist1C::SyncSeekSecondRelative(TInt aValue)
{
    SyncSeekSecondRelativeAvOpenhomeOrgPlaylist1C sync(*this);
    BeginSeekSecondRelative(aValue, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylist1C::BeginSeekSecondRelative(TInt aValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSeekSecondRelative, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSeekSecondRelative->InputParameters();
    invocation->AddInput(new ArgumentInt(*inParams[inIndex++], aValue));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylist1C::EndSeekSecondRelative(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SeekSecondRelative"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyAvOpenhomeOrgPlaylist1C::SyncSeekId(TUint aValue)
{
    SyncSeekIdAvOpenhomeOrgPlaylist1C sync(*this);
    BeginSeekId(aValue, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylist1C::BeginSeekId(TUint aValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSeekId, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSeekId->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aValue));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylist1C::EndSeekId(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SeekId"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyAvOpenhomeOrgPlaylist1C::SyncSeekIndex(TUint aValue)
{
    SyncSeekIndexAvOpenhomeOrgPlaylist1C sync(*this);
    BeginSeekIndex(aValue, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylist1C::BeginSeekIndex(TUint aValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSeekIndex, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSeekIndex->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aValue));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylist1C::EndSeekIndex(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SeekIndex"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyAvOpenhomeOrgPlaylist1C::SyncTransportState(Brh& aValue)
{
    SyncTransportStateAvOpenhomeOrgPlaylist1C sync(*this, aValue);
    BeginTransportState(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylist1C::BeginTransportState(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionTransportState, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionTransportState->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylist1C::EndTransportState(IAsync& aAsync, Brh& aValue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("TransportState"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aValue);
}

void CpProxyAvOpenhomeOrgPlaylist1C::SyncId(TUint& aValue)
{
    SyncIdAvOpenhomeOrgPlaylist1C sync(*this, aValue);
    BeginId(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylist1C::BeginId(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionId, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionId->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylist1C::EndId(IAsync& aAsync, TUint& aValue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Id"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aValue = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyAvOpenhomeOrgPlaylist1C::SyncRead(TUint aId, Brh& aUri, Brh& aMetadata)
{
    SyncReadAvOpenhomeOrgPlaylist1C sync(*this, aUri, aMetadata);
    BeginRead(aId, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylist1C::BeginRead(TUint aId, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionRead, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionRead->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aId));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionRead->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylist1C::EndRead(IAsync& aAsync, Brh& aUri, Brh& aMetadata)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Read"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aUri);
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aMetadata);
}

void CpProxyAvOpenhomeOrgPlaylist1C::SyncReadList(const Brx& aIdList, Brh& aTrackList)
{
    SyncReadListAvOpenhomeOrgPlaylist1C sync(*this, aTrackList);
    BeginReadList(aIdList, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylist1C::BeginReadList(const Brx& aIdList, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionReadList, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionReadList->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aIdList));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionReadList->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylist1C::EndReadList(IAsync& aAsync, Brh& aTrackList)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("ReadList"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aTrackList);
}

void CpProxyAvOpenhomeOrgPlaylist1C::SyncInsert(TUint aAfterId, const Brx& aUri, const Brx& aMetadata, TUint& aNewId)
{
    SyncInsertAvOpenhomeOrgPlaylist1C sync(*this, aNewId);
    BeginInsert(aAfterId, aUri, aMetadata, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylist1C::BeginInsert(TUint aAfterId, const Brx& aUri, const Brx& aMetadata, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionInsert, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionInsert->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aAfterId));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aUri));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aMetadata));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionInsert->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylist1C::EndInsert(IAsync& aAsync, TUint& aNewId)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Insert"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aNewId = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyAvOpenhomeOrgPlaylist1C::SyncDeleteId(TUint aValue)
{
    SyncDeleteIdAvOpenhomeOrgPlaylist1C sync(*this);
    BeginDeleteId(aValue, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylist1C::BeginDeleteId(TUint aValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionDeleteId, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionDeleteId->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aValue));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylist1C::EndDeleteId(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("DeleteId"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyAvOpenhomeOrgPlaylist1C::SyncDeleteAll()
{
    SyncDeleteAllAvOpenhomeOrgPlaylist1C sync(*this);
    BeginDeleteAll(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylist1C::BeginDeleteAll(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionDeleteAll, aFunctor);
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylist1C::EndDeleteAll(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("DeleteAll"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyAvOpenhomeOrgPlaylist1C::SyncTracksMax(TUint& aValue)
{
    SyncTracksMaxAvOpenhomeOrgPlaylist1C sync(*this, aValue);
    BeginTracksMax(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylist1C::BeginTracksMax(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionTracksMax, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionTracksMax->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylist1C::EndTracksMax(IAsync& aAsync, TUint& aValue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("TracksMax"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aValue = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyAvOpenhomeOrgPlaylist1C::SyncIdArray(TUint& aToken, Brh& aArray)
{
    SyncIdArrayAvOpenhomeOrgPlaylist1C sync(*this, aToken, aArray);
    BeginIdArray(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylist1C::BeginIdArray(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionIdArray, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionIdArray->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentBinary(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylist1C::EndIdArray(IAsync& aAsync, TUint& aToken, Brh& aArray)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("IdArray"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aToken = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    ((ArgumentBinary*)invocation.OutputArguments()[index++])->TransferTo(aArray);
}

void CpProxyAvOpenhomeOrgPlaylist1C::SyncIdArrayChanged(TUint aToken, TBool& aValue)
{
    SyncIdArrayChangedAvOpenhomeOrgPlaylist1C sync(*this, aValue);
    BeginIdArrayChanged(aToken, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylist1C::BeginIdArrayChanged(TUint aToken, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionIdArrayChanged, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionIdArrayChanged->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aToken));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionIdArrayChanged->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylist1C::EndIdArrayChanged(IAsync& aAsync, TBool& aValue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("IdArrayChanged"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aValue = ((ArgumentBool*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyAvOpenhomeOrgPlaylist1C::SyncProtocolInfo(Brh& aValue)
{
    SyncProtocolInfoAvOpenhomeOrgPlaylist1C sync(*this, aValue);
    BeginProtocolInfo(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylist1C::BeginProtocolInfo(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionProtocolInfo, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionProtocolInfo->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylist1C::EndProtocolInfo(IAsync& aAsync, Brh& aValue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("ProtocolInfo"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aValue);
}

void CpProxyAvOpenhomeOrgPlaylist1C::SetPropertyTransportStateChanged(Functor& aFunctor)
{
    iLock.Wait();
    iTransportStateChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgPlaylist1C::SetPropertyRepeatChanged(Functor& aFunctor)
{
    iLock.Wait();
    iRepeatChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgPlaylist1C::SetPropertyShuffleChanged(Functor& aFunctor)
{
    iLock.Wait();
    iShuffleChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgPlaylist1C::SetPropertyIdChanged(Functor& aFunctor)
{
    iLock.Wait();
    iIdChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgPlaylist1C::SetPropertyIdArrayChanged(Functor& aFunctor)
{
    iLock.Wait();
    iIdArrayChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgPlaylist1C::SetPropertyTracksMaxChanged(Functor& aFunctor)
{
    iLock.Wait();
    iTracksMaxChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgPlaylist1C::SetPropertyProtocolInfoChanged(Functor& aFunctor)
{
    iLock.Wait();
    iProtocolInfoChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgPlaylist1C::PropertyTransportState(Brhz& aTransportState) const
{
    AutoMutex a(GetPropertyReadLock());
    ASSERT(IsSubscribed());
    aTransportState.Set(iTransportState->Value());
}

void CpProxyAvOpenhomeOrgPlaylist1C::PropertyRepeat(TBool& aRepeat) const
{
    AutoMutex a(GetPropertyReadLock());
    ASSERT(IsSubscribed());
    aRepeat = iRepeat->Value();
}

void CpProxyAvOpenhomeOrgPlaylist1C::PropertyShuffle(TBool& aShuffle) const
{
    AutoMutex a(GetPropertyReadLock());
    ASSERT(IsSubscribed());
    aShuffle = iShuffle->Value();
}

void CpProxyAvOpenhomeOrgPlaylist1C::PropertyId(TUint& aId) const
{
    AutoMutex a(GetPropertyReadLock());
    ASSERT(IsSubscribed());
    aId = iId->Value();
}

void CpProxyAvOpenhomeOrgPlaylist1C::PropertyIdArray(Brh& aIdArray) const
{
    AutoMutex a(GetPropertyReadLock());
    ASSERT(IsSubscribed());
    aIdArray.Set(iIdArray->Value());
}

void CpProxyAvOpenhomeOrgPlaylist1C::PropertyTracksMax(TUint& aTracksMax) const
{
    AutoMutex a(GetPropertyReadLock());
    ASSERT(IsSubscribed());
    aTracksMax = iTracksMax->Value();
}

void CpProxyAvOpenhomeOrgPlaylist1C::PropertyProtocolInfo(Brhz& aProtocolInfo) const
{
    AutoMutex a(GetPropertyReadLock());
    ASSERT(IsSubscribed());
    aProtocolInfo.Set(iProtocolInfo->Value());
}

void CpProxyAvOpenhomeOrgPlaylist1C::TransportStatePropertyChanged()
{
    ReportEvent(iTransportStateChanged);
}

void CpProxyAvOpenhomeOrgPlaylist1C::RepeatPropertyChanged()
{
    ReportEvent(iRepeatChanged);
}

void CpProxyAvOpenhomeOrgPlaylist1C::ShufflePropertyChanged()
{
    ReportEvent(iShuffleChanged);
}

void CpProxyAvOpenhomeOrgPlaylist1C::IdPropertyChanged()
{
    ReportEvent(iIdChanged);
}

void CpProxyAvOpenhomeOrgPlaylist1C::IdArrayPropertyChanged()
{
    ReportEvent(iIdArrayChanged);
}

void CpProxyAvOpenhomeOrgPlaylist1C::TracksMaxPropertyChanged()
{
    ReportEvent(iTracksMaxChanged);
}

void CpProxyAvOpenhomeOrgPlaylist1C::ProtocolInfoPropertyChanged()
{
    ReportEvent(iProtocolInfoChanged);
}


THandle STDCALL CpProxyAvOpenhomeOrgPlaylist1Create(CpDeviceC aDevice)
{
    return new CpProxyAvOpenhomeOrgPlaylist1C(aDevice);
}

void STDCALL CpProxyAvOpenhomeOrgPlaylist1Destroy(THandle aHandle)
{
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    delete proxyC;
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylist1SyncPlay(THandle aHandle)
{
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncPlay();
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgPlaylist1BeginPlay(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginPlay(functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylist1EndPlay(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
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

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylist1SyncPause(THandle aHandle)
{
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncPause();
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgPlaylist1BeginPause(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginPause(functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylist1EndPause(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
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

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylist1SyncStop(THandle aHandle)
{
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncStop();
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgPlaylist1BeginStop(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginStop(functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylist1EndStop(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
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

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylist1SyncNext(THandle aHandle)
{
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncNext();
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgPlaylist1BeginNext(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginNext(functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylist1EndNext(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
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

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylist1SyncPrevious(THandle aHandle)
{
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncPrevious();
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgPlaylist1BeginPrevious(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginPrevious(functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylist1EndPrevious(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
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

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylist1SyncSetRepeat(THandle aHandle, uint32_t aValue)
{
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncSetRepeat((aValue==0? false : true));
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgPlaylist1BeginSetRepeat(THandle aHandle, uint32_t aValue, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSetRepeat((aValue==0? false : true), functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylist1EndSetRepeat(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetRepeat(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylist1SyncRepeat(THandle aHandle, uint32_t* aValue)
{
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    TBool Value;
    int32_t err = 0;
    try {
        proxyC->SyncRepeat(Value);
        *aValue = Value? 1 : 0;
    }
    catch (ProxyError& ) {
        err = -1;
        *aValue = false;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgPlaylist1BeginRepeat(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginRepeat(functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylist1EndRepeat(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aValue)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    TBool Value;
    try {
        proxyC->EndRepeat(*async, Value);
        *aValue = Value? 1 : 0;
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylist1SyncSetShuffle(THandle aHandle, uint32_t aValue)
{
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncSetShuffle((aValue==0? false : true));
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgPlaylist1BeginSetShuffle(THandle aHandle, uint32_t aValue, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSetShuffle((aValue==0? false : true), functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylist1EndSetShuffle(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetShuffle(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylist1SyncShuffle(THandle aHandle, uint32_t* aValue)
{
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    TBool Value;
    int32_t err = 0;
    try {
        proxyC->SyncShuffle(Value);
        *aValue = Value? 1 : 0;
    }
    catch (ProxyError& ) {
        err = -1;
        *aValue = false;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgPlaylist1BeginShuffle(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginShuffle(functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylist1EndShuffle(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aValue)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    TBool Value;
    try {
        proxyC->EndShuffle(*async, Value);
        *aValue = Value? 1 : 0;
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylist1SyncSeekSecondAbsolute(THandle aHandle, uint32_t aValue)
{
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncSeekSecondAbsolute(aValue);
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgPlaylist1BeginSeekSecondAbsolute(THandle aHandle, uint32_t aValue, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSeekSecondAbsolute(aValue, functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylist1EndSeekSecondAbsolute(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSeekSecondAbsolute(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylist1SyncSeekSecondRelative(THandle aHandle, int32_t aValue)
{
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncSeekSecondRelative(aValue);
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgPlaylist1BeginSeekSecondRelative(THandle aHandle, int32_t aValue, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSeekSecondRelative(aValue, functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylist1EndSeekSecondRelative(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSeekSecondRelative(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylist1SyncSeekId(THandle aHandle, uint32_t aValue)
{
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncSeekId(aValue);
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgPlaylist1BeginSeekId(THandle aHandle, uint32_t aValue, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSeekId(aValue, functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylist1EndSeekId(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSeekId(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylist1SyncSeekIndex(THandle aHandle, uint32_t aValue)
{
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncSeekIndex(aValue);
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgPlaylist1BeginSeekIndex(THandle aHandle, uint32_t aValue, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSeekIndex(aValue, functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylist1EndSeekIndex(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSeekIndex(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylist1SyncTransportState(THandle aHandle, char** aValue)
{
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aValue;
    int32_t err = 0;
    try {
        proxyC->SyncTransportState(buf_aValue);
        *aValue = buf_aValue.Extract();
    }
    catch (ProxyError& ) {
        err = -1;
        *aValue = NULL;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgPlaylist1BeginTransportState(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginTransportState(functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylist1EndTransportState(THandle aHandle, OhNetHandleAsync aAsync, char** aValue)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aValue;
    *aValue = NULL;
    try {
        proxyC->EndTransportState(*async, buf_aValue);
        *aValue = buf_aValue.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylist1SyncId(THandle aHandle, uint32_t* aValue)
{
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncId(*aValue);
    }
    catch (ProxyError& ) {
        err = -1;
        *aValue = 0;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgPlaylist1BeginId(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginId(functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylist1EndId(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aValue)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndId(*async, *aValue);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylist1SyncRead(THandle aHandle, uint32_t aId, char** aUri, char** aMetadata)
{
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aUri;
    Brh buf_aMetadata;
    int32_t err = 0;
    try {
        proxyC->SyncRead(aId, buf_aUri, buf_aMetadata);
        *aUri = buf_aUri.Extract();
        *aMetadata = buf_aMetadata.Extract();
    }
    catch (ProxyError& ) {
        err = -1;
        *aUri = NULL;
        *aMetadata = NULL;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgPlaylist1BeginRead(THandle aHandle, uint32_t aId, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginRead(aId, functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylist1EndRead(THandle aHandle, OhNetHandleAsync aAsync, char** aUri, char** aMetadata)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aUri;
    *aUri = NULL;
    Brh buf_aMetadata;
    *aMetadata = NULL;
    try {
        proxyC->EndRead(*async, buf_aUri, buf_aMetadata);
        *aUri = buf_aUri.Extract();
        *aMetadata = buf_aMetadata.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylist1SyncReadList(THandle aHandle, const char* aIdList, char** aTrackList)
{
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aIdList(aIdList);
    Brh buf_aTrackList;
    int32_t err = 0;
    try {
        proxyC->SyncReadList(buf_aIdList, buf_aTrackList);
        *aTrackList = buf_aTrackList.Extract();
    }
    catch (ProxyError& ) {
        err = -1;
        *aTrackList = NULL;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgPlaylist1BeginReadList(THandle aHandle, const char* aIdList, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aIdList(aIdList);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginReadList(buf_aIdList, functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylist1EndReadList(THandle aHandle, OhNetHandleAsync aAsync, char** aTrackList)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aTrackList;
    *aTrackList = NULL;
    try {
        proxyC->EndReadList(*async, buf_aTrackList);
        *aTrackList = buf_aTrackList.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylist1SyncInsert(THandle aHandle, uint32_t aAfterId, const char* aUri, const char* aMetadata, uint32_t* aNewId)
{
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aUri(aUri);
    Brh buf_aMetadata(aMetadata);
    int32_t err = 0;
    try {
        proxyC->SyncInsert(aAfterId, buf_aUri, buf_aMetadata, *aNewId);
    }
    catch (ProxyError& ) {
        err = -1;
        *aNewId = 0;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgPlaylist1BeginInsert(THandle aHandle, uint32_t aAfterId, const char* aUri, const char* aMetadata, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aUri(aUri);
    Brh buf_aMetadata(aMetadata);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginInsert(aAfterId, buf_aUri, buf_aMetadata, functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylist1EndInsert(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aNewId)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndInsert(*async, *aNewId);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylist1SyncDeleteId(THandle aHandle, uint32_t aValue)
{
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncDeleteId(aValue);
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgPlaylist1BeginDeleteId(THandle aHandle, uint32_t aValue, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginDeleteId(aValue, functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylist1EndDeleteId(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndDeleteId(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylist1SyncDeleteAll(THandle aHandle)
{
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncDeleteAll();
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgPlaylist1BeginDeleteAll(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginDeleteAll(functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylist1EndDeleteAll(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndDeleteAll(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylist1SyncTracksMax(THandle aHandle, uint32_t* aValue)
{
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncTracksMax(*aValue);
    }
    catch (ProxyError& ) {
        err = -1;
        *aValue = 0;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgPlaylist1BeginTracksMax(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginTracksMax(functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylist1EndTracksMax(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aValue)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndTracksMax(*async, *aValue);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylist1SyncIdArray(THandle aHandle, uint32_t* aToken, char** aArray, uint32_t* aArrayLen)
{
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aArray;
    int32_t err = 0;
    try {
        proxyC->SyncIdArray(*aToken, buf_aArray);
        *aArrayLen = buf_aArray.Bytes();
        *aArray = buf_aArray.Extract();
    }
    catch (ProxyError& ) {
        err = -1;
        *aToken = 0;
        *aArrayLen = 0;
        *aArray = NULL;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgPlaylist1BeginIdArray(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginIdArray(functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylist1EndIdArray(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aToken, char** aArray, uint32_t* aArrayLen)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aArray;
    *aArray = NULL;
    *aArrayLen = 0;
    try {
        proxyC->EndIdArray(*async, *aToken, buf_aArray);
        *aArrayLen = buf_aArray.Bytes();
        *aArray = buf_aArray.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylist1SyncIdArrayChanged(THandle aHandle, uint32_t aToken, uint32_t* aValue)
{
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    TBool Value;
    int32_t err = 0;
    try {
        proxyC->SyncIdArrayChanged(aToken, Value);
        *aValue = Value? 1 : 0;
    }
    catch (ProxyError& ) {
        err = -1;
        *aValue = false;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgPlaylist1BeginIdArrayChanged(THandle aHandle, uint32_t aToken, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginIdArrayChanged(aToken, functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylist1EndIdArrayChanged(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aValue)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    TBool Value;
    try {
        proxyC->EndIdArrayChanged(*async, Value);
        *aValue = Value? 1 : 0;
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylist1SyncProtocolInfo(THandle aHandle, char** aValue)
{
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aValue;
    int32_t err = 0;
    try {
        proxyC->SyncProtocolInfo(buf_aValue);
        *aValue = buf_aValue.Extract();
    }
    catch (ProxyError& ) {
        err = -1;
        *aValue = NULL;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgPlaylist1BeginProtocolInfo(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginProtocolInfo(functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylist1EndProtocolInfo(THandle aHandle, OhNetHandleAsync aAsync, char** aValue)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aValue;
    *aValue = NULL;
    try {
        proxyC->EndProtocolInfo(*async, buf_aValue);
        *aValue = buf_aValue.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgPlaylist1SetPropertyTransportStateChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyTransportStateChanged(functor);
}

void STDCALL CpProxyAvOpenhomeOrgPlaylist1SetPropertyRepeatChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyRepeatChanged(functor);
}

void STDCALL CpProxyAvOpenhomeOrgPlaylist1SetPropertyShuffleChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyShuffleChanged(functor);
}

void STDCALL CpProxyAvOpenhomeOrgPlaylist1SetPropertyIdChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyIdChanged(functor);
}

void STDCALL CpProxyAvOpenhomeOrgPlaylist1SetPropertyIdArrayChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyIdArrayChanged(functor);
}

void STDCALL CpProxyAvOpenhomeOrgPlaylist1SetPropertyTracksMaxChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyTracksMaxChanged(functor);
}

void STDCALL CpProxyAvOpenhomeOrgPlaylist1SetPropertyProtocolInfoChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyProtocolInfoChanged(functor);
}

void STDCALL CpProxyAvOpenhomeOrgPlaylist1PropertyTransportState(THandle aHandle, char** aTransportState)
{
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aTransportState;
    proxyC->PropertyTransportState(buf_aTransportState);
    *aTransportState = buf_aTransportState.Transfer();
}

void STDCALL CpProxyAvOpenhomeOrgPlaylist1PropertyRepeat(THandle aHandle, uint32_t* aRepeat)
{
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    TBool Repeat;
    proxyC->PropertyRepeat(Repeat);
    *aRepeat = Repeat? 1 : 0;
}

void STDCALL CpProxyAvOpenhomeOrgPlaylist1PropertyShuffle(THandle aHandle, uint32_t* aShuffle)
{
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    TBool Shuffle;
    proxyC->PropertyShuffle(Shuffle);
    *aShuffle = Shuffle? 1 : 0;
}

void STDCALL CpProxyAvOpenhomeOrgPlaylist1PropertyId(THandle aHandle, uint32_t* aId)
{
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyId(*aId);
}

void STDCALL CpProxyAvOpenhomeOrgPlaylist1PropertyIdArray(THandle aHandle, char** aIdArray, uint32_t* aLen)
{
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aIdArray;
    proxyC->PropertyIdArray(buf_aIdArray);
    *aLen = buf_aIdArray.Bytes();
    *aIdArray = buf_aIdArray.Extract();
}

void STDCALL CpProxyAvOpenhomeOrgPlaylist1PropertyTracksMax(THandle aHandle, uint32_t* aTracksMax)
{
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyTracksMax(*aTracksMax);
}

void STDCALL CpProxyAvOpenhomeOrgPlaylist1PropertyProtocolInfo(THandle aHandle, char** aProtocolInfo)
{
    CpProxyAvOpenhomeOrgPlaylist1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aProtocolInfo;
    proxyC->PropertyProtocolInfo(buf_aProtocolInfo);
    *aProtocolInfo = buf_aProtocolInfo.Transfer();
}

