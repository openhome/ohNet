#include <OpenHome/Av/ProviderTransportControlEriskay.h>
#include <Generated/DvOpenhomeOrgEriskayTransportControl1.h>
#include <OpenHome/Av/TransportControl.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Media/PipelineObserver.h>
#include <OpenHome/Media/Pipeline/Msg.h>

using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Net;

static const TUint kCodeBadAction = 801;
static const Brn kMsgBadAction("Action not supported by current stream");
static const TUint kCodeBadStreamId = 802;
static const Brn kMsgBadStreamId("Stream id incorrect");

ProviderTransportControlEriskay::ProviderTransportControlEriskay(Net::DvDevice& aDevice, ITransportControl& aTransportControl)
    : DvProviderOpenhomeOrgEriskayTransportControl1(aDevice)
    , iLock("PTCE")
    , iTransportControl(aTransportControl)
{
    EnablePropertyPlaySupported();
    EnablePropertyPauseSupported();
    EnablePropertyStopSupported();
    EnablePropertyNextSupported();
    EnablePropertyPrevSupported();
    EnablePropertySeekSupported();
    EnablePropertyStreamId();
    EnablePropertyTransportState();

    EnableActionCharacteristics();
    EnableActionPlay();
    EnableActionPause();
    EnableActionStop();
    EnableActionNext();
    EnableActionPrev();
    EnableActionSeekSecondsAbsolute();
    EnableActionSeekSecondsRelative();
    EnableActionStreamId();
    EnableActionTransportState();

    SetPropertyPlaySupported(false);
    SetPropertyPauseSupported(false);
    SetPropertyStopSupported(false);
    SetPropertyNextSupported(false);
    SetPropertyPrevSupported(false);
    SetPropertySeekSupported(false);
    SetPropertyStreamId(Media::IPipelineIdProvider::kStreamIdInvalid);
    NotifyState(Media::EPipelineStopped);
}

void ProviderTransportControlEriskay::NotifyMode()
{
    PropertiesLock();
    // update play, stop, next, prev
    PropertiesUnlock();
}

void ProviderTransportControlEriskay::NotifyStream(TUint aStreamId, TBool aPauseSupported, TBool aSeekSupported)
{
    PropertiesLock();
    SetPropertyStreamId(aStreamId);
    SetPropertyPauseSupported(aPauseSupported);
    SetPropertySeekSupported(aSeekSupported);
    PropertiesUnlock();
}

void ProviderTransportControlEriskay::NotifyState(Media::EPipelineState aState)
{
    iLock.Wait();
    iState = aState;
    Brn state(Media::TransportState::FromPipelineState(iState));
    iLock.Signal();
    SetPropertyTransportState(state);
}

void ProviderTransportControlEriskay::Characteristics(IDvInvocation& aInvocation,
                                                      IDvInvocationResponseBool& aPlaySupported,
                                                      IDvInvocationResponseBool& aPauseSupported,
                                                      IDvInvocationResponseBool& aStopSupported,
                                                      IDvInvocationResponseBool& aNextSupported,
                                                      IDvInvocationResponseBool& aPrevSupported,
                                                      IDvInvocationResponseBool& aSeekSupported)
{
    aInvocation.StartResponse();
    PropertiesLock();
    TBool val;
    GetPropertyPlaySupported(val);
    aPlaySupported.Write(val);
    GetPropertyPauseSupported(val);
    aPauseSupported.Write(val);
    GetPropertyStopSupported(val);
    aStopSupported.Write(val);
    GetPropertyNextSupported(val);
    aNextSupported.Write(val);
    GetPropertyPrevSupported(val);
    aPrevSupported.Write(val);
    GetPropertySeekSupported(val);
    aSeekSupported.Write(val);
    PropertiesUnlock();
    aInvocation.EndResponse();
}

void ProviderTransportControlEriskay::Play(IDvInvocation& aInvocation)
{
    try {
        iTransportControl.Play();
    }
    catch (TransportControlActionNotAllowed&) {
        aInvocation.Error(kCodeBadAction, kMsgBadAction);
    }
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderTransportControlEriskay::Pause(IDvInvocation& aInvocation, TUint aStreamId)
{
    try {
        iTransportControl.Pause(aStreamId);
    }
    catch (TransportControlIncorrectStreamId&) {
        aInvocation.Error(kCodeBadStreamId, kMsgBadStreamId);
    }
    catch (TransportControlActionNotAllowed&) {
        aInvocation.Error(kCodeBadAction, kMsgBadAction);
    }
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderTransportControlEriskay::Stop(IDvInvocation& aInvocation, TUint aStreamId)
{
    try {
        iTransportControl.Stop(aStreamId);
    }
    catch (TransportControlIncorrectStreamId&) {
        aInvocation.Error(kCodeBadStreamId, kMsgBadStreamId);
    }
    catch (TransportControlActionNotAllowed&) {
        aInvocation.Error(kCodeBadAction, kMsgBadAction);
    }
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderTransportControlEriskay::Next(IDvInvocation& aInvocation, TUint aStreamId)
{
    try {
        iTransportControl.Next(aStreamId);
    }
    catch (TransportControlIncorrectStreamId&) {
        aInvocation.Error(kCodeBadStreamId, kMsgBadStreamId);
    }
    catch (TransportControlActionNotAllowed&) {
        aInvocation.Error(kCodeBadAction, kMsgBadAction);
    }
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderTransportControlEriskay::Prev(IDvInvocation& aInvocation, TUint aStreamId)
{
    try {
        iTransportControl.Prev(aStreamId);
    }
    catch (TransportControlIncorrectStreamId&) {
        aInvocation.Error(kCodeBadStreamId, kMsgBadStreamId);
    }
    catch (TransportControlActionNotAllowed&) {
        aInvocation.Error(kCodeBadAction, kMsgBadAction);
    }
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderTransportControlEriskay::SeekSecondsAbsolute(IDvInvocation& aInvocation, TUint aStreamId, TUint aSecondsAbsolute)
{
    try {
        iTransportControl.SeekSecondsAbsolute(aStreamId, aSecondsAbsolute);
    }
    catch (TransportControlIncorrectStreamId&) {
        aInvocation.Error(kCodeBadStreamId, kMsgBadStreamId);
    }
    catch (TransportControlActionNotAllowed&) {
        aInvocation.Error(kCodeBadAction, kMsgBadAction);
    }
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderTransportControlEriskay::SeekSecondsRelative(IDvInvocation& aInvocation, TUint aStreamId, TInt aSecondsRelative)
{
    try {
        iTransportControl.SeekSecondsRelative(aStreamId, aSecondsRelative);
    }
    catch (TransportControlIncorrectStreamId&) {
        aInvocation.Error(kCodeBadStreamId, kMsgBadStreamId);
    }
    catch (TransportControlActionNotAllowed&) {
        aInvocation.Error(kCodeBadAction, kMsgBadAction);
    }
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderTransportControlEriskay::StreamId(IDvInvocation& aInvocation, IDvInvocationResponseUint& aValue)
{
    TUint id;
    GetPropertyStreamId(id);
    aInvocation.StartResponse();
    aValue.Write(id);
    aInvocation.EndResponse();
}

void ProviderTransportControlEriskay::TransportState(IDvInvocation& aInvocation, IDvInvocationResponseString& aValue)
{
    iLock.Wait();
    Brn state(Media::TransportState::FromPipelineState(iState));
    iLock.Signal();
    aInvocation.StartResponse();
    aValue.Write(state);
    aValue.WriteFlush();
    aInvocation.EndResponse();
}
