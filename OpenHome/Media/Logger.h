#ifndef HEADER_PIPELINE_LOGGER
#define HEADER_PIPELINE_LOGGER

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Media/Msg.h>

namespace OpenHome {
namespace Media {

/*
Element which logs msgs as they pass through.
Can be inserted [0..n] times through the pipeline, depending on your debugging needs.
*/

class Logger : public IPipelineElementUpstream, private IMsgProcessor, private INonCopyable
{
public:
    enum EMsgType
    {
        EMsgAudioEncoded  = 1<<0
       ,EMsgAudioDecoded  = 1<<1
       ,EMsgAudioPcm      = 1<<2
       ,EMsgSilence       = 1<<3
       ,EMsgPlayable      = 1<<4
       ,EMsgAudioFormat   = 1<<5
       ,EMsgTrack         = 1<<6
       ,EMsgEncodedStream = 1<<7
       ,EMsgMetaText      = 1<<8
       ,EMsgHalt          = 1<<9
       ,EMsgFlush         = 1<<10
       ,EMsgQuit          = 1<<11
       ,EMsgAll           = 0x7fffffff
    };
public:
    Logger(IPipelineElementUpstream& aUpstreamElement, const TChar* aId);
    ~Logger();
    void SetEnabled(TBool aEnabled);
    void SetFilter(TUint aMsgTypes);
public: // from IPipelineElementUpstream
    Msg* Pull();
private: // IMsgProcessor
    Msg* ProcessMsg(MsgAudioEncoded* aMsg);
    Msg* ProcessMsg(MsgAudioPcm* aMsg);
    Msg* ProcessMsg(MsgSilence* aMsg);
    Msg* ProcessMsg(MsgPlayable* aMsg);
    Msg* ProcessMsg(MsgAudioFormat* aMsg);
    Msg* ProcessMsg(MsgTrack* aMsg);
    Msg* ProcessMsg(MsgEncodedStream* aMsg);
    Msg* ProcessMsg(MsgMetaText* aMsg);
    Msg* ProcessMsg(MsgHalt* aMsg);
    Msg* ProcessMsg(MsgFlush* aMsg);
    Msg* ProcessMsg(MsgQuit* aMsg);
private:
    void LogRamp(const Media::Ramp& aRamp);
    TBool IsEnabled(EMsgType aType) const;
private:
    IPipelineElementUpstream& iUpstreamElement;
    const TChar* iId;
    TBool iEnabled;
    TInt iFilter;
    Semaphore iShutdownSem;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_LOGGER
