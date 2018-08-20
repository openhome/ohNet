#include <OpenHome/Net/Core/OhNet.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/NetworkAdapterList.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Net/Private/Globals.h>
#include <OpenHome/OsWrapper.h>

#include <string.h>

using namespace OpenHome;
using namespace OpenHome::Net;

// AutoNetworkAdapterRef
    
AutoNetworkAdapterRef::AutoNetworkAdapterRef(Environment& aEnv, const char* aCookie)
    : iCookie(aCookie)
{
    iAdapter = aEnv.NetworkAdapterList().CurrentAdapter(aCookie);
}

AutoNetworkAdapterRef::AutoNetworkAdapterRef(NetworkAdapter* aAdapter, const char* aCookie)
    : iAdapter(aAdapter)
    , iCookie(aCookie)
{
}

AutoNetworkAdapterRef::~AutoNetworkAdapterRef()
{
    if (iAdapter != NULL) {
        iAdapter->RemoveRef(iCookie);
    }
}

NetworkAdapter* AutoNetworkAdapterRef::Adapter()
{
    return iAdapter;
}

const NetworkAdapter* AutoNetworkAdapterRef::Adapter() const
{
    return iAdapter;
}


// NetworkAdapter

NetworkAdapter::NetworkAdapter(Environment& aEnv, TIpAddress aAddress, TIpAddress aNetMask,
                               TIpAddress aDhcp, TIpAddress aGateway,
                               const char* aName, const char* aCookie)
    : iEnv(&aEnv)
    , iRefCount(1)
    , iAddress(aAddress)
    , iNetMask(aNetMask)
    , iDhcpServer(aDhcp)
    , iGateway(aGateway)
    , iName(aName)
{
    iEnv->AddObject(this);
    iCookies.push_back(aCookie);
}

NetworkAdapter::~NetworkAdapter()
{
    iEnv->RemoveObject(this);
}

void NetworkAdapter::AddRef(const char* aCookie)
{
    iEnv->Mutex().Wait();
    iRefCount++;
    iCookies.push_back(aCookie);
    iEnv->Mutex().Signal();
}

void NetworkAdapter::RemoveRef(const char* aCookie)
{
    iEnv->Mutex().Wait();
    TBool dead = (--iRefCount == 0);
    TBool foundCookie = false;
    for (TUint i=0; i<(TUint)iCookies.size(); i++) {
        if (strcmp(iCookies[i], aCookie) == 0) {
            iCookies.erase(iCookies.begin() + i);
            foundCookie = true;
            break;
        }
    }
    ASSERT(foundCookie);
    iEnv->Mutex().Signal();
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

bool NetworkAdapter::ContainsAddress(TIpAddress aAddress) const
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

TBool NetworkAdapter::DhcpServerAddressAvailable() const
{
    return (iDhcpServer != 0);
}

TIpAddress NetworkAdapter::DhcpServerAddress() const
{
    return iDhcpServer;
}

TBool NetworkAdapter::GatewayAddressAvailable() const
{
    return (iGateway != 0);
}

TIpAddress NetworkAdapter::GatewayAddress() const
{
    return iGateway;
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
    Log::Print(", netmask=%s, name=%s, cookies={", buf.Ptr(), iName.Ptr());
    for (TUint i=0; (TUint)i<iCookies.size(); i++) {
        const char* cookie = ((iCookies[i] == NULL || strlen(iCookies[i]) == 0) ? "[none]" : iCookies[i]);
        Log::Print(" %s", cookie);
    }
    Log::Print(" }\n");
}


// InitialisationParams

class OpenHome::Net::DefaultLogger
{
public:
    void Log(const char* aMsg);
};

void OpenHome::Net::DefaultLogger::Log(const char* aMsg)
{
    Os::ConsoleWrite(aMsg);
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

void InitialisationParams::SetThreadExitHandler(Functor aFunctor)
{
    iThreadExitHandler = aFunctor;
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
    ASSERT(aNumThreads > 0);
    iNumEventSessionThreads = aNumThreads;
}

void InitialisationParams::SetNumXmlFetcherThreads(uint32_t aNumThreads)
{
    ASSERT(aNumThreads > 0);
    iNumXmlFetcherThreads = aNumThreads;
}

void InitialisationParams::SetNumActionInvokerThreads(uint32_t aNumThreads)
{
    ASSERT(aNumThreads > 0);
    iNumActionInvokerThreads = aNumThreads;
}

void InitialisationParams::SetNumInvocations(uint32_t aNumInvocations)
{
    ASSERT(aNumInvocations > 0);
    iNumInvocations = aNumInvocations;
}

void InitialisationParams::SetNumSubscriberThreads(uint32_t aNumThreads)
{
    ASSERT(aNumThreads > 0);
    iNumSubscriberThreads = aNumThreads;
}

void InitialisationParams::SetInvocationTimeout(uint32_t aMs)
{
    ASSERT(aMs > 0);
    iInvocationTimeoutMs = aMs;
}

void InitialisationParams::SetSubscriptionDuration(uint32_t aDurationSecs)
{
    ASSERT(aDurationSecs > 0);
    iSubscriptionDurationSecs = aDurationSecs;
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
    iUseLoopbackNetworkAdapter = ELoopbackUse;
}

void InitialisationParams::SetIncludeLoopbackNetworkAdapter()
{
    iUseLoopbackNetworkAdapter = ELoopbackInclude;
}

void InitialisationParams::SetDvMaxUpdateTime(uint32_t aSecs)
{
    iDvMaxUpdateTimeSecs = aSecs;
}

void InitialisationParams::SetDvNumServerThreads(uint32_t aNumThreads)
{
    ASSERT(aNumThreads > 0);
    iDvNumServerThreads = aNumThreads;
}

void InitialisationParams::SetDvNumPublisherThreads(uint32_t aNumThreads)
{
    ASSERT(aNumThreads > 0);
    iDvNumPublisherThreads = aNumThreads;
}

void InitialisationParams::SetDvPublisherThreadPriority(uint32_t aPriority)
{
    ASSERT(aPriority > kPrioritySystemLowest);
    ASSERT(aPriority < kPrioritySystemHighest);
    iDvPublisherThreadPriority = aPriority;
}

void InitialisationParams::SetDvPublisherModerationTime(uint32_t aMillisecs)
{
    iDvPublisherModerationTimeMs = aMillisecs;
}

void InitialisationParams::SetDvNumWebSocketThreads(uint32_t aNumThreads)
{
    iDvNumWebSocketThreads = aNumThreads;
}

void InitialisationParams::SetCpUpnpEventServerPort(TUint aPort)
{
    iCpUpnpEventServerPort = aPort;
}

void InitialisationParams::SetDvUpnpServerPort(TUint aPort)
{
    iDvUpnpWebServerPort = aPort;
}

void InitialisationParams::SetDvWebSocketPort(TUint aPort)
{
    iDvWebSocketPort = aPort;
}

void InitialisationParams::SetDvEnableBonjour(const TChar* aHostName, TBool aRequiresMdnsCache)
{
    iDvBonjourHostName.Set(aHostName);
    iEnableBonjour = true;
    iRequiresMdnsCache = aRequiresMdnsCache;
}

void InitialisationParams::SetDvNumLpecThreads(uint32_t aNumThreads)
{
    iDvNumLpecThreads = aNumThreads;
}

void InitialisationParams::SetDvLpecServerPort(uint32_t aPort)
{
    iDvLpecServerPort = aPort;
}

void InitialisationParams::SetHostUdpIsLowQuality(TBool aLow)
{
    iHostUdpLowQuality = aLow;
}

void InitialisationParams::SetTimerManagerPriority(uint32_t aPriority)
{
    iTimerManagerThreadPriority = aPriority;
}

void InitialisationParams::SetHttpUserAgent(const Brx& aUserAgent)
{
    iUserAgent.Set(aUserAgent);
}

void InitialisationParams::SetEnableShell(TUint aPort, TUint aSessionPriority)
{
    iEnableShell = true;
    iShellPort = aPort;
    iShellSessionPriority = aSessionPriority;
}

void InitialisationParams::SetSchedulingPolicy(EThreadScheduling aPolicy)
{
    iSchedulingPolicy = aPolicy;
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

Functor& InitialisationParams::ThreadExitHandler()
{
    return iThreadExitHandler;
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

uint32_t InitialisationParams::InvocationTimeoutMs() const
{
    return iInvocationTimeoutMs;
}

uint32_t InitialisationParams::SubscriptionDurationSecs() const
{
    return iSubscriptionDurationSecs;
}

uint32_t InitialisationParams::PendingSubscriptionTimeoutMs() const
{
    return iPendingSubscriptionTimeoutMs;
}

OhNetCallbackFreeExternal InitialisationParams::FreeExternal() const
{
    return iFreeExternal;
}

InitialisationParams::ELoopback InitialisationParams::LoopbackNetworkAdapter() const
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

uint32_t InitialisationParams::DvPublisherThreadPriority() const
{
    return iDvPublisherThreadPriority;
}

uint32_t InitialisationParams::DvPublisherModerationTimeMs() const
{
    return iDvPublisherModerationTimeMs;
}

uint32_t InitialisationParams::DvNumWebSocketThreads() const
{
    return iDvNumWebSocketThreads;
}

uint32_t InitialisationParams::CpUpnpEventServerPort() const
{
    return iCpUpnpEventServerPort;
}

uint32_t InitialisationParams::DvUpnpServerPort() const
{
    // Disable conflation of use of Bonjour with MDNS hostname setting for UPnP devices
    /*if (iEnableBonjour) {
        return 80;
    }*/
    return iDvUpnpWebServerPort;
}

uint32_t InitialisationParams::DvWebSocketPort() const
{
    return iDvWebSocketPort;
}

bool InitialisationParams::DvIsBonjourEnabled(const TChar*& aHostName, TBool& aRequiresMdnsCache) const
{
    aHostName = iDvBonjourHostName.CString();
    aRequiresMdnsCache = iRequiresMdnsCache;
    return iEnableBonjour;
}

uint32_t InitialisationParams::DvNumLpecThreads()
{
    return iDvNumLpecThreads;
}

uint32_t InitialisationParams::DvLpecServerPort()
{
    return iDvLpecServerPort;
}

bool InitialisationParams::IsHostUdpLowQuality()
{
    return iHostUdpLowQuality;
}

uint32_t InitialisationParams::TimerManagerPriority() const
{
    return iTimerManagerThreadPriority;
}

const Brx& InitialisationParams::HttpUserAgent() const
{
    return iUserAgent;
}

TBool InitialisationParams::IsShellEnabled(TUint& aPort, TUint& aSessionPriority) const
{
    aPort = iShellPort;
    aSessionPriority = iShellSessionPriority;
    return iEnableShell;
}

InitialisationParams::EThreadScheduling InitialisationParams::SchedulingPolicy() const
{
    return iSchedulingPolicy;
}

#if defined(PLATFORM_MACOSX_GNU) || defined (PLATFORM_IOS)
/* Assume that all Apple products have poor quality networking.
   This won't be the case for a wired Mac desktop but we'd need a way of signalling which
   adapters are wired from OsNetworkListAdapters to do this... */
# define HOST_UDP_LOW_QUALITY_DEFAULT true
#else
# define HOST_UDP_LOW_QUALITY_DEFAULT false
#endif

InitialisationParams::InitialisationParams()
    : iTcpConnectTimeoutMs(3000)
    , iMsearchTimeSecs(3)
    , iMsearchTtl(2)
    , iNumEventSessionThreads(4)
    , iNumXmlFetcherThreads(4)
    , iNumActionInvokerThreads(4)
    , iNumInvocations(20)
    , iNumSubscriberThreads(4)
    , iInvocationTimeoutMs(60 * 1000)
    , iSubscriptionDurationSecs(30 * 60)
    , iPendingSubscriptionTimeoutMs(2000)
    , iFreeExternal(NULL)
    , iUseLoopbackNetworkAdapter(ELoopbackExclude)
    , iDvMaxUpdateTimeSecs(1800)
    , iDvNumServerThreads(4)
    , iDvNumPublisherThreads(4)
    , iDvPublisherModerationTimeMs(0)
    , iDvPublisherThreadPriority(kPriorityNormal)
    , iDvNumWebSocketThreads(0)
    , iCpUpnpEventServerPort(0)
    , iDvUpnpWebServerPort(0)
    , iDvWebSocketPort(0)
    , iHostUdpLowQuality(HOST_UDP_LOW_QUALITY_DEFAULT)
    , iEnableBonjour(false)
    , iRequiresMdnsCache(false)
    , iDvNumLpecThreads(0)
    , iDvLpecServerPort(0)
    , iTimerManagerThreadPriority(kPriorityHigh)
    , iEnableShell(false)
    , iShellPort(0)
    , iShellSessionPriority(kPriorityNormal)
    , iSchedulingPolicy(EScheduleDefault)
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
    Os::Quit(gEnv->OsCtx());
}


// Library

Library::Library(InitialisationParams* aInitParams)
{
    if ( gEnv == NULL ) {
        iEnvOwner = true;
        iEnv = Environment::Create(aInitParams);
    }
    else {
        iEnvOwner = false;
        iEnv = gEnv;
        iEnv->SetInitParams(aInitParams);
    }
    //Debug::SetSeverity(Debug::kSeverityError);
}

Library::~Library()
{
    if ( iEnvOwner ) {
        delete iEnv;
        gEnv = NULL;
    }
}

OpenHome::Environment& Library::Env()
{
    return *iEnv;
}

std::vector<NetworkAdapter*>* Library::CreateSubnetList()
{
    return iEnv->NetworkAdapterList().CreateSubnetList();
}

void Library::DestroySubnetList(std::vector<NetworkAdapter*>* aSubnetList)
{ // static
    NetworkAdapterList::DestroySubnetList(aSubnetList);
}

std::vector<NetworkAdapter*>* Library::CreateNetworkAdapterList()
{
    return iEnv->NetworkAdapterList().CreateNetworkAdapterList();
}

void Library::DestroyNetworkAdapterList(std::vector<NetworkAdapter*>* aNetworkAdapterList)
{ // static
    NetworkAdapterList::DestroyNetworkAdapterList(aNetworkAdapterList);
}

void Library::SetCurrentSubnet(TIpAddress aSubnet)
{
    iEnv->NetworkAdapterList().SetCurrentSubnet(aSubnet);
}

NetworkAdapter* Library::CurrentSubnetAdapter(const char* aCookie)
{
    return iEnv->NetworkAdapterList().CurrentAdapter(aCookie);
}

void Library::RefreshNetworkAdapterList()
{
    iEnv->NetworkAdapterList().Refresh();
}

void Library::NotifySuspended()
{
    iEnv->NotifySuspended();
}

void Library::NotifyResumed()
{
    iEnv->NotifyResumed();
}


// UpnpLibrary

Environment* UpnpLibrary::Initialise(InitialisationParams* aInitParams)
{
    ASSERT(gEnv == NULL);
    Environment* env = Environment::Create(aInitParams);
    //Debug::SetSeverity(Debug::kSeverityError);
    return env;
}

Environment* UpnpLibrary::InitialiseMinimal(InitialisationParams* aInitParams)
{
    Environment* env = Environment::Create(aInitParams->LogOutput());
    return env;
}

void UpnpLibrary::Close()
{
    delete gEnv;
    gEnv = NULL;
}

std::vector<NetworkAdapter*>* UpnpLibrary::CreateSubnetList()
{
    return gEnv->NetworkAdapterList().CreateSubnetList();
}

void UpnpLibrary::DestroySubnetList(std::vector<NetworkAdapter*>* aSubnetList)
{
    Library::DestroySubnetList(aSubnetList);
}

std::vector<NetworkAdapter*>* UpnpLibrary::CreateNetworkAdapterList()
{
    return gEnv->NetworkAdapterList().CreateNetworkAdapterList();
}

void UpnpLibrary::DestroyNetworkAdapterList(std::vector<NetworkAdapter*>* aNetworkAdapterList)
{
    Library::DestroyNetworkAdapterList(aNetworkAdapterList);
}

void UpnpLibrary::SetCurrentSubnet(TIpAddress aSubnet)
{
    gEnv->NetworkAdapterList().SetCurrentSubnet(aSubnet);
}

NetworkAdapter* UpnpLibrary::CurrentSubnetAdapter(const char* aCookie)
{
    return gEnv->NetworkAdapterList().CurrentAdapter(aCookie);
}

void UpnpLibrary::RefreshNetworkAdapterList()
{
    gEnv->NetworkAdapterList().Refresh();
}

void UpnpLibrary::NotifySuspended()
{
    gEnv->NotifySuspended();
}

void UpnpLibrary::NotifyResumed()
{
    gEnv->NotifyResumed();
}
