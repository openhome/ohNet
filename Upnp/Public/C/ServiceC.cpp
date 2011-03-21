#include <C/Service.h>
#include <ZappTypes.h>
#include <C/Zapp.h>
#include <Service.h>
#include <Buffer.h>
#include <Functor.h>

using namespace Zapp;

ServiceParameter ServiceParameterCreateInt(const char* aName, int32_t aMinValue, int32_t aMaxValue, int32_t aStep)
{
    return (ServiceParameter)new ParameterInt(aName, aMinValue, aMaxValue, aStep);
}

ServiceParameter ServiceParameterCreateUint(const char* aName, uint32_t aMinValue, uint32_t aMaxValue, uint32_t aStep)
{
    return (ServiceParameter)new ParameterUint(aName, aMinValue, aMaxValue, aStep);
}

ServiceParameter ServiceParameterCreateBool(const char* aName)
{
    return (ServiceParameter)new ParameterBool(aName);
}

ServiceParameter ServiceParameterCreateString(const char* aName, char** aAllowedValues, uint32_t aCount)
{
    return (ServiceParameter)new ParameterString(aName, aAllowedValues, aCount);
}

ServiceParameter ServiceParameterCreateBinary(const char* aName)
{
    return (ServiceParameter)new ParameterBinary(aName);
}

ServiceParameter ServiceParameterCreateRelated(const char* aName, ServiceProperty aProperty)
{
    Zapp::Property* prop = reinterpret_cast<Zapp::Property*>(aProperty);
    return (ServiceParameter)new ParameterRelated(aName, *prop);
}

ServiceProperty ServicePropertyCreateIntCp(const char* aName, ZappCallback aCallback, void* aPtr)
{
    Functor functor = MakeFunctor(aPtr, aCallback);
    return (ServiceProperty)new PropertyInt(aName, functor);
}

ServiceProperty ServicePropertyCreateIntDv(ServiceParameter aParameter)
{
    Zapp::Parameter* param = reinterpret_cast<Zapp::Parameter*>(aParameter);
    return (ServiceProperty)new PropertyInt(param);
}

ServiceProperty ServicePropertyCreateUintCp(const char* aName, ZappCallback aCallback, void* aPtr)
{
    Functor functor = MakeFunctor(aPtr, aCallback);
    return (ServiceProperty)new PropertyUint(aName, functor);
}

ServiceProperty ServicePropertyCreateUintDv(ServiceParameter aParameter)
{
    Zapp::Parameter* param = reinterpret_cast<Zapp::Parameter*>(aParameter);
    return (ServiceProperty)new PropertyUint(param);
}

ServiceProperty ServicePropertyCreateBoolCp(const char* aName, ZappCallback aCallback, void* aPtr)
{
    Functor functor = MakeFunctor(aPtr, aCallback);
    return (ServiceProperty)new PropertyBool(aName, functor);
}

ServiceProperty ServicePropertyCreateBoolDv(ServiceParameter aParameter)
{
    Zapp::Parameter* param = reinterpret_cast<Zapp::Parameter*>(aParameter);
    return (ServiceProperty)new PropertyBool(param);
}

ServiceProperty ServicePropertyCreateStringCp(const char* aName, ZappCallback aCallback, void* aPtr)
{
    Functor functor = MakeFunctor(aPtr, aCallback);
    return (ServiceProperty)new PropertyString(aName, functor);
}

ServiceProperty ServicePropertyCreateStringDv(ServiceParameter aParameter)
{
    Zapp::Parameter* param = reinterpret_cast<Zapp::Parameter*>(aParameter);
    return (ServiceProperty)new PropertyString(param);
}

ServiceProperty ServicePropertyCreateBinaryCp(const char* aName, ZappCallback aCallback, void* aPtr)
{
    Functor functor = MakeFunctor(aPtr, aCallback);
    return (ServiceProperty)new PropertyBinary(aName, functor);
}

ServiceProperty ServicePropertyCreateBinaryDv(ServiceParameter aParameter)
{
    Zapp::Parameter* param = reinterpret_cast<Zapp::Parameter*>(aParameter);
    return (ServiceProperty)new PropertyBinary(param);
}

int32_t ServicePropertyValueInt(ServiceProperty aProperty)
{
    PropertyInt* prop = reinterpret_cast<PropertyInt*>(aProperty);
    ASSERT(prop != NULL);
    return prop->Value();
}

uint32_t ServicePropertyValueUint(ServiceProperty aProperty)
{
    PropertyUint* prop = reinterpret_cast<PropertyUint*>(aProperty);
    ASSERT(prop != NULL);
    return prop->Value();
}

uint32_t ServicePropertyValueBool(ServiceProperty aProperty)
{
    PropertyBool* prop = reinterpret_cast<PropertyBool*>(aProperty);
    ASSERT(prop != NULL);
    TBool val = prop->Value();
    return (val? 1 : 0);
}

const char* ServicePropertyValueString(ServiceProperty aProperty)
{
    PropertyString* prop = reinterpret_cast<PropertyString*>(aProperty);
    ASSERT(prop != NULL);
    Brhz buf(prop->Value());
    return buf.Transfer();
}

void ServicePropertyGetValueBinary(ServiceProperty aProperty, const uint8_t** aData, uint32_t* aLen)
{
    PropertyBinary* prop = reinterpret_cast<PropertyBinary*>(aProperty);
    ASSERT(prop != NULL);
    Brh val(prop->Value());
    *aLen = val.Bytes();
    *aData = (const uint8_t*)val.Extract();
}

uint32_t ServicePropertySetValueInt(ServiceProperty aProperty, int32_t aValue)
{
    PropertyInt* prop = reinterpret_cast<PropertyInt*>(aProperty);
    ASSERT(prop != NULL);
    if (prop->SetValue(aValue)) {
        return 1;
    }
    return 0;
}

uint32_t ServicePropertySetValueUint(ServiceProperty aProperty, uint32_t aValue)
{
    PropertyUint* prop = reinterpret_cast<PropertyUint*>(aProperty);
    ASSERT(prop != NULL);
    if (prop->SetValue(aValue)) {
        return 1;
    }
    return 0;
}

uint32_t ServicePropertySetValueBool(ServiceProperty aProperty, uint32_t aValue)
{
    PropertyBool* prop = reinterpret_cast<PropertyBool*>(aProperty);
    ASSERT(prop != NULL);
    TBool val = (aValue != 0);
    if (prop->SetValue(val)) {
        return 1;
    }
    return 0;
}

uint32_t ServicePropertySetValueString(ServiceProperty aProperty, const char* aValue)
{
    PropertyString* prop = reinterpret_cast<PropertyString*>(aProperty);
    ASSERT(prop != NULL);
    Brhz val(aValue);
    if (prop->SetValue(val)) {
        return 1;
    }
    return 0;
}

uint32_t ServicePropertySetValueBinary(ServiceProperty aProperty, uint8_t* aValue, uint32_t aLen)
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

ServiceAction ServiceActionCreate(const char* aName)
{
    return (ServiceAction)new Zapp::Action(aName);
}

void ServiceActionDestroy(ServiceAction aAction)
{
    Zapp::Action* action = reinterpret_cast<Zapp::Action*>(aAction);
    delete action;
}

void ServiceActionAddInputParameter(ServiceAction aAction, ServiceParameter aParameter)
{
    Zapp::Action* action = reinterpret_cast<Zapp::Action*>(aAction);
    ASSERT(action != NULL);
    Zapp::Parameter* param = reinterpret_cast<Zapp::Parameter*>(aParameter);
    ASSERT(param != NULL);
    action->AddInputParameter(param);
}

void ServiceActionAddOutputParameter(ServiceAction aAction, ServiceParameter aParameter)
{
    Zapp::Action* action = reinterpret_cast<Zapp::Action*>(aAction);
    ASSERT(action != NULL);
    Zapp::Parameter* param = reinterpret_cast<Zapp::Parameter*>(aParameter);
    ASSERT(param != NULL);
    action->AddOutputParameter(param);
}

const char* ServiceActionName(ServiceAction aAction)
{
    Zapp::Action* action = reinterpret_cast<Zapp::Action*>(aAction);
    ASSERT(action != NULL);
    return (const char*)action->Name().Ptr();
}
