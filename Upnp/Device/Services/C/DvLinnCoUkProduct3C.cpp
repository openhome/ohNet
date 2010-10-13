#include <C/DvLinnCoUkProduct3.h>
#include <Core/DvLinnCoUkProduct3.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvServiceLinnCoUkProduct3C : public DvServiceLinnCoUkProduct3
{
public:
    DvServiceLinnCoUkProduct3C(DvDevice& aDevice);
    void EnableActionType(CallbackProduct3Type aCallback, void* aPtr);
    void EnableActionModel(CallbackProduct3Model aCallback, void* aPtr);
    void EnableActionName(CallbackProduct3Name aCallback, void* aPtr);
    void EnableActionSetName(CallbackProduct3SetName aCallback, void* aPtr);
    void EnableActionRoom(CallbackProduct3Room aCallback, void* aPtr);
    void EnableActionSetRoom(CallbackProduct3SetRoom aCallback, void* aPtr);
    void EnableActionStandby(CallbackProduct3Standby aCallback, void* aPtr);
    void EnableActionSetStandby(CallbackProduct3SetStandby aCallback, void* aPtr);
    void EnableActionSourceCount(CallbackProduct3SourceCount aCallback, void* aPtr);
    void EnableActionSourceXml(CallbackProduct3SourceXml aCallback, void* aPtr);
    void EnableActionSourceIndex(CallbackProduct3SourceIndex aCallback, void* aPtr);
    void EnableActionSetSourceIndex(CallbackProduct3SetSourceIndex aCallback, void* aPtr);
    void EnableActionSetSourceIndexByName(CallbackProduct3SetSourceIndexByName aCallback, void* aPtr);
    void EnableActionSetStartupSourceIndexByName(CallbackProduct3SetStartupSourceIndexByName aCallback, void* aPtr);
    void EnableActionStartupSourceIndex(CallbackProduct3StartupSourceIndex aCallback, void* aPtr);
    void EnableActionSetStartupSourceIndex(CallbackProduct3SetStartupSourceIndex aCallback, void* aPtr);
    void EnableActionStartupSourceEnabled(CallbackProduct3StartupSourceEnabled aCallback, void* aPtr);
    void EnableActionSetStartupSourceEnabled(CallbackProduct3SetStartupSourceEnabled aCallback, void* aPtr);
    void EnableActionSourceSystemName(CallbackProduct3SourceSystemName aCallback, void* aPtr);
    void EnableActionSourceName(CallbackProduct3SourceName aCallback, void* aPtr);
    void EnableActionSetSourceName(CallbackProduct3SetSourceName aCallback, void* aPtr);
    void EnableActionSourceType(CallbackProduct3SourceType aCallback, void* aPtr);
    void EnableActionSourceVisible(CallbackProduct3SourceVisible aCallback, void* aPtr);
    void EnableActionSetSourceVisible(CallbackProduct3SetSourceVisible aCallback, void* aPtr);
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
    void SourceXml(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaSourceXml);
    void SourceIndex(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaSourceIndex);
    void SetSourceIndex(IInvocationResponse& aResponse, TUint aVersion, TUint aaSourceIndex);
    void SetSourceIndexByName(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaSourceName);
    void SetStartupSourceIndexByName(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaSourceName);
    void StartupSourceIndex(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaSourceIndex);
    void SetStartupSourceIndex(IInvocationResponse& aResponse, TUint aVersion, TUint aaSourceIndex);
    void StartupSourceEnabled(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaStartupSourceEnabled);
    void SetStartupSourceEnabled(IInvocationResponse& aResponse, TUint aVersion, TBool aaStartupSourceEnabled);
    void SourceSystemName(IInvocationResponse& aResponse, TUint aVersion, TUint aaSourceIndex, IInvocationResponseString& aaSourceName);
    void SourceName(IInvocationResponse& aResponse, TUint aVersion, TUint aaSourceIndex, IInvocationResponseString& aaSourceName);
    void SetSourceName(IInvocationResponse& aResponse, TUint aVersion, TUint aaSourceIndex, const Brx& aaSourceName);
    void SourceType(IInvocationResponse& aResponse, TUint aVersion, TUint aaSourceIndex, IInvocationResponseString& aaSourceType);
    void SourceVisible(IInvocationResponse& aResponse, TUint aVersion, TUint aaSourceIndex, IInvocationResponseBool& aaSourceVisible);
    void SetSourceVisible(IInvocationResponse& aResponse, TUint aVersion, TUint aaSourceIndex, TBool aaSourceVisible);
private:
    CallbackProduct3Type iCallbackType;
    void* iPtrType;
    CallbackProduct3Model iCallbackModel;
    void* iPtrModel;
    CallbackProduct3Name iCallbackName;
    void* iPtrName;
    CallbackProduct3SetName iCallbackSetName;
    void* iPtrSetName;
    CallbackProduct3Room iCallbackRoom;
    void* iPtrRoom;
    CallbackProduct3SetRoom iCallbackSetRoom;
    void* iPtrSetRoom;
    CallbackProduct3Standby iCallbackStandby;
    void* iPtrStandby;
    CallbackProduct3SetStandby iCallbackSetStandby;
    void* iPtrSetStandby;
    CallbackProduct3SourceCount iCallbackSourceCount;
    void* iPtrSourceCount;
    CallbackProduct3SourceXml iCallbackSourceXml;
    void* iPtrSourceXml;
    CallbackProduct3SourceIndex iCallbackSourceIndex;
    void* iPtrSourceIndex;
    CallbackProduct3SetSourceIndex iCallbackSetSourceIndex;
    void* iPtrSetSourceIndex;
    CallbackProduct3SetSourceIndexByName iCallbackSetSourceIndexByName;
    void* iPtrSetSourceIndexByName;
    CallbackProduct3SetStartupSourceIndexByName iCallbackSetStartupSourceIndexByName;
    void* iPtrSetStartupSourceIndexByName;
    CallbackProduct3StartupSourceIndex iCallbackStartupSourceIndex;
    void* iPtrStartupSourceIndex;
    CallbackProduct3SetStartupSourceIndex iCallbackSetStartupSourceIndex;
    void* iPtrSetStartupSourceIndex;
    CallbackProduct3StartupSourceEnabled iCallbackStartupSourceEnabled;
    void* iPtrStartupSourceEnabled;
    CallbackProduct3SetStartupSourceEnabled iCallbackSetStartupSourceEnabled;
    void* iPtrSetStartupSourceEnabled;
    CallbackProduct3SourceSystemName iCallbackSourceSystemName;
    void* iPtrSourceSystemName;
    CallbackProduct3SourceName iCallbackSourceName;
    void* iPtrSourceName;
    CallbackProduct3SetSourceName iCallbackSetSourceName;
    void* iPtrSetSourceName;
    CallbackProduct3SourceType iCallbackSourceType;
    void* iPtrSourceType;
    CallbackProduct3SourceVisible iCallbackSourceVisible;
    void* iPtrSourceVisible;
    CallbackProduct3SetSourceVisible iCallbackSetSourceVisible;
    void* iPtrSetSourceVisible;
};

DvServiceLinnCoUkProduct3C::DvServiceLinnCoUkProduct3C(DvDevice& aDevice)
    : DvServiceLinnCoUkProduct3(aDevice)
{
}

void DvServiceLinnCoUkProduct3C::EnableActionType(CallbackProduct3Type aCallback, void* aPtr)
{
    iCallbackType = aCallback;
    iPtrType = aPtr;
    DvServiceLinnCoUkProduct3::EnableActionType();
}

void DvServiceLinnCoUkProduct3C::EnableActionModel(CallbackProduct3Model aCallback, void* aPtr)
{
    iCallbackModel = aCallback;
    iPtrModel = aPtr;
    DvServiceLinnCoUkProduct3::EnableActionModel();
}

void DvServiceLinnCoUkProduct3C::EnableActionName(CallbackProduct3Name aCallback, void* aPtr)
{
    iCallbackName = aCallback;
    iPtrName = aPtr;
    DvServiceLinnCoUkProduct3::EnableActionName();
}

void DvServiceLinnCoUkProduct3C::EnableActionSetName(CallbackProduct3SetName aCallback, void* aPtr)
{
    iCallbackSetName = aCallback;
    iPtrSetName = aPtr;
    DvServiceLinnCoUkProduct3::EnableActionSetName();
}

void DvServiceLinnCoUkProduct3C::EnableActionRoom(CallbackProduct3Room aCallback, void* aPtr)
{
    iCallbackRoom = aCallback;
    iPtrRoom = aPtr;
    DvServiceLinnCoUkProduct3::EnableActionRoom();
}

void DvServiceLinnCoUkProduct3C::EnableActionSetRoom(CallbackProduct3SetRoom aCallback, void* aPtr)
{
    iCallbackSetRoom = aCallback;
    iPtrSetRoom = aPtr;
    DvServiceLinnCoUkProduct3::EnableActionSetRoom();
}

void DvServiceLinnCoUkProduct3C::EnableActionStandby(CallbackProduct3Standby aCallback, void* aPtr)
{
    iCallbackStandby = aCallback;
    iPtrStandby = aPtr;
    DvServiceLinnCoUkProduct3::EnableActionStandby();
}

void DvServiceLinnCoUkProduct3C::EnableActionSetStandby(CallbackProduct3SetStandby aCallback, void* aPtr)
{
    iCallbackSetStandby = aCallback;
    iPtrSetStandby = aPtr;
    DvServiceLinnCoUkProduct3::EnableActionSetStandby();
}

void DvServiceLinnCoUkProduct3C::EnableActionSourceCount(CallbackProduct3SourceCount aCallback, void* aPtr)
{
    iCallbackSourceCount = aCallback;
    iPtrSourceCount = aPtr;
    DvServiceLinnCoUkProduct3::EnableActionSourceCount();
}

void DvServiceLinnCoUkProduct3C::EnableActionSourceXml(CallbackProduct3SourceXml aCallback, void* aPtr)
{
    iCallbackSourceXml = aCallback;
    iPtrSourceXml = aPtr;
    DvServiceLinnCoUkProduct3::EnableActionSourceXml();
}

void DvServiceLinnCoUkProduct3C::EnableActionSourceIndex(CallbackProduct3SourceIndex aCallback, void* aPtr)
{
    iCallbackSourceIndex = aCallback;
    iPtrSourceIndex = aPtr;
    DvServiceLinnCoUkProduct3::EnableActionSourceIndex();
}

void DvServiceLinnCoUkProduct3C::EnableActionSetSourceIndex(CallbackProduct3SetSourceIndex aCallback, void* aPtr)
{
    iCallbackSetSourceIndex = aCallback;
    iPtrSetSourceIndex = aPtr;
    DvServiceLinnCoUkProduct3::EnableActionSetSourceIndex();
}

void DvServiceLinnCoUkProduct3C::EnableActionSetSourceIndexByName(CallbackProduct3SetSourceIndexByName aCallback, void* aPtr)
{
    iCallbackSetSourceIndexByName = aCallback;
    iPtrSetSourceIndexByName = aPtr;
    DvServiceLinnCoUkProduct3::EnableActionSetSourceIndexByName();
}

void DvServiceLinnCoUkProduct3C::EnableActionSetStartupSourceIndexByName(CallbackProduct3SetStartupSourceIndexByName aCallback, void* aPtr)
{
    iCallbackSetStartupSourceIndexByName = aCallback;
    iPtrSetStartupSourceIndexByName = aPtr;
    DvServiceLinnCoUkProduct3::EnableActionSetStartupSourceIndexByName();
}

void DvServiceLinnCoUkProduct3C::EnableActionStartupSourceIndex(CallbackProduct3StartupSourceIndex aCallback, void* aPtr)
{
    iCallbackStartupSourceIndex = aCallback;
    iPtrStartupSourceIndex = aPtr;
    DvServiceLinnCoUkProduct3::EnableActionStartupSourceIndex();
}

void DvServiceLinnCoUkProduct3C::EnableActionSetStartupSourceIndex(CallbackProduct3SetStartupSourceIndex aCallback, void* aPtr)
{
    iCallbackSetStartupSourceIndex = aCallback;
    iPtrSetStartupSourceIndex = aPtr;
    DvServiceLinnCoUkProduct3::EnableActionSetStartupSourceIndex();
}

void DvServiceLinnCoUkProduct3C::EnableActionStartupSourceEnabled(CallbackProduct3StartupSourceEnabled aCallback, void* aPtr)
{
    iCallbackStartupSourceEnabled = aCallback;
    iPtrStartupSourceEnabled = aPtr;
    DvServiceLinnCoUkProduct3::EnableActionStartupSourceEnabled();
}

void DvServiceLinnCoUkProduct3C::EnableActionSetStartupSourceEnabled(CallbackProduct3SetStartupSourceEnabled aCallback, void* aPtr)
{
    iCallbackSetStartupSourceEnabled = aCallback;
    iPtrSetStartupSourceEnabled = aPtr;
    DvServiceLinnCoUkProduct3::EnableActionSetStartupSourceEnabled();
}

void DvServiceLinnCoUkProduct3C::EnableActionSourceSystemName(CallbackProduct3SourceSystemName aCallback, void* aPtr)
{
    iCallbackSourceSystemName = aCallback;
    iPtrSourceSystemName = aPtr;
    DvServiceLinnCoUkProduct3::EnableActionSourceSystemName();
}

void DvServiceLinnCoUkProduct3C::EnableActionSourceName(CallbackProduct3SourceName aCallback, void* aPtr)
{
    iCallbackSourceName = aCallback;
    iPtrSourceName = aPtr;
    DvServiceLinnCoUkProduct3::EnableActionSourceName();
}

void DvServiceLinnCoUkProduct3C::EnableActionSetSourceName(CallbackProduct3SetSourceName aCallback, void* aPtr)
{
    iCallbackSetSourceName = aCallback;
    iPtrSetSourceName = aPtr;
    DvServiceLinnCoUkProduct3::EnableActionSetSourceName();
}

void DvServiceLinnCoUkProduct3C::EnableActionSourceType(CallbackProduct3SourceType aCallback, void* aPtr)
{
    iCallbackSourceType = aCallback;
    iPtrSourceType = aPtr;
    DvServiceLinnCoUkProduct3::EnableActionSourceType();
}

void DvServiceLinnCoUkProduct3C::EnableActionSourceVisible(CallbackProduct3SourceVisible aCallback, void* aPtr)
{
    iCallbackSourceVisible = aCallback;
    iPtrSourceVisible = aPtr;
    DvServiceLinnCoUkProduct3::EnableActionSourceVisible();
}

void DvServiceLinnCoUkProduct3C::EnableActionSetSourceVisible(CallbackProduct3SetSourceVisible aCallback, void* aPtr)
{
    iCallbackSetSourceVisible = aCallback;
    iPtrSetSourceVisible = aPtr;
    DvServiceLinnCoUkProduct3::EnableActionSetSourceVisible();
}

void DvServiceLinnCoUkProduct3C::Type(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaType)
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

void DvServiceLinnCoUkProduct3C::Model(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaModel)
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

void DvServiceLinnCoUkProduct3C::Name(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaName)
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

void DvServiceLinnCoUkProduct3C::SetName(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaName)
{
    ASSERT(iCallbackSetName != NULL);
    if (0 != iCallbackSetName(iPtrSetName, aVersion, (const char*)aaName.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkProduct3C::Room(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaRoom)
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

void DvServiceLinnCoUkProduct3C::SetRoom(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaRoom)
{
    ASSERT(iCallbackSetRoom != NULL);
    if (0 != iCallbackSetRoom(iPtrSetRoom, aVersion, (const char*)aaRoom.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkProduct3C::Standby(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaStandby)
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

void DvServiceLinnCoUkProduct3C::SetStandby(IInvocationResponse& aResponse, TUint aVersion, TBool aaStandby)
{
    ASSERT(iCallbackSetStandby != NULL);
    if (0 != iCallbackSetStandby(iPtrSetStandby, aVersion, aaStandby)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkProduct3C::SourceCount(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaSourceCount)
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

void DvServiceLinnCoUkProduct3C::SourceXml(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaSourceXml)
{
    char* aSourceXml;
    ASSERT(iCallbackSourceXml != NULL);
    if (0 != iCallbackSourceXml(iPtrSourceXml, aVersion, &aSourceXml)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufaSourceXml((const TChar*)aSourceXml);
    ZappFreeExternal(aSourceXml);
    aaSourceXml.Write(bufaSourceXml);
    aaSourceXml.WriteFlush();
    aResponse.End();
}

void DvServiceLinnCoUkProduct3C::SourceIndex(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaSourceIndex)
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

void DvServiceLinnCoUkProduct3C::SetSourceIndex(IInvocationResponse& aResponse, TUint aVersion, TUint aaSourceIndex)
{
    ASSERT(iCallbackSetSourceIndex != NULL);
    if (0 != iCallbackSetSourceIndex(iPtrSetSourceIndex, aVersion, aaSourceIndex)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkProduct3C::SetSourceIndexByName(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaSourceName)
{
    ASSERT(iCallbackSetSourceIndexByName != NULL);
    if (0 != iCallbackSetSourceIndexByName(iPtrSetSourceIndexByName, aVersion, (const char*)aaSourceName.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkProduct3C::SetStartupSourceIndexByName(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaSourceName)
{
    ASSERT(iCallbackSetStartupSourceIndexByName != NULL);
    if (0 != iCallbackSetStartupSourceIndexByName(iPtrSetStartupSourceIndexByName, aVersion, (const char*)aaSourceName.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkProduct3C::StartupSourceIndex(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaSourceIndex)
{
    uint32_t aSourceIndex;
    ASSERT(iCallbackStartupSourceIndex != NULL);
    if (0 != iCallbackStartupSourceIndex(iPtrStartupSourceIndex, aVersion, &aSourceIndex)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aaSourceIndex.Write(aSourceIndex);
    aResponse.End();
}

void DvServiceLinnCoUkProduct3C::SetStartupSourceIndex(IInvocationResponse& aResponse, TUint aVersion, TUint aaSourceIndex)
{
    ASSERT(iCallbackSetStartupSourceIndex != NULL);
    if (0 != iCallbackSetStartupSourceIndex(iPtrSetStartupSourceIndex, aVersion, aaSourceIndex)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkProduct3C::StartupSourceEnabled(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaStartupSourceEnabled)
{
    uint32_t aStartupSourceEnabled;
    ASSERT(iCallbackStartupSourceEnabled != NULL);
    if (0 != iCallbackStartupSourceEnabled(iPtrStartupSourceEnabled, aVersion, &aStartupSourceEnabled)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aaStartupSourceEnabled.Write((aStartupSourceEnabled!=0));
    aResponse.End();
}

void DvServiceLinnCoUkProduct3C::SetStartupSourceEnabled(IInvocationResponse& aResponse, TUint aVersion, TBool aaStartupSourceEnabled)
{
    ASSERT(iCallbackSetStartupSourceEnabled != NULL);
    if (0 != iCallbackSetStartupSourceEnabled(iPtrSetStartupSourceEnabled, aVersion, aaStartupSourceEnabled)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkProduct3C::SourceSystemName(IInvocationResponse& aResponse, TUint aVersion, TUint aaSourceIndex, IInvocationResponseString& aaSourceName)
{
    char* aSourceName;
    ASSERT(iCallbackSourceSystemName != NULL);
    if (0 != iCallbackSourceSystemName(iPtrSourceSystemName, aVersion, aaSourceIndex, &aSourceName)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufaSourceName((const TChar*)aSourceName);
    ZappFreeExternal(aSourceName);
    aaSourceName.Write(bufaSourceName);
    aaSourceName.WriteFlush();
    aResponse.End();
}

void DvServiceLinnCoUkProduct3C::SourceName(IInvocationResponse& aResponse, TUint aVersion, TUint aaSourceIndex, IInvocationResponseString& aaSourceName)
{
    char* aSourceName;
    ASSERT(iCallbackSourceName != NULL);
    if (0 != iCallbackSourceName(iPtrSourceName, aVersion, aaSourceIndex, &aSourceName)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufaSourceName((const TChar*)aSourceName);
    ZappFreeExternal(aSourceName);
    aaSourceName.Write(bufaSourceName);
    aaSourceName.WriteFlush();
    aResponse.End();
}

void DvServiceLinnCoUkProduct3C::SetSourceName(IInvocationResponse& aResponse, TUint aVersion, TUint aaSourceIndex, const Brx& aaSourceName)
{
    ASSERT(iCallbackSetSourceName != NULL);
    if (0 != iCallbackSetSourceName(iPtrSetSourceName, aVersion, aaSourceIndex, (const char*)aaSourceName.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkProduct3C::SourceType(IInvocationResponse& aResponse, TUint aVersion, TUint aaSourceIndex, IInvocationResponseString& aaSourceType)
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

void DvServiceLinnCoUkProduct3C::SourceVisible(IInvocationResponse& aResponse, TUint aVersion, TUint aaSourceIndex, IInvocationResponseBool& aaSourceVisible)
{
    uint32_t aSourceVisible;
    ASSERT(iCallbackSourceVisible != NULL);
    if (0 != iCallbackSourceVisible(iPtrSourceVisible, aVersion, aaSourceIndex, &aSourceVisible)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aaSourceVisible.Write((aSourceVisible!=0));
    aResponse.End();
}

void DvServiceLinnCoUkProduct3C::SetSourceVisible(IInvocationResponse& aResponse, TUint aVersion, TUint aaSourceIndex, TBool aaSourceVisible)
{
    ASSERT(iCallbackSetSourceVisible != NULL);
    if (0 != iCallbackSetSourceVisible(iPtrSetSourceVisible, aVersion, aaSourceIndex, aaSourceVisible)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}



THandle DvServiceLinnCoUkProduct3Create(DvDeviceC aDevice)
{
    return (THandle)new DvServiceLinnCoUkProduct3C(*(DviDeviceC::DeviceFromHandle(aDevice)));
}

void DvServiceLinnCoUkProduct3Destroy(THandle aService)
{
    delete reinterpret_cast<DvServiceLinnCoUkProduct3C*>(aService);
}

void DvServiceLinnCoUkProduct3EnableActionType(THandle aService, CallbackProduct3Type aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkProduct3C*>(aService)->EnableActionType(aCallback, aPtr);
}

void DvServiceLinnCoUkProduct3EnableActionModel(THandle aService, CallbackProduct3Model aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkProduct3C*>(aService)->EnableActionModel(aCallback, aPtr);
}

void DvServiceLinnCoUkProduct3EnableActionName(THandle aService, CallbackProduct3Name aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkProduct3C*>(aService)->EnableActionName(aCallback, aPtr);
}

void DvServiceLinnCoUkProduct3EnableActionSetName(THandle aService, CallbackProduct3SetName aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkProduct3C*>(aService)->EnableActionSetName(aCallback, aPtr);
}

void DvServiceLinnCoUkProduct3EnableActionRoom(THandle aService, CallbackProduct3Room aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkProduct3C*>(aService)->EnableActionRoom(aCallback, aPtr);
}

void DvServiceLinnCoUkProduct3EnableActionSetRoom(THandle aService, CallbackProduct3SetRoom aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkProduct3C*>(aService)->EnableActionSetRoom(aCallback, aPtr);
}

void DvServiceLinnCoUkProduct3EnableActionStandby(THandle aService, CallbackProduct3Standby aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkProduct3C*>(aService)->EnableActionStandby(aCallback, aPtr);
}

void DvServiceLinnCoUkProduct3EnableActionSetStandby(THandle aService, CallbackProduct3SetStandby aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkProduct3C*>(aService)->EnableActionSetStandby(aCallback, aPtr);
}

void DvServiceLinnCoUkProduct3EnableActionSourceCount(THandle aService, CallbackProduct3SourceCount aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkProduct3C*>(aService)->EnableActionSourceCount(aCallback, aPtr);
}

void DvServiceLinnCoUkProduct3EnableActionSourceXml(THandle aService, CallbackProduct3SourceXml aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkProduct3C*>(aService)->EnableActionSourceXml(aCallback, aPtr);
}

void DvServiceLinnCoUkProduct3EnableActionSourceIndex(THandle aService, CallbackProduct3SourceIndex aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkProduct3C*>(aService)->EnableActionSourceIndex(aCallback, aPtr);
}

void DvServiceLinnCoUkProduct3EnableActionSetSourceIndex(THandle aService, CallbackProduct3SetSourceIndex aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkProduct3C*>(aService)->EnableActionSetSourceIndex(aCallback, aPtr);
}

void DvServiceLinnCoUkProduct3EnableActionSetSourceIndexByName(THandle aService, CallbackProduct3SetSourceIndexByName aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkProduct3C*>(aService)->EnableActionSetSourceIndexByName(aCallback, aPtr);
}

void DvServiceLinnCoUkProduct3EnableActionSetStartupSourceIndexByName(THandle aService, CallbackProduct3SetStartupSourceIndexByName aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkProduct3C*>(aService)->EnableActionSetStartupSourceIndexByName(aCallback, aPtr);
}

void DvServiceLinnCoUkProduct3EnableActionStartupSourceIndex(THandle aService, CallbackProduct3StartupSourceIndex aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkProduct3C*>(aService)->EnableActionStartupSourceIndex(aCallback, aPtr);
}

void DvServiceLinnCoUkProduct3EnableActionSetStartupSourceIndex(THandle aService, CallbackProduct3SetStartupSourceIndex aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkProduct3C*>(aService)->EnableActionSetStartupSourceIndex(aCallback, aPtr);
}

void DvServiceLinnCoUkProduct3EnableActionStartupSourceEnabled(THandle aService, CallbackProduct3StartupSourceEnabled aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkProduct3C*>(aService)->EnableActionStartupSourceEnabled(aCallback, aPtr);
}

void DvServiceLinnCoUkProduct3EnableActionSetStartupSourceEnabled(THandle aService, CallbackProduct3SetStartupSourceEnabled aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkProduct3C*>(aService)->EnableActionSetStartupSourceEnabled(aCallback, aPtr);
}

void DvServiceLinnCoUkProduct3EnableActionSourceSystemName(THandle aService, CallbackProduct3SourceSystemName aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkProduct3C*>(aService)->EnableActionSourceSystemName(aCallback, aPtr);
}

void DvServiceLinnCoUkProduct3EnableActionSourceName(THandle aService, CallbackProduct3SourceName aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkProduct3C*>(aService)->EnableActionSourceName(aCallback, aPtr);
}

void DvServiceLinnCoUkProduct3EnableActionSetSourceName(THandle aService, CallbackProduct3SetSourceName aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkProduct3C*>(aService)->EnableActionSetSourceName(aCallback, aPtr);
}

void DvServiceLinnCoUkProduct3EnableActionSourceType(THandle aService, CallbackProduct3SourceType aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkProduct3C*>(aService)->EnableActionSourceType(aCallback, aPtr);
}

void DvServiceLinnCoUkProduct3EnableActionSourceVisible(THandle aService, CallbackProduct3SourceVisible aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkProduct3C*>(aService)->EnableActionSourceVisible(aCallback, aPtr);
}

void DvServiceLinnCoUkProduct3EnableActionSetSourceVisible(THandle aService, CallbackProduct3SetSourceVisible aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkProduct3C*>(aService)->EnableActionSetSourceVisible(aCallback, aPtr);
}

int32_t DvServiceLinnCoUkProduct3SetPropertyProductType(THandle aService, const char* aValue)
{
    Brhz buf(aValue);
    reinterpret_cast<DvServiceLinnCoUkProduct3C*>(aService)->SetPropertyProductType(buf);
    return 0;
}

void DvServiceLinnCoUkProduct3GetPropertyProductType(THandle aService, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvServiceLinnCoUkProduct3C*>(aService)->GetPropertyProductType(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvServiceLinnCoUkProduct3SetPropertyProductModel(THandle aService, const char* aValue)
{
    Brhz buf(aValue);
    reinterpret_cast<DvServiceLinnCoUkProduct3C*>(aService)->SetPropertyProductModel(buf);
    return 0;
}

void DvServiceLinnCoUkProduct3GetPropertyProductModel(THandle aService, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvServiceLinnCoUkProduct3C*>(aService)->GetPropertyProductModel(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvServiceLinnCoUkProduct3SetPropertyProductName(THandle aService, const char* aValue)
{
    Brhz buf(aValue);
    reinterpret_cast<DvServiceLinnCoUkProduct3C*>(aService)->SetPropertyProductName(buf);
    return 0;
}

void DvServiceLinnCoUkProduct3GetPropertyProductName(THandle aService, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvServiceLinnCoUkProduct3C*>(aService)->GetPropertyProductName(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvServiceLinnCoUkProduct3SetPropertyProductRoom(THandle aService, const char* aValue)
{
    Brhz buf(aValue);
    reinterpret_cast<DvServiceLinnCoUkProduct3C*>(aService)->SetPropertyProductRoom(buf);
    return 0;
}

void DvServiceLinnCoUkProduct3GetPropertyProductRoom(THandle aService, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvServiceLinnCoUkProduct3C*>(aService)->GetPropertyProductRoom(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvServiceLinnCoUkProduct3SetPropertyProductStandby(THandle aService, uint32_t aValue)
{
    reinterpret_cast<DvServiceLinnCoUkProduct3C*>(aService)->SetPropertyProductStandby((aValue!=0));
    return 0;
}

void DvServiceLinnCoUkProduct3GetPropertyProductStandby(THandle aService, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvServiceLinnCoUkProduct3C*>(aService)->GetPropertyProductStandby(val);
    *aValue = (val? 1 : 0);
}

int32_t DvServiceLinnCoUkProduct3SetPropertyProductSourceIndex(THandle aService, uint32_t aValue)
{
    reinterpret_cast<DvServiceLinnCoUkProduct3C*>(aService)->SetPropertyProductSourceIndex(aValue);
    return 0;
}

void DvServiceLinnCoUkProduct3GetPropertyProductSourceIndex(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvServiceLinnCoUkProduct3C*>(aService)->GetPropertyProductSourceIndex(val);
    *aValue = val;
}

int32_t DvServiceLinnCoUkProduct3SetPropertyProductSourceCount(THandle aService, uint32_t aValue)
{
    reinterpret_cast<DvServiceLinnCoUkProduct3C*>(aService)->SetPropertyProductSourceCount(aValue);
    return 0;
}

void DvServiceLinnCoUkProduct3GetPropertyProductSourceCount(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvServiceLinnCoUkProduct3C*>(aService)->GetPropertyProductSourceCount(val);
    *aValue = val;
}

int32_t DvServiceLinnCoUkProduct3SetPropertyProductSourceXml(THandle aService, const char* aValue)
{
    Brhz buf(aValue);
    reinterpret_cast<DvServiceLinnCoUkProduct3C*>(aService)->SetPropertyProductSourceXml(buf);
    return 0;
}

void DvServiceLinnCoUkProduct3GetPropertyProductSourceXml(THandle aService, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvServiceLinnCoUkProduct3C*>(aService)->GetPropertyProductSourceXml(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvServiceLinnCoUkProduct3SetPropertyStartupSourceIndex(THandle aService, uint32_t aValue)
{
    reinterpret_cast<DvServiceLinnCoUkProduct3C*>(aService)->SetPropertyStartupSourceIndex(aValue);
    return 0;
}

void DvServiceLinnCoUkProduct3GetPropertyStartupSourceIndex(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvServiceLinnCoUkProduct3C*>(aService)->GetPropertyStartupSourceIndex(val);
    *aValue = val;
}

int32_t DvServiceLinnCoUkProduct3SetPropertyStartupSourceEnabled(THandle aService, uint32_t aValue)
{
    reinterpret_cast<DvServiceLinnCoUkProduct3C*>(aService)->SetPropertyStartupSourceEnabled((aValue!=0));
    return 0;
}

void DvServiceLinnCoUkProduct3GetPropertyStartupSourceEnabled(THandle aService, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvServiceLinnCoUkProduct3C*>(aService)->GetPropertyStartupSourceEnabled(val);
    *aValue = (val? 1 : 0);
}

int32_t DvServiceLinnCoUkProduct3SetPropertyProductAnySourceName(THandle aService, uint32_t aValue)
{
    reinterpret_cast<DvServiceLinnCoUkProduct3C*>(aService)->SetPropertyProductAnySourceName(aValue);
    return 0;
}

void DvServiceLinnCoUkProduct3GetPropertyProductAnySourceName(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvServiceLinnCoUkProduct3C*>(aService)->GetPropertyProductAnySourceName(val);
    *aValue = val;
}

int32_t DvServiceLinnCoUkProduct3SetPropertyProductAnySourceVisible(THandle aService, uint32_t aValue)
{
    reinterpret_cast<DvServiceLinnCoUkProduct3C*>(aService)->SetPropertyProductAnySourceVisible(aValue);
    return 0;
}

void DvServiceLinnCoUkProduct3GetPropertyProductAnySourceVisible(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvServiceLinnCoUkProduct3C*>(aService)->GetPropertyProductAnySourceVisible(val);
    *aValue = val;
}

int32_t DvServiceLinnCoUkProduct3SetPropertyProductAnySourceType(THandle aService, uint32_t aValue)
{
    reinterpret_cast<DvServiceLinnCoUkProduct3C*>(aService)->SetPropertyProductAnySourceType(aValue);
    return 0;
}

void DvServiceLinnCoUkProduct3GetPropertyProductAnySourceType(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvServiceLinnCoUkProduct3C*>(aService)->GetPropertyProductAnySourceType(val);
    *aValue = val;
}

