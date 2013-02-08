#ifndef HEADER_PIPELINE_CODEC
#define HEADER_PIPELINE_CODEC

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Media/Msg.h>

#include <vector>

EXCEPTION(CodecStreamStart);
EXCEPTION(CodecStreamEnded);
EXCEPTION(CodecStreamFlush);
EXCEPTION(CodecStreamSeek);
EXCEPTION(CodecStreamFeatureUnsupported);

namespace OpenHome {
namespace Media {
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
    virtual TBool TrySeek(TUint aStreamId, TUint64 aBytePos) = 0;
    virtual void OutputDecodedStream(TUint aBitRate, TUint aBitDepth, TUint aSampleRate, TUint aNumChannels, const Brx& aCodecName, TUint64 aTrackLength, TUint64 aSampleStart, TBool aLossless) = 0;
    virtual void Output(MsgAudioPcm* aMsg) = 0; // FIXME - might be worth passing data, endianess etc rather than creating Msg inside each codec
};
    
class CodecBase
{
    friend class CodecController;
public:
    virtual ~CodecBase();
public:
    virtual TBool Recognise(const Brx& aData) = 0;
    virtual void StreamInitialise();
    virtual void Process() = 0;
    virtual TBool TrySeek(TUint aStreamId, TUint64 aSample) = 0; // FIXME - no obvious point to bool return
    virtual void StreamCompleted();
protected:
    CodecBase();
private:
    void Construct(ICodecController& aController, MsgFactory& aMsgFactory);
protected:
    ICodecController* iController;
    MsgFactory* iMsgFactory;
};

class CodecController : private ICodecController, private IMsgProcessor, private INonCopyable
{
public:
    CodecController(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstreamElement, IPipelineElementDownstream& aDownstreamElement);
    ~CodecController();
    void AddCodec(CodecBase* aCodec);
    TBool Seek(TUint aTrackId, TUint aStreamId, TUint aSecondsAbsolute);
private:
    void CodecThread();
    void PullMsg();
    void Queue(Msg* aMsg);
    TBool QueueTrackData() const;
    void ReleaseAudioEncoded();
    TBool DoRead(Bwx& aBuf, TUint aBytes);
private: // ICodecController
    void Read(Bwx& aBuf, TUint aBytes);
    TBool TrySeek(TUint aStreamId, TUint64 aBytePos);
    void OutputDecodedStream(TUint aBitRate, TUint aBitDepth, TUint aSampleRate, TUint aNumChannels, const Brx& aCodecName, TUint64 aTrackLength, TUint64 aSampleStart, TBool aLossless);
    void Output(MsgAudioPcm* aMsg);
private: // IMsgProcessor
    Msg* ProcessMsg(MsgAudioEncoded* aMsg);
    Msg* ProcessMsg(MsgAudioPcm* aMsg);
    Msg* ProcessMsg(MsgSilence* aMsg);
    Msg* ProcessMsg(MsgPlayable* aMsg);
    Msg* ProcessMsg(MsgDecodedStream* aMsg);
    Msg* ProcessMsg(MsgTrack* aMsg);
    Msg* ProcessMsg(MsgEncodedStream* aMsg);
    Msg* ProcessMsg(MsgMetaText* aMsg);
    Msg* ProcessMsg(MsgHalt* aMsg);
    Msg* ProcessMsg(MsgFlush* aMsg);
    Msg* ProcessMsg(MsgQuit* aMsg);
private:
    static const TUint kMaxRecogniseBytes = 6 * 1024;
    MsgFactory& iMsgFactory;
    IPipelineElementUpstream& iUpstreamElement;
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
    TBool iQuit;
    TBool iSeek;
    TUint iSeekSeconds;
    TUint iFlushExpectedCount;
    MsgDecodedStream* iPostSeekStreamInfo;
    MsgAudioEncoded* iAudioEncoded;
    TByte iReadBuf[kMaxRecogniseBytes];
    IRestreamer* iRestreamer;
    ILiveStreamer* iLiveStreamer;
    TUint iStreamId;
    TUint iSampleRate;
};


}; // namespace Codec
}; // namespace Media
}; // namespace OpenHome

#endif // HEADER_PIPELINE_CODEC
