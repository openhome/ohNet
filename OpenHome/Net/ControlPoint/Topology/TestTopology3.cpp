// Manual test program for exercising Topology Layer 3
//

#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/OptionParser.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Net/Private/Discovery.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Timer.h>
#include <OpenHome/OsWrapper.h>
#include "CpTopology3.h"

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::TestFramework;

class TopologyLogger : public ICpTopology3Handler
{
public:
    TopologyLogger();
	virtual void RoomAdded(CpTopology3Room& aRoom);
    virtual void RoomChanged(CpTopology3Room& aRoom);
    virtual void RoomRemoved(CpTopology3Room& aRoom);
	virtual void RoomStandbyChanged(CpTopology3Room& aRoom);
	virtual void RoomSourceChanged(CpTopology3Room& aRoom);
	virtual void RoomVolumeControlChanged(CpTopology3Room& aRoom);
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

void TopologyLogger::RoomChanged(CpTopology3Room& aRoom)
{
    Print("\n");
    PrintRoomInfo("Source List Changed ", aRoom);
    Print("\n");
    PrintSourceInfo(aRoom);
}

void TopologyLogger::RoomRemoved(CpTopology3Room& aRoom)
{
    PrintRoomInfo("Room Removed        ", aRoom);
    Print("\n");
}

void TopologyLogger::RoomStandbyChanged(CpTopology3Room& aRoom)
{
    PrintRoomInfo("Standby Changed     ", aRoom);
	switch (aRoom.Standby()) {
	case CpTopology3Room::eOn:
		Print("On");
		break;
	case CpTopology3Room::eMixed:
		Print("Mixed");
		break;
	case CpTopology3Room::eOff:
		Print("Off");
		break;
	}
    Print("\n");
}

void TopologyLogger::RoomSourceChanged(CpTopology3Room& aRoom)
{
    PrintRoomInfo("Source Changed      ", aRoom);
    Print(aRoom.CurrentSourceName());
    Print("\n");
}

void TopologyLogger::RoomVolumeControlChanged(CpTopology3Room& aRoom)
{
    PrintRoomInfo("Vol Control Changed ", aRoom);
	aRoom.HasVolumeControl() ? printf("Yes\n") : printf("No\n");
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
    Print(aRoom.Name());
    Print(" ");
}


void OpenHome::TestFramework::Runner::Main(TInt aArgc, TChar* aArgv[], InitialisationParams* aInitParams)
{
    OptionParser parser;

    OptionUint duration("-d", "--duration", 30, "Number of seconds to run the test");
    OptionUint adapter("-i", "--interface", 0, "index of network adapter to use");

    parser.AddOption(&duration);
    parser.AddOption(&adapter);

    if (!parser.Parse(aArgc, aArgv) || parser.HelpDisplayed()) {
        return;
    }

    UpnpLibrary::Initialise(aInitParams);
    std::vector<NetworkAdapter*>* ifs = Os::NetworkListAdapters(false, "TestTopology3");
    ASSERT(ifs->size() > 0 && adapter.Value() < ifs->size());
    TIpAddress subnet = (*ifs)[adapter.Value()]->Subnet();
    for (TUint i=0; i<ifs->size(); i++) {
        (*ifs)[i]->RemoveRef("TestTopology3");
    }
    delete ifs;
    UpnpLibrary::StartCp(subnet);

    Endpoint endpt(0, subnet);
    Endpoint::AddressBuf buf;
    endpt.AppendAddress(buf);
    Print("Using network interface %s\n\n", buf.Ptr());

    // Debug::SetLevel(Debug::kTopology);
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
