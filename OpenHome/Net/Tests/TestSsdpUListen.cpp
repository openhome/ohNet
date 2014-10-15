// Simple test for Unicast SSDP listener
// Logs results of msearch queries

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

class SsdpNotifyLoggerU : public ISsdpNotifyHandler
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

void SsdpNotifyLoggerU::SsdpNotifyRootAlive(const Brx& aUuid, const Brx& aLocation, TUint aMaxAge)
{
    Print("Alive    Root\n    uuid = ");
    Print(aUuid);
    Print("\n    location = ");
    Print(aLocation);
    Print("\n    maxAge = %u\n", aMaxAge);
}

void SsdpNotifyLoggerU::SsdpNotifyUuidAlive(const Brx& aUuid, const Brx& aLocation, TUint aMaxAge)
{
    Print("Alive    Uuid\n    uuid = ");
    Print(aUuid);
    Print("\n    location = ");
    Print(aLocation);
    Print("\n    maxAge = %u\n", aMaxAge);
}

void SsdpNotifyLoggerU::SsdpNotifyDeviceTypeAlive(const Brx& aUuid, const Brx& aDomain, const Brx& aType, TUint aVersion, const Brx& aLocation, TUint aMaxAge)
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

void SsdpNotifyLoggerU::SsdpNotifyServiceTypeAlive(const Brx& aUuid, const Brx& aDomain, const Brx& aType, TUint aVersion, const Brx& aLocation, TUint aMaxAge)
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

void SsdpNotifyLoggerU::SsdpNotifyRootByeBye(const Brx& aUuid)
{
    Print("ByeBye    Root\n    uuid = ");
    Print(aUuid);
    Print("\n");
}

void SsdpNotifyLoggerU::SsdpNotifyUuidByeBye(const Brx& aUuid)
{
    Print("ByeBye    Uuid\n    uuid = ");
    Print(aUuid);
    Print("\n");
}

void SsdpNotifyLoggerU::SsdpNotifyDeviceTypeByeBye(const Brx& aUuid, const Brx& aDomain, const Brx& aType, TUint aVersion)
{
    Print("ByeBye    Device\n    uuid = ");
    Print(aUuid);
    Print("\n    domain = ");
    Print(aDomain);
    Print("\n    type = ");
    Print(aType);
    Print("\n    version = %u\n", aVersion);
}

void SsdpNotifyLoggerU::SsdpNotifyServiceTypeByeBye(const Brx& aUuid, const Brx& aDomain, const Brx& aType, TUint aVersion)
{
    Print("ByeBye    Service\n    uuid = ");
    Print(aUuid);
    Print("\n    domain = ");
    Print(aDomain);
    Print("\n    type = ");
    Print(aType);
    Print("\n    version = %u\n", aVersion);
}


static TIpAddress NetworkIf(Environment& aEnv, TUint aIndex)
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

void TestSsdpUListen(Environment& aEnv, const std::vector<Brn>& aArgs)
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
    if (!parser.Parse(aArgs) || parser.HelpDisplayed()) {
        return;
    }

    //Debug::SetLevel(Debug::kSsdpMulticast);
    TBool block = true;
    SsdpNotifyLoggerU logger;
    SsdpListenerUnicast* uListener = new SsdpListenerUnicast(aEnv, logger, NetworkIf(aEnv, adapter.Value()));
    uListener->Start();
    if (all.Value()) {
        Print("Search all...\n");
        uListener->MsearchAll();
    }
    else if (root.Value()) {
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
        if (OpenHome::Net::Ssdp::ParseUrnDevice(urn.Value(), domainName, deviceType, ver)) {
            uListener->MsearchDeviceType(domainName, deviceType, ver);
        }
        else if (OpenHome::Net::Ssdp::ParseUrnService(urn.Value(), domainName, deviceType, ver)) {
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
        Blocker* blocker = new Blocker(aEnv);
        blocker->Wait(aEnv.InitParams()->MsearchTimeSecs());
        delete blocker;
    }
    delete uListener;
}
