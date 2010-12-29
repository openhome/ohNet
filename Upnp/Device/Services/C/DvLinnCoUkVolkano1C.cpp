#include "DvLinnCoUkVolkano1.h"
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <DvProvider.h>
#include <C/Zapp.h>
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace Zapp;

class DvProviderLinnCoUkVolkano1C : public DvProvider
{
public:
    DvProviderLinnCoUkVolkano1C(DvDeviceC aDevice);
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
    void DoReboot(IDviInvocation& aInvocation, TUint aVersion);
    void DoBootMode(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetBootMode(IDviInvocation& aInvocation, TUint aVersion);
    void DoBspType(IDviInvocation& aInvocation, TUint aVersion);
    void DoUglyName(IDviInvocation& aInvocation, TUint aVersion);
    void DoMacAddress(IDviInvocation& aInvocation, TUint aVersion);
    void DoProductId(IDviInvocation& aInvocation, TUint aVersion);
    void DoBoardId(IDviInvocation& aInvocation, TUint aVersion);
    void DoBoardType(IDviInvocation& aInvocation, TUint aVersion);
    void DoMaxBoards(IDviInvocation& aInvocation, TUint aVersion);
    void DoSoftwareVersion(IDviInvocation& aInvocation, TUint aVersion);
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

DvProviderLinnCoUkVolkano1C::DvProviderLinnCoUkVolkano1C(DvDeviceC aDevice)
    : DvProvider(DviDeviceC::DeviceFromHandle(aDevice)->Device(), "linn.co.uk", "Volkano", 1)
{
    
}

void DvProviderLinnCoUkVolkano1C::EnableActionReboot(CallbackVolkano1Reboot aCallback, void* aPtr)
{
    iCallbackReboot = aCallback;
    iPtrReboot = aPtr;
    Zapp::Action* action = new Zapp::Action("Reboot");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkVolkano1C::DoReboot);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkVolkano1C::EnableActionBootMode(CallbackVolkano1BootMode aCallback, void* aPtr)
{
    iCallbackBootMode = aCallback;
    iPtrBootMode = aPtr;
    Zapp::Action* action = new Zapp::Action("BootMode");
    TChar** allowedValues;
    TUint index;
    index = 0;
    allowedValues = new TChar*[3];
    allowedValues[index++] = (TChar*)"Main";
    allowedValues[index++] = (TChar*)"Fallback";
    allowedValues[index++] = (TChar*)"Ram";
    action->AddOutputParameter(new ParameterString("aMode", allowedValues, 3));
    delete[] allowedValues;
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkVolkano1C::DoBootMode);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkVolkano1C::EnableActionSetBootMode(CallbackVolkano1SetBootMode aCallback, void* aPtr)
{
    iCallbackSetBootMode = aCallback;
    iPtrSetBootMode = aPtr;
    Zapp::Action* action = new Zapp::Action("SetBootMode");
    TChar** allowedValues;
    TUint index;
    index = 0;
    allowedValues = new TChar*[2];
    allowedValues[index++] = (TChar*)"Main";
    allowedValues[index++] = (TChar*)"Fallback";
    action->AddInputParameter(new ParameterString("aMode", allowedValues, 2));
    delete[] allowedValues;
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkVolkano1C::DoSetBootMode);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkVolkano1C::EnableActionBspType(CallbackVolkano1BspType aCallback, void* aPtr)
{
    iCallbackBspType = aCallback;
    iPtrBspType = aPtr;
    Zapp::Action* action = new Zapp::Action("BspType");
    action->AddOutputParameter(new ParameterString("aBspType"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkVolkano1C::DoBspType);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkVolkano1C::EnableActionUglyName(CallbackVolkano1UglyName aCallback, void* aPtr)
{
    iCallbackUglyName = aCallback;
    iPtrUglyName = aPtr;
    Zapp::Action* action = new Zapp::Action("UglyName");
    action->AddOutputParameter(new ParameterString("aUglyName"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkVolkano1C::DoUglyName);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkVolkano1C::EnableActionMacAddress(CallbackVolkano1MacAddress aCallback, void* aPtr)
{
    iCallbackMacAddress = aCallback;
    iPtrMacAddress = aPtr;
    Zapp::Action* action = new Zapp::Action("MacAddress");
    action->AddOutputParameter(new ParameterString("aMacAddress"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkVolkano1C::DoMacAddress);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkVolkano1C::EnableActionProductId(CallbackVolkano1ProductId aCallback, void* aPtr)
{
    iCallbackProductId = aCallback;
    iPtrProductId = aPtr;
    Zapp::Action* action = new Zapp::Action("ProductId");
    action->AddOutputParameter(new ParameterString("aProductNumber"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkVolkano1C::DoProductId);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkVolkano1C::EnableActionBoardId(CallbackVolkano1BoardId aCallback, void* aPtr)
{
    iCallbackBoardId = aCallback;
    iPtrBoardId = aPtr;
    Zapp::Action* action = new Zapp::Action("BoardId");
    action->AddInputParameter(new ParameterUint("aIndex"));
    action->AddOutputParameter(new ParameterString("aBoardNumber"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkVolkano1C::DoBoardId);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkVolkano1C::EnableActionBoardType(CallbackVolkano1BoardType aCallback, void* aPtr)
{
    iCallbackBoardType = aCallback;
    iPtrBoardType = aPtr;
    Zapp::Action* action = new Zapp::Action("BoardType");
    action->AddInputParameter(new ParameterUint("aIndex"));
    action->AddOutputParameter(new ParameterString("aBoardNumber"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkVolkano1C::DoBoardType);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkVolkano1C::EnableActionMaxBoards(CallbackVolkano1MaxBoards aCallback, void* aPtr)
{
    iCallbackMaxBoards = aCallback;
    iPtrMaxBoards = aPtr;
    Zapp::Action* action = new Zapp::Action("MaxBoards");
    action->AddOutputParameter(new ParameterUint("aMaxBoards"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkVolkano1C::DoMaxBoards);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkVolkano1C::EnableActionSoftwareVersion(CallbackVolkano1SoftwareVersion aCallback, void* aPtr)
{
    iCallbackSoftwareVersion = aCallback;
    iPtrSoftwareVersion = aPtr;
    Zapp::Action* action = new Zapp::Action("SoftwareVersion");
    action->AddOutputParameter(new ParameterString("aSoftwareVersion"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkVolkano1C::DoSoftwareVersion);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkVolkano1C::DoReboot(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackReboot != NULL);
    if (0 != iCallbackReboot(iPtrReboot, aVersion)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkVolkano1C::DoBootMode(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* aMode;
    ASSERT(iCallbackBootMode != NULL);
    if (0 != iCallbackBootMode(iPtrBootMode, aVersion, &aMode)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respaMode(aInvocation, "aMode");
    resp.Start();
    Brhz bufaMode((const TChar*)aMode);
    ZappFreeExternal(aMode);
    respaMode.Write(bufaMode);
    respaMode.WriteFlush();
    resp.End();
}

void DvProviderLinnCoUkVolkano1C::DoSetBootMode(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz aMode;
    aInvocation.InvocationReadString("aMode", aMode);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetBootMode != NULL);
    if (0 != iCallbackSetBootMode(iPtrSetBootMode, aVersion, (const char*)aMode.Ptr())) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkVolkano1C::DoBspType(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* aBspType;
    ASSERT(iCallbackBspType != NULL);
    if (0 != iCallbackBspType(iPtrBspType, aVersion, &aBspType)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respaBspType(aInvocation, "aBspType");
    resp.Start();
    Brhz bufaBspType((const TChar*)aBspType);
    ZappFreeExternal(aBspType);
    respaBspType.Write(bufaBspType);
    respaBspType.WriteFlush();
    resp.End();
}

void DvProviderLinnCoUkVolkano1C::DoUglyName(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* aUglyName;
    ASSERT(iCallbackUglyName != NULL);
    if (0 != iCallbackUglyName(iPtrUglyName, aVersion, &aUglyName)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respaUglyName(aInvocation, "aUglyName");
    resp.Start();
    Brhz bufaUglyName((const TChar*)aUglyName);
    ZappFreeExternal(aUglyName);
    respaUglyName.Write(bufaUglyName);
    respaUglyName.WriteFlush();
    resp.End();
}

void DvProviderLinnCoUkVolkano1C::DoMacAddress(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* aMacAddress;
    ASSERT(iCallbackMacAddress != NULL);
    if (0 != iCallbackMacAddress(iPtrMacAddress, aVersion, &aMacAddress)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respaMacAddress(aInvocation, "aMacAddress");
    resp.Start();
    Brhz bufaMacAddress((const TChar*)aMacAddress);
    ZappFreeExternal(aMacAddress);
    respaMacAddress.Write(bufaMacAddress);
    respaMacAddress.WriteFlush();
    resp.End();
}

void DvProviderLinnCoUkVolkano1C::DoProductId(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* aProductNumber;
    ASSERT(iCallbackProductId != NULL);
    if (0 != iCallbackProductId(iPtrProductId, aVersion, &aProductNumber)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respaProductNumber(aInvocation, "aProductNumber");
    resp.Start();
    Brhz bufaProductNumber((const TChar*)aProductNumber);
    ZappFreeExternal(aProductNumber);
    respaProductNumber.Write(bufaProductNumber);
    respaProductNumber.WriteFlush();
    resp.End();
}

void DvProviderLinnCoUkVolkano1C::DoBoardId(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aIndex = aInvocation.InvocationReadUint("aIndex");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* aBoardNumber;
    ASSERT(iCallbackBoardId != NULL);
    if (0 != iCallbackBoardId(iPtrBoardId, aVersion, aIndex, &aBoardNumber)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respaBoardNumber(aInvocation, "aBoardNumber");
    resp.Start();
    Brhz bufaBoardNumber((const TChar*)aBoardNumber);
    ZappFreeExternal(aBoardNumber);
    respaBoardNumber.Write(bufaBoardNumber);
    respaBoardNumber.WriteFlush();
    resp.End();
}

void DvProviderLinnCoUkVolkano1C::DoBoardType(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aIndex = aInvocation.InvocationReadUint("aIndex");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* aBoardNumber;
    ASSERT(iCallbackBoardType != NULL);
    if (0 != iCallbackBoardType(iPtrBoardType, aVersion, aIndex, &aBoardNumber)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respaBoardNumber(aInvocation, "aBoardNumber");
    resp.Start();
    Brhz bufaBoardNumber((const TChar*)aBoardNumber);
    ZappFreeExternal(aBoardNumber);
    respaBoardNumber.Write(bufaBoardNumber);
    respaBoardNumber.WriteFlush();
    resp.End();
}

void DvProviderLinnCoUkVolkano1C::DoMaxBoards(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t aMaxBoards;
    ASSERT(iCallbackMaxBoards != NULL);
    if (0 != iCallbackMaxBoards(iPtrMaxBoards, aVersion, &aMaxBoards)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respaMaxBoards(aInvocation, "aMaxBoards");
    resp.Start();
    respaMaxBoards.Write(aMaxBoards);
    resp.End();
}

void DvProviderLinnCoUkVolkano1C::DoSoftwareVersion(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* aSoftwareVersion;
    ASSERT(iCallbackSoftwareVersion != NULL);
    if (0 != iCallbackSoftwareVersion(iPtrSoftwareVersion, aVersion, &aSoftwareVersion)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respaSoftwareVersion(aInvocation, "aSoftwareVersion");
    resp.Start();
    Brhz bufaSoftwareVersion((const TChar*)aSoftwareVersion);
    ZappFreeExternal(aSoftwareVersion);
    respaSoftwareVersion.Write(bufaSoftwareVersion);
    respaSoftwareVersion.WriteFlush();
    resp.End();
}



THandle DvProviderLinnCoUkVolkano1Create(DvDeviceC aDevice)
{
	return new DvProviderLinnCoUkVolkano1C(aDevice);
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

