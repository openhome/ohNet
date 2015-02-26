#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Media/Protocol/Protocol.h>
#include <OpenHome/Av/Radio/ContentProcessorFactory.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/File.h>

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Av;
using namespace OpenHome::Media;

namespace OpenHome {
namespace Av {

class SuiteContent : public Suite, protected IProtocolSet, protected IProtocolReader
{
protected:
    SuiteContent(const TChar* aName);
    ~SuiteContent();
protected: // from IProtocolSet
    ProtocolStreamResult Stream(const Brx& aUri) override;
private: // from IProtocolReader
    Brn Read(TUint aBytes) override;
    Brn ReadUntil(TByte aSeparator) override;
    void ReadFlush() override;
    void ReadInterrupt() override;
    Brn ReadRemaining() override;
protected:
    static const TUint kReadBufferSize = 1024 * 8;
    ContentProcessor* iProcessor;
    FileStream iFileStream;
    Srs<kReadBufferSize>* iReadBuffer;
    const TChar** iExpectedStreams;
    TUint iIndex;
    ProtocolStreamResult iNextResult;
    TUint iInterruptBytes;
    Bws<kReadBufferSize> iInterruptBuf;
    Bws<kReadBufferSize> iInterruptReturnBuf;
    TBool iInterrupt;
};
    
class SuitePls : public SuiteContent
{
public:
    SuitePls();
private: // from Suite
    void Test() override;
private:
    void TestRecognise();
    void TestParse();
};

class SuiteM3u : public SuiteContent
{
public:
    SuiteM3u();
private: // from Suite
    void Test() override;
private:
    void TestRecognise();
    void TestParse();
};

class SuiteM3uX : public SuiteContent
{
public:
    SuiteM3uX();
private: // from Suite
    void Test() override;
private:
    void TestRecognise();
    void TestParse();
};

class SuiteOpml : public SuiteContent
{
public:
    SuiteOpml();
private: // from Suite
    void Test() override;
private:
    void TestRecognise();
    void TestParse();
private: // from IProtocolSet
    ProtocolStreamResult Stream(const Brx& aUri) override;
private:
    TUint iNumFails;
}; 

class SuiteAsx : public SuiteContent
{
public:
    SuiteAsx();
private: // from Suite
    void Test() override;
private:
    void TestRecognise();
    void TestParse();
private: // from IProtocolSet
    ProtocolStreamResult Stream(const Brx& aUri) override;
private:
    TUint iNumFails;
};

} // namespace Media
} // namespace OpenHome

// SuiteContent

SuiteContent::SuiteContent(const TChar* aName)
    : Suite(aName)
    , iProcessor(NULL)
    , iInterruptBytes(0)
    , iInterrupt(false)
{
    iReadBuffer = new Srs<kReadBufferSize>(iFileStream);
}

SuiteContent::~SuiteContent()
{
    delete iReadBuffer;
    delete iProcessor;
}

ProtocolStreamResult SuiteContent::Stream(const Brx& aUri)
{
    Brn expected(iExpectedStreams[iIndex++]);
    TEST(aUri == expected);
    if (aUri != expected) {
        Print("\nERROR: Expected ");
        Print(expected);
        Print(", Got ");
        Print(aUri);
        Print("\n");
    }
    return iNextResult;
}

Brn SuiteContent::Read(TUint aBytes)
{
    Brn buf;
    if (iInterrupt) {
        THROW(ReaderError);
    }
    if (iInterruptBuf.Bytes() == 0) {
        buf.Set(iReadBuffer->Read(aBytes));
        if (iInterruptBytes != 0) {
            if (buf.Bytes() <= iInterruptBytes) {
                iInterruptBytes -= buf.Bytes();
                iInterrupt = (iInterruptBytes == 0);
            }
            else {
                Brn rem = buf.Split(buf.Bytes() - iInterruptBytes);
                iInterruptBuf.Replace(rem);
                iInterruptBytes = 0;
                iInterrupt = true;
            }
        }
    }
    else {
        if (iInterruptBuf.Bytes() > aBytes) {
            Brn rem = iInterruptBuf.Split(aBytes);
            iInterruptReturnBuf.Replace(iInterruptBuf);
            buf.Set(iInterruptReturnBuf);
            iInterruptBuf.Replace(rem);
        }
        else if (iInterruptBuf.Bytes() == aBytes) {
            buf.Set(iInterruptBuf);
            iInterruptBuf.SetBytes(0);
        }
        else {
            buf.Set(iReadBuffer->Read(aBytes - iInterruptBuf.Bytes()));
            iInterruptBuf.Append(buf);
            buf.Set(iInterruptBuf);
            iInterruptBuf.SetBytes(0);
        }
    }
    return buf;
}

Brn SuiteContent::ReadUntil(TByte aSeparator)
{
    Brn buf;
    if (iInterrupt) {
        THROW(ReaderError);
    }
    if (iInterruptBuf.Bytes() == 0) {
        buf.Set(iReadBuffer->ReadUntil(aSeparator));
        if (iInterruptBytes != 0) {
            if (iInterruptBytes > buf.Bytes()) {
                iInterruptBytes -= buf.Bytes();
            }
            else {
                iInterruptBuf.Replace(buf);
                //iInterruptBuf.Append(aSeparator);
                iInterruptBytes = 0;
                iInterrupt = true;
                THROW(ReaderError);
            }
        }
    }
    else {
        iInterruptReturnBuf.Replace(iInterruptBuf);
        buf.Set(iInterruptReturnBuf);
        iInterruptBuf.SetBytes(0);
/*
        if (Ascii::Contains(iInterruptBuf, aSeparator)) {
            Parser parser(iInterruptBuf);
            iInterruptReturnBuf.Replace(parser.Next(aSeparator));
            //iInterruptBuf.Append(aSeparator);
            buf.Set(iInterruptReturnBuf);
            iInterruptBuf.Replace(parser.Remaining());
        }
        else {
            buf.Set(iReadBuffer->ReadUntil(aSeparator));
            iInterruptReturnBuf.Replace(iInterruptBuf);
            iInterruptReturnBuf.Append(buf);
            buf.Set(iInterruptReturnBuf);
            iInterruptBuf.SetBytes(0);
        }*/
    }
    return buf;
}

void SuiteContent::ReadFlush()
{
    iInterruptBuf.SetBytes(0);
    iReadBuffer->ReadFlush();
}

void SuiteContent::ReadInterrupt()
{
    iReadBuffer->ReadInterrupt();
}

Brn SuiteContent::ReadRemaining()
{
    if (iInterruptBuf.Bytes() > 0) {
        return Brx::Empty();
        /*iInterruptReturnBuf.Replace(iInterruptBuf);
        iInterruptBuf.SetBytes(0);
        return Brn(iInterruptReturnBuf);*/
    }
    return iReadBuffer->Snaffle();
}



// SuitePls

SuitePls::SuitePls()
    : SuiteContent("Pls tests")
{
    iProcessor =    ContentProcessorFactory::NewPls();
    iProcessor->Initialise(*this);
}

void SuitePls::Test()
{
    TestRecognise();
    TestParse();
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
    TEST(iProcessor->Recognise(Brx::Empty(), Brn("audio/foobar"), content));

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
    content.Set(kFile2);
    TEST(iProcessor->Recognise(Brx::Empty(), Brx::Empty(), content));
}

void SuitePls::TestParse()
{
    iInterruptBytes = 0;

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
    TEST(iProcessor->Stream(*this, iFileStream.Bytes()) == EProtocolStreamSuccess);
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
    TEST(iProcessor->Stream(*this, iFileStream.Bytes()) == EProtocolStreamSuccess);
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
    TEST(iProcessor->Stream(*this, iFileStream.Bytes()) == EProtocolStreamErrorUnrecoverable);

    // processor passes on EProtocolStreamStopped errors
    iProcessor->Reset();
    file1.Seek(0);
    iFileStream.SetFile(&file1);
    iReadBuffer->ReadFlush();
    iIndex = 0;
    iNextResult = EProtocolStreamStopped;
    TEST(iProcessor->Stream(*this, iFileStream.Bytes()) == EProtocolStreamStopped);

    // interrupt mid-way through then resume
    iProcessor->Reset();
    iReadBuffer->ReadFlush();
    iFileStream.Seek(0);
    iIndex = 0;
    iNextResult = EProtocolStreamSuccess;
    static const TUint kInterruptBytes = 46; // part way through a File=[url] line
    iInterruptBytes = kInterruptBytes;
    TEST(iProcessor->Stream(*this, iFileStream.Bytes()) == EProtocolStreamErrorRecoverable);
    iInterrupt = false;
    TEST(iProcessor->Stream(*this, iFileStream.Bytes() - 30) == EProtocolStreamSuccess); // 30 chars in complete lines read before interruption
    TEST(iIndex == 3);
}


// SuiteM3u

SuiteM3u::SuiteM3u()
    : SuiteContent("M3u tests")
{
    iProcessor = ContentProcessorFactory::NewM3u();
    iProcessor->Initialise(*this);
}

void SuiteM3u::Test()
{
    TestRecognise();
    TestParse();
}

void SuiteM3u::TestRecognise()
{
    // recognition by MIME type
    TEST(iProcessor->Recognise(Brx::Empty(), Brn("audio/x-mpegurl"), Brx::Empty()));
    TEST(iProcessor->Recognise(Brx::Empty(), Brn("audio/mpegurl"), Brx::Empty()));

    // recognition fails for bad MIME
    TEST(!iProcessor->Recognise(Brx::Empty(), Brn("audio/foobar"), Brx::Empty()));

    static const TChar* kFile1 =
        "#EXTM3U\n"
        "\n"
        "#EXTINF:123,Sample title\n"
        "C:\\Documents and Settings\\I\\My Music\\Sample.mp3\n";
    // recognition by MIME type + content
    Brn content(kFile1);
    TEST(iProcessor->Recognise(Brx::Empty(), Brn("audio/mpegurl"), content));

    // recognition by content, no MIME
    TEST(iProcessor->Recognise(Brx::Empty(), Brx::Empty(), content));

    // good content, bad MIME
    TEST(iProcessor->Recognise(Brx::Empty(), Brn("audio/foobar"), content));

    // bad content, bad MIME
    TEST(!iProcessor->Recognise(Brx::Empty(), Brn("audio/foobar"), Brn("playlist")));

    static const TChar* kFile2 =
        "#EXTM3U\r\n"
        "\r\n"
        "#EXTINF:123,Sample title\r\n"
        "C:\\Documents and Settings\\I\\My Music\\Sample.mp3\r\n";
    // content with dos line endings
    content.Set(kFile2);
    TEST(iProcessor->Recognise(Brx::Empty(), Brx::Empty(), content));


    // Master Playlist M3U with #EXT-X- tags (i.e., an HLS M3U, aka M3UX for our purposes).
    static const TChar* kFile3 =
        "#EXTM3U\n"
        "#EXT-X-STREAM-INF:BANDWIDTH=1280000,AVERAGE-BANDWIDTH=1000000\n"
        "http://example.com/low.m3u8\n"
        "#EXT-X-STREAM-INF:BANDWIDTH=2560000,AVERAGE-BANDWIDTH=2000000\n"
        "http://example.com/mid.m3u8\n"
        "#EXT-X-STREAM-INF:BANDWIDTH=7680000,AVERAGE-BANDWIDTH=6000000\n"
        "http://example.com/hi.m3u8\n"
        "#EXT-X-STREAM-INF:BANDWIDTH=65000,CODECS=\"mp4a.40.5\"\n"
        "http://example.com/audio-only.m3u8\n";
    content.Set(kFile3);
    TEST(!iProcessor->Recognise(Brx::Empty(), Brx::Empty(), content));
}

void SuiteM3u::TestParse()
{
    iInterruptBytes = 0;

    // standard file with unix line endings
    static const TChar* kFile1 =
        "#EXTM3U\n"
        "\n"
        "#EXTINF:123,Sample title\n"
        "C:\\Documents and Settings\\I\\My Music\\Sample.mp3\n"
        "\n"
        "#EXTINF:321,Example title\n"
        "C:\\Documents and Settings\\I\\My Music\\Greatest Hits\\Example.ogg";
    FileBrx file1(kFile1);
    iFileStream.SetFile(&file1);
    const char* expected1[] = {"C:\\Documents and Settings\\I\\My Music\\Sample.mp3",
        "C:\\Documents and Settings\\I\\My Music\\Greatest Hits\\Example.ogg"};
    iExpectedStreams = expected1;
    iIndex = 0;
    iNextResult = EProtocolStreamSuccess;
    TEST(iProcessor->Stream(*this, iFileStream.Bytes()) == EProtocolStreamSuccess);
    TEST(iIndex == 2);

    // same file with dos line endings
    static const TChar* kFile2 =
        "#EXTM3U\r\n"
        "\r\n"
        "#EXTINF:123,Sample title\r\n"
        "C:\\Documents and Settings\\I\\My Music\\Sample.mp3\r\n"
        "\r\n"
        "#EXTINF:321,Example title\r\n"
        "C:\\Documents and Settings\\I\\My Music\\Greatest Hits\\Example.ogg\r\n";
    
    iProcessor->Reset();
    FileBrx file2(kFile2);
    iFileStream.SetFile(&file2);
    iReadBuffer->ReadFlush();
    iIndex = 0;
    TEST(iProcessor->Stream(*this, iFileStream.Bytes()) == EProtocolStreamSuccess);
    TEST(iIndex == 2);

    // file with no line endings should fail to be processed
    static const TChar* kFile3 =
        "#EXTM3U"
        ""
        "#EXTINF:123,Sample title"
        "C:\\Documents and Settings\\I\\My Music\\Sample.mp3"
        ""
        "#EXTINF:321,Example title"
        "C:\\Documents and Settings\\I\\My Music\\Greatest Hits\\Example.ogg";
    
    iProcessor->Reset();
    FileBrx file3(kFile3);
    iFileStream.SetFile(&file3);
    iReadBuffer->ReadFlush();
    iIndex = 0;
    TEST(iProcessor->Stream(*this, iFileStream.Bytes()) == EProtocolStreamErrorUnrecoverable);

    // processor passes on EProtocolStreamStopped errors
    iProcessor->Reset();
    file1.Seek(0);
    iFileStream.SetFile(&file1);
    iReadBuffer->ReadFlush();
    iIndex = 0;
    iNextResult = EProtocolStreamStopped;
    TEST(iProcessor->Stream(*this, iFileStream.Bytes()) == EProtocolStreamStopped);

    // interrupt mid-way through then resume
    iProcessor->Reset();
    iReadBuffer->ReadFlush();
    iFileStream.Seek(0);
    iIndex = 0;
    iNextResult = EProtocolStreamSuccess;
    static const TUint kInterruptBytes = 46; // part way through a File=[url] line
    iInterruptBytes = kInterruptBytes;
    TEST(iProcessor->Stream(*this, iFileStream.Bytes()) == EProtocolStreamErrorRecoverable);
    iInterrupt = false;
    TEST(iProcessor->Stream(*this, iFileStream.Bytes() - 34) == EProtocolStreamSuccess); // 34 chars in complete lines read before interruption
    TEST(iIndex == 2);
}


// SuiteM3uX

SuiteM3uX::SuiteM3uX()
    : SuiteContent("M3uX tests")
{
    iProcessor = ContentProcessorFactory::NewM3uX();
    iProcessor->Initialise(*this);
}

void SuiteM3uX::Test()
{
    TestRecognise();
    TestParse();
}

void SuiteM3uX::TestRecognise()
{
    // Example playlists.
    // https://tools.ietf.org/html/draft-pantos-http-live-streaming-14#section-10
    // https://developer.apple.com/library/ios/technotes/tn2288/_index.html#//apple_ref/doc/uid/DTS40012238-CH1-BASIC_VARIANT_PLAYLIST

    // recognition by MIME type
    TEST(iProcessor->Recognise(Brx::Empty(), Brn("application/x-mpegurl"), Brx::Empty()));
    TEST(iProcessor->Recognise(Brx::Empty(), Brn("application/vnd.apple.mpegurl"), Brx::Empty()));

    // recognition fails for bad MIME
    TEST(!iProcessor->Recognise(Brx::Empty(), Brn("audio/x-mpegurl"), Brx::Empty()));
    TEST(!iProcessor->Recognise(Brx::Empty(), Brn("audio/mpegurl"), Brx::Empty()));
    TEST(!iProcessor->Recognise(Brx::Empty(), Brn("audio/foobar"), Brx::Empty()));

    static const TChar* kFile1 =
        "#EXTM3U\n"
        "#EXT-X-STREAM-INF:BANDWIDTH=1280000,AVERAGE-BANDWIDTH=1000000\n"
        "http://example.com/low.m3u8\n"
        "#EXT-X-STREAM-INF:BANDWIDTH=2560000,AVERAGE-BANDWIDTH=2000000\n"
        "http://example.com/mid.m3u8\n"
        "#EXT-X-STREAM-INF:BANDWIDTH=7680000,AVERAGE-BANDWIDTH=6000000\n"
        "http://example.com/hi.m3u8\n"
        "#EXT-X-STREAM-INF:BANDWIDTH=65000,CODECS=\"mp4a.40.5\"\n"
        "http://example.com/audio-only.m3u8\n";

    // recognition by MIME type + content
    Brn content(kFile1);
    TEST(iProcessor->Recognise(Brx::Empty(), Brn("application/x-mpegurl"), content));

    // recognition by content, no MIME
    TEST(iProcessor->Recognise(Brx::Empty(), Brx::Empty(), content));

    // good content, bad MIME
    TEST(iProcessor->Recognise(Brx::Empty(), Brn("audio/foobar"), content));

    // bad content, bad MIME
    TEST(!iProcessor->Recognise(Brx::Empty(), Brn("audio/foobar"), Brn("playlist")));

    static const TChar* kFile2 =
        "#EXTM3U\r\n"
        "#EXT-X-STREAM-INF:BANDWIDTH=1280000,AVERAGE-BANDWIDTH=1000000\r\n"
        "http://example.com/low.m3u8\r\n"
        "#EXT-X-STREAM-INF:BANDWIDTH=2560000,AVERAGE-BANDWIDTH=2000000\r\n"
        "http://example.com/mid.m3u8\r\n"
        "#EXT-X-STREAM-INF:BANDWIDTH=7680000,AVERAGE-BANDWIDTH=6000000\r\n"
        "http://example.com/hi.m3u8\r\n"
        "#EXT-X-STREAM-INF:BANDWIDTH=65000,CODECS=\"mp4a.40.5\"\r\n"
        "http://example.com/audio-only.m3u8\r\n";
    // content with dos line endings
    content.Set(kFile2);
    TEST(iProcessor->Recognise(Brx::Empty(), Brx::Empty(), content));


    // Should fail to recognise standard M3U file.
    static const TChar* kFile3 =
        "#EXTM3U\n"
        "\n"
        "#EXTINF:123,Sample title\n"
        "C:\\Documents and Settings\\I\\My Music\\Sample.mp3\n"
        "\n"
        "#EXTINF:321,Example title\n"
        "C:\\Documents and Settings\\I\\My Music\\Greatest Hits\\Example.ogg";
    content.Set(kFile3);
    TEST(!iProcessor->Recognise(Brx::Empty(), Brx::Empty(), content));
}

void SuiteM3uX::TestParse()
{
    iInterruptBytes = 0;

    // standard file with unix line endings and desired stream first
    static const TChar* kFile1 =
        "#EXTM3U\n"
        "#EXT-X-STREAM-INF:BANDWIDTH=65000,CODECS=\"mp4a.40.5\"\n"
        "http://example.com/audio-only.m3u8\n";
        "#EXT-X-STREAM-INF:BANDWIDTH=1280000,AVERAGE-BANDWIDTH=1000000\n"
        "http://example.com/low.m3u8\n"
        "#EXT-X-STREAM-INF:BANDWIDTH=2560000,AVERAGE-BANDWIDTH=2000000\n"
        "http://example.com/mid.m3u8\n"
        "#EXT-X-STREAM-INF:BANDWIDTH=7680000,AVERAGE-BANDWIDTH=6000000\n"
        "http://example.com/hi.m3u8\n";
    FileBrx file1(kFile1);
    iFileStream.SetFile(&file1);
    const char* expected1[] = {"hls://example.com/audio-only.m3u8"};
    iExpectedStreams = expected1;
    iIndex = 0;
    iNextResult = EProtocolStreamSuccess;
    TEST(iProcessor->Stream(*this, iFileStream.Bytes()) == EProtocolStreamSuccess);
    TEST(iIndex == 1);

    // standard file with unix line endings and desired stream last
    static const TChar* kFile2 =
        "#EXTM3U\n"
        "#EXT-X-STREAM-INF:BANDWIDTH=1280000,AVERAGE-BANDWIDTH=1000000\n"
        "http://example.com/low.m3u8\n"
        "#EXT-X-STREAM-INF:BANDWIDTH=2560000,AVERAGE-BANDWIDTH=2000000\n"
        "http://example.com/mid.m3u8\n"
        "#EXT-X-STREAM-INF:BANDWIDTH=7680000,AVERAGE-BANDWIDTH=6000000\n"
        "http://example.com/hi.m3u8\n"
        "#EXT-X-STREAM-INF:BANDWIDTH=65000,CODECS=\"mp4a.40.5\"\n"
        "http://example.com/audio-only.m3u8\n";

    iProcessor->Reset();
    FileBrx file2(kFile2);
    iFileStream.SetFile(&file2);
    const char* expected2[] = {"hls://example.com/audio-only.m3u8"};
    iExpectedStreams = expected2;
    iReadBuffer->ReadFlush();
    iIndex = 0;
    TEST(iProcessor->Stream(*this, iFileStream.Bytes()) == EProtocolStreamSuccess);
    TEST(iIndex == 1);

    // standard file with unix line endings and no CODECS attribute for variants
    static const TChar* kFile3 =
        "#EXTM3U\n"
        "#EXT-X-STREAM-INF:BANDWIDTH=1280000,AVERAGE-BANDWIDTH=1000000\n"
        "http://example.com/low.m3u8\n"
        "#EXT-X-STREAM-INF:BANDWIDTH=2560000,AVERAGE-BANDWIDTH=2000000\n"
        "http://example.com/mid.m3u8\n"
        "#EXT-X-STREAM-INF:BANDWIDTH=7680000,AVERAGE-BANDWIDTH=6000000\n"
        "http://example.com/hi.m3u8\n";

    iProcessor->Reset();
    FileBrx file3(kFile3);
    iFileStream.SetFile(&file3);
    const char* expected3[] = {"hls://example.com/hi.m3u8"};
    iExpectedStreams = expected3;
    iReadBuffer->ReadFlush();
    iIndex = 0;
    TEST(iProcessor->Stream(*this, iFileStream.Bytes()) == EProtocolStreamSuccess);
    TEST(iIndex == 1);

    // same file with dos line endings
    static const TChar* kFile4 =
        "#EXTM3U\r\n"
        "#EXT-X-STREAM-INF:BANDWIDTH=1280000,AVERAGE-BANDWIDTH=1000000\r\n"
        "http://example.com/low.m3u8\r\n"
        "#EXT-X-STREAM-INF:BANDWIDTH=2560000,AVERAGE-BANDWIDTH=2000000\r\n"
        "http://example.com/mid.m3u8\r\n"
        "#EXT-X-STREAM-INF:BANDWIDTH=7680000,AVERAGE-BANDWIDTH=6000000\r\n"
        "http://example.com/hi.m3u8\r\n"
        "#EXT-X-STREAM-INF:BANDWIDTH=65000,CODECS=\"mp4a.40.5\"\r\n"
        "http://example.com/audio-only.m3u8\r\n";

    iProcessor->Reset();
    FileBrx file4(kFile4);
    iFileStream.SetFile(&file4);
    iExpectedStreams = expected1;
    iReadBuffer->ReadFlush();
    iIndex = 0;
    TEST(iProcessor->Stream(*this, iFileStream.Bytes()) == EProtocolStreamSuccess);
    TEST(iIndex == 1);

    // file with no line endings should fail to be processed
    static const TChar* kFile5 =
        "#EXTM3U"
        "#EXT-X-STREAM-INF:BANDWIDTH=1280000,AVERAGE-BANDWIDTH=1000000"
        "http://example.com/low.m3u8"
        "#EXT-X-STREAM-INF:BANDWIDTH=2560000,AVERAGE-BANDWIDTH=2000000"
        "http://example.com/mid.m3u8"
        "#EXT-X-STREAM-INF:BANDWIDTH=7680000,AVERAGE-BANDWIDTH=6000000"
        "http://example.com/hi.m3u8"
        "#EXT-X-STREAM-INF:BANDWIDTH=65000,CODECS=\"mp4a.40.5\""
        "http://example.com/audio-only.m3u8";

    iProcessor->Reset();
    FileBrx file5(kFile5);
    iFileStream.SetFile(&file5);
    iReadBuffer->ReadFlush();
    iIndex = 0;
    TEST(iProcessor->Stream(*this, iFileStream.Bytes()) == EProtocolStreamErrorUnrecoverable);

    // processor passes on EProtocolStreamStopped errors
    iProcessor->Reset();
    file1.Seek(0);
    iFileStream.SetFile(&file1);
    iReadBuffer->ReadFlush();
    iIndex = 0;
    iNextResult = EProtocolStreamStopped;
    TEST(iProcessor->Stream(*this, iFileStream.Bytes()) == EProtocolStreamStopped);

    // interrupt mid-way through then resume
    iProcessor->Reset();
    iReadBuffer->ReadFlush();
    iFileStream.Seek(0);
    iIndex = 0;
    iNextResult = EProtocolStreamSuccess;
    static const TUint kInterruptBytes = 80; // part way through a [url] line
    iInterruptBytes = kInterruptBytes;
    TEST(iProcessor->Stream(*this, iFileStream.Bytes()) == EProtocolStreamErrorRecoverable);
    iInterrupt = false;
    TEST(iProcessor->Stream(*this, iFileStream.Bytes() - 70) == EProtocolStreamSuccess); // 70 chars in complete lines read before interruption
    TEST(iIndex == 1);
}


// SuiteOpml

SuiteOpml::SuiteOpml()
    : SuiteContent("OPML tests")
    , iNumFails(0)
{
    iProcessor = ContentProcessorFactory::NewOpml();
    iProcessor->Initialise(*this);
}

void SuiteOpml::Test()
{
    TestRecognise();
    TestParse();
}

void SuiteOpml::TestRecognise()
{
    // recognition by MIME type fails
    TEST(!iProcessor->Recognise(Brx::Empty(), Brn("audio/x-mpegurl"), Brx::Empty()));
    TEST(!iProcessor->Recognise(Brx::Empty(), Brn("audio/mpegurl"), Brx::Empty()));

    // recognition also fails for bad MIME
    TEST(!iProcessor->Recognise(Brx::Empty(), Brn("audio/foobar"), Brx::Empty()));

    static const TChar* kFile1 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<opml version=\"1\">\n"
        "        <head>\n";
    // recognition by MIME type + content
    Brn content(kFile1);
    TEST(iProcessor->Recognise(Brx::Empty(), Brn("text/xml"), content));

    // recognition by content, no MIME
    TEST(iProcessor->Recognise(Brx::Empty(), Brx::Empty(), content));

    // good content, bad MIME
    TEST(iProcessor->Recognise(Brx::Empty(), Brn("audio/foobar"), content));

    // bad content, bad MIME
    TEST(!iProcessor->Recognise(Brx::Empty(), Brn("audio/foobar"), Brn("opml")));

    static const TChar* kFile2 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n"
        "<opml version=\"1\">\r\n"
        "        <head>\r\n";
    // content with dos line endings
    content.Set(kFile2);
    TEST(iProcessor->Recognise(Brx::Empty(), Brx::Empty(), content));
}

void SuiteOpml::TestParse()
{
    iInterruptBytes = 0;

    // standard file with unix line endings
    static const TChar* kFile1 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<opml version=\"1\">\n"
        "        <head>\n"
        "        <title>Listening Options</title>\n"
        "        <status>200</status>\n"
        "        </head>\n"
        "        <body>\n"
        "            <outline type=\"audio\" text=\"foo\" URL=\"http://streamexample.com:80\" bitrate=\"48000\" reliability=\"80\" guide_id=\"12345\" station_id=\"397\" title=\"Dummy Track #1\" now_playing_id=\"800\" media_type=\"audio/dummy\"/>\n"
        "            <outline type=\"audio\" text=\"foo\" URL=\"http://example.com/song.mp3\" bitrate=\"48000\" reliability=\"80\" guide_id=\"12345\" station_id=\"397\" title=\"Dummy Track #1\" now_playing_id=\"800\" media_type=\"audio/dummy\"/>\n"
        "            <outline type=\"audio\" text=\"foo\" URL=\"/home/myaccount/album.flac\" bitrate=\"48000\" reliability=\"80\" guide_id=\"12345\" station_id=\"397\" title=\"Dummy Track #1\" now_playing_id=\"800\" media_type=\"audio/dummy\"/>\n"
        "        </body>\n"
        "</opml>\n";
    FileBrx file1(kFile1);
    iFileStream.SetFile(&file1);
    const char* expected1[] = {"http://streamexample.com:80",
        "http://example.com/song.mp3",
        "/home/myaccount/album.flac"};
    iExpectedStreams = expected1;
    iIndex = 0;
    iNextResult = EProtocolStreamSuccess;
    TEST(iProcessor->Stream(*this, iFileStream.Bytes()) == EProtocolStreamSuccess);
    TEST(iIndex == 1);

    iProcessor->Reset();
    iFileStream.Seek(0);
    iIndex = 0;
    iReadBuffer->ReadFlush();
    iNumFails = 1;
    TEST(iProcessor->Stream(*this, iFileStream.Bytes()) == EProtocolStreamSuccess);
    TEST(iIndex == 2);

    iProcessor->Reset();
    iFileStream.Seek(0);
    iIndex = 0;
    iReadBuffer->ReadFlush();
    iNumFails = 2;
    TEST(iProcessor->Stream(*this, iFileStream.Bytes()) == EProtocolStreamSuccess);
    TEST(iIndex == 3);

    // same file with dos line endings
    static const TChar* kFile2 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n"
        "<opml version=\"1\">\r\n"
        "        <head>\r\n"
        "        <title>Listening Options</title>\r\n"
        "        <status>200</status>\r\n"
        "        </head>\r\n"
        "        <body>\r\n"
        "            <outline type=\"audio\" text=\"foo\" URL=\"http://streamexample.com:80\" bitrate=\"48000\" reliability=\"80\" guide_id=\"12345\" station_id=\"397\" title=\"Dummy Track #1\" now_playing_id=\"800\" media_type=\"audio/dummy\"/>\r\n"
        "            <outline type=\"audio\" text=\"foo\" URL=\"http://example.com/song.mp3\" bitrate=\"48000\" reliability=\"80\" guide_id=\"12345\" station_id=\"397\" title=\"Dummy Track #1\" now_playing_id=\"800\" media_type=\"audio/dummy\"/>\r\n"
        "            <outline type=\"audio\" text=\"foo\" URL=\"/home/myaccount/album.flac\" bitrate=\"48000\" reliability=\"80\" guide_id=\"12345\" station_id=\"397\" title=\"Dummy Track #1\" now_playing_id=\"800\" media_type=\"audio/dummy\"/>\r\n"
        "        </body>\r\n"
        "</opml>\r\n";
    
    iProcessor->Reset();
    FileBrx file2(kFile2);
    iFileStream.SetFile(&file2);
    iReadBuffer->ReadFlush();
    iIndex = 0;
    TEST(iProcessor->Stream(*this, iFileStream.Bytes()) == EProtocolStreamSuccess);
    TEST(iIndex == 1);

    // file with no line endings should fail to be processed
    static const TChar* kFile3 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
        "<opml version=\"1\">"
        "        <head>"
        "        <title>Listening Options</title>"
        "        <status>200</status>"
        "        </head>"
        "        <body>"
        "            <outline type=\"audio\" text=\"foo\" URL=\"http://streamexample.com:80\" bitrate=\"48000\" reliability=\"80\" guide_id=\"12345\" station_id=\"397\" title=\"Dummy Track #1\" now_playing_id=\"800\" media_type=\"audio/dummy\"/>"
        "            <outline type=\"audio\" text=\"foo\" URL=\"http://example.com/song.mp3\" bitrate=\"48000\" reliability=\"80\" guide_id=\"12345\" station_id=\"397\" title=\"Dummy Track #1\" now_playing_id=\"800\" media_type=\"audio/dummy\"/>"
        "            <outline type=\"audio\" text=\"foo\" URL=\"/home/myaccount/album.flac\" bitrate=\"48000\" reliability=\"80\" guide_id=\"12345\" station_id=\"397\" title=\"Dummy Track #1\" now_playing_id=\"800\" media_type=\"audio/dummy\"/>"
        "        </body>"
        "</opml>";
    
    iProcessor->Reset();
    FileBrx file3(kFile3);
    iFileStream.SetFile(&file3);
    iReadBuffer->ReadFlush();
    iIndex = 0;
    TEST(iProcessor->Stream(*this, iFileStream.Bytes()) == EProtocolStreamErrorUnrecoverable);

    // processor passes on EProtocolStreamStopped errors
    iProcessor->Reset();
    file1.Seek(0);
    iFileStream.SetFile(&file1);
    iReadBuffer->ReadFlush();
    iIndex = 0;
    iNextResult = EProtocolStreamStopped;
    TEST(iProcessor->Stream(*this, iFileStream.Bytes()) == EProtocolStreamStopped);

    // interrupt mid-way through then resume
    iProcessor->Reset();
    iReadBuffer->ReadFlush();
    iFileStream.Seek(0);
    iIndex = 0;
    iNextResult = EProtocolStreamSuccess;
    static const TUint kInterruptBytes = 229; // part way through a <outline type... line
    iInterruptBytes = kInterruptBytes;
    TEST(iProcessor->Stream(*this, iFileStream.Bytes()) == EProtocolStreamErrorRecoverable);
    iInterrupt = false;
    TEST(iProcessor->Stream(*this, iFileStream.Bytes() - 174) == EProtocolStreamSuccess); // 174 chars in complete lines read before interruption
    TEST(iIndex == 1);
}

ProtocolStreamResult SuiteOpml::Stream(const Brx& aUri)
{
    if (iNumFails > 0) {
        iNumFails--;
        iIndex++;
        return EProtocolStreamErrorUnrecoverable;
    }
    return SuiteContent::Stream(aUri);
}


// SuiteAsx

SuiteAsx::SuiteAsx()
    : SuiteContent("Asx tests")
    , iNumFails(0)
{
    iProcessor = ContentProcessorFactory::NewAsx();
    iProcessor->Initialise(*this);
}

void SuiteAsx::Test()
{
    TestRecognise();
    TestParse();
}

void SuiteAsx::TestRecognise()
{
    // recognition by MIME type
    TEST(iProcessor->Recognise(Brx::Empty(), Brn("video/x-ms-asf"), Brx::Empty()));
    TEST(iProcessor->Recognise(Brx::Empty(), Brn("video/x-ms-wax"), Brx::Empty()));
    TEST(iProcessor->Recognise(Brx::Empty(), Brn("video/x-ms-wvx"), Brx::Empty()));
    TEST(iProcessor->Recognise(Brx::Empty(), Brn("audio/x-ms-asf"), Brx::Empty()));
    TEST(iProcessor->Recognise(Brx::Empty(), Brn("audio/x-ms-wax"), Brx::Empty()));
    TEST(iProcessor->Recognise(Brx::Empty(), Brn("audio/x-ms-wvx"), Brx::Empty()));

    // recognition fails for bad MIME
    TEST(!iProcessor->Recognise(Brx::Empty(), Brn("video/ms-asf"), Brx::Empty()));
    TEST(!iProcessor->Recognise(Brx::Empty(), Brn("audio/ms-asf"), Brx::Empty()));

    static const TChar* kFile1 = "<asx version = \"3.0\">";
    static const TChar* kFile2 = "\n\r\n[Reference]";
    // recognition by MIME type + content
    Brn content(kFile1);
    TEST(iProcessor->Recognise(Brx::Empty(), Brn("video/x-ms-wvx"), content));
    content.Set(kFile2);
    TEST(iProcessor->Recognise(Brx::Empty(), Brn("video/x-ms-wvx"), content));

    // recognition by content, no MIME
    content.Set(kFile1);
    TEST(iProcessor->Recognise(Brx::Empty(), Brx::Empty(), content));
    content.Set(kFile2);
    TEST(iProcessor->Recognise(Brx::Empty(), Brx::Empty(), content));

    // good content, bad MIME
    content.Set(kFile1);
    TEST(iProcessor->Recognise(Brx::Empty(), Brn("audio/ms-asf"), content));
    content.Set(kFile2);
    TEST(iProcessor->Recognise(Brx::Empty(), Brn("audio/ms-asf"), content));

    // bad content, bad MIME
    TEST(!iProcessor->Recognise(Brx::Empty(), Brn("audio/foobar"), Brn("asx")));
}

void SuiteAsx::TestParse()
{
    // xml file
    static const TChar* kFile1 =
        "<asx version = \"3.0\">\n"
        "    <title>Absolute Classic Rock</title>\n"
        "    <entry>\n"
        "        <PARAM name=\"HTMLView\" value=\"http://www.absoluteclassicrock.co.uk/\" />\n"
        "        <abstract>Now playing info on our website.</abstract>\n"
        "        <ref href = \"mms://wm.as34763.net/vruk_vc_hi\" />\r\n"
        "        <ref href = \"http://wm.as34763.net/vruk_vc_hi\" />\n"
        "    </entry>\n"
        "</asx>\n";
    FileBrx file1(kFile1);
    iFileStream.SetFile(&file1);
    const char* expected1[] = {"mms://wm.as34763.net/vruk_vc_hi",
                               "http://wm.as34763.net/vruk_vc_hi"};
    iExpectedStreams = expected1;
    iIndex = 0;
    iNextResult = EProtocolStreamSuccess;
    TEST(iProcessor->Stream(*this, iFileStream.Bytes()) == EProtocolStreamSuccess);
    TEST(iIndex == 1);

    // plain text file
    static const TChar* kFile2 =
        "[Reference]\n"
        "Ref1=http://wmlive.bbc.co.uk/wms/england/lrcumbria?MSWMExt=.asf\n"
        "Ref2=mms://212.58.252.33:80/wms/england/lrcumbria?MSWMExt=.asf\n";
    iProcessor->Reset();
    FileBrx file2(kFile2);
    iFileStream.SetFile(&file2);
    iReadBuffer->ReadFlush();
    const char* expected2[] = {"mms://wmlive.bbc.co.uk/wms/england/lrcumbria?MSWMExt=.asf",
                               "mms://212.58.252.33:80/wms/england/lrcumbria?MSWMExt=.asf"};
    iExpectedStreams = expected2;
    iIndex = 0;
    TEST(iProcessor->Stream(*this, iFileStream.Bytes()) == EProtocolStreamSuccess);
    TEST(iIndex == 1);

    // xml with two entry blocks
    static const TChar* kFile3 =
        "<asx version = \"3.0\">\n"
        "    <title>Absolute Classic Rock</title>\n"
        "    <entry>\n"
        "        <PARAM name=\"HTMLView\" value=\"http://www.absoluteclassicrock.co.uk/\" />\n"
        "        <abstract>Now playing info on our website.</abstract>\n"
        "        <ref href = \"mms://wm.as34763.net/vruk_vc_hi\" />\r\n"
        "        <ref href = \"http://wm.as34763.net/vruk_vc_hi\" />\n"
        "    </entry>\n"
        "    <entry>\n"
        "        <abstract>probs</Abstract>\n"
        "        <PARAM name=\"HTMLView\" value=\"http://www.absoluteradio.co.uk/thestation/faq/listenonline.html\" />\n"
        "        <ref href = \"mms://wm.as34763.net/prerolls/problems_lo.wma\" />\n"
        "        <title>Absolute Classic Rock</title>\n"
        "    </entry>\n"
        "</asx>\n";
    iProcessor->Reset();
    FileBrx file3(kFile3);
    iFileStream.SetFile(&file3);
    iReadBuffer->ReadFlush();
    const char* expected3[] = {"mms://wm.as34763.net/vruk_vc_hi",
                               "mms://wm.as34763.net/prerolls/problems_lo.wma"};
    iExpectedStreams = expected3;
    iIndex = 0;
    TEST(iProcessor->Stream(*this, iFileStream.Bytes()) == EProtocolStreamSuccess);
    TEST(iIndex == 2);

    // xml file #1; first linked file fails, second succeeds
    iProcessor->Reset();
    iFileStream.SetFile(&file1);
    iFileStream.Seek(0, eSeekFromStart);
    iReadBuffer->ReadFlush();
    iExpectedStreams = expected1;
    iNumFails = 1;
    iIndex = 0;
    TEST(iProcessor->Stream(*this, iFileStream.Bytes()) == EProtocolStreamSuccess);
    TEST(iIndex == 2);

    // plain text file; first linked file fails, second succeeds
    iProcessor->Reset();
    iFileStream.SetFile(&file2);
    iFileStream.Seek(0, eSeekFromStart);
    iReadBuffer->ReadFlush();
    iExpectedStreams = expected2;
    iNumFails = 1;
    iIndex = 0;
    TEST(iProcessor->Stream(*this, iFileStream.Bytes()) == EProtocolStreamSuccess);
    TEST(iIndex == 2);

    // processor passes on EProtocolStreamStopped errors
    iProcessor->Reset();
    iFileStream.Seek(0, eSeekFromStart);
    iReadBuffer->ReadFlush();
    iNumFails = 0;
    iNextResult = EProtocolStreamStopped;
    iIndex = 0;
    TEST(iProcessor->Stream(*this, iFileStream.Bytes()) == EProtocolStreamStopped);

    // interrupt mid-way through then resume (xml file)
    iNextResult = EProtocolStreamSuccess;
    iProcessor->Reset();
    iFileStream.SetFile(&file1);
    iFileStream.Seek(0);
    iReadBuffer->ReadFlush();
    iExpectedStreams = expected1;
    iIndex = 0;
    iNextResult = EProtocolStreamSuccess;
    static const TUint kInterruptBytes = 245; // part way through a <ref href =... line
    iInterruptBytes = kInterruptBytes;
    TEST(iProcessor->Stream(*this, iFileStream.Bytes()) == EProtocolStreamErrorRecoverable);
    iInterrupt = false;
    TEST(iProcessor->Stream(*this, iFileStream.Bytes() - kInterruptBytes) == EProtocolStreamSuccess);
    TEST(iIndex == 1);

    // ...and repeat for plain text file
    iProcessor->Reset();
    iFileStream.SetFile(&file2);
    iFileStream.Seek(0);
    iReadBuffer->ReadFlush();
    iExpectedStreams = expected2;
    iIndex = 0;
    iInterruptBytes = 30; // part way through a Ref1=... line
    TEST(iProcessor->Stream(*this, iFileStream.Bytes()) == EProtocolStreamErrorRecoverable);
    iInterrupt = false;
    TEST(iProcessor->Stream(*this, iFileStream.Bytes() - 12) == EProtocolStreamSuccess); // 12 chars in complete lines read before interruption
    TEST(iIndex == 1);

}

ProtocolStreamResult SuiteAsx::Stream(const Brx& aUri)
{
    if (iNumFails > 0) {
        iNumFails--;
        iIndex++;
        return EProtocolStreamErrorUnrecoverable;
    }
    return SuiteContent::Stream(aUri);
}



void TestContentProcessor()
{
    Runner runner("Content Processor tests\n");
    runner.Add(new SuitePls());
    runner.Add(new SuiteM3u());
    runner.Add(new SuiteM3uX());
    runner.Add(new SuiteOpml());
    runner.Add(new SuiteAsx());
    runner.Run();
}
