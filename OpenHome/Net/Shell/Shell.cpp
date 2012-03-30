#include <OpenHome/Net/Private/Shell.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Private/Parser.h>
#include <OpenHome/Private/Printer.h>

using namespace OpenHome;
using namespace OpenHome::Net;

// WriterShellResponse

WriterShellResponse::WriterShellResponse(IWriter& aWriter)
{
    iWriteBuffer = new Sws<kWriteBufferSizeBytes>(aWriter);
}

WriterShellResponse::~WriterShellResponse()
{
    delete iWriteBuffer;
}

void WriterShellResponse::Write(TByte aValue)
{
    if (aValue == '\n') {
        iWriteBuffer->Write(Brn("\r\n"));
    }
    else {
        iWriteBuffer->Write(aValue);
    }
}

void WriterShellResponse::Write(const Brx& aBuffer)
{
    const TUint bytes = aBuffer.Bytes();
    for (TUint i=0; i<bytes; i++) {
        Write(aBuffer[i]);
    }
    WriteFlush();
}

void WriterShellResponse::WriteFlush()
{
    iWriteBuffer->WriteFlush();
}


// ShellSession

const Brn ShellSession::kCmdExit = Brn("exit");

ShellSession::ShellSession(IShellCommandHandler& aCommandHandler)
    : iCommandHandler(aCommandHandler)
    , iShutdownSem("SSHL", 1)
{
    iReadBuffer = new Srs<kMaxCommandBytes>(*this);
    iWriterResponse = new WriterShellResponse(*this);
}

ShellSession::~ShellSession()
{
    iReadBuffer->ReadInterrupt();
    delete iWriterResponse;
    iShutdownSem.Wait();
    delete iReadBuffer;
}

void ShellSession::Log(const char* aMsg)
{
    Brn msg(aMsg);
    iWriterResponse->Write(msg);
}

void ShellSession::Run()
{
    FunctorMsg logger = MakeFunctorMsg(*this, &OpenHome::Net::ShellSession::Log);
    FunctorMsg oldLogger = Log::SwapOutput(logger);
    iShutdownSem.Wait();
    for (;;) {
        Brn buf = iReadBuffer->ReadUntil('\n');
        TUint bytes = buf.Bytes();
        if (bytes > 0 && buf[bytes - 1] == '\r') { // strip any trailing LF
            buf.Set(buf.Ptr(), bytes-1);
        }
        Parser parser(buf);
        Brn command = parser.Next(' ');
        if (command == kCmdExit) {
            break;
        }
        std::vector<Brn> args;
        for (;;) {
            Brn arg = parser.Next(' ');
            if (arg.Bytes() == 0) {
                break;
            }
            args.push_back(arg);
        }
        try {
            iCommandHandler.HandleShellCommand(command, args, *iWriterResponse);
        }
        catch (ReaderError&) {
            break;
        }
        catch (WriterError&) {
            break;
        }
        catch (Exception& e) {
            Log::Print("Unexpected exception: %s from %s:%u\n", e.Message(), e.File(), e.Line());
            break;
        }
    }
    (void)Log::SwapOutput(oldLogger);
    iShutdownSem.Signal();
}
    

// Shell

Shell::Shell()
    : iLock("MSHL")
{
    // there's no obvious benefit to only listening on one interface per subnet
    // ...and we can save a bit of code by just binding to all interfaces rather than tracking subnet changes...
    iServer = new SocketTcpServer("SSHL", 2323, 0);
    iServer->Add("SHEL", new ShellSession(*this));
}

Shell::~Shell()
{
    delete iServer;
}

void Shell::AddCommandHandler(const TChar* aCommand, IShellCommandHandler& aHandler)
{
    iLock.Wait();
    Brn command(aCommand);
    if (iCommands.find(command) != iCommands.end()) {
        THROW(ShellCommandAlreadyRegistered);
    }
    iCommands.insert(std::pair<Brn, IShellCommandHandler*>(command, &aHandler));
    iLock.Signal();
}

void Shell::RemoveCommandHandler(const TChar* aCommand)
{
    iLock.Wait();
    Brn command(aCommand);
    Map::iterator it = iCommands.find(command);
    if (it != iCommands.end()) {
        iCommands.erase(it);
    }
    iLock.Signal();
}

void Shell::HandleShellCommand(Brn aCommand, const std::vector<Brn>& aArgs, IWriter& aResponse)
{
    AutoMutex a(iLock);
    Map::iterator it = iCommands.find(aCommand);
    if (it == iCommands.end()) {
        aResponse.Write(Brn("Unrecognised command: "));
        aResponse.Write(Brn(aCommand));
        aResponse.Write(Brn("\n"));
    }
    else {
        // Holding iLock for the duration of the following call is poor practice
        // We get away with it here by assuming that command handlers are registered on
        // startup, before commands are likely to run.
        it->second->HandleShellCommand(aCommand, aArgs, aResponse);
    }
}
