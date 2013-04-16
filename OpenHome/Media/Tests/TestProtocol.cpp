#include <OpenHome/Media/Tests/PipelineUtils.h>

#ifdef _WIN32
#define CDECL __cdecl
#else
#define CDECL
#endif

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::Media;
using namespace OpenHome::TestFramework;

int CDECL main(int aArgc, char* aArgv[])
{
    /* Useful test urls:
    http://10.2.9.146:26125/content/c2/b16/f44100/d2336-co13582.wav
    http://10.2.9.146:26125/content/c2/b16/f44100/d35587-co6318.flac
    http://10.2.9.146:26125/content/c2/b16/f44100/d40842-co4625.mp3
    file:///c:/test.wav
    http://10.2.11.131:9000/disk/NON-DLNA/music/O0$1$4I4009/Waiting%20for%20the%207.18.m4a  // alac
    http://10.2.11.174:26125/content/c2/b16/f48000/d2599-co459.m4a                          // aac
    */
    OptionParser parser;
    OptionString optionUrl("", "--url", Brn("http://10.2.9.146:26125/content/c2/b16/f44100/d2336-co13582.wav"), "[url] http url of file to play");
    parser.AddOption(&optionUrl);
    OptionString optionUdn("-u", "--udn", Brn("TestProtocol"), "[udn] udn for the upnp device");
    parser.AddOption(&optionUdn);
    OptionString optionName("-n", "--name", Brn("TestProtocol"), "[name] name of the sender");
    parser.AddOption(&optionName);
    OptionUint optionChannel("-c", "--channel", 0, "[0..65535] sender channel");
    parser.AddOption(&optionChannel);
    OptionUint optionAdapter("-a", "--adapter", 0, "[adapter] index of network adapter to use");
    parser.AddOption(&optionAdapter);

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

    TestProtocol* tph = new TestProtocol(lib->Env(), *dvStack, optionUrl.Value(), adapter, optionUdn.Value(), optionName.CString(), optionChannel.Value());
    const int ret = tph->Run();
    delete tph;
    
    delete lib;

    return ret;
}
