#include <OpenHome/Types.h>
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
    SuiteFlywheelRamper();

private:
    // from SuiteUnitTest
    void Test1(); // ConvolutionModel random values
    void Test2(); // ConvolutionModel zero coeffs
    void Test3(); // ConvolutionModel positive coeff impulse
    void Test4(); // ConvolutionModel negative coeff impulse
    void Test5(); // ConvolutionModel positive sample half impulse
    void Test6(); // ConvolutionModel negative sample impulse

    void Test7(); // FeedbackModel random values
    void Test8(); // FeedbackModel negative sample impulse

    void Setup();
    void TearDown();

    static void LogBuf(const Brx& aBuf);
    static TInt32 Int32(const Brx& aBuf, TUint aIndex);
    static void Append32(Bwx& aBuf, TInt32 aSample);
};

//////////////////////////////////////////////////////////////

} // TestFlywheelRamper
} // Media
} // OpenHome

//////////////////////////////////////////////////////////////

using namespace OpenHome::Media::TestFlywheelRamper;


SuiteFlywheelRamper::SuiteFlywheelRamper()
    :SuiteUnitTest("SuiteFlywheelRamper")
{
    AddTest(MakeFunctor(*this, &SuiteFlywheelRamper::Test1));
    AddTest(MakeFunctor(*this, &SuiteFlywheelRamper::Test2));
    AddTest(MakeFunctor(*this, &SuiteFlywheelRamper::Test3));
    AddTest(MakeFunctor(*this, &SuiteFlywheelRamper::Test4));
    AddTest(MakeFunctor(*this, &SuiteFlywheelRamper::Test5));
    AddTest(MakeFunctor(*this, &SuiteFlywheelRamper::Test6));
    //AddTest(MakeFunctor(*this, &SuiteFlywheelRamper::Test7));
    //AddTest(MakeFunctor(*this, &SuiteFlywheelRamper::Test8));
}




void SuiteFlywheelRamper::Test1()  // ConvolutionModel
{
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
    Append32(samplesIn, 0x00001fff);
    Append32(samplesIn, 0x00007f85);
    Append32(samplesIn, 0x0000505e);
    Append32(samplesIn, 0x0456f05e);
    Append32(samplesIn, 0xfefefefe);
    Append32(samplesIn, 0x000df35a);

    Bws<kSamplesOutBytes> samplesOut;

    auto conv = new ConvolutionModel(coeffs, kCoeffScaling, kDataInScaling, kDataOutScaling);
    conv->Process(samplesIn, samplesOut, kSamplesOutCount);

    //
    // sampleOut n = coeff(1)*sampleIn(n) + coeff(2)*sampleIn(n-1) + coeff(3)*sampleIn(n-2)...
    //
    // for n=1 to x (where x= num samples in + num coeffs -1):

    for(TUint j=0; j<kSamplesOutCount; j++)
    {
        //Log::Print("Test cycle %d\n", j);
        TInt64 sample = 0;

        for(TUint i=0; i<kCoeffsCount; i++)
        {
            TInt32 sampleInScaled = 0;
            TInt sampleInIndex = j-i;

            if ( (sampleInIndex>=0) && ((TUint)sampleInIndex<kSamplesInCount) )
            {
                TInt32 sampleIn = FlywheelRamper::Int32(samplesIn, (TUint)sampleInIndex*4);
                sampleInScaled = (sampleIn>>8); // scale
            }

            sample += (TInt64)sampleInScaled * (TInt64)coeffs[i];
            //Log::Print("sampleIn=0x%.8lx * coeffs[%d]=0x%.8lx  =  sample=0x%.16llx  \n", sampleInScaled, i, coeffs[i], sample);
        }

        sample >>= 23; // descale

        //Log::Print("samplesOut[%d]= 0x%.8lx , sample=0x%.8lx \n\n", j, FlywheelRamper::Int32(samplesOut, j*4), (TInt32)sample);

        TEST( FlywheelRamper::Int32(samplesOut, j*4) == (TInt32)sample );

    }
    delete conv;
    //Log::Print("\n");
}


void SuiteFlywheelRamper::Test2()  // ConvolutionModel zero coeffs
{
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
}


void SuiteFlywheelRamper::Test3()  // ConvolutionModel positive coeff impulse
{
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
}


void SuiteFlywheelRamper::Test4()  // ConvolutionModel negative coeff impulse
{
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
}


void SuiteFlywheelRamper::Test5()  // ConvolutionModel positive sample half impulse
{
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
}


void SuiteFlywheelRamper::Test6()  // ConvolutionModel negative sample impulse
{
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
}


void SuiteFlywheelRamper::Test7()  // FeedbackModel
{
    const TUint kCoeffScaling = 1;
    const TUint kDataInScaling = 1;
    const TUint kDataOutScaling = 1;

    const TUint kCoeffsCount = 6;
    const TUint kSamplesInCount = 6;

    const TUint kSamplesInBytes = kSamplesInCount*4;
    const TUint kSamplesOutCount = kSamplesInCount+kCoeffsCount;
    const TUint kSamplesOutBytes = kSamplesOutCount*4;

    std::vector<TInt32> coeffs;
    coeffs.push_back(0x1efb1a5e);
    coeffs.push_back(0xf13617f8);
    coeffs.push_back(0x17f8f136);
    coeffs.push_back(0xf1361efb);
    coeffs.push_back(0x1efb17f8);
    coeffs.push_back(0x1a5ef136);

    Bws<kSamplesInBytes> samplesIn;
    Append32(samplesIn, 0x038f1fff);
    Append32(samplesIn, 0xe75b7f85);
    Append32(samplesIn, 0x0000505e);
    Append32(samplesIn, 0x0456f05e);
    Append32(samplesIn, 0xfefefefe);
    Append32(samplesIn, 0x000df35a);

    Bws<kSamplesOutBytes> samplesOut;

    auto feedback = new FeedbackModel(coeffs, kCoeffScaling, kDataInScaling, kDataOutScaling);
    feedback->Process(samplesIn, samplesOut, kSamplesOutCount);

    //Log::Print("\n\nUnit Test\n\n");
    //
    // sampleOut n = sampleIn(n) + coeff(1)*sampleOut(n-1) + coeff(2)*sampleOut(n-2)...
    //
    // for n=1 to x (where x= num samples in + num coeffs -1):


    for(TUint j=0; j<kSamplesOutCount; j++)
    {
        //Log::Print("Test cycle %d\n", j);
        TInt64 sample = 0;
        TInt32 sampleInScaled = 0;

        // add the input sample to the accumulator (if count is within range)
        if (j<kSamplesInCount)
        {
            TInt32 sampleIn = FlywheelRamper::Int32(samplesIn, j*4);
            sampleInScaled = (sampleIn>>8);
            sample += (TInt64)sampleInScaled;
        }

        for(TUint i=0; i<kCoeffsCount; i++)
        {
            TInt sampleOutIndex = j-1-i;

            if (sampleOutIndex>=0)
            {
                sample += (TInt64)FlywheelRamper::Int32(samplesOut, sampleOutIndex*4) * (TInt64)coeffs[i];
            }
            //Log::Print("sampleIn=0x%.8lx * coeffs[%d]=0x%.8lx  =  sample=0x%.16llx  \n", sampleInScaled, i, coeffs[i], sample);
        }

        sample >>= 32;

        //Log::Print("samplesOut[%d]= 0x%.8lx , sample=0x%.8lx \n\n", j, FlywheelRamper::Int32(samplesOut, j*4), (TInt32)sample);

        TEST( FlywheelRamper::Int32(samplesOut, j*4) == (TInt32)sample );
    }

    delete feedback;
}


void SuiteFlywheelRamper::Test8()  // FeedbackModel step response output
{
    const TUint kCoeffScaling = 2;
    const TUint kDataInScaling = 2;
    const TUint kDataOutScaling = 2;

    const TUint kCoeffsCount = 6;
    const TUint kSamplesInCount = 2;

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
/*
    Append32(samplesIn, 0x00000000);
    Append32(samplesIn, 0x00000000);
    Append32(samplesIn, 0x00000000);
    Append32(samplesIn, 0x00000000);
*/
    Bws<kSamplesOutBytes> samplesOut;

    auto feedback = new FeedbackModel(coeffs, kCoeffScaling, kDataInScaling, kDataOutScaling);
    feedback->Process(samplesIn, samplesOut, kSamplesOutCount);

    //Log::Print("\n\nUnit Test\n\n");
    //
    // sampleOut n = sampleIn(n) + coeff(1)*sampleOut(n-1) + coeff(2)*sampleOut(n-2)...
    //
    // for n=1 to x (where x= num samples in + num coeffs -1):


    for(TUint i=0; i<kSamplesOutCount; i++)
    {
        TInt32 sampleOut = FlywheelRamper::Int32(samplesOut, i*4);
        //sampleOut &= 0xffffff00L;

        if ( (i<kSamplesInCount) && (i<coeffs.size()) )
        {
            TInt32 coeff = coeffs[i];
            Log::Print("sampleOut=0x%.8lx  coeff=0x%.8lx\n", sampleOut, coeff);
            // output sample will be half the coeff value
            TEST( sampleOut == coeff );
        }
        else
        {
            // for cycle counts above the input sample count the output sample will be zero
            TEST( sampleOut == 0 );
        }

        //Log::Print("\n");
    }

    delete feedback;
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

void TestFlywheelRamper()
{
    Runner runner("Testing FlywheelRamper");
    runner.Add(new SuiteFlywheelRamper());
    runner.Run();

}

/////////////////////////////////////////////////////////////////



