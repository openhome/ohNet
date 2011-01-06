#include "DvLinnCoUkVolkano1.h"
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace Zapp;

DvProviderLinnCoUkVolkano1::DvProviderLinnCoUkVolkano1(DvDevice& aDevice)
    : DvProvider(aDevice.Device(), "linn.co.uk", "Volkano", 1)
{
    
}

void DvProviderLinnCoUkVolkano1::EnableActionReboot()
{
    Zapp::Action* action = new Zapp::Action("Reboot");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkVolkano1::DoReboot);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkVolkano1::EnableActionBootMode()
{
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkVolkano1::DoBootMode);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkVolkano1::EnableActionSetBootMode()
{
    Zapp::Action* action = new Zapp::Action("SetBootMode");
    TChar** allowedValues;
    TUint index;
    index = 0;
    allowedValues = new TChar*[2];
    allowedValues[index++] = (TChar*)"Main";
    allowedValues[index++] = (TChar*)"Fallback";
    action->AddInputParameter(new ParameterString("aMode", allowedValues, 2));
    delete[] allowedValues;
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkVolkano1::DoSetBootMode);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkVolkano1::EnableActionBspType()
{
    Zapp::Action* action = new Zapp::Action("BspType");
    action->AddOutputParameter(new ParameterString("aBspType"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkVolkano1::DoBspType);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkVolkano1::EnableActionUglyName()
{
    Zapp::Action* action = new Zapp::Action("UglyName");
    action->AddOutputParameter(new ParameterString("aUglyName"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkVolkano1::DoUglyName);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkVolkano1::EnableActionMacAddress()
{
    Zapp::Action* action = new Zapp::Action("MacAddress");
    action->AddOutputParameter(new ParameterString("aMacAddress"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkVolkano1::DoMacAddress);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkVolkano1::EnableActionProductId()
{
    Zapp::Action* action = new Zapp::Action("ProductId");
    action->AddOutputParameter(new ParameterString("aProductNumber"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkVolkano1::DoProductId);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkVolkano1::EnableActionBoardId()
{
    Zapp::Action* action = new Zapp::Action("BoardId");
    action->AddInputParameter(new ParameterUint("aIndex"));
    action->AddOutputParameter(new ParameterString("aBoardNumber"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkVolkano1::DoBoardId);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkVolkano1::EnableActionBoardType()
{
    Zapp::Action* action = new Zapp::Action("BoardType");
    action->AddInputParameter(new ParameterUint("aIndex"));
    action->AddOutputParameter(new ParameterString("aBoardNumber"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkVolkano1::DoBoardType);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkVolkano1::EnableActionMaxBoards()
{
    Zapp::Action* action = new Zapp::Action("MaxBoards");
    action->AddOutputParameter(new ParameterUint("aMaxBoards"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkVolkano1::DoMaxBoards);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkVolkano1::EnableActionSoftwareVersion()
{
    Zapp::Action* action = new Zapp::Action("SoftwareVersion");
    action->AddOutputParameter(new ParameterString("aSoftwareVersion"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkVolkano1::DoSoftwareVersion);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkVolkano1::DoReboot(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    Reboot(resp, aVersion);
}

void DvProviderLinnCoUkVolkano1::DoBootMode(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaMode(aInvocation, "aMode");
    BootMode(resp, aVersion, respaMode);
}

void DvProviderLinnCoUkVolkano1::DoSetBootMode(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz aMode;
    aInvocation.InvocationReadString("aMode", aMode);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetBootMode(resp, aVersion, aMode);
}

void DvProviderLinnCoUkVolkano1::DoBspType(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaBspType(aInvocation, "aBspType");
    BspType(resp, aVersion, respaBspType);
}

void DvProviderLinnCoUkVolkano1::DoUglyName(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaUglyName(aInvocation, "aUglyName");
    UglyName(resp, aVersion, respaUglyName);
}

void DvProviderLinnCoUkVolkano1::DoMacAddress(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaMacAddress(aInvocation, "aMacAddress");
    MacAddress(resp, aVersion, respaMacAddress);
}

void DvProviderLinnCoUkVolkano1::DoProductId(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaProductNumber(aInvocation, "aProductNumber");
    ProductId(resp, aVersion, respaProductNumber);
}

void DvProviderLinnCoUkVolkano1::DoBoardId(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aIndex = aInvocation.InvocationReadUint("aIndex");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaBoardNumber(aInvocation, "aBoardNumber");
    BoardId(resp, aVersion, aIndex, respaBoardNumber);
}

void DvProviderLinnCoUkVolkano1::DoBoardType(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aIndex = aInvocation.InvocationReadUint("aIndex");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaBoardNumber(aInvocation, "aBoardNumber");
    BoardType(resp, aVersion, aIndex, respaBoardNumber);
}

void DvProviderLinnCoUkVolkano1::DoMaxBoards(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respaMaxBoards(aInvocation, "aMaxBoards");
    MaxBoards(resp, aVersion, respaMaxBoards);
}

void DvProviderLinnCoUkVolkano1::DoSoftwareVersion(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaSoftwareVersion(aInvocation, "aSoftwareVersion");
    SoftwareVersion(resp, aVersion, respaSoftwareVersion);
}

void DvProviderLinnCoUkVolkano1::Reboot(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkVolkano1::BootMode(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aaMode*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkVolkano1::SetBootMode(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aaMode*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkVolkano1::BspType(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aaBspType*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkVolkano1::UglyName(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aaUglyName*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkVolkano1::MacAddress(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aaMacAddress*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkVolkano1::ProductId(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aaProductNumber*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkVolkano1::BoardId(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaIndex*/, IInvocationResponseString& /*aaBoardNumber*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkVolkano1::BoardType(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaIndex*/, IInvocationResponseString& /*aaBoardNumber*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkVolkano1::MaxBoards(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aaMaxBoards*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkVolkano1::SoftwareVersion(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aaSoftwareVersion*/)
{
    ASSERTS();
}

