#ifndef HEADER_PIPELINE_CONTAINER
#define HEADER_PIPELINE_CONTAINER

#include <OpenHome/Types.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Private/Standard.h>
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
};


class IRecogniser
{
public:
    virtual TBool Recognise(Brx& aBuf) = 0;
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
    virtual TBool TryGet(IWriter& aWriter, const Brx& aUrl, TUint64 aOffset, TUint aBytes) = 0;
    virtual void NotifyStarving(const Brx& aMode, TUint aStreamId) = 0;
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
    void Construct(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstreamElement, IStreamHandler& aStreamHandler); // FIXME - don't pass istreamhandler here
    TBool ReadFromCachedAudio(Bwx& aBuf, TUint aBytes);
public: // from IRecogniser
    TBool Recognise(Brx& aBuf) = 0;   // need to reset inner container in this method
    //TBool Recognise(Brx& aBuf);
public: // from IPipelineElementUpstream
    Msg* Pull() override;
protected: // from IMsgProcessor
    Msg* ProcessMsg(MsgEncodedStream* aMsg) override;
private: // from IMsgProcessor
    Msg* ProcessMsg(MsgMode* aMsg) override;
    Msg* ProcessMsg(MsgSession* aMsg) override;
    Msg* ProcessMsg(MsgTrack* aMsg) override;
    Msg* ProcessMsg(MsgDelay* aMsg) override;
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
private: // from IStreamHandler
    EStreamPlay OkToPlay(TUint aStreamId) override;
    TUint TrySeek(TUint aStreamId, TUint64 aOffset) override;
    TUint TryStop(TUint aStreamId) override;
    TBool TryGet(IWriter& aWriter, const Brx& aUrl, TUint64 aOffset, TUint aBytes) override;
    void NotifyStarving(const Brx& aMode, TUint aStreamId) override;
protected:
    MsgAudioEncoded* iAudioEncoded;
    IStreamHandler* iStreamHandler;
    TUint iExpectedFlushId;
    TBool iPulling;
private:
    MsgFactory* iMsgFactory;
    IPipelineElementUpstream* iUpstreamElement;
    Msg* iPendingMsg;

protected:
    IContainer* iContainer;
};

class ContainerNull : public ContainerBase
{
public:
    ContainerNull();
public: // from IRecogniser
    TBool Recognise(Brx& aBuf);
};

class Container;

class ContainerFront : public IPipelineElementUpstream, private IMsgProcessor, public IStreamHandler, private INonCopyable
{
    friend class Container;
public:
    ContainerFront(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstreamElement);
    ~ContainerFront();
    void AddContainer(ContainerBase* aContainer);
public: // from IPipelineElementUpstream
    Msg* Pull() override;
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
private: // from IStreamHandler
    EStreamPlay OkToPlay(TUint aStreamId) override;
    TUint TrySeek(TUint aStreamId, TUint64 aOffset) override;
    TUint TryStop(TUint aStreamId) override;
    TBool TryGet(IWriter& aWriter, const Brx& aUrl, TUint64 aOffset, TUint aBytes) override;
    void NotifyStarving(const Brx& aMode, TUint aStreamId) override;
private:
    static const TUint kMaxRecogniseBytes = 6 * 1024;
    MsgFactory& iMsgFactory;
    IPipelineElementUpstream& iUpstreamElement;
    std::vector<IContainerBase*> iContainers;
    IContainerBase* iActiveContainer;
    ContainerNull* iContainerNull;
    IStreamHandler* iStreamHandler;

    MsgAudioEncoded* iAudioEncoded;
    TByte iReadBuf[EncodedAudio::kMaxBytes];
    TBool iRecognising;
    TUint iExpectedFlushId;
    TBool iQuit;
};

class Container : public IPipelineElementUpstream, private IMsgProcessor, public IStreamHandler, private INonCopyable
{
public:
    Container(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstreamElement);
    virtual ~Container();
    void AddContainer(ContainerBase* aContainer);
public: // from IPipelineElementUpstream
    Msg* Pull() override;
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
public: // from IStreamHandler
    EStreamPlay OkToPlay(TUint aStreamId) override;
    TUint TrySeek(TUint aStreamId, TUint64 aOffset) override;
    TUint TryStop(TUint aStreamId) override;
    TBool TryGet(IWriter& aWriter, const Brx& aUrl, TUint64 aOffset, TUint aBytes) override;
    void NotifyStarving(const Brx& aMode, TUint aStreamId) override;
private:
    MsgFactory& iMsgFactory;
    ContainerFront* iContainerFront;
    TBool iNewStream;
};

} // namespace Codec
} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_CONTAINER
