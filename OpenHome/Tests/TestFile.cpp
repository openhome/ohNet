#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/File.h>

using namespace OpenHome;
using namespace OpenHome::TestFramework;

class SuiteFile : public Suite
{
public:
    SuiteFile() : Suite("SuiteFile") {}
    void Test();
private:
    void TestFunctionality(IFile& aFile, TUint32 aBytes);
};

void SuiteFile::Test()
{
    //FileBrx tests.

    const TUint bufferBytes = 256;
    // Use only the first half of a buffer for IFile
    Bwh buf(bufferBytes, 2*bufferBytes);
    FileBrx fbrx(buf);
    TEST(fbrx.Bytes() == bufferBytes);
    Print("\n");

    TestFunctionality(fbrx, bufferBytes);

    try {
        IFile* f = IFile::Open("TestFile.elf", eFileReadOnly);
        TestFunctionality(*f, f->Bytes());
        delete f;
    }
    catch ( FileOpenError ) {
        // Ignore until I have an idea for portably testing real files.
    }
}

void SuiteFile::TestFunctionality(IFile& aFile, TUint32 aBytes)
{
    Print("Testing File implementation functionality on %d byte file\n", aBytes);

    // We should be able to set the file cursor to all
    // bytes, from 0, up to /and including/ aBytes.
    // i.e. it is valid for the cursor to be pointing off
    // the end, but not to read data from here.

    // Test absolute seeking - ensure cursor is changed for
    // each test.

    aFile.Seek(0, eSeekFromStart);
    TEST(aFile.Tell() == 0);

    aFile.Seek(aBytes, eSeekFromStart);
    TEST(aFile.Tell() == aBytes);

    aFile.Seek(-(TInt) aBytes, eSeekFromEnd);
    TEST(aFile.Tell() == 0);

    aFile.Seek(0, eSeekFromEnd);
    TEST(aFile.Tell() == aBytes);

    // Test boundaries

    // Backwards at start.
    TEST_THROWS(aFile.Seek(-1, eSeekFromStart),         FileSeekError);
    // Forwards at end
    //TEST_THROWS(aFile.Seek(+1, eSeekFromEnd),           FileSeekError);
    // Forwards from start
    //TEST_THROWS(aFile.Seek(aBytes+1, eSeekFromStart),   FileSeekError);

    // Backwards from end
    TEST_THROWS(aFile.Seek(-(TInt) (aBytes+1), eSeekFromEnd),  FileSeekError);

    // Reading

    Bwh buffer(aBytes + 20);
    aFile.Seek(0, eSeekFromStart);

    aFile.Read(buffer);
    TEST(aFile.Tell() == aBytes);
    TEST(buffer.Bytes() == aBytes);

    const TUint readBytes = 10;
    aFile.Seek(0, eSeekFromStart);
    buffer.SetBytes(0);
    aFile.Read(buffer, readBytes);
    TEST(aFile.Tell() == readBytes);
    TEST(buffer.Bytes() == readBytes);

    aFile.Seek(-(TInt) (readBytes/2), eSeekFromEnd);
    buffer.SetBytes(0);
    aFile.Read(buffer);
    TEST(aFile.Tell() == aBytes);
    TEST(buffer.Bytes() == readBytes/2);

    aFile.Seek(0, eSeekFromEnd);
    buffer.SetBytes(0);
    TEST_THROWS(aFile.Read(buffer), FileReadError);

    // Writing

    buffer.SetBytes(aBytes/2);
    TEST_THROWS(aFile.Write(buffer), FileWriteError);

    Print("\n");
}

class SuiteFileBrx : public Suite
{
public:
    SuiteFileBrx() : Suite("Test FileBrx data read.") {}
    void Test();
};

void SuiteFileBrx::Test()
{
    const TUint kBytes = 256;
    Bws<kBytes> b;
    // Populate each position in the buffer with it's index.
    for (TUint i=0; i<kBytes; i++) {
        b.Append((TChar)i);
    }

    FileBrx f(b);
    Bws<kBytes> buff;

    f.Read(buff);       // Read full buffer
    TEST(buff == b);

    buff.SetBytes(0);
    TEST_THROWS(f.Read(buff), FileReadError); // Attempt full buffer from end

    f.Seek(0, eSeekFromStart);
    buff.SetBytes(0);
    f.Read(buff, 10);
    TEST(buff[0] == 0);
    TEST(buff[9] == 9);

    f.Seek(10, eSeekFromStart);
    buff.SetBytes(0);
    f.Read(buff, 10);
    TEST(buff[0] == 10);
    TEST(buff[9] == 19);
    
    f.Seek(10, eSeekFromCurrent);
    buff.SetBytes(0);
    f.Read(buff, 10);
    TEST(buff[0] == 30);
    TEST(buff[9] == 39);
}

class SuiteFileStream : public Suite
{
public:
    SuiteFileStream() : Suite("Test FileStream") {}
    void Test();
};

void SuiteFileStream::Test()
{
    const TUint kBytes = 256;
    Bws<kBytes> b;
    // Populate each position in the buffer with it's index.
    for (TUint i=0; i<kBytes; i++) {
        b.Append((TChar)i);
    }
    FileBrx f(b);
    FileStream stream;
    stream.SetFile(&f);
    TEST(stream.Bytes() == kBytes);

    // test basic reading
    Bws<kBytes> buf;
    stream.Read(buf);
    TEST(buf == b);
    TEST(stream.Tell() == kBytes);

    // test that reads on a full buffer and at the end of a file throw
    TEST_THROWS(stream.Read(buf), ReaderError);
    buf.SetBytes(0);
    TEST_THROWS(stream.Read(buf), ReaderError);

    // test seeking
    stream.Seek(0);
    TEST(stream.Tell() == 0);

    // test a stream can be (un)interrupted
    stream.ReadInterrupt();
    Bws<10> buf2;
    TEST_THROWS(stream.Read(buf2), ReaderError);
    stream.Interrupt(false);
    stream.Read(buf2);
    TEST(buf2.Bytes() == buf2.MaxBytes());
    for (TUint i=0; i<10; i++) {
        TEST(buf2[i] == b[i]);
    }
    
    // test that Read appends to a buffer
    buf.SetBytes(0);
    buf.Append(buf2);
    stream.Read(buf);
    TEST(buf.Bytes() == kBytes);
    TEST(buf == b);
}



void TestFile()
{
    Runner runner("File testing.");
    runner.Add(new SuiteFile);
    runner.Add(new SuiteFileBrx);
    runner.Add(new SuiteFileStream);
    runner.Run();
}

