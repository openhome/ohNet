#include <OpenHome/Net/Private/ShellCommandWatchDog.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Private/Ascii.h>

using namespace OpenHome;
using namespace OpenHome::Net;


class ShellCommandWatchDog::WatchDog
{
public:
    WatchDog(TUint aTimeoutSeconds)
        : iMutex("wmtx")
        , iTimeoutSeconds(aTimeoutSeconds)
        , iRemainingSeconds(aTimeoutSeconds)
        , iThreadFunctor(NULL)
    {
        iThreadFunctor = new ThreadFunctor("wd", MakeFunctor(*this, &WatchDog::Run));
        iThreadFunctor->Start();
    }
    ~WatchDog()
    {
        delete iThreadFunctor;
    }
    void Feed()
    {
        AutoMutex a(iMutex);
        iRemainingSeconds = iTimeoutSeconds;
    }
    TInt RemainingSeconds()
    {
        AutoMutex a(iMutex);
        return iRemainingSeconds;
    }    
private:
    void Run()
    {
        for(;;)
        {
            Thread::Sleep(1000);
            Thread::CheckCurrentForKill();

            AutoMutex a(iMutex);
            iRemainingSeconds--;
            if ( iRemainingSeconds <= 0 )
                exit(-2);
        }
    }
private:
    Mutex           iMutex;
    TUint           iTimeoutSeconds;
    TInt            iRemainingSeconds;
    ThreadFunctor*  iThreadFunctor;
};

// ShellCommandWatchDog

static const TChar kShellCommandWatchDog[] = "watchdog";

ShellCommandWatchDog::ShellCommandWatchDog(Shell& aShell)
    : iShell(aShell)
    , iWatchDog(new WatchDog(5 * 60))
{
    iShell.AddCommandHandler(kShellCommandWatchDog, *this);
}

ShellCommandWatchDog::~ShellCommandWatchDog()
{
    delete iWatchDog;
    iShell.RemoveCommandHandler(kShellCommandWatchDog);
}

void ShellCommandWatchDog::HandleShellCommand(Brn aCommand, const std::vector<Brn>& aArgs, IWriter& aResponse)
{
    if (aArgs.size() != 1 ) {
        aResponse.Write(Brn("watchdog command takes 1 argument.\n"));
        DisplayHelp(aResponse);
        return;
    }
    
    if ( aArgs[0] == Brn("feed") )
        iWatchDog->Feed();
    else if ( aArgs[0] == Brn("status") )
    {
        Bws<16> buffer;
        Ascii::AppendDec(buffer, iWatchDog->RemainingSeconds());
        aResponse.Write(buffer);
    }
}

void ShellCommandWatchDog::DisplayHelp(IWriter& aResponse)
{
    aResponse.Write(Brn("feed   - reset the watchdog\nstatus - show time remaining\n"));
}

