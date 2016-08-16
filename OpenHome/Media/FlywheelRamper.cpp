#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/FlywheelRamper.h>
#include <OpenHome/Private/Debug.h>

using namespace OpenHome;
using namespace OpenHome::Media;
using namespace std;

static const TUint kBurgDataDescaleBitCount = 1;
static const TUint kBurgOutputFormat = 3;
static const TUint kBurgScaleShift = 16-kBurgOutputFormat;
static const TUint kDegree = 3;

static const TUint kFeedbackDataDescaleBitCount = 0;
static const TUint kFeedbackDataFormat = 1;

static const TUint kMaxChannelCount = 10;
static const TUint kMaxSampleRate = 192000;

const TUint FlywheelRamperManager::kMaxOutputJiffiesBlockSize = Jiffies::kPerMs; // 1ms

////////////////////////////////////////////////////////////////////////////////////////////

FlywheelRamperManager::FlywheelRamperManager(IPcmProcessor& aOutput, TUint aInputJiffies, TUint aOutputJiffies)
    :iOutput(aOutput)
    ,iOutBuf(FlywheelRamper::SampleCount(kMaxSampleRate, kMaxOutputJiffiesBlockSize)*kMaxChannelCount*4)
    ,iOutputJiffies(aOutputJiffies)
{
    for(TUint i=0; i<kMaxChannelCount; i++)
    {
        iRampers.push_back(new FlywheelRamper(kDegree, aInputJiffies));
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
    InitChannels(aSamples, aSampleRate, aChannelCount); // prepare the ramp generation

    TUint decFactor = FlywheelRamper::DecimationFactor(aSampleRate);
    TUint maxOutputSamplesBlockSize = FlywheelRamper::SampleCount(aSampleRate, kMaxOutputJiffiesBlockSize);
    TUint remainingSamples = FlywheelRamper::SampleCount(aSampleRate, iOutputJiffies);

    while (remainingSamples > 0)
    {
        TUint outputSamples = remainingSamples;
        if (remainingSamples>maxOutputSamplesBlockSize)
        {
            outputSamples = maxOutputSamplesBlockSize; // 1ms blocks
        }

        remainingSamples -= outputSamples;
        RenderChannels(outputSamples, decFactor, aChannelCount); // output ramp audio data
    }

    Reset(); // clear memory ready for next ramp request
}

void FlywheelRamperManager::InitChannels(const Brx& aSamples, TUint aSampleRate, TUint aChannelCount)
{
    const TByte* ptr = aSamples.Ptr();
    TUint bytesPerChan = aSamples.Bytes()/aChannelCount;

    // initialise the rampers for each channel
    for(TUint i=0; i<aChannelCount; i++)
    {
        Brn chanSamples(ptr, bytesPerChan);
        iRampers[i]->Initialise(chanSamples, aSampleRate);
        ptr += bytesPerChan;
    }
}

void FlywheelRamperManager::RenderChannels(TUint aSampleCount, TUint aDecFactor, TUint aChannelCount)
{
    TByte* ptr = (TByte*)iOutBuf.Ptr();
    TUint outputBytes = 0;
    TUint sampleHoldCount = 0;

    TInt32 prevSample[kMaxChannelCount];

    for(TUint j=0; j<aSampleCount; j++)
    {
        for(TUint k=0; k<aChannelCount; k++)
        {
            TInt32 sample;
            if (sampleHoldCount==0)
            {
                sample = iRampers[k]->NextSample();
                prevSample[k] = sample;
            }
            else
            {
                sample = prevSample[k];
            }

            // write out in big endian format
            *(ptr+3) = (TByte)sample;
            sample >>= 8;
            *(ptr+2) = (TByte)sample;
            sample >>= 8;
            *(ptr+1) = (TByte)sample;
            sample >>= 8;
            *(ptr) = (TByte)sample;

            ptr += 4;
            outputBytes += 4;
        }

        if (++sampleHoldCount == aDecFactor)
        {
            sampleHoldCount = 0;
        }
    }

    iOutBuf.SetBytes(outputBytes);
    iOutput.BeginBlock();
    iOutput.ProcessFragment32(iOutBuf, aChannelCount);
    iOutput.EndBlock();

}

void FlywheelRamperManager::Reset()
{
    for(TUint i=0; i<kMaxChannelCount; i++)
    {
        iRampers[i]->Reset(); // clears memory ready for next ramp request
    }
}

////////////////////////////////////////////////////////////////////////////////////////////

FlywheelRamper::FlywheelRamper(TUint aDegree, TUint aInputJiffies)
    :iDegree(aDegree)
    ,iInputJiffies(aInputJiffies)
    ,iFeedback(new FeedbackModel(iDegree, kFeedbackDataDescaleBitCount, kBurgOutputFormat, kFeedbackDataFormat, 1))
    ,iMaxInputSampleCount(SampleCount(kMaxSampleRate, iInputJiffies))
{
    iInputSamples = (TInt16*) calloc (iMaxInputSampleCount, sizeof(TInt16));
    iBurgPer = (TInt16*) calloc (iMaxInputSampleCount, sizeof(TInt16));
    iBurgPef = (TInt16*) calloc (iMaxInputSampleCount, sizeof(TInt16));
    iBurgCoeffs = (TInt16*) calloc (iDegree, sizeof(TInt16));
    iBurgH = (TInt16*) calloc (iDegree, sizeof(TInt16));

    iFeedbackSamples = (TInt32*) calloc (iDegree, sizeof(TInt32));
    iFeedbackCoeffs = (TInt32*) calloc (iDegree, sizeof(TInt32));
}

FlywheelRamper::~FlywheelRamper()
{
    free(iInputSamples);
    free(iBurgCoeffs);
    free(iBurgH);
    free(iBurgPer);
    free(iBurgPef);
    free(iFeedbackSamples);
    free(iFeedbackCoeffs);
    delete iFeedback;
}

TUint FlywheelRamper::InputJiffies() const
{
    return(iInputJiffies);
}

void FlywheelRamper::Initialise(const Brx& aSamples, TUint aSampleRate)
{
    ASSERT(aSampleRate<=kMaxSampleRate);
    ASSERT(aSamples.Bytes()==(SampleCount(aSampleRate, iInputJiffies)*kBytesPerSample));

    // copy input samples out of buffer into memory
    TUint decFactor = DecimationFactor(aSampleRate);
    TInt16* inputSamplesPtr = iInputSamples;
    const TByte* bufPtr = aSamples.Ptr();

    TUint sampleCount = aSamples.Bytes()/(kBytesPerSample*decFactor);
    TUint ptrInc = 4*decFactor;

    for(TUint i=0; i<sampleCount; i++)
    {
        TUint32 sample = (TUint32) (*(bufPtr));
        sample <<= 8;
        sample += (TUint32) (*(bufPtr+1));

        TInt16 sample16 = (TInt16)sample;

        sample <<= 8;
        sample += (TUint32) (*(bufPtr+2));
        sample <<= 8;
        sample += (TUint32) (*(bufPtr+3));

        bufPtr += ptrInc;

        if (i>=(sampleCount-iDegree))
        {
            // put the initial states into feedback buffer (in reverse order)
            iFeedbackSamples[sampleCount-i-1] = sample;
        }

        *(inputSamplesPtr++) = sample16>>kBurgDataDescaleBitCount;
    }

    BurgsMethod(iInputSamples, sampleCount, iDegree, iBurgCoeffs, iBurgH, iBurgPer, iBurgPef);

    CorrectBurgCoeffs(); // remove overflow
    PrepareFeedbackCoeffs(); // upcast and invert

    iFeedback->Initialise(iFeedbackCoeffs, iFeedbackSamples);
}

void FlywheelRamper::PrepareFeedbackCoeffs()
{
    for(TUint i=0; i<iDegree; i++)
    {
        // invert and upcast to 32 bit
        iFeedbackCoeffs[i] = -(((TInt32)iBurgCoeffs[i])<<16);
    }
}

void FlywheelRamper::Reset()
{
    memset(iBurgPer, 0, iMaxInputSampleCount*sizeof(TInt16)); // clear
    memset(iBurgPef, 0, iMaxInputSampleCount*sizeof(TInt16)); // clear
}

TInt32 FlywheelRamper::NextSample()
{
    return(iFeedback->NextSample());
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
            TInt16 t1 =  (aSamples[j+n+1] + aPef[j]);
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
            TInt64 ratio = (((TInt64)sn)<<kBurgScaleShift)/(TInt64)sd;
            t3 = (TInt16) (ratio);
        }

        aOutput[n] = t3;

        if (n > 0)  // skip the first one
        {
            for (TUint j=0; j < n; j++)
            {
                TInt32 prod = ( t3 * aOutput[n-j-1] );
                aH[j] = (TInt16)(prod>>kBurgScaleShift);
                aH[j] += aOutput[j];
            }

            for (TUint j=0; j < n; j++)
            {
                aOutput[j] = aH[j];
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
            TInt32 per = aPef[j] + aSamples[i+n];
            per *= t3;
            aPer[j] += (TInt16)(per>>kBurgScaleShift);

            TInt32 pef = aPer[i] + aSamples[i];
            pef *= t3;
            aPef[j] = (TInt16)(pef>>kBurgScaleShift);
            aPef[j] += aPef[i];
        }
    }
}

TUint FlywheelRamper::DecimationFactor(TUint aSampleRate)
{
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

    return(1);
}

void FlywheelRamper::CorrectBurgCoeffs()
{
    TInt16 coeffExcess = CoeffOverflow(iBurgCoeffs, iDegree, kBurgOutputFormat);
    if (coeffExcess!=0)
    {
        iBurgCoeffs[0] -= (coeffExcess*2);
    }
}

TInt16 FlywheelRamper::CoeffOverflow(TInt16* aCoeffs, TUint aCoeffCount, TUint aFormat)
{
    const TInt16 kOne = (1<<(16-aFormat));
    TInt16 coeffTotal = 0;

    for (TUint j=0; j<aCoeffCount; j++)
    {
        coeffTotal += aCoeffs[j];
    }

    if ( (coeffTotal<=kOne) && (coeffTotal>=(-kOne)) )
    {
        return(0);
    }

    TInt16 excess = 0;

    // find how much beyond the range the total is
    if (coeffTotal&0x8000)
    {
        // total < 0
        excess = coeffTotal + kOne;
    }
    else
    {
        // total > 0
        excess = coeffTotal - kOne;
    }

    return(excess);
}

TUint FlywheelRamper::SampleCount(TUint aSampleRate, TUint aJiffies)
{
    TUint64 sampleCount = (((TUint64)aSampleRate) * aJiffies) / Jiffies::kPerSecond;
    return (TUint)sampleCount;
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

FeedbackModel::FeedbackModel(TUint aStateCount, TUint aDataDescaleBitCount, TUint aCoeffFormat, TUint aDataFormat, TUint aOutputFormat)
    :iCoeffs(NULL)
    ,iSamples(NULL)
    ,iStateCount(aStateCount)
    ,iDataDescaleBitCount(aDataDescaleBitCount)
    ,iCoeffFormat(aCoeffFormat)
    ,iScaleShiftForOutput(aDataFormat+aDataDescaleBitCount-aOutputFormat)
{
    //Log::Print("FeedbackModel  iScaleShiftForProduct=%d  iScaleShiftForOutput=%d \n", iScaleShiftForProduct, iScaleShiftForOutput);
}

void FeedbackModel::Initialise(TInt32* aCoeffs, TInt32* aSamples)
{
    iCoeffs = aCoeffs;
    iSamples = aSamples;

    for (TUint j=0; j<iStateCount; j++)
    {
        iSamples[j] >>= iDataDescaleBitCount;
    }
}

TInt32 FeedbackModel::NextSample()
{
    ASSERT(iCoeffs!=NULL);
    ASSERT(iSamples!=NULL);

    TInt32 sum = 0;
    const TInt32* coeffPtr = iCoeffs;

    // iterate through the circular buff and calculate the output
    for (TUint j=0; j<iStateCount; j++)
    {
        TInt32 coeff = (*(coeffPtr++));
        TInt32 sample = iSamples[j];;

        TInt64 product = ((TInt64)sample) * ((TInt64)coeff); // 1.31 + 4.28 = 5.59 (13.51 with >>8 data  scaling etc)

        TInt32 prod = (TInt32)(product>>32);
        sum += prod;   // 5.27
    }


    // update the states
    for (TUint j=(iStateCount-1); j>0; j--)
    {
        iSamples[j] = iSamples[j-1];
    }


    sum <<= iCoeffFormat;
    iSamples[0] = sum;

    if (iScaleShiftForOutput<0)
    {
        sum >>= (-iScaleShiftForOutput);
    }
    else
    {
        sum <<= iScaleShiftForOutput;
    }

    return(sum);
}

/////////////////////////////////////////////////////////////////////
