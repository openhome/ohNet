#include <C/DvLinnCoUkProduct2.h>
#include <Core/DvLinnCoUkProduct2.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvProviderLinnCoUkProduct2C : public DvProviderLinnCoUkProduct2
{
public:
    DvProviderLinnCoUkProduct2C(DvDevice& aDevice);
    void EnableActionType(CallbackProduct2Type aCallback, void* aPtr);
    void EnableActionModel(CallbackProduct2Model aCallback, void* aPtr);
    void EnableActionName(CallbackProduct2Name aCallback, void* aPtr);
    void EnableActionSetName(CallbackProduct2SetName aCallback, void* aPtr);
    void EnableActionRoom(CallbackProduct2Room aCallback, void* aPtr);
    void EnableActionSetRoom(CallbackProduct2SetRoom aCallback, void* aPtr);
    void EnableActionStandby(CallbackProduct2Standby aCallback, void* aPtr);
    void EnableActionSetStandby(CallbackProduct2SetStandby aCallback, void* aPtr);
    void EnableActionSourceCount(CallbackProduct2SourceCount aCallback, void* aPtr);
    void EnableActionSourceIndex(CallbackProduct2SourceIndex aCallback, void* aPtr);
    void EnableActionSetSourceIndex(CallbackProduct2SetSourceIndex aCallback, void* aPtr);
    void EnableActionSourceType(CallbackProduct2SourceType aCallback, void* aPtr);
private:
    void Type(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaType);
    void Model(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaModel);
    void Name(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaName);
    void SetName(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaName);
    void Room(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaRoom);
    void SetRoom(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaRoom);
    void Standby(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaStandby);
    void SetStandby(IInvocationResponse& aResponse, TUint aVersion, TBool aaStandby);
    void SourceCount(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaSourceCount);
    void SourceIndex(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaSourceIndex);
    void SetSourceIndex(IInvocationResponse& aResponse, TUint aVersion, TUint aaSourceIndex);
    void SourceType(IInvocationResponse& aResponse, TUint aVersion, TUint aaSourceIndex, IInvocationResponseString& aaSourceType);
private:
    CallbackProduct2Type iCallbackType;
    void* iPtrType;
    CallbackProduct2Model iCallbackModel;
    void* iPtrModel;
    CallbackProduct2Name iCallbackName;
    void* iPtrName;
    CallbackProduct2SetName iCallbackSetName;
    void* iPtrSetName;
    CallbackProduct2Room iCallbackRoom;
    void* iPtrRoom;
    CallbackProduct2SetRoom iCallbackSetRoom;
    void* iPtrSetRoom;
    CallbackProduct2Standby iCallbackStandby;
    void* iPtrStandby;
    CallbackProduct2SetStandby iCallbackSetStandby;
    void* iPtrSetStandby;
    CallbackProduct2SourceCount iCallbackSourceCount;
    void* iPtrSourceCount;
    CallbackProduct2SourceIndex iCallbackSourceIndex;
    void* iPtrSourceIndex;
    CallbackProduct2SetSourceIndex iCallbackSetSourceIndex;
    void* iPtrSetSourceIndex;
    CallbackProduct2SourceType iCallbackSourceType;
    void* iPtrSourceType;
};

DvProviderLinnCoUkProduct2C::DvProviderLinnCoUkProduct2C(DvDevice& aDevice)
    : DvProviderLinnCoUkProduct2(aDevice)
{
}

void DvProviderLinnCoUkProduct2C::EnableActionType(CallbackProduct2Type aCallback, void* aPtr)
{
    iCallbackType = aCallback;
    iPtrType = aPtr;
    DvProviderLinnCoUkProduct2::EnableActionType();
}

void DvProviderLinnCoUkProduct2C::EnableActionModel(CallbackProduct2Model aCallback, void* aPtr)
{
    iCallbackModel = aCallback;
    iPtrModel = aPtr;
    DvProviderLinnCoUkProduct2::EnableActionModel();
}

void DvProviderLinnCoUkProduct2C::EnableActionName(CallbackProduct2Name aCallback, void* aPtr)
{
    iCallbackName = aCallback;
    iPtrName = aPtr;
    DvProviderLinnCoUkProduct2::EnableActionName();
}

void DvProviderLinnCoUkProduct2C::EnableActionSetName(CallbackProduct2SetName aCallback, void* aPtr)
{
    iCallbackSetName = aCallback;
    iPtrSetName = aPtr;
    DvProviderLinnCoUkProduct2::EnableActionSetName();
}

void DvProviderLinnCoUkProduct2C::EnableActionRoom(CallbackProduct2Room aCallback, void* aPtr)
{
    iCallbackRoom = aCallback;
    iPtrRoom = aPtr;
    DvProviderLinnCoUkProduct2::EnableActionRoom();
}

void DvProviderLinnCoUkProduct2C::EnableActionSetRoom(CallbackProduct2SetRoom aCallback, void* aPtr)
{
    iCallbackSetRoom = aCallback;
    iPtrSetRoom = aPtr;
    DvProviderLinnCoUkProduct2::EnableActionSetRoom();
}

void DvProviderLinnCoUkProduct2C::EnableActionStandby(CallbackProduct2Standby aCallback, void* aPtr)
{
    iCallbackStandby = aCallback;
    iPtrStandby = aPtr;
    DvProviderLinnCoUkProduct2::EnableActionStandby();
}

void DvProviderLinnCoUkProduct2C::EnableActionSetStandby(CallbackProduct2SetStandby aCallback, void* aPtr)
{
    iCallbackSetStandby = aCallback;
    iPtrSetStandby = aPtr;
    DvProviderLinnCoUkProduct2::EnableActionSetStandby();
}

void DvProviderLinnCoUkProduct2C::EnableActionSourceCount(CallbackProduct2SourceCount aCallback, void* aPtr)
{
    iCallbackSourceCount = aCallback;
    iPtrSourceCount = aPtr;
    DvProviderLinnCoUkProduct2::EnableActionSourceCount();
}

void DvProviderLinnCoUkProduct2C::EnableActionSourceIndex(CallbackProduct2SourceIndex aCallback, void* aPtr)
{
    iCallbackSourceIndex = aCallback;
    iPtrSourceIndex = aPtr;
    DvProviderLinnCoUkProduct2::EnableActionSourceIndex();
}

void DvProviderLinnCoUkProduct2C::EnableActionSetSourceIndex(CallbackProduct2SetSourceIndex aCallback, void* aPtr)
{
    iCallbackSetSourceIndex = aCallback;
    iPtrSetSourceIndex = aPtr;
    DvProviderLinnCoUkProduct2::EnableActionSetSourceIndex();
}

void DvProviderLinnCoUkProduct2C::EnableActionSourceType(CallbackProduct2SourceType aCallback, void* aPtr)
{
    iCallbackSourceType = aCallback;
    iPtrSourceType = aPtr;
    DvProviderLinnCoUkProduct2::EnableActionSourceType();
}

void DvProviderLinnCoUkProduct2C::Type(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaType)
{
    char* aType;
    ASSERT(iCallbackType != NULL);
    if (0 != iCallbackType(iPtrType, aVersion, &aType)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufaType((const TChar*)aType);
    ZappFreeExternal(aType);
    aaType.Write(bufaType);
    aaType.WriteFlush();
    aResponse.End();
}

void DvProviderLinnCoUkProduct2C::Model(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaModel)
{
    char* aModel;
    ASSERT(iCallbackModel != NULL);
    if (0 != iCallbackModel(iPtrModel, aVersion, &aModel)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufaModel((const TChar*)aModel);
    ZappFreeExternal(aModel);
    aaModel.Write(bufaModel);
    aaModel.WriteFlush();
    aResponse.End();
}

void DvProviderLinnCoUkProduct2C::Name(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaName)
{
    char* aName;
    ASSERT(iCallbackName != NULL);
    if (0 != iCallbackName(iPtrName, aVersion, &aName)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufaName((const TChar*)aName);
    ZappFreeExternal(aName);
    aaName.Write(bufaName);
    aaName.WriteFlush();
    aResponse.End();
}

void DvProviderLinnCoUkProduct2C::SetName(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaName)
{
    ASSERT(iCallbackSetName != NULL);
    if (0 != iCallbackSetName(iPtrSetName, aVersion, (const char*)aaName.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkProduct2C::Room(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaRoom)
{
    char* aRoom;
    ASSERT(iCallbackRoom != NULL);
    if (0 != iCallbackRoom(iPtrRoom, aVersion, &aRoom)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufaRoom((const TChar*)aRoom);
    ZappFreeExternal(aRoom);
    aaRoom.Write(bufaRoom);
    aaRoom.WriteFlush();
    aResponse.End();
}

void DvProviderLinnCoUkProduct2C::SetRoom(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaRoom)
{
    ASSERT(iCallbackSetRoom != NULL);
    if (0 != iCallbackSetRoom(iPtrSetRoom, aVersion, (const char*)aaRoom.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkProduct2C::Standby(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaStandby)
{
    uint32_t aStandby;
    ASSERT(iCallbackStandby != NULL);
    if (0 != iCallbackStandby(iPtrStandby, aVersion, &aStandby)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aaStandby.Write((aStandby!=0));
    aResponse.End();
}

void DvProviderLinnCoUkProduct2C::SetStandby(IInvocationResponse& aResponse, TUint aVersion, TBool aaStandby)
{
    ASSERT(iCallbackSetStandby != NULL);
    if (0 != iCallbackSetStandby(iPtrSetStandby, aVersion, aaStandby)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkProduct2C::SourceCount(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaSourceCount)
{
    uint32_t aSourceCount;
    ASSERT(iCallbackSourceCount != NULL);
    if (0 != iCallbackSourceCount(iPtrSourceCount, aVersion, &aSourceCount)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aaSourceCount.Write(aSourceCount);
    aResponse.End();
}

void DvProviderLinnCoUkProduct2C::SourceIndex(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaSourceIndex)
{
    uint32_t aSourceIndex;
    ASSERT(iCallbackSourceIndex != NULL);
    if (0 != iCallbackSourceIndex(iPtrSourceIndex, aVersion, &aSourceIndex)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aaSourceIndex.Write(aSourceIndex);
    aResponse.End();
}

void DvProviderLinnCoUkProduct2C::SetSourceIndex(IInvocationResponse& aResponse, TUint aVersion, TUint aaSourceIndex)
{
    ASSERT(iCallbackSetSourceIndex != NULL);
    if (0 != iCallbackSetSourceIndex(iPtrSetSourceIndex, aVersion, aaSourceIndex)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkProduct2C::SourceType(IInvocationResponse& aResponse, TUint aVersion, TUint aaSourceIndex, IInvocationResponseString& aaSourceType)
{
    char* aSourceType;
    ASSERT(iCallbackSourceType != NULL);
    if (0 != iCallbackSourceType(iPtrSourceType, aVersion, aaSourceIndex, &aSourceType)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufaSourceType((const TChar*)aSourceType);
    ZappFreeExternal(aSourceType);
    aaSourceType.Write(bufaSourceType);
    aaSourceType.WriteFlush();
    aResponse.End();
}



THandle DvProviderLinnCoUkProduct2Create(DvDeviceC aDevice)
{
	return new DvProviderLinnCoUkProduct2C(*(DviDeviceC::DeviceFromHandle(aDevice)));
}

void DvProviderLinnCoUkProduct2Destroy(THandle aService)
{
    delete reinterpret_cast<DvProviderLinnCoUkProduct2C*>(aService);
}

void DvProviderLinnCoUkProduct2EnableActionType(THandle aService, CallbackProduct2Type aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct2C*>(aService)->EnableActionType(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct2EnableActionModel(THandle aService, CallbackProduct2Model aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct2C*>(aService)->EnableActionModel(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct2EnableActionName(THandle aService, CallbackProduct2Name aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct2C*>(aService)->EnableActionName(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct2EnableActionSetName(THandle aService, CallbackProduct2SetName aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct2C*>(aService)->EnableActionSetName(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct2EnableActionRoom(THandle aService, CallbackProduct2Room aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct2C*>(aService)->EnableActionRoom(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct2EnableActionSetRoom(THandle aService, CallbackProduct2SetRoom aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct2C*>(aService)->EnableActionSetRoom(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct2EnableActionStandby(THandle aService, CallbackProduct2Standby aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct2C*>(aService)->EnableActionStandby(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct2EnableActionSetStandby(THandle aService, CallbackProduct2SetStandby aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct2C*>(aService)->EnableActionSetStandby(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct2EnableActionSourceCount(THandle aService, CallbackProduct2SourceCount aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct2C*>(aService)->EnableActionSourceCount(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct2EnableActionSourceIndex(THandle aService, CallbackProduct2SourceIndex aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct2C*>(aService)->EnableActionSourceIndex(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct2EnableActionSetSourceIndex(THandle aService, CallbackProduct2SetSourceIndex aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct2C*>(aService)->EnableActionSetSourceIndex(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct2EnableActionSourceType(THandle aService, CallbackProduct2SourceType aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct2C*>(aService)->EnableActionSourceType(aCallback, aPtr);
}

int32_t DvProviderLinnCoUkProduct2SetPropertyProductName(THandle aService, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkProduct2C*>(aService)->SetPropertyProductName(buf)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkProduct2GetPropertyProductName(THandle aService, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderLinnCoUkProduct2C*>(aService)->GetPropertyProductName(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvProviderLinnCoUkProduct2SetPropertyProductRoom(THandle aService, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkProduct2C*>(aService)->SetPropertyProductRoom(buf)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkProduct2GetPropertyProductRoom(THandle aService, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderLinnCoUkProduct2C*>(aService)->GetPropertyProductRoom(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvProviderLinnCoUkProduct2SetPropertyProductStandby(THandle aService, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkProduct2C*>(aService)->SetPropertyProductStandby((aValue!=0))? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkProduct2GetPropertyProductStandby(THandle aService, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvProviderLinnCoUkProduct2C*>(aService)->GetPropertyProductStandby(val);
    *aValue = (val? 1 : 0);
}

int32_t DvProviderLinnCoUkProduct2SetPropertyProductSourceIndex(THandle aService, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkProduct2C*>(aService)->SetPropertyProductSourceIndex(aValue)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkProduct2GetPropertyProductSourceIndex(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderLinnCoUkProduct2C*>(aService)->GetPropertyProductSourceIndex(val);
    *aValue = val;
}

