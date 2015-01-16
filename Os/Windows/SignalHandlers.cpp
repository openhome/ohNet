#include <OpenHome/Os.h>
#include <OpenHome/Exception.h>

#include <windows.h>
#include <stdio.h>

EXCEPTION(Windows_SEH)
EXCEPTION(Windows_SEH_AccessViolation)
EXCEPTION(Windows_SEH_ArrayBoundsExceeded)
EXCEPTION(Windows_SEH_DatatypeMisalignment)
EXCEPTION(Windows_SEH_GuardPage)
EXCEPTION(Windows_SEH_DivideByZero)
EXCEPTION(Windows_SEH_InvalidHandle)
EXCEPTION(Windows_SEH_StackOverflow)

static void SEHTranslator(unsigned int u, EXCEPTION_POINTERS* /*pExp*/)
{
    switch (u)
    {
    case EXCEPTION_ACCESS_VIOLATION:
        THROW(OpenHome::Windows_SEH_AccessViolation);
    case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
        THROW(OpenHome::Windows_SEH_ArrayBoundsExceeded);
    case EXCEPTION_DATATYPE_MISALIGNMENT:
        THROW(OpenHome::Windows_SEH_DatatypeMisalignment);
    case EXCEPTION_GUARD_PAGE:
        THROW(OpenHome::Windows_SEH_GuardPage);
    case EXCEPTION_INT_DIVIDE_BY_ZERO:
        THROW(OpenHome::Windows_SEH_DivideByZero);
    case EXCEPTION_INVALID_HANDLE:
        THROW(OpenHome::Windows_SEH_InvalidHandle);
    case EXCEPTION_STACK_OVERFLOW:
        THROW(OpenHome::Windows_SEH_StackOverflow);
    default:
        THROW(OpenHome::Windows_SEH);
    }
}

extern "C" void OsThreadInstallSignalHandlers()
{
    (void)_set_se_translator(SEHTranslator);
}
