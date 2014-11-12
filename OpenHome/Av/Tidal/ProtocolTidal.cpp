#include <OpenHome/Media/Protocol/ProtocolFactory.h>
#include <OpenHome/Media/Protocol/Protocol.h>
#include <OpenHome/Av/Credentials.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Types.h>
#include <OpenHome/Configuration/ConfigManager.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Uri.h>
#include <OpenHome/Media/Debug.h>
#include <OpenHome/Private/Parser.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Av/Tidal/Tidal.h>
        
namespace OpenHome {
namespace Av {

class ProtocolTidal : public Media::Protocol
{
public:
    ProtocolTidal(Environment& aEnv, const Brx& aToken, Av::Credentials& aCredentialsManager, Configuration::IConfigInitialiser& aConfigInitialiser);
    ~ProtocolTidal();
private: // from Media::Protocol
    void Interrupt(TBool aInterrupt) override;
    Media::ProtocolStreamResult Stream(const Brx& aUri) override;
    Media::ProtocolGetResult Get(IWriter& aWriter, const Brx& aUri, TUint64 aOffset, TUint aBytes) override;
private: // from Media::IStreamHandler
    Media::EStreamPlay OkToPlay(TUint aTrackId, TUint aStreamId) override;
    TUint TrySeek(TUint aTrackId, TUint aStreamId, TUint64 aOffset) override;
    TUint TryStop(TUint aTrackId, TUint aStreamId) override;
    TBool TryGet(IWriter& aWriter, TUint aTrackId, TUint aStreamId, TUint64 aOffset, TUint aBytes) override;
private:
    static TBool TryGetTrackId(const Brx& aQuery, Brn& aTrackId);
private:
    Tidal* iTidal;
    Uri iUri;
    Bws<1024> iStreamUrl;
};

};  // namespace Av
};  // namespace OpenHome

using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Media;
using namespace OpenHome::Configuration;


Protocol* ProtocolFactory::NewTidal(Environment& aEnv, const Brx& aToken, Av::Credentials& aCredentialsManager, IConfigInitialiser& aConfigInitialiser)
{ // static
    return new ProtocolTidal(aEnv, aToken, aCredentialsManager, aConfigInitialiser);
}


// ProtocolTidal

ProtocolTidal::ProtocolTidal(Environment& aEnv, const Brx& aToken, Credentials& aCredentialsManager, IConfigInitialiser& aConfigInitialiser)
    : Protocol(aEnv)
{
    iTidal = new Tidal(aEnv, aToken, aCredentialsManager, aConfigInitialiser);
    aCredentialsManager.Add(iTidal);
}

ProtocolTidal::~ProtocolTidal()
{
}

void ProtocolTidal::Interrupt(TBool aInterrupt)
{
    iTidal->Interrupt(aInterrupt);
}

ProtocolStreamResult ProtocolTidal::Stream(const Brx& aUri)
{
    iTidal->Interrupt(false);
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
    ProtocolStreamResult res = EProtocolStreamErrorUnrecoverable;
    if (iTidal->TryGetStreamUrl(trackId, sessionId, iStreamUrl)) {
        res = iProtocolManager->Stream(iStreamUrl);
        (void)iTidal->TryLogout(sessionId);
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
