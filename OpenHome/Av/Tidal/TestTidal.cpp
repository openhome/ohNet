#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/OptionParser.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Types.h>
#include <OpenHome/SocketSsl.h>
#include <OpenHome/Private/Http.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Media/Debug.h>

#include <algorithm>

using namespace OpenHome;
using namespace OpenHome::TestFramework;

class Tidal
{
    static const TUint kReadBufferBytes = 4 * 1024;
    static const TUint kWriteBufferBytes = 1024;
    static const Brn kHost;
    static const TUint kPortHttps = 443;
    static const TUint kPortHttp = 80;
    static const TUint kConnectTimeoutMs = 5000;
public:
    Tidal(Environment& aEnv, const Brx& aToken, const Brx& aUsername, const Brx& aPassword);
    void PrintStreamUrl(const Brx& aTrackId);
private:
    void Login(Bwx& aSessionId, Bwx& aCountryCode);
    Brn GetStreamUrl(const Brx& aTrackId, const Brx& aSessionId, const Brx& aCountryCode);
    void Logout(const Brx& aSessionId);
    TBool Connect(TUint aPort);
    void WriteRequestHeaders(const Brx& aMethod, const Brx& aPathAndQuery, TUint aPort, TUint aContentLength = 0);
    static Brn ReadValue(IReader& aReader, const Brx& aTag);
private:
    SocketSsl iSocket;
    Srs<kReadBufferBytes> iReaderBuf;
    Sws<kWriteBufferBytes> iWriterBuf;
    WriterHttpRequest iWriterRequest;
    ReaderHttpResponse iReaderResponse;
    Bws<32> iToken;
    Bws<32> iUsername;
    Bws<32> iPassword;
};
// Tidal

const Brn Tidal::kHost("api.wimpmusic.com");

Tidal::Tidal(Environment& aEnv, const Brx& aToken, const Brx& aUsername, const Brx& aPassword)
    : iSocket(aEnv, kReadBufferBytes)
    , iReaderBuf(iSocket)
    , iWriterBuf(iSocket)
    , iWriterRequest(iWriterBuf)
    , iReaderResponse(aEnv, iReaderBuf)
    , iToken(aToken)
    , iUsername(aUsername)
    , iPassword(aPassword)
{
}

void Tidal::PrintStreamUrl(const Brx& aTrackId)
{
    try {
        Bws<64> sessionId;
        Bws<8> countryCode;
        Login(sessionId, countryCode);
        try {
            Brn streamUrl = GetStreamUrl(aTrackId, sessionId, countryCode);
            Log::Print("stream url is ");
            Log::Print(streamUrl);
            Log::Print("\n");
        }
        catch (ReaderError&) {
        }
        catch (WriterError&) {
        }
        Logout(sessionId);
    }
    catch (ReaderError&) {
    }
    catch (WriterError&) {
    }
    iSocket.Close();
}

void Tidal::Login(Bwx& aSessionId, Bwx& aCountryCode)
{
    iSocket.SetSecure(true);
    if (!Connect(kPortHttps)) {
        Log::Print("Failed to connect\n");
        return;
    }
    Bws<256> reqBody(Brn("username="));
    reqBody.Append(iUsername);
    reqBody.Append(Brn("&password="));
    reqBody.Append(iPassword);

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
    }
    catch (Exception&) {
        iSocket.Close();
        throw;
    }
    iSocket.Close();
}

Brn Tidal::GetStreamUrl(const Brx& aTrackId, const Brx& aSessionId, const Brx& aCountryCode)
{
    iSocket.SetSecure(false);
    if (!Connect(kPortHttp)) {
        Log::Print("Failed to connect\n");
        return Brx::Empty();
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

        url.Set(ReadValue(iReaderBuf, Brn("url")));
    }
    catch (Exception&) {
        iSocket.Close();
        throw;
    }
    iSocket.Close();
    return url;
}

void Tidal::Logout(const Brx& aSessionId)
{
    iSocket.SetSecure(false);
    iSocket.LogVerbose(true);
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

TBool Tidal::Connect(TUint aPort)
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


void OpenHome::TestFramework::Runner::Main(TInt aArgc, TChar* aArgv[], Net::InitialisationParams* aInitParams)
{
    Environment* env = Net::UpnpLibrary::Initialise(aInitParams);
    OptionParser parser;
    OptionString optionToken("-t", "--token", Brn("tFqyFzmAjgcFSIWv"), "Application token");
    parser.AddOption(&optionToken);
    OptionString optionUsername("-u", "--username", Brn("linndev2"), "Username");
    parser.AddOption(&optionUsername);
    OptionString optionPassword("-p", "--password", Brn("wimphifi"), "Password");
    parser.AddOption(&optionPassword);
    OptionString optionId("-i", "--trackid", Brn("19224234"), "Track ID");
    parser.AddOption(&optionId);
    std::vector<Brn> args = OptionParser::ConvertArgs(aArgc, aArgv);
    if (!parser.Parse(args) || parser.HelpDisplayed()) {
        return;
    }

    Tidal* tidal = new Tidal(*env, optionToken.Value(), optionUsername.Value(), optionPassword.Value());
    tidal->PrintStreamUrl(optionId.Value());
    delete tidal;

    Net::UpnpLibrary::Close();
}
