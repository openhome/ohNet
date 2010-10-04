#include <C/Zapp.h>
#include <Zapp.h>
#include <Functor.h>
#include <FunctorMsg.h>
#include <Stack.h>

#include <stdlib.h>

using namespace Zapp;

int32_t ZappLibraryInitialise(ZappHandleInitParams aInitParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aInitParams);
    try {
        UpnpLibrary::Initialise(ip);
    }
    catch(...) {
        return -1;
    }
    return 0;
}

int32_t ZappLibraryInitialiseMinimal(ZappHandleInitParams aInitParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aInitParams);
    try {
        UpnpLibrary::InitialiseMinimal(ip);
    }
    catch(...) {
        return -1;
    }
    return 0;
}

void ZappLibraryClose()
{
    UpnpLibrary::Close();
}

void ZappFree(void* aPtr)
{
    free(aPtr);
}

ZappHandleInitParams ZappInitParamsCreate()
{
    return (ZappHandleInitParams)InitialisationParams::Create();
}

void ZappInitParamsDestroy(ZappHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    delete ip;
}

void ZappInitParamsSetLogOutput(ZappHandleInitParams aParams, ZappCallbackMsg aCallback, void* aPtr)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    FunctorMsg functor = MakeFunctorMsgC(aPtr, aCallback);
    ip->SetLogOutput(functor);
}

void ZappInitParamsSetFatalErrorHandler(ZappHandleInitParams aParams, ZappCallbackMsg aCallback, void* aPtr)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    FunctorMsg functor = MakeFunctorMsgC(aPtr, aCallback);
    ip->SetFatalErrorHandler(functor);
}

void ZappInitParamsSetAsyncBeginHandler(ZappHandleInitParams aParams, ZappCallbackAsync aCallback, void* aPtr)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    ip->SetAsyncBeginHandler(functor);
}

void ZappInitParamsSetAsyncEndHandler(ZappHandleInitParams aParams, ZappCallbackAsync aCallback, void* aPtr)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    ip->SetAsyncEndHandler(functor);
}

void ZappInitParamsSetAsyncErrorHandler(ZappHandleInitParams aParams, ZappCallbackAsync aCallback, void* aPtr)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    ip->SetAsyncErrorHandler(functor);
}

void ZappInitParamsSetDefaultSubnet(ZappHandleInitParams aParams, TIpAddress aSubnet)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    ip->SetDefaultSubnet(aSubnet);
}

void ZappInitParamsSetSubnetChangedListener(ZappHandleInitParams aParams, ZappCallback aCallback, void* aPtr)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    Functor functor = MakeFunctor(aPtr, aCallback);
    ip->SetSubnetChangedListener(functor);
}

void ZappInitParamsSetTcpConnectTimeout(ZappHandleInitParams aParams, uint32_t aTimeoutMs)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    ip->SetTcpConnectTimeout(aTimeoutMs);
}

void ZappInitParamsSetMsearchTime(ZappHandleInitParams aParams, uint32_t aSecs)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    ip->SetMsearchTime(aSecs);
}

void ZappInitParamsSetMsearchTtl(ZappHandleInitParams aParams, uint32_t aTtl)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    ip->SetMsearchTtl(aTtl);
}

void ZappInitParamsSetNumEventSessionThreads(ZappHandleInitParams aParams, uint32_t aNumThreads)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    ip->SetNumEventSessionThreads(aNumThreads);
}

void ZappInitParamsSetNumXmlFetcherThreads(ZappHandleInitParams aParams, uint32_t aNumThreads)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    ip->SetNumXmlFetcherThreads(aNumThreads);
}

void ZappInitParamsSetNumActionInvokerThreads(ZappHandleInitParams aParams, uint32_t aNumThreads)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    ip->SetNumActionInvokerThreads(aNumThreads);
}

void ZappInitParamsSetNumInvocations(ZappHandleInitParams aParams, uint32_t aNumInvocations)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    ip->SetNumInvocations(aNumInvocations);
}

void ZappInitParamsSetNumSubscriberThreads(ZappHandleInitParams aParams, uint32_t aNumThreads)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    ip->SetNumSubscriberThreads(aNumThreads);
}

void ZappInitParamsSetPendingSubscriptionTimeout(ZappHandleInitParams aParams, uint32_t aTimeoutMs)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    ip->SetPendingSubscriptionTimeout(aTimeoutMs);
}

void ZappInitParamsSetFreeExternalCallback(ZappHandleInitParams aParams, ZappCallbackFreeExternal aCallback)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    ip->SetFreeExternalCallback(aCallback);
}

void ZappInitParamsSetDvMaxUpdateTime(ZappHandleInitParams aParams, uint32_t aSecs)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    ip->SetDvMaxUpdateTime(aSecs);
}

void ZappInitParamsSetDvNumPublisherThreads(ZappHandleInitParams aParams, uint32_t aNumThreads)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
	ip->SetDvNumPublisherThreads(aNumThreads);
}

uint32_t ZappInitParamsTcpConnectTimeoutMs(ZappHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    return ip->TcpConnectTimeoutMs();
}

uint32_t ZappInitParamsMsearchTimeSecs(ZappHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    return ip->MsearchTimeSecs();
}

uint32_t ZappInitParamsMsearchTtl(ZappHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    return ip->MsearchTtl();
}

uint32_t ZappInitParamsNumEventSessionThreads(ZappHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    return ip->NumEventSessionThreads();
}

uint32_t ZappInitParamsNumXmlFetcherThreads(ZappHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    return ip->NumXmlFetcherThreads();
}

uint32_t ZappInitParamsNumActionInvokerThreads(ZappHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    return ip->NumActionInvokerThreads();
}

uint32_t ZappInitParamsNumInvocations(ZappHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    return ip->NumInvocations();
}

uint32_t ZappInitParamsNumSubscriberThreads(ZappHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    return ip->NumSubscriberThreads();
}

uint32_t ZappInitParamsPendingSubscriptionTimeoutMs(ZappHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    return ip->PendingSubscriptionTimeoutMs();
}

uint32_t ZappInitParamsDvMaxUpdateTimeSecs(ZappHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    return ip->DvMaxUpdateTimeSecs();
}

uint32_t ZappInitParamsDvNumPublisherThreads(ZappHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
	return ip->DvNumPublisherThreads();
}

TIpAddress ZappNetworkInterfaceAddress(ZappHandleNetworkInterface aNif)
{
    NetworkInterface* nif = reinterpret_cast<NetworkInterface*>(aNif);
    ASSERT(nif != NULL);
    return nif->Address();
}

TIpAddress ZappNetworkInterfaceSubnet(ZappHandleNetworkInterface aNif)
{
    NetworkInterface* nif = reinterpret_cast<NetworkInterface*>(aNif);
    ASSERT(nif != NULL);
    return nif->Subnet();
}

const char* ZappNetworkInterfaceName(ZappHandleNetworkInterface aNif)
{
    NetworkInterface* nif = reinterpret_cast<NetworkInterface*>(aNif);
    ASSERT(nif != NULL);
    return nif->Name();
}

ZappHandleNetworkInterfaceList ZappSubnetListCreate()
{
    return (ZappHandleNetworkInterfaceList)UpnpLibrary::SubnetList();
}

uint32_t ZappSubnetListSize(ZappHandleNetworkInterfaceList aList)
{
    std::vector<NetworkInterface*>* list = reinterpret_cast<std::vector<NetworkInterface*>*>(aList);
    ASSERT(list != NULL);
    return list->size();
}

ZappHandleNetworkInterface ZappSubnetAt(ZappHandleNetworkInterfaceList aList, uint32_t aIndex)
{
    std::vector<NetworkInterface*>* list = reinterpret_cast<std::vector<NetworkInterface*>*>(aList);
    ASSERT(list != NULL);
    return (ZappHandleNetworkInterface)(*list)[aIndex];
}

void ZappSubnetListDestroy(ZappHandleNetworkInterfaceList aList)
{
    std::vector<NetworkInterface*>* list = reinterpret_cast<std::vector<NetworkInterface*>*>(aList);
    if (list != NULL) {
        for (uint32_t i=0; i<list->size(); i++) {
            delete (*list)[i];
        }
        delete list;
    }
}

void ZappSetCurrentSubnet(ZappHandleNetworkInterface aSubnet)
{
    NetworkInterface* nif = reinterpret_cast<NetworkInterface*>(aSubnet);
    UpnpLibrary::SetCurrentSubnet(*nif);
}

void ZappSetDefaultSubnet()
{
    UpnpLibrary::SetDefaultSubnet();
}

void ZappFreeExternal(void* aPtr)
{
	ZappCallbackFreeExternal cb = Stack::InitParams().FreeExternal();
	if (cb != NULL) {
		cb(aPtr);
	}
	else {
		free(aPtr);
	}
}
