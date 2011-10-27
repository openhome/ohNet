// Simple test for Control Point side device list
// Looks suspiciously similar to TestSsdpUListen for now...
//

#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/OptionParser.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Net/Private/Discovery.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Timer.h>
#include <OpenHome/OsWrapper.h>
#include <OpenHome/Net/Core/CpDeviceUpnp.h>
#include <OpenHome/Net/Core/FunctorCpDevice.h>

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::TestFramework;

class DeviceListLogger
{
public:
    DeviceListLogger();
    void Added(CpDevice& aDevice);
    void Removed(CpDevice& aDevice);
private:
    void PrintDeviceInfo(const char* aPrologue, const CpDevice& aDevice);
private:
    Mutex iLock;
};

DeviceListLogger::DeviceListLogger()
    : iLock("DLLM")
{
}

void DeviceListLogger::Added(CpDevice& aDevice)
{
    PrintDeviceInfo("Added", aDevice);
}

void DeviceListLogger::Removed(CpDevice& aDevice)
{
    PrintDeviceInfo("Removed", aDevice);
}

void DeviceListLogger::PrintDeviceInfo(const char* aPrologue, const CpDevice& aDevice)
{
    iLock.Wait();
    Print("%s\n    udn = ", aPrologue);
    Print(aDevice.Udn());
    Print("\n    location = ");
    Brh val;
    aDevice.GetAttribute("Upnp.Location", val);
    Print(val);
    Print("\n    name = ");
    aDevice.GetAttribute("Upnp.FriendlyName", val);
    Print(val);
    Print("\n");
    iLock.Signal();
}


void OpenHome::TestFramework::Runner::Main(TInt aArgc, TChar* aArgv[], InitialisationParams* aInitParams)
{
    OptionParser parser;
    OptionUint mx("-mx", "--mx", 1, "[1..5] number of second to spread response over");
    parser.AddOption(&mx);
    OptionBool all("-a", "--all", "Search for all devices and services");
    parser.AddOption(&all);
    OptionBool root("-r", "--root", "Search for root devices only");
    parser.AddOption(&root);
    Brn emptyString("");
    OptionString uuid("-u", "--uuid", emptyString, "[uuid string] search for a particular device");
    parser.AddOption(&uuid);
    OptionString urn("-t", "--urn", emptyString, "Search for a device or service of the form [domain:[device|service]:type:ver]");
    parser.AddOption(&urn);
    OptionBool refresh("-f", "--refresh", "Wait mx secs then refresh list");
    parser.AddOption(&refresh);
    if (!parser.Parse(aArgc, aArgv) || parser.HelpDisplayed()) {
        return;
    }

    if (mx.Value() != 0) {
        aInitParams->SetMsearchTime(mx.Value());
    }
    UpnpLibrary::Initialise(aInitParams);
    std::vector<NetworkAdapter*>* subnetList = UpnpLibrary::CreateSubnetList();
    TIpAddress subnet = (*subnetList)[0]->Subnet();
    UpnpLibrary::DestroySubnetList(subnetList);
    UpnpLibrary::StartCp(subnet);

//    Debug::SetLevel(Debug::kDevice);
    DeviceListLogger logger;
    CpDeviceList* deviceList = NULL;
    FunctorCpDevice added = MakeFunctorCpDevice(logger, &DeviceListLogger::Added);
    FunctorCpDevice removed = MakeFunctorCpDevice(logger, &DeviceListLogger::Removed);
    if (all.Value()) {
        deviceList = new CpDeviceListUpnpAll(added, removed);
    }
    else if (root.Value()) {
        Print("Search root...\n");
        deviceList = new CpDeviceListUpnpRoot(added, removed);
    }
    else if (uuid.Value().Bytes() > 0) {
        Print("Search uuid...\n");
        deviceList = new CpDeviceListUpnpUuid(uuid.Value(), added, removed);
    }
    else if (urn.Value().Bytes() > 0) {
        Print("Search device/service...\n");
        Brn domainName;
        Brn type;
        TUint ver;
        if (OpenHome::Net::Ssdp::ParseUrnDevice(urn.Value(), domainName, type, ver)) {
            deviceList = new CpDeviceListUpnpDeviceType(domainName, type, ver, added, removed);
        }
        else if (OpenHome::Net::Ssdp::ParseUrnService(urn.Value(), domainName, type, ver)) {
            deviceList = new CpDeviceListUpnpServiceType(domainName, type, ver, added, removed);
        }
        else {
            parser.DisplayHelp();
        }
    }
    else {
        parser.DisplayHelp();
    }

    Blocker* blocker = new Blocker;
    if (deviceList != NULL) {
        blocker->Wait(aInitParams->MsearchTimeSecs());
    }
    if (refresh.Value()) {
        Print("\nRefreshing...\n\n");
        deviceList->Refresh();
        blocker->Wait(aInitParams->MsearchTimeSecs());
    }
    delete blocker;
    delete deviceList;

    UpnpLibrary::Close();
}
