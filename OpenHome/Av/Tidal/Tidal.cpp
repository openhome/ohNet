#include <OpenHome/Av/Tidal/Tidal.h>
#include <OpenHome/Av/Credentials.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Types.h>
#include <OpenHome/SocketSsl.h>
#include <OpenHome/Configuration/ConfigManager.h>
#include <OpenHome/Private/Http.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Uri.h>
#include <OpenHome/Media/Debug.h>
        
using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Configuration;


static const TChar* kSoundQualities[3] = {"LOW", "HIGH", "LOSSLESS"};

const Brn Tidal::kHost("api.tidalhifi.com");
const Brn Tidal::kId("tidalhifi.com");
const Brn Tidal::kConfigKeySoundQuality("tidalhifi.com.SoundQuality");

Tidal::Tidal(Environment& aEnv, const Brx& aToken, Av::Credentials& aCredentialsManager, Configuration::IConfigInitialiser& aConfigInitialiser)
    : iLock("TIDL")
    , iCredentialsManager(aCredentialsManager)
    , iSocket(aEnv, kReadBufferBytes)
    , iReaderBuf(iSocket)
    , iWriterBuf(iSocket)
    , iWriterRequest(iSocket)
    , iReaderResponse(aEnv, iReaderBuf)
    , iToken(aToken)
{
    const int arr[] = {0, 1, 2};
    std::vector<TUint> qualities(arr, arr + sizeof(arr)/sizeof(arr[0]));
    iConfigQuality = new ConfigChoice(aConfigInitialiser, kConfigKeySoundQuality, qualities, 2);
    iSubscriberIdQuality = iConfigQuality->Subscribe(MakeFunctorConfigChoice(*this, &Tidal::QualityChanged));
}

Tidal::~Tidal()
{
    iConfigQuality->Unsubscribe(iSubscriberIdQuality);
    delete iConfigQuality;
}

TBool Tidal::TryGetStreamUrl(const Brx& aTrackId, Bwx& aSessionId, Bwx& aStreamUrl)
{
    TBool success = false;
    Bws<8> countryCode;
    if (TryLogin(aSessionId, countryCode)) {
        success = TryGetStreamUrl(aTrackId, aSessionId, countryCode, aStreamUrl);
    }
    return success;
}

TBool Tidal::TryLogout(const Brx& aSessionId)
{
    TBool success = false;
    try {
        Logout(aSessionId);
        success = true;
    }
    catch (CredentialsLogoutFailed&) {
    }
    return success;
}

void Tidal::Interrupt(TBool aInterrupt)
{
    iSocket.Interrupt(aInterrupt);
}

const Brx& Tidal::Id() const
{
    return kId;
}

void Tidal::CredentialsChanged(const Brx& aUsername, const Brx& aPassword)
{
    // lock
    iUsername.Replace(aUsername);
    iPassword.Replace(aPassword);
    // login, report status
}

void Tidal::Login(Bwx& aToken)
{
    aToken.SetBytes(0);
    Bws<8> countryCode;
    if (!TryLogin(aToken, countryCode)) {
        THROW(CredentialsLoginFailed);
    }
}

TBool Tidal::TryConnect(TUint aPort)
{
    Endpoint ep;
    try {
        ep.SetAddress(kHost);
        ep.SetPort(aPort);
        iSocket.Connect(ep, kConnectTimeoutMs);
    }
    catch (NetworkTimeout&) {
        return false;
    }
    catch (NetworkError&) {
        return false;
    }
    return true;
}

TBool Tidal::TryLogin(Bwx& aSessionId, Bwx& aCountryCode)
{
    TBool success = false;
    if (!TryConnect(kPort)) {
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
        WriteRequestHeaders(Http::kMethodPost, pathAndQuery, kPort, reqBody.Bytes());
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

TBool Tidal::TryGetStreamUrl(const Brx& aTrackId, const Brx& aSessionId, const Brx& aCountryCode, Bwx& aStreamUrl)
{
    TBool success = false;
    if (!TryConnect(kPort)) {
        LOG2(kMedia, kError, "ProtocolTidal::TryGetStreamUrl - failed to connect\n");
        return false;
    }
    Bws<128> pathAndQuery("/v1/tracks/");
    pathAndQuery.Append(aTrackId);
    pathAndQuery.Append("/streamurl?sessionId=");
    pathAndQuery.Append(aSessionId);
    pathAndQuery.Append("&countryCode=");
    pathAndQuery.Append(aCountryCode);
    pathAndQuery.Append("&soundQuality=");
    pathAndQuery.Append(Brn(kSoundQualities[iSoundQuality]));
    Brn url;
    try {
        WriteRequestHeaders(Http::kMethodGet, pathAndQuery, kPort);

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

void Tidal::Logout(const Brx& aToken)
{
    if (!TryConnect(kPort)) {
        LOG2(kError, kMedia, "Tidal: failed to connect\n");
        THROW(CredentialsLogoutFailed);
    }
    TBool success = false;
    Bws<128> pathAndQuery("/v1/logout?sessionId=");
    pathAndQuery.Append(aToken);
    try {
        WriteRequestHeaders(Http::kMethodPost, pathAndQuery, kPort);

        iReaderResponse.Read();
        const TUint code = iReaderResponse.Status().Code();
        if (code < 200 || code >= 300) {
            LOG(kError, "Http error - %d - in response to Tidal logout\n", code);
            THROW(ReaderError);
        }
        success = true;
    }
    catch (WriterError&) {
        LOG2(kMedia, kError, "WriterError from Tidal logout\n");
    }
    catch (ReaderError&) {
        LOG2(kMedia, kError, "ReaderError from Tidal logout\n");
    }
    iSocket.Close();
    if (!success) {
        THROW(CredentialsLogoutFailed);
    }
}

void Tidal::WriteRequestHeaders(const Brx& aMethod, const Brx& aPathAndQuery, TUint aPort, TUint aContentLength)
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

Brn Tidal::ReadValue(IReader& aReader, const Brx& aTag)
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

void Tidal::QualityChanged(Configuration::KeyValuePair<TUint>& aKvp)
{
    iLock.Wait();
    iSoundQuality = aKvp.Value();
    iLock.Signal();
}
