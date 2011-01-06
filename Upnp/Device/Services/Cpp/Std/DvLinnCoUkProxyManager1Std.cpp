#include "DvLinnCoUkProxyManager1.h"
#include <ZappTypes.h>
#include <DviService.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace Zapp;

bool DvProviderLinnCoUkProxyManager1Cpp::SetPropertyKontrolProductConnected(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyKontrolProductConnected, buf);
}

void DvProviderLinnCoUkProxyManager1Cpp::GetPropertyKontrolProductConnected(std::string& aValue)
{
    const Brx& val = iPropertyKontrolProductConnected->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderLinnCoUkProxyManager1Cpp::SetPropertyKontrolProductComPort(uint32_t aValue)
{
    return SetPropertyUint(*iPropertyKontrolProductComPort, aValue);
}

void DvProviderLinnCoUkProxyManager1Cpp::GetPropertyKontrolProductComPort(uint32_t& aValue)
{
    aValue = iPropertyKontrolProductComPort->Value();
}

bool DvProviderLinnCoUkProxyManager1Cpp::SetPropertyDiscPlayerConnected(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyDiscPlayerConnected, buf);
}

void DvProviderLinnCoUkProxyManager1Cpp::GetPropertyDiscPlayerConnected(std::string& aValue)
{
    const Brx& val = iPropertyDiscPlayerConnected->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderLinnCoUkProxyManager1Cpp::SetPropertyDiscPlayerComPort(uint32_t aValue)
{
    return SetPropertyUint(*iPropertyDiscPlayerComPort, aValue);
}

void DvProviderLinnCoUkProxyManager1Cpp::GetPropertyDiscPlayerComPort(uint32_t& aValue)
{
    aValue = iPropertyDiscPlayerComPort->Value();
}

DvProviderLinnCoUkProxyManager1Cpp::DvProviderLinnCoUkProxyManager1Cpp(DvDeviceStd& aDevice)
    : DvProvider(aDevice.Device(), "linn.co.uk", "ProxyManager", 1)
{
    
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
    iPropertyKontrolProductConnected = new PropertyString(new ParameterString("KontrolProductConnected", allowedValues, 11));
    delete[] allowedValues;
    iService->AddProperty(iPropertyKontrolProductConnected); // passes ownership
    iPropertyKontrolProductComPort = new PropertyUint(new ParameterUint("KontrolProductComPort"));
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
    iPropertyDiscPlayerConnected = new PropertyString(new ParameterString("DiscPlayerConnected", allowedValues, 9));
    delete[] allowedValues;
    iService->AddProperty(iPropertyDiscPlayerConnected); // passes ownership
    iPropertyDiscPlayerComPort = new PropertyUint(new ParameterUint("DiscPlayerComPort"));
    iService->AddProperty(iPropertyDiscPlayerComPort); // passes ownership
}

void DvProviderLinnCoUkProxyManager1Cpp::EnableActionKontrolProductConnected()
{
    Zapp::Action* action = new Zapp::Action("KontrolProductConnected");
    action->AddOutputParameter(new ParameterRelated("aConnected", *iPropertyKontrolProductConnected));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProxyManager1Cpp::DoKontrolProductConnected);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProxyManager1Cpp::EnableActionSetKontrolProductConnected()
{
    Zapp::Action* action = new Zapp::Action("SetKontrolProductConnected");
    action->AddInputParameter(new ParameterRelated("aConnected", *iPropertyKontrolProductConnected));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProxyManager1Cpp::DoSetKontrolProductConnected);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProxyManager1Cpp::EnableActionKontrolProductComPort()
{
    Zapp::Action* action = new Zapp::Action("KontrolProductComPort");
    action->AddOutputParameter(new ParameterRelated("aPort", *iPropertyKontrolProductComPort));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProxyManager1Cpp::DoKontrolProductComPort);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProxyManager1Cpp::EnableActionSetKontrolProductComPort()
{
    Zapp::Action* action = new Zapp::Action("SetKontrolProductComPort");
    action->AddInputParameter(new ParameterRelated("aConnected", *iPropertyKontrolProductComPort));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProxyManager1Cpp::DoSetKontrolProductComPort);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProxyManager1Cpp::EnableActionDiscPlayerConnected()
{
    Zapp::Action* action = new Zapp::Action("DiscPlayerConnected");
    action->AddOutputParameter(new ParameterRelated("aConnected", *iPropertyDiscPlayerConnected));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProxyManager1Cpp::DoDiscPlayerConnected);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProxyManager1Cpp::EnableActionSetDiscPlayerConnected()
{
    Zapp::Action* action = new Zapp::Action("SetDiscPlayerConnected");
    action->AddInputParameter(new ParameterRelated("aConnected", *iPropertyDiscPlayerConnected));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProxyManager1Cpp::DoSetDiscPlayerConnected);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProxyManager1Cpp::EnableActionDiscPlayerComPort()
{
    Zapp::Action* action = new Zapp::Action("DiscPlayerComPort");
    action->AddOutputParameter(new ParameterRelated("aPort", *iPropertyDiscPlayerComPort));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProxyManager1Cpp::DoDiscPlayerComPort);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProxyManager1Cpp::EnableActionSetDiscPlayerComPort()
{
    Zapp::Action* action = new Zapp::Action("SetDiscPlayerComPort");
    action->AddInputParameter(new ParameterRelated("aConnected", *iPropertyDiscPlayerComPort));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProxyManager1Cpp::DoSetDiscPlayerComPort);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProxyManager1Cpp::EnableActionTestKontrolProductConnection()
{
    Zapp::Action* action = new Zapp::Action("TestKontrolProductConnection");
    action->AddOutputParameter(new ParameterBool("aResult"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProxyManager1Cpp::DoTestKontrolProductConnection);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProxyManager1Cpp::EnableActionTestDiscPlayerConnection()
{
    Zapp::Action* action = new Zapp::Action("TestDiscPlayerConnection");
    action->AddOutputParameter(new ParameterBool("aResult"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProxyManager1Cpp::DoTestDiscPlayerConnection);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProxyManager1Cpp::DoKontrolProductConnected(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respaConnected;
    KontrolProductConnected(aVersion, respaConnected);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriteraConnected(aInvocation, "aConnected");
    Brn buf_aConnected((const TByte*)respaConnected.c_str(), (TUint)respaConnected.length());
    respWriteraConnected.Write(buf_aConnected);
    aInvocation.InvocationWriteStringEnd("aConnected");
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkProxyManager1Cpp::DoSetKontrolProductConnected(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz buf_aConnected;
    aInvocation.InvocationReadString("aConnected", buf_aConnected);
    std::string aConnected((const char*)buf_aConnected.Ptr(), buf_aConnected.Bytes());
    aInvocation.InvocationReadEnd();
    SetKontrolProductConnected(aVersion, aConnected);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkProxyManager1Cpp::DoKontrolProductComPort(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respaPort;
    KontrolProductComPort(aVersion, respaPort);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriteraPort(aInvocation, "aPort");
    respWriteraPort.Write(respaPort);
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkProxyManager1Cpp::DoSetKontrolProductComPort(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t aConnected = aInvocation.InvocationReadUint("aConnected");
    aInvocation.InvocationReadEnd();
    SetKontrolProductComPort(aVersion, aConnected);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkProxyManager1Cpp::DoDiscPlayerConnected(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respaConnected;
    DiscPlayerConnected(aVersion, respaConnected);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriteraConnected(aInvocation, "aConnected");
    Brn buf_aConnected((const TByte*)respaConnected.c_str(), (TUint)respaConnected.length());
    respWriteraConnected.Write(buf_aConnected);
    aInvocation.InvocationWriteStringEnd("aConnected");
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkProxyManager1Cpp::DoSetDiscPlayerConnected(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz buf_aConnected;
    aInvocation.InvocationReadString("aConnected", buf_aConnected);
    std::string aConnected((const char*)buf_aConnected.Ptr(), buf_aConnected.Bytes());
    aInvocation.InvocationReadEnd();
    SetDiscPlayerConnected(aVersion, aConnected);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkProxyManager1Cpp::DoDiscPlayerComPort(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respaPort;
    DiscPlayerComPort(aVersion, respaPort);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriteraPort(aInvocation, "aPort");
    respWriteraPort.Write(respaPort);
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkProxyManager1Cpp::DoSetDiscPlayerComPort(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t aConnected = aInvocation.InvocationReadUint("aConnected");
    aInvocation.InvocationReadEnd();
    SetDiscPlayerComPort(aVersion, aConnected);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkProxyManager1Cpp::DoTestKontrolProductConnection(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    bool respaResult;
    TestKontrolProductConnection(aVersion, respaResult);
	aInvocation.InvocationWriteStart();
    InvocationResponseBool respWriteraResult(aInvocation, "aResult");
    respWriteraResult.Write(respaResult);
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkProxyManager1Cpp::DoTestDiscPlayerConnection(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    bool respaResult;
    TestDiscPlayerConnection(aVersion, respaResult);
	aInvocation.InvocationWriteStart();
    InvocationResponseBool respWriteraResult(aInvocation, "aResult");
    respWriteraResult.Write(respaResult);
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkProxyManager1Cpp::KontrolProductConnected(uint32_t /*aVersion*/, std::string& /*aaConnected*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkProxyManager1Cpp::SetKontrolProductConnected(uint32_t /*aVersion*/, const std::string& /*aaConnected*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkProxyManager1Cpp::KontrolProductComPort(uint32_t /*aVersion*/, uint32_t& /*aaPort*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkProxyManager1Cpp::SetKontrolProductComPort(uint32_t /*aVersion*/, uint32_t /*aaConnected*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkProxyManager1Cpp::DiscPlayerConnected(uint32_t /*aVersion*/, std::string& /*aaConnected*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkProxyManager1Cpp::SetDiscPlayerConnected(uint32_t /*aVersion*/, const std::string& /*aaConnected*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkProxyManager1Cpp::DiscPlayerComPort(uint32_t /*aVersion*/, uint32_t& /*aaPort*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkProxyManager1Cpp::SetDiscPlayerComPort(uint32_t /*aVersion*/, uint32_t /*aaConnected*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkProxyManager1Cpp::TestKontrolProductConnection(uint32_t /*aVersion*/, bool& /*aaResult*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkProxyManager1Cpp::TestDiscPlayerConnection(uint32_t /*aVersion*/, bool& /*aaResult*/)
{
    ASSERTS();
}

