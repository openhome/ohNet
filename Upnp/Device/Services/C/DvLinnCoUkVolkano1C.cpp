#include <C/DvLinnCoUkVolkano1.h>
#include <Core/DvLinnCoUkVolkano1.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvProviderLinnCoUkVolkano1C : public DvProviderLinnCoUkVolkano1
{
public:
    DvProviderLinnCoUkVolkano1C(DvDevice& aDevice);
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

DvProviderLinnCoUkVolkano1C::DvProviderLinnCoUkVolkano1C(DvDevice& aDevice)
    : DvProviderLinnCoUkVolkano1(aDevice)
{
}

void DvProviderLinnCoUkVolkano1C::EnableActionReboot(CallbackVolkano1Reboot aCallback, void* aPtr)
{
    iCallbackReboot = aCallback;
    iPtrReboot = aPtr;
    DvProviderLinnCoUkVolkano1::EnableActionReboot();
}

void DvProviderLinnCoUkVolkano1C::EnableActionBootMode(CallbackVolkano1BootMode aCallback, void* aPtr)
{
    iCallbackBootMode = aCallback;
    iPtrBootMode = aPtr;
    DvProviderLinnCoUkVolkano1::EnableActionBootMode();
}

void DvProviderLinnCoUkVolkano1C::EnableActionSetBootMode(CallbackVolkano1SetBootMode aCallback, void* aPtr)
{
    iCallbackSetBootMode = aCallback;
    iPtrSetBootMode = aPtr;
    DvProviderLinnCoUkVolkano1::EnableActionSetBootMode();
}

void DvProviderLinnCoUkVolkano1C::EnableActionBspType(CallbackVolkano1BspType aCallback, void* aPtr)
{
    iCallbackBspType = aCallback;
    iPtrBspType = aPtr;
    DvProviderLinnCoUkVolkano1::EnableActionBspType();
}

void DvProviderLinnCoUkVolkano1C::EnableActionUglyName(CallbackVolkano1UglyName aCallback, void* aPtr)
{
    iCallbackUglyName = aCallback;
    iPtrUglyName = aPtr;
    DvProviderLinnCoUkVolkano1::EnableActionUglyName();
}

void DvProviderLinnCoUkVolkano1C::EnableActionMacAddress(CallbackVolkano1MacAddress aCallback, void* aPtr)
{
    iCallbackMacAddress = aCallback;
    iPtrMacAddress = aPtr;
    DvProviderLinnCoUkVolkano1::EnableActionMacAddress();
}

void DvProviderLinnCoUkVolkano1C::EnableActionProductId(CallbackVolkano1ProductId aCallback, void* aPtr)
{
    iCallbackProductId = aCallback;
    iPtrProductId = aPtr;
    DvProviderLinnCoUkVolkano1::EnableActionProductId();
}

void DvProviderLinnCoUkVolkano1C::EnableActionBoardId(CallbackVolkano1BoardId aCallback, void* aPtr)
{
    iCallbackBoardId = aCallback;
    iPtrBoardId = aPtr;
    DvProviderLinnCoUkVolkano1::EnableActionBoardId();
}

void DvProviderLinnCoUkVolkano1C::EnableActionBoardType(CallbackVolkano1BoardType aCallback, void* aPtr)
{
    iCallbackBoardType = aCallback;
    iPtrBoardType = aPtr;
    DvProviderLinnCoUkVolkano1::EnableActionBoardType();
}

void DvProviderLinnCoUkVolkano1C::EnableActionMaxBoards(CallbackVolkano1MaxBoards aCallback, void* aPtr)
{
    iCallbackMaxBoards = aCallback;
    iPtrMaxBoards = aPtr;
    DvProviderLinnCoUkVolkano1::EnableActionMaxBoards();
}

void DvProviderLinnCoUkVolkano1C::EnableActionSoftwareVersion(CallbackVolkano1SoftwareVersion aCallback, void* aPtr)
{
    iCallbackSoftwareVersion = aCallback;
    iPtrSoftwareVersion = aPtr;
    DvProviderLinnCoUkVolkano1::EnableActionSoftwareVersion();
}

void DvProviderLinnCoUkVolkano1C::Reboot(IInvocationResponse& aResponse, TUint aVersion)
{
    ASSERT(iCallbackReboot != NULL);
    if (0 != iCallbackReboot(iPtrReboot, aVersion)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkVolkano1C::BootMode(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaMode)
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

void DvProviderLinnCoUkVolkano1C::SetBootMode(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaMode)
{
    ASSERT(iCallbackSetBootMode != NULL);
    if (0 != iCallbackSetBootMode(iPtrSetBootMode, aVersion, (const char*)aaMode.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkVolkano1C::BspType(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaBspType)
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

void DvProviderLinnCoUkVolkano1C::UglyName(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaUglyName)
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

void DvProviderLinnCoUkVolkano1C::MacAddress(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaMacAddress)
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

void DvProviderLinnCoUkVolkano1C::ProductId(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaProductNumber)
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

void DvProviderLinnCoUkVolkano1C::BoardId(IInvocationResponse& aResponse, TUint aVersion, TUint aaIndex, IInvocationResponseString& aaBoardNumber)
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

void DvProviderLinnCoUkVolkano1C::BoardType(IInvocationResponse& aResponse, TUint aVersion, TUint aaIndex, IInvocationResponseString& aaBoardNumber)
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

void DvProviderLinnCoUkVolkano1C::MaxBoards(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaMaxBoards)
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

void DvProviderLinnCoUkVolkano1C::SoftwareVersion(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaSoftwareVersion)
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



THandle DvProviderLinnCoUkVolkano1Create(DvDeviceC aDevice)
{
	return new DvProviderLinnCoUkVolkano1C(*(DviDeviceC::DeviceFromHandle(aDevice)));
}

void DvProviderLinnCoUkVolkano1Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderLinnCoUkVolkano1C*>(aProvider);
}

void DvProviderLinnCoUkVolkano1EnableActionReboot(THandle aProvider, CallbackVolkano1Reboot aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkVolkano1C*>(aProvider)->EnableActionReboot(aCallback, aPtr);
}

void DvProviderLinnCoUkVolkano1EnableActionBootMode(THandle aProvider, CallbackVolkano1BootMode aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkVolkano1C*>(aProvider)->EnableActionBootMode(aCallback, aPtr);
}

void DvProviderLinnCoUkVolkano1EnableActionSetBootMode(THandle aProvider, CallbackVolkano1SetBootMode aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkVolkano1C*>(aProvider)->EnableActionSetBootMode(aCallback, aPtr);
}

void DvProviderLinnCoUkVolkano1EnableActionBspType(THandle aProvider, CallbackVolkano1BspType aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkVolkano1C*>(aProvider)->EnableActionBspType(aCallback, aPtr);
}

void DvProviderLinnCoUkVolkano1EnableActionUglyName(THandle aProvider, CallbackVolkano1UglyName aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkVolkano1C*>(aProvider)->EnableActionUglyName(aCallback, aPtr);
}

void DvProviderLinnCoUkVolkano1EnableActionMacAddress(THandle aProvider, CallbackVolkano1MacAddress aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkVolkano1C*>(aProvider)->EnableActionMacAddress(aCallback, aPtr);
}

void DvProviderLinnCoUkVolkano1EnableActionProductId(THandle aProvider, CallbackVolkano1ProductId aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkVolkano1C*>(aProvider)->EnableActionProductId(aCallback, aPtr);
}

void DvProviderLinnCoUkVolkano1EnableActionBoardId(THandle aProvider, CallbackVolkano1BoardId aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkVolkano1C*>(aProvider)->EnableActionBoardId(aCallback, aPtr);
}

void DvProviderLinnCoUkVolkano1EnableActionBoardType(THandle aProvider, CallbackVolkano1BoardType aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkVolkano1C*>(aProvider)->EnableActionBoardType(aCallback, aPtr);
}

void DvProviderLinnCoUkVolkano1EnableActionMaxBoards(THandle aProvider, CallbackVolkano1MaxBoards aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkVolkano1C*>(aProvider)->EnableActionMaxBoards(aCallback, aPtr);
}

void DvProviderLinnCoUkVolkano1EnableActionSoftwareVersion(THandle aProvider, CallbackVolkano1SoftwareVersion aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkVolkano1C*>(aProvider)->EnableActionSoftwareVersion(aCallback, aPtr);
}

