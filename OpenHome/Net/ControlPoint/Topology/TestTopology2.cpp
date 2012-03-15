// Manual test program for exercising Topology Layer 2
//

#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/OptionParser.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Net/Private/Discovery.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Timer.h>
#include <OpenHome/OsWrapper.h>
#include "CpTopology2.h"

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::TestFramework;

class TopologyLogger : public ICpTopology2Handler
{
public:
    TopologyLogger();

    virtual void GroupAdded(CpTopology2Group& aGroup);
    virtual void GroupStandbyChanged(CpTopology2Group& aGroup);
    virtual void GroupSourceIndexChanged(CpTopology2Group& aGroup);
    virtual void GroupSourceListChanged(CpTopology2Group& aGroup);
    virtual void GroupRemoved(CpTopology2Group& aDevice);

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
    std::vector<NetworkAdapter*>* ifs = Os::NetworkListAdapters(false, "TestTopology2");
    ASSERT(ifs->size() > 0 && adapter.Value() < ifs->size());
    TIpAddress subnet = (*ifs)[adapter.Value()]->Subnet();
    for (TUint i=0; i<ifs->size(); i++) {
        (*ifs)[i]->RemoveRef("TestTopology2");
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

    CpTopology2* topology = new CpTopology2(logger);

    if (topology != NULL) {
        Blocker* blocker = new Blocker;
        blocker->Wait(duration.Value());
        delete blocker;
    }

    delete topology;

    UpnpLibrary::Close();
}
