#include <Std/DvLinnCoUkProduct3.h>
#include <ZappTypes.h>
#include <DviService.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

void DvServiceLinnCoUkProduct3Cpp::SetPropertyProductType(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), aValue.length());
    SetPropertyString(*iPropertyProductType, buf);
}

void DvServiceLinnCoUkProduct3Cpp::GetPropertyProductType(std::string& aValue)
{
    const Brx& val = iPropertyProductType->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

void DvServiceLinnCoUkProduct3Cpp::SetPropertyProductModel(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), aValue.length());
    SetPropertyString(*iPropertyProductModel, buf);
}

void DvServiceLinnCoUkProduct3Cpp::GetPropertyProductModel(std::string& aValue)
{
    const Brx& val = iPropertyProductModel->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

void DvServiceLinnCoUkProduct3Cpp::SetPropertyProductName(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), aValue.length());
    SetPropertyString(*iPropertyProductName, buf);
}

void DvServiceLinnCoUkProduct3Cpp::GetPropertyProductName(std::string& aValue)
{
    const Brx& val = iPropertyProductName->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

void DvServiceLinnCoUkProduct3Cpp::SetPropertyProductRoom(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), aValue.length());
    SetPropertyString(*iPropertyProductRoom, buf);
}

void DvServiceLinnCoUkProduct3Cpp::GetPropertyProductRoom(std::string& aValue)
{
    const Brx& val = iPropertyProductRoom->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

void DvServiceLinnCoUkProduct3Cpp::SetPropertyProductStandby(bool aValue)
{
    SetPropertyBool(*iPropertyProductStandby, aValue);
}

void DvServiceLinnCoUkProduct3Cpp::GetPropertyProductStandby(bool& aValue)
{
    aValue = iPropertyProductStandby->Value();
}

void DvServiceLinnCoUkProduct3Cpp::SetPropertyProductSourceIndex(uint32_t aValue)
{
    SetPropertyUint(*iPropertyProductSourceIndex, aValue);
}

void DvServiceLinnCoUkProduct3Cpp::GetPropertyProductSourceIndex(uint32_t& aValue)
{
    aValue = iPropertyProductSourceIndex->Value();
}

void DvServiceLinnCoUkProduct3Cpp::SetPropertyProductSourceCount(uint32_t aValue)
{
    SetPropertyUint(*iPropertyProductSourceCount, aValue);
}

void DvServiceLinnCoUkProduct3Cpp::GetPropertyProductSourceCount(uint32_t& aValue)
{
    aValue = iPropertyProductSourceCount->Value();
}

void DvServiceLinnCoUkProduct3Cpp::SetPropertyProductSourceXml(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), aValue.length());
    SetPropertyString(*iPropertyProductSourceXml, buf);
}

void DvServiceLinnCoUkProduct3Cpp::GetPropertyProductSourceXml(std::string& aValue)
{
    const Brx& val = iPropertyProductSourceXml->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

void DvServiceLinnCoUkProduct3Cpp::SetPropertyStartupSourceIndex(uint32_t aValue)
{
    SetPropertyUint(*iPropertyStartupSourceIndex, aValue);
}

void DvServiceLinnCoUkProduct3Cpp::GetPropertyStartupSourceIndex(uint32_t& aValue)
{
    aValue = iPropertyStartupSourceIndex->Value();
}

void DvServiceLinnCoUkProduct3Cpp::SetPropertyStartupSourceEnabled(bool aValue)
{
    SetPropertyBool(*iPropertyStartupSourceEnabled, aValue);
}

void DvServiceLinnCoUkProduct3Cpp::GetPropertyStartupSourceEnabled(bool& aValue)
{
    aValue = iPropertyStartupSourceEnabled->Value();
}

void DvServiceLinnCoUkProduct3Cpp::SetPropertyProductAnySourceName(uint32_t aValue)
{
    SetPropertyUint(*iPropertyProductAnySourceName, aValue);
}

void DvServiceLinnCoUkProduct3Cpp::GetPropertyProductAnySourceName(uint32_t& aValue)
{
    aValue = iPropertyProductAnySourceName->Value();
}

void DvServiceLinnCoUkProduct3Cpp::SetPropertyProductAnySourceVisible(uint32_t aValue)
{
    SetPropertyUint(*iPropertyProductAnySourceVisible, aValue);
}

void DvServiceLinnCoUkProduct3Cpp::GetPropertyProductAnySourceVisible(uint32_t& aValue)
{
    aValue = iPropertyProductAnySourceVisible->Value();
}

void DvServiceLinnCoUkProduct3Cpp::SetPropertyProductAnySourceType(uint32_t aValue)
{
    SetPropertyUint(*iPropertyProductAnySourceType, aValue);
}

void DvServiceLinnCoUkProduct3Cpp::GetPropertyProductAnySourceType(uint32_t& aValue)
{
    aValue = iPropertyProductAnySourceType->Value();
}

DvServiceLinnCoUkProduct3Cpp::DvServiceLinnCoUkProduct3Cpp(DvDeviceStd& aDevice)
    : DvService(aDevice.Device(), "linn.co.uk", "Product", 3)
{
    Functor empty;
    iPropertyProductType = new PropertyString(new ParameterString("ProductType"), empty);
    iService->AddProperty(iPropertyProductType); // passes ownership
    iPropertyProductModel = new PropertyString(new ParameterString("ProductModel"), empty);
    iService->AddProperty(iPropertyProductModel); // passes ownership
    iPropertyProductName = new PropertyString(new ParameterString("ProductName"), empty);
    iService->AddProperty(iPropertyProductName); // passes ownership
    iPropertyProductRoom = new PropertyString(new ParameterString("ProductRoom"), empty);
    iService->AddProperty(iPropertyProductRoom); // passes ownership
    iPropertyProductStandby = new PropertyBool(new ParameterBool("ProductStandby"), empty);
    iService->AddProperty(iPropertyProductStandby); // passes ownership
    iPropertyProductSourceIndex = new PropertyUint(new ParameterUint("ProductSourceIndex"), empty);
    iService->AddProperty(iPropertyProductSourceIndex); // passes ownership
    iPropertyProductSourceCount = new PropertyUint(new ParameterUint("ProductSourceCount"), empty);
    iService->AddProperty(iPropertyProductSourceCount); // passes ownership
    iPropertyProductSourceXml = new PropertyString(new ParameterString("ProductSourceXml"), empty);
    iService->AddProperty(iPropertyProductSourceXml); // passes ownership
    iPropertyStartupSourceIndex = new PropertyUint(new ParameterUint("StartupSourceIndex"), empty);
    iService->AddProperty(iPropertyStartupSourceIndex); // passes ownership
    iPropertyStartupSourceEnabled = new PropertyBool(new ParameterBool("StartupSourceEnabled"), empty);
    iService->AddProperty(iPropertyStartupSourceEnabled); // passes ownership
    iPropertyProductAnySourceName = new PropertyUint(new ParameterUint("ProductAnySourceName"), empty);
    iService->AddProperty(iPropertyProductAnySourceName); // passes ownership
    iPropertyProductAnySourceVisible = new PropertyUint(new ParameterUint("ProductAnySourceVisible"), empty);
    iService->AddProperty(iPropertyProductAnySourceVisible); // passes ownership
    iPropertyProductAnySourceType = new PropertyUint(new ParameterUint("ProductAnySourceType"), empty);
    iService->AddProperty(iPropertyProductAnySourceType); // passes ownership
}

void DvServiceLinnCoUkProduct3Cpp::EnableActionType()
{
    Zapp::Action* action = new Zapp::Action("Type");
    action->AddOutputParameter(new ParameterRelated("aType", *iPropertyProductType));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkProduct3Cpp::DoType);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkProduct3Cpp::EnableActionModel()
{
    Zapp::Action* action = new Zapp::Action("Model");
    action->AddOutputParameter(new ParameterRelated("aModel", *iPropertyProductModel));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkProduct3Cpp::DoModel);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkProduct3Cpp::EnableActionName()
{
    Zapp::Action* action = new Zapp::Action("Name");
    action->AddOutputParameter(new ParameterRelated("aName", *iPropertyProductName));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkProduct3Cpp::DoName);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkProduct3Cpp::EnableActionSetName()
{
    Zapp::Action* action = new Zapp::Action("SetName");
    action->AddInputParameter(new ParameterRelated("aName", *iPropertyProductName));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkProduct3Cpp::DoSetName);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkProduct3Cpp::EnableActionRoom()
{
    Zapp::Action* action = new Zapp::Action("Room");
    action->AddOutputParameter(new ParameterRelated("aRoom", *iPropertyProductRoom));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkProduct3Cpp::DoRoom);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkProduct3Cpp::EnableActionSetRoom()
{
    Zapp::Action* action = new Zapp::Action("SetRoom");
    action->AddInputParameter(new ParameterRelated("aRoom", *iPropertyProductRoom));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkProduct3Cpp::DoSetRoom);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkProduct3Cpp::EnableActionStandby()
{
    Zapp::Action* action = new Zapp::Action("Standby");
    action->AddOutputParameter(new ParameterRelated("aStandby", *iPropertyProductStandby));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkProduct3Cpp::DoStandby);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkProduct3Cpp::EnableActionSetStandby()
{
    Zapp::Action* action = new Zapp::Action("SetStandby");
    action->AddInputParameter(new ParameterRelated("aStandby", *iPropertyProductStandby));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkProduct3Cpp::DoSetStandby);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkProduct3Cpp::EnableActionSourceCount()
{
    Zapp::Action* action = new Zapp::Action("SourceCount");
    action->AddOutputParameter(new ParameterRelated("aSourceCount", *iPropertyProductSourceCount));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkProduct3Cpp::DoSourceCount);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkProduct3Cpp::EnableActionSourceXml()
{
    Zapp::Action* action = new Zapp::Action("SourceXml");
    action->AddOutputParameter(new ParameterRelated("aSourceXml", *iPropertyProductSourceXml));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkProduct3Cpp::DoSourceXml);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkProduct3Cpp::EnableActionSourceIndex()
{
    Zapp::Action* action = new Zapp::Action("SourceIndex");
    action->AddOutputParameter(new ParameterRelated("aSourceIndex", *iPropertyProductSourceIndex));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkProduct3Cpp::DoSourceIndex);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkProduct3Cpp::EnableActionSetSourceIndex()
{
    Zapp::Action* action = new Zapp::Action("SetSourceIndex");
    action->AddInputParameter(new ParameterRelated("aSourceIndex", *iPropertyProductSourceIndex));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkProduct3Cpp::DoSetSourceIndex);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkProduct3Cpp::EnableActionSetSourceIndexByName()
{
    Zapp::Action* action = new Zapp::Action("SetSourceIndexByName");
    action->AddInputParameter(new ParameterString("aSourceName"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkProduct3Cpp::DoSetSourceIndexByName);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkProduct3Cpp::EnableActionSetStartupSourceIndexByName()
{
    Zapp::Action* action = new Zapp::Action("SetStartupSourceIndexByName");
    action->AddInputParameter(new ParameterString("aSourceName"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkProduct3Cpp::DoSetStartupSourceIndexByName);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkProduct3Cpp::EnableActionStartupSourceIndex()
{
    Zapp::Action* action = new Zapp::Action("StartupSourceIndex");
    action->AddOutputParameter(new ParameterRelated("aSourceIndex", *iPropertyStartupSourceIndex));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkProduct3Cpp::DoStartupSourceIndex);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkProduct3Cpp::EnableActionSetStartupSourceIndex()
{
    Zapp::Action* action = new Zapp::Action("SetStartupSourceIndex");
    action->AddInputParameter(new ParameterRelated("aSourceIndex", *iPropertyStartupSourceIndex));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkProduct3Cpp::DoSetStartupSourceIndex);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkProduct3Cpp::EnableActionStartupSourceEnabled()
{
    Zapp::Action* action = new Zapp::Action("StartupSourceEnabled");
    action->AddOutputParameter(new ParameterRelated("aStartupSourceEnabled", *iPropertyStartupSourceEnabled));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkProduct3Cpp::DoStartupSourceEnabled);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkProduct3Cpp::EnableActionSetStartupSourceEnabled()
{
    Zapp::Action* action = new Zapp::Action("SetStartupSourceEnabled");
    action->AddInputParameter(new ParameterRelated("aStartupSourceEnabled", *iPropertyStartupSourceEnabled));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkProduct3Cpp::DoSetStartupSourceEnabled);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkProduct3Cpp::EnableActionSourceSystemName()
{
    Zapp::Action* action = new Zapp::Action("SourceSystemName");
    action->AddInputParameter(new ParameterRelated("aSourceIndex", *iPropertyProductSourceIndex));
    action->AddOutputParameter(new ParameterString("aSourceName"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkProduct3Cpp::DoSourceSystemName);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkProduct3Cpp::EnableActionSourceName()
{
    Zapp::Action* action = new Zapp::Action("SourceName");
    action->AddInputParameter(new ParameterRelated("aSourceIndex", *iPropertyProductSourceIndex));
    action->AddOutputParameter(new ParameterString("aSourceName"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkProduct3Cpp::DoSourceName);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkProduct3Cpp::EnableActionSetSourceName()
{
    Zapp::Action* action = new Zapp::Action("SetSourceName");
    action->AddInputParameter(new ParameterRelated("aSourceIndex", *iPropertyProductSourceIndex));
    action->AddInputParameter(new ParameterString("aSourceName"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkProduct3Cpp::DoSetSourceName);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkProduct3Cpp::EnableActionSourceType()
{
    Zapp::Action* action = new Zapp::Action("SourceType");
    action->AddInputParameter(new ParameterRelated("aSourceIndex", *iPropertyProductSourceIndex));
    action->AddOutputParameter(new ParameterString("aSourceType"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkProduct3Cpp::DoSourceType);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkProduct3Cpp::EnableActionSourceVisible()
{
    Zapp::Action* action = new Zapp::Action("SourceVisible");
    action->AddInputParameter(new ParameterRelated("aSourceIndex", *iPropertyProductSourceIndex));
    action->AddOutputParameter(new ParameterBool("aSourceVisible"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkProduct3Cpp::DoSourceVisible);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkProduct3Cpp::EnableActionSetSourceVisible()
{
    Zapp::Action* action = new Zapp::Action("SetSourceVisible");
    action->AddInputParameter(new ParameterRelated("aSourceIndex", *iPropertyProductSourceIndex));
    action->AddInputParameter(new ParameterBool("aSourceVisible"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkProduct3Cpp::DoSetSourceVisible);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkProduct3Cpp::DoType(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respaType;
    Type(aVersion, respaType);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriteraType(aInvocation, "aType");
    Brn buf_aType((const TByte*)respaType.c_str(), respaType.length());
    respWriteraType.Write(buf_aType);
    aInvocation.InvocationWriteStringEnd("aType");
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkProduct3Cpp::DoModel(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respaModel;
    Model(aVersion, respaModel);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriteraModel(aInvocation, "aModel");
    Brn buf_aModel((const TByte*)respaModel.c_str(), respaModel.length());
    respWriteraModel.Write(buf_aModel);
    aInvocation.InvocationWriteStringEnd("aModel");
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkProduct3Cpp::DoName(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respaName;
    Name(aVersion, respaName);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriteraName(aInvocation, "aName");
    Brn buf_aName((const TByte*)respaName.c_str(), respaName.length());
    respWriteraName.Write(buf_aName);
    aInvocation.InvocationWriteStringEnd("aName");
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkProduct3Cpp::DoSetName(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz buf_aName;
    aInvocation.InvocationReadString("aName", buf_aName);
    std::string aName((const char*)buf_aName.Ptr(), buf_aName.Bytes());
    aInvocation.InvocationReadEnd();
    SetName(aVersion, aName);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkProduct3Cpp::DoRoom(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceLinnCoUkProduct3Cpp::DoSetRoom(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceLinnCoUkProduct3Cpp::DoStandby(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceLinnCoUkProduct3Cpp::DoSetStandby(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    bool aStandby = aInvocation.InvocationReadBool("aStandby");
    aInvocation.InvocationReadEnd();
    SetStandby(aVersion, aStandby);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkProduct3Cpp::DoSourceCount(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respaSourceCount;
    SourceCount(aVersion, respaSourceCount);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriteraSourceCount(aInvocation, "aSourceCount");
    respWriteraSourceCount.Write(respaSourceCount);
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkProduct3Cpp::DoSourceXml(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respaSourceXml;
    SourceXml(aVersion, respaSourceXml);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriteraSourceXml(aInvocation, "aSourceXml");
    Brn buf_aSourceXml((const TByte*)respaSourceXml.c_str(), respaSourceXml.length());
    respWriteraSourceXml.Write(buf_aSourceXml);
    aInvocation.InvocationWriteStringEnd("aSourceXml");
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkProduct3Cpp::DoSourceIndex(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respaSourceIndex;
    SourceIndex(aVersion, respaSourceIndex);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriteraSourceIndex(aInvocation, "aSourceIndex");
    respWriteraSourceIndex.Write(respaSourceIndex);
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkProduct3Cpp::DoSetSourceIndex(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t aSourceIndex = aInvocation.InvocationReadUint("aSourceIndex");
    aInvocation.InvocationReadEnd();
    SetSourceIndex(aVersion, aSourceIndex);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkProduct3Cpp::DoSetSourceIndexByName(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz buf_aSourceName;
    aInvocation.InvocationReadString("aSourceName", buf_aSourceName);
    std::string aSourceName((const char*)buf_aSourceName.Ptr(), buf_aSourceName.Bytes());
    aInvocation.InvocationReadEnd();
    SetSourceIndexByName(aVersion, aSourceName);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkProduct3Cpp::DoSetStartupSourceIndexByName(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz buf_aSourceName;
    aInvocation.InvocationReadString("aSourceName", buf_aSourceName);
    std::string aSourceName((const char*)buf_aSourceName.Ptr(), buf_aSourceName.Bytes());
    aInvocation.InvocationReadEnd();
    SetStartupSourceIndexByName(aVersion, aSourceName);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkProduct3Cpp::DoStartupSourceIndex(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respaSourceIndex;
    StartupSourceIndex(aVersion, respaSourceIndex);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriteraSourceIndex(aInvocation, "aSourceIndex");
    respWriteraSourceIndex.Write(respaSourceIndex);
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkProduct3Cpp::DoSetStartupSourceIndex(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t aSourceIndex = aInvocation.InvocationReadUint("aSourceIndex");
    aInvocation.InvocationReadEnd();
    SetStartupSourceIndex(aVersion, aSourceIndex);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkProduct3Cpp::DoStartupSourceEnabled(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    bool respaStartupSourceEnabled;
    StartupSourceEnabled(aVersion, respaStartupSourceEnabled);
	aInvocation.InvocationWriteStart();
    InvocationResponseBool respWriteraStartupSourceEnabled(aInvocation, "aStartupSourceEnabled");
    respWriteraStartupSourceEnabled.Write(respaStartupSourceEnabled);
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkProduct3Cpp::DoSetStartupSourceEnabled(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    bool aStartupSourceEnabled = aInvocation.InvocationReadBool("aStartupSourceEnabled");
    aInvocation.InvocationReadEnd();
    SetStartupSourceEnabled(aVersion, aStartupSourceEnabled);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkProduct3Cpp::DoSourceSystemName(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t aSourceIndex = aInvocation.InvocationReadUint("aSourceIndex");
    aInvocation.InvocationReadEnd();
    std::string respaSourceName;
    SourceSystemName(aVersion, aSourceIndex, respaSourceName);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriteraSourceName(aInvocation, "aSourceName");
    Brn buf_aSourceName((const TByte*)respaSourceName.c_str(), respaSourceName.length());
    respWriteraSourceName.Write(buf_aSourceName);
    aInvocation.InvocationWriteStringEnd("aSourceName");
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkProduct3Cpp::DoSourceName(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t aSourceIndex = aInvocation.InvocationReadUint("aSourceIndex");
    aInvocation.InvocationReadEnd();
    std::string respaSourceName;
    SourceName(aVersion, aSourceIndex, respaSourceName);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriteraSourceName(aInvocation, "aSourceName");
    Brn buf_aSourceName((const TByte*)respaSourceName.c_str(), respaSourceName.length());
    respWriteraSourceName.Write(buf_aSourceName);
    aInvocation.InvocationWriteStringEnd("aSourceName");
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkProduct3Cpp::DoSetSourceName(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t aSourceIndex = aInvocation.InvocationReadUint("aSourceIndex");
    Brhz buf_aSourceName;
    aInvocation.InvocationReadString("aSourceName", buf_aSourceName);
    std::string aSourceName((const char*)buf_aSourceName.Ptr(), buf_aSourceName.Bytes());
    aInvocation.InvocationReadEnd();
    SetSourceName(aVersion, aSourceIndex, aSourceName);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkProduct3Cpp::DoSourceType(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t aSourceIndex = aInvocation.InvocationReadUint("aSourceIndex");
    aInvocation.InvocationReadEnd();
    std::string respaSourceType;
    SourceType(aVersion, aSourceIndex, respaSourceType);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriteraSourceType(aInvocation, "aSourceType");
    Brn buf_aSourceType((const TByte*)respaSourceType.c_str(), respaSourceType.length());
    respWriteraSourceType.Write(buf_aSourceType);
    aInvocation.InvocationWriteStringEnd("aSourceType");
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkProduct3Cpp::DoSourceVisible(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t aSourceIndex = aInvocation.InvocationReadUint("aSourceIndex");
    aInvocation.InvocationReadEnd();
    bool respaSourceVisible;
    SourceVisible(aVersion, aSourceIndex, respaSourceVisible);
	aInvocation.InvocationWriteStart();
    InvocationResponseBool respWriteraSourceVisible(aInvocation, "aSourceVisible");
    respWriteraSourceVisible.Write(respaSourceVisible);
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkProduct3Cpp::DoSetSourceVisible(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t aSourceIndex = aInvocation.InvocationReadUint("aSourceIndex");
    bool aSourceVisible = aInvocation.InvocationReadBool("aSourceVisible");
    aInvocation.InvocationReadEnd();
    SetSourceVisible(aVersion, aSourceIndex, aSourceVisible);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkProduct3Cpp::Type(uint32_t /*aVersion*/, std::string& /*aaType*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkProduct3Cpp::Model(uint32_t /*aVersion*/, std::string& /*aaModel*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkProduct3Cpp::Name(uint32_t /*aVersion*/, std::string& /*aaName*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkProduct3Cpp::SetName(uint32_t /*aVersion*/, const std::string& /*aaName*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkProduct3Cpp::Room(uint32_t /*aVersion*/, std::string& /*aaRoom*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkProduct3Cpp::SetRoom(uint32_t /*aVersion*/, const std::string& /*aaRoom*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkProduct3Cpp::Standby(uint32_t /*aVersion*/, bool& /*aaStandby*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkProduct3Cpp::SetStandby(uint32_t /*aVersion*/, bool /*aaStandby*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkProduct3Cpp::SourceCount(uint32_t /*aVersion*/, uint32_t& /*aaSourceCount*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkProduct3Cpp::SourceXml(uint32_t /*aVersion*/, std::string& /*aaSourceXml*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkProduct3Cpp::SourceIndex(uint32_t /*aVersion*/, uint32_t& /*aaSourceIndex*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkProduct3Cpp::SetSourceIndex(uint32_t /*aVersion*/, uint32_t /*aaSourceIndex*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkProduct3Cpp::SetSourceIndexByName(uint32_t /*aVersion*/, const std::string& /*aaSourceName*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkProduct3Cpp::SetStartupSourceIndexByName(uint32_t /*aVersion*/, const std::string& /*aaSourceName*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkProduct3Cpp::StartupSourceIndex(uint32_t /*aVersion*/, uint32_t& /*aaSourceIndex*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkProduct3Cpp::SetStartupSourceIndex(uint32_t /*aVersion*/, uint32_t /*aaSourceIndex*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkProduct3Cpp::StartupSourceEnabled(uint32_t /*aVersion*/, bool& /*aaStartupSourceEnabled*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkProduct3Cpp::SetStartupSourceEnabled(uint32_t /*aVersion*/, bool /*aaStartupSourceEnabled*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkProduct3Cpp::SourceSystemName(uint32_t /*aVersion*/, uint32_t /*aaSourceIndex*/, std::string& /*aaSourceName*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkProduct3Cpp::SourceName(uint32_t /*aVersion*/, uint32_t /*aaSourceIndex*/, std::string& /*aaSourceName*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkProduct3Cpp::SetSourceName(uint32_t /*aVersion*/, uint32_t /*aaSourceIndex*/, const std::string& /*aaSourceName*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkProduct3Cpp::SourceType(uint32_t /*aVersion*/, uint32_t /*aaSourceIndex*/, std::string& /*aaSourceType*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkProduct3Cpp::SourceVisible(uint32_t /*aVersion*/, uint32_t /*aaSourceIndex*/, bool& /*aaSourceVisible*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkProduct3Cpp::SetSourceVisible(uint32_t /*aVersion*/, uint32_t /*aaSourceIndex*/, bool /*aaSourceVisible*/)
{
    ASSERTS();
}

