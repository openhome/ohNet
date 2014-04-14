#ifndef HEADER_PIPELINE_CODEC
#define HEADER_PIPELINE_CODEC

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Media/Msg.h>
#include <OpenHome/Media/Rewinder.h>

#include <vector>

EXCEPTION(CodecStreamStart);
EXCEPTION(CodecStreamEnded);
EXCEPTION(CodecStreamStopped);
EXCEPTION(CodecStreamFlush);
EXCEPTION(CodecStreamSeek);
EXCEPTION(CodecStreamFeatureUnsupported);

namespace OpenHome {
namespace Media {
    class Logger;
namespace Codec {

/*
Element which holds all audio codecs.
Recognises the format of audio data then decodes it.
Accepts MsgAudioEncoded; outputs MsgAudioPcm.
MsgTrack and MsgStartOfStream are expected and passed through unchanged.
FIXME - no reporting of corrupt/unrecognised file errors.
*/

class ICodecController
{
public:
    virtual void Read(Bwx& aBuf, TUint aBytes) = 0;
    virtual void ReadNextMsg(Bwx& aBuf) = 0;
    virtual TBool TrySeek(TUint aStreamId, TUint64 aBytePos) = 0;
    virtual TUint64 StreamLength() const = 0;
    virtual TUint64 StreamPos() const = 0;
    virtual void OutputDecodedStream(TUint aBitRate, TUint aBitDepth, TUint aSampleRate, TUint aNumChannels, const Brx& aCodecName, TUint64 aTrackLength, TUint64 aSampleStart, TBool aLossless) = 0;
    virtual TUint64 OutputAudioPcm(const Brx& aData, TUint aChannels, TUint aSampleRate, TUint aBitDepth, EMediaDataEndian aEndian, TUint64 aTrackOffset) = 0; // returns jiffy size of data
    virtual TUint64 OutputAudioPcm(const Brx& aData, TUint aChannels, TUint aSampleRate, TUint aBitDepth, EMediaDataEndian aEndian, TUint64 aTrackOffset, TUint aRxTimestamp, TUint aLatency, TUint aNetworkTimestamp, TUint aMediaTimestamp) = 0; // returns jiffy size of data
    virtual void OutputWait() = 0;
    virtual void OutputHalt() = 0;
};
    
class CodecBase
{
    friend class CodecController;
public:
    virtual ~CodecBase();
public:
    virtual TBool SupportsMimeType(const Brx& aMimeType) = 0;
    virtual TBool Recognise() = 0;
    virtual void StreamInitialise();
    virtual void Process() = 0;
    virtual TBool TrySeek(TUint aStreamId, TUint64 aSample) = 0;
    virtual void StreamCompleted();
protected:
    CodecBase();
private:
    void Construct(ICodecController& aController);
protected:
    ICodecController* iController;
};

class CodecController : public ISeeker, private ICodecController, private IMsgProcessor, private IStreamHandler, private INonCopyable
{
public:
    CodecController(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstreamElement, IPipelineElementDownstream& aDownstreamElement);
    virtual ~CodecController();
    void AddCodec(CodecBase* aCodec);
    void Start();
    TBool SupportsMimeType(const Brx& aMimeType);
private:
    void CodecThread();
    void Rewind();
    Msg* PullMsg();
    void Queue(Msg* aMsg);
    TBool QueueTrackData() const;
    void ReleaseAudioEncoded();
    TBool DoRead(Bwx& aBuf, TUint aBytes);
private: // ISeeker
    void StartSeek(TUint aTrackId, TUint aStreamId, TUint aSecondsAbsolute, ISeekObserver& aObserver, TUint& aHandle);
private: // ICodecController
    void Read(Bwx& aBuf, TUint aBytes);
    void ReadNextMsg(Bwx& aBuf);
    TBool TrySeek(TUint aStreamId, TUint64 aBytePos);
    TUint64 StreamLength() const;
    TUint64 StreamPos() const;
    void OutputDecodedStream(TUint aBitRate, TUint aBitDepth, TUint aSampleRate, TUint aNumChannels, const Brx& aCodecName, TUint64 aTrackLength, TUint64 aSampleStart, TBool aLossless);
    TUint64 OutputAudioPcm(const Brx& aData, TUint aChannels, TUint aSampleRate, TUint aBitDepth, EMediaDataEndian aEndian, TUint64 aTrackOffset);
    TUint64 OutputAudioPcm(const Brx& aData, TUint aChannels, TUint aSampleRate, TUint aBitDepth, EMediaDataEndian aEndian, TUint64 aTrackOffset, TUint aRxTimestamp, TUint aLatency, TUint aNetworkTimestamp, TUint aMediaTimestamp);
    void OutputWait();
    void OutputHalt();
private: // IMsgProcessor
    Msg* ProcessMsg(MsgTrack* aMsg);
    Msg* ProcessMsg(MsgEncodedStream* aMsg);
    Msg* ProcessMsg(MsgAudioEncoded* aMsg);
    Msg* ProcessMsg(MsgMetaText* aMsg);
    Msg* ProcessMsg(MsgHalt* aMsg);
    Msg* ProcessMsg(MsgFlush* aMsg);
    Msg* ProcessMsg(MsgWait* aMsg);
    Msg* ProcessMsg(MsgDecodedStream* aMsg);
    Msg* ProcessMsg(MsgAudioPcm* aMsg);
    Msg* ProcessMsg(MsgSilence* aMsg);
    Msg* ProcessMsg(MsgPlayable* aMsg);
    Msg* ProcessMsg(MsgQuit* aMsg);
private: // IStreamHandler
    EStreamPlay OkToPlay(TUint aTrackId, TUint aStreamId);
    TUint TrySeek(TUint aTrackId, TUint aStreamId, TUint64 aOffset);
    TUint TryStop(TUint aTrackId, TUint aStreamId);
private:
    static const TUint kMaxRecogniseBytes = 6 * 1024;
    MsgFactory& iMsgFactory;
    Rewinder iRewinder;
    Logger* iLoggerRewinder;
    IPipelineElementDownstream& iDownstreamElement;
    Mutex iLock;
    std::vector<CodecBase*> iCodecs;
    ThreadFunctor* iDecoderThread;
    CodecBase* iActiveCodec;
    MsgQueue iQueue;
    Msg* iPendingMsg;
    TBool iQueueTrackData;
    TBool iStreamStarted;
    TBool iStreamEnded;
    TBool iStreamStopped;
    TBool iQuit;
    TBool iSeek;
    TBool iRecognising;
    TUint iSeekSeconds;
    TUint iExpectedFlushId;
    TBool iConsumeExpectedFlush;
    ISeekObserver* iSeekObserver;
    TUint iSeekHandle;
    MsgDecodedStream* iPostSeekStreamInfo;
    MsgAudioEncoded* iAudioEncoded;
    TByte iReadBuf[kMaxRecogniseBytes];
    TBool iSeekable;
    TBool iLive;
    IStreamHandler* iStreamHandler;
    TUint iStreamId;
    TUint iSampleRate;
    TUint64 iStreamLength;
    TUint64 iStreamPos;
    TUint iTrackId;
};

} // namespace Codec
} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_CODEC
