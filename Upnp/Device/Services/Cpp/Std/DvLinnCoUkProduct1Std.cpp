#include <Std/DvLinnCoUkProduct1.h>
#include <ZappTypes.h>
#include <DviService.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

void DvServiceLinnCoUkProduct1Cpp::SetPropertyRoom(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), aValue.length());
    SetPropertyString(*iPropertyRoom, buf);
}

void DvServiceLinnCoUkProduct1Cpp::GetPropertyRoom(std::string& aValue)
{
    const Brx& val = iPropertyRoom->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

void DvServiceLinnCoUkProduct1Cpp::SetPropertyStandby(bool aValue)
{
    SetPropertyBool(*iPropertyStandby, aValue);
}

void DvServiceLinnCoUkProduct1Cpp::GetPropertyStandby(bool& aValue)
{
    aValue = iPropertyStandby->Value();
}

DvServiceLinnCoUkProduct1Cpp::DvServiceLinnCoUkProduct1Cpp(DvDeviceStd& aDevice)
    : DvService(aDevice.Device(), "linn.co.uk", "Product", 1)
{
    Functor empty;
    iPropertyRoom = new PropertyString(new ParameterString("Room"), empty);
    iService->AddProperty(iPropertyRoom); // passes ownership
    iPropertyStandby = new PropertyBool(new ParameterBool("Standby"), empty);
    iService->AddProperty(iPropertyStandby); // passes ownership
}

void DvServiceLinnCoUkProduct1Cpp::EnableActionRoom()
{
    Zapp::Action* action = new Zapp::Action("Room");
    action->AddOutputParameter(new ParameterRelated("aRoom", *iPropertyRoom));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkProduct1Cpp::DoRoom);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkProduct1Cpp::EnableActionSetRoom()
{
    Zapp::Action* action = new Zapp::Action("SetRoom");
    action->AddInputParameter(new ParameterRelated("aRoom", *iPropertyRoom));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkProduct1Cpp::DoSetRoom);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkProduct1Cpp::EnableActionStandby()
{
    Zapp::Action* action = new Zapp::Action("Standby");
    action->AddOutputParameter(new ParameterRelated("aStandby", *iPropertyStandby));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkProduct1Cpp::DoStandby);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkProduct1Cpp::EnableActionSetStandby()
{
    Zapp::Action* action = new Zapp::Action("SetStandby");
    action->AddInputParameter(new ParameterRelated("aStandby", *iPropertyStandby));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkProduct1Cpp::DoSetStandby);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkProduct1Cpp::DoRoom(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respaRoom;
    Room(aVersion, respaRoom);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriteraRoom(aInvocation, "aRoom");
    Brn buf_aRoom((const TByte*)respaRoom.c_str(), respaRoom.length());
    respWriteraRoom.Write(buf_aRoom);
    aInvocation.InvocationWriteStringEnd("aRoom");
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkProduct1Cpp::DoSetRoom(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceLinnCoUkProduct1Cpp::DoStandby(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceLinnCoUkProduct1Cpp::DoSetStandby(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    bool aStandby = aInvocation.InvocationReadBool("aStandby");
    aInvocation.InvocationReadEnd();
    SetStandby(aVersion, aStandby);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkProduct1Cpp::Room(uint32_t /*aVersion*/, std::string& /*aaRoom*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkProduct1Cpp::SetRoom(uint32_t /*aVersion*/, const std::string& /*aaRoom*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkProduct1Cpp::Standby(uint32_t /*aVersion*/, bool& /*aaStandby*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkProduct1Cpp::SetStandby(uint32_t /*aVersion*/, bool /*aaStandby*/)
{
    ASSERTS();
}

