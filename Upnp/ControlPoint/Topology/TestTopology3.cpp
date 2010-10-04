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
#include "CpTopology3.h"

using namespace Zapp;
using namespace Zapp::TestFramework;

class TopologyLogger : public ICpTopology3Handler
{
public:
    TopologyLogger();
	virtual void RoomAdded(CpTopology3Room& aRoom);
	virtual void RoomStandbyChanged(CpTopology3Room& aRoom);
	virtual void RoomSourceIndexChanged(CpTopology3Room& aRoom);
	virtual void RoomSourceListChanged(CpTopology3Room& aRoom);
	virtual void RoomVolumeChanged(CpTopology3Room& aRoom);
	virtual void RoomMuteChanged(CpTopology3Room& aRoom);
	virtual void RoomRemoved(CpTopology3Room& aRoom);
private:
    void PrintRoomInfo(const char* aPrologue, const CpTopology3Room& aRoom);
    void PrintSourceInfo(const CpTopology3Room& aRoom);
};

TopologyLogger::TopologyLogger()
{
}

void TopologyLogger::RoomAdded(CpTopology3Room& aRoom)
{
    Print("\n");
    PrintRoomInfo("Room Added         ", aRoom);
    Print("\n");
    PrintSourceInfo(aRoom);
}

void TopologyLogger::RoomStandbyChanged(CpTopology3Room& aRoom)
{
    PrintRoomInfo("Standby Changed     ", aRoom);
    Print(aRoom.Standby() ? "true" : "false");
    Print("\n");
}

void TopologyLogger::RoomSourceIndexChanged(CpTopology3Room& aRoom)
{
    PrintRoomInfo("Source Index Changed", aRoom);
    Print("%u\n", aRoom.SourceIndex());
}

void TopologyLogger::RoomSourceListChanged(CpTopology3Room& aRoom)
{
    Print("\n");
    PrintRoomInfo("Source List Changed ", aRoom);
    Print("\n");
    PrintSourceInfo(aRoom);
}

void TopologyLogger::RoomVolumeChanged(CpTopology3Room& aRoom)
{
    PrintRoomInfo("Volume Changed      ", aRoom);
    Print("%u\n", aRoom.Volume());
}

void TopologyLogger::RoomMuteChanged(CpTopology3Room& aRoom)
{
    PrintRoomInfo("Mute Changed        ", aRoom);
    Print(aRoom.Mute() ? "true" : "false");
    Print("\n");
}

void TopologyLogger::RoomRemoved(CpTopology3Room& aRoom)
{
    PrintRoomInfo("Room Removed       ", aRoom);
    Print("\n");
}

void TopologyLogger::PrintSourceInfo(const CpTopology3Room& aRoom)
{
	TUint count = aRoom.SourceCount();

  	Print("===============================================\n");
	
	for (TUint i = 0; i < count; i++) {
    	Print("%u. ", i);
    	Print(aRoom.SourceName(i));
    	Print(" ");
    	Print(aRoom.SourceType(i));
    	Print("\n");
	}

  	Print("===============================================\n");
   	Print("\n");
}

void TopologyLogger::PrintRoomInfo(const char* aPrologue, const CpTopology3Room& aRoom)
{
    Print("%s ", aPrologue);
    Print(aRoom.Room());
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

    Debug::SetLevel(Debug::kTopology);
    // Debug::SetLevel(Debug::kAll);

    TopologyLogger logger;

    CpTopology3* topology = new CpTopology3(logger);

    if (topology != NULL) {
        Blocker* blocker = new Blocker;
        blocker->Wait(duration.Value());
        delete blocker;
    }

    delete topology;

    UpnpLibrary::Close();
}
