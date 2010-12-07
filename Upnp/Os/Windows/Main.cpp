// entrypoint used by unit tests

extern "C" {
#include <stdlib.h>
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

int __cdecl main(int argc, char* argv[])
{
    char* noErrDlgs = getenv("NO_ERROR_DIALOGS");
    if (noErrDlgs != NULL && strcmp(noErrDlgs, "1") == 0) {
        _set_abort_behavior(0, _WRITE_ABORT_MSG | _CALL_REPORTFAULT);
    }
    InitialisationParams* initParams = InitialisationParams::Create();
    Logger logger;
    FunctorMsg functor = MakeFunctorMsg(logger, &Logger::Log);
    initParams->SetLogOutput(functor);
    Zapp::TestFramework::Runner::Main(argc, argv, initParams);
    return 0;
}
