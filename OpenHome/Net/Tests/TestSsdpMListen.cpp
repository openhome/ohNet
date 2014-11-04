// Simple test for Multicast SSDP listener
// Prints alive/byebye messages plus any msearch requests
// Test will need to be manually killed if run forever (duration of 0 seconds)

/* Note that selection of network interface has little effect as the listeners
   in Environment seem to result in multicast messages on any interface being received
   on all interfaces for linux-hosted tests.
   CpiDeviceListUpnp works around this so client code is okay.  Be aware of this
   when reviewing test results however. */


#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/OptionParser.h>
#include <OpenHome/Types.h>
#include <OpenHome/Net/Private/Discovery.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Timer.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Private/NetworkAdapterList.h>

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::TestFramework;

class SsdpNotifyLoggerM : public ISsdpNotifyHandler
{
public:
    // ISsdpNotifyHandler
    void SsdpNotifyRootAlive(const Brx& aUuid, const Brx& aLocation, TUint aMaxAge);
    void SsdpNotifyUuidAlive(const Brx& aUuid, const Brx& aLocation, TUint aMaxAge);
    void SsdpNotifyDeviceTypeAlive(const Brx& aUuid, const Brx& aDomain, const Brx& aType, TUint aVersion, const Brx& aLocation, TUint aMaxAge);
    void SsdpNotifyServiceTypeAlive(const Brx& aUuid, const Brx& aDomain, const Brx& aType, TUint aVersion, const Brx& aLocation, TUint aMaxAge);
    void SsdpNotifyRootByeBye(const Brx& aUuid);
    void SsdpNotifyUuidByeBye(const Brx& aUuid);
    void SsdpNotifyDeviceTypeByeBye(const Brx& aUuid, const Brx& aDomain, const Brx& aType, TUint aVersion);
    void SsdpNotifyServiceTypeByeBye(const Brx& aUuid, const Brx& aDomain, const Brx& aType, TUint aVersion);
};

class MSearchLogger : public ISsdpMsearchHandler
{
public:
    // ISsdpMsearchHandler
    void SsdpSearchAll(const Endpoint& aEndpoint, TUint aMx);
    void SsdpSearchRoot(const Endpoint& aEndpoint, TUint aMx);
    void SsdpSearchUuid(const Endpoint& aEndpoint, TUint aMx, const Brx& aUuid);
    void SsdpSearchDeviceType(const Endpoint& aEndpoint, TUint aMx, const Brx& aDomain, const Brx& aType, TUint aVersion);
    void SsdpSearchServiceType(const Endpoint& aEndpoint, TUint aMx, const Brx& aDomain, const Brx& aType, TUint aVersion);
};


void SsdpNotifyLoggerM::SsdpNotifyRootAlive(const Brx& aUuid, const Brx& aLocation, TUint aMaxAge)
{
    Print("Alive    Root\n    uuid = ");
    Print(aUuid);
    Print("\n    location = ");
    Print(aLocation);
    Print("\n    maxAge = %u\n", aMaxAge);
}

void SsdpNotifyLoggerM::SsdpNotifyUuidAlive(const Brx& aUuid, const Brx& aLocation, TUint aMaxAge)
{
    Print("Alive    Uuid\n    uuid = ");
    Print(aUuid);
    Print("\n    location = ");
    Print(aLocation);
    Print("\n    maxAge = %u\n", aMaxAge);
}

void SsdpNotifyLoggerM::SsdpNotifyDeviceTypeAlive(const Brx& aUuid, const Brx& aDomain, const Brx& aType, TUint aVersion, const Brx& aLocation, TUint aMaxAge)
{
    Print("Alive    Device\n    uuid = ");
    Print(aUuid);
    Print("\n    domain = ");
    Print(aDomain);
    Print("\n    type = ");
    Print(aType);
    Print("\n    version = %u\n    location = ", aVersion);
    Print(aLocation);
    Print("\n    maxAge = %u\n", aMaxAge);
}

void SsdpNotifyLoggerM::SsdpNotifyServiceTypeAlive(const Brx& aUuid, const Brx& aDomain, const Brx& aType, TUint aVersion, const Brx& aLocation, TUint aMaxAge)
{
    Print("Alive    Service\n    uuid = ");
    Print(aUuid);
    Print("\n    domain = ");
    Print(aDomain);
    Print("\n    type = ");
    Print(aType);
    Print("\n    version = %u\n    location = ", aVersion);
    Print(aLocation);
    Print("\n    maxAge = %u\n", aMaxAge);
}

void SsdpNotifyLoggerM::SsdpNotifyRootByeBye(const Brx& aUuid)
{
    Print("ByeBye    Root\n    uuid = ");
    Print(aUuid);
    Print("\n");
}

void SsdpNotifyLoggerM::SsdpNotifyUuidByeBye(const Brx& aUuid)
{
    Print("ByeBye    Uuid\n    uuid = ");
    Print(aUuid);
    Print("\n");
}

void SsdpNotifyLoggerM::SsdpNotifyDeviceTypeByeBye(const Brx& aUuid, const Brx& aDomain, const Brx& aType, TUint aVersion)
{
    Print("ByeBye    Device\n    uuid = ");
    Print(aUuid);
    Print("\n    domain = ");
    Print(aDomain);
    Print("\n    type = ");
    Print(aType);
    Print("\n    version = %u\n", aVersion);
}

void SsdpNotifyLoggerM::SsdpNotifyServiceTypeByeBye(const Brx& aUuid, const Brx& aDomain, const Brx& aType, TUint aVersion)
{
    Print("ByeBye    Service\n    uuid = ");
    Print(aUuid);
    Print("\n    domain = ");
    Print(aDomain);
    Print("\n    type = ");
    Print(aType);
    Print("\n    version = %u\n", aVersion);
}


static void PrintEndpoint(const Endpoint& aEndpoint)
{
    Endpoint::EndpointBuf buf;
    aEndpoint.AppendEndpoint(buf);
    Print("%s", buf.Ptr());
}

void MSearchLogger::SsdpSearchAll(const Endpoint& aEndpoint, TUint aMx)
{
    Print("MSearch    All\n    from ");
    PrintEndpoint(aEndpoint);
    Print("\n    max response delay = %u\n", aMx);
}

void MSearchLogger::SsdpSearchRoot(const Endpoint& aEndpoint, TUint aMx)
{
    Print("MSearch    Root\n    from ");
    PrintEndpoint(aEndpoint);
    Print("\n    max response delay = %u\n", aMx);
}

void MSearchLogger::SsdpSearchUuid(const Endpoint& aEndpoint, TUint aMx, const Brx& aUuid)
{
    Print("MSearch    Uuid\n    from ");
    PrintEndpoint(aEndpoint);
    Print("\n    max response delay = %u\n    uuid = ", aMx);
    Print(aUuid);
    Print("\n");
}

void MSearchLogger::SsdpSearchDeviceType(const Endpoint& aEndpoint, TUint aMx, const Brx& aDomain, const Brx& aType, TUint aVersion)
{
    Print("MSearch    Device\n    from ");
    PrintEndpoint(aEndpoint);
    Print("\n    max response delay = %u\n    domain = ", aMx);
    Print(aDomain);
    Print("\n    type = ");
    Print(aType);
    Print("\n    version = %u\n", aVersion);
}

void MSearchLogger::SsdpSearchServiceType(const Endpoint& aEndpoint, TUint aMx, const Brx& aDomain, const Brx& aType, TUint aVersion)
{
    Print("MSearch    Service\n    from ");
    PrintEndpoint(aEndpoint);
    Print("\n    max response delay = %u\n    domain = ", aMx);
    Print(aDomain);
    Print("\n    type = ");
    Print(aType);
    Print("\n    version = %u\n", aVersion);
}


class SuiteListen : public Suite
{
public:
    SuiteListen(Environment& aEnv, TUint aDurationSeconds, TUint aInterfaceIndex);
    ~SuiteListen();
    void Test();
private:
    static TIpAddress NetworkIf(Environment& aEnv, TUint aIndex);
    void TimerExpired();
private:
    Environment& iEnv;
    Semaphore iSem;
    Timer* iTimer;
    TUint iDuration;
    TUint iInterfaceIndex;
};

SuiteListen::SuiteListen(Environment& aEnv, TUint aDurationSeconds, TUint aInterfaceIndex)
    : Suite("multicast listener")
    , iEnv(aEnv)
    , iSem("SBLK", 0)
    , iDuration(1000 * aDurationSeconds)
    , iInterfaceIndex(aInterfaceIndex)
{
    iTimer = new Timer(aEnv, MakeFunctor(*this, &SuiteListen::TimerExpired), "SuiteListen");
}

SuiteListen::~SuiteListen()
{
    delete iTimer;
}

TIpAddress SuiteListen::NetworkIf(Environment& aEnv, TUint aIndex)
{
    std::vector<NetworkAdapter*>* ifs = aEnv.NetworkAdapterList().CreateNetworkAdapterList();
    ASSERT(ifs->size() > 0 && aIndex < ifs->size());
    TIpAddress addr = (*ifs)[aIndex]->Address();
    NetworkAdapterList::DestroyNetworkAdapterList(ifs);
    Endpoint endpt(0, addr);
    Endpoint::AddressBuf buf;
    endpt.AppendAddress(buf);
    Print("Using network interface %s\n\n", buf.Ptr());
    return addr;
}

void SuiteListen::Test()
{
//    Debug::SetLevel(Debug::kSsdpMulticast);
    SsdpNotifyLoggerM notifyLogger;
    MSearchLogger msearchLogger;
    SsdpListenerMulticast mListener(iEnv, NetworkIf(iEnv, iInterfaceIndex));
    TInt notifyId = mListener.AddNotifyHandler(&notifyLogger);
    TInt msearchId = mListener.AddMsearchHandler(&msearchLogger);
    mListener.Start();
    iTimer->FireIn(iDuration);
    iSem.Wait();
    mListener.RemoveNotifyHandler(notifyId);
    mListener.RemoveMsearchHandler(msearchId);
}

void SuiteListen::TimerExpired()
{
    iSem.Signal();
}


void TestSsdpMListen(Environment& aEnv, const std::vector<Brn>& aArgs)
{
    OptionParser parser;
    OptionUint duration("-d", "--duration", 30, "Number of seconds to listen for.  Defaults to 30");
    parser.AddOption(&duration);
    OptionUint adapter("-i", "--interface", 0, "index of network adapter to use");
    parser.AddOption(&adapter);
    if (!parser.Parse(aArgs) || parser.HelpDisplayed()) {
        return;
    }

    Runner runner("SSDP multicast listener\n");
    runner.Add(new SuiteListen(aEnv, duration.Value(), adapter.Value()));
    runner.Run();
}
