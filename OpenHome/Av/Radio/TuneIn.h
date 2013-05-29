#ifndef HEADER_TUNEIN
#define HEADER_TUNEIN

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Http.h>
#include <OpenHome/Private/Timer.h>
#include <OpenHome/Private/Uri.h>
#include <OpenHome/Av/Radio/PresetDatabase.h>
#include <OpenHome/Media/Msg.h>

namespace OpenHome {
class Environment;
namespace Av {

class RadioPresetsTuneIn
{
    static const TUint kReadBufBytes = Media::kTrackMetaDataMaxBytes + 1024;
    static const TUint kWriteBufBytes = 1024;
    static const TUint kMaxUserNameBytes = 64;
    static const TUint kReadResponseTimeoutMs = 30 * 1000; // 30 seconds
    static const TUint kRefreshRateMs = 5 * 60 * 1000; // 5 minutes
    static const Brn kTuneInPresetsRequest;
    static const Brn kFormats;
    static const Brn kPartnerId;
    static const Brn kUsername;
public:
    RadioPresetsTuneIn(Environment& aEnv, IPresetDatabaseWriter& aDbWriter, const Brx& aUserName);
    ~RadioPresetsTuneIn();
    void Refresh();
private:
    void TimerCallback();
    void RefreshThread();
    void DoRefresh();
private:
    Mutex iLock;
    Environment& iEnv;
    IPresetDatabaseWriter& iDbWriter;
    ThreadFunctor* iRefreshThread;
    SocketTcpClient iSocket;
    Uri iRequestUri;
    Sws<kWriteBufBytes> iWriteBuffer;
    WriterHttpRequest iWriterRequest;
    Srs<kReadBufBytes> iReadBuffer;
    ReaderHttpResponse iReaderResponse;
    HttpHeaderContentLength iHeaderContentLength;
    Timer* iRefreshTimer;
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_TUNEIN
