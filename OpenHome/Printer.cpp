#include <OpenHome/Private/Printer.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

using namespace OpenHome;

static FunctorMsg gLogger;

TChar hexChar(TUint8 aNum)
{
    TUint8 nibble = aNum & 0x0f;
    if(nibble <= 9) {
        return ('0' + nibble);
    }
    return ('A' - 10 + nibble);
}

void Log::RegisterOutput(FunctorMsg& aLogOutput)
{ // static
    gLogger = aLogOutput;
}

FunctorMsg Log::SwapOutput(FunctorMsg& aLogOutput)
{ // static
    FunctorMsg old = gLogger;
    gLogger = aLogOutput;
    return old;
}

#define Min(a, b) ((a)<(b)? (a) : (b))
TInt Log::Print(const Brx& aMessage)
{
    return Print(gLogger, aMessage);
}

TInt Log::PrintHex(const Brx& aBrx)
{
    return PrintHex(gLogger, aBrx);
}

TInt Log::Print(const TChar* aFormat, ...)
{
    va_list args;
    va_start(args, aFormat);
    TInt n = PrintVA(aFormat, args);
    va_end(args);
    return n;
}

TInt Log::PrintVA(const TChar* aFormat, va_list aArgs)
{
    return Print(gLogger, aFormat, aArgs);
}

TInt Log::PrintHex(FunctorMsg& aOutput, const Brx& aBrx)
{
    Bws<kMaxPrintBytes+1> buf(kMaxPrintBytes+1);
    TUint split = aBrx.Bytes()/128;
    for(TUint k=0; k<split; k++) {
        TUint i=0;
        TUint j=0;
        for(i=0; i<128; i++) {
            buf[j++] = hexChar( (aBrx[i+(k*128)]&0xF0)>>4 );
            buf[j++] = hexChar( (aBrx[i+(k*128)]&0x0F) );
        }
        buf.PtrZ();
        DoPrint(aOutput, buf.Ptr());
    }
    TUint rem = aBrx.Bytes()%128;
    buf.SetBytes(rem*2);
    TUint i=0;
    TUint j=0;
    for(i=0; i<(rem); i++) {
        buf[j++] = hexChar( (aBrx[i+(split*128)]&0xF0)>>4 );
        buf[j++] = hexChar( (aBrx[i+(split*128)]&0x0F) );
    }
    buf.PtrZ();
    return DoPrint(aOutput, buf.Ptr());
}

TInt Log::Print(FunctorMsg& aOutput, const Brx& aMessage)
{
    TUint remaining = aMessage.Bytes();
    TInt ret = 0;
    const TByte* ptr = aMessage.Ptr();
    while (remaining > 0) {
        TInt len = (remaining<kMaxPrintBytes? remaining : kMaxPrintBytes);
        remaining -= len;
        TChar temp[kMaxPrintBytes+1];
        Bwn msg(temp, len, kMaxPrintBytes+1);
        msg.Replace(ptr, len);
        msg.PtrZ();
        ret += DoPrint(aOutput, msg.Ptr());
        ptr += len;
    }
    return ret;
}

TInt Log::Print(FunctorMsg& aOutput, const TChar* aFormat, va_list aArgs)
{
    TChar temp[kMaxPrintBytes+1];
    TInt n = vsnprintf(temp, kMaxPrintBytes, aFormat, aArgs);
    if (n > (TInt)kMaxPrintBytes || n < 0) {
        n = kMaxPrintBytes;
    }
    Bwn msg(temp, n, kMaxPrintBytes+1);
    msg.PtrZ();
    return DoPrint(aOutput, msg.Ptr());
}

TInt Log::DoPrint(FunctorMsg& aOutput, const TByte* aMessage)
{
    if (aOutput) {
        aOutput((const char*)aMessage);
    }
    return (TUint)strlen((const char*)aMessage);
}
