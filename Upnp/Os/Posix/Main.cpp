// entrypoint used by unit tests

extern "C" {
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <stdio.h>
}

#include <Zapp.h>
#include <TestFramework.h>

using namespace Zapp;
using namespace TestFramework;

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
    Zapp::TestFramework::Runner::Main(argc, argv, initParams);
    return 0;
}
