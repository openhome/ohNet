// Manual test program for exercising Topology Layer 1
//

#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/OptionParser.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Net/Private/Discovery.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Timer.h>
#include <OpenHome/OsWrapper.h>
#include "CpTopology1.h"

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::TestFramework;

class TopologyLogger : public ICpTopology1Handler
{
public:
    TopologyLogger();
    virtual void ProductAdded(CpDevice& aDevice);
    virtual void ProductRemoved(CpDevice& aDevice);
    virtual void UpnpAdded(CpDevice& aDevice);
    virtual void UpnpRemoved(CpDevice& aDevice);
private:
    void PrintDeviceInfo(const char* aPrologue, const CpDevice& aDevice);
};

TopologyLogger::TopologyLogger()
{
}

void TopologyLogger::ProductAdded(CpDevice& aDevice)
{
    PrintDeviceInfo("Product Added", aDevice);
}

void TopologyLogger::ProductRemoved(CpDevice& aDevice)
{
    PrintDeviceInfo("Product Removed", aDevice);
}

void TopologyLogger::UpnpAdded(CpDevice& aDevice)
{
    PrintDeviceInfo("Upnp Added", aDevice);
}

void TopologyLogger::UpnpRemoved(CpDevice& aDevice)
{
    PrintDeviceInfo("Upnp Removed", aDevice);
}

void TopologyLogger::PrintDeviceInfo(const char* aPrologue, const CpDevice& aDevice)
{
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
}


void OpenHome::TestFramework::Runner::Main(TInt aArgc, TChar* aArgv[], InitialisationParams* aInitParams)
{
    OptionParser parser;
    OptionUint mx("-mx", "--mx", 1, "[1..5] number of second to spread response over");
    parser.AddOption(&mx);
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

    // Debug::SetLevel(Debug::kTopology);
    // Debug::SetLevel(Debug::kAll);

    TopologyLogger logger;

    CpTopology1* topology = new CpTopology1(logger);

    if (topology != NULL) {
        Blocker* blocker = new Blocker;
        blocker->Wait(aInitParams->MsearchTimeSecs());
        delete blocker;
    }
    if (refresh.Value()) {
        Blocker* blocker = new Blocker;
        blocker->Wait(mx.Value());
        Print("\nRefreshing...\n\n");
        topology->Refresh();
        blocker->Wait(mx.Value());
        delete blocker;
    }
    
    delete topology;

    UpnpLibrary::Close();
}
