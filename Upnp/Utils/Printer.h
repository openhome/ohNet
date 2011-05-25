#ifndef HEADER_PRINTER
#define HEADER_PRINTER

#include <Standard.h>
#include <Buffer.h>
#include <FunctorMsg.h>
#include <stdio.h>

namespace OpenHome {
namespace Net {

const TUint kMaxPrintBytes = 1024;
    
class Log
{
public:
    static void RegisterOutput(FunctorMsg& aLogOutput);
    static TInt PrintHex(const Brx& aMessage);
    static TInt Print(const Brx& aMessage);
    static TInt Print(const TChar* aFormat, ...);
    static TInt Print(const TChar* aFormat, va_list aArgs);
    // following functions are equivalent to the Print()s above but send the formatted string to aOutput
    static TInt PrintHex(FunctorMsg& aOutput, const Brx& aMessage);
    static TInt Print(FunctorMsg& aOutput, const Brx& aMessage);
    static TInt Print(FunctorMsg& aOutput, const TChar* aFormat, va_list aArgs);
private:
    static TInt DoPrint(FunctorMsg& aOutput, const TByte* aMessage);
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_PRINTER
