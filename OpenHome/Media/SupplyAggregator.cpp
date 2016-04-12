#include <OpenHome/Media/SupplyAggregator.h>
#include <OpenHome/Types.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Pipeline/Msg.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// SupplyAggregator

SupplyAggregator::SupplyAggregator(MsgFactory& aMsgFactory, IPipelineElementDownstream& aDownStreamElement)
    : iMsgFactory(aMsgFactory)
    , iAudioEncoded(nullptr)
    , iDownStreamElement(aDownStreamElement)
{
}

SupplyAggregator::~SupplyAggregator()
{
    if (iAudioEncoded != nullptr) {
        iAudioEncoded->RemoveRef();
    }
}

void SupplyAggregator::Flush()
{
    if (iAudioEncoded != nullptr) {
        OutputEncodedAudio();
    }
}

void SupplyAggregator::OutputTrack(Track& aTrack, TBool aStartOfStream)
{
    MsgTrack* msg = iMsgFactory.CreateMsgTrack(aTrack, aStartOfStream);
    Output(msg);
}

void SupplyAggregator::OutputDrain(Functor aCallback)
{
    auto msg = iMsgFactory.CreateMsgDrain(aCallback);
    Output(msg);
}

void SupplyAggregator::OutputDelay(TUint aJiffies)
{
    MsgDelay* msg = iMsgFactory.CreateMsgDelay(aJiffies);
    Output(msg);
}

void SupplyAggregator::OutputMetadata(const Brx& aMetadata)
{
    MsgMetaText* msg = iMsgFactory.CreateMsgMetaText(aMetadata);
    Output(msg);
}

void SupplyAggregator::OutputStreamInterrupted()
{
    auto msg = iMsgFactory.CreateMsgStreamInterrupted();
    Output(msg);
}

void SupplyAggregator::OutputFlush(TUint aFlushId)
{
    MsgFlush* msg = iMsgFactory.CreateMsgFlush(aFlushId);
    Output(msg);
}

void SupplyAggregator::OutputWait()
{
    MsgWait* msg = iMsgFactory.CreateMsgWait();
    Output(msg);
}

void SupplyAggregator::Output(Msg* aMsg)
{
    if (iAudioEncoded != nullptr) {
        OutputEncodedAudio();
    }
    iDownStreamElement.Push(aMsg);
}

void SupplyAggregator::OutputEncodedAudio()
{
    iDownStreamElement.Push(iAudioEncoded);
    iAudioEncoded = nullptr;
}


// SupplyAggregatorBytes

SupplyAggregatorBytes::SupplyAggregatorBytes(MsgFactory& aMsgFactory, IPipelineElementDownstream& aDownStreamElement)
    : SupplyAggregator(aMsgFactory, aDownStreamElement)
{
}
void SupplyAggregatorBytes::OutputStream(const Brx& aUri, TUint64 aTotalBytes, TUint64 aStartPos, TBool aSeekable, TBool aLive, IStreamHandler& aStreamHandler, TUint aStreamId)
{
    // FIXME - no metatext available
    MsgEncodedStream* msg = iMsgFactory.CreateMsgEncodedStream(aUri, Brx::Empty(), aTotalBytes, aStartPos, aStreamId, aSeekable, aLive, &aStreamHandler);
    Output(msg);
}

void SupplyAggregatorBytes::OutputPcmStream(const Brx& aUri, TUint64 aTotalBytes, TBool aSeekable, TBool aLive, IStreamHandler& aStreamHandler, TUint aStreamId, const PcmStreamInfo& aPcmStream)
{
    // FIXME - no metatext available
    MsgEncodedStream* msg = iMsgFactory.CreateMsgEncodedStream(aUri, Brx::Empty(), aTotalBytes, 0, aStreamId, aSeekable, aLive, &aStreamHandler, aPcmStream);
    Output(msg);
}

void SupplyAggregatorBytes::OutputData(const Brx& aData)
{
    if (aData.Bytes() == 0) {
        return;
    }
    if (iAudioEncoded == nullptr) {
        iAudioEncoded = iMsgFactory.CreateMsgAudioEncoded(aData);
    }
    else {
        const TUint consumed = iAudioEncoded->Append(aData);
        if (consumed < aData.Bytes()) {
            OutputEncodedAudio();
            Brn remaining = aData.Split(consumed);
            iAudioEncoded = iMsgFactory.CreateMsgAudioEncoded(remaining);
        }
    }
}


// SupplyAggregatorJiffies

SupplyAggregatorJiffies::SupplyAggregatorJiffies(MsgFactory& aMsgFactory, IPipelineElementDownstream& aDownStreamElement)
    : SupplyAggregator(aMsgFactory, aDownStreamElement)
    , iDataMaxBytes(0)
{
}

void SupplyAggregatorJiffies::OutputStream(const Brx& /*aUri*/, TUint64 /*aTotalBytes*/, TUint64 /*aStartPos*/, TBool /*aSeekable*/, TBool /*aLive*/, IStreamHandler& /*aStreamHandler*/, TUint /*aStreamId*/)
{
    ASSERTS(); // can only aggregate by jiffies for PCM streams
}

void SupplyAggregatorJiffies::OutputPcmStream(const Brx& aUri, TUint64 aTotalBytes, TBool aSeekable, TBool aLive, IStreamHandler& aStreamHandler, TUint aStreamId, const PcmStreamInfo& aPcmStream)
{
    // FIXME - no metatext available
    TUint ignore = kMaxPcmDataJiffies;
    const TUint jiffiesPerSample = Jiffies::PerSample(aPcmStream.SampleRate());
    iDataMaxBytes = Jiffies::ToBytes(ignore, jiffiesPerSample, aPcmStream.NumChannels(), aPcmStream.BitDepth() / 8);
    MsgEncodedStream* msg = iMsgFactory.CreateMsgEncodedStream(aUri, Brx::Empty(), aTotalBytes, 0, aStreamId, aSeekable, aLive, &aStreamHandler, aPcmStream);
    Output(msg);
}

void SupplyAggregatorJiffies::OutputData(const Brx& aData)
{
    if (aData.Bytes() == 0) {
        return;
    }

    /* Don't try to split data precisely at kMaxPcmDataJiffies boundaries
       If we're passed in data that takes us over this threshold, accept as much as we can,
       passing it on immediately */
    if (iAudioEncoded == nullptr) {
        iAudioEncoded = iMsgFactory.CreateMsgAudioEncoded(aData);
    }
    else {
        const TUint consumed = iAudioEncoded->Append(aData);
        if (consumed < aData.Bytes()) {
            OutputEncodedAudio();
            Brn remaining = aData.Split(consumed);
            iAudioEncoded = iMsgFactory.CreateMsgAudioEncoded(remaining);
        }
    }
    if (iAudioEncoded->Bytes() >= iDataMaxBytes) {
        OutputEncodedAudio();
    }
}


// AutoSupplyFlush

AutoSupplyFlush::AutoSupplyFlush(SupplyAggregator& aSupply)
    : iSupply(aSupply)
{
}

AutoSupplyFlush::~AutoSupplyFlush()
{
    iSupply.Flush();
}
