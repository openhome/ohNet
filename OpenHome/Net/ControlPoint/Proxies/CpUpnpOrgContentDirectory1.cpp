#include "CpUpnpOrgContentDirectory1.h"
#include <OpenHome/Net/Core/CpProxy.h>
#include <OpenHome/Net/Private/CpiService.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Net/Private/AsyncPrivate.h>
#include <OpenHome/Net/Core/CpDevice.h>
#include <OpenHome/Net/Private/Error.h>
#include <OpenHome/Net/Private/CpiDevice.h>

using namespace OpenHome;
using namespace OpenHome::Net;


class SyncGetSearchCapabilitiesUpnpOrgContentDirectory1 : public SyncProxyAction
{
public:
    SyncGetSearchCapabilitiesUpnpOrgContentDirectory1(CpProxyUpnpOrgContentDirectory1& aProxy, Brh& aSearchCaps);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetSearchCapabilitiesUpnpOrgContentDirectory1() {}
private:
    CpProxyUpnpOrgContentDirectory1& iService;
    Brh& iSearchCaps;
};

SyncGetSearchCapabilitiesUpnpOrgContentDirectory1::SyncGetSearchCapabilitiesUpnpOrgContentDirectory1(CpProxyUpnpOrgContentDirectory1& aProxy, Brh& aSearchCaps)
    : iService(aProxy)
    , iSearchCaps(aSearchCaps)
{
}

void SyncGetSearchCapabilitiesUpnpOrgContentDirectory1::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetSearchCapabilities(aAsync, iSearchCaps);
}


class SyncGetSortCapabilitiesUpnpOrgContentDirectory1 : public SyncProxyAction
{
public:
    SyncGetSortCapabilitiesUpnpOrgContentDirectory1(CpProxyUpnpOrgContentDirectory1& aProxy, Brh& aSortCaps);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetSortCapabilitiesUpnpOrgContentDirectory1() {}
private:
    CpProxyUpnpOrgContentDirectory1& iService;
    Brh& iSortCaps;
};

SyncGetSortCapabilitiesUpnpOrgContentDirectory1::SyncGetSortCapabilitiesUpnpOrgContentDirectory1(CpProxyUpnpOrgContentDirectory1& aProxy, Brh& aSortCaps)
    : iService(aProxy)
    , iSortCaps(aSortCaps)
{
}

void SyncGetSortCapabilitiesUpnpOrgContentDirectory1::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetSortCapabilities(aAsync, iSortCaps);
}


class SyncGetSystemUpdateIDUpnpOrgContentDirectory1 : public SyncProxyAction
{
public:
    SyncGetSystemUpdateIDUpnpOrgContentDirectory1(CpProxyUpnpOrgContentDirectory1& aProxy, TUint& aId);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetSystemUpdateIDUpnpOrgContentDirectory1() {}
private:
    CpProxyUpnpOrgContentDirectory1& iService;
    TUint& iId;
};

SyncGetSystemUpdateIDUpnpOrgContentDirectory1::SyncGetSystemUpdateIDUpnpOrgContentDirectory1(CpProxyUpnpOrgContentDirectory1& aProxy, TUint& aId)
    : iService(aProxy)
    , iId(aId)
{
}

void SyncGetSystemUpdateIDUpnpOrgContentDirectory1::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetSystemUpdateID(aAsync, iId);
}


class SyncBrowseUpnpOrgContentDirectory1 : public SyncProxyAction
{
public:
    SyncBrowseUpnpOrgContentDirectory1(CpProxyUpnpOrgContentDirectory1& aProxy, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncBrowseUpnpOrgContentDirectory1() {}
private:
    CpProxyUpnpOrgContentDirectory1& iService;
    Brh& iResult;
    TUint& iNumberReturned;
    TUint& iTotalMatches;
    TUint& iUpdateID;
};

SyncBrowseUpnpOrgContentDirectory1::SyncBrowseUpnpOrgContentDirectory1(CpProxyUpnpOrgContentDirectory1& aProxy, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID)
    : iService(aProxy)
    , iResult(aResult)
    , iNumberReturned(aNumberReturned)
    , iTotalMatches(aTotalMatches)
    , iUpdateID(aUpdateID)
{
}

void SyncBrowseUpnpOrgContentDirectory1::CompleteRequest(IAsync& aAsync)
{
    iService.EndBrowse(aAsync, iResult, iNumberReturned, iTotalMatches, iUpdateID);
}


class SyncSearchUpnpOrgContentDirectory1 : public SyncProxyAction
{
public:
    SyncSearchUpnpOrgContentDirectory1(CpProxyUpnpOrgContentDirectory1& aProxy, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSearchUpnpOrgContentDirectory1() {}
private:
    CpProxyUpnpOrgContentDirectory1& iService;
    Brh& iResult;
    TUint& iNumberReturned;
    TUint& iTotalMatches;
    TUint& iUpdateID;
};

SyncSearchUpnpOrgContentDirectory1::SyncSearchUpnpOrgContentDirectory1(CpProxyUpnpOrgContentDirectory1& aProxy, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID)
    : iService(aProxy)
    , iResult(aResult)
    , iNumberReturned(aNumberReturned)
    , iTotalMatches(aTotalMatches)
    , iUpdateID(aUpdateID)
{
}

void SyncSearchUpnpOrgContentDirectory1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSearch(aAsync, iResult, iNumberReturned, iTotalMatches, iUpdateID);
}


class SyncCreateObjectUpnpOrgContentDirectory1 : public SyncProxyAction
{
public:
    SyncCreateObjectUpnpOrgContentDirectory1(CpProxyUpnpOrgContentDirectory1& aProxy, Brh& aObjectID, Brh& aResult);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncCreateObjectUpnpOrgContentDirectory1() {}
private:
    CpProxyUpnpOrgContentDirectory1& iService;
    Brh& iObjectID;
    Brh& iResult;
};

SyncCreateObjectUpnpOrgContentDirectory1::SyncCreateObjectUpnpOrgContentDirectory1(CpProxyUpnpOrgContentDirectory1& aProxy, Brh& aObjectID, Brh& aResult)
    : iService(aProxy)
    , iObjectID(aObjectID)
    , iResult(aResult)
{
}

void SyncCreateObjectUpnpOrgContentDirectory1::CompleteRequest(IAsync& aAsync)
{
    iService.EndCreateObject(aAsync, iObjectID, iResult);
}


class SyncDestroyObjectUpnpOrgContentDirectory1 : public SyncProxyAction
{
public:
    SyncDestroyObjectUpnpOrgContentDirectory1(CpProxyUpnpOrgContentDirectory1& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncDestroyObjectUpnpOrgContentDirectory1() {}
private:
    CpProxyUpnpOrgContentDirectory1& iService;
};

SyncDestroyObjectUpnpOrgContentDirectory1::SyncDestroyObjectUpnpOrgContentDirectory1(CpProxyUpnpOrgContentDirectory1& aProxy)
    : iService(aProxy)
{
}

void SyncDestroyObjectUpnpOrgContentDirectory1::CompleteRequest(IAsync& aAsync)
{
    iService.EndDestroyObject(aAsync);
}


class SyncUpdateObjectUpnpOrgContentDirectory1 : public SyncProxyAction
{
public:
    SyncUpdateObjectUpnpOrgContentDirectory1(CpProxyUpnpOrgContentDirectory1& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncUpdateObjectUpnpOrgContentDirectory1() {}
private:
    CpProxyUpnpOrgContentDirectory1& iService;
};

SyncUpdateObjectUpnpOrgContentDirectory1::SyncUpdateObjectUpnpOrgContentDirectory1(CpProxyUpnpOrgContentDirectory1& aProxy)
    : iService(aProxy)
{
}

void SyncUpdateObjectUpnpOrgContentDirectory1::CompleteRequest(IAsync& aAsync)
{
    iService.EndUpdateObject(aAsync);
}


class SyncImportResourceUpnpOrgContentDirectory1 : public SyncProxyAction
{
public:
    SyncImportResourceUpnpOrgContentDirectory1(CpProxyUpnpOrgContentDirectory1& aProxy, TUint& aTransferID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncImportResourceUpnpOrgContentDirectory1() {}
private:
    CpProxyUpnpOrgContentDirectory1& iService;
    TUint& iTransferID;
};

SyncImportResourceUpnpOrgContentDirectory1::SyncImportResourceUpnpOrgContentDirectory1(CpProxyUpnpOrgContentDirectory1& aProxy, TUint& aTransferID)
    : iService(aProxy)
    , iTransferID(aTransferID)
{
}

void SyncImportResourceUpnpOrgContentDirectory1::CompleteRequest(IAsync& aAsync)
{
    iService.EndImportResource(aAsync, iTransferID);
}


class SyncExportResourceUpnpOrgContentDirectory1 : public SyncProxyAction
{
public:
    SyncExportResourceUpnpOrgContentDirectory1(CpProxyUpnpOrgContentDirectory1& aProxy, TUint& aTransferID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncExportResourceUpnpOrgContentDirectory1() {}
private:
    CpProxyUpnpOrgContentDirectory1& iService;
    TUint& iTransferID;
};

SyncExportResourceUpnpOrgContentDirectory1::SyncExportResourceUpnpOrgContentDirectory1(CpProxyUpnpOrgContentDirectory1& aProxy, TUint& aTransferID)
    : iService(aProxy)
    , iTransferID(aTransferID)
{
}

void SyncExportResourceUpnpOrgContentDirectory1::CompleteRequest(IAsync& aAsync)
{
    iService.EndExportResource(aAsync, iTransferID);
}


class SyncStopTransferResourceUpnpOrgContentDirectory1 : public SyncProxyAction
{
public:
    SyncStopTransferResourceUpnpOrgContentDirectory1(CpProxyUpnpOrgContentDirectory1& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncStopTransferResourceUpnpOrgContentDirectory1() {}
private:
    CpProxyUpnpOrgContentDirectory1& iService;
};

SyncStopTransferResourceUpnpOrgContentDirectory1::SyncStopTransferResourceUpnpOrgContentDirectory1(CpProxyUpnpOrgContentDirectory1& aProxy)
    : iService(aProxy)
{
}

void SyncStopTransferResourceUpnpOrgContentDirectory1::CompleteRequest(IAsync& aAsync)
{
    iService.EndStopTransferResource(aAsync);
}


class SyncGetTransferProgressUpnpOrgContentDirectory1 : public SyncProxyAction
{
public:
    SyncGetTransferProgressUpnpOrgContentDirectory1(CpProxyUpnpOrgContentDirectory1& aProxy, Brh& aTransferStatus, Brh& aTransferLength, Brh& aTransferTotal);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetTransferProgressUpnpOrgContentDirectory1() {}
private:
    CpProxyUpnpOrgContentDirectory1& iService;
    Brh& iTransferStatus;
    Brh& iTransferLength;
    Brh& iTransferTotal;
};

SyncGetTransferProgressUpnpOrgContentDirectory1::SyncGetTransferProgressUpnpOrgContentDirectory1(CpProxyUpnpOrgContentDirectory1& aProxy, Brh& aTransferStatus, Brh& aTransferLength, Brh& aTransferTotal)
    : iService(aProxy)
    , iTransferStatus(aTransferStatus)
    , iTransferLength(aTransferLength)
    , iTransferTotal(aTransferTotal)
{
}

void SyncGetTransferProgressUpnpOrgContentDirectory1::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetTransferProgress(aAsync, iTransferStatus, iTransferLength, iTransferTotal);
}


class SyncDeleteResourceUpnpOrgContentDirectory1 : public SyncProxyAction
{
public:
    SyncDeleteResourceUpnpOrgContentDirectory1(CpProxyUpnpOrgContentDirectory1& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncDeleteResourceUpnpOrgContentDirectory1() {}
private:
    CpProxyUpnpOrgContentDirectory1& iService;
};

SyncDeleteResourceUpnpOrgContentDirectory1::SyncDeleteResourceUpnpOrgContentDirectory1(CpProxyUpnpOrgContentDirectory1& aProxy)
    : iService(aProxy)
{
}

void SyncDeleteResourceUpnpOrgContentDirectory1::CompleteRequest(IAsync& aAsync)
{
    iService.EndDeleteResource(aAsync);
}


class SyncCreateReferenceUpnpOrgContentDirectory1 : public SyncProxyAction
{
public:
    SyncCreateReferenceUpnpOrgContentDirectory1(CpProxyUpnpOrgContentDirectory1& aProxy, Brh& aNewID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncCreateReferenceUpnpOrgContentDirectory1() {}
private:
    CpProxyUpnpOrgContentDirectory1& iService;
    Brh& iNewID;
};

SyncCreateReferenceUpnpOrgContentDirectory1::SyncCreateReferenceUpnpOrgContentDirectory1(CpProxyUpnpOrgContentDirectory1& aProxy, Brh& aNewID)
    : iService(aProxy)
    , iNewID(aNewID)
{
}

void SyncCreateReferenceUpnpOrgContentDirectory1::CompleteRequest(IAsync& aAsync)
{
    iService.EndCreateReference(aAsync, iNewID);
}


CpProxyUpnpOrgContentDirectory1::CpProxyUpnpOrgContentDirectory1(CpDevice& aDevice)
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
    functor = MakeFunctor(*this, &CpProxyUpnpOrgContentDirectory1::TransferIDsPropertyChanged);
    iTransferIDs = new PropertyString(aDevice.Device().GetCpStack().Env(), "TransferIDs", functor);
    AddProperty(iTransferIDs);
    functor = MakeFunctor(*this, &CpProxyUpnpOrgContentDirectory1::SystemUpdateIDPropertyChanged);
    iSystemUpdateID = new PropertyUint(aDevice.Device().GetCpStack().Env(), "SystemUpdateID", functor);
    AddProperty(iSystemUpdateID);
    functor = MakeFunctor(*this, &CpProxyUpnpOrgContentDirectory1::ContainerUpdateIDsPropertyChanged);
    iContainerUpdateIDs = new PropertyString(aDevice.Device().GetCpStack().Env(), "ContainerUpdateIDs", functor);
    AddProperty(iContainerUpdateIDs);
}

CpProxyUpnpOrgContentDirectory1::~CpProxyUpnpOrgContentDirectory1()
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

void CpProxyUpnpOrgContentDirectory1::SyncGetSearchCapabilities(Brh& aSearchCaps)
{
    SyncGetSearchCapabilitiesUpnpOrgContentDirectory1 sync(*this, aSearchCaps);
    BeginGetSearchCapabilities(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory1::BeginGetSearchCapabilities(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetSearchCapabilities, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetSearchCapabilities->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory1::EndGetSearchCapabilities(IAsync& aAsync, Brh& aSearchCaps)
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
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aSearchCaps);
}

void CpProxyUpnpOrgContentDirectory1::SyncGetSortCapabilities(Brh& aSortCaps)
{
    SyncGetSortCapabilitiesUpnpOrgContentDirectory1 sync(*this, aSortCaps);
    BeginGetSortCapabilities(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory1::BeginGetSortCapabilities(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetSortCapabilities, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetSortCapabilities->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory1::EndGetSortCapabilities(IAsync& aAsync, Brh& aSortCaps)
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
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aSortCaps);
}

void CpProxyUpnpOrgContentDirectory1::SyncGetSystemUpdateID(TUint& aId)
{
    SyncGetSystemUpdateIDUpnpOrgContentDirectory1 sync(*this, aId);
    BeginGetSystemUpdateID(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory1::BeginGetSystemUpdateID(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetSystemUpdateID, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetSystemUpdateID->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory1::EndGetSystemUpdateID(IAsync& aAsync, TUint& aId)
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

void CpProxyUpnpOrgContentDirectory1::SyncBrowse(const Brx& aObjectID, const Brx& aBrowseFlag, const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID)
{
    SyncBrowseUpnpOrgContentDirectory1 sync(*this, aResult, aNumberReturned, aTotalMatches, aUpdateID);
    BeginBrowse(aObjectID, aBrowseFlag, aFilter, aStartingIndex, aRequestedCount, aSortCriteria, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory1::BeginBrowse(const Brx& aObjectID, const Brx& aBrowseFlag, const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionBrowse, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionBrowse->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aObjectID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aBrowseFlag));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aFilter));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aStartingIndex));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aRequestedCount));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aSortCriteria));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionBrowse->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory1::EndBrowse(IAsync& aAsync, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID)
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
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aResult);
    aNumberReturned = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aTotalMatches = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aUpdateID = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgContentDirectory1::SyncSearch(const Brx& aContainerID, const Brx& aSearchCriteria, const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID)
{
    SyncSearchUpnpOrgContentDirectory1 sync(*this, aResult, aNumberReturned, aTotalMatches, aUpdateID);
    BeginSearch(aContainerID, aSearchCriteria, aFilter, aStartingIndex, aRequestedCount, aSortCriteria, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory1::BeginSearch(const Brx& aContainerID, const Brx& aSearchCriteria, const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSearch, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSearch->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aContainerID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aSearchCriteria));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aFilter));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aStartingIndex));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aRequestedCount));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aSortCriteria));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionSearch->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory1::EndSearch(IAsync& aAsync, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID)
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
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aResult);
    aNumberReturned = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aTotalMatches = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aUpdateID = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgContentDirectory1::SyncCreateObject(const Brx& aContainerID, const Brx& aElements, Brh& aObjectID, Brh& aResult)
{
    SyncCreateObjectUpnpOrgContentDirectory1 sync(*this, aObjectID, aResult);
    BeginCreateObject(aContainerID, aElements, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory1::BeginCreateObject(const Brx& aContainerID, const Brx& aElements, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionCreateObject, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionCreateObject->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aContainerID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aElements));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionCreateObject->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory1::EndCreateObject(IAsync& aAsync, Brh& aObjectID, Brh& aResult)
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
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aObjectID);
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aResult);
}

void CpProxyUpnpOrgContentDirectory1::SyncDestroyObject(const Brx& aObjectID)
{
    SyncDestroyObjectUpnpOrgContentDirectory1 sync(*this);
    BeginDestroyObject(aObjectID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory1::BeginDestroyObject(const Brx& aObjectID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionDestroyObject, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionDestroyObject->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aObjectID));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory1::EndDestroyObject(IAsync& aAsync)
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

void CpProxyUpnpOrgContentDirectory1::SyncUpdateObject(const Brx& aObjectID, const Brx& aCurrentTagValue, const Brx& aNewTagValue)
{
    SyncUpdateObjectUpnpOrgContentDirectory1 sync(*this);
    BeginUpdateObject(aObjectID, aCurrentTagValue, aNewTagValue, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory1::BeginUpdateObject(const Brx& aObjectID, const Brx& aCurrentTagValue, const Brx& aNewTagValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionUpdateObject, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionUpdateObject->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aObjectID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aCurrentTagValue));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aNewTagValue));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory1::EndUpdateObject(IAsync& aAsync)
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

void CpProxyUpnpOrgContentDirectory1::SyncImportResource(const Brx& aSourceURI, const Brx& aDestinationURI, TUint& aTransferID)
{
    SyncImportResourceUpnpOrgContentDirectory1 sync(*this, aTransferID);
    BeginImportResource(aSourceURI, aDestinationURI, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory1::BeginImportResource(const Brx& aSourceURI, const Brx& aDestinationURI, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionImportResource, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionImportResource->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aSourceURI));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aDestinationURI));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionImportResource->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory1::EndImportResource(IAsync& aAsync, TUint& aTransferID)
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

void CpProxyUpnpOrgContentDirectory1::SyncExportResource(const Brx& aSourceURI, const Brx& aDestinationURI, TUint& aTransferID)
{
    SyncExportResourceUpnpOrgContentDirectory1 sync(*this, aTransferID);
    BeginExportResource(aSourceURI, aDestinationURI, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory1::BeginExportResource(const Brx& aSourceURI, const Brx& aDestinationURI, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionExportResource, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionExportResource->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aSourceURI));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aDestinationURI));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionExportResource->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory1::EndExportResource(IAsync& aAsync, TUint& aTransferID)
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

void CpProxyUpnpOrgContentDirectory1::SyncStopTransferResource(TUint aTransferID)
{
    SyncStopTransferResourceUpnpOrgContentDirectory1 sync(*this);
    BeginStopTransferResource(aTransferID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory1::BeginStopTransferResource(TUint aTransferID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionStopTransferResource, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionStopTransferResource->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aTransferID));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory1::EndStopTransferResource(IAsync& aAsync)
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

void CpProxyUpnpOrgContentDirectory1::SyncGetTransferProgress(TUint aTransferID, Brh& aTransferStatus, Brh& aTransferLength, Brh& aTransferTotal)
{
    SyncGetTransferProgressUpnpOrgContentDirectory1 sync(*this, aTransferStatus, aTransferLength, aTransferTotal);
    BeginGetTransferProgress(aTransferID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory1::BeginGetTransferProgress(TUint aTransferID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgContentDirectory1::EndGetTransferProgress(IAsync& aAsync, Brh& aTransferStatus, Brh& aTransferLength, Brh& aTransferTotal)
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
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aTransferStatus);
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aTransferLength);
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aTransferTotal);
}

void CpProxyUpnpOrgContentDirectory1::SyncDeleteResource(const Brx& aResourceURI)
{
    SyncDeleteResourceUpnpOrgContentDirectory1 sync(*this);
    BeginDeleteResource(aResourceURI, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory1::BeginDeleteResource(const Brx& aResourceURI, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionDeleteResource, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionDeleteResource->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aResourceURI));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory1::EndDeleteResource(IAsync& aAsync)
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

void CpProxyUpnpOrgContentDirectory1::SyncCreateReference(const Brx& aContainerID, const Brx& aObjectID, Brh& aNewID)
{
    SyncCreateReferenceUpnpOrgContentDirectory1 sync(*this, aNewID);
    BeginCreateReference(aContainerID, aObjectID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory1::BeginCreateReference(const Brx& aContainerID, const Brx& aObjectID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionCreateReference, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionCreateReference->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aContainerID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aObjectID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionCreateReference->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory1::EndCreateReference(IAsync& aAsync, Brh& aNewID)
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
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aNewID);
}

void CpProxyUpnpOrgContentDirectory1::SetPropertyTransferIDsChanged(Functor& aFunctor)
{
    iLock->Wait();
    iTransferIDsChanged = aFunctor;
    iLock->Signal();
}

void CpProxyUpnpOrgContentDirectory1::SetPropertySystemUpdateIDChanged(Functor& aFunctor)
{
    iLock->Wait();
    iSystemUpdateIDChanged = aFunctor;
    iLock->Signal();
}

void CpProxyUpnpOrgContentDirectory1::SetPropertyContainerUpdateIDsChanged(Functor& aFunctor)
{
    iLock->Wait();
    iContainerUpdateIDsChanged = aFunctor;
    iLock->Signal();
}

void CpProxyUpnpOrgContentDirectory1::PropertyTransferIDs(Brhz& aTransferIDs) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aTransferIDs.Set(iTransferIDs->Value());
}

void CpProxyUpnpOrgContentDirectory1::PropertySystemUpdateID(TUint& aSystemUpdateID) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aSystemUpdateID = iSystemUpdateID->Value();
}

void CpProxyUpnpOrgContentDirectory1::PropertyContainerUpdateIDs(Brhz& aContainerUpdateIDs) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aContainerUpdateIDs.Set(iContainerUpdateIDs->Value());
}

void CpProxyUpnpOrgContentDirectory1::TransferIDsPropertyChanged()
{
    ReportEvent(iTransferIDsChanged);
}

void CpProxyUpnpOrgContentDirectory1::SystemUpdateIDPropertyChanged()
{
    ReportEvent(iSystemUpdateIDChanged);
}

void CpProxyUpnpOrgContentDirectory1::ContainerUpdateIDsPropertyChanged()
{
    ReportEvent(iContainerUpdateIDsChanged);
}

