#ifndef HEADER_SONGCAST_SPLITTER
#define HEADER_SONGCAST_SPLITTER

#include <OpenHome/Types.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Media/Pipeline/Msg.h>

namespace OpenHome {
namespace Av {

class Splitter : public Media::IPipelineElementUpstream, private Media::IMsgProcessor, private INonCopyable
{
public:
    Splitter(Media::IPipelineElementDownstream& aBranch, const Brx& aSongcastMode);
    void SetUpstream(Media::IPipelineElementUpstream& aUpstream);
public: // from Media::IPipelineElementUpstream
    Media::Msg* Pull() override;
private: // Media::IMsgProcessor
    Media::Msg* ProcessMsg(Media::MsgMode* aMsg) override;
    Media::Msg* ProcessMsg(Media::MsgSession* aMsg) override;
    Media::Msg* ProcessMsg(Media::MsgTrack* aMsg) override;
    Media::Msg* ProcessMsg(Media::MsgDrain* aMsg) override;
    Media::Msg* ProcessMsg(Media::MsgDelay* aMsg) override;
    Media::Msg* ProcessMsg(Media::MsgEncodedStream* aMsg) override;
    Media::Msg* ProcessMsg(Media::MsgAudioEncoded* aMsg) override;
    Media::Msg* ProcessMsg(Media::MsgMetaText* aMsg) override;
    Media::Msg* ProcessMsg(Media::MsgStreamInterrupted* aMsg) override;
    Media::Msg* ProcessMsg(Media::MsgHalt* aMsg) override;
    Media::Msg* ProcessMsg(Media::MsgFlush* aMsg) override;
    Media::Msg* ProcessMsg(Media::MsgWait* aMsg) override;
    Media::Msg* ProcessMsg(Media::MsgDecodedStream* aMsg) override;
    Media::Msg* ProcessMsg(Media::MsgAudioPcm* aMsg) override;
    Media::Msg* ProcessMsg(Media::MsgSilence* aMsg) override;
    Media::Msg* ProcessMsg(Media::MsgPlayable* aMsg) override;
    Media::Msg* ProcessMsg(Media::MsgQuit* aMsg) override;
private:
    class MsgCloner : private Media::IMsgProcessor
    {
    public:
        static Media::Msg* NewRef(Media::Msg& aMsg);
    private:
        MsgCloner();
    private: // from IMsgProcessor
        Media::Msg* ProcessMsg(Media::MsgMode* aMsg) override;
        Media::Msg* ProcessMsg(Media::MsgSession* aMsg) override;
        Media::Msg* ProcessMsg(Media::MsgTrack* aMsg) override;
        Media::Msg* ProcessMsg(Media::MsgDrain* aMsg) override;
        Media::Msg* ProcessMsg(Media::MsgDelay* aMsg) override;
        Media::Msg* ProcessMsg(Media::MsgEncodedStream* aMsg) override;
        Media::Msg* ProcessMsg(Media::MsgAudioEncoded* aMsg) override;
        Media::Msg* ProcessMsg(Media::MsgMetaText* aMsg) override;
        Media::Msg* ProcessMsg(Media::MsgStreamInterrupted* aMsg) override;
        Media::Msg* ProcessMsg(Media::MsgHalt* aMsg) override;
        Media::Msg* ProcessMsg(Media::MsgFlush* aMsg) override;
        Media::Msg* ProcessMsg(Media::MsgWait* aMsg) override;
        Media::Msg* ProcessMsg(Media::MsgDecodedStream* aMsg) override;
        Media::Msg* ProcessMsg(Media::MsgAudioPcm* aMsg) override;
        Media::Msg* ProcessMsg(Media::MsgSilence* aMsg) override;
        Media::Msg* ProcessMsg(Media::MsgPlayable* aMsg) override;
        Media::Msg* ProcessMsg(Media::MsgQuit* aMsg) override;
    };
private:
    Media::IPipelineElementUpstream* iUpstream;
    Media::IPipelineElementDownstream& iBranch;
    Brn iSongcastMode;
    TBool iBranchEnabled;
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_SONGCAST_SPLITTER
