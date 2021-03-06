#include <OpenHome/Private/Printer.h>
#include <OpenHome/OsWrapper.h>
#include <OpenHome/Private/Timer.h>
#include <OpenHome/Net/Private/Globals.h>

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>

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
    Lock();
    FunctorMsg old = gLogger->iLogOutput;
    gLogger->iLogOutput = aLogOutput;
    Unlock();
    return old;
}

inline FunctorMsg& Log::LogOutput()
{ // static
    return gLogger? gLogger->iLogOutput : gDefaultPrinter;
}

inline void Log::Lock()
{ // static
    Log* self = gLogger;
    if (self) {
        self->iLockFunctor.Wait();
    }
}

inline void Log::Unlock()
{ // static
    Log* self = gLogger;
    if (self) {
        self->iLockFunctor.Signal();
    }
}

#define Min(a, b) ((a)<(b)? (a) : (b))
TInt Log::Print(const Brx& aMessage)
{
    Lock();
    const TInt ret = Print(LogOutput(), aMessage);
    Unlock();
    return ret;
}

TInt Log::PrintHex(const Brx& aBrx)
{
    Lock();
    const TInt ret = PrintHex(LogOutput(), aBrx);
    Unlock();
    return ret;
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
    Lock();
    const TInt ret = Print(LogOutput(), aFormat, aArgs);
    Unlock();
    return ret;
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

void Log::ToRam(TUint aCapacityBytes)
{
    gLogger->iRamLog.Enable(aCapacityBytes);
}

void Log::Flush()
{
    gLogger->iRamLog.Output();
}

TInt Log::DoPrint(FunctorMsg& aOutput, const TByte* aMessage)
{ // static

    if (aOutput) {
        try {
            aOutput((const char*)aMessage);
        }
        catch (...) { }
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


// RamLogger

RamLogger::~RamLogger()
{
    Output();
}

void RamLogger::Enable(TUint aCapacityBytes)
{
    FunctorMsg logger = MakeFunctorMsg(*this, &RamLogger::Log);
    iLogOutput = Log::SwapOutput(logger);
    iChunks.reserve(aCapacityBytes / 1024);
}

void RamLogger::Disable()
{
    (void)Log::SwapOutput(iLogOutput);
    iLogOutput = FunctorMsg();
}

void RamLogger::Output()
{
    for (std::vector<Chunk*>::iterator it = iChunks.begin(); it != iChunks.end(); it++) {
        iLogOutput((*it)->Data());
        delete *it;
    }
    iChunks.clear();
}

void RamLogger::Log(const char* aMsg)
{
    Chunk* chunk = NULL;
    if (iChunks.size() > 0) {
        chunk = iChunks[iChunks.size()-1];
        if (chunk->BytesRemaining() == 0) {
            chunk = NULL;
        }
    }
    if (chunk == NULL) {
        chunk = NewChunk();
    }
    const TUint len = (TUint)strlen(aMsg);
    const char* p = aMsg;
    for (;;) {
        p += chunk->Append(p);
        if (p >= aMsg+len) {
            break;
        }
        chunk = NewChunk();
    }
}

RamLogger::Chunk* RamLogger::NewChunk()
{
    Chunk* chunk = new Chunk();
    if (iChunks.size() == iChunks.capacity()) {
        ASSERT(iChunks.size() > 0);
        delete iChunks[0];
        iChunks.erase(iChunks.begin());
    }
    iChunks.push_back(chunk);
    return chunk;
}


// RamLogger::Chunk

RamLogger::Chunk::Chunk()
{
    iData[0] = '\0';
    iUsed = 0;
}

TUint RamLogger::Chunk::Append(const char* aMsg)
{
    const TUint len = (TUint)strlen(aMsg);
    const TUint remaining = kDataBytes - iUsed;
    (void)strncat(&iData[iUsed], aMsg, remaining);
    const TUint max = kDataBytes; // GCC can't resolve a reference to kDataBytes placed into the call to std::max below
    iUsed = std::min(max, iUsed+len);
    const TUint consumed = std::min(len, remaining);
    return consumed;
}

const char* RamLogger::Chunk::Data() const
{
    return iData;
}

TUint RamLogger::Chunk::BytesRemaining() const
{
    return kDataBytes - iUsed;
}

// RingBufferLogger

RingBufferLogger::RingBufferLogger(TUint aBytes)
    : iMutex("RingBufferLogger")
    , iBytes(aBytes)
    , iRingBuffer(aBytes)
    , iTimestampEnable(false)
    , iTimestampDue(false)
{
    // interpose our own handler, store old handler
    FunctorMsg functor = MakeFunctorMsg(*this, &RingBufferLogger::LogFunctor);
    iDownstreamFunctorMsg = Log::SwapOutput(functor);
}

RingBufferLogger::~RingBufferLogger()
{
    // restore old handler
    Log::SwapOutput(iDownstreamFunctorMsg);
}

void RingBufferLogger::PrefixTimestamp(TBool aEnable)
{
    iTimestampEnable = aEnable;
    iTimestampDue = true;
}

void RingBufferLogger::LogFunctor(const TChar* aMsg)
{
    AutoMutex amx(iMutex);

    if (iTimestampDue) {
#ifdef _WIN32
# define snprintf _snprintf_s
#endif
        char ts[20];
        snprintf(ts, sizeof(ts), "%010lu: ", (unsigned long)Time::Now(*gEnv));
        iDownstreamFunctorMsg(ts);
        Brn tsBuf(ts);
        iRingBuffer.Write(tsBuf);
        iTimestampDue = false;
    }
    Brn msg(aMsg);
    iTimestampDue = (iTimestampEnable && msg.Bytes() > 0 && msg[msg.Bytes()-1] == '\n');
    iRingBuffer.Write(msg);
    iDownstreamFunctorMsg(aMsg);
}

void RingBufferLogger::Read(IWriter& aWriter)
{
    Bwh temp(iBytes);
    {
        WriterBuffer writerBuffer(temp);
        AutoMutex amx(iMutex);
        iRingBuffer.Read(aWriter);
    }
    aWriter.Write(temp);
}

