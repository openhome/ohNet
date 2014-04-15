#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Net/Private/DviStack.h>
#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/OptionParser.h>
#include <OpenHome/Av/MediaPlayer.h>
#include <OpenHome/Net/Core/DvDevice.h>
#include <OpenHome/Media/DriverBasic.h>
#include <OpenHome/Media/PipelineManager.h>
#include "TestMediaPlayer.h"
#include <OpenHome/Private/Printer.h>

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Av;
using namespace OpenHome::Media;
using namespace OpenHome::Net;

int OpenHome::Av::Test::ExecuteTestMediaPlayer(int aArgc, char* aArgv[], CreateMediaPlayerFunc aFunc)
{
    OptionParser parser;
    OptionString optionRoom("-r", "--room", Brn(""), "room the Product service will report");
    parser.AddOption(&optionRoom);
    OptionString optionName("-n", "--name", Brn("SoftPlayer"), "Product name");
    parser.AddOption(&optionName);
    OptionUint optionChannel("-c", "--channel", 0, "[0..65535] sender channel");
    parser.AddOption(&optionChannel);
    OptionUint optionAdapter("-a", "--adapter", 0, "[adapter] index of network adapter to use");
    parser.AddOption(&optionAdapter);
    OptionString optionTuneIn("-t", "--tunein", Brn("linnproducts"), "TuneIn user name");
    parser.AddOption(&optionTuneIn);

    if (!parser.Parse(aArgc, aArgv)) {
        return 1;
    }

    InitialisationParams* initParams = InitialisationParams::Create();
    initParams->SetDvEnableBonjour();
//    initParams->SetUseLoopbackNetworkAdapter();
    //Debug::SetLevel(Debug::kDvEvent);
    Net::Library* lib = new Net::Library(initParams);
    Net::DvStack* dvStack = lib->StartDv();
    std::vector<NetworkAdapter*>* subnetList = lib->CreateSubnetList();
    const TUint adapterIndex = optionAdapter.Value();
    if (subnetList->size() <= adapterIndex) {
        Log::Print("ERROR: adapter %u doesn't exist\n", adapterIndex);
        ASSERTS();
    }
    Log::Print ("adapter list:\n");
    for (unsigned i=0; i<subnetList->size(); ++i) {
        TIpAddress addr = (*subnetList)[i]->Address();
        Log::Print ("  %d: %d.%d.%d.%d\n", i, addr&0xff, (addr>>8)&0xff, (addr>>16)&0xff, (addr>>24)&0xff);
    }
    TIpAddress address = (*subnetList)[adapterIndex]->Address();
    TIpAddress subnet = (*subnetList)[adapterIndex]->Subnet();
    Library::DestroySubnetList(subnetList);
    lib->SetCurrentSubnet(subnet);
    Log::Print("using subnet %d.%d.%d.%d\n", subnet&0xff, (subnet>>8)&0xff, (subnet>>16)&0xff, (subnet>>24)&0xff);

    const Brx& room = optionRoom.Value();
    if (room == Brx::Empty()) {
        Log::Print("ERROR: room must be set\n");
        ASSERTS();
    }
    // Re-seed random number generator with hash of (unique) room name + UPnP
    // device server port to avoid UDN clashes.
    DviServerUpnp& dvServerUpnp = dvStack->ServerUpnp();
    TUint port = dvServerUpnp.Port(address);
    Log::Print("UPnP DV server using port: %u\n", port);
    Environment& env = dvStack->Env();
    TUint hash = 0;
    for (TUint i=0; i<room.Bytes(); i++) {
        hash += room[i];
    }
    hash += port;
    env.SetRandomSeed(hash);

    Bwh udn("TestMediaPlayer");
    RandomiseUdn(env, udn);
    static const TUint kMaxDriverJiffies = Media::Jiffies::kJiffiesPerMs * 5;
    TestMediaPlayer* tmp = (*aFunc)(*dvStack, udn, optionRoom.CString(), optionName.CString(), kMaxDriverJiffies, optionTuneIn.CString());
    DriverBasic* driver = new DriverBasic(tmp->Pipeline(), dvStack->Env());
    tmp->Run();
    tmp->StopPipeline();
    delete driver;
    delete tmp;
    
    delete lib;

    return 0;
}
