#include <C/CpService.h>
#include <C/Service.h>
#include <ZappTypes.h>
#include <C/Zapp.h>
#include <CpiService.h>
#include <Service.h>
#include <Buffer.h>
#include <FunctorAsync.h>
#include <Printer.h>

using namespace Zapp;

CpService CpServiceCreate(const char* aDomain, const char* aName, uint32_t aVersion, CpDeviceC aDevice)
{
    CpiDevice* device = reinterpret_cast<CpiDevice*>(aDevice);
    return (CpService)new CpiService(aDomain, aName, aVersion, *device);
}

void CpServiceDestroy(CpService aService)
{
    CpiService* service = reinterpret_cast<CpiService*>(aService);
    delete service;
}

CpInvocationC CpServiceInvocation(CpService aService, ServiceAction aAction, ZappCallbackAsync aCallback, void* aPtr)
{
    CpiService* service = reinterpret_cast<CpiService*>(aService);
    ASSERT(service != NULL);
    Zapp::Action* action = reinterpret_cast<Zapp::Action*>(aAction);
    ASSERT(action != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, reinterpret_cast<ZappFunctorAsync>(aCallback));
    return (CpInvocationC)service->Invocation(*action, functor);
}

void CpServiceInvokeAction(CpService aService, CpInvocationC aInvocation)
{
    CpiService* service = reinterpret_cast<CpiService*>(aService);
    ASSERT(service != NULL);
    CpiDevice& device = service->Device();
    Invocation* invocation = reinterpret_cast<Invocation*>(aInvocation);
    ASSERT(invocation != NULL);
    device.InvokeAction(*invocation);
}

ActionArgument ActionArgumentCreateIntInput(ServiceParameter aParameter, int32_t aValue)
{
    Zapp::Parameter* param = reinterpret_cast<Zapp::Parameter*>(aParameter);
    return (ActionArgument)new ArgumentInt(*param, aValue);
}

ActionArgument ActionArgumentCreateIntOutput(ServiceParameter aParameter)
{
    Zapp::Parameter* param = reinterpret_cast<Zapp::Parameter*>(aParameter);
    return (ActionArgument)new ArgumentInt(*param);
}

ActionArgument ActionArgumentCreateUintInput(ServiceParameter aParameter, uint32_t aValue)
{
    Zapp::Parameter* param = reinterpret_cast<Zapp::Parameter*>(aParameter);
    return (ActionArgument)new ArgumentUint(*param, aValue);
}

ActionArgument ActionArgumentCreateUintOutput(ServiceParameter aParameter)
{
    Zapp::Parameter* param = reinterpret_cast<Zapp::Parameter*>(aParameter);
    return (ActionArgument)new ArgumentUint(*param);
}

ActionArgument ActionArgumentCreateBoolInput(ServiceParameter aParameter, uint32_t aValue)
{
    Zapp::Parameter* param = reinterpret_cast<Zapp::Parameter*>(aParameter);
    TBool val = (aValue!=0);
    return (ActionArgument)new ArgumentBool(*param, val);
}

ActionArgument ActionArgumentCreateBoolOutput(ServiceParameter aParameter)
{
    Zapp::Parameter* param = reinterpret_cast<Zapp::Parameter*>(aParameter);
    return (ActionArgument)new ArgumentBool(*param);
}

ActionArgument ActionArgumentCreateStringInput(ServiceParameter aParameter, const char* aValue)
{
    Zapp::Parameter* param = reinterpret_cast<Zapp::Parameter*>(aParameter);
    Brn buf(aValue);
    return (ActionArgument)new ArgumentString(*param, buf);
}

ActionArgument ActionArgumentCreateStringOutput(ServiceParameter aParameter)
{
    Zapp::Parameter* param = reinterpret_cast<Zapp::Parameter*>(aParameter);
    return (ActionArgument)new ArgumentString(*param);
}

ActionArgument ActionArgumentCreateBinaryInput(ServiceParameter aParameter, const uint8_t* aData, uint32_t aLen)
{
    Zapp::Parameter* param = reinterpret_cast<Zapp::Parameter*>(aParameter);
    Brn buf(aData, aLen);
    return (ActionArgument)new ArgumentBinary(*param, buf);
}

ActionArgument ActionArgumentCreateBinaryOutput(ServiceParameter aParameter)
{
    Zapp::Parameter* param = reinterpret_cast<Zapp::Parameter*>(aParameter);
    return (ActionArgument)new ArgumentBinary(*param);
}

int32_t ActionArgumentValueInt(ActionArgument aArgument)
{
    ArgumentInt* arg = reinterpret_cast<ArgumentInt*>(aArgument);
    ASSERT(arg != NULL);
    return arg->Value();
}

uint32_t ActionArgumentValueUint(ActionArgument aArgument)
{
    ArgumentUint* arg = reinterpret_cast<ArgumentUint*>(aArgument);
    ASSERT(arg != NULL);
    return arg->Value();
}

uint32_t ActionArgumentValueBool(ActionArgument aArgument)
{
    ArgumentBool* arg = reinterpret_cast<ArgumentBool*>(aArgument);
    ASSERT(arg != NULL);
    TBool val = arg->Value();
    return (val? 1 : 0);
}

char* ActionArgumentValueString(ActionArgument aArgument)
{
    ArgumentString* arg = reinterpret_cast<ArgumentString*>(aArgument);
    ASSERT(arg != NULL);
    Brh buf;
    arg->TransferTo(buf);
    return buf.Extract();
}

void ActionArgumentGetValueBinary(ActionArgument aArgument, uint8_t** aData, uint32_t* aLen)
{
    ArgumentBinary* arg = reinterpret_cast<ArgumentBinary*>(aArgument);
    ASSERT(arg != NULL);
    Brh buf;
    arg->TransferTo(buf);
    *aLen = buf.Bytes();
    *aData = (TByte*)buf.Extract();
}

void CpInvocationAddInput(CpInvocationC aInvocation, ActionArgument aArgument)
{
    Invocation* invocation = reinterpret_cast<Invocation*>(aInvocation);
    ASSERT(invocation != NULL);
    Zapp::Argument* arg = reinterpret_cast<Zapp::Argument*>(aArgument);
    ASSERT(arg != NULL);
    invocation->AddInput(arg);
}

void CpInvocationAddOutput(CpInvocationC aInvocation, ActionArgument aArgument)
{
    Invocation* invocation = reinterpret_cast<Invocation*>(aInvocation);
    ASSERT(invocation != NULL);
    Zapp::Argument* arg = reinterpret_cast<Zapp::Argument*>(aArgument);
    ASSERT(arg != NULL);
    invocation->AddOutput(arg);
}

uint32_t CpInvocationError(CpInvocationC aInvocation)
{
    Invocation* invocation = reinterpret_cast<Invocation*>(aInvocation);
    ASSERT(invocation != NULL);
    TBool err = invocation->Error();
    return (err? 1 : 0);
}

int32_t CpInvocationOutputInt(CpInvocationC aInvocation, uint32_t aIndex)
{
    Invocation* invocation = reinterpret_cast<Invocation*>(aInvocation);
    ASSERT(invocation != NULL);
    Invocation::VectorArguments& args = invocation->OutputArguments();
    ArgumentInt* arg = static_cast<ArgumentInt*>(args[aIndex]);
    return arg->Value();
}

uint32_t CpInvocationOutputUint(CpInvocationC aInvocation, uint32_t aIndex)
{
    Invocation* invocation = reinterpret_cast<Invocation*>(aInvocation);
    ASSERT(invocation != NULL);
    Invocation::VectorArguments& args = invocation->OutputArguments();
    ArgumentUint* arg = static_cast<ArgumentUint*>(args[aIndex]);
    return arg->Value();
}

uint32_t CpInvocationOutputBool(CpInvocationC aInvocation, uint32_t aIndex)
{
    Invocation* invocation = reinterpret_cast<Invocation*>(aInvocation);
    ASSERT(invocation != NULL);
    Invocation::VectorArguments& args = invocation->OutputArguments();
    ArgumentBool* arg = static_cast<ArgumentBool*>(args[aIndex]);
    TBool val = arg->Value();
    return (val? 1 : 0);
}

char* CpInvocationOutputString(CpInvocationC aInvocation, uint32_t aIndex)
{
    Invocation* invocation = reinterpret_cast<Invocation*>(aInvocation);
    ASSERT(invocation != NULL);
    Invocation::VectorArguments& args = invocation->OutputArguments();
    ArgumentString* arg = static_cast<ArgumentString*>(args[aIndex]);
    Brh buf;
    arg->TransferTo(buf);
    return (char*)buf.Extract();
}

void CpInvocationGetOutputBinary(CpInvocationC aInvocation, uint32_t aIndex, char** aData, uint32_t* aLen)
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
