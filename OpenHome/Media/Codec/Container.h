#ifndef HEADER_PIPELINE_CONTAINER
#define HEADER_PIPELINE_CONTAINER

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Media/Msg.h>

EXCEPTION(CodecStreamCorrupt);

namespace OpenHome {
namespace Media {
namespace Codec {

/*
Element which strips any container data from the start of a file.
Could (should) be extended later to handle more complex containers
...which read a stream, skip some data, read another stream repeatedly
...not just at the start of a file.
*/

class IContainer
{
public:
    virtual void Read(Bwx& aBuf, TUint aOffset, TUint aBytes) = 0;
};

class ContainerBase
{
    friend class Container;
public:
    virtual ~ContainerBase();
public:
    virtual void Initialise() = 0;          // reset container
    virtual TBool Recognise() = 0;          // recognise container
    virtual TUint Size() = 0;               // size of outer header portion
    virtual TBool AppendDuringSeek() = 0;   // include header bytes when seeking?
    virtual TUint Process() = 0;            // how many bytes to strip from next chunk of data
    virtual TUint Split() = 0;              // where should the next chunk be split before sending to codec?
protected:
    ContainerBase();
private:
    void Construct(IContainer& aContainer);
protected:
    IContainer* iContainer;
};

class Container : public IPipelineElementUpstream, private IContainer, private IMsgProcessor, private IStreamHandler, private INonCopyable
{
public:
    Container(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstreamElement);
    virtual ~Container();
    void AddContainer(ContainerBase* aContainer);
public: // from IPipelineElementUpstream
    Msg* Pull();
private: // IContainer
    void Read(Bwx& aBuf, TUint aOffset, TUint aBytes);
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
private: // from IStreamHandler
    EStreamPlay OkToPlay(TUint aTrackId, TUint aStreamId);
    TUint TrySeek(TUint aTrackId, TUint aStreamId, TUint64 aOffset);
    TUint TryStop(TUint aTrackId, TUint aStreamId);
private:
    MsgAudioEncoded* StripContainer(MsgAudioEncoded* aMsg);
    void FillBuffer();
    void ReleaseAudioEncoded();
private:
    MsgFactory& iMsgFactory;
    IPipelineElementUpstream& iUpstreamElement;
    std::vector<ContainerBase*> iContainers;
    ContainerBase* iActiveContainer;
    Msg* iPendingMsg;
    TBool iQuit;
    TBool iCheckForContainer;
    TUint iContainerSize;
    TUint iRemainingContainerSize; // number of bytes of container (that shouldn't be passed downstream)
    TUint iAppend;
    TUint iExpectedFlushId;
    IStreamHandler* iStreamHandler;
    MsgAudioEncoded* iAudioEncoded;
    TByte iReadBuf[EncodedAudio::kMaxBytes];
};

} // namespace Codec
} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_CONTAINER
