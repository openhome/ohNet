// Equivalent to TestDeviceList but for C++ wrapper APIs
//

#include <TestFramework.h>
#include <OptionParser.h>
#include <ZappTypes.h>
#include <Discovery.h>
#include <Thread.h>
#include <Timer.h>
#include <Os.h>
#include <Std/CpDeviceUpnp.h>
#include <Std/FunctorCpDevice.h>

#include <string>

using namespace Zapp;
using namespace Zapp::TestFramework;

class DeviceListLogger
{
public:
    DeviceListLogger();
    void Added(CpDeviceCpp& aDevice);
    void Removed(CpDeviceCpp& aDevice);
private:
    void PrintDeviceInfo(const char* aPrologue, const CpDeviceCpp& aDevice);
private:
    Mutex iLock;
};

DeviceListLogger::DeviceListLogger()
    : iLock("DLLM")
{
}

void DeviceListLogger::Added(CpDeviceCpp& aDevice)
{
    PrintDeviceInfo("Added", aDevice);
}

void DeviceListLogger::Removed(CpDeviceCpp& aDevice)
{
    PrintDeviceInfo("Removed", aDevice);
}

void DeviceListLogger::PrintDeviceInfo(const char* aPrologue, const CpDeviceCpp& aDevice)
{
    iLock.Wait();
    std::string location;
    aDevice.GetAttribute("Upnp.Location", location);
    std::string friendlyName;
    aDevice.GetAttribute("Upnp.FriendlyName", friendlyName);
    Print("%s\n    udn = %s\n    location = %s\n    name = %s\n",
          aPrologue, aDevice.Udn().c_str(), location.c_str(), friendlyName.c_str());
    iLock.Signal();
}


void Zapp::TestFramework::Runner::Main(TInt aArgc, TChar* aArgv[], InitialisationParams* aInitParams)
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
    UpnpLibrary::StartCp();

//    Debug::SetLevel(Debug::kSsdpUnicast);
    DeviceListLogger logger;
    TBool block = true;
    CpDeviceListCpp* deviceList = NULL;
    FunctorCpDeviceCpp added = MakeFunctorCpDeviceCpp(logger, &DeviceListLogger::Added);
    FunctorCpDeviceCpp removed = MakeFunctorCpDeviceCpp(logger, &DeviceListLogger::Removed);
    if (all.IsSet()) {
        deviceList = new CpDeviceListCppUpnpAll(added, removed);
    }
    else if (root.IsSet()) {
        Print("Search root...\n");
        deviceList = new CpDeviceListCppUpnpRoot(added, removed);
    }
    else if (uuid.Value().Bytes() > 0) {
        Print("Search uuid...\n");
        std::string udn((const char*)uuid.Value().Ptr(), uuid.Value().Bytes());
        deviceList = new CpDeviceListCppUpnpUuid(udn, added, removed);
    }
    else if (urn.Value().Bytes() > 0) {
        Print("Search device/service...\n");
        Brn domainName;
        Brn type;
        TUint ver;
        if (Zapp::Ssdp::ParseUrnDevice(urn.Value(), domainName, type, ver)) {
            std::string domain((const char*)domainName.Ptr(), domainName.Bytes());
            std::string deviceType((const char*)type.Ptr(), type.Bytes());
            deviceList = new CpDeviceListCppUpnpDeviceType(domain, deviceType, ver, added, removed);
        }
        else if (Zapp::Ssdp::ParseUrnService(urn.Value(), domainName, type, ver)) {
            std::string domain((const char*)domainName.Ptr(), domainName.Bytes());
            std::string serviceType((const char*)type.Ptr(), type.Bytes());
            deviceList = new CpDeviceListCppUpnpServiceType(domain, serviceType, ver, added, removed);
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

    if (deviceList != NULL) {
        Blocker* blocker = new Blocker;
        blocker->Wait(aInitParams->MsearchTimeSecs());
        delete blocker;
    }
    if (refresh.IsSet()) {
        Blocker* blocker = new Blocker;
        blocker->Wait(mx.Value());
        Print("\nRefreshing...\n\n");
        deviceList->Refresh();
        blocker->Wait(mx.Value());
        delete blocker;
    }
    delete deviceList;

    UpnpLibrary::Close();
}
