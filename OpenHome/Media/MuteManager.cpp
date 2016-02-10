#include <OpenHome/Media/MuteManager.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Standard.h>

using namespace OpenHome;
using namespace OpenHome::Media;


// Mute

MuteClient::MuteClient(IMute& aMute)
    : iMute(aMute)
    , iLock("MUTE")
    , iMuted(false)
{
}

void MuteClient::Mute()
{
    AutoMutex _(iLock);
    if (!iMuted) {
        iMuted = true;
        iMute.Mute();
    }
}

void MuteClient::Unmute()
{
    AutoMutex _(iLock);
    if (iMuted) {
        iMuted = false;
        iMute.Unmute();
    }
}


// MuteCounted

MuteCounted::MuteCounted(IMute& aMute)
    : iMute(aMute)
    , iLock("MUTC")
    , iCount(0)
{
}

void MuteCounted::Mute()
{
    AutoMutex _(iLock);
    ++iCount;
    if (1 == iCount) {
        iMute.Mute();
    }
}

void MuteCounted::Unmute()
{
    AutoMutex _(iLock);
    ASSERT(iCount > 0);
    --iCount;
    if (0 == iCount) {
        iMute.Unmute();
    }
}
