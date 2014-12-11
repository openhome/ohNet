#ifndef HEADER_SOCKET_SSL
#define HEADER_SOCKET_SSL

#include <OpenHome/Private/Network.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Types.h>

namespace OpenHome {

class Environment;
class SocketSslImpl;

class SocketSsl : public IWriter, public IReaderSource
{
public:
    SocketSsl(Environment& aEnv, TUint aReadBytes);
    ~SocketSsl();
    void SetSecure(TBool aSecure);
    void Connect(const Endpoint& aEndpoint, TUint aTimeoutMs);
    void Close();
    void Interrupt(TBool aInterrupt);
    void LogVerbose(TBool aVerbose);
public: // from IWriter
    void Write(TByte aValue) override;
    void Write(const Brx& aBuffer) override;
    void WriteFlush() override;
public: // from IReaderSource
    void Read(Bwx& aBuffer) override;
    void ReadFlush() override;
    void ReadInterrupt() override;
private:
    SocketSslImpl* iImpl;
};

} // namespace OpenHome

#endif // HEADER_SOCKET_SSL