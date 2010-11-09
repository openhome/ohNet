#include <Core/DvLinnCoUkProxyManager1.h>
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

TBool DvProviderLinnCoUkProxyManager1::SetPropertyKontrolProductConnected(const Brx& aValue)
{
    return SetPropertyString(*iPropertyKontrolProductConnected, aValue);
}

void DvProviderLinnCoUkProxyManager1::GetPropertyKontrolProductConnected(Brhz& aValue)
{
    aValue.Set(iPropertyKontrolProductConnected->Value());
}

TBool DvProviderLinnCoUkProxyManager1::SetPropertyKontrolProductComPort(TUint aValue)
{
    return SetPropertyUint(*iPropertyKontrolProductComPort, aValue);
}

void DvProviderLinnCoUkProxyManager1::GetPropertyKontrolProductComPort(TUint& aValue)
{
    aValue = iPropertyKontrolProductComPort->Value();
}

TBool DvProviderLinnCoUkProxyManager1::SetPropertyDiscPlayerConnected(const Brx& aValue)
{
    return SetPropertyString(*iPropertyDiscPlayerConnected, aValue);
}

void DvProviderLinnCoUkProxyManager1::GetPropertyDiscPlayerConnected(Brhz& aValue)
{
    aValue.Set(iPropertyDiscPlayerConnected->Value());
}

TBool DvProviderLinnCoUkProxyManager1::SetPropertyDiscPlayerComPort(TUint aValue)
{
    return SetPropertyUint(*iPropertyDiscPlayerComPort, aValue);
}

void DvProviderLinnCoUkProxyManager1::GetPropertyDiscPlayerComPort(TUint& aValue)
{
    aValue = iPropertyDiscPlayerComPort->Value();
}

DvProviderLinnCoUkProxyManager1::DvProviderLinnCoUkProxyManager1(DvDevice& aDevice)
    : DvProvider(aDevice.Device(), "linn.co.uk", "ProxyManager", 1)
{
    Functor empty;
    TChar** allowedValues;
    TUint index;
    index = 0;
    allowedValues = new TChar*[11];
    allowedValues[index++] = (TChar*)"None";
    allowedValues[index++] = (TChar*)"Klimax Kontrol";
    allowedValues[index++] = (TChar*)"Akurate Kontrol";
    allowedValues[index++] = (TChar*)"Kisto";
    allowedValues[index++] = (TChar*)"Kinos";
    allowedValues[index++] = (TChar*)"Majik Kontrol";
    allowedValues[index++] = (TChar*)"Majik-I";
    allowedValues[index++] = (TChar*)"Unidisk SC";
    allowedValues[index++] = (TChar*)"Classik Movie";
    allowedValues[index++] = (TChar*)"Classik Music";
    allowedValues[index++] = (TChar*)"Roomamp 2";
    iPropertyKontrolProductConnected = new PropertyString(new ParameterString("KontrolProductConnected", allowedValues, 11), empty);
    delete[] allowedValues;
    iService->AddProperty(iPropertyKontrolProductConnected); // passes ownership
    iPropertyKontrolProductComPort = new PropertyUint(new ParameterUint("KontrolProductComPort"), empty);
    iService->AddProperty(iPropertyKontrolProductComPort); // passes ownership
    index = 0;
    allowedValues = new TChar*[9];
    allowedValues[index++] = (TChar*)"None";
    allowedValues[index++] = (TChar*)"CD12";
    allowedValues[index++] = (TChar*)"Akurate CD";
    allowedValues[index++] = (TChar*)"Unidisk 1.1";
    allowedValues[index++] = (TChar*)"Unidisk 2.1";
    allowedValues[index++] = (TChar*)"Majik CD";
    allowedValues[index++] = (TChar*)"Unidisk SC";
    allowedValues[index++] = (TChar*)"Classik Movie";
    allowedValues[index++] = (TChar*)"Classik Music";
    iPropertyDiscPlayerConnected = new PropertyString(new ParameterString("DiscPlayerConnected", allowedValues, 9), empty);
    delete[] allowedValues;
    iService->AddProperty(iPropertyDiscPlayerConnected); // passes ownership
    iPropertyDiscPlayerComPort = new PropertyUint(new ParameterUint("DiscPlayerComPort"), empty);
    iService->AddProperty(iPropertyDiscPlayerComPort); // passes ownership
}

void DvProviderLinnCoUkProxyManager1::EnableActionKontrolProductConnected()
{
    Zapp::Action* action = new Zapp::Action("KontrolProductConnected");
    action->AddOutputParameter(new ParameterRelated("aConnected", *iPropertyKontrolProductConnected));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkProxyManager1::DoKontrolProductConnected);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProxyManager1::EnableActionSetKontrolProductConnected()
{
    Zapp::Action* action = new Zapp::Action("SetKontrolProductConnected");
    action->AddInputParameter(new ParameterRelated("aConnected", *iPropertyKontrolProductConnected));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkProxyManager1::DoSetKontrolProductConnected);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProxyManager1::EnableActionKontrolProductComPort()
{
    Zapp::Action* action = new Zapp::Action("KontrolProductComPort");
    action->AddOutputParameter(new ParameterRelated("aPort", *iPropertyKontrolProductComPort));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkProxyManager1::DoKontrolProductComPort);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProxyManager1::EnableActionSetKontrolProductComPort()
{
    Zapp::Action* action = new Zapp::Action("SetKontrolProductComPort");
    action->AddInputParameter(new ParameterRelated("aConnected", *iPropertyKontrolProductComPort));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkProxyManager1::DoSetKontrolProductComPort);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProxyManager1::EnableActionDiscPlayerConnected()
{
    Zapp::Action* action = new Zapp::Action("DiscPlayerConnected");
    action->AddOutputParameter(new ParameterRelated("aConnected", *iPropertyDiscPlayerConnected));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkProxyManager1::DoDiscPlayerConnected);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProxyManager1::EnableActionSetDiscPlayerConnected()
{
    Zapp::Action* action = new Zapp::Action("SetDiscPlayerConnected");
    action->AddInputParameter(new ParameterRelated("aConnected", *iPropertyDiscPlayerConnected));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkProxyManager1::DoSetDiscPlayerConnected);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProxyManager1::EnableActionDiscPlayerComPort()
{
    Zapp::Action* action = new Zapp::Action("DiscPlayerComPort");
    action->AddOutputParameter(new ParameterRelated("aPort", *iPropertyDiscPlayerComPort));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkProxyManager1::DoDiscPlayerComPort);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProxyManager1::EnableActionSetDiscPlayerComPort()
{
    Zapp::Action* action = new Zapp::Action("SetDiscPlayerComPort");
    action->AddInputParameter(new ParameterRelated("aConnected", *iPropertyDiscPlayerComPort));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkProxyManager1::DoSetDiscPlayerComPort);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProxyManager1::EnableActionTestKontrolProductConnection()
{
    Zapp::Action* action = new Zapp::Action("TestKontrolProductConnection");
    action->AddOutputParameter(new ParameterBool("aResult"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkProxyManager1::DoTestKontrolProductConnection);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProxyManager1::EnableActionTestDiscPlayerConnection()
{
    Zapp::Action* action = new Zapp::Action("TestDiscPlayerConnection");
    action->AddOutputParameter(new ParameterBool("aResult"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkProxyManager1::DoTestDiscPlayerConnection);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProxyManager1::DoKontrolProductConnected(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaConnected(aInvocation, "aConnected");
    KontrolProductConnected(resp, aVersion, respaConnected);
}

void DvProviderLinnCoUkProxyManager1::DoSetKontrolProductConnected(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz aConnected;
    aInvocation.InvocationReadString("aConnected", aConnected);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetKontrolProductConnected(resp, aVersion, aConnected);
}

void DvProviderLinnCoUkProxyManager1::DoKontrolProductComPort(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respaPort(aInvocation, "aPort");
    KontrolProductComPort(resp, aVersion, respaPort);
}

void DvProviderLinnCoUkProxyManager1::DoSetKontrolProductComPort(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aConnected = aInvocation.InvocationReadUint("aConnected");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetKontrolProductComPort(resp, aVersion, aConnected);
}

void DvProviderLinnCoUkProxyManager1::DoDiscPlayerConnected(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaConnected(aInvocation, "aConnected");
    DiscPlayerConnected(resp, aVersion, respaConnected);
}

void DvProviderLinnCoUkProxyManager1::DoSetDiscPlayerConnected(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz aConnected;
    aInvocation.InvocationReadString("aConnected", aConnected);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetDiscPlayerConnected(resp, aVersion, aConnected);
}

void DvProviderLinnCoUkProxyManager1::DoDiscPlayerComPort(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respaPort(aInvocation, "aPort");
    DiscPlayerComPort(resp, aVersion, respaPort);
}

void DvProviderLinnCoUkProxyManager1::DoSetDiscPlayerComPort(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aConnected = aInvocation.InvocationReadUint("aConnected");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetDiscPlayerComPort(resp, aVersion, aConnected);
}

void DvProviderLinnCoUkProxyManager1::DoTestKontrolProductConnection(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBool respaResult(aInvocation, "aResult");
    TestKontrolProductConnection(resp, aVersion, respaResult);
}

void DvProviderLinnCoUkProxyManager1::DoTestDiscPlayerConnection(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBool respaResult(aInvocation, "aResult");
    TestDiscPlayerConnection(resp, aVersion, respaResult);
}

void DvProviderLinnCoUkProxyManager1::KontrolProductConnected(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aaConnected*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkProxyManager1::SetKontrolProductConnected(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aaConnected*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkProxyManager1::KontrolProductComPort(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aaPort*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkProxyManager1::SetKontrolProductComPort(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaConnected*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkProxyManager1::DiscPlayerConnected(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aaConnected*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkProxyManager1::SetDiscPlayerConnected(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aaConnected*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkProxyManager1::DiscPlayerComPort(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aaPort*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkProxyManager1::SetDiscPlayerComPort(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaConnected*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkProxyManager1::TestKontrolProductConnection(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseBool& /*aaResult*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkProxyManager1::TestDiscPlayerConnection(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseBool& /*aaResult*/)
{
    ASSERTS();
}

