#include "CpOpenhomeOrgTestBasic1.h"
#include <OpenHome/Net/Core/CpProxy.h>
#include <OpenHome/Net/Private/CpiService.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Net/Private/AsyncPrivate.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Cpp/CpDevice.h>

#include <string>

using namespace OpenHome;
using namespace OpenHome::Net;


class SyncIncrementOpenhomeOrgTestBasic1Cpp : public SyncProxyAction
{
public:
    SyncIncrementOpenhomeOrgTestBasic1Cpp(CpProxyOpenhomeOrgTestBasic1Cpp& aProxy, uint32_t& aResult);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncIncrementOpenhomeOrgTestBasic1Cpp() {}
private:
    CpProxyOpenhomeOrgTestBasic1Cpp& iService;
    uint32_t& iResult;
};

SyncIncrementOpenhomeOrgTestBasic1Cpp::SyncIncrementOpenhomeOrgTestBasic1Cpp(CpProxyOpenhomeOrgTestBasic1Cpp& aProxy, uint32_t& aResult)
    : iService(aProxy)
    , iResult(aResult)
{
}

void SyncIncrementOpenhomeOrgTestBasic1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndIncrement(aAsync, iResult);
}


class SyncDecrementOpenhomeOrgTestBasic1Cpp : public SyncProxyAction
{
public:
    SyncDecrementOpenhomeOrgTestBasic1Cpp(CpProxyOpenhomeOrgTestBasic1Cpp& aProxy, int32_t& aResult);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncDecrementOpenhomeOrgTestBasic1Cpp() {}
private:
    CpProxyOpenhomeOrgTestBasic1Cpp& iService;
    int32_t& iResult;
};

SyncDecrementOpenhomeOrgTestBasic1Cpp::SyncDecrementOpenhomeOrgTestBasic1Cpp(CpProxyOpenhomeOrgTestBasic1Cpp& aProxy, int32_t& aResult)
    : iService(aProxy)
    , iResult(aResult)
{
}

void SyncDecrementOpenhomeOrgTestBasic1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndDecrement(aAsync, iResult);
}


class SyncToggleOpenhomeOrgTestBasic1Cpp : public SyncProxyAction
{
public:
    SyncToggleOpenhomeOrgTestBasic1Cpp(CpProxyOpenhomeOrgTestBasic1Cpp& aProxy, bool& aResult);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncToggleOpenhomeOrgTestBasic1Cpp() {}
private:
    CpProxyOpenhomeOrgTestBasic1Cpp& iService;
    bool& iResult;
};

SyncToggleOpenhomeOrgTestBasic1Cpp::SyncToggleOpenhomeOrgTestBasic1Cpp(CpProxyOpenhomeOrgTestBasic1Cpp& aProxy, bool& aResult)
    : iService(aProxy)
    , iResult(aResult)
{
}

void SyncToggleOpenhomeOrgTestBasic1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndToggle(aAsync, iResult);
}


class SyncEchoStringOpenhomeOrgTestBasic1Cpp : public SyncProxyAction
{
public:
    SyncEchoStringOpenhomeOrgTestBasic1Cpp(CpProxyOpenhomeOrgTestBasic1Cpp& aProxy, std::string& aResult);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncEchoStringOpenhomeOrgTestBasic1Cpp() {}
private:
    CpProxyOpenhomeOrgTestBasic1Cpp& iService;
    std::string& iResult;
};

SyncEchoStringOpenhomeOrgTestBasic1Cpp::SyncEchoStringOpenhomeOrgTestBasic1Cpp(CpProxyOpenhomeOrgTestBasic1Cpp& aProxy, std::string& aResult)
    : iService(aProxy)
    , iResult(aResult)
{
}

void SyncEchoStringOpenhomeOrgTestBasic1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndEchoString(aAsync, iResult);
}


class SyncEchoBinaryOpenhomeOrgTestBasic1Cpp : public SyncProxyAction
{
public:
    SyncEchoBinaryOpenhomeOrgTestBasic1Cpp(CpProxyOpenhomeOrgTestBasic1Cpp& aProxy, std::string& aResult);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncEchoBinaryOpenhomeOrgTestBasic1Cpp() {}
private:
    CpProxyOpenhomeOrgTestBasic1Cpp& iService;
    std::string& iResult;
};

SyncEchoBinaryOpenhomeOrgTestBasic1Cpp::SyncEchoBinaryOpenhomeOrgTestBasic1Cpp(CpProxyOpenhomeOrgTestBasic1Cpp& aProxy, std::string& aResult)
    : iService(aProxy)
    , iResult(aResult)
{
}

void SyncEchoBinaryOpenhomeOrgTestBasic1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndEchoBinary(aAsync, iResult);
}


class SyncSetUintOpenhomeOrgTestBasic1Cpp : public SyncProxyAction
{
public:
    SyncSetUintOpenhomeOrgTestBasic1Cpp(CpProxyOpenhomeOrgTestBasic1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetUintOpenhomeOrgTestBasic1Cpp() {}
private:
    CpProxyOpenhomeOrgTestBasic1Cpp& iService;
};

SyncSetUintOpenhomeOrgTestBasic1Cpp::SyncSetUintOpenhomeOrgTestBasic1Cpp(CpProxyOpenhomeOrgTestBasic1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncSetUintOpenhomeOrgTestBasic1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetUint(aAsync);
}


class SyncGetUintOpenhomeOrgTestBasic1Cpp : public SyncProxyAction
{
public:
    SyncGetUintOpenhomeOrgTestBasic1Cpp(CpProxyOpenhomeOrgTestBasic1Cpp& aProxy, uint32_t& aValueUint);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetUintOpenhomeOrgTestBasic1Cpp() {}
private:
    CpProxyOpenhomeOrgTestBasic1Cpp& iService;
    uint32_t& iValueUint;
};

SyncGetUintOpenhomeOrgTestBasic1Cpp::SyncGetUintOpenhomeOrgTestBasic1Cpp(CpProxyOpenhomeOrgTestBasic1Cpp& aProxy, uint32_t& aValueUint)
    : iService(aProxy)
    , iValueUint(aValueUint)
{
}

void SyncGetUintOpenhomeOrgTestBasic1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetUint(aAsync, iValueUint);
}


class SyncSetIntOpenhomeOrgTestBasic1Cpp : public SyncProxyAction
{
public:
    SyncSetIntOpenhomeOrgTestBasic1Cpp(CpProxyOpenhomeOrgTestBasic1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetIntOpenhomeOrgTestBasic1Cpp() {}
private:
    CpProxyOpenhomeOrgTestBasic1Cpp& iService;
};

SyncSetIntOpenhomeOrgTestBasic1Cpp::SyncSetIntOpenhomeOrgTestBasic1Cpp(CpProxyOpenhomeOrgTestBasic1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncSetIntOpenhomeOrgTestBasic1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetInt(aAsync);
}


class SyncGetIntOpenhomeOrgTestBasic1Cpp : public SyncProxyAction
{
public:
    SyncGetIntOpenhomeOrgTestBasic1Cpp(CpProxyOpenhomeOrgTestBasic1Cpp& aProxy, int32_t& aValueInt);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetIntOpenhomeOrgTestBasic1Cpp() {}
private:
    CpProxyOpenhomeOrgTestBasic1Cpp& iService;
    int32_t& iValueInt;
};

SyncGetIntOpenhomeOrgTestBasic1Cpp::SyncGetIntOpenhomeOrgTestBasic1Cpp(CpProxyOpenhomeOrgTestBasic1Cpp& aProxy, int32_t& aValueInt)
    : iService(aProxy)
    , iValueInt(aValueInt)
{
}

void SyncGetIntOpenhomeOrgTestBasic1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetInt(aAsync, iValueInt);
}


class SyncSetBoolOpenhomeOrgTestBasic1Cpp : public SyncProxyAction
{
public:
    SyncSetBoolOpenhomeOrgTestBasic1Cpp(CpProxyOpenhomeOrgTestBasic1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetBoolOpenhomeOrgTestBasic1Cpp() {}
private:
    CpProxyOpenhomeOrgTestBasic1Cpp& iService;
};

SyncSetBoolOpenhomeOrgTestBasic1Cpp::SyncSetBoolOpenhomeOrgTestBasic1Cpp(CpProxyOpenhomeOrgTestBasic1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncSetBoolOpenhomeOrgTestBasic1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetBool(aAsync);
}


class SyncGetBoolOpenhomeOrgTestBasic1Cpp : public SyncProxyAction
{
public:
    SyncGetBoolOpenhomeOrgTestBasic1Cpp(CpProxyOpenhomeOrgTestBasic1Cpp& aProxy, bool& aValueBool);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetBoolOpenhomeOrgTestBasic1Cpp() {}
private:
    CpProxyOpenhomeOrgTestBasic1Cpp& iService;
    bool& iValueBool;
};

SyncGetBoolOpenhomeOrgTestBasic1Cpp::SyncGetBoolOpenhomeOrgTestBasic1Cpp(CpProxyOpenhomeOrgTestBasic1Cpp& aProxy, bool& aValueBool)
    : iService(aProxy)
    , iValueBool(aValueBool)
{
}

void SyncGetBoolOpenhomeOrgTestBasic1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetBool(aAsync, iValueBool);
}


class SyncSetMultipleOpenhomeOrgTestBasic1Cpp : public SyncProxyAction
{
public:
    SyncSetMultipleOpenhomeOrgTestBasic1Cpp(CpProxyOpenhomeOrgTestBasic1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetMultipleOpenhomeOrgTestBasic1Cpp() {}
private:
    CpProxyOpenhomeOrgTestBasic1Cpp& iService;
};

SyncSetMultipleOpenhomeOrgTestBasic1Cpp::SyncSetMultipleOpenhomeOrgTestBasic1Cpp(CpProxyOpenhomeOrgTestBasic1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncSetMultipleOpenhomeOrgTestBasic1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetMultiple(aAsync);
}


class SyncSetStringOpenhomeOrgTestBasic1Cpp : public SyncProxyAction
{
public:
    SyncSetStringOpenhomeOrgTestBasic1Cpp(CpProxyOpenhomeOrgTestBasic1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetStringOpenhomeOrgTestBasic1Cpp() {}
private:
    CpProxyOpenhomeOrgTestBasic1Cpp& iService;
};

SyncSetStringOpenhomeOrgTestBasic1Cpp::SyncSetStringOpenhomeOrgTestBasic1Cpp(CpProxyOpenhomeOrgTestBasic1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncSetStringOpenhomeOrgTestBasic1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetString(aAsync);
}


class SyncGetStringOpenhomeOrgTestBasic1Cpp : public SyncProxyAction
{
public:
    SyncGetStringOpenhomeOrgTestBasic1Cpp(CpProxyOpenhomeOrgTestBasic1Cpp& aProxy, std::string& aValueStr);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetStringOpenhomeOrgTestBasic1Cpp() {}
private:
    CpProxyOpenhomeOrgTestBasic1Cpp& iService;
    std::string& iValueStr;
};

SyncGetStringOpenhomeOrgTestBasic1Cpp::SyncGetStringOpenhomeOrgTestBasic1Cpp(CpProxyOpenhomeOrgTestBasic1Cpp& aProxy, std::string& aValueStr)
    : iService(aProxy)
    , iValueStr(aValueStr)
{
}

void SyncGetStringOpenhomeOrgTestBasic1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetString(aAsync, iValueStr);
}


class SyncSetBinaryOpenhomeOrgTestBasic1Cpp : public SyncProxyAction
{
public:
    SyncSetBinaryOpenhomeOrgTestBasic1Cpp(CpProxyOpenhomeOrgTestBasic1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetBinaryOpenhomeOrgTestBasic1Cpp() {}
private:
    CpProxyOpenhomeOrgTestBasic1Cpp& iService;
};

SyncSetBinaryOpenhomeOrgTestBasic1Cpp::SyncSetBinaryOpenhomeOrgTestBasic1Cpp(CpProxyOpenhomeOrgTestBasic1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncSetBinaryOpenhomeOrgTestBasic1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetBinary(aAsync);
}


class SyncGetBinaryOpenhomeOrgTestBasic1Cpp : public SyncProxyAction
{
public:
    SyncGetBinaryOpenhomeOrgTestBasic1Cpp(CpProxyOpenhomeOrgTestBasic1Cpp& aProxy, std::string& aValueBin);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetBinaryOpenhomeOrgTestBasic1Cpp() {}
private:
    CpProxyOpenhomeOrgTestBasic1Cpp& iService;
    std::string& iValueBin;
};

SyncGetBinaryOpenhomeOrgTestBasic1Cpp::SyncGetBinaryOpenhomeOrgTestBasic1Cpp(CpProxyOpenhomeOrgTestBasic1Cpp& aProxy, std::string& aValueBin)
    : iService(aProxy)
    , iValueBin(aValueBin)
{
}

void SyncGetBinaryOpenhomeOrgTestBasic1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetBinary(aAsync, iValueBin);
}


class SyncToggleBoolOpenhomeOrgTestBasic1Cpp : public SyncProxyAction
{
public:
    SyncToggleBoolOpenhomeOrgTestBasic1Cpp(CpProxyOpenhomeOrgTestBasic1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncToggleBoolOpenhomeOrgTestBasic1Cpp() {}
private:
    CpProxyOpenhomeOrgTestBasic1Cpp& iService;
};

SyncToggleBoolOpenhomeOrgTestBasic1Cpp::SyncToggleBoolOpenhomeOrgTestBasic1Cpp(CpProxyOpenhomeOrgTestBasic1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncToggleBoolOpenhomeOrgTestBasic1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndToggleBool(aAsync);
}


class SyncWriteFileOpenhomeOrgTestBasic1Cpp : public SyncProxyAction
{
public:
    SyncWriteFileOpenhomeOrgTestBasic1Cpp(CpProxyOpenhomeOrgTestBasic1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncWriteFileOpenhomeOrgTestBasic1Cpp() {}
private:
    CpProxyOpenhomeOrgTestBasic1Cpp& iService;
};

SyncWriteFileOpenhomeOrgTestBasic1Cpp::SyncWriteFileOpenhomeOrgTestBasic1Cpp(CpProxyOpenhomeOrgTestBasic1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncWriteFileOpenhomeOrgTestBasic1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndWriteFile(aAsync);
}


class SyncShutdownOpenhomeOrgTestBasic1Cpp : public SyncProxyAction
{
public:
    SyncShutdownOpenhomeOrgTestBasic1Cpp(CpProxyOpenhomeOrgTestBasic1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncShutdownOpenhomeOrgTestBasic1Cpp() {}
private:
    CpProxyOpenhomeOrgTestBasic1Cpp& iService;
};

SyncShutdownOpenhomeOrgTestBasic1Cpp::SyncShutdownOpenhomeOrgTestBasic1Cpp(CpProxyOpenhomeOrgTestBasic1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncShutdownOpenhomeOrgTestBasic1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndShutdown(aAsync);
}


CpProxyOpenhomeOrgTestBasic1Cpp::CpProxyOpenhomeOrgTestBasic1Cpp(CpDeviceCpp& aDevice)
    : CpProxy("openhome-org", "TestBasic", 1, aDevice.Device())
{
    OpenHome::Net::Parameter* param;

    iActionIncrement = new Action("Increment");
    param = new OpenHome::Net::ParameterUint("Value");
    iActionIncrement->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("Result");
    iActionIncrement->AddOutputParameter(param);

    iActionDecrement = new Action("Decrement");
    param = new OpenHome::Net::ParameterInt("Value");
    iActionDecrement->AddInputParameter(param);
    param = new OpenHome::Net::ParameterInt("Result");
    iActionDecrement->AddOutputParameter(param);

    iActionToggle = new Action("Toggle");
    param = new OpenHome::Net::ParameterBool("Value");
    iActionToggle->AddInputParameter(param);
    param = new OpenHome::Net::ParameterBool("Result");
    iActionToggle->AddOutputParameter(param);

    iActionEchoString = new Action("EchoString");
    param = new OpenHome::Net::ParameterString("Value");
    iActionEchoString->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Result");
    iActionEchoString->AddOutputParameter(param);

    iActionEchoBinary = new Action("EchoBinary");
    param = new OpenHome::Net::ParameterBinary("Value");
    iActionEchoBinary->AddInputParameter(param);
    param = new OpenHome::Net::ParameterBinary("Result");
    iActionEchoBinary->AddOutputParameter(param);

    iActionSetUint = new Action("SetUint");
    param = new OpenHome::Net::ParameterUint("ValueUint");
    iActionSetUint->AddInputParameter(param);

    iActionGetUint = new Action("GetUint");
    param = new OpenHome::Net::ParameterUint("ValueUint");
    iActionGetUint->AddOutputParameter(param);

    iActionSetInt = new Action("SetInt");
    param = new OpenHome::Net::ParameterInt("ValueInt");
    iActionSetInt->AddInputParameter(param);

    iActionGetInt = new Action("GetInt");
    param = new OpenHome::Net::ParameterInt("ValueInt");
    iActionGetInt->AddOutputParameter(param);

    iActionSetBool = new Action("SetBool");
    param = new OpenHome::Net::ParameterBool("ValueBool");
    iActionSetBool->AddInputParameter(param);

    iActionGetBool = new Action("GetBool");
    param = new OpenHome::Net::ParameterBool("ValueBool");
    iActionGetBool->AddOutputParameter(param);

    iActionSetMultiple = new Action("SetMultiple");
    param = new OpenHome::Net::ParameterUint("ValueUint");
    iActionSetMultiple->AddInputParameter(param);
    param = new OpenHome::Net::ParameterInt("ValueInt");
    iActionSetMultiple->AddInputParameter(param);
    param = new OpenHome::Net::ParameterBool("ValueBool");
    iActionSetMultiple->AddInputParameter(param);

    iActionSetString = new Action("SetString");
    param = new OpenHome::Net::ParameterString("ValueStr");
    iActionSetString->AddInputParameter(param);

    iActionGetString = new Action("GetString");
    param = new OpenHome::Net::ParameterString("ValueStr");
    iActionGetString->AddOutputParameter(param);

    iActionSetBinary = new Action("SetBinary");
    param = new OpenHome::Net::ParameterBinary("ValueBin");
    iActionSetBinary->AddInputParameter(param);

    iActionGetBinary = new Action("GetBinary");
    param = new OpenHome::Net::ParameterBinary("ValueBin");
    iActionGetBinary->AddOutputParameter(param);

    iActionToggleBool = new Action("ToggleBool");

    iActionWriteFile = new Action("WriteFile");
    param = new OpenHome::Net::ParameterString("Data");
    iActionWriteFile->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("FileFullName");
    iActionWriteFile->AddInputParameter(param);

    iActionShutdown = new Action("Shutdown");

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyOpenhomeOrgTestBasic1Cpp::VarUintPropertyChanged);
    iVarUint = new PropertyUint("VarUint", functor);
    AddProperty(iVarUint);
    functor = MakeFunctor(*this, &CpProxyOpenhomeOrgTestBasic1Cpp::VarIntPropertyChanged);
    iVarInt = new PropertyInt("VarInt", functor);
    AddProperty(iVarInt);
    functor = MakeFunctor(*this, &CpProxyOpenhomeOrgTestBasic1Cpp::VarBoolPropertyChanged);
    iVarBool = new PropertyBool("VarBool", functor);
    AddProperty(iVarBool);
    functor = MakeFunctor(*this, &CpProxyOpenhomeOrgTestBasic1Cpp::VarStrPropertyChanged);
    iVarStr = new PropertyString("VarStr", functor);
    AddProperty(iVarStr);
    functor = MakeFunctor(*this, &CpProxyOpenhomeOrgTestBasic1Cpp::VarBinPropertyChanged);
    iVarBin = new PropertyBinary("VarBin", functor);
    AddProperty(iVarBin);
}

CpProxyOpenhomeOrgTestBasic1Cpp::~CpProxyOpenhomeOrgTestBasic1Cpp()
{
    DestroyService();
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
    delete iActionToggleBool;
    delete iActionWriteFile;
    delete iActionShutdown;
}

void CpProxyOpenhomeOrgTestBasic1Cpp::SyncIncrement(uint32_t aValue, uint32_t& aResult)
{
    SyncIncrementOpenhomeOrgTestBasic1Cpp sync(*this, aResult);
    BeginIncrement(aValue, sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestBasic1Cpp::BeginIncrement(uint32_t aValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionIncrement, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionIncrement->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aValue));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionIncrement->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgTestBasic1Cpp::EndIncrement(IAsync& aAsync, uint32_t& aResult)
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

void CpProxyOpenhomeOrgTestBasic1Cpp::SyncDecrement(int32_t aValue, int32_t& aResult)
{
    SyncDecrementOpenhomeOrgTestBasic1Cpp sync(*this, aResult);
    BeginDecrement(aValue, sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestBasic1Cpp::BeginDecrement(int32_t aValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionDecrement, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionDecrement->InputParameters();
    invocation->AddInput(new ArgumentInt(*inParams[inIndex++], aValue));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionDecrement->OutputParameters();
    invocation->AddOutput(new ArgumentInt(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgTestBasic1Cpp::EndDecrement(IAsync& aAsync, int32_t& aResult)
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

void CpProxyOpenhomeOrgTestBasic1Cpp::SyncToggle(bool aValue, bool& aResult)
{
    SyncToggleOpenhomeOrgTestBasic1Cpp sync(*this, aResult);
    BeginToggle(aValue, sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestBasic1Cpp::BeginToggle(bool aValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionToggle, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionToggle->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aValue));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionToggle->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgTestBasic1Cpp::EndToggle(IAsync& aAsync, bool& aResult)
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

void CpProxyOpenhomeOrgTestBasic1Cpp::SyncEchoString(const std::string& aValue, std::string& aResult)
{
    SyncEchoStringOpenhomeOrgTestBasic1Cpp sync(*this, aResult);
    BeginEchoString(aValue, sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestBasic1Cpp::BeginEchoString(const std::string& aValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionEchoString, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionEchoString->InputParameters();
    {
        Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionEchoString->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgTestBasic1Cpp::EndEchoString(IAsync& aAsync, std::string& aResult)
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

void CpProxyOpenhomeOrgTestBasic1Cpp::SyncEchoBinary(const std::string& aValue, std::string& aResult)
{
    SyncEchoBinaryOpenhomeOrgTestBasic1Cpp sync(*this, aResult);
    BeginEchoBinary(aValue, sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestBasic1Cpp::BeginEchoBinary(const std::string& aValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionEchoBinary, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionEchoBinary->InputParameters();
    {
        Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
        invocation->AddInput(new ArgumentBinary(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionEchoBinary->OutputParameters();
    invocation->AddOutput(new ArgumentBinary(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgTestBasic1Cpp::EndEchoBinary(IAsync& aAsync, std::string& aResult)
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

void CpProxyOpenhomeOrgTestBasic1Cpp::SyncSetUint(uint32_t aValueUint)
{
    SyncSetUintOpenhomeOrgTestBasic1Cpp sync(*this);
    BeginSetUint(aValueUint, sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestBasic1Cpp::BeginSetUint(uint32_t aValueUint, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetUint, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetUint->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aValueUint));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgTestBasic1Cpp::EndSetUint(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetUint"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyOpenhomeOrgTestBasic1Cpp::SyncGetUint(uint32_t& aValueUint)
{
    SyncGetUintOpenhomeOrgTestBasic1Cpp sync(*this, aValueUint);
    BeginGetUint(sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestBasic1Cpp::BeginGetUint(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetUint, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetUint->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgTestBasic1Cpp::EndGetUint(IAsync& aAsync, uint32_t& aValueUint)
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

void CpProxyOpenhomeOrgTestBasic1Cpp::SyncSetInt(int32_t aValueInt)
{
    SyncSetIntOpenhomeOrgTestBasic1Cpp sync(*this);
    BeginSetInt(aValueInt, sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestBasic1Cpp::BeginSetInt(int32_t aValueInt, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetInt, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetInt->InputParameters();
    invocation->AddInput(new ArgumentInt(*inParams[inIndex++], aValueInt));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgTestBasic1Cpp::EndSetInt(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetInt"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyOpenhomeOrgTestBasic1Cpp::SyncGetInt(int32_t& aValueInt)
{
    SyncGetIntOpenhomeOrgTestBasic1Cpp sync(*this, aValueInt);
    BeginGetInt(sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestBasic1Cpp::BeginGetInt(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetInt, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetInt->OutputParameters();
    invocation->AddOutput(new ArgumentInt(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgTestBasic1Cpp::EndGetInt(IAsync& aAsync, int32_t& aValueInt)
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

void CpProxyOpenhomeOrgTestBasic1Cpp::SyncSetBool(bool aValueBool)
{
    SyncSetBoolOpenhomeOrgTestBasic1Cpp sync(*this);
    BeginSetBool(aValueBool, sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestBasic1Cpp::BeginSetBool(bool aValueBool, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetBool, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetBool->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aValueBool));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgTestBasic1Cpp::EndSetBool(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetBool"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyOpenhomeOrgTestBasic1Cpp::SyncGetBool(bool& aValueBool)
{
    SyncGetBoolOpenhomeOrgTestBasic1Cpp sync(*this, aValueBool);
    BeginGetBool(sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestBasic1Cpp::BeginGetBool(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetBool, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetBool->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgTestBasic1Cpp::EndGetBool(IAsync& aAsync, bool& aValueBool)
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

void CpProxyOpenhomeOrgTestBasic1Cpp::SyncSetMultiple(uint32_t aValueUint, int32_t aValueInt, bool aValueBool)
{
    SyncSetMultipleOpenhomeOrgTestBasic1Cpp sync(*this);
    BeginSetMultiple(aValueUint, aValueInt, aValueBool, sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestBasic1Cpp::BeginSetMultiple(uint32_t aValueUint, int32_t aValueInt, bool aValueBool, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetMultiple, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetMultiple->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aValueUint));
    invocation->AddInput(new ArgumentInt(*inParams[inIndex++], aValueInt));
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aValueBool));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgTestBasic1Cpp::EndSetMultiple(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetMultiple"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyOpenhomeOrgTestBasic1Cpp::SyncSetString(const std::string& aValueStr)
{
    SyncSetStringOpenhomeOrgTestBasic1Cpp sync(*this);
    BeginSetString(aValueStr, sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestBasic1Cpp::BeginSetString(const std::string& aValueStr, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetString, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetString->InputParameters();
    {
        Brn buf((const TByte*)aValueStr.c_str(), (TUint)aValueStr.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    iInvocable.InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgTestBasic1Cpp::EndSetString(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetString"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyOpenhomeOrgTestBasic1Cpp::SyncGetString(std::string& aValueStr)
{
    SyncGetStringOpenhomeOrgTestBasic1Cpp sync(*this, aValueStr);
    BeginGetString(sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestBasic1Cpp::BeginGetString(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetString, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetString->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgTestBasic1Cpp::EndGetString(IAsync& aAsync, std::string& aValueStr)
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

void CpProxyOpenhomeOrgTestBasic1Cpp::SyncSetBinary(const std::string& aValueBin)
{
    SyncSetBinaryOpenhomeOrgTestBasic1Cpp sync(*this);
    BeginSetBinary(aValueBin, sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestBasic1Cpp::BeginSetBinary(const std::string& aValueBin, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetBinary, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetBinary->InputParameters();
    {
        Brn buf((const TByte*)aValueBin.c_str(), (TUint)aValueBin.length());
        invocation->AddInput(new ArgumentBinary(*inParams[inIndex++], buf));
    }
    iInvocable.InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgTestBasic1Cpp::EndSetBinary(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetBinary"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyOpenhomeOrgTestBasic1Cpp::SyncGetBinary(std::string& aValueBin)
{
    SyncGetBinaryOpenhomeOrgTestBasic1Cpp sync(*this, aValueBin);
    BeginGetBinary(sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestBasic1Cpp::BeginGetBinary(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetBinary, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetBinary->OutputParameters();
    invocation->AddOutput(new ArgumentBinary(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgTestBasic1Cpp::EndGetBinary(IAsync& aAsync, std::string& aValueBin)
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

void CpProxyOpenhomeOrgTestBasic1Cpp::SyncToggleBool()
{
    SyncToggleBoolOpenhomeOrgTestBasic1Cpp sync(*this);
    BeginToggleBool(sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestBasic1Cpp::BeginToggleBool(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionToggleBool, aFunctor);
    iInvocable.InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgTestBasic1Cpp::EndToggleBool(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("ToggleBool"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyOpenhomeOrgTestBasic1Cpp::SyncWriteFile(const std::string& aData, const std::string& aFileFullName)
{
    SyncWriteFileOpenhomeOrgTestBasic1Cpp sync(*this);
    BeginWriteFile(aData, aFileFullName, sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestBasic1Cpp::BeginWriteFile(const std::string& aData, const std::string& aFileFullName, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionWriteFile, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionWriteFile->InputParameters();
    {
        Brn buf((const TByte*)aData.c_str(), (TUint)aData.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aFileFullName.c_str(), (TUint)aFileFullName.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    iInvocable.InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgTestBasic1Cpp::EndWriteFile(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("WriteFile"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyOpenhomeOrgTestBasic1Cpp::SyncShutdown()
{
    SyncShutdownOpenhomeOrgTestBasic1Cpp sync(*this);
    BeginShutdown(sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestBasic1Cpp::BeginShutdown(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionShutdown, aFunctor);
    iInvocable.InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgTestBasic1Cpp::EndShutdown(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Shutdown"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyOpenhomeOrgTestBasic1Cpp::SetPropertyVarUintChanged(Functor& aFunctor)
{
    iLock->Wait();
    iVarUintChanged = aFunctor;
    iLock->Signal();
}

void CpProxyOpenhomeOrgTestBasic1Cpp::SetPropertyVarIntChanged(Functor& aFunctor)
{
    iLock->Wait();
    iVarIntChanged = aFunctor;
    iLock->Signal();
}

void CpProxyOpenhomeOrgTestBasic1Cpp::SetPropertyVarBoolChanged(Functor& aFunctor)
{
    iLock->Wait();
    iVarBoolChanged = aFunctor;
    iLock->Signal();
}

void CpProxyOpenhomeOrgTestBasic1Cpp::SetPropertyVarStrChanged(Functor& aFunctor)
{
    iLock->Wait();
    iVarStrChanged = aFunctor;
    iLock->Signal();
}

void CpProxyOpenhomeOrgTestBasic1Cpp::SetPropertyVarBinChanged(Functor& aFunctor)
{
    iLock->Wait();
    iVarBinChanged = aFunctor;
    iLock->Signal();
}

void CpProxyOpenhomeOrgTestBasic1Cpp::PropertyVarUint(uint32_t& aVarUint) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aVarUint = iVarUint->Value();
    PropertyReadUnlock();
}

void CpProxyOpenhomeOrgTestBasic1Cpp::PropertyVarInt(int32_t& aVarInt) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aVarInt = iVarInt->Value();
    PropertyReadUnlock();
}

void CpProxyOpenhomeOrgTestBasic1Cpp::PropertyVarBool(bool& aVarBool) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aVarBool = iVarBool->Value();
    PropertyReadUnlock();
}

void CpProxyOpenhomeOrgTestBasic1Cpp::PropertyVarStr(std::string& aVarStr) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iVarStr->Value();
    aVarStr.assign((const char*)val.Ptr(), val.Bytes());
    PropertyReadUnlock();
}

void CpProxyOpenhomeOrgTestBasic1Cpp::PropertyVarBin(std::string& aVarBin) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iVarBin->Value();
    aVarBin.assign((const char*)val.Ptr(), val.Bytes());
    PropertyReadUnlock();
}

void CpProxyOpenhomeOrgTestBasic1Cpp::VarUintPropertyChanged()
{
    ReportEvent(iVarUintChanged);
}

void CpProxyOpenhomeOrgTestBasic1Cpp::VarIntPropertyChanged()
{
    ReportEvent(iVarIntChanged);
}

void CpProxyOpenhomeOrgTestBasic1Cpp::VarBoolPropertyChanged()
{
    ReportEvent(iVarBoolChanged);
}

void CpProxyOpenhomeOrgTestBasic1Cpp::VarStrPropertyChanged()
{
    ReportEvent(iVarStrChanged);
}

void CpProxyOpenhomeOrgTestBasic1Cpp::VarBinPropertyChanged()
{
    ReportEvent(iVarBinChanged);
}

