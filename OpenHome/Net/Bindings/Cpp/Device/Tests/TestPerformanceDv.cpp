#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/OptionParser.h>
#include <OpenHome/Types.h>
#include <OpenHome/Net/Cpp/DvDevice.h>
#include <OpenHome/Net/Core/OhNet.h>
#include "TestBasicDv.h"
#include <OpenHome/Net/Private/Globals.h>

#include <stdlib.h>
#include <vector>
#include <sys/stat.h>

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::TestFramework;

void OpenHome::TestFramework::Runner::Main(TInt aArgc, TChar* aArgv[], InitialisationParams* aInitParams)
{
    OptionParser parser;
    Brn emptyString("");
    OptionBool loopback("-l", "--loopback", "Use the loopback adapter only");
    parser.AddOption(&loopback);
    if (!parser.Parse(aArgc, aArgv) || parser.HelpDisplayed()) {
        return;
    }
    if (loopback.Value()) {
        aInitParams->SetUseLoopbackNetworkAdapter();
    }
    UpnpLibrary::Initialise(aInitParams);
    UpnpLibrary::StartDv();

    Print("TestPerformanceDv - starting ('q' to quit)\n");
    DeviceBasic* device = new DeviceBasic(*gEnv, DeviceBasic::eProtocolUpnp);
    while (getchar() != 'q');
    delete device;
    Print("TestPerformanceDv - exiting\n");

    UpnpLibrary::Close();
}
