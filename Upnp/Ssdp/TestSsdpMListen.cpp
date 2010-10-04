// Simple test for Multicast SSDP listener
// Prints alive/byebye messages plus any msearch requests
// Test will need to be manually killed if run forever (duration of 0 seconds)

/* Note that selection of network interface has little effect as the listeners
   in Stack seem to result in multicast messages on any interface being received
   on all interfaces for linux-hosted tests.
   CpiDeviceListUpnp works around this so client code is okay.  Be aware of this
   when reviewing test results however. */


#include <TestFramework.h>
#include <OptionParser.h>
#include <ZappTypes.h>
#include <Discovery.h>
#include <Thread.h>
#include <Timer.h>
#include <Stack.h>

using namespace Zapp;
using namespace Zapp::TestFramework;

class SsdpNotifyLogger : public ISsdpNotifyHandler
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


void SsdpNotifyLogger::SsdpNotifyRootAlive(const Brx& aUuid, const Brx& aLocation, TUint aMaxAge)
{
    Print("Alive    Root\n    uuid = ");
    Print(aUuid);
    Print("\n    location = ");
    Print(aLocation);
    Print("\n    maxAge = %u\n", aMaxAge);
}

void SsdpNotifyLogger::SsdpNotifyUuidAlive(const Brx& aUuid, const Brx& aLocation, TUint aMaxAge)
{
    Print("Alive    Uuid\n    uuid = ");
    Print(aUuid);
    Print("\n    location = ");
    Print(aLocation);
    Print("\n    maxAge = %u\n", aMaxAge);
}

void SsdpNotifyLogger::SsdpNotifyDeviceTypeAlive(const Brx& aUuid, const Brx& aDomain, const Brx& aType, TUint aVersion, const Brx& aLocation, TUint aMaxAge)
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

void SsdpNotifyLogger::SsdpNotifyServiceTypeAlive(const Brx& aUuid, const Brx& aDomain, const Brx& aType, TUint aVersion, const Brx& aLocation, TUint aMaxAge)
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

void SsdpNotifyLogger::SsdpNotifyRootByeBye(const Brx& aUuid)
{
    Print("ByeBye    Root\n    uuid = ");
    Print(aUuid);
    Print("\n");
}

void SsdpNotifyLogger::SsdpNotifyUuidByeBye(const Brx& aUuid)
{
    Print("ByeBye    Uuid\n    uuid = ");
    Print(aUuid);
    Print("\n");
}

void SsdpNotifyLogger::SsdpNotifyDeviceTypeByeBye(const Brx& aUuid, const Brx& aDomain, const Brx& aType, TUint aVersion)
{
    Print("ByeBye    Device\n    uuid = ");
    Print(aUuid);
    Print("\n    domain = ");
    Print(aDomain);
    Print("\n    type = ");
    Print(aType);
    Print("\n    version = %u\n", aVersion);
}

void SsdpNotifyLogger::SsdpNotifyServiceTypeByeBye(const Brx& aUuid, const Brx& aDomain, const Brx& aType, TUint aVersion)
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
    TUint addr = aEndpoint.Address();
    Print("%u.%u.%u.%u:%u", (addr>>24), ((addr>>16)&0xff), ((addr>>8)&0xff), addr&0xff, aEndpoint.Port());
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
    SuiteListen(TUint aDurationSeconds, TUint aInterfaceIndex);
    ~SuiteListen();
    void Test();
private:
    static TIpAddress NetworkIf(TUint aIndex);
    void TimerExpired();
private:
    Semaphore iSem;
    Timer* iTimer;
    TUint iDuration;
    TUint iInterfaceIndex;
};

SuiteListen::SuiteListen(TUint aDurationSeconds, TUint aInterfaceIndex)
    : Suite("multicast listener")
    , iSem("SBLK", 0)
    , iDuration(1000 * aDurationSeconds)
    , iInterfaceIndex(aInterfaceIndex)
{
    iTimer = new Timer(MakeFunctor(*this, &SuiteListen::TimerExpired));
}

SuiteListen::~SuiteListen()
{
    delete iTimer;
}

TIpAddress SuiteListen::NetworkIf(TUint aIndex)
{
    const std::vector<NetworkInterface*>& ifs = Stack::NetworkInterfaceList().List();
    ASSERT(ifs.size() > 0 && aIndex < ifs.size());
    TIpAddress addr = ifs[aIndex]->Address();
    Print("Using network interface %d.%d.%d.%d\n", addr&0xff, (addr>>8)&0xff, (addr>>16)&0xff, (addr>>24)&0xff);
    return ifs[aIndex]->Address();
}

void SuiteListen::Test()
{
//    Debug::SetLevel(Debug::kSsdpMulticast);
    SsdpNotifyLogger notifyLogger;
    MSearchLogger msearchLogger;
    SsdpListenerMulticast mListener(NetworkIf(iInterfaceIndex));
    (void)mListener.AddNotifyHandler(&notifyLogger);
    (void)mListener.AddMsearchHandler(&msearchLogger);
    mListener.Start();
    iTimer->FireIn(iDuration);
    iSem.Wait();
}

void SuiteListen::TimerExpired()
{
    iSem.Signal();
}


void Zapp::TestFramework::Runner::Main(TInt aArgc, TChar* aArgv[], InitialisationParams* aInitParams)
{
    OptionParser parser;
    OptionUint duration("-d", "--duration", 30, "Number of seconds to listen for.  Defaults to 30");
    parser.AddOption(&duration);
    OptionUint adapter("-i", "--interface", 0, "index of network adapter to use");
    parser.AddOption(&adapter);
    if (!parser.Parse(aArgc, aArgv) || parser.HelpDisplayed()) {
        return;
    }

    UpnpLibrary::Initialise(aInitParams);

    Runner runner("SSDP multicast listener\n");
    runner.Add(new SuiteListen(duration.Value(), adapter.Value()));
    runner.Run();

    UpnpLibrary::Close();
}
