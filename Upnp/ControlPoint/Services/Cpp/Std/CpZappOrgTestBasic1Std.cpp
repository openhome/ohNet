#include <Std/CpZappOrgTestBasic1.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Buffer.h>
#include <Std/CpDevice.h>

#include <string>

using namespace Zapp;


class SyncIncrementZappOrgTestBasic1Cpp : public SyncProxyAction
{
public:
    SyncIncrementZappOrgTestBasic1Cpp(CpProxyZappOrgTestBasic1Cpp& aService, uint32_t& aResult);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestBasic1Cpp& iService;
    uint32_t& iResult;
};

SyncIncrementZappOrgTestBasic1Cpp::SyncIncrementZappOrgTestBasic1Cpp(CpProxyZappOrgTestBasic1Cpp& aService, uint32_t& aResult)
    : iService(aService)
    , iResult(aResult)
{
}

void SyncIncrementZappOrgTestBasic1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndIncrement(aAsync, iResult);
}


class SyncDecrementZappOrgTestBasic1Cpp : public SyncProxyAction
{
public:
    SyncDecrementZappOrgTestBasic1Cpp(CpProxyZappOrgTestBasic1Cpp& aService, int32_t& aResult);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestBasic1Cpp& iService;
    int32_t& iResult;
};

SyncDecrementZappOrgTestBasic1Cpp::SyncDecrementZappOrgTestBasic1Cpp(CpProxyZappOrgTestBasic1Cpp& aService, int32_t& aResult)
    : iService(aService)
    , iResult(aResult)
{
}

void SyncDecrementZappOrgTestBasic1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndDecrement(aAsync, iResult);
}


class SyncToggleZappOrgTestBasic1Cpp : public SyncProxyAction
{
public:
    SyncToggleZappOrgTestBasic1Cpp(CpProxyZappOrgTestBasic1Cpp& aService, bool& aResult);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestBasic1Cpp& iService;
    bool& iResult;
};

SyncToggleZappOrgTestBasic1Cpp::SyncToggleZappOrgTestBasic1Cpp(CpProxyZappOrgTestBasic1Cpp& aService, bool& aResult)
    : iService(aService)
    , iResult(aResult)
{
}

void SyncToggleZappOrgTestBasic1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndToggle(aAsync, iResult);
}


class SyncEchoStringZappOrgTestBasic1Cpp : public SyncProxyAction
{
public:
    SyncEchoStringZappOrgTestBasic1Cpp(CpProxyZappOrgTestBasic1Cpp& aService, std::string& aResult);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestBasic1Cpp& iService;
    std::string& iResult;
};

SyncEchoStringZappOrgTestBasic1Cpp::SyncEchoStringZappOrgTestBasic1Cpp(CpProxyZappOrgTestBasic1Cpp& aService, std::string& aResult)
    : iService(aService)
    , iResult(aResult)
{
}

void SyncEchoStringZappOrgTestBasic1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndEchoString(aAsync, iResult);
}


class SyncEchoBinaryZappOrgTestBasic1Cpp : public SyncProxyAction
{
public:
    SyncEchoBinaryZappOrgTestBasic1Cpp(CpProxyZappOrgTestBasic1Cpp& aService, std::string& aResult);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestBasic1Cpp& iService;
    std::string& iResult;
};

SyncEchoBinaryZappOrgTestBasic1Cpp::SyncEchoBinaryZappOrgTestBasic1Cpp(CpProxyZappOrgTestBasic1Cpp& aService, std::string& aResult)
    : iService(aService)
    , iResult(aResult)
{
}

void SyncEchoBinaryZappOrgTestBasic1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndEchoBinary(aAsync, iResult);
}


class SyncSetUintZappOrgTestBasic1Cpp : public SyncProxyAction
{
public:
    SyncSetUintZappOrgTestBasic1Cpp(CpProxyZappOrgTestBasic1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestBasic1Cpp& iService;
};

SyncSetUintZappOrgTestBasic1Cpp::SyncSetUintZappOrgTestBasic1Cpp(CpProxyZappOrgTestBasic1Cpp& aService)
    : iService(aService)
{
}

void SyncSetUintZappOrgTestBasic1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetUint(aAsync);
}


class SyncGetUintZappOrgTestBasic1Cpp : public SyncProxyAction
{
public:
    SyncGetUintZappOrgTestBasic1Cpp(CpProxyZappOrgTestBasic1Cpp& aService, uint32_t& aValueUint);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestBasic1Cpp& iService;
    uint32_t& iValueUint;
};

SyncGetUintZappOrgTestBasic1Cpp::SyncGetUintZappOrgTestBasic1Cpp(CpProxyZappOrgTestBasic1Cpp& aService, uint32_t& aValueUint)
    : iService(aService)
    , iValueUint(aValueUint)
{
}

void SyncGetUintZappOrgTestBasic1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetUint(aAsync, iValueUint);
}


class SyncSetIntZappOrgTestBasic1Cpp : public SyncProxyAction
{
public:
    SyncSetIntZappOrgTestBasic1Cpp(CpProxyZappOrgTestBasic1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestBasic1Cpp& iService;
};

SyncSetIntZappOrgTestBasic1Cpp::SyncSetIntZappOrgTestBasic1Cpp(CpProxyZappOrgTestBasic1Cpp& aService)
    : iService(aService)
{
}

void SyncSetIntZappOrgTestBasic1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetInt(aAsync);
}


class SyncGetIntZappOrgTestBasic1Cpp : public SyncProxyAction
{
public:
    SyncGetIntZappOrgTestBasic1Cpp(CpProxyZappOrgTestBasic1Cpp& aService, int32_t& aValueInt);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestBasic1Cpp& iService;
    int32_t& iValueInt;
};

SyncGetIntZappOrgTestBasic1Cpp::SyncGetIntZappOrgTestBasic1Cpp(CpProxyZappOrgTestBasic1Cpp& aService, int32_t& aValueInt)
    : iService(aService)
    , iValueInt(aValueInt)
{
}

void SyncGetIntZappOrgTestBasic1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetInt(aAsync, iValueInt);
}


class SyncSetBoolZappOrgTestBasic1Cpp : public SyncProxyAction
{
public:
    SyncSetBoolZappOrgTestBasic1Cpp(CpProxyZappOrgTestBasic1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestBasic1Cpp& iService;
};

SyncSetBoolZappOrgTestBasic1Cpp::SyncSetBoolZappOrgTestBasic1Cpp(CpProxyZappOrgTestBasic1Cpp& aService)
    : iService(aService)
{
}

void SyncSetBoolZappOrgTestBasic1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetBool(aAsync);
}


class SyncGetBoolZappOrgTestBasic1Cpp : public SyncProxyAction
{
public:
    SyncGetBoolZappOrgTestBasic1Cpp(CpProxyZappOrgTestBasic1Cpp& aService, bool& aValueBool);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestBasic1Cpp& iService;
    bool& iValueBool;
};

SyncGetBoolZappOrgTestBasic1Cpp::SyncGetBoolZappOrgTestBasic1Cpp(CpProxyZappOrgTestBasic1Cpp& aService, bool& aValueBool)
    : iService(aService)
    , iValueBool(aValueBool)
{
}

void SyncGetBoolZappOrgTestBasic1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetBool(aAsync, iValueBool);
}


class SyncSetMultipleZappOrgTestBasic1Cpp : public SyncProxyAction
{
public:
    SyncSetMultipleZappOrgTestBasic1Cpp(CpProxyZappOrgTestBasic1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestBasic1Cpp& iService;
};

SyncSetMultipleZappOrgTestBasic1Cpp::SyncSetMultipleZappOrgTestBasic1Cpp(CpProxyZappOrgTestBasic1Cpp& aService)
    : iService(aService)
{
}

void SyncSetMultipleZappOrgTestBasic1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetMultiple(aAsync);
}


class SyncSetStringZappOrgTestBasic1Cpp : public SyncProxyAction
{
public:
    SyncSetStringZappOrgTestBasic1Cpp(CpProxyZappOrgTestBasic1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestBasic1Cpp& iService;
};

SyncSetStringZappOrgTestBasic1Cpp::SyncSetStringZappOrgTestBasic1Cpp(CpProxyZappOrgTestBasic1Cpp& aService)
    : iService(aService)
{
}

void SyncSetStringZappOrgTestBasic1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetString(aAsync);
}


class SyncGetStringZappOrgTestBasic1Cpp : public SyncProxyAction
{
public:
    SyncGetStringZappOrgTestBasic1Cpp(CpProxyZappOrgTestBasic1Cpp& aService, std::string& aValueStr);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestBasic1Cpp& iService;
    std::string& iValueStr;
};

SyncGetStringZappOrgTestBasic1Cpp::SyncGetStringZappOrgTestBasic1Cpp(CpProxyZappOrgTestBasic1Cpp& aService, std::string& aValueStr)
    : iService(aService)
    , iValueStr(aValueStr)
{
}

void SyncGetStringZappOrgTestBasic1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetString(aAsync, iValueStr);
}


class SyncSetBinaryZappOrgTestBasic1Cpp : public SyncProxyAction
{
public:
    SyncSetBinaryZappOrgTestBasic1Cpp(CpProxyZappOrgTestBasic1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestBasic1Cpp& iService;
};

SyncSetBinaryZappOrgTestBasic1Cpp::SyncSetBinaryZappOrgTestBasic1Cpp(CpProxyZappOrgTestBasic1Cpp& aService)
    : iService(aService)
{
}

void SyncSetBinaryZappOrgTestBasic1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetBinary(aAsync);
}


class SyncGetBinaryZappOrgTestBasic1Cpp : public SyncProxyAction
{
public:
    SyncGetBinaryZappOrgTestBasic1Cpp(CpProxyZappOrgTestBasic1Cpp& aService, std::string& aValueBin);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestBasic1Cpp& iService;
    std::string& iValueBin;
};

SyncGetBinaryZappOrgTestBasic1Cpp::SyncGetBinaryZappOrgTestBasic1Cpp(CpProxyZappOrgTestBasic1Cpp& aService, std::string& aValueBin)
    : iService(aService)
    , iValueBin(aValueBin)
{
}

void SyncGetBinaryZappOrgTestBasic1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetBinary(aAsync, iValueBin);
}


CpProxyZappOrgTestBasic1Cpp::CpProxyZappOrgTestBasic1Cpp(CpDeviceCpp& aDevice)
{
    iService = new CpiService("zapp-org", "TestBasic", 1, aDevice.Device());
    Zapp::Parameter* param;

    iActionIncrement = new Action("Increment");
    param = new Zapp::ParameterUint("Value");
    iActionIncrement->AddInputParameter(param);
    param = new Zapp::ParameterUint("Result");
    iActionIncrement->AddOutputParameter(param);

    iActionDecrement = new Action("Decrement");
    param = new Zapp::ParameterInt("Value");
    iActionDecrement->AddInputParameter(param);
    param = new Zapp::ParameterInt("Result");
    iActionDecrement->AddOutputParameter(param);

    iActionToggle = new Action("Toggle");
    param = new Zapp::ParameterBool("Value");
    iActionToggle->AddInputParameter(param);
    param = new Zapp::ParameterBool("Result");
    iActionToggle->AddOutputParameter(param);

    iActionEchoString = new Action("EchoString");
    param = new Zapp::ParameterString("Value");
    iActionEchoString->AddInputParameter(param);
    param = new Zapp::ParameterString("Result");
    iActionEchoString->AddOutputParameter(param);

    iActionEchoBinary = new Action("EchoBinary");
    param = new Zapp::ParameterBinary("Value");
    iActionEchoBinary->AddInputParameter(param);
    param = new Zapp::ParameterBinary("Result");
    iActionEchoBinary->AddOutputParameter(param);

    iActionSetUint = new Action("SetUint");
    param = new Zapp::ParameterUint("ValueUint");
    iActionSetUint->AddInputParameter(param);

    iActionGetUint = new Action("GetUint");
    param = new Zapp::ParameterUint("ValueUint");
    iActionGetUint->AddOutputParameter(param);

    iActionSetInt = new Action("SetInt");
    param = new Zapp::ParameterInt("ValueInt");
    iActionSetInt->AddInputParameter(param);

    iActionGetInt = new Action("GetInt");
    param = new Zapp::ParameterInt("ValueInt");
    iActionGetInt->AddOutputParameter(param);

    iActionSetBool = new Action("SetBool");
    param = new Zapp::ParameterBool("ValueBool");
    iActionSetBool->AddInputParameter(param);

    iActionGetBool = new Action("GetBool");
    param = new Zapp::ParameterBool("ValueBool");
    iActionGetBool->AddOutputParameter(param);

    iActionSetMultiple = new Action("SetMultiple");
    param = new Zapp::ParameterUint("ValueUint");
    iActionSetMultiple->AddInputParameter(param);
    param = new Zapp::ParameterInt("ValueInt");
    iActionSetMultiple->AddInputParameter(param);
    param = new Zapp::ParameterBool("ValueBool");
    iActionSetMultiple->AddInputParameter(param);

    iActionSetString = new Action("SetString");
    param = new Zapp::ParameterString("ValueStr");
    iActionSetString->AddInputParameter(param);

    iActionGetString = new Action("GetString");
    param = new Zapp::ParameterString("ValueStr");
    iActionGetString->AddOutputParameter(param);

    iActionSetBinary = new Action("SetBinary");
    param = new Zapp::ParameterBinary("ValueBin");
    iActionSetBinary->AddInputParameter(param);

    iActionGetBinary = new Action("GetBinary");
    param = new Zapp::ParameterBinary("ValueBin");
    iActionGetBinary->AddOutputParameter(param);

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyZappOrgTestBasic1Cpp::VarUintPropertyChanged);
    iVarUint = new PropertyUint("VarUint", functor);
    iService->AddProperty(iVarUint);
    functor = MakeFunctor(*this, &CpProxyZappOrgTestBasic1Cpp::VarIntPropertyChanged);
    iVarInt = new PropertyInt("VarInt", functor);
    iService->AddProperty(iVarInt);
    functor = MakeFunctor(*this, &CpProxyZappOrgTestBasic1Cpp::VarBoolPropertyChanged);
    iVarBool = new PropertyBool("VarBool", functor);
    iService->AddProperty(iVarBool);
    functor = MakeFunctor(*this, &CpProxyZappOrgTestBasic1Cpp::VarStrPropertyChanged);
    iVarStr = new PropertyString("VarStr", functor);
    iService->AddProperty(iVarStr);
    functor = MakeFunctor(*this, &CpProxyZappOrgTestBasic1Cpp::VarBinPropertyChanged);
    iVarBin = new PropertyBinary("VarBin", functor);
    iService->AddProperty(iVarBin);
}

CpProxyZappOrgTestBasic1Cpp::~CpProxyZappOrgTestBasic1Cpp()
{
    delete iService;
    delete iActionIncrement;
    delete iActionDecrement;
    delete iActionToggle;
    delete iActionEchoString;
    delete iActionEchoBinary;
    delete iActionSetUint;
    delete iActionGetUint;
    delete iActionSetInt;
    delete iActionGetInt;
    delete iActionSetBool;
    delete iActionGetBool;
    delete iActionSetMultiple;
    delete iActionSetString;
    delete iActionGetString;
    delete iActionSetBinary;
    delete iActionGetBinary;
}

void CpProxyZappOrgTestBasic1Cpp::SyncIncrement(uint32_t aValue, uint32_t& aResult)
{
    SyncIncrementZappOrgTestBasic1Cpp sync(*this, aResult);
    BeginIncrement(aValue, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestBasic1Cpp::BeginIncrement(uint32_t aValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionIncrement, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionIncrement->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aValue));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionIncrement->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyZappOrgTestBasic1Cpp::EndIncrement(IAsync& aAsync, uint32_t& aResult)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Increment"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aResult = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyZappOrgTestBasic1Cpp::SyncDecrement(int32_t aValue, int32_t& aResult)
{
    SyncDecrementZappOrgTestBasic1Cpp sync(*this, aResult);
    BeginDecrement(aValue, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestBasic1Cpp::BeginDecrement(int32_t aValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionDecrement, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionDecrement->InputParameters();
    invocation->AddInput(new ArgumentInt(*inParams[inIndex++], aValue));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionDecrement->OutputParameters();
    invocation->AddOutput(new ArgumentInt(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyZappOrgTestBasic1Cpp::EndDecrement(IAsync& aAsync, int32_t& aResult)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Decrement"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aResult = ((ArgumentInt*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyZappOrgTestBasic1Cpp::SyncToggle(bool aValue, bool& aResult)
{
    SyncToggleZappOrgTestBasic1Cpp sync(*this, aResult);
    BeginToggle(aValue, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestBasic1Cpp::BeginToggle(bool aValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionToggle, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionToggle->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aValue));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionToggle->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyZappOrgTestBasic1Cpp::EndToggle(IAsync& aAsync, bool& aResult)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Toggle"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aResult = ((ArgumentBool*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyZappOrgTestBasic1Cpp::SyncEchoString(const std::string& aValue, std::string& aResult)
{
    SyncEchoStringZappOrgTestBasic1Cpp sync(*this, aResult);
    BeginEchoString(aValue, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestBasic1Cpp::BeginEchoString(const std::string& aValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionEchoString, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionEchoString->InputParameters();
    {
        Brn buf((const TByte*)aValue.c_str(), aValue.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionEchoString->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyZappOrgTestBasic1Cpp::EndEchoString(IAsync& aAsync, std::string& aResult)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("EchoString"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aResult.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyZappOrgTestBasic1Cpp::SyncEchoBinary(const std::string& aValue, std::string& aResult)
{
    SyncEchoBinaryZappOrgTestBasic1Cpp sync(*this, aResult);
    BeginEchoBinary(aValue, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestBasic1Cpp::BeginEchoBinary(const std::string& aValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionEchoBinary, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionEchoBinary->InputParameters();
    {
        Brn buf((const TByte*)aValue.c_str(), aValue.length());
        invocation->AddInput(new ArgumentBinary(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionEchoBinary->OutputParameters();
    invocation->AddOutput(new ArgumentBinary(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyZappOrgTestBasic1Cpp::EndEchoBinary(IAsync& aAsync, std::string& aResult)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("EchoBinary"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aResult.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyZappOrgTestBasic1Cpp::SyncSetUint(uint32_t aValueUint)
{
    SyncSetUintZappOrgTestBasic1Cpp sync(*this);
    BeginSetUint(aValueUint, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestBasic1Cpp::BeginSetUint(uint32_t aValueUint, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetUint, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetUint->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aValueUint));
    invocation->Invoke();
}

void CpProxyZappOrgTestBasic1Cpp::EndSetUint(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetUint"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyZappOrgTestBasic1Cpp::SyncGetUint(uint32_t& aValueUint)
{
    SyncGetUintZappOrgTestBasic1Cpp sync(*this, aValueUint);
    BeginGetUint(sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestBasic1Cpp::BeginGetUint(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetUint, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetUint->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyZappOrgTestBasic1Cpp::EndGetUint(IAsync& aAsync, uint32_t& aValueUint)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetUint"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aValueUint = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyZappOrgTestBasic1Cpp::SyncSetInt(int32_t aValueInt)
{
    SyncSetIntZappOrgTestBasic1Cpp sync(*this);
    BeginSetInt(aValueInt, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestBasic1Cpp::BeginSetInt(int32_t aValueInt, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetInt, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetInt->InputParameters();
    invocation->AddInput(new ArgumentInt(*inParams[inIndex++], aValueInt));
    invocation->Invoke();
}

void CpProxyZappOrgTestBasic1Cpp::EndSetInt(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetInt"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyZappOrgTestBasic1Cpp::SyncGetInt(int32_t& aValueInt)
{
    SyncGetIntZappOrgTestBasic1Cpp sync(*this, aValueInt);
    BeginGetInt(sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestBasic1Cpp::BeginGetInt(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetInt, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetInt->OutputParameters();
    invocation->AddOutput(new ArgumentInt(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyZappOrgTestBasic1Cpp::EndGetInt(IAsync& aAsync, int32_t& aValueInt)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetInt"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aValueInt = ((ArgumentInt*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyZappOrgTestBasic1Cpp::SyncSetBool(bool aValueBool)
{
    SyncSetBoolZappOrgTestBasic1Cpp sync(*this);
    BeginSetBool(aValueBool, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestBasic1Cpp::BeginSetBool(bool aValueBool, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetBool, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetBool->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aValueBool));
    invocation->Invoke();
}

void CpProxyZappOrgTestBasic1Cpp::EndSetBool(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetBool"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyZappOrgTestBasic1Cpp::SyncGetBool(bool& aValueBool)
{
    SyncGetBoolZappOrgTestBasic1Cpp sync(*this, aValueBool);
    BeginGetBool(sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestBasic1Cpp::BeginGetBool(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetBool, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetBool->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyZappOrgTestBasic1Cpp::EndGetBool(IAsync& aAsync, bool& aValueBool)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetBool"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aValueBool = ((ArgumentBool*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyZappOrgTestBasic1Cpp::SyncSetMultiple(uint32_t aValueUint, int32_t aValueInt, bool aValueBool)
{
    SyncSetMultipleZappOrgTestBasic1Cpp sync(*this);
    BeginSetMultiple(aValueUint, aValueInt, aValueBool, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestBasic1Cpp::BeginSetMultiple(uint32_t aValueUint, int32_t aValueInt, bool aValueBool, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetMultiple, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetMultiple->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aValueUint));
    invocation->AddInput(new ArgumentInt(*inParams[inIndex++], aValueInt));
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aValueBool));
    invocation->Invoke();
}

void CpProxyZappOrgTestBasic1Cpp::EndSetMultiple(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetMultiple"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyZappOrgTestBasic1Cpp::SyncSetString(const std::string& aValueStr)
{
    SyncSetStringZappOrgTestBasic1Cpp sync(*this);
    BeginSetString(aValueStr, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestBasic1Cpp::BeginSetString(const std::string& aValueStr, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetString, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetString->InputParameters();
    {
        Brn buf((const TByte*)aValueStr.c_str(), aValueStr.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    invocation->Invoke();
}

void CpProxyZappOrgTestBasic1Cpp::EndSetString(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetString"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyZappOrgTestBasic1Cpp::SyncGetString(std::string& aValueStr)
{
    SyncGetStringZappOrgTestBasic1Cpp sync(*this, aValueStr);
    BeginGetString(sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestBasic1Cpp::BeginGetString(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetString, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetString->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyZappOrgTestBasic1Cpp::EndGetString(IAsync& aAsync, std::string& aValueStr)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetString"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aValueStr.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyZappOrgTestBasic1Cpp::SyncSetBinary(const std::string& aValueBin)
{
    SyncSetBinaryZappOrgTestBasic1Cpp sync(*this);
    BeginSetBinary(aValueBin, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestBasic1Cpp::BeginSetBinary(const std::string& aValueBin, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetBinary, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetBinary->InputParameters();
    {
        Brn buf((const TByte*)aValueBin.c_str(), aValueBin.length());
        invocation->AddInput(new ArgumentBinary(*inParams[inIndex++], buf));
    }
    invocation->Invoke();
}

void CpProxyZappOrgTestBasic1Cpp::EndSetBinary(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetBinary"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyZappOrgTestBasic1Cpp::SyncGetBinary(std::string& aValueBin)
{
    SyncGetBinaryZappOrgTestBasic1Cpp sync(*this, aValueBin);
    BeginGetBinary(sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestBasic1Cpp::BeginGetBinary(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetBinary, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetBinary->OutputParameters();
    invocation->AddOutput(new ArgumentBinary(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyZappOrgTestBasic1Cpp::EndGetBinary(IAsync& aAsync, std::string& aValueBin)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetBinary"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aValueBin.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyZappOrgTestBasic1Cpp::SetPropertyVarUintChanged(Functor& aFunctor)
{
    iLock->Wait();
    iVarUintChanged = aFunctor;
    iLock->Signal();
}

void CpProxyZappOrgTestBasic1Cpp::SetPropertyVarIntChanged(Functor& aFunctor)
{
    iLock->Wait();
    iVarIntChanged = aFunctor;
    iLock->Signal();
}

void CpProxyZappOrgTestBasic1Cpp::SetPropertyVarBoolChanged(Functor& aFunctor)
{
    iLock->Wait();
    iVarBoolChanged = aFunctor;
    iLock->Signal();
}

void CpProxyZappOrgTestBasic1Cpp::SetPropertyVarStrChanged(Functor& aFunctor)
{
    iLock->Wait();
    iVarStrChanged = aFunctor;
    iLock->Signal();
}

void CpProxyZappOrgTestBasic1Cpp::SetPropertyVarBinChanged(Functor& aFunctor)
{
    iLock->Wait();
    iVarBinChanged = aFunctor;
    iLock->Signal();
}

void CpProxyZappOrgTestBasic1Cpp::PropertyVarUint(uint32_t& aVarUint) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aVarUint = iVarUint->Value();
}

void CpProxyZappOrgTestBasic1Cpp::PropertyVarInt(int32_t& aVarInt) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aVarInt = iVarInt->Value();
}

void CpProxyZappOrgTestBasic1Cpp::PropertyVarBool(bool& aVarBool) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aVarBool = iVarBool->Value();
}

void CpProxyZappOrgTestBasic1Cpp::PropertyVarStr(std::string& aVarStr) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iVarStr->Value();
    aVarStr.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyZappOrgTestBasic1Cpp::PropertyVarBin(std::string& aVarBin) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iVarBin->Value();
    aVarBin.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyZappOrgTestBasic1Cpp::VarUintPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iVarUintChanged != NULL) {
        iVarUintChanged();
    }
}

void CpProxyZappOrgTestBasic1Cpp::VarIntPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iVarIntChanged != NULL) {
        iVarIntChanged();
    }
}

void CpProxyZappOrgTestBasic1Cpp::VarBoolPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iVarBoolChanged != NULL) {
        iVarBoolChanged();
    }
}

void CpProxyZappOrgTestBasic1Cpp::VarStrPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iVarStrChanged != NULL) {
        iVarStrChanged();
    }
}

void CpProxyZappOrgTestBasic1Cpp::VarBinPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iVarBinChanged != NULL) {
        iVarBinChanged();
    }
}

