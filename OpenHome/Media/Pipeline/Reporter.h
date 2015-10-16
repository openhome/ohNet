#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Media/Pipeline/Msg.h>

namespace OpenHome {
namespace Media {

class IPipelinePropertyObserver
{
public:
    virtual void NotifyMode(const Brx& aMode, const ModeInfo& aInfo) = 0;
    virtual void NotifyTrack(Track& aTrack, const Brx& aMode, TBool aStartOfStream) = 0;
    virtual void NotifyMetaText(const Brx& aText) = 0;
    virtual void NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds) = 0;
    virtual void NotifyStreamInfo(const DecodedStreamInfo& aStreamInfo) = 0;
    virtual ~IPipelinePropertyObserver() {}
};

/*
Element which reports state changes in pipeline.
Is passive - it reports on Msgs but doesn't create/destroy/edit them.
*/

class IPipelineElementObserverThread;

class Reporter : public PipelineElement, public IPipelineElementUpstream, private INonCopyable
{
    static const TUint kSupportedMsgTypes;
    static const Brn kNullMetaText;
    static const TUint kTrackNotifyDelayMs = 10;
public:
    Reporter(IPipelineElementUpstream& aUpstreamElement, IPipelinePropertyObserver& aObserver, IPipelineElementObserverThread& aObserverThread);
    virtual ~Reporter();
public: // from IPipelineElementUpstream
    Msg* Pull() override;
private: // IMsgProcessor
    Msg* ProcessMsg(MsgMode* aMsg) override;
    Msg* ProcessMsg(MsgTrack* aMsg) override;
    Msg* ProcessMsg(MsgMetaText* aMsg) override;
    Msg* ProcessMsg(MsgDecodedStream* aMsg) override;
    Msg* ProcessMsg(MsgBitRate* aMsg) override;
    Msg* ProcessMsg(MsgAudioPcm* aMsg) override;
private:
    void EventCallback();
private:
    Mutex iLock;
    IPipelineElementUpstream& iUpstreamElement;
    IPipelinePropertyObserver& iObserver;
    IPipelineElementObserverThread& iObserverThread;
    TUint iEventId;
    MsgMode* iMsgMode;
    MsgTrack* iMsgTrack;
    MsgDecodedStream* iMsgDecodedStreamInfo;
    MsgMetaText* iMsgMetaText;
    TUint iSeconds;
    TUint iJiffies; // Fraction of a second
    TUint iTrackDurationSeconds;
    BwsMode iMode;
    BwsMode iModeTrack;
    TBool iNotifyTime;
};

} // namespace Media
} // namespace OpenHome

