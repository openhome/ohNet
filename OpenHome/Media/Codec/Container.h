#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Private/Uri.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/Pipeline/Rewinder.h>
#include <OpenHome/Media/Pipeline/Logger.h>

#include <atomic>
#include <vector>

EXCEPTION(CodecStreamCorrupt);
EXCEPTION(CodecPulledNullMsg);
EXCEPTION(AudioCacheException); // Thrown if IMsgAudioEncodedCache implementation can't fulfill a request during a Pull() (e.g., trying to perform an out-of-band read from a server which does not support partial gets).
EXCEPTION(ContainerStreamCorrupt);

namespace OpenHome {
namespace Media {
namespace Codec {

/**
 * Element which strips any container data from a file.
 * Complex containers which read a stream, skip some data, read another stream
 * repeatedly, not just parse a header at the start of a file, are implementable
 * as IContainerBase plugins.
 */

class IMsgAudioEncodedCache
{
public:
    /**
     * Set cache to discard a given number of bytes, followed by reading a given number of bytes.
     */
    virtual void Discard(TUint aBytes) = 0;
    virtual void Inspect(Bwx& aBuf, TUint aBytes) = 0;
    virtual void Accumulate(TUint aBytes) = 0;
    /**
     * Discard until discard bytes has been reached.
     * Then, read into expect buffer until full, at which point nullptr is returned.
     * Then, accumulate until accumulate bytes has been reached, at which point a MsgAudioEncoded of accumulated bytes must be returned.
     * Further pulls beyond this should return messages in order and un-modified (i.e. go into pass-through mode).
     * If a non-MsgAudioEncoded msg is encountered, it is returned immediately and any caching operations resume on the next call (i.e., state is retained).
     */
    virtual Msg* Pull() = 0;    // THROWS CodecPulledNullMsg.
    virtual ~IMsgAudioEncodedCache() {}
};

class IContainerSeekHandler
{
public:
    virtual TBool TrySeekTo(TUint aStreamId, TUint64 aBytePos) = 0;
    virtual ~IContainerSeekHandler() {}
};

class IContainerUrlBlockWriter
{
public:
    virtual TBool TryGetUrl(IWriter& aWriter, TUint64 aOffset, TUint aBytes) = 0;
    virtual ~IContainerUrlBlockWriter() {}
};

class IContainerStopper
{
public:
    virtual void ContainerTryStop() = 0;
    virtual ~IContainerStopper() {}
};

class ContainerController;

class ContainerBase : public IPipelineElementUpstream, private INonCopyable
{
    friend class ContainerController;
private:
    static const TUint kMaxNameBytes = 4;
protected:
    ContainerBase(const Brx& aId);
public:
    virtual Msg* Recognise() = 0;   // Returns nullptr upon recognition complete.
    virtual TBool Recognised() const = 0; // Can only be called after Recognise() returns nullptr.
    virtual void Reset() = 0;
    virtual void Init(TUint64 aStreamBytes) = 0;
    virtual TBool TrySeek(TUint aStreamId, TUint64 aOffset) = 0;
    const Brx& Id() const;
protected:
    virtual void Construct(IMsgAudioEncodedCache& aCache, MsgFactory& aMsgFactory, IContainerSeekHandler& aSeekHandler, IContainerUrlBlockWriter& aUrlBlockWriter, IContainerStopper& aContainerStopper);
public: // from IPipelineElementUpstream
    Msg* Pull() = 0;
protected:
    IMsgAudioEncodedCache* iCache;
    MsgFactory* iMsgFactory;
    IContainerSeekHandler* iSeekHandler;
    IContainerUrlBlockWriter* iUrlBlockWriter;
    IContainerStopper* iStopper;
private:
    const Bws<kMaxNameBytes> iId;
};

class MsgAudioEncodedCache : public IMsgAudioEncodedCache, public IMsgProcessor, private INonCopyable
{
public:
    MsgAudioEncodedCache(IPipelineElementUpstream& aUpstreamElement);
    ~MsgAudioEncodedCache();
    void Reset();
    void SetFlushing(TUint aFlushId);
private:
    TUint CacheBytes() const;
    MsgAudioEncoded* ProcessCache();
    TBool PendingInspectionBuffer() const;
    TBool InspectionBufferFilled() const;
    MsgAudioEncoded* ExtractMsgAudioEncoded(TUint aBytes);
    Msg* PullUpstreamMsg();
public: // from IMsgAudioEncodedCache
    void Discard(TUint aBytes) override;
    void Inspect(Bwx& aBuf, TUint aBytes) override;
    void Accumulate(TUint aBytes) override;
    Msg* Pull() override;
private: // from IMsgProcessor
    Msg* ProcessMsg(MsgMode* aMsg) override;
    Msg* ProcessMsg(MsgTrack* aMsg) override;
    Msg* ProcessMsg(MsgDrain* aMsg) override;
    Msg* ProcessMsg(MsgDelay* aMsg) override;
    Msg* ProcessMsg(MsgEncodedStream* aMsg) override;
    Msg* ProcessMsg(MsgAudioEncoded* aMsg) override;
    Msg* ProcessMsg(MsgMetaText* aMsg) override;
    Msg* ProcessMsg(MsgStreamInterrupted* aMsg) override;
    Msg* ProcessMsg(MsgHalt* aMsg) override;
    Msg* ProcessMsg(MsgFlush* aMsg) override;
    Msg* ProcessMsg(MsgWait* aMsg) override;
    Msg* ProcessMsg(MsgDecodedStream* aMsg) override;
    Msg* ProcessMsg(MsgBitRate* aMsg) override;
    Msg* ProcessMsg(MsgAudioPcm* aMsg) override;
    Msg* ProcessMsg(MsgSilence* aMsg) override;
    Msg* ProcessMsg(MsgPlayable* aMsg) override;
    Msg* ProcessMsg(MsgQuit* aMsg) override;
private:
    IPipelineElementUpstream& iUpstreamElement;
    MsgAudioEncoded* iAudioEncoded;
    TUint iDiscardBytesRemaining;
    TUint iInspectBytesRemaining;
    TUint iAccumulateBytesRemaining;
    TUint iInspectBufferBytes;
    Bwx* iBuffer;
    TUint iExpectedFlushId;
    Mutex iLock;
};

class ContainerNull : public ContainerBase
{
public:
    ContainerNull();
public: // from ContainerBase
    Msg* Recognise() override;
    TBool Recognised() const override;
    void Reset() override;
    void Init(TUint64 aStreamBytes) override;
    TBool TrySeek(TUint aStreamId, TUint64 aOffset) override;
    Msg* Pull() override;
};

/**
 * Container that can be used to discard all audio from a stream but still pass
 * on non-audio messages.
 */
class ContainerDiscard : public ContainerBase
{
public:
    ContainerDiscard();
public: // from ContainerBase
    Msg* Recognise() override;
    TBool Recognised() const override;
    void Reset() override;
    void Init(TUint64 aStreamBytes) override;
    TBool TrySeek(TUint aStreamId, TUint64 aOffset) override;
    Msg* Pull() override;
};

class ContainerController : public IPipelineElementUpstream, private IMsgProcessor, public IStreamHandler, public IContainerSeekHandler, public IContainerUrlBlockWriter, public IContainerStopper, private INonCopyable
{
public:
    ContainerController(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstreamElement, IUrlBlockWriter& aUrlBlockWriter);
    ~ContainerController();
    void AddContainer(ContainerBase* aContainer);
private:
    Msg* RecogniseContainer();
public: // from IPipelineElementUpstream
    Msg* Pull() override;
private: // IMsgProcessor
    Msg* ProcessMsg(MsgMode* aMsg) override;
    Msg* ProcessMsg(MsgTrack* aMsg) override;
    Msg* ProcessMsg(MsgDrain* aMsg) override;
    Msg* ProcessMsg(MsgDelay* aMsg) override;
    Msg* ProcessMsg(MsgEncodedStream* aMsg) override;
    Msg* ProcessMsg(MsgAudioEncoded* aMsg) override;
    Msg* ProcessMsg(MsgMetaText* aMsg) override;
    Msg* ProcessMsg(MsgStreamInterrupted* aMsg) override;
    Msg* ProcessMsg(MsgHalt* aMsg) override;
    Msg* ProcessMsg(MsgFlush* aMsg) override;
    Msg* ProcessMsg(MsgWait* aMsg) override;
    Msg* ProcessMsg(MsgDecodedStream* aMsg) override;
    Msg* ProcessMsg(MsgBitRate* aMsg) override;
    Msg* ProcessMsg(MsgAudioPcm* aMsg) override;
    Msg* ProcessMsg(MsgSilence* aMsg) override;
    Msg* ProcessMsg(MsgPlayable* aMsg) override;
    Msg* ProcessMsg(MsgQuit* aMsg) override;
public: // from IStreamHandler
    EStreamPlay OkToPlay(TUint aStreamId) override;
    TUint TrySeek(TUint aStreamId, TUint64 aOffset) override;
    TUint TryDiscard(TUint aJiffies) override;
    TUint TryStop(TUint aStreamId) override;
    void NotifyStarving(const Brx& aMode, TUint aStreamId, TBool aStarving) override;
private: // from IContainerSeekHandler
    TBool TrySeekTo(TUint aStreamId, TUint64 aBytePos) override;
private: // from IContainerUrlBlockWriter
    TBool TryGetUrl(IWriter& aWriter, TUint64 aOffset, TUint aBytes) override;
private: // from IContainerStopper
    void ContainerTryStop() override;
private:
    enum ERecognitionState
    {
        eRecognitionStart,
        eRecognitionSelectContainer,
        eRecognitionContainer,
        eRecognitionComplete,
    };
private:
    MsgFactory& iMsgFactory;
    IUrlBlockWriter& iUrlBlockWriter;
    Rewinder iRewinder;
    Logger iLoggerRewinder;
    MsgAudioEncodedCache iCache;
    std::vector<ContainerBase*> iContainers;
    ContainerBase* iActiveContainer;
    ContainerNull* iContainerNull;
    ContainerDiscard* iContainerDiscard;
    std::atomic<IStreamHandler*> iStreamHandler;
    Bws<Uri::kMaxUriBytes> iUrl;
    TBool iPassThrough;
    TBool iRecognising;
    ERecognitionState iState;
    TUint iRecogIdx;
    TBool iStreamEnded;
    TUint iStreamId;
    TUint64 iStreamBytes;
    TUint iExpectedFlushId;
    Mutex iLock;
};

class MsgAudioEncodedRecogniser : public IMsgProcessor
{
public:
    MsgAudioEncodedRecogniser();
    void Reset();
    MsgAudioEncoded* AudioEncoded();
private: // from IMsgProcessor
    Msg* ProcessMsg(MsgMode* aMsg) override;
    Msg* ProcessMsg(MsgTrack* aMsg) override;
    Msg* ProcessMsg(MsgDrain* aMsg) override;
    Msg* ProcessMsg(MsgDelay* aMsg) override;
    Msg* ProcessMsg(MsgEncodedStream* aMsg) override;
    Msg* ProcessMsg(MsgAudioEncoded* aMsg) override;
    Msg* ProcessMsg(MsgMetaText* aMsg) override;
    Msg* ProcessMsg(MsgStreamInterrupted* aMsg) override;
    Msg* ProcessMsg(MsgHalt* aMsg) override;
    Msg* ProcessMsg(MsgFlush* aMsg) override;
    Msg* ProcessMsg(MsgWait* aMsg) override;
    Msg* ProcessMsg(MsgDecodedStream* aMsg) override;
    Msg* ProcessMsg(MsgBitRate* aMsg) override;
    Msg* ProcessMsg(MsgAudioPcm* aMsg) override;
    Msg* ProcessMsg(MsgSilence* aMsg) override;
    Msg* ProcessMsg(MsgPlayable* aMsg) override;
    Msg* ProcessMsg(MsgQuit* aMsg) override;
private:
    MsgAudioEncoded* iAudioEncoded;
};

class MsgEncodedStreamRecogniser : public IMsgProcessor
{
public:
    MsgEncodedStreamRecogniser();
    void Reset();
    const TBool RecognisedMsgEncodedStream();
private: // from IMsgProcessor
    Msg* ProcessMsg(MsgMode* aMsg) override;
    Msg* ProcessMsg(MsgTrack* aMsg) override;
    Msg* ProcessMsg(MsgDrain* aMsg) override;
    Msg* ProcessMsg(MsgDelay* aMsg) override;
    Msg* ProcessMsg(MsgEncodedStream* aMsg) override;
    Msg* ProcessMsg(MsgAudioEncoded* aMsg) override;
    Msg* ProcessMsg(MsgMetaText* aMsg) override;
    Msg* ProcessMsg(MsgStreamInterrupted* aMsg) override;
    Msg* ProcessMsg(MsgHalt* aMsg) override;
    Msg* ProcessMsg(MsgFlush* aMsg) override;
    Msg* ProcessMsg(MsgWait* aMsg) override;
    Msg* ProcessMsg(MsgDecodedStream* aMsg) override;
    Msg* ProcessMsg(MsgBitRate* aMsg) override;
    Msg* ProcessMsg(MsgAudioPcm* aMsg) override;
    Msg* ProcessMsg(MsgSilence* aMsg) override;
    Msg* ProcessMsg(MsgPlayable* aMsg) override;
    Msg* ProcessMsg(MsgQuit* aMsg) override;
private:
    TBool iRecognisedMsgEncodedStream;
};

} // namespace Codec
} // namespace Media
} // namespace OpenHome

