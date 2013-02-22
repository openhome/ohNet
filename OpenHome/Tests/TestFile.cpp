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
    FileBrx fbrx(new Bwh(bufferBytes, 2*bufferBytes));
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
    aFile.Read(buffer, readBytes);
    TEST(aFile.Tell() == readBytes);
    TEST(buffer.Bytes() == readBytes);

    aFile.Seek(-(TInt) (readBytes/2), eSeekFromEnd);
    aFile.Read(buffer);
    TEST(aFile.Tell() == aBytes);
    TEST(buffer.Bytes() == readBytes/2);

    aFile.Seek(0, eSeekFromEnd);
    aFile.Read(buffer);
    TEST(buffer.Bytes() == 0);

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
    Bwx* b = new Bwh(kBytes);

    // Populate each position in the buffer with it's index.
    for ( TInt i = 0 ; i < 256 ; ++i ) {
        b->Append((TChar) i);
    }

    FileBrx f(b);
    Bws<kBytes> buff;

    f.Read(buff);       // Read full buffer
    TEST(buff == *b);

    f.Read(buff);       // Attempt full buffer from end
    TEST(buff.Bytes() == 0);

    f.Seek(0, eSeekFromStart);
    f.Read(buff, 10);
    TEST(buff[0] == 0);
    TEST(buff[9] == 9);

    f.Seek(10, eSeekFromStart);
    f.Read(buff, 10);
    TEST(buff[0] == 10);
    TEST(buff[9] == 19);
    
    f.Seek(10, eSeekFromCurrent);
    f.Read(buff, 10);
    TEST(buff[0] == 30);
    TEST(buff[9] == 39);
}

void TestFile()
{
    Runner runner("File testing.");
    runner.Add(new SuiteFile);
    runner.Add(new SuiteFileBrx);
    runner.Run();
}

