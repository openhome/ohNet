#include <Core/CpZappOrgTestBasic1.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Core/CpDevice.h>

using namespace Zapp;


class SyncIncrementZappOrgTestBasic1 : public SyncProxyAction
{
public:
    SyncIncrementZappOrgTestBasic1(CpProxyZappOrgTestBasic1& aService, TUint& aResult);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestBasic1& iService;
    TUint& iResult;
};

SyncIncrementZappOrgTestBasic1::SyncIncrementZappOrgTestBasic1(CpProxyZappOrgTestBasic1& aService, TUint& aResult)
    : iService(aService)
    , iResult(aResult)
{
}

void SyncIncrementZappOrgTestBasic1::CompleteRequest(IAsync& aAsync)
{
    iService.EndIncrement(aAsync, iResult);
}


class SyncDecrementZappOrgTestBasic1 : public SyncProxyAction
{
public:
    SyncDecrementZappOrgTestBasic1(CpProxyZappOrgTestBasic1& aService, TInt& aResult);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestBasic1& iService;
    TInt& iResult;
};

SyncDecrementZappOrgTestBasic1::SyncDecrementZappOrgTestBasic1(CpProxyZappOrgTestBasic1& aService, TInt& aResult)
    : iService(aService)
    , iResult(aResult)
{
}

void SyncDecrementZappOrgTestBasic1::CompleteRequest(IAsync& aAsync)
{
    iService.EndDecrement(aAsync, iResult);
}


class SyncToggleZappOrgTestBasic1 : public SyncProxyAction
{
public:
    SyncToggleZappOrgTestBasic1(CpProxyZappOrgTestBasic1& aService, TBool& aResult);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestBasic1& iService;
    TBool& iResult;
};

SyncToggleZappOrgTestBasic1::SyncToggleZappOrgTestBasic1(CpProxyZappOrgTestBasic1& aService, TBool& aResult)
    : iService(aService)
    , iResult(aResult)
{
}

void SyncToggleZappOrgTestBasic1::CompleteRequest(IAsync& aAsync)
{
    iService.EndToggle(aAsync, iResult);
}


class SyncEchoStringZappOrgTestBasic1 : public SyncProxyAction
{
public:
    SyncEchoStringZappOrgTestBasic1(CpProxyZappOrgTestBasic1& aService, Brh& aResult);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestBasic1& iService;
    Brh& iResult;
};

SyncEchoStringZappOrgTestBasic1::SyncEchoStringZappOrgTestBasic1(CpProxyZappOrgTestBasic1& aService, Brh& aResult)
    : iService(aService)
    , iResult(aResult)
{
}

void SyncEchoStringZappOrgTestBasic1::CompleteRequest(IAsync& aAsync)
{
    iService.EndEchoString(aAsync, iResult);
}


class SyncEchoBinaryZappOrgTestBasic1 : public SyncProxyAction
{
public:
    SyncEchoBinaryZappOrgTestBasic1(CpProxyZappOrgTestBasic1& aService, Brh& aResult);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestBasic1& iService;
    Brh& iResult;
};

SyncEchoBinaryZappOrgTestBasic1::SyncEchoBinaryZappOrgTestBasic1(CpProxyZappOrgTestBasic1& aService, Brh& aResult)
    : iService(aService)
    , iResult(aResult)
{
}

void SyncEchoBinaryZappOrgTestBasic1::CompleteRequest(IAsync& aAsync)
{
    iService.EndEchoBinary(aAsync, iResult);
}


class SyncSetUintZappOrgTestBasic1 : public SyncProxyAction
{
public:
    SyncSetUintZappOrgTestBasic1(CpProxyZappOrgTestBasic1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestBasic1& iService;
};

SyncSetUintZappOrgTestBasic1::SyncSetUintZappOrgTestBasic1(CpProxyZappOrgTestBasic1& aService)
    : iService(aService)
{
}

void SyncSetUintZappOrgTestBasic1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetUint(aAsync);
}


class SyncGetUintZappOrgTestBasic1 : public SyncProxyAction
{
public:
    SyncGetUintZappOrgTestBasic1(CpProxyZappOrgTestBasic1& aService, TUint& aValueUint);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestBasic1& iService;
    TUint& iValueUint;
};

SyncGetUintZappOrgTestBasic1::SyncGetUintZappOrgTestBasic1(CpProxyZappOrgTestBasic1& aService, TUint& aValueUint)
    : iService(aService)
    , iValueUint(aValueUint)
{
}

void SyncGetUintZappOrgTestBasic1::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetUint(aAsync, iValueUint);
}


class SyncSetIntZappOrgTestBasic1 : public SyncProxyAction
{
public:
    SyncSetIntZappOrgTestBasic1(CpProxyZappOrgTestBasic1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestBasic1& iService;
};

SyncSetIntZappOrgTestBasic1::SyncSetIntZappOrgTestBasic1(CpProxyZappOrgTestBasic1& aService)
    : iService(aService)
{
}

void SyncSetIntZappOrgTestBasic1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetInt(aAsync);
}


class SyncGetIntZappOrgTestBasic1 : public SyncProxyAction
{
public:
    SyncGetIntZappOrgTestBasic1(CpProxyZappOrgTestBasic1& aService, TInt& aValueInt);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestBasic1& iService;
    TInt& iValueInt;
};

SyncGetIntZappOrgTestBasic1::SyncGetIntZappOrgTestBasic1(CpProxyZappOrgTestBasic1& aService, TInt& aValueInt)
    : iService(aService)
    , iValueInt(aValueInt)
{
}

void SyncGetIntZappOrgTestBasic1::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetInt(aAsync, iValueInt);
}


class SyncSetBoolZappOrgTestBasic1 : public SyncProxyAction
{
public:
    SyncSetBoolZappOrgTestBasic1(CpProxyZappOrgTestBasic1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestBasic1& iService;
};

SyncSetBoolZappOrgTestBasic1::SyncSetBoolZappOrgTestBasic1(CpProxyZappOrgTestBasic1& aService)
    : iService(aService)
{
}

void SyncSetBoolZappOrgTestBasic1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetBool(aAsync);
}


class SyncGetBoolZappOrgTestBasic1 : public SyncProxyAction
{
public:
    SyncGetBoolZappOrgTestBasic1(CpProxyZappOrgTestBasic1& aService, TBool& aValueBool);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestBasic1& iService;
    TBool& iValueBool;
};

SyncGetBoolZappOrgTestBasic1::SyncGetBoolZappOrgTestBasic1(CpProxyZappOrgTestBasic1& aService, TBool& aValueBool)
    : iService(aService)
    , iValueBool(aValueBool)
{
}

void SyncGetBoolZappOrgTestBasic1::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetBool(aAsync, iValueBool);
}


class SyncSetMultipleZappOrgTestBasic1 : public SyncProxyAction
{
public:
    SyncSetMultipleZappOrgTestBasic1(CpProxyZappOrgTestBasic1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestBasic1& iService;
};

SyncSetMultipleZappOrgTestBasic1::SyncSetMultipleZappOrgTestBasic1(CpProxyZappOrgTestBasic1& aService)
    : iService(aService)
{
}

void SyncSetMultipleZappOrgTestBasic1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetMultiple(aAsync);
}


class SyncSetStringZappOrgTestBasic1 : public SyncProxyAction
{
public:
    SyncSetStringZappOrgTestBasic1(CpProxyZappOrgTestBasic1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestBasic1& iService;
};

SyncSetStringZappOrgTestBasic1::SyncSetStringZappOrgTestBasic1(CpProxyZappOrgTestBasic1& aService)
    : iService(aService)
{
}

void SyncSetStringZappOrgTestBasic1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetString(aAsync);
}


class SyncGetStringZappOrgTestBasic1 : public SyncProxyAction
{
public:
    SyncGetStringZappOrgTestBasic1(CpProxyZappOrgTestBasic1& aService, Brh& aValueStr);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestBasic1& iService;
    Brh& iValueStr;
};

SyncGetStringZappOrgTestBasic1::SyncGetStringZappOrgTestBasic1(CpProxyZappOrgTestBasic1& aService, Brh& aValueStr)
    : iService(aService)
    , iValueStr(aValueStr)
{
}

void SyncGetStringZappOrgTestBasic1::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetString(aAsync, iValueStr);
}


class SyncSetBinaryZappOrgTestBasic1 : public SyncProxyAction
{
public:
    SyncSetBinaryZappOrgTestBasic1(CpProxyZappOrgTestBasic1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestBasic1& iService;
};

SyncSetBinaryZappOrgTestBasic1::SyncSetBinaryZappOrgTestBasic1(CpProxyZappOrgTestBasic1& aService)
    : iService(aService)
{
}

void SyncSetBinaryZappOrgTestBasic1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetBinary(aAsync);
}


class SyncGetBinaryZappOrgTestBasic1 : public SyncProxyAction
{
public:
    SyncGetBinaryZappOrgTestBasic1(CpProxyZappOrgTestBasic1& aService, Brh& aValueBin);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestBasic1& iService;
    Brh& iValueBin;
};

SyncGetBinaryZappOrgTestBasic1::SyncGetBinaryZappOrgTestBasic1(CpProxyZappOrgTestBasic1& aService, Brh& aValueBin)
    : iService(aService)
    , iValueBin(aValueBin)
{
}

void SyncGetBinaryZappOrgTestBasic1::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetBinary(aAsync, iValueBin);
}


CpProxyZappOrgTestBasic1::CpProxyZappOrgTestBasic1(CpDevice& aDevice)
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
    functor = MakeFunctor(*this, &CpProxyZappOrgTestBasic1::VarUintPropertyChanged);
    iVarUint = new PropertyUint("VarUint", functor);
    iService->AddProperty(iVarUint);
    functor = MakeFunctor(*this, &CpProxyZappOrgTestBasic1::VarIntPropertyChanged);
    iVarInt = new PropertyInt("VarInt", functor);
    iService->AddProperty(iVarInt);
    functor = MakeFunctor(*this, &CpProxyZappOrgTestBasic1::VarBoolPropertyChanged);
    iVarBool = new PropertyBool("VarBool", functor);
    iService->AddProperty(iVarBool);
    functor = MakeFunctor(*this, &CpProxyZappOrgTestBasic1::VarStrPropertyChanged);
    iVarStr = new PropertyString("VarStr", functor);
    iService->AddProperty(iVarStr);
    functor = MakeFunctor(*this, &CpProxyZappOrgTestBasic1::VarBinPropertyChanged);
    iVarBin = new PropertyBinary("VarBin", functor);
    iService->AddProperty(iVarBin);
}

CpProxyZappOrgTestBasic1::~CpProxyZappOrgTestBasic1()
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

void CpProxyZappOrgTestBasic1::SyncIncrement(TUint aValue, TUint& aResult)
{
    SyncIncrementZappOrgTestBasic1 sync(*this, aResult);
    BeginIncrement(aValue, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestBasic1::BeginIncrement(TUint aValue, FunctorAsync& aFunctor)
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

void CpProxyZappOrgTestBasic1::EndIncrement(IAsync& aAsync, TUint& aResult)
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

void CpProxyZappOrgTestBasic1::SyncDecrement(TInt aValue, TInt& aResult)
{
    SyncDecrementZappOrgTestBasic1 sync(*this, aResult);
    BeginDecrement(aValue, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestBasic1::BeginDecrement(TInt aValue, FunctorAsync& aFunctor)
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

void CpProxyZappOrgTestBasic1::EndDecrement(IAsync& aAsync, TInt& aResult)
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

void CpProxyZappOrgTestBasic1::SyncToggle(TBool aValue, TBool& aResult)
{
    SyncToggleZappOrgTestBasic1 sync(*this, aResult);
    BeginToggle(aValue, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestBasic1::BeginToggle(TBool aValue, FunctorAsync& aFunctor)
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

void CpProxyZappOrgTestBasic1::EndToggle(IAsync& aAsync, TBool& aResult)
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

void CpProxyZappOrgTestBasic1::SyncEchoString(const Brx& aValue, Brh& aResult)
{
    SyncEchoStringZappOrgTestBasic1 sync(*this, aResult);
    BeginEchoString(aValue, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestBasic1::BeginEchoString(const Brx& aValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionEchoString, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionEchoString->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aValue));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionEchoString->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyZappOrgTestBasic1::EndEchoString(IAsync& aAsync, Brh& aResult)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("EchoString"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aResult);
}

void CpProxyZappOrgTestBasic1::SyncEchoBinary(const Brx& aValue, Brh& aResult)
{
    SyncEchoBinaryZappOrgTestBasic1 sync(*this, aResult);
    BeginEchoBinary(aValue, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestBasic1::BeginEchoBinary(const Brx& aValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionEchoBinary, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionEchoBinary->InputParameters();
    invocation->AddInput(new ArgumentBinary(*inParams[inIndex++], aValue));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionEchoBinary->OutputParameters();
    invocation->AddOutput(new ArgumentBinary(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyZappOrgTestBasic1::EndEchoBinary(IAsync& aAsync, Brh& aResult)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("EchoBinary"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentBinary*)invocation.OutputArguments()[index++])->TransferTo(aResult);
}

void CpProxyZappOrgTestBasic1::SyncSetUint(TUint aValueUint)
{
    SyncSetUintZappOrgTestBasic1 sync(*this);
    BeginSetUint(aValueUint, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestBasic1::BeginSetUint(TUint aValueUint, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetUint, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetUint->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aValueUint));
    invocation->Invoke();
}

void CpProxyZappOrgTestBasic1::EndSetUint(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetUint"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyZappOrgTestBasic1::SyncGetUint(TUint& aValueUint)
{
    SyncGetUintZappOrgTestBasic1 sync(*this, aValueUint);
    BeginGetUint(sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestBasic1::BeginGetUint(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetUint, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetUint->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyZappOrgTestBasic1::EndGetUint(IAsync& aAsync, TUint& aValueUint)
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

void CpProxyZappOrgTestBasic1::SyncSetInt(TInt aValueInt)
{
    SyncSetIntZappOrgTestBasic1 sync(*this);
    BeginSetInt(aValueInt, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestBasic1::BeginSetInt(TInt aValueInt, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetInt, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetInt->InputParameters();
    invocation->AddInput(new ArgumentInt(*inParams[inIndex++], aValueInt));
    invocation->Invoke();
}

void CpProxyZappOrgTestBasic1::EndSetInt(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetInt"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyZappOrgTestBasic1::SyncGetInt(TInt& aValueInt)
{
    SyncGetIntZappOrgTestBasic1 sync(*this, aValueInt);
    BeginGetInt(sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestBasic1::BeginGetInt(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetInt, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetInt->OutputParameters();
    invocation->AddOutput(new ArgumentInt(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyZappOrgTestBasic1::EndGetInt(IAsync& aAsync, TInt& aValueInt)
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

void CpProxyZappOrgTestBasic1::SyncSetBool(TBool aValueBool)
{
    SyncSetBoolZappOrgTestBasic1 sync(*this);
    BeginSetBool(aValueBool, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestBasic1::BeginSetBool(TBool aValueBool, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetBool, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetBool->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aValueBool));
    invocation->Invoke();
}

void CpProxyZappOrgTestBasic1::EndSetBool(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetBool"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyZappOrgTestBasic1::SyncGetBool(TBool& aValueBool)
{
    SyncGetBoolZappOrgTestBasic1 sync(*this, aValueBool);
    BeginGetBool(sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestBasic1::BeginGetBool(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetBool, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetBool->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyZappOrgTestBasic1::EndGetBool(IAsync& aAsync, TBool& aValueBool)
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

void CpProxyZappOrgTestBasic1::SyncSetMultiple(TUint aValueUint, TInt aValueInt, TBool aValueBool)
{
    SyncSetMultipleZappOrgTestBasic1 sync(*this);
    BeginSetMultiple(aValueUint, aValueInt, aValueBool, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestBasic1::BeginSetMultiple(TUint aValueUint, TInt aValueInt, TBool aValueBool, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetMultiple, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetMultiple->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aValueUint));
    invocation->AddInput(new ArgumentInt(*inParams[inIndex++], aValueInt));
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aValueBool));
    invocation->Invoke();
}

void CpProxyZappOrgTestBasic1::EndSetMultiple(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetMultiple"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyZappOrgTestBasic1::SyncSetString(const Brx& aValueStr)
{
    SyncSetStringZappOrgTestBasic1 sync(*this);
    BeginSetString(aValueStr, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestBasic1::BeginSetString(const Brx& aValueStr, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetString, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetString->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aValueStr));
    invocation->Invoke();
}

void CpProxyZappOrgTestBasic1::EndSetString(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetString"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyZappOrgTestBasic1::SyncGetString(Brh& aValueStr)
{
    SyncGetStringZappOrgTestBasic1 sync(*this, aValueStr);
    BeginGetString(sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestBasic1::BeginGetString(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetString, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetString->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyZappOrgTestBasic1::EndGetString(IAsync& aAsync, Brh& aValueStr)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetString"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aValueStr);
}

void CpProxyZappOrgTestBasic1::SyncSetBinary(const Brx& aValueBin)
{
    SyncSetBinaryZappOrgTestBasic1 sync(*this);
    BeginSetBinary(aValueBin, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestBasic1::BeginSetBinary(const Brx& aValueBin, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetBinary, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetBinary->InputParameters();
    invocation->AddInput(new ArgumentBinary(*inParams[inIndex++], aValueBin));
    invocation->Invoke();
}

void CpProxyZappOrgTestBasic1::EndSetBinary(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetBinary"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyZappOrgTestBasic1::SyncGetBinary(Brh& aValueBin)
{
    SyncGetBinaryZappOrgTestBasic1 sync(*this, aValueBin);
    BeginGetBinary(sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestBasic1::BeginGetBinary(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetBinary, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetBinary->OutputParameters();
    invocation->AddOutput(new ArgumentBinary(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyZappOrgTestBasic1::EndGetBinary(IAsync& aAsync, Brh& aValueBin)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetBinary"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentBinary*)invocation.OutputArguments()[index++])->TransferTo(aValueBin);
}

void CpProxyZappOrgTestBasic1::SetPropertyVarUintChanged(Functor& aFunctor)
{
    iLock->Wait();
    iVarUintChanged = aFunctor;
    iLock->Signal();
}

void CpProxyZappOrgTestBasic1::SetPropertyVarIntChanged(Functor& aFunctor)
{
    iLock->Wait();
    iVarIntChanged = aFunctor;
    iLock->Signal();
}

void CpProxyZappOrgTestBasic1::SetPropertyVarBoolChanged(Functor& aFunctor)
{
    iLock->Wait();
    iVarBoolChanged = aFunctor;
    iLock->Signal();
}

void CpProxyZappOrgTestBasic1::SetPropertyVarStrChanged(Functor& aFunctor)
{
    iLock->Wait();
    iVarStrChanged = aFunctor;
    iLock->Signal();
}

void CpProxyZappOrgTestBasic1::SetPropertyVarBinChanged(Functor& aFunctor)
{
    iLock->Wait();
    iVarBinChanged = aFunctor;
    iLock->Signal();
}

void CpProxyZappOrgTestBasic1::PropertyVarUint(TUint& aVarUint) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aVarUint = iVarUint->Value();
}

void CpProxyZappOrgTestBasic1::PropertyVarInt(TInt& aVarInt) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aVarInt = iVarInt->Value();
}

void CpProxyZappOrgTestBasic1::PropertyVarBool(TBool& aVarBool) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aVarBool = iVarBool->Value();
}

void CpProxyZappOrgTestBasic1::PropertyVarStr(Brhz& aVarStr) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aVarStr.Set(iVarStr->Value());
}

void CpProxyZappOrgTestBasic1::PropertyVarBin(Brh& aVarBin) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aVarBin.Set(iVarBin->Value());
}

void CpProxyZappOrgTestBasic1::VarUintPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iVarUintChanged != NULL) {
        iVarUintChanged();
    }
}

void CpProxyZappOrgTestBasic1::VarIntPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iVarIntChanged != NULL) {
        iVarIntChanged();
    }
}

void CpProxyZappOrgTestBasic1::VarBoolPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iVarBoolChanged != NULL) {
        iVarBoolChanged();
    }
}

void CpProxyZappOrgTestBasic1::VarStrPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iVarStrChanged != NULL) {
        iVarStrChanged();
    }
}

void CpProxyZappOrgTestBasic1::VarBinPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iVarBinChanged != NULL) {
        iVarBinChanged();
    }
}

