#ifndef HEADER_PRINTER
#define HEADER_PRINTER

#include <OpenHome/Private/Standard.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/FunctorMsg.h>
#include <stdarg.h>
#include <stdio.h>

namespace OpenHome {

const TUint kMaxPrintBytes = 1024;
    
class Log
{
public:
    static void RegisterOutput(FunctorMsg& aLogOutput);
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
    static TInt DoPrint(FunctorMsg& aOutput, const TByte* aMessage);
};

} // namespace OpenHome

#endif // HEADER_PRINTER
