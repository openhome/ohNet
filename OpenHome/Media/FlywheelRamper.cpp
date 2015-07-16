#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/FlywheelRamper.h>
#include <OpenHome/Private/Debug.h>

using namespace OpenHome;
using namespace OpenHome::Media;
using namespace std;

/////////////////////////////////////////////

FlywheelRamper::FlywheelRamper(TUint aGenerationJiffies, TUint aRampMs)
    :iGenerationJiffies(aGenerationJiffies)
    ,iRampMs(aRampMs)
    ,iRampSamples(Bytes(192000, kMaxChannelCount, iRampMs*Jiffies::kPerMs, kBytesPerSample))
    ,iProcessor(new PcmProcessorFwr(*this, iGenerationJiffies))
{

}


IPcmProcessor& FlywheelRamper::Ramp(IWriter& aWriter, TUint aSampleRate, TUint aChannelCount)
{
    ASSERT(aChannelCount<=kMaxChannelCount);
    iSampleRate = aSampleRate;
    iChannelCount = aChannelCount;
    iWriter = &aWriter;
    return(*iProcessor);
}


TUint FlywheelRamper::RampMs() const
{
    return(iRampMs);
}


TUint FlywheelRamper::GenerationJiffies() const
{
    return(iGenerationJiffies);
}

void FlywheelRamper::CreateRamp(const Brx& aSamples)
{
    TUint64 checkBytes = Bytes(iSampleRate, iChannelCount, iGenerationJiffies, kBytesPerSample);
    //Log::Print("checkBytes=%lld  aSamples.Bytes()=%d", checkBytes, aSamples.Bytes());

    ASSERT(aSamples.Bytes()==checkBytes);

    iRampSamples.SetBytes(0);
    iRampSamples.Replace(aSamples);
    ApplyRamp(iRampSamples);
    iWriter->Write(iRampSamples);
    iWriter->WriteFlush();
}


void FlywheelRamper::ApplyRamp(Bwx& aSamples)
{
    TUint scalePerCent = 100;
    TUint bytesPerScaleDec = aSamples.Bytes()/100;

    for (TUint i=0; i<aSamples.Bytes();)
    {

        if ((i>0) && ((i%bytesPerScaleDec)==0))
        {
            if (scalePerCent>0)
            {
                scalePerCent--;
            }
        }

        Bwn sample(aSamples.Ptr()+i, kBytesPerSample, kBytesPerSample);
        ScaleSample(sample, scalePerCent);
        i += kBytesPerSample;
    }
}


void FlywheelRamper::ScaleSample(Bwx& aSample, TUint aScaleFactorPerCent)
{
    //Log::Print("scale = %d \n", aScaleFactorPerCent);
    TInt32 sample = Int32(aSample);
    TInt32 scaledSample = (TInt)(sample*aScaleFactorPerCent)/100;

    //Log::Print("scaledSample=%lx  sample=%lx  aScaleFactorPerCent=%d \n", scaledSample, sample, aScaleFactorPerCent);

    sample = scaledSample;
    aSample[0] = (sample>>24)&0xff;
    aSample[1] = (sample>>16)&0xff;
    aSample[2] = (sample>>8)&0xff;
    aSample[3] = sample&0xff;
}

TInt32 FlywheelRamper::Int32(Bwx& aSample, TUint aIndex)
{
    TInt32 sample = (TInt32)aSample[aIndex];
    sample <<= 8;
    sample |= (TInt32)aSample[aIndex+1];
    sample <<= 8;
    sample |= (TInt32)aSample[aIndex+2];
    sample <<= 8;
    sample |= (TInt32)aSample[aIndex+3];
    return(sample);
}

TUint FlywheelRamper::Bytes(TUint aSampleRate, TUint aChannelCount, TUint aJiffies, TUint aBytesPerSample)
{
    TUint64 bytes = (((TUint64)aChannelCount*aSampleRate*aBytesPerSample*aJiffies)/Jiffies::kPerSecond);
    //Log::Print("aChannelCount=%d  aSampleRate=%d  kBytesPerSample=%d  aJiffies=%d  Jiffies::kPerSecond=%d   bytes=%lld\n", aChannelCount, aSampleRate, kBytesPerSample, aJiffies, Jiffies::kPerSecond, bytes);
    return((TUint)bytes);
}


void FlywheelRamper::LogBuf(const Brx& aBuf)
{
    for(TUint x=0; x<aBuf.Bytes(); x++)
    {
        Log::Print("%x ", aBuf[x]);
    }
    Log::Print("\n");
}

///////////////////////////////////////////////////////////////////////

PcmProcessorFwr::PcmProcessorFwr(FlywheelRamper& aFwr, TUint aGenerationJiffies)
    :iFwr(aFwr)
    ,iSamples(FlywheelRamper::Bytes(192000, FlywheelRamper::kMaxChannelCount, aGenerationJiffies, FlywheelRamper::kBytesPerSample))
{

}


void PcmProcessorFwr::BeginBlock()
{
}


TBool PcmProcessorFwr::ProcessFragment8(const Brx& aSamples, TUint aNumChannels)
{
    if (iSamples.Bytes()==0)
    {
        iNumChannels = aNumChannels;
    }
    else
    {
        ASSERT(aNumChannels==iNumChannels);
    }
    for(TUint i=0; i<aSamples.Bytes();)
    {
        iSamples.Append(aSamples[i]);
        iSamples.Append((TByte)0); // pad lower 24 bits
        iSamples.Append((TByte)0); // pad lower 24 bits
        iSamples.Append((TByte)0); // pad lower 24 bits
        i+=1;
    }
    return(true);
}


TBool PcmProcessorFwr::ProcessFragment16(const Brx& aSamples, TUint aNumChannels)
{
    Log::Print("ProcessFragment16 \n ");

    if (iSamples.Bytes()==0)
    {
        iNumChannels = aNumChannels;
    }
    else
    {
        ASSERT(aNumChannels==iNumChannels);
    }
    ASSERT(aNumChannels==iNumChannels);
    for(TUint i=0; i<aSamples.Bytes();)
    {
        iSamples.Append(aSamples[i]);
        iSamples.Append(aSamples[i+1]);
        iSamples.Append((TByte)0); // pad lower 16 bits
        iSamples.Append((TByte)0); // pad lower 16 bits
        i += 2;
    }

    return(true);
}


TBool PcmProcessorFwr::ProcessFragment24(const Brx& aSamples, TUint aNumChannels)
{
    if (iSamples.Bytes()==0)
    {
        iNumChannels = aNumChannels;
    }
    else
    {
        ASSERT(aNumChannels==iNumChannels);
    }

    for(TUint i=0; i<aSamples.Bytes();)
    {
        iSamples.Append(aSamples[i]);
        iSamples.Append(aSamples[i+1]);
        iSamples.Append(aSamples[i+2]);
        iSamples.Append((TByte)0); // pad lower 8 bits
        i+=3;
    }

    return(true);
}


void PcmProcessorFwr::ProcessSample8(const TByte* aSample, TUint aNumChannels)
{
    Brn samples(aSample, aNumChannels);
    ProcessFragment8(samples, aNumChannels);
}


void PcmProcessorFwr::ProcessSample16(const TByte* aSample, TUint aNumChannels)
{
    Brn samples(aSample, 2*aNumChannels);
    ProcessFragment16(samples, aNumChannels);
}


void PcmProcessorFwr::ProcessSample24(const TByte* aSample, TUint aNumChannels)
{
    Brn samples(aSample, 3*aNumChannels);
    ProcessFragment24(samples, aNumChannels);
}


void PcmProcessorFwr::EndBlock()
{
    iFwr.CreateRamp(iSamples);
    iSamples.SetBytes(0);
}


////////////////////////////////////////////////////////////

ConvolutionModel::ConvolutionModel(const vector<TInt32>& aCoeffs, TUint aCoeffScaling, TUint aDataInScaling, TUint aDataOutScaling)
    :iCoeffs(aCoeffs)
    ,iSamples(iCoeffs.size(), 0)
    ,iCoeffScaling(aCoeffScaling)
    ,iDataInScaling(aDataInScaling)
    ,iDataOutScaling(aDataOutScaling)
    ,iScaleShift(24+(iDataOutScaling-(iCoeffScaling+iDataInScaling)))
{
    //Log::Print("iCoeffs.size()=%d ", iCoeffs.size());
    //Log::Print("iSamples.size()=%d \n", iSamples.size());
}


void ConvolutionModel::Process(const Brx& aSamplesIn, Bwx& aSamplesOut)
{
    Process(aSamplesIn, aSamplesOut, aSamplesOut.Bytes()/4);
}


void ConvolutionModel::Process(const Brx& aSamplesIn, Bwx& aSamplesOut, TUint aCount)
{
//    Log::Print("aCycleCount=%d  aSamplesIn.Bytes()=%d  iCoeffs.size()=%d \n", aCycleCount, aSamplesIn.Bytes(), iCoeffs.size());
    TUint sampleCount = aSamplesIn.Bytes()/4;
    ASSERT(aCount<=(sampleCount+iCoeffs.size()-1));
    TUint index = 0;
    TUint smpByteIdx = 0;

    for(TUint i=0; i<aCount; i++)
    {
        // insert the sample in the next slot in the circular buffer
        if (smpByteIdx>=aSamplesIn.Bytes())
        {
            iSamples[index] = 0;
        }
        else
        {
            iSamples[index] = (aSamplesIn[smpByteIdx]<<24) | (aSamplesIn[smpByteIdx+1]<<16) | (aSamplesIn[smpByteIdx+2]<<8) | aSamplesIn[smpByteIdx+3];
            smpByteIdx += 4;
        }

        //Log::Print("cycle %d\nsampleIn=0x%.8lx  (0x%.8lx)\n", i, iSamples[index], iSamples[index]>>8);

        iSamples[index] >>= 8; // 1.31 > 9.23 (FPFN)

        // iterate through the circular buff and apply the coeffs
        TInt64 outSample = 0;
        for (TUint j=0; j<iCoeffs.size(); )
        {
            outSample +=  ((TInt64)iSamples[index])*((TInt64)iCoeffs[j]);  // 9.23*1.31 > 10.54 (fixed point fractional)
            //Log::Print("(iSamples[%d]) 0x%.8lx * 0x%.8lx (iCoeffs[%d]) outSample=0x%.16llx   j=%d\n", index, iSamples[index], iCoeffs[j], j, outSample, j);

            if ( (++j) >= iCoeffs.size() )
            {
                break;
                // this will leave index 1 less than it was when we entered this loop
                // (we're populating circular buffer in reverse)
            }

            if ((++index)>=iCoeffs.size())
            {
                index = 0;
            }
        }


        // need to convert 10.54 > 1.31
        //
        // 10.54 > 1.63 (<<9)
        // convert from 64bit to 32bit (>>32)
        // total = >>(32-9) = >>23


        aSamplesOut.Append( (TByte)(outSample>>(iScaleShift+24)) );
        aSamplesOut.Append( (TByte)(outSample>>(iScaleShift+16)) );
        aSamplesOut.Append( (TByte)(outSample>>(iScaleShift+8)) );
        aSamplesOut.Append( (TByte)(outSample>>iScaleShift) );



        // descale (<<8) - because we scaled (>>8) earlier
        // convert 2.62 format to 1.63 format (<<1)
        // that's (<<9)
        // but we only want the upper 32 bits (>>32)
        // that's >>23 in total

        //Log::Print("outSample=0x%.16llx  sampleOut=0x%.8lx  cycle=%d\n\n\n", outSample, FlywheelRamper::Int32(aSamplesOut, aSamplesOut.Bytes()-4),  i);
    }
}

///////////////////////////////////////////////////////////////////////////////////////


FeedbackModel::FeedbackModel(const std::vector<TInt32>& aCoeffs, TUint aCoeffScaling, TUint aDataInScaling, TUint aDataOutScaling)
    :iCoeffs(aCoeffs)
    ,iSamples(iCoeffs.size(), 0)
    ,iCoeffScaling(aCoeffScaling)
    ,iDataInScaling(aDataInScaling)
    ,iDataOutScaling(aDataOutScaling)
    ,iScaleShift(24+(iDataOutScaling-(iCoeffScaling+iDataInScaling)))
{

}

void FeedbackModel::Process(const Brx& aSamplesIn, Bwx& aSamplesOut)
{
    Process(aSamplesIn, aSamplesOut, aSamplesOut.Bytes()/4);
}


void FeedbackModel::Process(const Brx& aSamplesIn, Bwx& aSamplesOut, TUint aCount)
{
//    Log::Print("aCycleCount=%d  aSamplesIn.Bytes()=%d  iCoeffs.size()=%d \n", aCycleCount, aSamplesIn.Bytes(), iCoeffs.size());
    TUint sampleCount = aSamplesIn.Bytes()/4;
    ASSERT(aCount<=(sampleCount+iCoeffs.size()));
    TUint index = 0;
    TUint smpByteIdx = 0;

    for(TUint i=0; i<aCount; i++)
    {
        TInt32 sampleIn = 0;

        if (smpByteIdx<aSamplesIn.Bytes())
        {
            sampleIn = (aSamplesIn[smpByteIdx]<<24) | (aSamplesIn[smpByteIdx+1]<<16) | (aSamplesIn[smpByteIdx+2]<<8) | aSamplesIn[smpByteIdx+3];
            smpByteIdx += 4;
        }

        //Log::Print("cycle %d\nsampleIn=0x%.8lx  (0x%.8lx)\n", i, sampleIn, sampleIn>>8);
        sampleIn >>= 8;


        // iterate through the circular buff and apply the coeffs
        TInt64 outSample = (TInt64)sampleIn;
        //Log::Print("outSample=0x%.16llx \n", outSample);
        for (TUint j=0; j<iCoeffs.size(); )
        {
            outSample += ((TInt64)iSamples[index]) * ((TInt64)iCoeffs[j]) ;
            //Log::Print("(iSamples[%d]) 0x%.8lx * 0x%.8lx (iCoeffs[%d]) outSample=0x%.16llx   j=%d\n", index, iSamples[index], iCoeffs[j], j, outSample, j);

            if ( (++j) >= iCoeffs.size() )
            {
                break;
                // this will leave index 1 less than it was when we entered this loop
                // (we're populating circular buffer in reverse)
            }

            if ((++index)>=iCoeffs.size())
            {
                index = 0;
            }
        }



        // insert the output sample in the next slot in the circular buffer
        // truncate the output sample to 32bits before feeding back in
        iSamples[index] = (TInt32)(outSample>>iScaleShift); // output back into input (feedback)


        // write the upper 32 bits of the 64 bit processed sample into the output buffer

        aSamplesOut.Append( (TByte)(outSample>>(iScaleShift+24)) );
        aSamplesOut.Append( (TByte)(outSample>>(iScaleShift+16)) );
        aSamplesOut.Append( (TByte)(outSample>>(iScaleShift+8)) );
        aSamplesOut.Append( (TByte)(outSample>>iScaleShift) );


        //Log::Print("outSample=0x%.16llx  sampleOut=0x%.8lx  \n\n", outSample, FlywheelRamper::Int32(aSamplesOut, aSamplesOut.Bytes()-4));
    }



}

