#include <OpenHome/Private/SuiteUnitTest.h>
#include <OpenHome/OsWrapper.h>
#include <OpenHome/Private/Arch.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Private/Http.h>


using namespace OpenHome;
using namespace OpenHome::TestFramework;


EXCEPTION(TestException);


namespace OpenHome {

class SuiteHttpReader: public SuiteUnitTest, public INonCopyable
{
public:
    SuiteHttpReader(Environment& aEnv);

private:
    // from SuiteUnitTest
    void Setup();
    void TearDown();
private:
    void Test1();

private:
    Environment& iEnv;
};


} // namespace OpenHome

/////////////////////////////////////////////////////////

// SuitePowerManager

SuiteHttpReader::SuiteHttpReader(Environment& aEnv)
    :SuiteUnitTest("SuiteHttpReader")
    ,iEnv(aEnv)
{
    AddTest(MakeFunctor(*this, &SuiteHttpReader::Test1));
}


void SuiteHttpReader::Setup()
{
}


void SuiteHttpReader::TearDown()
{
}


void SuiteHttpReader::Test1()
{
    HttpReader httpReader(iEnv);

    // can't call Read() before Connect("...")
    TEST_THROWS(httpReader.Read(1), AssertionFailed);
    // other IReader methods should have no effect before Connect("...")
    (void)httpReader.ReadFlush();
    (void)httpReader.ReadInterrupt();

    TEST(httpReader.Connect(Uri(Brn("http://www.google.co.uk"))));

    // if trying to reuse an open socket, should automatically close and connect to new URL.
    TEST(httpReader.Connect(Uri(Brn("http://www.google.co.uk"))));

    for(;;) {
        try {
            Brn data(httpReader.Read(1024));
            //Log::Print(data);
        }
        catch(ReaderError&) {
            break;
        }
    }

}

////////////////////////////////////////////

void TestHttpReader(Environment& aEnv)
{
    Debug::SetLevel(Debug::kError);
    Runner runner("HttpReader tests\n");
    runner.Add(new SuiteHttpReader(aEnv));
    runner.Run();
}
