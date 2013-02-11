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

    // Writing

    buffer.SetBytes(aBytes/2);
    TEST_THROWS(aFile.Write(buffer), FileWriteError);

    Print("\n");
}

void Test()
{
    Runner runner("File testing.");
    runner.Add(new SuiteFile);
    runner.Run();
}

