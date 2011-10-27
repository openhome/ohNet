#include <OpenHome/Net/Core/OhNet.h>
#include <OpenHome/Net/Private/Stack.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/NetworkAdapterList.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Private/Network.h>

using namespace OpenHome;
using namespace OpenHome::Net;

// NetworkAdapter

NetworkAdapter::NetworkAdapter(TIpAddress aAddress, TIpAddress aNetMask, const char* aName)
    : iRefCount(1)
    , iAddress(aAddress)
    , iNetMask(aNetMask)
    , iName(aName)
{
    Stack::AddObject(this);
}

NetworkAdapter::~NetworkAdapter()
{
    Stack::RemoveObject(this);
}

void NetworkAdapter::AddRef()
{
    Stack::Mutex().Wait();
    iRefCount++;
    Stack::Mutex().Signal();
}

void NetworkAdapter::RemoveRef()
{
    Stack::Mutex().Wait();
    TBool dead = (--iRefCount == 0);
    Stack::Mutex().Signal();
    if (dead) {
        delete this;
    }
}

TIpAddress NetworkAdapter::Address() const
{
    return iAddress;
}

TIpAddress NetworkAdapter::Subnet() const
{
    return (iAddress & iNetMask);
}

TIpAddress NetworkAdapter::Mask() const
{
    return iNetMask;
}

bool NetworkAdapter::ContainsAddress(TIpAddress aAddress)
{
    return ((aAddress&iNetMask) == Subnet());
}

const char* NetworkAdapter::Name() const
{
    return (const char*)iName.Ptr();
}

char* NetworkAdapter::FullName() const
{
    TUint len = Endpoint::kMaxAddressBytes + 4 + iName.Bytes();
    Bwh buf(len);
    Endpoint ep(0, iAddress);
    ep.AppendAddress(buf);
    buf.Append(' ');
    buf.Append('(');
    buf.Append(iName);
    buf.Append(')');
    buf.PtrZ();
    Brhz buf2;
    buf.TransferTo(buf2);
    return (char*)buf2.Transfer();
}

void NetworkAdapter::ListObjectDetails() const
{
    Endpoint ep(0, iAddress);
    Endpoint::AddressBuf buf;
    ep.AppendAddress(buf);
    Log::Print("  NetworkAdapter: addr=%p, ip=%s", this, buf.Ptr());
    ep.SetAddress(iNetMask);
    buf.SetBytes(0);
    ep.AppendAddress(buf);
    Log::Print(", netmask=%s, name=%s\n", buf.Ptr(), iName.Ptr());
}


// InitialisationParams

class OpenHome::Net::DefaultLogger
{
public:
    void Log(const char* aMsg);
};

void OpenHome::Net::DefaultLogger::Log(const char* aMsg)
{
    fprintf(stdout, "%s", aMsg);
    fflush(stdout);
}

class OpenHome::Net::DefaultAsyncHandler : private IAsyncOutput
{
public:
    void LogError(IAsync& aAsync);
    virtual ~DefaultAsyncHandler() {}
private:
    void Output(const TChar* aKey, const TChar* aValue);
};

void OpenHome::Net::DefaultAsyncHandler::LogError(IAsync& aAsync)
{
    Log::Print("------------------------------\n");
    aAsync.Output(*this);
    Log::Print("------------------------------\n");
}

void OpenHome::Net::DefaultAsyncHandler::Output(const TChar* aKey, const TChar* aValue)
{
    Log::Print("%s:  %s\n", aKey, aValue);
}

InitialisationParams* InitialisationParams::Create()
{
    return new InitialisationParams();
}

InitialisationParams::~InitialisationParams()
{
    delete iDefaultLogger;
    delete iDefaultAsyncHandler;
}

void InitialisationParams::SetLogOutput(FunctorMsg aLogOutput)
{
    iLogOutput = aLogOutput;
}

void InitialisationParams::SetFatalErrorHandler(FunctorMsg aFunctor)
{
    ASSERT(aFunctor);
    iFatalErrorHandler = aFunctor;
}

void InitialisationParams::SetAsyncBeginHandler(FunctorAsync aHandler)
{
    iAsyncBeginHandler = aHandler;
}

void InitialisationParams::SetAsyncEndHandler(FunctorAsync aHandler)
{
    iAsyncEndHandler = aHandler;
}

void InitialisationParams::SetAsyncErrorHandler(FunctorAsync aHandler)
{
    iAsyncErrorHandler = aHandler;
}

void InitialisationParams::SetSubnetListChangedListener(Functor aFunctor)
{
    iSubnetListChangedListener = aFunctor;
}

void InitialisationParams::SetSubnetAddedListener(FunctorNetworkAdapter aFunctor)
{
    iSubnetAddedListener = aFunctor;
}

void InitialisationParams::SetSubnetRemovedListener(FunctorNetworkAdapter aFunctor)
{
    iSubnetRemovedListener = aFunctor;
}

void InitialisationParams::SetNetworkAdapterChangedListener(FunctorNetworkAdapter aFunctor)
{
    iNetworkAdapterChangedListener = aFunctor;
}

void InitialisationParams::SetTcpConnectTimeout(uint32_t aTimeoutMs)
{
    ASSERT(aTimeoutMs > 0);
    iTcpConnectTimeoutMs = aTimeoutMs;
}

void InitialisationParams::SetMsearchTime(uint32_t aSecs)
{
    ASSERT(aSecs >= 1 && aSecs <= 5);
    iMsearchTimeSecs = aSecs;
}

void InitialisationParams::SetMsearchTtl(uint32_t aTtl)
{
    ASSERT(aTtl > 0);
    iMsearchTtl = aTtl;
}

void InitialisationParams::SetNumEventSessionThreads(uint32_t aNumThreads)
{
    ASSERT(aNumThreads > 0 && aNumThreads < 10);
    iNumEventSessionThreads = aNumThreads;
}

void InitialisationParams::SetNumXmlFetcherThreads(uint32_t aNumThreads)
{
    ASSERT(aNumThreads > 0 && aNumThreads < 10);
    iNumXmlFetcherThreads = aNumThreads;
}

void InitialisationParams::SetNumActionInvokerThreads(uint32_t aNumThreads)
{
    ASSERT(aNumThreads > 0 && aNumThreads < 100);
    iNumActionInvokerThreads = aNumThreads;
}

void InitialisationParams::SetNumInvocations(uint32_t aNumInvocations)
{
    ASSERT(aNumInvocations > 0);
    iNumInvocations = aNumInvocations;
}

void InitialisationParams::SetNumSubscriberThreads(uint32_t aNumThreads)
{
    ASSERT(aNumThreads > 0 && aNumThreads < 10);
    iNumSubscriberThreads = aNumThreads;
}

void InitialisationParams::SetPendingSubscriptionTimeout(uint32_t aTimeoutMs)
{
    ASSERT(aTimeoutMs > 0);
    iPendingSubscriptionTimeoutMs = aTimeoutMs;
}

void InitialisationParams::SetFreeExternalCallback(OhNetCallbackFreeExternal aCallback)
{
    iFreeExternal = aCallback;
}

void InitialisationParams::SetUseLoopbackNetworkAdapter()
{
    iUseLoopbackNetworkAdapter = true;
}

void InitialisationParams::SetDvMaxUpdateTime(uint32_t aSecs)
{
	iDvMaxUpdateTimeSecs = aSecs;
}

void InitialisationParams::SetDvNumServerThreads(uint32_t aNumThreads)
{
    ASSERT(aNumThreads > 0 && aNumThreads < 100);
    iDvNumServerThreads = aNumThreads;
}

void InitialisationParams::SetDvNumPublisherThreads(uint32_t aNumThreads)
{
    ASSERT(aNumThreads > 0 && aNumThreads < 100);
    iDvNumPublisherThreads = aNumThreads;
}

void InitialisationParams::SetDvNumWebSocketThreads(uint32_t aNumThreads)
{
    ASSERT(aNumThreads >= 0 && aNumThreads < 100);
    iDvNumWebSocketThreads = aNumThreads;
}

void InitialisationParams::SetDvWebSocketPort(TUint aPort)
{
    iDvWebSocketPort = aPort;
}

void InitialisationParams::SetDvEnableBonjour()
{
    iEnableBonjour = true;
}

FunctorMsg& InitialisationParams::LogOutput()
{
    return iLogOutput;
}

FunctorMsg& InitialisationParams::FatalErrorHandler()
{
    return iFatalErrorHandler;
}

FunctorAsync& InitialisationParams::AsyncBeginHandler()
{
    return iAsyncBeginHandler;
}

FunctorAsync& InitialisationParams::AsyncEndHandler()
{
    return iAsyncEndHandler;
}

FunctorAsync& InitialisationParams::AsyncErrorHandler()
{
    return iAsyncErrorHandler;
}

Functor& InitialisationParams::SubnetListChangedListener()
{
    return iSubnetListChangedListener;
}

FunctorNetworkAdapter& InitialisationParams::SubnetAddedListener()
{
    return iSubnetAddedListener;
}

FunctorNetworkAdapter& InitialisationParams::SubnetRemovedListener()
{
    return iSubnetRemovedListener;
}

FunctorNetworkAdapter& InitialisationParams::NetworkAdapterChangedListener()
{
    return iNetworkAdapterChangedListener;
}

uint32_t InitialisationParams::TcpConnectTimeoutMs() const
{
    return iTcpConnectTimeoutMs;
}

uint32_t InitialisationParams::MsearchTimeSecs() const
{
    return iMsearchTimeSecs;
}

uint32_t InitialisationParams::MsearchTtl() const
{
    return iMsearchTtl;
}

uint32_t InitialisationParams::NumEventSessionThreads() const
{
    return iNumEventSessionThreads;
}

uint32_t InitialisationParams::NumXmlFetcherThreads() const
{
    return iNumXmlFetcherThreads;
}

uint32_t InitialisationParams::NumActionInvokerThreads() const
{
    return iNumActionInvokerThreads;
}

uint32_t InitialisationParams::NumInvocations() const
{
    return iNumInvocations;
}

uint32_t InitialisationParams::NumSubscriberThreads() const
{
    return iNumSubscriberThreads;
}

uint32_t InitialisationParams::PendingSubscriptionTimeoutMs() const
{
    return iPendingSubscriptionTimeoutMs;
}

OhNetCallbackFreeExternal InitialisationParams::FreeExternal() const
{
    return iFreeExternal;
}

bool InitialisationParams::UseLoopbackNetworkAdapter() const
{
    return iUseLoopbackNetworkAdapter;
}

uint32_t InitialisationParams::DvMaxUpdateTimeSecs() const
{
	return iDvMaxUpdateTimeSecs;
}

uint32_t InitialisationParams::DvNumServerThreads() const
{
    return iDvNumServerThreads;
}

uint32_t InitialisationParams::DvNumPublisherThreads() const
{
	return iDvNumPublisherThreads;
}

uint32_t InitialisationParams::DvNumWebSocketThreads() const
{
	return iDvNumWebSocketThreads;
}

uint32_t InitialisationParams::DvWebSocketPort() const
{
    return iDvWebSocketPort;
}

bool InitialisationParams::DvIsBonjourEnabled() const
{
    return iEnableBonjour;
}

InitialisationParams::InitialisationParams()
    : iTcpConnectTimeoutMs(500)
    , iMsearchTimeSecs(3)
    , iMsearchTtl(2)
    , iNumEventSessionThreads(4)
    , iNumXmlFetcherThreads(4)
    , iNumActionInvokerThreads(4)
    , iNumInvocations(20)
    , iNumSubscriberThreads(4)
    , iPendingSubscriptionTimeoutMs(2000)
    , iFreeExternal(NULL)
    , iUseLoopbackNetworkAdapter(false)
	, iDvMaxUpdateTimeSecs(1800)
    , iDvNumServerThreads(4)
	, iDvNumPublisherThreads(4)
    , iDvNumWebSocketThreads(0)
    , iDvWebSocketPort(0)
    , iEnableBonjour(false)
{
    iDefaultLogger = new DefaultLogger;
    FunctorMsg functor = MakeFunctorMsg(*iDefaultLogger, &OpenHome::Net::DefaultLogger::Log);
    SetLogOutput(functor);
    iDefaultAsyncHandler = new DefaultAsyncHandler;
    iAsyncErrorHandler = MakeFunctorAsync(*iDefaultAsyncHandler, &DefaultAsyncHandler::LogError);
    iFatalErrorHandler = MakeFunctorMsg(*this, &InitialisationParams::FatalErrorHandlerDefault);
}

void InitialisationParams::FatalErrorHandlerDefault(const char* aMsg)
{
    Log::Print(aMsg);
    Os::Quit();
}


// Entrypoint

static void BaseInit(InitialisationParams* aInitParams)
{
    Log::RegisterOutput(aInitParams->LogOutput());
    if (0 != OpenHome::Os::Create()) {
        throw std::bad_alloc();
    }
}

void UpnpLibrary::Initialise(InitialisationParams* aInitParams)
{
    BaseInit(aInitParams);
    new Stack(aInitParams);
    //Debug::SetLevel(Debug::kError);
}

void UpnpLibrary::InitialiseMinimal(InitialisationParams* aInitParams)
{
    BaseInit(aInitParams);
    new Stack();
}

void UpnpLibrary::Close()
{
    Stack::Destroy();
    OpenHome::Os::Destroy();
}

std::vector<NetworkAdapter*>* UpnpLibrary::CreateSubnetList()
{
    return Stack::NetworkAdapterList().CreateSubnetList();
}

void UpnpLibrary::DestroySubnetList(std::vector<NetworkAdapter*>* aSubnetList)
{
    if (aSubnetList == NULL) {
        return;
    }
    for (size_t i=0; i<aSubnetList->size(); i++) {
        (*aSubnetList)[i]->RemoveRef();
    }
    delete aSubnetList;
}

void UpnpLibrary::SetCurrentSubnet(TIpAddress aSubnet)
{
    Stack::NetworkAdapterList().SetCurrentSubnet(aSubnet);
}

NetworkAdapter* UpnpLibrary::CurrentSubnetAdapter()
{
    return Stack::NetworkAdapterList().CurrentAdapter();
}
