#ifndef HEADER_TERMINAL
#define HEADER_TERMINAL

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Private/Fifo.h>
#include <OpenHome/Exception.h>
#include <cstdarg>

EXCEPTION(TerminalClosed);

namespace OpenHome {

class ITerminal
{
public:
    virtual TChar GetChar() = 0;
    virtual void Print(const TChar* aFormat, ...) = 0;
    virtual void Print(const Brx& aBuffer) = 0;
};

class TerminalOs : public ITerminal
{
public:
    TerminalOs();
    virtual TChar GetChar();
    virtual void Print(const TChar* aFormat, ...);
    virtual void Print(const Brx& aBuffer);
private:
    void PrintVA(const TChar* aFormat, va_list aArgs);
private:
    THandle iHandle;
};

class TerminalTcpSession : public SocketTcpSession, public ITerminal
{
public:
    TerminalTcpSession();
    virtual ~TerminalTcpSession();
    //  From SocketTcpSession
    virtual void Run();
    // From ITerminal
    virtual TChar GetChar();
    virtual void Print(const TChar* aFormat, ...);
    virtual void Print(const Brx& aBuffer);

    void Wait();
private:
    Mutex       iBufferMutex;
    Bws<1024>   iBuffer;
    Fifo<TChar> iFifo;
    Semaphore   iReadySema;
    TBool       iInterrupted;
};

} // namespace OpenHome

#endif

