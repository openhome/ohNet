#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/FlywheelRamper.h>
#include <OpenHome/Private/Debug.h>

using namespace OpenHome;
using namespace OpenHome::Media;
using namespace std;


static const TUint kDegree = 3;

double gMax = 0;
double gMin = 0;


const TUint kMaxSampleRate = 192000;


////////////////////////////////////////////////////////////////////////////////////////////


FlywheelRamperManager::FlywheelRamperManager(OpenHome::Environment& aEnv, IPcmProcessor& aOutput, TUint aChannelCount, TUint aGenJiffies, TUint aRampJiffies)
    :iEnv(aEnv)
    ,iOutput(aOutput)
    ,iChannelCount(aChannelCount)
    ,iOutBuf(FlywheelRamper::SampleCount(kMaxSampleRate, aRampJiffies)*aChannelCount*4)
    ,iRampJiffies(aRampJiffies)
{
    //Log::Print("iOutBuf.MaxBytes() = %d \n", iOutBuf.MaxBytes());
    for(TUint i=0; i<iChannelCount; i++)
    {
        iRampers.push_back(new FlywheelRamper(iEnv, aGenJiffies));
    }
}


FlywheelRamperManager::~FlywheelRamperManager()
{
    for(TUint i=0; i<iChannelCount; i++)
    {
        delete iRampers[i];
    }
}

void FlywheelRamperManager::Ramp(const Brx& aSamples, TUint aSampleRate)
{
    TUint startTime = Os::TimeInMs(iEnv.OsCtx());

    //for (TUint j=0; j<1000; j++)  // scale up for profiling
    {
        const TByte* ptr = aSamples.Ptr();
        TUint bytesPerChan = aSamples.Bytes()/iChannelCount;

        // initialise all the rampers
        for(TUint i=0; i<iChannelCount; i++)
        {
            iRampers[i]->Initialise(Brn(ptr, bytesPerChan), aSampleRate);
            ptr += bytesPerChan;
        }
    }

    TUint rampSamplesPerChan = FlywheelRamper::SampleCount(aSampleRate, iRampJiffies);
    //Log::Print("rampSamplesPerChan = %d \n", rampSamplesPerChan);

    TUint endPrepTime = Os::TimeInMs(iEnv.OsCtx());

    TByte* ptr = (TByte*)iOutBuf.Ptr();
    TUint outputBytes = 0;


    //for (TUint i=0; i<1000; i++)  // scale up for profiling
    {
        //outputBytes = 0;
        //ptr = (TByte*)iOutBuf.Ptr();

        for(TUint j=0; j<rampSamplesPerChan; j++)
        {
            for(TUint k=0; k<iChannelCount; k++)
            {
                //Log::Print("outputBytes = %d ", outputBytes);
                TInt32 sample = iRampers[k]->Cycle();

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
        }
    }

    iOutBuf.SetBytes(outputBytes);
    iOutput.BeginBlock();
    iOutput.ProcessFragment32(iOutBuf, iChannelCount);
    iOutput.EndBlock();

    TUint endGenTime = Os::TimeInMs(iEnv.OsCtx());

    Log::Print("FWRMan prep time = %dms   sample pull time = %dms \n", endPrepTime-startTime, endGenTime-endPrepTime);

    Reset(); // clears memory ready for next ramp request
}


void FlywheelRamperManager::Reset()
{
    for(TUint i=0; i<iChannelCount; i++)
    {
        iRampers[i]->Reset(); // clears memory ready for next ramp request
    }
}



////////////////////////////////////////////////////////////////////////////////////////////

FlywheelRamper::FlywheelRamper(OpenHome::Environment& aEnv, TUint aGenJiffies)
    :iEnv(aEnv)
    ,iGenJiffies(aGenJiffies)
    ,iDegree(kDegree)
    ,iFeedback(new FeedbackModel(iDegree, 0, 4, 1, 1))
    ,iMaxGenSampleCount(SampleCount(kMaxSampleRate, iGenJiffies))
{
    iGenSamples = (TInt16*) calloc (iMaxGenSampleCount, sizeof(TInt16));
    iBurgPer = (TInt16*) calloc (iMaxGenSampleCount, sizeof(TInt16));
    iBurgPef = (TInt16*) calloc (iMaxGenSampleCount, sizeof(TInt16));
    iBurgCoeffs = (TInt16*) calloc (iDegree, sizeof(TInt16));
    iBurgH = (TInt16*) calloc (iDegree, sizeof(TInt16));
}


FlywheelRamper::~FlywheelRamper()
{
    free(iGenSamples);
    free(iBurgCoeffs);
    free(iBurgH);
    free(iBurgPer);
    free(iBurgPef);
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

    // copy input samples out of buffer into memory
    TInt16* ipPtr = iGenSamples;
    const TByte* bufPtr = aSamples.Ptr();
    for(TUint i=0; i<aSamples.Bytes(); i+=kBytesPerSample)
    {
        TInt16 sample = (TInt16) (*(bufPtr++));
        sample <<= 8;
        sample += (TInt16) (*bufPtr);
        bufPtr += 3;
        *(ipPtr++) = sample;
    }

    BurgsMethod(iGenSamples, aSamples.Bytes()/kBytesPerSample, iDegree, iBurgCoeffs, iBurgH, iBurgPer, iBurgPef);

    // Invert the coeffs
    Invert(iBurgCoeffs, iDegree);

    TUint feedbackSampleByteCount = iDegree*kBytesPerSample;

    iFeedback->Initialise(iBurgCoeffs, aSamples.Split(aSamples.Bytes()-feedbackSampleByteCount));
}


void FlywheelRamper::Reset()
{
    memset(iBurgPer, 0, iMaxGenSampleCount*sizeof(TInt16)); // clear
    memset(iBurgPef, 0, iMaxGenSampleCount*sizeof(TInt16)); // clear
}


TInt32 FlywheelRamper::Cycle()
{
    return(iFeedback->Cycle());
}


void FlywheelRamper::BurgsMethod(TInt16* aSamples, TUint aSamplesCount, TUint aDegree, TInt16* aOutput, TInt16* aH, TInt16* aPer, TInt16* aPef)
{
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

            TInt32 t1t1 = (TInt32)t1*(TInt32)t1;
            TInt32 t2t2 = (TInt32)t2*(TInt32)t2;
            TInt32 t1t2 = (TInt32)t1*(TInt32)t2;

            sn -= (2*t1t2);  // 2.30
            sd += t1t1 + t2t2; // 2.30
        }

        limit1--;

        TInt16 t3 = 0;
        if (sn!=0)
        {
            t3 = (TInt16)((sn)/(sd>>12)&0x0000ffff);  // 4.12
        }


        aOutput[n] = t3; // 4.12

        if (n > 0)  // skip the first one
        {
            for (TUint j=0; j < n; j++)
            {
                TInt32 prod = ( t3 * aOutput[n-j-1] );  // 4.12 + 4.12
                aH[j] = (TInt16)(prod>>12); // 8.24 >  4.12
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
            aPer[j] += (TInt16)(per>>12); //  17.27 > 1.15

            TInt32 pef = aPer[i] + aSamples[i];
            pef *= t3;
            aPef[j] = (TInt16)(pef>>12); //  17.27 > 1.15
            aPef[j] += aPef[i];
        }
    }
}


void FlywheelRamper::Invert(TInt16* aData, TUint aLength)
{
    // get 2's compliment (= 1's compliment + 1)
    for(TUint i=0; i<aLength; i++)
    {
        TInt16 x = ((*aData)^0xffffL); // 1's compliment
        *(aData++) = x+1; // 2's compliment
    }
}


TUint FlywheelRamper::SampleCount(TUint aSampleRate, TUint aJiffies)
{
    TUint64 sampleCount = (((TUint64)aSampleRate*((TUint64)aJiffies))/((TUint64)Jiffies::kPerSecond));
    //Log::Print("FlywheelRamper::Samples  aSampleRate=%d  aJiffies=%d  Jiffies::kPerSecond=%d  samples=%lld\n", aSampleRate, aJiffies, Jiffies::kPerSecond, samples);
    return((TUint)sampleCount);
}

///////////////////////////////////////////////////////////////////////////////////////

FeedbackModel::FeedbackModel(TUint aCoeffCount, TUint aDataScaleBitCount, TUint aCoeffFormat, TUint aDataFormat, TUint aOutputFormat)
    :iCoeffs(NULL)
    ,iStateCount(aCoeffCount)
    ,iSamples(aCoeffCount, 0)
    ,iDataScaleBitCount(aDataScaleBitCount)
    ,iScaleShiftForProduct(aCoeffFormat)
    ,iScaleShiftForOutput(aDataFormat+iDataScaleBitCount-aOutputFormat)
{
    //Log::Print("FeedbackModel  iScaleShiftForProduct=%d  iScaleShiftForOutput=%d \n", iScaleShiftForProduct, iScaleShiftForOutput);
}

void FeedbackModel::Initialise(TInt16* aCoeffs, const Brx& aSamples)
{
    ASSERT((aSamples.Bytes()/4) == iStateCount);

    iCoeffs = aCoeffs;

    // put the initial states into buffer (in reverse order)
    const TByte* ptr = aSamples.Ptr();
    TUint index = iStateCount-1;

    for(TUint i=0; i<iStateCount; i++)
    {
        TInt32 sample = (TInt32) *(ptr++);
        sample <<= 8;
        sample += (TInt32) *(ptr++);
        sample <<= 8;
        sample += (TInt32) *(ptr++);
        sample <<= 8;
        sample += (TInt32) *(ptr++);
        iSamples[index--] = (sample>>iDataScaleBitCount);
    }
}


TInt32 FeedbackModel::Cycle()
{
    ASSERT(iCoeffs!=NULL);

    TInt32 sum = 0;
    TInt16* coeffPtr = iCoeffs;

    // iterate through the circular buff and calculate the output
    for (TUint j=0; j<iStateCount; j++)
    {
        TInt32 coeff = (((TInt32)(*(coeffPtr++)))<<16);
        TInt64 product = ((TInt64)iSamples[j]) * ((TInt64)coeff); // 1.31 + 4.28 = 5.59 (10.54 with >>8 data  scaling etc)
        sum += (TInt32)(product>>32);   // 5.27
    }

    // update the states
    for (TUint j=(iStateCount-1); j>0; j--)
    {
        iSamples[j] = iSamples[j-1];
    }

    sum <<= iScaleShiftForProduct;

    iSamples[0] = sum;

    return(sum<<iScaleShiftForOutput);
}


