#include <Std/DvLinnCoUkVolkano1.h>
#include <ZappTypes.h>
#include <DviService.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

DvServiceLinnCoUkVolkano1Cpp::DvServiceLinnCoUkVolkano1Cpp(DvDeviceStd& aDevice)
    : DvService(aDevice.Device(), "linn.co.uk", "Volkano", 1)
{
    Functor empty;
}

void DvServiceLinnCoUkVolkano1Cpp::EnableActionReboot()
{
    Zapp::Action* action = new Zapp::Action("Reboot");
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkVolkano1Cpp::DoReboot);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkVolkano1Cpp::EnableActionBootMode()
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
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkVolkano1Cpp::DoBootMode);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkVolkano1Cpp::EnableActionSetBootMode()
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
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkVolkano1Cpp::DoSetBootMode);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkVolkano1Cpp::EnableActionBspType()
{
    Zapp::Action* action = new Zapp::Action("BspType");
    action->AddOutputParameter(new ParameterString("aBspType"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkVolkano1Cpp::DoBspType);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkVolkano1Cpp::EnableActionUglyName()
{
    Zapp::Action* action = new Zapp::Action("UglyName");
    action->AddOutputParameter(new ParameterString("aUglyName"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkVolkano1Cpp::DoUglyName);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkVolkano1Cpp::EnableActionMacAddress()
{
    Zapp::Action* action = new Zapp::Action("MacAddress");
    action->AddOutputParameter(new ParameterString("aMacAddress"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkVolkano1Cpp::DoMacAddress);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkVolkano1Cpp::EnableActionProductId()
{
    Zapp::Action* action = new Zapp::Action("ProductId");
    action->AddOutputParameter(new ParameterString("aProductNumber"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkVolkano1Cpp::DoProductId);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkVolkano1Cpp::EnableActionBoardId()
{
    Zapp::Action* action = new Zapp::Action("BoardId");
    action->AddInputParameter(new ParameterUint("aIndex"));
    action->AddOutputParameter(new ParameterString("aBoardNumber"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkVolkano1Cpp::DoBoardId);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkVolkano1Cpp::EnableActionBoardType()
{
    Zapp::Action* action = new Zapp::Action("BoardType");
    action->AddInputParameter(new ParameterUint("aIndex"));
    action->AddOutputParameter(new ParameterString("aBoardNumber"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkVolkano1Cpp::DoBoardType);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkVolkano1Cpp::EnableActionMaxBoards()
{
    Zapp::Action* action = new Zapp::Action("MaxBoards");
    action->AddOutputParameter(new ParameterUint("aMaxBoards"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkVolkano1Cpp::DoMaxBoards);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkVolkano1Cpp::EnableActionSoftwareVersion()
{
    Zapp::Action* action = new Zapp::Action("SoftwareVersion");
    action->AddOutputParameter(new ParameterString("aSoftwareVersion"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkVolkano1Cpp::DoSoftwareVersion);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkVolkano1Cpp::DoReboot(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    Reboot(aVersion);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkVolkano1Cpp::DoBootMode(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respaMode;
    BootMode(aVersion, respaMode);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriteraMode(aInvocation, "aMode");
    Brn buf_aMode((const TByte*)respaMode.c_str(), respaMode.length());
    respWriteraMode.Write(buf_aMode);
    aInvocation.InvocationWriteStringEnd("aMode");
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkVolkano1Cpp::DoSetBootMode(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz buf_aMode;
    aInvocation.InvocationReadString("aMode", buf_aMode);
    std::string aMode((const char*)buf_aMode.Ptr(), buf_aMode.Bytes());
    aInvocation.InvocationReadEnd();
    SetBootMode(aVersion, aMode);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkVolkano1Cpp::DoBspType(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respaBspType;
    BspType(aVersion, respaBspType);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriteraBspType(aInvocation, "aBspType");
    Brn buf_aBspType((const TByte*)respaBspType.c_str(), respaBspType.length());
    respWriteraBspType.Write(buf_aBspType);
    aInvocation.InvocationWriteStringEnd("aBspType");
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkVolkano1Cpp::DoUglyName(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respaUglyName;
    UglyName(aVersion, respaUglyName);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriteraUglyName(aInvocation, "aUglyName");
    Brn buf_aUglyName((const TByte*)respaUglyName.c_str(), respaUglyName.length());
    respWriteraUglyName.Write(buf_aUglyName);
    aInvocation.InvocationWriteStringEnd("aUglyName");
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkVolkano1Cpp::DoMacAddress(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respaMacAddress;
    MacAddress(aVersion, respaMacAddress);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriteraMacAddress(aInvocation, "aMacAddress");
    Brn buf_aMacAddress((const TByte*)respaMacAddress.c_str(), respaMacAddress.length());
    respWriteraMacAddress.Write(buf_aMacAddress);
    aInvocation.InvocationWriteStringEnd("aMacAddress");
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkVolkano1Cpp::DoProductId(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respaProductNumber;
    ProductId(aVersion, respaProductNumber);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriteraProductNumber(aInvocation, "aProductNumber");
    Brn buf_aProductNumber((const TByte*)respaProductNumber.c_str(), respaProductNumber.length());
    respWriteraProductNumber.Write(buf_aProductNumber);
    aInvocation.InvocationWriteStringEnd("aProductNumber");
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkVolkano1Cpp::DoBoardId(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t aIndex = aInvocation.InvocationReadUint("aIndex");
    aInvocation.InvocationReadEnd();
    std::string respaBoardNumber;
    BoardId(aVersion, aIndex, respaBoardNumber);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriteraBoardNumber(aInvocation, "aBoardNumber");
    Brn buf_aBoardNumber((const TByte*)respaBoardNumber.c_str(), respaBoardNumber.length());
    respWriteraBoardNumber.Write(buf_aBoardNumber);
    aInvocation.InvocationWriteStringEnd("aBoardNumber");
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkVolkano1Cpp::DoBoardType(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t aIndex = aInvocation.InvocationReadUint("aIndex");
    aInvocation.InvocationReadEnd();
    std::string respaBoardNumber;
    BoardType(aVersion, aIndex, respaBoardNumber);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriteraBoardNumber(aInvocation, "aBoardNumber");
    Brn buf_aBoardNumber((const TByte*)respaBoardNumber.c_str(), respaBoardNumber.length());
    respWriteraBoardNumber.Write(buf_aBoardNumber);
    aInvocation.InvocationWriteStringEnd("aBoardNumber");
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkVolkano1Cpp::DoMaxBoards(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respaMaxBoards;
    MaxBoards(aVersion, respaMaxBoards);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriteraMaxBoards(aInvocation, "aMaxBoards");
    respWriteraMaxBoards.Write(respaMaxBoards);
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkVolkano1Cpp::DoSoftwareVersion(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respaSoftwareVersion;
    SoftwareVersion(aVersion, respaSoftwareVersion);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriteraSoftwareVersion(aInvocation, "aSoftwareVersion");
    Brn buf_aSoftwareVersion((const TByte*)respaSoftwareVersion.c_str(), respaSoftwareVersion.length());
    respWriteraSoftwareVersion.Write(buf_aSoftwareVersion);
    aInvocation.InvocationWriteStringEnd("aSoftwareVersion");
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkVolkano1Cpp::Reboot(uint32_t /*aVersion*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkVolkano1Cpp::BootMode(uint32_t /*aVersion*/, std::string& /*aaMode*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkVolkano1Cpp::SetBootMode(uint32_t /*aVersion*/, const std::string& /*aaMode*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkVolkano1Cpp::BspType(uint32_t /*aVersion*/, std::string& /*aaBspType*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkVolkano1Cpp::UglyName(uint32_t /*aVersion*/, std::string& /*aaUglyName*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkVolkano1Cpp::MacAddress(uint32_t /*aVersion*/, std::string& /*aaMacAddress*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkVolkano1Cpp::ProductId(uint32_t /*aVersion*/, std::string& /*aaProductNumber*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkVolkano1Cpp::BoardId(uint32_t /*aVersion*/, uint32_t /*aaIndex*/, std::string& /*aaBoardNumber*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkVolkano1Cpp::BoardType(uint32_t /*aVersion*/, uint32_t /*aaIndex*/, std::string& /*aaBoardNumber*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkVolkano1Cpp::MaxBoards(uint32_t /*aVersion*/, uint32_t& /*aaMaxBoards*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkVolkano1Cpp::SoftwareVersion(uint32_t /*aVersion*/, std::string& /*aaSoftwareVersion*/)
{
    ASSERTS();
}

