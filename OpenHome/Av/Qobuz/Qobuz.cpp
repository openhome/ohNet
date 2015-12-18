#include <OpenHome/Av/Qobuz/Qobuz.h>
#include <OpenHome/Av/Credentials.h>
#include <OpenHome/Configuration/ConfigManager.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Types.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Http.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Av/Qobuz/UnixTimestamp.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Media/Debug.h>
#include <OpenHome/Private/md5.h>
#include <OpenHome/Av/Utils/Json.h>

#include <algorithm>
#include <vector>

using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Configuration;


const Brn Qobuz::kHost("www.qobuz.com");
const Brn Qobuz::kId("qobuz.com");
const Brn Qobuz::kVersionAndFormat("/api.json/0.2/");
const Brn Qobuz::kConfigKeySoundQuality("qobuz.com.AudioQuality");

static const TUint kQualityValues[] ={ 5, 6, 7, 27 };

Qobuz::Qobuz(Environment& aEnv, const Brx& aAppId, const Brx& aAppSecret, ICredentialsState& aCredentialsState, IConfigInitialiser& aConfigInitialiser)
    : iEnv(aEnv)
    , iLock("QBZ1")
    , iLockConfig("QBZ2")
    , iCredentialsState(aCredentialsState)
    , iReaderBuf(iSocket)
    , iReaderUntil1(iReaderBuf)
    , iWriterBuf(iSocket)
    , iWriterRequest(iWriterBuf)
    , iReaderResponse(aEnv, iReaderUntil1)
    , iDechunker(iReaderUntil1)
    , iReaderUntil2(iDechunker)
    , iUnixTimestamp(aEnv)
    , iAppId(aAppId)
    , iAppSecret(aAppSecret)
{
    iReaderResponse.AddHeader(iHeaderContentLength);
    iReaderResponse.AddHeader(iHeaderTransferEncoding);

    const int arr[] = {0, 1, 2, 3};
    /* 'arr' above describes the highest possible quality of a Qobuz stream
         5:  320kbps AAC
         6:  FLAC 16-bit, 44.1kHz
         7:  FLAC 24-bit, up to 96kHz
        27:  FLAC 24-bit, up to 192kHz
    */
    std::vector<TUint> qualities(arr, arr + sizeof(arr)/sizeof(arr[0]));
    iConfigQuality = new ConfigChoice(aConfigInitialiser, kConfigKeySoundQuality, qualities, 3);
    iSubscriberIdQuality = iConfigQuality->Subscribe(MakeFunctorConfigChoice(*this, &Qobuz::QualityChanged));
}

Qobuz::~Qobuz()
{
    iConfigQuality->Unsubscribe(iSubscriberIdQuality);
    delete iConfigQuality;
}

TBool Qobuz::TryLogin()
{
    AutoMutex _(iLock);
    return TryLoginLocked();
}

TBool Qobuz::TryGetStreamUrl(const Brx& aTrackId, Bwx& aStreamUrl)
{
    TBool success = false;
    if (!TryConnect()) {
        LOG2(kPipeline, kError, "Qobuz::TryLogin - connection failure\n");
        return false;
    }
    AutoSocketReader _(iSocket, iReaderUntil2);

    // see https://github.com/Qobuz/api-documentation#request-signature for rules on creating request_sig value
    TUint timestamp;
    try {
        timestamp = iUnixTimestamp.Now();
    }
    catch (UnixTimestampUnavailable&) {
        LOG2(kPipeline, kError, "Qobuz::TryLogin - failure to determine network time\n");
        return false;
    }
    Bws<Ascii::kMaxUintStringBytes> audioFormatBuf;
    iLockConfig.Wait();
    Ascii::AppendDec(audioFormatBuf, iSoundQuality);
    iLockConfig.Signal();
    Bws<128> sig("trackgetFileUrlformat_id");
    sig.Append(audioFormatBuf);
    sig.Append("intentstreamtrack_id");
    sig.Append(aTrackId);
    Ascii::AppendDec(sig, timestamp);
    sig.Append(iAppSecret);

    iPathAndQuery.Replace(kVersionAndFormat);
    iPathAndQuery.Append("track/getFileUrl?app_id=");
    iPathAndQuery.Append(iAppId);
    iPathAndQuery.Append("&user_auth_token=");
    iPathAndQuery.Append(iAuthToken);
    iPathAndQuery.Append("&request_ts=");
    Ascii::AppendDec(iPathAndQuery, timestamp);
    iPathAndQuery.Append("&request_sig=");
    AppendMd5(iPathAndQuery, sig);
    iPathAndQuery.Append("&track_id=");
    iPathAndQuery.Append(aTrackId);
    iPathAndQuery.Append("&format_id=");
    iPathAndQuery.Append(audioFormatBuf);
    iPathAndQuery.Append("&intent=stream");

    try {
        const TUint code = WriteRequestReadResponse(Http::kMethodGet, iPathAndQuery);
        if (code != 200) {
            LOG(kError, "Http error - %d - in response to Qobuz::TryGetStreamUrl.  Some/all of response is:\n", code);
            Brn buf = iDechunker.Read(kReadBufferBytes);
            LOG2(kPipeline, kError, "%.*s\n", PBUF(buf));
            THROW(ReaderError);
        }

        static const Brn kTagUrl("url");
        Brn val;
        do {
            val.Set(ReadString());
        } while (val != kTagUrl);
        aStreamUrl.Replace(ReadString());
        Json::Unescape(aStreamUrl);
        success = true;
    }
    catch (HttpError&) {
        LOG2(kPipeline, kError, "HttpError in Qobuz::TryGetStreamUrl\n");
    }
    catch (ReaderError&) {
        LOG2(kPipeline, kError, "ReaderError in Qobuz::TryGetStreamUrl\n");
    }
    catch (WriterError&) {
        LOG2(kPipeline, kError, "WriterError in Qobuz::TryGetStreamUrl\n");
    }
    return success;
}

void Qobuz::Interrupt(TBool aInterrupt)
{
    iSocket.Interrupt(aInterrupt);
}

const Brx& Qobuz::Id() const
{
    return kId;
}

void Qobuz::CredentialsChanged(const Brx& aUsername, const Brx& aPassword)
{
    AutoMutex _(iLockConfig);
    iUsername.Replace(aUsername);
    iPassword.Replace(aPassword);
}

void Qobuz::UpdateStatus()
{
    AutoMutex _(iLock);
    iLockConfig.Wait();
    const TBool noCredentials = (iUsername.Bytes() == 0 && iPassword.Bytes() == 0);
    iLockConfig.Signal();
    if (noCredentials) {
        iCredentialsState.SetState(kId, Brx::Empty(), Brx::Empty());
    }
    else {
        (void)TryLoginLocked();
    }
}

void Qobuz::Login(Bwx& aToken)
{
    AutoMutex _(iLock);
    if (iAuthToken.Bytes() == 0 && !TryLoginLocked()) {
        THROW(CredentialsLoginFailed);
    }
    aToken.Replace(iAuthToken);
}

void Qobuz::ReLogin(const Brx& aCurrentToken, Bwx& aNewToken)
{
    AutoMutex _(iLock);
    if (aCurrentToken == iAuthToken) {
        if (!TryLoginLocked()) {
            THROW(CredentialsLoginFailed);
        }
    }
    aNewToken.Replace(iAuthToken);
}

TBool Qobuz::TryConnect()
{
    OpenHome::Endpoint ep;
    try {
        iSocket.Open(iEnv);
        ep.SetAddress(kHost);
        ep.SetPort(kPort);
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

TBool Qobuz::TryLoginLocked()
{
    TBool updatedStatus = false;
    Bws<50> error;
    TBool success = false;

    if (!TryConnect()) {
        LOG2(kMedia, kError, "Qobuz::TryLogin - connection failure\n");
        iCredentialsState.SetState(kId, Brn("Login Error (Connection Failed): Please Try Again."), Brx::Empty());
        return false;
    }
    AutoSocketReader _(iSocket, iReaderUntil2);

    iPathAndQuery.Replace(kVersionAndFormat);
    iPathAndQuery.Append("user/login?app_id=");
    iPathAndQuery.Append(iAppId);
    iPathAndQuery.Append("&username=");
    iLockConfig.Wait();
    iPathAndQuery.Append(iUsername);
    iPathAndQuery.Append("&password=");
    AppendMd5(iPathAndQuery, iPassword);
    iLockConfig.Signal();

    try {
        const TUint code = WriteRequestReadResponse(Http::kMethodGet, iPathAndQuery);
        if (code != 200) {
            Bws<ICredentials::kMaxStatusBytes> status;
            TUint len = std::min(status.MaxBytes(), iHeaderContentLength.ContentLength());
            if (len > 0) {
                status.Replace(iDechunker.Read(len));
                iCredentialsState.SetState(kId, status, Brx::Empty());
            }
            else {
                status.AppendPrintf("Login Error (Response Code %d): ", code);
                Brn buf = iDechunker.Read(kReadBufferBytes);
                len = std::min(status.MaxBytes() - status.Bytes(), buf.Bytes());
                buf.Set(buf.Ptr(), len);
                status.Append(buf);
                iCredentialsState.SetState(kId, status, Brx::Empty());
            }
            updatedStatus = true;
            LOG2(kPipeline, kError, "Http error - %d - in response to Qobuz login.  Some/all of response is:\n%.*s\n", code, PBUF(status));
            THROW(ReaderError);
        }

        static const Brn kUserAuthToken("user_auth_token");
        Brn val;
        do {
            val.Set(ReadString());
        } while (val != kUserAuthToken);
        iAuthToken.Replace(ReadString());
        iCredentialsState.SetState(kId, Brx::Empty(), iAppId);
        updatedStatus = true;
        success = true;
    }
    catch (HttpError&) {
        error.Append("Login Error (Http Failure): Please Try Again.");
        LOG2(kPipeline, kError, "HttpError in Qobuz::TryLoginLocked\n");
    }
    catch (ReaderError&) {
        error.Append("Login Error (Read Failure): Please Try Again.");
        LOG2(kPipeline, kError, "ReaderError in Qobuz::TryLoginLocked\n");
    }
    catch (WriterError&) {
        error.Append("Login Error (Write Failure): Please Try Again.");
        LOG2(kPipeline, kError, "WriterError in Qobuz::TryLoginLocked\n");
    }

    if (!updatedStatus) {
        iCredentialsState.SetState(kId, error, Brx::Empty());
    }
    return success;
}

TUint Qobuz::WriteRequestReadResponse(const Brx& aMethod, const Brx& aPathAndQuery)
{
    iWriterRequest.WriteMethod(aMethod, aPathAndQuery, Http::eHttp11);
    Http::WriteHeaderHostAndPort(iWriterRequest, kHost, kPort);
    Http::WriteHeaderConnectionClose(iWriterRequest);
    iWriterRequest.WriteFlush();
    iReaderResponse.Read();
    const TUint code = iReaderResponse.Status().Code();
    iDechunker.SetChunked(iHeaderTransferEncoding.IsChunked());
    return code;
}

Brn Qobuz::ReadString()
{
    (void)iReaderUntil2.ReadUntil('\"');
    return iReaderUntil2.ReadUntil('\"');
}

void Qobuz::QualityChanged(Configuration::KeyValuePair<TUint>& aKvp)
{
    iLockConfig.Wait();
    iSoundQuality = kQualityValues[aKvp.Value()];
    iLockConfig.Signal();
}

void Qobuz::AppendMd5(Bwx& aBuffer, const Brx& aToHash)
{ // static
    md5_state_t state;
    md5_byte_t digest[16];
    md5_init(&state);
    md5_append(&state, (const md5_byte_t*)aToHash.Ptr(), aToHash.Bytes());
    md5_finish(&state, digest);
    for (TUint i=0; i<sizeof(digest); i++) {
        Ascii::AppendHex(aBuffer, digest[i]);
    }
}
