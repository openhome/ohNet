#include <C/OhNet.h>
#include <OhNet.h>
#include <Functor.h>
#include <FunctorMsg.h>
#include <Stack.h>

#include <stdlib.h>

using namespace OpenHome;
using namespace OpenHome::Net;

int32_t OhNetLibraryInitialise(OhNetHandleInitParams aInitParams)
{
    if (Stack::IsInitialised()) {
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

int32_t OhNetLibraryInitialiseMinimal(OhNetHandleInitParams aInitParams)
{
    if (Stack::IsInitialised()) {
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

void OhNetLibraryClose()
{
    UpnpLibrary::Close();
}

void OhNetFree(void* aPtr)
{
    free(aPtr);
}

OhNetHandleInitParams OhNetInitParamsCreate()
{
    return (OhNetHandleInitParams)InitialisationParams::Create();
}

void OhNetInitParamsDestroy(OhNetHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    delete ip;
}

void OhNetInitParamsSetLogOutput(OhNetHandleInitParams aParams, OhNetCallbackMsg aCallback, void* aPtr)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    FunctorMsg functor = MakeFunctorMsgC(aPtr, aCallback);
    ip->SetLogOutput(functor);
}

void OhNetInitParamsSetFatalErrorHandler(OhNetHandleInitParams aParams, OhNetCallbackMsg aCallback, void* aPtr)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    FunctorMsg functor = MakeFunctorMsgC(aPtr, aCallback);
    ip->SetFatalErrorHandler(functor);
}

void OhNetInitParamsSetAsyncBeginHandler(OhNetHandleInitParams aParams, OhNetCallbackAsync aCallback, void* aPtr)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    ip->SetAsyncBeginHandler(functor);
}

void OhNetInitParamsSetAsyncEndHandler(OhNetHandleInitParams aParams, OhNetCallbackAsync aCallback, void* aPtr)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    ip->SetAsyncEndHandler(functor);
}

void OhNetInitParamsSetAsyncErrorHandler(OhNetHandleInitParams aParams, OhNetCallbackAsync aCallback, void* aPtr)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    ip->SetAsyncErrorHandler(functor);
}

void OhNetInitParamsSetSubnetListChangedListener(OhNetHandleInitParams aParams, OhNetCallback aCallback, void* aPtr)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    Functor functor = MakeFunctor(aPtr, aCallback);
    ip->SetSubnetListChangedListener(functor);
}

void OhNetInitParamsSetTcpConnectTimeout(OhNetHandleInitParams aParams, uint32_t aTimeoutMs)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    ip->SetTcpConnectTimeout(aTimeoutMs);
}

void OhNetInitParamsSetMsearchTime(OhNetHandleInitParams aParams, uint32_t aSecs)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    ip->SetMsearchTime(aSecs);
}

void OhNetInitParamsSetMsearchTtl(OhNetHandleInitParams aParams, uint32_t aTtl)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    ip->SetMsearchTtl(aTtl);
}

void OhNetInitParamsSetNumEventSessionThreads(OhNetHandleInitParams aParams, uint32_t aNumThreads)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    ip->SetNumEventSessionThreads(aNumThreads);
}

void OhNetInitParamsSetNumXmlFetcherThreads(OhNetHandleInitParams aParams, uint32_t aNumThreads)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    ip->SetNumXmlFetcherThreads(aNumThreads);
}

void OhNetInitParamsSetNumActionInvokerThreads(OhNetHandleInitParams aParams, uint32_t aNumThreads)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    ip->SetNumActionInvokerThreads(aNumThreads);
}

void OhNetInitParamsSetNumInvocations(OhNetHandleInitParams aParams, uint32_t aNumInvocations)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    ip->SetNumInvocations(aNumInvocations);
}

void OhNetInitParamsSetNumSubscriberThreads(OhNetHandleInitParams aParams, uint32_t aNumThreads)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    ip->SetNumSubscriberThreads(aNumThreads);
}

void OhNetInitParamsSetPendingSubscriptionTimeout(OhNetHandleInitParams aParams, uint32_t aTimeoutMs)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    ip->SetPendingSubscriptionTimeout(aTimeoutMs);
}

void OhNetInitParamsSetFreeExternalCallback(OhNetHandleInitParams aParams, OhNetCallbackFreeExternal aCallback)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    ip->SetFreeExternalCallback(aCallback);
}

void OhNetInitParamsSetUseLoopbackNetworkAdapter(OhNetHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    ip->SetUseLoopbackNetworkAdapter();
}

void OhNetInitParamsSetDvMaxUpdateTime(OhNetHandleInitParams aParams, uint32_t aSecs)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    ip->SetDvMaxUpdateTime(aSecs);
}

void OhNetInitParamsSetDvNumServerThreads(OhNetHandleInitParams aParams, uint32_t aNumThreads)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
	ip->SetDvNumServerThreads(aNumThreads);
}

void OhNetInitParamsSetDvNumPublisherThreads(OhNetHandleInitParams aParams, uint32_t aNumThreads)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
	ip->SetDvNumPublisherThreads(aNumThreads);
}

void OhNetInitParamsSetDvNumWebSocketThreads(OhNetHandleInitParams aParams, uint32_t aNumThreads)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
	ip->SetDvNumWebSocketThreads(aNumThreads);
}

void OhNetInitParamsSetDvWebSocketPort(OhNetHandleInitParams aParams, uint32_t aPort)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
	ip->SetDvWebSocketPort(aPort);
}

void OhNetInitParamsSetDvEnableBonjour(OhNetHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    ip->SetDvEnableBonjour();
}

uint32_t OhNetInitParamsTcpConnectTimeoutMs(OhNetHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    return ip->TcpConnectTimeoutMs();
}

uint32_t OhNetInitParamsMsearchTimeSecs(OhNetHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    return ip->MsearchTimeSecs();
}

uint32_t OhNetInitParamsMsearchTtl(OhNetHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    return ip->MsearchTtl();
}

uint32_t OhNetInitParamsNumEventSessionThreads(OhNetHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    return ip->NumEventSessionThreads();
}

uint32_t OhNetInitParamsNumXmlFetcherThreads(OhNetHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    return ip->NumXmlFetcherThreads();
}

uint32_t OhNetInitParamsNumActionInvokerThreads(OhNetHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    return ip->NumActionInvokerThreads();
}

uint32_t OhNetInitParamsNumInvocations(OhNetHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    return ip->NumInvocations();
}

uint32_t OhNetInitParamsNumSubscriberThreads(OhNetHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    return ip->NumSubscriberThreads();
}

uint32_t OhNetInitParamsPendingSubscriptionTimeoutMs(OhNetHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    return ip->PendingSubscriptionTimeoutMs();
}

uint32_t OhNetInitParamsDvMaxUpdateTimeSecs(OhNetHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    return ip->DvMaxUpdateTimeSecs();
}

uint32_t OhNetInitParamsDvNumServerThreads(OhNetHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
	return ip->DvNumServerThreads();
}

uint32_t OhNetInitParamsDvNumPublisherThreads(OhNetHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
	return ip->DvNumPublisherThreads();
}

uint32_t OhNetInitParamsDvNumWebSocketThreads(OhNetHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
	return ip->DvNumWebSocketThreads();
}

uint32_t OhNetInitParamsDvWebSocketPort(OhNetHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
	return ip->DvWebSocketPort();
}

uint32_t OhNetInitParamsDvIsBonjourEnabled(OhNetHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
	return (ip->DvIsBonjourEnabled()? 1 : 0);
}

TIpAddress OhNetNetworkAdapterAddress(OhNetHandleNetworkAdapter aNif)
{
    NetworkAdapter* nif = reinterpret_cast<NetworkAdapter*>(aNif);
    ASSERT(nif != NULL);
    return nif->Address();
}

TIpAddress OhNetNetworkAdapterSubnet(OhNetHandleNetworkAdapter aNif)
{
    NetworkAdapter* nif = reinterpret_cast<NetworkAdapter*>(aNif);
    ASSERT(nif != NULL);
    return nif->Subnet();
}

const char* OhNetNetworkAdapterName(OhNetHandleNetworkAdapter aNif)
{
    NetworkAdapter* nif = reinterpret_cast<NetworkAdapter*>(aNif);
    ASSERT(nif != NULL);
    return nif->Name();
}

char* OhNetNetworkAdapterFullName(OhNetHandleNetworkAdapter aNif)
{
    NetworkAdapter* nif = reinterpret_cast<NetworkAdapter*>(aNif);
    ASSERT(nif != NULL);
    return nif->FullName();
}

OhNetHandleNetworkAdapterList OhNetSubnetListCreate()
{
    return (OhNetHandleNetworkAdapterList)UpnpLibrary::CreateSubnetList();
}

uint32_t OhNetSubnetListSize(OhNetHandleNetworkAdapterList aList)
{
    std::vector<NetworkAdapter*>* list = reinterpret_cast<std::vector<NetworkAdapter*>*>(aList);
    ASSERT(list != NULL);
    return (TUint)list->size();
}

OhNetHandleNetworkAdapter OhNetSubnetAt(OhNetHandleNetworkAdapterList aList, uint32_t aIndex)
{
    std::vector<NetworkAdapter*>* list = reinterpret_cast<std::vector<NetworkAdapter*>*>(aList);
    ASSERT(list != NULL);
    return (OhNetHandleNetworkAdapter)(*list)[aIndex];
}

void OhNetSubnetListDestroy(OhNetHandleNetworkAdapterList aList)
{
    std::vector<NetworkAdapter*>* list = reinterpret_cast<std::vector<NetworkAdapter*>*>(aList);
    UpnpLibrary::DestroySubnetList(list);
}

void OhNetSetCurrentSubnet(OhNetHandleNetworkAdapter aSubnet)
{
    NetworkAdapter* nif = reinterpret_cast<NetworkAdapter*>(aSubnet);
    UpnpLibrary::SetCurrentSubnet(nif->Subnet());
}

OhNetHandleNetworkAdapter OhNetCurrentSubnetAdapter()
{
    return (OhNetHandleNetworkAdapter)UpnpLibrary::CurrentSubnetAdapter();
}

void OhNetFreeExternal(void* aPtr)
{
	OhNetCallbackFreeExternal cb = Stack::InitParams().FreeExternal();
	if (cb != NULL) {
		cb(aPtr);
	}
	else {
		free(aPtr);
	}
}
