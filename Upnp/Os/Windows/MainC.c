// entrypoint used by tests for C-wrapper APIs

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <C/Zapp.h>


void logger(void* aPtr, const char* aMsg)
{
    aPtr = aPtr;
    fprintf(stdout, "%s", aMsg);
    fflush(stdout);
}

extern void ZappTestRunner(ZappHandleInitParams aInitParams);

int __cdecl main(int argc, char* argv[])
{
    ZappHandleInitParams initParams;
    char* noErrDlgs = getenv("NO_ERROR_DIALOGS");
    if (noErrDlgs != NULL && strcmp(noErrDlgs, "1") == 0) {
        _set_abort_behavior(0, _WRITE_ABORT_MSG | _CALL_REPORTFAULT);
    }
    initParams = ZappInitParamsCreate();
    argc = argc;
    argv = argv;
    ZappInitParamsSetLogOutput(initParams, logger, NULL);
    ZappTestRunner(initParams);
    return 0;
}
