#include "CpUpnpOrgContentDirectory1.h"
#include <OpenHome/Net/Core/CpProxy.h>
#include <OpenHome/Net/Private/CpiService.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Net/Private/AsyncPrivate.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Cpp/CpDevice.h>
#include <OpenHome/Net/Private/CpiDevice.h>

#include <string>

using namespace OpenHome;
using namespace OpenHome::Net;


class SyncGetSearchCapabilitiesUpnpOrgContentDirectory1Cpp : public SyncProxyAction
{
public:
    SyncGetSearchCapabilitiesUpnpOrgContentDirectory1Cpp(CpProxyUpnpOrgContentDirectory1Cpp& aProxy, std::string& aSearchCaps);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetSearchCapabilitiesUpnpOrgContentDirectory1Cpp() {}
private:
    CpProxyUpnpOrgContentDirectory1Cpp& iService;
    std::string& iSearchCaps;
};

SyncGetSearchCapabilitiesUpnpOrgContentDirectory1Cpp::SyncGetSearchCapabilitiesUpnpOrgContentDirectory1Cpp(CpProxyUpnpOrgContentDirectory1Cpp& aProxy, std::string& aSearchCaps)
    : iService(aProxy)
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
    SyncGetSortCapabilitiesUpnpOrgContentDirectory1Cpp(CpProxyUpnpOrgContentDirectory1Cpp& aProxy, std::string& aSortCaps);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetSortCapabilitiesUpnpOrgContentDirectory1Cpp() {}
private:
    CpProxyUpnpOrgContentDirectory1Cpp& iService;
    std::string& iSortCaps;
};

SyncGetSortCapabilitiesUpnpOrgContentDirectory1Cpp::SyncGetSortCapabilitiesUpnpOrgContentDirectory1Cpp(CpProxyUpnpOrgContentDirectory1Cpp& aProxy, std::string& aSortCaps)
    : iService(aProxy)
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
    SyncGetSystemUpdateIDUpnpOrgContentDirectory1Cpp(CpProxyUpnpOrgContentDirectory1Cpp& aProxy, uint32_t& aId);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetSystemUpdateIDUpnpOrgContentDirectory1Cpp() {}
private:
    CpProxyUpnpOrgContentDirectory1Cpp& iService;
    uint32_t& iId;
};

SyncGetSystemUpdateIDUpnpOrgContentDirectory1Cpp::SyncGetSystemUpdateIDUpnpOrgContentDirectory1Cpp(CpProxyUpnpOrgContentDirectory1Cpp& aProxy, uint32_t& aId)
    : iService(aProxy)
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
    SyncBrowseUpnpOrgContentDirectory1Cpp(CpProxyUpnpOrgContentDirectory1Cpp& aProxy, std::string& aResult, uint32_t& aNumberReturned, uint32_t& aTotalMatches, uint32_t& aUpdateID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncBrowseUpnpOrgContentDirectory1Cpp() {}
private:
    CpProxyUpnpOrgContentDirectory1Cpp& iService;
    std::string& iResult;
    uint32_t& iNumberReturned;
    uint32_t& iTotalMatches;
    uint32_t& iUpdateID;
};

SyncBrowseUpnpOrgContentDirectory1Cpp::SyncBrowseUpnpOrgContentDirectory1Cpp(CpProxyUpnpOrgContentDirectory1Cpp& aProxy, std::string& aResult, uint32_t& aNumberReturned, uint32_t& aTotalMatches, uint32_t& aUpdateID)
    : iService(aProxy)
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
    SyncSearchUpnpOrgContentDirectory1Cpp(CpProxyUpnpOrgContentDirectory1Cpp& aProxy, std::string& aResult, uint32_t& aNumberReturned, uint32_t& aTotalMatches, uint32_t& aUpdateID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSearchUpnpOrgContentDirectory1Cpp() {}
private:
    CpProxyUpnpOrgContentDirectory1Cpp& iService;
    std::string& iResult;
    uint32_t& iNumberReturned;
    uint32_t& iTotalMatches;
    uint32_t& iUpdateID;
};

SyncSearchUpnpOrgContentDirectory1Cpp::SyncSearchUpnpOrgContentDirectory1Cpp(CpProxyUpnpOrgContentDirectory1Cpp& aProxy, std::string& aResult, uint32_t& aNumberReturned, uint32_t& aTotalMatches, uint32_t& aUpdateID)
    : iService(aProxy)
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
    SyncCreateObjectUpnpOrgContentDirectory1Cpp(CpProxyUpnpOrgContentDirectory1Cpp& aProxy, std::string& aObjectID, std::string& aResult);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncCreateObjectUpnpOrgContentDirectory1Cpp() {}
private:
    CpProxyUpnpOrgContentDirectory1Cpp& iService;
    std::string& iObjectID;
    std::string& iResult;
};

SyncCreateObjectUpnpOrgContentDirectory1Cpp::SyncCreateObjectUpnpOrgContentDirectory1Cpp(CpProxyUpnpOrgContentDirectory1Cpp& aProxy, std::string& aObjectID, std::string& aResult)
    : iService(aProxy)
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
    SyncDestroyObjectUpnpOrgContentDirectory1Cpp(CpProxyUpnpOrgContentDirectory1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncDestroyObjectUpnpOrgContentDirectory1Cpp() {}
private:
    CpProxyUpnpOrgContentDirectory1Cpp& iService;
};

SyncDestroyObjectUpnpOrgContentDirectory1Cpp::SyncDestroyObjectUpnpOrgContentDirectory1Cpp(CpProxyUpnpOrgContentDirectory1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncDestroyObjectUpnpOrgContentDirectory1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndDestroyObject(aAsync);
}


class SyncUpdateObjectUpnpOrgContentDirectory1Cpp : public SyncProxyAction
{
public:
    SyncUpdateObjectUpnpOrgContentDirectory1Cpp(CpProxyUpnpOrgContentDirectory1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncUpdateObjectUpnpOrgContentDirectory1Cpp() {}
private:
    CpProxyUpnpOrgContentDirectory1Cpp& iService;
};

SyncUpdateObjectUpnpOrgContentDirectory1Cpp::SyncUpdateObjectUpnpOrgContentDirectory1Cpp(CpProxyUpnpOrgContentDirectory1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncUpdateObjectUpnpOrgContentDirectory1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndUpdateObject(aAsync);
}


class SyncImportResourceUpnpOrgContentDirectory1Cpp : public SyncProxyAction
{
public:
    SyncImportResourceUpnpOrgContentDirectory1Cpp(CpProxyUpnpOrgContentDirectory1Cpp& aProxy, uint32_t& aTransferID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncImportResourceUpnpOrgContentDirectory1Cpp() {}
private:
    CpProxyUpnpOrgContentDirectory1Cpp& iService;
    uint32_t& iTransferID;
};

SyncImportResourceUpnpOrgContentDirectory1Cpp::SyncImportResourceUpnpOrgContentDirectory1Cpp(CpProxyUpnpOrgContentDirectory1Cpp& aProxy, uint32_t& aTransferID)
    : iService(aProxy)
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
    SyncExportResourceUpnpOrgContentDirectory1Cpp(CpProxyUpnpOrgContentDirectory1Cpp& aProxy, uint32_t& aTransferID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncExportResourceUpnpOrgContentDirectory1Cpp() {}
private:
    CpProxyUpnpOrgContentDirectory1Cpp& iService;
    uint32_t& iTransferID;
};

SyncExportResourceUpnpOrgContentDirectory1Cpp::SyncExportResourceUpnpOrgContentDirectory1Cpp(CpProxyUpnpOrgContentDirectory1Cpp& aProxy, uint32_t& aTransferID)
    : iService(aProxy)
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
    SyncStopTransferResourceUpnpOrgContentDirectory1Cpp(CpProxyUpnpOrgContentDirectory1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncStopTransferResourceUpnpOrgContentDirectory1Cpp() {}
private:
    CpProxyUpnpOrgContentDirectory1Cpp& iService;
};

SyncStopTransferResourceUpnpOrgContentDirectory1Cpp::SyncStopTransferResourceUpnpOrgContentDirectory1Cpp(CpProxyUpnpOrgContentDirectory1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncStopTransferResourceUpnpOrgContentDirectory1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndStopTransferResource(aAsync);
}


class SyncGetTransferProgressUpnpOrgContentDirectory1Cpp : public SyncProxyAction
{
public:
    SyncGetTransferProgressUpnpOrgContentDirectory1Cpp(CpProxyUpnpOrgContentDirectory1Cpp& aProxy, std::string& aTransferStatus, std::string& aTransferLength, std::string& aTransferTotal);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetTransferProgressUpnpOrgContentDirectory1Cpp() {}
private:
    CpProxyUpnpOrgContentDirectory1Cpp& iService;
    std::string& iTransferStatus;
    std::string& iTransferLength;
    std::string& iTransferTotal;
};

SyncGetTransferProgressUpnpOrgContentDirectory1Cpp::SyncGetTransferProgressUpnpOrgContentDirectory1Cpp(CpProxyUpnpOrgContentDirectory1Cpp& aProxy, std::string& aTransferStatus, std::string& aTransferLength, std::string& aTransferTotal)
    : iService(aProxy)
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
    SyncDeleteResourceUpnpOrgContentDirectory1Cpp(CpProxyUpnpOrgContentDirectory1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncDeleteResourceUpnpOrgContentDirectory1Cpp() {}
private:
    CpProxyUpnpOrgContentDirectory1Cpp& iService;
};

SyncDeleteResourceUpnpOrgContentDirectory1Cpp::SyncDeleteResourceUpnpOrgContentDirectory1Cpp(CpProxyUpnpOrgContentDirectory1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncDeleteResourceUpnpOrgContentDirectory1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndDeleteResource(aAsync);
}


class SyncCreateReferenceUpnpOrgContentDirectory1Cpp : public SyncProxyAction
{
public:
    SyncCreateReferenceUpnpOrgContentDirectory1Cpp(CpProxyUpnpOrgContentDirectory1Cpp& aProxy, std::string& aNewID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncCreateReferenceUpnpOrgContentDirectory1Cpp() {}
private:
    CpProxyUpnpOrgContentDirectory1Cpp& iService;
    std::string& iNewID;
};

SyncCreateReferenceUpnpOrgContentDirectory1Cpp::SyncCreateReferenceUpnpOrgContentDirectory1Cpp(CpProxyUpnpOrgContentDirectory1Cpp& aProxy, std::string& aNewID)
    : iService(aProxy)
    , iNewID(aNewID)
{
}

void SyncCreateReferenceUpnpOrgContentDirectory1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndCreateReference(aAsync, iNewID);
}


CpProxyUpnpOrgContentDirectory1Cpp::CpProxyUpnpOrgContentDirectory1Cpp(CpDeviceCpp& aDevice)
    : CpProxy("schemas-upnp-org", "ContentDirectory", 1, aDevice.Device())
{
    OpenHome::Net::Parameter* param;
    TChar** allowedValues;
    TUint index;

    iActionGetSearchCapabilities = new Action("GetSearchCapabilities");
    param = new OpenHome::Net::ParameterString("SearchCaps");
    iActionGetSearchCapabilities->AddOutputParameter(param);

    iActionGetSortCapabilities = new Action("GetSortCapabilities");
    param = new OpenHome::Net::ParameterString("SortCaps");
    iActionGetSortCapabilities->AddOutputParameter(param);

    iActionGetSystemUpdateID = new Action("GetSystemUpdateID");
    param = new OpenHome::Net::ParameterUint("Id");
    iActionGetSystemUpdateID->AddOutputParameter(param);

    iActionBrowse = new Action("Browse");
    param = new OpenHome::Net::ParameterString("ObjectID");
    iActionBrowse->AddInputParameter(param);
    index = 0;
    allowedValues = new TChar*[2];
    allowedValues[index++] = (TChar*)"BrowseMetadata";
    allowedValues[index++] = (TChar*)"BrowseDirectChildren";
    param = new OpenHome::Net::ParameterString("BrowseFlag", allowedValues, 2);
    iActionBrowse->AddInputParameter(param);
    delete[] allowedValues;
    param = new OpenHome::Net::ParameterString("Filter");
    iActionBrowse->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("StartingIndex");
    iActionBrowse->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("RequestedCount");
    iActionBrowse->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("SortCriteria");
    iActionBrowse->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Result");
    iActionBrowse->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("NumberReturned");
    iActionBrowse->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("TotalMatches");
    iActionBrowse->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("UpdateID");
    iActionBrowse->AddOutputParameter(param);

    iActionSearch = new Action("Search");
    param = new OpenHome::Net::ParameterString("ContainerID");
    iActionSearch->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("SearchCriteria");
    iActionSearch->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Filter");
    iActionSearch->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("StartingIndex");
    iActionSearch->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("RequestedCount");
    iActionSearch->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("SortCriteria");
    iActionSearch->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Result");
    iActionSearch->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("NumberReturned");
    iActionSearch->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("TotalMatches");
    iActionSearch->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("UpdateID");
    iActionSearch->AddOutputParameter(param);

    iActionCreateObject = new Action("CreateObject");
    param = new OpenHome::Net::ParameterString("ContainerID");
    iActionCreateObject->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Elements");
    iActionCreateObject->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("ObjectID");
    iActionCreateObject->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("Result");
    iActionCreateObject->AddOutputParameter(param);

    iActionDestroyObject = new Action("DestroyObject");
    param = new OpenHome::Net::ParameterString("ObjectID");
    iActionDestroyObject->AddInputParameter(param);

    iActionUpdateObject = new Action("UpdateObject");
    param = new OpenHome::Net::ParameterString("ObjectID");
    iActionUpdateObject->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("CurrentTagValue");
    iActionUpdateObject->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("NewTagValue");
    iActionUpdateObject->AddInputParameter(param);

    iActionImportResource = new Action("ImportResource");
    param = new OpenHome::Net::ParameterString("SourceURI");
    iActionImportResource->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("DestinationURI");
    iActionImportResource->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("TransferID");
    iActionImportResource->AddOutputParameter(param);

    iActionExportResource = new Action("ExportResource");
    param = new OpenHome::Net::ParameterString("SourceURI");
    iActionExportResource->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("DestinationURI");
    iActionExportResource->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("TransferID");
    iActionExportResource->AddOutputParameter(param);

    iActionStopTransferResource = new Action("StopTransferResource");
    param = new OpenHome::Net::ParameterUint("TransferID");
    iActionStopTransferResource->AddInputParameter(param);

    iActionGetTransferProgress = new Action("GetTransferProgress");
    param = new OpenHome::Net::ParameterUint("TransferID");
    iActionGetTransferProgress->AddInputParameter(param);
    index = 0;
    allowedValues = new TChar*[4];
    allowedValues[index++] = (TChar*)"COMPLETED";
    allowedValues[index++] = (TChar*)"ERROR";
    allowedValues[index++] = (TChar*)"IN_PROGRESS";
    allowedValues[index++] = (TChar*)"STOPPED";
    param = new OpenHome::Net::ParameterString("TransferStatus", allowedValues, 4);
    iActionGetTransferProgress->AddOutputParameter(param);
    delete[] allowedValues;
    param = new OpenHome::Net::ParameterString("TransferLength");
    iActionGetTransferProgress->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("TransferTotal");
    iActionGetTransferProgress->AddOutputParameter(param);

    iActionDeleteResource = new Action("DeleteResource");
    param = new OpenHome::Net::ParameterString("ResourceURI");
    iActionDeleteResource->AddInputParameter(param);

    iActionCreateReference = new Action("CreateReference");
    param = new OpenHome::Net::ParameterString("ContainerID");
    iActionCreateReference->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("ObjectID");
    iActionCreateReference->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("NewID");
    iActionCreateReference->AddOutputParameter(param);

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyUpnpOrgContentDirectory1Cpp::TransferIDsPropertyChanged);
    iTransferIDs = new PropertyString(aDevice.Device().GetCpStack().Env(), "TransferIDs", functor);
    AddProperty(iTransferIDs);
    functor = MakeFunctor(*this, &CpProxyUpnpOrgContentDirectory1Cpp::SystemUpdateIDPropertyChanged);
    iSystemUpdateID = new PropertyUint(aDevice.Device().GetCpStack().Env(), "SystemUpdateID", functor);
    AddProperty(iSystemUpdateID);
    functor = MakeFunctor(*this, &CpProxyUpnpOrgContentDirectory1Cpp::ContainerUpdateIDsPropertyChanged);
    iContainerUpdateIDs = new PropertyString(aDevice.Device().GetCpStack().Env(), "ContainerUpdateIDs", functor);
    AddProperty(iContainerUpdateIDs);
}

CpProxyUpnpOrgContentDirectory1Cpp::~CpProxyUpnpOrgContentDirectory1Cpp()
{
    DestroyService();
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
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory1Cpp::EndGetSearchCapabilities(IAsync& aAsync, std::string& aSearchCaps)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetSearchCapabilities"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
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
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory1Cpp::EndGetSortCapabilities(IAsync& aAsync, std::string& aSortCaps)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetSortCapabilities"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
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
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory1Cpp::EndGetSystemUpdateID(IAsync& aAsync, uint32_t& aId)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetSystemUpdateID"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
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
        Brn buf((const TByte*)aObjectID.c_str(), (TUint)aObjectID.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aBrowseFlag.c_str(), (TUint)aBrowseFlag.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aFilter.c_str(), (TUint)aFilter.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aStartingIndex));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aRequestedCount));
    {
        Brn buf((const TByte*)aSortCriteria.c_str(), (TUint)aSortCriteria.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionBrowse->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory1Cpp::EndBrowse(IAsync& aAsync, std::string& aResult, uint32_t& aNumberReturned, uint32_t& aTotalMatches, uint32_t& aUpdateID)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Browse"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
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
        Brn buf((const TByte*)aContainerID.c_str(), (TUint)aContainerID.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aSearchCriteria.c_str(), (TUint)aSearchCriteria.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aFilter.c_str(), (TUint)aFilter.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aStartingIndex));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aRequestedCount));
    {
        Brn buf((const TByte*)aSortCriteria.c_str(), (TUint)aSortCriteria.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionSearch->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory1Cpp::EndSearch(IAsync& aAsync, std::string& aResult, uint32_t& aNumberReturned, uint32_t& aTotalMatches, uint32_t& aUpdateID)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Search"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
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
        Brn buf((const TByte*)aContainerID.c_str(), (TUint)aContainerID.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aElements.c_str(), (TUint)aElements.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionCreateObject->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory1Cpp::EndCreateObject(IAsync& aAsync, std::string& aObjectID, std::string& aResult)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("CreateObject"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
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
        Brn buf((const TByte*)aObjectID.c_str(), (TUint)aObjectID.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory1Cpp::EndDestroyObject(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("DestroyObject"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
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
        Brn buf((const TByte*)aObjectID.c_str(), (TUint)aObjectID.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aCurrentTagValue.c_str(), (TUint)aCurrentTagValue.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aNewTagValue.c_str(), (TUint)aNewTagValue.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory1Cpp::EndUpdateObject(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("UpdateObject"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
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
        Brn buf((const TByte*)aSourceURI.c_str(), (TUint)aSourceURI.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aDestinationURI.c_str(), (TUint)aDestinationURI.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionImportResource->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory1Cpp::EndImportResource(IAsync& aAsync, uint32_t& aTransferID)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("ImportResource"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
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
        Brn buf((const TByte*)aSourceURI.c_str(), (TUint)aSourceURI.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aDestinationURI.c_str(), (TUint)aDestinationURI.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionExportResource->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory1Cpp::EndExportResource(IAsync& aAsync, uint32_t& aTransferID)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("ExportResource"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
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
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory1Cpp::EndStopTransferResource(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("StopTransferResource"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
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
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory1Cpp::EndGetTransferProgress(IAsync& aAsync, std::string& aTransferStatus, std::string& aTransferLength, std::string& aTransferTotal)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetTransferProgress"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
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
        Brn buf((const TByte*)aResourceURI.c_str(), (TUint)aResourceURI.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory1Cpp::EndDeleteResource(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("DeleteResource"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
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
        Brn buf((const TByte*)aContainerID.c_str(), (TUint)aContainerID.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aObjectID.c_str(), (TUint)aObjectID.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionCreateReference->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory1Cpp::EndCreateReference(IAsync& aAsync, std::string& aNewID)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("CreateReference"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
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
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iTransferIDs->Value();
    aTransferIDs.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyUpnpOrgContentDirectory1Cpp::PropertySystemUpdateID(uint32_t& aSystemUpdateID) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aSystemUpdateID = iSystemUpdateID->Value();
}

void CpProxyUpnpOrgContentDirectory1Cpp::PropertyContainerUpdateIDs(std::string& aContainerUpdateIDs) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iContainerUpdateIDs->Value();
    aContainerUpdateIDs.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyUpnpOrgContentDirectory1Cpp::TransferIDsPropertyChanged()
{
    ReportEvent(iTransferIDsChanged);
}

void CpProxyUpnpOrgContentDirectory1Cpp::SystemUpdateIDPropertyChanged()
{
    ReportEvent(iSystemUpdateIDChanged);
}

void CpProxyUpnpOrgContentDirectory1Cpp::ContainerUpdateIDsPropertyChanged()
{
    ReportEvent(iContainerUpdateIDsChanged);
}

