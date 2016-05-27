#include <OpenHome/Av/Songcast/ProtocolOhm.h>
#include <OpenHome/Media/Protocol/Protocol.h>
#include <OpenHome/Av/Songcast/Ohm.h>
#include <OpenHome/Av/Songcast/OhmMsg.h>
#include <OpenHome/Av/Songcast/OhmSocket.h>
#include <OpenHome/Av/Songcast/ProtocolOhBase.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Timer.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Av/Debug.h>
#include <OpenHome/Media/ClockPuller.h>
#include <OpenHome/Media/Pipeline/Msg.h>

#include <cstdlib>
#include <limits>

using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Media;

/* The Join Timeout represents the time within which the Ohm sender
   must see a join message before it decides that no receivers
   are interested in its channel and stops sending audio. The receiver
   can be in one of two Join Modes: Master or Slave. Each mode has
   its own timeout. The Master Join Timeout is a randomly generated time
   between 1/8 and 2/8 of the Join Timeout. The randomisation is performed
   each time a timer is primed with the timeout. The Slave Join Timeout
   is a randomly generated time between 3/8 and 4/8 of the Join Timeout.
   Again, the randomisation is performed each time a timer is primed with
   the timeout. When a receiver starts listening to a Ohm channel it
   is in Master Join Mode: it sends a join message immediately and then
   waits for the Master Join Timeout. If it sees a join message sent
   by another receiver during this period then it moves to Slave Join Mode.
   Otherwise, when the timeout expires it sends a join message and waits for
   the Master Join Timeout again. In Slave Join Mode it does not send join
   messages; it merely monitors join messages sent by the Master. Every time
   a join message is seen the Slave Join Timeout is restarted. If this timeout
   expires without seeing a join message from another receiver, then it moves
   back to Master Join Mode. This system of operation tends to select a single
   receiver as Master. If this Master stops receiving then one of the remaining
   Slaves will tend to be randomly selected as the new Master. If there are
   no Slaves left then the sender will stop sending after the Join Timeout. */


// ProtocolOhm

const TInt ProtocolOhm::kLockingMaxDeviation = Jiffies::kPerMs / 2;
const TUint ProtocolOhm::kLockingMsgCount = 4;

ProtocolOhm::ProtocolOhm(Environment& aEnv, IOhmMsgFactory& aMsgFactory, TrackFactory& aTrackFactory,
                         Optional<IOhmTimestamper> aTimestamper, const Brx& aMode)
    : ProtocolOhBase(aEnv, aMsgFactory, aTrackFactory, aTimestamper, "ohm", aMode)
    , iStoppedLock("POHM")
    , iSemSenderUnicastOverride("POM2", 0)
    , iSenderUnicastOverrideEnabled(false)
{
    ASSERT(iSenderUnicastOverrideEnabled.is_lock_free());
}

void ProtocolOhm::UnicastOverrideEnabled()
{
    iSenderUnicastOverrideEnabled.store(true);
    iSemSenderUnicastOverride.Signal();
}

void ProtocolOhm::UnicastOverrideDisabled()
{
    iSenderUnicastOverrideEnabled.store(false);
    (void)iSemSenderUnicastOverride.Clear();
}

ProtocolStreamResult ProtocolOhm::Play(TIpAddress aInterface, TUint aTtl, const Endpoint& aEndpoint)
{
    if (aEndpoint.Address() == 0) {
        // ohm null address
        // return immediately and leave the Filler to clear all track data
        return EProtocolStreamStopped;
    }
    iNextFlushId = MsgFlush::kIdInvalid;
    iStoppedLock.Wait();
    iStopped = false;
    iStoppedLock.Signal();
    iEndpoint.Replace(aEndpoint);
    // drain the pipeline before creating a multicast socket
    // ...to ensure any songcast sender first stops, removing membership of their multicast group
    // ...this helps keep a full player at membership of 4 multicast groups
    // ...matching hardware limits of some clients
    WaitForPipelineToEmpty();
    if (!iSenderUnicastOverrideEnabled.load()) {
        iSemSenderUnicastOverride.Wait();
    }
    TBool firstJoin = true;
    iCheckForTimestamp = true;
    iStreamIsTimestamped = false;

    do {
        if (!firstJoin) {
            WaitForPipelineToEmpty();
        }
        iStoppedLock.Wait();
        if (iStarving && !iStopped) {
            iStarving = false;
            iSocket.Interrupt(false);
        }
        iStoppedLock.Signal();
        try {
            iSocket.Close();
            iSocket.OpenMulticast(aInterface, aTtl, iEndpoint);
            if (iTimestamper != nullptr) {
                iTimestamper->Stop();
                iTimestamper->Start(iEndpoint);
            }
            ResetClockPuller();

            OhmHeader header;
            SendJoin();

            // Phase 1, periodically send join until Track and Metatext have been received
            TBool joinComplete = false;
            TBool receivedTrack = false;
            TBool receivedMetatext = false;

            while (!joinComplete) {
                try {
                    header.Internalise(iReadBuffer);

                    switch (header.MsgType())
                    {
                    case OhmHeader::kMsgTypeJoin:
                    case OhmHeader::kMsgTypeListen:
                    case OhmHeader::kMsgTypeLeave:
                    case OhmHeader::kMsgTypeSlave:
                        break;
                    case OhmHeader::kMsgTypeAudio:
                    {
                        /* Ignore audio while joining - it might be from while we were waiting
                           for the pipeline to empty if we're re-starting a stream following a drop-out
                           We do however need to check for timestamps, to avoid the timestamper
                           filling up with out of date values */
                        auto msg = iMsgFactory.CreateAudio(iReadBuffer, header);
                        AddRxTimestamp(*msg);
                        msg->RemoveRef();
                    }
                        break;
                    case OhmHeader::kMsgTypeTrack:
                        Add(iMsgFactory.CreateTrack(iReadBuffer, header));
                        receivedTrack = true;
                        joinComplete = receivedMetatext;
                        break;
                    case OhmHeader::kMsgTypeMetatext:
                        Add(iMsgFactory.CreateMetatext(iReadBuffer, header));
                        receivedMetatext = true;
                        joinComplete = receivedTrack;
                        break;
                    case OhmHeader::kMsgTypeResend:
                        ResendSeen();
                        break;
                    }

                    iReadBuffer.ReadFlush();
                }
                catch (OhmError&) {
                }
            }
            
            iTimerJoin->Cancel();
            if (firstJoin) {
                /* Put pipeline into Waiting state initially in case sender is currently paused.
                   Subsequent loops will likely be prompted by network starvation.  We don't want
                   to output a Wait in this case; its correct that the pipeline goes Buffering */
                iSupply->OutputWait();
                firstJoin = false;
            }

            // Phase 2, periodically send listen if required
            iTimerListen->FireIn((kTimerListenTimeoutMs >> 2) - iEnv.Random(kTimerListenTimeoutMs >> 3)); // listen primary timeout
            for (;;) {
                try {
                    header.Internalise(iReadBuffer);

                    switch (header.MsgType())
                    {
                    case OhmHeader::kMsgTypeJoin:
                    case OhmHeader::kMsgTypeLeave:
                    case OhmHeader::kMsgTypeSlave:
                        break;
                    case OhmHeader::kMsgTypeListen:
                        iTimerListen->FireIn((kTimerListenTimeoutMs >> 1) - iEnv.Random(kTimerListenTimeoutMs >> 3)); // listen secondary timeout
                        break;
                    case OhmHeader::kMsgTypeAudio:
                        Add(iMsgFactory.CreateAudio(iReadBuffer, header));
                        break;
                    case OhmHeader::kMsgTypeTrack:
                        Add(iMsgFactory.CreateTrack(iReadBuffer, header));
                        break;
                    case OhmHeader::kMsgTypeMetatext:
                        Add(iMsgFactory.CreateMetatext(iReadBuffer, header));
                        break;
                    case OhmHeader::kMsgTypeResend:
                        ResendSeen();
                        break;
                    }

                    iReadBuffer.ReadFlush();
                }
                catch (OhmError&) {
                }
            }
        }
        catch (ReaderError&) {
        }
    } while (!iStopped);

    if (iTimestamper != nullptr) {
        iTimestamper->Stop();
    }

    iReadBuffer.ReadFlush();
    iTimerJoin->Cancel();
    iTimerListen->Cancel();
    iSocket.Close();
    iMutexTransport.Wait();
    iStreamId = IPipelineIdProvider::kStreamIdInvalid;
    const TUint flushId = iNextFlushId;
    iNextFlushId = MsgFlush::kIdInvalid;
    iMutexTransport.Signal();
    if (flushId != MsgFlush::kIdInvalid) {
        iSupply->OutputFlush(flushId);
    }
    return iStopped? EProtocolStreamStopped : EProtocolStreamErrorUnrecoverable;
}

void ProtocolOhm::ProcessTimestamps(const OhmMsgAudio& aMsg, TBool& aDiscard)
{
    aDiscard = false;
    if (iTimestamper == nullptr) {
        return;
    }
    const TBool msgTimestamped = (aMsg.Timestamped() && aMsg.RxTimestamped());
    if (iCheckForTimestamp) {
        iCheckForTimestamp = false;
        iStreamIsTimestamped = aMsg.Timestamped(); // Tx timestamp && iTimestamper!==nullptr => expect timestamps
    }

    if (!iStreamIsTimestamped) {
        return;
    }

    const TUint sampleRate = aMsg.SampleRate();
    const TUint timestamperFreq = Jiffies::SongcastTicksPerSecond(sampleRate);
    if (iTimestamperFreq != timestamperFreq) {
        // any stored timestamps are unreliable - reset timestamper
        (void)iTimestamper->SetSampleRate(sampleRate);
        iTimestamper->Stop();
        iTimestamper->Start(iEndpoint);

        iTimestamperFreq = timestamperFreq;
        iLockingMaxDeviation = Jiffies::ToSongcastTime(kLockingMaxDeviation, sampleRate);
        if (!aMsg.Timestamped2()) { // Original Linn sender.  Next MediaLatency() worth of timestamps may be wrong.
            iJiffiesBeforeTimestampsReliable = static_cast<TUint>(Jiffies::FromSongcastTime(aMsg.MediaLatency(), sampleRate));
        }
        else {
            // Single timestamp on clock family change may be unreliable.
            // Set things up so that timestampReliable gets set false below
            const TUint msgJiffies = aMsg.Samples() * Jiffies::PerSample(sampleRate);
            iJiffiesBeforeTimestampsReliable = msgJiffies;
        }
    }

    const TBool timestampReliable = (iJiffiesBeforeTimestampsReliable == 0);
    if (!timestampReliable) {
        const TUint msgJiffies = aMsg.Samples() * Jiffies::PerSample(sampleRate);
        if (msgJiffies > iJiffiesBeforeTimestampsReliable) {
            iJiffiesBeforeTimestampsReliable = 0;
        }
        else {
            iJiffiesBeforeTimestampsReliable -= msgJiffies;
        }
        aDiscard = true;
        return;
    }

    if (!iLockedToStream) {
        if (!msgTimestamped) {
            aDiscard = true;
            return;
        }
        const TInt delta = static_cast<TInt>(aMsg.RxTimestamp() - aMsg.NetworkTimestamp());
        if (iCalculateTimestampDelta) {
            iTimestampDelta = delta;
            iMsgsTillLock = kLockingMsgCount - 1;
            iCalculateTimestampDelta = false;
        }
        else if ((TUint)std::abs(iTimestampDelta - delta) > iLockingMaxDeviation) {
            iMsgsTillLock = kLockingMsgCount;
            iCalculateTimestampDelta = true;
            iTimestampDelta = 0;
        }
        else if (--iMsgsTillLock == 0) {
            iLockedToStream = true;
        }
        if (!iLockedToStream) {
            aDiscard = true;
            return;
        }
    }
}

void ProtocolOhm::Interrupt(TBool aInterrupt)
{
    //LOG(kSongcast, "OHM: Interrupt(%u)\n", aInterrupt);
    if (aInterrupt) {
        iStoppedLock.Wait();
        iStopped = aInterrupt;
        iStoppedLock.Signal();
    }
    ProtocolOhBase::Interrupt(aInterrupt);
}

TUint ProtocolOhm::TryStop(TUint aStreamId)
{
    AutoMutex _(iMutexTransport);
    if (IsCurrentStream(aStreamId) && iStreamId == aStreamId) {
        if (iNextFlushId == MsgFlush::kIdInvalid) {
            iNextFlushId = iFlushIdProvider->NextFlushId();
        }
        iStoppedLock.Wait();
        iStopped = true;
        iStoppedLock.Signal();
        iSocket.ReadInterrupt();
    }
    return iNextFlushId;
}

void ProtocolOhm::ResetClockPuller()
{
    iLockedToStream = false;
    iCalculateTimestampDelta = true;
    iTimestamperFreq = 0;
    iLockingMaxDeviation = UINT_MAX;
    iJiffiesBeforeTimestampsReliable = 0;
    iTimestampDelta = 0;
    iMsgsTillLock = 0;
}
