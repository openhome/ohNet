#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Net/Private/DviStack.h>
#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/OptionParser.h>
#include <OpenHome/Av/MediaPlayer.h>
#include <OpenHome/Net/Core/DvDevice.h>
#include <OpenHome/Media/DriverSongcastSender.h>
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
    OptionString optionRoom("-r", "--room", Brn("SoftPlayer"), "room the Product service will report");
    parser.AddOption(&optionRoom);
    OptionString optionName("-n", "--name", Brn("SoftPlayer"), "Product name");
    parser.AddOption(&optionName);
    OptionUint optionChannel("-c", "--channel", 0, "[0..65535] sender channel");
    parser.AddOption(&optionChannel);
    OptionUint optionAdapter("-a", "--adapter", 0, "[adapter] index of network adapter to use");
    parser.AddOption(&optionAdapter);
    OptionString optionTuneIn("-n", "--tunein", Brn("linnproducts"), "TuneIn user name");
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
    TIpAddress subnet = (*subnetList)[adapterIndex]->Subnet();
    TIpAddress adapter = (*subnetList)[adapterIndex]->Address();
    Library::DestroySubnetList(subnetList);
    lib->SetCurrentSubnet(subnet);
    Log::Print("using subnet %d.%d.%d.%d\n", subnet&0xff, (subnet>>8)&0xff, (subnet>>16)&0xff, (subnet>>24)&0xff);

    Bwh udn("TestMediaPlayer");
    RandomiseUdn(dvStack->Env(), udn);
    static const TUint kMaxDriverJiffies = Media::Jiffies::kJiffiesPerMs * 5;
    TestMediaPlayer* tmp = (*aFunc)(*dvStack, udn, optionRoom.CString(), optionName.CString(), kMaxDriverJiffies, optionTuneIn.CString());
    DriverSongcastSender* driver = new DriverSongcastSender(tmp->Pipeline(), kMaxDriverJiffies, dvStack->Env(), *(tmp->Device()), udn, optionChannel.Value(), adapter, false /*unicast*/);
    tmp->AddAttribute("Sender");
    tmp->Run();
    delete tmp;
    delete driver;
    
    delete lib;

    return 0;
}
