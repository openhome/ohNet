#include "DvLinnCoUkProduct3C.h"
#include "DvLinnCoUkProduct3.h"
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvProviderLinnCoUkProduct3C : public DvProviderLinnCoUkProduct3
{
public:
    DvProviderLinnCoUkProduct3C(DvDevice& aDevice);
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

DvProviderLinnCoUkProduct3C::DvProviderLinnCoUkProduct3C(DvDevice& aDevice)
    : DvProviderLinnCoUkProduct3(aDevice)
{
}

void DvProviderLinnCoUkProduct3C::EnableActionType(CallbackProduct3Type aCallback, void* aPtr)
{
    iCallbackType = aCallback;
    iPtrType = aPtr;
    DvProviderLinnCoUkProduct3::EnableActionType();
}

void DvProviderLinnCoUkProduct3C::EnableActionModel(CallbackProduct3Model aCallback, void* aPtr)
{
    iCallbackModel = aCallback;
    iPtrModel = aPtr;
    DvProviderLinnCoUkProduct3::EnableActionModel();
}

void DvProviderLinnCoUkProduct3C::EnableActionName(CallbackProduct3Name aCallback, void* aPtr)
{
    iCallbackName = aCallback;
    iPtrName = aPtr;
    DvProviderLinnCoUkProduct3::EnableActionName();
}

void DvProviderLinnCoUkProduct3C::EnableActionSetName(CallbackProduct3SetName aCallback, void* aPtr)
{
    iCallbackSetName = aCallback;
    iPtrSetName = aPtr;
    DvProviderLinnCoUkProduct3::EnableActionSetName();
}

void DvProviderLinnCoUkProduct3C::EnableActionRoom(CallbackProduct3Room aCallback, void* aPtr)
{
    iCallbackRoom = aCallback;
    iPtrRoom = aPtr;
    DvProviderLinnCoUkProduct3::EnableActionRoom();
}

void DvProviderLinnCoUkProduct3C::EnableActionSetRoom(CallbackProduct3SetRoom aCallback, void* aPtr)
{
    iCallbackSetRoom = aCallback;
    iPtrSetRoom = aPtr;
    DvProviderLinnCoUkProduct3::EnableActionSetRoom();
}

void DvProviderLinnCoUkProduct3C::EnableActionStandby(CallbackProduct3Standby aCallback, void* aPtr)
{
    iCallbackStandby = aCallback;
    iPtrStandby = aPtr;
    DvProviderLinnCoUkProduct3::EnableActionStandby();
}

void DvProviderLinnCoUkProduct3C::EnableActionSetStandby(CallbackProduct3SetStandby aCallback, void* aPtr)
{
    iCallbackSetStandby = aCallback;
    iPtrSetStandby = aPtr;
    DvProviderLinnCoUkProduct3::EnableActionSetStandby();
}

void DvProviderLinnCoUkProduct3C::EnableActionSourceCount(CallbackProduct3SourceCount aCallback, void* aPtr)
{
    iCallbackSourceCount = aCallback;
    iPtrSourceCount = aPtr;
    DvProviderLinnCoUkProduct3::EnableActionSourceCount();
}

void DvProviderLinnCoUkProduct3C::EnableActionSourceXml(CallbackProduct3SourceXml aCallback, void* aPtr)
{
    iCallbackSourceXml = aCallback;
    iPtrSourceXml = aPtr;
    DvProviderLinnCoUkProduct3::EnableActionSourceXml();
}

void DvProviderLinnCoUkProduct3C::EnableActionSourceIndex(CallbackProduct3SourceIndex aCallback, void* aPtr)
{
    iCallbackSourceIndex = aCallback;
    iPtrSourceIndex = aPtr;
    DvProviderLinnCoUkProduct3::EnableActionSourceIndex();
}

void DvProviderLinnCoUkProduct3C::EnableActionSetSourceIndex(CallbackProduct3SetSourceIndex aCallback, void* aPtr)
{
    iCallbackSetSourceIndex = aCallback;
    iPtrSetSourceIndex = aPtr;
    DvProviderLinnCoUkProduct3::EnableActionSetSourceIndex();
}

void DvProviderLinnCoUkProduct3C::EnableActionSetSourceIndexByName(CallbackProduct3SetSourceIndexByName aCallback, void* aPtr)
{
    iCallbackSetSourceIndexByName = aCallback;
    iPtrSetSourceIndexByName = aPtr;
    DvProviderLinnCoUkProduct3::EnableActionSetSourceIndexByName();
}

void DvProviderLinnCoUkProduct3C::EnableActionSetStartupSourceIndexByName(CallbackProduct3SetStartupSourceIndexByName aCallback, void* aPtr)
{
    iCallbackSetStartupSourceIndexByName = aCallback;
    iPtrSetStartupSourceIndexByName = aPtr;
    DvProviderLinnCoUkProduct3::EnableActionSetStartupSourceIndexByName();
}

void DvProviderLinnCoUkProduct3C::EnableActionStartupSourceIndex(CallbackProduct3StartupSourceIndex aCallback, void* aPtr)
{
    iCallbackStartupSourceIndex = aCallback;
    iPtrStartupSourceIndex = aPtr;
    DvProviderLinnCoUkProduct3::EnableActionStartupSourceIndex();
}

void DvProviderLinnCoUkProduct3C::EnableActionSetStartupSourceIndex(CallbackProduct3SetStartupSourceIndex aCallback, void* aPtr)
{
    iCallbackSetStartupSourceIndex = aCallback;
    iPtrSetStartupSourceIndex = aPtr;
    DvProviderLinnCoUkProduct3::EnableActionSetStartupSourceIndex();
}

void DvProviderLinnCoUkProduct3C::EnableActionStartupSourceEnabled(CallbackProduct3StartupSourceEnabled aCallback, void* aPtr)
{
    iCallbackStartupSourceEnabled = aCallback;
    iPtrStartupSourceEnabled = aPtr;
    DvProviderLinnCoUkProduct3::EnableActionStartupSourceEnabled();
}

void DvProviderLinnCoUkProduct3C::EnableActionSetStartupSourceEnabled(CallbackProduct3SetStartupSourceEnabled aCallback, void* aPtr)
{
    iCallbackSetStartupSourceEnabled = aCallback;
    iPtrSetStartupSourceEnabled = aPtr;
    DvProviderLinnCoUkProduct3::EnableActionSetStartupSourceEnabled();
}

void DvProviderLinnCoUkProduct3C::EnableActionSourceSystemName(CallbackProduct3SourceSystemName aCallback, void* aPtr)
{
    iCallbackSourceSystemName = aCallback;
    iPtrSourceSystemName = aPtr;
    DvProviderLinnCoUkProduct3::EnableActionSourceSystemName();
}

void DvProviderLinnCoUkProduct3C::EnableActionSourceName(CallbackProduct3SourceName aCallback, void* aPtr)
{
    iCallbackSourceName = aCallback;
    iPtrSourceName = aPtr;
    DvProviderLinnCoUkProduct3::EnableActionSourceName();
}

void DvProviderLinnCoUkProduct3C::EnableActionSetSourceName(CallbackProduct3SetSourceName aCallback, void* aPtr)
{
    iCallbackSetSourceName = aCallback;
    iPtrSetSourceName = aPtr;
    DvProviderLinnCoUkProduct3::EnableActionSetSourceName();
}

void DvProviderLinnCoUkProduct3C::EnableActionSourceType(CallbackProduct3SourceType aCallback, void* aPtr)
{
    iCallbackSourceType = aCallback;
    iPtrSourceType = aPtr;
    DvProviderLinnCoUkProduct3::EnableActionSourceType();
}

void DvProviderLinnCoUkProduct3C::EnableActionSourceVisible(CallbackProduct3SourceVisible aCallback, void* aPtr)
{
    iCallbackSourceVisible = aCallback;
    iPtrSourceVisible = aPtr;
    DvProviderLinnCoUkProduct3::EnableActionSourceVisible();
}

void DvProviderLinnCoUkProduct3C::EnableActionSetSourceVisible(CallbackProduct3SetSourceVisible aCallback, void* aPtr)
{
    iCallbackSetSourceVisible = aCallback;
    iPtrSetSourceVisible = aPtr;
    DvProviderLinnCoUkProduct3::EnableActionSetSourceVisible();
}

void DvProviderLinnCoUkProduct3C::Type(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaType)
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

void DvProviderLinnCoUkProduct3C::Model(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaModel)
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

void DvProviderLinnCoUkProduct3C::Name(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaName)
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

void DvProviderLinnCoUkProduct3C::SetName(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaName)
{
    ASSERT(iCallbackSetName != NULL);
    if (0 != iCallbackSetName(iPtrSetName, aVersion, (const char*)aaName.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkProduct3C::Room(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaRoom)
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

void DvProviderLinnCoUkProduct3C::SetRoom(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaRoom)
{
    ASSERT(iCallbackSetRoom != NULL);
    if (0 != iCallbackSetRoom(iPtrSetRoom, aVersion, (const char*)aaRoom.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkProduct3C::Standby(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaStandby)
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

void DvProviderLinnCoUkProduct3C::SetStandby(IInvocationResponse& aResponse, TUint aVersion, TBool aaStandby)
{
    ASSERT(iCallbackSetStandby != NULL);
    if (0 != iCallbackSetStandby(iPtrSetStandby, aVersion, aaStandby)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkProduct3C::SourceCount(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaSourceCount)
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

void DvProviderLinnCoUkProduct3C::SourceXml(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaSourceXml)
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

void DvProviderLinnCoUkProduct3C::SourceIndex(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaSourceIndex)
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

void DvProviderLinnCoUkProduct3C::SetSourceIndex(IInvocationResponse& aResponse, TUint aVersion, TUint aaSourceIndex)
{
    ASSERT(iCallbackSetSourceIndex != NULL);
    if (0 != iCallbackSetSourceIndex(iPtrSetSourceIndex, aVersion, aaSourceIndex)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkProduct3C::SetSourceIndexByName(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaSourceName)
{
    ASSERT(iCallbackSetSourceIndexByName != NULL);
    if (0 != iCallbackSetSourceIndexByName(iPtrSetSourceIndexByName, aVersion, (const char*)aaSourceName.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkProduct3C::SetStartupSourceIndexByName(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaSourceName)
{
    ASSERT(iCallbackSetStartupSourceIndexByName != NULL);
    if (0 != iCallbackSetStartupSourceIndexByName(iPtrSetStartupSourceIndexByName, aVersion, (const char*)aaSourceName.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkProduct3C::StartupSourceIndex(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaSourceIndex)
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

void DvProviderLinnCoUkProduct3C::SetStartupSourceIndex(IInvocationResponse& aResponse, TUint aVersion, TUint aaSourceIndex)
{
    ASSERT(iCallbackSetStartupSourceIndex != NULL);
    if (0 != iCallbackSetStartupSourceIndex(iPtrSetStartupSourceIndex, aVersion, aaSourceIndex)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkProduct3C::StartupSourceEnabled(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaStartupSourceEnabled)
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

void DvProviderLinnCoUkProduct3C::SetStartupSourceEnabled(IInvocationResponse& aResponse, TUint aVersion, TBool aaStartupSourceEnabled)
{
    ASSERT(iCallbackSetStartupSourceEnabled != NULL);
    if (0 != iCallbackSetStartupSourceEnabled(iPtrSetStartupSourceEnabled, aVersion, aaStartupSourceEnabled)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkProduct3C::SourceSystemName(IInvocationResponse& aResponse, TUint aVersion, TUint aaSourceIndex, IInvocationResponseString& aaSourceName)
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

void DvProviderLinnCoUkProduct3C::SourceName(IInvocationResponse& aResponse, TUint aVersion, TUint aaSourceIndex, IInvocationResponseString& aaSourceName)
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

void DvProviderLinnCoUkProduct3C::SetSourceName(IInvocationResponse& aResponse, TUint aVersion, TUint aaSourceIndex, const Brx& aaSourceName)
{
    ASSERT(iCallbackSetSourceName != NULL);
    if (0 != iCallbackSetSourceName(iPtrSetSourceName, aVersion, aaSourceIndex, (const char*)aaSourceName.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkProduct3C::SourceType(IInvocationResponse& aResponse, TUint aVersion, TUint aaSourceIndex, IInvocationResponseString& aaSourceType)
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

void DvProviderLinnCoUkProduct3C::SourceVisible(IInvocationResponse& aResponse, TUint aVersion, TUint aaSourceIndex, IInvocationResponseBool& aaSourceVisible)
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

void DvProviderLinnCoUkProduct3C::SetSourceVisible(IInvocationResponse& aResponse, TUint aVersion, TUint aaSourceIndex, TBool aaSourceVisible)
{
    ASSERT(iCallbackSetSourceVisible != NULL);
    if (0 != iCallbackSetSourceVisible(iPtrSetSourceVisible, aVersion, aaSourceIndex, aaSourceVisible)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}



THandle DvProviderLinnCoUkProduct3Create(DvDeviceC aDevice)
{
	return new DvProviderLinnCoUkProduct3C(*(DviDeviceC::DeviceFromHandle(aDevice)));
}

void DvProviderLinnCoUkProduct3Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider);
}

void DvProviderLinnCoUkProduct3EnableActionType(THandle aProvider, CallbackProduct3Type aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->EnableActionType(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct3EnableActionModel(THandle aProvider, CallbackProduct3Model aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->EnableActionModel(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct3EnableActionName(THandle aProvider, CallbackProduct3Name aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->EnableActionName(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct3EnableActionSetName(THandle aProvider, CallbackProduct3SetName aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->EnableActionSetName(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct3EnableActionRoom(THandle aProvider, CallbackProduct3Room aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->EnableActionRoom(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct3EnableActionSetRoom(THandle aProvider, CallbackProduct3SetRoom aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->EnableActionSetRoom(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct3EnableActionStandby(THandle aProvider, CallbackProduct3Standby aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->EnableActionStandby(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct3EnableActionSetStandby(THandle aProvider, CallbackProduct3SetStandby aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->EnableActionSetStandby(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct3EnableActionSourceCount(THandle aProvider, CallbackProduct3SourceCount aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->EnableActionSourceCount(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct3EnableActionSourceXml(THandle aProvider, CallbackProduct3SourceXml aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->EnableActionSourceXml(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct3EnableActionSourceIndex(THandle aProvider, CallbackProduct3SourceIndex aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->EnableActionSourceIndex(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct3EnableActionSetSourceIndex(THandle aProvider, CallbackProduct3SetSourceIndex aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->EnableActionSetSourceIndex(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct3EnableActionSetSourceIndexByName(THandle aProvider, CallbackProduct3SetSourceIndexByName aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->EnableActionSetSourceIndexByName(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct3EnableActionSetStartupSourceIndexByName(THandle aProvider, CallbackProduct3SetStartupSourceIndexByName aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->EnableActionSetStartupSourceIndexByName(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct3EnableActionStartupSourceIndex(THandle aProvider, CallbackProduct3StartupSourceIndex aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->EnableActionStartupSourceIndex(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct3EnableActionSetStartupSourceIndex(THandle aProvider, CallbackProduct3SetStartupSourceIndex aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->EnableActionSetStartupSourceIndex(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct3EnableActionStartupSourceEnabled(THandle aProvider, CallbackProduct3StartupSourceEnabled aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->EnableActionStartupSourceEnabled(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct3EnableActionSetStartupSourceEnabled(THandle aProvider, CallbackProduct3SetStartupSourceEnabled aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->EnableActionSetStartupSourceEnabled(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct3EnableActionSourceSystemName(THandle aProvider, CallbackProduct3SourceSystemName aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->EnableActionSourceSystemName(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct3EnableActionSourceName(THandle aProvider, CallbackProduct3SourceName aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->EnableActionSourceName(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct3EnableActionSetSourceName(THandle aProvider, CallbackProduct3SetSourceName aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->EnableActionSetSourceName(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct3EnableActionSourceType(THandle aProvider, CallbackProduct3SourceType aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->EnableActionSourceType(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct3EnableActionSourceVisible(THandle aProvider, CallbackProduct3SourceVisible aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->EnableActionSourceVisible(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct3EnableActionSetSourceVisible(THandle aProvider, CallbackProduct3SetSourceVisible aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->EnableActionSetSourceVisible(aCallback, aPtr);
}

int32_t DvProviderLinnCoUkProduct3SetPropertyProductType(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->SetPropertyProductType(buf)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkProduct3GetPropertyProductType(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->GetPropertyProductType(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvProviderLinnCoUkProduct3SetPropertyProductModel(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->SetPropertyProductModel(buf)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkProduct3GetPropertyProductModel(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->GetPropertyProductModel(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvProviderLinnCoUkProduct3SetPropertyProductName(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->SetPropertyProductName(buf)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkProduct3GetPropertyProductName(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->GetPropertyProductName(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvProviderLinnCoUkProduct3SetPropertyProductRoom(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->SetPropertyProductRoom(buf)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkProduct3GetPropertyProductRoom(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->GetPropertyProductRoom(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvProviderLinnCoUkProduct3SetPropertyProductStandby(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->SetPropertyProductStandby((aValue!=0))? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkProduct3GetPropertyProductStandby(THandle aProvider, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->GetPropertyProductStandby(val);
    *aValue = (val? 1 : 0);
}

int32_t DvProviderLinnCoUkProduct3SetPropertyProductSourceIndex(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->SetPropertyProductSourceIndex(aValue)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkProduct3GetPropertyProductSourceIndex(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->GetPropertyProductSourceIndex(val);
    *aValue = val;
}

int32_t DvProviderLinnCoUkProduct3SetPropertyProductSourceCount(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->SetPropertyProductSourceCount(aValue)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkProduct3GetPropertyProductSourceCount(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->GetPropertyProductSourceCount(val);
    *aValue = val;
}

int32_t DvProviderLinnCoUkProduct3SetPropertyProductSourceXml(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->SetPropertyProductSourceXml(buf)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkProduct3GetPropertyProductSourceXml(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->GetPropertyProductSourceXml(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvProviderLinnCoUkProduct3SetPropertyStartupSourceIndex(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->SetPropertyStartupSourceIndex(aValue)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkProduct3GetPropertyStartupSourceIndex(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->GetPropertyStartupSourceIndex(val);
    *aValue = val;
}

int32_t DvProviderLinnCoUkProduct3SetPropertyStartupSourceEnabled(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->SetPropertyStartupSourceEnabled((aValue!=0))? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkProduct3GetPropertyStartupSourceEnabled(THandle aProvider, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->GetPropertyStartupSourceEnabled(val);
    *aValue = (val? 1 : 0);
}

int32_t DvProviderLinnCoUkProduct3SetPropertyProductAnySourceName(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->SetPropertyProductAnySourceName(aValue)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkProduct3GetPropertyProductAnySourceName(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->GetPropertyProductAnySourceName(val);
    *aValue = val;
}

int32_t DvProviderLinnCoUkProduct3SetPropertyProductAnySourceVisible(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->SetPropertyProductAnySourceVisible(aValue)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkProduct3GetPropertyProductAnySourceVisible(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->GetPropertyProductAnySourceVisible(val);
    *aValue = val;
}

int32_t DvProviderLinnCoUkProduct3SetPropertyProductAnySourceType(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->SetPropertyProductAnySourceType(aValue)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkProduct3GetPropertyProductAnySourceType(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->GetPropertyProductAnySourceType(val);
    *aValue = val;
}

