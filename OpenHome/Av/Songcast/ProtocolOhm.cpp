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

    do {
        if (!firstJoin) {
            /* allow lower priority threads to run.  If all network operations are failing
            (say because we have no IP address), this high priority thread will loop. */
            Thread::Sleep(50);
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
        catch (NetworkError&) { // from OpenMulticast only
        }
        catch (ReaderError&) {
        }
        catch (OhmDiscontinuity&) {
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

