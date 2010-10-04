// entrypoint used by tests for C-wrapper APIs

#include <stdlib.h>
#include <stdio.h>

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
    ZappHandleInitParams initParams = ZappInitParamsCreate();
    argc = argc;
    argv = argv;
    ZappInitParamsSetLogOutput(initParams, logger, NULL);
    ZappTestRunner(initParams);
    return 0;
}
