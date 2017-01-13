#ifndef HEADER_PRINTER
#define HEADER_PRINTER

#include <OpenHome/Private/Standard.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/FunctorMsg.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Stream.h>
#include <stdarg.h>
#include <stdio.h>

#include <vector>


namespace OpenHome {
//For use with formatted strings e.g. 'printf("Print this buffer %.*s. Print this bool %s. Print this hex %.*s", PBUF(buffer), PBool(bool), PBUF(hexconvertedstring))'
//To print hex, you should first use AppendHex(Bwx& aBuf, const Brx& aValue) where aBuf is atleast 5x the size of the aValue to be converted.
#define PBUF(buf) (buf).Bytes(), (const TChar*)((buf).Ptr())
inline const TChar* PBool(TBool aBool, const TChar* aIfTrue = "true", const TChar* aIfFalse = "false"){ return  aBool ? aIfTrue : aIfFalse;}

// class that logs to RAM, discarding old data if it fills up
// output is only passed on if Output() is called.
class RamLogger
{
public:
    ~RamLogger();
    void Enable(TUint aCapacityBytes);
    void Disable();
    void Output();
private:
    class Chunk
    {
        static const TUint kDataBytes = 1024;
    public:
        Chunk();
        TUint Append(const char* aMsg);
        const char* Data() const;
        TUint BytesRemaining() const;
    private:
        char iData[kDataBytes+1];
        TUint iUsed;
    };
private:
    void Log(const char* aMsg);
    Chunk* NewChunk();
private:
    FunctorMsg iLogOutput;
    std::vector<Chunk*> iChunks;
};

// A class that records the last N bytes of log data
// in a ring-buffer.
// It installs itself at the head of the log-chain
// on construction, uninstalling on destruction. This
// is racy (SwapOutput) and not quite as composable as
// it seems.
// Call Read() to stream out a snapshot of the current
// buffer.
class RingBufferLogger
{
public:
    RingBufferLogger(TUint aBytes);
    ~RingBufferLogger();
    void PrefixTimestamp(TBool aEnable); // defaults to off
    void Read(OpenHome::IWriter& aWriter);
private:
    void LogFunctor(const TChar*);
private:
    Mutex iMutex;
    TUint iBytes;
    WriterRingBuffer iRingBuffer;
    FunctorMsg iDownstreamFunctorMsg;
    TBool iTimestampEnable;
    TBool iTimestampDue;
};

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

    static void ToRam(TUint aCapacityBytes); // log to RAM, discarding content on overflow.  Flush() outputs.
    static void Flush(); // output any buffered content
private:
    static TInt DoPrint(FunctorMsg& aOutput, const TByte* aMessage);
    Log(FunctorMsg& aLogOutput);
    static inline FunctorMsg& LogOutput();
    static inline void Lock();
    static inline void Unlock();
private:
    FunctorMsg iLogOutput;
    Mutex iLockStdio;
    Mutex iLockFunctor;
    RamLogger iRamLog;
};

} // namespace OpenHome

#endif // HEADER_PRINTER
