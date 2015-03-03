#include <OpenHome/Media/Protocol/Protocol.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Types.h>
#include <OpenHome/Private/Http.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Uri.h>
#include <OpenHome/Media/Supply.h>

#include <algorithm>

EXCEPTION(HlsVariantPlaylistError);
EXCEPTION(HlsEndOfStream);
EXCEPTION(HlsSegmentError);


namespace OpenHome {
namespace Media {

class ITimerHandler
{
public:
    virtual void TimerFired() = 0;
    virtual ~ITimerHandler() {}
};

class ITimer
{
public:
    virtual void Start(TUint aDurationMs, ITimerHandler& aHandler) = 0;
    virtual void Cancel() = 0;
    virtual ~ITimer() {}
};

class ISemaphore
{
public:
    virtual void Wait() = 0;
    virtual TBool Clear() = 0;
    virtual void Signal() = 0;
    virtual ~ISemaphore() {}
};

class ISegmentUriProvider
{
public:
    virtual TUint NextSegmentUri(Uri& aUri) = 0;    // returns segment duration (in milliseconds)
                                                    // THROWS HlsVariantPlaylistError, HlsEndOfStream.
    virtual ~ISegmentUriProvider() {}
};

class HlsM3uReader : public ITimerHandler, public ISegmentUriProvider
{
private:
    static const TUint kMaxM3uVersion = 2;
    static const TUint kMillisecondsPerSecond = 1000;
public:
    HlsM3uReader(IHttpSocket& aSocket, IReaderBuffered& aReader, ITimer& aTimer, ISemaphore& aSemaphore);
    void SetUri(const Uri& aUri);
    TUint Version() const;
    void Interrupt();
    void Close();
public: // from ITimerHandler
    void TimerFired() override;
public: // from ISegmentUriProvider
    TUint NextSegmentUri(Uri& aUri) override;
private:
    void ReadNextLine();
    TBool ReloadVariantPlaylist();
    TBool PreprocessM3u();
    void SetSegmentUri(Uri& aUri, const Brx& aSegmentUri);
private:
    // FIXME - could have some intelligent logic to limit retries
    // e.g. in addition to waiting for, at the minimum, the target duration (or half target duration if playlist has not changed), could instead choose:
    // max(targetDuration, sum(newSegmentDurations)-targetDuration);
    ITimer& iTimer;
    IHttpSocket& iSocket;
    IReaderBuffered& iReader;
    OpenHome::Uri iUri;
    TUint64 iTotalBytes;
    TUint64 iOffset;
    TUint iVersion;
    TUint64 iLastSegment;
    TUint iTargetDuration;
    TBool iEndlist;
    Brn iNextLine;
    Mutex iLock;
    ISemaphore& iSem;
    TBool iInterrupted;
};

class SegmentStreamer : public IProtocolReader
{
public:
    SegmentStreamer(IHttpSocket& aSocket, IReaderBuffered& aReader);
    void Stream(ISegmentUriProvider& aSegmentUriProvider);
    void Close();
public: // from IProtocolReader
    Brn Read(TUint aBytes) override;
    Brn ReadUntil(TByte aSeparator) override;
    void ReadFlush() override;
    void ReadInterrupt() override;
    Brn ReadRemaining() override;
private:
    void GetNextSegment();
    void EnsureSegmentIsReady();
private:
    IHttpSocket& iSocket;
    IReaderBuffered& iReader;
    ISegmentUriProvider* iSegmentUriProvider;
    OpenHome::Uri iUri;
    TUint64 iTotalBytes;
    TUint64 iOffset;
    TBool iInterrupted;
    Mutex iLock;
};

} // namespace Media
} // namespace OpenHome
