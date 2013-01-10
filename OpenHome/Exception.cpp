#include <OpenHome/Exception.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Net/Core/OhNet.h>
#include <OpenHome/OsWrapper.h>
#include <OpenHome/Net/Private/Globals.h>

#include <stdio.h>

#ifdef _WIN32
# define snprintf _snprintf
#endif

#define EXCEPTION_LOGGING_LEVEL (0)

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
    if (gEnv == NULL) {
        Os::ConsoleWrite(aMsg);
    }
    else {
        FunctorMsg& handler = gEnv->InitParams().FatalErrorHandler();
        handler(aMsg);
    }
}

void OpenHome::AssertHandlerDefault(const TChar* aFile, TUint aLine)
{
    char buf[1024];
    (void)snprintf(buf, sizeof(buf), "Assertion failed.  %s:%lu\n", aFile, (unsigned long)aLine);
    CallFatalErrorHandler(buf);
    Os::Quit(OpenHome::gEnv->OsCtx());
}

static void GetThreadName(Bws<5>& aThName)
{
    aThName.SetBytes(0);
    aThName.Append(Thread::CurrentThreadName());
    aThName.PtrZ();
}

void OpenHome::UnhandledExceptionHandler(const TChar* aExceptionMessage, const TChar* aFile, TUint aLine)
{
    Bws<5> thName;
    GetThreadName(thName);
    char buf[1024];
    (void)snprintf(buf, sizeof(buf), "Unhandled exception %s at %s:%lu in thread %s\n", aExceptionMessage, aFile, (unsigned long)aLine, thName.Ptr());
    CallFatalErrorHandler(buf);
}

void OpenHome::UnhandledExceptionHandler(Exception& aException)
{
    Bws<5> thName;
    GetThreadName(thName);
    char buf[1024];
    (void)snprintf(buf, sizeof(buf), "Unhandled exception %s at %s:%lu in thread %s\n", aException.Message(), aException.File(), (unsigned long)aException.Line(), thName.Ptr());

    TInt len = 8*1024;
    char* msg = new char[len];
    if (msg != NULL) {
        (void)strncpy(msg, buf, len);
        len -= (TInt)strlen(buf);
        (void)strncat(msg, "\n", len);
        len -= 2;

        THandle stackTrace = aException.StackTrace();
        TUint count = Os::StackTraceNumEntries(stackTrace);
        for (TUint i=0; i<count; i++) {
            const char* entry = Os::StackTraceEntry(stackTrace, i);
            (void)strncat(msg, entry, len);
            len -= (TInt)strlen(entry) + 2;
            if (len < 0) {
                break;
            }
            (void)strncat(msg, "\n", len);
        }
    }
    if (len > 0) {
        (void)strncat(msg, "\n", len);
    }

    CallFatalErrorHandler((msg!=NULL? msg : buf));
    delete msg;
}

void OpenHome::UnhandledExceptionHandler(std::exception& aException)
{
    Bws<5> thName;
    GetThreadName(thName);
    char buf[1024];
    (void)snprintf(buf, sizeof(buf), "Unhandled exception %s in thread %s\n", aException.what(), thName.Ptr());
    CallFatalErrorHandler(buf);
}

Exception::Exception(const TChar* aMsg, const TChar* aFile, TUint aLine)
    : iMsg(aMsg)
    , iFile(aFile)
    , iLine(aLine)
{
#if EXCEPTION_LOGGING_LEVEL > 0
    Log::Print("THROW %s from %s:%u", aMsg, aFile, aLine);
    Log::Print(" (th=");
    Log::Print(Thread::CurrentThreadName());
    Log::Print(")\n");
#endif
    iStackTrace = Os::StackTraceInitialise(OpenHome::gEnv->OsCtx());
}

const TChar* kUnknown = "Release mode. File/line information unavailable";
Exception::Exception(const TChar* aMsg)
    : iMsg(aMsg)
    , iFile(kUnknown)
    , iLine(0)
{
#if EXCEPTION_LOGGING_LEVEL > 0
    Log::Print("THROW %s", aMsg);
    Log::Print(" (th=");
    Log::Print(Thread::CurrentThreadName());
    Log::Print(")\n");
#endif
    iStackTrace = Os::StackTraceInitialise(OpenHome::gEnv->OsCtx());
}

Exception::Exception(const Exception& aException)
{
#if EXCEPTION_LOGGING_LEVEL > 1
    Log::Print("Copy ctor for %s\n", iMsg);
#endif
    iMsg = aException.iMsg;
    iFile = aException.iFile;
    iLine = aException.iLine;
    iStackTrace = Os::StackTraceCopy(aException.iStackTrace);
}

Exception::~Exception()
{
#if EXCEPTION_LOGGING_LEVEL > 1
    Log::Print("Dtor for %s\n", iMsg);
#endif
    Os::StackTraceFinalise(iStackTrace);
}

const TChar* Exception::Message()
{
    return iMsg;
}

THandle Exception::StackTrace()
{
    return iStackTrace;
}

const TChar* Exception::File()
{
    return iFile;
}

TUint Exception::Line()
{
    return iLine;
}
