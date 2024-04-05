#include <OpenHome/Net/C/Service.h>
#include <OpenHome/Types.h>
#include <OpenHome/Os.h>
#include <OpenHome/Net/C/OhNet.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Net/Private/Globals.h>

using namespace OpenHome;
using namespace OpenHome::Net;

ServiceParameter STDCALL ServiceParameterCreateInt(const char* aName, int32_t aMinValue, int32_t aMaxValue, int32_t aStep)
{
    try {
        return (ServiceParameter)new ParameterInt(aName, aMinValue, aMaxValue, aStep);
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    return kHandleNull;
}

ServiceParameter STDCALL ServiceParameterCreateUint(const char* aName, uint32_t aMinValue, uint32_t aMaxValue, uint32_t aStep)
{
    try {
        return (ServiceParameter)new ParameterUint(aName, aMinValue, aMaxValue, aStep);
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    return kHandleNull;
}

ServiceParameter STDCALL ServiceParameterCreateBool(const char* aName)
{
    try {
        return (ServiceParameter)new ParameterBool(aName);
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    return kHandleNull;
}

ServiceParameter STDCALL ServiceParameterCreateString(const char* aName, char** aAllowedValues, uint32_t aCount)
{
    try {
        return (ServiceParameter)new ParameterString(aName, aAllowedValues, aCount);
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    return kHandleNull;
}

ServiceParameter STDCALL ServiceParameterCreateBinary(const char* aName)
{
    try {
        return (ServiceParameter)new ParameterBinary(aName);
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    return kHandleNull;
}

ServiceParameter STDCALL ServiceParameterCreateRelated(const char* aName, ServiceProperty aProperty)
{
    try {
        OpenHome::Net::Property* prop = reinterpret_cast<OpenHome::Net::Property*>(aProperty);
        ASSERT(prop != NULL);
        return (ServiceParameter)new ParameterRelated(aName, *prop);
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    return kHandleNull;
}

void STDCALL ServicePropertyDestroy(ServiceProperty aProperty)
{
    try {
        delete reinterpret_cast<OpenHome::Net::Property*>(aProperty);
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
}

ServiceProperty STDCALL ServicePropertyCreateIntCp(const char* aName, OhNetCallback aCallback, void* aPtr)
{
    try {
        Functor functor = MakeFunctor(aPtr, aCallback);
        return (ServiceProperty)new PropertyInt(aName, functor);
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    return kHandleNull;
}

ServiceProperty STDCALL ServicePropertyCreateIntDv(ServiceParameter aParameter)
{
    try {
        OpenHome::Net::Parameter* param = reinterpret_cast<OpenHome::Net::Parameter*>(aParameter);
        ASSERT(param != NULL);
        return (ServiceProperty)new PropertyInt(param);
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    return kHandleNull;
}

ServiceProperty STDCALL ServicePropertyCreateUintCp(const char* aName, OhNetCallback aCallback, void* aPtr)
{
    try {
        Functor functor = MakeFunctor(aPtr, aCallback);
        return (ServiceProperty)new PropertyUint(aName, functor);
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    return kHandleNull;
}

ServiceProperty STDCALL ServicePropertyCreateUintDv(ServiceParameter aParameter)
{
    try {
        OpenHome::Net::Parameter* param = reinterpret_cast<OpenHome::Net::Parameter*>(aParameter);
        ASSERT(param != NULL);
        return (ServiceProperty)new PropertyUint(param);
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    return kHandleNull;
}

ServiceProperty STDCALL ServicePropertyCreateBoolCp(const char* aName, OhNetCallback aCallback, void* aPtr)
{
    try {
        Functor functor = MakeFunctor(aPtr, aCallback);
        return (ServiceProperty)new PropertyBool(aName, functor);
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    return kHandleNull;
}

ServiceProperty STDCALL ServicePropertyCreateBoolDv(ServiceParameter aParameter)
{
    try {
        OpenHome::Net::Parameter* param = reinterpret_cast<OpenHome::Net::Parameter*>(aParameter);
        ASSERT(param != NULL);
        return (ServiceProperty)new PropertyBool(param);
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    return kHandleNull;
}

ServiceProperty STDCALL ServicePropertyCreateStringCp(const char* aName, OhNetCallback aCallback, void* aPtr)
{
    try {
        Functor functor = MakeFunctor(aPtr, aCallback);
        return (ServiceProperty)new PropertyString(aName, functor);
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    return kHandleNull;
}

ServiceProperty STDCALL ServicePropertyCreateStringDv(ServiceParameter aParameter)
{
    try {
        OpenHome::Net::Parameter* param = reinterpret_cast<OpenHome::Net::Parameter*>(aParameter);
        ASSERT(param != NULL);
        return (ServiceProperty)new PropertyString(param);
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    return kHandleNull;
}

ServiceProperty STDCALL ServicePropertyCreateBinaryCp(const char* aName, OhNetCallback aCallback, void* aPtr)
{
    try {
        Functor functor = MakeFunctor(aPtr, aCallback);
        return (ServiceProperty)new PropertyBinary(aName, functor);
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    return kHandleNull;
}

ServiceProperty STDCALL ServicePropertyCreateBinaryDv(ServiceParameter aParameter)
{
    try {
        OpenHome::Net::Parameter* param = reinterpret_cast<OpenHome::Net::Parameter*>(aParameter);
        ASSERT(param != NULL);
        return (ServiceProperty)new PropertyBinary(param);
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    return kHandleNull;
}

int32_t STDCALL ServicePropertyValueInt(ServiceProperty aProperty, int32_t* aValue)
{
    int32_t err = -1;
    try {
        PropertyInt* prop = reinterpret_cast<PropertyInt*>(aProperty);
        ASSERT(prop != NULL);
        *aValue = prop->Value();
        err = 0;
    }
    catch (PropertyError&) {}
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    return err;
}

int32_t STDCALL ServicePropertyValueUint(ServiceProperty aProperty, uint32_t* aValue)
{
    int32_t err = -1;
    try {
        PropertyUint* prop = reinterpret_cast<PropertyUint*>(aProperty);
        ASSERT(prop != NULL);
        *aValue = prop->Value();
        err = 0;
    }
    catch (PropertyError&) {}
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    return err;
}

int32_t STDCALL ServicePropertyValueBool(ServiceProperty aProperty, uint32_t* aValue)
{
    int32_t err = -1;
    try {
        PropertyBool* prop = reinterpret_cast<PropertyBool*>(aProperty);
        ASSERT(prop != NULL);
        TBool val;
        val = prop->Value();
        *aValue = (val? 1 : 0);
        err = 0;
    }
    catch (PropertyError&) {}
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    return err;
}

const char* STDCALL ServicePropertyValueString(ServiceProperty aProperty)
{
    try {
        // FIXME - no handling of PropertyError
        PropertyString* prop = reinterpret_cast<PropertyString*>(aProperty);
        ASSERT(prop != NULL);
        Brhz buf(prop->Value());
        return buf.Transfer();
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    return NULL;
}

int32_t STDCALL ServicePropertyGetValueString(ServiceProperty aProperty, const char** aData, uint32_t* aLen)
{
    int32_t err = -1;
    try {
        PropertyString* prop = reinterpret_cast<PropertyString*>(aProperty);
        ASSERT(prop != NULL);
        Brhz buf(prop->Value());
        err = 0;
        if (buf.Bytes() == 0) {
            *aData = NULL;
            *aLen = 0;
        }
        else {
            *aLen = buf.Bytes();
            *aData = buf.Transfer();
        }
    }
    catch (PropertyError&) {}
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    return err;
}

int32_t STDCALL ServicePropertyGetValueBinary(ServiceProperty aProperty, const uint8_t** aData, uint32_t* aLen)
{
    int32_t err = -1;
    try {
        PropertyBinary* prop = reinterpret_cast<PropertyBinary*>(aProperty);
        ASSERT(prop != NULL);
        Brh val(prop->Value());
        *aLen = val.Bytes();
        *aData = (const uint8_t*)val.Extract();
        err = 0;
    }
    catch (PropertyError&) {}
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    return err;
}

uint32_t STDCALL ServicePropertySetValueInt(ServiceProperty aProperty, int32_t aValue)
{
    try {
        PropertyInt* prop = reinterpret_cast<PropertyInt*>(aProperty);
        ASSERT(prop != NULL);
        if (prop->SetValue(aValue)) {
            return 1;
        }
        return 0;
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    return 0;
}

uint32_t STDCALL ServicePropertySetValueUint(ServiceProperty aProperty, uint32_t aValue)
{
    try {
        PropertyUint* prop = reinterpret_cast<PropertyUint*>(aProperty);
        ASSERT(prop != NULL);
        if (prop->SetValue(aValue)) {
            return 1;
        }
        return 0;
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    return 0;
}

uint32_t STDCALL ServicePropertySetValueBool(ServiceProperty aProperty, uint32_t aValue)
{
    try {
        PropertyBool* prop = reinterpret_cast<PropertyBool*>(aProperty);
        ASSERT(prop != NULL);
        TBool val = (aValue != 0);
        if (prop->SetValue(val)) {
            return 1;
        }
        return 0;
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    return 0;
}

uint32_t STDCALL ServicePropertySetValueString(ServiceProperty aProperty, const char* aValue)
{
    try {
        PropertyString* prop = reinterpret_cast<PropertyString*>(aProperty);
        ASSERT(prop != NULL);
        Brhz val(aValue);
        if (prop->SetValue(val)) {
            return 1;
        }
        return 0;
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    return 0;
}

uint32_t STDCALL ServicePropertySetValueStringAsBuffer(ServiceProperty aProperty, const char* aValue, uint32_t aLen)
{
    try {
        PropertyString* prop = reinterpret_cast<PropertyString*>(aProperty);
        ASSERT(prop != NULL);
        Brn val((TByte*)aValue, aLen);
        if (prop->SetValue(val)) {
            return 1;
        }
        return 0;
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    return 0;
}

uint32_t STDCALL ServicePropertySetValueBinary(ServiceProperty aProperty, uint8_t* aValue, uint32_t aLen)
{
    try {
        PropertyBinary* prop = reinterpret_cast<PropertyBinary*>(aProperty);
        ASSERT(prop != NULL);
        Brh data;
        data.Set(aValue, aLen);
        if (prop->SetValue(data)) {
            return 1;
        }
        return 0;
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    return 0;
}

ServiceAction STDCALL ServiceActionCreate(const char* aName)
{
    try {
        return (ServiceAction)new OpenHome::Net::Action(aName);
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    return kHandleNull;
}

void STDCALL ServiceActionDestroy(ServiceAction aAction)
{
    try {
        OpenHome::Net::Action* action = reinterpret_cast<OpenHome::Net::Action*>(aAction);
        delete action;
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
}

void STDCALL ServiceActionAddInputParameter(ServiceAction aAction, ServiceParameter aParameter)
{
    try {
        OpenHome::Net::Action* action = reinterpret_cast<OpenHome::Net::Action*>(aAction);
        ASSERT(action != NULL);
        OpenHome::Net::Parameter* param = reinterpret_cast<OpenHome::Net::Parameter*>(aParameter);
        ASSERT(param != NULL);
        action->AddInputParameter(param);
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
}

void STDCALL ServiceActionAddOutputParameter(ServiceAction aAction, ServiceParameter aParameter)
{
    try {
        OpenHome::Net::Action* action = reinterpret_cast<OpenHome::Net::Action*>(aAction);
        ASSERT(action != NULL);
        OpenHome::Net::Parameter* param = reinterpret_cast<OpenHome::Net::Parameter*>(aParameter);
        ASSERT(param != NULL);
        action->AddOutputParameter(param);
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
}

const char* STDCALL ServiceActionName(ServiceAction aAction)
{
    try {
        OpenHome::Net::Action* action = reinterpret_cast<OpenHome::Net::Action*>(aAction);
        ASSERT(action != NULL);
        return (const char*)action->Name().Ptr();
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    return NULL;
}

void STDCALL ServiceActionGetName(ServiceAction aAction, const char** aName, uint32_t* aLen)
{
    try {
        OpenHome::Net::Action* action = reinterpret_cast<OpenHome::Net::Action*>(aAction);
        ASSERT(action != NULL);
        Brn name(action->Name());
        if (name.Bytes() == 0) {
            *aName = NULL;
            *aLen = 0;
        }
        else {
            *aName = (const char*)name.Ptr();
            *aLen = name.Bytes();
        }
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
}
