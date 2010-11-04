#include <C/DvLinnCoUkDs1.h>
#include <Core/DvLinnCoUkDs1.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvProviderLinnCoUkDs1C : public DvProviderLinnCoUkDs1
{
public:
    DvProviderLinnCoUkDs1C(DvDevice& aDevice);
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

DvProviderLinnCoUkDs1C::DvProviderLinnCoUkDs1C(DvDevice& aDevice)
    : DvProviderLinnCoUkDs1(aDevice)
{
}

void DvProviderLinnCoUkDs1C::EnableActionPlay(CallbackDs1Play aCallback, void* aPtr)
{
    iCallbackPlay = aCallback;
    iPtrPlay = aPtr;
    DvProviderLinnCoUkDs1::EnableActionPlay();
}

void DvProviderLinnCoUkDs1C::EnableActionPause(CallbackDs1Pause aCallback, void* aPtr)
{
    iCallbackPause = aCallback;
    iPtrPause = aPtr;
    DvProviderLinnCoUkDs1::EnableActionPause();
}

void DvProviderLinnCoUkDs1C::EnableActionStop(CallbackDs1Stop aCallback, void* aPtr)
{
    iCallbackStop = aCallback;
    iPtrStop = aPtr;
    DvProviderLinnCoUkDs1::EnableActionStop();
}

void DvProviderLinnCoUkDs1C::EnableActionSeekSecondAbsolute(CallbackDs1SeekSecondAbsolute aCallback, void* aPtr)
{
    iCallbackSeekSecondAbsolute = aCallback;
    iPtrSeekSecondAbsolute = aPtr;
    DvProviderLinnCoUkDs1::EnableActionSeekSecondAbsolute();
}

void DvProviderLinnCoUkDs1C::EnableActionSeekSecondRelative(CallbackDs1SeekSecondRelative aCallback, void* aPtr)
{
    iCallbackSeekSecondRelative = aCallback;
    iPtrSeekSecondRelative = aPtr;
    DvProviderLinnCoUkDs1::EnableActionSeekSecondRelative();
}

void DvProviderLinnCoUkDs1C::EnableActionSeekTrackId(CallbackDs1SeekTrackId aCallback, void* aPtr)
{
    iCallbackSeekTrackId = aCallback;
    iPtrSeekTrackId = aPtr;
    DvProviderLinnCoUkDs1::EnableActionSeekTrackId();
}

void DvProviderLinnCoUkDs1C::EnableActionSeekTrackAbsolute(CallbackDs1SeekTrackAbsolute aCallback, void* aPtr)
{
    iCallbackSeekTrackAbsolute = aCallback;
    iPtrSeekTrackAbsolute = aPtr;
    DvProviderLinnCoUkDs1::EnableActionSeekTrackAbsolute();
}

void DvProviderLinnCoUkDs1C::EnableActionSeekTrackRelative(CallbackDs1SeekTrackRelative aCallback, void* aPtr)
{
    iCallbackSeekTrackRelative = aCallback;
    iPtrSeekTrackRelative = aPtr;
    DvProviderLinnCoUkDs1::EnableActionSeekTrackRelative();
}

void DvProviderLinnCoUkDs1C::EnableActionState(CallbackDs1State aCallback, void* aPtr)
{
    iCallbackState = aCallback;
    iPtrState = aPtr;
    DvProviderLinnCoUkDs1::EnableActionState();
}

void DvProviderLinnCoUkDs1C::EnableActionProtocolInfo(CallbackDs1ProtocolInfo aCallback, void* aPtr)
{
    iCallbackProtocolInfo = aCallback;
    iPtrProtocolInfo = aPtr;
    DvProviderLinnCoUkDs1::EnableActionProtocolInfo();
}

void DvProviderLinnCoUkDs1C::Play(IInvocationResponse& aResponse, TUint aVersion)
{
    ASSERT(iCallbackPlay != NULL);
    if (0 != iCallbackPlay(iPtrPlay, aVersion)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkDs1C::Pause(IInvocationResponse& aResponse, TUint aVersion)
{
    ASSERT(iCallbackPause != NULL);
    if (0 != iCallbackPause(iPtrPause, aVersion)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkDs1C::Stop(IInvocationResponse& aResponse, TUint aVersion)
{
    ASSERT(iCallbackStop != NULL);
    if (0 != iCallbackStop(iPtrStop, aVersion)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkDs1C::SeekSecondAbsolute(IInvocationResponse& aResponse, TUint aVersion, TUint aaSecond)
{
    ASSERT(iCallbackSeekSecondAbsolute != NULL);
    if (0 != iCallbackSeekSecondAbsolute(iPtrSeekSecondAbsolute, aVersion, aaSecond)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkDs1C::SeekSecondRelative(IInvocationResponse& aResponse, TUint aVersion, TInt aaSecond)
{
    ASSERT(iCallbackSeekSecondRelative != NULL);
    if (0 != iCallbackSeekSecondRelative(iPtrSeekSecondRelative, aVersion, aaSecond)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkDs1C::SeekTrackId(IInvocationResponse& aResponse, TUint aVersion, TUint aaTrackId)
{
    ASSERT(iCallbackSeekTrackId != NULL);
    if (0 != iCallbackSeekTrackId(iPtrSeekTrackId, aVersion, aaTrackId)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkDs1C::SeekTrackAbsolute(IInvocationResponse& aResponse, TUint aVersion, TUint aaTrack)
{
    ASSERT(iCallbackSeekTrackAbsolute != NULL);
    if (0 != iCallbackSeekTrackAbsolute(iPtrSeekTrackAbsolute, aVersion, aaTrack)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkDs1C::SeekTrackRelative(IInvocationResponse& aResponse, TUint aVersion, TInt aaTrack)
{
    ASSERT(iCallbackSeekTrackRelative != NULL);
    if (0 != iCallbackSeekTrackRelative(iPtrSeekTrackRelative, aVersion, aaTrack)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkDs1C::State(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaTransportState, IInvocationResponseUint& aaTrackDuration, IInvocationResponseUint& aaTrackBitRate, IInvocationResponseBool& aaTrackLossless, IInvocationResponseUint& aaTrackBitDepth, IInvocationResponseUint& aaTrackSampleRate, IInvocationResponseString& aaTrackCodecName, IInvocationResponseUint& aaTrackId)
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

void DvProviderLinnCoUkDs1C::ProtocolInfo(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaSupportedProtocols)
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



THandle DvProviderLinnCoUkDs1Create(DvDeviceC aDevice)
{
	return new DvProviderLinnCoUkDs1C(*(DviDeviceC::DeviceFromHandle(aDevice)));
}

void DvProviderLinnCoUkDs1Destroy(THandle aService)
{
    delete reinterpret_cast<DvProviderLinnCoUkDs1C*>(aService);
}

void DvProviderLinnCoUkDs1EnableActionPlay(THandle aService, CallbackDs1Play aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkDs1C*>(aService)->EnableActionPlay(aCallback, aPtr);
}

void DvProviderLinnCoUkDs1EnableActionPause(THandle aService, CallbackDs1Pause aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkDs1C*>(aService)->EnableActionPause(aCallback, aPtr);
}

void DvProviderLinnCoUkDs1EnableActionStop(THandle aService, CallbackDs1Stop aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkDs1C*>(aService)->EnableActionStop(aCallback, aPtr);
}

void DvProviderLinnCoUkDs1EnableActionSeekSecondAbsolute(THandle aService, CallbackDs1SeekSecondAbsolute aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkDs1C*>(aService)->EnableActionSeekSecondAbsolute(aCallback, aPtr);
}

void DvProviderLinnCoUkDs1EnableActionSeekSecondRelative(THandle aService, CallbackDs1SeekSecondRelative aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkDs1C*>(aService)->EnableActionSeekSecondRelative(aCallback, aPtr);
}

void DvProviderLinnCoUkDs1EnableActionSeekTrackId(THandle aService, CallbackDs1SeekTrackId aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkDs1C*>(aService)->EnableActionSeekTrackId(aCallback, aPtr);
}

void DvProviderLinnCoUkDs1EnableActionSeekTrackAbsolute(THandle aService, CallbackDs1SeekTrackAbsolute aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkDs1C*>(aService)->EnableActionSeekTrackAbsolute(aCallback, aPtr);
}

void DvProviderLinnCoUkDs1EnableActionSeekTrackRelative(THandle aService, CallbackDs1SeekTrackRelative aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkDs1C*>(aService)->EnableActionSeekTrackRelative(aCallback, aPtr);
}

void DvProviderLinnCoUkDs1EnableActionState(THandle aService, CallbackDs1State aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkDs1C*>(aService)->EnableActionState(aCallback, aPtr);
}

void DvProviderLinnCoUkDs1EnableActionProtocolInfo(THandle aService, CallbackDs1ProtocolInfo aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkDs1C*>(aService)->EnableActionProtocolInfo(aCallback, aPtr);
}

int32_t DvProviderLinnCoUkDs1SetPropertySupportedProtocols(THandle aService, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkDs1C*>(aService)->SetPropertySupportedProtocols(buf)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkDs1GetPropertySupportedProtocols(THandle aService, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderLinnCoUkDs1C*>(aService)->GetPropertySupportedProtocols(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvProviderLinnCoUkDs1SetPropertyTrackDuration(THandle aService, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkDs1C*>(aService)->SetPropertyTrackDuration(aValue)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkDs1GetPropertyTrackDuration(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderLinnCoUkDs1C*>(aService)->GetPropertyTrackDuration(val);
    *aValue = val;
}

int32_t DvProviderLinnCoUkDs1SetPropertyTrackBitRate(THandle aService, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkDs1C*>(aService)->SetPropertyTrackBitRate(aValue)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkDs1GetPropertyTrackBitRate(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderLinnCoUkDs1C*>(aService)->GetPropertyTrackBitRate(val);
    *aValue = val;
}

int32_t DvProviderLinnCoUkDs1SetPropertyTrackLossless(THandle aService, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkDs1C*>(aService)->SetPropertyTrackLossless((aValue!=0))? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkDs1GetPropertyTrackLossless(THandle aService, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvProviderLinnCoUkDs1C*>(aService)->GetPropertyTrackLossless(val);
    *aValue = (val? 1 : 0);
}

int32_t DvProviderLinnCoUkDs1SetPropertyTrackBitDepth(THandle aService, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkDs1C*>(aService)->SetPropertyTrackBitDepth(aValue)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkDs1GetPropertyTrackBitDepth(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderLinnCoUkDs1C*>(aService)->GetPropertyTrackBitDepth(val);
    *aValue = val;
}

int32_t DvProviderLinnCoUkDs1SetPropertyTrackSampleRate(THandle aService, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkDs1C*>(aService)->SetPropertyTrackSampleRate(aValue)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkDs1GetPropertyTrackSampleRate(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderLinnCoUkDs1C*>(aService)->GetPropertyTrackSampleRate(val);
    *aValue = val;
}

int32_t DvProviderLinnCoUkDs1SetPropertyTrackCodecName(THandle aService, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkDs1C*>(aService)->SetPropertyTrackCodecName(buf)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkDs1GetPropertyTrackCodecName(THandle aService, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderLinnCoUkDs1C*>(aService)->GetPropertyTrackCodecName(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvProviderLinnCoUkDs1SetPropertyTrackId(THandle aService, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkDs1C*>(aService)->SetPropertyTrackId(aValue)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkDs1GetPropertyTrackId(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderLinnCoUkDs1C*>(aService)->GetPropertyTrackId(val);
    *aValue = val;
}

int32_t DvProviderLinnCoUkDs1SetPropertyTransportState(THandle aService, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkDs1C*>(aService)->SetPropertyTransportState(buf)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkDs1GetPropertyTransportState(THandle aService, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderLinnCoUkDs1C*>(aService)->GetPropertyTransportState(buf);
    *aValue = (char*)buf.Transfer();
}

