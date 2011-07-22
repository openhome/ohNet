// entrypoint used by tests for C-wrapper APIs

#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <stdio.h>

#include <OpenHome/Net/C/OhNet.h>


void logger(void* aPtr, const char* aMsg)
{
    fprintf(stdout, "%s", aMsg);
    fflush(stdout);
}

extern void OhNetTestRunner(OhNetHandleInitParams aInitParams);

int main(int argc, char* argv[])
{
    OhNetHandleInitParams initParams = OhNetInitParamsCreate();
    OhNetInitParamsSetLogOutput(initParams, logger, NULL);
    OhNetTestRunner(initParams);
    return 0;
}
