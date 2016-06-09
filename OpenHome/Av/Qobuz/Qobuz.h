#pragma once

#include <OpenHome/Av/Credentials.h>
#include <OpenHome/Types.h>
#include <OpenHome/Configuration/ConfigManager.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Http.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Buffer.h>

namespace OpenHome {
    class Environment;
    class IUnixTimestamp;
namespace Configuration {
    class IConfigInitialiser;
    class ConfigChoice;
}
namespace Av {

class Qobuz : public ICredentialConsumer
{
    friend class TestQobuz;
    static const TUint kReadBufferBytes = 4 * 1024;
    static const TUint kWriteBufferBytes = 1024;
    static const TUint kConnectTimeoutMs = 10000; // FIXME - should read this + ProtocolNetwork's equivalent from a single client-changable location
    static const Brn kHost;
    static const TUint kPort = 80;
    static const TUint kMaxUsernameBytes = 128;
    static const TUint kMaxPasswordBytes = 128;
    static const Brn kId;
    static const Brn kVersionAndFormat;
    static const TUint kSecsBetweenNtpAndUnixEpoch = 2208988800; // secs between 1900 and 1970
public:
    static const Brn kConfigKeySoundQuality;
public:
    Qobuz(Environment& aEnv, const Brx& aAppId, const Brx& aAppSecret,
          ICredentialsState& aCredentialsState, Configuration::IConfigInitialiser& aConfigInitialiser,
          IUnixTimestamp& aUnixTimestamp);
    ~Qobuz();
    TBool TryLogin();
    TBool TryGetStreamUrl(const Brx& aTrackId, Bwx& aStreamUrl);
    void Interrupt(TBool aInterrupt);
private: // from ICredentialConsumer
    const Brx& Id() const override;
    void CredentialsChanged(const Brx& aUsername, const Brx& aPassword) override;
    void UpdateStatus() override;
    void Login(Bwx& aToken) override;
    void ReLogin(const Brx& aCurrentToken, Bwx& aNewToken) override;
private:
    TBool TryConnect();
    TBool TryLoginLocked();
    TUint WriteRequestReadResponse(const Brx& aMethod, const Brx& aPathAndQuery);
    Brn ReadString();
    void QualityChanged(Configuration::KeyValuePair<TUint>& aKvp);
    static void AppendMd5(Bwx& aBuffer, const Brx& aToHash);
private:
    Environment& iEnv;
    Mutex iLock;
    Mutex iLockConfig;
    ICredentialsState& iCredentialsState;
    IUnixTimestamp& iUnixTimestamp;
    SocketTcpClient iSocket;
    Srs<1024> iReaderBuf;
    ReaderUntilS<1024> iReaderUntil1;
    Sws<kWriteBufferBytes> iWriterBuf;
    WriterHttpRequest iWriterRequest;
    ReaderHttpResponse iReaderResponse;
    ReaderHttpChunked iDechunker;
    ReaderUntilS<kReadBufferBytes> iReaderUntil2;
    HttpHeaderContentLength iHeaderContentLength;
    HttpHeaderTransferEncoding iHeaderTransferEncoding;
    const Bws<32> iAppId;
    const Bws<32> iAppSecret;
    Bws<kMaxUsernameBytes> iUsername;
    Bws<kMaxPasswordBytes> iPassword;
    TUint iSoundQuality;
    Bws<128> iAuthToken;
    Bws<512> iPathAndQuery; // slightly too large for the stack; requires that all network operations are serialised
    Configuration::ConfigChoice* iConfigQuality;
    TUint iSubscriberIdQuality;
};

};  // namespace Av
};  // namespace OpenHome


