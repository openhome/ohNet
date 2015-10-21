#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/OsWrapper.h>
#include <OpenHome/Net/Cpp/OhNet.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/FlywheelRamper.h>
#include <OpenHome/Private/File.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Media/Tests/Cdecl.h>
#include <OpenHome/Private/OptionParser.h>
#include <stdlib.h>


using namespace OpenHome::TestFramework;


using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::Media;


namespace OpenHome {
namespace Media {
namespace TestFlywheelRamperManual {


/////////////////////////////////////////////

class TestFWRManual : public INonCopyable
{
public:
    TestFWRManual(Net::Library& aLib, const Brx& aInputWavFilename, const Brx& aOutputWavFilename, TUint aDegree, TUint aGenMs, TUint aRampMs);
    void Run();

    static void LogBuf(const Brx& aBuf);

private:
    void UpdateDataSize(TUint32 aDataSizeBytes);
    void WriteOutHeader();
    void ProcessChannelFragment(IPcmProcessor& aProc, const Brx& aBuf, TUint aChannelCount);
    void ReadHeader();

    static TInt32 Int32(const Brx& aBuf, TUint aIndex);
    static void Append32(Bwx& aBuf, TInt32 aSample);
    static void ExtractChannelSamples(const Brx& aSamplesIn, Bwx& aChanSamplesOut, TUint aBytesPerSample, TUint aChannelCount, TUint aChannel);
    static void EndianSwitch(Bwx& aBuf, TUint aBytesPerSample);
    static void InterleaveChannelSamples(Bwx& aBuf, TUint aBytesPerSample, TUint aChannelCount);
    static void DeinterleaveChannelSamples(Bwx& aBuf, TUint aBytesPerSample, TUint aChannelCount);
    static void ReduceBitDepthBe(Bwx& aBuf, TUint aBytesPerSample);
    static void IncreaseBitDepthBe32(const Brx& aBufIn, Bwx& aBufOut, TUint iBytesPerSample);

private:
    Net::Library& iLib;
    IFile* iInputFile;
    FileStream* iOutputFile;
    TUint iDegree;
    TUint iGenMs;
    TUint iRampMs;

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

class PcmProcessorFwrMan: public IPcmProcessor, public INonCopyable
{
public:
    PcmProcessorFwrMan(Bwx& aBuf);

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
    virtual void ProcessSample32(const TByte* aSample, TUint aNumChannels) {ASSERTS();};
    virtual void Flush() {ASSERTS();};

private:
    Bwx& iBuf;
};


//////////////////////////////////////////////////////////////

class FormatConverter : public IWriter, public INonCopyable
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

using namespace OpenHome::Media::TestFlywheelRamperManual;


TestFWRManual::TestFWRManual(Net::Library& aLib, const Brx& aInputFilename, const Brx& aOutputFilename, TUint aDegree, TUint aGenMs, TUint aRampMs)
    :iLib(aLib)
    ,iOutputFile(new FileStream())
    ,iDegree(aDegree)
    ,iGenMs(aGenMs)
    ,iRampMs(aRampMs)
{
    try
    {
        Bwh inputFilename(aInputFilename);
        inputFilename.Grow(inputFilename.Bytes()+1);
        iInputFile = IFile::Open(inputFilename.PtrZ(), eFileReadOnly);
    }
    catch(FileOpenError)
    {
        Log::Print("Failed to open input file \n");
        ASSERTS();
    }

    try
    {
        if (aOutputFilename==Brx::Empty())
        {
            Bwh outputFilename(aInputFilename);
            outputFilename.Grow(outputFilename.Bytes()+16); // "-fwr-xx-yyy-zzz" = 15 chars + 1 for NULL terminator
            outputFilename.SetBytes(outputFilename.Bytes()-4); // ".wav"
            outputFilename.Append(Brn("-fwr-"));
            Ascii::AppendDec(outputFilename, iDegree); // xx
            outputFilename.Append("-");
            Ascii::AppendDec(outputFilename, iGenMs); // yyy
            outputFilename.Append("-");
            Ascii::AppendDec(outputFilename, iRampMs); // zzz
            outputFilename.Append(Brn(".wav"));
            iOutputFile->OpenFile(outputFilename.PtrZ(), eFileReadWrite);
        }
        else
        {
            Bwh outputFilename(aOutputFilename);
            outputFilename.Grow(outputFilename.Bytes()+1);
            iOutputFile->OpenFile(outputFilename.PtrZ(), eFileReadWrite);
        }
    }
    catch(FileOpenError)
    {
        Log::Print("Failed to open output file \n");
        ASSERTS();
    }

    ReadHeader();

    //Log::Print("channelCount=%d  sampleRate=%d  byteRate=%d  bitsPerSample=%d   iSubChunk2Size=%d \n", iChannelCount,  iSampleRate,  iByteRate,  iBitDepth, iSubChunk2Size);
}

void TestFWRManual::ReadHeader()
{
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
}


void TestFWRManual::Run()
{
    TUint genJiffies = (Jiffies::kPerMs * iGenMs);
    TUint rampJiffies = (Jiffies::kPerMs * iRampMs);

    // calculate bytes required to generate a ramp
    TUint genSamplesPerChan = FlywheelRamper::SampleCount(iSampleRate, genJiffies);
    TUint genBytesPerChan = genSamplesPerChan*iBytesPerSample;
    TUint genBytes = genBytesPerChan*iChannelCount;
    //Log::Print("genBytes=%d \n", genBytes);

    // calculate bytes required to accommodate ramp audio samples
    TUint rampSamplesPerChannel = FlywheelRamper::SampleCount(iSampleRate, rampJiffies);
    TUint rampBytesPerChannel = rampSamplesPerChannel*FlywheelRamper::kBytesPerSample;
    TUint rampBytes = rampBytesPerChannel*iChannelCount;
    //Log::Print("Test: rampBytes=%d \n", rampBytes);

    Bwh rampOutput(rampBytes);
    WriterBuffer writerFwr(rampOutput);
    //Log::Print("rampBytesPerChannel=%d  rampBytes=%d \n", rampBytesPerChannel, rampBytes);

    PcmProcessorFwrMan opProc(rampOutput);

    auto ramper = new FlywheelRamperManager(iLib.Env(), opProc, iChannelCount, genJiffies, rampJiffies);

    /////////////////

    WriteOutHeader();

    const TUint kAudioTestBlockSecs = 1;
    TUint audioTestBlockBytes = iByteRate*kAudioTestBlockSecs;
    Bwh buf(audioTestBlockBytes);
    TUint totalAudioDataBytes = 0;

    TUint bufSplitIndex = buf.MaxBytes()-genBytes;


    // append a ramp block after each AudioTestBlock
    // and write out the output file

    //for (TUint i=0; i<=(iSubChunk2Size-audioTestBlockBytes);)
    for (TUint i=0; i<audioTestBlockBytes;)
    {
        iInputFile->Read(buf); // read a test block
        iOutputFile->Write(buf); // write test block to output file

        Bwh genSamples(buf.Split(bufSplitIndex)); //

        EndianSwitch(genSamples, iBytesPerSample);  // change to big endian
        DeinterleaveChannelSamples(genSamples, iBytesPerSample, iChannelCount);

        Bwh genSamples32(genSamples.Bytes()*(4/iBytesPerSample)); //
        IncreaseBitDepthBe32(genSamples, genSamples32, iBytesPerSample);

        ramper->Ramp(genSamples32, iSampleRate); // generate the ramp

        // reduce the bit depth back to original format
        ReduceBitDepthBe(rampOutput, iBytesPerSample);

        // convert back to little endian format
        EndianSwitch(rampOutput, iBytesPerSample);

        iOutputFile->Write(rampOutput);

        i += audioTestBlockBytes;
        buf.SetBytes(0);
        totalAudioDataBytes += audioTestBlockBytes; // increase output data by ramp block size
        totalAudioDataBytes += rampOutput.Bytes(); // increase output data by ramp block size
    }


    // write out any remaining block (end portion < audioTestBlockBytes)
    if (iInputFile->Tell()<iInputFile->Bytes())
    {
        iInputFile->Read(buf);
        iOutputFile->Write(buf);
    }

    UpdateDataSize(totalAudioDataBytes);
    WriteOutHeader();

    delete ramper;
    delete iInputFile;
    delete iOutputFile;
}



/*
void TestFWRManual::Run()
{
    TUint genJiffies = (Jiffies::kPerMs * iGenMs);
    TUint rampJiffies = (Jiffies::kPerMs * iRampMs);

    auto ramper = new FlywheelRamper(iDegree, genJiffies, rampJiffies);

    // calculate bytes required to generate a ramp
    TUint genSamplesPerChan = FlywheelRamper::SampleCount(iSampleRate, genJiffies);
    TUint genBytesPerChan = genSamplesPerChan*iBytesPerSample;
    TUint genBytes = genBytesPerChan*iChannelCount;
    //Log::Print("genBytes=%d \n", genBytes);

    // calculate bytes required to accommodate ramp audio samples
    TUint rampSamplesPerChannel = FlywheelRamper::SampleCount(iSampleRate, rampJiffies);
    TUint rampBytesPerChannel = rampSamplesPerChannel*FlywheelRamper::kBytesPerSample;
    TUint rampBytes = rampBytesPerChannel*iChannelCount;
    //Log::Print("rampBytes=%d \n", rampBytes);

    Bwh rampOutput(rampBytes);
    WriterBuffer writerFwr(rampOutput);
    //Log::Print("rampBytesPerChannel=%d  rampBytes=%d \n", rampBytesPerChannel, rampBytes);


    /////////////////

    WriteOutHeader();

    const TUint kAudioTestBlockSecs = 1;
    TUint audioTestBlockBytes = iByteRate*kAudioTestBlockSecs;
    Bwh buf(audioTestBlockBytes);
    //TUint totalAudioDataBytes = iSubChunk2Size;
    TUint totalAudioDataBytes = 0;

    TUint bufSplitIndex = buf.MaxBytes()-genBytes;

    //Log::Print("bufSplitIndex=%d  buf.MaxBytes()=%d  genBytes=%d\n", bufSplitIndex, buf.MaxBytes(), genBytes);

    IPcmProcessor& proc = ramper->Ramp(writerFwr, iSampleRate);

    // append a ramp block after each AudioTestBlock
    // and write out the output file
    //for (TUint i=0; i<=(iSubChunk2Size-audioTestBlockBytes);)
    for (TUint i=0; i<audioTestBlockBytes;)
    {
        iInputFile->Read(buf); // read a test block
        iOutputFile->Write(buf); // write test block to output file

        //Log::Print("bufSplitIndex=%d  buf.Bytes()=%d \n\n", bufSplitIndex, buf.Bytes() );
        Bwh genSamples(buf.Split(bufSplitIndex)); //

        //Log::Print("iBytesPerSample=%d  bufSplitIndex=%d  sampleStartIndex=%d genSamples.Bytes()=%d  genSamples=%d\n", iBytesPerSample, bufSplitIndex, bufSplitIndex/iBytesPerSample, genSamples.Bytes(), genSamples.Bytes()/4);

        EndianSwitch(genSamples, iBytesPerSample);  // change to big endian
        Bwh genChanSamples(genSamples.Bytes()/iChannelCount);


        for(TUint i=0; i<iChannelCount; i++)
        {
            ExtractChannelSamples(genSamples, genChanSamples, iBytesPerSample, iChannelCount, i);
            //Log::Print("genSamplesBe.Bytes()=%d  genChanSamples.Bytes()=%d\n", genSamples.Bytes(), genChanSamples.Bytes());
            ProcessChannelFragment(proc, genChanSamples, 1);
        }


        // reduce the bit depth back to original format
        ReduceBitDepthBe(rampOutput, iBytesPerSample);

        // convert back to little endian format
        EndianSwitch(rampOutput, iBytesPerSample);

        // interleave the samples for output
        InterleaveChannelSamples(rampOutput, iBytesPerSample, iChannelCount);

        iOutputFile->Write(rampOutput);

        i += audioTestBlockBytes;
        buf.SetBytes(0);
        totalAudioDataBytes += audioTestBlockBytes; // increase output data by ramp block size
        //Log::Print("totalAudioDataBytes=%d  rampSamplesReduced.Bytes()=%d \n", totalAudioDataBytes, rampOutput.Bytes());
        totalAudioDataBytes += rampOutput.Bytes(); // increase output data by ramp block size
        //Log::Print("totalAudioDataBytes=%d   \n", totalAudioDataBytes);
    }

    //Log::Print("Time = %d", Os::TimeNow());

    // write out any remaining block (end portion < audioTestBlockBytes)
    if (iInputFile->Tell()<iInputFile->Bytes())
    {
        iInputFile->Read(buf);
        iOutputFile->Write(buf);
    }

    UpdateDataSize(totalAudioDataBytes);
    WriteOutHeader();

    delete ramper;
    delete iInputFile;
    delete iOutputFile;
}
*/

void TestFWRManual::ProcessChannelFragment(IPcmProcessor& aProc, const Brx& aBuf, TUint aChannelCount)
{
    aProc.BeginBlock();
    if (iBitDepth==8)
    {
        aProc.ProcessFragment8(aBuf, aChannelCount);
    }
    else if (iBitDepth==16)
    {
        aProc.ProcessFragment16(aBuf, aChannelCount);
    }
    else if (iBitDepth==24)
    {
        aProc.ProcessFragment24(aBuf, aChannelCount);
    }
    else
    {
        ASSERTS();
    }
    aProc.EndBlock();
}


void TestFWRManual::ExtractChannelSamples(const Brx& aBuf, Bwx& aBufChan, TUint aBytesPerSample, TUint aChannelCount, TUint aChannel)
{
    //Log::Print("ExtractChannelSamples\n");
    aBufChan.SetBytes(0);
    TUint byteInc = aBytesPerSample*aChannelCount;
    TUint startByteIndex = aBytesPerSample*aChannel;

    for(TUint i=startByteIndex; i<aBuf.Bytes(); i+=byteInc)
    {
        for(TUint j=0; j<aBytesPerSample; j++)
        {
            TUint k = i+j;
            //Log::Print("%d ", k);
            aBufChan.Append(aBuf[k]);
        }

        //Log::Print("\n");

    }


    ASSERT(aBufChan.Bytes()==aBuf.Bytes()/aChannelCount);
}


void TestFWRManual::DeinterleaveChannelSamples(Bwx& aBuf, TUint aBytesPerSample, TUint aChannelCount)
{
    //Log::Print("ExtractChannelSamples\n");
    Bwh buf(aBuf);

    aBuf.SetBytes(0);

    for(TUint chan=0; chan<aChannelCount; chan++)
    {
        TUint byteInc = aBytesPerSample*aChannelCount;
        TUint startByteIndex = aBytesPerSample*chan;

        for(TUint i=startByteIndex; i<buf.Bytes(); i+=byteInc)
        {
            for(TUint j=0; j<aBytesPerSample; j++)
            {
                TUint k = i+j;
                //Log::Print("%d ", k);
                aBuf.Append(buf[k]);
            }
        }
    }

    ASSERT(buf.Bytes()==aBuf.Bytes());
}


void TestFWRManual::InterleaveChannelSamples(Bwx& aBuf, TUint aBytesPerSample, TUint aChannelCount)
{
    Bwh buf(aBuf);
    aBuf.SetBytes(0);

    TUint bytesPerChan = buf.Bytes()/aChannelCount;

    for(TUint i=0; i<bytesPerChan; i+=aBytesPerSample)
    {
        for(TUint j=0; j<aChannelCount; j++)
        {
            for(TUint k=0; k<aBytesPerSample; k++)
            {
                aBuf.Append(buf[i+(j*bytesPerChan)+k]);
            }
        }
    }
}


void TestFWRManual::IncreaseBitDepthBe32(const Brx& aBufIn, Bwx& aBufOut, TUint iBytesPerSample)
{
    aBufOut.SetBytes(0);
    TUint padByteCount = (4-iBytesPerSample);

    for(TUint i=0; i<aBufIn.Bytes(); )
    {
        for(TUint j=0; j<iBytesPerSample; j++)
        {
            aBufOut.Append(aBufIn[i+j]);
        }

        for(TUint k=0; k<padByteCount; k++)
        {
            aBufOut.Append((TByte)0);
        }

        i+=iBytesPerSample;
    }
}


void TestFWRManual::ReduceBitDepthBe(Bwx& aBuf, TUint aBytesPerSample)
{
    // reduce (Big Endian samples) from 32bits to specified bit depth (aBytesPerSample)
    Bwh buf(aBuf);
    aBuf.SetBytes(0);

    for(TUint i=0; i<buf.Bytes(); )
    {
        for(TUint j=0; j<aBytesPerSample; j++)
        {
            aBuf.Append(buf[i+j]);
        }
        i+=4;
    }
}


void TestFWRManual::EndianSwitch(Bwx& aBuf, TUint aBytesPerSample)
{
    Bwh buf(aBuf);
    aBuf.SetBytes(0);

    if (aBytesPerSample>1)
    {
        for (TUint i=0; i<buf.Bytes();)
        {
            for (TInt j=(aBytesPerSample-1); j>=0; j--)
            {
                aBuf.Append(buf[i+j]);
            }

            i+=aBytesPerSample;
        }
    }
}




void TestFWRManual::UpdateDataSize(TUint32 aDataSizeBytes)
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


void TestFWRManual::WriteOutHeader()
{
    iOutputFile->Seek(0);
    iOutputFile->Write(iHeader);
}


void TestFWRManual::LogBuf(const Brx& aBuf)
{
    for(TUint x=0; x<aBuf.Bytes(); x++)
    {
        Log::Print("%x ", aBuf[x]);
    }
    //Log::Print("\n");
}


void TestFWRManual::Append32(Bwx& aBuf, TInt32 aSample)
{
    aBuf.Append((TByte)(aSample>>24));
    aBuf.Append((TByte)(aSample>>16));
    aBuf.Append((TByte)(aSample>>8));
    aBuf.Append((TByte)(aSample));
}

TInt32 TestFWRManual::Int32(const Brx& aBuf, TUint aIndex)
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


void FormatConverter::Write(TByte /*aValue*/)
{
    ASSERTS();
}


void FormatConverter::Write(const Brx& aBuffer)
{
    // aBuffer is always 4 bytes per sample
    // output may be 1, 2 or 3 (8/16/24bit) bytes per sample

    TestFWRManual::LogBuf(aBuffer);

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

PcmProcessorFwrMan::PcmProcessorFwrMan(Bwx& aBuf)
    :iBuf(aBuf)
{

}


void PcmProcessorFwrMan::ProcessFragment32(const Brx& aData, TUint aNumChannels)
{
    //ASSERT(aNumChannels==1);
    iBuf.Append(aData);
}

/////////////////////////////////////////////////////////////////


int CDECL main(int aArgc, TChar* aArgv[])
{
    std::vector<Brn> args;

    for(int i=0; i<aArgc; i++)
    {
        args.push_back(Brn(aArgv[i]));
    }

    OptionParser parser;

    OptionString optionInput("-i", "--input", Brn(""), "name of input file");
    parser.AddOption(&optionInput);

    OptionString optionOutput("-o", "--output", Brn(""), "name of output file");
    parser.AddOption(&optionOutput);

    OptionUint optionDegree("-d", "--degree", 10, "degree of filter (number of taps)");
    parser.AddOption(&optionDegree);

    OptionUint optionGenMs("-g", "--gen", 100, "generation data length in ms");
    parser.AddOption(&optionGenMs);

    OptionUint optionRampMs("-r", "--ramp", 100, "ramp length in ms");
    parser.AddOption(&optionRampMs);

    if (!parser.Parse(args) || parser.HelpDisplayed()) {
        return(0);
    }

    ASSERT(optionDegree.Value()<100);
    ASSERT(optionGenMs.Value()<1000);
    ASSERT(optionRampMs.Value()<1000);


    InitialisationParams* initParams = Net::InitialisationParams::Create();
    Net::Library* lib = new Net::Library(initParams);

    auto test = new TestFWRManual(*lib, optionInput.Value(), optionOutput.Value(), optionDegree.Value(), optionGenMs.Value(), optionRampMs.Value());
    test->Run();
    //Log::Print("time = %d \n", Os::TimeInMs(lib->Env().OsCtx()));

    delete test;
    delete lib;

}

/////////////////////////////////////////////////////////////////



