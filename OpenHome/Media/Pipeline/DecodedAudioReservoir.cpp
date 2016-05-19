#include <OpenHome/Media/Pipeline/DecodedAudioReservoir.h>
#include <OpenHome/Types.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/ClockPuller.h>

#include <limits.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// DecodedAudioReservoir

DecodedAudioReservoir::DecodedAudioReservoir(MsgFactory& aMsgFactory, TUint aMaxSize, TUint aMaxStreamCount)
    : iMsgFactory(aMsgFactory)
    , iLockClockPuller("DCR1")
    , iClockPuller(nullptr)
    , iMaxJiffies(aMaxSize)
    , iMaxStreamCount(aMaxStreamCount)
    , iClockPullerStarted(false)
{
}

TUint DecodedAudioReservoir::SizeInJiffies() const
{
    return Jiffies();
}

TBool DecodedAudioReservoir::IsFull() const
{
    return (Jiffies() > iMaxJiffies         ||
            TrackCount() >= iMaxStreamCount ||
            DecodedStreamCount() >= iMaxStreamCount);
}

void DecodedAudioReservoir::ProcessMsgIn(MsgTrack* /*aMsg*/)
{
    BlockIfFull();
}

void DecodedAudioReservoir::ProcessMsgIn(MsgDecodedStream* /*aMsg*/)
{
    BlockIfFull();
}

void DecodedAudioReservoir::ProcessMsgIn(MsgAudioPcm* aMsg)
{
    BlockIfFull();
    AutoMutex _(iLockClockPuller);
    if (iClockPuller != nullptr && iClockPullerStarted) {
        const TUint size = Jiffies() + aMsg->Jiffies();
        iClockPuller->NotifySize(size);
    }
}

void DecodedAudioReservoir::ProcessMsgIn(MsgSilence* /*aMsg*/)
{
    ASSERTS(); // don't expect anything upstream to be generating silence
}

Msg* DecodedAudioReservoir::ProcessMsgOut(MsgMode* aMsg)
{
    if (iClockPuller != nullptr) {
        iClockPuller->Stop();
    }
    AutoMutex _(iLockClockPuller);
    iClockPuller = aMsg->ClockPullers().ReservoirLeft();
    iClockPullerStarted = false;
    if (iClockPuller != nullptr) {
        const auto modeInfo = aMsg->Info();
        MsgMode* msg = iMsgFactory.CreateMsgMode(aMsg->Mode(),
                                                 modeInfo.SupportsLatency(), modeInfo.IsRealTime(),
                                                 ModeClockPullers(this),
                                                 modeInfo.SupportsNext(), modeInfo.SupportsPrev());
        aMsg->RemoveRef();
        aMsg = msg;
    }
    return aMsg;
}

Msg* DecodedAudioReservoir::ProcessMsgOut(MsgDrain* aMsg)
{
    AutoMutex _(iLockClockPuller);
    if (iClockPuller != nullptr) {
        iClockPullerStarted = false;
        iClockPuller->Stop();
    }
    return aMsg;
}

Msg* DecodedAudioReservoir::ProcessMsgOut(MsgAudioPcm* aMsg)
{
    AutoMutex _(iLockClockPuller);
    if (iClockPuller != nullptr && iClockPullerStarted) {
        iClockPuller->NotifySize(Jiffies());
    }

    return aMsg;
}

void DecodedAudioReservoir::Start(TUint aExpectedDecodedReservoirJiffies)
{
    AutoMutex _(iLockClockPuller);
    if (iClockPuller != nullptr) {
        iClockPuller->Start(aExpectedDecodedReservoirJiffies);
        iClockPullerStarted = true;
    }
}

void DecodedAudioReservoir::Stop()
{
    AutoMutex _(iLockClockPuller);
    iClockPullerStarted = false;
    iClockPuller->Stop();
}

void DecodedAudioReservoir::Reset()
{
    ASSERTS();
}

void DecodedAudioReservoir::NotifySize(TUint /*aJiffies*/)
{
    ASSERTS();
}
