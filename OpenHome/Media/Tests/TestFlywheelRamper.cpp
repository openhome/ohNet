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

class SuiteFlywheelRamper : public SuiteUnitTest, public INonCopyable
{
public:
    SuiteFlywheelRamper(OpenHome::Environment& aEnv);

private:
    OpenHome::Environment& iEnv;
    // from SuiteUnitTest
    void Test1(); // ConvolutionModel scaling
    void Test2(); // ConvolutionModel zero coeffs
    void Test3(); // ConvolutionModel positive coeff impulse
    void Test4(); // ConvolutionModel negative coeff impulse
    void Test5(); // ConvolutionModel positive sample impulse
    void Test6(); // ConvolutionModel negative sample impulse

    void Test7(); // FeedbackModel scaling
    void Test8(); // FeedbackModel step response output
    void Test9(); // FeedbackModel periodic impulse output
    void Test10(); // FeedbackModel oscillator (periodic alternating polarity impulse output)

    void Test11(); // // double<>FFPN

    void Test12(); // ConvolutionModel algorithm
    void Test13(); // FeedbackModel algorithm

    void Test14(); // Burg Method profiling
    void Test15(); // Burg Method testing

    void Setup();
    void TearDown();

    static void LogBuf(const Brx& aBuf);
    static TInt32 Int32(const Brx& aBuf, TUint aIndex);
    static void Append32(Bwx& aBuf, TInt32 aSample);

    static double ToDouble(TInt32 aVal);
    static TInt32 ToFfpn(double aVal);

};

//////////////////////////////////////////////////////////////

} // TestFlywheelRamper
} // Media
} // OpenHome

//////////////////////////////////////////////////////////////

using namespace OpenHome::Media::TestFlywheelRamper;


SuiteFlywheelRamper::SuiteFlywheelRamper(OpenHome::Environment& aEnv)
    :SuiteUnitTest("SuiteFlywheelRamper")
    ,iEnv(aEnv)
{
/*
    AddTest(MakeFunctor(*this, &SuiteFlywheelRamper::Test1));
    AddTest(MakeFunctor(*this, &SuiteFlywheelRamper::Test2));
    AddTest(MakeFunctor(*this, &SuiteFlywheelRamper::Test3));
    AddTest(MakeFunctor(*this, &SuiteFlywheelRamper::Test4));
    AddTest(MakeFunctor(*this, &SuiteFlywheelRamper::Test5));
    AddTest(MakeFunctor(*this, &SuiteFlywheelRamper::Test6));
    AddTest(MakeFunctor(*this, &SuiteFlywheelRamper::Test7));
    AddTest(MakeFunctor(*this, &SuiteFlywheelRamper::Test8));
    AddTest(MakeFunctor(*this, &SuiteFlywheelRamper::Test9));
    AddTest(MakeFunctor(*this, &SuiteFlywheelRamper::Test10));
*/
    //AddTest(MakeFunctor(*this, &SuiteFlywheelRamper::Test11));
    //AddTest(MakeFunctor(*this, &SuiteFlywheelRamper::Test12));

    //AddTest(MakeFunctor(*this, &SuiteFlywheelRamper::Test13));
    //AddTest(MakeFunctor(*this, &SuiteFlywheelRamper::Test14));
    AddTest(MakeFunctor(*this, &SuiteFlywheelRamper::Test15));
}


void SuiteFlywheelRamper::Test1()  // ConvolutionModel scaling
{
/*
    const TUint kCoeffsCount = 2;
    const TUint kSamplesInCount = 2;
    const TUint kSamplesInBytes = kSamplesInCount*4;
    const TUint kSamplesOutCount = kSamplesInCount+kCoeffsCount-1;
    const TUint kSamplesOutBytes = kSamplesOutCount*4;


    std::vector<TInt32> coeffs;
    coeffs.push_back(0x01000000);
    coeffs.push_back(0x02000000);

    Bws<kSamplesInBytes> samplesIn;
    Append32(samplesIn, 0x01000000);
    Append32(samplesIn, 0);

    Bws<kSamplesOutBytes> samplesOut;


    ConvolutionModel* conv;
    TInt32 sampleOut0;
    TInt32 sampleOut1;


    conv = new ConvolutionModel(coeffs, 1, 1, 1);
    conv->Process(samplesIn, samplesOut, 2);
    sampleOut0 = FlywheelRamper::Int32(samplesOut, 0);
    sampleOut1 = FlywheelRamper::Int32(samplesOut, 4);
    TEST( sampleOut0 == 0x20000);
    TEST( sampleOut1 == 0x40000);
    delete conv;


    conv = new ConvolutionModel(coeffs, 2, 1, 1);
    conv->Process(samplesIn, samplesOut, 2);
    sampleOut0 = FlywheelRamper::Int32(samplesOut, 0);
    sampleOut1 = FlywheelRamper::Int32(samplesOut, 4);
    TEST( sampleOut0 == 0x20000<<1); // << (2-1)
    TEST( sampleOut1 == 0x40000<<1);
    delete conv;

    conv = new ConvolutionModel(coeffs, 3, 1, 1);
    conv->Process(samplesIn, samplesOut, 2);
    sampleOut0 = FlywheelRamper::Int32(samplesOut, 0);
    sampleOut1 = FlywheelRamper::Int32(samplesOut, 4);
    TEST( sampleOut0 == 0x20000<<2); // << (3-1)
    TEST( sampleOut1 == 0x40000<<2);
    delete conv;

    conv = new ConvolutionModel(coeffs, 4, 1, 1);
    conv->Process(samplesIn, samplesOut, 2);
    sampleOut0 = FlywheelRamper::Int32(samplesOut, 0);
    sampleOut1 = FlywheelRamper::Int32(samplesOut, 4);
    TEST( sampleOut0 == 0x20000<<3); // << (4-1)
    TEST( sampleOut1 == 0x40000<<3);
    delete conv;


    conv = new ConvolutionModel(coeffs, 1, 2, 1);
    conv->Process(samplesIn, samplesOut, 2);
    sampleOut0 = FlywheelRamper::Int32(samplesOut, 0);
    sampleOut1 = FlywheelRamper::Int32(samplesOut, 4);
    TEST( sampleOut0 == 0x20000<<1); // <<  (2-1)
    TEST( sampleOut1 == 0x40000<<1);
    delete conv;

    conv = new ConvolutionModel(coeffs, 1, 3, 1);
    conv->Process(samplesIn, samplesOut, 2);
    sampleOut0 = FlywheelRamper::Int32(samplesOut, 0);
    sampleOut1 = FlywheelRamper::Int32(samplesOut, 4);
    TEST( sampleOut0 == 0x20000<<2); // << (3-1)
    TEST( sampleOut1 == 0x40000<<2);
    delete conv;

    conv = new ConvolutionModel(coeffs, 1, 4, 1);
    conv->Process(samplesIn, samplesOut, 2);
    sampleOut0 = FlywheelRamper::Int32(samplesOut, 0);
    sampleOut1 = FlywheelRamper::Int32(samplesOut, 4);
    TEST( sampleOut0 == 0x20000<<3); // << (4-1)
    TEST( sampleOut1 == 0x40000<<3);
    delete conv;

    conv = new ConvolutionModel(coeffs, 1, 1, 2);
    conv->Process(samplesIn, samplesOut, 2);
    sampleOut0 = FlywheelRamper::Int32(samplesOut, 0);
    sampleOut1 = FlywheelRamper::Int32(samplesOut, 4);
    TEST( sampleOut0 == 0x20000>>1); // >> (2-1)
    TEST( sampleOut1 == 0x40000>>1);
    delete conv;

    conv = new ConvolutionModel(coeffs, 1, 1, 3);
    conv->Process(samplesIn, samplesOut, 2);
    sampleOut0 = FlywheelRamper::Int32(samplesOut, 0);
    sampleOut1 = FlywheelRamper::Int32(samplesOut, 4);
    TEST( sampleOut0 == 0x20000>>2); // >> (3-1)
    TEST( sampleOut1 == 0x40000>>2);
    delete conv;

    conv = new ConvolutionModel(coeffs, 1, 1, 4);
    conv->Process(samplesIn, samplesOut, 2);
    sampleOut0 = FlywheelRamper::Int32(samplesOut, 0);
    sampleOut1 = FlywheelRamper::Int32(samplesOut, 4);
    TEST( sampleOut0 == 0x20000>>3); // >> (4-1)
    TEST( sampleOut1 == 0x40000>>3);
    delete conv;


    conv = new ConvolutionModel(coeffs, 2, 4, 2);
    conv->Process(samplesIn, samplesOut, 2);
    sampleOut0 = FlywheelRamper::Int32(samplesOut, 0);
    sampleOut1 = FlywheelRamper::Int32(samplesOut, 4);
    TEST( sampleOut0 == 0x20000<<3); // << (2-1)+(4-1)-(2-1)
    TEST( sampleOut1 == 0x40000<<3);
    delete conv;

    conv = new ConvolutionModel(coeffs, 8, 4, 3);
    conv->Process(samplesIn, samplesOut, 2);
    sampleOut0 = FlywheelRamper::Int32(samplesOut, 0);
    sampleOut1 = FlywheelRamper::Int32(samplesOut, 4);
    TEST( sampleOut0 == 0x20000<<8); // << (8-1)+(4-1)-(3-1)
    TEST( sampleOut1 == 0x40000<<8);
    delete conv;
*/
}


void SuiteFlywheelRamper::Test2()  // ConvolutionModel zero coeffs
{
/*
    const TUint kCoeffScaling = 1;
    const TUint kDataInScaling = 1;
    const TUint kDataOutScaling = 1;

    const TUint kCoeffsCount = 6;
    const TUint kSamplesInCount = 6;
    const TUint kSamplesInBytes = kSamplesInCount*4;
    const TUint kSamplesOutCount = kSamplesInCount+kCoeffsCount-1;
    const TUint kSamplesOutBytes = kSamplesOutCount*4;

    std::vector<TInt32> coeffs;
    coeffs.push_back(0);
    coeffs.push_back(0);
    coeffs.push_back(0);
    coeffs.push_back(0);
    coeffs.push_back(0);
    coeffs.push_back(0);

    Bws<kSamplesInBytes> samplesIn;
    Append32(samplesIn, 0x00001fff);
    Append32(samplesIn, 0x00007f85);
    Append32(samplesIn, 0x0000505e);
    Append32(samplesIn, 0x0456f05e);
    Append32(samplesIn, 0xfefefefe);
    Append32(samplesIn, 0x000df35a);

    Bws<kSamplesOutBytes> samplesOut;

    auto conv = new ConvolutionModel(coeffs, kCoeffScaling, kDataInScaling, kDataOutScaling);
    conv->Process(samplesIn, samplesOut, kSamplesOutCount);

    for(TUint i=0; i<kSamplesOutCount; i++)
    {
        TEST( FlywheelRamper::Int32(samplesOut, i*4) == 0 );
    }

    delete conv;
*/
}


void SuiteFlywheelRamper::Test3()  // ConvolutionModel positive coeff impulse
{
/*
    const TUint kCoeffScaling = 2;
    const TUint kDataInScaling = 1;
    const TUint kDataOutScaling = 1;

    const TUint kCoeffsCount = 2;
    const TUint kSamplesInCount = 6;
    const TUint kSamplesInBytes = kSamplesInCount*4;
    const TUint kSamplesOutCount = kSamplesInCount+kCoeffsCount-1;
    const TUint kSamplesOutBytes = kSamplesOutCount*4;

    std::vector<TInt32> coeffs;
    coeffs.push_back(0x40000000); //  +1 (coeff scaling = 2)
    coeffs.push_back(0);
    coeffs.push_back(0);
    coeffs.push_back(0);
    coeffs.push_back(0);
    coeffs.push_back(0);

    Bws<kSamplesInBytes> samplesIn;
    Append32(samplesIn, 0x00001fff);
    Append32(samplesIn, 0x00007f85);
    Append32(samplesIn, 0x0000505e);
    Append32(samplesIn, 0x0456f05e);
    Append32(samplesIn, 0xfefefefe);
    Append32(samplesIn, 0x000df35a);

    Bws<kSamplesOutBytes> samplesOut;

    auto conv = new ConvolutionModel(coeffs, kCoeffScaling, kDataInScaling, kDataOutScaling);
    conv->Process(samplesIn, samplesOut, kSamplesOutCount);

    for(TUint i=0; i<kSamplesOutCount; i++)
    {
        if (i<kSamplesInCount)
        {
            TInt32 sampleIn = FlywheelRamper::Int32(samplesIn, i*4);
            sampleIn &= 0xffffff00L; // lower 8 bits are discarded by model calculation
            TInt32 sampleOut = FlywheelRamper::Int32(samplesOut, i*4);

            // output sample will equal input sample
            TEST( sampleOut == sampleIn );
        }
        else
        {
            // for cycle counts above the input sample count the output sample will be zero
            TEST( FlywheelRamper::Int32(samplesOut, i*4) == 0 );
        }
    }

    delete conv;
*/
}


void SuiteFlywheelRamper::Test4()  // ConvolutionModel negative coeff impulse
{
/*
    const TUint kCoeffScaling = 1;
    const TUint kDataInScaling = 1;
    const TUint kDataOutScaling = 1;

    const TUint kCoeffsCount = 2;
    const TUint kSamplesInCount = 6;
    const TUint kSamplesInBytes = kSamplesInCount*4;
    const TUint kSamplesOutCount = kSamplesInCount+kCoeffsCount-1;
    const TUint kSamplesOutBytes = kSamplesOutCount*4;

    std::vector<TInt32> coeffs;
    coeffs.push_back(0x80000000); //  -1
    coeffs.push_back(0);
    coeffs.push_back(0);
    coeffs.push_back(0);
    coeffs.push_back(0);
    coeffs.push_back(0);

    Bws<kSamplesInBytes> samplesIn;
    Append32(samplesIn, 0x00001fff);
    Append32(samplesIn, 0x00007f85);
    Append32(samplesIn, 0x0000505e);
    Append32(samplesIn, 0x0456f05e);
    Append32(samplesIn, 0xfefefefe);
    Append32(samplesIn, 0x000df35a);

    Bws<kSamplesOutBytes> samplesOut;

    auto conv = new ConvolutionModel(coeffs, kCoeffScaling, kDataInScaling, kDataOutScaling);
    conv->Process(samplesIn, samplesOut, kSamplesOutCount);

    for(TUint i=0; i<kSamplesOutCount; i++)
    {
        if (i<kSamplesInCount)
        {
            TInt32 sampleIn = FlywheelRamper::Int32(samplesIn, i*4);
            sampleIn &= 0xffffff00L; // lower 8 bits are discarded by model calculation
            TInt32 sampleOut = FlywheelRamper::Int32(samplesOut, i*4);
            sampleOut &= 0xffffff00L; // lower 8 bits are discarded by model calculation
            // output sample will equal inverse of input sample
            TEST( sampleOut == -sampleIn );
        }
        else
        {
            // for cycle counts above the input sample count the output sample will be zero
            TEST( FlywheelRamper::Int32(samplesOut, i*4) == 0 );
        }
    }

    delete conv;
*/
}


void SuiteFlywheelRamper::Test5()  // ConvolutionModel positive sample impulse
{
/*
    const TUint kCoeffScaling = 1;
    const TUint kDataInScaling = 2;
    const TUint kDataOutScaling = 1;

    const TUint kCoeffsCount = 6;
    const TUint kSamplesInCount = 6;
    const TUint kSamplesInBytes = kSamplesInCount*4;
    const TUint kSamplesOutCount = kSamplesInCount+kCoeffsCount-1;
    const TUint kSamplesOutBytes = kSamplesOutCount*4;

    std::vector<TInt32> coeffs;
    coeffs.push_back(0x1efb1a5e);
    coeffs.push_back(0xf13617f8);
    coeffs.push_back(0x17f8f136);
    coeffs.push_back(0xf1361efb);
    coeffs.push_back(0x1efb17f8);
    coeffs.push_back(0x1a5ef136);

    Bws<kSamplesInBytes> samplesIn;
    Append32(samplesIn, 0x40000000); // +1 (kDataInScaling = 2)
    Append32(samplesIn, 0);
    Append32(samplesIn, 0);
    Append32(samplesIn, 0);
    Append32(samplesIn, 0);
    Append32(samplesIn, 0);
    Bws<kSamplesOutBytes> samplesOut;

    auto conv = new ConvolutionModel(coeffs, kCoeffScaling, kDataInScaling, kDataOutScaling);
    conv->Process(samplesIn, samplesOut, kSamplesOutCount);

    for(TUint i=0; i<kSamplesOutCount; i++)
    {
        TInt32 sampleOut = FlywheelRamper::Int32(samplesOut, i*4);
        sampleOut &= 0xffffff00L;

        if ( (i<kSamplesInCount) && (i<coeffs.size()) )
        {
            TInt32 coeff = (coeffs[i])&0xffffff00L;
            //Log::Print("sampleOut=0x%.8lx  coeff=0x%.8lx\n", sampleOut, coeff);
            // output sample will equal the coeff value
            TEST( sampleOut == coeff );
        }
        else
        {
            // for cycle counts above the input sample count the output sample will be zero
            TEST( sampleOut == 0 );
        }

        //Log::Print("\n");
    }

    delete conv;
*/
}


void SuiteFlywheelRamper::Test6()  // ConvolutionModel negative sample impulse
{
/*
    const TUint kCoeffScaling = 1;
    const TUint kDataInScaling = 1;
    const TUint kDataOutScaling = 1;

    const TUint kCoeffsCount = 6;
    const TUint kSamplesInCount = 6;
    const TUint kSamplesInBytes = kSamplesInCount*4;
    const TUint kSamplesOutCount = kSamplesInCount+kCoeffsCount-1;
    const TUint kSamplesOutBytes = kSamplesOutCount*4;

    std::vector<TInt32> coeffs;
    coeffs.push_back(0x1efb1a5e);
    coeffs.push_back(0xf13617f8);
    coeffs.push_back(0x17f8f136);
    coeffs.push_back(0xf1361efb);
    coeffs.push_back(0x1efb17f8);
    coeffs.push_back(0x1a5ef136);

    Bws<kSamplesInBytes> samplesIn;
    Append32(samplesIn, 0x80000000);
    Append32(samplesIn, 0);
    Append32(samplesIn, 0);
    Append32(samplesIn, 0);
    Append32(samplesIn, 0);
    Append32(samplesIn, 0);

    Bws<kSamplesOutBytes> samplesOut;

    auto conv = new ConvolutionModel(coeffs, kCoeffScaling, kDataInScaling, kDataOutScaling);
    conv->Process(samplesIn, samplesOut, kSamplesOutCount);

    for(TUint i=0; i<kSamplesOutCount; i++)
    {
        if ( (i<kSamplesInCount) && (i<coeffs.size()) )
        {
            TInt32 sampleOut = FlywheelRamper::Int32(samplesOut, i*4);
            TInt coeff = coeffs[i];
            //Log::Print("sampleOut=0x%.8lx  coeff=0x%.8lx\n", sampleOut, coeff);

            // output sample will equal inverse of coeff
            TEST( sampleOut == -coeff );
        }
        else
        {
            // for cycle counts above the input sample count the output sample will be zero
            TEST( FlywheelRamper::Int32(samplesOut, i*4) == 0 );
        }

        //Log::Print("\n");
    }

    delete conv;
*/
}


void SuiteFlywheelRamper::Test7()  // FeedbackModel scaling
{

    const TUint kCoeffsCount = 2;
    const TUint kSamplesInCount = 2;
    const TUint kSamplesInBytes = kSamplesInCount*4;
    const TUint kSamplesOutCount = kSamplesInCount+kCoeffsCount;
    const TUint kSamplesOutBytes = kSamplesOutCount*4;

    std::vector<TInt32> coeffs;
    coeffs.push_back(0x01000000);
    coeffs.push_back(0);

    Bws<kSamplesInBytes> samplesIn;
    Append32(samplesIn, 0x01000000);
    Append32(samplesIn, 0);

    Bws<kSamplesOutBytes> samplesOut;


    FeedbackModel* feedback;
    TInt32 sampleOut0;
    TInt32 sampleOut1;


    feedback = new FeedbackModel(coeffs, 8, 1, 1, 1);

    feedback->Process(samplesIn, samplesOut, 2);
    sampleOut0 = FlywheelRamper::Int32(samplesOut, 0);
    sampleOut1 = FlywheelRamper::Int32(samplesOut, 4);
    TEST( sampleOut0 == 0x01000000);
    TEST( sampleOut1 == 0x20000);
    delete feedback;

    feedback = new FeedbackModel(coeffs, 8, 2, 1, 1);

    feedback->Process(samplesIn, samplesOut, 2);
    sampleOut0 = FlywheelRamper::Int32(samplesOut, 0);
    sampleOut1 = FlywheelRamper::Int32(samplesOut, 4);
    TEST( sampleOut0 == 0x01000000);
    TEST( sampleOut1 == 0x20000<<1); // (2/x/x)
    delete feedback;

    feedback = new FeedbackModel(coeffs, 8, 3, 1, 1);

    feedback->Process(samplesIn, samplesOut, 2);
    sampleOut0 = FlywheelRamper::Int32(samplesOut, 0);
    sampleOut1 = FlywheelRamper::Int32(samplesOut, 4);
    TEST( sampleOut0 == 0x01000000);
    TEST( sampleOut1 == 0x20000<<2); // (3/x/x)
    delete feedback;

    feedback = new FeedbackModel(coeffs, 8, 4, 1, 1);

    feedback->Process(samplesIn, samplesOut, 2);
    sampleOut0 = FlywheelRamper::Int32(samplesOut, 0);
    sampleOut1 = FlywheelRamper::Int32(samplesOut, 4);
    TEST( sampleOut0 == 0x01000000);
    TEST( sampleOut1 == 0x20000<<3); // (4/x/x)
    delete feedback;



    feedback = new FeedbackModel(coeffs, 8, 1, 2, 1);

    feedback->Process(samplesIn, samplesOut, 2);
    sampleOut0 = FlywheelRamper::Int32(samplesOut, 0);
    sampleOut1 = FlywheelRamper::Int32(samplesOut, 4);
    TEST( sampleOut0 == 0x01000000<<1); //  (x/2/x)
    TEST( sampleOut1 == 0x20000<<1);  //  (x/2/x)
    delete feedback;

    feedback = new FeedbackModel(coeffs, 8, 1, 3, 1);

    feedback->Process(samplesIn, samplesOut, 2);
    sampleOut0 = FlywheelRamper::Int32(samplesOut, 0);
    sampleOut1 = FlywheelRamper::Int32(samplesOut, 4);
    TEST( sampleOut0 == 0x01000000<<2); //  (x/3/x)
    TEST( sampleOut1 == 0x20000<<2);  //  (x/3/x)
    delete feedback;

    feedback = new FeedbackModel(coeffs, 8, 1, 4, 1);

    feedback->Process(samplesIn, samplesOut, 2);
    sampleOut0 = FlywheelRamper::Int32(samplesOut, 0);
    sampleOut1 = FlywheelRamper::Int32(samplesOut, 4);
    TEST( sampleOut0 == 0x01000000<<3); //  (x/4/x)
    TEST( sampleOut1 == 0x20000<<3);  //  (x/4/x)
    delete feedback;


    feedback = new FeedbackModel(coeffs, 8, 1, 1, 2);

    feedback->Process(samplesIn, samplesOut, 2);
    sampleOut0 = FlywheelRamper::Int32(samplesOut, 0);
    sampleOut1 = FlywheelRamper::Int32(samplesOut, 4);
    TEST( sampleOut0 == 0x01000000>>1); //  (x/x/2)
    TEST( sampleOut1 == 0x20000>>1); //  (x/x/2)
    delete feedback;

    feedback = new FeedbackModel(coeffs, 8, 1, 1, 3);

    feedback->Process(samplesIn, samplesOut, 2);
    sampleOut0 = FlywheelRamper::Int32(samplesOut, 0);
    sampleOut1 = FlywheelRamper::Int32(samplesOut, 4);
    TEST( sampleOut0 == 0x01000000>>2); //  (x/x/3)
    TEST( sampleOut1 == 0x20000>>2); //  (x/x/3)
    delete feedback;


    feedback = new FeedbackModel(coeffs, 8, 1, 1, 4);

    feedback->Process(samplesIn, samplesOut, 2);
    sampleOut0 = FlywheelRamper::Int32(samplesOut, 0);
    sampleOut1 = FlywheelRamper::Int32(samplesOut, 4);
    TEST( sampleOut0 == 0x01000000>>3); //  (x/x/4)
    TEST( sampleOut1 == 0x20000>>3); //  (x/x/4)
    delete feedback;


    feedback = new FeedbackModel(coeffs, 8, 2, 2, 2);

    feedback->Process(samplesIn, samplesOut, 2);
    sampleOut0 = FlywheelRamper::Int32(samplesOut, 0);
    sampleOut1 = FlywheelRamper::Int32(samplesOut, 4);
    TEST( sampleOut0 == 0x01000000); //  (x/2/2)
    TEST( sampleOut1 == 0x20000<<1); // *2*2/2  (2/2/2)
    delete feedback;


}


void SuiteFlywheelRamper::Test8()  // FeedbackModel step response output
{
    const TUint kCoeffScaling = 2;
    const TUint kDataInScaling = 2;
    const TUint kDataOutScaling = 2;

    const TUint kCoeffsCount = 6;
    const TUint kSamplesInCount = 6;

    const TUint kSamplesInBytes = kSamplesInCount*4;
    const TUint kSamplesOutCount = kSamplesInCount+kCoeffsCount;
    const TUint kSamplesOutBytes = kSamplesOutCount*4;

    std::vector<TInt32> coeffs;
    coeffs.push_back(0x40000000);
    coeffs.push_back(0x00000000);
    coeffs.push_back(0x00000000);
    coeffs.push_back(0x00000000);
    coeffs.push_back(0x00000000);
    coeffs.push_back(0x00000000);


    Bws<kSamplesInBytes> samplesIn;
    Append32(samplesIn, 0x40000000);
    Append32(samplesIn, 0x00000000);
    Append32(samplesIn, 0x00000000);
    Append32(samplesIn, 0x00000000);
    Append32(samplesIn, 0x00000000);
    Append32(samplesIn, 0x00000000);

    Bws<kSamplesOutBytes> samplesOut;

    auto feedback = new FeedbackModel(coeffs, 8, kCoeffScaling, kDataInScaling, kDataOutScaling);
    feedback->Process(samplesIn, samplesOut, kSamplesOutCount);

    //Log::Print("\n\nUnit Test\n\n");
    //
    // sampleOut n = sampleIn(n) + coeff(1)*sampleOut(n-1) + coeff(2)*sampleOut(n-2)...
    //
    // for n=1 to x (where x= num samples in + num coeffs -1):


    for(TUint i=0; i<kSamplesOutCount; i++)
    {
        TInt32 sampleOut = FlywheelRamper::Int32(samplesOut, i*4);
        // output sample will equal the coeff value
        TEST( sampleOut == 0x40000000 );
        //Log::Print("\n");
    }

    delete feedback;
}


void SuiteFlywheelRamper::Test9()  // FeedbackModel periodic impulse output
{
    const TUint kCoeffScaling = 2;
    const TUint kDataInScaling = 2;
    const TUint kDataOutScaling = 2;

    const TUint kCoeffsCount = 6;
    const TUint kSamplesInCount = 6;

    const TUint kSamplesInBytes = kSamplesInCount*4;
    const TUint kSamplesOutCount = kSamplesInCount+kCoeffsCount;
    const TUint kSamplesOutBytes = kSamplesOutCount*4;

    std::vector<TInt32> coeffs;
    coeffs.push_back(0x00000000);
    coeffs.push_back(0x40000000);
    coeffs.push_back(0x00000000);
    coeffs.push_back(0x00000000);
    coeffs.push_back(0x00000000);
    coeffs.push_back(0x00000000);


    Bws<kSamplesInBytes> samplesIn;
    Append32(samplesIn, 0x40000000);
    Append32(samplesIn, 0x00000000);
    Append32(samplesIn, 0x00000000);
    Append32(samplesIn, 0x00000000);
    Append32(samplesIn, 0x00000000);
    Append32(samplesIn, 0x00000000);

    Bws<kSamplesOutBytes> samplesOut;

    auto feedback = new FeedbackModel(coeffs, 8, kCoeffScaling, kDataInScaling, kDataOutScaling);
    feedback->Process(samplesIn, samplesOut, kSamplesOutCount);

    //Log::Print("\n\nUnit Test\n\n");
    //
    // sampleOut n = sampleIn(n) + coeff(1)*sampleOut(n-1) + coeff(2)*sampleOut(n-2)...
    //
    // for n=1 to x (where x= num samples in + num coeffs -1):


    for(TUint i=0; i<kSamplesOutCount;)
    {
        TInt32 sampleOut = FlywheelRamper::Int32(samplesOut, i*4);
        // output sample will equal the coeff value
        TEST( sampleOut == 0x40000000 );
        i++;

        sampleOut = FlywheelRamper::Int32(samplesOut, i*4);
        // output sample will equal the coeff value
        TEST( sampleOut == 0 );
        i++;
        //Log::Print("\n");
    }

    delete feedback;




    std::vector<TInt32> coeffs2;
    coeffs2.push_back(0x00000000);
    coeffs2.push_back(0x00000000);
    coeffs2.push_back(0x40000000);
    coeffs2.push_back(0x00000000);
    coeffs2.push_back(0x00000000);
    coeffs2.push_back(0x00000000);

    feedback = new FeedbackModel(coeffs2, 8, kCoeffScaling, kDataInScaling, kDataOutScaling);
    feedback->Process(samplesIn, samplesOut, kSamplesOutCount);



    for(TUint i=0; i<kSamplesOutCount;)
    {
        TInt32 sampleOut = FlywheelRamper::Int32(samplesOut, i*4);
        // output sample will equal the coeff value
        TEST( sampleOut == 0x40000000 );
        i++;
        if(i>=kSamplesOutCount) {break;}

        sampleOut = FlywheelRamper::Int32(samplesOut, i*4);
        // output sample will equal the coeff value
        TEST( sampleOut == 0 );
        i++;
        if(i>=kSamplesOutCount) {break;}

        sampleOut = FlywheelRamper::Int32(samplesOut, i*4);
        // output sample will equal the coeff value
        TEST( sampleOut == 0 );
        i++;
    }

    delete feedback;

}


void SuiteFlywheelRamper::Test10()  // FeedbackModel alternating polarity periodic impulse output (oscillator)
{
    // Period of oscillation is determined by position of coeff in list

    const TUint kCoeffScaling = 2;
    const TUint kDataInScaling = 2;
    const TUint kDataOutScaling = 2;

    const TUint kCoeffsCount = 6;
    const TUint kSamplesInCount = 6;

    const TUint kSamplesInBytes = kSamplesInCount*4;
    const TUint kSamplesOutCount = kSamplesInCount+kCoeffsCount;
    const TUint kSamplesOutBytes = kSamplesOutCount*4;

    std::vector<TInt32> coeffs;
    coeffs.push_back(0xc0000000);
    coeffs.push_back(0x00000000);
    coeffs.push_back(0x00000000);
    coeffs.push_back(0x00000000);
    coeffs.push_back(0x00000000);
    coeffs.push_back(0x00000000);


    Bws<kSamplesInBytes> samplesIn;
    Append32(samplesIn, 0x40000000);
    Append32(samplesIn, 0x00000000);
    Append32(samplesIn, 0x00000000);
    Append32(samplesIn, 0x00000000);
    Append32(samplesIn, 0x00000000);
    Append32(samplesIn, 0x00000000);

    Bws<kSamplesOutBytes> samplesOut;

    auto feedback = new FeedbackModel(coeffs, 8, kCoeffScaling, kDataInScaling, kDataOutScaling);
    feedback->Process(samplesIn, samplesOut, kSamplesOutCount);

    //Log::Print("\n\nUnit Test\n\n");
    //
    // sampleOut n = sampleIn(n) + coeff(1)*sampleOut(n-1) + coeff(2)*sampleOut(n-2)...
    //
    // for n=1 to x (where x= num samples in + num coeffs -1):


    for(TUint i=0; i<kSamplesOutCount;)
    {
        TInt32 sampleOut = FlywheelRamper::Int32(samplesOut, i*4);
        // output sample will equal the coeff value
        TEST( sampleOut == 0x40000000L );
        i++;
        if(i>=kSamplesOutCount) {break;}

        sampleOut = FlywheelRamper::Int32(samplesOut, i*4);
        // output sample will equal the coeff value
        TEST( sampleOut == (TInt32)0xc0000000L );
        i++;
        //Log::Print("\n");
    }

    delete feedback;


    std::vector<TInt32> coeffs2;
    coeffs2.push_back(0x00000000);
    coeffs2.push_back(0xc0000000);
    coeffs2.push_back(0x00000000);
    coeffs2.push_back(0x00000000);
    coeffs2.push_back(0x00000000);
    coeffs2.push_back(0x00000000);



    feedback = new FeedbackModel(coeffs2, 8, kCoeffScaling, kDataInScaling, kDataOutScaling);
    feedback->Process(samplesIn, samplesOut, kSamplesOutCount);


    for(TUint i=0; i<kSamplesOutCount;)
    {
        TInt32 sampleOut = FlywheelRamper::Int32(samplesOut, i*4);
        // output sample will equal the coeff value
        TEST( sampleOut == 0x40000000 );
        i++;
        if(i>=kSamplesOutCount) {break;}

        sampleOut = FlywheelRamper::Int32(samplesOut, i*4);
        // output sample will equal the coeff value
        TEST( sampleOut == 0 );
        i++;
        if(i>=kSamplesOutCount) {break;}

        sampleOut = FlywheelRamper::Int32(samplesOut, i*4);
        // output sample will equal the coeff value
        TEST( sampleOut == (TInt32)0xc0000000L );
        i++;

        sampleOut = FlywheelRamper::Int32(samplesOut, i*4);
        // output sample will equal the coeff value
        TEST( sampleOut == 0 );
        i++;
        if(i>=kSamplesOutCount) {break;}
    }

    delete feedback;


    std::vector<TInt32> coeffs3;
    coeffs3.push_back(0x00000000);
    coeffs3.push_back(0x00000000);
    coeffs3.push_back(0xc0000000);
    coeffs3.push_back(0x00000000);
    coeffs3.push_back(0x00000000);
    coeffs3.push_back(0x00000000);

    feedback = new FeedbackModel(coeffs3, 8, kCoeffScaling, kDataInScaling, kDataOutScaling);
    feedback->Process(samplesIn, samplesOut, kSamplesOutCount);


    for(TUint i=0; i<kSamplesOutCount;)
    {
        TInt32 sampleOut = FlywheelRamper::Int32(samplesOut, i*4);
        // output sample will equal the coeff value
        TEST( sampleOut == 0x40000000 );
        i++;
        if(i>=kSamplesOutCount) {break;}

        sampleOut = FlywheelRamper::Int32(samplesOut, i*4);
        // output sample will equal the coeff value
        TEST( sampleOut == 0 );
        i++;
        if(i>=kSamplesOutCount) {break;}

        sampleOut = FlywheelRamper::Int32(samplesOut, i*4);
        // output sample will equal the coeff value
        TEST( sampleOut == 0 );
        i++;
        if(i>=kSamplesOutCount) {break;}

        sampleOut = FlywheelRamper::Int32(samplesOut, i*4);
        // output sample will equal the coeff value
        TEST( sampleOut == (TInt32)0xc0000000L );
        i++;

        sampleOut = FlywheelRamper::Int32(samplesOut, i*4);
        // output sample will equal the coeff value
        TEST( sampleOut == 0 );
        i++;
        if(i>=kSamplesOutCount) {break;}

        sampleOut = FlywheelRamper::Int32(samplesOut, i*4);
        // output sample will equal the coeff value
        TEST( sampleOut == 0 );
        i++;
        if(i>=kSamplesOutCount) {break;}
    }

    delete feedback;

}


//#define FRACTION_BITS 31
//#define FIXED_BITVALUE (1.0 / (double)(1<<FRACTION_BITS))

/*
double SuiteFlywheelRamper::ToDouble(TInt32 aVal)
{
    //double dbl = FIXED_BITVALUE * aVal;
    double dbl = (double)aVal/2147483648L; // 1<<31
    return(dbl);
}




TInt32 SuiteFlywheelRamper::ToFfpn(double aVal)
{
    TInt32 s = (TInt32) ((aVal)*2147483648L);
    return(s);
}
*/

void SuiteFlywheelRamper::Test11()  // double<>FFPN
{
    //Log::Print("double >  ffpn  \n\n");
/*
    Log::Print(" 0x%.8lx  =  %f \n", 0x80000000L, BurgsMethod::ToDouble(0x80000000L));
    Log::Print(" 0x%.8lx  =  %f \n", 0x90000000L, BurgsMethod::ToDouble(0x90000000L));
    Log::Print(" 0x%.8lx  =  %f \n", 0xa0000000L, BurgsMethod::ToDouble(0xa0000000L));
    Log::Print(" 0x%.8lx  =  %f \n", 0xb0000000L, BurgsMethod::ToDouble(0xb0000000L));
    Log::Print(" 0x%.8lx  =  %f \n", 0xc0000000L, BurgsMethod::ToDouble(0xc0000000L));
    Log::Print(" 0x%.8lx  =  %f \n", 0xd0000000L, BurgsMethod::ToDouble(0xd0000000L));
    Log::Print(" 0x%.8lx  =  %f \n", 0xe0000000L, BurgsMethod::ToDouble(0xe0000000L));
    Log::Print(" 0x%.8lx  =  %f \n", 0xf0000000L, BurgsMethod::ToDouble(0xf0000000L));

    Log::Print(" 0x%.8lx  =  %f \n", 0x00000000L, BurgsMethod::ToDouble(0x00000000L));
    Log::Print(" 0x%.8lx  =  %f \n", 0x10000000L, BurgsMethod::ToDouble(0x10000000L));
    Log::Print(" 0x%.8lx  =  %f \n", 0x20000000L, BurgsMethod::ToDouble(0x20000000L));
    Log::Print(" 0x%.8lx  =  %f \n", 0x30000000L, BurgsMethod::ToDouble(0x30000000L));
    Log::Print(" 0x%.8lx  =  %f \n", 0x40000000L, BurgsMethod::ToDouble(0x40000000L));
    Log::Print(" 0x%.8lx  =  %f \n", 0x50000000L, BurgsMethod::ToDouble(0x50000000L));
    Log::Print(" 0x%.8lx  =  %f \n", 0x60000000L, BurgsMethod::ToDouble(0x60000000L));
    Log::Print(" 0x%.8lx  =  %f \n", 0x70000000L, BurgsMethod::ToDouble(0x70000000L));
    Log::Print(" 0x%.8lx  =  %f \n", 0x7fffffffL, BurgsMethod::ToDouble(0x7fffffffL));


    Log::Print("\n\nffpn > double\n\n");


    for (double i=-1; i<1; i+=0.125)
    {
        TInt32 ffpn = BurgsMethod::ToInt32(i);
        Log::Print("%f = 0x%.8lx \n", i, ffpn);
    }
*/


    double d = 0.125;
    TInt32 fp = BurgsMethod::ToInt32(d, 1);
    //Log::Print("\n\n\n%f = 0x%.8lx \n", d, fp);
    double d2 = BurgsMethod::ToDouble(fp, 1);
    //Log::Print("%f \n", d2);
    TEST(d==d2);


    d = 2.00;
    fp = BurgsMethod::ToInt32(d, 3);
    //Log::Print("\n\n\n%f = 0x%.8lx \n", d, fp);
    d2 = BurgsMethod::ToDouble(fp, 3);
    //Log::Print("%f  %x\n", d2, (TInt32)d2);
    TEST(d==d2);

    d = 2.50;
    fp = BurgsMethod::ToInt32(d, 3);
    //Log::Print("\n\n\n%f = 0x%.8lx \n", d, fp);
    d2 = BurgsMethod::ToDouble(fp, 3);
    //Log::Print("%f  %x\n", d2, (TInt32)d2);
    TEST(d==d2);


    //Log::Print("\n\n3.29 ...(536870912L) \n\n");
    for(double i=-3; i<3; i+=0.125)
    {
        TInt32 fixed = BurgsMethod::ToInt32(i, 3);
        //Log::Print("%.8f = 0x%.8lx \n", i, fixed);
        double dbl = BurgsMethod::ToDouble(fixed, 3);
        //Log::Print("0x%.8x = %.8f\n\n", fixed, dbl );
        TEST(dbl == i);
    }

    //Log::Print("\n\n1.31 ...(2147483648L) \n\n");

    for(double i=-1; i<1; i+=0.125)
    {
        TInt32 fixed = BurgsMethod::ToInt32(i, 1);
        //Log::Print("%.8f = 0x%.8lx \n", i, fixed);
        double dbl = BurgsMethod::ToDouble(fixed, 1);
        //Log::Print("0x%.8x = %.8f\n\n", fixed, dbl );
        TEST(dbl == i);
    }

/*
    for(double i=-0.875; i<1; i+=0.125)
    {
        TInt32 fixed = BurgsMethod::ToInt32(i);
        TInt32 inverted = (fixed^0xffffffffL)+1;
        double invDbl = BurgsMethod::ToDouble(inverted);
        //Log::Print("i=%.8f: 0x%.8x  inverted: 0x%.8x = %.8f\n", i, fixed, inverted, invDbl);
        TEST(invDbl == -i);
    }
*/

}


void SuiteFlywheelRamper::Test12() // ConvolutionModel algorithm
{
    //Log::Print("\n");

/*
    const TUint kCoeffsCount = 4;
    const TUint kSamplesInCount = 4;
    const TUint kSamplesInBytes = kSamplesInCount*4;
    const TUint kSamplesOutCount = kSamplesInCount+kCoeffsCount-1;
    const TUint kSamplesOutBytes = kSamplesOutCount*4;



    std::vector<TInt32> coeffs;
    coeffs.push_back(0x01000000);
    coeffs.push_back(0x02000000);
    coeffs.push_back(0x04000000);
    coeffs.push_back(0x08000000);

    Bws<kSamplesInBytes> samplesIn;
    Append32(samplesIn, 0x01000000);
    Append32(samplesIn, 0x02000000);
    Append32(samplesIn, 0x04000000);
    Append32(samplesIn, 0x08000000);

    Bws<kSamplesOutBytes> samplesOut;

    std::vector<TInt32> expectedSamplesOut;
    expectedSamplesOut.push_back(0x00020000);
    expectedSamplesOut.push_back(0x00080000);
    expectedSamplesOut.push_back(0x00180000);
    expectedSamplesOut.push_back(0x00400000);
    expectedSamplesOut.push_back(0x00600000);
    expectedSamplesOut.push_back(0x00800000);
    expectedSamplesOut.push_back(0x00800000);

    ConvolutionModel* conv = new ConvolutionModel(coeffs, 1, 1, 1);

    conv->Process(samplesIn, samplesOut, kSamplesOutCount);
    for (TUint i=0; i<kSamplesOutCount; i++)
    {
        TEST(FlywheelRamper::Int32(samplesOut, i*4) == expectedSamplesOut[i]);
    }
*/
}



void SuiteFlywheelRamper::Test13() // FeedbackModel algorithm
{
    Log::Print("\n");

    const TUint kCoeffsCount = 4;
    const TUint kSamplesInCount = 4;
    const TUint kSamplesInBytes = kSamplesInCount*4;
    const TUint kSamplesOutCount = kSamplesInCount+kCoeffsCount-1;
    const TUint kSamplesOutBytes = kSamplesOutCount*4;



    std::vector<TInt32> coeffs;
    coeffs.push_back(0x01000000);
    coeffs.push_back(0x02000000);
    coeffs.push_back(0x04000000);
    coeffs.push_back(0x08000000);

    Bws<kSamplesInBytes> samplesIn;
    Append32(samplesIn, 0x01000000);
    Append32(samplesIn, 0x02000000);
    Append32(samplesIn, 0x04000000);
    Append32(samplesIn, 0x08000000);

    Log::Print("0x01000000 = %f \n", BurgsMethod::ToDouble(0x01000000, 1));
    Log::Print("0x02000000 = %f \n", BurgsMethod::ToDouble(0x02000000, 1));
    Log::Print("0x04000000 = %f \n", BurgsMethod::ToDouble(0x04000000, 1));
    Log::Print("0x08000000 = %f \n", BurgsMethod::ToDouble(0x08000000, 1));


    Bws<kSamplesOutBytes> samplesOut;

    std::vector<TInt32> expectedSamplesOut;
    expectedSamplesOut.push_back(0x01000000);
    expectedSamplesOut.push_back(0x02020000);
    expectedSamplesOut.push_back(0x04080400);
    expectedSamplesOut.push_back(0x08181800);
    expectedSamplesOut.push_back(0x00406000);
    expectedSamplesOut.push_back(0x00614100);
    expectedSamplesOut.push_back(0x00830500);

    FeedbackModel* feedB = new FeedbackModel(coeffs, 8, 1, 1, 1);

    feedB->Process(samplesIn, samplesOut, kSamplesOutCount);
    for (TUint i=0; i<kSamplesOutCount; i++)
    {
        TEST(FlywheelRamper::Int32(samplesOut, i*4) == expectedSamplesOut[i]);
    }
}


void SuiteFlywheelRamper::Test14() // Burg Method profiling
{
    Log::Print("Burg Method profiling \n");
    Log::Print("Double: \n");

/*
    TUint maxDegree = 200;
    TUint maxLength = FlywheelRamper::Samples(192000, Jiffies::kPerMs*100); // 100ms at 192kHz


    {
    double* h = (double*) calloc (maxDegree, sizeof(double));
    double* per = (double*) calloc (maxLength, sizeof(double));
    double* pef = (double*) calloc (maxLength, sizeof(double));
    double* input = (double*) calloc (maxLength, sizeof(double));
    double* output = (double*) calloc (maxDegree+1, sizeof(double));

    for(TUint degree=10; degree<200; degree*=2)
    {
        for(TUint genMs=1; genMs<100; genMs*=2)
        {
            //Log::Print("degree=%d  genMs=%d\n", degree, genMs);
            TUint length = FlywheelRamper::Samples(192000, Jiffies::kPerMs*genMs);
            TUint startTime = Os::TimeInMs(iEnv.OsCtx());
            BurgsMethod::ARMaxEntropy(input, length, degree, output, h, per, pef);
            TUint endTime = Os::TimeInMs(iEnv.OsCtx());
            Log::Print("degree= %3d  genMs= %2d  %4dms  \n", degree, genMs, endTime-startTime);
        }
    }

    // free memory
    free(h);
    free(per);
    free(pef);
    free(input);
    free(output);
    }
*/

    Log::Print("Fixed point: \n");
/*
    {
    TInt32* fh = (TInt32*) calloc (maxDegree, sizeof(TInt32));
    TInt32* fper = (TInt32*) calloc (maxLength, sizeof(TInt32));
    TInt32* fpef = (TInt32*) calloc (maxLength, sizeof(TInt32));
    TInt32* finput = (TInt32*) calloc (maxLength, sizeof(TInt32));
    TInt32* foutput = (TInt32*) calloc (maxDegree+1, sizeof(TInt32));

    for(TUint degree=1; degree<10; degree++)
    {
        for(TUint genMs=1; genMs<10; genMs++)
        {
            //Log::Print("degree=%d  genMs=%d\n", degree, genMs);
            TUint length = FlywheelRamper::Samples(192000, Jiffies::kPerMs*genMs);
            TUint64 startTime = Os::TimeInUs(iEnv.OsCtx());
            BurgsMethod::ARMaxEntropy(finput, length, degree, foutput, fh, fper, fpef);
            BurgsMethod::ARMaxEntropy(finput, length, degree, foutput, fh, fper, fpef);
            BurgsMethod::ARMaxEntropy(finput, length, degree, foutput, fh, fper, fpef);
            BurgsMethod::ARMaxEntropy(finput, length, degree, foutput, fh, fper, fpef);
            BurgsMethod::ARMaxEntropy(finput, length, degree, foutput, fh, fper, fpef);
            BurgsMethod::ARMaxEntropy(finput, length, degree, foutput, fh, fper, fpef);
            BurgsMethod::ARMaxEntropy(finput, length, degree, foutput, fh, fper, fpef);
            BurgsMethod::ARMaxEntropy(finput, length, degree, foutput, fh, fper, fpef);
            TUint64 endTime = Os::TimeInUs(iEnv.OsCtx());
            Log::Print("degree= %3d  genMs= %2d  %8lldms  \n", degree, genMs, endTime-startTime);
        }
    }

    // free memory
    free(fh);
    free(fper);
    free(fpef);
    free(finput);
    free(foutput);
    }
*/


}


void SuiteFlywheelRamper::Test15() // Burg Method testing
{
    //Log::Print("size of double = %d \n", sizeof(double));

    std::vector<TInt32> coeffsOut;

 //6 a4  0  0  6 94  0  0  6 7d  0  0

    Bwh samplesIn(12);

    samplesIn.Append((TByte)0x06);
    samplesIn.Append((TByte)0xa4);
    samplesIn.Append((TByte)0x00);
    samplesIn.Append((TByte)0x00);

    samplesIn.Append((TByte)0x06);
    samplesIn.Append((TByte)0x94);
    samplesIn.Append((TByte)0x00);
    samplesIn.Append((TByte)0x00);

    samplesIn.Append((TByte)0x06);
    samplesIn.Append((TByte)0x7d);
    samplesIn.Append((TByte)0x00);
    samplesIn.Append((TByte)0x00);

    BurgsMethod::Coeffs(2, samplesIn, coeffsOut);
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

/////////////////////////////////////////////////////////////////

void TestFlywheelRamper(OpenHome::Environment& aEnv)
{
    Runner runner("Testing FlywheelRamper");
    runner.Add(new SuiteFlywheelRamper(aEnv));
    runner.Run();

}

/////////////////////////////////////////////////////////////////



