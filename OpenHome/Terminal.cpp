#include <OpenHome/Private/Terminal.h>
#include <cstdarg>

namespace OpenHome {

void Terminal::Print(const TChar* aFormat, ...)
{
    Bws<1024> buffer;
    va_list args;
    va_start(args, aFormat);
    buffer.AppendPrintf(aFormat, args);
    Print(buffer); // Call virtual function to do work.
    va_end(args);
}

TerminalTcpSession::TerminalTcpSession()
    : iFifo(32)
    , iReadySema("redy", 0)
    , iInterrupted(false)
{
}

TerminalTcpSession::~TerminalTcpSession()
{
}

void TerminalTcpSession::Run()
{
    iReadySema.Signal();

    Bws<1> charBuffer;

    for (;;) {
        try
        {
            Receive(charBuffer, 1);
            iFifo.Write((TChar) charBuffer[0]);
        }
        catch(NetworkError) {
            iInterrupted = true;
            iFifo.Write(0); // Trigger a read from the fifo.
            throw;
        }
    }
}

void TerminalTcpSession::Wait()
{
    iReadySema.Wait();
}

TChar TerminalTcpSession::GetChar()
{
    TChar key = iFifo.Read();
    if ( iInterrupted )
        THROW(TerminalClosed);
    return key;
}


void TerminalTcpSession::Print(const Brx& aBuffer)
{
    try {
        Send(aBuffer);
    }
    catch(NetworkError) {
        THROW(TerminalClosed);
    }
}

} // namespace OpenHome

