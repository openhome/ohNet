#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/SuiteUnitTest.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Private/ShellCommandLogMode.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Stream.h>

using namespace OpenHome;
using namespace OpenHome::TestFramework;

class MockShellLogMode : public IShellLogMode
{
public:
    MockShellLogMode()
        : iMode(ShellLogMode::eShell)
    { }

    void SetLogMode(ShellLogMode aMode)
    {
        iMode = aMode;
    }

    ShellLogMode GetLogMode() const
    {
        return iMode;
    }

private:
    ShellLogMode iMode;
};


class SuiteShellCommandLogMode : public SuiteUnitTest
{
public:
    SuiteShellCommandLogMode(Environment& aEnv);
public: // from SuiteUnitTest
    void Setup() override;
    void TearDown() override;
private:
    void TestLogModeShell();
    void TestLogModeAll();
private:
    Environment& iEnv;
    Shell* iShell;
    IShellLogMode* iMode;
    ShellCommandLogMode* iHandler;
    Bws<1> iBuf;
    WriterBuffer* iWriterBuffer;
};

// SuitePriorityQueue

SuiteShellCommandLogMode::SuiteShellCommandLogMode(Environment& aEnv)
    : SuiteUnitTest("ShellCommandLogMode")
    , iEnv(aEnv)
{
    AddTest(MakeFunctor(*this, &SuiteShellCommandLogMode::TestLogModeShell), "TestLogModeShell");
    AddTest(MakeFunctor(*this, &SuiteShellCommandLogMode::TestLogModeAll), "TestLogModeAll");
}

void SuiteShellCommandLogMode::Setup()
{
    iShell = new Shell(iEnv, 0);
    iMode = new MockShellLogMode();
    iHandler = new ShellCommandLogMode(*iShell, *iMode);
    iWriterBuffer = new WriterBuffer(iBuf);
}

void SuiteShellCommandLogMode::TearDown()
{
    delete iWriterBuffer;
    iBuf.SetBytes(0);
    delete iHandler;
    delete iMode;
    delete iShell;
}

void SuiteShellCommandLogMode::TestLogModeShell()
{
    std::vector<Brn> args;
    Brn arg("shell");
    args.push_back(arg);

    iHandler->HandleShellCommand(Brn("logmode"), args, *iWriterBuffer);

    TEST(iMode->GetLogMode() == EShellLogMode::eShell);
    TEST(iBuf.Bytes() == 0);
}

void SuiteShellCommandLogMode::TestLogModeAll()
{
    std::vector<Brn> args;
    Brn arg("all");
    args.push_back(arg);

    iHandler->HandleShellCommand(Brn("logmode"), args, *iWriterBuffer);

    TEST(iMode->GetLogMode() == EShellLogMode::eAll);
    TEST(iBuf.Bytes() == 0);
}

void TestShellCommandLogMode(Environment& aEnv)
{
    Runner runner("ShellCommandLogMode tests\n");
    runner.Add(new SuiteShellCommandLogMode(aEnv));
    runner.Run();
}
