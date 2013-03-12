#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Media/Protocol/Protocol.h>
#include <OpenHome/Media/Protocol/ContentPls.h>
#include <OpenHome/Media/Msg.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/File.h>

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Media;

namespace OpenHome {
namespace Media {

class SuitePls : public Suite, private IProtocolSet, private IReaderSource
{
public:
    SuitePls();
    ~SuitePls();
private: // from Suite
    void Test();
private: // from IProtocolSet
    ProtocolStreamResult Stream(const Brx& aUri);
private: // from IReader
    void Read(Bwx& aBuffer);
    void ReadFlush();
    void ReadInterrupt();
private:
    void TestRecognise();
    void TestParse();
private:
    static const TUint kReadBufferSize = 1024 * 2;
    ContentProcessor* iProcessor;
    FileStream iFileStream;
    Srs<kReadBufferSize>* iReadBuffer;
    const TChar** iExpectedStreams;
    TUint iIndex;
    ProtocolStreamResult iNextResult;
    TUint iInterruptBytes;
    Bws<kReadBufferSize> iInterruptBuf;
    TBool iInterrupt;
};

} // namespace Media
} // namespace OpenHome

// SuitePls

SuitePls::SuitePls()
    : Suite("Pls tests")
    , iInterruptBytes(0)
    , iInterrupt(false)
{
    iProcessor = new ContentPls();
    iProcessor->Initialise(*this);
    iReadBuffer = new Srs<kReadBufferSize>(*this);
}

SuitePls::~SuitePls()
{
    delete iReadBuffer;
    delete iProcessor;
}

void SuitePls::Test()
{
    TestRecognise();
    TestParse();
}

ProtocolStreamResult SuitePls::Stream(const Brx& aUri)
{
    Brn expected(iExpectedStreams[iIndex++]);
    TEST(aUri == expected);
    return iNextResult;
}

void SuitePls::Read(Bwx& aBuffer)
{
    if (iInterrupt) {
        THROW(ReaderError);
    }
    if (iInterruptBuf.Bytes() != 0) {
        aBuffer.Append(iInterruptBuf);
        iInterruptBuf.SetBytes(0);
    }
    else {
        iFileStream.Read(aBuffer);
        if (iInterruptBytes != 0) {
            if (aBuffer.Bytes() < iInterruptBytes) {
                iInterruptBytes -= aBuffer.Bytes();
            }
            else {
                if (aBuffer.Bytes() != iInterruptBytes) {
                    Brn rem = aBuffer.Split(iInterruptBytes);
                    iInterruptBuf.Append(rem);
                    aBuffer.SetBytes(iInterruptBytes);
                }
                iInterruptBytes = 0;
                iInterrupt = true;
            }
        }
    }
}

void SuitePls::ReadFlush()
{
    iFileStream.ReadFlush();
}

void SuitePls::ReadInterrupt()
{
    iFileStream.ReadInterrupt();
}

void SuitePls::TestRecognise()
{
    // recognition by MIME type
    TEST(iProcessor->Recognise(Brx::Empty(), Brn("audio/x-scpls"), Brx::Empty()));

    // recognition fails for bad MIME
    TEST(!iProcessor->Recognise(Brx::Empty(), Brn("audio/foobar"), Brx::Empty()));

    static const TChar* kFile1 =
        "[playlist]\n"
        "NumberOfEntries=1\n"
        "\n"
        "File1=http://streamexample.com:80\n"
        "Title1=My Favorite Online Radio\n"
        "Length1=-1";
    // recognition by MIME type + content
    Brn content(kFile1);
    TEST(iProcessor->Recognise(Brx::Empty(), Brn("audio/x-scpls"), content));

    // recognition by content, no MIME
    TEST(iProcessor->Recognise(Brx::Empty(), Brx::Empty(), content));

    // good content, bad MIME
    TEST(!iProcessor->Recognise(Brx::Empty(), Brn("audio/foobar"), content));

    // bad content, bad MIME
    TEST(!iProcessor->Recognise(Brx::Empty(), Brn("audio/foobar"), Brn("playlist")));

    static const TChar* kFile2 =
        "[playlist]\r\n"
        "NumberOfEntries=1\r\n"
        "\r\n"
        "File1=http://streamexample.com:80\r\n"
        "Title1=My Favorite Online Radio\r\n"
        "Length1=-1";
    // content with dos line endings
    content.Set(kFile1);
    TEST(iProcessor->Recognise(Brx::Empty(), Brx::Empty(), content));
}

void SuitePls::TestParse()
{
    iInterruptBytes = 0;
    TUint64 offset = 0;

    // standard file with unix line endings
    static const TChar* kFile1 =
        "[playlist]\n"
        "NumberOfEntries=3\n"
        "\n"
        "File1=http://streamexample.com:80\n"
        "Title1=My Favorite Online Radio\n"
        "Length1=-1\n"
        "\n"
        "File2=http://example.com/song.mp3\n"
        "Title2=Remote MP3\n"
        "Length2=286\n"
        "\n"
        "File3=/home/myaccount/album.flac\n"
        "Title3=Local album\n"
        "Length3=3487\n"
        "\n"
        "Version=2";
    FileBrx file1(kFile1);
    iFileStream.SetFile(&file1);
    const char* expected1[] = {"http://streamexample.com:80",
        "http://example.com/song.mp3",
        "/home/myaccount/album.flac"};
    iExpectedStreams = expected1;
    iIndex = 0;
    iNextResult = EProtocolStreamSuccess;
    TEST(iProcessor->TryStream(*iReadBuffer, iFileStream.Bytes(), offset) == EProtocolStreamSuccess);
    TEST(iIndex == 3);

    // same file with dos line endings
    static const TChar* kFile2 =
        "[playlist]\r\n"
        "NumberOfEntries=3\r\n"
        "\r\n"
        "File1=http://streamexample.com:80\r\n"
        "Title1=My Favorite Online Radio\r\n"
        "Length1=-1\r\n"
        "\r\n"
        "File2=http://example.com/song.mp3\r\n"
        "Title2=Remote MP3\r\n"
        "Length2=286\r\n"
        "\r\n"
        "File3=/home/myaccount/album.flac\r\n"
        "Title3=Local album\r\n"
        "Length3=3487\r\n"
        "\r\n"
        "Version=2\r\n";
    
    iProcessor->Reset();
    FileBrx file2(kFile2);
    iFileStream.SetFile(&file2);
    iReadBuffer->ReadFlush();
    iIndex = 0;
    offset = 0;
    TEST(iProcessor->TryStream(*iReadBuffer, iFileStream.Bytes(), offset) == EProtocolStreamSuccess);
    TEST(iIndex == 3);

    // file with no line endings should fail to be processed
    static const TChar* kFile3 =
        "[playlist]"
        "NumberOfEntries=3"
        ""
        "File1=http://streamexample.com:80"
        "Title1=My Favorite Online Radio"
        "Length1=-1"
        ""
        "File2=http://example.com/song.mp3"
        "Title2=Remote MP3"
        "Length2=286"
        ""
        "File3=/home/myaccount/album.flac"
        "Title3=Local album"
        "Length3=3487"
        ""
        "Version=2";
    
    iProcessor->Reset();
    FileBrx file3(kFile3);
    iFileStream.SetFile(&file3);
    iReadBuffer->ReadFlush();
    iIndex = 0;
    offset = 0;
    TEST(iProcessor->TryStream(*iReadBuffer, iFileStream.Bytes(), offset) == EProtocolStreamErrorUnrecoverable);

    // processor passes on EProtocolStreamStopped errors
    iProcessor->Reset();
    file1.Seek(0);
    iFileStream.SetFile(&file1);
    iReadBuffer->ReadFlush();
    iIndex = 0;
    offset = 0;
    iNextResult = EProtocolStreamStopped;
    TEST(iProcessor->TryStream(*iReadBuffer, iFileStream.Bytes(), offset) == EProtocolStreamStopped);

    // interrupt mid-way through then resume
    iProcessor->Reset();
    iReadBuffer->ReadFlush();
    iFileStream.Seek(0);
    iIndex = 0;
    offset = 0;
    iNextResult = EProtocolStreamSuccess;
    static const TUint kInterruptBytes = 46; // part way through a File=[url] line
    iInterruptBytes = kInterruptBytes;
    TEST(iProcessor->TryStream(*iReadBuffer, iFileStream.Bytes(), offset) == EProtocolStreamErrorRecoverable);
    iInterrupt = false;
    offset = 0;
    TEST(iProcessor->TryStream(*iReadBuffer, iFileStream.Bytes() - kInterruptBytes, offset) == EProtocolStreamSuccess);
    TEST(iIndex == 3);
}



void TestContentProcessor()
{
    Runner runner("Content Processor tests\n");
    runner.Add(new SuitePls());
    runner.Run();
}
