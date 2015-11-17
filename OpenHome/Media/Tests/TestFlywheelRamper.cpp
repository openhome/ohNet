#include <OpenHome/Types.h>
#include <OpenHome/OsWrapper.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/SuiteUnitTest.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/FlywheelRamper.h>
#include <OpenHome/Private/File.h>

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Media;


namespace OpenHome {
namespace Media {
namespace TestFlywheelRamper {


/////////////////////////////////////////////

class PcmProcessorFeedback;

class SuiteFlywheelRamper : public SuiteUnitTest, public INonCopyable
{
public:
    SuiteFlywheelRamper(OpenHome::Environment& aEnv);

private:
    OpenHome::Environment& iEnv;
    // from SuiteUnitTest

    void Test1(); // FeedbackModel algorithm
    void Test2(); // FeedbackModel scaling
    void Test3(); // FeedbackModel step response output
    void Test4(); // FeedbackModel periodic impulse output
    void Test5(); // FeedbackModel oscillator (periodic alternating polarity impulse output)
    void Test6(); // Burg Method profiling
    void Test7(); // Burg Method testing
    void Test8(); // FeedbackModel profiling



    void Setup();
    void TearDown();

    void FeedbackCycle();

    static void LogBuf(const Brx& aBuf);
    static TInt32 Int32(const Brx& aBuf, TUint aIndex);
    static void Append32(Bwx& aBuf, TInt32 aSample);

    static double ToDouble(TInt32 aVal);
    static TInt32 ToFfpn(double aVal);

private:
    TInt16* iCoeffs;
    std::vector<TInt32> iSamples;
    PcmProcessorFeedback* iOutputProc;
    TUint iScaleShiftForProduct;
    TUint iScaleShiftForOutput;
    TUint iDegree;
};

//////////////////////////////////////////////////////////////

class PcmProcessorFeedback : public IPcmProcessor, public INonCopyable
{
public:
    PcmProcessorFeedback(Bwx& aBuf);

    // IPcmProcessor
    virtual void BeginBlock() {};
    virtual void EndBlock() {};

    virtual void ProcessFragment8(const Brx& /*aData*/, TUint /*aNumChannels*/) {ASSERTS();};
    virtual void ProcessFragment16(const Brx& /*aData*/, TUint /*aNumChannels*/) {ASSERTS();};
    virtual void ProcessFragment24(const Brx& /*aData*/, TUint /*aNumChannels*/) {ASSERTS();};
    virtual void ProcessFragment32(const Brx& aData, TUint aNumChannels);
    virtual void ProcessSample8(const TByte* /*aSample*/, TUint /*aNumChannels*/) {ASSERTS();};
    virtual void ProcessSample16(const TByte* /*aSample*/, TUint /*aNumChannels*/) {ASSERTS();};
    virtual void ProcessSample24(const TByte* /*aSample*/, TUint /*aNumChannels*/) {ASSERTS();};
    virtual void ProcessSample32(const TByte* /*aSample*/, TUint /*aNumChannels*/) {ASSERTS();};
    virtual void Flush() {ASSERTS();};


private:
    //Bwx& iBuf;
};



} // TestFlywheelRamper
} // Media
} // OpenHome

//////////////////////////////////////////////////////////////

using namespace OpenHome::Media::TestFlywheelRamper;


TInt32 SuiteFlywheelRamper::Int32(const Brx& aSamples, TUint aByteIndex)
{
    TInt32 sample = (TInt32)aSamples[aByteIndex];
    sample <<= 8;
    sample |= (TInt32)aSamples[aByteIndex+1];
    sample <<= 8;
    sample |= (TInt32)aSamples[aByteIndex+2];
    sample <<= 8;
    sample |= (TInt32)aSamples[aByteIndex+3];
    return(sample);
}


SuiteFlywheelRamper::SuiteFlywheelRamper(OpenHome::Environment& aEnv)
    :SuiteUnitTest("SuiteFlywheelRamper")
    ,iEnv(aEnv)
{
    AddTest(MakeFunctor(*this, &SuiteFlywheelRamper::Test1));
    AddTest(MakeFunctor(*this, &SuiteFlywheelRamper::Test2));
    AddTest(MakeFunctor(*this, &SuiteFlywheelRamper::Test3));
    AddTest(MakeFunctor(*this, &SuiteFlywheelRamper::Test4));
    AddTest(MakeFunctor(*this, &SuiteFlywheelRamper::Test5));

    //AddTest(MakeFunctor(*this, &SuiteFlywheelRamper::Test6)); // Burg Method testing
    //AddTest(MakeFunctor(*this, &SuiteFlywheelRamper::Test7)); // Burg Method profiling
    //AddTest(MakeFunctor(*this, &SuiteFlywheelRamper::Test8)); // Feedback profiling
}


void SuiteFlywheelRamper::Test1() // FeedbackModel algorithm
{
    //Log::Print("\n");
    const TUint kDataInDescaleBits = 8;
    const TUint kCoeffFormat = 1;
    const TUint kDataInFormat = 1;
    const TUint kDataOutFormat = 1;

    const TUint kDegree = 4;

    TInt16* coeffs = (TInt16*) calloc (kDegree, sizeof(TInt16));
    TInt16* coeffsPtr = coeffs;

    *(coeffsPtr++) = 0x0100;
    *(coeffsPtr++) = 0x0200;
    *(coeffsPtr++) = 0x0400;
    *(coeffsPtr++) = 0x0800;

    TInt32* samplesIn = (TInt32*) calloc (kDegree, sizeof(TInt32));
    TInt32* samplesInPtr = samplesIn;
    *(samplesInPtr++) = 0x01000000;
    *(samplesInPtr++) = 0x02000000;
    *(samplesInPtr++) = 0x04000000;
    *(samplesInPtr++) = 0x08000000;

    std::vector<TInt32> expectedSamplesOut;
    expectedSamplesOut.push_back(0x00aa0000);
    expectedSamplesOut.push_back(0x00555400);
    expectedSamplesOut.push_back(0x002b5200);
    expectedSamplesOut.push_back(0x0016fa00);


    FeedbackModel* feedback = new FeedbackModel(kDegree, kDataInDescaleBits, kCoeffFormat, kDataInFormat, kDataOutFormat);
    feedback->Initialise(coeffs, samplesIn);

    for (TUint i=0; i<kDegree; i++)
    {
        TInt sample = feedback->NextSample();
        TEST(sample == expectedSamplesOut[i]);
        //Log::Print(" actual=%lx   expected=%lx  i=%d\n", sample, expectedSamplesOut[i], i);
    }

    delete feedback;
    free(coeffs);
    free(samplesIn);
}

void SuiteFlywheelRamper::Test2()  // FeedbackModel scaling
{
    //Log::Print("\n");
    const TUint kDataInDescaleBits = 8;

    const TUint kDegree = 2;

    TInt16* coeffs = (TInt16*) calloc (kDegree, sizeof(TInt16));
    *coeffs = 0x0100;
    *(coeffs+1) = 0;

    TInt32* samplesIn = (TInt32*) calloc (kDegree, sizeof(TInt32));
    *samplesIn = 0x01000000;
    *(samplesIn+1) = 0;

    FeedbackModel* feedback;

    feedback = new FeedbackModel(kDegree, kDataInDescaleBits, 1, 1, 1);
    feedback->Initialise(coeffs, samplesIn);
    TEST( feedback->NextSample() == 0x20000);
    TEST( feedback->NextSample() == 0x400);
    delete feedback;

    *samplesIn = 0x01000000;
    *(samplesIn+1) = 0;
    feedback = new FeedbackModel(kDegree, kDataInDescaleBits, 2, 1, 1);
    feedback->Initialise(coeffs, samplesIn);
    TEST( feedback->NextSample() == 0x40000);
    TEST( feedback->NextSample() == 0x1000); // (2/x/x)
    delete feedback;

    *samplesIn = 0x01000000;
    *(samplesIn+1) = 0;
    feedback = new FeedbackModel(kDegree, kDataInDescaleBits, 3, 1, 1);
    feedback->Initialise(coeffs, samplesIn);
    TEST( feedback->NextSample() == 0x80000);
    TEST( feedback->NextSample() == 0x4000); // (3/x/x)
    delete feedback;

    *samplesIn = 0x01000000;
    *(samplesIn+1) = 0;
    feedback = new FeedbackModel(kDegree, kDataInDescaleBits, 4, 1, 1);
    feedback->Initialise(coeffs, samplesIn);
    TEST( feedback->NextSample() == 0x0100000);
    TEST( feedback->NextSample() == 0x10000); // (4/x/x)
    delete feedback;

    *samplesIn = 0x01000000;
    *(samplesIn+1) = 0;
    feedback = new FeedbackModel(kDegree, kDataInDescaleBits, 1, 2, 1);
    feedback->Initialise(coeffs, samplesIn);
    TEST( feedback->NextSample() == 0x40000); //  (x/2/x)
    TEST( feedback->NextSample() == 0x800);  //  (x/2/x)
    delete feedback;

    *samplesIn = 0x01000000;
    *(samplesIn+1) = 0;
    feedback = new FeedbackModel(kDegree, kDataInDescaleBits, 1, 3, 1);
    feedback->Initialise(coeffs, samplesIn);
    TEST( feedback->NextSample() == 0x80000); //  (x/3/x)
    TEST( feedback->NextSample() == 0x1000);  //  (x/3/x)
    delete feedback;

    *samplesIn = 0x01000000;
    *(samplesIn+1) = 0;
    feedback = new FeedbackModel(kDegree, kDataInDescaleBits, 1, 4, 1);
    feedback->Initialise(coeffs, samplesIn);
    TEST( feedback->NextSample() == 0x0100000); //  (x/4/x)
    TEST( feedback->NextSample() == 0x2000);  //  (x/4/x)
    delete feedback;

    *samplesIn = 0x01000000;
    *(samplesIn+1) = 0;
    feedback = new FeedbackModel(kDegree, kDataInDescaleBits, 1, 1, 2);
    feedback->Initialise(coeffs, samplesIn);
    TEST( feedback->NextSample() == 0x10000); //  (x/x/2)
    TEST( feedback->NextSample() == 0x200); //  (x/x/2)
    delete feedback;

    *samplesIn = 0x01000000;
    *(samplesIn+1) = 0;
    feedback = new FeedbackModel(kDegree, kDataInDescaleBits, 1, 1, 3);
    feedback->Initialise(coeffs, samplesIn);
    TEST( feedback->NextSample() == 0x8000); //  (x/x/3)
    TEST( feedback->NextSample() == 0x100); //  (x/x/3)
    delete feedback;

    *samplesIn = 0x01000000;
    *(samplesIn+1) = 0;
    feedback = new FeedbackModel(kDegree, kDataInDescaleBits, 1, 1, 4);
    feedback->Initialise(coeffs, samplesIn);
    TEST( feedback->NextSample() == 0x4000); //  (x/x/4)
    TEST( feedback->NextSample() == 0x80); //  (x/x/4)
    delete feedback;

    *samplesIn = 0x01000000;
    *(samplesIn+1) = 0;
    feedback = new FeedbackModel(kDegree, kDataInDescaleBits, 2, 2, 2);
    feedback->Initialise(coeffs, samplesIn);
    TEST( feedback->NextSample() == 0x40000); //  (x/2/2)
    TEST( feedback->NextSample() == 0x1000); // *2*2/2  (2/2/2)
    delete feedback;

    free(coeffs);
    free(samplesIn);
}


void SuiteFlywheelRamper::Test3()  // FeedbackModel step response output
{

    const TUint kDataInDescaleBits = 8;

    const TUint kCoeffFormat = 2;
    const TUint kDataInFormat = 2;
    const TUint kDataOutFormat = 2;

    const TUint kDegree = 6;

    TInt16* coeffs = (TInt16*) calloc (kDegree, sizeof(TInt16));
    TInt16* coeffPtr = coeffs;
    *(coeffPtr++) = 0x4000;
    *(coeffPtr++) = 0;
    *(coeffPtr++) = 0;
    *(coeffPtr++) = 0;
    *(coeffPtr++) = 0;
    *(coeffPtr++) = 0;

    TInt32* samplesIn = (TInt32*) calloc (kDegree, sizeof(TInt32));
    TInt32* samplesInPtr = samplesIn;
    *(samplesInPtr++) = 0x40000000;
    *(samplesInPtr++) = 0x00000000;
    *(samplesInPtr++) = 0x00000000;
    *(samplesInPtr++) = 0x00000000;
    *(samplesInPtr++) = 0x00000000;
    *(samplesInPtr++) = 0x00000000;


    auto feedback = new FeedbackModel(kDegree, kDataInDescaleBits, kCoeffFormat, kDataInFormat, kDataOutFormat);
    feedback->Initialise(coeffs, samplesIn);

    //Log::Print("\n\nUnit Test\n\n");
    //
    // sampleOut n = sampleIn(n) + coeff(1)*sampleOut(n-1) + coeff(2)*sampleOut(n-2)...
    //
    // for n=1 to x (where x= num samples in + num coeffs -1):


    for(TUint i=0; i<10; i++)
    {
        // output sample will equal the coeff value
        TEST( feedback->NextSample() == 0x40000000 );
    }

    delete feedback;
    free(coeffs);
    free(samplesIn);
}


void SuiteFlywheelRamper::Test4()  // FeedbackModel periodic impulse output
{

    const TUint kDataInDescaleBits = 8;
    const TUint kCoeffFormat = 2;
    const TUint kDataInFormat = 2;
    const TUint kDataOutFormat = 2;

    const TUint kDegree = 6;

    TInt16* coeffs = (TInt16*) calloc (kDegree, sizeof(TInt16));
    TInt16* coeffPtr = coeffs;

    *(coeffPtr++) = 0;
    *(coeffPtr++) = 0x4000;
    *(coeffPtr++) = 0;
    *(coeffPtr++) = 0;
    *(coeffPtr++) = 0;
    *(coeffPtr++) = 0;


    TInt32* samplesIn = (TInt32*) calloc (kDegree, sizeof(TInt32));
    TInt32* samplesInPtr = samplesIn;
    *(samplesInPtr++) = 0x40000000;
    *(samplesInPtr++) = 0x00000000;
    *(samplesInPtr++) = 0x00000000;
    *(samplesInPtr++) = 0x00000000;
    *(samplesInPtr++) = 0x00000000;
    *(samplesInPtr++) = 0x00000000;


    auto feedback = new FeedbackModel(kDegree, kDataInDescaleBits, kCoeffFormat, kDataInFormat, kDataOutFormat);
    feedback->Initialise(coeffs, samplesIn);


    //Log::Print("\n\nUnit Test\n\n");
    //
    // sampleOut n = sampleIn(n) + coeff(1)*sampleOut(n-1) + coeff(2)*sampleOut(n-2)...
    //
    // for n=1 to x (where x= num samples in + num coeffs -1):


    TEST( feedback->NextSample() == 0 );
    TEST( feedback->NextSample() == 0x40000000 );
    TEST( feedback->NextSample() == 0 );
    TEST( feedback->NextSample() == 0x40000000 );
    TEST( feedback->NextSample() == 0 );
    TEST( feedback->NextSample() == 0x40000000 );
    TEST( feedback->NextSample() == 0 );
    TEST( feedback->NextSample() == 0x40000000 );

    delete feedback;


    coeffPtr = coeffs;
    *(coeffPtr++) = 0;
    *(coeffPtr++) = 0;
    *(coeffPtr++) = 0x4000;
    *(coeffPtr++) = 0;
    *(coeffPtr++) = 0;
    *(coeffPtr++) = 0;

    samplesInPtr = samplesIn;
    *(samplesInPtr++) = 0x40000000;
    *(samplesInPtr++) = 0x00000000;
    *(samplesInPtr++) = 0x00000000;
    *(samplesInPtr++) = 0x00000000;
    *(samplesInPtr++) = 0x00000000;
    *(samplesInPtr++) = 0x00000000;


    feedback = new FeedbackModel(kDegree, kDataInDescaleBits, kCoeffFormat, kDataInFormat, kDataOutFormat);
    feedback->Initialise(coeffs, samplesIn);

    TEST( feedback->NextSample() == 0 );
    TEST( feedback->NextSample() == 0 );
    TEST( feedback->NextSample() == 0x40000000 );
    TEST( feedback->NextSample() == 0 );
    TEST( feedback->NextSample() == 0 );
    TEST( feedback->NextSample() == 0x40000000 );

    delete feedback;
    free(coeffs);
    free(samplesIn);
}


void SuiteFlywheelRamper::Test5()  // FeedbackModel alternating polarity periodic impulse output (oscillator)
{
    // Period of oscillation is determined by position of coeff in list

    const TUint kDataInDescaleBits = 8;
    const TUint kCoeffFormat = 2;
    const TUint kDataInFormat = 2;
    const TUint kDataOutFormat = 2;

    const TUint kDegree = 6;


    TUint16* coeffs = (TUint16*) calloc (kDegree, sizeof(TUint16));
    TUint16* coeffPtr = coeffs;
    *(coeffPtr++) = 0xc000;
    *(coeffPtr++) = 0;
    *(coeffPtr++) = 0;
    *(coeffPtr++) = 0;
    *(coeffPtr++) = 0;
    *(coeffPtr++) = 0;


    TInt32* samplesIn = (TInt32*) calloc (kDegree, sizeof(TInt32));
    TInt32* samplesInPtr = samplesIn;
    *(samplesInPtr++) = 0x40000000;
    *(samplesInPtr++) = 0x00000000;
    *(samplesInPtr++) = 0x00000000;
    *(samplesInPtr++) = 0x00000000;
    *(samplesInPtr++) = 0x00000000;
    *(samplesInPtr++) = 0x00000000;


    auto feedback = new FeedbackModel(kDegree, kDataInDescaleBits, kCoeffFormat, kDataInFormat, kDataOutFormat);
    feedback->Initialise((TInt16*)coeffs, samplesIn);

    //Log::Print("\n\nUnit Test\n\n");
    //
    // sampleOut n = sampleIn(n) + coeff(1)*sampleOut(n-1) + coeff(2)*sampleOut(n-2)...
    //
    // for n=1 to x (where x= num samples in + num coeffs -1):


    TEST( feedback->NextSample() == (TInt32)0xc0000000L );
    TEST( feedback->NextSample() == 0x40000000L );
    TEST( feedback->NextSample() == (TInt32)0xc0000000L );
    TEST( feedback->NextSample() == 0x40000000L );
    TEST( feedback->NextSample() == (TInt32)0xc0000000L );
    TEST( feedback->NextSample() == 0x40000000L );

    delete feedback;


    coeffPtr = coeffs;
    *(coeffPtr++) = 0;
    *(coeffPtr++) = 0xc000;
    *(coeffPtr++) = 0;
    *(coeffPtr++) = 0;
    *(coeffPtr++) = 0;
    *(coeffPtr++) = 0;

    samplesInPtr = samplesIn;
    *(samplesInPtr++) = 0x40000000;
    *(samplesInPtr++) = 0x00000000;
    *(samplesInPtr++) = 0x00000000;
    *(samplesInPtr++) = 0x00000000;
    *(samplesInPtr++) = 0x00000000;
    *(samplesInPtr++) = 0x00000000;


    feedback = new FeedbackModel(kDegree, kDataInDescaleBits, kCoeffFormat, kDataInFormat, kDataOutFormat);
    feedback->Initialise((TInt16*)coeffs, samplesIn);

    TEST( feedback->NextSample() == 0 );
    TEST( feedback->NextSample() == (TInt32)0xc0000000L );
    TEST( feedback->NextSample() == 0 );
    TEST( feedback->NextSample() == 0x40000000 );
    TEST( feedback->NextSample() == 0 );
    TEST( feedback->NextSample() == (TInt32)0xc0000000L );

    delete feedback;

    coeffPtr = coeffs;
    *(coeffPtr++) = 0;
    *(coeffPtr++) = 0;
    *(coeffPtr++) = 0xc000;
    *(coeffPtr++) = 0;
    *(coeffPtr++) = 0;
    *(coeffPtr++) = 0;
    samplesInPtr = samplesIn;
    *(samplesInPtr++) = 0x40000000;
    *(samplesInPtr++) = 0x00000000;
    *(samplesInPtr++) = 0x00000000;
    *(samplesInPtr++) = 0x00000000;
    *(samplesInPtr++) = 0x00000000;
    *(samplesInPtr++) = 0x00000000;


    feedback = new FeedbackModel(kDegree, kDataInDescaleBits, kCoeffFormat, kDataInFormat, kDataOutFormat);
    feedback->Initialise((TInt16*)coeffs, samplesIn);


    TEST( feedback->NextSample() == 0 );
    TEST( feedback->NextSample() == 0 );
    TEST( feedback->NextSample() == (TInt32)0xc0000000L );
    TEST( feedback->NextSample() == 0 );
    TEST( feedback->NextSample() == 0 );
    TEST( feedback->NextSample() == 0x40000000 );
    TEST( feedback->NextSample() == 0 );
    TEST( feedback->NextSample() == 0 );
    TEST( feedback->NextSample() == (TInt32)0xc0000000L );
    TEST( feedback->NextSample() == 0 );
    TEST( feedback->NextSample() == 0 );
    TEST( feedback->NextSample() == 0x40000000 );


    delete feedback;
    free(coeffs);
    free(samplesIn);
}




TInt32 kBurgTestInput1[] =
{
    111411200, 110362624, 108855296, 107937792, 108265472, 108462080, 108199936, 108527616, 107479040, 105578496, 102170624, 97845248, 93257728, 88342528, 83034112, 77004800, 70844416, 63963136, 56885248, 51183616, 46399488, 41418752, 36306944, 31457280, 27000832, 21430272, 15597568, 10027008, 4521984, 196608, -5439488,
    -10420224, -15335424, -20905984, -26083328, -32112640, -37552128, -42270720, -47251456, -52232192, -55836672, -59834368, -63700992, -67960832
};


TInt32 kBurgTestInput2[] =
{
    80150528, 78249984, 75628544, 74055680, 73924608, 73924608, 73400320, 72744960, 72351744, 70189056, 67174400, 64225280, 60948480, 57999360, 53673984, 49676288, 46596096, 42598400, 38731776, 36044800, 34144256, 31588352, 28966912, 26673152, 24838144, 21889024, 18087936, 14548992, 9961472, 7208960, 3735552, 131072, -3342336, -7602176, -10616832, -14417920, -18546688, -21626880, -25296896, -28901376, -32505856, -35913728, -38731776, -42401792

};



TInt16 kBurgTestOutput1[] =
{
    -8387, 4564, -256
};

TInt16 kBurgTestOutput2[] =
{
    -7362, 2577, 708
};






void SuiteFlywheelRamper::Test6() // Burg Method testing
{
    const TUint kSampleCount = 44;
    const TUint kDegree = 3;

    TInt16* coeffsOut = (TInt16*) calloc (kDegree, sizeof(TInt16));
    TInt16* h = (TInt16*) calloc (kDegree, sizeof(TInt16));
    TInt16* per = (TInt16*) calloc (kSampleCount, sizeof(TInt16));
    TInt16* pef = (TInt16*) calloc (kSampleCount, sizeof(TInt16));
    TInt16* samples = (TInt16*) calloc (kSampleCount, sizeof(TInt16));

    for(TUint i=0; i<kSampleCount; i++)
    {
        *(samples+i) = ((TInt16)(kBurgTestInput1[i]>>16));
    }


    FlywheelRamper::BurgsMethod(samples, kSampleCount, kDegree, coeffsOut, h, per, pef);

    for(TUint i=0; i<kDegree; i++)
    {
        TEST(coeffsOut[i]==kBurgTestOutput1[i]);
        Log::Print("coeffsOut[%d]= %d  kBurgTestOutput1[%d]= %d \n", i, coeffsOut[i], i, kBurgTestOutput1[i]);
    }


    memset(per, 0, kSampleCount*sizeof(TInt16)); // clear
    memset(pef, 0, kSampleCount*sizeof(TInt16)); // clear

    for(TUint i=0; i<kSampleCount; i++)
    {
        *(samples+i) = ((TInt16)(kBurgTestInput2[i]>>16));
    }


    FlywheelRamper::BurgsMethod(samples, kSampleCount, kDegree, coeffsOut, h, per, pef);

    //Log::Print("\n");

    for(TUint i=0; i<kDegree; i++)
    {
        TEST(coeffsOut[i]==kBurgTestOutput2[i]);
    }

    free(coeffsOut);
    free(h);
    free(per);
    free(pef);
}


void SuiteFlywheelRamper::Test7() // Burg Method profiling
{
    Log::Print("Burg Method profiling:: \n");

    const TUint kSampleRate = 192000;
    const TUint kChanCount = 8;
    const TUint kGenMs = 1;
    const TUint kRampMs = 1;
    const TUint kGenJiffies = kGenMs*Jiffies::kPerMs;
    const TUint kRampJiffies = kRampMs*Jiffies::kPerMs;

    TUint genByteCount = FlywheelRamper::SampleCount(kSampleRate, kGenJiffies)*FlywheelRamper::kBytesPerSample*kChanCount;
    TUint rampByteCount = FlywheelRamper::SampleCount(kSampleRate, kRampJiffies)*FlywheelRamper::kBytesPerSample*kChanCount;

    Log::Print("rampByteCount (%d channels) =  %d\n", kChanCount, rampByteCount);


    Bwh genSamples(genByteCount);
    genSamples.SetBytes(genByteCount);
    genSamples.Fill(0); // to keep valgrind happy

    Bwh rampOutput(rampByteCount*1000);
    PcmProcessorFeedback opProc(rampOutput);
    auto ramper = new FlywheelRamperManager(/*iEnv,*/ opProc, kGenJiffies, kRampJiffies);

    ramper->Ramp(genSamples, kSampleRate, kChanCount); // generate the ramp

    //TUint startTime = Os::TimeInMs(iEnv.OsCtx());
    //TUint endTime = Os::TimeInMs(iEnv.OsCtx());
    //Log::Print("time taken = %dms  \n", endTime-startTime);

    Log::Print("processed = %d 32bit samples (%d)\n", rampOutput.Bytes()/4, rampByteCount/4);

    delete ramper;

}


void SuiteFlywheelRamper::Test8() // FeedbackModel profiling
{
/*
    iScaleShiftForProduct = 4;
    iScaleShiftForOutput = 0;

    const TUint kTestScaleCount = 1000;
    const TUint kSampleCount = 192;  // 1 channel at 192khz
    const TUint kChannelCount = 8;
    const TUint kBytesPerSample = 4;
    const TUint kBufBytes = kSampleCount*kChannelCount*kBytesPerSample*kTestScaleCount;

    iDegree = 3;

    TInt16 coeffs;

    iCoeffs = &coeffs;
    iSamples.push_back(0);
    iSamples.push_back(0);
    iSamples.push_back(0);

    Bwh aSamplesOut(kBufBytes);
    iOutputProc = new PcmProcessorFeedback(aSamplesOut);


    TUint startTime = Os::TimeInMs(iEnv.OsCtx());

    for(TUint i=0; i<kTestScaleCount; i++)
    {
        iOutputProc->BeginBlock();
        for(TUint j=0; j<kSampleCount; j++)
        {
            for(TUint k=0; k<kChannelCount; k++)
            {
                FeedbackCycle();
            }

        }
        iOutputProc->EndBlock();
    }

    TUint endTime = Os::TimeInMs(iEnv.OsCtx());

    Log::Print("Feedback Process: time taken = %dms  (%d samples) \n", endTime-startTime, aSamplesOut.Bytes()/4);

    aSamplesOut.SetBytes(0);

    TUint startTime2 = Os::TimeInMs(iEnv.OsCtx());

    for(TUint i=0; i<kTestScaleCount; i++)
    {
        iOutputProc->BeginBlock();
        for(TUint j=0; j<kSampleCount; j++)
        {
            for(TUint k=0; k<kChannelCount; k++)
            {
                ASSERT(iCoeffs!=NULL);

                TInt32 sum = 0;

                TInt16* coeffPtr = iCoeffs;

                // iterate through the circular buff and calculate the output
                for (TUint j=0; j<iDegree; j++)
                {
                    TInt32 coeff = (((TInt32)(*(coeffPtr++)))<<16);
                    TInt64 product = ((TInt64)iSamples[j]) * ((TInt64)coeff); // 1.31 + 4.28 = 5.59 (10.54 with >>8 data  scaling etc)
                    sum += (TInt32)(product>>32);   // 5.27
                }

                // update the states

                for (TInt j=(iDegree-1); j>0; j--)
                {
                    iSamples[j] = iSamples[j-1];
                }

                sum <<= iScaleShiftForProduct;

                iSamples[0] = sum;

                sum <<= iScaleShiftForOutput;

                TByte sample[4];

                sample[3] = (TByte) sum;
                sum >>= 8;
                sample[2] = (TByte) sum;
                sum >>= 8;
                sample[1] = (TByte) sum;
                sum >>= 8;
                sample[0] = (TByte) sum;

                iOutputProc->ProcessSample32(sample, 1); // 1 channel

            }
        }
        iOutputProc->EndBlock();
    }

    TUint endTime2 = Os::TimeInMs(iEnv.OsCtx());


    Log::Print("Feedback Process(inline): time taken = %dms  (%d samples)  \n", endTime2-startTime2, aSamplesOut.Bytes()/4);
*/
}


void SuiteFlywheelRamper::FeedbackCycle()
{
    ASSERT(iCoeffs!=NULL);

    TInt32 sum = 0;

    TInt16* coeffPtr = iCoeffs;

    // iterate through the circular buff and calculate the output
    for (TUint j=0; j<iDegree; j++)
    {
        TInt32 coeff = (((TInt32)(*(coeffPtr++)))<<16);
        TInt64 product = ((TInt64)iSamples[j]) * ((TInt64)coeff); // 1.31 + 4.28 = 5.59 (10.54 with >>8 data  scaling etc)
        sum += (TInt32)(product>>32);   // 5.27
    }

    // update the states

    for (TInt j=(iDegree-1); j>0; j--)
    {
        iSamples[j] = iSamples[j-1];
    }

    sum <<= iScaleShiftForProduct;

    iSamples[0] = sum;

    sum <<= iScaleShiftForOutput;

    TByte sample[4];

    sample[3] = (TByte) sum;
    sum >>= 8;
    sample[2] = (TByte) sum;
    sum >>= 8;
    sample[1] = (TByte) sum;
    sum >>= 8;
    sample[0] = (TByte) sum;

    iOutputProc->ProcessSample32(sample, 1); // 1 channel
}

void SuiteFlywheelRamper::Setup()
{
}


void SuiteFlywheelRamper::TearDown()
{
}


void SuiteFlywheelRamper::LogBuf(const Brx& aBuf)
{
    for(TUint x=0; x<aBuf.Bytes(); x++)
    {
        Log::Print("%x ", aBuf[x]);
    }
    Log::Print("\n");
}


void SuiteFlywheelRamper::Append32(Bwx& aBuf, TInt32 aSample)
{
    aBuf.Append((TByte)(aSample>>24));
    aBuf.Append((TByte)(aSample>>16));
    aBuf.Append((TByte)(aSample>>8));
    aBuf.Append((TByte)(aSample));
}


/*
double FlywheelRamper::ToDouble(TInt32 aVal, TUint aScale)
{
    // from : http://forums.devshed.com/programming-42/converting-12-20-fixed-float-636842.html
    TUint scaleFactor = (1<<(32-aScale));
    double dbl = ((double)aVal)/scaleFactor;
    return(dbl);
}

double FlywheelRamper::ToDouble(TInt16 aVal, TUint aScale)
{
    // from : http://forums.devshed.com/programming-42/converting-12-20-fixed-float-636842.html
    TUint scaleFactor = (1<<(16-aScale));
    double dbl = ((double)aVal)/scaleFactor;
    return(dbl);
}
*/

/////////////////////////////////////////////////////////////////

PcmProcessorFeedback::PcmProcessorFeedback(Bwx& /*aBuf*/)
    //:iBuf(aBuf)
{

}

void PcmProcessorFeedback::ProcessFragment32(const Brx& /*aData*/, TUint /*aNumChannels*/)
{

}




/////////////////////////////////////////////////////////////////

void TestFlywheelRamper(OpenHome::Environment& aEnv)
{
    Runner runner("Testing FlywheelRamper");
    runner.Add(new SuiteFlywheelRamper(aEnv));
    runner.Run();

}

/////////////////////////////////////////////////////////////////



