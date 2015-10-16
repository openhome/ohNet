#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <vector>
#include <stdlib.h>
#include <OpenHome/OsWrapper.h>


namespace OpenHome {
namespace Media {

class FeedbackModel;

///////////////////////////////////////////////////////////////////////////////////////////
//
// FlywheelRamper: uses an algorthim to generate ramp audio aRampMs long.
//
// Needs to be fed a block of audio to allow it to generate ramp.
// Generation audio block must be exactly aGenerationJiffies long (rounded down to nearest integer number of samples)
// Client supplies generation audio via IPcmProcessor object returned via Ramp method.
// Ramp audio is written to IWriter specified in Ramp method
//
// Generation audio is assumed to be 32bit in big endian format
// Ramp audio is 32bit and written out in big endian format
///////////////////////////////////////////////////////////////////////////////////////////

class FlywheelRamper
{
    friend class PcmProcessorFwr;

public:
    static const TUint kBytesPerSample = 4; // 32 bit audio

public:
    FlywheelRamper(OpenHome::Environment& aEnv, IPcmProcessor& aOutput, TUint aGenJiffies); // generation(input) audio length
    ~FlywheelRamper();

    void Initialise(const Brx& aSamples, TUint aSampleRate);
    TUint GenJiffies() const;
    void Cycle(TUint aCount = 1);
    void Reset();

    static void BurgsMethod(TInt16* aSamples, TUint aSamplesInCount, TUint aDegree, TInt16* aOutput, TInt16* aH, TInt16* aPer, TInt16* aPef);

    static TUint SampleCount(TUint aSampleRate, TUint aJiffies);
    static void Invert(TInt16* aData, TUint aLength);

private:
    OpenHome::Environment& iEnv;
    TUint iGenJiffies;
    TUint iDegree;
    FeedbackModel* iFeedback;
    IPcmProcessor* iProcessor;

    TInt16* iGenSamples;
    TInt16* iBurgCoeffs;
    TInt16* iBurgH;
    TInt16* iBurgPer;
    TInt16* iBurgPef;
    TUint iMaxGenSampleCount;

    IWriter* iWriter;
};


///////////////////////////////////////////////////////////////////////////////////////////

class FlywheelRamperManager
{
public:
    FlywheelRamperManager(OpenHome::Environment& aEnv, IPcmProcessor& aOutput, TUint aChannelCount, TUint aGenJiffies, TUint aRampJiffies);
    void Ramp(const Brx& aSamples, TUint aSampleRate);

private:
    void Reset();

private:
    OpenHome::Environment& iEnv;
    IPcmProcessor& iOutput;
    TUint iChannelCount;
    TUint iRampJiffies;
    std::vector<FlywheelRamper*> iRampers;
};


////////////////////////////////////////////////////////////////////////////
//
// FeedbackModel:
//
// Constructed with a list of 32 bit coefficients, and format specifiers
// for coefficients, input data and output data.
// Format specifiers indicate the bit width of the integer portion of the
// associated fractional fixed point notation data enties
// (a value of 1 indicates a format of 1.31, 2 indicates a format of 2.30)
//
// Process method takes in a block of 32 bit samples, and a count and
// returns a new block of 32 bit samples.
// Count determines the number of samples in the returned output data block.
//
// Max count = no. of samples in input block + no. of coeffs
//
// The value of each sample in output block is calculated by:
//
// sampleOut n = sampleIn(n) + coeff(1)*sampleIn(n-1) + coeff(2)*sampleIn(n-2)...
//

class FeedbackModel : public INonCopyable
{
public:
    FeedbackModel(IPcmProcessor& aOutput, TUint aCoeffCount, TUint aDataScaleBitCount, TUint aCoeffFormat, TUint aDataFormat, TUint aOutputFormat);
    void Initialise(TInt16* aCoeffs, const Brx& aSamples);

    void Cycle(TUint aCount = 1);

private:
    IPcmProcessor& iOutput;
    TInt16* iCoeffs;
    TUint iStateCount;
    std::vector<TInt32> iSamples;
    TUint iDataScaleBitCount;
    TUint iScaleShiftForSum;
    TUint iScaleShiftForProduct;
    TInt iScaleShiftForOutput;
};


////////////////////////////////////////////////////////////////////////////


} // Media
} // OpenHome


