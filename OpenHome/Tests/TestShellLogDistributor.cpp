#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/SuiteUnitTest.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Private/Shell.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Stream.h>

using namespace OpenHome;
using namespace OpenHome::TestFramework;

class SuiteShellLogDistributor : public SuiteUnitTest
{
public:
    SuiteShellLogDistributor();
public: // from SuiteUnitTest
    void Setup() override;
    void TearDown() override;
private:
    void TestLogDistributorDefault();
    void TestLogDistributorSetModeShell();
    void TestLogDistributorSetModeAll();
    void TestLogDistributorEnableWithEmptyShellMsgFunctor();
    void TestLogDistributorPrintWithEmptyDefaultMsgFunctor();
    void LogShell(const TChar* msg);
    void LogFlashAndRs232(const TChar* msg);
private:
    ShellLogDistributor* iDistributor;
    Bws<256> iShellMsg;
    Bws<256> iFlashAndRs232Msg;
    const char iTestMsg[17] = "test log message";
    FunctorMsg iOriginalOutput;
};

// SuitePriorityQueue

SuiteShellLogDistributor::SuiteShellLogDistributor()
    : SuiteUnitTest("ShellLogDistributor")
{
    AddTest(MakeFunctor(*this, &SuiteShellLogDistributor::TestLogDistributorDefault), "TestLogDistributorDefault");
    AddTest(MakeFunctor(*this, &SuiteShellLogDistributor::TestLogDistributorSetModeShell), "TestLogDistributorSetModeShell");
    AddTest(MakeFunctor(*this, &SuiteShellLogDistributor::TestLogDistributorSetModeAll), "TestLogDistributorSetModeAll");
    AddTest(MakeFunctor(*this, &SuiteShellLogDistributor::TestLogDistributorEnableWithEmptyShellMsgFunctor), "TestLogDistributorEnableWithEmptyShellMsgFunctor");
    AddTest(MakeFunctor(*this, &SuiteShellLogDistributor::TestLogDistributorPrintWithEmptyDefaultMsgFunctor), "TestLogDistributorPrintWithEmptyDefaultMsgFunctor");
}

void SuiteShellLogDistributor::Setup()
{
    iDistributor = new ShellLogDistributor();
    FunctorMsg logFlashAndRs232 = MakeFunctorMsg(*this, &SuiteShellLogDistributor::LogFlashAndRs232);
    iOriginalOutput = Log::SwapOutput(logFlashAndRs232);    // replace with testing flash/rs232 functor and store default output functor
}

void SuiteShellLogDistributor::TearDown()
{
    Log::SwapOutput(iOriginalOutput);   // return original output functor
    iFlashAndRs232Msg.SetBytes(0);
    iShellMsg.SetBytes(0);
    delete iDistributor;
}

void SuiteShellLogDistributor::TestLogDistributorDefault()
{
    // enable log distributor with test shell function and print test message
    FunctorMsg logShell = MakeFunctorMsg(*this, &SuiteShellLogDistributor::LogShell);
    iDistributor->Enable(logShell);

    Log::Print(iTestMsg);

    // by default should in shell log mode and output to shell only
    TEST(iDistributor->GetLogMode() == EShellLogMode::eShell);
    TEST(iShellMsg == Brn(iTestMsg));
    TEST(iFlashAndRs232Msg.Bytes() == 0);

    // reset shell msg and disable log distributor, print test message again
    iShellMsg.SetBytes(0);
    iDistributor->Disable();

    Log::Print(iTestMsg);

    // should have returned to outputing to flash/rs232
    TEST(iShellMsg.Bytes() == 0);
    TEST(iFlashAndRs232Msg == Brn(iTestMsg));
}

void SuiteShellLogDistributor::TestLogDistributorSetModeShell()
{
    FunctorMsg logShell = MakeFunctorMsg(*this, &SuiteShellLogDistributor::LogShell);
    iDistributor->Enable(logShell);
    iDistributor->SetLogMode(EShellLogMode::eShell);    // enable shell log mode, same as default otherwise

    Log::Print(iTestMsg);

    TEST(iDistributor->GetLogMode() == EShellLogMode::eShell);
    TEST(iShellMsg == Brn(iTestMsg));
    TEST(iFlashAndRs232Msg.Bytes() == 0);

    iShellMsg.SetBytes(0);
    iDistributor->Disable();

    Log::Print(iTestMsg);

    TEST(iShellMsg.Bytes() == 0);
    TEST(iFlashAndRs232Msg == Brn(iTestMsg));
}

void SuiteShellLogDistributor::TestLogDistributorSetModeAll()
{
    FunctorMsg logShell = MakeFunctorMsg(*this, &SuiteShellLogDistributor::LogShell);
    iDistributor->Enable(logShell);
    iDistributor->SetLogMode(EShellLogMode::eAll);      // enable all log mode

    Log::Print(iTestMsg);

    // for this case should print to shell + flash/rs232
    TEST(iDistributor->GetLogMode() == EShellLogMode::eAll);
    TEST(iShellMsg == Brn(iTestMsg));
    TEST(iFlashAndRs232Msg == Brn(iTestMsg));

    iShellMsg.SetBytes(0);
    iFlashAndRs232Msg.SetBytes(0);
    iDistributor->Disable();

    Log::Print(iTestMsg);

    TEST(iShellMsg.Bytes() == 0);
    TEST(iFlashAndRs232Msg == Brn(iTestMsg));
}

void SuiteShellLogDistributor::TestLogDistributorEnableWithEmptyShellMsgFunctor()
{
    // test when we call enable with an empty functor msg, does it assert
    FunctorMsg emptyFunctorMsg = FunctorMsg();
    TEST_THROWS(iDistributor->Enable(emptyFunctorMsg), AssertionFailed);
}

void SuiteShellLogDistributor::TestLogDistributorPrintWithEmptyDefaultMsgFunctor()
{
    // test when default msg functor is empty and we print and log mode is all, does rs232/shell msg stay bytes==0
    // swap default output with empty functor msg before enabling
    FunctorMsg emptyFunctorMsg = FunctorMsg();
    Log::SwapOutput(emptyFunctorMsg);
    
    FunctorMsg logShell = MakeFunctorMsg(*this, &SuiteShellLogDistributor::LogShell);

    iDistributor->Enable(logShell);
    iDistributor->SetLogMode(EShellLogMode::eAll);      // enable all log mode

    Log::Print(iTestMsg);

    TEST(iFlashAndRs232Msg.Bytes() == 0);
}

void SuiteShellLogDistributor::LogShell(const TChar* msg)
{
    iShellMsg.Append(msg);
}

void SuiteShellLogDistributor::LogFlashAndRs232(const TChar* msg)
{
    iFlashAndRs232Msg.Append(msg);
}

void TestShellLogDistributor()
{
    Runner runner("ShellLogDistributor tests\n");
    runner.Add(new SuiteShellLogDistributor());
    runner.Run();
}
