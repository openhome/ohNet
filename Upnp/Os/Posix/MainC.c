// entrypoint used by tests for C-wrapper APIs

#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <stdio.h>

#include <C/Zapp.h>


void logger(void* aPtr, const char* aMsg)
{
    fprintf(stdout, "%s", aMsg);
    fflush(stdout);
}

extern void ZappTestRunner(ZappHandleInitParams aInitParams);

int main(int argc, char* argv[])
{
    ZappHandleInitParams initParams = ZappInitParamsCreate();
    ZappInitParamsSetLogOutput(initParams, logger, NULL);
    ZappTestRunner(initParams);
    return 0;
}
