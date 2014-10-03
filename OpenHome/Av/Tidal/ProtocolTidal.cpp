#include <OpenHome/Media/Protocol/ProtocolFactory.h>
#include <OpenHome/Media/Protocol/Protocol.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Types.h>
#include <OpenHome/SocketSsl.h>
#include <OpenHome/Configuration/ConfigManager.h>
#include <OpenHome/Private/Http.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Uri.h>
#include <OpenHome/Media/Debug.h>
#include <OpenHome/Private/Parser.h>
#include <OpenHome/Private/Ascii.h>

#include "openssl/bio.h"
#include "openssl/pem.h"

namespace OpenHome {
namespace Media {

class ProtocolTidal : public Protocol
{
    static const TUint kReadBufferBytes = 4 * 1024;
    static const TUint kWriteBufferBytes = 1024;
    static const TUint kConnectTimeoutMs = 5000; // FIXME - should read this + ProtocolNetwork's equivalent from a single client-changable location
    static const Brn kHost;
    static const TUint kPortHttps = 443;
    static const TUint kPortHttp = 80;
    static const TUint kMaxUsernameBytes = 128;
    static const TUint kMaxPasswordBytes = 128;
public:
    static const Brn kConfigKeyUsername;
    static const Brn kConfigKeyPassword;
public:
    ProtocolTidal(Environment& aEnv, const Brx& aToken, const Brx& aRsaPrivateKey, Configuration::IConfigManagerInitialiser& aConfigInitialiser);
    ~ProtocolTidal();
private: // from Protocol
    void Interrupt(TBool aInterrupt);
    ProtocolStreamResult Stream(const Brx& aUri);
    ProtocolGetResult Get(IWriter& aWriter, const Brx& aUri, TUint64 aOffset, TUint aBytes);
private: // from IStreamHandler
    EStreamPlay OkToPlay(TUint aTrackId, TUint aStreamId);
    TUint TrySeek(TUint aTrackId, TUint aStreamId, TUint64 aOffset);
    TUint TryStop(TUint aTrackId, TUint aStreamId);
    TBool TryGet(IWriter& aWriter, TUint aTrackId, TUint aStreamId, TUint64 aOffset, TUint aBytes);
private:
    static TBool TryGetTrackId(const Brx& aQuery, Brn& aTrackId);
    TBool Connect(TUint aPort);
    TBool TryLogin(Bwx& aSessionId, Bwx& aCountryCode);
    TBool TryGetStreamUrl(const Brx& aTrackId, const Brx& aSessionId, const Brx& aCountryCode, Bwx& aStreamUrl);
    void Logout(const Brx& aSessionId);
    void WriteRequestHeaders(const Brx& aMethod, const Brx& aPathAndQuery, TUint aPort, TUint aContentLength = 0);
    static Brn ReadValue(IReader& aReader, const Brx& aTag);
    void UsernameChanged(Configuration::KeyValuePair<const Brx&>& aKvp);
    void PasswordChanged(Configuration::KeyValuePair<const Brx&>& aKvp);
    void Decrypt(const Brx& aEncrypted, Bwx& aDecrypted, const TChar* aType);
private:
    Mutex iLock;
    SocketSsl iSocket;
    Srs<kReadBufferBytes> iReaderBuf;
    Sws<kWriteBufferBytes> iWriterBuf;
    WriterHttpRequest iWriterRequest;
    ReaderHttpResponse iReaderResponse;
    const Bws<32> iToken;
    Bws<kMaxUsernameBytes> iUsername;
    Bws<kMaxPasswordBytes> iPassword;
    Uri iUri;
    Bws<1024> iStreamUrl;
    RSA* iPrivateKey;
    Configuration::ConfigText* iConfigUsername;
    Configuration::ConfigText* iConfigPassword;
    TUint iSubscriberIdUsername;
    TUint iSubscriberIdPassword;
};

};  // namespace Media
};  // namespace OpenHome

using namespace OpenHome;
using namespace OpenHome::Media;
using namespace OpenHome::Configuration;


Protocol* ProtocolFactory::NewTidal(Environment& aEnv, const Brx& aToken, const Brx& aRsaPrivateKey, IConfigManagerInitialiser& aConfigInitialiser)
{ // static
    return new ProtocolTidal(aEnv, aToken, aRsaPrivateKey, aConfigInitialiser);
}


// ProtocolTidal

const Brn ProtocolTidal::kHost("api.wimpmusic.com");
const Brn ProtocolTidal::kConfigKeyUsername("Tidal.Username");
const Brn ProtocolTidal::kConfigKeyPassword("Tidal.Password");

ProtocolTidal::ProtocolTidal(Environment& aEnv, const Brx& aToken, const Brx& aRsaPrivateKey, IConfigManagerInitialiser& aConfigInitialiser)
    : Protocol(aEnv)
    , iLock("PTID")
    , iSocket(aEnv, kReadBufferBytes)
    , iReaderBuf(iSocket)
    , iWriterBuf(iSocket)
    , iWriterRequest(iSocket)
    , iReaderResponse(aEnv, iReaderBuf)
    , iToken(aToken)
{
    BIO *bio = BIO_new_mem_buf((void*)aRsaPrivateKey.Ptr(), aRsaPrivateKey.Bytes());
    iPrivateKey = PEM_read_bio_RSAPrivateKey(bio, NULL, 0, NULL);
    BIO_free(bio);

    const TUint maxEncryptedLen = RSA_size(iPrivateKey);
    iConfigUsername = new ConfigText(aConfigInitialiser, kConfigKeyUsername, maxEncryptedLen, Brx::Empty());
    iSubscriberIdUsername = iConfigUsername->Subscribe(MakeFunctorConfigText(*this, &ProtocolTidal::UsernameChanged));
    iConfigPassword = new ConfigText(aConfigInitialiser, kConfigKeyPassword, maxEncryptedLen, Brx::Empty());
    iSubscriberIdPassword = iConfigPassword->Subscribe(MakeFunctorConfigText(*this, &ProtocolTidal::PasswordChanged));
}

ProtocolTidal::~ProtocolTidal()
{
    iConfigUsername->Unsubscribe(iSubscriberIdUsername);
    delete iConfigUsername;
    iConfigPassword->Unsubscribe(iSubscriberIdPassword);
    delete iConfigPassword;
    RSA_free(iPrivateKey);
}

void ProtocolTidal::Interrupt(TBool aInterrupt)
{
    iSocket.Interrupt(aInterrupt);
}

ProtocolStreamResult ProtocolTidal::Stream(const Brx& aUri)
{
    iSocket.Interrupt(false);
    iUri.Replace(aUri);
    if (iUri.Scheme() != Brn("tidal")) {
        LOG(kMedia, "ProtocolTidal::Stream scheme not recognised\n");
        return EProtocolErrorNotSupported;
    }
    LOG(kMedia, "ProtocolTidal::Stream(");
    LOG(kMedia, aUri);
    LOG(kMedia, ")\n");
    Brn trackId;
    if (!TryGetTrackId(iUri.Query(), trackId)) {
        return EProtocolStreamErrorUnrecoverable;
    }

    Bws<64> sessionId;
    Bws<8> countryCode;
    ProtocolStreamResult res = EProtocolStreamErrorUnrecoverable;
    if (TryLogin(sessionId, countryCode)) {
        if (TryGetStreamUrl(trackId, sessionId, countryCode, iStreamUrl)) {
            res = iProtocolManager->Stream(iStreamUrl);
        }
        Logout(sessionId);
    }
    return res;
}

ProtocolGetResult ProtocolTidal::Get(IWriter& /*aWriter*/, const Brx& /*aUri*/, TUint64 /*aOffset*/, TUint /*aBytes*/)
{
    return EProtocolGetErrorNotSupported;
}

EStreamPlay ProtocolTidal::OkToPlay(TUint /*aTrackId*/, TUint /*aStreamId*/)
{
    ASSERTS();
    return ePlayNo;
}

TUint ProtocolTidal::TrySeek(TUint /*aTrackId*/, TUint /*aStreamId*/, TUint64 /*aOffset*/)
{
    ASSERTS();
    return MsgFlush::kIdInvalid;
}

TUint ProtocolTidal::TryStop(TUint /*aTrackId*/, TUint /*aStreamId*/)
{
    ASSERTS();
    return MsgFlush::kIdInvalid;
}

TBool ProtocolTidal::TryGet(IWriter& /*aWriter*/, TUint /*aTrackId*/, TUint /*aStreamId*/, TUint64 /*aOffset*/, TUint /*aBytes*/)
{
    ASSERTS();
    return false;
}

TBool ProtocolTidal::TryGetTrackId(const Brx& aQuery, Brn& aTrackId)
{ // static
    Parser parser(aQuery);
    (void)parser.Next('?');
    Brn buf = parser.Next('=');
    if (buf != Brn("version")) {
        LOG2(kMedia, kError, "TryGetTrackId failed - no version\n");
        return false;
    }
    Brn verBuf = parser.Next('&');
    try {
        const TUint ver = Ascii::Uint(verBuf);
        if (ver != 1) {
            LOG2(kMedia, kError, "TryGetTrackId failed - unsupported version - %d\n", ver);
            return false;
        }
    }
    catch (AsciiError&) {
        LOG2(kMedia, kError, "TryGetTrackId failed - invalid version\n");
        return false;
    }
    buf.Set(parser.Next('='));
    if (buf != Brn("trackId")) {
        LOG2(kMedia, kError, "TryGetTrackId failed - no track id tag\n");
        return false;
    }
    aTrackId.Set(parser.Remaining());
    if (aTrackId.Bytes() == 0) {
        LOG2(kMedia, kError, "TryGetTrackId failed - no track id value\n");
        return false;
    }
    return true;
}

TBool ProtocolTidal::Connect(TUint aPort)
{
    Endpoint ep;
    try {
        ep.SetAddress(kHost);
        ep.SetPort(aPort);
        iSocket.Connect(ep, kConnectTimeoutMs);
    }
    catch (NetworkError&) {
        return false;
    }
    return true;
}

TBool ProtocolTidal::TryLogin(Bwx& aSessionId, Bwx& aCountryCode)
{
    TBool success = false;
    iSocket.SetSecure(true);
    if (!Connect(kPortHttps)) {
        LOG2(kMedia, kError, "ProtocolTidal::TryLogin - failed to connect\n");
        return false;
    }
    iLock.Wait();
    Bws<280> reqBody(Brn("username="));
    reqBody.Append(iUsername);
    reqBody.Append(Brn("&password="));
    reqBody.Append(iPassword);
    iLock.Signal();

    Bws<128> pathAndQuery("/v1/login/username?token=");
    pathAndQuery.Append(iToken);
    try {
        WriteRequestHeaders(Http::kMethodPost, pathAndQuery, kPortHttps, reqBody.Bytes());
        iWriterBuf.Write(reqBody);
        iWriterBuf.WriteFlush();

        iReaderResponse.Read();
        const TUint code = iReaderResponse.Status().Code();
        if (code != 200) {
            LOG(kError, "Http error - %d - in response to Tidal login\n", code);
            THROW(ReaderError);
        }

        aSessionId.Replace(ReadValue(iReaderBuf, Brn("sessionId")));
        aCountryCode.Replace(ReadValue(iReaderBuf, Brn("countryCode")));
        success = true;
    }
    catch (HttpError&) {
        LOG2(kMedia, kError, "HttpError in ProtocolTidal::TryLogin\n");
    }
    catch (ReaderError&) {
        LOG2(kMedia, kError, "ReaderError in ProtocolTidal::TryLogin\n");
    }
    catch (WriterError&) {
        LOG2(kMedia, kError, "WriterError in ProtocolTidal::TryLogin\n");
    }
    iSocket.Close();
    return success;
}

TBool ProtocolTidal::TryGetStreamUrl(const Brx& aTrackId, const Brx& aSessionId, const Brx& aCountryCode, Bwx& aStreamUrl)
{
    TBool success = false;
    iSocket.SetSecure(false);
    if (!Connect(kPortHttp)) {
        LOG2(kMedia, kError, "ProtocolTidal::TryGetStreamUrl - failed to connect\n");
        return false;
    }
    Bws<128> pathAndQuery("/v1/tracks/");
    pathAndQuery.Append(aTrackId);
    pathAndQuery.Append("/streamurl?sessionId=");
    pathAndQuery.Append(aSessionId);
    pathAndQuery.Append("&countryCode=");
    pathAndQuery.Append(aCountryCode);
    pathAndQuery.Append("&soundQuality=LOSSLESS");
    Brn url;
    try {
        WriteRequestHeaders(Http::kMethodGet, pathAndQuery, kPortHttp);

        iReaderResponse.Read();
        const TUint code = iReaderResponse.Status().Code();
        if (code != 200) {
            LOG(kError, "Http error - %d - in response to Tidal GetStreamUrl\n", code);
            THROW(ReaderError);
        }

        aStreamUrl.Replace(ReadValue(iReaderBuf, Brn("url")));
        success = true;
    }
    catch (HttpError&) {
        LOG2(kMedia, kError, "HttpError in ProtocolTidal::TryGetStreamUrl\n");
    }
    catch (ReaderError&) {
        LOG2(kMedia, kError, "ReaderError in ProtocolTidal::TryGetStreamUrl\n");
    }
    catch (WriterError&) {
        LOG2(kMedia, kError, "WriterError in ProtocolTidal::TryGetStreamUrl\n");
    }
    iSocket.Close();
    return success;
}

void ProtocolTidal::Logout(const Brx& aSessionId)
{
    iSocket.SetSecure(false);
    if (!Connect(kPortHttp)) {
        Log::Print("Failed to connect\n");
        return;
    }
    Bws<128> pathAndQuery("/v1/logout?sessionId=");
    pathAndQuery.Append(aSessionId);
    try {
        WriteRequestHeaders(Http::kMethodPost, pathAndQuery, kPortHttp);

        iReaderResponse.Read();
        const TUint code = iReaderResponse.Status().Code();
        if (code < 200 || code >= 300) {
            LOG(kError, "Http error - %d - in response to Tidal logout\n", code);
            THROW(ReaderError);
        }
    }
    catch (WriterError&) {
        LOG2(kMedia, kError, "WriterError from Tidal logout\n");
    }
    catch (ReaderError&) {
        LOG2(kMedia, kError, "ReaderError from Tidal logout\n");
    }
    iSocket.Close();
}

void ProtocolTidal::WriteRequestHeaders(const Brx& aMethod, const Brx& aPathAndQuery, TUint aPort, TUint aContentLength)
{
    iWriterRequest.WriteMethod(aMethod, aPathAndQuery, Http::eHttp11);
    Http::WriteHeaderHostAndPort(iWriterRequest, kHost, aPort);
    if (aContentLength > 0) {
        Http::WriteHeaderContentLength(iWriterRequest, aContentLength);
    }
    Http::WriteHeaderContentType(iWriterRequest, Brn("application/x-www-form-urlencoded"));
    Http::WriteHeaderConnectionClose(iWriterRequest);
    iWriterRequest.WriteFlush();
}

Brn ProtocolTidal::ReadValue(IReader& aReader, const Brx& aTag)
{ // static
    (void)aReader.ReadUntil('\"');
    for (;;) {
        Brn buf = aReader.ReadUntil('\"');
        if (buf == aTag) {
            break;
        }
    }
    (void)aReader.ReadUntil('\"');
    Brn buf = aReader.ReadUntil('\"');
    return buf;
}

void ProtocolTidal::UsernameChanged(KeyValuePair<const Brx&>& aKvp)
{
    iLock.Wait();
    Decrypt(aKvp.Value(), iUsername, "username");
    iLock.Signal();
}

void ProtocolTidal::PasswordChanged(KeyValuePair<const Brx&>& aKvp)
{
    iLock.Wait();
    Decrypt(aKvp.Value(), iPassword, "password");
    iLock.Signal();
}

void ProtocolTidal::Decrypt(const Brx& aEncrypted, Bwx& aDecrypted, const TChar* aType)
{
    aDecrypted.SetBytes(0);
    if (aEncrypted.Bytes() == 0) {
        return;
    }
    const int decryptedLen = RSA_private_decrypt(aEncrypted.Bytes(), aEncrypted.Ptr(), const_cast<TByte*>(aDecrypted.Ptr()), iPrivateKey, RSA_PKCS1_OAEP_PADDING);
    if (decryptedLen < 0) {
        LOG2(kMedia, kError, "Failed to decrypt Tidal %s\n", aType);
    }
    else {
        aDecrypted.SetBytes((TUint)decryptedLen);
    }
}
