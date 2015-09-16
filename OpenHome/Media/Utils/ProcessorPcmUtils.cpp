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

void ProcessorPcmBufTest::ProcessSample8(const TByte* aSample, TUint aNumChannels)
{
    Brn sample(aSample, aNumChannels);
    ProcessFragment(sample);
}

void ProcessorPcmBufTest::ProcessSample16(const TByte* aSample, TUint aNumChannels)
{
    Brn sample(aSample, 2*aNumChannels);
    ProcessFragment(sample);
}

void ProcessorPcmBufTest::ProcessSample24(const TByte* aSample, TUint aNumChannels)
{
    Brn sample(aSample, 3*aNumChannels);
    ProcessFragment(sample);
}

void ProcessorPcmBufTest::ProcessSample32(const TByte* aSample, TUint aNumChannels)
{
    Brn sample(aSample, 4*aNumChannels);
    ProcessFragment(sample);
}

void ProcessorPcmBufTest::EndBlock()
{
}


// ProcessorSample

ProcessorSample::ProcessorSample(IPcmProcessor& aDownstream)
    : iDownstream(aDownstream)
{
}

void ProcessorSample::BeginBlock()
{
    iDownstream.BeginBlock();
}

void ProcessorSample::ProcessFragment8(const Brx& aData, TUint aNumChannels)
{
    const TUint bytesPerSample = aNumChannels;
    const TUint numSamples = aData.Bytes() / bytesPerSample;
    const TByte* ptr = aData.Ptr();
    for (TUint i=0; i<numSamples; i++) {
        iDownstream.ProcessSample8(ptr, bytesPerSample);
        ptr += bytesPerSample;
    }
}

void ProcessorSample::ProcessFragment16(const Brx& aData, TUint aNumChannels)
{
    const TUint bytesPerSample = 2 * aNumChannels;
    const TUint numSamples = aData.Bytes() / bytesPerSample;
    const TByte* ptr = aData.Ptr();
    for (TUint i=0; i<numSamples; i++) {
        iDownstream.ProcessSample16(ptr, bytesPerSample);
        ptr += bytesPerSample;
    }
}

void ProcessorSample::ProcessFragment24(const Brx& aData, TUint aNumChannels)
{
    const TUint bytesPerSample = 3 * aNumChannels;
    const TUint numSamples = aData.Bytes() / bytesPerSample;
    const TByte* ptr = aData.Ptr();
    for (TUint i=0; i<numSamples; i++) {
        iDownstream.ProcessSample24(ptr, bytesPerSample);
        ptr += bytesPerSample;
    }
}

void ProcessorSample::ProcessFragment32(const Brx& aData, TUint aNumChannels)
{
    const TUint bytesPerSample = 4 * aNumChannels;
    const TUint numSamples = aData.Bytes() / bytesPerSample;
    const TByte* ptr = aData.Ptr();
    for (TUint i=0; i<numSamples; i++) {
        iDownstream.ProcessSample32(ptr, bytesPerSample);
        ptr += bytesPerSample;
    }
}

void ProcessorSample::ProcessSample8(const TByte* aSample, TUint aNumChannels)
{
    iDownstream.ProcessSample8(aSample, aNumChannels);
}

void ProcessorSample::ProcessSample16(const TByte* aSample, TUint aNumChannels)
{
    iDownstream.ProcessSample16(aSample, aNumChannels);
}

void ProcessorSample::ProcessSample24(const TByte* aSample, TUint aNumChannels)
{
    iDownstream.ProcessSample24(aSample, aNumChannels);
}

void ProcessorSample::ProcessSample32(const TByte* aSample, TUint aNumChannels)
{
    iDownstream.ProcessSample32(aSample, aNumChannels);
}

void ProcessorSample::EndBlock()
{
    iDownstream.EndBlock();
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

void ProcessorAggregateUnpacked::ProcessSample8(const TByte* aSample, TUint aNumChannels)
{
    const TUint unpackedSampleBytes = 4 * aNumChannels;
    TByte unpackedSample[kMaxSampleBytes];
    TByte* s = unpackedSample;
    for (TUint j=0; j<aNumChannels; j++) {
        *s++ = *aSample++;
        *s++ = 0;
        *s++ = 0;
        *s++ = 0;
    }
    Brn sample(unpackedSample, unpackedSampleBytes);
    ProcessUnpackedSample(sample, aNumChannels);
}

void ProcessorAggregateUnpacked::ProcessSample16(const TByte* aSample, TUint aNumChannels)
{
    const TUint unpackedSampleBytes = 4 * aNumChannels;
    TByte unpackedSample[kMaxSampleBytes];
    TByte* s = unpackedSample;
    for (TUint j=0; j<aNumChannels; j++) {
        *s++ = *aSample++;
        *s++ = *aSample++;
        *s++ = 0;
        *s++ = 0;
    }
    Brn sample(unpackedSample, unpackedSampleBytes);
    ProcessUnpackedSample(sample, aNumChannels);
}

void ProcessorAggregateUnpacked::ProcessSample24(const TByte* aSample, TUint aNumChannels)
{
    const TUint unpackedSampleBytes = 4 * aNumChannels;
    TByte unpackedSample[kMaxSampleBytes];
    TByte* s = unpackedSample;
    for (TUint j=0; j<aNumChannels; j++) {
        *s++ = *aSample++;
        *s++ = *aSample++;
        *s++ = *aSample++;
        *s++ = 0;
    }
    Brn sample(unpackedSample, unpackedSampleBytes);
    ProcessUnpackedSample(sample, aNumChannels);
}

void ProcessorAggregateUnpacked::ProcessSample32(const TByte* aSample, TUint aNumChannels)
{
    Brn sample(aSample, aNumChannels*4);
    ProcessUnpackedSample(sample, aNumChannels);
}

void ProcessorAggregateUnpacked::EndBlock()
{
}
