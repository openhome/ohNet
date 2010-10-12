#include <C/DvLinnCoUkVolkano1.h>
#include <Core/DvLinnCoUkVolkano1.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvServiceLinnCoUkVolkano1C : public DvServiceLinnCoUkVolkano1
{
public:
    DvServiceLinnCoUkVolkano1C(DvDevice& aDevice);
    void EnableActionReboot(CallbackVolkano1Reboot aCallback, void* aPtr);
    void EnableActionBootMode(CallbackVolkano1BootMode aCallback, void* aPtr);
    void EnableActionSetBootMode(CallbackVolkano1SetBootMode aCallback, void* aPtr);
    void EnableActionBspType(CallbackVolkano1BspType aCallback, void* aPtr);
    void EnableActionUglyName(CallbackVolkano1UglyName aCallback, void* aPtr);
    void EnableActionMacAddress(CallbackVolkano1MacAddress aCallback, void* aPtr);
    void EnableActionProductId(CallbackVolkano1ProductId aCallback, void* aPtr);
    void EnableActionBoardId(CallbackVolkano1BoardId aCallback, void* aPtr);
    void EnableActionBoardType(CallbackVolkano1BoardType aCallback, void* aPtr);
    void EnableActionMaxBoards(CallbackVolkano1MaxBoards aCallback, void* aPtr);
    void EnableActionSoftwareVersion(CallbackVolkano1SoftwareVersion aCallback, void* aPtr);
private:
    void Reboot(IInvocationResponse& aResponse, TUint aVersion);
    void BootMode(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaMode);
    void SetBootMode(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaMode);
    void BspType(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaBspType);
    void UglyName(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaUglyName);
    void MacAddress(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaMacAddress);
    void ProductId(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaProductNumber);
    void BoardId(IInvocationResponse& aResponse, TUint aVersion, TUint aaIndex, IInvocationResponseString& aaBoardNumber);
    void BoardType(IInvocationResponse& aResponse, TUint aVersion, TUint aaIndex, IInvocationResponseString& aaBoardNumber);
    void MaxBoards(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaMaxBoards);
    void SoftwareVersion(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaSoftwareVersion);
private:
    CallbackVolkano1Reboot iCallbackReboot;
    void* iPtrReboot;
    CallbackVolkano1BootMode iCallbackBootMode;
    void* iPtrBootMode;
    CallbackVolkano1SetBootMode iCallbackSetBootMode;
    void* iPtrSetBootMode;
    CallbackVolkano1BspType iCallbackBspType;
    void* iPtrBspType;
    CallbackVolkano1UglyName iCallbackUglyName;
    void* iPtrUglyName;
    CallbackVolkano1MacAddress iCallbackMacAddress;
    void* iPtrMacAddress;
    CallbackVolkano1ProductId iCallbackProductId;
    void* iPtrProductId;
    CallbackVolkano1BoardId iCallbackBoardId;
    void* iPtrBoardId;
    CallbackVolkano1BoardType iCallbackBoardType;
    void* iPtrBoardType;
    CallbackVolkano1MaxBoards iCallbackMaxBoards;
    void* iPtrMaxBoards;
    CallbackVolkano1SoftwareVersion iCallbackSoftwareVersion;
    void* iPtrSoftwareVersion;
};

DvServiceLinnCoUkVolkano1C::DvServiceLinnCoUkVolkano1C(DvDevice& aDevice)
    : DvServiceLinnCoUkVolkano1(aDevice)
{
}

void DvServiceLinnCoUkVolkano1C::EnableActionReboot(CallbackVolkano1Reboot aCallback, void* aPtr)
{
    iCallbackReboot = aCallback;
    iPtrReboot = aPtr;
    DvServiceLinnCoUkVolkano1::EnableActionReboot();
}

void DvServiceLinnCoUkVolkano1C::EnableActionBootMode(CallbackVolkano1BootMode aCallback, void* aPtr)
{
    iCallbackBootMode = aCallback;
    iPtrBootMode = aPtr;
    DvServiceLinnCoUkVolkano1::EnableActionBootMode();
}

void DvServiceLinnCoUkVolkano1C::EnableActionSetBootMode(CallbackVolkano1SetBootMode aCallback, void* aPtr)
{
    iCallbackSetBootMode = aCallback;
    iPtrSetBootMode = aPtr;
    DvServiceLinnCoUkVolkano1::EnableActionSetBootMode();
}

void DvServiceLinnCoUkVolkano1C::EnableActionBspType(CallbackVolkano1BspType aCallback, void* aPtr)
{
    iCallbackBspType = aCallback;
    iPtrBspType = aPtr;
    DvServiceLinnCoUkVolkano1::EnableActionBspType();
}

void DvServiceLinnCoUkVolkano1C::EnableActionUglyName(CallbackVolkano1UglyName aCallback, void* aPtr)
{
    iCallbackUglyName = aCallback;
    iPtrUglyName = aPtr;
    DvServiceLinnCoUkVolkano1::EnableActionUglyName();
}

void DvServiceLinnCoUkVolkano1C::EnableActionMacAddress(CallbackVolkano1MacAddress aCallback, void* aPtr)
{
    iCallbackMacAddress = aCallback;
    iPtrMacAddress = aPtr;
    DvServiceLinnCoUkVolkano1::EnableActionMacAddress();
}

void DvServiceLinnCoUkVolkano1C::EnableActionProductId(CallbackVolkano1ProductId aCallback, void* aPtr)
{
    iCallbackProductId = aCallback;
    iPtrProductId = aPtr;
    DvServiceLinnCoUkVolkano1::EnableActionProductId();
}

void DvServiceLinnCoUkVolkano1C::EnableActionBoardId(CallbackVolkano1BoardId aCallback, void* aPtr)
{
    iCallbackBoardId = aCallback;
    iPtrBoardId = aPtr;
    DvServiceLinnCoUkVolkano1::EnableActionBoardId();
}

void DvServiceLinnCoUkVolkano1C::EnableActionBoardType(CallbackVolkano1BoardType aCallback, void* aPtr)
{
    iCallbackBoardType = aCallback;
    iPtrBoardType = aPtr;
    DvServiceLinnCoUkVolkano1::EnableActionBoardType();
}

void DvServiceLinnCoUkVolkano1C::EnableActionMaxBoards(CallbackVolkano1MaxBoards aCallback, void* aPtr)
{
    iCallbackMaxBoards = aCallback;
    iPtrMaxBoards = aPtr;
    DvServiceLinnCoUkVolkano1::EnableActionMaxBoards();
}

void DvServiceLinnCoUkVolkano1C::EnableActionSoftwareVersion(CallbackVolkano1SoftwareVersion aCallback, void* aPtr)
{
    iCallbackSoftwareVersion = aCallback;
    iPtrSoftwareVersion = aPtr;
    DvServiceLinnCoUkVolkano1::EnableActionSoftwareVersion();
}

void DvServiceLinnCoUkVolkano1C::Reboot(IInvocationResponse& aResponse, TUint aVersion)
{
    ASSERT(iCallbackReboot != NULL);
    if (0 != iCallbackReboot(iPtrReboot, aVersion)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkVolkano1C::BootMode(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaMode)
{
    char* aMode;
    ASSERT(iCallbackBootMode != NULL);
    if (0 != iCallbackBootMode(iPtrBootMode, aVersion, &aMode)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufaMode((const TChar*)aMode);
    ZappFreeExternal(aMode);
    aaMode.Write(bufaMode);
    aaMode.WriteFlush();
    aResponse.End();
}

void DvServiceLinnCoUkVolkano1C::SetBootMode(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaMode)
{
    ASSERT(iCallbackSetBootMode != NULL);
    if (0 != iCallbackSetBootMode(iPtrSetBootMode, aVersion, (const char*)aaMode.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkVolkano1C::BspType(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaBspType)
{
    char* aBspType;
    ASSERT(iCallbackBspType != NULL);
    if (0 != iCallbackBspType(iPtrBspType, aVersion, &aBspType)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufaBspType((const TChar*)aBspType);
    ZappFreeExternal(aBspType);
    aaBspType.Write(bufaBspType);
    aaBspType.WriteFlush();
    aResponse.End();
}

void DvServiceLinnCoUkVolkano1C::UglyName(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaUglyName)
{
    char* aUglyName;
    ASSERT(iCallbackUglyName != NULL);
    if (0 != iCallbackUglyName(iPtrUglyName, aVersion, &aUglyName)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufaUglyName((const TChar*)aUglyName);
    ZappFreeExternal(aUglyName);
    aaUglyName.Write(bufaUglyName);
    aaUglyName.WriteFlush();
    aResponse.End();
}

void DvServiceLinnCoUkVolkano1C::MacAddress(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaMacAddress)
{
    char* aMacAddress;
    ASSERT(iCallbackMacAddress != NULL);
    if (0 != iCallbackMacAddress(iPtrMacAddress, aVersion, &aMacAddress)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufaMacAddress((const TChar*)aMacAddress);
    ZappFreeExternal(aMacAddress);
    aaMacAddress.Write(bufaMacAddress);
    aaMacAddress.WriteFlush();
    aResponse.End();
}

void DvServiceLinnCoUkVolkano1C::ProductId(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaProductNumber)
{
    char* aProductNumber;
    ASSERT(iCallbackProductId != NULL);
    if (0 != iCallbackProductId(iPtrProductId, aVersion, &aProductNumber)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufaProductNumber((const TChar*)aProductNumber);
    ZappFreeExternal(aProductNumber);
    aaProductNumber.Write(bufaProductNumber);
    aaProductNumber.WriteFlush();
    aResponse.End();
}

void DvServiceLinnCoUkVolkano1C::BoardId(IInvocationResponse& aResponse, TUint aVersion, TUint aaIndex, IInvocationResponseString& aaBoardNumber)
{
    char* aBoardNumber;
    ASSERT(iCallbackBoardId != NULL);
    if (0 != iCallbackBoardId(iPtrBoardId, aVersion, aaIndex, &aBoardNumber)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufaBoardNumber((const TChar*)aBoardNumber);
    ZappFreeExternal(aBoardNumber);
    aaBoardNumber.Write(bufaBoardNumber);
    aaBoardNumber.WriteFlush();
    aResponse.End();
}

void DvServiceLinnCoUkVolkano1C::BoardType(IInvocationResponse& aResponse, TUint aVersion, TUint aaIndex, IInvocationResponseString& aaBoardNumber)
{
    char* aBoardNumber;
    ASSERT(iCallbackBoardType != NULL);
    if (0 != iCallbackBoardType(iPtrBoardType, aVersion, aaIndex, &aBoardNumber)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufaBoardNumber((const TChar*)aBoardNumber);
    ZappFreeExternal(aBoardNumber);
    aaBoardNumber.Write(bufaBoardNumber);
    aaBoardNumber.WriteFlush();
    aResponse.End();
}

void DvServiceLinnCoUkVolkano1C::MaxBoards(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaMaxBoards)
{
    uint32_t aMaxBoards;
    ASSERT(iCallbackMaxBoards != NULL);
    if (0 != iCallbackMaxBoards(iPtrMaxBoards, aVersion, &aMaxBoards)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aaMaxBoards.Write(aMaxBoards);
    aResponse.End();
}

void DvServiceLinnCoUkVolkano1C::SoftwareVersion(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaSoftwareVersion)
{
    char* aSoftwareVersion;
    ASSERT(iCallbackSoftwareVersion != NULL);
    if (0 != iCallbackSoftwareVersion(iPtrSoftwareVersion, aVersion, &aSoftwareVersion)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufaSoftwareVersion((const TChar*)aSoftwareVersion);
    ZappFreeExternal(aSoftwareVersion);
    aaSoftwareVersion.Write(bufaSoftwareVersion);
    aaSoftwareVersion.WriteFlush();
    aResponse.End();
}



THandle DvServiceLinnCoUkVolkano1Create(DvDeviceC aDevice)
{
    return (THandle)new DvServiceLinnCoUkVolkano1C(*(DviDeviceC::DeviceFromHandle(aDevice)));
}

void DvServiceLinnCoUkVolkano1Destroy(THandle aService)
{
    delete reinterpret_cast<DvServiceLinnCoUkVolkano1C*>(aService);
}

void DvServiceLinnCoUkVolkano1EnableActionReboot(THandle aService, CallbackVolkano1Reboot aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkVolkano1C*>(aService)->EnableActionReboot(aCallback, aPtr);
}

void DvServiceLinnCoUkVolkano1EnableActionBootMode(THandle aService, CallbackVolkano1BootMode aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkVolkano1C*>(aService)->EnableActionBootMode(aCallback, aPtr);
}

void DvServiceLinnCoUkVolkano1EnableActionSetBootMode(THandle aService, CallbackVolkano1SetBootMode aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkVolkano1C*>(aService)->EnableActionSetBootMode(aCallback, aPtr);
}

void DvServiceLinnCoUkVolkano1EnableActionBspType(THandle aService, CallbackVolkano1BspType aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkVolkano1C*>(aService)->EnableActionBspType(aCallback, aPtr);
}

void DvServiceLinnCoUkVolkano1EnableActionUglyName(THandle aService, CallbackVolkano1UglyName aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkVolkano1C*>(aService)->EnableActionUglyName(aCallback, aPtr);
}

void DvServiceLinnCoUkVolkano1EnableActionMacAddress(THandle aService, CallbackVolkano1MacAddress aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkVolkano1C*>(aService)->EnableActionMacAddress(aCallback, aPtr);
}

void DvServiceLinnCoUkVolkano1EnableActionProductId(THandle aService, CallbackVolkano1ProductId aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkVolkano1C*>(aService)->EnableActionProductId(aCallback, aPtr);
}

void DvServiceLinnCoUkVolkano1EnableActionBoardId(THandle aService, CallbackVolkano1BoardId aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkVolkano1C*>(aService)->EnableActionBoardId(aCallback, aPtr);
}

void DvServiceLinnCoUkVolkano1EnableActionBoardType(THandle aService, CallbackVolkano1BoardType aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkVolkano1C*>(aService)->EnableActionBoardType(aCallback, aPtr);
}

void DvServiceLinnCoUkVolkano1EnableActionMaxBoards(THandle aService, CallbackVolkano1MaxBoards aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkVolkano1C*>(aService)->EnableActionMaxBoards(aCallback, aPtr);
}

void DvServiceLinnCoUkVolkano1EnableActionSoftwareVersion(THandle aService, CallbackVolkano1SoftwareVersion aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkVolkano1C*>(aService)->EnableActionSoftwareVersion(aCallback, aPtr);
}

