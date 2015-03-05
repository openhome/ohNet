#include "TestMediaPlayer.h"
#include <OpenHome/Types.h>
#include <OpenHome/Media/Tests/Cdecl.h>
#include <OpenHome/Media/Tests/GetCh.h>
#include <OpenHome/Net/Private/DviStack.h>
#include <OpenHome/Media/Utils/DriverBasic.h>

#include <stdlib.h>

using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Av::Test;
using namespace OpenHome::Net;

int CDECL main(int aArgc, char* aArgv[])
{
#ifdef _WIN32
    char* noErrDlgs = getenv("NO_ERROR_DIALOGS");
    if (noErrDlgs != NULL && strcmp(noErrDlgs, "1") == 0) {
        _set_abort_behavior(0, _WRITE_ABORT_MSG | _CALL_REPORTFAULT);
    }
#endif // _WIN32

    // Parse options.
    TestMediaPlayerOptions options;
    if (!options.Parse(aArgc, aArgv)) {
        return 1;
    }

    // Create lib.
    Library* lib = TestMediaPlayerInit::CreateLibrary(options.Loopback().Value(), options.Adapter().Value());
    const TChar* cookie ="TestMediaPlayerMain";
    NetworkAdapter* adapter = lib->CurrentSubnetAdapter(cookie);
    Net::DvStack* dvStack = lib->StartDv();

    // Seed random number generator.
    TestMediaPlayerInit::SeedRandomNumberGenerator(dvStack->Env(), options.Room().Value(), adapter->Address(), dvStack->ServerUpnp());
    adapter->RemoveRef(cookie);

    // Set/construct UDN.
    Bwh udn;
    TestMediaPlayerInit::AppendUniqueId(dvStack->Env(), options.Udn().Value(), Brn("TestMediaPlayer"), udn);

    // Create TestMediaPlayer.
    Media::DriverBasic* driver = new Media::DriverBasic(dvStack->Env());
    TestMediaPlayer* tmp = new TestMediaPlayer(*dvStack, udn, options.Room().CString(), options.Name().CString(),
                                               options.TuneIn().Value(), options.Tidal().Value(), options.Qobuz().Value(),
                                               options.UserAgent().Value(), NULL/*driver*/, *driver);
    driver->SetPipeline(tmp->Pipeline());
    tmp->Run();
    tmp->StopPipeline();
    delete driver;
    delete tmp;

    delete lib;

    return 0;
}
