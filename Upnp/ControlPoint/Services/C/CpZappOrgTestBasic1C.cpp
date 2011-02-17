#include "CpZappOrgTestBasic1.h"
#include <Core/CpDevice.h>
#include <C/CpProxyCPrivate.h>
#include <FunctorAsync.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <Exception.h>
#include <Functor.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Core/CpDevice.h>

using namespace Zapp;

class CpProxyZappOrgTestBasic1C : public CpProxyC
{
public:
    CpProxyZappOrgTestBasic1C(CpDeviceC aDevice);
    ~CpProxyZappOrgTestBasic1C();
    //CpProxyZappOrgTestBasic1* Proxy() { return static_cast<CpProxyZappOrgTestBasic1*>(iProxy); }

    void SyncIncrement(TUint aValue, TUint& aResult);
    void BeginIncrement(TUint aValue, FunctorAsync& aFunctor);
    void EndIncrement(IAsync& aAsync, TUint& aResult);

    void SyncDecrement(TInt aValue, TInt& aResult);
    void BeginDecrement(TInt aValue, FunctorAsync& aFunctor);
    void EndDecrement(IAsync& aAsync, TInt& aResult);

    void SyncToggle(TBool aValue, TBool& aResult);
    void BeginToggle(TBool aValue, FunctorAsync& aFunctor);
    void EndToggle(IAsync& aAsync, TBool& aResult);

    void SyncEchoString(const Brx& aValue, Brh& aResult);
    void BeginEchoString(const Brx& aValue, FunctorAsync& aFunctor);
    void EndEchoString(IAsync& aAsync, Brh& aResult);

    void SyncEchoBinary(const Brx& aValue, Brh& aResult);
    void BeginEchoBinary(const Brx& aValue, FunctorAsync& aFunctor);
    void EndEchoBinary(IAsync& aAsync, Brh& aResult);

    void SyncSetUint(TUint aValueUint);
    void BeginSetUint(TUint aValueUint, FunctorAsync& aFunctor);
    void EndSetUint(IAsync& aAsync);

    void SyncGetUint(TUint& aValueUint);
    void BeginGetUint(FunctorAsync& aFunctor);
    void EndGetUint(IAsync& aAsync, TUint& aValueUint);

    void SyncSetInt(TInt aValueInt);
    void BeginSetInt(TInt aValueInt, FunctorAsync& aFunctor);
    void EndSetInt(IAsync& aAsync);

    void SyncGetInt(TInt& aValueInt);
    void BeginGetInt(FunctorAsync& aFunctor);
    void EndGetInt(IAsync& aAsync, TInt& aValueInt);

    void SyncSetBool(TBool aValueBool);
    void BeginSetBool(TBool aValueBool, FunctorAsync& aFunctor);
    void EndSetBool(IAsync& aAsync);

    void SyncGetBool(TBool& aValueBool);
    void BeginGetBool(FunctorAsync& aFunctor);
    void EndGetBool(IAsync& aAsync, TBool& aValueBool);

    void SyncSetMultiple(TUint aValueUint, TInt aValueInt, TBool aValueBool);
    void BeginSetMultiple(TUint aValueUint, TInt aValueInt, TBool aValueBool, FunctorAsync& aFunctor);
    void EndSetMultiple(IAsync& aAsync);

    void SyncSetString(const Brx& aValueStr);
    void BeginSetString(const Brx& aValueStr, FunctorAsync& aFunctor);
    void EndSetString(IAsync& aAsync);

    void SyncGetString(Brh& aValueStr);
    void BeginGetString(FunctorAsync& aFunctor);
    void EndGetString(IAsync& aAsync, Brh& aValueStr);

    void SyncSetBinary(const Brx& aValueBin);
    void BeginSetBinary(const Brx& aValueBin, FunctorAsync& aFunctor);
    void EndSetBinary(IAsync& aAsync);

    void SyncGetBinary(Brh& aValueBin);
    void BeginGetBinary(FunctorAsync& aFunctor);
    void EndGetBinary(IAsync& aAsync, Brh& aValueBin);

    void SyncToggleBool();
    void BeginToggleBool(FunctorAsync& aFunctor);
    void EndToggleBool(IAsync& aAsync);

    void SyncWriteFile(const Brx& aData, const Brx& aFileFullName);
    void BeginWriteFile(const Brx& aData, const Brx& aFileFullName, FunctorAsync& aFunctor);
    void EndWriteFile(IAsync& aAsync);

    void SyncShutdown();
    void BeginShutdown(FunctorAsync& aFunctor);
    void EndShutdown(IAsync& aAsync);

    void SetPropertyVarUintChanged(Functor& aFunctor);
    void SetPropertyVarIntChanged(Functor& aFunctor);
    void SetPropertyVarBoolChanged(Functor& aFunctor);
    void SetPropertyVarStrChanged(Functor& aFunctor);
    void SetPropertyVarBinChanged(Functor& aFunctor);

    void PropertyVarUint(TUint& aVarUint) const;
    void PropertyVarInt(TInt& aVarInt) const;
    void PropertyVarBool(TBool& aVarBool) const;
    void PropertyVarStr(Brhz& aVarStr) const;
    void PropertyVarBin(Brh& aVarBin) const;
private:
    void VarUintPropertyChanged();
    void VarIntPropertyChanged();
    void VarBoolPropertyChanged();
    void VarStrPropertyChanged();
    void VarBinPropertyChanged();
private:
    Mutex iLock;
    Action* iActionIncrement;
    Action* iActionDecrement;
    Action* iActionToggle;
    Action* iActionEchoString;
    Action* iActionEchoBinary;
    Action* iActionSetUint;
    Action* iActionGetUint;
    Action* iActionSetInt;
    Action* iActionGetInt;
    Action* iActionSetBool;
    Action* iActionGetBool;
    Action* iActionSetMultiple;
    Action* iActionSetString;
    Action* iActionGetString;
    Action* iActionSetBinary;
    Action* iActionGetBinary;
    Action* iActionToggleBool;
    Action* iActionWriteFile;
    Action* iActionShutdown;
    PropertyUint* iVarUint;
    PropertyInt* iVarInt;
    PropertyBool* iVarBool;
    PropertyString* iVarStr;
    PropertyBinary* iVarBin;
    Functor iVarUintChanged;
    Functor iVarIntChanged;
    Functor iVarBoolChanged;
    Functor iVarStrChanged;
    Functor iVarBinChanged;
};


class SyncIncrementZappOrgTestBasic1C : public SyncProxyAction
{
public:
    SyncIncrementZappOrgTestBasic1C(CpProxyZappOrgTestBasic1C& aProxy, TUint& aResult);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestBasic1C& iService;
    TUint& iResult;
};

SyncIncrementZappOrgTestBasic1C::SyncIncrementZappOrgTestBasic1C(CpProxyZappOrgTestBasic1C& aProxy, TUint& aResult)
    : iService(aProxy)
    , iResult(aResult)
{
}

void SyncIncrementZappOrgTestBasic1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndIncrement(aAsync, iResult);
}


class SyncDecrementZappOrgTestBasic1C : public SyncProxyAction
{
public:
    SyncDecrementZappOrgTestBasic1C(CpProxyZappOrgTestBasic1C& aProxy, TInt& aResult);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestBasic1C& iService;
    TInt& iResult;
};

SyncDecrementZappOrgTestBasic1C::SyncDecrementZappOrgTestBasic1C(CpProxyZappOrgTestBasic1C& aProxy, TInt& aResult)
    : iService(aProxy)
    , iResult(aResult)
{
}

void SyncDecrementZappOrgTestBasic1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndDecrement(aAsync, iResult);
}


class SyncToggleZappOrgTestBasic1C : public SyncProxyAction
{
public:
    SyncToggleZappOrgTestBasic1C(CpProxyZappOrgTestBasic1C& aProxy, TBool& aResult);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestBasic1C& iService;
    TBool& iResult;
};

SyncToggleZappOrgTestBasic1C::SyncToggleZappOrgTestBasic1C(CpProxyZappOrgTestBasic1C& aProxy, TBool& aResult)
    : iService(aProxy)
    , iResult(aResult)
{
}

void SyncToggleZappOrgTestBasic1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndToggle(aAsync, iResult);
}


class SyncEchoStringZappOrgTestBasic1C : public SyncProxyAction
{
public:
    SyncEchoStringZappOrgTestBasic1C(CpProxyZappOrgTestBasic1C& aProxy, Brh& aResult);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestBasic1C& iService;
    Brh& iResult;
};

SyncEchoStringZappOrgTestBasic1C::SyncEchoStringZappOrgTestBasic1C(CpProxyZappOrgTestBasic1C& aProxy, Brh& aResult)
    : iService(aProxy)
    , iResult(aResult)
{
}

void SyncEchoStringZappOrgTestBasic1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndEchoString(aAsync, iResult);
}


class SyncEchoBinaryZappOrgTestBasic1C : public SyncProxyAction
{
public:
    SyncEchoBinaryZappOrgTestBasic1C(CpProxyZappOrgTestBasic1C& aProxy, Brh& aResult);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestBasic1C& iService;
    Brh& iResult;
};

SyncEchoBinaryZappOrgTestBasic1C::SyncEchoBinaryZappOrgTestBasic1C(CpProxyZappOrgTestBasic1C& aProxy, Brh& aResult)
    : iService(aProxy)
    , iResult(aResult)
{
}

void SyncEchoBinaryZappOrgTestBasic1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndEchoBinary(aAsync, iResult);
}


class SyncSetUintZappOrgTestBasic1C : public SyncProxyAction
{
public:
    SyncSetUintZappOrgTestBasic1C(CpProxyZappOrgTestBasic1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestBasic1C& iService;
};

SyncSetUintZappOrgTestBasic1C::SyncSetUintZappOrgTestBasic1C(CpProxyZappOrgTestBasic1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetUintZappOrgTestBasic1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetUint(aAsync);
}


class SyncGetUintZappOrgTestBasic1C : public SyncProxyAction
{
public:
    SyncGetUintZappOrgTestBasic1C(CpProxyZappOrgTestBasic1C& aProxy, TUint& aValueUint);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestBasic1C& iService;
    TUint& iValueUint;
};

SyncGetUintZappOrgTestBasic1C::SyncGetUintZappOrgTestBasic1C(CpProxyZappOrgTestBasic1C& aProxy, TUint& aValueUint)
    : iService(aProxy)
    , iValueUint(aValueUint)
{
}

void SyncGetUintZappOrgTestBasic1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetUint(aAsync, iValueUint);
}


class SyncSetIntZappOrgTestBasic1C : public SyncProxyAction
{
public:
    SyncSetIntZappOrgTestBasic1C(CpProxyZappOrgTestBasic1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestBasic1C& iService;
};

SyncSetIntZappOrgTestBasic1C::SyncSetIntZappOrgTestBasic1C(CpProxyZappOrgTestBasic1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetIntZappOrgTestBasic1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetInt(aAsync);
}


class SyncGetIntZappOrgTestBasic1C : public SyncProxyAction
{
public:
    SyncGetIntZappOrgTestBasic1C(CpProxyZappOrgTestBasic1C& aProxy, TInt& aValueInt);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestBasic1C& iService;
    TInt& iValueInt;
};

SyncGetIntZappOrgTestBasic1C::SyncGetIntZappOrgTestBasic1C(CpProxyZappOrgTestBasic1C& aProxy, TInt& aValueInt)
    : iService(aProxy)
    , iValueInt(aValueInt)
{
}

void SyncGetIntZappOrgTestBasic1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetInt(aAsync, iValueInt);
}


class SyncSetBoolZappOrgTestBasic1C : public SyncProxyAction
{
public:
    SyncSetBoolZappOrgTestBasic1C(CpProxyZappOrgTestBasic1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestBasic1C& iService;
};

SyncSetBoolZappOrgTestBasic1C::SyncSetBoolZappOrgTestBasic1C(CpProxyZappOrgTestBasic1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetBoolZappOrgTestBasic1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetBool(aAsync);
}


class SyncGetBoolZappOrgTestBasic1C : public SyncProxyAction
{
public:
    SyncGetBoolZappOrgTestBasic1C(CpProxyZappOrgTestBasic1C& aProxy, TBool& aValueBool);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestBasic1C& iService;
    TBool& iValueBool;
};

SyncGetBoolZappOrgTestBasic1C::SyncGetBoolZappOrgTestBasic1C(CpProxyZappOrgTestBasic1C& aProxy, TBool& aValueBool)
    : iService(aProxy)
    , iValueBool(aValueBool)
{
}

void SyncGetBoolZappOrgTestBasic1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetBool(aAsync, iValueBool);
}


class SyncSetMultipleZappOrgTestBasic1C : public SyncProxyAction
{
public:
    SyncSetMultipleZappOrgTestBasic1C(CpProxyZappOrgTestBasic1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestBasic1C& iService;
};

SyncSetMultipleZappOrgTestBasic1C::SyncSetMultipleZappOrgTestBasic1C(CpProxyZappOrgTestBasic1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetMultipleZappOrgTestBasic1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetMultiple(aAsync);
}


class SyncSetStringZappOrgTestBasic1C : public SyncProxyAction
{
public:
    SyncSetStringZappOrgTestBasic1C(CpProxyZappOrgTestBasic1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestBasic1C& iService;
};

SyncSetStringZappOrgTestBasic1C::SyncSetStringZappOrgTestBasic1C(CpProxyZappOrgTestBasic1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetStringZappOrgTestBasic1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetString(aAsync);
}


class SyncGetStringZappOrgTestBasic1C : public SyncProxyAction
{
public:
    SyncGetStringZappOrgTestBasic1C(CpProxyZappOrgTestBasic1C& aProxy, Brh& aValueStr);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestBasic1C& iService;
    Brh& iValueStr;
};

SyncGetStringZappOrgTestBasic1C::SyncGetStringZappOrgTestBasic1C(CpProxyZappOrgTestBasic1C& aProxy, Brh& aValueStr)
    : iService(aProxy)
    , iValueStr(aValueStr)
{
}

void SyncGetStringZappOrgTestBasic1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetString(aAsync, iValueStr);
}


class SyncSetBinaryZappOrgTestBasic1C : public SyncProxyAction
{
public:
    SyncSetBinaryZappOrgTestBasic1C(CpProxyZappOrgTestBasic1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestBasic1C& iService;
};

SyncSetBinaryZappOrgTestBasic1C::SyncSetBinaryZappOrgTestBasic1C(CpProxyZappOrgTestBasic1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetBinaryZappOrgTestBasic1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetBinary(aAsync);
}


class SyncGetBinaryZappOrgTestBasic1C : public SyncProxyAction
{
public:
    SyncGetBinaryZappOrgTestBasic1C(CpProxyZappOrgTestBasic1C& aProxy, Brh& aValueBin);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestBasic1C& iService;
    Brh& iValueBin;
};

SyncGetBinaryZappOrgTestBasic1C::SyncGetBinaryZappOrgTestBasic1C(CpProxyZappOrgTestBasic1C& aProxy, Brh& aValueBin)
    : iService(aProxy)
    , iValueBin(aValueBin)
{
}

void SyncGetBinaryZappOrgTestBasic1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetBinary(aAsync, iValueBin);
}


class SyncToggleBoolZappOrgTestBasic1C : public SyncProxyAction
{
public:
    SyncToggleBoolZappOrgTestBasic1C(CpProxyZappOrgTestBasic1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestBasic1C& iService;
};

SyncToggleBoolZappOrgTestBasic1C::SyncToggleBoolZappOrgTestBasic1C(CpProxyZappOrgTestBasic1C& aProxy)
    : iService(aProxy)
{
}

void SyncToggleBoolZappOrgTestBasic1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndToggleBool(aAsync);
}


class SyncWriteFileZappOrgTestBasic1C : public SyncProxyAction
{
public:
    SyncWriteFileZappOrgTestBasic1C(CpProxyZappOrgTestBasic1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestBasic1C& iService;
};

SyncWriteFileZappOrgTestBasic1C::SyncWriteFileZappOrgTestBasic1C(CpProxyZappOrgTestBasic1C& aProxy)
    : iService(aProxy)
{
}

void SyncWriteFileZappOrgTestBasic1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndWriteFile(aAsync);
}


class SyncShutdownZappOrgTestBasic1C : public SyncProxyAction
{
public:
    SyncShutdownZappOrgTestBasic1C(CpProxyZappOrgTestBasic1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestBasic1C& iService;
};

SyncShutdownZappOrgTestBasic1C::SyncShutdownZappOrgTestBasic1C(CpProxyZappOrgTestBasic1C& aProxy)
    : iService(aProxy)
{
}

void SyncShutdownZappOrgTestBasic1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndShutdown(aAsync);
}

CpProxyZappOrgTestBasic1C::CpProxyZappOrgTestBasic1C(CpDeviceC aDevice)
    : CpProxyC("zapp-org", "TestBasic", 1, *reinterpret_cast<CpiDevice*>(aDevice))
    , iLock("MPCS")
{
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

    iActionToggleBool = new Action("ToggleBool");

    iActionWriteFile = new Action("WriteFile");
    param = new Zapp::ParameterString("Data");
    iActionWriteFile->AddInputParameter(param);
    param = new Zapp::ParameterString("FileFullName");
    iActionWriteFile->AddInputParameter(param);

    iActionShutdown = new Action("Shutdown");

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyZappOrgTestBasic1C::VarUintPropertyChanged);
    iVarUint = new PropertyUint("VarUint", functor);
    AddProperty(iVarUint);
    functor = MakeFunctor(*this, &CpProxyZappOrgTestBasic1C::VarIntPropertyChanged);
    iVarInt = new PropertyInt("VarInt", functor);
    AddProperty(iVarInt);
    functor = MakeFunctor(*this, &CpProxyZappOrgTestBasic1C::VarBoolPropertyChanged);
    iVarBool = new PropertyBool("VarBool", functor);
    AddProperty(iVarBool);
    functor = MakeFunctor(*this, &CpProxyZappOrgTestBasic1C::VarStrPropertyChanged);
    iVarStr = new PropertyString("VarStr", functor);
    AddProperty(iVarStr);
    functor = MakeFunctor(*this, &CpProxyZappOrgTestBasic1C::VarBinPropertyChanged);
    iVarBin = new PropertyBinary("VarBin", functor);
    AddProperty(iVarBin);
}

CpProxyZappOrgTestBasic1C::~CpProxyZappOrgTestBasic1C()
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

void CpProxyZappOrgTestBasic1C::SyncIncrement(TUint aValue, TUint& aResult)
{
    SyncIncrementZappOrgTestBasic1C sync(*this, aResult);
    BeginIncrement(aValue, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestBasic1C::BeginIncrement(TUint aValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionIncrement, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionIncrement->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aValue));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionIncrement->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyZappOrgTestBasic1C::EndIncrement(IAsync& aAsync, TUint& aResult)
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

void CpProxyZappOrgTestBasic1C::SyncDecrement(TInt aValue, TInt& aResult)
{
    SyncDecrementZappOrgTestBasic1C sync(*this, aResult);
    BeginDecrement(aValue, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestBasic1C::BeginDecrement(TInt aValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionDecrement, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionDecrement->InputParameters();
    invocation->AddInput(new ArgumentInt(*inParams[inIndex++], aValue));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionDecrement->OutputParameters();
    invocation->AddOutput(new ArgumentInt(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyZappOrgTestBasic1C::EndDecrement(IAsync& aAsync, TInt& aResult)
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

void CpProxyZappOrgTestBasic1C::SyncToggle(TBool aValue, TBool& aResult)
{
    SyncToggleZappOrgTestBasic1C sync(*this, aResult);
    BeginToggle(aValue, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestBasic1C::BeginToggle(TBool aValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionToggle, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionToggle->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aValue));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionToggle->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyZappOrgTestBasic1C::EndToggle(IAsync& aAsync, TBool& aResult)
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

void CpProxyZappOrgTestBasic1C::SyncEchoString(const Brx& aValue, Brh& aResult)
{
    SyncEchoStringZappOrgTestBasic1C sync(*this, aResult);
    BeginEchoString(aValue, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestBasic1C::BeginEchoString(const Brx& aValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionEchoString, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionEchoString->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aValue));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionEchoString->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyZappOrgTestBasic1C::EndEchoString(IAsync& aAsync, Brh& aResult)
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

void CpProxyZappOrgTestBasic1C::SyncEchoBinary(const Brx& aValue, Brh& aResult)
{
    SyncEchoBinaryZappOrgTestBasic1C sync(*this, aResult);
    BeginEchoBinary(aValue, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestBasic1C::BeginEchoBinary(const Brx& aValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionEchoBinary, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionEchoBinary->InputParameters();
    invocation->AddInput(new ArgumentBinary(*inParams[inIndex++], aValue));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionEchoBinary->OutputParameters();
    invocation->AddOutput(new ArgumentBinary(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyZappOrgTestBasic1C::EndEchoBinary(IAsync& aAsync, Brh& aResult)
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

void CpProxyZappOrgTestBasic1C::SyncSetUint(TUint aValueUint)
{
    SyncSetUintZappOrgTestBasic1C sync(*this);
    BeginSetUint(aValueUint, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestBasic1C::BeginSetUint(TUint aValueUint, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetUint, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetUint->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aValueUint));
    Invocable().InvokeAction(*invocation);
}

void CpProxyZappOrgTestBasic1C::EndSetUint(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetUint"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyZappOrgTestBasic1C::SyncGetUint(TUint& aValueUint)
{
    SyncGetUintZappOrgTestBasic1C sync(*this, aValueUint);
    BeginGetUint(sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestBasic1C::BeginGetUint(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetUint, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetUint->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyZappOrgTestBasic1C::EndGetUint(IAsync& aAsync, TUint& aValueUint)
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

void CpProxyZappOrgTestBasic1C::SyncSetInt(TInt aValueInt)
{
    SyncSetIntZappOrgTestBasic1C sync(*this);
    BeginSetInt(aValueInt, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestBasic1C::BeginSetInt(TInt aValueInt, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetInt, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetInt->InputParameters();
    invocation->AddInput(new ArgumentInt(*inParams[inIndex++], aValueInt));
    Invocable().InvokeAction(*invocation);
}

void CpProxyZappOrgTestBasic1C::EndSetInt(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetInt"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyZappOrgTestBasic1C::SyncGetInt(TInt& aValueInt)
{
    SyncGetIntZappOrgTestBasic1C sync(*this, aValueInt);
    BeginGetInt(sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestBasic1C::BeginGetInt(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetInt, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetInt->OutputParameters();
    invocation->AddOutput(new ArgumentInt(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyZappOrgTestBasic1C::EndGetInt(IAsync& aAsync, TInt& aValueInt)
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

void CpProxyZappOrgTestBasic1C::SyncSetBool(TBool aValueBool)
{
    SyncSetBoolZappOrgTestBasic1C sync(*this);
    BeginSetBool(aValueBool, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestBasic1C::BeginSetBool(TBool aValueBool, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetBool, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetBool->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aValueBool));
    Invocable().InvokeAction(*invocation);
}

void CpProxyZappOrgTestBasic1C::EndSetBool(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetBool"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyZappOrgTestBasic1C::SyncGetBool(TBool& aValueBool)
{
    SyncGetBoolZappOrgTestBasic1C sync(*this, aValueBool);
    BeginGetBool(sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestBasic1C::BeginGetBool(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetBool, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetBool->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyZappOrgTestBasic1C::EndGetBool(IAsync& aAsync, TBool& aValueBool)
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

void CpProxyZappOrgTestBasic1C::SyncSetMultiple(TUint aValueUint, TInt aValueInt, TBool aValueBool)
{
    SyncSetMultipleZappOrgTestBasic1C sync(*this);
    BeginSetMultiple(aValueUint, aValueInt, aValueBool, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestBasic1C::BeginSetMultiple(TUint aValueUint, TInt aValueInt, TBool aValueBool, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetMultiple, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetMultiple->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aValueUint));
    invocation->AddInput(new ArgumentInt(*inParams[inIndex++], aValueInt));
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aValueBool));
    Invocable().InvokeAction(*invocation);
}

void CpProxyZappOrgTestBasic1C::EndSetMultiple(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetMultiple"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyZappOrgTestBasic1C::SyncSetString(const Brx& aValueStr)
{
    SyncSetStringZappOrgTestBasic1C sync(*this);
    BeginSetString(aValueStr, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestBasic1C::BeginSetString(const Brx& aValueStr, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetString, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetString->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aValueStr));
    Invocable().InvokeAction(*invocation);
}

void CpProxyZappOrgTestBasic1C::EndSetString(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetString"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyZappOrgTestBasic1C::SyncGetString(Brh& aValueStr)
{
    SyncGetStringZappOrgTestBasic1C sync(*this, aValueStr);
    BeginGetString(sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestBasic1C::BeginGetString(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetString, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetString->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyZappOrgTestBasic1C::EndGetString(IAsync& aAsync, Brh& aValueStr)
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

void CpProxyZappOrgTestBasic1C::SyncSetBinary(const Brx& aValueBin)
{
    SyncSetBinaryZappOrgTestBasic1C sync(*this);
    BeginSetBinary(aValueBin, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestBasic1C::BeginSetBinary(const Brx& aValueBin, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetBinary, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetBinary->InputParameters();
    invocation->AddInput(new ArgumentBinary(*inParams[inIndex++], aValueBin));
    Invocable().InvokeAction(*invocation);
}

void CpProxyZappOrgTestBasic1C::EndSetBinary(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetBinary"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyZappOrgTestBasic1C::SyncGetBinary(Brh& aValueBin)
{
    SyncGetBinaryZappOrgTestBasic1C sync(*this, aValueBin);
    BeginGetBinary(sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestBasic1C::BeginGetBinary(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetBinary, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetBinary->OutputParameters();
    invocation->AddOutput(new ArgumentBinary(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyZappOrgTestBasic1C::EndGetBinary(IAsync& aAsync, Brh& aValueBin)
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

void CpProxyZappOrgTestBasic1C::SyncToggleBool()
{
    SyncToggleBoolZappOrgTestBasic1C sync(*this);
    BeginToggleBool(sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestBasic1C::BeginToggleBool(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionToggleBool, aFunctor);
    Invocable().InvokeAction(*invocation);
}

void CpProxyZappOrgTestBasic1C::EndToggleBool(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("ToggleBool"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyZappOrgTestBasic1C::SyncWriteFile(const Brx& aData, const Brx& aFileFullName)
{
    SyncWriteFileZappOrgTestBasic1C sync(*this);
    BeginWriteFile(aData, aFileFullName, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestBasic1C::BeginWriteFile(const Brx& aData, const Brx& aFileFullName, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionWriteFile, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionWriteFile->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aData));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aFileFullName));
    Invocable().InvokeAction(*invocation);
}

void CpProxyZappOrgTestBasic1C::EndWriteFile(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("WriteFile"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyZappOrgTestBasic1C::SyncShutdown()
{
    SyncShutdownZappOrgTestBasic1C sync(*this);
    BeginShutdown(sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestBasic1C::BeginShutdown(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionShutdown, aFunctor);
    Invocable().InvokeAction(*invocation);
}

void CpProxyZappOrgTestBasic1C::EndShutdown(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Shutdown"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyZappOrgTestBasic1C::SetPropertyVarUintChanged(Functor& aFunctor)
{
    iLock.Wait();
    iVarUintChanged = aFunctor;
    iLock.Signal();
}

void CpProxyZappOrgTestBasic1C::SetPropertyVarIntChanged(Functor& aFunctor)
{
    iLock.Wait();
    iVarIntChanged = aFunctor;
    iLock.Signal();
}

void CpProxyZappOrgTestBasic1C::SetPropertyVarBoolChanged(Functor& aFunctor)
{
    iLock.Wait();
    iVarBoolChanged = aFunctor;
    iLock.Signal();
}

void CpProxyZappOrgTestBasic1C::SetPropertyVarStrChanged(Functor& aFunctor)
{
    iLock.Wait();
    iVarStrChanged = aFunctor;
    iLock.Signal();
}

void CpProxyZappOrgTestBasic1C::SetPropertyVarBinChanged(Functor& aFunctor)
{
    iLock.Wait();
    iVarBinChanged = aFunctor;
    iLock.Signal();
}

void CpProxyZappOrgTestBasic1C::PropertyVarUint(TUint& aVarUint) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aVarUint = iVarUint->Value();
    PropertyReadUnlock();
}

void CpProxyZappOrgTestBasic1C::PropertyVarInt(TInt& aVarInt) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aVarInt = iVarInt->Value();
    PropertyReadUnlock();
}

void CpProxyZappOrgTestBasic1C::PropertyVarBool(TBool& aVarBool) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aVarBool = iVarBool->Value();
    PropertyReadUnlock();
}

void CpProxyZappOrgTestBasic1C::PropertyVarStr(Brhz& aVarStr) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aVarStr.Set(iVarStr->Value());
    PropertyReadUnlock();
}

void CpProxyZappOrgTestBasic1C::PropertyVarBin(Brh& aVarBin) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aVarBin.Set(iVarBin->Value());
    PropertyReadUnlock();
}

void CpProxyZappOrgTestBasic1C::VarUintPropertyChanged()
{
    ReportEvent(iVarUintChanged);
}

void CpProxyZappOrgTestBasic1C::VarIntPropertyChanged()
{
    ReportEvent(iVarIntChanged);
}

void CpProxyZappOrgTestBasic1C::VarBoolPropertyChanged()
{
    ReportEvent(iVarBoolChanged);
}

void CpProxyZappOrgTestBasic1C::VarStrPropertyChanged()
{
    ReportEvent(iVarStrChanged);
}

void CpProxyZappOrgTestBasic1C::VarBinPropertyChanged()
{
    ReportEvent(iVarBinChanged);
}


THandle CpProxyZappOrgTestBasic1Create(CpDeviceC aDevice)
{
    return new CpProxyZappOrgTestBasic1C(aDevice);
}

void CpProxyZappOrgTestBasic1Destroy(THandle aHandle)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    delete proxyC;
}

void CpProxyZappOrgTestBasic1SyncIncrement(THandle aHandle, uint32_t aValue, uint32_t* aResult)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncIncrement(aValue, *aResult);
}

void CpProxyZappOrgTestBasic1BeginIncrement(THandle aHandle, uint32_t aValue, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginIncrement(aValue, functor);
}

int32_t CpProxyZappOrgTestBasic1EndIncrement(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aResult)
{
    int32_t err = 0;
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndIncrement(*async, *aResult);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyZappOrgTestBasic1SyncDecrement(THandle aHandle, int32_t aValue, int32_t* aResult)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncDecrement(aValue, *aResult);
}

void CpProxyZappOrgTestBasic1BeginDecrement(THandle aHandle, int32_t aValue, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginDecrement(aValue, functor);
}

int32_t CpProxyZappOrgTestBasic1EndDecrement(THandle aHandle, ZappHandleAsync aAsync, int32_t* aResult)
{
    int32_t err = 0;
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndDecrement(*async, *aResult);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyZappOrgTestBasic1SyncToggle(THandle aHandle, uint32_t aValue, uint32_t* aResult)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aResult = 0;
    proxyC->SyncToggle((aValue==0? false : true), *(TBool*)aResult);
}

void CpProxyZappOrgTestBasic1BeginToggle(THandle aHandle, uint32_t aValue, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginToggle((aValue==0? false : true), functor);
}

int32_t CpProxyZappOrgTestBasic1EndToggle(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aResult)
{
    int32_t err = 0;
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    *aResult = 0;
    try {
        proxyC->EndToggle(*async, *(TBool*)aResult);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyZappOrgTestBasic1SyncEchoString(THandle aHandle, const char* aValue, char** aResult)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aValue(aValue);
    Brh buf_aResult;
    proxyC->SyncEchoString(buf_aValue, buf_aResult);
    *aResult = buf_aResult.Extract();
}

void CpProxyZappOrgTestBasic1BeginEchoString(THandle aHandle, const char* aValue, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aValue(aValue);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginEchoString(buf_aValue, functor);
}

int32_t CpProxyZappOrgTestBasic1EndEchoString(THandle aHandle, ZappHandleAsync aAsync, char** aResult)
{
    int32_t err = 0;
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aResult;
    *aResult = NULL;
    try {
        proxyC->EndEchoString(*async, buf_aResult);
        *aResult = buf_aResult.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyZappOrgTestBasic1SyncEchoBinary(THandle aHandle, const char* aValue, uint32_t aValueLen, char** aResult, uint32_t* aResultLen)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aValue;
    buf_aValue.Set((const TByte*)aValue, aValueLen);
    Brh buf_aResult;
    proxyC->SyncEchoBinary(buf_aValue, buf_aResult);
    *aResultLen = buf_aResult.Bytes();
    *aResult = buf_aResult.Extract();
}

void CpProxyZappOrgTestBasic1BeginEchoBinary(THandle aHandle, const char* aValue, uint32_t aValueLen, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aValue;
    buf_aValue.Set((const TByte*)aValue, aValueLen);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginEchoBinary(buf_aValue, functor);
}

int32_t CpProxyZappOrgTestBasic1EndEchoBinary(THandle aHandle, ZappHandleAsync aAsync, char** aResult, uint32_t* aResultLen)
{
    int32_t err = 0;
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aResult;
    *aResult = NULL;
    *aResultLen = 0;
    try {
        proxyC->EndEchoBinary(*async, buf_aResult);
        *aResultLen = buf_aResult.Bytes();
        *aResult = buf_aResult.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyZappOrgTestBasic1SyncSetUint(THandle aHandle, uint32_t aValueUint)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSetUint(aValueUint);
}

void CpProxyZappOrgTestBasic1BeginSetUint(THandle aHandle, uint32_t aValueUint, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetUint(aValueUint, functor);
}

int32_t CpProxyZappOrgTestBasic1EndSetUint(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetUint(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyZappOrgTestBasic1SyncGetUint(THandle aHandle, uint32_t* aValueUint)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncGetUint(*aValueUint);
}

void CpProxyZappOrgTestBasic1BeginGetUint(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginGetUint(functor);
}

int32_t CpProxyZappOrgTestBasic1EndGetUint(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aValueUint)
{
    int32_t err = 0;
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndGetUint(*async, *aValueUint);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyZappOrgTestBasic1SyncSetInt(THandle aHandle, int32_t aValueInt)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSetInt(aValueInt);
}

void CpProxyZappOrgTestBasic1BeginSetInt(THandle aHandle, int32_t aValueInt, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetInt(aValueInt, functor);
}

int32_t CpProxyZappOrgTestBasic1EndSetInt(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetInt(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyZappOrgTestBasic1SyncGetInt(THandle aHandle, int32_t* aValueInt)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncGetInt(*aValueInt);
}

void CpProxyZappOrgTestBasic1BeginGetInt(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginGetInt(functor);
}

int32_t CpProxyZappOrgTestBasic1EndGetInt(THandle aHandle, ZappHandleAsync aAsync, int32_t* aValueInt)
{
    int32_t err = 0;
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndGetInt(*async, *aValueInt);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyZappOrgTestBasic1SyncSetBool(THandle aHandle, uint32_t aValueBool)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSetBool((aValueBool==0? false : true));
}

void CpProxyZappOrgTestBasic1BeginSetBool(THandle aHandle, uint32_t aValueBool, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetBool((aValueBool==0? false : true), functor);
}

int32_t CpProxyZappOrgTestBasic1EndSetBool(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetBool(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyZappOrgTestBasic1SyncGetBool(THandle aHandle, uint32_t* aValueBool)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aValueBool = 0;
    proxyC->SyncGetBool(*(TBool*)aValueBool);
}

void CpProxyZappOrgTestBasic1BeginGetBool(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginGetBool(functor);
}

int32_t CpProxyZappOrgTestBasic1EndGetBool(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aValueBool)
{
    int32_t err = 0;
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    *aValueBool = 0;
    try {
        proxyC->EndGetBool(*async, *(TBool*)aValueBool);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyZappOrgTestBasic1SyncSetMultiple(THandle aHandle, uint32_t aValueUint, int32_t aValueInt, uint32_t aValueBool)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSetMultiple(aValueUint, aValueInt, (aValueBool==0? false : true));
}

void CpProxyZappOrgTestBasic1BeginSetMultiple(THandle aHandle, uint32_t aValueUint, int32_t aValueInt, uint32_t aValueBool, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetMultiple(aValueUint, aValueInt, (aValueBool==0? false : true), functor);
}

int32_t CpProxyZappOrgTestBasic1EndSetMultiple(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetMultiple(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyZappOrgTestBasic1SyncSetString(THandle aHandle, const char* aValueStr)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aValueStr(aValueStr);
    proxyC->SyncSetString(buf_aValueStr);
}

void CpProxyZappOrgTestBasic1BeginSetString(THandle aHandle, const char* aValueStr, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aValueStr(aValueStr);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetString(buf_aValueStr, functor);
}

int32_t CpProxyZappOrgTestBasic1EndSetString(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetString(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyZappOrgTestBasic1SyncGetString(THandle aHandle, char** aValueStr)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aValueStr;
    proxyC->SyncGetString(buf_aValueStr);
    *aValueStr = buf_aValueStr.Extract();
}

void CpProxyZappOrgTestBasic1BeginGetString(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginGetString(functor);
}

int32_t CpProxyZappOrgTestBasic1EndGetString(THandle aHandle, ZappHandleAsync aAsync, char** aValueStr)
{
    int32_t err = 0;
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aValueStr;
    *aValueStr = NULL;
    try {
        proxyC->EndGetString(*async, buf_aValueStr);
        *aValueStr = buf_aValueStr.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyZappOrgTestBasic1SyncSetBinary(THandle aHandle, const char* aValueBin, uint32_t aValueBinLen)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aValueBin;
    buf_aValueBin.Set((const TByte*)aValueBin, aValueBinLen);
    proxyC->SyncSetBinary(buf_aValueBin);
}

void CpProxyZappOrgTestBasic1BeginSetBinary(THandle aHandle, const char* aValueBin, uint32_t aValueBinLen, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aValueBin;
    buf_aValueBin.Set((const TByte*)aValueBin, aValueBinLen);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetBinary(buf_aValueBin, functor);
}

int32_t CpProxyZappOrgTestBasic1EndSetBinary(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetBinary(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyZappOrgTestBasic1SyncGetBinary(THandle aHandle, char** aValueBin, uint32_t* aValueBinLen)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aValueBin;
    proxyC->SyncGetBinary(buf_aValueBin);
    *aValueBinLen = buf_aValueBin.Bytes();
    *aValueBin = buf_aValueBin.Extract();
}

void CpProxyZappOrgTestBasic1BeginGetBinary(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginGetBinary(functor);
}

int32_t CpProxyZappOrgTestBasic1EndGetBinary(THandle aHandle, ZappHandleAsync aAsync, char** aValueBin, uint32_t* aValueBinLen)
{
    int32_t err = 0;
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aValueBin;
    *aValueBin = NULL;
    *aValueBinLen = 0;
    try {
        proxyC->EndGetBinary(*async, buf_aValueBin);
        *aValueBinLen = buf_aValueBin.Bytes();
        *aValueBin = buf_aValueBin.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyZappOrgTestBasic1SyncToggleBool(THandle aHandle)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncToggleBool();
}

void CpProxyZappOrgTestBasic1BeginToggleBool(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginToggleBool(functor);
}

int32_t CpProxyZappOrgTestBasic1EndToggleBool(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndToggleBool(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyZappOrgTestBasic1SyncWriteFile(THandle aHandle, const char* aData, const char* aFileFullName)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aData(aData);
    Brh buf_aFileFullName(aFileFullName);
    proxyC->SyncWriteFile(buf_aData, buf_aFileFullName);
}

void CpProxyZappOrgTestBasic1BeginWriteFile(THandle aHandle, const char* aData, const char* aFileFullName, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aData(aData);
    Brh buf_aFileFullName(aFileFullName);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginWriteFile(buf_aData, buf_aFileFullName, functor);
}

int32_t CpProxyZappOrgTestBasic1EndWriteFile(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndWriteFile(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyZappOrgTestBasic1SyncShutdown(THandle aHandle)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncShutdown();
}

void CpProxyZappOrgTestBasic1BeginShutdown(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginShutdown(functor);
}

int32_t CpProxyZappOrgTestBasic1EndShutdown(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndShutdown(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyZappOrgTestBasic1SetPropertyVarUintChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyVarUintChanged(functor);
}

void CpProxyZappOrgTestBasic1SetPropertyVarIntChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyVarIntChanged(functor);
}

void CpProxyZappOrgTestBasic1SetPropertyVarBoolChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyVarBoolChanged(functor);
}

void CpProxyZappOrgTestBasic1SetPropertyVarStrChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyVarStrChanged(functor);
}

void CpProxyZappOrgTestBasic1SetPropertyVarBinChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyVarBinChanged(functor);
}

void CpProxyZappOrgTestBasic1PropertyVarUint(THandle aHandle, uint32_t* aVarUint)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyVarUint(*aVarUint);
}

void CpProxyZappOrgTestBasic1PropertyVarInt(THandle aHandle, int32_t* aVarInt)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyVarInt(*aVarInt);
}

void CpProxyZappOrgTestBasic1PropertyVarBool(THandle aHandle, uint32_t* aVarBool)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aVarBool = false;
    proxyC->PropertyVarBool(*(TBool*)aVarBool);
}

void CpProxyZappOrgTestBasic1PropertyVarStr(THandle aHandle, char** aVarStr)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aVarStr;
    proxyC->PropertyVarStr(buf_aVarStr);
    *aVarStr = buf_aVarStr.Transfer();
}

void CpProxyZappOrgTestBasic1PropertyVarBin(THandle aHandle, char** aVarBin, uint32_t* aLen)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aVarBin;
    proxyC->PropertyVarBin(buf_aVarBin);
    *aLen = buf_aVarBin.Bytes();
    *aVarBin = buf_aVarBin.Extract();
}

