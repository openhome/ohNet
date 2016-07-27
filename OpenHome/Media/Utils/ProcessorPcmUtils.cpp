#include <OpenHome/Media/Utils/ProcessorPcmUtils.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// ProcessorPcmBufTest

Brn ProcessorPcmBufTest::Buf() const
{
    return Brn(iBuf);
}

const TByte* ProcessorPcmBufTest::Ptr() const
{
    return iBuf.Ptr();
}

ProcessorPcmBufTest::ProcessorPcmBufTest()
    : iBuf(kBufferGranularity)
{
}

void ProcessorPcmBufTest::CheckSize(TUint aAdditionalBytes)
{
    while (iBuf.Bytes() + aAdditionalBytes > iBuf.MaxBytes()) {
        const TUint size = iBuf.MaxBytes() + kBufferGranularity;
        iBuf.Grow(size);
    }
}

void ProcessorPcmBufTest::ProcessFragment(const Brx& aData)
{
    CheckSize(aData.Bytes());
    iBuf.Append(aData);
}

void ProcessorPcmBufTest::BeginBlock()
{
    iBuf.SetBytes(0);
}


void ProcessorPcmBufTest::ProcessFragment8(const Brx& aData, TUint /*aNumChannels*/)
{
    ProcessFragment(aData);
}

void ProcessorPcmBufTest::ProcessFragment16(const Brx& aData, TUint /*aNumChannels*/)
{
    ProcessFragment(aData);
}

void ProcessorPcmBufTest::ProcessFragment24(const Brx& aData, TUint /*aNumChannels*/)
{
    ProcessFragment(aData);
}

void ProcessorPcmBufTest::ProcessFragment32(const Brx& aData, TUint /*aNumChannels*/)
{
    ProcessFragment(aData);
}

void ProcessorPcmBufTest::EndBlock()
{
}

void ProcessorPcmBufTest::Flush()
{
}


// ProcessorAggregateUnpacked

ProcessorAggregateUnpacked::ProcessorAggregateUnpacked(IPcmProcessor& aDownstream, TUint aNumSamples, TUint aMaxChannels)
    : iDownstream(aDownstream)
    , iNumSamples(aNumSamples)
    , iBuf(aNumSamples * 4 * aMaxChannels)
    , iRemainingSamples(aNumSamples)
{
    ASSERT(aMaxChannels <= kMaxSampleBytes);
}

void ProcessorAggregateUnpacked::Flush(TUint aNumChannels)
{
    TByte s[kMaxSampleBytes] ={ 0 };
    Brn sample(s, aNumChannels*4);
    while (iRemainingSamples != iNumSamples) {
        ProcessUnpackedSample(sample, aNumChannels);
    }
}

void ProcessorAggregateUnpacked::ProcessUnpackedSample(const Brx& aData, TUint aNumChannels)
{
    iBuf.Append(aData);
    if (--iRemainingSamples == 0) {
        iDownstream.BeginBlock();
        iDownstream.ProcessFragment32(iBuf, aNumChannels);
        iDownstream.EndBlock();
        iBuf.Replace(Brx::Empty());
        iRemainingSamples = iNumSamples;
    }
}

void ProcessorAggregateUnpacked::BeginBlock()
{
}

void ProcessorAggregateUnpacked::ProcessFragment8(const Brx& aData, TUint aNumChannels)
{
    const TUint numSamples = aData.Bytes() / aNumChannels;
    const TByte* p = aData.Ptr();
    const TUint unpackedSampleBytes = 4 * aNumChannels;
    TByte unpackedSample[kMaxSampleBytes];
    for (TUint i=0; i<numSamples; i++) {
        TByte* s = unpackedSample;
        for (TUint j=0; j<aNumChannels; j++) {
            *s++ = *p++;
            *s++ = 0;
            *s++ = 0;
            *s++ = 0;
        }
        Brn sample(unpackedSample, unpackedSampleBytes);
        ProcessUnpackedSample(sample, aNumChannels);
    }
}

void ProcessorAggregateUnpacked::ProcessFragment16(const Brx& aData, TUint aNumChannels)
{
    const TUint numSamples = aData.Bytes() / (aNumChannels * 2);
    const TByte* p = aData.Ptr();
    const TUint unpackedSampleBytes = 4 * aNumChannels;
    TByte unpackedSample[kMaxSampleBytes];
    for (TUint i=0; i<numSamples; i++) {
        TByte* s = unpackedSample;
        for (TUint j=0; j<aNumChannels; j++) {
            *s++ = *p++;
            *s++ = *p++;
            *s++ = 0;
            *s++ = 0;
        }
        Brn sample(unpackedSample, unpackedSampleBytes);
        ProcessUnpackedSample(sample, aNumChannels);
    }
}

void ProcessorAggregateUnpacked::ProcessFragment24(const Brx& aData, TUint aNumChannels)
{
    const TUint numSamples = aData.Bytes() / (aNumChannels * 3);
    const TByte* p = aData.Ptr();
    const TUint unpackedSampleBytes = 4 * aNumChannels;
    TByte unpackedSample[kMaxSampleBytes];
    for (TUint i=0; i<numSamples; i++) {
        TByte* s = unpackedSample;
        for (TUint j=0; j<aNumChannels; j++) {
            *s++ = *p++;
            *s++ = *p++;
            *s++ = *p++;
            *s++ = 0;
        }
        Brn sample(unpackedSample, unpackedSampleBytes);
        ProcessUnpackedSample(sample, aNumChannels);
    }
}

void ProcessorAggregateUnpacked::ProcessFragment32(const Brx& aData, TUint aNumChannels)
{
    const TUint numSamples = aData.Bytes() / (aNumChannels * 3);
    const TByte* p = aData.Ptr();
    const TUint sampleBytes = 4 * aNumChannels;
    for (TUint i=0; i<numSamples; i++) {
        Brn sample(p, sampleBytes);
        ProcessUnpackedSample(sample, aNumChannels);
        p += sampleBytes;
    }
}

void ProcessorAggregateUnpacked::EndBlock()
{
}

void ProcessorAggregateUnpacked::Flush()
{
}
