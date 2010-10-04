#include <Exception.h>
#include <Standard.h>
#include <ZappTypes.h>
#include <Stack.h>
#include <Zapp.h>
#include <Os.h>

#include <stdio.h>

#ifdef _WIN32
# define snprintf _snprintf
#endif

using namespace Zapp;

AssertHandler gAssertHandler = 0;

AssertHandler Zapp::SetAssertHandler(AssertHandler aHandler)
{
    AssertHandler temp = gAssertHandler;
    gAssertHandler = aHandler;
    return temp;
}

void Zapp::CallAssertHandler(const TChar* aFile, TUint aLine)
{
    gAssertHandler(aFile, aLine);
}

static void CallFatalErrorHandler(const char* aMsg)
{
    if (Stack::IsInitialised()) {
        FunctorMsg& handler = Stack::InitParams().FatalErrorHandler();
        handler(aMsg);
    }
    else {
        Os::ConsoleWrite(aMsg);
    }
}

void Zapp::AssertHandlerDefault(const TChar* aFile, TUint aLine)
{
    char buf[1024];
    (void)snprintf(buf, sizeof(buf), "Assertion failed.  %s:%d\n", aFile, aLine);
    CallFatalErrorHandler(buf);
    Os::Quit();
}

void Zapp::UnhandledExceptionHandler(const TChar* aExceptionMessage, const TChar* aFile, TUint aLine)
{
    char buf[1024];
    (void)snprintf(buf, sizeof(buf), "Unhandled exception %s at %s:%d\n", aExceptionMessage, aFile, aLine);
    CallFatalErrorHandler(buf);
}

void Zapp::UnhandledExceptionHandler(Exception& aException)
{
    char buf[1024];
    (void)snprintf(buf, sizeof(buf), "Unhandled exception %s at %s:%d\n",
                   aException.Message(), aException.File(), aException.Line());
    CallFatalErrorHandler(buf);
}

void Zapp::UnhandledExceptionHandler(std::exception& aException)
{
    char buf[1024];
    (void)snprintf(buf, sizeof(buf), "Unhandled exception %s\n", aException.what());
    CallFatalErrorHandler(buf);
}

Exception::Exception(const TChar* aMsg, const TChar* aFile, TUint aLine)
    : iMsg(aMsg)
    , iFile(aFile)
    , iLine(aLine)
{
}

const TChar* kUnknown = "Release mode. File/line information unavailable";
Exception::Exception(const TChar* aMsg)
    : iMsg(aMsg)
    , iFile(kUnknown)
    , iLine(0)
{
}

Exception::~Exception()
{
}

const TChar* Exception::Message()
{
    return iMsg;
}

const TChar* Exception::File()
{
    return iFile;
}

TUint Exception::Line()
{
    return iLine;
}
