#include <OpenHome/Types.h>
#include <OpenHome/Media/Pipeline/SampleReporter.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// SampleReporter

SampleReporter::SampleReporter(IPipelineElementUpstream& aUpstreamElement, MsgFactory& aMsgFactory)
    : iUpstreamElement(aUpstreamElement)
    , iMsgFactory(aMsgFactory)
    , iMsgPending(NULL)
    , iChannels(0)
    , iSampleRate(0)
    , iSubSamples(0)
    , iOverflowCount(0)
    , iLock("SARL")
{
}

SampleReporter::~SampleReporter()
{
    AutoMutex a(iLock);
    if (iMsgPending != NULL) {
        iMsgPending->RemoveRef();
    }
}

Msg* SampleReporter::Pull()
{
    {
        AutoMutex a(iLock);
        if (iMsgPending != NULL) {
            Msg* msg = iMsgPending;
            iMsgPending = NULL;
            return msg;
        }
    }
    Msg* msg = iUpstreamElement.Pull();
    (void)msg->Process(*this);
    return msg;
}

TUint SampleReporter::SubSamples()
{
    AutoMutex a(iLock);
    ASSERT(iOverflowCount <= 1);
    iOverflowCount = 0;
    return iSubSamples;
}

TUint SampleReporter::SubSamplesDiff(TUint aPrevSubSamples)
{
    AutoMutex a(iLock);
    ASSERT(iOverflowCount <= 1);
    iOverflowCount = 0;
    // NOTE: this calculation is only valid up to ~2 billion subsamples.
    return iSubSamples - aPrevSubSamples;
}

void SampleReporter::InjectTrack(Track& aTrack, TUint aTrackId)
{
    MsgTrack* msg = iMsgFactory.CreateMsgTrack(aTrack, aTrackId);
    AutoMutex a(iLock);
    ASSERT(iMsgPending == NULL);
    iMsgPending = msg;
}

Msg* SampleReporter::ProcessMsg(MsgMode* aMsg)
{
    AutoMutex a(iLock);
    iChannels = 0;
    iSampleRate = 0;
    iSubSamples = 0;
    iOverflowCount = 0;
    return aMsg;
}

Msg* SampleReporter::ProcessMsg(MsgSession* aMsg)
{
    return aMsg;
}

Msg* SampleReporter::ProcessMsg(MsgTrack* aMsg)
{
    return aMsg;
}

Msg* SampleReporter::ProcessMsg(MsgDelay* aMsg)
{
    return aMsg;
}

Msg* SampleReporter::ProcessMsg(MsgEncodedStream* aMsg)
{
    ASSERTS(); // don't expect to see MsgEncodedStream at this stage of the pipeline
    return aMsg;
}

Msg* SampleReporter::ProcessMsg(MsgAudioEncoded* /*aMsg*/)
{
    ASSERTS(); /* only expect to deal with decoded audio at this stage of the pipeline */
    return NULL;
}

Msg* SampleReporter::ProcessMsg(MsgMetaText* aMsg)
{
    return aMsg;
}

Msg* SampleReporter::ProcessMsg(MsgHalt* aMsg)
{
    return aMsg;
}

Msg* SampleReporter::ProcessMsg(MsgFlush* /*aMsg*/)
{
    ASSERTS(); // don't expect to see MsgFlush at this stage of the pipeline
    return NULL;
}

Msg* SampleReporter::ProcessMsg(MsgWait* aMsg)
{
    return aMsg;
}

Msg* SampleReporter::ProcessMsg(MsgDecodedStream* aMsg)
{
    const DecodedStreamInfo& streamInfo = aMsg->StreamInfo();
    // Don't need to lock this, as this won't be called at same time as ProcessMsg(MsgAudioPcm)
    iChannels = streamInfo.NumChannels();
    iSampleRate = streamInfo.SampleRate();
    ASSERT(iChannels != 0);
    ASSERT(iSampleRate != 0);
    return aMsg;
}

Msg* SampleReporter::ProcessMsg(MsgAudioPcm* aMsg)
{
    ASSERT(iChannels != 0);
    ASSERT(iSampleRate != 0);
    TUint samples = aMsg->Jiffies()/Jiffies::JiffiesPerSample(iSampleRate);
    AutoMutex a(iLock);
    TUint subSamplesPrev = iSubSamples;
    iSubSamples += samples*iChannels;
    if (iSubSamples < subSamplesPrev) {
        iOverflowCount++;
    }
    return aMsg;
}

Msg* SampleReporter::ProcessMsg(MsgSilence* aMsg)
{
    return aMsg;
}

Msg* SampleReporter::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    ASSERTS(); // don't expect to see MsgPlayable in the pipeline
    return NULL;
}

Msg* SampleReporter::ProcessMsg(MsgQuit* aMsg)
{
    return aMsg;
}
