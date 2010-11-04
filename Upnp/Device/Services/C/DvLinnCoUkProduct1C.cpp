#include <C/DvLinnCoUkProduct1.h>
#include <Core/DvLinnCoUkProduct1.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvProviderLinnCoUkProduct1C : public DvProviderLinnCoUkProduct1
{
public:
    DvProviderLinnCoUkProduct1C(DvDevice& aDevice);
    void EnableActionRoom(CallbackProduct1Room aCallback, void* aPtr);
    void EnableActionSetRoom(CallbackProduct1SetRoom aCallback, void* aPtr);
    void EnableActionStandby(CallbackProduct1Standby aCallback, void* aPtr);
    void EnableActionSetStandby(CallbackProduct1SetStandby aCallback, void* aPtr);
private:
    void Room(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaRoom);
    void SetRoom(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaRoom);
    void Standby(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaStandby);
    void SetStandby(IInvocationResponse& aResponse, TUint aVersion, TBool aaStandby);
private:
    CallbackProduct1Room iCallbackRoom;
    void* iPtrRoom;
    CallbackProduct1SetRoom iCallbackSetRoom;
    void* iPtrSetRoom;
    CallbackProduct1Standby iCallbackStandby;
    void* iPtrStandby;
    CallbackProduct1SetStandby iCallbackSetStandby;
    void* iPtrSetStandby;
};

DvProviderLinnCoUkProduct1C::DvProviderLinnCoUkProduct1C(DvDevice& aDevice)
    : DvProviderLinnCoUkProduct1(aDevice)
{
}

void DvProviderLinnCoUkProduct1C::EnableActionRoom(CallbackProduct1Room aCallback, void* aPtr)
{
    iCallbackRoom = aCallback;
    iPtrRoom = aPtr;
    DvProviderLinnCoUkProduct1::EnableActionRoom();
}

void DvProviderLinnCoUkProduct1C::EnableActionSetRoom(CallbackProduct1SetRoom aCallback, void* aPtr)
{
    iCallbackSetRoom = aCallback;
    iPtrSetRoom = aPtr;
    DvProviderLinnCoUkProduct1::EnableActionSetRoom();
}

void DvProviderLinnCoUkProduct1C::EnableActionStandby(CallbackProduct1Standby aCallback, void* aPtr)
{
    iCallbackStandby = aCallback;
    iPtrStandby = aPtr;
    DvProviderLinnCoUkProduct1::EnableActionStandby();
}

void DvProviderLinnCoUkProduct1C::EnableActionSetStandby(CallbackProduct1SetStandby aCallback, void* aPtr)
{
    iCallbackSetStandby = aCallback;
    iPtrSetStandby = aPtr;
    DvProviderLinnCoUkProduct1::EnableActionSetStandby();
}

void DvProviderLinnCoUkProduct1C::Room(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaRoom)
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

void DvProviderLinnCoUkProduct1C::SetRoom(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaRoom)
{
    ASSERT(iCallbackSetRoom != NULL);
    if (0 != iCallbackSetRoom(iPtrSetRoom, aVersion, (const char*)aaRoom.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkProduct1C::Standby(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaStandby)
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

void DvProviderLinnCoUkProduct1C::SetStandby(IInvocationResponse& aResponse, TUint aVersion, TBool aaStandby)
{
    ASSERT(iCallbackSetStandby != NULL);
    if (0 != iCallbackSetStandby(iPtrSetStandby, aVersion, aaStandby)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}



THandle DvProviderLinnCoUkProduct1Create(DvDeviceC aDevice)
{
	return new DvProviderLinnCoUkProduct1C(*(DviDeviceC::DeviceFromHandle(aDevice)));
}

void DvProviderLinnCoUkProduct1Destroy(THandle aService)
{
    delete reinterpret_cast<DvProviderLinnCoUkProduct1C*>(aService);
}

void DvProviderLinnCoUkProduct1EnableActionRoom(THandle aService, CallbackProduct1Room aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct1C*>(aService)->EnableActionRoom(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct1EnableActionSetRoom(THandle aService, CallbackProduct1SetRoom aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct1C*>(aService)->EnableActionSetRoom(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct1EnableActionStandby(THandle aService, CallbackProduct1Standby aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct1C*>(aService)->EnableActionStandby(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct1EnableActionSetStandby(THandle aService, CallbackProduct1SetStandby aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct1C*>(aService)->EnableActionSetStandby(aCallback, aPtr);
}

int32_t DvProviderLinnCoUkProduct1SetPropertyRoom(THandle aService, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkProduct1C*>(aService)->SetPropertyRoom(buf)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkProduct1GetPropertyRoom(THandle aService, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderLinnCoUkProduct1C*>(aService)->GetPropertyRoom(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvProviderLinnCoUkProduct1SetPropertyStandby(THandle aService, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkProduct1C*>(aService)->SetPropertyStandby((aValue!=0))? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkProduct1GetPropertyStandby(THandle aService, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvProviderLinnCoUkProduct1C*>(aService)->GetPropertyStandby(val);
    *aValue = (val? 1 : 0);
}

