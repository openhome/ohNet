#ifndef HEADER_TERMINAL
#define HEADER_TERMINAL

#include <OpenHome/Types.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Private/Fifo.h>
#include <OpenHome/Exception.h>
#include <cstdarg>

EXCEPTION(TerminalClosed)

namespace OpenHome {

class Terminal
{
public:
    virtual ~Terminal() {}
    virtual TChar GetChar() = 0;
    virtual void Print(const Brx& aBuffer) = 0;

    void Print(const TChar* aFormat, ...);
};

class TerminalOs : public Terminal
{
public:
    TerminalOs();
    virtual ~TerminalOs();
    virtual TChar GetChar();
    virtual void Print(const Brx& aBuffer);
private:
    THandle iHandle;
};

// Terminal was once the ITerminal interface, so this was cool. llvm-gcc not
// happy with virtual variadic Print(, ...), so hack it together for now.

class TerminalTcpSession : public SocketTcpSession, public Terminal
{
public:
    TerminalTcpSession();
    virtual ~TerminalTcpSession();

    void Wait();

    //  From SocketTcpSession
    virtual void Run();
    // From Terminal
    virtual TChar GetChar();
    virtual void Print(const Brx& aBuffer);

private:
    Fifo<TChar> iFifo;
    Semaphore   iReadySema;
    TBool       iInterrupted;
};

} // namespace OpenHome

#endif

