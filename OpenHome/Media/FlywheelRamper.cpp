#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/FlywheelRamper.h>
#include <OpenHome/Private/Debug.h>

using namespace OpenHome;
using namespace OpenHome::Media;
using namespace std;


static const TUint kDegree = 20;

double gMax = 0;
double gMin = 0;

////////////////////////////////////////////////////////////////////////////////////////////

FlywheelRamper::FlywheelRamper(TUint aGenJiffies, TUint aRampJiffies)
    :iGenJiffies(aGenJiffies)
    ,iRampJiffies(aRampJiffies)
    ,iDegree(kDegree)
    ,iRampSamples(Samples(192000, iRampJiffies)*kBytesPerSample)
    ,iProcessor(new PcmProcessorFwr(*this, iGenJiffies))
{

}

FlywheelRamper::FlywheelRamper(TUint aDegree, TUint aGenJiffies, TUint aRampJiffies)
    :iGenJiffies(aGenJiffies)
    ,iRampJiffies(aRampJiffies)
    ,iDegree(aDegree)
    ,iRampSamples(Samples(192000, iRampJiffies)*kBytesPerSample)
    ,iProcessor(new PcmProcessorFwr(*this, iGenJiffies))
{
    Log::Print("FlywheelRamper::FlywheelRamper  degree=%d\n", iDegree);
}

FlywheelRamper::~FlywheelRamper()
{
}

IPcmProcessor& FlywheelRamper::Ramp(IWriter& aWriter, TUint aSampleRate)
{
    iSampleRate = aSampleRate;
    iWriter = &aWriter;
    return(*iProcessor);
}


 TUint FlywheelRamper::RampJiffies() const
{
    return(iRampJiffies);
}


TUint FlywheelRamper::GenJiffies() const
{
    return(iGenJiffies);
}



/*
        TInt32* inputSamples = (TInt32*) calloc (sampleCount, sizeof(TInt32));
        TInt32* outputCoeffs = (TInt32*) calloc (coeffCount, sizeof(TInt32));
        TInt32* h = (TInt32*) calloc (aDegree, sizeof(TInt32));
        TInt32* per = (TInt32*) calloc (sampleCount, sizeof(TInt32));
        TInt32* pef = (TInt32*) calloc (sampleCount, sizeof(TInt32));


        TInt32* ipPtr = inputSamples;
        TInt32* opPtr = outputCoeffs;


        for(TUint i=0; i<aSamplesIn.Bytes(); )
        {
            *ipPtr = FlywheelRamper::Int32(aSamplesIn, i);
            i+=4;
            ipPtr++;

        }
        ARMaxEntropy(inputSamples, sampleCount, aDegree, outputCoeffs, h, per, pef);


        for(TUint i=0; i<coeffCount; i++)
        {
            if (i>0) // skip first coeff
            {
                aCoeffsOut.push_back(*opPtr);
            }
            opPtr++;
        }


        free(inputSamples);
        free(outputCoeffs);
        free(h);
        free(per);
        free(pef);



*/


void FlywheelRamper::CreateRamp(const Brx& aSamples)
{
    TUint64 checkBytes = Samples(iSampleRate, iGenJiffies)*kBytesPerSample;
    ASSERT(aSamples.Bytes()==checkBytes);

    // get the coeffs from Burg's Method

    std::vector<TInt32> coeffs;

    TUint sampleCount = aSamples.Bytes()/4;
    TUint coeffCount = iDegree+1;

    //BurgsMethod::Coeffs(iDegree, aSamples, coeffs);
    TInt32* inputSamples = (TInt32*) calloc (sampleCount, sizeof(TInt32));
    TInt32* outputCoeffs = (TInt32*) calloc (coeffCount, sizeof(TInt32));
    TInt32* h = (TInt32*) calloc (iDegree, sizeof(TInt32));
    TInt32* per = (TInt32*) calloc (sampleCount, sizeof(TInt32));
    TInt32* pef = (TInt32*) calloc (sampleCount, sizeof(TInt32));


    TInt32* ipPtr = inputSamples;
    TInt32* opPtr = outputCoeffs;


    for(TUint i=0; i<aSamples.Bytes(); )
    {
        *ipPtr = FlywheelRamper::Int32(aSamples, i);
        i+=4;
        ipPtr++;

    }
    BurgsMethod::ARMaxEntropy(inputSamples, sampleCount, iDegree, outputCoeffs, h, per, pef);


    for(TUint i=0; i<coeffCount; i++)
    {
        if (i>0) // skip first coeff
        {
            coeffs.push_back(*opPtr);
        }
        opPtr++;
    }




    // Reverse and invert the coeffs and reverse the input data
    std::vector<TInt32> invCoeffs;
    std::vector<TInt32> revInvCoeffs;
    Invert(coeffs, invCoeffs);
    Reverse(invCoeffs, revInvCoeffs);



    Bwh samplesRev(iDegree*kBytesPerSample);
    Brn lastSamples(aSamples.Split(aSamples.Bytes()-(iDegree*kBytesPerSample)));
    Reverse(lastSamples, samplesRev);

    const TUint kFeedbIterations = Samples(iSampleRate, iRampJiffies); // output samples requested

    // Run the Feedback model with the coeffs and data
    auto feedb = new FeedbackModel(invCoeffs, 8, 4, 1, 1);
    TUint samplesOutFeedbBytes = (kFeedbIterations*kBytesPerSample);
    //Log::Print("samplesOutFeedbBytes=%d \n", samplesOutFeedbBytes);

    Bwh samplesOutFeedb(samplesOutFeedbBytes);
    samplesOutFeedb.SetBytes(0);
    feedb->Process(samplesRev, samplesOutFeedb, kFeedbIterations);


    // write output from Feedback model to iWriter
    iWriter->Write(samplesOutFeedb);
    iWriter->WriteFlush();

}



void FlywheelRamper::Reverse(const Brx& aInput, Bwx& aReversed)
{
    aReversed.SetBytes(0);
    TUint readStartIndex = aInput.Bytes()-kBytesPerSample;

    for(TUint i=0; i<aInput.Bytes(); i+=kBytesPerSample)
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

TUint FlywheelRamper::Samples(TUint aSampleRate, TUint aJiffies)
{
    TUint64 samples = (((TUint64)aSampleRate*((TUint64)aJiffies))/((TUint64)Jiffies::kPerSecond));
    //Log::Print("FlywheelRamper::Samples  aSampleRate=%d  aJiffies=%d  Jiffies::kPerSecond=%d  samples=%lld\n", aSampleRate, aJiffies, Jiffies::kPerSecond, samples);
    return((TUint)samples);
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
    ,iSamples(FlywheelRamper::Samples(192000, aGenerationJiffies)*FlywheelRamper::kBytesPerSample)
{

}


void PcmProcessorFwr::BeginBlock()
{
}


TBool PcmProcessorFwr::ProcessFragment8(const Brx& aSamples, TUint /*aNumChannels*/)
{
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


TBool PcmProcessorFwr::ProcessFragment16(const Brx& aSamples, TUint /*aNumChannels*/)
{
    //Log::Print("ProcessFragment16 \n ");
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


TBool PcmProcessorFwr::ProcessFragment24(const Brx& aSamples, TUint /*aNumChannels*/)
{
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
    Brn samples(aSample, 1);
    ProcessFragment8(samples, aNumChannels);
}


void PcmProcessorFwr::ProcessSample16(const TByte* aSample, TUint aNumChannels)
{
    Brn samples(aSample, 2);
    ProcessFragment16(samples, aNumChannels);
}


void PcmProcessorFwr::ProcessSample24(const TByte* aSample, TUint aNumChannels)
{
    Brn samples(aSample, 3);
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
    Log::Print("Input coeffs: ");
    FlywheelRamper::LogDouble(iCoeffs, aCoeffFormat);
    Log::Print("\n");


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

    // put the initial states into the circular buffer
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

double BurgsMethod::ToDouble(TInt64 aVal, TUint aScale)
{
    // from : http://forums.devshed.com/programming-42/converting-12-20-fixed-float-636842.html

    TUint64 scaleFactor = (1<<(64-aScale));
    double dbl = (double)(aVal/scaleFactor);
    return(dbl);
}


double BurgsMethod::ToDouble(TInt32 aVal, TUint aScale)
{
    // from : http://forums.devshed.com/programming-42/converting-12-20-fixed-float-636842.html

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


void BurgsMethod::Coeffs(TUint aDegree, const Brx& aSamplesIn, std::vector<TInt32>& aCoeffsOut, TBool aFloatingPoint)
{
    //Log::Print(">BurgsMethod::Coeffs  degree=%d\n", aDegree);
    Log::Print("BurgsMethod::Coeffs  SamplesIn: ");

    aFloatingPoint = false;

    for(TUint i=0; i<12; i++)
    {
        Log::Print("%2x ", aSamplesIn[i]);
    }

    TUint sampleCount = aSamplesIn.Bytes()/4;
    TUint coeffCount = aDegree+1;

    if(aFloatingPoint)
    {
        double* inputSamples = (double*) calloc (sampleCount, sizeof(double));
        double* outputCoeffs = (double*) calloc (coeffCount, sizeof(double));
        double* h = (double*) calloc (aDegree, sizeof(double));
        double* per = (double*) calloc (sampleCount, sizeof(double));
        double* pef = (double*) calloc (sampleCount, sizeof(double));

        ToDouble(aSamplesIn, inputSamples, 1);
        ARMaxEntropy(inputSamples, sampleCount, aDegree, outputCoeffs, h, per, pef);
        //ToInt32(outputCoeffs+1, coeffCount-1, aCoeffsOut, 4); // discard the 1st coeff

        // free memory
        free(h);
        free(per);
        free(pef);
        free(inputSamples);
        free(outputCoeffs);
    }
    else
    {
        TInt32* inputSamples = (TInt32*) calloc (sampleCount, sizeof(TInt32));
        TInt32* outputCoeffs = (TInt32*) calloc (coeffCount, sizeof(TInt32));
        TInt32* h = (TInt32*) calloc (aDegree, sizeof(TInt32));
        TInt32* per = (TInt32*) calloc (sampleCount, sizeof(TInt32));
        TInt32* pef = (TInt32*) calloc (sampleCount, sizeof(TInt32));


        TInt32* ipPtr = inputSamples;
        TInt32* opPtr = outputCoeffs;


        for(TUint i=0; i<aSamplesIn.Bytes(); )
        {
            *ipPtr = FlywheelRamper::Int32(aSamplesIn, i);
            i+=4;
            ipPtr++;

        }
        ARMaxEntropy(inputSamples, sampleCount, aDegree, outputCoeffs, h, per, pef);


        for(TUint i=0; i<coeffCount; i++)
        {
            if (i>0) // skip first coeff
            {
                aCoeffsOut.push_back(*opPtr);
            }
            opPtr++;
        }


        free(inputSamples);
        free(outputCoeffs);
        free(h);
        free(per);
        free(pef);
    }


    //Log::Print("<BurgsMethod::Coeffs  degree=%d\n", aDegree);
}


void BurgsMethod::ARMaxEntropy (double* aInputseries, TUint aLength, TUint aDegree, double* aOutput, double* aH, double* aPer, double* aPef)
{
    Log::Print("\nBurgsMethod::ARMaxEntropy  (float) degree=%d\n\n", aDegree);

    for (TUint n = 1; n <= aDegree; n++)
    {
        double t1, t2;
        double sn = 0.0;
        double sd = 0.0;

        TUint jj = aLength - n;

        for (TUint j = 0; j < jj; j++)
        {
            t1 = aInputseries [j + n] + aPef [j];
            t2 = aInputseries [j] + aPef [j];
            double t1t2 = t1*t2;
            double t1t1 = t1*t1;
            double t2t2 = t2*t2;

            sn -= t1t2;
            sn -= t1t2;
            sd += t1t1;
            sd += t2t2;

        }

        t1 = aOutput[n] = sn / sd;

        if (n != 1)
        {
            Log::Print("+++++++\n");
            for (TUint j = 1; j < n; j++)
            {
                double prod =  (t1 * aOutput [n - j]);
                aH [j] = aOutput [j] + prod;
                Log::Print("aH[%d]=%lf \n", j, aH[j]);
            }
            Log::Print("#######\n");
            for (TUint j = 1; j < n; j++)
            {
                aOutput [j] = aH [j];
                Log::Print("aOutput[%d]=%lf \n", j, aOutput[j]);
            }
            jj--;
        }

        for (TUint j = 0; j < jj; j++)
        {
            aPer [j] += t1 * aPef [j] + t1 * aInputseries [j + n];
            aPef [j] = aPef [j + 1] + t1 * aPer [j + 1] + t1 * aInputseries [j + 1];
        }
    }

    for(TUint i=0; i<(aDegree+1) ; i++)
    {
        Log::Print("aOutput[%d]=%lf \n", i, aOutput[i]);
    }


}


void BurgsMethod::ARMaxEntropy (TInt32* aInputseries, TUint aLength, TUint aDegree, TInt32* aOutput, TInt32* aH, TInt32* aPer, TInt32* aPef)
{
    Log::Print("\n\n\nBurgsMethod::ARMaxEntropy  (fixed point) aDegree=%d  aLength=%d \n\n", aDegree, aLength);

    const TUint kDataScaleBitCount = 3;
    const TUint kScaleShiftForLog = kDataScaleBitCount+1;
    const TUint kScaleShiftForAdd = 32-kDataScaleBitCount-1;


    for (TUint n = 1; n <= aDegree; n++)
    {
        TInt32 t1;
        TInt32 t2;
        TInt64 sn = 0;
        TInt64 sd = 0;

        TUint jj = aLength - n;

        for (TUint j=0; j < jj; j++)
        {
            t1 = (aInputseries[j+n]>>kDataScaleBitCount) + aPef[j];
            t2 = (aInputseries[j]>>kDataScaleBitCount) + aPer[j];

            TInt64 t1t2 = ((TInt64)t1) * ((TInt64)t2);
            TInt64 t1t1 = ((TInt64)t1) * ((TInt64)t1);
            TInt64 t2t2 = ((TInt64)t2) * ((TInt64)t2);

            sn -= t1t2;
            sn -= t1t2;
            sd += t1t1;
            sd += t2t2;
        }


        TInt64 x = (sn)/(sd>>kScaleShiftForAdd);
        t1 = (TInt32)x;
        aOutput[n] = t1;


        if (n != 1)
        {
            Log::Print("+++++++\n");
            for (TUint j=1; j < n; j++)
            {
                TInt32 prod = ((TInt32)((((TInt64)t1) * ((TInt64)aOutput[n-j]))>>kScaleShiftForAdd));
                aH[j] = aOutput[j] + prod;
                Log::Print("aH[%d]=%lf \n", j, ToDouble(aH[j], kScaleShiftForLog));
            }

            Log::Print("#######\n");
            for (TUint j=1; j < n; j++)
            {
                aOutput[j] = aH[j];
                Log::Print("aOutput[%d]=%lf \n", j, ToDouble(aOutput[j], kScaleShiftForLog));

            }
            jj--;
        }


        for (TUint j = 0; j < jj; j++)
        {
            TInt64 x = (((((TInt64)t1) * ((TInt64)aPef[j])) + (((TInt64)t1) * ((TInt64)(aInputseries[j+n]>>kDataScaleBitCount))))>>kScaleShiftForAdd);
            aPer[j] += (TInt32)(x);
            aPef[j] = aPef[j+1] + ((TInt32)((((TInt64)t1) * ((TInt64)aPer[j+1]))>>kScaleShiftForAdd)) + ((TInt32)((((TInt64)t1) * ((TInt64)(aInputseries[j+1]>>kDataScaleBitCount)))>>kScaleShiftForAdd));
        }

    }

    for(TUint i=0; i<(aDegree+1) ; i++)
    {
        Log::Print("aOutput[%d]=%lf \n", i, ToDouble(aOutput[i], kScaleShiftForLog));
    }
}


