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

void ProcessorSample::EndBlock()
{
    iDownstream.EndBlock();
}
