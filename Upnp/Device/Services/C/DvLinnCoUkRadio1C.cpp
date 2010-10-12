#include <C/DvLinnCoUkRadio1.h>
#include <Core/DvLinnCoUkRadio1.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvServiceLinnCoUkRadio1C : public DvServiceLinnCoUkRadio1
{
public:
    DvServiceLinnCoUkRadio1C(DvDevice& aDevice);
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

DvServiceLinnCoUkRadio1C::DvServiceLinnCoUkRadio1C(DvDevice& aDevice)
    : DvServiceLinnCoUkRadio1(aDevice)
{
}

void DvServiceLinnCoUkRadio1C::EnableActionPlay(CallbackRadio1Play aCallback, void* aPtr)
{
    iCallbackPlay = aCallback;
    iPtrPlay = aPtr;
    DvServiceLinnCoUkRadio1::EnableActionPlay();
}

void DvServiceLinnCoUkRadio1C::EnableActionPause(CallbackRadio1Pause aCallback, void* aPtr)
{
    iCallbackPause = aCallback;
    iPtrPause = aPtr;
    DvServiceLinnCoUkRadio1::EnableActionPause();
}

void DvServiceLinnCoUkRadio1C::EnableActionStop(CallbackRadio1Stop aCallback, void* aPtr)
{
    iCallbackStop = aCallback;
    iPtrStop = aPtr;
    DvServiceLinnCoUkRadio1::EnableActionStop();
}

void DvServiceLinnCoUkRadio1C::EnableActionSeekSecondAbsolute(CallbackRadio1SeekSecondAbsolute aCallback, void* aPtr)
{
    iCallbackSeekSecondAbsolute = aCallback;
    iPtrSeekSecondAbsolute = aPtr;
    DvServiceLinnCoUkRadio1::EnableActionSeekSecondAbsolute();
}

void DvServiceLinnCoUkRadio1C::EnableActionSeekSecondRelative(CallbackRadio1SeekSecondRelative aCallback, void* aPtr)
{
    iCallbackSeekSecondRelative = aCallback;
    iPtrSeekSecondRelative = aPtr;
    DvServiceLinnCoUkRadio1::EnableActionSeekSecondRelative();
}

void DvServiceLinnCoUkRadio1C::EnableActionChannel(CallbackRadio1Channel aCallback, void* aPtr)
{
    iCallbackChannel = aCallback;
    iPtrChannel = aPtr;
    DvServiceLinnCoUkRadio1::EnableActionChannel();
}

void DvServiceLinnCoUkRadio1C::EnableActionSetChannel(CallbackRadio1SetChannel aCallback, void* aPtr)
{
    iCallbackSetChannel = aCallback;
    iPtrSetChannel = aPtr;
    DvServiceLinnCoUkRadio1::EnableActionSetChannel();
}

void DvServiceLinnCoUkRadio1C::EnableActionProtocolInfo(CallbackRadio1ProtocolInfo aCallback, void* aPtr)
{
    iCallbackProtocolInfo = aCallback;
    iPtrProtocolInfo = aPtr;
    DvServiceLinnCoUkRadio1::EnableActionProtocolInfo();
}

void DvServiceLinnCoUkRadio1C::EnableActionTransportState(CallbackRadio1TransportState aCallback, void* aPtr)
{
    iCallbackTransportState = aCallback;
    iPtrTransportState = aPtr;
    DvServiceLinnCoUkRadio1::EnableActionTransportState();
}

void DvServiceLinnCoUkRadio1C::EnableActionId(CallbackRadio1Id aCallback, void* aPtr)
{
    iCallbackId = aCallback;
    iPtrId = aPtr;
    DvServiceLinnCoUkRadio1::EnableActionId();
}

void DvServiceLinnCoUkRadio1C::EnableActionSetId(CallbackRadio1SetId aCallback, void* aPtr)
{
    iCallbackSetId = aCallback;
    iPtrSetId = aPtr;
    DvServiceLinnCoUkRadio1::EnableActionSetId();
}

void DvServiceLinnCoUkRadio1C::EnableActionRead(CallbackRadio1Read aCallback, void* aPtr)
{
    iCallbackRead = aCallback;
    iPtrRead = aPtr;
    DvServiceLinnCoUkRadio1::EnableActionRead();
}

void DvServiceLinnCoUkRadio1C::EnableActionReadList(CallbackRadio1ReadList aCallback, void* aPtr)
{
    iCallbackReadList = aCallback;
    iPtrReadList = aPtr;
    DvServiceLinnCoUkRadio1::EnableActionReadList();
}

void DvServiceLinnCoUkRadio1C::EnableActionIdArray(CallbackRadio1IdArray aCallback, void* aPtr)
{
    iCallbackIdArray = aCallback;
    iPtrIdArray = aPtr;
    DvServiceLinnCoUkRadio1::EnableActionIdArray();
}

void DvServiceLinnCoUkRadio1C::EnableActionIdArrayChanged(CallbackRadio1IdArrayChanged aCallback, void* aPtr)
{
    iCallbackIdArrayChanged = aCallback;
    iPtrIdArrayChanged = aPtr;
    DvServiceLinnCoUkRadio1::EnableActionIdArrayChanged();
}

void DvServiceLinnCoUkRadio1C::EnableActionIdsMax(CallbackRadio1IdsMax aCallback, void* aPtr)
{
    iCallbackIdsMax = aCallback;
    iPtrIdsMax = aPtr;
    DvServiceLinnCoUkRadio1::EnableActionIdsMax();
}

void DvServiceLinnCoUkRadio1C::Play(IInvocationResponse& aResponse, TUint aVersion)
{
    ASSERT(iCallbackPlay != NULL);
    if (0 != iCallbackPlay(iPtrPlay, aVersion)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkRadio1C::Pause(IInvocationResponse& aResponse, TUint aVersion)
{
    ASSERT(iCallbackPause != NULL);
    if (0 != iCallbackPause(iPtrPause, aVersion)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkRadio1C::Stop(IInvocationResponse& aResponse, TUint aVersion)
{
    ASSERT(iCallbackStop != NULL);
    if (0 != iCallbackStop(iPtrStop, aVersion)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkRadio1C::SeekSecondAbsolute(IInvocationResponse& aResponse, TUint aVersion, TUint aaSecond)
{
    ASSERT(iCallbackSeekSecondAbsolute != NULL);
    if (0 != iCallbackSeekSecondAbsolute(iPtrSeekSecondAbsolute, aVersion, aaSecond)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkRadio1C::SeekSecondRelative(IInvocationResponse& aResponse, TUint aVersion, TInt aaSecond)
{
    ASSERT(iCallbackSeekSecondRelative != NULL);
    if (0 != iCallbackSeekSecondRelative(iPtrSeekSecondRelative, aVersion, aaSecond)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkRadio1C::Channel(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaUri, IInvocationResponseString& aaMetadata)
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

void DvServiceLinnCoUkRadio1C::SetChannel(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaUri, const Brx& aaMetadata)
{
    ASSERT(iCallbackSetChannel != NULL);
    if (0 != iCallbackSetChannel(iPtrSetChannel, aVersion, (const char*)aaUri.Ptr(), (const char*)aaMetadata.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkRadio1C::ProtocolInfo(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaInfo)
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

void DvServiceLinnCoUkRadio1C::TransportState(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaState)
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

void DvServiceLinnCoUkRadio1C::Id(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaId)
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

void DvServiceLinnCoUkRadio1C::SetId(IInvocationResponse& aResponse, TUint aVersion, TUint aaId, const Brx& aaUri)
{
    ASSERT(iCallbackSetId != NULL);
    if (0 != iCallbackSetId(iPtrSetId, aVersion, aaId, (const char*)aaUri.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkRadio1C::Read(IInvocationResponse& aResponse, TUint aVersion, TUint aaId, IInvocationResponseString& aaMetadata)
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

void DvServiceLinnCoUkRadio1C::ReadList(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaIdList, IInvocationResponseString& aaMetadataList)
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

void DvServiceLinnCoUkRadio1C::IdArray(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaIdArrayToken, IInvocationResponseBinary& aaIdArray)
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

void DvServiceLinnCoUkRadio1C::IdArrayChanged(IInvocationResponse& aResponse, TUint aVersion, TUint aaIdArrayToken, IInvocationResponseBool& aaIdArrayChanged)
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

void DvServiceLinnCoUkRadio1C::IdsMax(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaIdsMax)
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



THandle DvServiceLinnCoUkRadio1Create(DvDeviceC aDevice)
{
    return (THandle)new DvServiceLinnCoUkRadio1C(*(DviDeviceC::DeviceFromHandle(aDevice)));
}

void DvServiceLinnCoUkRadio1Destroy(THandle aService)
{
    delete reinterpret_cast<DvServiceLinnCoUkRadio1C*>(aService);
}

void DvServiceLinnCoUkRadio1EnableActionPlay(THandle aService, CallbackRadio1Play aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkRadio1C*>(aService)->EnableActionPlay(aCallback, aPtr);
}

void DvServiceLinnCoUkRadio1EnableActionPause(THandle aService, CallbackRadio1Pause aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkRadio1C*>(aService)->EnableActionPause(aCallback, aPtr);
}

void DvServiceLinnCoUkRadio1EnableActionStop(THandle aService, CallbackRadio1Stop aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkRadio1C*>(aService)->EnableActionStop(aCallback, aPtr);
}

void DvServiceLinnCoUkRadio1EnableActionSeekSecondAbsolute(THandle aService, CallbackRadio1SeekSecondAbsolute aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkRadio1C*>(aService)->EnableActionSeekSecondAbsolute(aCallback, aPtr);
}

void DvServiceLinnCoUkRadio1EnableActionSeekSecondRelative(THandle aService, CallbackRadio1SeekSecondRelative aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkRadio1C*>(aService)->EnableActionSeekSecondRelative(aCallback, aPtr);
}

void DvServiceLinnCoUkRadio1EnableActionChannel(THandle aService, CallbackRadio1Channel aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkRadio1C*>(aService)->EnableActionChannel(aCallback, aPtr);
}

void DvServiceLinnCoUkRadio1EnableActionSetChannel(THandle aService, CallbackRadio1SetChannel aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkRadio1C*>(aService)->EnableActionSetChannel(aCallback, aPtr);
}

void DvServiceLinnCoUkRadio1EnableActionProtocolInfo(THandle aService, CallbackRadio1ProtocolInfo aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkRadio1C*>(aService)->EnableActionProtocolInfo(aCallback, aPtr);
}

void DvServiceLinnCoUkRadio1EnableActionTransportState(THandle aService, CallbackRadio1TransportState aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkRadio1C*>(aService)->EnableActionTransportState(aCallback, aPtr);
}

void DvServiceLinnCoUkRadio1EnableActionId(THandle aService, CallbackRadio1Id aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkRadio1C*>(aService)->EnableActionId(aCallback, aPtr);
}

void DvServiceLinnCoUkRadio1EnableActionSetId(THandle aService, CallbackRadio1SetId aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkRadio1C*>(aService)->EnableActionSetId(aCallback, aPtr);
}

void DvServiceLinnCoUkRadio1EnableActionRead(THandle aService, CallbackRadio1Read aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkRadio1C*>(aService)->EnableActionRead(aCallback, aPtr);
}

void DvServiceLinnCoUkRadio1EnableActionReadList(THandle aService, CallbackRadio1ReadList aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkRadio1C*>(aService)->EnableActionReadList(aCallback, aPtr);
}

void DvServiceLinnCoUkRadio1EnableActionIdArray(THandle aService, CallbackRadio1IdArray aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkRadio1C*>(aService)->EnableActionIdArray(aCallback, aPtr);
}

void DvServiceLinnCoUkRadio1EnableActionIdArrayChanged(THandle aService, CallbackRadio1IdArrayChanged aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkRadio1C*>(aService)->EnableActionIdArrayChanged(aCallback, aPtr);
}

void DvServiceLinnCoUkRadio1EnableActionIdsMax(THandle aService, CallbackRadio1IdsMax aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkRadio1C*>(aService)->EnableActionIdsMax(aCallback, aPtr);
}

int32_t DvServiceLinnCoUkRadio1SetPropertyChannelUri(THandle aService, const char* aValue)
{
    Brhz buf(aValue);
    reinterpret_cast<DvServiceLinnCoUkRadio1C*>(aService)->SetPropertyChannelUri(buf);
    return 0;
}

void DvServiceLinnCoUkRadio1GetPropertyChannelUri(THandle aService, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvServiceLinnCoUkRadio1C*>(aService)->GetPropertyChannelUri(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvServiceLinnCoUkRadio1SetPropertyChannelMetadata(THandle aService, const char* aValue)
{
    Brhz buf(aValue);
    reinterpret_cast<DvServiceLinnCoUkRadio1C*>(aService)->SetPropertyChannelMetadata(buf);
    return 0;
}

void DvServiceLinnCoUkRadio1GetPropertyChannelMetadata(THandle aService, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvServiceLinnCoUkRadio1C*>(aService)->GetPropertyChannelMetadata(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvServiceLinnCoUkRadio1SetPropertyTransportState(THandle aService, const char* aValue)
{
    Brhz buf(aValue);
    reinterpret_cast<DvServiceLinnCoUkRadio1C*>(aService)->SetPropertyTransportState(buf);
    return 0;
}

void DvServiceLinnCoUkRadio1GetPropertyTransportState(THandle aService, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvServiceLinnCoUkRadio1C*>(aService)->GetPropertyTransportState(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvServiceLinnCoUkRadio1SetPropertyProtocolInfo(THandle aService, const char* aValue)
{
    Brhz buf(aValue);
    reinterpret_cast<DvServiceLinnCoUkRadio1C*>(aService)->SetPropertyProtocolInfo(buf);
    return 0;
}

void DvServiceLinnCoUkRadio1GetPropertyProtocolInfo(THandle aService, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvServiceLinnCoUkRadio1C*>(aService)->GetPropertyProtocolInfo(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvServiceLinnCoUkRadio1SetPropertyId(THandle aService, uint32_t aValue)
{
    reinterpret_cast<DvServiceLinnCoUkRadio1C*>(aService)->SetPropertyId(aValue);
    return 0;
}

void DvServiceLinnCoUkRadio1GetPropertyId(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvServiceLinnCoUkRadio1C*>(aService)->GetPropertyId(val);
    *aValue = val;
}

int32_t DvServiceLinnCoUkRadio1SetPropertyIdArray(THandle aService, const char* aValue, uint32_t aValueLen)
{
    Brh buf;
    buf.Set((const TByte*)aValue, aValueLen);
    reinterpret_cast<DvServiceLinnCoUkRadio1C*>(aService)->SetPropertyIdArray(buf);
    return 0;
}

void DvServiceLinnCoUkRadio1GetPropertyIdArray(THandle aService, char** aValue, uint32_t* aValueLen)
{
    Brh buf;
    reinterpret_cast<DvServiceLinnCoUkRadio1C*>(aService)->GetPropertyIdArray(buf);
    *aValueLen = buf.Bytes();
    *aValue = (char*)buf.Extract();
}

int32_t DvServiceLinnCoUkRadio1SetPropertyIdsMax(THandle aService, uint32_t aValue)
{
    reinterpret_cast<DvServiceLinnCoUkRadio1C*>(aService)->SetPropertyIdsMax(aValue);
    return 0;
}

void DvServiceLinnCoUkRadio1GetPropertyIdsMax(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvServiceLinnCoUkRadio1C*>(aService)->GetPropertyIdsMax(val);
    *aValue = val;
}

