#include <OpenHome/Media/ProcessorPcmUtils.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// ProcessorPcmBuf

Brn ProcessorPcmBuf::Buf() const
{
    return Brn(iBuf);
}

const TByte* ProcessorPcmBuf::Ptr() const
{
    return iBuf.Ptr();
}

ProcessorPcmBuf::ProcessorPcmBuf()
    : iBuf(kBufferGranularity)
{
}

void ProcessorPcmBuf::CheckSize(TUint aAdditionalBytes)
{
    while (iBuf.Bytes() + aAdditionalBytes > iBuf.MaxBytes()) {
        const TUint size = iBuf.MaxBytes() + kBufferGranularity;
        iBuf.Grow(size);
    }
}

void ProcessorPcmBuf::ProcessFragment(const Brx& aData)
{
    CheckSize(aData.Bytes());
    iBuf.Append(aData);
}

void ProcessorPcmBuf::BeginBlock()
{
    iBuf.SetBytes(0);
}

void ProcessorPcmBuf::EndBlock()
{
}


// ProcessorPcmBufPacked

ProcessorPcmBufPacked::ProcessorPcmBufPacked()
{
}

TBool ProcessorPcmBufPacked::ProcessFragment8(const Brx& aData, TUint /*aNumChannels*/)
{
    ProcessFragment(aData);
    return true;
}

TBool ProcessorPcmBufPacked::ProcessFragment16(const Brx& aData, TUint /*aNumChannels*/)
{
    ProcessFragment(aData);
    return true;
}

TBool ProcessorPcmBufPacked::ProcessFragment24(const Brx& aData, TUint /*aNumChannels*/)
{
    ProcessFragment(aData);
    return true;
}

void ProcessorPcmBufPacked::ProcessSample8(const TByte* aSample, TUint aNumChannels)
{
    Brn sample(aSample, aNumChannels);
    ProcessFragment(sample);
}

void ProcessorPcmBufPacked::ProcessSample16(const TByte* aSample, TUint aNumChannels)
{
    Brn sample(aSample, 2*aNumChannels);
    ProcessFragment(sample);
}

void ProcessorPcmBufPacked::ProcessSample24(const TByte* aSample, TUint aNumChannels)
{
    Brn sample(aSample, 3*aNumChannels);
    ProcessFragment(sample);
}


// ProcessorPcmBufUnpacked

ProcessorPcmBufUnpacked::ProcessorPcmBufUnpacked()
{
}

TBool ProcessorPcmBufUnpacked::ProcessFragment8(const Brx& /*aData*/, TUint /*aNumChannels*/)
{
    return false;
}

TBool ProcessorPcmBufUnpacked::ProcessFragment16(const Brx& /*aData*/, TUint /*aNumChannels*/)
{
    return false;
}

TBool ProcessorPcmBufUnpacked::ProcessFragment24(const Brx& /*aData*/, TUint /*aNumChannels*/)
{
    return false;
}

void ProcessorPcmBufUnpacked::ProcessSample8(const TByte* aSample, TUint aNumChannels)
{
    TByte sample[4] = { 0 };
    for (TUint i=0; i<aNumChannels; i++) {
        sample[0] = *aSample;
        Brn sampleBuf(sample, 4);
        ProcessFragment(sampleBuf);
        aSample++;
    }
}

void ProcessorPcmBufUnpacked::ProcessSample16(const TByte* aSample, TUint aNumChannels)
{
    TByte sample[4] = { 0 };
    for (TUint i=0; i<aNumChannels; i++) {
        sample[0] = *aSample;
        aSample++;
        sample[1] = *aSample;
        aSample++;
        Brn sampleBuf(sample, 4);
        ProcessFragment(sampleBuf);
    }
}

void ProcessorPcmBufUnpacked::ProcessSample24(const TByte* aSample, TUint aNumChannels)
{
    TByte sample[4] = { 0 };
    for (TUint i=0; i<aNumChannels; i++) {
        sample[0] = *aSample;
        aSample++;
        sample[1] = *aSample;
        aSample++;
        sample[2] = *aSample;
        aSample++;
        Brn sampleBuf(sample, 4);
        ProcessFragment(sampleBuf);
    }
}


// ProcessorPcmBufPackedDualMono

ProcessorPcmBufPackedDualMono::ProcessorPcmBufPackedDualMono()
{
}

TBool ProcessorPcmBufPackedDualMono::ProcessFragment8(const Brx& /*aData*/, TUint /*aNumChannels*/)
{
    return false;
}

TBool ProcessorPcmBufPackedDualMono::ProcessFragment16(const Brx& /*aData*/, TUint /*aNumChannels*/)
{
    return false;
}

TBool ProcessorPcmBufPackedDualMono::ProcessFragment24(const Brx& /*aData*/, TUint /*aNumChannels*/)
{
    return false;
}

void ProcessorPcmBufPackedDualMono::ProcessSample8(const TByte* aSample, TUint aNumChannels)
{
    if (aNumChannels == 1) {
        aNumChannels = 2;
        for (TUint i=0; i<aNumChannels; i++) {
            Brn sampleBuf(aSample, 1);
            ProcessFragment(sampleBuf);
        }
    }
    else {
        Brn sample(aSample, aNumChannels);
        ProcessFragment(sample);
    }
}

void ProcessorPcmBufPackedDualMono::ProcessSample16(const TByte* aSample, TUint aNumChannels)
{
    if (aNumChannels == 1) {
        aNumChannels = 2;
        const TByte* sampleStart = aSample;
        TByte sample[2] = { 0 };
        for (TUint i=0; i<aNumChannels; i++) {
            aSample = sampleStart;
            sample[0] = *aSample;
            aSample++;
            sample[1] = *aSample;
            aSample++;
            Brn sampleBuf(sample, 2);
            ProcessFragment(sampleBuf);
        }
    }
    else {
        Brn sample(aSample, 2*aNumChannels);
        ProcessFragment(sample);
    }
}

void ProcessorPcmBufPackedDualMono::ProcessSample24(const TByte* aSample, TUint aNumChannels)
{
    if (aNumChannels == 1) {
        aNumChannels = 2;
        const TByte* sampleStart = aSample;
        TByte sample[3] = { 0 };
        for (TUint i=0; i<aNumChannels; i++) {
            aSample = sampleStart;
            sample[0] = *aSample;
            aSample++;
            sample[1] = *aSample;
            aSample++;
            sample[2] = *aSample;
            aSample++;
            Brn sampleBuf(sample, 3);
            ProcessFragment(sampleBuf);
        }
    }
    else {
        Brn sample(aSample, 2*aNumChannels);
        ProcessFragment(sample);
    }
}