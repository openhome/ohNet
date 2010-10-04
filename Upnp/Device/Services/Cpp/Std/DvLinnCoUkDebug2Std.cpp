#include <Std/DvLinnCoUkDebug2.h>
#include <ZappTypes.h>
#include <DviService.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

DvServiceLinnCoUkDebug2Cpp::DvServiceLinnCoUkDebug2Cpp(DvDeviceStd& aDevice)
    : DvService(aDevice.Device(), "linn.co.uk", "Debug", 2)
{
    Functor empty;
}

void DvServiceLinnCoUkDebug2Cpp::EnableActionSetDebugLevel()
{
    Zapp::Action* action = new Zapp::Action("SetDebugLevel");
    action->AddInputParameter(new ParameterUint("aDebugLevel"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkDebug2Cpp::DoSetDebugLevel);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkDebug2Cpp::EnableActionDebugLevel()
{
    Zapp::Action* action = new Zapp::Action("DebugLevel");
    action->AddOutputParameter(new ParameterUint("aDebugLevel"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkDebug2Cpp::DoDebugLevel);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkDebug2Cpp::EnableActionMemWrite()
{
    Zapp::Action* action = new Zapp::Action("MemWrite");
    action->AddInputParameter(new ParameterUint("aMemAddress"));
    action->AddInputParameter(new ParameterBinary("aMemData"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkDebug2Cpp::DoMemWrite);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkDebug2Cpp::DoSetDebugLevel(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t aDebugLevel = aInvocation.InvocationReadUint("aDebugLevel");
    aInvocation.InvocationReadEnd();
    SetDebugLevel(aVersion, aDebugLevel);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkDebug2Cpp::DoDebugLevel(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respaDebugLevel;
    DebugLevel(aVersion, respaDebugLevel);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriteraDebugLevel(aInvocation, "aDebugLevel");
    respWriteraDebugLevel.Write(respaDebugLevel);
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkDebug2Cpp::DoMemWrite(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t aMemAddress = aInvocation.InvocationReadUint("aMemAddress");
    Brh buf_aMemData;
    aInvocation.InvocationReadBinary("aMemData", buf_aMemData);
    std::string aMemData((const char*)buf_aMemData.Ptr(), buf_aMemData.Bytes());
    aInvocation.InvocationReadEnd();
    MemWrite(aVersion, aMemAddress, aMemData);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkDebug2Cpp::SetDebugLevel(uint32_t /*aVersion*/, uint32_t /*aaDebugLevel*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkDebug2Cpp::DebugLevel(uint32_t /*aVersion*/, uint32_t& /*aaDebugLevel*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkDebug2Cpp::MemWrite(uint32_t /*aVersion*/, uint32_t /*aaMemAddress*/, const std::string& /*aaMemData*/)
{
    ASSERTS();
}

