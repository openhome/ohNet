#include <OpenHome/Os.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Private/Standard.h>

#include <windows.h>
#include <stdio.h>

static void SEHTranslator(unsigned int u, EXCEPTION_POINTERS* /*pExp*/)
{
    _asm int 3;
    switch (u)
    {
    case EXCEPTION_ACCESS_VIOLATION:
        THROW(OpenHome::AssertionFailed);
    case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
        THROW(OpenHome::AssertionFailed);
    case EXCEPTION_DATATYPE_MISALIGNMENT:
        THROW(OpenHome::AssertionFailed);
    case EXCEPTION_GUARD_PAGE:
        THROW(OpenHome::AssertionFailed);
    case EXCEPTION_INT_DIVIDE_BY_ZERO:
        THROW(OpenHome::AssertionFailed);
    case EXCEPTION_INVALID_HANDLE:
        THROW(OpenHome::AssertionFailed);
    case EXCEPTION_STACK_OVERFLOW:
        THROW(OpenHome::AssertionFailed);
    default:
        THROW(OpenHome::AssertionFailed);
    }
}

extern "C" void OsThreadInstallSignalHandlers()
{
    (void)_set_se_translator(SEHTranslator);
}
