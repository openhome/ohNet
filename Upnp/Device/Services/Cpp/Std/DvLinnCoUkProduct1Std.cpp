#include <Std/DvLinnCoUkProduct1.h>
#include <ZappTypes.h>
#include <DviService.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace Zapp;

bool DvProviderLinnCoUkProduct1Cpp::SetPropertyRoom(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyRoom, buf);
}

void DvProviderLinnCoUkProduct1Cpp::GetPropertyRoom(std::string& aValue)
{
    const Brx& val = iPropertyRoom->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderLinnCoUkProduct1Cpp::SetPropertyStandby(bool aValue)
{
    return SetPropertyBool(*iPropertyStandby, aValue);
}

void DvProviderLinnCoUkProduct1Cpp::GetPropertyStandby(bool& aValue)
{
    aValue = iPropertyStandby->Value();
}

DvProviderLinnCoUkProduct1Cpp::DvProviderLinnCoUkProduct1Cpp(DvDeviceStd& aDevice)
    : DvProvider(aDevice.Device(), "linn.co.uk", "Product", 1)
{
    
    iPropertyRoom = new PropertyString(new ParameterString("Room"));
    iService->AddProperty(iPropertyRoom); // passes ownership
    iPropertyStandby = new PropertyBool(new ParameterBool("Standby"));
    iService->AddProperty(iPropertyStandby); // passes ownership
}

void DvProviderLinnCoUkProduct1Cpp::EnableActionRoom()
{
    Zapp::Action* action = new Zapp::Action("Room");
    action->AddOutputParameter(new ParameterRelated("aRoom", *iPropertyRoom));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProduct1Cpp::DoRoom);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct1Cpp::EnableActionSetRoom()
{
    Zapp::Action* action = new Zapp::Action("SetRoom");
    action->AddInputParameter(new ParameterRelated("aRoom", *iPropertyRoom));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProduct1Cpp::DoSetRoom);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct1Cpp::EnableActionStandby()
{
    Zapp::Action* action = new Zapp::Action("Standby");
    action->AddOutputParameter(new ParameterRelated("aStandby", *iPropertyStandby));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProduct1Cpp::DoStandby);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct1Cpp::EnableActionSetStandby()
{
    Zapp::Action* action = new Zapp::Action("SetStandby");
    action->AddInputParameter(new ParameterRelated("aStandby", *iPropertyStandby));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProduct1Cpp::DoSetStandby);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct1Cpp::DoRoom(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respaRoom;
    Room(aVersion, respaRoom);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriteraRoom(aInvocation, "aRoom");
    Brn buf_aRoom((const TByte*)respaRoom.c_str(), (TUint)respaRoom.length());
    respWriteraRoom.Write(buf_aRoom);
    aInvocation.InvocationWriteStringEnd("aRoom");
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkProduct1Cpp::DoSetRoom(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz buf_aRoom;
    aInvocation.InvocationReadString("aRoom", buf_aRoom);
    std::string aRoom((const char*)buf_aRoom.Ptr(), buf_aRoom.Bytes());
    aInvocation.InvocationReadEnd();
    SetRoom(aVersion, aRoom);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkProduct1Cpp::DoStandby(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    bool respaStandby;
    Standby(aVersion, respaStandby);
	aInvocation.InvocationWriteStart();
    InvocationResponseBool respWriteraStandby(aInvocation, "aStandby");
    respWriteraStandby.Write(respaStandby);
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkProduct1Cpp::DoSetStandby(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    bool aStandby = aInvocation.InvocationReadBool("aStandby");
    aInvocation.InvocationReadEnd();
    SetStandby(aVersion, aStandby);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkProduct1Cpp::Room(uint32_t /*aVersion*/, std::string& /*aaRoom*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkProduct1Cpp::SetRoom(uint32_t /*aVersion*/, const std::string& /*aaRoom*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkProduct1Cpp::Standby(uint32_t /*aVersion*/, bool& /*aaStandby*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkProduct1Cpp::SetStandby(uint32_t /*aVersion*/, bool /*aaStandby*/)
{
    ASSERTS();
}

