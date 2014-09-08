#include <OpenHome/Types.h>
#include <OpenHome/Net/Private/DviStack.h>
#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/OptionParser.h>
#include <OpenHome/Av/MediaPlayer.h>
#include <OpenHome/Net/Core/DvDevice.h>
#include <OpenHome/Media/Utils/DriverBasic.h>
#include <OpenHome/Media/PipelineManager.h>
#include "TestMediaPlayer.h"
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Av/Debug.h>
#include <OpenHome/Media/Debug.h>

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Av;
using namespace OpenHome::Media;
using namespace OpenHome::Net;

int OpenHome::Av::Test::ExecuteTestMediaPlayer(int aArgc, char* aArgv[], CreateMediaPlayerFunc aFunc)
{
    // Parse options.
    TestMediaPlayerOptions options;
    if (!options.Parse(aArgc, aArgv)) {
        return 1;
    }

    // Create lib.
    Library* lib = TestMediaPlayerInit::CreateLibrary(options.Loopback().Value(), options.Adapter().Value());
    const TChar* cookie ="TestMediaPlayerMain";
    NetworkAdapter* adapter = lib->CurrentSubnetAdapter(cookie);
    TUint subnet = adapter->Subnet();
    Net::CpStack* cpStack = NULL;
    Net::DvStack* dvStack = NULL;
    lib->StartCombined(subnet, cpStack, dvStack);

    // Seed random number generator.
    TestMediaPlayerInit::SeedRandomNumberGenerator(dvStack->Env(), options.Room().Value(), adapter->Address(), dvStack->ServerUpnp());
    adapter->RemoveRef(cookie);

    // Set/construct UDN.
    Bwh udn;
    TestMediaPlayerInit::AppendUniqueId(dvStack->Env(), options.Udn().Value(), Brn("TestMediaPlayer"), udn);

    // Create TestMediaPlayer.
    DriverBasic* driver = new DriverBasic(dvStack->Env());
    TestMediaPlayer* tmp = (*aFunc)(*cpStack, *dvStack, udn, options.Room().CString(), options.Name().CString(), options.TuneIn().CString(), NULL/*driver*/);
    driver->SetPipeline(tmp->Pipeline());
    tmp->Run();
    tmp->StopPipeline();
    delete driver;
    delete tmp;

    delete lib;

    return 0;
}
