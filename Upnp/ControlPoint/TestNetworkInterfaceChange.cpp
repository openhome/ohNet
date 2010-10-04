// Tests for device list and subscription handling of changes in network interfaces
// Can only be run manually and may only run on certain platforms
// Assumes the presense of multiple active interfaces on the same subnet

#include <TestFramework.h>
#include <OptionParser.h>
#include <ZappTypes.h>
#include <Discovery.h>
#include <Thread.h>
#include <Timer.h>
#include <Os.h>
#include <CpiDeviceUpnp.h>
#include <Stack.h>
#include <FunctorCpiDevice.h>
#include <UpnpOrgConnectionManager1.h>
#include <LinnCoUkPlaylist1.h>

using namespace Zapp;
using namespace Zapp::TestFramework;

class DeviceListLogger
{
public:
    void Added(CpiDevice& aDevice);
    void Removed(CpiDevice& aDevice);
private:
    void PrintDeviceInfo(const char* aPrologue, const CpiDevice& aDevice);
};

void DeviceListLogger::Added(CpiDevice& aDevice)
{
    PrintDeviceInfo("Added", aDevice);
}

void DeviceListLogger::Removed(CpiDevice& aDevice)
{
    PrintDeviceInfo("Removed", aDevice);
}

void DeviceListLogger::PrintDeviceInfo(const char* aPrologue, const CpiDevice& aDevice)
{
    Print("%s\n    udn = ", aPrologue);
    Print(aDevice.Udn());
    Print("\n    location = ");
    Print(static_cast<const CpiDeviceUpnp&>(aDevice).Location());
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
    CpiDevice* Transfer();
    void Added(CpiDevice& aDevice);
    void Removed(CpiDevice& aDevice);
private:
    CpiDevice* iDevice;
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

CpiDevice* DevicePicker::Transfer()
{
    CpiDevice* ret = iDevice;
    ASSERT(ret != NULL);
    iDevice = NULL;
    return ret;
}

void DevicePicker::Added(CpiDevice& aDevice)
{
    if (iDevice == NULL) {
        iDevice = &aDevice;
        iDevice->AddRef();
    }
}

void DevicePicker::Removed(CpiDevice& /*aDevice*/)
{
}



extern "C" void OsNetworkSetTestInterfaceIndex(int32_t aIndex);
void setTestNifIndex(TInt aIndex, Blocker& aBlocker)
{
    OsNetworkSetTestInterfaceIndex(aIndex);
    aBlocker.Wait(1); /* sleep to leave room for the interface change to be processed
                       not completely reliable but using the current/subnet change listeners
                       would cause problems too as we've have to hard-code knowledge of
                       when they would/wouldn't be run */
    NetworkInterface* nif = Stack::NetworkInterfaceList().CurrentInterface();
    TIpAddress addr = (nif==NULL? 0 : nif->Address());
    delete nif;
    Print("Current network interface %d.%d.%d.%d\n\n", addr&0xff, (addr>>8)&0xff, (addr>>16)&0xff, (addr>>24)&0xff);
}


class PropertyLogger : public INonCopyable
{
public:
    PropertyLogger(Blocker& aBlocker);
    ~PropertyLogger();
    void Test();
private:
    void Ready();
    void LogSinkProtocolInfo();
    void LogShuffle();
private:
    Blocker& iBlocker;
    DevicePicker iPicker;
    CpProxyUpnpOrgConnectionManager1* iConnMgr;
    CpProxyLinnCoUkPlaylist1* iPlayList;
    CpiDevice* iCmDevice;
    CpiDevice* iPlDevice;
};

PropertyLogger::PropertyLogger(Blocker& aBlocker)
    : iBlocker(aBlocker)
{
    // each property should be logged once initially
    Brn domainName("upnp.org");
    Brn type("ConnectionManager");
    FunctorCpiDevice added = MakeFunctorCpiDevice(iPicker, &DevicePicker::Added);
    FunctorCpiDevice removed = MakeFunctorCpiDevice(iPicker, &DevicePicker::Removed);
    CpiDeviceList* deviceList = new CpiDeviceListUpnpServiceType(domainName, type, 1, 2, added, removed);
    deviceList->Start();
    iBlocker.Wait(1);
    iCmDevice = iPicker.Transfer();
    delete deviceList;
    Functor functor = MakeFunctor(*this, &PropertyLogger::Ready);
    Print("\nTesting subscriptions...\n\n");
    iConnMgr = new CpProxyUpnpOrgConnectionManager1(*iCmDevice, functor);
    iConnMgr->Subscribe();

    domainName.Set("linn.co.uk");
    type.Set("Playlist");
    deviceList = new CpiDeviceListUpnpServiceType(domainName, type, 1, added, removed);
    deviceList->Start();
    iBlocker.Wait(1);
    iPlDevice = iPicker.Transfer();
    delete deviceList;
    functor = MakeFunctor(*this, &PropertyLogger::Ready);
    iPlayList = new CpProxyLinnCoUkPlaylist1(*iPlDevice, functor);
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

    // select the first nig again.  No property changes should be logged
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

void PropertyLogger::Ready()
{
    Functor functor = MakeFunctor(*this, &PropertyLogger::LogSinkProtocolInfo);
    iConnMgr->SetPropertySinkProtocolInfoChanged(functor);
}

void PropertyLogger::LogSinkProtocolInfo()
{
    Brh info;
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


void Zapp::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], InitialisationParams* aInitParams)
{
    UpnpLibrary::Initialise(aInitParams);
    UpnpLibrary::StartCp();
    Debug::SetLevel(Debug::kNone);

    Blocker* blocker = new Blocker;

    // generate device list for arbitrarily chosen service
    DeviceListLogger logger;
    Brn domainName("linn.co.uk");
    Brn type("Radio");
    FunctorCpiDevice added = MakeFunctorCpiDevice(logger, &DeviceListLogger::Added);
    FunctorCpiDevice removed = MakeFunctorCpiDevice(logger, &DeviceListLogger::Removed);
    CpiDeviceList* deviceList = new CpiDeviceListUpnpServiceType(domainName, type, 1, added, removed);
    deviceList->Start();
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
    UpnpLibrary::Close();
}
