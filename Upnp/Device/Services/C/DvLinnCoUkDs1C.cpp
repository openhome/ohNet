#include <C/DvLinnCoUkDs1.h>
#include <Core/DvLinnCoUkDs1.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvServiceLinnCoUkDs1C : public DvServiceLinnCoUkDs1
{
public:
    DvServiceLinnCoUkDs1C(DvDevice& aDevice);
    void EnableActionPlay(CallbackDs1Play aCallback, void* aPtr);
    void EnableActionPause(CallbackDs1Pause aCallback, void* aPtr);
    void EnableActionStop(CallbackDs1Stop aCallback, void* aPtr);
    void EnableActionSeekSecondAbsolute(CallbackDs1SeekSecondAbsolute aCallback, void* aPtr);
    void EnableActionSeekSecondRelative(CallbackDs1SeekSecondRelative aCallback, void* aPtr);
    void EnableActionSeekTrackId(CallbackDs1SeekTrackId aCallback, void* aPtr);
    void EnableActionSeekTrackAbsolute(CallbackDs1SeekTrackAbsolute aCallback, void* aPtr);
    void EnableActionSeekTrackRelative(CallbackDs1SeekTrackRelative aCallback, void* aPtr);
    void EnableActionState(CallbackDs1State aCallback, void* aPtr);
    void EnableActionProtocolInfo(CallbackDs1ProtocolInfo aCallback, void* aPtr);
private:
    void Play(IInvocationResponse& aResponse, TUint aVersion);
    void Pause(IInvocationResponse& aResponse, TUint aVersion);
    void Stop(IInvocationResponse& aResponse, TUint aVersion);
    void SeekSecondAbsolute(IInvocationResponse& aResponse, TUint aVersion, TUint aaSecond);
    void SeekSecondRelative(IInvocationResponse& aResponse, TUint aVersion, TInt aaSecond);
    void SeekTrackId(IInvocationResponse& aResponse, TUint aVersion, TUint aaTrackId);
    void SeekTrackAbsolute(IInvocationResponse& aResponse, TUint aVersion, TUint aaTrack);
    void SeekTrackRelative(IInvocationResponse& aResponse, TUint aVersion, TInt aaTrack);
    void State(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaTransportState, IInvocationResponseUint& aaTrackDuration, IInvocationResponseUint& aaTrackBitRate, IInvocationResponseBool& aaTrackLossless, IInvocationResponseUint& aaTrackBitDepth, IInvocationResponseUint& aaTrackSampleRate, IInvocationResponseString& aaTrackCodecName, IInvocationResponseUint& aaTrackId);
    void ProtocolInfo(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaSupportedProtocols);
private:
    CallbackDs1Play iCallbackPlay;
    void* iPtrPlay;
    CallbackDs1Pause iCallbackPause;
    void* iPtrPause;
    CallbackDs1Stop iCallbackStop;
    void* iPtrStop;
    CallbackDs1SeekSecondAbsolute iCallbackSeekSecondAbsolute;
    void* iPtrSeekSecondAbsolute;
    CallbackDs1SeekSecondRelative iCallbackSeekSecondRelative;
    void* iPtrSeekSecondRelative;
    CallbackDs1SeekTrackId iCallbackSeekTrackId;
    void* iPtrSeekTrackId;
    CallbackDs1SeekTrackAbsolute iCallbackSeekTrackAbsolute;
    void* iPtrSeekTrackAbsolute;
    CallbackDs1SeekTrackRelative iCallbackSeekTrackRelative;
    void* iPtrSeekTrackRelative;
    CallbackDs1State iCallbackState;
    void* iPtrState;
    CallbackDs1ProtocolInfo iCallbackProtocolInfo;
    void* iPtrProtocolInfo;
};

DvServiceLinnCoUkDs1C::DvServiceLinnCoUkDs1C(DvDevice& aDevice)
    : DvServiceLinnCoUkDs1(aDevice)
{
}

void DvServiceLinnCoUkDs1C::EnableActionPlay(CallbackDs1Play aCallback, void* aPtr)
{
    iCallbackPlay = aCallback;
    iPtrPlay = aPtr;
    DvServiceLinnCoUkDs1::EnableActionPlay();
}

void DvServiceLinnCoUkDs1C::EnableActionPause(CallbackDs1Pause aCallback, void* aPtr)
{
    iCallbackPause = aCallback;
    iPtrPause = aPtr;
    DvServiceLinnCoUkDs1::EnableActionPause();
}

void DvServiceLinnCoUkDs1C::EnableActionStop(CallbackDs1Stop aCallback, void* aPtr)
{
    iCallbackStop = aCallback;
    iPtrStop = aPtr;
    DvServiceLinnCoUkDs1::EnableActionStop();
}

void DvServiceLinnCoUkDs1C::EnableActionSeekSecondAbsolute(CallbackDs1SeekSecondAbsolute aCallback, void* aPtr)
{
    iCallbackSeekSecondAbsolute = aCallback;
    iPtrSeekSecondAbsolute = aPtr;
    DvServiceLinnCoUkDs1::EnableActionSeekSecondAbsolute();
}

void DvServiceLinnCoUkDs1C::EnableActionSeekSecondRelative(CallbackDs1SeekSecondRelative aCallback, void* aPtr)
{
    iCallbackSeekSecondRelative = aCallback;
    iPtrSeekSecondRelative = aPtr;
    DvServiceLinnCoUkDs1::EnableActionSeekSecondRelative();
}

void DvServiceLinnCoUkDs1C::EnableActionSeekTrackId(CallbackDs1SeekTrackId aCallback, void* aPtr)
{
    iCallbackSeekTrackId = aCallback;
    iPtrSeekTrackId = aPtr;
    DvServiceLinnCoUkDs1::EnableActionSeekTrackId();
}

void DvServiceLinnCoUkDs1C::EnableActionSeekTrackAbsolute(CallbackDs1SeekTrackAbsolute aCallback, void* aPtr)
{
    iCallbackSeekTrackAbsolute = aCallback;
    iPtrSeekTrackAbsolute = aPtr;
    DvServiceLinnCoUkDs1::EnableActionSeekTrackAbsolute();
}

void DvServiceLinnCoUkDs1C::EnableActionSeekTrackRelative(CallbackDs1SeekTrackRelative aCallback, void* aPtr)
{
    iCallbackSeekTrackRelative = aCallback;
    iPtrSeekTrackRelative = aPtr;
    DvServiceLinnCoUkDs1::EnableActionSeekTrackRelative();
}

void DvServiceLinnCoUkDs1C::EnableActionState(CallbackDs1State aCallback, void* aPtr)
{
    iCallbackState = aCallback;
    iPtrState = aPtr;
    DvServiceLinnCoUkDs1::EnableActionState();
}

void DvServiceLinnCoUkDs1C::EnableActionProtocolInfo(CallbackDs1ProtocolInfo aCallback, void* aPtr)
{
    iCallbackProtocolInfo = aCallback;
    iPtrProtocolInfo = aPtr;
    DvServiceLinnCoUkDs1::EnableActionProtocolInfo();
}

void DvServiceLinnCoUkDs1C::Play(IInvocationResponse& aResponse, TUint aVersion)
{
    ASSERT(iCallbackPlay != NULL);
    if (0 != iCallbackPlay(iPtrPlay, aVersion)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkDs1C::Pause(IInvocationResponse& aResponse, TUint aVersion)
{
    ASSERT(iCallbackPause != NULL);
    if (0 != iCallbackPause(iPtrPause, aVersion)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkDs1C::Stop(IInvocationResponse& aResponse, TUint aVersion)
{
    ASSERT(iCallbackStop != NULL);
    if (0 != iCallbackStop(iPtrStop, aVersion)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkDs1C::SeekSecondAbsolute(IInvocationResponse& aResponse, TUint aVersion, TUint aaSecond)
{
    ASSERT(iCallbackSeekSecondAbsolute != NULL);
    if (0 != iCallbackSeekSecondAbsolute(iPtrSeekSecondAbsolute, aVersion, aaSecond)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkDs1C::SeekSecondRelative(IInvocationResponse& aResponse, TUint aVersion, TInt aaSecond)
{
    ASSERT(iCallbackSeekSecondRelative != NULL);
    if (0 != iCallbackSeekSecondRelative(iPtrSeekSecondRelative, aVersion, aaSecond)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkDs1C::SeekTrackId(IInvocationResponse& aResponse, TUint aVersion, TUint aaTrackId)
{
    ASSERT(iCallbackSeekTrackId != NULL);
    if (0 != iCallbackSeekTrackId(iPtrSeekTrackId, aVersion, aaTrackId)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkDs1C::SeekTrackAbsolute(IInvocationResponse& aResponse, TUint aVersion, TUint aaTrack)
{
    ASSERT(iCallbackSeekTrackAbsolute != NULL);
    if (0 != iCallbackSeekTrackAbsolute(iPtrSeekTrackAbsolute, aVersion, aaTrack)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkDs1C::SeekTrackRelative(IInvocationResponse& aResponse, TUint aVersion, TInt aaTrack)
{
    ASSERT(iCallbackSeekTrackRelative != NULL);
    if (0 != iCallbackSeekTrackRelative(iPtrSeekTrackRelative, aVersion, aaTrack)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkDs1C::State(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaTransportState, IInvocationResponseUint& aaTrackDuration, IInvocationResponseUint& aaTrackBitRate, IInvocationResponseBool& aaTrackLossless, IInvocationResponseUint& aaTrackBitDepth, IInvocationResponseUint& aaTrackSampleRate, IInvocationResponseString& aaTrackCodecName, IInvocationResponseUint& aaTrackId)
{
    char* aTransportState;
    uint32_t aTrackDuration;
    uint32_t aTrackBitRate;
    uint32_t aTrackLossless;
    uint32_t aTrackBitDepth;
    uint32_t aTrackSampleRate;
    char* aTrackCodecName;
    uint32_t aTrackId;
    ASSERT(iCallbackState != NULL);
    if (0 != iCallbackState(iPtrState, aVersion, &aTransportState, &aTrackDuration, &aTrackBitRate, &aTrackLossless, &aTrackBitDepth, &aTrackSampleRate, &aTrackCodecName, &aTrackId)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufaTransportState((const TChar*)aTransportState);
    ZappFreeExternal(aTransportState);
    aaTransportState.Write(bufaTransportState);
    aaTransportState.WriteFlush();
    aaTrackDuration.Write(aTrackDuration);
    aaTrackBitRate.Write(aTrackBitRate);
    aaTrackLossless.Write((aTrackLossless!=0));
    aaTrackBitDepth.Write(aTrackBitDepth);
    aaTrackSampleRate.Write(aTrackSampleRate);
    Brhz bufaTrackCodecName((const TChar*)aTrackCodecName);
    ZappFreeExternal(aTrackCodecName);
    aaTrackCodecName.Write(bufaTrackCodecName);
    aaTrackCodecName.WriteFlush();
    aaTrackId.Write(aTrackId);
    aResponse.End();
}

void DvServiceLinnCoUkDs1C::ProtocolInfo(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaSupportedProtocols)
{
    char* aSupportedProtocols;
    ASSERT(iCallbackProtocolInfo != NULL);
    if (0 != iCallbackProtocolInfo(iPtrProtocolInfo, aVersion, &aSupportedProtocols)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufaSupportedProtocols((const TChar*)aSupportedProtocols);
    ZappFreeExternal(aSupportedProtocols);
    aaSupportedProtocols.Write(bufaSupportedProtocols);
    aaSupportedProtocols.WriteFlush();
    aResponse.End();
}



THandle DvServiceLinnCoUkDs1Create(DvDeviceC aDevice)
{
    return (THandle)new DvServiceLinnCoUkDs1C(*(DviDeviceC::DeviceFromHandle(aDevice)));
}

void DvServiceLinnCoUkDs1Destroy(THandle aService)
{
    delete reinterpret_cast<DvServiceLinnCoUkDs1C*>(aService);
}

void DvServiceLinnCoUkDs1EnableActionPlay(THandle aService, CallbackDs1Play aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkDs1C*>(aService)->EnableActionPlay(aCallback, aPtr);
}

void DvServiceLinnCoUkDs1EnableActionPause(THandle aService, CallbackDs1Pause aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkDs1C*>(aService)->EnableActionPause(aCallback, aPtr);
}

void DvServiceLinnCoUkDs1EnableActionStop(THandle aService, CallbackDs1Stop aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkDs1C*>(aService)->EnableActionStop(aCallback, aPtr);
}

void DvServiceLinnCoUkDs1EnableActionSeekSecondAbsolute(THandle aService, CallbackDs1SeekSecondAbsolute aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkDs1C*>(aService)->EnableActionSeekSecondAbsolute(aCallback, aPtr);
}

void DvServiceLinnCoUkDs1EnableActionSeekSecondRelative(THandle aService, CallbackDs1SeekSecondRelative aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkDs1C*>(aService)->EnableActionSeekSecondRelative(aCallback, aPtr);
}

void DvServiceLinnCoUkDs1EnableActionSeekTrackId(THandle aService, CallbackDs1SeekTrackId aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkDs1C*>(aService)->EnableActionSeekTrackId(aCallback, aPtr);
}

void DvServiceLinnCoUkDs1EnableActionSeekTrackAbsolute(THandle aService, CallbackDs1SeekTrackAbsolute aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkDs1C*>(aService)->EnableActionSeekTrackAbsolute(aCallback, aPtr);
}

void DvServiceLinnCoUkDs1EnableActionSeekTrackRelative(THandle aService, CallbackDs1SeekTrackRelative aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkDs1C*>(aService)->EnableActionSeekTrackRelative(aCallback, aPtr);
}

void DvServiceLinnCoUkDs1EnableActionState(THandle aService, CallbackDs1State aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkDs1C*>(aService)->EnableActionState(aCallback, aPtr);
}

void DvServiceLinnCoUkDs1EnableActionProtocolInfo(THandle aService, CallbackDs1ProtocolInfo aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkDs1C*>(aService)->EnableActionProtocolInfo(aCallback, aPtr);
}

int32_t DvServiceLinnCoUkDs1SetPropertySupportedProtocols(THandle aService, const char* aValue)
{
    Brhz buf(aValue);
    reinterpret_cast<DvServiceLinnCoUkDs1C*>(aService)->SetPropertySupportedProtocols(buf);
    return 0;
}

void DvServiceLinnCoUkDs1GetPropertySupportedProtocols(THandle aService, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvServiceLinnCoUkDs1C*>(aService)->GetPropertySupportedProtocols(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvServiceLinnCoUkDs1SetPropertyTrackDuration(THandle aService, uint32_t aValue)
{
    reinterpret_cast<DvServiceLinnCoUkDs1C*>(aService)->SetPropertyTrackDuration(aValue);
    return 0;
}

void DvServiceLinnCoUkDs1GetPropertyTrackDuration(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvServiceLinnCoUkDs1C*>(aService)->GetPropertyTrackDuration(val);
    *aValue = val;
}

int32_t DvServiceLinnCoUkDs1SetPropertyTrackBitRate(THandle aService, uint32_t aValue)
{
    reinterpret_cast<DvServiceLinnCoUkDs1C*>(aService)->SetPropertyTrackBitRate(aValue);
    return 0;
}

void DvServiceLinnCoUkDs1GetPropertyTrackBitRate(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvServiceLinnCoUkDs1C*>(aService)->GetPropertyTrackBitRate(val);
    *aValue = val;
}

int32_t DvServiceLinnCoUkDs1SetPropertyTrackLossless(THandle aService, uint32_t aValue)
{
    reinterpret_cast<DvServiceLinnCoUkDs1C*>(aService)->SetPropertyTrackLossless((aValue!=0));
    return 0;
}

void DvServiceLinnCoUkDs1GetPropertyTrackLossless(THandle aService, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvServiceLinnCoUkDs1C*>(aService)->GetPropertyTrackLossless(val);
    *aValue = (val? 1 : 0);
}

int32_t DvServiceLinnCoUkDs1SetPropertyTrackBitDepth(THandle aService, uint32_t aValue)
{
    reinterpret_cast<DvServiceLinnCoUkDs1C*>(aService)->SetPropertyTrackBitDepth(aValue);
    return 0;
}

void DvServiceLinnCoUkDs1GetPropertyTrackBitDepth(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvServiceLinnCoUkDs1C*>(aService)->GetPropertyTrackBitDepth(val);
    *aValue = val;
}

int32_t DvServiceLinnCoUkDs1SetPropertyTrackSampleRate(THandle aService, uint32_t aValue)
{
    reinterpret_cast<DvServiceLinnCoUkDs1C*>(aService)->SetPropertyTrackSampleRate(aValue);
    return 0;
}

void DvServiceLinnCoUkDs1GetPropertyTrackSampleRate(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvServiceLinnCoUkDs1C*>(aService)->GetPropertyTrackSampleRate(val);
    *aValue = val;
}

int32_t DvServiceLinnCoUkDs1SetPropertyTrackCodecName(THandle aService, const char* aValue)
{
    Brhz buf(aValue);
    reinterpret_cast<DvServiceLinnCoUkDs1C*>(aService)->SetPropertyTrackCodecName(buf);
    return 0;
}

void DvServiceLinnCoUkDs1GetPropertyTrackCodecName(THandle aService, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvServiceLinnCoUkDs1C*>(aService)->GetPropertyTrackCodecName(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvServiceLinnCoUkDs1SetPropertyTrackId(THandle aService, uint32_t aValue)
{
    reinterpret_cast<DvServiceLinnCoUkDs1C*>(aService)->SetPropertyTrackId(aValue);
    return 0;
}

void DvServiceLinnCoUkDs1GetPropertyTrackId(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvServiceLinnCoUkDs1C*>(aService)->GetPropertyTrackId(val);
    *aValue = val;
}

int32_t DvServiceLinnCoUkDs1SetPropertyTransportState(THandle aService, const char* aValue)
{
    Brhz buf(aValue);
    reinterpret_cast<DvServiceLinnCoUkDs1C*>(aService)->SetPropertyTransportState(buf);
    return 0;
}

void DvServiceLinnCoUkDs1GetPropertyTransportState(THandle aService, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvServiceLinnCoUkDs1C*>(aService)->GetPropertyTransportState(buf);
    *aValue = (char*)buf.Transfer();
}

