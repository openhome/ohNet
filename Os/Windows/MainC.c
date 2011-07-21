// entrypoint used by tests for C-wrapper APIs

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <OpenHome/Net/C/OhNet.h>


void STDCALL logger(void* aPtr, const char* aMsg)
{
    aPtr = aPtr;
    fprintf(stdout, "%s", aMsg);
    fflush(stdout);
}

extern void OhNetTestRunner(OhNetHandleInitParams aInitParams);

int __cdecl main(int argc, char* argv[])
{
    OhNetHandleInitParams initParams;
    char* noErrDlgs = getenv("NO_ERROR_DIALOGS");
    if (noErrDlgs != NULL && strcmp(noErrDlgs, "1") == 0) {
        _set_abort_behavior(0, _WRITE_ABORT_MSG | _CALL_REPORTFAULT);
    }
    initParams = OhNetInitParamsCreate();
    argc = argc;
    argv = argv;
    OhNetInitParamsSetLogOutput(initParams, logger, NULL);
    OhNetTestRunner(initParams);
    return 0;
}
