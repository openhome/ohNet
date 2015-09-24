#ifndef HEADER_FLYWHEEL_RAMPER
#define HEADER_FLYWHEEL_RAMPER

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <vector>
#include <stdlib.h>

namespace OpenHome {
namespace Media {


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
    FlywheelRamper(TUint aGenJiffies, TUint aRampJiffies); // audio quantity needed to generate a ramp, ramp duration
    FlywheelRamper(TUint aDegree, TUint aGenJiffies, TUint aRampJiffies); // filter degree/order, audio quantity needed to generate a ramp, ramp duration
    ~FlywheelRamper();

    IPcmProcessor& Ramp(IWriter& aWriter, TUint aSampleRate);
    TUint GenJiffies() const;
    TUint RampJiffies() const;

    static TUint Samples(TUint aSampleRate, TUint aJiffies);
    static TInt32 Int32(const Brx& aSamples, TUint aIndex=0);
    static void Invert(std::vector<TInt32>& aInput, std::vector<TInt32>& aOutput);
    static void Reverse(std::vector<TInt32>& aInput, std::vector<TInt32>& aOutput);
    static void Reverse(const Brx& aInput, Bwx& aReversed);

    static void LogBuf(const Brx& aBuf);
    static void Log32(std::vector<TInt32>& aVals);
    static void Log32(const Brx& aBuf);
    static void LogDouble(std::vector<double>& aVals);
    static void LogDouble(std::vector<TInt32>& aVals, TUint aScale);
    static void LogDouble(const Brx& aBuf, TUint aScale);


private:
    void CreateRamp(const Brx& aSamples);

private:
    TUint iGenJiffies;
    TUint iRampJiffies;
    TUint iDegree;
    Bwh iRampSamples;
    IPcmProcessor* iProcessor;
    IWriter* iWriter;
    TUint iSampleRate;
};


///////////////////////////////////////////////////////////////////////////////////////////
//
// PcmProcessorFwr : Used to feed audio to FlywheelRamper object
//
// Audio can be passed in one complete block or multiple fragments/samples
// Begin block must be called once before any audio is passed
// End block must be called once when complete audio block has been passed
//
// Prior to feeding entire audio block to FlywheelRamper...
// 8 bit audio samples are converted to 32bit (by padding lower 24bits with 0 or 0xffffff)
// 16 bit audio samples are converted to 32bit (by padding lower 16bits with 0 or 0xffff)
// 24 bit audio samples are converted to 32bit (by padding lower 8bits with 0 or 0xff)
///////////////////////////////////////////////////////////////////////////////////////////

class PcmProcessorFwr : public IPcmProcessor
{
public:
    PcmProcessorFwr(FlywheelRamper& aFwr, TUint aGenerationJiffies);

    // IPcmProcessor
    virtual void BeginBlock();
    virtual TBool ProcessFragment8(const Brx& aData, TUint aNumChannels);
    virtual TBool ProcessFragment16(const Brx& aData, TUint aNumChannels);
    virtual TBool ProcessFragment24(const Brx& aData, TUint aNumChannels);
    virtual void ProcessSample8(const TByte* aSample, TUint aNumChannels);
    virtual void ProcessSample16(const TByte* aSample, TUint aNumChannels);
    virtual void ProcessSample24(const TByte* aSample, TUint aNumChannels);
    virtual void EndBlock();

private:
    FlywheelRamper& iFwr;
    Bwh iSamples;
    TUint iNumChannels;
};


////////////////////////////////////////////////////////////////////////////
//
// ConvolutionModel:
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
// Max count = no. of samples in input block + no. of coeffs - 1
//
// The value of each sample in output block is calculated by:
//
// sampleOut n = coeff(1)*sampleIn(n) + coeff(2)*sampleIn(n-1) + coeff(3)*sampleIn(n-2)...
//
// for n=1 to x (where x= num samples in + num coeffs -1):
/*
class ConvolutionModel : public INonCopyable
{
public:
    ConvolutionModel(const std::vector<TInt32>& aCoeffs, TUint aCoeffFormat, TUint aDataFormat, TUint aOutputFormat);

    void Process(const Brx& aSamplesIn, Bwx& aSamplesOut, TUint aCount, TBool aReverseSamplesIn = false);

private:
    const std::vector<TInt32> iCoeffs;
    std::vector<TInt32> iSamples;
    TUint iCoeffFormat;
    TUint iDataFormat;
    TUint iOutputFormat;
    TUint iDataScaleBitCount;
};
*/
//////////////////////////////////////////////////////////////////////////

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
    FeedbackModel(const std::vector<TInt32>& aCoeffs, TUint aDataScaleBitCount, TUint aCoeffFormat, TUint aDataFormat, TUint aOutputFormat);

    void Process(const Brx& aSamplesIn, Bwx& aSamplesOut, TUint aCount);
    void Process(const Brx& aSamplesIn, Bwx& aSamplesOut);

private:
    std::vector<TInt32> iCoeffs;
    TUint iStateCount;
    std::vector<TInt32> iSamples;
    TUint iDataScaleBitCount;
    TUint iScaleShiftForSum;
    TUint iScaleShiftForProduct;
    TInt iScaleShiftForOutput;
};

////////////////////////////////////////////////////////////////////////////

class BurgsMethod
{
public:
    static void Coeffs(TUint aDegree, const Brx& aSamplesIn, std::vector<TInt32>& aCoeffsOut, TBool aFloatingPoint = false);
    static void ARMaxEntropy (double* aInputseries, TUint aLength, TUint aDegree, double* aOutput, double* aH, double* aPer, double* aPef);
    static void ARMaxEntropy(TInt32* aInputseries, TUint aLength, TUint aDegree, TInt32* aG, TInt32* aH, TInt32* aPer, TInt32* aPef);

    static void ToInt32(double* aInput, TUint aLength, std::vector<TInt32>& aOutput, TUint aScale);
    static TInt32 ToInt32(double aVal, TUint Scale);

    static void ToDouble(const Brx& aSamplesIn, double* aOutput, TUint aScale);
    static double ToDouble(TInt32 aVal, TUint aScale);
    static double ToDouble(TInt64 aVal, TUint aScale);

};


} // Media
} // OpenHome


#endif // HEADER_FLYWHEEL_RAMPER
