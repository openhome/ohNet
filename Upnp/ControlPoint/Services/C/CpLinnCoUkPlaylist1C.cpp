#include "CpLinnCoUkPlaylist1.h"
#include <Core/CpDevice.h>
#include <C/CpProxyCPrivate.h>
#include <FunctorAsync.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <Exception.h>
#include <Functor.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Core/CpDevice.h>

using namespace Zapp;

class CpProxyLinnCoUkPlaylist1C : public CpProxyC
{
public:
    CpProxyLinnCoUkPlaylist1C(CpDeviceC aDevice);
    ~CpProxyLinnCoUkPlaylist1C();
    //CpProxyLinnCoUkPlaylist1* Proxy() { return static_cast<CpProxyLinnCoUkPlaylist1*>(iProxy); }

    void SyncRead(TUint aaId, Brh& aaUri, Brh& aaMetaData);
    void BeginRead(TUint aaId, FunctorAsync& aFunctor);
    void EndRead(IAsync& aAsync, Brh& aaUri, Brh& aaMetaData);

    void SyncReadList(const Brx& aaIdList, Brh& aaMetaDataList);
    void BeginReadList(const Brx& aaIdList, FunctorAsync& aFunctor);
    void EndReadList(IAsync& aAsync, Brh& aaMetaDataList);

    void SyncInsert(TUint aaAfterId, const Brx& aaUri, const Brx& aaMetaData, TUint& aaNewId);
    void BeginInsert(TUint aaAfterId, const Brx& aaUri, const Brx& aaMetaData, FunctorAsync& aFunctor);
    void EndInsert(IAsync& aAsync, TUint& aaNewId);

    void SyncDelete(TUint aaId);
    void BeginDelete(TUint aaId, FunctorAsync& aFunctor);
    void EndDelete(IAsync& aAsync);

    void SyncDeleteAll();
    void BeginDeleteAll(FunctorAsync& aFunctor);
    void EndDeleteAll(IAsync& aAsync);

    void SyncSetRepeat(TBool aaRepeat);
    void BeginSetRepeat(TBool aaRepeat, FunctorAsync& aFunctor);
    void EndSetRepeat(IAsync& aAsync);

    void SyncRepeat(TBool& aaRepeat);
    void BeginRepeat(FunctorAsync& aFunctor);
    void EndRepeat(IAsync& aAsync, TBool& aaRepeat);

    void SyncSetShuffle(TBool aaShuffle);
    void BeginSetShuffle(TBool aaShuffle, FunctorAsync& aFunctor);
    void EndSetShuffle(IAsync& aAsync);

    void SyncShuffle(TBool& aaShuffle);
    void BeginShuffle(FunctorAsync& aFunctor);
    void EndShuffle(IAsync& aAsync, TBool& aaShuffle);

    void SyncTracksMax(TUint& aaTracksMax);
    void BeginTracksMax(FunctorAsync& aFunctor);
    void EndTracksMax(IAsync& aAsync, TUint& aaTracksMax);

    void SyncIdArray(TUint& aaIdArrayToken, Brh& aaIdArray);
    void BeginIdArray(FunctorAsync& aFunctor);
    void EndIdArray(IAsync& aAsync, TUint& aaIdArrayToken, Brh& aaIdArray);

    void SyncIdArrayChanged(TUint aaIdArrayToken, TBool& aaIdArrayChanged);
    void BeginIdArrayChanged(TUint aaIdArrayToken, FunctorAsync& aFunctor);
    void EndIdArrayChanged(IAsync& aAsync, TBool& aaIdArrayChanged);

    void SetPropertyIdArrayChanged(Functor& aFunctor);
    void SetPropertyRepeatChanged(Functor& aFunctor);
    void SetPropertyShuffleChanged(Functor& aFunctor);
    void SetPropertyTracksMaxChanged(Functor& aFunctor);

    void PropertyIdArray(Brh& aIdArray) const;
    void PropertyRepeat(TBool& aRepeat) const;
    void PropertyShuffle(TBool& aShuffle) const;
    void PropertyTracksMax(TUint& aTracksMax) const;
private:
    void IdArrayPropertyChanged();
    void RepeatPropertyChanged();
    void ShufflePropertyChanged();
    void TracksMaxPropertyChanged();
private:
    Mutex iLock;
    mutable Mutex iPropertyLock;
    Action* iActionRead;
    Action* iActionReadList;
    Action* iActionInsert;
    Action* iActionDelete;
    Action* iActionDeleteAll;
    Action* iActionSetRepeat;
    Action* iActionRepeat;
    Action* iActionSetShuffle;
    Action* iActionShuffle;
    Action* iActionTracksMax;
    Action* iActionIdArray;
    Action* iActionIdArrayChanged;
    PropertyBinary* iIdArray;
    PropertyBool* iRepeat;
    PropertyBool* iShuffle;
    PropertyUint* iTracksMax;
    Functor iIdArrayChanged;
    Functor iRepeatChanged;
    Functor iShuffleChanged;
    Functor iTracksMaxChanged;
};


class SyncReadLinnCoUkPlaylist1C : public SyncProxyAction
{
public:
    SyncReadLinnCoUkPlaylist1C(CpProxyLinnCoUkPlaylist1C& aProxy, Brh& aaUri, Brh& aaMetaData);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPlaylist1C& iService;
    Brh& iaUri;
    Brh& iaMetaData;
};

SyncReadLinnCoUkPlaylist1C::SyncReadLinnCoUkPlaylist1C(CpProxyLinnCoUkPlaylist1C& aProxy, Brh& aaUri, Brh& aaMetaData)
    : iService(aProxy)
    , iaUri(aaUri)
    , iaMetaData(aaMetaData)
{
}

void SyncReadLinnCoUkPlaylist1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndRead(aAsync, iaUri, iaMetaData);
}


class SyncReadListLinnCoUkPlaylist1C : public SyncProxyAction
{
public:
    SyncReadListLinnCoUkPlaylist1C(CpProxyLinnCoUkPlaylist1C& aProxy, Brh& aaMetaDataList);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPlaylist1C& iService;
    Brh& iaMetaDataList;
};

SyncReadListLinnCoUkPlaylist1C::SyncReadListLinnCoUkPlaylist1C(CpProxyLinnCoUkPlaylist1C& aProxy, Brh& aaMetaDataList)
    : iService(aProxy)
    , iaMetaDataList(aaMetaDataList)
{
}

void SyncReadListLinnCoUkPlaylist1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndReadList(aAsync, iaMetaDataList);
}


class SyncInsertLinnCoUkPlaylist1C : public SyncProxyAction
{
public:
    SyncInsertLinnCoUkPlaylist1C(CpProxyLinnCoUkPlaylist1C& aProxy, TUint& aaNewId);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPlaylist1C& iService;
    TUint& iaNewId;
};

SyncInsertLinnCoUkPlaylist1C::SyncInsertLinnCoUkPlaylist1C(CpProxyLinnCoUkPlaylist1C& aProxy, TUint& aaNewId)
    : iService(aProxy)
    , iaNewId(aaNewId)
{
}

void SyncInsertLinnCoUkPlaylist1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndInsert(aAsync, iaNewId);
}


class SyncDeleteLinnCoUkPlaylist1C : public SyncProxyAction
{
public:
    SyncDeleteLinnCoUkPlaylist1C(CpProxyLinnCoUkPlaylist1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPlaylist1C& iService;
};

SyncDeleteLinnCoUkPlaylist1C::SyncDeleteLinnCoUkPlaylist1C(CpProxyLinnCoUkPlaylist1C& aProxy)
    : iService(aProxy)
{
}

void SyncDeleteLinnCoUkPlaylist1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndDelete(aAsync);
}


class SyncDeleteAllLinnCoUkPlaylist1C : public SyncProxyAction
{
public:
    SyncDeleteAllLinnCoUkPlaylist1C(CpProxyLinnCoUkPlaylist1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPlaylist1C& iService;
};

SyncDeleteAllLinnCoUkPlaylist1C::SyncDeleteAllLinnCoUkPlaylist1C(CpProxyLinnCoUkPlaylist1C& aProxy)
    : iService(aProxy)
{
}

void SyncDeleteAllLinnCoUkPlaylist1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndDeleteAll(aAsync);
}


class SyncSetRepeatLinnCoUkPlaylist1C : public SyncProxyAction
{
public:
    SyncSetRepeatLinnCoUkPlaylist1C(CpProxyLinnCoUkPlaylist1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPlaylist1C& iService;
};

SyncSetRepeatLinnCoUkPlaylist1C::SyncSetRepeatLinnCoUkPlaylist1C(CpProxyLinnCoUkPlaylist1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetRepeatLinnCoUkPlaylist1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetRepeat(aAsync);
}


class SyncRepeatLinnCoUkPlaylist1C : public SyncProxyAction
{
public:
    SyncRepeatLinnCoUkPlaylist1C(CpProxyLinnCoUkPlaylist1C& aProxy, TBool& aaRepeat);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPlaylist1C& iService;
    TBool& iaRepeat;
};

SyncRepeatLinnCoUkPlaylist1C::SyncRepeatLinnCoUkPlaylist1C(CpProxyLinnCoUkPlaylist1C& aProxy, TBool& aaRepeat)
    : iService(aProxy)
    , iaRepeat(aaRepeat)
{
}

void SyncRepeatLinnCoUkPlaylist1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndRepeat(aAsync, iaRepeat);
}


class SyncSetShuffleLinnCoUkPlaylist1C : public SyncProxyAction
{
public:
    SyncSetShuffleLinnCoUkPlaylist1C(CpProxyLinnCoUkPlaylist1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPlaylist1C& iService;
};

SyncSetShuffleLinnCoUkPlaylist1C::SyncSetShuffleLinnCoUkPlaylist1C(CpProxyLinnCoUkPlaylist1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetShuffleLinnCoUkPlaylist1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetShuffle(aAsync);
}


class SyncShuffleLinnCoUkPlaylist1C : public SyncProxyAction
{
public:
    SyncShuffleLinnCoUkPlaylist1C(CpProxyLinnCoUkPlaylist1C& aProxy, TBool& aaShuffle);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPlaylist1C& iService;
    TBool& iaShuffle;
};

SyncShuffleLinnCoUkPlaylist1C::SyncShuffleLinnCoUkPlaylist1C(CpProxyLinnCoUkPlaylist1C& aProxy, TBool& aaShuffle)
    : iService(aProxy)
    , iaShuffle(aaShuffle)
{
}

void SyncShuffleLinnCoUkPlaylist1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndShuffle(aAsync, iaShuffle);
}


class SyncTracksMaxLinnCoUkPlaylist1C : public SyncProxyAction
{
public:
    SyncTracksMaxLinnCoUkPlaylist1C(CpProxyLinnCoUkPlaylist1C& aProxy, TUint& aaTracksMax);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPlaylist1C& iService;
    TUint& iaTracksMax;
};

SyncTracksMaxLinnCoUkPlaylist1C::SyncTracksMaxLinnCoUkPlaylist1C(CpProxyLinnCoUkPlaylist1C& aProxy, TUint& aaTracksMax)
    : iService(aProxy)
    , iaTracksMax(aaTracksMax)
{
}

void SyncTracksMaxLinnCoUkPlaylist1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndTracksMax(aAsync, iaTracksMax);
}


class SyncIdArrayLinnCoUkPlaylist1C : public SyncProxyAction
{
public:
    SyncIdArrayLinnCoUkPlaylist1C(CpProxyLinnCoUkPlaylist1C& aProxy, TUint& aaIdArrayToken, Brh& aaIdArray);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPlaylist1C& iService;
    TUint& iaIdArrayToken;
    Brh& iaIdArray;
};

SyncIdArrayLinnCoUkPlaylist1C::SyncIdArrayLinnCoUkPlaylist1C(CpProxyLinnCoUkPlaylist1C& aProxy, TUint& aaIdArrayToken, Brh& aaIdArray)
    : iService(aProxy)
    , iaIdArrayToken(aaIdArrayToken)
    , iaIdArray(aaIdArray)
{
}

void SyncIdArrayLinnCoUkPlaylist1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndIdArray(aAsync, iaIdArrayToken, iaIdArray);
}


class SyncIdArrayChangedLinnCoUkPlaylist1C : public SyncProxyAction
{
public:
    SyncIdArrayChangedLinnCoUkPlaylist1C(CpProxyLinnCoUkPlaylist1C& aProxy, TBool& aaIdArrayChanged);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPlaylist1C& iService;
    TBool& iaIdArrayChanged;
};

SyncIdArrayChangedLinnCoUkPlaylist1C::SyncIdArrayChangedLinnCoUkPlaylist1C(CpProxyLinnCoUkPlaylist1C& aProxy, TBool& aaIdArrayChanged)
    : iService(aProxy)
    , iaIdArrayChanged(aaIdArrayChanged)
{
}

void SyncIdArrayChangedLinnCoUkPlaylist1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndIdArrayChanged(aAsync, iaIdArrayChanged);
}

CpProxyLinnCoUkPlaylist1C::CpProxyLinnCoUkPlaylist1C(CpDeviceC aDevice)
    : CpProxyC("linn-co-uk", "Playlist", 1, *reinterpret_cast<CpiDevice*>(aDevice))
    , iLock("MPCS")
    , iPropertyLock("MPCP")
{
    Zapp::Parameter* param;

    iActionRead = new Action("Read");
    param = new Zapp::ParameterUint("aId");
    iActionRead->AddInputParameter(param);
    param = new Zapp::ParameterString("aUri");
    iActionRead->AddOutputParameter(param);
    param = new Zapp::ParameterString("aMetaData");
    iActionRead->AddOutputParameter(param);

    iActionReadList = new Action("ReadList");
    param = new Zapp::ParameterString("aIdList");
    iActionReadList->AddInputParameter(param);
    param = new Zapp::ParameterString("aMetaDataList");
    iActionReadList->AddOutputParameter(param);

    iActionInsert = new Action("Insert");
    param = new Zapp::ParameterUint("aAfterId");
    iActionInsert->AddInputParameter(param);
    param = new Zapp::ParameterString("aUri");
    iActionInsert->AddInputParameter(param);
    param = new Zapp::ParameterString("aMetaData");
    iActionInsert->AddInputParameter(param);
    param = new Zapp::ParameterUint("aNewId");
    iActionInsert->AddOutputParameter(param);

    iActionDelete = new Action("Delete");
    param = new Zapp::ParameterUint("aId");
    iActionDelete->AddInputParameter(param);

    iActionDeleteAll = new Action("DeleteAll");

    iActionSetRepeat = new Action("SetRepeat");
    param = new Zapp::ParameterBool("aRepeat");
    iActionSetRepeat->AddInputParameter(param);

    iActionRepeat = new Action("Repeat");
    param = new Zapp::ParameterBool("aRepeat");
    iActionRepeat->AddOutputParameter(param);

    iActionSetShuffle = new Action("SetShuffle");
    param = new Zapp::ParameterBool("aShuffle");
    iActionSetShuffle->AddInputParameter(param);

    iActionShuffle = new Action("Shuffle");
    param = new Zapp::ParameterBool("aShuffle");
    iActionShuffle->AddOutputParameter(param);

    iActionTracksMax = new Action("TracksMax");
    param = new Zapp::ParameterUint("aTracksMax");
    iActionTracksMax->AddOutputParameter(param);

    iActionIdArray = new Action("IdArray");
    param = new Zapp::ParameterUint("aIdArrayToken");
    iActionIdArray->AddOutputParameter(param);
    param = new Zapp::ParameterBinary("aIdArray");
    iActionIdArray->AddOutputParameter(param);

    iActionIdArrayChanged = new Action("IdArrayChanged");
    param = new Zapp::ParameterUint("aIdArrayToken");
    iActionIdArrayChanged->AddInputParameter(param);
    param = new Zapp::ParameterBool("aIdArrayChanged");
    iActionIdArrayChanged->AddOutputParameter(param);

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyLinnCoUkPlaylist1C::IdArrayPropertyChanged);
    iIdArray = new PropertyBinary("IdArray", functor);
    AddProperty(iIdArray);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkPlaylist1C::RepeatPropertyChanged);
    iRepeat = new PropertyBool("Repeat", functor);
    AddProperty(iRepeat);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkPlaylist1C::ShufflePropertyChanged);
    iShuffle = new PropertyBool("Shuffle", functor);
    AddProperty(iShuffle);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkPlaylist1C::TracksMaxPropertyChanged);
    iTracksMax = new PropertyUint("TracksMax", functor);
    AddProperty(iTracksMax);
}

CpProxyLinnCoUkPlaylist1C::~CpProxyLinnCoUkPlaylist1C()
{
    DestroyService();
    delete iActionRead;
    delete iActionReadList;
    delete iActionInsert;
    delete iActionDelete;
    delete iActionDeleteAll;
    delete iActionSetRepeat;
    delete iActionRepeat;
    delete iActionSetShuffle;
    delete iActionShuffle;
    delete iActionTracksMax;
    delete iActionIdArray;
    delete iActionIdArrayChanged;
}

void CpProxyLinnCoUkPlaylist1C::SyncRead(TUint aaId, Brh& aaUri, Brh& aaMetaData)
{
    SyncReadLinnCoUkPlaylist1C sync(*this, aaUri, aaMetaData);
    BeginRead(aaId, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPlaylist1C::BeginRead(TUint aaId, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionRead, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionRead->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaId));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionRead->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkPlaylist1C::EndRead(IAsync& aAsync, Brh& aaUri, Brh& aaMetaData)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Read"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aaUri);
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aaMetaData);
}

void CpProxyLinnCoUkPlaylist1C::SyncReadList(const Brx& aaIdList, Brh& aaMetaDataList)
{
    SyncReadListLinnCoUkPlaylist1C sync(*this, aaMetaDataList);
    BeginReadList(aaIdList, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPlaylist1C::BeginReadList(const Brx& aaIdList, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionReadList, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionReadList->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aaIdList));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionReadList->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkPlaylist1C::EndReadList(IAsync& aAsync, Brh& aaMetaDataList)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("ReadList"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aaMetaDataList);
}

void CpProxyLinnCoUkPlaylist1C::SyncInsert(TUint aaAfterId, const Brx& aaUri, const Brx& aaMetaData, TUint& aaNewId)
{
    SyncInsertLinnCoUkPlaylist1C sync(*this, aaNewId);
    BeginInsert(aaAfterId, aaUri, aaMetaData, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPlaylist1C::BeginInsert(TUint aaAfterId, const Brx& aaUri, const Brx& aaMetaData, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionInsert, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionInsert->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaAfterId));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aaUri));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aaMetaData));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionInsert->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkPlaylist1C::EndInsert(IAsync& aAsync, TUint& aaNewId)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Insert"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aaNewId = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyLinnCoUkPlaylist1C::SyncDelete(TUint aaId)
{
    SyncDeleteLinnCoUkPlaylist1C sync(*this);
    BeginDelete(aaId, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPlaylist1C::BeginDelete(TUint aaId, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionDelete, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionDelete->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaId));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkPlaylist1C::EndDelete(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Delete"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkPlaylist1C::SyncDeleteAll()
{
    SyncDeleteAllLinnCoUkPlaylist1C sync(*this);
    BeginDeleteAll(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPlaylist1C::BeginDeleteAll(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionDeleteAll, aFunctor);
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkPlaylist1C::EndDeleteAll(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("DeleteAll"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkPlaylist1C::SyncSetRepeat(TBool aaRepeat)
{
    SyncSetRepeatLinnCoUkPlaylist1C sync(*this);
    BeginSetRepeat(aaRepeat, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPlaylist1C::BeginSetRepeat(TBool aaRepeat, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetRepeat, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetRepeat->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aaRepeat));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkPlaylist1C::EndSetRepeat(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetRepeat"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkPlaylist1C::SyncRepeat(TBool& aaRepeat)
{
    SyncRepeatLinnCoUkPlaylist1C sync(*this, aaRepeat);
    BeginRepeat(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPlaylist1C::BeginRepeat(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionRepeat, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionRepeat->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkPlaylist1C::EndRepeat(IAsync& aAsync, TBool& aaRepeat)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Repeat"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aaRepeat = ((ArgumentBool*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyLinnCoUkPlaylist1C::SyncSetShuffle(TBool aaShuffle)
{
    SyncSetShuffleLinnCoUkPlaylist1C sync(*this);
    BeginSetShuffle(aaShuffle, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPlaylist1C::BeginSetShuffle(TBool aaShuffle, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetShuffle, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetShuffle->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aaShuffle));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkPlaylist1C::EndSetShuffle(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetShuffle"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkPlaylist1C::SyncShuffle(TBool& aaShuffle)
{
    SyncShuffleLinnCoUkPlaylist1C sync(*this, aaShuffle);
    BeginShuffle(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPlaylist1C::BeginShuffle(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionShuffle, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionShuffle->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkPlaylist1C::EndShuffle(IAsync& aAsync, TBool& aaShuffle)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Shuffle"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aaShuffle = ((ArgumentBool*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyLinnCoUkPlaylist1C::SyncTracksMax(TUint& aaTracksMax)
{
    SyncTracksMaxLinnCoUkPlaylist1C sync(*this, aaTracksMax);
    BeginTracksMax(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPlaylist1C::BeginTracksMax(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionTracksMax, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionTracksMax->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkPlaylist1C::EndTracksMax(IAsync& aAsync, TUint& aaTracksMax)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("TracksMax"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aaTracksMax = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyLinnCoUkPlaylist1C::SyncIdArray(TUint& aaIdArrayToken, Brh& aaIdArray)
{
    SyncIdArrayLinnCoUkPlaylist1C sync(*this, aaIdArrayToken, aaIdArray);
    BeginIdArray(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPlaylist1C::BeginIdArray(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionIdArray, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionIdArray->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentBinary(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkPlaylist1C::EndIdArray(IAsync& aAsync, TUint& aaIdArrayToken, Brh& aaIdArray)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("IdArray"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aaIdArrayToken = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    ((ArgumentBinary*)invocation.OutputArguments()[index++])->TransferTo(aaIdArray);
}

void CpProxyLinnCoUkPlaylist1C::SyncIdArrayChanged(TUint aaIdArrayToken, TBool& aaIdArrayChanged)
{
    SyncIdArrayChangedLinnCoUkPlaylist1C sync(*this, aaIdArrayChanged);
    BeginIdArrayChanged(aaIdArrayToken, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPlaylist1C::BeginIdArrayChanged(TUint aaIdArrayToken, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionIdArrayChanged, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionIdArrayChanged->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaIdArrayToken));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionIdArrayChanged->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkPlaylist1C::EndIdArrayChanged(IAsync& aAsync, TBool& aaIdArrayChanged)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("IdArrayChanged"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aaIdArrayChanged = ((ArgumentBool*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyLinnCoUkPlaylist1C::SetPropertyIdArrayChanged(Functor& aFunctor)
{
    iLock.Wait();
    iIdArrayChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkPlaylist1C::SetPropertyRepeatChanged(Functor& aFunctor)
{
    iLock.Wait();
    iRepeatChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkPlaylist1C::SetPropertyShuffleChanged(Functor& aFunctor)
{
    iLock.Wait();
    iShuffleChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkPlaylist1C::SetPropertyTracksMaxChanged(Functor& aFunctor)
{
    iLock.Wait();
    iTracksMaxChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkPlaylist1C::PropertyIdArray(Brh& aIdArray) const
{
    iPropertyLock.Wait();
    ASSERT(IsSubscribed());
    aIdArray.Set(iIdArray->Value());
    iPropertyLock.Signal();
}

void CpProxyLinnCoUkPlaylist1C::PropertyRepeat(TBool& aRepeat) const
{
    iPropertyLock.Wait();
    ASSERT(IsSubscribed());
    aRepeat = iRepeat->Value();
    iPropertyLock.Signal();
}

void CpProxyLinnCoUkPlaylist1C::PropertyShuffle(TBool& aShuffle) const
{
    iPropertyLock.Wait();
    ASSERT(IsSubscribed());
    aShuffle = iShuffle->Value();
    iPropertyLock.Signal();
}

void CpProxyLinnCoUkPlaylist1C::PropertyTracksMax(TUint& aTracksMax) const
{
    iPropertyLock.Wait();
    ASSERT(IsSubscribed());
    aTracksMax = iTracksMax->Value();
    iPropertyLock.Signal();
}

void CpProxyLinnCoUkPlaylist1C::IdArrayPropertyChanged()
{
    ReportEvent(iIdArrayChanged);
}

void CpProxyLinnCoUkPlaylist1C::RepeatPropertyChanged()
{
    ReportEvent(iRepeatChanged);
}

void CpProxyLinnCoUkPlaylist1C::ShufflePropertyChanged()
{
    ReportEvent(iShuffleChanged);
}

void CpProxyLinnCoUkPlaylist1C::TracksMaxPropertyChanged()
{
    ReportEvent(iTracksMaxChanged);
}


THandle CpProxyLinnCoUkPlaylist1Create(CpDeviceC aDevice)
{
    return new CpProxyLinnCoUkPlaylist1C(aDevice);
}

void CpProxyLinnCoUkPlaylist1Destroy(THandle aHandle)
{
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    delete proxyC;
}

void CpProxyLinnCoUkPlaylist1SyncRead(THandle aHandle, uint32_t aaId, char** aaUri, char** aaMetaData)
{
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaUri;
    Brh buf_aaMetaData;
    proxyC->SyncRead(aaId, buf_aaUri, buf_aaMetaData);
    *aaUri = buf_aaUri.Extract();
    *aaMetaData = buf_aaMetaData.Extract();
}

void CpProxyLinnCoUkPlaylist1BeginRead(THandle aHandle, uint32_t aaId, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginRead(aaId, functor);
}

int32_t CpProxyLinnCoUkPlaylist1EndRead(THandle aHandle, ZappHandleAsync aAsync, char** aaUri, char** aaMetaData)
{
    int32_t err = 0;
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaUri;
    *aaUri = NULL;
    Brh buf_aaMetaData;
    *aaMetaData = NULL;
    try {
        proxyC->EndRead(*async, buf_aaUri, buf_aaMetaData);
        *aaUri = buf_aaUri.Extract();
        *aaMetaData = buf_aaMetaData.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkPlaylist1SyncReadList(THandle aHandle, const char* aaIdList, char** aaMetaDataList)
{
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaIdList(aaIdList);
    Brh buf_aaMetaDataList;
    proxyC->SyncReadList(buf_aaIdList, buf_aaMetaDataList);
    *aaMetaDataList = buf_aaMetaDataList.Extract();
}

void CpProxyLinnCoUkPlaylist1BeginReadList(THandle aHandle, const char* aaIdList, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaIdList(aaIdList);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginReadList(buf_aaIdList, functor);
}

int32_t CpProxyLinnCoUkPlaylist1EndReadList(THandle aHandle, ZappHandleAsync aAsync, char** aaMetaDataList)
{
    int32_t err = 0;
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaMetaDataList;
    *aaMetaDataList = NULL;
    try {
        proxyC->EndReadList(*async, buf_aaMetaDataList);
        *aaMetaDataList = buf_aaMetaDataList.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkPlaylist1SyncInsert(THandle aHandle, uint32_t aaAfterId, const char* aaUri, const char* aaMetaData, uint32_t* aaNewId)
{
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaUri(aaUri);
    Brh buf_aaMetaData(aaMetaData);
    proxyC->SyncInsert(aaAfterId, buf_aaUri, buf_aaMetaData, *aaNewId);
}

void CpProxyLinnCoUkPlaylist1BeginInsert(THandle aHandle, uint32_t aaAfterId, const char* aaUri, const char* aaMetaData, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaUri(aaUri);
    Brh buf_aaMetaData(aaMetaData);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginInsert(aaAfterId, buf_aaUri, buf_aaMetaData, functor);
}

int32_t CpProxyLinnCoUkPlaylist1EndInsert(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaNewId)
{
    int32_t err = 0;
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndInsert(*async, *aaNewId);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkPlaylist1SyncDelete(THandle aHandle, uint32_t aaId)
{
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncDelete(aaId);
}

void CpProxyLinnCoUkPlaylist1BeginDelete(THandle aHandle, uint32_t aaId, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginDelete(aaId, functor);
}

int32_t CpProxyLinnCoUkPlaylist1EndDelete(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndDelete(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkPlaylist1SyncDeleteAll(THandle aHandle)
{
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncDeleteAll();
}

void CpProxyLinnCoUkPlaylist1BeginDeleteAll(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginDeleteAll(functor);
}

int32_t CpProxyLinnCoUkPlaylist1EndDeleteAll(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
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

void CpProxyLinnCoUkPlaylist1SyncSetRepeat(THandle aHandle, uint32_t aaRepeat)
{
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSetRepeat((aaRepeat==0? false : true));
}

void CpProxyLinnCoUkPlaylist1BeginSetRepeat(THandle aHandle, uint32_t aaRepeat, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetRepeat((aaRepeat==0? false : true), functor);
}

int32_t CpProxyLinnCoUkPlaylist1EndSetRepeat(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
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

void CpProxyLinnCoUkPlaylist1SyncRepeat(THandle aHandle, uint32_t* aaRepeat)
{
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aaRepeat = 0;
    proxyC->SyncRepeat(*(TBool*)aaRepeat);
}

void CpProxyLinnCoUkPlaylist1BeginRepeat(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginRepeat(functor);
}

int32_t CpProxyLinnCoUkPlaylist1EndRepeat(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaRepeat)
{
    int32_t err = 0;
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    *aaRepeat = 0;
    try {
        proxyC->EndRepeat(*async, *(TBool*)aaRepeat);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkPlaylist1SyncSetShuffle(THandle aHandle, uint32_t aaShuffle)
{
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSetShuffle((aaShuffle==0? false : true));
}

void CpProxyLinnCoUkPlaylist1BeginSetShuffle(THandle aHandle, uint32_t aaShuffle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetShuffle((aaShuffle==0? false : true), functor);
}

int32_t CpProxyLinnCoUkPlaylist1EndSetShuffle(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
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

void CpProxyLinnCoUkPlaylist1SyncShuffle(THandle aHandle, uint32_t* aaShuffle)
{
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aaShuffle = 0;
    proxyC->SyncShuffle(*(TBool*)aaShuffle);
}

void CpProxyLinnCoUkPlaylist1BeginShuffle(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginShuffle(functor);
}

int32_t CpProxyLinnCoUkPlaylist1EndShuffle(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaShuffle)
{
    int32_t err = 0;
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    *aaShuffle = 0;
    try {
        proxyC->EndShuffle(*async, *(TBool*)aaShuffle);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkPlaylist1SyncTracksMax(THandle aHandle, uint32_t* aaTracksMax)
{
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncTracksMax(*aaTracksMax);
}

void CpProxyLinnCoUkPlaylist1BeginTracksMax(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginTracksMax(functor);
}

int32_t CpProxyLinnCoUkPlaylist1EndTracksMax(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaTracksMax)
{
    int32_t err = 0;
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndTracksMax(*async, *aaTracksMax);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkPlaylist1SyncIdArray(THandle aHandle, uint32_t* aaIdArrayToken, char** aaIdArray, uint32_t* aaIdArrayLen)
{
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaIdArray;
    proxyC->SyncIdArray(*aaIdArrayToken, buf_aaIdArray);
    *aaIdArrayLen = buf_aaIdArray.Bytes();
    *aaIdArray = buf_aaIdArray.Extract();
}

void CpProxyLinnCoUkPlaylist1BeginIdArray(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginIdArray(functor);
}

int32_t CpProxyLinnCoUkPlaylist1EndIdArray(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaIdArrayToken, char** aaIdArray, uint32_t* aaIdArrayLen)
{
    int32_t err = 0;
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaIdArray;
    *aaIdArray = NULL;
    *aaIdArrayLen = 0;
    try {
        proxyC->EndIdArray(*async, *aaIdArrayToken, buf_aaIdArray);
        *aaIdArrayLen = buf_aaIdArray.Bytes();
        *aaIdArray = buf_aaIdArray.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkPlaylist1SyncIdArrayChanged(THandle aHandle, uint32_t aaIdArrayToken, uint32_t* aaIdArrayChanged)
{
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aaIdArrayChanged = 0;
    proxyC->SyncIdArrayChanged(aaIdArrayToken, *(TBool*)aaIdArrayChanged);
}

void CpProxyLinnCoUkPlaylist1BeginIdArrayChanged(THandle aHandle, uint32_t aaIdArrayToken, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginIdArrayChanged(aaIdArrayToken, functor);
}

int32_t CpProxyLinnCoUkPlaylist1EndIdArrayChanged(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaIdArrayChanged)
{
    int32_t err = 0;
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    *aaIdArrayChanged = 0;
    try {
        proxyC->EndIdArrayChanged(*async, *(TBool*)aaIdArrayChanged);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkPlaylist1SetPropertyIdArrayChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyIdArrayChanged(functor);
}

void CpProxyLinnCoUkPlaylist1SetPropertyRepeatChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyRepeatChanged(functor);
}

void CpProxyLinnCoUkPlaylist1SetPropertyShuffleChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyShuffleChanged(functor);
}

void CpProxyLinnCoUkPlaylist1SetPropertyTracksMaxChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyTracksMaxChanged(functor);
}

void CpProxyLinnCoUkPlaylist1PropertyIdArray(THandle aHandle, char** aIdArray, uint32_t* aLen)
{
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aIdArray;
    proxyC->PropertyIdArray(buf_aIdArray);
    *aLen = buf_aIdArray.Bytes();
    *aIdArray = buf_aIdArray.Extract();
}

void CpProxyLinnCoUkPlaylist1PropertyRepeat(THandle aHandle, uint32_t* aRepeat)
{
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aRepeat = false;
    proxyC->PropertyRepeat(*(TBool*)aRepeat);
}

void CpProxyLinnCoUkPlaylist1PropertyShuffle(THandle aHandle, uint32_t* aShuffle)
{
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aShuffle = false;
    proxyC->PropertyShuffle(*(TBool*)aShuffle);
}

void CpProxyLinnCoUkPlaylist1PropertyTracksMax(THandle aHandle, uint32_t* aTracksMax)
{
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyTracksMax(*aTracksMax);
}

