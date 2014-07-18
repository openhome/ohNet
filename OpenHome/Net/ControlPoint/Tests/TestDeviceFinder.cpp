// Simple test for Control Point side device list
// Looks suspiciously similar to TestSsdpUListen for now...
//

#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/OptionParser.h>
#include <OpenHome/Types.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Net/Private/Ssdp.h>
#include <OpenHome/Net/Core/CpDeviceUpnp.h>
#include <OpenHome/Net/Core/FunctorCpDevice.h>
#include <OpenHome/Net/Private/XmlParser.h>
#include <OpenHome/Net/Private/Globals.h>

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
    Mutex iLock;
};

DeviceListLogger::DeviceListLogger()
    : iLock("DLLM")
{
}

void DeviceListLogger::Added(CpDevice& aDevice)
{
    Brh xml;
    (void)aDevice.GetAttribute("Upnp.DeviceXml", xml);
    Brn presentationUrl = XmlParserBasic::Find("presentationURL", xml);
    iLock.Wait();
    Print(presentationUrl);
    Print("\n");
    iLock.Signal();
}

void DeviceListLogger::Removed(CpDevice& /*aDevice*/)
{
}


void OpenHome::TestFramework::Runner::Main(TInt aArgc, TChar* aArgv[], InitialisationParams* aInitParams)
{
    OptionParser parser;
    OptionString service("-s", "--service", Brn(""), "Search for a service of the form [domain]:service:[type]:[ver]");
    parser.AddOption(&service);
    OptionBool loopback("-l", "--loopback", "Use the loopback adapter only");
    parser.AddOption(&loopback);
    if (!parser.Parse(aArgc, aArgv) || parser.HelpDisplayed()) {
        return;
    }

    if (loopback.Value()) {
        aInitParams->SetUseLoopbackNetworkAdapter();
    }
    UpnpLibrary::Initialise(aInitParams);
    std::vector<NetworkAdapter*>* subnetList = UpnpLibrary::CreateSubnetList();
    TIpAddress subnet = (*subnetList)[0]->Subnet();
    UpnpLibrary::DestroySubnetList(subnetList);
    UpnpLibrary::StartCp(subnet);

    Brn domainName;
    Brn type;
    TUint ver;
    if (OpenHome::Net::Ssdp::ParseUrnService(service.Value(), domainName, type, ver)) {
        DeviceListLogger logger;
        FunctorCpDevice added = MakeFunctorCpDevice(logger, &DeviceListLogger::Added);
        FunctorCpDevice removed = MakeFunctorCpDevice(logger, &DeviceListLogger::Removed);
        CpDeviceList* deviceList = new CpDeviceListUpnpServiceType(*gCpStack, domainName, type, ver, added, removed);
        Blocker* blocker = new Blocker(*gEnv);
        blocker->Wait(aInitParams->MsearchTimeSecs());
        delete blocker;
        delete deviceList;
    }
    else {
        parser.DisplayHelp();
    }

    UpnpLibrary::Close();
}
