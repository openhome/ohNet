#include <Std/CpUpnpOrgContentDirectory1.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Buffer.h>
#include <Std/CpDevice.h>

#include <string>

using namespace Zapp;


class SyncGetSearchCapabilitiesUpnpOrgContentDirectory1Cpp : public SyncProxyAction
{
public:
    SyncGetSearchCapabilitiesUpnpOrgContentDirectory1Cpp(CpProxyUpnpOrgContentDirectory1Cpp& aService, std::string& aSearchCaps);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgContentDirectory1Cpp& iService;
    std::string& iSearchCaps;
};

SyncGetSearchCapabilitiesUpnpOrgContentDirectory1Cpp::SyncGetSearchCapabilitiesUpnpOrgContentDirectory1Cpp(CpProxyUpnpOrgContentDirectory1Cpp& aService, std::string& aSearchCaps)
    : iService(aService)
    , iSearchCaps(aSearchCaps)
{
}

void SyncGetSearchCapabilitiesUpnpOrgContentDirectory1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetSearchCapabilities(aAsync, iSearchCaps);
}


class SyncGetSortCapabilitiesUpnpOrgContentDirectory1Cpp : public SyncProxyAction
{
public:
    SyncGetSortCapabilitiesUpnpOrgContentDirectory1Cpp(CpProxyUpnpOrgContentDirectory1Cpp& aService, std::string& aSortCaps);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgContentDirectory1Cpp& iService;
    std::string& iSortCaps;
};

SyncGetSortCapabilitiesUpnpOrgContentDirectory1Cpp::SyncGetSortCapabilitiesUpnpOrgContentDirectory1Cpp(CpProxyUpnpOrgContentDirectory1Cpp& aService, std::string& aSortCaps)
    : iService(aService)
    , iSortCaps(aSortCaps)
{
}

void SyncGetSortCapabilitiesUpnpOrgContentDirectory1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetSortCapabilities(aAsync, iSortCaps);
}


class SyncGetSystemUpdateIDUpnpOrgContentDirectory1Cpp : public SyncProxyAction
{
public:
    SyncGetSystemUpdateIDUpnpOrgContentDirectory1Cpp(CpProxyUpnpOrgContentDirectory1Cpp& aService, uint32_t& aId);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgContentDirectory1Cpp& iService;
    uint32_t& iId;
};

SyncGetSystemUpdateIDUpnpOrgContentDirectory1Cpp::SyncGetSystemUpdateIDUpnpOrgContentDirectory1Cpp(CpProxyUpnpOrgContentDirectory1Cpp& aService, uint32_t& aId)
    : iService(aService)
    , iId(aId)
{
}

void SyncGetSystemUpdateIDUpnpOrgContentDirectory1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetSystemUpdateID(aAsync, iId);
}


class SyncBrowseUpnpOrgContentDirectory1Cpp : public SyncProxyAction
{
public:
    SyncBrowseUpnpOrgContentDirectory1Cpp(CpProxyUpnpOrgContentDirectory1Cpp& aService, std::string& aResult, uint32_t& aNumberReturned, uint32_t& aTotalMatches, uint32_t& aUpdateID);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgContentDirectory1Cpp& iService;
    std::string& iResult;
    uint32_t& iNumberReturned;
    uint32_t& iTotalMatches;
    uint32_t& iUpdateID;
};

SyncBrowseUpnpOrgContentDirectory1Cpp::SyncBrowseUpnpOrgContentDirectory1Cpp(CpProxyUpnpOrgContentDirectory1Cpp& aService, std::string& aResult, uint32_t& aNumberReturned, uint32_t& aTotalMatches, uint32_t& aUpdateID)
    : iService(aService)
    , iResult(aResult)
    , iNumberReturned(aNumberReturned)
    , iTotalMatches(aTotalMatches)
    , iUpdateID(aUpdateID)
{
}

void SyncBrowseUpnpOrgContentDirectory1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndBrowse(aAsync, iResult, iNumberReturned, iTotalMatches, iUpdateID);
}


class SyncSearchUpnpOrgContentDirectory1Cpp : public SyncProxyAction
{
public:
    SyncSearchUpnpOrgContentDirectory1Cpp(CpProxyUpnpOrgContentDirectory1Cpp& aService, std::string& aResult, uint32_t& aNumberReturned, uint32_t& aTotalMatches, uint32_t& aUpdateID);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgContentDirectory1Cpp& iService;
    std::string& iResult;
    uint32_t& iNumberReturned;
    uint32_t& iTotalMatches;
    uint32_t& iUpdateID;
};

SyncSearchUpnpOrgContentDirectory1Cpp::SyncSearchUpnpOrgContentDirectory1Cpp(CpProxyUpnpOrgContentDirectory1Cpp& aService, std::string& aResult, uint32_t& aNumberReturned, uint32_t& aTotalMatches, uint32_t& aUpdateID)
    : iService(aService)
    , iResult(aResult)
    , iNumberReturned(aNumberReturned)
    , iTotalMatches(aTotalMatches)
    , iUpdateID(aUpdateID)
{
}

void SyncSearchUpnpOrgContentDirectory1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSearch(aAsync, iResult, iNumberReturned, iTotalMatches, iUpdateID);
}


class SyncCreateObjectUpnpOrgContentDirectory1Cpp : public SyncProxyAction
{
public:
    SyncCreateObjectUpnpOrgContentDirectory1Cpp(CpProxyUpnpOrgContentDirectory1Cpp& aService, std::string& aObjectID, std::string& aResult);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgContentDirectory1Cpp& iService;
    std::string& iObjectID;
    std::string& iResult;
};

SyncCreateObjectUpnpOrgContentDirectory1Cpp::SyncCreateObjectUpnpOrgContentDirectory1Cpp(CpProxyUpnpOrgContentDirectory1Cpp& aService, std::string& aObjectID, std::string& aResult)
    : iService(aService)
    , iObjectID(aObjectID)
    , iResult(aResult)
{
}

void SyncCreateObjectUpnpOrgContentDirectory1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndCreateObject(aAsync, iObjectID, iResult);
}


class SyncDestroyObjectUpnpOrgContentDirectory1Cpp : public SyncProxyAction
{
public:
    SyncDestroyObjectUpnpOrgContentDirectory1Cpp(CpProxyUpnpOrgContentDirectory1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgContentDirectory1Cpp& iService;
};

SyncDestroyObjectUpnpOrgContentDirectory1Cpp::SyncDestroyObjectUpnpOrgContentDirectory1Cpp(CpProxyUpnpOrgContentDirectory1Cpp& aService)
    : iService(aService)
{
}

void SyncDestroyObjectUpnpOrgContentDirectory1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndDestroyObject(aAsync);
}


class SyncUpdateObjectUpnpOrgContentDirectory1Cpp : public SyncProxyAction
{
public:
    SyncUpdateObjectUpnpOrgContentDirectory1Cpp(CpProxyUpnpOrgContentDirectory1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgContentDirectory1Cpp& iService;
};

SyncUpdateObjectUpnpOrgContentDirectory1Cpp::SyncUpdateObjectUpnpOrgContentDirectory1Cpp(CpProxyUpnpOrgContentDirectory1Cpp& aService)
    : iService(aService)
{
}

void SyncUpdateObjectUpnpOrgContentDirectory1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndUpdateObject(aAsync);
}


class SyncImportResourceUpnpOrgContentDirectory1Cpp : public SyncProxyAction
{
public:
    SyncImportResourceUpnpOrgContentDirectory1Cpp(CpProxyUpnpOrgContentDirectory1Cpp& aService, uint32_t& aTransferID);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgContentDirectory1Cpp& iService;
    uint32_t& iTransferID;
};

SyncImportResourceUpnpOrgContentDirectory1Cpp::SyncImportResourceUpnpOrgContentDirectory1Cpp(CpProxyUpnpOrgContentDirectory1Cpp& aService, uint32_t& aTransferID)
    : iService(aService)
    , iTransferID(aTransferID)
{
}

void SyncImportResourceUpnpOrgContentDirectory1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndImportResource(aAsync, iTransferID);
}


class SyncExportResourceUpnpOrgContentDirectory1Cpp : public SyncProxyAction
{
public:
    SyncExportResourceUpnpOrgContentDirectory1Cpp(CpProxyUpnpOrgContentDirectory1Cpp& aService, uint32_t& aTransferID);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgContentDirectory1Cpp& iService;
    uint32_t& iTransferID;
};

SyncExportResourceUpnpOrgContentDirectory1Cpp::SyncExportResourceUpnpOrgContentDirectory1Cpp(CpProxyUpnpOrgContentDirectory1Cpp& aService, uint32_t& aTransferID)
    : iService(aService)
    , iTransferID(aTransferID)
{
}

void SyncExportResourceUpnpOrgContentDirectory1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndExportResource(aAsync, iTransferID);
}


class SyncStopTransferResourceUpnpOrgContentDirectory1Cpp : public SyncProxyAction
{
public:
    SyncStopTransferResourceUpnpOrgContentDirectory1Cpp(CpProxyUpnpOrgContentDirectory1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgContentDirectory1Cpp& iService;
};

SyncStopTransferResourceUpnpOrgContentDirectory1Cpp::SyncStopTransferResourceUpnpOrgContentDirectory1Cpp(CpProxyUpnpOrgContentDirectory1Cpp& aService)
    : iService(aService)
{
}

void SyncStopTransferResourceUpnpOrgContentDirectory1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndStopTransferResource(aAsync);
}


class SyncGetTransferProgressUpnpOrgContentDirectory1Cpp : public SyncProxyAction
{
public:
    SyncGetTransferProgressUpnpOrgContentDirectory1Cpp(CpProxyUpnpOrgContentDirectory1Cpp& aService, std::string& aTransferStatus, std::string& aTransferLength, std::string& aTransferTotal);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgContentDirectory1Cpp& iService;
    std::string& iTransferStatus;
    std::string& iTransferLength;
    std::string& iTransferTotal;
};

SyncGetTransferProgressUpnpOrgContentDirectory1Cpp::SyncGetTransferProgressUpnpOrgContentDirectory1Cpp(CpProxyUpnpOrgContentDirectory1Cpp& aService, std::string& aTransferStatus, std::string& aTransferLength, std::string& aTransferTotal)
    : iService(aService)
    , iTransferStatus(aTransferStatus)
    , iTransferLength(aTransferLength)
    , iTransferTotal(aTransferTotal)
{
}

void SyncGetTransferProgressUpnpOrgContentDirectory1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetTransferProgress(aAsync, iTransferStatus, iTransferLength, iTransferTotal);
}


class SyncDeleteResourceUpnpOrgContentDirectory1Cpp : public SyncProxyAction
{
public:
    SyncDeleteResourceUpnpOrgContentDirectory1Cpp(CpProxyUpnpOrgContentDirectory1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgContentDirectory1Cpp& iService;
};

SyncDeleteResourceUpnpOrgContentDirectory1Cpp::SyncDeleteResourceUpnpOrgContentDirectory1Cpp(CpProxyUpnpOrgContentDirectory1Cpp& aService)
    : iService(aService)
{
}

void SyncDeleteResourceUpnpOrgContentDirectory1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndDeleteResource(aAsync);
}


class SyncCreateReferenceUpnpOrgContentDirectory1Cpp : public SyncProxyAction
{
public:
    SyncCreateReferenceUpnpOrgContentDirectory1Cpp(CpProxyUpnpOrgContentDirectory1Cpp& aService, std::string& aNewID);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgContentDirectory1Cpp& iService;
    std::string& iNewID;
};

SyncCreateReferenceUpnpOrgContentDirectory1Cpp::SyncCreateReferenceUpnpOrgContentDirectory1Cpp(CpProxyUpnpOrgContentDirectory1Cpp& aService, std::string& aNewID)
    : iService(aService)
    , iNewID(aNewID)
{
}

void SyncCreateReferenceUpnpOrgContentDirectory1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndCreateReference(aAsync, iNewID);
}


CpProxyUpnpOrgContentDirectory1Cpp::CpProxyUpnpOrgContentDirectory1Cpp(CpDeviceCpp& aDevice)
{
    iService = new CpiService("schemas-upnp-org", "ContentDirectory", 1, aDevice.Device());
    Zapp::Parameter* param;
    TChar** allowedValues;
    TUint index;

    iActionGetSearchCapabilities = new Action("GetSearchCapabilities");
    param = new Zapp::ParameterString("SearchCaps");
    iActionGetSearchCapabilities->AddOutputParameter(param);

    iActionGetSortCapabilities = new Action("GetSortCapabilities");
    param = new Zapp::ParameterString("SortCaps");
    iActionGetSortCapabilities->AddOutputParameter(param);

    iActionGetSystemUpdateID = new Action("GetSystemUpdateID");
    param = new Zapp::ParameterUint("Id");
    iActionGetSystemUpdateID->AddOutputParameter(param);

    iActionBrowse = new Action("Browse");
    param = new Zapp::ParameterString("ObjectID");
    iActionBrowse->AddInputParameter(param);
    index = 0;
    allowedValues = new TChar*[2];
    allowedValues[index++] = (TChar*)"BrowseMetadata";
    allowedValues[index++] = (TChar*)"BrowseDirectChildren";
    param = new Zapp::ParameterString("BrowseFlag", allowedValues, 2);
    iActionBrowse->AddInputParameter(param);
    delete[] allowedValues;
    param = new Zapp::ParameterString("Filter");
    iActionBrowse->AddInputParameter(param);
    param = new Zapp::ParameterUint("StartingIndex");
    iActionBrowse->AddInputParameter(param);
    param = new Zapp::ParameterUint("RequestedCount");
    iActionBrowse->AddInputParameter(param);
    param = new Zapp::ParameterString("SortCriteria");
    iActionBrowse->AddInputParameter(param);
    param = new Zapp::ParameterString("Result");
    iActionBrowse->AddOutputParameter(param);
    param = new Zapp::ParameterUint("NumberReturned");
    iActionBrowse->AddOutputParameter(param);
    param = new Zapp::ParameterUint("TotalMatches");
    iActionBrowse->AddOutputParameter(param);
    param = new Zapp::ParameterUint("UpdateID");
    iActionBrowse->AddOutputParameter(param);

    iActionSearch = new Action("Search");
    param = new Zapp::ParameterString("ContainerID");
    iActionSearch->AddInputParameter(param);
    param = new Zapp::ParameterString("SearchCriteria");
    iActionSearch->AddInputParameter(param);
    param = new Zapp::ParameterString("Filter");
    iActionSearch->AddInputParameter(param);
    param = new Zapp::ParameterUint("StartingIndex");
    iActionSearch->AddInputParameter(param);
    param = new Zapp::ParameterUint("RequestedCount");
    iActionSearch->AddInputParameter(param);
    param = new Zapp::ParameterString("SortCriteria");
    iActionSearch->AddInputParameter(param);
    param = new Zapp::ParameterString("Result");
    iActionSearch->AddOutputParameter(param);
    param = new Zapp::ParameterUint("NumberReturned");
    iActionSearch->AddOutputParameter(param);
    param = new Zapp::ParameterUint("TotalMatches");
    iActionSearch->AddOutputParameter(param);
    param = new Zapp::ParameterUint("UpdateID");
    iActionSearch->AddOutputParameter(param);

    iActionCreateObject = new Action("CreateObject");
    param = new Zapp::ParameterString("ContainerID");
    iActionCreateObject->AddInputParameter(param);
    param = new Zapp::ParameterString("Elements");
    iActionCreateObject->AddInputParameter(param);
    param = new Zapp::ParameterString("ObjectID");
    iActionCreateObject->AddOutputParameter(param);
    param = new Zapp::ParameterString("Result");
    iActionCreateObject->AddOutputParameter(param);

    iActionDestroyObject = new Action("DestroyObject");
    param = new Zapp::ParameterString("ObjectID");
    iActionDestroyObject->AddInputParameter(param);

    iActionUpdateObject = new Action("UpdateObject");
    param = new Zapp::ParameterString("ObjectID");
    iActionUpdateObject->AddInputParameter(param);
    param = new Zapp::ParameterString("CurrentTagValue");
    iActionUpdateObject->AddInputParameter(param);
    param = new Zapp::ParameterString("NewTagValue");
    iActionUpdateObject->AddInputParameter(param);

    iActionImportResource = new Action("ImportResource");
    param = new Zapp::ParameterString("SourceURI");
    iActionImportResource->AddInputParameter(param);
    param = new Zapp::ParameterString("DestinationURI");
    iActionImportResource->AddInputParameter(param);
    param = new Zapp::ParameterUint("TransferID");
    iActionImportResource->AddOutputParameter(param);

    iActionExportResource = new Action("ExportResource");
    param = new Zapp::ParameterString("SourceURI");
    iActionExportResource->AddInputParameter(param);
    param = new Zapp::ParameterString("DestinationURI");
    iActionExportResource->AddInputParameter(param);
    param = new Zapp::ParameterUint("TransferID");
    iActionExportResource->AddOutputParameter(param);

    iActionStopTransferResource = new Action("StopTransferResource");
    param = new Zapp::ParameterUint("TransferID");
    iActionStopTransferResource->AddInputParameter(param);

    iActionGetTransferProgress = new Action("GetTransferProgress");
    param = new Zapp::ParameterUint("TransferID");
    iActionGetTransferProgress->AddInputParameter(param);
    index = 0;
    allowedValues = new TChar*[4];
    allowedValues[index++] = (TChar*)"COMPLETED";
    allowedValues[index++] = (TChar*)"ERROR";
    allowedValues[index++] = (TChar*)"IN_PROGRESS";
    allowedValues[index++] = (TChar*)"STOPPED";
    param = new Zapp::ParameterString("TransferStatus", allowedValues, 4);
    iActionGetTransferProgress->AddOutputParameter(param);
    delete[] allowedValues;
    param = new Zapp::ParameterString("TransferLength");
    iActionGetTransferProgress->AddOutputParameter(param);
    param = new Zapp::ParameterString("TransferTotal");
    iActionGetTransferProgress->AddOutputParameter(param);

    iActionDeleteResource = new Action("DeleteResource");
    param = new Zapp::ParameterString("ResourceURI");
    iActionDeleteResource->AddInputParameter(param);

    iActionCreateReference = new Action("CreateReference");
    param = new Zapp::ParameterString("ContainerID");
    iActionCreateReference->AddInputParameter(param);
    param = new Zapp::ParameterString("ObjectID");
    iActionCreateReference->AddInputParameter(param);
    param = new Zapp::ParameterString("NewID");
    iActionCreateReference->AddOutputParameter(param);

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyUpnpOrgContentDirectory1Cpp::TransferIDsPropertyChanged);
    iTransferIDs = new PropertyString("TransferIDs", functor);
    iService->AddProperty(iTransferIDs);
    functor = MakeFunctor(*this, &CpProxyUpnpOrgContentDirectory1Cpp::SystemUpdateIDPropertyChanged);
    iSystemUpdateID = new PropertyUint("SystemUpdateID", functor);
    iService->AddProperty(iSystemUpdateID);
    functor = MakeFunctor(*this, &CpProxyUpnpOrgContentDirectory1Cpp::ContainerUpdateIDsPropertyChanged);
    iContainerUpdateIDs = new PropertyString("ContainerUpdateIDs", functor);
    iService->AddProperty(iContainerUpdateIDs);
}

CpProxyUpnpOrgContentDirectory1Cpp::~CpProxyUpnpOrgContentDirectory1Cpp()
{
    delete iService;
    delete iActionGetSearchCapabilities;
    delete iActionGetSortCapabilities;
    delete iActionGetSystemUpdateID;
    delete iActionBrowse;
    delete iActionSearch;
    delete iActionCreateObject;
    delete iActionDestroyObject;
    delete iActionUpdateObject;
    delete iActionImportResource;
    delete iActionExportResource;
    delete iActionStopTransferResource;
    delete iActionGetTransferProgress;
    delete iActionDeleteResource;
    delete iActionCreateReference;
}

void CpProxyUpnpOrgContentDirectory1Cpp::SyncGetSearchCapabilities(std::string& aSearchCaps)
{
    SyncGetSearchCapabilitiesUpnpOrgContentDirectory1Cpp sync(*this, aSearchCaps);
    BeginGetSearchCapabilities(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory1Cpp::BeginGetSearchCapabilities(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetSearchCapabilities, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetSearchCapabilities->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyUpnpOrgContentDirectory1Cpp::EndGetSearchCapabilities(IAsync& aAsync, std::string& aSearchCaps)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetSearchCapabilities"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aSearchCaps.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyUpnpOrgContentDirectory1Cpp::SyncGetSortCapabilities(std::string& aSortCaps)
{
    SyncGetSortCapabilitiesUpnpOrgContentDirectory1Cpp sync(*this, aSortCaps);
    BeginGetSortCapabilities(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory1Cpp::BeginGetSortCapabilities(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetSortCapabilities, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetSortCapabilities->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyUpnpOrgContentDirectory1Cpp::EndGetSortCapabilities(IAsync& aAsync, std::string& aSortCaps)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetSortCapabilities"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aSortCaps.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyUpnpOrgContentDirectory1Cpp::SyncGetSystemUpdateID(uint32_t& aId)
{
    SyncGetSystemUpdateIDUpnpOrgContentDirectory1Cpp sync(*this, aId);
    BeginGetSystemUpdateID(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory1Cpp::BeginGetSystemUpdateID(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetSystemUpdateID, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetSystemUpdateID->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyUpnpOrgContentDirectory1Cpp::EndGetSystemUpdateID(IAsync& aAsync, uint32_t& aId)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetSystemUpdateID"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aId = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgContentDirectory1Cpp::SyncBrowse(const std::string& aObjectID, const std::string& aBrowseFlag, const std::string& aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const std::string& aSortCriteria, std::string& aResult, uint32_t& aNumberReturned, uint32_t& aTotalMatches, uint32_t& aUpdateID)
{
    SyncBrowseUpnpOrgContentDirectory1Cpp sync(*this, aResult, aNumberReturned, aTotalMatches, aUpdateID);
    BeginBrowse(aObjectID, aBrowseFlag, aFilter, aStartingIndex, aRequestedCount, aSortCriteria, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory1Cpp::BeginBrowse(const std::string& aObjectID, const std::string& aBrowseFlag, const std::string& aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const std::string& aSortCriteria, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionBrowse, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionBrowse->InputParameters();
    {
        Brn buf((const TByte*)aObjectID.c_str(), aObjectID.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aBrowseFlag.c_str(), aBrowseFlag.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aFilter.c_str(), aFilter.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aStartingIndex));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aRequestedCount));
    {
        Brn buf((const TByte*)aSortCriteria.c_str(), aSortCriteria.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionBrowse->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyUpnpOrgContentDirectory1Cpp::EndBrowse(IAsync& aAsync, std::string& aResult, uint32_t& aNumberReturned, uint32_t& aTotalMatches, uint32_t& aUpdateID)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Browse"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aResult.assign((const char*)val.Ptr(), val.Bytes());
    }
    aNumberReturned = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aTotalMatches = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aUpdateID = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgContentDirectory1Cpp::SyncSearch(const std::string& aContainerID, const std::string& aSearchCriteria, const std::string& aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const std::string& aSortCriteria, std::string& aResult, uint32_t& aNumberReturned, uint32_t& aTotalMatches, uint32_t& aUpdateID)
{
    SyncSearchUpnpOrgContentDirectory1Cpp sync(*this, aResult, aNumberReturned, aTotalMatches, aUpdateID);
    BeginSearch(aContainerID, aSearchCriteria, aFilter, aStartingIndex, aRequestedCount, aSortCriteria, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory1Cpp::BeginSearch(const std::string& aContainerID, const std::string& aSearchCriteria, const std::string& aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const std::string& aSortCriteria, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSearch, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSearch->InputParameters();
    {
        Brn buf((const TByte*)aContainerID.c_str(), aContainerID.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aSearchCriteria.c_str(), aSearchCriteria.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aFilter.c_str(), aFilter.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aStartingIndex));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aRequestedCount));
    {
        Brn buf((const TByte*)aSortCriteria.c_str(), aSortCriteria.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionSearch->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyUpnpOrgContentDirectory1Cpp::EndSearch(IAsync& aAsync, std::string& aResult, uint32_t& aNumberReturned, uint32_t& aTotalMatches, uint32_t& aUpdateID)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Search"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aResult.assign((const char*)val.Ptr(), val.Bytes());
    }
    aNumberReturned = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aTotalMatches = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aUpdateID = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgContentDirectory1Cpp::SyncCreateObject(const std::string& aContainerID, const std::string& aElements, std::string& aObjectID, std::string& aResult)
{
    SyncCreateObjectUpnpOrgContentDirectory1Cpp sync(*this, aObjectID, aResult);
    BeginCreateObject(aContainerID, aElements, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory1Cpp::BeginCreateObject(const std::string& aContainerID, const std::string& aElements, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionCreateObject, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionCreateObject->InputParameters();
    {
        Brn buf((const TByte*)aContainerID.c_str(), aContainerID.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aElements.c_str(), aElements.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionCreateObject->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyUpnpOrgContentDirectory1Cpp::EndCreateObject(IAsync& aAsync, std::string& aObjectID, std::string& aResult)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("CreateObject"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aObjectID.assign((const char*)val.Ptr(), val.Bytes());
    }
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aResult.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyUpnpOrgContentDirectory1Cpp::SyncDestroyObject(const std::string& aObjectID)
{
    SyncDestroyObjectUpnpOrgContentDirectory1Cpp sync(*this);
    BeginDestroyObject(aObjectID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory1Cpp::BeginDestroyObject(const std::string& aObjectID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionDestroyObject, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionDestroyObject->InputParameters();
    {
        Brn buf((const TByte*)aObjectID.c_str(), aObjectID.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    invocation->Invoke();
}

void CpProxyUpnpOrgContentDirectory1Cpp::EndDestroyObject(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("DestroyObject"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgContentDirectory1Cpp::SyncUpdateObject(const std::string& aObjectID, const std::string& aCurrentTagValue, const std::string& aNewTagValue)
{
    SyncUpdateObjectUpnpOrgContentDirectory1Cpp sync(*this);
    BeginUpdateObject(aObjectID, aCurrentTagValue, aNewTagValue, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory1Cpp::BeginUpdateObject(const std::string& aObjectID, const std::string& aCurrentTagValue, const std::string& aNewTagValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionUpdateObject, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionUpdateObject->InputParameters();
    {
        Brn buf((const TByte*)aObjectID.c_str(), aObjectID.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aCurrentTagValue.c_str(), aCurrentTagValue.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aNewTagValue.c_str(), aNewTagValue.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    invocation->Invoke();
}

void CpProxyUpnpOrgContentDirectory1Cpp::EndUpdateObject(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("UpdateObject"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgContentDirectory1Cpp::SyncImportResource(const std::string& aSourceURI, const std::string& aDestinationURI, uint32_t& aTransferID)
{
    SyncImportResourceUpnpOrgContentDirectory1Cpp sync(*this, aTransferID);
    BeginImportResource(aSourceURI, aDestinationURI, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory1Cpp::BeginImportResource(const std::string& aSourceURI, const std::string& aDestinationURI, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionImportResource, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionImportResource->InputParameters();
    {
        Brn buf((const TByte*)aSourceURI.c_str(), aSourceURI.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aDestinationURI.c_str(), aDestinationURI.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionImportResource->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyUpnpOrgContentDirectory1Cpp::EndImportResource(IAsync& aAsync, uint32_t& aTransferID)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("ImportResource"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aTransferID = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgContentDirectory1Cpp::SyncExportResource(const std::string& aSourceURI, const std::string& aDestinationURI, uint32_t& aTransferID)
{
    SyncExportResourceUpnpOrgContentDirectory1Cpp sync(*this, aTransferID);
    BeginExportResource(aSourceURI, aDestinationURI, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory1Cpp::BeginExportResource(const std::string& aSourceURI, const std::string& aDestinationURI, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionExportResource, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionExportResource->InputParameters();
    {
        Brn buf((const TByte*)aSourceURI.c_str(), aSourceURI.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aDestinationURI.c_str(), aDestinationURI.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionExportResource->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyUpnpOrgContentDirectory1Cpp::EndExportResource(IAsync& aAsync, uint32_t& aTransferID)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("ExportResource"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aTransferID = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgContentDirectory1Cpp::SyncStopTransferResource(uint32_t aTransferID)
{
    SyncStopTransferResourceUpnpOrgContentDirectory1Cpp sync(*this);
    BeginStopTransferResource(aTransferID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory1Cpp::BeginStopTransferResource(uint32_t aTransferID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionStopTransferResource, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionStopTransferResource->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aTransferID));
    invocation->Invoke();
}

void CpProxyUpnpOrgContentDirectory1Cpp::EndStopTransferResource(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("StopTransferResource"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgContentDirectory1Cpp::SyncGetTransferProgress(uint32_t aTransferID, std::string& aTransferStatus, std::string& aTransferLength, std::string& aTransferTotal)
{
    SyncGetTransferProgressUpnpOrgContentDirectory1Cpp sync(*this, aTransferStatus, aTransferLength, aTransferTotal);
    BeginGetTransferProgress(aTransferID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory1Cpp::BeginGetTransferProgress(uint32_t aTransferID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetTransferProgress, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetTransferProgress->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aTransferID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetTransferProgress->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyUpnpOrgContentDirectory1Cpp::EndGetTransferProgress(IAsync& aAsync, std::string& aTransferStatus, std::string& aTransferLength, std::string& aTransferTotal)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetTransferProgress"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aTransferStatus.assign((const char*)val.Ptr(), val.Bytes());
    }
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aTransferLength.assign((const char*)val.Ptr(), val.Bytes());
    }
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aTransferTotal.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyUpnpOrgContentDirectory1Cpp::SyncDeleteResource(const std::string& aResourceURI)
{
    SyncDeleteResourceUpnpOrgContentDirectory1Cpp sync(*this);
    BeginDeleteResource(aResourceURI, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory1Cpp::BeginDeleteResource(const std::string& aResourceURI, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionDeleteResource, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionDeleteResource->InputParameters();
    {
        Brn buf((const TByte*)aResourceURI.c_str(), aResourceURI.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    invocation->Invoke();
}

void CpProxyUpnpOrgContentDirectory1Cpp::EndDeleteResource(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("DeleteResource"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgContentDirectory1Cpp::SyncCreateReference(const std::string& aContainerID, const std::string& aObjectID, std::string& aNewID)
{
    SyncCreateReferenceUpnpOrgContentDirectory1Cpp sync(*this, aNewID);
    BeginCreateReference(aContainerID, aObjectID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory1Cpp::BeginCreateReference(const std::string& aContainerID, const std::string& aObjectID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionCreateReference, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionCreateReference->InputParameters();
    {
        Brn buf((const TByte*)aContainerID.c_str(), aContainerID.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aObjectID.c_str(), aObjectID.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionCreateReference->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyUpnpOrgContentDirectory1Cpp::EndCreateReference(IAsync& aAsync, std::string& aNewID)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("CreateReference"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aNewID.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyUpnpOrgContentDirectory1Cpp::SetPropertyTransferIDsChanged(Functor& aFunctor)
{
    iLock->Wait();
    iTransferIDsChanged = aFunctor;
    iLock->Signal();
}

void CpProxyUpnpOrgContentDirectory1Cpp::SetPropertySystemUpdateIDChanged(Functor& aFunctor)
{
    iLock->Wait();
    iSystemUpdateIDChanged = aFunctor;
    iLock->Signal();
}

void CpProxyUpnpOrgContentDirectory1Cpp::SetPropertyContainerUpdateIDsChanged(Functor& aFunctor)
{
    iLock->Wait();
    iContainerUpdateIDsChanged = aFunctor;
    iLock->Signal();
}

void CpProxyUpnpOrgContentDirectory1Cpp::PropertyTransferIDs(std::string& aTransferIDs) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iTransferIDs->Value();
    aTransferIDs.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyUpnpOrgContentDirectory1Cpp::PropertySystemUpdateID(uint32_t& aSystemUpdateID) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aSystemUpdateID = iSystemUpdateID->Value();
}

void CpProxyUpnpOrgContentDirectory1Cpp::PropertyContainerUpdateIDs(std::string& aContainerUpdateIDs) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iContainerUpdateIDs->Value();
    aContainerUpdateIDs.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyUpnpOrgContentDirectory1Cpp::TransferIDsPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iTransferIDsChanged != NULL) {
        iTransferIDsChanged();
    }
}

void CpProxyUpnpOrgContentDirectory1Cpp::SystemUpdateIDPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iSystemUpdateIDChanged != NULL) {
        iSystemUpdateIDChanged();
    }
}

void CpProxyUpnpOrgContentDirectory1Cpp::ContainerUpdateIDsPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iContainerUpdateIDsChanged != NULL) {
        iContainerUpdateIDsChanged();
    }
}

