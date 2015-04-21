// Equivalent to TestDeviceList but for C wrapper APIs
//

#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/OptionParser.h>
#include <OpenHome/Types.h>
#include <OpenHome/Net/Private/Discovery.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/OsWrapper.h>
#include <OpenHome/Net/C/CpDeviceUpnp.h>
#include <OpenHome/Net/C/OhNet.h>
#include <OpenHome/Net/Private/Globals.h>

#include <stdlib.h>
#include <string.h>

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::TestFramework;

static void printDeviceInfo(const char* aPrologue, CpDeviceC aDevice)
{
    char* location;
    ASSERT(0 != CpDeviceCGetAttribute(aDevice, "Upnp.Location", &location));
    char* friendlyName;
    ASSERT(0 != CpDeviceCGetAttribute(aDevice, "Upnp.FriendlyName", &friendlyName));
    Print("%s\n    udn = %s\n    location = %s\n    name = %s\n",
          aPrologue, CpDeviceCUdn(aDevice), location, friendlyName);
    free(location);
    free(friendlyName);
}

static void STDCALL added(void* aPtr, CpDeviceC aDevice)
{
    Mutex* lock = (Mutex*)aPtr;
    lock->Wait();
    printDeviceInfo("Added", aDevice);
    lock->Signal();
}

static void STDCALL removed(void* aPtr, CpDeviceC aDevice)
{
    Mutex* lock = (Mutex*)aPtr;
    lock->Wait();
    printDeviceInfo("Removed", aDevice);
    lock->Signal();
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
    HandleCpDeviceList deviceList = kHandleNull;
    Mutex* mutex = new Mutex("TDLM");
    if (all.Value()) {
        deviceList = CpDeviceListCreateUpnpAll(added, mutex, removed, mutex);
    }
    else if (root.Value()) {
        Print("Search root...\n");
        deviceList = CpDeviceListCreateUpnpRoot(added, mutex, removed, mutex);
    }
    else if (uuid.Value().Bytes() > 0) {
        Print("Search uuid...\n");
        Brhz udn(uuid.Value());
        deviceList = CpDeviceListCreateUpnpUuid(udn.CString(), added, mutex, removed, mutex);
    }
    else if (urn.Value().Bytes() > 0) {
        Print("Search device/service...\n");
        Brn domainName;
        Brn type;
        TUint ver;
        if (OpenHome::Net::Ssdp::ParseUrnDevice(urn.Value(), domainName, type, ver)) {
            Brhz domain(domainName);
            Brhz deviceType(type);
            deviceList = CpDeviceListCreateUpnpDeviceType(domain.CString(), deviceType.CString(), ver,
                                                          added, mutex, removed, mutex);
        }
        else if (OpenHome::Net::Ssdp::ParseUrnService(urn.Value(), domainName, type, ver)) {
            Brhz domain(domainName);
            Brhz serviceType(type);
            deviceList = CpDeviceListCreateUpnpServiceType(domain.CString(), serviceType.CString(), ver,
                                                           added, mutex, removed, mutex);
        }
        else {
            parser.DisplayHelp();
        }
    }
    else {
        parser.DisplayHelp();
    }

    Blocker* blocker = new Blocker(*gEnv);
    if (deviceList != kHandleNull) {
        blocker->Wait(aInitParams->MsearchTimeSecs());
    }
    if (refresh.Value()) {
        Print("\nRefreshing...\n\n");
        CpDeviceListRefresh(deviceList);
        blocker->Wait(aInitParams->MsearchTimeSecs());
    }
    delete blocker;
    CpDeviceListDestroy(deviceList);
    delete mutex;

    UpnpLibrary::Close();
}
