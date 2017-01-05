#include <OpenHome/Private/ShellCommandWatchDog.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Private/Ascii.h>

using namespace OpenHome;


class ShellCommandWatchDog::WatchDog
{
public:
    WatchDog(TUint aTimeoutSeconds)
        : iMutex("wmtx")
        , iTimeoutSeconds(aTimeoutSeconds)
        , iRemainingSeconds(aTimeoutSeconds)
        , iThreadFunctor(NULL)
    {
        iThreadFunctor = new ThreadFunctor("ShellWatchdog", MakeFunctor(*this, &WatchDog::Run));
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
    void Update(TUint aNewSeconds)
    {
        AutoMutex a(iMutex);
        iRemainingSeconds = aNewSeconds;
        iTimeoutSeconds = aNewSeconds;
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
                exit(2);
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

ShellCommandWatchDog::ShellCommandWatchDog(Shell& aShell, TUint aWatchdogTimeoutSeconds)
    : iShell(aShell)
    , iWatchDog(new WatchDog(aWatchdogTimeoutSeconds))
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
    if ( aArgs.size() < 1 ) {
        DisplayHelp(aResponse);
        return;
    }

    if ( aArgs[0] == Brn("feed") )
    {
        if ( aArgs.size() != 1 )
        {
            DisplayHelp(aResponse);
            return;
        }
        iWatchDog->Feed();
    }
    else if ( aArgs[0] == Brn("status") )
    {
        if ( aArgs.size() != 1 )
        {
            DisplayHelp(aResponse);
            return;
        }
        Bws<16> buffer;
        Ascii::AppendDec(buffer, iWatchDog->RemainingSeconds());
        aResponse.Write(buffer);
    }
    else if ( aArgs[0] == Brn("update") )
    {
        if ( aArgs.size() != 2 )
        {
            DisplayHelp(aResponse);
            return;
        }
        // read integer, update watchdog.
        iWatchDog->Update(Ascii::Uint(aArgs[1]));
    }
}

void ShellCommandWatchDog::DisplayHelp(IWriter& aResponse)
{
    aResponse.Write(Brn("feed   - reset the watchdog\nstatus - show time remaining\nupdate SECONDS - set the watchdog counter\n"));
}

