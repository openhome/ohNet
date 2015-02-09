#include <OpenHome/Av/Tidal/Tidal.h>
#include <OpenHome/Av/Credentials.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Types.h>
#include <OpenHome/SocketSsl.h>
#include <OpenHome/Configuration/ConfigManager.h>
#include <OpenHome/Private/Http.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Uri.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Media/Debug.h>

#include <algorithm>

using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Configuration;


static const TChar* kSoundQualities[3] = {"LOW", "HIGH", "LOSSLESS"};

const Brn Tidal::kHost("api.tidalhifi.com");
const Brn Tidal::kId("tidalhifi.com");
const Brn Tidal::kConfigKeySoundQuality("tidalhifi.com.SoundQuality");

Tidal::Tidal(Environment& aEnv, const Brx& aToken, ICredentialsState& aCredentialsState, Configuration::IConfigInitialiser& aConfigInitialiser)
    : iLock("TDL1")
    , iReLoginLock("TDL2")
    , iCredentialsState(aCredentialsState)
    , iSocket(aEnv, kReadBufferBytes)
    , iReaderBuf(iSocket)
    , iWriterBuf(iSocket)
    , iWriterRequest(iSocket)
    , iReaderResponse(aEnv, iReaderBuf)
    , iToken(aToken)
{
    iReaderResponse.AddHeader(iHeaderContentLength);
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

TBool Tidal::TryLogin(Bwx& aSessionId)
{
    if (!TryLogin()) {
        aSessionId.SetBytes(0);
        return false;
    }
    iLock.Wait();
    aSessionId.Replace(iSessionId);
    iLock.Signal();
    return true;
}

TBool Tidal::TryReLogin(const Brx& aCurrentToken, Bwx& aNewToken)
{
    AutoMutex _(iReLoginLock);
    iLock.Wait();
    if (iSessionId.Bytes() == 0 || aCurrentToken == iSessionId) {
        iLock.Signal();
        if (TryLogin()) {
            iLock.Wait();
            aNewToken.Replace(iSessionId);
            iLock.Signal();
            return true;
        }
        return false;
    }
    aNewToken.Replace(iSessionId);
    iLock.Signal();
    return true;
}

TBool Tidal::TryGetStreamUrl(const Brx& aTrackId, Bwx& aStreamUrl)
{
    TBool success = false;
    if (!TryConnect(kPort)) {
        LOG2(kMedia, kError, "ProtocolTidal::TryGetStreamUrl - failed to connect\n");
        return false;
    }
    AutoSocketSsl _(iSocket);
    iLock.Wait();
    Bws<128> pathAndQuery("/v1/tracks/");
    pathAndQuery.Append(aTrackId);
    pathAndQuery.Append("/streamurl?sessionId=");
    pathAndQuery.Append(iSessionId);
    pathAndQuery.Append("&countryCode=");
    pathAndQuery.Append(iCountryCode);
    pathAndQuery.Append("&soundQuality=");
    pathAndQuery.Append(Brn(kSoundQualities[iSoundQuality]));
    iLock.Signal();
    Brn url;
    try {
        WriteRequestHeaders(Http::kMethodGet, pathAndQuery, kPort);

        iReaderResponse.Read();
        const TUint code = iReaderResponse.Status().Code();
        if (code != 200) {
            LOG(kError, "Http error - %d - in response to Tidal GetStreamUrl.  Some/all of response is:\n", code);
            LOG(kError, iReaderBuf.Snaffle());
            LOG(kError, "\n");
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
    return success;
}

TBool Tidal::TryLogout(const Brx& aSessionId)
{
    if (aSessionId.Bytes() == 0) {
        return true;
    }
    TBool success = false;
    if (!TryConnect(kPort)) {
        LOG2(kError, kMedia, "Tidal: failed to connect\n");
        return false;
    }
    AutoSocketSsl _(iSocket);
    Bws<128> pathAndQuery("/v1/logout?sessionId=");
    pathAndQuery.Append(aSessionId);
    try {
        WriteRequestHeaders(Http::kMethodPost, pathAndQuery, kPort);

        iReaderResponse.Read();
        const TUint code = iReaderResponse.Status().Code();
        if (code < 200 || code >= 300) {
            LOG(kError, "Http error - %d - in response to Tidal logout.  Some/all of response is:\n", code);
            LOG(kError, iReaderBuf.Snaffle());
            LOG(kError, "\n");
            THROW(ReaderError);
        }
        success = true;
        iLock.Wait();
        iSessionId.SetBytes(0);
        iLock.Signal();
    }
    catch (WriterError&) {
        LOG2(kMedia, kError, "WriterError from Tidal logout\n");
    }
    catch (ReaderError&) {
        LOG2(kMedia, kError, "ReaderError from Tidal logout\n");
    }
    catch (HttpError&) {
        LOG2(kMedia, kError, "HttpError from Tidal logout\n");
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
    iLock.Wait();
    iUsername.Replace(aUsername);
    iPassword.Replace(aPassword);
    iLock.Signal();
}

void Tidal::UpdateStatus()
{
    (void)TryLogout(iSessionId);
    iLock.Wait();
    const TBool noCredentials = (iUsername.Bytes() == 0 && iPassword.Bytes() == 0);
    iLock.Signal();
    if (noCredentials) {
        iCredentialsState.SetState(kId, Brx::Empty(), Brx::Empty());
    }
    else {
        (void)TryLogin();
    }
}

void Tidal::Login(Bwx& aToken)
{
    if (!TryLogin(aToken)) {
        THROW(CredentialsLoginFailed);
    }
}

void Tidal::ReLogin(const Brx& aCurrentToken, Bwx& aNewToken)
{
    if (!TryReLogin(aCurrentToken, aNewToken)) {
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

TBool Tidal::TryLogin()
{
    TBool updatedStatus = false;
    Bws<50> error;
    iLock.Wait();
    iSessionId.SetBytes(0);
    iLock.Signal();
    TBool success = false;
    if (!TryConnect(kPort)) {
        LOG2(kMedia, kError, "ProtocolTidal::TryLogin - failed to connect\n");
        iCredentialsState.SetState(kId, Brn("Login Error (Connection Failed): Please Try Again."), Brx::Empty());
        return false;
    }
    AutoSocketSsl _(iSocket);
    iLock.Wait();
    Bws<280> reqBody(Brn("username="));
    WriterBuffer writer(reqBody);
    FormUrlEncode(writer, iUsername);
    reqBody.Append(Brn("&password="));
    FormUrlEncode(writer, iPassword);
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
            Bws<ICredentials::kMaxStatusBytes> status;
            const TUint len = std::min(status.MaxBytes(), iHeaderContentLength.ContentLength());
            if (len > 0) {
                status.Replace(iReaderBuf.Read(len));
                iCredentialsState.SetState(kId, status, Brx::Empty());
            }
            else {
                error.AppendPrintf("Login Error (Response Code %d): Please Try Again.", code);
                iCredentialsState.SetState(kId, error, Brx::Empty());
            }
            updatedStatus = true;
            LOG(kError, "Http error - %d - in response to Tidal login.  Some/all of response is:\n", code);
            LOG(kError, status);
            LOG(kError, "\n");
            THROW(ReaderError);
        }

        iLock.Wait();
        iSessionId.Replace(ReadValue(iReaderBuf, Brn("sessionId")));
        iCountryCode.Replace(ReadValue(iReaderBuf, Brn("countryCode")));
        iLock.Signal();
        iCredentialsState.SetState(kId, Brx::Empty(), iCountryCode);
        updatedStatus = true;
        success = true;
    }
    catch (HttpError&) {
        error.Append("Login Error (Http Failure): Please Try Again.");
        LOG2(kMedia, kError, "HttpError in ProtocolTidal::TryLogin\n");
    }
    catch (ReaderError&) {
        error.Append("Login Error (Read Failure): Please Try Again.");
        LOG2(kMedia, kError, "ReaderError in ProtocolTidal::TryLogin\n");
    }
    catch (WriterError&) {
        error.Append("Login Error (Write Failure): Please Try Again.");
        LOG2(kMedia, kError, "WriterError in ProtocolTidal::TryLogin\n");
    }
    if (!updatedStatus) {
        iCredentialsState.SetState(kId, error, Brx::Empty());
    }
    return success;
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

void Tidal::FormUrlEncode(IWriter& aWriter, const Brx& aSrc)
{ // static
    const TUint bytes = aSrc.Bytes();
    for (TUint i=0; i<bytes; i++) {
        TChar ch = aSrc[i];
        if (Ascii::IsAlphabetic(ch) || Ascii::IsDigit(ch)) {
            aWriter.Write(ch);
        }
        else if (ch == ' ') {
            aWriter.Write('+');
        }
        else {
            aWriter.Write('%');
            WriterAscii writerAscii(aWriter);
            writerAscii.WriteHex(static_cast<TByte>(ch));
        }
    }
}
