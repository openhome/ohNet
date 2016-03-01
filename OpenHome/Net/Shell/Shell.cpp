#include <OpenHome/Net/Private/Shell.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Parser.h>
#include <OpenHome/Private/Printer.h>

using namespace OpenHome;
using namespace OpenHome::Net;

// WriterShellResponse

const Brn WriterShellResponse::kCrLf("\r\n");

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
    Brn buf(aBuffer);
    for (;;) {
        const TUint index = Ascii::IndexOf(buf, '\n');
        if (index == buf.Bytes()) {
            if (buf.Bytes() > 0) {
                iWriteBuffer->Write(buf);
            }
            break;
        }
        Brn line(buf.Ptr(), index+1);
        buf.Set(buf.Ptr()+index+1, buf.Bytes()-index-1);
        TBool writeNewline = false;
        if (index == 0 || line[index-1] != '\r') {
            line.Set(line.Ptr(), line.Bytes()-1);
            writeNewline = true;
        }
        iWriteBuffer->Write(line);
        if (writeNewline) {
            iWriteBuffer->Write(kCrLf);
        }
    }
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
    iReaderUntil = new ReaderUntilS<kMaxCommandBytes>(*iReadBuffer);
    iWriterResponse = new WriterShellResponse(*this);
}

ShellSession::~ShellSession()
{
    iReadBuffer->ReadInterrupt();
    delete iWriterResponse;
    iShutdownSem.Wait();
    delete iReaderUntil;
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
        try {
            Brn buf = iReaderUntil->ReadUntil('\n');
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
            iCommandHandler.HandleShellCommand(command, args, *iWriterResponse);
            iWriterResponse->WriteFlush();
        }
        catch (ReaderError&) {
            break;
        }
        catch (WriterError&) {
            break;
        }
    }
    (void)Log::SwapOutput(oldLogger);
    iShutdownSem.Signal();
}
    

// Shell

Shell::Shell(Environment& aEnv, TUint aPort)
    : iLock("MSHL")
{
    iCommandHelp = new ShellCommandHelp(*this);
    // there's no obvious benefit to only listening on one interface per subnet
    // ...and we can save a bit of code by just binding to all interfaces rather than tracking subnet changes...
    iServer = new SocketTcpServer(aEnv, "ShellServer", aPort, 0);
    iServer->Add("ShellSession", new ShellSession(*this));
}

Shell::~Shell()
{
    delete iServer;
    delete iCommandHelp;
}

TUint Shell::Port() const
{
    return iServer->Port();
}

void Shell::AddCommandHandler(const TChar* aCommand, IShellCommandHandler& aHandler)
{
    AutoMutex a(iLock);
    Brn command(aCommand);
    if (iCommands.find(command) != iCommands.end()) {
        THROW(ShellCommandAlreadyRegistered);
    }
    iCommands.insert(std::pair<Brn, IShellCommandHandler*>(command, &aHandler));
}

void Shell::RemoveCommandHandler(const TChar* aCommand)
{
    AutoMutex a(iLock);
    Brn command(aCommand);
    CommandMap::iterator it = iCommands.find(command);
    if (it != iCommands.end()) {
        iCommands.erase(it);
    }
}

void Shell::HandleShellCommand(Brn aCommand, const std::vector<Brn>& aArgs, IWriter& aResponse)
{
    AutoMutex a(iLock);
    CommandMap::iterator it = iCommands.find(aCommand);
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
        aResponse.Write(Brn("\n")); // add blank line after test output for the sake of readability
    }
}

void Shell::DisplayHelp(IWriter& /*aResponse*/)
{
    ASSERTS();
}


// ShellCommandHelp

static const TChar* kShellCommandHelp = "help";

ShellCommandHelp::ShellCommandHelp(Shell& aShell)
    : iShell(aShell)
{
    iShell.AddCommandHandler(kShellCommandHelp, *this);
}

ShellCommandHelp::~ShellCommandHelp()
{
    iShell.RemoveCommandHandler(kShellCommandHelp);
}

void ShellCommandHelp::HandleShellCommand(Brn aCommand, const std::vector<Brn>& aArgs, IWriter& aResponse)
{
    if (aArgs.size() == 0) {
        aResponse.Write(Brn("Available shell commands are:\n"));
        Shell::CommandMap::iterator it = iShell.iCommands.begin();
        while (it != iShell.iCommands.end()) {
            aResponse.Write(Brn("  "));
            aResponse.Write(it->first);
            aResponse.Write(Brn("\n"));
            it++;
        }
    }
    else {
        Shell::CommandMap::iterator it = iShell.iCommands.find(aArgs[0]);
        if (it != iShell.iCommands.end()) {
            it->second->DisplayHelp(aResponse);
        }
        else {
            aResponse.Write(Brn("Error: unrecognised command - "));
            aResponse.Write(aArgs[0]);
            aResponse.Write(Brn(" - so no help available\n"));
        }
    }
}

void ShellCommandHelp::DisplayHelp(IWriter& aResponse)
{
    aResponse.Write(Brn("Usage for command \'help\':\n"));
    aResponse.Write(Brn("  available shell commands if called with no args\n"));
    aResponse.Write(Brn("  help for given command if called with one arg\n"));
    aResponse.Write(Brn("  ...ignores any args 1..n\n"));
}


// ShellNull

void ShellNull::AddCommandHandler(const TChar* /*aCommand*/, IShellCommandHandler& /*aHandler*/)
{
}

void ShellNull::RemoveCommandHandler(const TChar* /*aCommand*/)
{
}
