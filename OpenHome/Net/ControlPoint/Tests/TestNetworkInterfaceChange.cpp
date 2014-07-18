// Tests for device list and subscription handling of changes in network interfaces
// Can only be run manually and may only run on certain platforms
// Assumes the presense of multiple active interfaces on the same subnet

#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/OptionParser.h>
#include <OpenHome/Types.h>
#include <OpenHome/Net/Private/Discovery.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Timer.h>
#include <OpenHome/OsWrapper.h>
#include <OpenHome/Net/Core/CpDevice.h>
#include <OpenHome/Net/Core/CpDeviceUpnp.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Net/Core/FunctorCpDevice.h>
#include <OpenHome/Net/Core/CpUpnpOrgConnectionManager1.h>
#include <OpenHome/Net/Core/CpAvOpenHomeOrgPlaylist1.h>
#include <OpenHome/Net/Private/Globals.h>
#include <OpenHome/Private/NetworkAdapterList.h>

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::TestFramework;

class DeviceListLogger
{
public:
    void Added(CpDevice& aDevice);
    void Removed(CpDevice& aDevice);
private:
    void PrintDeviceInfo(const char* aPrologue, const CpDevice& aDevice);
};

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
    Print("%s - ", aPrologue);
    Print(aDevice.Udn());
    Print("\n");
}

/**
 * Stores the first device in a given list
 */
class DevicePicker
{
public:
    DevicePicker();
    ~DevicePicker();
    CpDevice* Transfer();
    void Added(CpDevice& aDevice);
    void Removed(CpDevice& aDevice);
private:
    CpDevice* iDevice;
};

DevicePicker::DevicePicker()
    : iDevice(NULL)
{
}

DevicePicker::~DevicePicker()
{
    if (iDevice != NULL) {
        iDevice->RemoveRef();
    }
}

CpDevice* DevicePicker::Transfer()
{
    CpDevice* ret = iDevice;
    ASSERT(ret != NULL);
    iDevice = NULL;
    return ret;
}

void DevicePicker::Added(CpDevice& aDevice)
{
    if (iDevice == NULL) {
        iDevice = &aDevice;
        iDevice->AddRef();
    }
}

void DevicePicker::Removed(CpDevice& /*aDevice*/)
{
}



extern "C" void OsNetworkSetTestInterfaceIndex(OsContext* aContext, int32_t aIndex);
void setTestNifIndex(TInt aIndex, Blocker& aBlocker)
{
    OsNetworkSetTestInterfaceIndex(gEnv->OsCtx(), aIndex);
    aBlocker.Wait(1); /* sleep to leave room for the interface change to be processed
                       not completely reliable but using the current/subnet change listeners
                       would cause problems too as we've have to hard-code knowledge of
                       when they would/wouldn't be run */
    NetworkAdapter* nif = gEnv->NetworkAdapterList().CurrentAdapter("TestNetworkInterfaceChange");
    TIpAddress addr = 0;
    if (nif != NULL) {
        addr = nif->Address();
        nif->RemoveRef("TestNetworkInterfaceChange");
    }
    Endpoint endpt(0, addr);
    Endpoint::AddressBuf buf;
    endpt.AppendAddress(buf);
    Print("Current network interface %s\n\n", buf.Ptr());
}


class PropertyLogger : public INonCopyable
{
public:
    PropertyLogger(Blocker& aBlocker);
    ~PropertyLogger();
    void Test();
private:
    void LogSinkProtocolInfo();
    void LogShuffle();
private:
    Blocker& iBlocker;
    DevicePicker iPicker;
    CpProxyUpnpOrgConnectionManager1* iConnMgr;
    CpProxyAvOpenhomeOrgPlaylist1* iPlayList;
    CpDevice* iCmDevice;
    CpDevice* iPlDevice;
};

PropertyLogger::PropertyLogger(Blocker& aBlocker)
    : iBlocker(aBlocker)
{
    // each property should be logged once initially
    Brn domainName("upnp.org");
    Brn type("ConnectionManager");
    FunctorCpDevice added = MakeFunctorCpDevice(iPicker, &DevicePicker::Added);
    FunctorCpDevice removed = MakeFunctorCpDevice(iPicker, &DevicePicker::Removed);
    CpDeviceList* deviceList = new CpDeviceListUpnpServiceType(*gCpStack, domainName, type, 1, added, removed);
    iBlocker.Wait(1);
    iCmDevice = iPicker.Transfer();
    delete deviceList;
    Print("\nTesting subscriptions...\n\n");
    iConnMgr = new CpProxyUpnpOrgConnectionManager1(*iCmDevice);
    Functor functor = MakeFunctor(*this, &PropertyLogger::LogSinkProtocolInfo);
    iConnMgr->SetPropertySinkProtocolInfoChanged(functor);
    iConnMgr->Subscribe();

    domainName.Set("av.openhome.org");
    type.Set("Playlist");
    deviceList = new CpDeviceListUpnpServiceType(*gCpStack, domainName, type, 1, added, removed);
    iBlocker.Wait(1);
    iPlDevice = iPicker.Transfer();
    delete deviceList;
    iPlayList = new CpProxyAvOpenhomeOrgPlaylist1(*iPlDevice);
    functor = MakeFunctor(*this, &PropertyLogger::LogShuffle);
    iPlayList->SetPropertyShuffleChanged(functor);
    iPlayList->Subscribe();
    iBlocker.Wait(1);
}

PropertyLogger::~PropertyLogger()
{
    Print("\nCleaning up subscriptions...\n");
    iPlayList->Unsubscribe();
    iConnMgr->Unsubscribe();
    delete iPlayList;
    iPlDevice->RemoveRef();
    delete iConnMgr;
    iCmDevice->RemoveRef();
}

void PropertyLogger::Test()
{
    Print("\nDisable all but first interface...\n");
    setTestNifIndex(0, iBlocker);
    iBlocker.Wait(3);

    // select the first nif again.  No property changes should be logged
    Print("\nDisable all but first interface (again)...\n");
    setTestNifIndex(0, iBlocker);
    iBlocker.Wait(3);

    Print("\nDisable all but second interface...\n");
    setTestNifIndex(1, iBlocker);
    iBlocker.Wait(3);

    // No property changes should be logged
    Print("\nDisabling all interfaces...\n");
    setTestNifIndex(-2, iBlocker);
    iBlocker.Wait(3);

    // Both properties should be logged
    Print("\nRe-enable first interface...\n");
    setTestNifIndex(0, iBlocker);
    iBlocker.Wait(3);
}

void PropertyLogger::LogSinkProtocolInfo()
{
    Brhz info;
    iConnMgr->PropertySinkProtocolInfo(info);
    Log::Print("ConnMgr sink info: ");
    if (info.Bytes() > 0) {
        Log::Print(info);
    }
    else {
        Log::Print("<empty>");
    }
    Log::Print("\n");
}

void PropertyLogger::LogShuffle()
{
    TBool shuffle;
    iPlayList->PropertyShuffle(shuffle);
    Log::Print("PlayList shuffle = %d\n", (shuffle? 1 : 0));
}


void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    UpnpLibrary::Initialise(aInitParams);
    std::vector<NetworkAdapter*>* subnetList = UpnpLibrary::CreateSubnetList();
    TIpAddress subnet = (*subnetList)[0]->Subnet();
    UpnpLibrary::DestroySubnetList(subnetList);
    UpnpLibrary::StartCp(subnet);
    Debug::SetLevel(Debug::kNone);

    Blocker* blocker = new Blocker(*gEnv);

    // generate device list for arbitrarily chosen service
    DeviceListLogger logger;
    Brn domainName("linn.co.uk");
    Brn type("Radio");
    FunctorCpDevice added = MakeFunctorCpDevice(logger, &DeviceListLogger::Added);
    FunctorCpDevice removed = MakeFunctorCpDevice(logger, &DeviceListLogger::Removed);
    CpDeviceList* deviceList = new CpDeviceListUpnpServiceType(*gCpStack, domainName, type, 1, added, removed);
    blocker->Wait(2);
    // disable all but the first network interface.  Check there are few/no changes to the list
    Print("\nDisable all but first interface...\n");
    setTestNifIndex(0, *blocker);
    blocker->Wait(3);

    // disable all but the second network interface.  Check there are few/no changes to the list
    Print("\nDisable all but second interface...\n");
    setTestNifIndex(1, *blocker);
    blocker->Wait(3);

    // disable all interfaces.  Check all devices are removed from the list
    Print("\nDisabling all interfaces...\n");
    setTestNifIndex(-2, *blocker);
    blocker->Wait(3);

    // re-enable first interface.  Check all devices are added again
    Print("\nRe-enable first interface...\n");
    setTestNifIndex(0, *blocker);
    blocker->Wait(3);

    Print("\nCleaning up device list...\n");
    delete deviceList;

    // enable all interfaces
    setTestNifIndex(-1, *blocker);

    // listen to / log changes in properties in a couple of services
    PropertyLogger* propertyLogger = new PropertyLogger(*blocker);
    propertyLogger->Test();
    delete propertyLogger;

    delete blocker;
    Net::UpnpLibrary::Close();
}
