#include <Std/CpLinnCoUkPlaylist1.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Buffer.h>
#include <Std/CpDevice.h>

#include <string>

using namespace Zapp;


class SyncReadLinnCoUkPlaylist1Cpp : public SyncProxyAction
{
public:
    SyncReadLinnCoUkPlaylist1Cpp(CpProxyLinnCoUkPlaylist1Cpp& aService, std::string& aaUri, std::string& aaMetaData);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPlaylist1Cpp& iService;
    std::string& iaUri;
    std::string& iaMetaData;
};

SyncReadLinnCoUkPlaylist1Cpp::SyncReadLinnCoUkPlaylist1Cpp(CpProxyLinnCoUkPlaylist1Cpp& aService, std::string& aaUri, std::string& aaMetaData)
    : iService(aService)
    , iaUri(aaUri)
    , iaMetaData(aaMetaData)
{
}

void SyncReadLinnCoUkPlaylist1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndRead(aAsync, iaUri, iaMetaData);
}


class SyncReadListLinnCoUkPlaylist1Cpp : public SyncProxyAction
{
public:
    SyncReadListLinnCoUkPlaylist1Cpp(CpProxyLinnCoUkPlaylist1Cpp& aService, std::string& aaMetaDataList);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPlaylist1Cpp& iService;
    std::string& iaMetaDataList;
};

SyncReadListLinnCoUkPlaylist1Cpp::SyncReadListLinnCoUkPlaylist1Cpp(CpProxyLinnCoUkPlaylist1Cpp& aService, std::string& aaMetaDataList)
    : iService(aService)
    , iaMetaDataList(aaMetaDataList)
{
}

void SyncReadListLinnCoUkPlaylist1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndReadList(aAsync, iaMetaDataList);
}


class SyncInsertLinnCoUkPlaylist1Cpp : public SyncProxyAction
{
public:
    SyncInsertLinnCoUkPlaylist1Cpp(CpProxyLinnCoUkPlaylist1Cpp& aService, uint32_t& aaNewId);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPlaylist1Cpp& iService;
    uint32_t& iaNewId;
};

SyncInsertLinnCoUkPlaylist1Cpp::SyncInsertLinnCoUkPlaylist1Cpp(CpProxyLinnCoUkPlaylist1Cpp& aService, uint32_t& aaNewId)
    : iService(aService)
    , iaNewId(aaNewId)
{
}

void SyncInsertLinnCoUkPlaylist1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndInsert(aAsync, iaNewId);
}


class SyncDeleteLinnCoUkPlaylist1Cpp : public SyncProxyAction
{
public:
    SyncDeleteLinnCoUkPlaylist1Cpp(CpProxyLinnCoUkPlaylist1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPlaylist1Cpp& iService;
};

SyncDeleteLinnCoUkPlaylist1Cpp::SyncDeleteLinnCoUkPlaylist1Cpp(CpProxyLinnCoUkPlaylist1Cpp& aService)
    : iService(aService)
{
}

void SyncDeleteLinnCoUkPlaylist1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndDelete(aAsync);
}


class SyncDeleteAllLinnCoUkPlaylist1Cpp : public SyncProxyAction
{
public:
    SyncDeleteAllLinnCoUkPlaylist1Cpp(CpProxyLinnCoUkPlaylist1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPlaylist1Cpp& iService;
};

SyncDeleteAllLinnCoUkPlaylist1Cpp::SyncDeleteAllLinnCoUkPlaylist1Cpp(CpProxyLinnCoUkPlaylist1Cpp& aService)
    : iService(aService)
{
}

void SyncDeleteAllLinnCoUkPlaylist1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndDeleteAll(aAsync);
}


class SyncSetRepeatLinnCoUkPlaylist1Cpp : public SyncProxyAction
{
public:
    SyncSetRepeatLinnCoUkPlaylist1Cpp(CpProxyLinnCoUkPlaylist1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPlaylist1Cpp& iService;
};

SyncSetRepeatLinnCoUkPlaylist1Cpp::SyncSetRepeatLinnCoUkPlaylist1Cpp(CpProxyLinnCoUkPlaylist1Cpp& aService)
    : iService(aService)
{
}

void SyncSetRepeatLinnCoUkPlaylist1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetRepeat(aAsync);
}


class SyncRepeatLinnCoUkPlaylist1Cpp : public SyncProxyAction
{
public:
    SyncRepeatLinnCoUkPlaylist1Cpp(CpProxyLinnCoUkPlaylist1Cpp& aService, bool& aaRepeat);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPlaylist1Cpp& iService;
    bool& iaRepeat;
};

SyncRepeatLinnCoUkPlaylist1Cpp::SyncRepeatLinnCoUkPlaylist1Cpp(CpProxyLinnCoUkPlaylist1Cpp& aService, bool& aaRepeat)
    : iService(aService)
    , iaRepeat(aaRepeat)
{
}

void SyncRepeatLinnCoUkPlaylist1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndRepeat(aAsync, iaRepeat);
}


class SyncSetShuffleLinnCoUkPlaylist1Cpp : public SyncProxyAction
{
public:
    SyncSetShuffleLinnCoUkPlaylist1Cpp(CpProxyLinnCoUkPlaylist1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPlaylist1Cpp& iService;
};

SyncSetShuffleLinnCoUkPlaylist1Cpp::SyncSetShuffleLinnCoUkPlaylist1Cpp(CpProxyLinnCoUkPlaylist1Cpp& aService)
    : iService(aService)
{
}

void SyncSetShuffleLinnCoUkPlaylist1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetShuffle(aAsync);
}


class SyncShuffleLinnCoUkPlaylist1Cpp : public SyncProxyAction
{
public:
    SyncShuffleLinnCoUkPlaylist1Cpp(CpProxyLinnCoUkPlaylist1Cpp& aService, bool& aaShuffle);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPlaylist1Cpp& iService;
    bool& iaShuffle;
};

SyncShuffleLinnCoUkPlaylist1Cpp::SyncShuffleLinnCoUkPlaylist1Cpp(CpProxyLinnCoUkPlaylist1Cpp& aService, bool& aaShuffle)
    : iService(aService)
    , iaShuffle(aaShuffle)
{
}

void SyncShuffleLinnCoUkPlaylist1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndShuffle(aAsync, iaShuffle);
}


class SyncTracksMaxLinnCoUkPlaylist1Cpp : public SyncProxyAction
{
public:
    SyncTracksMaxLinnCoUkPlaylist1Cpp(CpProxyLinnCoUkPlaylist1Cpp& aService, uint32_t& aaTracksMax);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPlaylist1Cpp& iService;
    uint32_t& iaTracksMax;
};

SyncTracksMaxLinnCoUkPlaylist1Cpp::SyncTracksMaxLinnCoUkPlaylist1Cpp(CpProxyLinnCoUkPlaylist1Cpp& aService, uint32_t& aaTracksMax)
    : iService(aService)
    , iaTracksMax(aaTracksMax)
{
}

void SyncTracksMaxLinnCoUkPlaylist1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndTracksMax(aAsync, iaTracksMax);
}


class SyncIdArrayLinnCoUkPlaylist1Cpp : public SyncProxyAction
{
public:
    SyncIdArrayLinnCoUkPlaylist1Cpp(CpProxyLinnCoUkPlaylist1Cpp& aService, uint32_t& aaIdArrayToken, std::string& aaIdArray);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPlaylist1Cpp& iService;
    uint32_t& iaIdArrayToken;
    std::string& iaIdArray;
};

SyncIdArrayLinnCoUkPlaylist1Cpp::SyncIdArrayLinnCoUkPlaylist1Cpp(CpProxyLinnCoUkPlaylist1Cpp& aService, uint32_t& aaIdArrayToken, std::string& aaIdArray)
    : iService(aService)
    , iaIdArrayToken(aaIdArrayToken)
    , iaIdArray(aaIdArray)
{
}

void SyncIdArrayLinnCoUkPlaylist1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndIdArray(aAsync, iaIdArrayToken, iaIdArray);
}


class SyncIdArrayChangedLinnCoUkPlaylist1Cpp : public SyncProxyAction
{
public:
    SyncIdArrayChangedLinnCoUkPlaylist1Cpp(CpProxyLinnCoUkPlaylist1Cpp& aService, bool& aaIdArrayChanged);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPlaylist1Cpp& iService;
    bool& iaIdArrayChanged;
};

SyncIdArrayChangedLinnCoUkPlaylist1Cpp::SyncIdArrayChangedLinnCoUkPlaylist1Cpp(CpProxyLinnCoUkPlaylist1Cpp& aService, bool& aaIdArrayChanged)
    : iService(aService)
    , iaIdArrayChanged(aaIdArrayChanged)
{
}

void SyncIdArrayChangedLinnCoUkPlaylist1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndIdArrayChanged(aAsync, iaIdArrayChanged);
}


CpProxyLinnCoUkPlaylist1Cpp::CpProxyLinnCoUkPlaylist1Cpp(CpDeviceCpp& aDevice)
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
    functor = MakeFunctor(*this, &CpProxyLinnCoUkPlaylist1Cpp::IdArrayPropertyChanged);
    iIdArray = new PropertyBinary("IdArray", functor);
    iService->AddProperty(iIdArray);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkPlaylist1Cpp::RepeatPropertyChanged);
    iRepeat = new PropertyBool("Repeat", functor);
    iService->AddProperty(iRepeat);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkPlaylist1Cpp::ShufflePropertyChanged);
    iShuffle = new PropertyBool("Shuffle", functor);
    iService->AddProperty(iShuffle);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkPlaylist1Cpp::TracksMaxPropertyChanged);
    iTracksMax = new PropertyUint("TracksMax", functor);
    iService->AddProperty(iTracksMax);
}

CpProxyLinnCoUkPlaylist1Cpp::~CpProxyLinnCoUkPlaylist1Cpp()
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

void CpProxyLinnCoUkPlaylist1Cpp::SyncRead(uint32_t aaId, std::string& aaUri, std::string& aaMetaData)
{
    SyncReadLinnCoUkPlaylist1Cpp sync(*this, aaUri, aaMetaData);
    BeginRead(aaId, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPlaylist1Cpp::BeginRead(uint32_t aaId, FunctorAsync& aFunctor)
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

void CpProxyLinnCoUkPlaylist1Cpp::EndRead(IAsync& aAsync, std::string& aaUri, std::string& aaMetaData)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Read"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aaUri.assign((const char*)val.Ptr(), val.Bytes());
    }
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aaMetaData.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyLinnCoUkPlaylist1Cpp::SyncReadList(const std::string& aaIdList, std::string& aaMetaDataList)
{
    SyncReadListLinnCoUkPlaylist1Cpp sync(*this, aaMetaDataList);
    BeginReadList(aaIdList, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPlaylist1Cpp::BeginReadList(const std::string& aaIdList, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionReadList, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionReadList->InputParameters();
    {
        Brn buf((const TByte*)aaIdList.c_str(), aaIdList.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionReadList->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkPlaylist1Cpp::EndReadList(IAsync& aAsync, std::string& aaMetaDataList)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("ReadList"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aaMetaDataList.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyLinnCoUkPlaylist1Cpp::SyncInsert(uint32_t aaAfterId, const std::string& aaUri, const std::string& aaMetaData, uint32_t& aaNewId)
{
    SyncInsertLinnCoUkPlaylist1Cpp sync(*this, aaNewId);
    BeginInsert(aaAfterId, aaUri, aaMetaData, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPlaylist1Cpp::BeginInsert(uint32_t aaAfterId, const std::string& aaUri, const std::string& aaMetaData, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionInsert, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionInsert->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaAfterId));
    {
        Brn buf((const TByte*)aaUri.c_str(), aaUri.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aaMetaData.c_str(), aaMetaData.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionInsert->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkPlaylist1Cpp::EndInsert(IAsync& aAsync, uint32_t& aaNewId)
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

void CpProxyLinnCoUkPlaylist1Cpp::SyncDelete(uint32_t aaId)
{
    SyncDeleteLinnCoUkPlaylist1Cpp sync(*this);
    BeginDelete(aaId, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPlaylist1Cpp::BeginDelete(uint32_t aaId, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionDelete, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionDelete->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaId));
    invocation->Invoke();
}

void CpProxyLinnCoUkPlaylist1Cpp::EndDelete(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Delete"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkPlaylist1Cpp::SyncDeleteAll()
{
    SyncDeleteAllLinnCoUkPlaylist1Cpp sync(*this);
    BeginDeleteAll(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPlaylist1Cpp::BeginDeleteAll(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionDeleteAll, aFunctor);
    invocation->Invoke();
}

void CpProxyLinnCoUkPlaylist1Cpp::EndDeleteAll(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("DeleteAll"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkPlaylist1Cpp::SyncSetRepeat(bool aaRepeat)
{
    SyncSetRepeatLinnCoUkPlaylist1Cpp sync(*this);
    BeginSetRepeat(aaRepeat, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPlaylist1Cpp::BeginSetRepeat(bool aaRepeat, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetRepeat, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetRepeat->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aaRepeat));
    invocation->Invoke();
}

void CpProxyLinnCoUkPlaylist1Cpp::EndSetRepeat(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetRepeat"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkPlaylist1Cpp::SyncRepeat(bool& aaRepeat)
{
    SyncRepeatLinnCoUkPlaylist1Cpp sync(*this, aaRepeat);
    BeginRepeat(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPlaylist1Cpp::BeginRepeat(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionRepeat, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionRepeat->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkPlaylist1Cpp::EndRepeat(IAsync& aAsync, bool& aaRepeat)
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

void CpProxyLinnCoUkPlaylist1Cpp::SyncSetShuffle(bool aaShuffle)
{
    SyncSetShuffleLinnCoUkPlaylist1Cpp sync(*this);
    BeginSetShuffle(aaShuffle, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPlaylist1Cpp::BeginSetShuffle(bool aaShuffle, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetShuffle, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetShuffle->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aaShuffle));
    invocation->Invoke();
}

void CpProxyLinnCoUkPlaylist1Cpp::EndSetShuffle(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetShuffle"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkPlaylist1Cpp::SyncShuffle(bool& aaShuffle)
{
    SyncShuffleLinnCoUkPlaylist1Cpp sync(*this, aaShuffle);
    BeginShuffle(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPlaylist1Cpp::BeginShuffle(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionShuffle, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionShuffle->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkPlaylist1Cpp::EndShuffle(IAsync& aAsync, bool& aaShuffle)
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

void CpProxyLinnCoUkPlaylist1Cpp::SyncTracksMax(uint32_t& aaTracksMax)
{
    SyncTracksMaxLinnCoUkPlaylist1Cpp sync(*this, aaTracksMax);
    BeginTracksMax(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPlaylist1Cpp::BeginTracksMax(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionTracksMax, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionTracksMax->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkPlaylist1Cpp::EndTracksMax(IAsync& aAsync, uint32_t& aaTracksMax)
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

void CpProxyLinnCoUkPlaylist1Cpp::SyncIdArray(uint32_t& aaIdArrayToken, std::string& aaIdArray)
{
    SyncIdArrayLinnCoUkPlaylist1Cpp sync(*this, aaIdArrayToken, aaIdArray);
    BeginIdArray(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPlaylist1Cpp::BeginIdArray(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionIdArray, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionIdArray->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentBinary(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkPlaylist1Cpp::EndIdArray(IAsync& aAsync, uint32_t& aaIdArrayToken, std::string& aaIdArray)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("IdArray"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aaIdArrayToken = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aaIdArray.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyLinnCoUkPlaylist1Cpp::SyncIdArrayChanged(uint32_t aaIdArrayToken, bool& aaIdArrayChanged)
{
    SyncIdArrayChangedLinnCoUkPlaylist1Cpp sync(*this, aaIdArrayChanged);
    BeginIdArrayChanged(aaIdArrayToken, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPlaylist1Cpp::BeginIdArrayChanged(uint32_t aaIdArrayToken, FunctorAsync& aFunctor)
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

void CpProxyLinnCoUkPlaylist1Cpp::EndIdArrayChanged(IAsync& aAsync, bool& aaIdArrayChanged)
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

void CpProxyLinnCoUkPlaylist1Cpp::SetPropertyIdArrayChanged(Functor& aFunctor)
{
    iLock->Wait();
    iIdArrayChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkPlaylist1Cpp::SetPropertyRepeatChanged(Functor& aFunctor)
{
    iLock->Wait();
    iRepeatChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkPlaylist1Cpp::SetPropertyShuffleChanged(Functor& aFunctor)
{
    iLock->Wait();
    iShuffleChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkPlaylist1Cpp::SetPropertyTracksMaxChanged(Functor& aFunctor)
{
    iLock->Wait();
    iTracksMaxChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkPlaylist1Cpp::PropertyIdArray(std::string& aIdArray) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iIdArray->Value();
    aIdArray.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyLinnCoUkPlaylist1Cpp::PropertyRepeat(bool& aRepeat) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aRepeat = iRepeat->Value();
}

void CpProxyLinnCoUkPlaylist1Cpp::PropertyShuffle(bool& aShuffle) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aShuffle = iShuffle->Value();
}

void CpProxyLinnCoUkPlaylist1Cpp::PropertyTracksMax(uint32_t& aTracksMax) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aTracksMax = iTracksMax->Value();
}

void CpProxyLinnCoUkPlaylist1Cpp::IdArrayPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iIdArrayChanged != NULL) {
        iIdArrayChanged();
    }
}

void CpProxyLinnCoUkPlaylist1Cpp::RepeatPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iRepeatChanged != NULL) {
        iRepeatChanged();
    }
}

void CpProxyLinnCoUkPlaylist1Cpp::ShufflePropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iShuffleChanged != NULL) {
        iShuffleChanged();
    }
}

void CpProxyLinnCoUkPlaylist1Cpp::TracksMaxPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iTracksMaxChanged != NULL) {
        iTracksMaxChanged();
    }
}

