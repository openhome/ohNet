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
    virtual void GroupAdded(CpTopology3Group& aGroup);
    virtual void GroupStandbyChanged(CpTopology3Group& aGroup);
    virtual void GroupSourceIndexChanged(CpTopology3Group& aGroup);
    virtual void GroupSourceListChanged(CpTopology3Group& aGroup);
    virtual void GroupRemoved(CpTopology3Group& aDevice);
	virtual void GroupVolumeControlChanged(CpTopology3Group& aDevice);
	virtual void GroupVolumeChanged(CpTopology3Group& aDevice);
	virtual void GroupMuteChanged(CpTopology3Group& aDevice);
	virtual void GroupVolumeLimitChanged(CpTopology3Group& aDevice);
private:
    void PrintGroupInfo(const char* aPrologue, const CpTopology3Group& aGroup);
    void PrintSourceInfo(const CpTopology3Group& aGroup);
};

TopologyLogger::TopologyLogger()
{
}

void TopologyLogger::GroupAdded(CpTopology3Group& aGroup)
{
    Print("\n");
    PrintGroupInfo("Group Added         ", aGroup);
    Print("\n");
    PrintSourceInfo(aGroup);
}

void TopologyLogger::GroupStandbyChanged(CpTopology3Group& aGroup)
{
    PrintGroupInfo("Standby Changed     ", aGroup);
    Print(aGroup.Standby() ? "true" : "false");
    Print("\n");
}

void TopologyLogger::GroupSourceIndexChanged(CpTopology3Group& aGroup)
{
    PrintGroupInfo("Source Index Changed", aGroup);
    Print("%u\n", aGroup.SourceIndex());
}

void TopologyLogger::GroupSourceListChanged(CpTopology3Group& aGroup)
{
    Print("\n");
    PrintGroupInfo("Source List Changed ", aGroup);
    Print("\n");
    PrintSourceInfo(aGroup);
}

void TopologyLogger::GroupRemoved(CpTopology3Group& aGroup)
{
    PrintGroupInfo("Group Removed       ", aGroup);
    Print("\n");
}

void TopologyLogger::GroupVolumeControlChanged(CpTopology3Group& aGroup)
{
    PrintGroupInfo("Vol Control Changed ", aGroup);
    aGroup.HasVolumeControl() ? printf("Yes\n") : printf("No\n");
	if(aGroup.HasVolumeControl())
	{
		Print("Vol      ");
		Bws<Ascii::kMaxUintStringBytes> bufferVol;
		Ascii::AppendDec(bufferVol, aGroup.Volume());
		Print(bufferVol);
		Print("\n");
		Print("Mute      ");
		Bws<Ascii::kMaxUintStringBytes> bufferMute;
		Ascii::AppendDec(bufferMute, aGroup.Mute());
		Print(bufferMute);
		Print("\n");
		Print("Vol Limit      ");
		Bws<Ascii::kMaxUintStringBytes> bufferVolLim;
		Ascii::AppendDec(bufferVolLim, aGroup.VolumeLimit());
		Print(bufferVolLim);
		Print("\n");
	}
}

void TopologyLogger::GroupVolumeChanged(CpTopology3Group& aGroup)
{
	PrintGroupInfo("Vol Changed      ", aGroup);
	Bws<Ascii::kMaxUintStringBytes> buffer;
	Ascii::AppendDec(buffer, aGroup.Volume());
    Print(buffer);
    Print("\n");
}

void TopologyLogger::GroupMuteChanged(CpTopology3Group& aGroup)
{
	PrintGroupInfo("Mute Changed      ", aGroup);
	Bws<Ascii::kMaxUintStringBytes> buffer;
	Ascii::AppendDec(buffer, aGroup.Mute());
    Print(buffer);
    Print("\n");
}

void TopologyLogger::GroupVolumeLimitChanged(CpTopology3Group& aGroup)
{
	PrintGroupInfo("Vol Limit Changed      ", aGroup);
    Bws<Ascii::kMaxUintStringBytes> buffer;
	Ascii::AppendDec(buffer, aGroup.VolumeLimit());
    Print(buffer);
    Print("\n");
}

void TopologyLogger::PrintSourceInfo(const CpTopology3Group& aGroup)
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

void TopologyLogger::PrintGroupInfo(const char* aPrologue, const CpTopology3Group& aGroup)
{
    Print("%s ", aPrologue);
    Print(aGroup.Room());
    Print(":");
    Print(aGroup.Name());
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
