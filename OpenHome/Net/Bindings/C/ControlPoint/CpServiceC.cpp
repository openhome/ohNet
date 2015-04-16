#include <OpenHome/Net/C/CpService.h>
#include <OpenHome/Net/C/Service.h>
#include <OpenHome/Types.h>
#include <OpenHome/Net/C/OhNet.h>
#include <OpenHome/Net/Private/CpiService.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Core/FunctorAsync.h>
#include <OpenHome/Private/Printer.h>

using namespace OpenHome;
using namespace OpenHome::Net;

CpService STDCALL CpServiceCreate(const char* aDomain, const char* aName, uint32_t aVersion, CpDeviceC aDevice)
{
    CpiDevice* device = reinterpret_cast<CpiDevice*>(aDevice);
    ASSERT(device != NULL);
    return (CpService)new CpiService(aDomain, aName, aVersion, *device);
}

void STDCALL CpServiceDestroy(CpService aService)
{
    CpiService* service = reinterpret_cast<CpiService*>(aService);
    delete service;
}

CpInvocationC STDCALL CpServiceInvocation(CpService aService, ServiceAction aAction, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpiService* service = reinterpret_cast<CpiService*>(aService);
    ASSERT(service != NULL);
    OpenHome::Net::Action* action = reinterpret_cast<OpenHome::Net::Action*>(aAction);
    ASSERT(action != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, reinterpret_cast<OhNetFunctorAsync>(aCallback));
    return (CpInvocationC)service->Invocation(*action, functor);
}

void STDCALL CpServiceInvokeAction(CpService aService, CpInvocationC aInvocation)
{
    CpiService* service = reinterpret_cast<CpiService*>(aService);
    ASSERT(service != NULL);
    CpiDevice& device = service->Device();
    Invocation* invocation = reinterpret_cast<Invocation*>(aInvocation);
    ASSERT(invocation != NULL);
    device.InvokeAction(*invocation);
}

ActionArgument STDCALL ActionArgumentCreateIntInput(ServiceParameter aParameter, int32_t aValue)
{
    OpenHome::Net::Parameter* param = reinterpret_cast<OpenHome::Net::Parameter*>(aParameter);
    ASSERT(param != NULL);
    return (ActionArgument)new ArgumentInt(*param, aValue);
}

ActionArgument STDCALL ActionArgumentCreateIntOutput(ServiceParameter aParameter)
{
    OpenHome::Net::Parameter* param = reinterpret_cast<OpenHome::Net::Parameter*>(aParameter);
    ASSERT(param != NULL);
    return (ActionArgument)new ArgumentInt(*param);
}

ActionArgument STDCALL ActionArgumentCreateUintInput(ServiceParameter aParameter, uint32_t aValue)
{
    OpenHome::Net::Parameter* param = reinterpret_cast<OpenHome::Net::Parameter*>(aParameter);
    ASSERT(param != NULL);
    return (ActionArgument)new ArgumentUint(*param, aValue);
}

ActionArgument STDCALL ActionArgumentCreateUintOutput(ServiceParameter aParameter)
{
    OpenHome::Net::Parameter* param = reinterpret_cast<OpenHome::Net::Parameter*>(aParameter);
    ASSERT(param != NULL);
    return (ActionArgument)new ArgumentUint(*param);
}

ActionArgument STDCALL ActionArgumentCreateBoolInput(ServiceParameter aParameter, uint32_t aValue)
{
    OpenHome::Net::Parameter* param = reinterpret_cast<OpenHome::Net::Parameter*>(aParameter);
    ASSERT(param != NULL);
    TBool val = (aValue!=0);
    return (ActionArgument)new ArgumentBool(*param, val);
}

ActionArgument STDCALL ActionArgumentCreateBoolOutput(ServiceParameter aParameter)
{
    OpenHome::Net::Parameter* param = reinterpret_cast<OpenHome::Net::Parameter*>(aParameter);
    ASSERT(param != NULL);
    return (ActionArgument)new ArgumentBool(*param);
}

ActionArgument STDCALL ActionArgumentCreateStringInput(ServiceParameter aParameter, const char* aValue)
{
    OpenHome::Net::Parameter* param = reinterpret_cast<OpenHome::Net::Parameter*>(aParameter);
    ASSERT(param != NULL);
    Brn buf(aValue);
    return (ActionArgument)new ArgumentString(*param, buf);
}

ActionArgument STDCALL ActionArgumentCreateStringOutput(ServiceParameter aParameter)
{
    OpenHome::Net::Parameter* param = reinterpret_cast<OpenHome::Net::Parameter*>(aParameter);
    ASSERT(param != NULL);
    return (ActionArgument)new ArgumentString(*param);
}

ActionArgument STDCALL ActionArgumentCreateBinaryInput(ServiceParameter aParameter, const uint8_t* aData, uint32_t aLen)
{
    OpenHome::Net::Parameter* param = reinterpret_cast<OpenHome::Net::Parameter*>(aParameter);
    ASSERT(param != NULL);
    Brn buf(aData, aLen);
    return (ActionArgument)new ArgumentBinary(*param, buf);
}

ActionArgument STDCALL ActionArgumentCreateBinaryOutput(ServiceParameter aParameter)
{
    OpenHome::Net::Parameter* param = reinterpret_cast<OpenHome::Net::Parameter*>(aParameter);
    ASSERT(param != NULL);
    return (ActionArgument)new ArgumentBinary(*param);
}

int32_t STDCALL ActionArgumentValueInt(ActionArgument aArgument)
{
    ArgumentInt* arg = reinterpret_cast<ArgumentInt*>(aArgument);
    ASSERT(arg != NULL);
    return arg->Value();
}

uint32_t STDCALL ActionArgumentValueUint(ActionArgument aArgument)
{
    ArgumentUint* arg = reinterpret_cast<ArgumentUint*>(aArgument);
    ASSERT(arg != NULL);
    return arg->Value();
}

uint32_t STDCALL ActionArgumentValueBool(ActionArgument aArgument)
{
    ArgumentBool* arg = reinterpret_cast<ArgumentBool*>(aArgument);
    ASSERT(arg != NULL);
    TBool val = arg->Value();
    return (val? 1 : 0);
}

char* STDCALL ActionArgumentValueString(ActionArgument aArgument)
{
    ArgumentString* arg = reinterpret_cast<ArgumentString*>(aArgument);
    ASSERT(arg != NULL);
    Brh buf;
    arg->TransferTo(buf);
    return buf.Extract();
}

void STDCALL ActionArgumentGetValueString(ActionArgument aArgument, char** aData, uint32_t* aLen)
{
    ArgumentString* arg = reinterpret_cast<ArgumentString*>(aArgument);
    ASSERT(arg != NULL);
    Brh buf;
    arg->TransferTo(buf);
    if (buf.Bytes() == 0) {
        *aData = NULL;
        *aLen = 0;
    }
    else {
        *aLen = buf.Bytes();
        *aData = (char*)buf.Extract();
    }
}

void STDCALL ActionArgumentGetValueBinary(ActionArgument aArgument, uint8_t** aData, uint32_t* aLen)
{
    ArgumentBinary* arg = reinterpret_cast<ArgumentBinary*>(aArgument);
    ASSERT(arg != NULL);
    Brh buf;
    arg->TransferTo(buf);
    *aLen = buf.Bytes();
    *aData = (TByte*)buf.Extract();
}

void STDCALL CpInvocationAddInput(CpInvocationC aInvocation, ActionArgument aArgument)
{
    Invocation* invocation = reinterpret_cast<Invocation*>(aInvocation);
    ASSERT(invocation != NULL);
    OpenHome::Net::Argument* arg = reinterpret_cast<OpenHome::Net::Argument*>(aArgument);
    ASSERT(arg != NULL);
    invocation->AddInput(arg);
}

void STDCALL CpInvocationAddOutput(CpInvocationC aInvocation, ActionArgument aArgument)
{
    Invocation* invocation = reinterpret_cast<Invocation*>(aInvocation);
    ASSERT(invocation != NULL);
    OpenHome::Net::Argument* arg = reinterpret_cast<OpenHome::Net::Argument*>(aArgument);
    ASSERT(arg != NULL);
    invocation->AddOutput(arg);
}

uint32_t STDCALL CpInvocationError(CpInvocationC aInvocation, uint32_t* aErrorCode, const char** aErrorDesc)
{
    Invocation* invocation = reinterpret_cast<Invocation*>(aInvocation);
    ASSERT(invocation != NULL);
    Error::ELevel ignore;
    TUint code;
    const TChar* desc;
    if (invocation->Error(ignore, code, desc)) {
        *aErrorCode = code;
        *aErrorDesc = desc;
        return 1;
    }
    *aErrorCode = 0;
    *aErrorDesc = NULL;
    return 0;
}

int32_t STDCALL CpInvocationOutputInt(CpInvocationC aInvocation, uint32_t aIndex)
{
    Invocation* invocation = reinterpret_cast<Invocation*>(aInvocation);
    ASSERT(invocation != NULL);
    Invocation::VectorArguments& args = invocation->OutputArguments();
    ArgumentInt* arg = static_cast<ArgumentInt*>(args[aIndex]);
    return arg->Value();
}

uint32_t STDCALL CpInvocationOutputUint(CpInvocationC aInvocation, uint32_t aIndex)
{
    Invocation* invocation = reinterpret_cast<Invocation*>(aInvocation);
    ASSERT(invocation != NULL);
    Invocation::VectorArguments& args = invocation->OutputArguments();
    ArgumentUint* arg = static_cast<ArgumentUint*>(args[aIndex]);
    return arg->Value();
}

uint32_t STDCALL CpInvocationOutputBool(CpInvocationC aInvocation, uint32_t aIndex)
{
    Invocation* invocation = reinterpret_cast<Invocation*>(aInvocation);
    ASSERT(invocation != NULL);
    Invocation::VectorArguments& args = invocation->OutputArguments();
    ArgumentBool* arg = static_cast<ArgumentBool*>(args[aIndex]);
    TBool val = arg->Value();
    return (val? 1 : 0);
}

char* STDCALL CpInvocationOutputString(CpInvocationC aInvocation, uint32_t aIndex)
{
    Invocation* invocation = reinterpret_cast<Invocation*>(aInvocation);
    ASSERT(invocation != NULL);
    Invocation::VectorArguments& args = invocation->OutputArguments();
    ArgumentString* arg = static_cast<ArgumentString*>(args[aIndex]);
    Brh buf;
    arg->TransferTo(buf);
    return (char*)buf.Extract();
}

void STDCALL CpInvocationGetOutputString(CpInvocationC aInvocation, uint32_t aIndex, char** aData, uint32_t* aLen)
{
    Invocation* invocation = reinterpret_cast<Invocation*>(aInvocation);
    ASSERT(invocation != NULL);
    Invocation::VectorArguments& args = invocation->OutputArguments();
    ArgumentString* arg = static_cast<ArgumentString*>(args[aIndex]);
    Brh buf;
    arg->TransferTo(buf);
    if (buf.Bytes() == 0) {
        *aData = NULL;
        *aLen = 0;
    }
    else {
        *aLen = buf.Bytes();
        *aData = buf.Extract();
    }
}

void STDCALL CpInvocationGetOutputBinary(CpInvocationC aInvocation, uint32_t aIndex, char** aData, uint32_t* aLen)
{
    Invocation* invocation = reinterpret_cast<Invocation*>(aInvocation);
    ASSERT(invocation != NULL);
    Invocation::VectorArguments& args = invocation->OutputArguments();
    ArgumentBinary* arg = static_cast<ArgumentBinary*>(args[aIndex]);
    Brh buf;
    arg->TransferTo(buf);
    *aLen = buf.Bytes();
    *aData = buf.Extract();
}
