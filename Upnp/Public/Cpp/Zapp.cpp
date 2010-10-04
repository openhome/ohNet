#include <Zapp.h>
#include <Stack.h>
#include <Standard.h>
#include <Printer.h>
#include <NetworkInterfaceList.h>
#include <Debug.h>

using namespace Zapp;

// NetworkInterface

NetworkInterface::NetworkInterface(TIpAddress aAddress, TIpAddress aNetMask, const char* aName)
    : iAddress(aAddress)
    , iNetMask(aNetMask)
    , iName(aName)
{
}

NetworkInterface* NetworkInterface::Clone() const
{
    return new NetworkInterface(iAddress, iNetMask, (const char*)iName.Ptr());
}

TIpAddress NetworkInterface::Address() const
{
    return iAddress;
}

TIpAddress NetworkInterface::Subnet() const
{
    return (iAddress & iNetMask);
}

bool NetworkInterface::ContainsAddress(TIpAddress aAddress)
{
    return ((aAddress&iNetMask) == Subnet());
}

const char* NetworkInterface::Name() const
{
    return (const char*)iName.Ptr();
}


// InitialisationParams

class Zapp::DefaultLogger
{
public:
    void Log(const char* aMsg);
};

void Zapp::DefaultLogger::Log(const char* aMsg)
{
    fprintf(stdout, "%s", aMsg);
    fflush(stdout);
}

class Zapp::DefaultAsyncHandler : private IAsyncOutput
{
public:
    void LogError(IAsync& aAsync);
private:
    void Output(const TChar* aKey, const TChar* aValue);
};

void Zapp::DefaultAsyncHandler::LogError(IAsync& aAsync)
{
    Log::Print("------------------------------\n");
    aAsync.Output(*this);
    Log::Print("------------------------------\n");
}

void Zapp::DefaultAsyncHandler::Output(const TChar* aKey, const TChar* aValue)
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

void InitialisationParams::SetDefaultSubnet(TIpAddress aSubnet)
{
    iDefaultSubnet = aSubnet;
}

void InitialisationParams::SetSubnetChangedListener(Functor aFunctor)
{
    iSubnetChangedListener = aFunctor;
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
    ASSERT(aNumThreads > 0 && aNumThreads < 10);
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

void InitialisationParams::SetFreeExternalCallback(ZappCallbackFreeExternal aCallback)
{
    iFreeExternal = aCallback;
}

void InitialisationParams::SetDvMaxUpdateTime(uint32_t aSecs)
{
	iDvMaxUpdateTimeSecs = aSecs;
}

void InitialisationParams::SetDvNumPublisherThreads(uint32_t aNumThreads)
{
    ASSERT(aNumThreads > 0 && aNumThreads < 100);
    iDvNumPublisherThreads = aNumThreads;
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

TIpAddress InitialisationParams::DefaultSubnet() const
{
    return iDefaultSubnet;
}

Functor& InitialisationParams::SubnetChangedListener()
{
    return iSubnetChangedListener;
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

ZappCallbackFreeExternal InitialisationParams::FreeExternal() const
{
    return iFreeExternal;
}

uint32_t InitialisationParams::DvMaxUpdateTimeSecs() const
{
	return iDvMaxUpdateTimeSecs;
}

uint32_t InitialisationParams::DvNumPublisherThreads() const
{
	return iDvNumPublisherThreads;
}

InitialisationParams::InitialisationParams()
    : iDefaultSubnet(0)
    , iTcpConnectTimeoutMs(500)
    , iMsearchTimeSecs(3)
    , iMsearchTtl(2)
    , iNumEventSessionThreads(4)
    , iNumXmlFetcherThreads(4)
    , iNumActionInvokerThreads(4)
    , iNumInvocations(20)
    , iNumSubscriberThreads(4)
    , iPendingSubscriptionTimeoutMs(2000)
    , iFreeExternal(NULL)
	, iDvMaxUpdateTimeSecs(1800)
	, iDvNumPublisherThreads(4)
{
    iDefaultLogger = new DefaultLogger;
    FunctorMsg functor = MakeFunctorMsg(*iDefaultLogger, &Zapp::DefaultLogger::Log);
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

void UpnpLibrary::Initialise(InitialisationParams* aInitParams)
{
    UpnpLibrary::InitialiseMinimal(aInitParams);
    new Stack(aInitParams);
    //Debug::SetLevel(Debug::kEvent | Debug::kDvEvent);
}

void UpnpLibrary::InitialiseMinimal(InitialisationParams* aInitParams)
{
    Log::RegisterOutput(aInitParams->LogOutput());
    if (0 != Zapp::Os::Create()) {
        throw std::bad_alloc();
    }
}

void UpnpLibrary::Close()
{
    Stack::Destroy();
    Zapp::Os::Destroy();
}

std::vector<NetworkInterface*>* UpnpLibrary::SubnetList()
{
    return Stack::NetworkInterfaceList().CreateSubnetList();
}

void UpnpLibrary::SetCurrentSubnet(const NetworkInterface& aSubnet)
{
    Stack::NetworkInterfaceList().SetCurrentSubnet(aSubnet);
}

void UpnpLibrary::SetDefaultSubnet()
{
    Stack::NetworkInterfaceList().ClearCurrentSubnet();
}
