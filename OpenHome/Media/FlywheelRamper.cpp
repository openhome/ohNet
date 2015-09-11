#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/FlywheelRamper.h>
#include <OpenHome/Private/Debug.h>

using namespace OpenHome;
using namespace OpenHome::Media;
using namespace std;


static const TUint kDegree = 20;

static const TUint kBurgCoeffCount = kDegree+1;

double gMax = 0;
double gMin = 0;

////////////////////////////////////////////////////////////////////////////////////////////

FlywheelRamper::FlywheelRamper(TUint aGenerationJiffies, TUint aRampMs)
    :iGenerationJiffies(aGenerationJiffies)
    ,iRampMs(aRampMs)
    ,iDegree(kDegree)
    ,iRampSamples(Bytes(192000, iRampMs*Jiffies::kPerMs, kBytesPerSample))
    ,iProcessor(new PcmProcessorFwr(*this, iGenerationJiffies))
{

}

FlywheelRamper::FlywheelRamper(TUint aDegree, TUint aGenerationJiffies, TUint aRampMs)
    :iGenerationJiffies(aGenerationJiffies)
    ,iRampMs(aRampMs)
    ,iDegree(aDegree)
    ,iRampSamples(Bytes(192000, iRampMs*Jiffies::kPerMs, kBytesPerSample))
    ,iProcessor(new PcmProcessorFwr(*this, iGenerationJiffies))
{

}

FlywheelRamper::~FlywheelRamper()
{
    //Log::Print("BurgsMethod::ToInt32  max=%f  min=%f\n", gMax, gMin);
}

IPcmProcessor& FlywheelRamper::Ramp(IWriter& aWriter, TUint aSampleRate)
{
    iSampleRate = aSampleRate;
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
    Log::Print("\nFlywheelRamper::CreateRampForSingleChannel \n");

    TUint64 checkBytes = Bytes(iSampleRate, iGenerationJiffies, kBytesPerSample);
    //Log::Print("checkBytes=%lld  aSamples.Bytes()=%d \n", checkBytes, aSamples.Bytes());
    ASSERT(aSamples.Bytes()==checkBytes);

    // get the coeffs from Burg's Method

    std::vector<TInt32> coeffs;
    BurgsMethod::Coeffs(iDegree, aSamples, coeffs);

    //Log::Print("Burg output coeffs  \n");
    //LogDouble(coeffs, 4);
    //Log::Print("\n");
    //Log32(coeffs, false);
    //Log::Print(" (3.29) \n");

    //Log::Print("min=%f max=%f\n", gMin, gMax);

    ASSERT(coeffs.size()==kDegree);


    // Reverse and invert the coeffs and reverse the input data
    std::vector<TInt32> invCoeffs;
    std::vector<TInt32> revInvCoeffs;
    Invert(coeffs, invCoeffs);
    Reverse(invCoeffs, revInvCoeffs);



    //LogDouble(invCoeffs, 4);
    //Log::Print(" inverted \n");

    //LogDouble(revInvCoeffs, 4);
    //Log::Print(" reversed and inverted\n");
    //Log32(revInvCoeffs, false);
    //Log::Print(" (3.29) reversed and inverted\n");

    //Log::Print("\nLast %d samples of input data:\n", kDegree);

    //Log32(aSamples.Split(aSamples.Bytes()-(kDegree*4)));
    //Log::Print("\n");

    Bwh samplesRev(iDegree*4);
    Brn lastSamples(aSamples.Split(aSamples.Bytes()-(iDegree*4)));
    Reverse(lastSamples, samplesRev);
    //LogDouble(samplesRev, 4);
    //Log::Print(" reversed\n");

    const TUint kFeedbIterations = Bytes(iSampleRate, iRampMs*Jiffies::kPerMs, 4)/4; // output samples requested

    // Run the Feedback model with the coeffs and data
    auto feedb = new FeedbackModel(invCoeffs, 8, 4, 1, 1);
    TUint samplesOutFeedbBytes = (kFeedbIterations*4);
    Log::Print("samplesOutFeedbBytes=%d \n", samplesOutFeedbBytes);

    Bwh samplesOutFeedb(samplesOutFeedbBytes);
    samplesOutFeedb.SetBytes(0);
    feedb->Process(samplesRev, samplesOutFeedb, kFeedbIterations);


    //Log::Print("\nOutput samples: \n");

    //LogDouble(samplesOutFeedb, 4); // show the output samples in double format (1.31)
    //Log::Print("\n");
    //Log32(samplesOutFeedb); // show the ouput samples in fixed point format (1.31)
    //Log::Print(" (1.31)\n");

    // write output from Feedback model to iWriter
    iWriter->Write(samplesOutFeedb);
    iWriter->WriteFlush();

}



void FlywheelRamper::Reverse(const Brx& aInput, Bwx& aReversed)
{
    aReversed.SetBytes(0);
    TUint readStartIndex = aInput.Bytes()-4;

    for(TUint i=0; i<aInput.Bytes(); i+=4)
    {
        //Log::Print("i=%d \n", i);
        aReversed.Append(aInput[readStartIndex-i]);
        aReversed.Append(aInput[readStartIndex+1-i]);
        aReversed.Append(aInput[readStartIndex+2-i]);
        aReversed.Append(aInput[readStartIndex+3-i]);
    }
}


void FlywheelRamper::Reverse(std::vector<TInt32>& aInput, std::vector<TInt32>& aOutput)
{
    for(auto it = aInput.rbegin(); it!= aInput.rend(); it++)
    {
        aOutput.push_back(*it);
    }
}


void FlywheelRamper::Invert(std::vector<TInt32>& aInput, std::vector<TInt32>& aOutput)
{
    for(auto it = aInput.begin(); it!= aInput.end(); it++)
    {
        TInt32 x = *it;
        // 2's compliment
        x ^= 0xffffffff;  // 1's compliment
        x++; // add 1
        aOutput.push_back(x);
    }
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

TInt32 FlywheelRamper::Int32(const Brx& aSamples, TUint aIndex)
{
    TInt32 sample = (TInt32)aSamples[aIndex];
    sample <<= 8;
    sample |= (TInt32)aSamples[aIndex+1];
    sample <<= 8;
    sample |= (TInt32)aSamples[aIndex+2];
    sample <<= 8;
    sample |= (TInt32)aSamples[aIndex+3];
    return(sample);
}

TUint FlywheelRamper::Bytes(TUint aSampleRate, TUint aJiffies, TUint aBytesPerSample)
{
    TUint64 bytes = (((TUint64)aSampleRate*aBytesPerSample*aJiffies)/Jiffies::kPerSecond);
    //Log::Print("aChannelCount=%d  aSampleRate=%d  kBytesPerSample=%d  aJiffies=%d  Jiffies::kPerSecond=%d   bytes=%lld\n", aChannelCount, aSampleRate, kBytesPerSample, aJiffies, Jiffies::kPerSecond, bytes);
    return((TUint)bytes);
}


void FlywheelRamper::LogBuf(const Brx& aBuf)
{
    for(TUint i=0; i<aBuf.Bytes(); i++)
    {
        Log::Print("%x ", aBuf[i]);
    }
    Log::Print("\n");
}


void FlywheelRamper::LogDouble(std::vector<double>& aVals)
{
    for (TUint i=0; i<aVals.size();i++)
    {
        Log::Print("%.8f ", aVals[i]);
    }
    //Log::Print("\n");
}

void FlywheelRamper::LogDouble(const Brx& aBuf, TUint aScale)
{
    for (TUint i=0; i<aBuf.Bytes();)
    {
        TInt32 x = Int32(aBuf, i);
        double d = BurgsMethod::ToDouble(x, aScale);
        Log::Print("%.8f ", d);
        i+=4;
    }

    //Log::Print("\n");
}


void FlywheelRamper::LogDouble(std::vector<TInt32>& aVals, TUint aScale)
{
    for (TUint i=0; i<aVals.size(); i++)
    {
        TInt32 x = aVals[i];
        double d = BurgsMethod::ToDouble(x, aScale);
        Log::Print("%.8f ", d);
    }

    //Log::Print("\n");
}


void FlywheelRamper::Log32(const Brx& aBuf)
{
    for (TUint i=0; i<aBuf.Bytes();)
    {
        TInt32 x = Int32(aBuf, i);
        Log::Print("0x%.8x ", x);
        i+=4;
    }

    //Log::Print("\n");
}


void FlywheelRamper::Log32(std::vector<TInt32>& aVals)
{
    for (TUint i=0; i<aVals.size(); i++)
    {
        TInt32 x = aVals[i];
        Log::Print("0x%.8x ", x);
    }
    //Log::Print("\n");
}


///////////////////////////////////////////////////////////////////////

PcmProcessorFwr::PcmProcessorFwr(FlywheelRamper& aFwr, TUint aGenerationJiffies)
    :iFwr(aFwr)
    ,iSamples(FlywheelRamper::Bytes(192000, aGenerationJiffies, FlywheelRamper::kBytesPerSample))
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
    //Log::Print("ProcessFragment16 \n ");

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


///////////////////////////////////////////////////////////////////////////////////////


FeedbackModel::FeedbackModel(const std::vector<TInt32>& aCoeffs, TUint aDataScaleBitCount, TUint aCoeffFormat, TUint aDataFormat, TUint aOutputFormat)
    :iCoeffs(aCoeffs)
    ,iStateCount(iCoeffs.size())
    ,iSamples(iCoeffs.size(), 0)
    ,iDataScaleBitCount(aDataScaleBitCount)
    ,iScaleShiftForProduct(32-aCoeffFormat)
    ,iScaleShiftForOutput(32-aCoeffFormat-aDataFormat-iDataScaleBitCount+aOutputFormat)
{
    //Log::Print("\n\nFeedback Model: %d, %d, %d, %d, iScaleShiftForOutput=%d\n", aDataScaleBitCount, aCoeffFormat, aDataFormat, aOutputFormat, iScaleShiftForOutput);
    //Log::Print("\n\n");
    //Log::Print("Input coeffs: ");
    //FlywheelRamper::LogDouble(iCoeffs, aCoeffFormat);
    //Log::Print("\n");
}

void FeedbackModel::Process(const Brx& aSamplesIn, Bwx& aSamplesOut)
{
    Process(aSamplesIn, aSamplesOut, aSamplesOut.Bytes()/4);
}


void FeedbackModel::Process(const Brx& aSamplesIn, Bwx& aSamplesOut, TUint aCount)
{
    //Log::Print("Input states: ");
    //FlywheelRamper::Log32(aSamplesIn);
    //Log::Print("\n");

    ASSERT((aSamplesIn.Bytes()/4) == iStateCount);

    //aSamplesOut.SetBytes(0);

    //TUint index = 0;
    TUint smpByteIdx = 0;

    // put the innitial states into the circular buffer
    for(TUint i=0; i<iStateCount; i++)
    {
        TInt32 sampleIn =   (aSamplesIn[smpByteIdx]<<24) |
                            (aSamplesIn[smpByteIdx+1]<<16) |
                            (aSamplesIn[smpByteIdx+2]<<8) |
                             aSamplesIn[smpByteIdx+3];

        smpByteIdx += 4;

        iSamples[i] = (sampleIn>>iDataScaleBitCount); // 1.31 > 9.23  scale down for multiply
    }



    for(TUint i=0; i<aCount; i++)
    {
        TInt64 sum = 0;


        // iterate through the circular buff and calculate the output
        for (TUint j=0; j<iStateCount; j++)
        {
            TInt64 product = ((TInt64)iSamples[j]) * (((TInt64)iCoeffs[j])); // 1.31 * 1.31 = 2.62 (10.54 with >>8 data  scaling etc)

/*  Next block only needed for logging

            Log::Print("iSamples[%d]*iCoeffs[%d] = 0x%.8lx * 0x%.8lx   \n", j,j, iSamples[j], iCoeffs[j]);
            double data = BurgsMethod::ToDouble(iSamples[j]<<iDataScaleBitCount);
            double coeff = BurgsMethod::ToDouble_329(iCoeffs[j]);
            double dProd = data*coeff;
            Log::Print("iSamples[%d]*iCoeffs[%d] : %.8f * %.8f  =  %.8f\n", j,j, data, coeff, dProd);
            TInt32 scaledProduct = (TInt32)(product<<(-iScaleShiftForOutput));
            TInt32 scaledProduct = (TInt32)(product>>iScaleShiftForOutput);
            double d = BurgsMethod::ToDouble(scaledProduct);
            Log::Print("product = 0x%.16llx  scaled = 0x%.8lx  (%f)  iScaleShiftForOutput=%d \n\n", product, scaledProduct, d, iScaleShiftForOutput);
*/

            sum += product;

        }

        //Log::Print("\n");

        // update the states
        for (TUint j=(iStateCount-1); j>0; j--)
        {
            iSamples[j] = iSamples[j-1];
        }

        iSamples[0] = (TInt32)(sum>>iScaleShiftForProduct);


        sum >>= iScaleShiftForOutput;


        aSamplesOut.Append( (TByte)(sum>>24) );
        aSamplesOut.Append( (TByte)(sum>>16) );
        aSamplesOut.Append( (TByte)(sum>>8) );
        aSamplesOut.Append( (TByte)(sum) );

        //Log::Print("scaledOutSample=0x%.8lx  sampleOut=0x%.8lx  \n", scaledOutSample, FlywheelRamper::Int32(aSamplesOut, aSamplesOut.Bytes()-4));
    }



}

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

////////////////////////////////////////////////////////////////////////////////////////


void BurgsMethod::Coeffs(TUint aDegree, const Brx& aSamplesIn, std::vector<TInt32>& aCoeffsOut)
{
    TUint sampleCount = aSamplesIn.Bytes()/4;
    TUint coeffCount = kBurgCoeffCount;
    double* inputSamples = (double*) calloc (sampleCount, sizeof(double));
    double* outputCoeffs = (double*) calloc (coeffCount, sizeof(double));

    ToDouble(aSamplesIn, inputSamples, 1);
    ARMaxEntropy(inputSamples, sampleCount, aDegree, outputCoeffs);

    ToInt32(outputCoeffs+1, coeffCount-1, aCoeffsOut, 4); // discard the 1st coeff

    free(inputSamples);
    free(outputCoeffs);
}


// from : http://forums.devshed.com/programming-42/converting-12-20-fixed-float-636842.html

void BurgsMethod::ToInt32(double* aInput, TUint aLength, std::vector<TInt32>& aOutput, TUint aScale)
{
    for (TUint i=0; i<aLength; i++)
    {
        double val = *aInput;

        if (val>gMax)
        {
            gMax = val;
        }
        else if (val<gMin)
        {
            gMin = val;
        }

        //Log::Print("val=%f \n", val);

        TInt32 s = ToInt32(val, aScale);
        aOutput.push_back(s);
        aInput++;
    }

}


TInt32 BurgsMethod::ToInt32(double aVal, TUint aScale)
{
    TUint scaleFactor = (1<<(32-aScale));
    //Log::Print("BurgsMethod::ToInt32  scaleFactor=%lu \n", scaleFactor);
    TInt32 s = (TInt32) (aVal*scaleFactor); // 2^31
    return(s);
}


double BurgsMethod::ToDouble(TInt32 aVal, TUint aScale)
{
    TUint scaleFactor = (1<<(32-aScale));
    double dbl = (double)aVal/scaleFactor;
    return(dbl);
}


void BurgsMethod::ToDouble(const Brx& aInput, double* aOutput, TUint aScale)
{
    for (TUint i=0; i<aInput.Bytes(); i+=4)
    {
        TInt32 s = FlywheelRamper::Int32(aInput, i);
        *aOutput = ToDouble(s, aScale);
        aOutput++;
    }
}


void BurgsMethod::ARMaxEntropy (double *inputseries, TUint length, TUint degree, /*double *per, double *pef, double *h,*/ double *g)
{
    // degree = order of model (number of taps/coeffs)
    //
    // h : num elements = degree
    // per : num elements = length
    // pef : num elements = length
    // g : num elements = degree+1

    double* h = (double*) calloc (degree, sizeof(double));
    double* per = (double*) calloc (length, sizeof(double));
    double* pef = (double*) calloc (length, sizeof(double));


    for (TUint n = 1; n <= degree; n++)
    {
        double t1, t2;
        double sn = 0.0;
        double sd = 0.0;

        TUint jj = length - n;

        for (TUint j = 0; j < jj; j++)
        {
            t1 = inputseries [j + n] + pef [j];
            t2 = inputseries [j] + per [j];
            sn -= 2.0 * t1 * t2;
            sd += (t1 * t1) + (t2 * t2);
        }

        t1 = g [n] = sn / sd;
        if (n != 1)
        {
            for (TUint j = 1; j < n; j++)
            {
                h [j] = g [j] + t1 * g [n - j];
            }
            for (TUint j = 1; j < n; j++)
            {
                g [j] = h [j];
            }
            jj--;
        }

        for (TUint j = 0; j < jj; j++)
        {
            per [j] += t1 * pef [j] + t1 * inputseries [j + n];
            pef [j] = pef [j + 1] + t1 * per [j + 1] + t1 * inputseries [j + 1];
        }
    }

    // free memory
    free(h);
    free(per);
    free(pef);

}

