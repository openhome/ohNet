// Simple test for Control Point side device list
// Looks suspiciously similar to TestSsdpUListen for now...
//

#include <TestFramework.h>
#include <OptionParser.h>
#include <ZappTypes.h>
#include <Thread.h>
#include <Ssdp.h>
#include <Core/CpDeviceUpnp.h>
#include <Core/FunctorCpDevice.h>
#include <XmlParser.h>

using namespace Zapp;
using namespace Zapp::TestFramework;

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


void Zapp::TestFramework::Runner::Main(TInt aArgc, TChar* aArgv[], InitialisationParams* aInitParams)
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
        aInitParams->SetUseLoopbackNetworkInterface();
    }
    UpnpLibrary::Initialise(aInitParams);
    UpnpLibrary::StartCp();

    Brn domainName;
    Brn type;
    TUint ver;
    if (Zapp::Ssdp::ParseUrnService(service.Value(), domainName, type, ver)) {
        DeviceListLogger logger;
        FunctorCpDevice added = MakeFunctorCpDevice(logger, &DeviceListLogger::Added);
        FunctorCpDevice removed = MakeFunctorCpDevice(logger, &DeviceListLogger::Removed);
        CpDeviceList* deviceList = new CpDeviceListUpnpServiceType(domainName, type, ver, added, removed);
        Blocker* blocker = new Blocker;
        blocker->Wait(aInitParams->MsearchTimeSecs());
        delete blocker;
        delete deviceList;
    }
    else {
        parser.DisplayHelp();
    }

    UpnpLibrary::Close();
}
