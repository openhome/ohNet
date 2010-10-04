// Simple test for Unicast SSDP listener
// Logs results of msearch queries

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


static TIpAddress NetworkIf(TUint aIndex)
{
    const std::vector<NetworkInterface*>& ifs = Stack::NetworkInterfaceList().List();
    ASSERT(ifs.size() > 0 && aIndex < ifs.size());
    TIpAddress addr = ifs[aIndex]->Address();
    Print("Using network interface %d.%d.%d.%d\n", addr&0xff, (addr>>8)&0xff, (addr>>16)&0xff, (addr>>24)&0xff);
    return ifs[aIndex]->Address();
}

void Zapp::TestFramework::Runner::Main(TInt aArgc, TChar* aArgv[], InitialisationParams* aInitParams)
{
    OptionParser parser;
    OptionUint mx("-mx", "--mx", 0, "[1..5] number of second to spread response over");
    parser.AddOption(&mx);
    OptionUint adapter("-i", "--interface", 0, "index of network adapter to use");
    parser.AddOption(&adapter);
    OptionBool all("-a", "--all", "Search for all devices and services");
    parser.AddOption(&all);
    OptionBool root("-r", "--root", "Search for root devices only");
    parser.AddOption(&root);
    Brn emptyString("");
    OptionString uuid("-u", "--uuid", emptyString, "[uuid string] search for a particular device");
    parser.AddOption(&uuid);
    OptionString urn("-t", "--urn", emptyString, "Search for a device or service of the form [domain:[device|service]:type:ver]");
    parser.AddOption(&urn);
    if (!parser.Parse(aArgc, aArgv) || parser.HelpDisplayed()) {
        return;
    }

    if (mx.Value() != 0) {
        aInitParams->SetMsearchTime(mx.Value());
    }
    UpnpLibrary::Initialise(aInitParams);

    //Debug::SetLevel(Debug::kSsdpMulticast);
    TBool block = true;
    SsdpNotifyLogger logger;
    SsdpListenerUnicast* uListener = new SsdpListenerUnicast(logger, NetworkIf(adapter.Value()));
    uListener->Start();
    if (all.IsSet()) {
        Print("Search all...\n");
        uListener->MsearchAll();
    }
    else if (root.IsSet()) {
        Print("Search root...\n");
        uListener->MsearchRoot();
    }
    else if (uuid.Value().Bytes() > 0) {
        Print("Search uuid...\n");
        uListener->MsearchUuid(uuid.Value());
    }
    else if (urn.Value().Bytes() > 0) {
        Print("Search device/service...\n");
        Brn domainName;
        Brn deviceType;
        TUint ver;
        if (Zapp::Ssdp::ParseUrnDevice(urn.Value(), domainName, deviceType, ver)) {
            uListener->MsearchDeviceType(domainName, deviceType, ver);
        }
        else if (Zapp::Ssdp::ParseUrnService(urn.Value(), domainName, deviceType, ver)) {
            uListener->MsearchServiceType(domainName, deviceType, ver);
        }
        else {
            parser.DisplayHelp();
            block = false;
        }
    }
    else {
        parser.DisplayHelp();
        block = false;
    }

    if (block) {
        Blocker* blocker = new Blocker;
        blocker->Wait(aInitParams->MsearchTimeSecs());
        delete blocker;
    }
    delete uListener;

    UpnpLibrary::Close();
}
