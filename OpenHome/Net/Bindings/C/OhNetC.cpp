#include <OpenHome/Net/C/OhNet.h>
#include <OpenHome/Net/Core/OhNet.h>
#include <OpenHome/Functor.h>
#include <OpenHome/FunctorMsg.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Net/Private/Globals.h>
#include <OpenHome/OsWrapper.h>
#include <OpenHome/Net/Private/CpiStack.h>
#include <OpenHome/Net/Private/CpiSubscription.h>

#include <stdlib.h>

using namespace OpenHome;
using namespace OpenHome::Net;

int32_t STDCALL OhNetLibraryInitialise(OhNetHandleInitParams aInitParams)
{
    if (gEnv != NULL) {
        return -1;
    }
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aInitParams);
    try {
        UpnpLibrary::Initialise(ip);
    }
    catch(...) {
        return -1;
    }
    return 0;
}

int32_t STDCALL OhNetLibraryInitialiseMinimal(OhNetHandleInitParams aInitParams)
{
    if (gEnv != NULL) {
        return -1;
    }
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aInitParams);
    try {
        UpnpLibrary::InitialiseMinimal(ip);
    }
    catch(...) {
        return -1;
    }
    return 0;
}

void STDCALL OhNetLibraryClose()
{
    UpnpLibrary::Close();
}

void STDCALL OhNetLibraryNotifySuspended(void)
{
    UpnpLibrary::NotifySuspended();
}

void STDCALL OhNetLibraryNotifyResumed(void)
{
    UpnpLibrary::NotifyResumed();
}

void STDCALL OhNetLibraryRenewSubscriptions(void)
{
    ASSERT(gCpStack != NULL);
    gCpStack->SubscriptionManager().RenewAll();
}

void STDCALL OhNetFree(void* aPtr)
{
    free(aPtr);
}

OhNetHandleInitParams STDCALL OhNetInitParamsCreate()
{
    return (OhNetHandleInitParams)InitialisationParams::Create();
}

void STDCALL OhNetInitParamsDestroy(OhNetHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    delete ip;
}

void STDCALL OhNetInitParamsSetLogOutput(OhNetHandleInitParams aParams, OhNetCallbackMsg aCallback, void* aPtr)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    FunctorMsg functor = MakeFunctorMsgC(aPtr, aCallback);
    ip->SetLogOutput(functor);
}

void STDCALL OhNetInitParamsSetFatalErrorHandler(OhNetHandleInitParams aParams, OhNetCallbackMsg aCallback, void* aPtr)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    FunctorMsg functor = MakeFunctorMsgC(aPtr, aCallback);
    ip->SetFatalErrorHandler(functor);
}

void STDCALL OhNetInitParamsSetAsyncBeginHandler(OhNetHandleInitParams aParams, OhNetCallbackAsync aCallback, void* aPtr)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    ip->SetAsyncBeginHandler(functor);
}

void STDCALL OhNetInitParamsSetAsyncEndHandler(OhNetHandleInitParams aParams, OhNetCallbackAsync aCallback, void* aPtr)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    ip->SetAsyncEndHandler(functor);
}

void STDCALL OhNetInitParamsSetAsyncErrorHandler(OhNetHandleInitParams aParams, OhNetCallbackAsync aCallback, void* aPtr)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    ip->SetAsyncErrorHandler(functor);
}

void STDCALL OhNetInitParamsSetSubnetListChangedListener(OhNetHandleInitParams aParams, OhNetCallback aCallback, void* aPtr)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    Functor functor = MakeFunctor(aPtr, aCallback);
    ip->SetSubnetListChangedListener(functor);
}

void STDCALL OhNetInitParamsSetSubnetAddedListener(OhNetHandleInitParams aParams, OhNetCallbackNetworkAdapter aCallback, void* aPtr)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    FunctorNetworkAdapter functor = MakeFunctorNetworkAdapter(aPtr, (OhNetFunctorNetworkAdapter)aCallback);
    ip->SetSubnetAddedListener(functor);
}

void STDCALL OhNetInitParamsSetSubnetRemovedListener(OhNetHandleInitParams aParams, OhNetCallbackNetworkAdapter aCallback, void* aPtr)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    FunctorNetworkAdapter functor = MakeFunctorNetworkAdapter(aPtr, (OhNetFunctorNetworkAdapter)aCallback);
    ip->SetSubnetRemovedListener(functor);
}

void STDCALL OhNetInitParamsSetNetworkAdapterChangedListener(OhNetHandleInitParams aParams, OhNetCallbackNetworkAdapter aCallback, void* aPtr)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    FunctorNetworkAdapter functor = MakeFunctorNetworkAdapter(aPtr, (OhNetFunctorNetworkAdapter)aCallback);
    ip->SetNetworkAdapterChangedListener(functor);
}

void STDCALL OhNetInitParamsSetThreadExitHandler(OhNetHandleInitParams aParams, OhNetCallback aCallback, void* aPtr)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    Functor functor = MakeFunctor(aPtr, aCallback);
    ip->SetThreadExitHandler(functor);
}

void STDCALL OhNetInitParamsSetTcpConnectTimeout(OhNetHandleInitParams aParams, uint32_t aTimeoutMs)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    ip->SetTcpConnectTimeout(aTimeoutMs);
}

void STDCALL OhNetInitParamsSetMsearchTime(OhNetHandleInitParams aParams, uint32_t aSecs)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    ip->SetMsearchTime(aSecs);
}

void STDCALL OhNetInitParamsSetMsearchTtl(OhNetHandleInitParams aParams, uint32_t aTtl)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    ip->SetMsearchTtl(aTtl);
}

void STDCALL OhNetInitParamsSetNumEventSessionThreads(OhNetHandleInitParams aParams, uint32_t aNumThreads)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    ip->SetNumEventSessionThreads(aNumThreads);
}

void STDCALL OhNetInitParamsSetNumXmlFetcherThreads(OhNetHandleInitParams aParams, uint32_t aNumThreads)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    ip->SetNumXmlFetcherThreads(aNumThreads);
}

void STDCALL OhNetInitParamsSetNumActionInvokerThreads(OhNetHandleInitParams aParams, uint32_t aNumThreads)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    ip->SetNumActionInvokerThreads(aNumThreads);
}

void STDCALL OhNetInitParamsSetNumInvocations(OhNetHandleInitParams aParams, uint32_t aNumInvocations)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    ip->SetNumInvocations(aNumInvocations);
}

void STDCALL OhNetInitParamsSetNumSubscriberThreads(OhNetHandleInitParams aParams, uint32_t aNumThreads)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    ip->SetNumSubscriberThreads(aNumThreads);
}

void STDCALL OhNetInitParamsSetSubscriptionDuration(OhNetHandleInitParams aParams, uint32_t aDurationSecs)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    ip->SetSubscriptionDuration(aDurationSecs);
}

void STDCALL OhNetInitParamsSetPendingSubscriptionTimeout(OhNetHandleInitParams aParams, uint32_t aTimeoutMs)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    ip->SetPendingSubscriptionTimeout(aTimeoutMs);
}

void STDCALL OhNetInitParamsSetFreeExternalCallback(OhNetHandleInitParams aParams, OhNetCallbackFreeExternal aCallback)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    ip->SetFreeExternalCallback(aCallback);
}

void STDCALL OhNetInitParamsSetUseLoopbackNetworkAdapter(OhNetHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    ip->SetUseLoopbackNetworkAdapter();
}

void STDCALL OhNetInitParamsSetIncludeLoopbackNetworkAdapter(OhNetHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    ip->SetIncludeLoopbackNetworkAdapter();
}

void STDCALL OhNetInitParamsSetDvMaxUpdateTime(OhNetHandleInitParams aParams, uint32_t aSecs)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    ip->SetDvMaxUpdateTime(aSecs);
}

void STDCALL OhNetInitParamsSetDvNumServerThreads(OhNetHandleInitParams aParams, uint32_t aNumThreads)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    ip->SetDvNumServerThreads(aNumThreads);
}

void STDCALL OhNetInitParamsSetDvNumPublisherThreads(OhNetHandleInitParams aParams, uint32_t aNumThreads)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    ip->SetDvNumPublisherThreads(aNumThreads);
}

void STDCALL OhNetInitParamsSetDvNumWebSocketThreads(OhNetHandleInitParams aParams, uint32_t aNumThreads)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    ip->SetDvNumWebSocketThreads(aNumThreads);
}

void STDCALL OhNetInitParamsSetCpUpnpEventServerPort(OhNetHandleInitParams aParams, TUint aPort)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    ip->SetCpUpnpEventServerPort(aPort);
}

void STDCALL OhNetInitParamsSetDvUpnpServerPort(OhNetHandleInitParams aParams, TUint aPort)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    ip->SetDvUpnpServerPort(aPort);
}

void STDCALL OhNetInitParamsSetDvWebSocketPort(OhNetHandleInitParams aParams, uint32_t aPort)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    ip->SetDvWebSocketPort(aPort);
}

void STDCALL OhNetInitParamsSetDvEnableBonjour(OhNetHandleInitParams aParams, const char* aHostName)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    ip->SetDvEnableBonjour(aHostName);
}

void STDCALL OhNetInitParamsSetUserAgent(OhNetHandleInitParams aParams, const char* aUserAgent)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    ip->SetUserAgent(aUserAgent);
}

uint32_t STDCALL OhNetInitParamsTcpConnectTimeoutMs(OhNetHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    return ip->TcpConnectTimeoutMs();
}

uint32_t STDCALL OhNetInitParamsMsearchTimeSecs(OhNetHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    return ip->MsearchTimeSecs();
}

uint32_t STDCALL OhNetInitParamsMsearchTtl(OhNetHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    return ip->MsearchTtl();
}

uint32_t STDCALL OhNetInitParamsNumEventSessionThreads(OhNetHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    return ip->NumEventSessionThreads();
}

uint32_t STDCALL OhNetInitParamsNumXmlFetcherThreads(OhNetHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    return ip->NumXmlFetcherThreads();
}

uint32_t STDCALL OhNetInitParamsNumActionInvokerThreads(OhNetHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    return ip->NumActionInvokerThreads();
}

uint32_t STDCALL OhNetInitParamsNumInvocations(OhNetHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    return ip->NumInvocations();
}

uint32_t STDCALL OhNetInitParamsNumSubscriberThreads(OhNetHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    return ip->NumSubscriberThreads();
}

uint32_t STDCALL OhNetInitParamsSubscriptionDurationSecs(OhNetHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    return ip->SubscriptionDurationSecs();
}

uint32_t STDCALL OhNetInitParamsPendingSubscriptionTimeoutMs(OhNetHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    return ip->PendingSubscriptionTimeoutMs();
}

uint32_t STDCALL OhNetInitParamsDvMaxUpdateTimeSecs(OhNetHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    return ip->DvMaxUpdateTimeSecs();
}

uint32_t STDCALL OhNetInitParamsDvNumServerThreads(OhNetHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    return ip->DvNumServerThreads();
}

uint32_t STDCALL OhNetInitParamsDvNumPublisherThreads(OhNetHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    return ip->DvNumPublisherThreads();
}

uint32_t STDCALL OhNetInitParamsDvNumWebSocketThreads(OhNetHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    return ip->DvNumWebSocketThreads();
}

uint32_t STDCALL OhNetInitParamsCpUpnpEventServerPort(OhNetHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    return ip->CpUpnpEventServerPort();
}

uint32_t STDCALL OhNetInitParamsDvUpnpServerPort(OhNetHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    return ip->DvUpnpServerPort();
}

uint32_t STDCALL OhNetInitParamsDvWebSocketPort(OhNetHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    return ip->DvWebSocketPort();
}

uint32_t STDCALL OhNetInitParamsDvIsBonjourEnabled(OhNetHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    const TChar* ignore = NULL;
    return (ip->DvIsBonjourEnabled(ignore)? 1 : 0);
}

TIpAddress STDCALL OhNetNetworkAdapterAddress(OhNetHandleNetworkAdapter aNif)
{
    NetworkAdapter* nif = reinterpret_cast<NetworkAdapter*>(aNif);
    ASSERT(nif != NULL);
    return nif->Address();
}

TIpAddress STDCALL OhNetNetworkAdapterSubnet(OhNetHandleNetworkAdapter aNif)
{
    NetworkAdapter* nif = reinterpret_cast<NetworkAdapter*>(aNif);
    ASSERT(nif != NULL);
    return nif->Subnet();
}

TIpAddress STDCALL OhNetNetworkAdapterMask(OhNetHandleNetworkAdapter aNif)
{
    NetworkAdapter* nif = reinterpret_cast<NetworkAdapter*>(aNif);
    ASSERT(nif != NULL);
    return nif->Mask();
}

const char* STDCALL OhNetNetworkAdapterName(OhNetHandleNetworkAdapter aNif)
{
    NetworkAdapter* nif = reinterpret_cast<NetworkAdapter*>(aNif);
    ASSERT(nif != NULL);
    return nif->Name();
}

char* STDCALL OhNetNetworkAdapterFullName(OhNetHandleNetworkAdapter aNif)
{
    NetworkAdapter* nif = reinterpret_cast<NetworkAdapter*>(aNif);
    ASSERT(nif != NULL);
    return nif->FullName();
}

void STDCALL OhNetNetworkAdapterAddRef(OhNetHandleNetworkAdapter aNif, const char* aCookie)
{
    NetworkAdapter* nif = reinterpret_cast<NetworkAdapter*>(aNif);
    ASSERT(nif != NULL);
    return nif->AddRef(aCookie);
}

void STDCALL OhNetNetworkAdapterRemoveRef(OhNetHandleNetworkAdapter aNif, const char* aCookie)
{
    NetworkAdapter* nif = reinterpret_cast<NetworkAdapter*>(aNif);
    ASSERT(nif != NULL);
    return nif->RemoveRef(aCookie);
}

OhNetHandleNetworkAdapterList STDCALL OhNetSubnetListCreate()
{
    return (OhNetHandleNetworkAdapterList)UpnpLibrary::CreateSubnetList();
}

uint32_t STDCALL OhNetSubnetListSize(OhNetHandleNetworkAdapterList aList)
{
    std::vector<NetworkAdapter*>* list = reinterpret_cast<std::vector<NetworkAdapter*>*>(aList);
    ASSERT(list != NULL);
    return (TUint)list->size();
}

OhNetHandleNetworkAdapter STDCALL OhNetSubnetAt(OhNetHandleNetworkAdapterList aList, uint32_t aIndex)
{
    std::vector<NetworkAdapter*>* list = reinterpret_cast<std::vector<NetworkAdapter*>*>(aList);
    ASSERT(list != NULL);
    return (OhNetHandleNetworkAdapter)(*list)[aIndex];
}

void STDCALL OhNetSubnetListDestroy(OhNetHandleNetworkAdapterList aList)
{
    std::vector<NetworkAdapter*>* list = reinterpret_cast<std::vector<NetworkAdapter*>*>(aList);
    UpnpLibrary::DestroySubnetList(list);
}

OhNetHandleNetworkAdapterList STDCALL OhNetNetworkAdapterListCreate()
{
    return (OhNetHandleNetworkAdapterList)UpnpLibrary::CreateNetworkAdapterList();
}

uint32_t STDCALL OhNetNetworkAdapterListSize(OhNetHandleNetworkAdapterList aList)
{
    std::vector<NetworkAdapter*>* list = reinterpret_cast<std::vector<NetworkAdapter*>*>(aList);
    ASSERT(list != NULL);
    return (TUint)list->size();
}

OhNetHandleNetworkAdapter STDCALL OhNetNetworkAdapterAt(OhNetHandleNetworkAdapterList aList, uint32_t aIndex)
{
    std::vector<NetworkAdapter*>* list = reinterpret_cast<std::vector<NetworkAdapter*>*>(aList);
    ASSERT(list != NULL);
    return (OhNetHandleNetworkAdapter)(*list)[aIndex];
}

void STDCALL OhNetNetworkAdapterListDestroy(OhNetHandleNetworkAdapterList aList)
{
    std::vector<NetworkAdapter*>* list = reinterpret_cast<std::vector<NetworkAdapter*>*>(aList);
    UpnpLibrary::DestroyNetworkAdapterList(list);
}

void STDCALL OhNetSetCurrentSubnet(uint32_t aSubnet)
{
    UpnpLibrary::SetCurrentSubnet(aSubnet);
}

OhNetHandleNetworkAdapter STDCALL OhNetCurrentSubnetAdapter(const char* aCookie)
{
    return (OhNetHandleNetworkAdapter)UpnpLibrary::CurrentSubnetAdapter(aCookie);
}

void STDCALL OhNetRefreshNetworkAdapterList()
{
    UpnpLibrary::RefreshNetworkAdapterList();
}

void STDCALL OhNetFreeExternal(void* aPtr)
{
    OhNetCallbackFreeExternal cb = gEnv->InitParams()->FreeExternal();
    if (cb != NULL) {
        cb(aPtr);
    }
    else {
        free(aPtr);
    }
}

void STDCALL OhNetDebugSetLevel(uint32_t aLevel)
{
    Debug::SetLevel(aLevel);
}

void STDCALL OhNetAbortProcess()
{
    Os::Quit(gEnv->OsCtx());
}
