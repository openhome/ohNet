// Simple test for Control Point side device list
// Looks suspiciously similar to TestSsdpUListen for now...
//

#include <TestFramework.h>
#include <OptionParser.h>
#include <ZappTypes.h>
#include <Discovery.h>
#include <Thread.h>
#include <Timer.h>
#include <Os.h>
#include "CpTopology2.h"

using namespace Zapp;
using namespace Zapp::TestFramework;

class TopologyLogger : public ICpTopology2Handler
{
public:
    TopologyLogger();
	virtual void GroupAdded(CpTopology2Group& aGroup);
	virtual void GroupStandbyChanged(CpTopology2Group& aGroup);
	virtual void GroupSourceIndexChanged(CpTopology2Group& aGroup);
	virtual void GroupSourceListChanged(CpTopology2Group& aGroup);
	virtual void GroupVolumeChanged(CpTopology2Group& aGroup);
	virtual void GroupMuteChanged(CpTopology2Group& aGroup);
	virtual void GroupRemoved(CpTopology2Group& aGroup);
private:
    void PrintGroupInfo(const char* aPrologue, const CpTopology2Group& aGroup);
    void PrintSourceInfo(const CpTopology2Group& aGroup);
};

TopologyLogger::TopologyLogger()
{
}

void TopologyLogger::GroupAdded(CpTopology2Group& aGroup)
{
    Print("\n");
    PrintGroupInfo("Group Added         ", aGroup);
    Print("\n");
    PrintSourceInfo(aGroup);
}

void TopologyLogger::GroupStandbyChanged(CpTopology2Group& aGroup)
{
    PrintGroupInfo("Standby Changed     ", aGroup);
    Print(aGroup.Standby() ? "true" : "false");
    Print("\n");
}

void TopologyLogger::GroupSourceIndexChanged(CpTopology2Group& aGroup)
{
    PrintGroupInfo("Source Index Changed", aGroup);
    Print("%u\n", aGroup.SourceIndex());
}

void TopologyLogger::GroupSourceListChanged(CpTopology2Group& aGroup)
{
    Print("\n");
    PrintGroupInfo("Source List Changed ", aGroup);
    Print("\n");
    PrintSourceInfo(aGroup);
}

void TopologyLogger::GroupVolumeChanged(CpTopology2Group& aGroup)
{
    PrintGroupInfo("Volume Changed      ", aGroup);
    Print("%u\n", aGroup.Volume());
}

void TopologyLogger::GroupMuteChanged(CpTopology2Group& aGroup)
{
    PrintGroupInfo("Mute Changed        ", aGroup);
    Print(aGroup.Mute() ? "true" : "false");
    Print("\n");
}

void TopologyLogger::GroupRemoved(CpTopology2Group& aGroup)
{
    PrintGroupInfo("Group Removed       ", aGroup);
    Print("\n");
}

void TopologyLogger::PrintSourceInfo(const CpTopology2Group& aGroup)
{
	TUint count = aGroup.SourceCount();

  	Print("===============================================\n");
	
	for (TUint i = 0; i < count; i++) {
    	Print("%u. ", i);
    	Print(aGroup.SourceName(i));
    	Print(" ");
    	Print(aGroup.SourceType(i));
    	Print(" ");
    	Print(aGroup.SourceVisible(i) ? "true" : "false");
    	Print("\n");
	}

  	Print("===============================================\n");
   	Print("\n");
}

void TopologyLogger::PrintGroupInfo(const char* aPrologue, const CpTopology2Group& aGroup)
{
    Print("%s ", aPrologue);
    Print(aGroup.Room());
    Print(":");
    Print(aGroup.Name());
    Print(" ");
}


void Zapp::TestFramework::Runner::Main(TInt aArgc, TChar* aArgv[], InitialisationParams* aInitParams)
{
    OptionParser parser;

    OptionUint duration("-d", "--duration", 30, "Number of seconds to run the test");
    OptionUint network("-n", "--network", 0, "Index of the network to use");

    parser.AddOption(&duration);
    parser.AddOption(&network);

    if (!parser.Parse(aArgc, aArgv) || parser.HelpDisplayed()) {
        return;
    }

    UpnpLibrary::Initialise(aInitParams);
    UpnpLibrary::StartCp();
    
    static std::vector<NetworkInterface*>* subnetList = UpnpLibrary::SubnetList();

    if (network.Value() >= subnetList->size()) {
        Print("Invalid network specified. Available networks ...\n");
	    for (TUint i = 0; i < subnetList->size(); i++) {
	    	Print("%u. %s\n", i, subnetList->at(i)->Name());
	    }
        return;
    }

    UpnpLibrary::SetCurrentSubnet(*subnetList->at(network.Value()));

    // Debug::SetLevel(Debug::kTopology);
    // Debug::SetLevel(Debug::kAll);

    TopologyLogger logger;

    CpTopology2* topology = new CpTopology2(logger);

    if (topology != NULL) {
        Blocker* blocker = new Blocker;
        blocker->Wait(duration.Value());
        delete blocker;
    }

    delete topology;

    UpnpLibrary::Close();
}
