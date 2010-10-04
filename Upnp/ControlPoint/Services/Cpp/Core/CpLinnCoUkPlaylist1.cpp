#include <Core/CpLinnCoUkPlaylist1.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Core/CpDevice.h>

using namespace Zapp;


class SyncReadLinnCoUkPlaylist1 : public SyncProxyAction
{
public:
    SyncReadLinnCoUkPlaylist1(CpProxyLinnCoUkPlaylist1& aService, Brh& aaUri, Brh& aaMetaData);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPlaylist1& iService;
    Brh& iaUri;
    Brh& iaMetaData;
};

SyncReadLinnCoUkPlaylist1::SyncReadLinnCoUkPlaylist1(CpProxyLinnCoUkPlaylist1& aService, Brh& aaUri, Brh& aaMetaData)
    : iService(aService)
    , iaUri(aaUri)
    , iaMetaData(aaMetaData)
{
}

void SyncReadLinnCoUkPlaylist1::CompleteRequest(IAsync& aAsync)
{
    iService.EndRead(aAsync, iaUri, iaMetaData);
}


class SyncReadListLinnCoUkPlaylist1 : public SyncProxyAction
{
public:
    SyncReadListLinnCoUkPlaylist1(CpProxyLinnCoUkPlaylist1& aService, Brh& aaMetaDataList);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPlaylist1& iService;
    Brh& iaMetaDataList;
};

SyncReadListLinnCoUkPlaylist1::SyncReadListLinnCoUkPlaylist1(CpProxyLinnCoUkPlaylist1& aService, Brh& aaMetaDataList)
    : iService(aService)
    , iaMetaDataList(aaMetaDataList)
{
}

void SyncReadListLinnCoUkPlaylist1::CompleteRequest(IAsync& aAsync)
{
    iService.EndReadList(aAsync, iaMetaDataList);
}


class SyncInsertLinnCoUkPlaylist1 : public SyncProxyAction
{
public:
    SyncInsertLinnCoUkPlaylist1(CpProxyLinnCoUkPlaylist1& aService, TUint& aaNewId);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPlaylist1& iService;
    TUint& iaNewId;
};

SyncInsertLinnCoUkPlaylist1::SyncInsertLinnCoUkPlaylist1(CpProxyLinnCoUkPlaylist1& aService, TUint& aaNewId)
    : iService(aService)
    , iaNewId(aaNewId)
{
}

void SyncInsertLinnCoUkPlaylist1::CompleteRequest(IAsync& aAsync)
{
    iService.EndInsert(aAsync, iaNewId);
}


class SyncDeleteLinnCoUkPlaylist1 : public SyncProxyAction
{
public:
    SyncDeleteLinnCoUkPlaylist1(CpProxyLinnCoUkPlaylist1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPlaylist1& iService;
};

SyncDeleteLinnCoUkPlaylist1::SyncDeleteLinnCoUkPlaylist1(CpProxyLinnCoUkPlaylist1& aService)
    : iService(aService)
{
}

void SyncDeleteLinnCoUkPlaylist1::CompleteRequest(IAsync& aAsync)
{
    iService.EndDelete(aAsync);
}


class SyncDeleteAllLinnCoUkPlaylist1 : public SyncProxyAction
{
public:
    SyncDeleteAllLinnCoUkPlaylist1(CpProxyLinnCoUkPlaylist1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPlaylist1& iService;
};

SyncDeleteAllLinnCoUkPlaylist1::SyncDeleteAllLinnCoUkPlaylist1(CpProxyLinnCoUkPlaylist1& aService)
    : iService(aService)
{
}

void SyncDeleteAllLinnCoUkPlaylist1::CompleteRequest(IAsync& aAsync)
{
    iService.EndDeleteAll(aAsync);
}


class SyncSetRepeatLinnCoUkPlaylist1 : public SyncProxyAction
{
public:
    SyncSetRepeatLinnCoUkPlaylist1(CpProxyLinnCoUkPlaylist1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPlaylist1& iService;
};

SyncSetRepeatLinnCoUkPlaylist1::SyncSetRepeatLinnCoUkPlaylist1(CpProxyLinnCoUkPlaylist1& aService)
    : iService(aService)
{
}

void SyncSetRepeatLinnCoUkPlaylist1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetRepeat(aAsync);
}


class SyncRepeatLinnCoUkPlaylist1 : public SyncProxyAction
{
public:
    SyncRepeatLinnCoUkPlaylist1(CpProxyLinnCoUkPlaylist1& aService, TBool& aaRepeat);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPlaylist1& iService;
    TBool& iaRepeat;
};

SyncRepeatLinnCoUkPlaylist1::SyncRepeatLinnCoUkPlaylist1(CpProxyLinnCoUkPlaylist1& aService, TBool& aaRepeat)
    : iService(aService)
    , iaRepeat(aaRepeat)
{
}

void SyncRepeatLinnCoUkPlaylist1::CompleteRequest(IAsync& aAsync)
{
    iService.EndRepeat(aAsync, iaRepeat);
}


class SyncSetShuffleLinnCoUkPlaylist1 : public SyncProxyAction
{
public:
    SyncSetShuffleLinnCoUkPlaylist1(CpProxyLinnCoUkPlaylist1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPlaylist1& iService;
};

SyncSetShuffleLinnCoUkPlaylist1::SyncSetShuffleLinnCoUkPlaylist1(CpProxyLinnCoUkPlaylist1& aService)
    : iService(aService)
{
}

void SyncSetShuffleLinnCoUkPlaylist1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetShuffle(aAsync);
}


class SyncShuffleLinnCoUkPlaylist1 : public SyncProxyAction
{
public:
    SyncShuffleLinnCoUkPlaylist1(CpProxyLinnCoUkPlaylist1& aService, TBool& aaShuffle);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPlaylist1& iService;
    TBool& iaShuffle;
};

SyncShuffleLinnCoUkPlaylist1::SyncShuffleLinnCoUkPlaylist1(CpProxyLinnCoUkPlaylist1& aService, TBool& aaShuffle)
    : iService(aService)
    , iaShuffle(aaShuffle)
{
}

void SyncShuffleLinnCoUkPlaylist1::CompleteRequest(IAsync& aAsync)
{
    iService.EndShuffle(aAsync, iaShuffle);
}


class SyncTracksMaxLinnCoUkPlaylist1 : public SyncProxyAction
{
public:
    SyncTracksMaxLinnCoUkPlaylist1(CpProxyLinnCoUkPlaylist1& aService, TUint& aaTracksMax);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPlaylist1& iService;
    TUint& iaTracksMax;
};

SyncTracksMaxLinnCoUkPlaylist1::SyncTracksMaxLinnCoUkPlaylist1(CpProxyLinnCoUkPlaylist1& aService, TUint& aaTracksMax)
    : iService(aService)
    , iaTracksMax(aaTracksMax)
{
}

void SyncTracksMaxLinnCoUkPlaylist1::CompleteRequest(IAsync& aAsync)
{
    iService.EndTracksMax(aAsync, iaTracksMax);
}


class SyncIdArrayLinnCoUkPlaylist1 : public SyncProxyAction
{
public:
    SyncIdArrayLinnCoUkPlaylist1(CpProxyLinnCoUkPlaylist1& aService, TUint& aaIdArrayToken, Brh& aaIdArray);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPlaylist1& iService;
    TUint& iaIdArrayToken;
    Brh& iaIdArray;
};

SyncIdArrayLinnCoUkPlaylist1::SyncIdArrayLinnCoUkPlaylist1(CpProxyLinnCoUkPlaylist1& aService, TUint& aaIdArrayToken, Brh& aaIdArray)
    : iService(aService)
    , iaIdArrayToken(aaIdArrayToken)
    , iaIdArray(aaIdArray)
{
}

void SyncIdArrayLinnCoUkPlaylist1::CompleteRequest(IAsync& aAsync)
{
    iService.EndIdArray(aAsync, iaIdArrayToken, iaIdArray);
}


class SyncIdArrayChangedLinnCoUkPlaylist1 : public SyncProxyAction
{
public:
    SyncIdArrayChangedLinnCoUkPlaylist1(CpProxyLinnCoUkPlaylist1& aService, TBool& aaIdArrayChanged);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPlaylist1& iService;
    TBool& iaIdArrayChanged;
};

SyncIdArrayChangedLinnCoUkPlaylist1::SyncIdArrayChangedLinnCoUkPlaylist1(CpProxyLinnCoUkPlaylist1& aService, TBool& aaIdArrayChanged)
    : iService(aService)
    , iaIdArrayChanged(aaIdArrayChanged)
{
}

void SyncIdArrayChangedLinnCoUkPlaylist1::CompleteRequest(IAsync& aAsync)
{
    iService.EndIdArrayChanged(aAsync, iaIdArrayChanged);
}


CpProxyLinnCoUkPlaylist1::CpProxyLinnCoUkPlaylist1(CpDevice& aDevice)
{
    iService = new CpiService("linn-co-uk", "Playlist", 1, aDevice.Device());
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
    functor = MakeFunctor(*this, &CpProxyLinnCoUkPlaylist1::IdArrayPropertyChanged);
    iIdArray = new PropertyBinary("IdArray", functor);
    iService->AddProperty(iIdArray);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkPlaylist1::RepeatPropertyChanged);
    iRepeat = new PropertyBool("Repeat", functor);
    iService->AddProperty(iRepeat);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkPlaylist1::ShufflePropertyChanged);
    iShuffle = new PropertyBool("Shuffle", functor);
    iService->AddProperty(iShuffle);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkPlaylist1::TracksMaxPropertyChanged);
    iTracksMax = new PropertyUint("TracksMax", functor);
    iService->AddProperty(iTracksMax);
}

CpProxyLinnCoUkPlaylist1::~CpProxyLinnCoUkPlaylist1()
{
    delete iService;
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

void CpProxyLinnCoUkPlaylist1::SyncRead(TUint aaId, Brh& aaUri, Brh& aaMetaData)
{
    SyncReadLinnCoUkPlaylist1 sync(*this, aaUri, aaMetaData);
    BeginRead(aaId, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPlaylist1::BeginRead(TUint aaId, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionRead, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionRead->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaId));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionRead->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkPlaylist1::EndRead(IAsync& aAsync, Brh& aaUri, Brh& aaMetaData)
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

void CpProxyLinnCoUkPlaylist1::SyncReadList(const Brx& aaIdList, Brh& aaMetaDataList)
{
    SyncReadListLinnCoUkPlaylist1 sync(*this, aaMetaDataList);
    BeginReadList(aaIdList, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPlaylist1::BeginReadList(const Brx& aaIdList, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionReadList, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionReadList->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aaIdList));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionReadList->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkPlaylist1::EndReadList(IAsync& aAsync, Brh& aaMetaDataList)
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

void CpProxyLinnCoUkPlaylist1::SyncInsert(TUint aaAfterId, const Brx& aaUri, const Brx& aaMetaData, TUint& aaNewId)
{
    SyncInsertLinnCoUkPlaylist1 sync(*this, aaNewId);
    BeginInsert(aaAfterId, aaUri, aaMetaData, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPlaylist1::BeginInsert(TUint aaAfterId, const Brx& aaUri, const Brx& aaMetaData, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionInsert, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionInsert->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaAfterId));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aaUri));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aaMetaData));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionInsert->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkPlaylist1::EndInsert(IAsync& aAsync, TUint& aaNewId)
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

void CpProxyLinnCoUkPlaylist1::SyncDelete(TUint aaId)
{
    SyncDeleteLinnCoUkPlaylist1 sync(*this);
    BeginDelete(aaId, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPlaylist1::BeginDelete(TUint aaId, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionDelete, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionDelete->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaId));
    invocation->Invoke();
}

void CpProxyLinnCoUkPlaylist1::EndDelete(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Delete"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkPlaylist1::SyncDeleteAll()
{
    SyncDeleteAllLinnCoUkPlaylist1 sync(*this);
    BeginDeleteAll(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPlaylist1::BeginDeleteAll(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionDeleteAll, aFunctor);
    invocation->Invoke();
}

void CpProxyLinnCoUkPlaylist1::EndDeleteAll(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("DeleteAll"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkPlaylist1::SyncSetRepeat(TBool aaRepeat)
{
    SyncSetRepeatLinnCoUkPlaylist1 sync(*this);
    BeginSetRepeat(aaRepeat, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPlaylist1::BeginSetRepeat(TBool aaRepeat, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetRepeat, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetRepeat->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aaRepeat));
    invocation->Invoke();
}

void CpProxyLinnCoUkPlaylist1::EndSetRepeat(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetRepeat"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkPlaylist1::SyncRepeat(TBool& aaRepeat)
{
    SyncRepeatLinnCoUkPlaylist1 sync(*this, aaRepeat);
    BeginRepeat(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPlaylist1::BeginRepeat(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionRepeat, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionRepeat->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkPlaylist1::EndRepeat(IAsync& aAsync, TBool& aaRepeat)
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

void CpProxyLinnCoUkPlaylist1::SyncSetShuffle(TBool aaShuffle)
{
    SyncSetShuffleLinnCoUkPlaylist1 sync(*this);
    BeginSetShuffle(aaShuffle, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPlaylist1::BeginSetShuffle(TBool aaShuffle, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetShuffle, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetShuffle->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aaShuffle));
    invocation->Invoke();
}

void CpProxyLinnCoUkPlaylist1::EndSetShuffle(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetShuffle"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkPlaylist1::SyncShuffle(TBool& aaShuffle)
{
    SyncShuffleLinnCoUkPlaylist1 sync(*this, aaShuffle);
    BeginShuffle(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPlaylist1::BeginShuffle(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionShuffle, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionShuffle->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkPlaylist1::EndShuffle(IAsync& aAsync, TBool& aaShuffle)
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

void CpProxyLinnCoUkPlaylist1::SyncTracksMax(TUint& aaTracksMax)
{
    SyncTracksMaxLinnCoUkPlaylist1 sync(*this, aaTracksMax);
    BeginTracksMax(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPlaylist1::BeginTracksMax(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionTracksMax, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionTracksMax->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkPlaylist1::EndTracksMax(IAsync& aAsync, TUint& aaTracksMax)
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

void CpProxyLinnCoUkPlaylist1::SyncIdArray(TUint& aaIdArrayToken, Brh& aaIdArray)
{
    SyncIdArrayLinnCoUkPlaylist1 sync(*this, aaIdArrayToken, aaIdArray);
    BeginIdArray(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPlaylist1::BeginIdArray(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionIdArray, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionIdArray->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentBinary(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkPlaylist1::EndIdArray(IAsync& aAsync, TUint& aaIdArrayToken, Brh& aaIdArray)
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

void CpProxyLinnCoUkPlaylist1::SyncIdArrayChanged(TUint aaIdArrayToken, TBool& aaIdArrayChanged)
{
    SyncIdArrayChangedLinnCoUkPlaylist1 sync(*this, aaIdArrayChanged);
    BeginIdArrayChanged(aaIdArrayToken, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPlaylist1::BeginIdArrayChanged(TUint aaIdArrayToken, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionIdArrayChanged, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionIdArrayChanged->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaIdArrayToken));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionIdArrayChanged->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkPlaylist1::EndIdArrayChanged(IAsync& aAsync, TBool& aaIdArrayChanged)
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

void CpProxyLinnCoUkPlaylist1::SetPropertyIdArrayChanged(Functor& aFunctor)
{
    iLock->Wait();
    iIdArrayChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkPlaylist1::SetPropertyRepeatChanged(Functor& aFunctor)
{
    iLock->Wait();
    iRepeatChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkPlaylist1::SetPropertyShuffleChanged(Functor& aFunctor)
{
    iLock->Wait();
    iShuffleChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkPlaylist1::SetPropertyTracksMaxChanged(Functor& aFunctor)
{
    iLock->Wait();
    iTracksMaxChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkPlaylist1::PropertyIdArray(Brh& aIdArray) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aIdArray.Set(iIdArray->Value());
}

void CpProxyLinnCoUkPlaylist1::PropertyRepeat(TBool& aRepeat) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aRepeat = iRepeat->Value();
}

void CpProxyLinnCoUkPlaylist1::PropertyShuffle(TBool& aShuffle) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aShuffle = iShuffle->Value();
}

void CpProxyLinnCoUkPlaylist1::PropertyTracksMax(TUint& aTracksMax) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aTracksMax = iTracksMax->Value();
}

void CpProxyLinnCoUkPlaylist1::IdArrayPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iIdArrayChanged != NULL) {
        iIdArrayChanged();
    }
}

void CpProxyLinnCoUkPlaylist1::RepeatPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iRepeatChanged != NULL) {
        iRepeatChanged();
    }
}

void CpProxyLinnCoUkPlaylist1::ShufflePropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iShuffleChanged != NULL) {
        iShuffleChanged();
    }
}

void CpProxyLinnCoUkPlaylist1::TracksMaxPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iTracksMaxChanged != NULL) {
        iTracksMaxChanged();
    }
}

