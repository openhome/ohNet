// entrypoint used by unit tests

extern "C" {
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <stdio.h>
}

#include <OpenHome/Net/Core/OhNet.h>
#include <OpenHome/Private/TestFramework.h>

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
    fprintf(stdout, "%s", aMsg);
    fflush(stdout);
}

int main(int argc, char* argv[])
{
    InitialisationParams* initParams = InitialisationParams::Create();
    Logger logger;
    FunctorMsg functor = MakeFunctorMsg(logger, &Logger::Log);
    initParams->SetLogOutput(functor);
    Runner::Main(argc, argv, initParams);
    return 0;
}
