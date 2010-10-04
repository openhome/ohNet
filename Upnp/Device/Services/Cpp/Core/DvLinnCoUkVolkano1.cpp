#include <Core/DvLinnCoUkVolkano1.h>
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

DvServiceLinnCoUkVolkano1::DvServiceLinnCoUkVolkano1(DvDevice& aDevice)
    : DvService(aDevice.Device(), "linn.co.uk", "Volkano", 1)
{
    Functor empty;
}

void DvServiceLinnCoUkVolkano1::EnableActionReboot()
{
    Zapp::Action* action = new Zapp::Action("Reboot");
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkVolkano1::DoReboot);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkVolkano1::EnableActionBootMode()
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
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkVolkano1::DoBootMode);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkVolkano1::EnableActionSetBootMode()
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
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkVolkano1::DoSetBootMode);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkVolkano1::EnableActionBspType()
{
    Zapp::Action* action = new Zapp::Action("BspType");
    action->AddOutputParameter(new ParameterString("aBspType"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkVolkano1::DoBspType);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkVolkano1::EnableActionUglyName()
{
    Zapp::Action* action = new Zapp::Action("UglyName");
    action->AddOutputParameter(new ParameterString("aUglyName"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkVolkano1::DoUglyName);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkVolkano1::EnableActionMacAddress()
{
    Zapp::Action* action = new Zapp::Action("MacAddress");
    action->AddOutputParameter(new ParameterString("aMacAddress"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkVolkano1::DoMacAddress);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkVolkano1::EnableActionProductId()
{
    Zapp::Action* action = new Zapp::Action("ProductId");
    action->AddOutputParameter(new ParameterString("aProductNumber"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkVolkano1::DoProductId);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkVolkano1::EnableActionBoardId()
{
    Zapp::Action* action = new Zapp::Action("BoardId");
    action->AddInputParameter(new ParameterUint("aIndex"));
    action->AddOutputParameter(new ParameterString("aBoardNumber"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkVolkano1::DoBoardId);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkVolkano1::EnableActionBoardType()
{
    Zapp::Action* action = new Zapp::Action("BoardType");
    action->AddInputParameter(new ParameterUint("aIndex"));
    action->AddOutputParameter(new ParameterString("aBoardNumber"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkVolkano1::DoBoardType);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkVolkano1::EnableActionMaxBoards()
{
    Zapp::Action* action = new Zapp::Action("MaxBoards");
    action->AddOutputParameter(new ParameterUint("aMaxBoards"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkVolkano1::DoMaxBoards);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkVolkano1::EnableActionSoftwareVersion()
{
    Zapp::Action* action = new Zapp::Action("SoftwareVersion");
    action->AddOutputParameter(new ParameterString("aSoftwareVersion"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkVolkano1::DoSoftwareVersion);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkVolkano1::DoReboot(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    Reboot(resp, aVersion);
}

void DvServiceLinnCoUkVolkano1::DoBootMode(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaMode(aInvocation, "aMode");
    BootMode(resp, aVersion, respaMode);
}

void DvServiceLinnCoUkVolkano1::DoSetBootMode(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz aMode;
    aInvocation.InvocationReadString("aMode", aMode);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetBootMode(resp, aVersion, aMode);
}

void DvServiceLinnCoUkVolkano1::DoBspType(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaBspType(aInvocation, "aBspType");
    BspType(resp, aVersion, respaBspType);
}

void DvServiceLinnCoUkVolkano1::DoUglyName(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaUglyName(aInvocation, "aUglyName");
    UglyName(resp, aVersion, respaUglyName);
}

void DvServiceLinnCoUkVolkano1::DoMacAddress(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaMacAddress(aInvocation, "aMacAddress");
    MacAddress(resp, aVersion, respaMacAddress);
}

void DvServiceLinnCoUkVolkano1::DoProductId(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaProductNumber(aInvocation, "aProductNumber");
    ProductId(resp, aVersion, respaProductNumber);
}

void DvServiceLinnCoUkVolkano1::DoBoardId(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aIndex = aInvocation.InvocationReadUint("aIndex");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaBoardNumber(aInvocation, "aBoardNumber");
    BoardId(resp, aVersion, aIndex, respaBoardNumber);
}

void DvServiceLinnCoUkVolkano1::DoBoardType(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aIndex = aInvocation.InvocationReadUint("aIndex");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaBoardNumber(aInvocation, "aBoardNumber");
    BoardType(resp, aVersion, aIndex, respaBoardNumber);
}

void DvServiceLinnCoUkVolkano1::DoMaxBoards(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respaMaxBoards(aInvocation, "aMaxBoards");
    MaxBoards(resp, aVersion, respaMaxBoards);
}

void DvServiceLinnCoUkVolkano1::DoSoftwareVersion(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaSoftwareVersion(aInvocation, "aSoftwareVersion");
    SoftwareVersion(resp, aVersion, respaSoftwareVersion);
}

void DvServiceLinnCoUkVolkano1::Reboot(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkVolkano1::BootMode(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aaMode*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkVolkano1::SetBootMode(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aaMode*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkVolkano1::BspType(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aaBspType*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkVolkano1::UglyName(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aaUglyName*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkVolkano1::MacAddress(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aaMacAddress*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkVolkano1::ProductId(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aaProductNumber*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkVolkano1::BoardId(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaIndex*/, IInvocationResponseString& /*aaBoardNumber*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkVolkano1::BoardType(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaIndex*/, IInvocationResponseString& /*aaBoardNumber*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkVolkano1::MaxBoards(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aaMaxBoards*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkVolkano1::SoftwareVersion(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aaSoftwareVersion*/)
{
    ASSERTS();
}

