#include <TestFramework.h>
#include <OptionParser.h>
#include <ZappTypes.h>
#include <Std/DvDevice.h>
#include <Zapp.h>
#include <Std/TestBasicDv.h>

#include <stdlib.h>
#include <vector>
#include <sys/stat.h>

using namespace Zapp;
using namespace Zapp::TestFramework;

void Zapp::TestFramework::Runner::Main(TInt aArgc, TChar* aArgv[], InitialisationParams* aInitParams)
{
    OptionParser parser;
    Brn emptyString("");
    OptionBool loopback("-l", "--loopback", "Use the loopback adapter only");
    parser.AddOption(&loopback);
    if (!parser.Parse(aArgc, aArgv) || parser.HelpDisplayed()) {
        return;
    }
    if (loopback.Value()) {
        aInitParams->SetUseLoopbackNetworkInterface();
    }
    UpnpLibrary::Initialise(aInitParams);
    UpnpLibrary::StartDv();

    Print("TestPerformanceDv - starting ('q' to quit)\n");
    DeviceBasic* device = new DeviceBasic();
    while (getchar() != 'q');
    delete device;
    Print("TestPerformanceDv - exiting\n");

    UpnpLibrary::Close();
}
