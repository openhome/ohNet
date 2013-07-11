#ifndef HEADER_PRINTER
#define HEADER_PRINTER

#include <OpenHome/Private/Standard.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/FunctorMsg.h>
#include <OpenHome/Private/Thread.h>
#include <stdarg.h>
#include <stdio.h>

namespace OpenHome {

class Log
{
    friend class Environment;
public:
    static const TUint kMaxPrintBytes = 1024;
public:
    static FunctorMsg SwapOutput(FunctorMsg& aLogOutput);
    static TInt PrintHex(const Brx& aMessage);
    static TInt Print(const Brx& aMessage);
    static TInt Print(const TChar* aFormat, ...);
    static TInt PrintVA(const TChar* aFormat, va_list aArgs);
    // following functions are equivalent to the Print()s above but send the formatted string to aOutput
    static TInt PrintHex(FunctorMsg& aOutput, const Brx& aMessage);
    static TInt Print(FunctorMsg& aOutput, const Brx& aMessage);
    static TInt Print(FunctorMsg& aOutput, const TChar* aFormat, va_list aArgs);
private:
    TInt DoPrint(FunctorMsg& aOutput, const TByte* aMessage);
    Log(FunctorMsg& aLogOutput);
private:
    FunctorMsg iLogOutput;
    Mutex iLockStdio;
    Mutex iLockFunctor;
};

} // namespace OpenHome

#endif // HEADER_PRINTER
