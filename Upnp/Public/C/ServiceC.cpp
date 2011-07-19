#include <C/Service.h>
#include <OhNetTypes.h>
#include <C/OhNet.h>
#include <Service.h>
#include <Buffer.h>
#include <Functor.h>

using namespace OpenHome;
using namespace OpenHome::Net;

ServiceParameter STDCALL ServiceParameterCreateInt(const char* aName, int32_t aMinValue, int32_t aMaxValue, int32_t aStep)
{
    return (ServiceParameter)new ParameterInt(aName, aMinValue, aMaxValue, aStep);
}

ServiceParameter STDCALL ServiceParameterCreateUint(const char* aName, uint32_t aMinValue, uint32_t aMaxValue, uint32_t aStep)
{
    return (ServiceParameter)new ParameterUint(aName, aMinValue, aMaxValue, aStep);
}

ServiceParameter STDCALL ServiceParameterCreateBool(const char* aName)
{
    return (ServiceParameter)new ParameterBool(aName);
}

ServiceParameter STDCALL ServiceParameterCreateString(const char* aName, char** aAllowedValues, uint32_t aCount)
{
    return (ServiceParameter)new ParameterString(aName, aAllowedValues, aCount);
}

ServiceParameter STDCALL ServiceParameterCreateBinary(const char* aName)
{
    return (ServiceParameter)new ParameterBinary(aName);
}

ServiceParameter STDCALL ServiceParameterCreateRelated(const char* aName, ServiceProperty aProperty)
{
    OpenHome::Net::Property* prop = reinterpret_cast<OpenHome::Net::Property*>(aProperty);
    return (ServiceParameter)new ParameterRelated(aName, *prop);
}

void STDCALL ServicePropertyDestroy(ServiceProperty aProperty)
{
    delete reinterpret_cast<OpenHome::Net::Property*>(aProperty);
}

ServiceProperty STDCALL ServicePropertyCreateIntCp(const char* aName, OhNetCallback aCallback, void* aPtr)
{
    Functor functor = MakeFunctor(aPtr, aCallback);
    return (ServiceProperty)new PropertyInt(aName, functor);
}

ServiceProperty STDCALL ServicePropertyCreateIntDv(ServiceParameter aParameter)
{
    OpenHome::Net::Parameter* param = reinterpret_cast<OpenHome::Net::Parameter*>(aParameter);
    return (ServiceProperty)new PropertyInt(param);
}

ServiceProperty STDCALL ServicePropertyCreateUintCp(const char* aName, OhNetCallback aCallback, void* aPtr)
{
    Functor functor = MakeFunctor(aPtr, aCallback);
    return (ServiceProperty)new PropertyUint(aName, functor);
}

ServiceProperty STDCALL ServicePropertyCreateUintDv(ServiceParameter aParameter)
{
    OpenHome::Net::Parameter* param = reinterpret_cast<OpenHome::Net::Parameter*>(aParameter);
    return (ServiceProperty)new PropertyUint(param);
}

ServiceProperty STDCALL ServicePropertyCreateBoolCp(const char* aName, OhNetCallback aCallback, void* aPtr)
{
    Functor functor = MakeFunctor(aPtr, aCallback);
    return (ServiceProperty)new PropertyBool(aName, functor);
}

ServiceProperty STDCALL ServicePropertyCreateBoolDv(ServiceParameter aParameter)
{
    OpenHome::Net::Parameter* param = reinterpret_cast<OpenHome::Net::Parameter*>(aParameter);
    return (ServiceProperty)new PropertyBool(param);
}

ServiceProperty STDCALL ServicePropertyCreateStringCp(const char* aName, OhNetCallback aCallback, void* aPtr)
{
    Functor functor = MakeFunctor(aPtr, aCallback);
    return (ServiceProperty)new PropertyString(aName, functor);
}

ServiceProperty STDCALL ServicePropertyCreateStringDv(ServiceParameter aParameter)
{
    OpenHome::Net::Parameter* param = reinterpret_cast<OpenHome::Net::Parameter*>(aParameter);
    return (ServiceProperty)new PropertyString(param);
}

ServiceProperty STDCALL ServicePropertyCreateBinaryCp(const char* aName, OhNetCallback aCallback, void* aPtr)
{
    Functor functor = MakeFunctor(aPtr, aCallback);
    return (ServiceProperty)new PropertyBinary(aName, functor);
}

ServiceProperty STDCALL ServicePropertyCreateBinaryDv(ServiceParameter aParameter)
{
    OpenHome::Net::Parameter* param = reinterpret_cast<OpenHome::Net::Parameter*>(aParameter);
    return (ServiceProperty)new PropertyBinary(param);
}

int32_t STDCALL ServicePropertyValueInt(ServiceProperty aProperty)
{
    PropertyInt* prop = reinterpret_cast<PropertyInt*>(aProperty);
    ASSERT(prop != NULL);
    return prop->Value();
}

uint32_t STDCALL ServicePropertyValueUint(ServiceProperty aProperty)
{
    PropertyUint* prop = reinterpret_cast<PropertyUint*>(aProperty);
    ASSERT(prop != NULL);
    return prop->Value();
}

uint32_t STDCALL ServicePropertyValueBool(ServiceProperty aProperty)
{
    PropertyBool* prop = reinterpret_cast<PropertyBool*>(aProperty);
    ASSERT(prop != NULL);
    TBool val = prop->Value();
    return (val? 1 : 0);
}

const char* STDCALL ServicePropertyValueString(ServiceProperty aProperty)
{
    PropertyString* prop = reinterpret_cast<PropertyString*>(aProperty);
    ASSERT(prop != NULL);
    Brhz buf(prop->Value());
    return buf.Transfer();
}

void STDCALL ServicePropertyGetValueBinary(ServiceProperty aProperty, const uint8_t** aData, uint32_t* aLen)
{
    PropertyBinary* prop = reinterpret_cast<PropertyBinary*>(aProperty);
    ASSERT(prop != NULL);
    Brh val(prop->Value());
    *aLen = val.Bytes();
    *aData = (const uint8_t*)val.Extract();
}

uint32_t STDCALL ServicePropertySetValueInt(ServiceProperty aProperty, int32_t aValue)
{
    PropertyInt* prop = reinterpret_cast<PropertyInt*>(aProperty);
    ASSERT(prop != NULL);
    if (prop->SetValue(aValue)) {
        return 1;
    }
    return 0;
}

uint32_t STDCALL ServicePropertySetValueUint(ServiceProperty aProperty, uint32_t aValue)
{
    PropertyUint* prop = reinterpret_cast<PropertyUint*>(aProperty);
    ASSERT(prop != NULL);
    if (prop->SetValue(aValue)) {
        return 1;
    }
    return 0;
}

uint32_t STDCALL ServicePropertySetValueBool(ServiceProperty aProperty, uint32_t aValue)
{
    PropertyBool* prop = reinterpret_cast<PropertyBool*>(aProperty);
    ASSERT(prop != NULL);
    TBool val = (aValue != 0);
    if (prop->SetValue(val)) {
        return 1;
    }
    return 0;
}

uint32_t STDCALL ServicePropertySetValueString(ServiceProperty aProperty, const char* aValue)
{
    PropertyString* prop = reinterpret_cast<PropertyString*>(aProperty);
    ASSERT(prop != NULL);
    Brhz val(aValue);
    if (prop->SetValue(val)) {
        return 1;
    }
    return 0;
}

uint32_t STDCALL ServicePropertySetValueBinary(ServiceProperty aProperty, uint8_t* aValue, uint32_t aLen)
{
    PropertyBinary* prop = reinterpret_cast<PropertyBinary*>(aProperty);
    ASSERT(prop != NULL);
    Brh data;
    data.Set(aValue, aLen);
    if (prop->SetValue(data)) {
        return 1;
    }
    return 0;
}

ServiceAction STDCALL ServiceActionCreate(const char* aName)
{
    return (ServiceAction)new OpenHome::Net::Action(aName);
}

void STDCALL ServiceActionDestroy(ServiceAction aAction)
{
    OpenHome::Net::Action* action = reinterpret_cast<OpenHome::Net::Action*>(aAction);
    delete action;
}

void STDCALL ServiceActionAddInputParameter(ServiceAction aAction, ServiceParameter aParameter)
{
    OpenHome::Net::Action* action = reinterpret_cast<OpenHome::Net::Action*>(aAction);
    ASSERT(action != NULL);
    OpenHome::Net::Parameter* param = reinterpret_cast<OpenHome::Net::Parameter*>(aParameter);
    ASSERT(param != NULL);
    action->AddInputParameter(param);
}

void STDCALL ServiceActionAddOutputParameter(ServiceAction aAction, ServiceParameter aParameter)
{
    OpenHome::Net::Action* action = reinterpret_cast<OpenHome::Net::Action*>(aAction);
    ASSERT(action != NULL);
    OpenHome::Net::Parameter* param = reinterpret_cast<OpenHome::Net::Parameter*>(aParameter);
    ASSERT(param != NULL);
    action->AddOutputParameter(param);
}

const char* STDCALL ServiceActionName(ServiceAction aAction)
{
    OpenHome::Net::Action* action = reinterpret_cast<OpenHome::Net::Action*>(aAction);
    ASSERT(action != NULL);
    return (const char*)action->Name().Ptr();
}
