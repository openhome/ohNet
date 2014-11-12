#ifndef HEADER_TIDAL
#define HEADER_TIDAL

#include <OpenHome/Av/Credentials.h>
#include <OpenHome/Types.h>
#include <OpenHome/SocketSsl.h>
#include <OpenHome/Configuration/ConfigManager.h>
#include <OpenHome/Private/Http.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Buffer.h>
        
namespace OpenHome {
    class Environment;
namespace Configuration {
    class IConfigInitialiser;
    class ConfigChoice;
}
namespace Av {

class Tidal : public ICredentialConsumer
{
    static const TUint kReadBufferBytes = 4 * 1024;
    static const TUint kWriteBufferBytes = 1024;
    static const TUint kConnectTimeoutMs = 5000; // FIXME - should read this + ProtocolNetwork's equivalent from a single client-changable location
    static const Brn kHost;
    static const TUint kPort = 443;
    static const TUint kMaxUsernameBytes = 128;
    static const TUint kMaxPasswordBytes = 128;
    static const Brn kId;
public:
    static const Brn kConfigKeySoundQuality;
public:
    Tidal(Environment& aEnv, const Brx& aToken, Credentials& aCredentialsManager, Configuration::IConfigInitialiser& aConfigInitialiser);
    ~Tidal();
    TBool TryGetStreamUrl(const Brx& aTrackId, Bwx& aSessionId, Bwx& aStreamUrl);
    TBool TryLogout(const Brx& aSessionId);
    void Interrupt(TBool aInterrupt);
private: // from ICredentialConsumer
    const Brx& Id() const override;
    void CredentialsChanged(const Brx& aUsername, const Brx& aPassword) override;
    void Login(Bwx& aToken) override;
    void Logout(const Brx& aToken) override;
private:
    TBool TryConnect(TUint aPort);
    TBool TryLogin(Bwx& aSessionId, Bwx& aCountryCode);
    TBool TryGetStreamUrl(const Brx& aTrackId, const Brx& aSessionId, const Brx& aCountryCode, Bwx& aStreamUrl);
    void WriteRequestHeaders(const Brx& aMethod, const Brx& aPathAndQuery, TUint aPort, TUint aContentLength = 0);
    static Brn ReadValue(IReader& aReader, const Brx& aTag);
    void QualityChanged(Configuration::KeyValuePair<TUint>& aKvp);
private:
    Mutex iLock;
    //Credentials& iCredentialsManager;
    SocketSsl iSocket;
    Srs<kReadBufferBytes> iReaderBuf;
    Sws<kWriteBufferBytes> iWriterBuf;
    WriterHttpRequest iWriterRequest;
    ReaderHttpResponse iReaderResponse;
    const Bws<32> iToken;
    Bws<kMaxUsernameBytes> iUsername;
    Bws<kMaxPasswordBytes> iPassword;
    TUint iSoundQuality;
    Bws<1024> iStreamUrl;
    Configuration::ConfigChoice* iConfigQuality;
    TUint iSubscriberIdQuality;
};

};  // namespace Av
};  // namespace OpenHome


#endif // HEADER_TIDAL
