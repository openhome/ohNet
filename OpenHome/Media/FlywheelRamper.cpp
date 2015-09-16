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


void PcmProcessorFwr::ProcessFragment8(const Brx& aSamples, TUint aNumChannels)
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
}


void PcmProcessorFwr::ProcessFragment16(const Brx& aSamples, TUint aNumChannels)
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
}


void PcmProcessorFwr::ProcessFragment24(const Brx& aSamples, TUint aNumChannels)
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

ConvolutionModel::ConvolutionModel(const vector<TInt32>& aCoeffs, TUint aCoeffFormat, TUint aDataFormat, TUint aOutputFormat)
    :iCoeffs(aCoeffs)
    ,iSamples(iCoeffs.size(), 0)
    ,iCoeffFormat(aCoeffFormat)
    ,iDataFormat(aDataFormat)
    ,iOutputFormat(aOutputFormat)
    ,iDataScaleBitCount(8)
{
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

    aSamplesOut.SetBytes(0);

    TInt scaleShiftForOutput = 32-iCoeffFormat-iDataScaleBitCount-iDataFormat+iOutputFormat;


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

        iSamples[index] >>= iDataScaleBitCount; // 1.31 > 9.23 (FPFN)

        // iterate through the circular buff and apply the coeffs
        TInt64 outSample = 0;
        for (TUint j=0; j<iCoeffs.size(); )
        {
            outSample +=  ((TInt64)iSamples[index])*((TInt64)iCoeffs[j]);  // 9.23*1.31 > 10.54 (fixed point fractional)
            //Log::Print("(iSamples[%d]) 0x%.8lx * 0x%.8lx (iCoeffs[%d]) outSample=0x%.16llx   j=%d\n", index, iSamples[index], iCoeffs[j], j, outSample, j);

            if ( (++j) >= iCoeffs.size() )
            {
                break; // leave index 1 less than it was when we entered this loop (we're populating circular buffer in reverse)
            }

            if ((++index)>=iCoeffs.size())
            {
                index = 0;
            }
        }

        TInt64 scaledOutSample = (outSample>>scaleShiftForOutput);
        aSamplesOut.Append( (TByte)(scaledOutSample>>24) );
        aSamplesOut.Append( (TByte)(scaledOutSample>>16) );
        aSamplesOut.Append( (TByte)(scaledOutSample>>8) );
        aSamplesOut.Append( (TByte)(scaledOutSample) );

        //Log::Print("outSample=0x%.16llx  sampleOut=0x%.8lx  cycle=%d\n\n\n", outSample, FlywheelRamper::Int32(aSamplesOut, aSamplesOut.Bytes()-4),  i);
    }
}

///////////////////////////////////////////////////////////////////////////////////////


    // convert data to apt 64bit format for addition
    // 1.31*1.31 = 2.62  1/1/x  = <<31
    // 1.31*2.30 = 3.61  1/2/x  = <<31
    // 1.31*3.29 = 4.60  1/3/x  = <<31
    // 1.31*4.28 = 5.59  1/4/x  = <<31

    // 2.30*1.31 = 3.61  2/1/x  = <<30
    // 2.30*2.30 = 4.60  2/2/x  = <<30
    // 2.30*3.29 = 5.59  2/3/x  = <<30
    // 2.30*4.28 = 6.58  2/4/x  = <<30

    // 3.29*1.31 = 4.60  3/1/x  = <<29
    // 3.29*2.30 = 5.59  3/2/x  = <<29
    // 3.29*3.29 = 6.58  3/3/x  = <<29
    // 3.29*4.28 = 7.57  3/4/x  = <<29

    // 4.28*1.31 = 5.59  4/1/x  = <<28
    // 4.28*2.30 = 6.58  4/2/x  = <<28
    // 4.28*3.29 = 7.57  4/3/x  = <<28
    // 4.28*4.28 = 8.56  4/4/x  = <<28

    // convert output to dataIn format before feeding back in
    //
    // 1/1/x 1.31*1.31 : 2.62 convert 2.62 to 1.31 = >> 31
    // 1/2/x 1.31*2.30 : 3.61 convert 3.61 to 2.30 = >> 31
    // 1/3/x 1.31*3.29 : 4.60 convert 4.60 to 3.29 = >> 31
    // 1/4/x 1.31*4.28 : 5.59 convert 5.59 to 4.28 = >> 31

    // 2/1/x 2.30*1.31 : 3.61 convert 3.61 to 1.31 = >> 30
    // 2/2/x 2.30*2.30 : 4.60 convert 4.60 to 2.30 = >> 30
    // 2/3/x 2.30*3.29 : 5.59 convert 5.59 to 3.29 = >> 30
    // 2/4/x 2.30*4.28 : 6.58 convert 6.58 to 4.28 = >> 30

    // 3/1/x 3.29*1.31 : 4.60 convert 4.60 to 1.31 = >> 29
    // 3/2/x 3.29*2.30 : 5.59 convert 5.59 to 2.30 = >> 29
    // 3/3/x 3.29*3.29 : 6.58 convert 6.58 to 3.29 = >> 29
    // 3/4/x 3.29*4.28 : 7.57 convert 7.57 to 4.28 = >> 29

    // 4/1/x 4.28*1.31 : 5.59 convert 5.59 to 1.31 = >> 28
    // 4/2/x 4.28*2.30 : 6.58 convert 6.58 to 2.30 = >> 28
    // 4/3/x 4.28*3.29 : 7.57 convert 7.57 to 3.29 = >> 28
    // 4/4/x 4.28*4.28 : 8.56 convert 8.56 to 4.28 = >> 28


    // Convert multiplied format back to (standard) output format
    //
    // 1/1/x 1.31*1.31 : 2.62 convert 2.62 to 1.31 = >> 31
    // 1/2/x 1.31*2.30 : 3.61 convert 3.61 to 1.31 = >> 30
    // 1/3/x 1.31*3.29 : 4.60 convert 4.60 to 1.31 = >> 29
    // 1/4/x 1.31*4.28 : 5.59 convert 5.59 to 1.31 = >> 28

    // 2/1/x 2.30*1.31 : 3.61 convert 3.61 to 1.31 = >> 30
    // 2/2/x 2.30*2.30 : 4.60 convert 4.60 to 1.31 = >> 29
    // 2/3/x 2.30*3.29 : 5.59 convert 5.59 to 1.31 = >> 28
    // 2/4/x 2.30*4.28 : 6.58 convert 6.58 to 1.31 = >> 27

    // 3/1/x 3.29*1.31 : 4.60 convert 4.60 to 1.31 = >> 29
    // 3/2/x 3.29*2.30 : 5.59 convert 5.59 to 1.31 = >> 28
    // 3/3/x 3.29*3.29 : 6.58 convert 6.58 to 1.31 = >> 27
    // 3/4/x 3.29*4.28 : 7.57 convert 7.57 to 1.31 = >> 26

    // 4/1/x 4.28*1.31 : 5.59 convert 5.59 to 1.31 = >> 28
    // 4/2/x 4.28*2.30 : 6.58 convert 6.58 to 1.31 = >> 27
    // 4/3/x 4.28*3.29 : 7.57 convert 7.57 to 1.31 = >> 26
    // 4/4/x 4.28*4.28 : 8.56 convert 8.56 to 1.31 = >> 25

FeedbackModel::FeedbackModel(const std::vector<TInt32>& aCoeffs, TUint aDataScaleBitCount, TUint aCoeffFormat, TUint aDataFormat, TUint aOutputFormat)
    :iCoeffs(aCoeffs)
    ,iSamples(iCoeffs.size(), 0)
    ,iDataScaleBitCount(aDataScaleBitCount)
    ,iScaleShiftForSum(32-aCoeffFormat-iDataScaleBitCount)
    ,iScaleShiftForProduct(32-aCoeffFormat)
    ,iScaleShiftForOutput(aOutputFormat-iDataScaleBitCount-aDataFormat)
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

    aSamplesOut.SetBytes(0);

    TUint index = 0;
    TUint smpByteIdx = 0;

    for(TUint i=0; i<aCount; i++)
    {
        //Log::Print("\ncycle %d\n", i);
        TInt64 outSample = 0;
        TInt64 sampleInScaled = 0;

        if (smpByteIdx<aSamplesIn.Bytes())
        {
            TInt32 sampleIn =   (aSamplesIn[smpByteIdx]<<24) |
                                (aSamplesIn[smpByteIdx+1]<<16) |
                                (aSamplesIn[smpByteIdx+2]<<8) |
                                 aSamplesIn[smpByteIdx+3];

            smpByteIdx += 4;

            sampleInScaled = (((TInt64)sampleIn)<<iScaleShiftForSum); //format (1.31>2.62) for addition
            //Log::Print("cycle %d\nsampleIn=0x%.8lx  (0x%.8lx  scaled)  (0x%.16llx  aligned)\n", i, sampleIn, sampleIn>>(8-iDataFormat), sampleInScaled);
        }


        // iterate through the circular buff and apply the coeffs
        //Log::Print("outSample=0x%.16llx \n", outSample);
        for (TUint j=0; j<iCoeffs.size(); )
        {
            outSample += ((TInt64)iSamples[index]) * (((TInt64)iCoeffs[j])); // 1.31 * 1.31 = 2.62 (10.54 with >>8 data  scaling etc)
            //Log::Print("outSample = 0x%.16llx   j=%d\n", outSample, j);

            if ( (++j) >= iCoeffs.size() )
            {
                break;
                // this will leave index 1 less than it was when we entered this loop
                // (we're populating circular buffer in reverse)
            }

            if ( (++index) >=iCoeffs.size())
            {
                index = 0; // wrap around
            }
        }

        //Log::Print("outSample = 0x%.16llx +  0x%.16llx (sampleInScaled) =  0x%.16llx\n", outSample, sampleInScaled, (outSample+sampleInScaled));

        outSample += sampleInScaled;
        //Log::Print("total = 0x%.16llx \n", outSample);
        //Log::Print("0x%.16llx (reformatted for addition)\n", (outSample>>(32-iCoeffFormat)));


        // insert the output sample in the next slot in the circular buffer

        TInt64 fmOutSample = (outSample>>iScaleShiftForProduct); //format for multiplication
        iSamples[index] = (TInt32)fmOutSample;
        //Log::Print("iSamples[%d] = 0x%.8lx\n", index, iSamples[index]);

        if (iScaleShiftForOutput<0)
        {
           fmOutSample <<= -iScaleShiftForOutput;
        }
        else
        {
           fmOutSample >>= iScaleShiftForOutput;
        }

        TInt32 scaledOutSample = (TInt32) fmOutSample ; //format for output (2.62>1.31)

        aSamplesOut.Append( (TByte)(scaledOutSample>>24) );
        aSamplesOut.Append( (TByte)(scaledOutSample>>16) );
        aSamplesOut.Append( (TByte)(scaledOutSample>>8) );
        aSamplesOut.Append( (TByte)(scaledOutSample) );

        //Log::Print("scaledOutSample=0x%.8lx  sampleOut=0x%.8lx  \n", scaledOutSample, FlywheelRamper::Int32(aSamplesOut, aSamplesOut.Bytes()-4));
    }



}

