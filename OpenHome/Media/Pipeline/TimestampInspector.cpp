#include <OpenHome/Media/Pipeline/TimestampInspector.h>
#include <OpenHome/Types.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/ClockPuller.h>
#include <OpenHome/Private/Printer.h>

#include <cstdlib>
#include <limits.h>

using namespace OpenHome;
using namespace OpenHome::Media;

const TUint TimestampInspector::kSupportedMsgTypes =   eMode
                                                     | eTrack
                                                     | eDrain
                                                     | eDelay
                                                     | eEncodedStream
                                                     | eMetatext
                                                     | eStreamInterrupted
                                                     | eHalt
                                                     | eFlush
                                                     | eWait
                                                     | eDecodedStream
                                                     | eAudioPcm
                                                     | eQuit;

TimestampInspector::TimestampInspector(MsgFactory& aMsgFactory, IPipelineElementDownstream& aDownstreamElement)
    : PipelineElement(kSupportedMsgTypes)
    , iMsgFactory(aMsgFactory)
    , iDownstreamElement(aDownstreamElement)
    , iClockPuller(nullptr)
    , iDecodedStream(nullptr)
    , iCheckForTimestamp(false)
    , iStreamIsTimestamped(false)
    , iLockedToStream(false)
    , iCalculateTimestampDelta(false)
    , iMsgsTillLock(0)
    , iTimestampDelta(0)
    , iDiscardedJiffies(0)
{
}

TimestampInspector::~TimestampInspector()
{
    if (iDecodedStream != nullptr) {
        iDecodedStream->RemoveRef();
    }
}

void TimestampInspector::StreamInterrupted()
{
    if (iStreamIsTimestamped) {
        iLockedToStream = false;
        iMsgsTillLock = kLockingMsgCount;
        iTimestampDelta = 0;
        iCalculateTimestampDelta = true;
    }
}

void TimestampInspector::Push(Msg* aMsg)
{
    Msg* msg = aMsg->Process(*this);
    if (msg != nullptr) {
        iDownstreamElement.Push(msg);
    }
}

Msg* TimestampInspector::ProcessMsg(MsgMode* aMsg)
{
    if (iClockPuller != nullptr && iStreamIsTimestamped) {
        iClockPuller->StopTimestamp();
    }
    iClockPuller = aMsg->ClockPuller();
    if (iClockPuller != nullptr && iStreamIsTimestamped) {
        iClockPuller->StopTimestamp();
    }
    iCheckForTimestamp = (iClockPuller != nullptr);
    iStreamIsTimestamped = false;
    iLockedToStream = false;
    iCalculateTimestampDelta = true;
    iMsgsTillLock = 0;
    iTimestampDelta = 0;
    iDiscardedJiffies = 0;
    return aMsg;
}

Msg* TimestampInspector::ProcessMsg(MsgStreamInterrupted* aMsg)
{
    StreamInterrupted();
    return aMsg;
}

Msg* TimestampInspector::ProcessMsg(MsgHalt* aMsg)
{
    StreamInterrupted();
    return aMsg;
}

Msg* TimestampInspector::ProcessMsg(MsgFlush* aMsg)
{
    StreamInterrupted();
    return aMsg;
}

Msg* TimestampInspector::ProcessMsg(MsgWait* aMsg)
{
    StreamInterrupted();
    return aMsg;
}

Msg* TimestampInspector::ProcessMsg(MsgDecodedStream* aMsg)
{
    if (iDecodedStream != nullptr) {
        iDecodedStream->RemoveRef();
    }
    iDecodedStream = aMsg;
    iDecodedStream->AddRef();
    const TUint sampleRate = iDecodedStream->StreamInfo().SampleRate();
    iLockingMaxDeviation = Jiffies::ToSongcastTime(kLockingMaxDeviation, sampleRate);
    if (iStreamIsTimestamped && iClockPuller != nullptr) {
        iClockPuller->NotifyTimestampSampleRate(sampleRate);
    }
    return aMsg;
}

Msg* TimestampInspector::ProcessMsg(MsgAudioPcm* aMsg)
{
    if (iCheckForTimestamp) {
        TUint ignore;
        iStreamIsTimestamped = aMsg->TryGetTimestamps(ignore, ignore);
        if (iStreamIsTimestamped && iClockPuller != nullptr) {
            iClockPuller->StartTimestamp();
            iClockPuller->NotifyTimestampSampleRate(iDecodedStream->StreamInfo().SampleRate());
        }
        iLockedToStream = !iStreamIsTimestamped;
        iCalculateTimestampDelta = iStreamIsTimestamped;
        iCheckForTimestamp = false;
    }
    if (iStreamIsTimestamped) {
        TUint networkTimestamp, rxTimestamp;
        // Not all msgs may be timestamped - the second half of a msg that has been Split() won't have a timestamp to report
        const TBool timestamped = aMsg->TryGetTimestamps(networkTimestamp, rxTimestamp);
        if (!iLockedToStream) {
            iDiscardedJiffies += aMsg->Jiffies();
            aMsg->RemoveRef();
            if (!timestamped) {
                return nullptr;
            }
            const TInt delta = static_cast<TInt>(rxTimestamp - networkTimestamp);
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
                ASSERT(iDecodedStream != nullptr);
                const DecodedStreamInfo& s = iDecodedStream->StreamInfo();
                const TUint64 discardedSamples = iDiscardedJiffies / Jiffies::JiffiesPerSample(s.SampleRate());
                const TUint64 sampleStart = s.SampleStart() + discardedSamples;
                Msg* msg = iMsgFactory.CreateMsgDecodedStream(s.StreamId(), s.BitRate(), s.BitDepth(), s.SampleRate(),
                                                              s.NumChannels(), s.CodecName(), s.TrackLength(), sampleStart,
                                                              s.Lossless(), s.Seekable(), s.Live(), s.StreamHandler());
                iDiscardedJiffies = 0;
                iDecodedStream->RemoveRef();
                iDecodedStream = nullptr;
                return msg;
            }
            return nullptr;
        }
        if (timestamped && iClockPuller != nullptr) {
            const TInt drift = iTimestampDelta - static_cast<TInt>(rxTimestamp - networkTimestamp);
            iClockPuller->NotifyTimestamp(drift, networkTimestamp);
        }
        // fall through
    }
    return aMsg;
}
