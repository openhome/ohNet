#include <C/DvLinnCoUkProduct1.h>
#include <Core/DvLinnCoUkProduct1.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvServiceLinnCoUkProduct1C : public DvServiceLinnCoUkProduct1
{
public:
    DvServiceLinnCoUkProduct1C(DvDevice& aDevice);
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

DvServiceLinnCoUkProduct1C::DvServiceLinnCoUkProduct1C(DvDevice& aDevice)
    : DvServiceLinnCoUkProduct1(aDevice)
{
}

void DvServiceLinnCoUkProduct1C::EnableActionRoom(CallbackProduct1Room aCallback, void* aPtr)
{
    iCallbackRoom = aCallback;
    iPtrRoom = aPtr;
    DvServiceLinnCoUkProduct1::EnableActionRoom();
}

void DvServiceLinnCoUkProduct1C::EnableActionSetRoom(CallbackProduct1SetRoom aCallback, void* aPtr)
{
    iCallbackSetRoom = aCallback;
    iPtrSetRoom = aPtr;
    DvServiceLinnCoUkProduct1::EnableActionSetRoom();
}

void DvServiceLinnCoUkProduct1C::EnableActionStandby(CallbackProduct1Standby aCallback, void* aPtr)
{
    iCallbackStandby = aCallback;
    iPtrStandby = aPtr;
    DvServiceLinnCoUkProduct1::EnableActionStandby();
}

void DvServiceLinnCoUkProduct1C::EnableActionSetStandby(CallbackProduct1SetStandby aCallback, void* aPtr)
{
    iCallbackSetStandby = aCallback;
    iPtrSetStandby = aPtr;
    DvServiceLinnCoUkProduct1::EnableActionSetStandby();
}

void DvServiceLinnCoUkProduct1C::Room(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaRoom)
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

void DvServiceLinnCoUkProduct1C::SetRoom(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaRoom)
{
    ASSERT(iCallbackSetRoom != NULL);
    if (0 != iCallbackSetRoom(iPtrSetRoom, aVersion, (const char*)aaRoom.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkProduct1C::Standby(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaStandby)
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

void DvServiceLinnCoUkProduct1C::SetStandby(IInvocationResponse& aResponse, TUint aVersion, TBool aaStandby)
{
    ASSERT(iCallbackSetStandby != NULL);
    if (0 != iCallbackSetStandby(iPtrSetStandby, aVersion, aaStandby)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}



THandle DvServiceLinnCoUkProduct1Create(DvDeviceC aDevice)
{
    return (THandle)new DvServiceLinnCoUkProduct1C(*(DviDeviceC::DeviceFromHandle(aDevice)));
}

void DvServiceLinnCoUkProduct1Destroy(THandle aService)
{
    delete reinterpret_cast<DvServiceLinnCoUkProduct1C*>(aService);
}

void DvServiceLinnCoUkProduct1EnableActionRoom(THandle aService, CallbackProduct1Room aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkProduct1C*>(aService)->EnableActionRoom(aCallback, aPtr);
}

void DvServiceLinnCoUkProduct1EnableActionSetRoom(THandle aService, CallbackProduct1SetRoom aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkProduct1C*>(aService)->EnableActionSetRoom(aCallback, aPtr);
}

void DvServiceLinnCoUkProduct1EnableActionStandby(THandle aService, CallbackProduct1Standby aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkProduct1C*>(aService)->EnableActionStandby(aCallback, aPtr);
}

void DvServiceLinnCoUkProduct1EnableActionSetStandby(THandle aService, CallbackProduct1SetStandby aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkProduct1C*>(aService)->EnableActionSetStandby(aCallback, aPtr);
}

int32_t DvServiceLinnCoUkProduct1SetPropertyRoom(THandle aService, const char* aValue)
{
    Brhz buf(aValue);
    reinterpret_cast<DvServiceLinnCoUkProduct1C*>(aService)->SetPropertyRoom(buf);
    return 0;
}

void DvServiceLinnCoUkProduct1GetPropertyRoom(THandle aService, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvServiceLinnCoUkProduct1C*>(aService)->GetPropertyRoom(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvServiceLinnCoUkProduct1SetPropertyStandby(THandle aService, uint32_t aValue)
{
    reinterpret_cast<DvServiceLinnCoUkProduct1C*>(aService)->SetPropertyStandby((aValue!=0));
    return 0;
}

void DvServiceLinnCoUkProduct1GetPropertyStandby(THandle aService, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvServiceLinnCoUkProduct1C*>(aService)->GetPropertyStandby(val);
    *aValue = (val? 1 : 0);
}

