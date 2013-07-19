#include <OpenHome/Private/Printer.h>
#include <OpenHome/OsWrapper.h>

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

using namespace OpenHome;

static void STDCALL defaultPrinter(void* /*aPtr*/, const char* aMsg)
{
    Os::ConsoleWrite(aMsg);
}

static Log* gLogger;
static FunctorMsg gDefaultPrinter = MakeFunctorMsgC(NULL, defaultPrinter);

TChar hexChar(TUint8 aNum)
{
    TUint8 nibble = aNum & 0x0f;
    if(nibble <= 9) {
        return ('0' + nibble);
    }
    return ('A' - 10 + nibble);
}

FunctorMsg Log::SwapOutput(FunctorMsg& aLogOutput)
{ // static
    FunctorMsg old = gLogger->iLogOutput;
    gLogger->iLogOutput = aLogOutput;
    return old;
}

inline FunctorMsg& Log::LogOutput()
{ // static
    return gLogger? gLogger->iLogOutput : gDefaultPrinter;
}

#define Min(a, b) ((a)<(b)? (a) : (b))
TInt Log::Print(const Brx& aMessage)
{
    return Print(LogOutput(), aMessage);
}

TInt Log::PrintHex(const Brx& aBrx)
{
    return PrintHex(LogOutput(), aBrx);
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
    return Print(LogOutput(), aFormat, aArgs);
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
        buf.SetBytes(j);
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
    Log* self = gLogger;
    if (self) {
        self->iLockStdio.Wait();
    }
    TInt n = vsnprintf(temp, kMaxPrintBytes, aFormat, aArgs);
    if (self) {
        self->iLockStdio.Signal();
    }
    if (n > (TInt)kMaxPrintBytes || n < 0) {
        n = kMaxPrintBytes;
    }
    Bwn msg(temp, n, kMaxPrintBytes+1);
    msg.PtrZ();
    return DoPrint(aOutput, msg.Ptr());
}

TInt Log::DoPrint(FunctorMsg& aOutput, const TByte* aMessage)
{ // static
    Log* self = gLogger;
    if (self) {
        self->iLockFunctor.Wait();
    }
    if (aOutput) {
        try {
            aOutput((const char*)aMessage);
        }
        catch (...) { }
    }
    if (self) {
        self->iLockFunctor.Signal();
    }
    return (TUint)strlen((const char*)aMessage);
}

Log::Log(FunctorMsg& aLogOutput)
    : iLogOutput(aLogOutput)
    , iLockStdio("MLG1")
    , iLockFunctor("MLG2")
{
    gLogger = this;
}
