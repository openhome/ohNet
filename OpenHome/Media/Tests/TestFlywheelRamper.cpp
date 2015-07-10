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
    void Setup();
    void TearDown();
    void Test1();

//    static void ConvertToBe16(const Brx& aBuf, Bwx& aBufBe);
//    static void ConvertToBe24(const Brx& aBuf, Bwx& aBufBe);
    static void LogBuf(const Brx& aBuf);
    static TInt32 Int32(const Brx& aBuf, TUint aIndex);
    static void Append32(Bwx& aBuf, TInt32 aSample);


private:
    FlywheelRamper* iFlywheelRamper;
};

//////////////////////////////////////////////////////////////
/*
class FormatConverter : public IWriter
{
public:
    FormatConverter(IWriter& aWriterLe, TUint aOutputBytesPerSample);

    // IWriter
    void Write(TByte aValue);
    void Write(const Brx& aBuffer);
    void WriteFlush();

private:
    IWriter& iWriterLe;
    TUint iBitDepth;
};
*/


} // TestFlywheelRamper
} // Media
} // OpenHome

//////////////////////////////////////////////////////////////

using namespace OpenHome::Media::TestFlywheelRamper;


SuiteFlywheelRamper::SuiteFlywheelRamper()
    :SuiteUnitTest("SuiteFlywheelRamper")
{
    AddTest(MakeFunctor(*this, &SuiteFlywheelRamper::Test1));
}


void SuiteFlywheelRamper::Setup()
{
}


void SuiteFlywheelRamper::TearDown()
{
}


/*
void SuiteFlywheelRamper::ConvertToBe24(const Brx& aBuf, Bwx& aBufBe)
{
    for (TUint i=0; i<aBuf.Bytes();)
    {
        aBufBe.Append(aBuf[i+2]);
        aBufBe.Append(aBuf[i+1]);
        aBufBe.Append(aBuf[i]);
        i+=3;
    }
}


void SuiteFlywheelRamper::ConvertToBe16(const Brx& aBuf, Bwx& aBufBe)
{
    for (TUint i=0; i<aBuf.Bytes();)
    {
        aBufBe.Append(aBuf[i+1]);
        aBufBe.Append(aBuf[i]);
        i+=2;
    }
}
*/

void SuiteFlywheelRamper::LogBuf(const Brx& aBuf)
{
    for(TUint x=0; x<aBuf.Bytes(); x++)
    {
        Log::Print("%x ", aBuf[x]);
    }
    Log::Print("\n");
}



void SuiteFlywheelRamper::Test1()  // ConvolutionModel
{
    const TUint kCoeffsCount = 6;

    std::vector<TInt32> coeffs;
    coeffs.push_back(0x1efb1a5e);
    coeffs.push_back(0xf13617f8);
    coeffs.push_back(0x17f8f136);
    coeffs.push_back(0xf1361efb);
    coeffs.push_back(0x1efb17f8);
    coeffs.push_back(0x1a5ef136);


    const TUint kSamplesInCount = 6;
    const TUint kSamplesInBytes = kSamplesInCount*4;
    const TUint kSamplesOutCount = kSamplesInCount+kCoeffsCount-1;
    const TUint kSamplesOutBytes = kSamplesOutCount*4;

    Bws<kSamplesInBytes> samplesIn;
    Append32(samplesIn, 0x00001fff);
    Append32(samplesIn, 0x00007f85);
    Append32(samplesIn, 0x0000505e);
    Append32(samplesIn, 0x0456f05e);
    Append32(samplesIn, 0xfefefefe);
    Append32(samplesIn, 0x000df35a);

    Bws<kSamplesOutBytes> samplesOut; // 11 32bit samples

    auto conv = new ConvolutionModel(coeffs);
    conv->Process(samplesIn, samplesOut, kSamplesOutCount);


    //Log::Print("\n\nUnit Test\n\n");
    //
    // sampleOut n = coeff(1)*sampleIn(n) + coeff(2)*sampleIn(n-1) + coeff(3)*sampleIn(n-2)...
    //
    // for n=1 to x (where x= num samples in + num coeffs -1):


    TInt sampleInIndex;
    TInt64 sample;
    TInt32 sampleInScaled;

    for(TUint j=0; j<kSamplesOutCount; j++)
    {
        sample = 0;

        for(TUint i=0; i<kCoeffsCount; i++)
        {
            sampleInScaled = 0;
            sampleInIndex = j-i;

            if ( (sampleInIndex>=0) && ((TUint)sampleInIndex<kSamplesInCount) )
            {
                TInt sampleIn = Int32(samplesIn, (TUint)sampleInIndex);
                sampleInScaled = (sampleIn>>8);
                //Log::Print("sampleInScaled=0x%.8lx  sampleIn=0x%.8lx \n", sampleInScaled, sampleIn);
            }

            sample += (TInt64)sampleInScaled * (TInt64)coeffs[i];
            //Log::Print("sample=0x%.16llx  sampleInScaled=0x%.8lx  coeffs[%d]=0x%.8lx\n", sample, sampleInScaled, i, coeffs[i]);
        }

        sample >>= 32;

        //Log::Print("samplesOut[%d]= 0x%.8lx , sample=0x%.8lx \n", j, Int32(samplesOut, j), (TInt32)sample);

        TEST( Int32(samplesOut, j) == (TInt32)sample );
        //Log::Print("\n");
    }

    delete conv;
}


void SuiteFlywheelRamper::Append32(Bwx& aBuf, TInt32 aSample)
{
    aBuf.Append((TByte)(aSample>>24));
    aBuf.Append((TByte)(aSample>>16));
    aBuf.Append((TByte)(aSample>>8));
    aBuf.Append((TByte)(aSample));
}

TInt32 SuiteFlywheelRamper::Int32(const Brx& aBuf, TUint aIndex)
{
    TUint i = aIndex*4;
    return( (TInt32) ((aBuf[i]<<24) + (aBuf[i+1]<<16) + (aBuf[i+2]<<8) + (aBuf[i+3])) );
}

/////////////////////////////////////////////////////////////////

void TestFlywheelRamper()
{
    Runner runner("Testing FlywheelRamper");
    runner.Add(new SuiteFlywheelRamper());
    runner.Run();

}

/////////////////////////////////////////////////////////////////



