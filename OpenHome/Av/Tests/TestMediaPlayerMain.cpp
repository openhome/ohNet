#include "TestMediaPlayer.h"
#include <OpenHome/Types.h>
#include <OpenHome/Media/Tests/Cdecl.h>
#include <OpenHome/Media/Tests/GetCh.h>
#include <OpenHome/Net/Private/DviStack.h>
#include <OpenHome/Media/Utils/AnimatorBasic.h>
#include <OpenHome/Media/PipelineManager.h>

#include <stdlib.h>

using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Av::Test;
using namespace OpenHome::Net;

int CDECL main(int aArgc, char* aArgv[])
{
#ifdef _WIN32
    char* noErrDlgs = getenv("NO_ERROR_DIALOGS");
    if (noErrDlgs != nullptr && strcmp(noErrDlgs, "1") == 0) {
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
    Media::PriorityArbitratorAnimator arbAnimator(kPrioritySystemHighest);
    ThreadPriorityArbitrator& priorityArbitrator = lib->Env().PriorityArbitrator();
    priorityArbitrator.Add(arbAnimator);
    Media::PriorityArbitratorPipeline arbPipeline(kPrioritySystemHighest-1);
    priorityArbitrator.Add(arbPipeline);
    const TChar* cookie ="TestMediaPlayerMain";
    NetworkAdapter* adapter = lib->CurrentSubnetAdapter(cookie);
    Net::DvStack* dvStack = lib->StartDv();

    // Seed random number generator.
    TestMediaPlayerInit::SeedRandomNumberGenerator(dvStack->Env(), options.Room().Value(), adapter->Address(), dvStack->ServerUpnp());
    adapter->RemoveRef(cookie);

    // Set/construct UDN.
    Bwh udn;
    // FIXME - 4c494e4e- prefix to udn is temporary measure to allow Linn Konfig to recognise our devices
    TestMediaPlayerInit::AppendUniqueId(dvStack->Env(), options.Udn().Value(), Brn("4c494e4e-TestMediaPlayer"), udn);

    // Create TestMediaPlayer.
    TestMediaPlayer* tmp = new TestMediaPlayer(*dvStack, udn, options.Room().CString(), options.Name().CString(),
                                               options.TuneIn().Value(), options.Tidal().Value(), options.Qobuz().Value(),
                                               options.UserAgent().Value());
    Media::AnimatorBasic* animator = new Media::AnimatorBasic(dvStack->Env(), tmp->Pipeline());
    tmp->SetPullableClock(*animator);
    tmp->Run();
    tmp->StopPipeline();
    delete animator;
    delete tmp;

    delete lib;

    return 0;
}
