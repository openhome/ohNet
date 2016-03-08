#include <OpenHome/Exception.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Types.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Net/Core/OhNet.h>
#include <OpenHome/OsWrapper.h>
#include <OpenHome/Net/Private/Globals.h>
#include <OpenHome/Private/Printer.h>

#include <stdio.h>

#ifdef _WIN32
# define snprintf _snprintf
#endif

#define EXCEPTION_LOGGING_LEVEL (0)

using namespace OpenHome;

static IExitHandler* gExitHandler = 0;

void OpenHome::SetExitHandler(IExitHandler& aExitHandler)
{
    gExitHandler = &aExitHandler;
}

static void CallFatalErrorHandler(const char* aMsg)
{
    if ( gExitHandler ) {
        gExitHandler->FatalErrorHandler(aMsg);
    }

    if (gEnv == NULL || gEnv->InitParams() == NULL) {
        Os::ConsoleWrite(aMsg);
    }
    else {
        FunctorMsg& handler = gEnv->InitParams()->FatalErrorHandler();
        handler(aMsg);
    }
}

static TBool gAssertThrows = false;

void OpenHome::SetAssertThrows(TBool aAssertThrows)
{
    gAssertThrows = aAssertThrows;
}

static void AssertHandlerDefault(const TChar* aFile, TUint aLine)
{
    THROW_WITH_FILE_LINE(AssertionFailed, aFile, aLine);
#if 0 // previous ASSERT implementation
    char buf[1024];
    (void)snprintf(buf, sizeof(buf), "Assertion failed.  %s:%lu\n", aFile, (unsigned long)aLine);
    CallFatalErrorHandler(buf);
    Os::Quit(OpenHome::gEnv->OsCtx());
#endif
}

void OpenHome::CallAssertHandler(const TChar* aFile, TUint aLine)
{
    if ( gAssertThrows ) {
        THROW_WITH_FILE_LINE(AssertionFailed, aFile, aLine);
    }

    if ( gExitHandler ) {
        gExitHandler->AssertionFailure(aFile, aLine);
    }

    AssertHandlerDefault(aFile, aLine);
}

void OpenHome::CallAssertHandlerVA(const TChar* aFile, TUint aLine, const TChar* aFormat, ...)
{
    va_list args;
    va_start(args, aFormat);
    (void)Log::PrintVA(aFormat, args);
    va_end(args);
    OpenHome::CallAssertHandler(aFile, aLine);
}

static void GetThreadName(Bwx& aThName)
{
    aThName.SetBytes(0);
    aThName.Append(Thread::CurrentThreadName());
    aThName.PtrZ();
}

void OpenHome::UnhandledExceptionHandler(const TChar* aExceptionMessage, const TChar* aFile, TUint aLine)
{
    if ( gExitHandler ) {
        gExitHandler->UnhandledExceptionHandler(aExceptionMessage, aFile, aLine);
    }

    Bws<Thread::kMaxNameBytes> thName;
    GetThreadName(thName);
    char buf[1024];
    (void)snprintf(buf, sizeof(buf), "Unhandled exception %s at %s:%lu in thread %s\n", aExceptionMessage, aFile, (unsigned long)aLine, thName.Ptr());
    CallFatalErrorHandler(buf);
}

void OpenHome::UnhandledExceptionHandler(Exception& aException)
{
    if ( gExitHandler ) {
        gExitHandler->UnhandledExceptionHandler(aException);
    }

    Bws<Thread::kMaxNameBytes> thName;
    GetThreadName(thName);
    char buf[512];
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
    if ( gExitHandler ) {
        gExitHandler->UnhandledExceptionHandler(aException);
    }

    Bws<Thread::kMaxNameBytes> thName;
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

Exception& Exception::operator= (const Exception& aException)
{
#if EXCEPTION_LOGGING_LEVEL > 1
    Log::Print("assignment for %s\n", iMsg);
#endif
    if ( this != &aException )
    {
        iMsg = aException.iMsg;
        iFile = aException.iFile;
        iLine = aException.iLine;
        Os::StackTraceFinalise(iStackTrace);
        iStackTrace = Os::StackTraceCopy(aException.iStackTrace);
    }
    return *this;
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

void Exception::LogStackTrace()
{
    const TUint entryCount = Os::StackTraceNumEntries(iStackTrace);
    for ( TUint i = 0 ; i < entryCount ; ++i )
    {
        Log::Print(Os::StackTraceEntry(iStackTrace, i));
        Log::Print("\n");
    }
}

const TChar* Exception::File()
{
    return iFile;
}

TUint Exception::Line()
{
    return iLine;
}
