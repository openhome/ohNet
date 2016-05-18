#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Http.h>
#include <OpenHome/Private/Timer.h>
#include <OpenHome/Private/Uri.h>
#include <OpenHome/Av/Radio/PresetDatabase.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Configuration/ConfigManager.h>
#include <OpenHome/Av/Credentials.h>

#include <vector>
#include <algorithm>

namespace OpenHome {
    class Environment;
    class Parser;
namespace Configuration {
    class IConfigInitialiser;
    class ConfigText;
}
namespace Media {
    class PipelineManager;
    class MimeTypeList;
}
namespace Av {

class RadioPresetsTuneIn
{
private:
    static const TUint kReadBufBytes = Media::kTrackMetaDataMaxBytes + 1024;
    static const TUint kWriteBufBytes = 1024;
    static const TUint kMaxUserNameBytes = 64;
    static const TUint kMaxPartnerIdBytes = 64;
    static const TUint kReadResponseTimeoutMs = 30 * 1000; // 30 seconds
    static const TUint kRefreshRateMs = 5 * 60 * 1000; // 5 minutes
    static const TUint kMaxPresetTitleBytes = 256;
    static const Brn kConfigKeyUsername;
    static const Brn kConfigUsernameDefault;
    static const Brn kTuneInPresetsRequest;
    static const Brn kFormats;
    static const Brn kPartnerId;
    static const Brn kUsername;
public:
    RadioPresetsTuneIn(Environment& aEnv, const Brx& aPartnerId,
                       IPresetDatabaseWriter& aDbWriter, Configuration::IConfigInitialiser& aConfigInit,
                       Credentials& aCredentialsManager, Media::MimeTypeList& aMimeTypeList);
    ~RadioPresetsTuneIn();
    void Refresh();
private:
    void UpdateUsername(const Brx& aUsername);
    void UsernameChanged(Configuration::KeyValuePair<const Brx&>& aKvp);
    void CurrentAdapterChanged();
    void TimerCallback();
    void RefreshThread();
    void DoRefresh();
    TBool ReadElement(Parser& aParser, const TChar* aKey, Bwx& aValue);
    TBool ValidateKey(Parser& aParser, const TChar* aKey, TBool aLogErrors);
    TBool ReadValue(Parser& aParser, const TChar* aKey, Bwx& aValue);
private:
    Mutex iLock;
    Environment& iEnv;
    IPresetDatabaseWriter& iDbWriter;
    ThreadFunctor* iRefreshThread;
    SocketTcpClient iSocket;
    Uri iRequestUri;
    Sws<kWriteBufBytes> iWriteBuffer;
    WriterHttpRequest iWriterRequest;
    Srs<1024> iReadBuffer;
    ReaderUntilS<kReadBufBytes> iReaderUntil;
    ReaderHttpResponse iReaderResponse;
    HttpHeaderContentLength iHeaderContentLength;
    Timer* iRefreshTimer;
    Bws<40> iSupportedFormats;
    // Following members provide temp storage used while converting OPML elements to Didl-Lite
    Bws<Media::kTrackMetaDataMaxBytes> iDidlLite;
    Bws<Media::kTrackUriMaxBytes> iPresetUrl;
    Uri iPresetUri;
    Bws<Media::kTrackUriMaxBytes> iPresetArtUrl;
    Bws<kMaxPresetTitleBytes> iPresetTitle;
    Configuration::ConfigText* iConfigUsername;
    TUint iListenerId;
    std::vector<TUint> iAllocatedPresets;
    Media::BwsTrackUri iDbUri; // only required in a single function but too large for the stack
    Bws<2*1024> iDbMetaData;
    const Bws<kMaxPartnerIdBytes> iPartnerId;
    TUint iNacnId;
};

class CredentialsTuneIn : public ICredentialConsumer, private INonCopyable
{
    static const Brn kId;
public:
    CredentialsTuneIn(Credentials& aCredentialsManager, const Brx& aPartnerId);
private: // from ICredentialConsumer
    const Brx& Id() const override;
    void CredentialsChanged(const Brx& aUsername, const Brx& aPassword) override;
    void UpdateStatus() override;
    void Login(Bwx& aToken) override;
    void ReLogin(const Brx& aCurrentToken, Bwx& aNewToken) override;
};

} // namespace Av
} // namespace OpenHome

