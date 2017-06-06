#pragma once

#include <OpenHome/Av/Credentials.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Exception.h>
#include <OpenHome/SocketSsl.h>
#include <OpenHome/Private/Http.h>
#include <OpenHome/Private/Stream.h>

EXCEPTION(CalmRadioNoToken)

namespace OpenHome {
    class Environment;
namespace Av {

class CalmRadio : public ICredentialConsumer
{
    static const TUint kReadBufferBytes = 4 * 1024;
    static const TUint kWriteBufferBytes = 1024;
    static const TUint kConnectTimeoutMs = 10000; // FIXME - should read this + ProtocolNetwork's equivalent from a single client-changable location
    static const Brn kHost;
    static const TUint kPort = 443;
    static const TUint kGranularity = 128;
    static const Brn kId;
    static const TUint kMaxStatusBytes = 512;
public:
    CalmRadio(Environment& aEnv, ICredentialsState& aCredentialsState);
    ~CalmRadio();
    void Interrupt(TBool aInterrupt);
    void GetStreamUrl(Bwx& aUrlBase);
    void ForceLogin(); // logs in regardless of whether we already have a token
private: // from ICredentialConsumer
    const Brx& Id() const override;
    void CredentialsChanged(const Brx& aUsername, const Brx& aPassword) override;
    void UpdateStatus() override;
    void Login(Bwx& aToken) override;
    void ReLogin(const Brx& aCurrentToken, Bwx& aNewToken) override;
private:
    TBool TryLoginLocked(Bwx& aToken);
    TBool TryLoginLocked();
private:
    Mutex iLock;
    Mutex iLockConfig;
    ICredentialsState& iCredentialsState;
    SocketSsl iSocket;
    Srs<1024> iReaderBuf;
    ReaderUntilS<kReadBufferBytes> iReaderUntil;
    Sws<kWriteBufferBytes> iWriterBuf;
    WriterHttpRequest iWriterRequest;
    ReaderHttpResponse iReaderResponse;
    ReaderHttpChunked iDechunker;
    HttpHeaderContentLength iHeaderContentLength;
    HttpHeaderTransferEncoding iHeaderTransferEncoding;
    WriterBwh iUsername;
    WriterBwh iPassword;
    WriterBwh iToken;
    Bws<2048> iLoginResp;
};

};  // namespace Av
};  // namespace OpenHome


