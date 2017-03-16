#include <OpenHome/Net/C/DvProvider.h>
#include <OpenHome/Net/Core/DvProvider.h>
#include <OpenHome/Net/Private/DviService.h>
#include "DviDeviceC.h"
#include <OpenHome/Net/Core/DvDevice.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Os.h>

#include <string.h>

using namespace OpenHome;
using namespace OpenHome::Net;

class DvProviderWrapper : public DvProvider
{
public:
    DvProviderWrapper(DviDevice& aDevice, const TChar* aDomain, const TChar* aType, TUint aVersion) : DvProvider(aDevice, aDomain, aType, aVersion) {}
    ~DvProviderWrapper() {}
    void AddAction(OpenHome::Net::Action* aAction, FunctorDviInvocation aInvocation) { iService->AddAction(aAction, aInvocation); }
    void AddProperty(OpenHome::Net::Property* aProperty) { iService->AddProperty(aProperty); }
    bool SetPropertyInt(PropertyInt& aProperty, TInt aValue) { return DvProvider::SetPropertyInt(aProperty, aValue); }
    bool SetPropertyUint(PropertyUint& aProperty, TUint aValue) { return DvProvider::SetPropertyUint(aProperty, aValue); }
    bool SetPropertyBool(PropertyBool& aProperty, TBool aValue) { return DvProvider::SetPropertyBool(aProperty, aValue); }
    bool SetPropertyString(PropertyString& aProperty, const Brx& aValue) { return DvProvider::SetPropertyString(aProperty, aValue); }
    bool SetPropertyBinary(PropertyBinary& aProperty, const Brx& aValue) { return DvProvider::SetPropertyBinary(aProperty, aValue); }
};

static DvProviderWrapper* ProviderFromHandle(DvProviderC aProvider)
{
    DvProviderWrapper* provider = reinterpret_cast<DvProviderWrapper*>(aProvider);
    ASSERT(provider != NULL);
    return provider;
}

DvProviderC STDCALL DvProviderCreate(DvDeviceC aDevice, const char* aDomain, const char* aType, uint32_t aVersion)
{
    try {
        DvDevice* d = DviDeviceC::DeviceFromHandle(aDevice);
        DviDevice& device = d->Device();
        return (DvProviderC)new DvProviderWrapper(device, aDomain, aType, aVersion);
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    return kHandleNull;
}

void STDCALL DvProviderDestroy(DvProviderC aProvider)
{
    try {
        delete reinterpret_cast<DvProviderWrapper*>(aProvider);
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
}

void STDCALL DvProviderAddAction(DvProviderC aProvider, ServiceAction aAction, OhNetCallbackDvInvocation aCallback, void* aPtr)
{
    try {
        OhNetFunctorDviInvocation cb = reinterpret_cast<OhNetFunctorDviInvocation>(aCallback);
        FunctorDviInvocation functor = MakeFunctorDviInvocation(aPtr, cb);
        OpenHome::Net::Action* action = reinterpret_cast<OpenHome::Net::Action*>(aAction);
        ProviderFromHandle(aProvider)->AddAction(action, functor);
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
}

void STDCALL DvProviderPropertiesLock(DvProviderC aProvider)
{
    try {
        ProviderFromHandle(aProvider)->PropertiesLock();
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
}

void STDCALL DvProviderPropertiesUnlock(DvProviderC aProvider)
{
    try {
        ProviderFromHandle(aProvider)->PropertiesUnlock();
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
}

void STDCALL DvProviderAddProperty(DvProviderC aProvider, ServiceProperty aProperty)
{
    try {
        OpenHome::Net::Property* prop = reinterpret_cast<OpenHome::Net::Property*>(aProperty);
        ASSERT(prop != NULL);
        ProviderFromHandle(aProvider)->AddProperty(prop);
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
}

int32_t STDCALL DvProviderSetPropertyInt(DvProviderC aProvider, ServiceProperty aProperty, int32_t aValue, uint32_t* aChanged)
{
    try {
        PropertyInt* prop = reinterpret_cast<PropertyInt*>(aProperty);
        ASSERT(prop != NULL);
        TBool changed = ProviderFromHandle(aProvider)->SetPropertyInt(*prop, aValue);
        *aChanged = (changed? 1 : 0);
    }
    catch (ParameterValidationError&) {
        return -1;
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    return 0;
}

int32_t STDCALL DvProviderSetPropertyUint(DvProviderC aProvider, ServiceProperty aProperty, uint32_t aValue, uint32_t* aChanged)
{
    try {
        PropertyUint* prop = reinterpret_cast<PropertyUint*>(aProperty);
        ASSERT(prop != NULL);
        TBool changed = ProviderFromHandle(aProvider)->SetPropertyUint(*prop, aValue);
        *aChanged = (changed? 1 : 0);
    }
    catch (ParameterValidationError&) {
        return -1;
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    return 0;
}

int32_t STDCALL DvProviderSetPropertyBool(DvProviderC aProvider, ServiceProperty aProperty, uint32_t aValue, uint32_t* aChanged)
{
    try {
        PropertyBool* prop = reinterpret_cast<PropertyBool*>(aProperty);
        ASSERT(prop != NULL);
        TBool value = (aValue != 0);
        TBool changed = ProviderFromHandle(aProvider)->SetPropertyBool(*prop, value);
        *aChanged = (changed? 1 : 0);
    }
    catch (ParameterValidationError&) {
        return -1;
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    return 0;
}

int32_t STDCALL DvProviderSetPropertyString(DvProviderC aProvider, ServiceProperty aProperty, const char* aValue, uint32_t* aChanged)
{
    try {
        PropertyString* prop = reinterpret_cast<PropertyString*>(aProperty);
        ASSERT(prop != NULL);
        Brn value(aValue);
        TBool changed = ProviderFromHandle(aProvider)->SetPropertyString(*prop, value);
        *aChanged = (changed? 1 : 0);
    }
    catch (ParameterValidationError&) {
        return -1;
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    return 0;
}

int32_t STDCALL DvProviderSetPropertyBinary(DvProviderC aProvider, ServiceProperty aProperty, const uint8_t* aData, uint32_t aLen, uint32_t* aChanged)
{
    try {
        PropertyBinary* prop = reinterpret_cast<PropertyBinary*>(aProperty);
        ASSERT(prop != NULL);
        TBool changed;
        if (aLen == 0) {
            changed = ProviderFromHandle(aProvider)->SetPropertyBinary(*prop, Brx::Empty());
        }
        else {
            Brn data(aData, aLen);
            changed = ProviderFromHandle(aProvider)->SetPropertyBinary(*prop, data);
        }
        *aChanged = (changed? 1 : 0);
    }
    catch (ParameterValidationError&) {
        return -1;
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    return 0;
}



static IDviInvocation* InvocationFromHandle(DvInvocationC aInvocation)
{
    IDviInvocation* invocation = reinterpret_cast<IDviInvocation*>(aInvocation);
    ASSERT(invocation != NULL);
    return invocation;
}

void STDCALL DvInvocationGetVersion(DvInvocationC aInvocation, uint32_t* aVersion)
{
    try {
        IDviInvocation* invocation = InvocationFromHandle(aInvocation);
        *aVersion = invocation->Version();
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
}

void STDCALL DvInvocationGetAdapter(DvInvocationC aInvocation, TIpAddress* aAdapter)
{
    try {
        IDviInvocation* invocation = InvocationFromHandle(aInvocation);
        *aAdapter = invocation->Adapter();
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
}

void STDCALL DvInvocationGetResourceUriPrefix(DvInvocationC aInvocation, const char** aPrefix, uint32_t* aLen)
{
    try {
        IDviInvocation* invocation = InvocationFromHandle(aInvocation);
        *aPrefix = invocation->ResourceUriPrefix();
        if (*aPrefix == NULL) {
            *aLen = 0;
        }
        else {
            *aLen = (uint32_t)strlen(*aPrefix);
        }
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
}

void STDCALL DvInvocationGetClientEndpoint(DvInvocationC aInvocation, TIpAddress* aAddress, uint32_t* aPort)
{
    try {
        IDviInvocation* invocation = InvocationFromHandle(aInvocation);
        Endpoint ep = invocation->ClientEndpoint();
        *aAddress = ep.Address();
        *aPort = ep.Port();
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
}

int32_t STDCALL DvInvocationReadStart(DvInvocationC aInvocation)
{
    IDviInvocation* invocation = InvocationFromHandle(aInvocation);
    try {
        invocation->InvocationReadStart();
    }
    catch (InvocationError&) {
        return -1;
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    return 0;
}

int32_t STDCALL DvInvocationReadInt(DvInvocationC aInvocation, const char* aName, int32_t* aValue)
{
    IDviInvocation* invocation = InvocationFromHandle(aInvocation);
    try {
        *aValue = invocation->InvocationReadInt(aName);
    }
    catch (InvocationError&) {
        return -1;
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    return 0;
}

int32_t STDCALL DvInvocationReadUint(DvInvocationC aInvocation, const char* aName, uint32_t* aValue)
{
    IDviInvocation* invocation = InvocationFromHandle(aInvocation);
    try {
        *aValue = invocation->InvocationReadUint(aName);
    }
    catch (InvocationError&) {
        return -1;
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    return 0;
}

int32_t STDCALL DvInvocationReadBool(DvInvocationC aInvocation, const char* aName, uint32_t* aValue)
{
    IDviInvocation* invocation = InvocationFromHandle(aInvocation);
    try {
        TBool value = invocation->InvocationReadBool(aName);
        *aValue = (value? 1 : 0);
    }
    catch (InvocationError&) {
        return -1;
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    return 0;
}

int32_t STDCALL DvInvocationReadString(DvInvocationC aInvocation, const char* aName, char** aValue)
{
    IDviInvocation* invocation = InvocationFromHandle(aInvocation);
    try {
        Brhz value;
        invocation->InvocationReadString(aName, value);
        *aValue = value.Transfer();
    }
    catch (InvocationError&) {
        return -1;
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    return 0;
}

int32_t STDCALL DvInvocationReadStringAsBuffer(DvInvocationC aInvocation, const char* aName, char** aValue, uint32_t* aLen)
{
    IDviInvocation* invocation = InvocationFromHandle(aInvocation);
    try {
        Brhz value;
        invocation->InvocationReadString(aName, value);
        if (value.Bytes() == 0) {
            *aValue = NULL;
            *aLen = 0;
        }
        else {
            *aLen = value.Bytes();
            *aValue = value.Transfer();
        }
    }
    catch (InvocationError&) {
        return -1;
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    return 0;
}

int32_t STDCALL DvInvocationReadBinary(DvInvocationC aInvocation, const char* aName, uint8_t** aData, uint32_t* aLen)
{
    IDviInvocation* invocation = InvocationFromHandle(aInvocation);
    try {
        Brh value;
        invocation->InvocationReadBinary(aName, value);
        *aLen = value.Bytes();
        *aData = (uint8_t*)value.Extract();
    }
    catch (InvocationError&) {
        return -1;
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    return 0;
}

int32_t STDCALL DvInvocationReadEnd(DvInvocationC aInvocation)
{
    IDviInvocation* invocation = InvocationFromHandle(aInvocation);
    try {
        invocation->InvocationReadEnd();
    }
    catch (InvocationError&) {
        return -1;
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    return 0;
}

int32_t STDCALL DvInvocationReportError(DvInvocationC aInvocation, uint32_t aCode, const char* aDescription)
{
    IDviInvocation* invocation = InvocationFromHandle(aInvocation);
    try {
        Brn desc(aDescription);
        invocation->InvocationReportError(aCode, desc);
    }
    catch (WriterError&) {
        return -1;
    }
    catch (InvocationError&) {}
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    return 0;
}

int32_t STDCALL DvInvocationWriteStart(DvInvocationC aInvocation)
{
    IDviInvocation* invocation = InvocationFromHandle(aInvocation);
    try {
        invocation->InvocationWriteStart();
    }
    catch (WriterError&) {
        return -1;
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    return 0;
}

int32_t STDCALL DvInvocationWriteInt(DvInvocationC aInvocation, const char* aName, int32_t aValue)
{
    IDviInvocation* invocation = InvocationFromHandle(aInvocation);
    try {
        invocation->InvocationWriteInt(aName, aValue);
    }
    catch (WriterError&) {
        return -1;
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    return 0;
}

int32_t STDCALL DvInvocationWriteUint(DvInvocationC aInvocation, const char* aName, uint32_t aValue)
{
    IDviInvocation* invocation = InvocationFromHandle(aInvocation);
    try {
        invocation->InvocationWriteUint(aName, aValue);
    }
    catch (WriterError&) {
        return -1;
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    return 0;
}

int32_t STDCALL DvInvocationWriteBool(DvInvocationC aInvocation, const char* aName, uint32_t aValue)
{
    IDviInvocation* invocation = InvocationFromHandle(aInvocation);
    try {
        TBool value = (aValue != 0);
        invocation->InvocationWriteBool(aName, value);
    }
    catch (WriterError&) {
        return -1;
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    return 0;
}

int32_t STDCALL DvInvocationWriteStringStart(DvInvocationC aInvocation, const char* aName)
{
    IDviInvocation* invocation = InvocationFromHandle(aInvocation);
    try {
        invocation->InvocationWriteStringStart(aName);
    }
    catch (WriterError&) {
        return -1;
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    return 0;
}

int32_t STDCALL DvInvocationWriteString(DvInvocationC aInvocation, const char* aValue)
{
    IDviInvocation* invocation = InvocationFromHandle(aInvocation);
    try {
        Brn value(aValue);
        invocation->InvocationWriteString(value);
    }
    catch (WriterError&) {
        return -1;
    }
    catch (ParameterValidationError&) {
        return -1;
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    return 0;
}

int32_t STDCALL DvInvocationWriteStringAsBuffer(DvInvocationC aInvocation, const char* aValue, uint32_t aLen)
{
    IDviInvocation* invocation = InvocationFromHandle(aInvocation);
    try {
        Brn value((TByte*)aValue, aLen);
        invocation->InvocationWriteString(value);
    }
    catch (WriterError&) {
        return -1;
    }
    catch (ParameterValidationError&) {
        return -1;
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    return 0;
}

int32_t STDCALL DvInvocationWriteStringEnd(DvInvocationC aInvocation, const char* aName)
{
    IDviInvocation* invocation = InvocationFromHandle(aInvocation);
    try {
        invocation->InvocationWriteStringEnd(aName);
    }
    catch (WriterError&) {
        return -1;
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    return 0;
}

int32_t STDCALL DvInvocationWriteBinaryStart(DvInvocationC aInvocation, const char* aName)
{
    IDviInvocation* invocation = InvocationFromHandle(aInvocation);
    try {
        invocation->InvocationWriteBinaryStart(aName);
    }
    catch (WriterError&) {
        return -1;
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    return 0;
}

int32_t STDCALL DvInvocationWriteBinary(DvInvocationC aInvocation, const uint8_t* aData, uint32_t aLen)
{
    IDviInvocation* invocation = InvocationFromHandle(aInvocation);
    try {
        Brn data(aData, aLen);
        invocation->InvocationWriteBinary(data);
    }
    catch (WriterError&) {
        return -1;
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    return 0;
}

int32_t STDCALL DvInvocationWriteBinaryEnd(DvInvocationC aInvocation, const char* aName)
{
    IDviInvocation* invocation = InvocationFromHandle(aInvocation);
    try {
        invocation->InvocationWriteBinaryEnd(aName);
    }
    catch (WriterError&) {
        return -1;
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    return 0;
}

int32_t STDCALL DvInvocationWriteEnd(DvInvocationC aInvocation)
{
    IDviInvocation* invocation = InvocationFromHandle(aInvocation);
    try {
        invocation->InvocationWriteEnd();
    }
    catch (WriterError&) {
        return -1;
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    return 0;
}
