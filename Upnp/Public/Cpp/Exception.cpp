#include <Exception.h>
#include <Standard.h>
#include <OhNetTypes.h>
#include <Stack.h>
#include <OhNet.h>
#include <OsWrapper.h>

#include <stdio.h>

#ifdef _WIN32
# define snprintf _snprintf
#endif

using namespace OpenHome;

AssertHandler gAssertHandler = 0;

AssertHandler OpenHome::SetAssertHandler(AssertHandler aHandler)
{
    AssertHandler temp = gAssertHandler;
    gAssertHandler = aHandler;
    return temp;
}

void OpenHome::CallAssertHandler(const TChar* aFile, TUint aLine)
{
    gAssertHandler(aFile, aLine);
}

static void CallFatalErrorHandler(const char* aMsg)
{
    if (Net::Stack::IsInitialised()) {
        FunctorMsg& handler = Net::Stack::InitParams().FatalErrorHandler();
        handler(aMsg);
    }
    else {
        Os::ConsoleWrite(aMsg);
    }
}

void OpenHome::AssertHandlerDefault(const TChar* aFile, TUint aLine)
{
    char buf[1024];
    (void)snprintf(buf, sizeof(buf), "Assertion failed.  %s:%d\n", aFile, aLine);
    CallFatalErrorHandler(buf);
    Os::Quit();
}

void OpenHome::UnhandledExceptionHandler(const TChar* aExceptionMessage, const TChar* aFile, TUint aLine)
{
    char buf[1024];
    (void)snprintf(buf, sizeof(buf), "Unhandled exception %s at %s:%d\n", aExceptionMessage, aFile, aLine);
    CallFatalErrorHandler(buf);
}

void OpenHome::UnhandledExceptionHandler(Exception& aException)
{
    char buf[1024];
    (void)snprintf(buf, sizeof(buf), "Unhandled exception %s at %s:%d\n",
                   aException.Message(), aException.File(), aException.Line());
    CallFatalErrorHandler(buf);
}

void OpenHome::UnhandledExceptionHandler(std::exception& aException)
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
