#include "CpAvOpenhomeOrgPlaylistManager1.h"
#include <OpenHome/Net/Core/CpProxy.h>
#include <OpenHome/Net/Private/CpiService.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Net/Private/AsyncPrivate.h>
#include <OpenHome/Net/Core/CpDevice.h>

using namespace OpenHome;
using namespace OpenHome::Net;


class SyncMetadataAvOpenhomeOrgPlaylistManager1 : public SyncProxyAction
{
public:
    SyncMetadataAvOpenhomeOrgPlaylistManager1(CpProxyAvOpenhomeOrgPlaylistManager1& aProxy, Brh& aMetadata);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgPlaylistManager1& iService;
    Brh& iMetadata;
};

SyncMetadataAvOpenhomeOrgPlaylistManager1::SyncMetadataAvOpenhomeOrgPlaylistManager1(CpProxyAvOpenhomeOrgPlaylistManager1& aProxy, Brh& aMetadata)
    : iService(aProxy)
    , iMetadata(aMetadata)
{
}

void SyncMetadataAvOpenhomeOrgPlaylistManager1::CompleteRequest(IAsync& aAsync)
{
    iService.EndMetadata(aAsync, iMetadata);
}


class SyncImagesXmlAvOpenhomeOrgPlaylistManager1 : public SyncProxyAction
{
public:
    SyncImagesXmlAvOpenhomeOrgPlaylistManager1(CpProxyAvOpenhomeOrgPlaylistManager1& aProxy, Brh& aImagesXml);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgPlaylistManager1& iService;
    Brh& iImagesXml;
};

SyncImagesXmlAvOpenhomeOrgPlaylistManager1::SyncImagesXmlAvOpenhomeOrgPlaylistManager1(CpProxyAvOpenhomeOrgPlaylistManager1& aProxy, Brh& aImagesXml)
    : iService(aProxy)
    , iImagesXml(aImagesXml)
{
}

void SyncImagesXmlAvOpenhomeOrgPlaylistManager1::CompleteRequest(IAsync& aAsync)
{
    iService.EndImagesXml(aAsync, iImagesXml);
}


class SyncPlaylistReadArrayAvOpenhomeOrgPlaylistManager1 : public SyncProxyAction
{
public:
    SyncPlaylistReadArrayAvOpenhomeOrgPlaylistManager1(CpProxyAvOpenhomeOrgPlaylistManager1& aProxy, Brh& aArray);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgPlaylistManager1& iService;
    Brh& iArray;
};

SyncPlaylistReadArrayAvOpenhomeOrgPlaylistManager1::SyncPlaylistReadArrayAvOpenhomeOrgPlaylistManager1(CpProxyAvOpenhomeOrgPlaylistManager1& aProxy, Brh& aArray)
    : iService(aProxy)
    , iArray(aArray)
{
}

void SyncPlaylistReadArrayAvOpenhomeOrgPlaylistManager1::CompleteRequest(IAsync& aAsync)
{
    iService.EndPlaylistReadArray(aAsync, iArray);
}


class SyncPlaylistReadMetadataAvOpenhomeOrgPlaylistManager1 : public SyncProxyAction
{
public:
    SyncPlaylistReadMetadataAvOpenhomeOrgPlaylistManager1(CpProxyAvOpenhomeOrgPlaylistManager1& aProxy, Brh& aMetadata);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgPlaylistManager1& iService;
    Brh& iMetadata;
};

SyncPlaylistReadMetadataAvOpenhomeOrgPlaylistManager1::SyncPlaylistReadMetadataAvOpenhomeOrgPlaylistManager1(CpProxyAvOpenhomeOrgPlaylistManager1& aProxy, Brh& aMetadata)
    : iService(aProxy)
    , iMetadata(aMetadata)
{
}

void SyncPlaylistReadMetadataAvOpenhomeOrgPlaylistManager1::CompleteRequest(IAsync& aAsync)
{
    iService.EndPlaylistReadMetadata(aAsync, iMetadata);
}


class SyncPlaylistReadAvOpenhomeOrgPlaylistManager1 : public SyncProxyAction
{
public:
    SyncPlaylistReadAvOpenhomeOrgPlaylistManager1(CpProxyAvOpenhomeOrgPlaylistManager1& aProxy, Brh& aName, Brh& aDescription, TUint& aImageId);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgPlaylistManager1& iService;
    Brh& iName;
    Brh& iDescription;
    TUint& iImageId;
};

SyncPlaylistReadAvOpenhomeOrgPlaylistManager1::SyncPlaylistReadAvOpenhomeOrgPlaylistManager1(CpProxyAvOpenhomeOrgPlaylistManager1& aProxy, Brh& aName, Brh& aDescription, TUint& aImageId)
    : iService(aProxy)
    , iName(aName)
    , iDescription(aDescription)
    , iImageId(aImageId)
{
}

void SyncPlaylistReadAvOpenhomeOrgPlaylistManager1::CompleteRequest(IAsync& aAsync)
{
    iService.EndPlaylistRead(aAsync, iName, iDescription, iImageId);
}


class SyncPlaylistUpdateAvOpenhomeOrgPlaylistManager1 : public SyncProxyAction
{
public:
    SyncPlaylistUpdateAvOpenhomeOrgPlaylistManager1(CpProxyAvOpenhomeOrgPlaylistManager1& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgPlaylistManager1& iService;
};

SyncPlaylistUpdateAvOpenhomeOrgPlaylistManager1::SyncPlaylistUpdateAvOpenhomeOrgPlaylistManager1(CpProxyAvOpenhomeOrgPlaylistManager1& aProxy)
    : iService(aProxy)
{
}

void SyncPlaylistUpdateAvOpenhomeOrgPlaylistManager1::CompleteRequest(IAsync& aAsync)
{
    iService.EndPlaylistUpdate(aAsync);
}


class SyncPlaylistInsertAvOpenhomeOrgPlaylistManager1 : public SyncProxyAction
{
public:
    SyncPlaylistInsertAvOpenhomeOrgPlaylistManager1(CpProxyAvOpenhomeOrgPlaylistManager1& aProxy, TUint& aNewId);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgPlaylistManager1& iService;
    TUint& iNewId;
};

SyncPlaylistInsertAvOpenhomeOrgPlaylistManager1::SyncPlaylistInsertAvOpenhomeOrgPlaylistManager1(CpProxyAvOpenhomeOrgPlaylistManager1& aProxy, TUint& aNewId)
    : iService(aProxy)
    , iNewId(aNewId)
{
}

void SyncPlaylistInsertAvOpenhomeOrgPlaylistManager1::CompleteRequest(IAsync& aAsync)
{
    iService.EndPlaylistInsert(aAsync, iNewId);
}


class SyncPlaylistDeleteIdAvOpenhomeOrgPlaylistManager1 : public SyncProxyAction
{
public:
    SyncPlaylistDeleteIdAvOpenhomeOrgPlaylistManager1(CpProxyAvOpenhomeOrgPlaylistManager1& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgPlaylistManager1& iService;
};

SyncPlaylistDeleteIdAvOpenhomeOrgPlaylistManager1::SyncPlaylistDeleteIdAvOpenhomeOrgPlaylistManager1(CpProxyAvOpenhomeOrgPlaylistManager1& aProxy)
    : iService(aProxy)
{
}

void SyncPlaylistDeleteIdAvOpenhomeOrgPlaylistManager1::CompleteRequest(IAsync& aAsync)
{
    iService.EndPlaylistDeleteId(aAsync);
}


class SyncPlaylistsMaxAvOpenhomeOrgPlaylistManager1 : public SyncProxyAction
{
public:
    SyncPlaylistsMaxAvOpenhomeOrgPlaylistManager1(CpProxyAvOpenhomeOrgPlaylistManager1& aProxy, TUint& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgPlaylistManager1& iService;
    TUint& iValue;
};

SyncPlaylistsMaxAvOpenhomeOrgPlaylistManager1::SyncPlaylistsMaxAvOpenhomeOrgPlaylistManager1(CpProxyAvOpenhomeOrgPlaylistManager1& aProxy, TUint& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncPlaylistsMaxAvOpenhomeOrgPlaylistManager1::CompleteRequest(IAsync& aAsync)
{
    iService.EndPlaylistsMax(aAsync, iValue);
}


class SyncTracksMaxAvOpenhomeOrgPlaylistManager1 : public SyncProxyAction
{
public:
    SyncTracksMaxAvOpenhomeOrgPlaylistManager1(CpProxyAvOpenhomeOrgPlaylistManager1& aProxy, TUint& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgPlaylistManager1& iService;
    TUint& iValue;
};

SyncTracksMaxAvOpenhomeOrgPlaylistManager1::SyncTracksMaxAvOpenhomeOrgPlaylistManager1(CpProxyAvOpenhomeOrgPlaylistManager1& aProxy, TUint& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncTracksMaxAvOpenhomeOrgPlaylistManager1::CompleteRequest(IAsync& aAsync)
{
    iService.EndTracksMax(aAsync, iValue);
}


class SyncPlaylistArraysAvOpenhomeOrgPlaylistManager1 : public SyncProxyAction
{
public:
    SyncPlaylistArraysAvOpenhomeOrgPlaylistManager1(CpProxyAvOpenhomeOrgPlaylistManager1& aProxy, TUint& aToken, Brh& aIdArray, Brh& aTokenArray);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgPlaylistManager1& iService;
    TUint& iToken;
    Brh& iIdArray;
    Brh& iTokenArray;
};

SyncPlaylistArraysAvOpenhomeOrgPlaylistManager1::SyncPlaylistArraysAvOpenhomeOrgPlaylistManager1(CpProxyAvOpenhomeOrgPlaylistManager1& aProxy, TUint& aToken, Brh& aIdArray, Brh& aTokenArray)
    : iService(aProxy)
    , iToken(aToken)
    , iIdArray(aIdArray)
    , iTokenArray(aTokenArray)
{
}

void SyncPlaylistArraysAvOpenhomeOrgPlaylistManager1::CompleteRequest(IAsync& aAsync)
{
    iService.EndPlaylistArrays(aAsync, iToken, iIdArray, iTokenArray);
}


class SyncPlaylistArraysChangedAvOpenhomeOrgPlaylistManager1 : public SyncProxyAction
{
public:
    SyncPlaylistArraysChangedAvOpenhomeOrgPlaylistManager1(CpProxyAvOpenhomeOrgPlaylistManager1& aProxy, TBool& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgPlaylistManager1& iService;
    TBool& iValue;
};

SyncPlaylistArraysChangedAvOpenhomeOrgPlaylistManager1::SyncPlaylistArraysChangedAvOpenhomeOrgPlaylistManager1(CpProxyAvOpenhomeOrgPlaylistManager1& aProxy, TBool& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncPlaylistArraysChangedAvOpenhomeOrgPlaylistManager1::CompleteRequest(IAsync& aAsync)
{
    iService.EndPlaylistArraysChanged(aAsync, iValue);
}


class SyncReadAvOpenhomeOrgPlaylistManager1 : public SyncProxyAction
{
public:
    SyncReadAvOpenhomeOrgPlaylistManager1(CpProxyAvOpenhomeOrgPlaylistManager1& aProxy, Brh& aMetadata);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgPlaylistManager1& iService;
    Brh& iMetadata;
};

SyncReadAvOpenhomeOrgPlaylistManager1::SyncReadAvOpenhomeOrgPlaylistManager1(CpProxyAvOpenhomeOrgPlaylistManager1& aProxy, Brh& aMetadata)
    : iService(aProxy)
    , iMetadata(aMetadata)
{
}

void SyncReadAvOpenhomeOrgPlaylistManager1::CompleteRequest(IAsync& aAsync)
{
    iService.EndRead(aAsync, iMetadata);
}


class SyncReadListAvOpenhomeOrgPlaylistManager1 : public SyncProxyAction
{
public:
    SyncReadListAvOpenhomeOrgPlaylistManager1(CpProxyAvOpenhomeOrgPlaylistManager1& aProxy, Brh& aTrackList);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgPlaylistManager1& iService;
    Brh& iTrackList;
};

SyncReadListAvOpenhomeOrgPlaylistManager1::SyncReadListAvOpenhomeOrgPlaylistManager1(CpProxyAvOpenhomeOrgPlaylistManager1& aProxy, Brh& aTrackList)
    : iService(aProxy)
    , iTrackList(aTrackList)
{
}

void SyncReadListAvOpenhomeOrgPlaylistManager1::CompleteRequest(IAsync& aAsync)
{
    iService.EndReadList(aAsync, iTrackList);
}


class SyncInsertAvOpenhomeOrgPlaylistManager1 : public SyncProxyAction
{
public:
    SyncInsertAvOpenhomeOrgPlaylistManager1(CpProxyAvOpenhomeOrgPlaylistManager1& aProxy, TUint& aNewTrackId);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgPlaylistManager1& iService;
    TUint& iNewTrackId;
};

SyncInsertAvOpenhomeOrgPlaylistManager1::SyncInsertAvOpenhomeOrgPlaylistManager1(CpProxyAvOpenhomeOrgPlaylistManager1& aProxy, TUint& aNewTrackId)
    : iService(aProxy)
    , iNewTrackId(aNewTrackId)
{
}

void SyncInsertAvOpenhomeOrgPlaylistManager1::CompleteRequest(IAsync& aAsync)
{
    iService.EndInsert(aAsync, iNewTrackId);
}


class SyncDeleteIdAvOpenhomeOrgPlaylistManager1 : public SyncProxyAction
{
public:
    SyncDeleteIdAvOpenhomeOrgPlaylistManager1(CpProxyAvOpenhomeOrgPlaylistManager1& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgPlaylistManager1& iService;
};

SyncDeleteIdAvOpenhomeOrgPlaylistManager1::SyncDeleteIdAvOpenhomeOrgPlaylistManager1(CpProxyAvOpenhomeOrgPlaylistManager1& aProxy)
    : iService(aProxy)
{
}

void SyncDeleteIdAvOpenhomeOrgPlaylistManager1::CompleteRequest(IAsync& aAsync)
{
    iService.EndDeleteId(aAsync);
}


class SyncDeleteAllAvOpenhomeOrgPlaylistManager1 : public SyncProxyAction
{
public:
    SyncDeleteAllAvOpenhomeOrgPlaylistManager1(CpProxyAvOpenhomeOrgPlaylistManager1& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgPlaylistManager1& iService;
};

SyncDeleteAllAvOpenhomeOrgPlaylistManager1::SyncDeleteAllAvOpenhomeOrgPlaylistManager1(CpProxyAvOpenhomeOrgPlaylistManager1& aProxy)
    : iService(aProxy)
{
}

void SyncDeleteAllAvOpenhomeOrgPlaylistManager1::CompleteRequest(IAsync& aAsync)
{
    iService.EndDeleteAll(aAsync);
}


CpProxyAvOpenhomeOrgPlaylistManager1::CpProxyAvOpenhomeOrgPlaylistManager1(CpDevice& aDevice)
    : CpProxy("av-openhome-org", "PlaylistManager", 1, aDevice.Device())
{
    OpenHome::Net::Parameter* param;

    iActionMetadata = new Action("Metadata");
    param = new OpenHome::Net::ParameterString("Metadata");
    iActionMetadata->AddOutputParameter(param);

    iActionImagesXml = new Action("ImagesXml");
    param = new OpenHome::Net::ParameterString("ImagesXml");
    iActionImagesXml->AddOutputParameter(param);

    iActionPlaylistReadArray = new Action("PlaylistReadArray");
    param = new OpenHome::Net::ParameterUint("Id");
    iActionPlaylistReadArray->AddInputParameter(param);
    param = new OpenHome::Net::ParameterBinary("Array");
    iActionPlaylistReadArray->AddOutputParameter(param);

    iActionPlaylistReadMetadata = new Action("PlaylistReadMetadata");
    param = new OpenHome::Net::ParameterString("IdList");
    iActionPlaylistReadMetadata->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Metadata");
    iActionPlaylistReadMetadata->AddOutputParameter(param);

    iActionPlaylistRead = new Action("PlaylistRead");
    param = new OpenHome::Net::ParameterUint("Id");
    iActionPlaylistRead->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Name");
    iActionPlaylistRead->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("Description");
    iActionPlaylistRead->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("ImageId");
    iActionPlaylistRead->AddOutputParameter(param);

    iActionPlaylistUpdate = new Action("PlaylistUpdate");
    param = new OpenHome::Net::ParameterUint("Id");
    iActionPlaylistUpdate->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Name");
    iActionPlaylistUpdate->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Description");
    iActionPlaylistUpdate->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("ImageId");
    iActionPlaylistUpdate->AddInputParameter(param);

    iActionPlaylistInsert = new Action("PlaylistInsert");
    param = new OpenHome::Net::ParameterUint("AfterId");
    iActionPlaylistInsert->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Name");
    iActionPlaylistInsert->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Description");
    iActionPlaylistInsert->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("ImageId");
    iActionPlaylistInsert->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("NewId");
    iActionPlaylistInsert->AddOutputParameter(param);

    iActionPlaylistDeleteId = new Action("PlaylistDeleteId");
    param = new OpenHome::Net::ParameterUint("Value");
    iActionPlaylistDeleteId->AddInputParameter(param);

    iActionPlaylistsMax = new Action("PlaylistsMax");
    param = new OpenHome::Net::ParameterUint("Value");
    iActionPlaylistsMax->AddOutputParameter(param);

    iActionTracksMax = new Action("TracksMax");
    param = new OpenHome::Net::ParameterUint("Value");
    iActionTracksMax->AddOutputParameter(param);

    iActionPlaylistArrays = new Action("PlaylistArrays");
    param = new OpenHome::Net::ParameterUint("Token");
    iActionPlaylistArrays->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterBinary("IdArray");
    iActionPlaylistArrays->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterBinary("TokenArray");
    iActionPlaylistArrays->AddOutputParameter(param);

    iActionPlaylistArraysChanged = new Action("PlaylistArraysChanged");
    param = new OpenHome::Net::ParameterUint("Token");
    iActionPlaylistArraysChanged->AddInputParameter(param);
    param = new OpenHome::Net::ParameterBool("Value");
    iActionPlaylistArraysChanged->AddOutputParameter(param);

    iActionRead = new Action("Read");
    param = new OpenHome::Net::ParameterUint("Id");
    iActionRead->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("TrackId");
    iActionRead->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Metadata");
    iActionRead->AddOutputParameter(param);

    iActionReadList = new Action("ReadList");
    param = new OpenHome::Net::ParameterUint("Id");
    iActionReadList->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("TrackIdList");
    iActionReadList->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("TrackList");
    iActionReadList->AddOutputParameter(param);

    iActionInsert = new Action("Insert");
    param = new OpenHome::Net::ParameterUint("Id");
    iActionInsert->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("AfterTrackId");
    iActionInsert->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Udn");
    iActionInsert->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("MetadataId");
    iActionInsert->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("NewTrackId");
    iActionInsert->AddOutputParameter(param);

    iActionDeleteId = new Action("DeleteId");
    param = new OpenHome::Net::ParameterUint("TrackId");
    iActionDeleteId->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("Value");
    iActionDeleteId->AddInputParameter(param);

    iActionDeleteAll = new Action("DeleteAll");
    param = new OpenHome::Net::ParameterUint("TrackId");
    iActionDeleteAll->AddInputParameter(param);

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgPlaylistManager1::MetadataPropertyChanged);
    iMetadata = new PropertyString("Metadata", functor);
    AddProperty(iMetadata);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgPlaylistManager1::ImagesXmlPropertyChanged);
    iImagesXml = new PropertyString("ImagesXml", functor);
    AddProperty(iImagesXml);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgPlaylistManager1::IdArrayPropertyChanged);
    iIdArray = new PropertyBinary("IdArray", functor);
    AddProperty(iIdArray);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgPlaylistManager1::TokenArrayPropertyChanged);
    iTokenArray = new PropertyBinary("TokenArray", functor);
    AddProperty(iTokenArray);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgPlaylistManager1::PlaylistsMaxPropertyChanged);
    iPlaylistsMax = new PropertyUint("PlaylistsMax", functor);
    AddProperty(iPlaylistsMax);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgPlaylistManager1::TracksMaxPropertyChanged);
    iTracksMax = new PropertyUint("TracksMax", functor);
    AddProperty(iTracksMax);
}

CpProxyAvOpenhomeOrgPlaylistManager1::~CpProxyAvOpenhomeOrgPlaylistManager1()
{
    DestroyService();
    delete iActionMetadata;
    delete iActionImagesXml;
    delete iActionPlaylistReadArray;
    delete iActionPlaylistReadMetadata;
    delete iActionPlaylistRead;
    delete iActionPlaylistUpdate;
    delete iActionPlaylistInsert;
    delete iActionPlaylistDeleteId;
    delete iActionPlaylistsMax;
    delete iActionTracksMax;
    delete iActionPlaylistArrays;
    delete iActionPlaylistArraysChanged;
    delete iActionRead;
    delete iActionReadList;
    delete iActionInsert;
    delete iActionDeleteId;
    delete iActionDeleteAll;
}

void CpProxyAvOpenhomeOrgPlaylistManager1::SyncMetadata(Brh& aMetadata)
{
    SyncMetadataAvOpenhomeOrgPlaylistManager1 sync(*this, aMetadata);
    BeginMetadata(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylistManager1::BeginMetadata(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionMetadata, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionMetadata->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylistManager1::EndMetadata(IAsync& aAsync, Brh& aMetadata)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Metadata"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aMetadata);
}

void CpProxyAvOpenhomeOrgPlaylistManager1::SyncImagesXml(Brh& aImagesXml)
{
    SyncImagesXmlAvOpenhomeOrgPlaylistManager1 sync(*this, aImagesXml);
    BeginImagesXml(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylistManager1::BeginImagesXml(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionImagesXml, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionImagesXml->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylistManager1::EndImagesXml(IAsync& aAsync, Brh& aImagesXml)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("ImagesXml"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aImagesXml);
}

void CpProxyAvOpenhomeOrgPlaylistManager1::SyncPlaylistReadArray(TUint aId, Brh& aArray)
{
    SyncPlaylistReadArrayAvOpenhomeOrgPlaylistManager1 sync(*this, aArray);
    BeginPlaylistReadArray(aId, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylistManager1::BeginPlaylistReadArray(TUint aId, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionPlaylistReadArray, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionPlaylistReadArray->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aId));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionPlaylistReadArray->OutputParameters();
    invocation->AddOutput(new ArgumentBinary(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylistManager1::EndPlaylistReadArray(IAsync& aAsync, Brh& aArray)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("PlaylistReadArray"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentBinary*)invocation.OutputArguments()[index++])->TransferTo(aArray);
}

void CpProxyAvOpenhomeOrgPlaylistManager1::SyncPlaylistReadMetadata(const Brx& aIdList, Brh& aMetadata)
{
    SyncPlaylistReadMetadataAvOpenhomeOrgPlaylistManager1 sync(*this, aMetadata);
    BeginPlaylistReadMetadata(aIdList, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylistManager1::BeginPlaylistReadMetadata(const Brx& aIdList, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionPlaylistReadMetadata, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionPlaylistReadMetadata->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aIdList));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionPlaylistReadMetadata->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylistManager1::EndPlaylistReadMetadata(IAsync& aAsync, Brh& aMetadata)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("PlaylistReadMetadata"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aMetadata);
}

void CpProxyAvOpenhomeOrgPlaylistManager1::SyncPlaylistRead(TUint aId, Brh& aName, Brh& aDescription, TUint& aImageId)
{
    SyncPlaylistReadAvOpenhomeOrgPlaylistManager1 sync(*this, aName, aDescription, aImageId);
    BeginPlaylistRead(aId, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylistManager1::BeginPlaylistRead(TUint aId, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionPlaylistRead, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionPlaylistRead->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aId));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionPlaylistRead->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylistManager1::EndPlaylistRead(IAsync& aAsync, Brh& aName, Brh& aDescription, TUint& aImageId)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("PlaylistRead"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aName);
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aDescription);
    aImageId = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyAvOpenhomeOrgPlaylistManager1::SyncPlaylistUpdate(TUint aId, const Brx& aName, const Brx& aDescription, TUint aImageId)
{
    SyncPlaylistUpdateAvOpenhomeOrgPlaylistManager1 sync(*this);
    BeginPlaylistUpdate(aId, aName, aDescription, aImageId, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylistManager1::BeginPlaylistUpdate(TUint aId, const Brx& aName, const Brx& aDescription, TUint aImageId, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionPlaylistUpdate, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionPlaylistUpdate->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aId));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aName));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aDescription));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aImageId));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylistManager1::EndPlaylistUpdate(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("PlaylistUpdate"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyAvOpenhomeOrgPlaylistManager1::SyncPlaylistInsert(TUint aAfterId, const Brx& aName, const Brx& aDescription, TUint aImageId, TUint& aNewId)
{
    SyncPlaylistInsertAvOpenhomeOrgPlaylistManager1 sync(*this, aNewId);
    BeginPlaylistInsert(aAfterId, aName, aDescription, aImageId, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylistManager1::BeginPlaylistInsert(TUint aAfterId, const Brx& aName, const Brx& aDescription, TUint aImageId, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionPlaylistInsert, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionPlaylistInsert->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aAfterId));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aName));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aDescription));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aImageId));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionPlaylistInsert->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylistManager1::EndPlaylistInsert(IAsync& aAsync, TUint& aNewId)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("PlaylistInsert"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aNewId = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyAvOpenhomeOrgPlaylistManager1::SyncPlaylistDeleteId(TUint aValue)
{
    SyncPlaylistDeleteIdAvOpenhomeOrgPlaylistManager1 sync(*this);
    BeginPlaylistDeleteId(aValue, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylistManager1::BeginPlaylistDeleteId(TUint aValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionPlaylistDeleteId, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionPlaylistDeleteId->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aValue));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylistManager1::EndPlaylistDeleteId(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("PlaylistDeleteId"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyAvOpenhomeOrgPlaylistManager1::SyncPlaylistsMax(TUint& aValue)
{
    SyncPlaylistsMaxAvOpenhomeOrgPlaylistManager1 sync(*this, aValue);
    BeginPlaylistsMax(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylistManager1::BeginPlaylistsMax(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionPlaylistsMax, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionPlaylistsMax->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylistManager1::EndPlaylistsMax(IAsync& aAsync, TUint& aValue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("PlaylistsMax"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aValue = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyAvOpenhomeOrgPlaylistManager1::SyncTracksMax(TUint& aValue)
{
    SyncTracksMaxAvOpenhomeOrgPlaylistManager1 sync(*this, aValue);
    BeginTracksMax(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylistManager1::BeginTracksMax(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionTracksMax, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionTracksMax->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylistManager1::EndTracksMax(IAsync& aAsync, TUint& aValue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("TracksMax"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aValue = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyAvOpenhomeOrgPlaylistManager1::SyncPlaylistArrays(TUint& aToken, Brh& aIdArray, Brh& aTokenArray)
{
    SyncPlaylistArraysAvOpenhomeOrgPlaylistManager1 sync(*this, aToken, aIdArray, aTokenArray);
    BeginPlaylistArrays(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylistManager1::BeginPlaylistArrays(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionPlaylistArrays, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionPlaylistArrays->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentBinary(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentBinary(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylistManager1::EndPlaylistArrays(IAsync& aAsync, TUint& aToken, Brh& aIdArray, Brh& aTokenArray)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("PlaylistArrays"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aToken = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    ((ArgumentBinary*)invocation.OutputArguments()[index++])->TransferTo(aIdArray);
    ((ArgumentBinary*)invocation.OutputArguments()[index++])->TransferTo(aTokenArray);
}

void CpProxyAvOpenhomeOrgPlaylistManager1::SyncPlaylistArraysChanged(TUint aToken, TBool& aValue)
{
    SyncPlaylistArraysChangedAvOpenhomeOrgPlaylistManager1 sync(*this, aValue);
    BeginPlaylistArraysChanged(aToken, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylistManager1::BeginPlaylistArraysChanged(TUint aToken, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionPlaylistArraysChanged, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionPlaylistArraysChanged->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aToken));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionPlaylistArraysChanged->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylistManager1::EndPlaylistArraysChanged(IAsync& aAsync, TBool& aValue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("PlaylistArraysChanged"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aValue = ((ArgumentBool*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyAvOpenhomeOrgPlaylistManager1::SyncRead(TUint aId, TUint aTrackId, Brh& aMetadata)
{
    SyncReadAvOpenhomeOrgPlaylistManager1 sync(*this, aMetadata);
    BeginRead(aId, aTrackId, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylistManager1::BeginRead(TUint aId, TUint aTrackId, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionRead, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionRead->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aId));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aTrackId));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionRead->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylistManager1::EndRead(IAsync& aAsync, Brh& aMetadata)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Read"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aMetadata);
}

void CpProxyAvOpenhomeOrgPlaylistManager1::SyncReadList(TUint aId, const Brx& aTrackIdList, Brh& aTrackList)
{
    SyncReadListAvOpenhomeOrgPlaylistManager1 sync(*this, aTrackList);
    BeginReadList(aId, aTrackIdList, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylistManager1::BeginReadList(TUint aId, const Brx& aTrackIdList, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionReadList, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionReadList->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aId));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aTrackIdList));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionReadList->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylistManager1::EndReadList(IAsync& aAsync, Brh& aTrackList)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("ReadList"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aTrackList);
}

void CpProxyAvOpenhomeOrgPlaylistManager1::SyncInsert(TUint aId, TUint aAfterTrackId, const Brx& aUdn, const Brx& aMetadataId, TUint& aNewTrackId)
{
    SyncInsertAvOpenhomeOrgPlaylistManager1 sync(*this, aNewTrackId);
    BeginInsert(aId, aAfterTrackId, aUdn, aMetadataId, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylistManager1::BeginInsert(TUint aId, TUint aAfterTrackId, const Brx& aUdn, const Brx& aMetadataId, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionInsert, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionInsert->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aId));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aAfterTrackId));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aUdn));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aMetadataId));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionInsert->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylistManager1::EndInsert(IAsync& aAsync, TUint& aNewTrackId)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Insert"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aNewTrackId = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyAvOpenhomeOrgPlaylistManager1::SyncDeleteId(TUint aTrackId, TUint aValue)
{
    SyncDeleteIdAvOpenhomeOrgPlaylistManager1 sync(*this);
    BeginDeleteId(aTrackId, aValue, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylistManager1::BeginDeleteId(TUint aTrackId, TUint aValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionDeleteId, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionDeleteId->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aTrackId));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aValue));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylistManager1::EndDeleteId(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("DeleteId"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyAvOpenhomeOrgPlaylistManager1::SyncDeleteAll(TUint aTrackId)
{
    SyncDeleteAllAvOpenhomeOrgPlaylistManager1 sync(*this);
    BeginDeleteAll(aTrackId, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylistManager1::BeginDeleteAll(TUint aTrackId, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionDeleteAll, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionDeleteAll->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aTrackId));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylistManager1::EndDeleteAll(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("DeleteAll"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyAvOpenhomeOrgPlaylistManager1::SetPropertyMetadataChanged(Functor& aFunctor)
{
    iLock->Wait();
    iMetadataChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgPlaylistManager1::SetPropertyImagesXmlChanged(Functor& aFunctor)
{
    iLock->Wait();
    iImagesXmlChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgPlaylistManager1::SetPropertyIdArrayChanged(Functor& aFunctor)
{
    iLock->Wait();
    iIdArrayChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgPlaylistManager1::SetPropertyTokenArrayChanged(Functor& aFunctor)
{
    iLock->Wait();
    iTokenArrayChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgPlaylistManager1::SetPropertyPlaylistsMaxChanged(Functor& aFunctor)
{
    iLock->Wait();
    iPlaylistsMaxChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgPlaylistManager1::SetPropertyTracksMaxChanged(Functor& aFunctor)
{
    iLock->Wait();
    iTracksMaxChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgPlaylistManager1::PropertyMetadata(Brhz& aMetadata) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aMetadata.Set(iMetadata->Value());
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgPlaylistManager1::PropertyImagesXml(Brhz& aImagesXml) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aImagesXml.Set(iImagesXml->Value());
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgPlaylistManager1::PropertyIdArray(Brh& aIdArray) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aIdArray.Set(iIdArray->Value());
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgPlaylistManager1::PropertyTokenArray(Brh& aTokenArray) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aTokenArray.Set(iTokenArray->Value());
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgPlaylistManager1::PropertyPlaylistsMax(TUint& aPlaylistsMax) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aPlaylistsMax = iPlaylistsMax->Value();
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgPlaylistManager1::PropertyTracksMax(TUint& aTracksMax) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aTracksMax = iTracksMax->Value();
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgPlaylistManager1::MetadataPropertyChanged()
{
    ReportEvent(iMetadataChanged);
}

void CpProxyAvOpenhomeOrgPlaylistManager1::ImagesXmlPropertyChanged()
{
    ReportEvent(iImagesXmlChanged);
}

void CpProxyAvOpenhomeOrgPlaylistManager1::IdArrayPropertyChanged()
{
    ReportEvent(iIdArrayChanged);
}

void CpProxyAvOpenhomeOrgPlaylistManager1::TokenArrayPropertyChanged()
{
    ReportEvent(iTokenArrayChanged);
}

void CpProxyAvOpenhomeOrgPlaylistManager1::PlaylistsMaxPropertyChanged()
{
    ReportEvent(iPlaylistsMaxChanged);
}

void CpProxyAvOpenhomeOrgPlaylistManager1::TracksMaxPropertyChanged()
{
    ReportEvent(iTracksMaxChanged);
}

