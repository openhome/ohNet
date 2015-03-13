#ifndef HEADER_SHELL
#define HEADER_SHELL

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Thread.h>

#include <vector>
#include <map>

EXCEPTION(ShellCommandAlreadyRegistered)

namespace OpenHome {
namespace Net {

class IShellCommandHandler : public INonCopyable
{
public:
    virtual ~IShellCommandHandler() {}
    virtual void HandleShellCommand(Brn aCommand, const std::vector<Brn>& aArgs, IWriter& aResponse) = 0;
    virtual void DisplayHelp(IWriter& aResponse) = 0;
};
    
class WriterShellResponse : public IWriter
{
    static const TUint kWriteBufferSizeBytes = 1024;
public:
    WriterShellResponse(IWriter& aWriter);
    ~WriterShellResponse();
public: // from IWriter
    void Write(TByte aValue);
    void Write(const Brx& aBuffer);
    void WriteFlush();
private:
    Sws<kWriteBufferSizeBytes>* iWriteBuffer;
};

class ShellSession : public SocketTcpSession
{
    static const TUint kMaxCommandBytes = 256;
    static const Brn kCmdExit;
public:
    ShellSession(IShellCommandHandler& aCommandHandler);
    virtual ~ShellSession();
private:
    void Log(const char* aMsg);
private: // from SocketTcpSession
    void Run();
private:
    IShellCommandHandler& iCommandHandler;
    Srx* iReadBuffer;
    ReaderUntil* iReaderUntil;
    WriterShellResponse* iWriterResponse;
    Semaphore iShutdownSem;
};
    
class ShellCommandHelp;

class Shell : private IShellCommandHandler
{
    friend class ShellCommandHelp;
public:
    static const TUint kServerPortDefault = 2323;
public:
    Shell(Environment& aStack, TUint aPort=kServerPortDefault);
    ~Shell();
    TUint Port() const;
    void AddCommandHandler(const TChar* aCommand, IShellCommandHandler& aHandler);
    void RemoveCommandHandler(const TChar* aCommand);
private: // from IShellCommandHandler
    void HandleShellCommand(Brn aCommand, const std::vector<Brn>& aArgs, IWriter& aResponse);
    void DisplayHelp(IWriter& aResponse);
private:
    Mutex iLock;
    SocketTcpServer* iServer;
    typedef std::map<Brn, IShellCommandHandler*, BufferCmp> CommandMap;
    CommandMap iCommands;
    ShellCommandHelp* iCommandHelp;
};

class ShellCommandHelp : private IShellCommandHandler
{
public:
    ShellCommandHelp(Shell& aShell);
    ~ShellCommandHelp();
private: // from IShellCommandHandler
    void HandleShellCommand(Brn aCommand, const std::vector<Brn>& aArgs, IWriter& aResponse);
    void DisplayHelp(IWriter& aResponse);
private:
    Shell& iShell;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_SHELL
