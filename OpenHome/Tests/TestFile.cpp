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

    Bwh* buffer = new Bwh(256);
    buffer->SetBytes(buffer->MaxBytes());

    for ( TInt i = 0 ; i < 256 ; ++i )
    {
        buffer->At(i) = i;
    }

    FileBrx fbrx(buffer);

    TestFunctionality(fbrx, 256);

    try {
        IFile* f = IFile::Open("TestFile.elf", eFileReadOnly);
        TestFunctionality(*f, f->Bytes());
        delete f;
    }
    catch ( FileOpenError ) {
        // Ignore until I have an idea of testing real files.
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

    aFile.Seek(-aBytes, eSeekFromEnd);
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
    TEST_THROWS(aFile.Seek(-(aBytes+1), eSeekFromEnd),  FileSeekError);

    // Reading

    Bwh readBuffer(aBytes + 20);
    aFile.Seek(0, eSeekFromStart);

    aFile.Read(readBuffer);
    TEST(aFile.Tell() == aBytes);
    TEST(readBuffer.Bytes() == aBytes);

    const TUint readBytes = 10;
    aFile.Seek(0, eSeekFromStart);
    aFile.Read(readBuffer, readBytes);
    TEST(aFile.Tell() == readBytes);
    TEST(readBuffer.Bytes() == readBytes);

    Print("\n");
}

void Test()
{
    Runner runner("File testing.");
    runner.Add(new SuiteFile);
    runner.Run();
}

