#include "CpAvOpenhomeOrgPlaylistManager1.h"
#include <OpenHome/Net/Core/CpProxy.h>
#include <OpenHome/Net/Private/CpiService.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Net/Private/AsyncPrivate.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Cpp/CpDevice.h>

#include <string>

using namespace OpenHome;
using namespace OpenHome::Net;


class SyncMetadataAvOpenhomeOrgPlaylistManager1Cpp : public SyncProxyAction
{
public:
    SyncMetadataAvOpenhomeOrgPlaylistManager1Cpp(CpProxyAvOpenhomeOrgPlaylistManager1Cpp& aProxy, std::string& aMetadata);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgPlaylistManager1Cpp& iService;
    std::string& iMetadata;
};

SyncMetadataAvOpenhomeOrgPlaylistManager1Cpp::SyncMetadataAvOpenhomeOrgPlaylistManager1Cpp(CpProxyAvOpenhomeOrgPlaylistManager1Cpp& aProxy, std::string& aMetadata)
    : iService(aProxy)
    , iMetadata(aMetadata)
{
}

void SyncMetadataAvOpenhomeOrgPlaylistManager1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndMetadata(aAsync, iMetadata);
}


class SyncImagesXmlAvOpenhomeOrgPlaylistManager1Cpp : public SyncProxyAction
{
public:
    SyncImagesXmlAvOpenhomeOrgPlaylistManager1Cpp(CpProxyAvOpenhomeOrgPlaylistManager1Cpp& aProxy, std::string& aImagesXml);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgPlaylistManager1Cpp& iService;
    std::string& iImagesXml;
};

SyncImagesXmlAvOpenhomeOrgPlaylistManager1Cpp::SyncImagesXmlAvOpenhomeOrgPlaylistManager1Cpp(CpProxyAvOpenhomeOrgPlaylistManager1Cpp& aProxy, std::string& aImagesXml)
    : iService(aProxy)
    , iImagesXml(aImagesXml)
{
}

void SyncImagesXmlAvOpenhomeOrgPlaylistManager1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndImagesXml(aAsync, iImagesXml);
}


class SyncPlaylistReadArrayAvOpenhomeOrgPlaylistManager1Cpp : public SyncProxyAction
{
public:
    SyncPlaylistReadArrayAvOpenhomeOrgPlaylistManager1Cpp(CpProxyAvOpenhomeOrgPlaylistManager1Cpp& aProxy, std::string& aArray);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgPlaylistManager1Cpp& iService;
    std::string& iArray;
};

SyncPlaylistReadArrayAvOpenhomeOrgPlaylistManager1Cpp::SyncPlaylistReadArrayAvOpenhomeOrgPlaylistManager1Cpp(CpProxyAvOpenhomeOrgPlaylistManager1Cpp& aProxy, std::string& aArray)
    : iService(aProxy)
    , iArray(aArray)
{
}

void SyncPlaylistReadArrayAvOpenhomeOrgPlaylistManager1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndPlaylistReadArray(aAsync, iArray);
}


class SyncPlaylistReadMetadataAvOpenhomeOrgPlaylistManager1Cpp : public SyncProxyAction
{
public:
    SyncPlaylistReadMetadataAvOpenhomeOrgPlaylistManager1Cpp(CpProxyAvOpenhomeOrgPlaylistManager1Cpp& aProxy, std::string& aMetadata);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgPlaylistManager1Cpp& iService;
    std::string& iMetadata;
};

SyncPlaylistReadMetadataAvOpenhomeOrgPlaylistManager1Cpp::SyncPlaylistReadMetadataAvOpenhomeOrgPlaylistManager1Cpp(CpProxyAvOpenhomeOrgPlaylistManager1Cpp& aProxy, std::string& aMetadata)
    : iService(aProxy)
    , iMetadata(aMetadata)
{
}

void SyncPlaylistReadMetadataAvOpenhomeOrgPlaylistManager1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndPlaylistReadMetadata(aAsync, iMetadata);
}


class SyncPlaylistReadAvOpenhomeOrgPlaylistManager1Cpp : public SyncProxyAction
{
public:
    SyncPlaylistReadAvOpenhomeOrgPlaylistManager1Cpp(CpProxyAvOpenhomeOrgPlaylistManager1Cpp& aProxy, std::string& aName, std::string& aDescription, uint32_t& aImageId);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgPlaylistManager1Cpp& iService;
    std::string& iName;
    std::string& iDescription;
    uint32_t& iImageId;
};

SyncPlaylistReadAvOpenhomeOrgPlaylistManager1Cpp::SyncPlaylistReadAvOpenhomeOrgPlaylistManager1Cpp(CpProxyAvOpenhomeOrgPlaylistManager1Cpp& aProxy, std::string& aName, std::string& aDescription, uint32_t& aImageId)
    : iService(aProxy)
    , iName(aName)
    , iDescription(aDescription)
    , iImageId(aImageId)
{
}

void SyncPlaylistReadAvOpenhomeOrgPlaylistManager1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndPlaylistRead(aAsync, iName, iDescription, iImageId);
}


class SyncPlaylistUpdateAvOpenhomeOrgPlaylistManager1Cpp : public SyncProxyAction
{
public:
    SyncPlaylistUpdateAvOpenhomeOrgPlaylistManager1Cpp(CpProxyAvOpenhomeOrgPlaylistManager1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgPlaylistManager1Cpp& iService;
};

SyncPlaylistUpdateAvOpenhomeOrgPlaylistManager1Cpp::SyncPlaylistUpdateAvOpenhomeOrgPlaylistManager1Cpp(CpProxyAvOpenhomeOrgPlaylistManager1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncPlaylistUpdateAvOpenhomeOrgPlaylistManager1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndPlaylistUpdate(aAsync);
}


class SyncPlaylistInsertAvOpenhomeOrgPlaylistManager1Cpp : public SyncProxyAction
{
public:
    SyncPlaylistInsertAvOpenhomeOrgPlaylistManager1Cpp(CpProxyAvOpenhomeOrgPlaylistManager1Cpp& aProxy, uint32_t& aNewId);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgPlaylistManager1Cpp& iService;
    uint32_t& iNewId;
};

SyncPlaylistInsertAvOpenhomeOrgPlaylistManager1Cpp::SyncPlaylistInsertAvOpenhomeOrgPlaylistManager1Cpp(CpProxyAvOpenhomeOrgPlaylistManager1Cpp& aProxy, uint32_t& aNewId)
    : iService(aProxy)
    , iNewId(aNewId)
{
}

void SyncPlaylistInsertAvOpenhomeOrgPlaylistManager1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndPlaylistInsert(aAsync, iNewId);
}


class SyncPlaylistDeleteIdAvOpenhomeOrgPlaylistManager1Cpp : public SyncProxyAction
{
public:
    SyncPlaylistDeleteIdAvOpenhomeOrgPlaylistManager1Cpp(CpProxyAvOpenhomeOrgPlaylistManager1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgPlaylistManager1Cpp& iService;
};

SyncPlaylistDeleteIdAvOpenhomeOrgPlaylistManager1Cpp::SyncPlaylistDeleteIdAvOpenhomeOrgPlaylistManager1Cpp(CpProxyAvOpenhomeOrgPlaylistManager1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncPlaylistDeleteIdAvOpenhomeOrgPlaylistManager1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndPlaylistDeleteId(aAsync);
}


class SyncPlaylistsMaxAvOpenhomeOrgPlaylistManager1Cpp : public SyncProxyAction
{
public:
    SyncPlaylistsMaxAvOpenhomeOrgPlaylistManager1Cpp(CpProxyAvOpenhomeOrgPlaylistManager1Cpp& aProxy, uint32_t& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgPlaylistManager1Cpp& iService;
    uint32_t& iValue;
};

SyncPlaylistsMaxAvOpenhomeOrgPlaylistManager1Cpp::SyncPlaylistsMaxAvOpenhomeOrgPlaylistManager1Cpp(CpProxyAvOpenhomeOrgPlaylistManager1Cpp& aProxy, uint32_t& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncPlaylistsMaxAvOpenhomeOrgPlaylistManager1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndPlaylistsMax(aAsync, iValue);
}


class SyncTracksMaxAvOpenhomeOrgPlaylistManager1Cpp : public SyncProxyAction
{
public:
    SyncTracksMaxAvOpenhomeOrgPlaylistManager1Cpp(CpProxyAvOpenhomeOrgPlaylistManager1Cpp& aProxy, uint32_t& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgPlaylistManager1Cpp& iService;
    uint32_t& iValue;
};

SyncTracksMaxAvOpenhomeOrgPlaylistManager1Cpp::SyncTracksMaxAvOpenhomeOrgPlaylistManager1Cpp(CpProxyAvOpenhomeOrgPlaylistManager1Cpp& aProxy, uint32_t& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncTracksMaxAvOpenhomeOrgPlaylistManager1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndTracksMax(aAsync, iValue);
}


class SyncPlaylistArraysAvOpenhomeOrgPlaylistManager1Cpp : public SyncProxyAction
{
public:
    SyncPlaylistArraysAvOpenhomeOrgPlaylistManager1Cpp(CpProxyAvOpenhomeOrgPlaylistManager1Cpp& aProxy, uint32_t& aToken, std::string& aIdArray, std::string& aTokenArray);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgPlaylistManager1Cpp& iService;
    uint32_t& iToken;
    std::string& iIdArray;
    std::string& iTokenArray;
};

SyncPlaylistArraysAvOpenhomeOrgPlaylistManager1Cpp::SyncPlaylistArraysAvOpenhomeOrgPlaylistManager1Cpp(CpProxyAvOpenhomeOrgPlaylistManager1Cpp& aProxy, uint32_t& aToken, std::string& aIdArray, std::string& aTokenArray)
    : iService(aProxy)
    , iToken(aToken)
    , iIdArray(aIdArray)
    , iTokenArray(aTokenArray)
{
}

void SyncPlaylistArraysAvOpenhomeOrgPlaylistManager1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndPlaylistArrays(aAsync, iToken, iIdArray, iTokenArray);
}


class SyncPlaylistArraysChangedAvOpenhomeOrgPlaylistManager1Cpp : public SyncProxyAction
{
public:
    SyncPlaylistArraysChangedAvOpenhomeOrgPlaylistManager1Cpp(CpProxyAvOpenhomeOrgPlaylistManager1Cpp& aProxy, bool& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgPlaylistManager1Cpp& iService;
    bool& iValue;
};

SyncPlaylistArraysChangedAvOpenhomeOrgPlaylistManager1Cpp::SyncPlaylistArraysChangedAvOpenhomeOrgPlaylistManager1Cpp(CpProxyAvOpenhomeOrgPlaylistManager1Cpp& aProxy, bool& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncPlaylistArraysChangedAvOpenhomeOrgPlaylistManager1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndPlaylistArraysChanged(aAsync, iValue);
}


class SyncReadAvOpenhomeOrgPlaylistManager1Cpp : public SyncProxyAction
{
public:
    SyncReadAvOpenhomeOrgPlaylistManager1Cpp(CpProxyAvOpenhomeOrgPlaylistManager1Cpp& aProxy, std::string& aMetadata);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgPlaylistManager1Cpp& iService;
    std::string& iMetadata;
};

SyncReadAvOpenhomeOrgPlaylistManager1Cpp::SyncReadAvOpenhomeOrgPlaylistManager1Cpp(CpProxyAvOpenhomeOrgPlaylistManager1Cpp& aProxy, std::string& aMetadata)
    : iService(aProxy)
    , iMetadata(aMetadata)
{
}

void SyncReadAvOpenhomeOrgPlaylistManager1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndRead(aAsync, iMetadata);
}


class SyncReadListAvOpenhomeOrgPlaylistManager1Cpp : public SyncProxyAction
{
public:
    SyncReadListAvOpenhomeOrgPlaylistManager1Cpp(CpProxyAvOpenhomeOrgPlaylistManager1Cpp& aProxy, std::string& aTrackList);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgPlaylistManager1Cpp& iService;
    std::string& iTrackList;
};

SyncReadListAvOpenhomeOrgPlaylistManager1Cpp::SyncReadListAvOpenhomeOrgPlaylistManager1Cpp(CpProxyAvOpenhomeOrgPlaylistManager1Cpp& aProxy, std::string& aTrackList)
    : iService(aProxy)
    , iTrackList(aTrackList)
{
}

void SyncReadListAvOpenhomeOrgPlaylistManager1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndReadList(aAsync, iTrackList);
}


class SyncInsertAvOpenhomeOrgPlaylistManager1Cpp : public SyncProxyAction
{
public:
    SyncInsertAvOpenhomeOrgPlaylistManager1Cpp(CpProxyAvOpenhomeOrgPlaylistManager1Cpp& aProxy, uint32_t& aNewTrackId);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgPlaylistManager1Cpp& iService;
    uint32_t& iNewTrackId;
};

SyncInsertAvOpenhomeOrgPlaylistManager1Cpp::SyncInsertAvOpenhomeOrgPlaylistManager1Cpp(CpProxyAvOpenhomeOrgPlaylistManager1Cpp& aProxy, uint32_t& aNewTrackId)
    : iService(aProxy)
    , iNewTrackId(aNewTrackId)
{
}

void SyncInsertAvOpenhomeOrgPlaylistManager1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndInsert(aAsync, iNewTrackId);
}


class SyncDeleteIdAvOpenhomeOrgPlaylistManager1Cpp : public SyncProxyAction
{
public:
    SyncDeleteIdAvOpenhomeOrgPlaylistManager1Cpp(CpProxyAvOpenhomeOrgPlaylistManager1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgPlaylistManager1Cpp& iService;
};

SyncDeleteIdAvOpenhomeOrgPlaylistManager1Cpp::SyncDeleteIdAvOpenhomeOrgPlaylistManager1Cpp(CpProxyAvOpenhomeOrgPlaylistManager1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncDeleteIdAvOpenhomeOrgPlaylistManager1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndDeleteId(aAsync);
}


class SyncDeleteAllAvOpenhomeOrgPlaylistManager1Cpp : public SyncProxyAction
{
public:
    SyncDeleteAllAvOpenhomeOrgPlaylistManager1Cpp(CpProxyAvOpenhomeOrgPlaylistManager1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgPlaylistManager1Cpp& iService;
};

SyncDeleteAllAvOpenhomeOrgPlaylistManager1Cpp::SyncDeleteAllAvOpenhomeOrgPlaylistManager1Cpp(CpProxyAvOpenhomeOrgPlaylistManager1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncDeleteAllAvOpenhomeOrgPlaylistManager1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndDeleteAll(aAsync);
}


CpProxyAvOpenhomeOrgPlaylistManager1Cpp::CpProxyAvOpenhomeOrgPlaylistManager1Cpp(CpDeviceCpp& aDevice)
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
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgPlaylistManager1Cpp::MetadataPropertyChanged);
    iMetadata = new PropertyString("Metadata", functor);
    AddProperty(iMetadata);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgPlaylistManager1Cpp::ImagesXmlPropertyChanged);
    iImagesXml = new PropertyString("ImagesXml", functor);
    AddProperty(iImagesXml);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgPlaylistManager1Cpp::IdArrayPropertyChanged);
    iIdArray = new PropertyBinary("IdArray", functor);
    AddProperty(iIdArray);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgPlaylistManager1Cpp::TokenArrayPropertyChanged);
    iTokenArray = new PropertyBinary("TokenArray", functor);
    AddProperty(iTokenArray);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgPlaylistManager1Cpp::PlaylistsMaxPropertyChanged);
    iPlaylistsMax = new PropertyUint("PlaylistsMax", functor);
    AddProperty(iPlaylistsMax);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgPlaylistManager1Cpp::TracksMaxPropertyChanged);
    iTracksMax = new PropertyUint("TracksMax", functor);
    AddProperty(iTracksMax);
}

CpProxyAvOpenhomeOrgPlaylistManager1Cpp::~CpProxyAvOpenhomeOrgPlaylistManager1Cpp()
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

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::SyncMetadata(std::string& aMetadata)
{
    SyncMetadataAvOpenhomeOrgPlaylistManager1Cpp sync(*this, aMetadata);
    BeginMetadata(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::BeginMetadata(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionMetadata, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionMetadata->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::EndMetadata(IAsync& aAsync, std::string& aMetadata)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Metadata"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aMetadata.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::SyncImagesXml(std::string& aImagesXml)
{
    SyncImagesXmlAvOpenhomeOrgPlaylistManager1Cpp sync(*this, aImagesXml);
    BeginImagesXml(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::BeginImagesXml(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionImagesXml, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionImagesXml->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::EndImagesXml(IAsync& aAsync, std::string& aImagesXml)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("ImagesXml"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aImagesXml.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::SyncPlaylistReadArray(uint32_t aId, std::string& aArray)
{
    SyncPlaylistReadArrayAvOpenhomeOrgPlaylistManager1Cpp sync(*this, aArray);
    BeginPlaylistReadArray(aId, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::BeginPlaylistReadArray(uint32_t aId, FunctorAsync& aFunctor)
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

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::EndPlaylistReadArray(IAsync& aAsync, std::string& aArray)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("PlaylistReadArray"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aArray.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::SyncPlaylistReadMetadata(const std::string& aIdList, std::string& aMetadata)
{
    SyncPlaylistReadMetadataAvOpenhomeOrgPlaylistManager1Cpp sync(*this, aMetadata);
    BeginPlaylistReadMetadata(aIdList, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::BeginPlaylistReadMetadata(const std::string& aIdList, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionPlaylistReadMetadata, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionPlaylistReadMetadata->InputParameters();
    {
        Brn buf((const TByte*)aIdList.c_str(), (TUint)aIdList.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionPlaylistReadMetadata->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::EndPlaylistReadMetadata(IAsync& aAsync, std::string& aMetadata)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("PlaylistReadMetadata"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aMetadata.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::SyncPlaylistRead(uint32_t aId, std::string& aName, std::string& aDescription, uint32_t& aImageId)
{
    SyncPlaylistReadAvOpenhomeOrgPlaylistManager1Cpp sync(*this, aName, aDescription, aImageId);
    BeginPlaylistRead(aId, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::BeginPlaylistRead(uint32_t aId, FunctorAsync& aFunctor)
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

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::EndPlaylistRead(IAsync& aAsync, std::string& aName, std::string& aDescription, uint32_t& aImageId)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("PlaylistRead"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aName.assign((const char*)val.Ptr(), val.Bytes());
    }
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aDescription.assign((const char*)val.Ptr(), val.Bytes());
    }
    aImageId = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::SyncPlaylistUpdate(uint32_t aId, const std::string& aName, const std::string& aDescription, uint32_t aImageId)
{
    SyncPlaylistUpdateAvOpenhomeOrgPlaylistManager1Cpp sync(*this);
    BeginPlaylistUpdate(aId, aName, aDescription, aImageId, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::BeginPlaylistUpdate(uint32_t aId, const std::string& aName, const std::string& aDescription, uint32_t aImageId, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionPlaylistUpdate, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionPlaylistUpdate->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aId));
    {
        Brn buf((const TByte*)aName.c_str(), (TUint)aName.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aDescription.c_str(), (TUint)aDescription.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aImageId));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::EndPlaylistUpdate(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("PlaylistUpdate"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::SyncPlaylistInsert(uint32_t aAfterId, const std::string& aName, const std::string& aDescription, uint32_t aImageId, uint32_t& aNewId)
{
    SyncPlaylistInsertAvOpenhomeOrgPlaylistManager1Cpp sync(*this, aNewId);
    BeginPlaylistInsert(aAfterId, aName, aDescription, aImageId, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::BeginPlaylistInsert(uint32_t aAfterId, const std::string& aName, const std::string& aDescription, uint32_t aImageId, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionPlaylistInsert, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionPlaylistInsert->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aAfterId));
    {
        Brn buf((const TByte*)aName.c_str(), (TUint)aName.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aDescription.c_str(), (TUint)aDescription.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aImageId));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionPlaylistInsert->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::EndPlaylistInsert(IAsync& aAsync, uint32_t& aNewId)
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

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::SyncPlaylistDeleteId(uint32_t aValue)
{
    SyncPlaylistDeleteIdAvOpenhomeOrgPlaylistManager1Cpp sync(*this);
    BeginPlaylistDeleteId(aValue, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::BeginPlaylistDeleteId(uint32_t aValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionPlaylistDeleteId, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionPlaylistDeleteId->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aValue));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::EndPlaylistDeleteId(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("PlaylistDeleteId"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::SyncPlaylistsMax(uint32_t& aValue)
{
    SyncPlaylistsMaxAvOpenhomeOrgPlaylistManager1Cpp sync(*this, aValue);
    BeginPlaylistsMax(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::BeginPlaylistsMax(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionPlaylistsMax, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionPlaylistsMax->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::EndPlaylistsMax(IAsync& aAsync, uint32_t& aValue)
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

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::SyncTracksMax(uint32_t& aValue)
{
    SyncTracksMaxAvOpenhomeOrgPlaylistManager1Cpp sync(*this, aValue);
    BeginTracksMax(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::BeginTracksMax(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionTracksMax, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionTracksMax->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::EndTracksMax(IAsync& aAsync, uint32_t& aValue)
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

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::SyncPlaylistArrays(uint32_t& aToken, std::string& aIdArray, std::string& aTokenArray)
{
    SyncPlaylistArraysAvOpenhomeOrgPlaylistManager1Cpp sync(*this, aToken, aIdArray, aTokenArray);
    BeginPlaylistArrays(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::BeginPlaylistArrays(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionPlaylistArrays, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionPlaylistArrays->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentBinary(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentBinary(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::EndPlaylistArrays(IAsync& aAsync, uint32_t& aToken, std::string& aIdArray, std::string& aTokenArray)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("PlaylistArrays"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aToken = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aIdArray.assign((const char*)val.Ptr(), val.Bytes());
    }
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aTokenArray.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::SyncPlaylistArraysChanged(uint32_t aToken, bool& aValue)
{
    SyncPlaylistArraysChangedAvOpenhomeOrgPlaylistManager1Cpp sync(*this, aValue);
    BeginPlaylistArraysChanged(aToken, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::BeginPlaylistArraysChanged(uint32_t aToken, FunctorAsync& aFunctor)
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

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::EndPlaylistArraysChanged(IAsync& aAsync, bool& aValue)
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

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::SyncRead(uint32_t aId, uint32_t aTrackId, std::string& aMetadata)
{
    SyncReadAvOpenhomeOrgPlaylistManager1Cpp sync(*this, aMetadata);
    BeginRead(aId, aTrackId, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::BeginRead(uint32_t aId, uint32_t aTrackId, FunctorAsync& aFunctor)
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

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::EndRead(IAsync& aAsync, std::string& aMetadata)
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
        aMetadata.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::SyncReadList(uint32_t aId, const std::string& aTrackIdList, std::string& aTrackList)
{
    SyncReadListAvOpenhomeOrgPlaylistManager1Cpp sync(*this, aTrackList);
    BeginReadList(aId, aTrackIdList, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::BeginReadList(uint32_t aId, const std::string& aTrackIdList, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionReadList, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionReadList->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aId));
    {
        Brn buf((const TByte*)aTrackIdList.c_str(), (TUint)aTrackIdList.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionReadList->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::EndReadList(IAsync& aAsync, std::string& aTrackList)
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
        aTrackList.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::SyncInsert(uint32_t aId, uint32_t aAfterTrackId, const std::string& aUdn, const std::string& aMetadataId, uint32_t& aNewTrackId)
{
    SyncInsertAvOpenhomeOrgPlaylistManager1Cpp sync(*this, aNewTrackId);
    BeginInsert(aId, aAfterTrackId, aUdn, aMetadataId, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::BeginInsert(uint32_t aId, uint32_t aAfterTrackId, const std::string& aUdn, const std::string& aMetadataId, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionInsert, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionInsert->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aId));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aAfterTrackId));
    {
        Brn buf((const TByte*)aUdn.c_str(), (TUint)aUdn.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aMetadataId.c_str(), (TUint)aMetadataId.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionInsert->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::EndInsert(IAsync& aAsync, uint32_t& aNewTrackId)
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

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::SyncDeleteId(uint32_t aTrackId, uint32_t aValue)
{
    SyncDeleteIdAvOpenhomeOrgPlaylistManager1Cpp sync(*this);
    BeginDeleteId(aTrackId, aValue, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::BeginDeleteId(uint32_t aTrackId, uint32_t aValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionDeleteId, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionDeleteId->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aTrackId));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aValue));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::EndDeleteId(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("DeleteId"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::SyncDeleteAll(uint32_t aTrackId)
{
    SyncDeleteAllAvOpenhomeOrgPlaylistManager1Cpp sync(*this);
    BeginDeleteAll(aTrackId, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::BeginDeleteAll(uint32_t aTrackId, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionDeleteAll, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionDeleteAll->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aTrackId));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::EndDeleteAll(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("DeleteAll"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::SetPropertyMetadataChanged(Functor& aFunctor)
{
    iLock->Wait();
    iMetadataChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::SetPropertyImagesXmlChanged(Functor& aFunctor)
{
    iLock->Wait();
    iImagesXmlChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::SetPropertyIdArrayChanged(Functor& aFunctor)
{
    iLock->Wait();
    iIdArrayChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::SetPropertyTokenArrayChanged(Functor& aFunctor)
{
    iLock->Wait();
    iTokenArrayChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::SetPropertyPlaylistsMaxChanged(Functor& aFunctor)
{
    iLock->Wait();
    iPlaylistsMaxChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::SetPropertyTracksMaxChanged(Functor& aFunctor)
{
    iLock->Wait();
    iTracksMaxChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::PropertyMetadata(std::string& aMetadata) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iMetadata->Value();
    aMetadata.assign((const char*)val.Ptr(), val.Bytes());
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::PropertyImagesXml(std::string& aImagesXml) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iImagesXml->Value();
    aImagesXml.assign((const char*)val.Ptr(), val.Bytes());
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::PropertyIdArray(std::string& aIdArray) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iIdArray->Value();
    aIdArray.assign((const char*)val.Ptr(), val.Bytes());
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::PropertyTokenArray(std::string& aTokenArray) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iTokenArray->Value();
    aTokenArray.assign((const char*)val.Ptr(), val.Bytes());
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::PropertyPlaylistsMax(uint32_t& aPlaylistsMax) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aPlaylistsMax = iPlaylistsMax->Value();
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::PropertyTracksMax(uint32_t& aTracksMax) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aTracksMax = iTracksMax->Value();
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::MetadataPropertyChanged()
{
    ReportEvent(iMetadataChanged);
}

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::ImagesXmlPropertyChanged()
{
    ReportEvent(iImagesXmlChanged);
}

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::IdArrayPropertyChanged()
{
    ReportEvent(iIdArrayChanged);
}

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::TokenArrayPropertyChanged()
{
    ReportEvent(iTokenArrayChanged);
}

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::PlaylistsMaxPropertyChanged()
{
    ReportEvent(iPlaylistsMaxChanged);
}

void CpProxyAvOpenhomeOrgPlaylistManager1Cpp::TracksMaxPropertyChanged()
{
    ReportEvent(iTracksMaxChanged);
}

