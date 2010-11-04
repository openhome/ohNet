#include <Std/DvLinnCoUkVolkano1.h>
#include <ZappTypes.h>
#include <DviService.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

DvProviderLinnCoUkVolkano1Cpp::DvProviderLinnCoUkVolkano1Cpp(DvDeviceStd& aDevice)
    : DvProvider(aDevice.Device(), "linn.co.uk", "Volkano", 1)
{
    Functor empty;
}

void DvProviderLinnCoUkVolkano1Cpp::EnableActionReboot()
{
    Zapp::Action* action = new Zapp::Action("Reboot");
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkVolkano1Cpp::DoReboot);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkVolkano1Cpp::EnableActionBootMode()
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
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkVolkano1Cpp::DoBootMode);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkVolkano1Cpp::EnableActionSetBootMode()
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
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkVolkano1Cpp::DoSetBootMode);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkVolkano1Cpp::EnableActionBspType()
{
    Zapp::Action* action = new Zapp::Action("BspType");
    action->AddOutputParameter(new ParameterString("aBspType"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkVolkano1Cpp::DoBspType);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkVolkano1Cpp::EnableActionUglyName()
{
    Zapp::Action* action = new Zapp::Action("UglyName");
    action->AddOutputParameter(new ParameterString("aUglyName"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkVolkano1Cpp::DoUglyName);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkVolkano1Cpp::EnableActionMacAddress()
{
    Zapp::Action* action = new Zapp::Action("MacAddress");
    action->AddOutputParameter(new ParameterString("aMacAddress"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkVolkano1Cpp::DoMacAddress);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkVolkano1Cpp::EnableActionProductId()
{
    Zapp::Action* action = new Zapp::Action("ProductId");
    action->AddOutputParameter(new ParameterString("aProductNumber"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkVolkano1Cpp::DoProductId);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkVolkano1Cpp::EnableActionBoardId()
{
    Zapp::Action* action = new Zapp::Action("BoardId");
    action->AddInputParameter(new ParameterUint("aIndex"));
    action->AddOutputParameter(new ParameterString("aBoardNumber"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkVolkano1Cpp::DoBoardId);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkVolkano1Cpp::EnableActionBoardType()
{
    Zapp::Action* action = new Zapp::Action("BoardType");
    action->AddInputParameter(new ParameterUint("aIndex"));
    action->AddOutputParameter(new ParameterString("aBoardNumber"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkVolkano1Cpp::DoBoardType);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkVolkano1Cpp::EnableActionMaxBoards()
{
    Zapp::Action* action = new Zapp::Action("MaxBoards");
    action->AddOutputParameter(new ParameterUint("aMaxBoards"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkVolkano1Cpp::DoMaxBoards);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkVolkano1Cpp::EnableActionSoftwareVersion()
{
    Zapp::Action* action = new Zapp::Action("SoftwareVersion");
    action->AddOutputParameter(new ParameterString("aSoftwareVersion"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkVolkano1Cpp::DoSoftwareVersion);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkVolkano1Cpp::DoReboot(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    Reboot(aVersion);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkVolkano1Cpp::DoBootMode(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respaMode;
    BootMode(aVersion, respaMode);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriteraMode(aInvocation, "aMode");
    Brn buf_aMode((const TByte*)respaMode.c_str(), (TUint)respaMode.length());
    respWriteraMode.Write(buf_aMode);
    aInvocation.InvocationWriteStringEnd("aMode");
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkVolkano1Cpp::DoSetBootMode(IDvInvocation& aInvocation, TUint aVersion)
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

void DvProviderLinnCoUkVolkano1Cpp::DoBspType(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respaBspType;
    BspType(aVersion, respaBspType);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriteraBspType(aInvocation, "aBspType");
    Brn buf_aBspType((const TByte*)respaBspType.c_str(), (TUint)respaBspType.length());
    respWriteraBspType.Write(buf_aBspType);
    aInvocation.InvocationWriteStringEnd("aBspType");
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkVolkano1Cpp::DoUglyName(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respaUglyName;
    UglyName(aVersion, respaUglyName);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriteraUglyName(aInvocation, "aUglyName");
    Brn buf_aUglyName((const TByte*)respaUglyName.c_str(), (TUint)respaUglyName.length());
    respWriteraUglyName.Write(buf_aUglyName);
    aInvocation.InvocationWriteStringEnd("aUglyName");
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkVolkano1Cpp::DoMacAddress(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respaMacAddress;
    MacAddress(aVersion, respaMacAddress);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriteraMacAddress(aInvocation, "aMacAddress");
    Brn buf_aMacAddress((const TByte*)respaMacAddress.c_str(), (TUint)respaMacAddress.length());
    respWriteraMacAddress.Write(buf_aMacAddress);
    aInvocation.InvocationWriteStringEnd("aMacAddress");
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkVolkano1Cpp::DoProductId(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respaProductNumber;
    ProductId(aVersion, respaProductNumber);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriteraProductNumber(aInvocation, "aProductNumber");
    Brn buf_aProductNumber((const TByte*)respaProductNumber.c_str(), (TUint)respaProductNumber.length());
    respWriteraProductNumber.Write(buf_aProductNumber);
    aInvocation.InvocationWriteStringEnd("aProductNumber");
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkVolkano1Cpp::DoBoardId(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t aIndex = aInvocation.InvocationReadUint("aIndex");
    aInvocation.InvocationReadEnd();
    std::string respaBoardNumber;
    BoardId(aVersion, aIndex, respaBoardNumber);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriteraBoardNumber(aInvocation, "aBoardNumber");
    Brn buf_aBoardNumber((const TByte*)respaBoardNumber.c_str(), (TUint)respaBoardNumber.length());
    respWriteraBoardNumber.Write(buf_aBoardNumber);
    aInvocation.InvocationWriteStringEnd("aBoardNumber");
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkVolkano1Cpp::DoBoardType(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t aIndex = aInvocation.InvocationReadUint("aIndex");
    aInvocation.InvocationReadEnd();
    std::string respaBoardNumber;
    BoardType(aVersion, aIndex, respaBoardNumber);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriteraBoardNumber(aInvocation, "aBoardNumber");
    Brn buf_aBoardNumber((const TByte*)respaBoardNumber.c_str(), (TUint)respaBoardNumber.length());
    respWriteraBoardNumber.Write(buf_aBoardNumber);
    aInvocation.InvocationWriteStringEnd("aBoardNumber");
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkVolkano1Cpp::DoMaxBoards(IDvInvocation& aInvocation, TUint aVersion)
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

void DvProviderLinnCoUkVolkano1Cpp::DoSoftwareVersion(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respaSoftwareVersion;
    SoftwareVersion(aVersion, respaSoftwareVersion);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriteraSoftwareVersion(aInvocation, "aSoftwareVersion");
    Brn buf_aSoftwareVersion((const TByte*)respaSoftwareVersion.c_str(), (TUint)respaSoftwareVersion.length());
    respWriteraSoftwareVersion.Write(buf_aSoftwareVersion);
    aInvocation.InvocationWriteStringEnd("aSoftwareVersion");
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkVolkano1Cpp::Reboot(uint32_t /*aVersion*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkVolkano1Cpp::BootMode(uint32_t /*aVersion*/, std::string& /*aaMode*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkVolkano1Cpp::SetBootMode(uint32_t /*aVersion*/, const std::string& /*aaMode*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkVolkano1Cpp::BspType(uint32_t /*aVersion*/, std::string& /*aaBspType*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkVolkano1Cpp::UglyName(uint32_t /*aVersion*/, std::string& /*aaUglyName*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkVolkano1Cpp::MacAddress(uint32_t /*aVersion*/, std::string& /*aaMacAddress*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkVolkano1Cpp::ProductId(uint32_t /*aVersion*/, std::string& /*aaProductNumber*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkVolkano1Cpp::BoardId(uint32_t /*aVersion*/, uint32_t /*aaIndex*/, std::string& /*aaBoardNumber*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkVolkano1Cpp::BoardType(uint32_t /*aVersion*/, uint32_t /*aaIndex*/, std::string& /*aaBoardNumber*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkVolkano1Cpp::MaxBoards(uint32_t /*aVersion*/, uint32_t& /*aaMaxBoards*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkVolkano1Cpp::SoftwareVersion(uint32_t /*aVersion*/, std::string& /*aaSoftwareVersion*/)
{
    ASSERTS();
}

