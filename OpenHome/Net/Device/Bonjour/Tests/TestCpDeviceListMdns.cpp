#include <OpenHome/Types.h>
#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/OptionParser.h>
#include <OpenHome/Net/Core/OhNet.h>
#include <OpenHome/Net/Private/MdnsProvider.h>

#include <vector>

using namespace OpenHome;
using namespace OpenHome::Net;

void OpenHome::TestFramework::Runner::Main(TInt aArgc, TChar* aArgv[], Net::InitialisationParams* aInitParams)
{
    OptionParser parser;
    OptionUint adapter("-a", "--adapter", 0, "[0...n] Adpater index to use");
    parser.AddOption(&adapter);
    if (!parser.Parse(aArgc, aArgv) || parser.HelpDisplayed()) {
        return;
    }

    aInitParams->SetDvEnableBonjour("Test-CpDevListMdns");
    Library* lib = new Library(aInitParams);
    std::vector<NetworkAdapter*>* subnetList = lib->CreateSubnetList();
    TIpAddress subnet = (*subnetList)[adapter.Value()]->Subnet();
    Library::DestroySubnetList(subnetList);
    Debug::SetLevel(Debug::kBonjour);
    Debug::SetSeverity(Debug::kSeverityTrace);

    Bws<Endpoint::kMaxAddressBytes> addr;
    Endpoint::AppendAddress(addr, subnet);
    Log::Print("Subnet in use: ");
    Log::Print(addr);
    Log::Print("\n");
    
    // combined
    CpStack* cpStack = NULL;
    DvStack* dvStack = NULL;
    lib->StartCombined(subnet, cpStack, dvStack);

    lib->Env().MdnsProvider()->FindDevices("_spotify-connect._tcp");
    Thread::Sleep(40 * 1000);

    delete lib;
}
