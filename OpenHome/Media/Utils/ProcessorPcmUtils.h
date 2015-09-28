#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Media/Pipeline/Msg.h>

namespace OpenHome {
namespace Media {

class ProcessorPcmBufTest : public IPcmProcessor // Reads packed data into dynamically allocated buffer.
                                                 // Suitable for test code only.
{
    static const TUint kBufferGranularity = DecodedAudio::kMaxBytes;
public:
    ProcessorPcmBufTest();
    Brn Buf() const;
    const TByte* Ptr() const;
protected:
    void CheckSize(TUint aAdditionalBytes);
    void ProcessFragment(const Brx& aData);
private: // from IPcmProcessor
    void BeginBlock() override;
    void ProcessFragment8(const Brx& aData, TUint aNumChannels) override;
    void ProcessFragment16(const Brx& aData, TUint aNumChannels) override;
    void ProcessFragment24(const Brx& aData, TUint aNumChannels) override;
    void ProcessFragment32(const Brx& aData, TUint aNumChannels) override;
    void ProcessSample8(const TByte* aSample, TUint aNumChannels) override;
    void ProcessSample16(const TByte* aSample, TUint aNumChannels) override;
    void ProcessSample24(const TByte* aSample, TUint aNumChannels) override;
    void ProcessSample32(const TByte* aSample, TUint aNumChannels) override;
    void EndBlock() override;
protected:
    Bwh iBuf;
};

class ProcessorSample : public IPcmProcessor, private INonCopyable // passes data downstream via ProcessSample* only
{
public:
    ProcessorSample(IPcmProcessor& aDownstream);
private: // from IPcmProcessor
    void BeginBlock() override;
    void ProcessFragment8(const Brx& aData, TUint aNumChannels) override;
    void ProcessFragment16(const Brx& aData, TUint aNumChannels) override;
    void ProcessFragment24(const Brx& aData, TUint aNumChannels) override;
    void ProcessFragment32(const Brx& aData, TUint aNumChannels) override;
    void ProcessSample8(const TByte* aSample, TUint aNumChannels) override;
    void ProcessSample16(const TByte* aSample, TUint aNumChannels) override;
    void ProcessSample24(const TByte* aSample, TUint aNumChannels) override;
    void ProcessSample32(const TByte* aSample, TUint aNumChannels) override;
    void EndBlock() override;
private:
    IPcmProcessor& iDownstream;
};

class ProcessorAggregateUnpacked : public IPcmProcessor, private INonCopyable
{
    static const TUint kMaxSampleBytes = 32; // 8 channels unpacked
public:
    ProcessorAggregateUnpacked(IPcmProcessor& aDownstream, TUint aNumSamples, TUint aMaxChannels);
    void Flush(TUint aNumChannels); // output any pending data, padded with zeros (silence) to target sample total
private:
    inline void CheckBitDepth(TUint aBitDepth);
    void ProcessUnpackedSample(const Brx& aData, TUint aNumSamples);
private: // from IPcmProcessor
    void BeginBlock() override;
    void ProcessFragment8(const Brx& aData, TUint aNumChannels) override;
    void ProcessFragment16(const Brx& aData, TUint aNumChannels) override;
    void ProcessFragment24(const Brx& aData, TUint aNumChannels) override;
    void ProcessFragment32(const Brx& aData, TUint aNumChannels) override;
    void ProcessSample8(const TByte* aSample, TUint aNumChannels) override;
    void ProcessSample16(const TByte* aSample, TUint aNumChannels) override;
    void ProcessSample24(const TByte* aSample, TUint aNumChannels) override;
    void ProcessSample32(const TByte* aSample, TUint aNumChannels) override;
    void EndBlock() override;
private:
    IPcmProcessor& iDownstream;
    const TUint iNumSamples;
    Bwh iBuf;
    TUint iRemainingSamples;
};

} // namespace Media
} // namespace OpenHome

