#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/OsWrapper.h>

#include <vector>
#include <stdlib.h>

namespace OpenHome {
namespace Media {

namespace TestFlywheelRamper {
    class SuiteFlywheelRamper;
}

class FeedbackModel;

///////////////////////////////////////////////////////////////////////////////////////////
//
// FlywheelRamper: uses an algorthim to generate ramp audio aRampMs long.
//
// Needs to be initialised with a block of audio before NextSample can be called
// Audio block must be exactly aGenJiffies long (rounded down to nearest integer number of samples).
//
// Next sample returns one 32 bit sample and can be called an infinite number of times
//
// Generation (input) audio is assumed to be 32bit/big endian
// Ramp (output) audio is written out in 32bit/big endian
///////////////////////////////////////////////////////////////////////////////////////////

class FlywheelRamper : public INonCopyable
{
    friend class FlywheelRamperManager;
    friend class TestFlywheelRamper::SuiteFlywheelRamper;
public:
    static const TUint kBytesPerSample = 4; // 32 bit audio
private:
    FlywheelRamper(TUint aDegree, TUint aInputJiffies); // generation(input) audio length
    ~FlywheelRamper();
    void Initialise(const Brx& aSamples, TUint aSampleRate);
    TUint InputJiffies() const;
    TInt32 NextSample();
    void Reset();
public:
    static void BurgsMethod(TInt16* aSamples, TUint aSamplesCount, TUint aDegree, TInt16* aOutput, TInt16* aH, TInt16* aPer, TInt16* aPef);
    static TUint SampleCount(TUint aSampleRate, TUint aJiffies);
    static TUint DecimationFactor(TUint aSampleRate);
    static TInt16 CoeffOverflow(TInt16* aCoeffs, TUint aCoeffCount, TUint aFormat);
    static void ToInt32(double* aInput, TUint aLength, TInt32* aOutput, TUint aScale);
    static TInt32 ToInt32(double aVal, TUint aScale);
    static double ToDouble(TInt32 aVal, TUint aScale);
    static void ToDouble(const Brx& aInput, double* aOutput, TUint aScale);
private:
    void PrepareFeedbackCoeffs();
    void CorrectBurgCoeffs();
private:
    TUint iDegree;
    TUint iInputJiffies;
    FeedbackModel* iFeedback;

    TInt16* iInputSamples;
    TInt16* iBurgCoeffs;
    TInt16* iBurgH;
    TInt16* iBurgPer;
    TInt16* iBurgPef;

    TUint iMaxInputSampleCount;
    TInt32* iFeedbackSamples;
    TInt32* iFeedbackCoeffs;
};


///////////////////////////////////////////////////////////////////////////////////////////


class FlywheelRamperManager : public INonCopyable
{
    friend class TestFlywheelRamper::SuiteFlywheelRamper;
public:
    static const TUint kMaxOutputJiffiesBlockSize;
public:
    FlywheelRamperManager(IPcmProcessor& aOutput, TUint aInputJiffies, TUint aOutputJiffies);
    ~FlywheelRamperManager();
    void Ramp(const Brx& aSamples, TUint aSampleRate, TUint aChannelCount);
private:
    void InitChannels(const Brx& aSamples, TUint aSampleRate, TUint aChannelCount);
    void RenderChannels(TUint aSampleCount, TUint aDecFactor, TUint aChannelCount);
    void Reset();
private:
    IPcmProcessor& iOutput;
    Bwh iOutBuf;
    TUint iOutputJiffies;
    std::vector<FlywheelRamper*> iRampers;
};


////////////////////////////////////////////////////////////////////////////
//
// FeedbackModel:
//
// Constructed with a state count, a data descale bit count and format specifiers
// for coefficients, input data and output data.
// Format specifiers indicate the bit width of the integer portion of the
// associated fractional fixed point notation data entities
// (a value of 1 indicates a format of 1.31, 2 indicates a format of 2.30)
//
// Needs to be initialised with ptrs to a collection of coeffs and a samples(init states)
// Both collections are assumed to be of length specified by aStateCount
//
// Once initialised, NextSample can be called  an infinite number of times
// Next sample returns one 32 bit sample calculated by:
//
// sampleOut(0) = coeff(0)*sampleIn(0) + coeff(1)*sampleIn(1) + coeff(2)*sampleIn(2)...
// sampleOut(1) = coeff(0)*sampleOut(0) + coeff(1)*sampleIn(0) + coeff(2)*sampleIn(1)...
// sampleOut(2) = coeff(0)*sampleOut(1) + coeff(1)*sampleOut(0) + coeff(2)*sampleIn(0)...
//
// sampleOut(n) = coeff(0)*sampleOut(n-1) + coeff(1)*sampleOut(n-2)...
//

class FeedbackModel : public INonCopyable
{
public:
    FeedbackModel(TUint aStateCount, TUint aDataDescaleBitCount, TUint aCoeffFormat, TUint aDataFormat, TUint aOutputFormat);
    void Initialise(TInt32* aCoeffs, TInt32* aSamples);
    TInt32 NextSample();
private:
    TInt32* iCoeffs;
    TInt32* iSamples;
    TUint iStateCount;
    TUint iDataDescaleBitCount;
    TUint iCoeffFormat;
    TInt iScaleShiftForOutput;
};

} // Media
} // OpenHome
