#include <OpenHome/Types.h>
#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/OptionParser.h>
#include <OpenHome/Net/Core/OhNet.h>
#include <OpenHome/Net/Private/MdnsProvider.h>

#include <vector>

using namespace OpenHome;
using namespace OpenHome::Net;

class MdnsDeviceLogger : public IMdnsDeviceListener
{
public:
    MdnsDeviceLogger();
    // IMdnsDeviceListener
    void DeviceAdded(MdnsDevice& aDev);
private:
    void PrintDeviceInfo(const char* aPrologue, MdnsDevice& aDev);
private:
    Mutex iLock;
};

MdnsDeviceLogger::MdnsDeviceLogger()
    : iLock("DLMD")
{
}

void MdnsDeviceLogger::DeviceAdded(MdnsDevice& aDev)
{
    PrintDeviceInfo("Added", aDev);
}


void MdnsDeviceLogger::PrintDeviceInfo(const char* aPrologue, MdnsDevice& aDev)
{
    iLock.Wait();
    Log::Print("%s (%.*s)    %.*s (%.*s) %.*s:%d\n", aPrologue, PBUF(aDev.Type()), PBUF(aDev.FriendlyName()), PBUF(aDev.UglyName()), PBUF(aDev.IpAddress()), aDev.Port());
    iLock.Signal();
}

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
    //Debug::SetLevel(Debug::kBonjour);
    //Debug::SetSeverity(Debug::kSeverityTrace);

    Bws<Endpoint::kMaxAddressBytes> addr;
    Endpoint::AppendAddress(addr, subnet);
    Log::Print("Subnet in use: ");
    Log::Print(addr);
    Log::Print("\n");
    
    // combined
    CpStack* cpStack = NULL;
    DvStack* dvStack = NULL;
    lib->StartCombined(subnet, cpStack, dvStack);

    MdnsDeviceLogger logger;
    lib->Env().MdnsProvider()->AddMdnsDeviceListener(&logger);
    Log::Print("Finding odp mDNS devices...\n");
    lib->Env().MdnsProvider()->FindDevices("_odp._tcp");
    Thread::Sleep(10 * 1000);
    Log::Print("Finding raop mDNS devices...\n");
    lib->Env().MdnsProvider()->FindDevices("_raop._tcp");
    Thread::Sleep(10 * 1000);
    Log::Print("Finding spotify-connect mDNS devices...\n");
    lib->Env().MdnsProvider()->FindDevices("_spotify-connect._tcp");
    Thread::Sleep(10 * 1000);

    delete lib;
}
