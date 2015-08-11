#include <OpenHome/Media/Pipeline/DecodedAudioValidator.h>
#include <OpenHome/Types.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Private/Printer.h>

using namespace OpenHome;
using namespace OpenHome::Media;

const TUint DecodedAudioValidator::kSupportedMsgTypes =   eMode
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
                                                        | eSilence
                                                        | eQuit;

DecodedAudioValidator::DecodedAudioValidator(IPipelineElementUpstream& aUpstream, const TChar* aId)
    : PipelineElement(kSupportedMsgTypes)
    , iUpstream(&aUpstream)
    , iDownstream(NULL)
    , iId(aId)
    , iStreamPos(0)
    , iExpectDecodedStreamBeforeAudio(true)
    , iEnabled(true)
{
}

DecodedAudioValidator::DecodedAudioValidator(const TChar* aId, IPipelineElementDownstream& aDownstream)
    : PipelineElement(kSupportedMsgTypes)
    , iUpstream(NULL)
    , iDownstream(&aDownstream)
    , iId(aId)
    , iStreamPos(0)
    , iExpectDecodedStreamBeforeAudio(true)
    , iEnabled(true)
{
}

void DecodedAudioValidator::SetEnabled()
{
    iEnabled = true;
}

Msg* DecodedAudioValidator::Pull()
{
    ASSERT(iUpstream != NULL);
    Msg* msg = iUpstream->Pull();
    if (iEnabled) {
        msg = msg->Process(*this);
    }
    return msg;
}

void DecodedAudioValidator::Push(Msg* aMsg)
{
    ASSERT(iDownstream != NULL);
    if (iEnabled) {
        aMsg = aMsg->Process(*this);
    }
    iDownstream->Push(aMsg);
}

Msg* DecodedAudioValidator::ProcessMsg(MsgMode* aMsg)
{
    //Log::Print("MsgMode (%s)\n", iId);
    iExpectDecodedStreamBeforeAudio = true;
    return aMsg;
}

Msg* DecodedAudioValidator::ProcessMsg(MsgTrack* aMsg)
{
    if (aMsg->StartOfStream()) {
        //Log::Print("MsgTrack (%s)\n", iId);
        iExpectDecodedStreamBeforeAudio = true;
    }
    return aMsg;
}

Msg* DecodedAudioValidator::ProcessMsg(MsgEncodedStream* aMsg)
{
    //Log::Print("MsgEncodedStream (%s)\n", iId);
    iExpectDecodedStreamBeforeAudio = true;
    return aMsg;
}

Msg* DecodedAudioValidator::ProcessMsg(MsgStreamInterrupted* aMsg)
{
    //Log::Print("MsgStreamInterrupted (%s)\n", iId);
    iExpectDecodedStreamBeforeAudio = true;
    return aMsg;
}

Msg* DecodedAudioValidator::ProcessMsg(MsgDecodedStream* aMsg)
{
    //Log::Print("MsgDecodedStream (%s)\n", iId);
    iExpectDecodedStreamBeforeAudio = false;
    const DecodedStreamInfo& streamInfo = aMsg->StreamInfo();
    iStreamPos = streamInfo.SampleStart() * Jiffies::JiffiesPerSample(streamInfo.SampleRate());
    return aMsg;
}

Msg* DecodedAudioValidator::ProcessMsg(MsgAudioPcm* aMsg)
{
    const TUint64 streamPos = aMsg->TrackOffset();
    if (iExpectDecodedStreamBeforeAudio) {
        Log::Print("WARNING: discontinuity in audio (%s): expected DecodedStream before audio\n", iId);
    }
    else if (iStreamPos != streamPos) {
        Log::Print("WARNING: discontinuity in audio (%s): missing [%llu..%llu) (%dms)\n",
            iId, iStreamPos, streamPos, (static_cast<TInt>(streamPos-iStreamPos) / Jiffies::kPerMs));
    }
    iStreamPos = streamPos + aMsg->Jiffies();
    return aMsg;
}
