#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Media/Pipeline/Msg.h>

namespace OpenHome {
namespace Media {

class SupplyAggregator : public ISupply, private INonCopyable
{
public:
    SupplyAggregator(MsgFactory& aMsgFactory, IPipelineElementDownstream& aDownStreamElement);
    virtual ~SupplyAggregator();
    void Flush();
public: // from ISupply
    void OutputTrack(Track& aTrack, TBool aStartOfStream = true) override;
    void OutputDrain(Functor aCallback) override;
    void OutputDelay(TUint aJiffies) override;
    void OutputMetadata(const Brx& aMetadata) override;
    void OutputStreamInterrupted() override;
    void OutputFlush(TUint aFlushId) override;
    void OutputWait() override;
protected:
    void Output(Msg* aMsg);
    void OutputEncodedAudio();
protected:
    MsgFactory& iMsgFactory;
    MsgAudioEncoded* iAudioEncoded;
private:
    IPipelineElementDownstream& iDownStreamElement;
};

class SupplyAggregatorBytes : public SupplyAggregator
{
public:
    SupplyAggregatorBytes(MsgFactory& aMsgFactory, IPipelineElementDownstream& aDownStreamElement);
public: // from ISupply
    void OutputStream(const Brx& aUri, TUint64 aTotalBytes, TUint64 aStartPos, TBool aSeekable, TBool aLive, IStreamHandler& aStreamHandler, TUint aStreamId) override;
    void OutputPcmStream(const Brx& aUri, TUint64 aTotalBytes, TBool aSeekable, TBool aLive, IStreamHandler& aStreamHandler, TUint aStreamId, const PcmStreamInfo& aPcmStream) override;
    void OutputData(const Brx& aData) override;
};

class SupplyAggregatorJiffies : public SupplyAggregator
{
    static const TUint kMaxPcmDataJiffies = Jiffies::kPerMs * 4;
public:
    SupplyAggregatorJiffies(MsgFactory& aMsgFactory, IPipelineElementDownstream& aDownStreamElement);
public: // from ISupply
    void OutputStream(const Brx& aUri, TUint64 aTotalBytes, TUint64 aStartPos, TBool aSeekable, TBool aLive, IStreamHandler& aStreamHandler, TUint aStreamId) override;
    void OutputPcmStream(const Brx& aUri, TUint64 aTotalBytes, TBool aSeekable, TBool aLive, IStreamHandler& aStreamHandler, TUint aStreamId, const PcmStreamInfo& aPcmStream) override;
    void OutputData(const Brx& aData) override;
private:
    TUint iDataMaxBytes;
};

class AutoSupplyFlush : private INonCopyable
{
public:
    AutoSupplyFlush(SupplyAggregator& aSupply);
    ~AutoSupplyFlush();
private:
    SupplyAggregator& iSupply;
};

} // namespace Media
} // namespace OpenHome

