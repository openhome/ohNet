#include "DvLinnCoUkRadio1C.h"
#include "DvLinnCoUkRadio1.h"
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvProviderLinnCoUkRadio1C : public DvProviderLinnCoUkRadio1
{
public:
    DvProviderLinnCoUkRadio1C(DvDevice& aDevice);
    void EnableActionPlay(CallbackRadio1Play aCallback, void* aPtr);
    void EnableActionPause(CallbackRadio1Pause aCallback, void* aPtr);
    void EnableActionStop(CallbackRadio1Stop aCallback, void* aPtr);
    void EnableActionSeekSecondAbsolute(CallbackRadio1SeekSecondAbsolute aCallback, void* aPtr);
    void EnableActionSeekSecondRelative(CallbackRadio1SeekSecondRelative aCallback, void* aPtr);
    void EnableActionChannel(CallbackRadio1Channel aCallback, void* aPtr);
    void EnableActionSetChannel(CallbackRadio1SetChannel aCallback, void* aPtr);
    void EnableActionProtocolInfo(CallbackRadio1ProtocolInfo aCallback, void* aPtr);
    void EnableActionTransportState(CallbackRadio1TransportState aCallback, void* aPtr);
    void EnableActionId(CallbackRadio1Id aCallback, void* aPtr);
    void EnableActionSetId(CallbackRadio1SetId aCallback, void* aPtr);
    void EnableActionRead(CallbackRadio1Read aCallback, void* aPtr);
    void EnableActionReadList(CallbackRadio1ReadList aCallback, void* aPtr);
    void EnableActionIdArray(CallbackRadio1IdArray aCallback, void* aPtr);
    void EnableActionIdArrayChanged(CallbackRadio1IdArrayChanged aCallback, void* aPtr);
    void EnableActionIdsMax(CallbackRadio1IdsMax aCallback, void* aPtr);
private:
    void Play(IInvocationResponse& aResponse, TUint aVersion);
    void Pause(IInvocationResponse& aResponse, TUint aVersion);
    void Stop(IInvocationResponse& aResponse, TUint aVersion);
    void SeekSecondAbsolute(IInvocationResponse& aResponse, TUint aVersion, TUint aaSecond);
    void SeekSecondRelative(IInvocationResponse& aResponse, TUint aVersion, TInt aaSecond);
    void Channel(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaUri, IInvocationResponseString& aaMetadata);
    void SetChannel(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaUri, const Brx& aaMetadata);
    void ProtocolInfo(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaInfo);
    void TransportState(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaState);
    void Id(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaId);
    void SetId(IInvocationResponse& aResponse, TUint aVersion, TUint aaId, const Brx& aaUri);
    void Read(IInvocationResponse& aResponse, TUint aVersion, TUint aaId, IInvocationResponseString& aaMetadata);
    void ReadList(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaIdList, IInvocationResponseString& aaMetadataList);
    void IdArray(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaIdArrayToken, IInvocationResponseBinary& aaIdArray);
    void IdArrayChanged(IInvocationResponse& aResponse, TUint aVersion, TUint aaIdArrayToken, IInvocationResponseBool& aaIdArrayChanged);
    void IdsMax(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaIdsMax);
private:
    CallbackRadio1Play iCallbackPlay;
    void* iPtrPlay;
    CallbackRadio1Pause iCallbackPause;
    void* iPtrPause;
    CallbackRadio1Stop iCallbackStop;
    void* iPtrStop;
    CallbackRadio1SeekSecondAbsolute iCallbackSeekSecondAbsolute;
    void* iPtrSeekSecondAbsolute;
    CallbackRadio1SeekSecondRelative iCallbackSeekSecondRelative;
    void* iPtrSeekSecondRelative;
    CallbackRadio1Channel iCallbackChannel;
    void* iPtrChannel;
    CallbackRadio1SetChannel iCallbackSetChannel;
    void* iPtrSetChannel;
    CallbackRadio1ProtocolInfo iCallbackProtocolInfo;
    void* iPtrProtocolInfo;
    CallbackRadio1TransportState iCallbackTransportState;
    void* iPtrTransportState;
    CallbackRadio1Id iCallbackId;
    void* iPtrId;
    CallbackRadio1SetId iCallbackSetId;
    void* iPtrSetId;
    CallbackRadio1Read iCallbackRead;
    void* iPtrRead;
    CallbackRadio1ReadList iCallbackReadList;
    void* iPtrReadList;
    CallbackRadio1IdArray iCallbackIdArray;
    void* iPtrIdArray;
    CallbackRadio1IdArrayChanged iCallbackIdArrayChanged;
    void* iPtrIdArrayChanged;
    CallbackRadio1IdsMax iCallbackIdsMax;
    void* iPtrIdsMax;
};

DvProviderLinnCoUkRadio1C::DvProviderLinnCoUkRadio1C(DvDevice& aDevice)
    : DvProviderLinnCoUkRadio1(aDevice)
{
}

void DvProviderLinnCoUkRadio1C::EnableActionPlay(CallbackRadio1Play aCallback, void* aPtr)
{
    iCallbackPlay = aCallback;
    iPtrPlay = aPtr;
    DvProviderLinnCoUkRadio1::EnableActionPlay();
}

void DvProviderLinnCoUkRadio1C::EnableActionPause(CallbackRadio1Pause aCallback, void* aPtr)
{
    iCallbackPause = aCallback;
    iPtrPause = aPtr;
    DvProviderLinnCoUkRadio1::EnableActionPause();
}

void DvProviderLinnCoUkRadio1C::EnableActionStop(CallbackRadio1Stop aCallback, void* aPtr)
{
    iCallbackStop = aCallback;
    iPtrStop = aPtr;
    DvProviderLinnCoUkRadio1::EnableActionStop();
}

void DvProviderLinnCoUkRadio1C::EnableActionSeekSecondAbsolute(CallbackRadio1SeekSecondAbsolute aCallback, void* aPtr)
{
    iCallbackSeekSecondAbsolute = aCallback;
    iPtrSeekSecondAbsolute = aPtr;
    DvProviderLinnCoUkRadio1::EnableActionSeekSecondAbsolute();
}

void DvProviderLinnCoUkRadio1C::EnableActionSeekSecondRelative(CallbackRadio1SeekSecondRelative aCallback, void* aPtr)
{
    iCallbackSeekSecondRelative = aCallback;
    iPtrSeekSecondRelative = aPtr;
    DvProviderLinnCoUkRadio1::EnableActionSeekSecondRelative();
}

void DvProviderLinnCoUkRadio1C::EnableActionChannel(CallbackRadio1Channel aCallback, void* aPtr)
{
    iCallbackChannel = aCallback;
    iPtrChannel = aPtr;
    DvProviderLinnCoUkRadio1::EnableActionChannel();
}

void DvProviderLinnCoUkRadio1C::EnableActionSetChannel(CallbackRadio1SetChannel aCallback, void* aPtr)
{
    iCallbackSetChannel = aCallback;
    iPtrSetChannel = aPtr;
    DvProviderLinnCoUkRadio1::EnableActionSetChannel();
}

void DvProviderLinnCoUkRadio1C::EnableActionProtocolInfo(CallbackRadio1ProtocolInfo aCallback, void* aPtr)
{
    iCallbackProtocolInfo = aCallback;
    iPtrProtocolInfo = aPtr;
    DvProviderLinnCoUkRadio1::EnableActionProtocolInfo();
}

void DvProviderLinnCoUkRadio1C::EnableActionTransportState(CallbackRadio1TransportState aCallback, void* aPtr)
{
    iCallbackTransportState = aCallback;
    iPtrTransportState = aPtr;
    DvProviderLinnCoUkRadio1::EnableActionTransportState();
}

void DvProviderLinnCoUkRadio1C::EnableActionId(CallbackRadio1Id aCallback, void* aPtr)
{
    iCallbackId = aCallback;
    iPtrId = aPtr;
    DvProviderLinnCoUkRadio1::EnableActionId();
}

void DvProviderLinnCoUkRadio1C::EnableActionSetId(CallbackRadio1SetId aCallback, void* aPtr)
{
    iCallbackSetId = aCallback;
    iPtrSetId = aPtr;
    DvProviderLinnCoUkRadio1::EnableActionSetId();
}

void DvProviderLinnCoUkRadio1C::EnableActionRead(CallbackRadio1Read aCallback, void* aPtr)
{
    iCallbackRead = aCallback;
    iPtrRead = aPtr;
    DvProviderLinnCoUkRadio1::EnableActionRead();
}

void DvProviderLinnCoUkRadio1C::EnableActionReadList(CallbackRadio1ReadList aCallback, void* aPtr)
{
    iCallbackReadList = aCallback;
    iPtrReadList = aPtr;
    DvProviderLinnCoUkRadio1::EnableActionReadList();
}

void DvProviderLinnCoUkRadio1C::EnableActionIdArray(CallbackRadio1IdArray aCallback, void* aPtr)
{
    iCallbackIdArray = aCallback;
    iPtrIdArray = aPtr;
    DvProviderLinnCoUkRadio1::EnableActionIdArray();
}

void DvProviderLinnCoUkRadio1C::EnableActionIdArrayChanged(CallbackRadio1IdArrayChanged aCallback, void* aPtr)
{
    iCallbackIdArrayChanged = aCallback;
    iPtrIdArrayChanged = aPtr;
    DvProviderLinnCoUkRadio1::EnableActionIdArrayChanged();
}

void DvProviderLinnCoUkRadio1C::EnableActionIdsMax(CallbackRadio1IdsMax aCallback, void* aPtr)
{
    iCallbackIdsMax = aCallback;
    iPtrIdsMax = aPtr;
    DvProviderLinnCoUkRadio1::EnableActionIdsMax();
}

void DvProviderLinnCoUkRadio1C::Play(IInvocationResponse& aResponse, TUint aVersion)
{
    ASSERT(iCallbackPlay != NULL);
    if (0 != iCallbackPlay(iPtrPlay, aVersion)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkRadio1C::Pause(IInvocationResponse& aResponse, TUint aVersion)
{
    ASSERT(iCallbackPause != NULL);
    if (0 != iCallbackPause(iPtrPause, aVersion)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkRadio1C::Stop(IInvocationResponse& aResponse, TUint aVersion)
{
    ASSERT(iCallbackStop != NULL);
    if (0 != iCallbackStop(iPtrStop, aVersion)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkRadio1C::SeekSecondAbsolute(IInvocationResponse& aResponse, TUint aVersion, TUint aaSecond)
{
    ASSERT(iCallbackSeekSecondAbsolute != NULL);
    if (0 != iCallbackSeekSecondAbsolute(iPtrSeekSecondAbsolute, aVersion, aaSecond)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkRadio1C::SeekSecondRelative(IInvocationResponse& aResponse, TUint aVersion, TInt aaSecond)
{
    ASSERT(iCallbackSeekSecondRelative != NULL);
    if (0 != iCallbackSeekSecondRelative(iPtrSeekSecondRelative, aVersion, aaSecond)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkRadio1C::Channel(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaUri, IInvocationResponseString& aaMetadata)
{
    char* aUri;
    char* aMetadata;
    ASSERT(iCallbackChannel != NULL);
    if (0 != iCallbackChannel(iPtrChannel, aVersion, &aUri, &aMetadata)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufaUri((const TChar*)aUri);
    ZappFreeExternal(aUri);
    aaUri.Write(bufaUri);
    aaUri.WriteFlush();
    Brhz bufaMetadata((const TChar*)aMetadata);
    ZappFreeExternal(aMetadata);
    aaMetadata.Write(bufaMetadata);
    aaMetadata.WriteFlush();
    aResponse.End();
}

void DvProviderLinnCoUkRadio1C::SetChannel(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaUri, const Brx& aaMetadata)
{
    ASSERT(iCallbackSetChannel != NULL);
    if (0 != iCallbackSetChannel(iPtrSetChannel, aVersion, (const char*)aaUri.Ptr(), (const char*)aaMetadata.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkRadio1C::ProtocolInfo(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaInfo)
{
    char* aInfo;
    ASSERT(iCallbackProtocolInfo != NULL);
    if (0 != iCallbackProtocolInfo(iPtrProtocolInfo, aVersion, &aInfo)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufaInfo((const TChar*)aInfo);
    ZappFreeExternal(aInfo);
    aaInfo.Write(bufaInfo);
    aaInfo.WriteFlush();
    aResponse.End();
}

void DvProviderLinnCoUkRadio1C::TransportState(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaState)
{
    char* aState;
    ASSERT(iCallbackTransportState != NULL);
    if (0 != iCallbackTransportState(iPtrTransportState, aVersion, &aState)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufaState((const TChar*)aState);
    ZappFreeExternal(aState);
    aaState.Write(bufaState);
    aaState.WriteFlush();
    aResponse.End();
}

void DvProviderLinnCoUkRadio1C::Id(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaId)
{
    uint32_t aId;
    ASSERT(iCallbackId != NULL);
    if (0 != iCallbackId(iPtrId, aVersion, &aId)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aaId.Write(aId);
    aResponse.End();
}

void DvProviderLinnCoUkRadio1C::SetId(IInvocationResponse& aResponse, TUint aVersion, TUint aaId, const Brx& aaUri)
{
    ASSERT(iCallbackSetId != NULL);
    if (0 != iCallbackSetId(iPtrSetId, aVersion, aaId, (const char*)aaUri.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkRadio1C::Read(IInvocationResponse& aResponse, TUint aVersion, TUint aaId, IInvocationResponseString& aaMetadata)
{
    char* aMetadata;
    ASSERT(iCallbackRead != NULL);
    if (0 != iCallbackRead(iPtrRead, aVersion, aaId, &aMetadata)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufaMetadata((const TChar*)aMetadata);
    ZappFreeExternal(aMetadata);
    aaMetadata.Write(bufaMetadata);
    aaMetadata.WriteFlush();
    aResponse.End();
}

void DvProviderLinnCoUkRadio1C::ReadList(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaIdList, IInvocationResponseString& aaMetadataList)
{
    char* aMetadataList;
    ASSERT(iCallbackReadList != NULL);
    if (0 != iCallbackReadList(iPtrReadList, aVersion, (const char*)aaIdList.Ptr(), &aMetadataList)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufaMetadataList((const TChar*)aMetadataList);
    ZappFreeExternal(aMetadataList);
    aaMetadataList.Write(bufaMetadataList);
    aaMetadataList.WriteFlush();
    aResponse.End();
}

void DvProviderLinnCoUkRadio1C::IdArray(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaIdArrayToken, IInvocationResponseBinary& aaIdArray)
{
    uint32_t aIdArrayToken;
    char* aIdArray;
    uint32_t aIdArrayLen;
    ASSERT(iCallbackIdArray != NULL);
    if (0 != iCallbackIdArray(iPtrIdArray, aVersion, &aIdArrayToken, &aIdArray, &aIdArrayLen)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aaIdArrayToken.Write(aIdArrayToken);
    Brh bufaIdArray;
    bufaIdArray.Set((const TByte*)aIdArray, aIdArrayLen);
    ZappFreeExternal(aIdArray);
    aaIdArray.Write(bufaIdArray);
    aaIdArray.WriteFlush();
    aResponse.End();
}

void DvProviderLinnCoUkRadio1C::IdArrayChanged(IInvocationResponse& aResponse, TUint aVersion, TUint aaIdArrayToken, IInvocationResponseBool& aaIdArrayChanged)
{
    uint32_t aIdArrayChanged;
    ASSERT(iCallbackIdArrayChanged != NULL);
    if (0 != iCallbackIdArrayChanged(iPtrIdArrayChanged, aVersion, aaIdArrayToken, &aIdArrayChanged)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aaIdArrayChanged.Write((aIdArrayChanged!=0));
    aResponse.End();
}

void DvProviderLinnCoUkRadio1C::IdsMax(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaIdsMax)
{
    uint32_t aIdsMax;
    ASSERT(iCallbackIdsMax != NULL);
    if (0 != iCallbackIdsMax(iPtrIdsMax, aVersion, &aIdsMax)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aaIdsMax.Write(aIdsMax);
    aResponse.End();
}



THandle DvProviderLinnCoUkRadio1Create(DvDeviceC aDevice)
{
	return new DvProviderLinnCoUkRadio1C(*(DviDeviceC::DeviceFromHandle(aDevice)));
}

void DvProviderLinnCoUkRadio1Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderLinnCoUkRadio1C*>(aProvider);
}

void DvProviderLinnCoUkRadio1EnableActionPlay(THandle aProvider, CallbackRadio1Play aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkRadio1C*>(aProvider)->EnableActionPlay(aCallback, aPtr);
}

void DvProviderLinnCoUkRadio1EnableActionPause(THandle aProvider, CallbackRadio1Pause aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkRadio1C*>(aProvider)->EnableActionPause(aCallback, aPtr);
}

void DvProviderLinnCoUkRadio1EnableActionStop(THandle aProvider, CallbackRadio1Stop aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkRadio1C*>(aProvider)->EnableActionStop(aCallback, aPtr);
}

void DvProviderLinnCoUkRadio1EnableActionSeekSecondAbsolute(THandle aProvider, CallbackRadio1SeekSecondAbsolute aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkRadio1C*>(aProvider)->EnableActionSeekSecondAbsolute(aCallback, aPtr);
}

void DvProviderLinnCoUkRadio1EnableActionSeekSecondRelative(THandle aProvider, CallbackRadio1SeekSecondRelative aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkRadio1C*>(aProvider)->EnableActionSeekSecondRelative(aCallback, aPtr);
}

void DvProviderLinnCoUkRadio1EnableActionChannel(THandle aProvider, CallbackRadio1Channel aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkRadio1C*>(aProvider)->EnableActionChannel(aCallback, aPtr);
}

void DvProviderLinnCoUkRadio1EnableActionSetChannel(THandle aProvider, CallbackRadio1SetChannel aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkRadio1C*>(aProvider)->EnableActionSetChannel(aCallback, aPtr);
}

void DvProviderLinnCoUkRadio1EnableActionProtocolInfo(THandle aProvider, CallbackRadio1ProtocolInfo aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkRadio1C*>(aProvider)->EnableActionProtocolInfo(aCallback, aPtr);
}

void DvProviderLinnCoUkRadio1EnableActionTransportState(THandle aProvider, CallbackRadio1TransportState aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkRadio1C*>(aProvider)->EnableActionTransportState(aCallback, aPtr);
}

void DvProviderLinnCoUkRadio1EnableActionId(THandle aProvider, CallbackRadio1Id aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkRadio1C*>(aProvider)->EnableActionId(aCallback, aPtr);
}

void DvProviderLinnCoUkRadio1EnableActionSetId(THandle aProvider, CallbackRadio1SetId aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkRadio1C*>(aProvider)->EnableActionSetId(aCallback, aPtr);
}

void DvProviderLinnCoUkRadio1EnableActionRead(THandle aProvider, CallbackRadio1Read aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkRadio1C*>(aProvider)->EnableActionRead(aCallback, aPtr);
}

void DvProviderLinnCoUkRadio1EnableActionReadList(THandle aProvider, CallbackRadio1ReadList aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkRadio1C*>(aProvider)->EnableActionReadList(aCallback, aPtr);
}

void DvProviderLinnCoUkRadio1EnableActionIdArray(THandle aProvider, CallbackRadio1IdArray aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkRadio1C*>(aProvider)->EnableActionIdArray(aCallback, aPtr);
}

void DvProviderLinnCoUkRadio1EnableActionIdArrayChanged(THandle aProvider, CallbackRadio1IdArrayChanged aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkRadio1C*>(aProvider)->EnableActionIdArrayChanged(aCallback, aPtr);
}

void DvProviderLinnCoUkRadio1EnableActionIdsMax(THandle aProvider, CallbackRadio1IdsMax aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkRadio1C*>(aProvider)->EnableActionIdsMax(aCallback, aPtr);
}

int32_t DvProviderLinnCoUkRadio1SetPropertyChannelUri(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkRadio1C*>(aProvider)->SetPropertyChannelUri(buf)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkRadio1GetPropertyChannelUri(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderLinnCoUkRadio1C*>(aProvider)->GetPropertyChannelUri(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvProviderLinnCoUkRadio1SetPropertyChannelMetadata(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkRadio1C*>(aProvider)->SetPropertyChannelMetadata(buf)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkRadio1GetPropertyChannelMetadata(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderLinnCoUkRadio1C*>(aProvider)->GetPropertyChannelMetadata(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvProviderLinnCoUkRadio1SetPropertyTransportState(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkRadio1C*>(aProvider)->SetPropertyTransportState(buf)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkRadio1GetPropertyTransportState(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderLinnCoUkRadio1C*>(aProvider)->GetPropertyTransportState(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvProviderLinnCoUkRadio1SetPropertyProtocolInfo(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkRadio1C*>(aProvider)->SetPropertyProtocolInfo(buf)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkRadio1GetPropertyProtocolInfo(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderLinnCoUkRadio1C*>(aProvider)->GetPropertyProtocolInfo(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvProviderLinnCoUkRadio1SetPropertyId(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkRadio1C*>(aProvider)->SetPropertyId(aValue)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkRadio1GetPropertyId(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderLinnCoUkRadio1C*>(aProvider)->GetPropertyId(val);
    *aValue = val;
}

int32_t DvProviderLinnCoUkRadio1SetPropertyIdArray(THandle aProvider, const char* aValue, uint32_t aValueLen, uint32_t* aChanged)
{
    Brh buf;
    buf.Set((const TByte*)aValue, aValueLen);
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkRadio1C*>(aProvider)->SetPropertyIdArray(buf)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkRadio1GetPropertyIdArray(THandle aProvider, char** aValue, uint32_t* aValueLen)
{
    Brh buf;
    reinterpret_cast<DvProviderLinnCoUkRadio1C*>(aProvider)->GetPropertyIdArray(buf);
    *aValueLen = buf.Bytes();
    *aValue = (char*)buf.Extract();
}

int32_t DvProviderLinnCoUkRadio1SetPropertyIdsMax(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkRadio1C*>(aProvider)->SetPropertyIdsMax(aValue)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkRadio1GetPropertyIdsMax(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderLinnCoUkRadio1C*>(aProvider)->GetPropertyIdsMax(val);
    *aValue = val;
}

