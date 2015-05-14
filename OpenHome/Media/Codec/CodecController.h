#ifndef HEADER_PIPELINE_CODEC
#define HEADER_PIPELINE_CODEC

#include <OpenHome/Types.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/Pipeline/Rewinder.h>

#include <vector>

EXCEPTION(CodecStreamStart);
EXCEPTION(CodecStreamEnded);
EXCEPTION(CodecStreamStopped);
EXCEPTION(CodecStreamFlush);
EXCEPTION(CodecStreamFeatureUnsupported);

namespace OpenHome {
namespace Media {
    class Logger;
namespace Codec {

/**
 * Interface used by codecs to communicate with the pipeline.
 */
class ICodecController
{
public:
    /**
     * Read up to a specified number of bytes.
     *
     * Appends to the client's buffer.  May return a smaller number of bytes than
     * requested at the end of the stream.
     *
     * @param[in] aBuf           Buffer to write into.  Data is appended to any existing content.
     * @param[in] aBytes         Number of bytes to read.
     *                           Fewer bytes may be returned at the end of a stream.
     */
    virtual void Read(Bwx& aBuf, TUint aBytes) = 0;
    /**
     * Read the content of the next audio msg.
     *
     * Appends to the client's buffer.  May return less than the content of a single
     * audio msg if the audio data is larger than the client's buffer.
     * This offers a small efficiency gain for audio formats that are transmitted in frames
     * which can only be processed in their entirety.
     *
     * @param[in] aBuf           Buffer to write into.  Data is appended to any existing content.
     */
    virtual void ReadNextMsg(Bwx& aBuf) = 0;
    /**
     * Read a block of data out of band, without affecting the state of the current stream.
     *
     * This is useful if a codec's Recognise() function requires data from near the end
     * of a stream.  (Seeking during recognition would be awkward; calling Read() repeatedly
     * would attempt to buffer more data than the pipeline supports and would risk a protocol
     * module moving on to the next stream.)
     * This is relatively inefficient so should be used with care.  (Use during recognition is
     * likely reasonable; use during decoding would be questionable.)
     *
     * @param[in] aWriter        Interface used to return the requested data.
     * @param[in] aOffset        Byte offset into the stream.
     * @param[in] aBytes         Length (in bytes) of data to be read.
     *
     * @return     true if the read succeeded; false if [0..aBytes) were written.
     */
    virtual TBool Read(IWriter& aWriter, TUint64 aOffset, TUint aBytes) = 0;
    /**
     * Request a seek to a different point in the stream.
     *
     * @param[in] aStreamId      Stream identifier.  Passed to a codec's TrySeek() function.
     * @param[in] aBytePos       Byte offset to seek to.
     *
     * @return     true if the request succeeded (the next call to Read() will return data from aBytePos);
     *             false if the request failed.
     */
    virtual TBool TrySeekTo(TUint aStreamId, TUint64 aBytePos) = 0;
    /**
     * Query the length (in bytes) of the current stream.
     *
     * @return     The total number of bytes in the current stream; 0 if this isn't available.
     */
    virtual TUint64 StreamLength() const = 0;
    /**
     * Query our position in the current stream.
     *
     * The next call to Read() will return data at this position.
     *
     * @return     Number of bytes the codec has consumed from the stream.
     */
    virtual TUint64 StreamPos() const = 0;
    /**
     * Notify the pipeline of a new stream or a discontinuity in the current stream.
     *
     * Must be called before any other Output function at the start of a stream,  This is
     * typically done from either StreamInitialise() or Process().  Must also be called after
     * a successful seek.  Should not be called at any other times.
     *
     * @param[in] aBitRate       The bit rate of the stream.  Reported to UI code; not used by the pipeline.
     * @param[in] aBitDepth      The bit depth of the decoded stream.  Must be one of 8, 16 or 24.
     * @param[in] aSampleRate    The sample rate of the decoded stream.
     * @param[in] aNumChannels   The number of channels in the decoded stream.  Must be in the range [2..8].
     * @param[in] aCodecName     The name of the codec.  Reported to UI code; not used by the pipeline.
     * @param[in] aLength        Number of bytes in the encoded stream.  Reported to UI code; not used by the pipeline.
     * @param[in] aSampleStart   The first sample number in the next audio data to be output.  0 at the start of a stream.
     * @param[in] aLossless      Whether the stream is in a lossless format.  Reported to UI code; not used by the pipeline.
     */
    virtual void OutputDecodedStream(TUint aBitRate, TUint aBitDepth, TUint aSampleRate, TUint aNumChannels, const Brx& aCodecName, TUint64 aLength, TUint64 aSampleStart, TBool aLossless) = 0;
    /**
     * Notify the pipeline of a change in delay (latency).
     *
     * Only used for audio formats which embed latency requirements with audio data.
     * Any change in delay will be applied after any previously output audio is played
     * but before any subsequent audio.
     *
     * @param[in] aJiffies       Delay in Jiffies.
     */
    virtual void OutputDelay(TUint aJiffies) = 0;
    /**
     * Add a block of decoded (PCM) audio to the pipeline.
     *
     * @param[in] aData          PCM audio data.  Must contain an exact number of samples.
     *                           i.e. aData.Bytes() % (aChannels * aBitDepth/8) == 0
     * @param[in] aChannels      Number of channels.  Must be in the range [2..8].
     * @param[in] aSampleRate    Sample rate.
     * @param[in] aBitDepth      Number of bits of audio for a single sample for a single channel.
     * @param[in] aEndian        Endianness of audio data.
     * @param[in] aTrackOffset   Offset (in jiffies) into the stream at the start of aData.
     *
     * @return     Number of jiffies of audio contained in aData.
     */
    virtual TUint64 OutputAudioPcm(const Brx& aData, TUint aChannels, TUint aSampleRate, TUint aBitDepth, EMediaDataEndian aEndian, TUint64 aTrackOffset) = 0;
    /**
     * Add a block of decoded (PCM) audio to the pipeline.
     *
     * Includes the same functionality as the 6-argument overload but also specifies
     * timestamps, allowing for synchronised playback.
     *
     * @param[in] aData          PCM audio data.  Must contain an exact number of samples.
     *                           i.e. aData.Bytes() % (aChannels * aBitDepth/8) == 0
     * @param[in] aChannels      Number of channels.  Must be in the range [2..8].
     * @param[in] aSampleRate    Sample rate.
     * @param[in] aBitDepth      Number of bits of audio for a single sample for a single channel.
     * @param[in] aEndian        Endianness of audio data.
     * @param[in] aTrackOffset   Offset (in jiffies) into the stream at the start of aData.
     * @param[in] aRxTimestamp   Time when encoded frame was received by this device.
     * @param[in] aNetworkTimestamp  Time when the previous encoded frame was sent over the network
     *
     * @return     Number of jiffies of audio contained in aData.
     */
    virtual TUint64 OutputAudioPcm(const Brx& aData, TUint aChannels, TUint aSampleRate, TUint aBitDepth, EMediaDataEndian aEndian, TUint64 aTrackOffset, TUint aRxTimestamp, TUint aNetworkTimestamp) = 0;
    /**
     * Output a Wait command to the pipeline.
     *
     * This hints that there may now be a break in audio.  This break would be expected
     * so the pipeline will report its state as Waiting rather than Buffering.
     */
    virtual void OutputWait() = 0;
    /**
     * Output a Halt command to the pipeline.
     *
     * This hints that a break in audio may follow.  The publisher of the audio stream
     * anticipated this and has already ramped the audio down.  The pipeline will not ramp
     * down if network exhaustion immediately follows a Halt command.
     */
    virtual void OutputHalt() = 0;
    /**
     * Output a Session command to the pipeline.
     *
     * This informs the pipeline about a discontinuity in audio, allowing it to apply
     * ramps or delays as appropriate.
     */
    virtual void OutputSession() = 0;
    /**
     * Notify the pipeline of an update in meta text.
     *
     * This allows the pipeline to output additional information about a stream.
     *
     * @param[in] aMetaText          Meta text. Must be in DIDL-Lite format.
     */
    virtual void OutputMetaText(const Brx& aMetaText) = 0;
};

class EncodedStreamInfo
{
    friend class CodecController;
public:
    TBool RawPcm() const;
    TUint BitDepth() const;
    TUint SampleRate() const;
    TUint NumChannels() const;
    EMediaDataEndian Endian() const;
    TUint64 StartSample() const;
private:
    EncodedStreamInfo();
    void Set(TUint aBitDepth, TUint aSampleRate, TUint aNumChannels, EMediaDataEndian aEndian, TUint64 aStartSample);
private:
    TBool iRawPcm;
    TUint iBitDepth;
    TUint iSampleRate;
    TUint iNumChannels;
    EMediaDataEndian iEndian;
    TUint64 iStartSample;
};
    
/**
 * Base class for all codecs.
 *
 * A codec accepts encoded data and outputs PCM.
 * Each instance can choose to decode one or more audio formats.
 */
class CodecBase
{
    friend class CodecController;
public:
    virtual ~CodecBase();
public:
    /**
     * Query whether a given audio format is supported.
     *
     * @param[in] aMimeType      MIME type of the form type/subtype.  All lowercase.
     *
     * @return     true if the codec can decode aMimeType; false otherwise.
     */
    virtual TBool SupportsMimeType(const Brx& aMimeType) = 0;
    /**
     * Report whether a new audio stream is handled by this codec.
     *
     * Data is fetched by calling iController->Read().  Any data read during recognition will
     * also be made available to other codecs (if recognition fails) or this codec again
     * during processing (if recognition succeeds).
     *
     * @param[in] aStreamInfo    Details Info describing the current encoded stream
     *
     * @return     true if this codec can decode the audio stream; false otherwise.
     */
    virtual TBool Recognise(const EncodedStreamInfo& aStreamInfo) = 0;
    /**
     * Notify a codec that decoding of a stream is about to begin.
     *
     * Called after Recognise() succeeds but before any call to Process().
     * May be used to initialise any state that is specific to the current stream.
     */
    virtual void StreamInitialise();
    /**
     * Decode a chunk of the stream.
     *
     * Will be called repeatedly until the stream is fully decoded.
     * Call iController->Read() to pull encoded data.  Each call can decode as much or as
     * little audio as is convenient.  Note however that decoding in very large blocks
     * risks delaying any Seek requests.
     * Can either throw CodecStreamEnded or just continue to try reading (causing an exception
     * to be thrown) to indicate it has reached the end of the stream.
     */
    virtual void Process() = 0;
    /**
     * Seek to a given sample position in the stream.
     *
     * The codec should translate the specified sample position into a byte offset then call
     * iController->TrySeekTo().  The controller can be called many times for a single seek
     * request if necessary.
     * @param[in] aStreamId      Stream identifier.  Passed to iController->TrySeekTo().
     * @param[in] aSample        Decoded sample position (zero-based) to seek to.
     *
     * @return     true if the seek succeeded; false otherwise.
     */
    virtual TBool TrySeek(TUint aStreamId, TUint64 aSample) = 0;
    /**
     * Notify a codec that decoding of a stream has finished.
     *
     * Called after the final call to Process() for a stream.
     * May be used to destroy any state that is specific to the current stream.
     */
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
    CodecController(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstreamElement, IPipelineElementDownstream& aDownstreamElement,
                    IUrlBlockWriter& aUrlBlockWriter, TUint aThreadPriority);
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
    void StartSeek(TUint aStreamId, TUint aSecondsAbsolute, ISeekObserver& aObserver, TUint& aHandle);
private: // ICodecController
    void Read(Bwx& aBuf, TUint aBytes);
    void ReadNextMsg(Bwx& aBuf);
    TBool Read(IWriter& aWriter, TUint64 aOffset, TUint aBytes); // Read an arbitrary amount of data from current stream, out-of-band from pipeline
    TBool TrySeekTo(TUint aStreamId, TUint64 aBytePos);
    TUint64 StreamLength() const;
    TUint64 StreamPos() const;
    void OutputDecodedStream(TUint aBitRate, TUint aBitDepth, TUint aSampleRate, TUint aNumChannels, const Brx& aCodecName, TUint64 aTrackLength, TUint64 aSampleStart, TBool aLossless);
    void OutputDelay(TUint aJiffies);
    TUint64 OutputAudioPcm(const Brx& aData, TUint aChannels, TUint aSampleRate, TUint aBitDepth, EMediaDataEndian aEndian, TUint64 aTrackOffset);
    TUint64 OutputAudioPcm(const Brx& aData, TUint aChannels, TUint aSampleRate, TUint aBitDepth, EMediaDataEndian aEndian, TUint64 aTrackOffset, TUint aRxTimestamp, TUint aNetworkTimestamp);
    void OutputWait();
    void OutputHalt();
    void OutputSession();
    void OutputMetaText(const Brx& aMetaText);
private: // IMsgProcessor
    Msg* ProcessMsg(MsgMode* aMsg) override;
    Msg* ProcessMsg(MsgSession* aMsg) override;
    Msg* ProcessMsg(MsgTrack* aMsg) override;
    Msg* ProcessMsg(MsgDelay* aMsg) override;
    Msg* ProcessMsg(MsgEncodedStream* aMsg) override;
    Msg* ProcessMsg(MsgAudioEncoded* aMsg) override;
    Msg* ProcessMsg(MsgMetaText* aMsg) override;
    Msg* ProcessMsg(MsgHalt* aMsg) override;
    Msg* ProcessMsg(MsgFlush* aMsg) override;
    Msg* ProcessMsg(MsgWait* aMsg) override;
    Msg* ProcessMsg(MsgDecodedStream* aMsg) override;
    Msg* ProcessMsg(MsgAudioPcm* aMsg) override;
    Msg* ProcessMsg(MsgSilence* aMsg) override;
    Msg* ProcessMsg(MsgPlayable* aMsg) override;
    Msg* ProcessMsg(MsgQuit* aMsg) override;
private: // IStreamHandler
    EStreamPlay OkToPlay(TUint aStreamId) override;
    TUint TrySeek(TUint aStreamId, TUint64 aOffset) override;
    TUint TryStop(TUint aStreamId) override;
    void NotifyStarving(const Brx& aMode, TUint aStreamId) override;
private:
    static const TUint kMaxRecogniseBytes = 6 * 1024;
    MsgFactory& iMsgFactory;
    Rewinder iRewinder;
    Logger* iLoggerRewinder;
    IPipelineElementDownstream& iDownstreamElement;
    IUrlBlockWriter& iUrlBlockWriter;
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
    TUint iExpectedSeekFlushId;
    MsgDecodedStream* iPostSeekStreamInfo;
    MsgAudioEncoded* iAudioEncoded;

    TBool iSeekable;
    TBool iLive;
    TBool iRawPcm;
    PcmStreamInfo iPcmStream;
    IStreamHandler* iStreamHandler;
    TUint iStreamId;
    BwsTrackUri iTrackUri;
    TUint iSampleRate;
    TUint64 iStreamLength;
    TUint64 iStreamPos;
    TUint iTrackId;
};

class CodecBufferedReader : public IReader, private INonCopyable
{
private:
    enum EState
    {
        eReading,
        eEos,
        eBeyondEos,
    };
public:
    CodecBufferedReader(ICodecController& aCodecController, Bwx& aBuf);
public: // from IReader
    Brn Read(TUint aBytes) override; // Returns [0..aBytes].  0 => stream closed, followed by ReaderError on subsequent reads beyond end of stream.
    void ReadFlush() override;
    void ReadInterrupt() override;  // ASSERTS
private:
    ICodecController& iCodecController;
    Bwx& iBuf;
    EState iState;
};

} // namespace Codec
} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_CODEC
