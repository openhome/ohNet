#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/OptionParser.h>
#include <OpenHome/Media/PipelineManager.h>
#include <OpenHome/Media/Codec/Flac.h>
#include <OpenHome/Media/Codec/Wav.h>
#include <OpenHome/Media/DriverSongcastSender.h>
#include <OpenHome/Media/Msg.h>
#include <OpenHome/Av/InfoProvider.h>
#include <OpenHome/Net/Core/OhNet.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Private/Terminal.h>
#include "AllocatorInfoLogger.h"

#include "FileSender.h"

#ifdef _WIN32
#define CDECL __cdecl
#else
#define CDECL 
#endif

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Media;
using namespace OpenHome::Net;

int CDECL main(int aArgc, char* aArgv[])
{
    OptionParser parser;
    OptionString optionFile("-f", "--file", Brn(""), "[file] flac/wav file to play");
    parser.AddOption(&optionFile);
    OptionString optionUdn("-u", "--udn", Brn("PipelineFileSender"), "[udn] udn for the upnp device");
    parser.AddOption(&optionUdn);
    OptionString optionName("-n", "--name", Brn("Pipeline FileSender"), "[name] name of the sender");
    parser.AddOption(&optionName);
    OptionUint optionChannel("-c", "--channel", 0, "[0..65535] sender channel");
    parser.AddOption(&optionChannel);
    OptionUint optionAdapter("-a", "--adapter", 0, "[adapter] index of network adapter to use");
    parser.AddOption(&optionAdapter);
    OptionBool optionMulticast("-m", "--multicast", "use multicast protocol (default is unicast)");
    parser.AddOption(&optionMulticast);

    if (!parser.Parse(aArgc, aArgv)) {
        return 1;
    }

    InitialisationParams* initParams = InitialisationParams::Create();
    Net::Library* lib = new Net::Library(initParams);
    Net::DvStack* dvStack = lib->StartDv();
    std::vector<NetworkAdapter*>* subnetList = lib->CreateSubnetList();
    const TUint adapterIndex = optionAdapter.Value();
    if (subnetList->size() <= adapterIndex) {
        Log::Print("ERROR: adapter %d doesn't exist\n", adapterIndex);
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

    int ret = 1;

    try {

        Terminal* terminal = new TerminalOs();

        FileSender* fileSender = new FileSender(lib->Env(),
            *terminal,
            *dvStack,
            optionFile.Value(),
            adapter,
            optionUdn.Value(),
            optionName.CString(),
            optionChannel.Value(),
            optionMulticast.Value());

        ret = fileSender->Run();

        delete fileSender;
        delete terminal;
    }
    catch ( FileOpenError ) {

        Log::Print("FileSender: Could not open file %s\n", optionFile.CString());
    }

    delete lib;
    return ret;
}
