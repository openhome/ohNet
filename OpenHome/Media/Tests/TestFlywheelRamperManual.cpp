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
    SuiteFlywheelRamper(TChar* aInputWavFilename, TChar* aOutputWavFilename);

private:
    // from SuiteUnitTest
    void Setup();
    void TearDown();
    void Test1();
    void Test2();

    void UpdateDataSize(TUint32 aDataSizeBytes);
    void WriteOutHeader();

    static void ConvertToBe16(const Brx& aBuf, Bwx& aBufBe);
    static void ConvertToBe24(const Brx& aBuf, Bwx& aBufBe);
    static void LogBuf(const Brx& aBuf);
    static TInt32 Int32(const Brx& aBuf, TUint aIndex);
    static void Append32(Bwx& aBuf, TInt32 aSample);


private:
    FlywheelRamper* iFlywheelRamper;
    IFile* iInputFile;
    FileStream* iOutputFile;
    Bws<44> iHeader;
    TUint32 iChunkSize;
    TUint16 iChannelCount;
    TUint32 iSampleRate;
    TUint16 iBitDepth;
    TUint32 iByteRate;
    TUint32 iSubChunk2Size;
    TUint iBytesPerSample;
};

//////////////////////////////////////////////////////////////

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



} // TestFlywheelRamper
} // Media
} // OpenHome

//////////////////////////////////////////////////////////////

using namespace OpenHome::Media::TestFlywheelRamper;


SuiteFlywheelRamper::SuiteFlywheelRamper(TChar* aInputWavFilename, TChar* aOutputWavFilename)
    :SuiteUnitTest("SuiteFlywheelRamper")
    ,iOutputFile(new FileStream())
{
    //AddTest(MakeFunctor(*this, &SuiteFlywheelRamper::Test1));
    AddTest(MakeFunctor(*this, &SuiteFlywheelRamper::Test2));

    try
    {
        iInputFile = IFile::Open(aInputWavFilename, eFileReadOnly);
    }
    catch(FileOpenError)
    {
        Log::Print("Failed to open input file \n");
        ASSERTS();
    }


    try
    {
        iOutputFile->OpenFile(aOutputWavFilename, eFileReadWrite);
    }
    catch(FileOpenError)
    {
        Log::Print("Failed to open output file \n");
        ASSERTS();
    }



    iInputFile->Read(iHeader);

    // Chunk size
    iChunkSize = 0;
    iChunkSize += iHeader[7];
    iChunkSize <<= 8;
    iChunkSize += iHeader[6];
    iChunkSize <<= 8;
    iChunkSize += iHeader[5];
    iChunkSize <<= 8;
    iChunkSize += iHeader[4];

    // channel count
    iChannelCount = 0;
    iChannelCount += iHeader[23];
    iChannelCount <<= 8;
    iChannelCount += iHeader[22];

    // sampleRate
    iSampleRate = 0;
    iSampleRate += iHeader[27];
    iSampleRate <<= 8;
    iSampleRate += iHeader[26];
    iSampleRate <<= 8;
    iSampleRate += iHeader[25];
    iSampleRate <<= 8;
    iSampleRate += iHeader[24];

    // byteRate
    iByteRate = 0;
    iByteRate += iHeader[31];
    iByteRate <<= 8;
    iByteRate += iHeader[30];
    iByteRate <<= 8;
    iByteRate += iHeader[29];
    iByteRate <<= 8;
    iByteRate += iHeader[28];


    // bitsPerSample
    iBitDepth = 0;
    iBitDepth += iHeader[35];
    iBitDepth <<= 8;
    iBitDepth += iHeader[34];

    if (iBitDepth==8)
    {
        iBytesPerSample = 1;
    }
    else if(iBitDepth==16)
    {
        iBytesPerSample = 2;
    }
    else if(iBitDepth==24)
    {
        iBytesPerSample = 3;
    }
    else
    {
        ASSERTS();
    }

    // iSubChunk2Size (little endian)
    iSubChunk2Size = 0;
    iSubChunk2Size += iHeader[43];
    iSubChunk2Size <<= 8;
    iSubChunk2Size += iHeader[42];
    iSubChunk2Size <<= 8;
    iSubChunk2Size += iHeader[41];
    iSubChunk2Size <<= 8;
    iSubChunk2Size += iHeader[40];

    Log::Print("channelCount=%d  sampleRate=%d  byteRate=%d  bitsPerSample=%d   iSubChunk2Size=%d \n", iChannelCount,  iSampleRate,  iByteRate,  iBitDepth, iSubChunk2Size);
}


void SuiteFlywheelRamper::Setup()
{
}


void SuiteFlywheelRamper::TearDown()
{
    delete iInputFile;
    delete iOutputFile;
}


void SuiteFlywheelRamper::Test1()
{
    Log::Print("\n");

    const TUint kRampMs = 1000; // 100ms
    const TUint kGenJiffies = Jiffies::kPerSecond/1; // 100ms

    auto ramper = new FlywheelRamper(kGenJiffies, kRampMs);

    // calculate bytes of audio samples required to generate a ramp
    TUint genJiffies = ramper->GenerationJiffies(); // should = kGenJiffies
    TUint64 genSampleBytes = FlywheelRamper::Bytes(iSampleRate, iChannelCount, genJiffies, iBytesPerSample);

    // calculate bytes required to accommodate ramp audio samples
    TUint64 rampJiffies = (TUint64)(kRampMs*Jiffies::kPerSecond/1000);
    TUint64 rampSampleBytes = FlywheelRamper::Bytes(iSampleRate, iChannelCount, rampJiffies, iBytesPerSample);

    WriteOutHeader();

    const TUint kAudioTestBlockSecs = 1;
    TUint audioTestBlockBytes = iByteRate*kAudioTestBlockSecs;
    Bwh buf(audioTestBlockBytes);
    TUint totalAudioDataBytes = iSubChunk2Size;

    TUint bufSplitIndex = buf.MaxBytes()-genSampleBytes;

    //Log::Print("bufSplitIndex=%d  buf.MaxBytes()=%d  genSampleBytes=%d\n", bufSplitIndex, buf.MaxBytes(), genSampleBytes);

    FormatConverter converter(*iOutputFile, iBitDepth);
    IPcmProcessor& proc = ramper->Ramp(converter, iSampleRate, iChannelCount);


    // append a ramp block after each AudioTestBlock
    // and write out the output file
    for (TUint i=0; i<=(iSubChunk2Size-audioTestBlockBytes);)
    {
        iInputFile->Read(buf); // read a test block
        iOutputFile->Write(buf); // write test block to output file

        //Log::Print("here 1  bufSplitIndex=%d  buf.Bytes()=%d \n\n", bufSplitIndex, buf.Bytes() );
        Brn genSamples(buf.Split(bufSplitIndex)); //
        Bwh genSamplesBe(genSamples.Bytes());

        proc.BeginBlock();
        if (iBitDepth==8)
        {
            Log::Print("8 bit\n");
            proc.ProcessFragment8(genSamples, iChannelCount);
        }
        else if (iBitDepth==16)
        {
            Log::Print("16 bit\n");
            ConvertToBe16(genSamples, genSamplesBe);
            proc.ProcessFragment16(genSamplesBe, iChannelCount);
        }
        else if (iBitDepth==24)
        {
            Log::Print("24 bit\n");
            ConvertToBe24(genSamples, genSamplesBe);
            proc.ProcessFragment24(genSamplesBe, iChannelCount);
        }
        else
        {
            Log::Print("unknown bit depth\n");
            ASSERTS();
        }
        proc.EndBlock();

        i += audioTestBlockBytes;
        buf.SetBytes(0);
        totalAudioDataBytes += rampSampleBytes; // increase output data by ramp block size
    }


    // write out any remaining block (end portion < audioTestBlockBytes)
    if (iInputFile->Tell()<iInputFile->Bytes())
    {
        iInputFile->Read(buf);
        iOutputFile->Write(buf);
    }

    UpdateDataSize(totalAudioDataBytes);
    WriteOutHeader();
}


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


void SuiteFlywheelRamper::UpdateDataSize(TUint32 aDataSizeBytes)
{
    iSubChunk2Size = aDataSizeBytes;
    iChunkSize = iSubChunk2Size+36;

    iHeader[4] = ((TUint8)iChunkSize);
    iHeader[5] = ((TUint8)(iChunkSize>>8));
    iHeader[6] = ((TUint8)(iChunkSize>>16));
    iHeader[7] = ((TUint8)(iChunkSize>>24));

    iHeader[40] = ((TUint8)(iSubChunk2Size));
    iHeader[41] = ((TUint8)(iSubChunk2Size>>8));
    iHeader[42] = ((TUint8)(iSubChunk2Size>>16));
    iHeader[43] = ((TUint8)(iSubChunk2Size>>24));

}


void SuiteFlywheelRamper::WriteOutHeader()
{
    iOutputFile->Seek(0);
    iOutputFile->Write(iHeader);
}


void SuiteFlywheelRamper::LogBuf(const Brx& aBuf)
{
    for(TUint x=0; x<aBuf.Bytes(); x++)
    {
        Log::Print("%x ", aBuf[x]);
    }
    Log::Print("\n");
}



void SuiteFlywheelRamper::Test2()
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


    Log::Print("\n\nUnit Test\n\n");
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
            Log::Print("sample=0x%.16llx  sampleInScaled=0x%.8lx  coeffs[%d]=0x%.8lx\n", sample, sampleInScaled, i, coeffs[i]);
        }

        sample >>= 32;

        Log::Print("samplesOut[%d]= 0x%.8lx , sample=0x%.8lx \n", j, Int32(samplesOut, j), (TInt32)sample);

        TEST( Int32(samplesOut, j) == (TInt32)sample );
        Log::Print("\n");
    }
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

FormatConverter::FormatConverter(IWriter& aWriterLe, TUint aBitDepth)
    :iWriterLe(aWriterLe)
    ,iBitDepth(aBitDepth)
{
    // converts 32bit  BigEndian to LittleEndian
    // also 32bits to 8/16/24 bits when apt
}


void FormatConverter::Write(TByte aValue)
{
    ASSERTS();
}


void FormatConverter::Write(const Brx& aBuffer)
{
    // aBuffer is always 4 bytes per sample
    // output may be 1, 2 or 3 (8/16/24bit) bytes per sample
    for(TUint i=0; i<aBuffer.Bytes();)
    {
        if (iBitDepth==24)
        {
            iWriterLe.Write(aBuffer[i+3]); //
            iWriterLe.Write(aBuffer[i+2]); //
            iWriterLe.Write(aBuffer[i+1]); //
        }
        else if (iBitDepth==16)
        {
            iWriterLe.Write(aBuffer[i+3]); //
            iWriterLe.Write(aBuffer[i+2]); //
        }
        else if (iBitDepth==8)
        {
            iWriterLe.Write(aBuffer[i+3]); //
        }
        else
        {
            ASSERTS();
        }

        i+=4;
    }
}


void FormatConverter::WriteFlush()
{

}


/////////////////////////////////////////////////////////////////


void TestFlywheelRamperManual(Net::Library& aLib, TChar* aArgv[])
{
    Runner runner("Testing FlywheelRamper");
    runner.Add(new SuiteFlywheelRamper(aArgv[1], aArgv[2]));
    runner.Run();

}

/////////////////////////////////////////////////////////////////



