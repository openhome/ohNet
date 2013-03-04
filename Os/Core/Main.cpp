#include <OpenHome/Net/Core/OhNet.h>
#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Os.h>

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::TestFramework;

class Logger
{
public:
    void Log(const char* aMsg);
};

void Logger::Log(const char* aMsg)
{
    OsConsoleWrite(aMsg);
}

static void threadMain ( void* aData )
{
    InitialisationParams* initParams = InitialisationParams::Create();
    Logger logger;
    FunctorMsg functor = MakeFunctorMsg(logger, &Logger::Log);
    initParams->SetLogOutput(functor);
    Runner::Main(0, NULL, initParams);
}


int main(int argc, char* argv[])
{
    ThreadFunctor t("MAIN", MakeFunctor(NULL, threadMain));
    t.Start();
    return 0;
}

