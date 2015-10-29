#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/FlywheelRamper.h>
#include <OpenHome/Private/Debug.h>

using namespace OpenHome;
using namespace OpenHome::Media;
using namespace std;

// 2 and 5

static const TUint kDataScaleShift = 2;
static const TUint kFeedbackDataFormat = kDataScaleShift+1;
static const TUint kBurgOutputFormat = 5;  // 4 gives better (less overflows) but divbyzero!
static const TUint kBurgScaleShift = 16-kBurgOutputFormat;
static const TUint kDegree = 3;

static const TUint kMaxChannelCount = 8;

static const TUint kMaxSampleRate = 192000;
static const TUint kMaxRampJiffiesBlockSize = Jiffies::kPerMs; // 1ms

//double gMax;
//double gMin;

////////////////////////////////////////////////////////////////////////////////////////////


FlywheelRamperManager::FlywheelRamperManager(/*OpenHome::Environment& aEnv, */IPcmProcessor& aOutput, TUint aGenJiffies, TUint aRampJiffies)
    :/*iEnv(aEnv)
    ,*/iOutput(aOutput)
    ,iOutBuf(FlywheelRamper::SampleCount(kMaxSampleRate, aRampJiffies)*kMaxChannelCount*4)
    ,iRampJiffies(aRampJiffies)
{
//    gMax = 0;
//    gMin = 0;


    //Log::Print("iOutBuf.MaxBytes() = %d \n", iOutBuf.MaxBytes());
    for(TUint i=0; i<kMaxChannelCount; i++)
    {
        iRampers.push_back(new FlywheelRamper(/*iEnv, */aGenJiffies));
    }
}


FlywheelRamperManager::~FlywheelRamperManager()
{
    for(TUint i=0; i<kMaxChannelCount; i++)
    {
        delete iRampers[i];
    }
}

void FlywheelRamperManager::Ramp(const Brx& aSamples, TUint aSampleRate, TUint aChannelCount)
{
    ASSERT(aChannelCount<=kMaxChannelCount);
    //Log::Print("FlywheelRamperManager::Ramp \n");

    //TUint startTime = Os::TimeInMs(iEnv.OsCtx());

    //for (TUint j=0; j<1000; j++)  // scale up for profiling
    {
        const TByte* ptr = aSamples.Ptr();
        TUint bytesPerChan = aSamples.Bytes()/aChannelCount;

        // initialise all the rampers
        for(TUint i=0; i<aChannelCount; i++)
        {
            Brn chanSamples(ptr, bytesPerChan);
            iRampers[i]->Initialise(chanSamples, aSampleRate);
            ptr += bytesPerChan;
        }
    }


    TUint decFactor = FlywheelRamper::DecimationFactor(aSampleRate);
    TUint remainingSamples = FlywheelRamper::SampleCount(aSampleRate, iRampJiffies);
    //Log::Print("rampSamplesPerChan = %d \n", rampSamplesPerChan);

    //TUint endPrepTime = Os::TimeInMs(iEnv.OsCtx());

    //Log::Print("FlywheelRamperManager::Ramp  processing\n");

    TUint maxRampSamplesBlockSize = FlywheelRamper::SampleCount(aSampleRate, kMaxRampJiffiesBlockSize);

    TUint outputBytes = 0;

    //for (TUint i=0; i<1000; i++)  // scale up for profiling
    {
        TUint sampleHoldCount = 0;
        TInt32 prevSample[aChannelCount];

        while (remainingSamples > 0)
        {
            TByte* ptr = (TByte*)iOutBuf.Ptr();
            outputBytes = 0;

            TUint rampSamples = remainingSamples;
            if (remainingSamples>maxRampSamplesBlockSize)
            {
                rampSamples = maxRampSamplesBlockSize;
            }

            remainingSamples -= rampSamples;

            for(TUint j=0; j<rampSamples; j++)
            {
                for(TUint k=0; k<aChannelCount; k++)
                {
                    TInt32 sample;
                    if (sampleHoldCount==0)
                    {
                        sample = iRampers[k]->NextSample();
                        //Log::Print("sample = %8x  chan=%d   sampleHoldCount=%d \n", sample, k, sampleHoldCount);
                        prevSample[k] = sample;
                    }
                    else
                    {
                        sample = prevSample[k];
                    }

                    //Log::Print("sample = %8x  chan=%d   sampleHoldCount=%d \n", sample, k, sampleHoldCount);

                    *(ptr+3) = (TByte) sample;
                    sample >>= 8;
                    *(ptr+2) = (TByte) sample;
                    sample >>= 8;
                    *(ptr+1) = (TByte) sample;
                    sample >>= 8;
                    *(ptr) = (TByte) sample;

                    ptr += 4;
                    outputBytes += 4;
                }

                sampleHoldCount++;

                if (sampleHoldCount > (decFactor-1))
                {
                    sampleHoldCount = 0;
                }
            }

            iOutBuf.SetBytes(outputBytes);
            iOutput.BeginBlock();
            iOutput.ProcessFragment32(iOutBuf, aChannelCount);
            iOutput.EndBlock();
        }
    }


    //TUint endGenTime = Os::TimeInMs(iEnv.OsCtx());
    //Log::Print("FWRMan prep time = %dms   sample pull time = %dms \n", endPrepTime-startTime, endGenTime-endPrepTime);

    Reset(); // clears memory ready for next ramp request
}


void FlywheelRamperManager::Reset()
{
    for(TUint i=0; i<kMaxChannelCount; i++)
    {
        iRampers[i]->Reset(); // clears memory ready for next ramp request
    }
}



////////////////////////////////////////////////////////////////////////////////////////////

FlywheelRamper::FlywheelRamper(/*OpenHome::Environment& aEnv,*/TUint aGenJiffies)
    :/*iEnv(aEnv)
    ,*/iGenJiffies(aGenJiffies)
    ,iDegree(kDegree)
    ,iFeedback(new FeedbackModel(iDegree, 0, kBurgOutputFormat, kFeedbackDataFormat, 1))
    ,iMaxGenSampleCount(SampleCount(kMaxSampleRate, iGenJiffies))
{
    iGenSamples = (TInt16*) calloc (iMaxGenSampleCount, sizeof(TInt16));
    iBurgPer = (TInt16*) calloc (iMaxGenSampleCount, sizeof(TInt16));
    iBurgPef = (TInt16*) calloc (iMaxGenSampleCount, sizeof(TInt16));
    iBurgCoeffs = (TInt16*) calloc (iDegree, sizeof(TInt16));
    iBurgH = (TInt16*) calloc (iDegree, sizeof(TInt16));

    iFeedbackSamples = (TInt32*) calloc (iDegree, sizeof(TInt32));

/*
    iFpGenSamples = (double*) calloc (iMaxGenSampleCount, sizeof(double));
    iFpBurgPer = (double*) calloc (iMaxGenSampleCount, sizeof(double));
    iFpBurgPef = (double*) calloc (iMaxGenSampleCount, sizeof(double));
    iFpBurgCoeffs = (double*) calloc (iDegree, sizeof(double));
    iFpBurgH = (double*) calloc (iDegree, sizeof(double));
*/
}


FlywheelRamper::~FlywheelRamper()
{
    free(iGenSamples);
    free(iBurgCoeffs);
    free(iBurgH);
    free(iBurgPer);
    free(iBurgPef);
    free(iFeedbackSamples);
    delete iFeedback;
}


TUint FlywheelRamper::GenJiffies() const
{
    return(iGenJiffies);
}


void FlywheelRamper::Initialise(const Brx& aSamples, TUint aSampleRate)
{
    //Log::Print("FlywheelRamper::Initialise \n");
    ASSERT(aSampleRate<=kMaxSampleRate);
    ASSERT(aSamples.Bytes()==(SampleCount(aSampleRate, iGenJiffies)*kBytesPerSample));
/*
    Log::Print("\nFlywheelRamper::Initialise samples in: \n");

    for (TUint i=0; i<aSamples.Bytes(); i++)  // scale up for profiling
    {
        Log::Print("%x ", aSamples[i]);
    }

    Log::Print("\n");
*/

    //double* iFpGenSampPtr = iFpGenSamples;

    // copy input samples out of buffer into memory
    TUint decFactor = DecimationFactor(aSampleRate);
    TInt16* iGenSampPtr = iGenSamples;
    const TByte* bufPtr = aSamples.Ptr();
    TUint sampleCount = aSamples.Bytes()/(kBytesPerSample*decFactor);
    TUint ptrInc = 4*decFactor;

    for(TUint i=0; i<sampleCount; i++)
    {
        TUint16 sample = (TUint16) (*(bufPtr));
        sample <<= 8;
        sample += (TUint16) (*(bufPtr+1));
        bufPtr += ptrInc;

        *(iGenSampPtr++) = ((TInt16)(sample))>>kDataScaleShift;
        //*(iFpGenSampPtr++) = ToDouble(((TInt32)sample)<<16, 1);
    }

    BurgsMethod(iGenSamples, sampleCount, iDegree, iBurgCoeffs, iBurgH, iBurgPer, iBurgPef);
    //BurgsMethod(iFpGenSamples, sampleCount, iDegree, iFpBurgCoeffs, iFpBurgH, iFpBurgPer, iFpBurgPef);

    // Invert the coeffs
    Invert(iBurgCoeffs, iDegree);

    // put the initial states into buffer (in reverse order)
    for(TUint i=0; i<iDegree; i++)
    {
        iFeedbackSamples[i] = ((TInt32)iGenSamples[sampleCount-1-i])<<16;
    }

    iFeedback->Initialise(iBurgCoeffs, iFeedbackSamples);
}


void FlywheelRamper::Reset()
{
    memset(iBurgPer, 0, iMaxGenSampleCount*sizeof(TInt16)); // clear
    memset(iBurgPef, 0, iMaxGenSampleCount*sizeof(TInt16)); // clear
/*
    memset(iFpBurgPer, 0, iMaxGenSampleCount*sizeof(double)); // clear
    memset(iFpBurgPef, 0, iMaxGenSampleCount*sizeof(double)); // clear
*/
}


TInt32 FlywheelRamper::NextSample()
{
    return(iFeedback->NextSample());
}


void FlywheelRamper::BurgsMethod(TInt16* aSamples, TUint aSamplesCount, TUint aDegree, TInt16* aOutput, TInt16* aH, TInt16* aPer, TInt16* aPef)
{
/*
    Log::Print("Fixed: ");
    for(TUint i=0; i<5; i++)
    {
        TInt32 sample = (TInt32) *(aSamples+i);
        Log::Print("%f  ", ToDouble(sample<<16, 1));
    }
    Log::Print("\n");
*/

    TUint limit1 = aSamplesCount-1;
    TUint limit2 = limit1;

    for (TUint n = 0; n < aDegree; n++)
    {
        TInt32 sn = 0;
        TInt32 sd = 0;

        for (TUint j=0; j < limit1; j++)
        {
            TInt16 t1 =  (aSamples[j+n+1] + aPef[j]);  // 1.15 + 1.15
            TInt16 t2 =  (aSamples[j] + aPer[j]);

            TInt32 t1t1 = (TInt32)t1*(TInt32)t1;  // 2.30
            TInt32 t2t2 = (TInt32)t2*(TInt32)t2;
            TInt32 t1t2 = (TInt32)t1*(TInt32)t2;

            sn -= (2*t1t2);  // 2.30
            sd += t1t1 + t2t2; // 2.30
        }

        limit1--;

        TInt16 t3 = 0;


        TInt32 sdShift = (sd>>kBurgScaleShift);

        if (sdShift==0)
        {
            Log::Print(" div by zero !!! \n");
        }


        if ( (sn!=0) && (sdShift!=0))
        {
            TInt32 ratio = sn/sdShift; // 20.12
            t3 = (TInt16) (ratio);
            //Log::Print(" sn=%08lx  sd=%08lx  (%08lx)  ratio=%08lx  t3=%04x (%f) \n", sn , sd, sdShift, ratio, t3, ToDouble(((TInt32)t3)<<16, kBurgOutputFormat) );
        }


        aOutput[n] = t3; // 4.12

        if (n > 0)  // skip the first one
        {
            for (TUint j=0; j < n; j++)
            {
                TInt32 prod = ( t3 * aOutput[n-j-1] );  // 4.12 + 4.12
                aH[j] = (TInt16)(prod>>kBurgScaleShift); // 8.24 >  4.12
                aH[j] += aOutput[j];
            }

            for (TUint j=0; j < n; j++)
            {
                aOutput[j] = aH[j];  // 4.12
            }

            limit2--;
        }


        if (n==(aDegree-1))  // exit early to avoid next loop
        {
            break;
        }


        for (TUint j = 0; j < limit2; j++)
        {
            TUint i = j+1;
            TInt32 per = aPef[j] + aSamples[i+n];  // 1.15 + 1.15
            per *= t3;  // +4.12 = 5.27
            aPer[j] += (TInt16)(per>>kBurgScaleShift); //  5.27 > 1.15

            TInt32 pef = aPer[i] + aSamples[i]; // 1.15 + 1.15
            pef *= t3; // +4.12 = 5.27
            aPef[j] = (TInt16)(pef>>kBurgScaleShift); //  5.27 > 1.15 (>>12 = >>(16-4) = >>(16-kBurgOutputFormat))
            aPef[j] += aPef[i];
        }
    }

/*
    Log::Print("(Fixed) Coeffs:");
    for(TUint i=0; i<aDegree; i++)
    {
        //Log::Print("%08x  (%f)", aOutput[i], ToDouble(((TInt32)aOutput[i])<<16, kBurgOutputFormat));
        Log::Print("%f  ", ToDouble(((TInt32)aOutput[i])<<16, kBurgOutputFormat));
    }
    Log::Print("\n");
*/
}



void FlywheelRamper::BurgsMethod(double *inputseries, TUint length, TUint degree, double *g, double *h, double *per, double *pef)
{
/*
    Log::Print("Float: ");
    for(TUint i=0; i<5; i++)
    {
        Log::Print("%f  ", *(inputseries+i));
    }
    Log::Print("\n");
*/

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
        //Log::Print("sn=%f  sd=%f  ratio=%f  t3=%f  \n", sn , sd, sn/sd, t1 );


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

/*
    //Log::Print("(Float) Coeffs:");
    for(TUint i=1; i<=degree; i++)
    {
        if (g[i]>gMax)
        {
            gMax = g[i];
            Log::Print("gMax = %f \n", gMax);
        }
        else if (g[i]<gMin)
        {
            gMin = g[i];
            Log::Print("gMin = %f \n", gMin);
        }

        //Log::Print("%f  ", g[i]);
    }
    //Log::Print("\n\n");
*/
}


void FlywheelRamper::Invert(TInt16* aData, TUint aLength)
{
    // get 2's compliment (= 1's compliment + 1)
    for(TUint i=0; i<aLength; i++)
    {
        TInt16 x = *aData; // 1's compliment
        *(aData++) = (~x)+1; // 2's compliment
    }
}

TUint FlywheelRamper::DecimationFactor(TUint /*aSampleRate*/)
{
/*
    switch(aSampleRate)
    {
        case 192000:
        case 176400:
            return(4);
        case 88200:
        case 96000:
            return(2);
        default:
            break;
    }
*/
    return(1);
}


TUint FlywheelRamper::SampleCount(TUint aSampleRate, TUint aJiffies)
{
    TUint64 sampleCount = (((TUint64)aSampleRate*((TUint64)aJiffies))/((TUint64)Jiffies::kPerSecond));
    //Log::Print("FlywheelRamper::Samples  aSampleRate=%d  aJiffies=%d  Jiffies::kPerSecond=%d  samples=%lld\n", aSampleRate, aJiffies, Jiffies::kPerSecond, samples);
    return((TUint)sampleCount);
}


void FlywheelRamper::ToInt32(double* aInput, TUint aLength, TInt32* aOutput, TUint aScale)
{
    TInt32* ptr = aOutput;

    for (TUint i=0; i<aLength; i++)
    {
        double val = *(aInput++);
        TInt32 s = ToInt32(val, aScale);
        *(ptr++) = s;
    }

}


TInt32 FlywheelRamper::ToInt32(double aVal, TUint aScale)
{
    TUint scaleFactor = (1<<(32-aScale));
    //Log::Print("BurgsMethod::ToInt32  scaleFactor=%lu \n", scaleFactor);
    TInt32 s = (TInt32) (aVal*scaleFactor); // 2^31
    return(s);
}


double FlywheelRamper::ToDouble(TInt32 aVal, TUint aScale)
{
    TUint scaleFactor = (1<<(32-aScale));
    double dbl = (double)aVal/scaleFactor;
    return(dbl);
}


void FlywheelRamper::ToDouble(const Brx& aInput, double* aOutput, TUint aScale)
{
    const TByte* ptr = aInput.Ptr();

    for (TUint i=0; i<aInput.Bytes(); i+=4)
    {
        TInt32 s = (TInt32) (*(ptr++));
        s<<=8;
        s += (TInt32) (*(ptr++));
        s<<=8;
        s += (TInt32) (*(ptr++));
        s<<=8;
        s += (TInt32) (*(ptr++));

        *aOutput = ToDouble(s, aScale);
        aOutput++;
    }
}


///////////////////////////////////////////////////////////////////////////////////////

FeedbackModel::FeedbackModel(TUint aCoeffCount, TUint aDataScaleBitCount, TUint aCoeffFormat, TUint aDataFormat, TUint aOutputFormat)
    :iCoeffs(NULL)
    ,iSamples(NULL)
    ,iStateCount(aCoeffCount)
    ,iDataScaleBitCount(aDataScaleBitCount)
    ,iScaleShiftForProduct(aCoeffFormat)
    ,iScaleShiftForOutput(aDataFormat+iDataScaleBitCount-aOutputFormat)
{
    //Log::Print("FeedbackModel  iScaleShiftForProduct=%d  iScaleShiftForOutput=%d \n", iScaleShiftForProduct, iScaleShiftForOutput);
}


void FeedbackModel::Initialise(TInt16* aCoeffs, TInt32* aSamples)
{
    iCoeffs = aCoeffs;
    iSamples = aSamples;
}


TInt32 FeedbackModel::NextSample()
{
    ASSERT(iCoeffs!=NULL);
    ASSERT(iSamples!=NULL);

    TInt32 sum = 0;
    TInt16* coeffPtr = iCoeffs;

    // iterate through the circular buff and calculate the output
    for (TUint j=0; j<iStateCount; j++)
    {
        TInt32 coeff = (((TInt32)(*(coeffPtr++)))<<16);
        TInt64 product = ((TInt64)(iSamples[j]>>iDataScaleBitCount)) * ((TInt64)coeff); // 1.31 + 4.28 = 5.59 (13.51 with >>8 data  scaling etc)
        TInt32 prod = (TInt32)(product>>32);
        sum += prod;   // 5.27
        //Log::Print("prod = %08lx   new sum = %08lx \n", prod, sum);
    }

    //Log::Print("\n");

    // update the states
    for (TUint j=(iStateCount-1); j>0; j--)
    {
        iSamples[j] = iSamples[j-1];
    }

    //Log::Print("sum = %08lx  <<%d = ", sum, iScaleShiftForProduct);

    sum <<= iScaleShiftForProduct;

    //Log::Print("%08lx  ", sum);


    iSamples[0] = sum;

    //Log::Print("<<%d = %08lx (output) \n", iScaleShiftForOutput, sum<<iScaleShiftForOutput);

    //Log::Print("feedback out = %08lx  \n", sum<<iScaleShiftForOutput);

    return(sum<<iScaleShiftForOutput);
}




/////////////////////////////////////////////////////////////////////





