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
EXCEPTION(HlsReaderError);
EXCEPTION(HlsDiscontinuityError);


namespace OpenHome {
namespace Media {

class IHlsTimerHandler
{
public:
    virtual void TimerFired() = 0;
    virtual ~IHlsTimerHandler() {}
};

class IHlsTimer
{
public:
    virtual void Start(TUint aDurationMs, IHlsTimerHandler& aHandler) = 0;
    virtual void Cancel() = 0;
    virtual ~IHlsTimer() {}
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

class IHlsReader
{
public:
    virtual IHttpSocket& Socket() = 0;
    virtual IReader& Reader() = 0;
    virtual ~IHlsReader() {}
};

class HlsM3uReader : public IHlsTimerHandler, public ISegmentUriProvider
{
private:
    static const TUint kMaxM3uVersion = 2;
    static const TUint kMillisecondsPerSecond = 1000;
    static const TUint kMaxLineBytes = 2048;
public:
    HlsM3uReader(IHttpSocket& aSocket, IReader& aReader, IHlsTimer& aTimer, ISemaphore& aSemaphore);
    void SetUri(const Uri& aUri);
    TUint Version() const;
    TBool StreamEnded() const;
    TBool Error() const;
    TBool Discontinuity() const;
    void Interrupt();
    void Close();
public: // from IHlsTimerHandler
    void TimerFired() override;
public: // from ISegmentUriProvider
    TUint NextSegmentUri(Uri& aUri) override;
private:
    void ReadNextLine();
    TBool ReloadVariantPlaylist();
    TBool PreprocessM3u();
    void SetSegmentUri(Uri& aUri, const Brx& aSegmentUri);
private:
    IHlsTimer& iTimer;
    IHttpSocket& iSocket;
    ReaderUntilS<kMaxLineBytes> iReaderUntil;
    OpenHome::Uri iUri;
    TBool iConnected;
    TUint64 iTotalBytes;
    TUint64 iOffset;
    TUint iVersion;
    TUint64 iLastSegment;
    TUint iTargetDuration;
    TBool iEndlist;
    TBool iStreamEnded;
    Brn iNextLine;
    Mutex iLock;
    ISemaphore& iSem;
    TBool iInterrupted;
    TBool iError;
};

class SegmentStreamer : public IReader
{
public:
    SegmentStreamer(IHttpSocket& aSocket, IReader& aReader);
    void Stream(ISegmentUriProvider& aSegmentUriProvider);
    TBool Error() const;
    void Close();
public: // from IReader
    Brn Read(TUint aBytes) override;
    void ReadFlush() override;
    void ReadInterrupt() override;
private:
    void GetNextSegment();
    void EnsureSegmentIsReady();
private:
    IHttpSocket& iSocket;
    IReader& iReader;
    ISegmentUriProvider* iSegmentUriProvider;
    OpenHome::Uri iUri;
    TBool iConnected;
    TUint64 iTotalBytes;
    TUint64 iOffset;
    TBool iInterrupted;
    TBool iError;
    Mutex iLock;

    TUint iSocketConnectTime;
};

} // namespace Media
} // namespace OpenHome
