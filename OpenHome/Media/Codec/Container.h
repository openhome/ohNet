#ifndef HEADER_PIPELINE_CONTAINER
#define HEADER_PIPELINE_CONTAINER

#include <OpenHome/Types.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Private/Uri.h>
#include <OpenHome/Media/Pipeline/Msg.h>

EXCEPTION(CodecStreamCorrupt);

namespace OpenHome {
namespace Media {
namespace Codec {

/*
Element which strips any container data from a file.
Complex containers which read a stream, skip some data, read another stream
repeatedly, not just parse a header at the start of a file, are implementable
as IContainerBase plugins.
*/

class IContainer
{
public:
    virtual void Read(Bwx& aBuf, TUint aOffset, TUint aBytes) = 0;
    virtual ~IContainer() {}
};


class IRecogniser
{
public:
    virtual TBool Recognise(Brx& aBuf) = 0;
    virtual ~IRecogniser() {}
};

class IContainerBase : public IRecogniser, public IPipelineElementUpstream, public IStreamHandler
{
public: // from IRecogniser
    virtual TBool Recognise(Brx& aBuf) = 0;
public: // from IPipelineElementUpstream
    virtual Msg* Pull() = 0;
public: // from IStreamHandler
    virtual EStreamPlay OkToPlay(TUint aStreamId) = 0;
    virtual TUint TrySeek(TUint aStreamId, TUint64 aOffset) = 0;
    virtual TUint TryStop(TUint aStreamId) = 0;
    virtual void NotifyStarving(const Brx& aMode, TUint aStreamId, TBool aStarving) = 0;
};

class IContainerUrlBlockWriter
{
public:
    virtual TBool TryGetUrl(IWriter& aWriter, TUint64 aOffset, TUint aBytes) = 0;
    virtual ~IContainerUrlBlockWriter() {}
};

class ContainerBase : public IContainerBase, private IMsgProcessor, private INonCopyable
{
    friend class ContainerFront;
public:
    ContainerBase();
    ~ContainerBase();
protected:
    Msg* PullMsg();
    void AddToAudioEncoded(MsgAudioEncoded* aMsg);
    void ReleaseAudioEncoded();
    void PullAudio(TUint aBytes);
    void DiscardAudio(TUint aBytes);
    void Read(Bwx& aBuf, TUint aBytes);
private:
    void Construct(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstreamElement, IStreamHandler& aStreamHandler, IContainerUrlBlockWriter& aUrlBlockWriter); // FIXME - don't pass istreamhandler here
    TBool ReadFromCachedAudio(Bwx& aBuf, TUint aBytes);
public: // from IRecogniser
    TBool Recognise(Brx& aBuf) = 0;   // need to reset inner container in this method
    //TBool Recognise(Brx& aBuf);
public: // from IPipelineElementUpstream
    Msg* Pull() override;
protected: // from IMsgProcessor
    // Only method that it makes sense to allow deriving classes to override.
    // Msgs such as MsgEncodedStream will be received before the desired Container
    // is Recognise()d, so are not guaranteed to be received by any specific
    // Container.
    Msg* ProcessMsg(MsgAudioEncoded* aMsg) override;
private: // from IMsgProcessor
    Msg* ProcessMsg(MsgMode* aMsg) override;
    Msg* ProcessMsg(MsgTrack* aMsg) override;
    Msg* ProcessMsg(MsgDrain* aMsg) override;
    Msg* ProcessMsg(MsgDelay* aMsg) override;
    Msg* ProcessMsg(MsgEncodedStream* aMsg) override;
    Msg* ProcessMsg(MsgMetaText* aMsg) override;
    Msg* ProcessMsg(MsgStreamInterrupted* aMsg) override;
    Msg* ProcessMsg(MsgHalt* aMsg) override;
    Msg* ProcessMsg(MsgFlush* aMsg) override;
    Msg* ProcessMsg(MsgWait* aMsg) override;
    Msg* ProcessMsg(MsgDecodedStream* aMsg) override;
    Msg* ProcessMsg(MsgAudioPcm* aMsg) override;
    Msg* ProcessMsg(MsgSilence* aMsg) override;
    Msg* ProcessMsg(MsgPlayable* aMsg) override;
    Msg* ProcessMsg(MsgQuit* aMsg) override;
private: // from IStreamHandler
    EStreamPlay OkToPlay(TUint aStreamId) override;
    TUint TrySeek(TUint aStreamId, TUint64 aOffset) override;
    TUint TryStop(TUint aStreamId) override;
    void NotifyStarving(const Brx& aMode, TUint aStreamId, TBool aStarving) override;
protected:
    MsgFactory* iMsgFactory;
    MsgAudioEncoded* iAudioEncoded;
    IStreamHandler* iStreamHandler;
    TUint iExpectedFlushId;
    TBool iPulling;
    IContainerUrlBlockWriter* iUrlBlockWriter;
private:
    IPipelineElementUpstream* iUpstreamElement;
    Msg* iPendingMsg;
};

class ContainerNull : public ContainerBase
{
public:
    ContainerNull();
public: // from IRecogniser
    TBool Recognise(Brx& aBuf);
};

class Container;

class ContainerFront : public IPipelineElementUpstream, private IMsgProcessor, public IStreamHandler, public IContainerUrlBlockWriter, private INonCopyable
{
    friend class Container;
public:
    ContainerFront(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstreamElement, IUrlBlockWriter& aUrlBlockWriter);
    ~ContainerFront();
    void AddContainer(ContainerBase* aContainer);
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
    Msg* ProcessMsg(MsgAudioPcm* aMsg) override;
    Msg* ProcessMsg(MsgSilence* aMsg) override;
    Msg* ProcessMsg(MsgPlayable* aMsg) override;
    Msg* ProcessMsg(MsgQuit* aMsg) override;
private: // from IStreamHandler
    EStreamPlay OkToPlay(TUint aStreamId) override;
    TUint TrySeek(TUint aStreamId, TUint64 aOffset) override;
    TUint TryStop(TUint aStreamId) override;
    void NotifyStarving(const Brx& aMode, TUint aStreamId, TBool aStarving) override;
private: // from IContainerUrlBlockWriter
    TBool TryGetUrl(IWriter& aWriter, TUint64 aOffset, TUint aBytes) override;
private:
    static const TUint kMaxRecogniseBytes = 6 * 1024;
    MsgFactory& iMsgFactory;
    IPipelineElementUpstream& iUpstreamElement;
    IUrlBlockWriter& iUrlBlockWriter;
    std::vector<IContainerBase*> iContainers;
    IContainerBase* iActiveContainer;
    ContainerNull* iContainerNull;
    IStreamHandler* iStreamHandler;
    Bws<Uri::kMaxUriBytes> iUrl;
    MsgAudioEncoded* iAudioEncoded;
    TByte iReadBuf[EncodedAudio::kMaxBytes];
    TBool iRecognising;
    TUint iExpectedFlushId;
    TBool iQuit;
};

class Container : public IPipelineElementUpstream, private IMsgProcessor, public IStreamHandler, private INonCopyable
{
public:
    Container(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstreamElement, IUrlBlockWriter& aUrlBlockWriter);
    Container(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstreamElement); // FIXME - remove
    virtual ~Container();
    void AddContainer(ContainerBase* aContainer);
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
    Msg* ProcessMsg(MsgAudioPcm* aMsg) override;
    Msg* ProcessMsg(MsgSilence* aMsg) override;
    Msg* ProcessMsg(MsgPlayable* aMsg) override;
    Msg* ProcessMsg(MsgQuit* aMsg) override;
public: // from IStreamHandler
    EStreamPlay OkToPlay(TUint aStreamId) override;
    TUint TrySeek(TUint aStreamId, TUint64 aOffset) override;
    TUint TryStop(TUint aStreamId) override;
    void NotifyStarving(const Brx& aMode, TUint aStreamId, TBool aStarving) override;
private:
    MsgFactory& iMsgFactory;
    ContainerFront* iContainerFront;
    TBool iNewStream;
};

} // namespace Codec
} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_CONTAINER
