#include "CpOpenhomeOrgTestBasic1.h"
#include <OpenHome/Net/Core/CpDevice.h>
#include <OpenHome/Net/C/CpProxyCPrivate.h>
#include <OpenHome/Net/Core/FunctorAsync.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Net/Core/CpProxy.h>
#include <OpenHome/Net/Private/CpiService.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Net/Private/AsyncPrivate.h>
#include <OpenHome/Net/Core/CpDevice.h>

using namespace OpenHome;
using namespace OpenHome::Net;

class CpProxyOpenhomeOrgTestBasic1C : public CpProxyC
{
public:
    CpProxyOpenhomeOrgTestBasic1C(CpDeviceC aDevice);
    ~CpProxyOpenhomeOrgTestBasic1C();
    //CpProxyOpenhomeOrgTestBasic1* Proxy() { return static_cast<CpProxyOpenhomeOrgTestBasic1*>(iProxy); }

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


class SyncIncrementOpenhomeOrgTestBasic1C : public SyncProxyAction
{
public:
    SyncIncrementOpenhomeOrgTestBasic1C(CpProxyOpenhomeOrgTestBasic1C& aProxy, TUint& aResult);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncIncrementOpenhomeOrgTestBasic1C() {};
private:
    CpProxyOpenhomeOrgTestBasic1C& iService;
    TUint& iResult;
};

SyncIncrementOpenhomeOrgTestBasic1C::SyncIncrementOpenhomeOrgTestBasic1C(CpProxyOpenhomeOrgTestBasic1C& aProxy, TUint& aResult)
    : iService(aProxy)
    , iResult(aResult)
{
}

void SyncIncrementOpenhomeOrgTestBasic1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndIncrement(aAsync, iResult);
}


class SyncDecrementOpenhomeOrgTestBasic1C : public SyncProxyAction
{
public:
    SyncDecrementOpenhomeOrgTestBasic1C(CpProxyOpenhomeOrgTestBasic1C& aProxy, TInt& aResult);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncDecrementOpenhomeOrgTestBasic1C() {};
private:
    CpProxyOpenhomeOrgTestBasic1C& iService;
    TInt& iResult;
};

SyncDecrementOpenhomeOrgTestBasic1C::SyncDecrementOpenhomeOrgTestBasic1C(CpProxyOpenhomeOrgTestBasic1C& aProxy, TInt& aResult)
    : iService(aProxy)
    , iResult(aResult)
{
}

void SyncDecrementOpenhomeOrgTestBasic1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndDecrement(aAsync, iResult);
}


class SyncToggleOpenhomeOrgTestBasic1C : public SyncProxyAction
{
public:
    SyncToggleOpenhomeOrgTestBasic1C(CpProxyOpenhomeOrgTestBasic1C& aProxy, TBool& aResult);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncToggleOpenhomeOrgTestBasic1C() {};
private:
    CpProxyOpenhomeOrgTestBasic1C& iService;
    TBool& iResult;
};

SyncToggleOpenhomeOrgTestBasic1C::SyncToggleOpenhomeOrgTestBasic1C(CpProxyOpenhomeOrgTestBasic1C& aProxy, TBool& aResult)
    : iService(aProxy)
    , iResult(aResult)
{
}

void SyncToggleOpenhomeOrgTestBasic1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndToggle(aAsync, iResult);
}


class SyncEchoStringOpenhomeOrgTestBasic1C : public SyncProxyAction
{
public:
    SyncEchoStringOpenhomeOrgTestBasic1C(CpProxyOpenhomeOrgTestBasic1C& aProxy, Brh& aResult);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncEchoStringOpenhomeOrgTestBasic1C() {};
private:
    CpProxyOpenhomeOrgTestBasic1C& iService;
    Brh& iResult;
};

SyncEchoStringOpenhomeOrgTestBasic1C::SyncEchoStringOpenhomeOrgTestBasic1C(CpProxyOpenhomeOrgTestBasic1C& aProxy, Brh& aResult)
    : iService(aProxy)
    , iResult(aResult)
{
}

void SyncEchoStringOpenhomeOrgTestBasic1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndEchoString(aAsync, iResult);
}


class SyncEchoBinaryOpenhomeOrgTestBasic1C : public SyncProxyAction
{
public:
    SyncEchoBinaryOpenhomeOrgTestBasic1C(CpProxyOpenhomeOrgTestBasic1C& aProxy, Brh& aResult);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncEchoBinaryOpenhomeOrgTestBasic1C() {};
private:
    CpProxyOpenhomeOrgTestBasic1C& iService;
    Brh& iResult;
};

SyncEchoBinaryOpenhomeOrgTestBasic1C::SyncEchoBinaryOpenhomeOrgTestBasic1C(CpProxyOpenhomeOrgTestBasic1C& aProxy, Brh& aResult)
    : iService(aProxy)
    , iResult(aResult)
{
}

void SyncEchoBinaryOpenhomeOrgTestBasic1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndEchoBinary(aAsync, iResult);
}


class SyncSetUintOpenhomeOrgTestBasic1C : public SyncProxyAction
{
public:
    SyncSetUintOpenhomeOrgTestBasic1C(CpProxyOpenhomeOrgTestBasic1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetUintOpenhomeOrgTestBasic1C() {};
private:
    CpProxyOpenhomeOrgTestBasic1C& iService;
};

SyncSetUintOpenhomeOrgTestBasic1C::SyncSetUintOpenhomeOrgTestBasic1C(CpProxyOpenhomeOrgTestBasic1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetUintOpenhomeOrgTestBasic1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetUint(aAsync);
}


class SyncGetUintOpenhomeOrgTestBasic1C : public SyncProxyAction
{
public:
    SyncGetUintOpenhomeOrgTestBasic1C(CpProxyOpenhomeOrgTestBasic1C& aProxy, TUint& aValueUint);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetUintOpenhomeOrgTestBasic1C() {};
private:
    CpProxyOpenhomeOrgTestBasic1C& iService;
    TUint& iValueUint;
};

SyncGetUintOpenhomeOrgTestBasic1C::SyncGetUintOpenhomeOrgTestBasic1C(CpProxyOpenhomeOrgTestBasic1C& aProxy, TUint& aValueUint)
    : iService(aProxy)
    , iValueUint(aValueUint)
{
}

void SyncGetUintOpenhomeOrgTestBasic1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetUint(aAsync, iValueUint);
}


class SyncSetIntOpenhomeOrgTestBasic1C : public SyncProxyAction
{
public:
    SyncSetIntOpenhomeOrgTestBasic1C(CpProxyOpenhomeOrgTestBasic1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetIntOpenhomeOrgTestBasic1C() {};
private:
    CpProxyOpenhomeOrgTestBasic1C& iService;
};

SyncSetIntOpenhomeOrgTestBasic1C::SyncSetIntOpenhomeOrgTestBasic1C(CpProxyOpenhomeOrgTestBasic1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetIntOpenhomeOrgTestBasic1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetInt(aAsync);
}


class SyncGetIntOpenhomeOrgTestBasic1C : public SyncProxyAction
{
public:
    SyncGetIntOpenhomeOrgTestBasic1C(CpProxyOpenhomeOrgTestBasic1C& aProxy, TInt& aValueInt);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetIntOpenhomeOrgTestBasic1C() {};
private:
    CpProxyOpenhomeOrgTestBasic1C& iService;
    TInt& iValueInt;
};

SyncGetIntOpenhomeOrgTestBasic1C::SyncGetIntOpenhomeOrgTestBasic1C(CpProxyOpenhomeOrgTestBasic1C& aProxy, TInt& aValueInt)
    : iService(aProxy)
    , iValueInt(aValueInt)
{
}

void SyncGetIntOpenhomeOrgTestBasic1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetInt(aAsync, iValueInt);
}


class SyncSetBoolOpenhomeOrgTestBasic1C : public SyncProxyAction
{
public:
    SyncSetBoolOpenhomeOrgTestBasic1C(CpProxyOpenhomeOrgTestBasic1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetBoolOpenhomeOrgTestBasic1C() {};
private:
    CpProxyOpenhomeOrgTestBasic1C& iService;
};

SyncSetBoolOpenhomeOrgTestBasic1C::SyncSetBoolOpenhomeOrgTestBasic1C(CpProxyOpenhomeOrgTestBasic1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetBoolOpenhomeOrgTestBasic1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetBool(aAsync);
}


class SyncGetBoolOpenhomeOrgTestBasic1C : public SyncProxyAction
{
public:
    SyncGetBoolOpenhomeOrgTestBasic1C(CpProxyOpenhomeOrgTestBasic1C& aProxy, TBool& aValueBool);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetBoolOpenhomeOrgTestBasic1C() {};
private:
    CpProxyOpenhomeOrgTestBasic1C& iService;
    TBool& iValueBool;
};

SyncGetBoolOpenhomeOrgTestBasic1C::SyncGetBoolOpenhomeOrgTestBasic1C(CpProxyOpenhomeOrgTestBasic1C& aProxy, TBool& aValueBool)
    : iService(aProxy)
    , iValueBool(aValueBool)
{
}

void SyncGetBoolOpenhomeOrgTestBasic1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetBool(aAsync, iValueBool);
}


class SyncSetMultipleOpenhomeOrgTestBasic1C : public SyncProxyAction
{
public:
    SyncSetMultipleOpenhomeOrgTestBasic1C(CpProxyOpenhomeOrgTestBasic1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetMultipleOpenhomeOrgTestBasic1C() {};
private:
    CpProxyOpenhomeOrgTestBasic1C& iService;
};

SyncSetMultipleOpenhomeOrgTestBasic1C::SyncSetMultipleOpenhomeOrgTestBasic1C(CpProxyOpenhomeOrgTestBasic1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetMultipleOpenhomeOrgTestBasic1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetMultiple(aAsync);
}


class SyncSetStringOpenhomeOrgTestBasic1C : public SyncProxyAction
{
public:
    SyncSetStringOpenhomeOrgTestBasic1C(CpProxyOpenhomeOrgTestBasic1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetStringOpenhomeOrgTestBasic1C() {};
private:
    CpProxyOpenhomeOrgTestBasic1C& iService;
};

SyncSetStringOpenhomeOrgTestBasic1C::SyncSetStringOpenhomeOrgTestBasic1C(CpProxyOpenhomeOrgTestBasic1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetStringOpenhomeOrgTestBasic1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetString(aAsync);
}


class SyncGetStringOpenhomeOrgTestBasic1C : public SyncProxyAction
{
public:
    SyncGetStringOpenhomeOrgTestBasic1C(CpProxyOpenhomeOrgTestBasic1C& aProxy, Brh& aValueStr);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetStringOpenhomeOrgTestBasic1C() {};
private:
    CpProxyOpenhomeOrgTestBasic1C& iService;
    Brh& iValueStr;
};

SyncGetStringOpenhomeOrgTestBasic1C::SyncGetStringOpenhomeOrgTestBasic1C(CpProxyOpenhomeOrgTestBasic1C& aProxy, Brh& aValueStr)
    : iService(aProxy)
    , iValueStr(aValueStr)
{
}

void SyncGetStringOpenhomeOrgTestBasic1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetString(aAsync, iValueStr);
}


class SyncSetBinaryOpenhomeOrgTestBasic1C : public SyncProxyAction
{
public:
    SyncSetBinaryOpenhomeOrgTestBasic1C(CpProxyOpenhomeOrgTestBasic1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetBinaryOpenhomeOrgTestBasic1C() {};
private:
    CpProxyOpenhomeOrgTestBasic1C& iService;
};

SyncSetBinaryOpenhomeOrgTestBasic1C::SyncSetBinaryOpenhomeOrgTestBasic1C(CpProxyOpenhomeOrgTestBasic1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetBinaryOpenhomeOrgTestBasic1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetBinary(aAsync);
}


class SyncGetBinaryOpenhomeOrgTestBasic1C : public SyncProxyAction
{
public:
    SyncGetBinaryOpenhomeOrgTestBasic1C(CpProxyOpenhomeOrgTestBasic1C& aProxy, Brh& aValueBin);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetBinaryOpenhomeOrgTestBasic1C() {};
private:
    CpProxyOpenhomeOrgTestBasic1C& iService;
    Brh& iValueBin;
};

SyncGetBinaryOpenhomeOrgTestBasic1C::SyncGetBinaryOpenhomeOrgTestBasic1C(CpProxyOpenhomeOrgTestBasic1C& aProxy, Brh& aValueBin)
    : iService(aProxy)
    , iValueBin(aValueBin)
{
}

void SyncGetBinaryOpenhomeOrgTestBasic1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetBinary(aAsync, iValueBin);
}


class SyncToggleBoolOpenhomeOrgTestBasic1C : public SyncProxyAction
{
public:
    SyncToggleBoolOpenhomeOrgTestBasic1C(CpProxyOpenhomeOrgTestBasic1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncToggleBoolOpenhomeOrgTestBasic1C() {};
private:
    CpProxyOpenhomeOrgTestBasic1C& iService;
};

SyncToggleBoolOpenhomeOrgTestBasic1C::SyncToggleBoolOpenhomeOrgTestBasic1C(CpProxyOpenhomeOrgTestBasic1C& aProxy)
    : iService(aProxy)
{
}

void SyncToggleBoolOpenhomeOrgTestBasic1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndToggleBool(aAsync);
}


class SyncWriteFileOpenhomeOrgTestBasic1C : public SyncProxyAction
{
public:
    SyncWriteFileOpenhomeOrgTestBasic1C(CpProxyOpenhomeOrgTestBasic1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncWriteFileOpenhomeOrgTestBasic1C() {};
private:
    CpProxyOpenhomeOrgTestBasic1C& iService;
};

SyncWriteFileOpenhomeOrgTestBasic1C::SyncWriteFileOpenhomeOrgTestBasic1C(CpProxyOpenhomeOrgTestBasic1C& aProxy)
    : iService(aProxy)
{
}

void SyncWriteFileOpenhomeOrgTestBasic1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndWriteFile(aAsync);
}


class SyncShutdownOpenhomeOrgTestBasic1C : public SyncProxyAction
{
public:
    SyncShutdownOpenhomeOrgTestBasic1C(CpProxyOpenhomeOrgTestBasic1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncShutdownOpenhomeOrgTestBasic1C() {};
private:
    CpProxyOpenhomeOrgTestBasic1C& iService;
};

SyncShutdownOpenhomeOrgTestBasic1C::SyncShutdownOpenhomeOrgTestBasic1C(CpProxyOpenhomeOrgTestBasic1C& aProxy)
    : iService(aProxy)
{
}

void SyncShutdownOpenhomeOrgTestBasic1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndShutdown(aAsync);
}

CpProxyOpenhomeOrgTestBasic1C::CpProxyOpenhomeOrgTestBasic1C(CpDeviceC aDevice)
    : CpProxyC("openhome-org", "TestBasic", 1, *reinterpret_cast<CpiDevice*>(aDevice))
    , iLock("MPCS")
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
    functor = MakeFunctor(*this, &CpProxyOpenhomeOrgTestBasic1C::VarUintPropertyChanged);
    iVarUint = new PropertyUint("VarUint", functor);
    AddProperty(iVarUint);
    functor = MakeFunctor(*this, &CpProxyOpenhomeOrgTestBasic1C::VarIntPropertyChanged);
    iVarInt = new PropertyInt("VarInt", functor);
    AddProperty(iVarInt);
    functor = MakeFunctor(*this, &CpProxyOpenhomeOrgTestBasic1C::VarBoolPropertyChanged);
    iVarBool = new PropertyBool("VarBool", functor);
    AddProperty(iVarBool);
    functor = MakeFunctor(*this, &CpProxyOpenhomeOrgTestBasic1C::VarStrPropertyChanged);
    iVarStr = new PropertyString("VarStr", functor);
    AddProperty(iVarStr);
    functor = MakeFunctor(*this, &CpProxyOpenhomeOrgTestBasic1C::VarBinPropertyChanged);
    iVarBin = new PropertyBinary("VarBin", functor);
    AddProperty(iVarBin);
}

CpProxyOpenhomeOrgTestBasic1C::~CpProxyOpenhomeOrgTestBasic1C()
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

void CpProxyOpenhomeOrgTestBasic1C::SyncIncrement(TUint aValue, TUint& aResult)
{
    SyncIncrementOpenhomeOrgTestBasic1C sync(*this, aResult);
    BeginIncrement(aValue, sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestBasic1C::BeginIncrement(TUint aValue, FunctorAsync& aFunctor)
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

void CpProxyOpenhomeOrgTestBasic1C::EndIncrement(IAsync& aAsync, TUint& aResult)
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

void CpProxyOpenhomeOrgTestBasic1C::SyncDecrement(TInt aValue, TInt& aResult)
{
    SyncDecrementOpenhomeOrgTestBasic1C sync(*this, aResult);
    BeginDecrement(aValue, sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestBasic1C::BeginDecrement(TInt aValue, FunctorAsync& aFunctor)
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

void CpProxyOpenhomeOrgTestBasic1C::EndDecrement(IAsync& aAsync, TInt& aResult)
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

void CpProxyOpenhomeOrgTestBasic1C::SyncToggle(TBool aValue, TBool& aResult)
{
    SyncToggleOpenhomeOrgTestBasic1C sync(*this, aResult);
    BeginToggle(aValue, sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestBasic1C::BeginToggle(TBool aValue, FunctorAsync& aFunctor)
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

void CpProxyOpenhomeOrgTestBasic1C::EndToggle(IAsync& aAsync, TBool& aResult)
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

void CpProxyOpenhomeOrgTestBasic1C::SyncEchoString(const Brx& aValue, Brh& aResult)
{
    SyncEchoStringOpenhomeOrgTestBasic1C sync(*this, aResult);
    BeginEchoString(aValue, sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestBasic1C::BeginEchoString(const Brx& aValue, FunctorAsync& aFunctor)
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

void CpProxyOpenhomeOrgTestBasic1C::EndEchoString(IAsync& aAsync, Brh& aResult)
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

void CpProxyOpenhomeOrgTestBasic1C::SyncEchoBinary(const Brx& aValue, Brh& aResult)
{
    SyncEchoBinaryOpenhomeOrgTestBasic1C sync(*this, aResult);
    BeginEchoBinary(aValue, sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestBasic1C::BeginEchoBinary(const Brx& aValue, FunctorAsync& aFunctor)
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

void CpProxyOpenhomeOrgTestBasic1C::EndEchoBinary(IAsync& aAsync, Brh& aResult)
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

void CpProxyOpenhomeOrgTestBasic1C::SyncSetUint(TUint aValueUint)
{
    SyncSetUintOpenhomeOrgTestBasic1C sync(*this);
    BeginSetUint(aValueUint, sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestBasic1C::BeginSetUint(TUint aValueUint, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetUint, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetUint->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aValueUint));
    Invocable().InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgTestBasic1C::EndSetUint(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetUint"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyOpenhomeOrgTestBasic1C::SyncGetUint(TUint& aValueUint)
{
    SyncGetUintOpenhomeOrgTestBasic1C sync(*this, aValueUint);
    BeginGetUint(sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestBasic1C::BeginGetUint(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetUint, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetUint->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgTestBasic1C::EndGetUint(IAsync& aAsync, TUint& aValueUint)
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

void CpProxyOpenhomeOrgTestBasic1C::SyncSetInt(TInt aValueInt)
{
    SyncSetIntOpenhomeOrgTestBasic1C sync(*this);
    BeginSetInt(aValueInt, sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestBasic1C::BeginSetInt(TInt aValueInt, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetInt, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetInt->InputParameters();
    invocation->AddInput(new ArgumentInt(*inParams[inIndex++], aValueInt));
    Invocable().InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgTestBasic1C::EndSetInt(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetInt"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyOpenhomeOrgTestBasic1C::SyncGetInt(TInt& aValueInt)
{
    SyncGetIntOpenhomeOrgTestBasic1C sync(*this, aValueInt);
    BeginGetInt(sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestBasic1C::BeginGetInt(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetInt, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetInt->OutputParameters();
    invocation->AddOutput(new ArgumentInt(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgTestBasic1C::EndGetInt(IAsync& aAsync, TInt& aValueInt)
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

void CpProxyOpenhomeOrgTestBasic1C::SyncSetBool(TBool aValueBool)
{
    SyncSetBoolOpenhomeOrgTestBasic1C sync(*this);
    BeginSetBool(aValueBool, sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestBasic1C::BeginSetBool(TBool aValueBool, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetBool, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetBool->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aValueBool));
    Invocable().InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgTestBasic1C::EndSetBool(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetBool"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyOpenhomeOrgTestBasic1C::SyncGetBool(TBool& aValueBool)
{
    SyncGetBoolOpenhomeOrgTestBasic1C sync(*this, aValueBool);
    BeginGetBool(sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestBasic1C::BeginGetBool(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetBool, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetBool->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgTestBasic1C::EndGetBool(IAsync& aAsync, TBool& aValueBool)
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

void CpProxyOpenhomeOrgTestBasic1C::SyncSetMultiple(TUint aValueUint, TInt aValueInt, TBool aValueBool)
{
    SyncSetMultipleOpenhomeOrgTestBasic1C sync(*this);
    BeginSetMultiple(aValueUint, aValueInt, aValueBool, sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestBasic1C::BeginSetMultiple(TUint aValueUint, TInt aValueInt, TBool aValueBool, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetMultiple, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetMultiple->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aValueUint));
    invocation->AddInput(new ArgumentInt(*inParams[inIndex++], aValueInt));
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aValueBool));
    Invocable().InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgTestBasic1C::EndSetMultiple(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetMultiple"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyOpenhomeOrgTestBasic1C::SyncSetString(const Brx& aValueStr)
{
    SyncSetStringOpenhomeOrgTestBasic1C sync(*this);
    BeginSetString(aValueStr, sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestBasic1C::BeginSetString(const Brx& aValueStr, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetString, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetString->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aValueStr));
    Invocable().InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgTestBasic1C::EndSetString(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetString"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyOpenhomeOrgTestBasic1C::SyncGetString(Brh& aValueStr)
{
    SyncGetStringOpenhomeOrgTestBasic1C sync(*this, aValueStr);
    BeginGetString(sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestBasic1C::BeginGetString(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetString, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetString->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgTestBasic1C::EndGetString(IAsync& aAsync, Brh& aValueStr)
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

void CpProxyOpenhomeOrgTestBasic1C::SyncSetBinary(const Brx& aValueBin)
{
    SyncSetBinaryOpenhomeOrgTestBasic1C sync(*this);
    BeginSetBinary(aValueBin, sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestBasic1C::BeginSetBinary(const Brx& aValueBin, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetBinary, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetBinary->InputParameters();
    invocation->AddInput(new ArgumentBinary(*inParams[inIndex++], aValueBin));
    Invocable().InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgTestBasic1C::EndSetBinary(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetBinary"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyOpenhomeOrgTestBasic1C::SyncGetBinary(Brh& aValueBin)
{
    SyncGetBinaryOpenhomeOrgTestBasic1C sync(*this, aValueBin);
    BeginGetBinary(sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestBasic1C::BeginGetBinary(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetBinary, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetBinary->OutputParameters();
    invocation->AddOutput(new ArgumentBinary(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgTestBasic1C::EndGetBinary(IAsync& aAsync, Brh& aValueBin)
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

void CpProxyOpenhomeOrgTestBasic1C::SyncToggleBool()
{
    SyncToggleBoolOpenhomeOrgTestBasic1C sync(*this);
    BeginToggleBool(sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestBasic1C::BeginToggleBool(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionToggleBool, aFunctor);
    Invocable().InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgTestBasic1C::EndToggleBool(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("ToggleBool"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyOpenhomeOrgTestBasic1C::SyncWriteFile(const Brx& aData, const Brx& aFileFullName)
{
    SyncWriteFileOpenhomeOrgTestBasic1C sync(*this);
    BeginWriteFile(aData, aFileFullName, sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestBasic1C::BeginWriteFile(const Brx& aData, const Brx& aFileFullName, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionWriteFile, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionWriteFile->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aData));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aFileFullName));
    Invocable().InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgTestBasic1C::EndWriteFile(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("WriteFile"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyOpenhomeOrgTestBasic1C::SyncShutdown()
{
    SyncShutdownOpenhomeOrgTestBasic1C sync(*this);
    BeginShutdown(sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestBasic1C::BeginShutdown(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionShutdown, aFunctor);
    Invocable().InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgTestBasic1C::EndShutdown(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Shutdown"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyOpenhomeOrgTestBasic1C::SetPropertyVarUintChanged(Functor& aFunctor)
{
    iLock.Wait();
    iVarUintChanged = aFunctor;
    iLock.Signal();
}

void CpProxyOpenhomeOrgTestBasic1C::SetPropertyVarIntChanged(Functor& aFunctor)
{
    iLock.Wait();
    iVarIntChanged = aFunctor;
    iLock.Signal();
}

void CpProxyOpenhomeOrgTestBasic1C::SetPropertyVarBoolChanged(Functor& aFunctor)
{
    iLock.Wait();
    iVarBoolChanged = aFunctor;
    iLock.Signal();
}

void CpProxyOpenhomeOrgTestBasic1C::SetPropertyVarStrChanged(Functor& aFunctor)
{
    iLock.Wait();
    iVarStrChanged = aFunctor;
    iLock.Signal();
}

void CpProxyOpenhomeOrgTestBasic1C::SetPropertyVarBinChanged(Functor& aFunctor)
{
    iLock.Wait();
    iVarBinChanged = aFunctor;
    iLock.Signal();
}

void CpProxyOpenhomeOrgTestBasic1C::PropertyVarUint(TUint& aVarUint) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aVarUint = iVarUint->Value();
    PropertyReadUnlock();
}

void CpProxyOpenhomeOrgTestBasic1C::PropertyVarInt(TInt& aVarInt) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aVarInt = iVarInt->Value();
    PropertyReadUnlock();
}

void CpProxyOpenhomeOrgTestBasic1C::PropertyVarBool(TBool& aVarBool) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aVarBool = iVarBool->Value();
    PropertyReadUnlock();
}

void CpProxyOpenhomeOrgTestBasic1C::PropertyVarStr(Brhz& aVarStr) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aVarStr.Set(iVarStr->Value());
    PropertyReadUnlock();
}

void CpProxyOpenhomeOrgTestBasic1C::PropertyVarBin(Brh& aVarBin) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aVarBin.Set(iVarBin->Value());
    PropertyReadUnlock();
}

void CpProxyOpenhomeOrgTestBasic1C::VarUintPropertyChanged()
{
    ReportEvent(iVarUintChanged);
}

void CpProxyOpenhomeOrgTestBasic1C::VarIntPropertyChanged()
{
    ReportEvent(iVarIntChanged);
}

void CpProxyOpenhomeOrgTestBasic1C::VarBoolPropertyChanged()
{
    ReportEvent(iVarBoolChanged);
}

void CpProxyOpenhomeOrgTestBasic1C::VarStrPropertyChanged()
{
    ReportEvent(iVarStrChanged);
}

void CpProxyOpenhomeOrgTestBasic1C::VarBinPropertyChanged()
{
    ReportEvent(iVarBinChanged);
}


THandle STDCALL CpProxyOpenhomeOrgTestBasic1Create(CpDeviceC aDevice)
{
    return new CpProxyOpenhomeOrgTestBasic1C(aDevice);
}

void STDCALL CpProxyOpenhomeOrgTestBasic1Destroy(THandle aHandle)
{
    CpProxyOpenhomeOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestBasic1C*>(aHandle);
    delete proxyC;
}

void STDCALL CpProxyOpenhomeOrgTestBasic1SyncIncrement(THandle aHandle, uint32_t aValue, uint32_t* aResult)
{
    CpProxyOpenhomeOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncIncrement(aValue, *aResult);
}

void STDCALL CpProxyOpenhomeOrgTestBasic1BeginIncrement(THandle aHandle, uint32_t aValue, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyOpenhomeOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginIncrement(aValue, functor);
}

int32_t STDCALL CpProxyOpenhomeOrgTestBasic1EndIncrement(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aResult)
{
    int32_t err = 0;
    CpProxyOpenhomeOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestBasic1C*>(aHandle);
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

void STDCALL CpProxyOpenhomeOrgTestBasic1SyncDecrement(THandle aHandle, int32_t aValue, int32_t* aResult)
{
    CpProxyOpenhomeOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncDecrement(aValue, *aResult);
}

void STDCALL CpProxyOpenhomeOrgTestBasic1BeginDecrement(THandle aHandle, int32_t aValue, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyOpenhomeOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginDecrement(aValue, functor);
}

int32_t STDCALL CpProxyOpenhomeOrgTestBasic1EndDecrement(THandle aHandle, OhNetHandleAsync aAsync, int32_t* aResult)
{
    int32_t err = 0;
    CpProxyOpenhomeOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestBasic1C*>(aHandle);
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

void STDCALL CpProxyOpenhomeOrgTestBasic1SyncToggle(THandle aHandle, uint32_t aValue, uint32_t* aResult)
{
    CpProxyOpenhomeOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aResult = 0;
    proxyC->SyncToggle((aValue==0? false : true), *(TBool*)aResult);
}

void STDCALL CpProxyOpenhomeOrgTestBasic1BeginToggle(THandle aHandle, uint32_t aValue, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyOpenhomeOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginToggle((aValue==0? false : true), functor);
}

int32_t STDCALL CpProxyOpenhomeOrgTestBasic1EndToggle(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aResult)
{
    int32_t err = 0;
    CpProxyOpenhomeOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestBasic1C*>(aHandle);
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

void STDCALL CpProxyOpenhomeOrgTestBasic1SyncEchoString(THandle aHandle, const char* aValue, char** aResult)
{
    CpProxyOpenhomeOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aValue(aValue);
    Brh buf_aResult;
    proxyC->SyncEchoString(buf_aValue, buf_aResult);
    *aResult = buf_aResult.Extract();
}

void STDCALL CpProxyOpenhomeOrgTestBasic1BeginEchoString(THandle aHandle, const char* aValue, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyOpenhomeOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aValue(aValue);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginEchoString(buf_aValue, functor);
}

int32_t STDCALL CpProxyOpenhomeOrgTestBasic1EndEchoString(THandle aHandle, OhNetHandleAsync aAsync, char** aResult)
{
    int32_t err = 0;
    CpProxyOpenhomeOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestBasic1C*>(aHandle);
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

void STDCALL CpProxyOpenhomeOrgTestBasic1SyncEchoBinary(THandle aHandle, const char* aValue, uint32_t aValueLen, char** aResult, uint32_t* aResultLen)
{
    CpProxyOpenhomeOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aValue;
    buf_aValue.Set((const TByte*)aValue, aValueLen);
    Brh buf_aResult;
    proxyC->SyncEchoBinary(buf_aValue, buf_aResult);
    *aResultLen = buf_aResult.Bytes();
    *aResult = buf_aResult.Extract();
}

void STDCALL CpProxyOpenhomeOrgTestBasic1BeginEchoBinary(THandle aHandle, const char* aValue, uint32_t aValueLen, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyOpenhomeOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aValue;
    buf_aValue.Set((const TByte*)aValue, aValueLen);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginEchoBinary(buf_aValue, functor);
}

int32_t STDCALL CpProxyOpenhomeOrgTestBasic1EndEchoBinary(THandle aHandle, OhNetHandleAsync aAsync, char** aResult, uint32_t* aResultLen)
{
    int32_t err = 0;
    CpProxyOpenhomeOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestBasic1C*>(aHandle);
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

void STDCALL CpProxyOpenhomeOrgTestBasic1SyncSetUint(THandle aHandle, uint32_t aValueUint)
{
    CpProxyOpenhomeOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSetUint(aValueUint);
}

void STDCALL CpProxyOpenhomeOrgTestBasic1BeginSetUint(THandle aHandle, uint32_t aValueUint, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyOpenhomeOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSetUint(aValueUint, functor);
}

int32_t STDCALL CpProxyOpenhomeOrgTestBasic1EndSetUint(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyOpenhomeOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestBasic1C*>(aHandle);
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

void STDCALL CpProxyOpenhomeOrgTestBasic1SyncGetUint(THandle aHandle, uint32_t* aValueUint)
{
    CpProxyOpenhomeOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncGetUint(*aValueUint);
}

void STDCALL CpProxyOpenhomeOrgTestBasic1BeginGetUint(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyOpenhomeOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetUint(functor);
}

int32_t STDCALL CpProxyOpenhomeOrgTestBasic1EndGetUint(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aValueUint)
{
    int32_t err = 0;
    CpProxyOpenhomeOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestBasic1C*>(aHandle);
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

void STDCALL CpProxyOpenhomeOrgTestBasic1SyncSetInt(THandle aHandle, int32_t aValueInt)
{
    CpProxyOpenhomeOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSetInt(aValueInt);
}

void STDCALL CpProxyOpenhomeOrgTestBasic1BeginSetInt(THandle aHandle, int32_t aValueInt, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyOpenhomeOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSetInt(aValueInt, functor);
}

int32_t STDCALL CpProxyOpenhomeOrgTestBasic1EndSetInt(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyOpenhomeOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestBasic1C*>(aHandle);
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

void STDCALL CpProxyOpenhomeOrgTestBasic1SyncGetInt(THandle aHandle, int32_t* aValueInt)
{
    CpProxyOpenhomeOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncGetInt(*aValueInt);
}

void STDCALL CpProxyOpenhomeOrgTestBasic1BeginGetInt(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyOpenhomeOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetInt(functor);
}

int32_t STDCALL CpProxyOpenhomeOrgTestBasic1EndGetInt(THandle aHandle, OhNetHandleAsync aAsync, int32_t* aValueInt)
{
    int32_t err = 0;
    CpProxyOpenhomeOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestBasic1C*>(aHandle);
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

void STDCALL CpProxyOpenhomeOrgTestBasic1SyncSetBool(THandle aHandle, uint32_t aValueBool)
{
    CpProxyOpenhomeOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSetBool((aValueBool==0? false : true));
}

void STDCALL CpProxyOpenhomeOrgTestBasic1BeginSetBool(THandle aHandle, uint32_t aValueBool, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyOpenhomeOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSetBool((aValueBool==0? false : true), functor);
}

int32_t STDCALL CpProxyOpenhomeOrgTestBasic1EndSetBool(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyOpenhomeOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestBasic1C*>(aHandle);
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

void STDCALL CpProxyOpenhomeOrgTestBasic1SyncGetBool(THandle aHandle, uint32_t* aValueBool)
{
    CpProxyOpenhomeOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aValueBool = 0;
    proxyC->SyncGetBool(*(TBool*)aValueBool);
}

void STDCALL CpProxyOpenhomeOrgTestBasic1BeginGetBool(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyOpenhomeOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetBool(functor);
}

int32_t STDCALL CpProxyOpenhomeOrgTestBasic1EndGetBool(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aValueBool)
{
    int32_t err = 0;
    CpProxyOpenhomeOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestBasic1C*>(aHandle);
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

void STDCALL CpProxyOpenhomeOrgTestBasic1SyncSetMultiple(THandle aHandle, uint32_t aValueUint, int32_t aValueInt, uint32_t aValueBool)
{
    CpProxyOpenhomeOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSetMultiple(aValueUint, aValueInt, (aValueBool==0? false : true));
}

void STDCALL CpProxyOpenhomeOrgTestBasic1BeginSetMultiple(THandle aHandle, uint32_t aValueUint, int32_t aValueInt, uint32_t aValueBool, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyOpenhomeOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSetMultiple(aValueUint, aValueInt, (aValueBool==0? false : true), functor);
}

int32_t STDCALL CpProxyOpenhomeOrgTestBasic1EndSetMultiple(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyOpenhomeOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestBasic1C*>(aHandle);
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

void STDCALL CpProxyOpenhomeOrgTestBasic1SyncSetString(THandle aHandle, const char* aValueStr)
{
    CpProxyOpenhomeOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aValueStr(aValueStr);
    proxyC->SyncSetString(buf_aValueStr);
}

void STDCALL CpProxyOpenhomeOrgTestBasic1BeginSetString(THandle aHandle, const char* aValueStr, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyOpenhomeOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aValueStr(aValueStr);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSetString(buf_aValueStr, functor);
}

int32_t STDCALL CpProxyOpenhomeOrgTestBasic1EndSetString(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyOpenhomeOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestBasic1C*>(aHandle);
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

void STDCALL CpProxyOpenhomeOrgTestBasic1SyncGetString(THandle aHandle, char** aValueStr)
{
    CpProxyOpenhomeOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aValueStr;
    proxyC->SyncGetString(buf_aValueStr);
    *aValueStr = buf_aValueStr.Extract();
}

void STDCALL CpProxyOpenhomeOrgTestBasic1BeginGetString(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyOpenhomeOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetString(functor);
}

int32_t STDCALL CpProxyOpenhomeOrgTestBasic1EndGetString(THandle aHandle, OhNetHandleAsync aAsync, char** aValueStr)
{
    int32_t err = 0;
    CpProxyOpenhomeOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestBasic1C*>(aHandle);
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

void STDCALL CpProxyOpenhomeOrgTestBasic1SyncSetBinary(THandle aHandle, const char* aValueBin, uint32_t aValueBinLen)
{
    CpProxyOpenhomeOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aValueBin;
    buf_aValueBin.Set((const TByte*)aValueBin, aValueBinLen);
    proxyC->SyncSetBinary(buf_aValueBin);
}

void STDCALL CpProxyOpenhomeOrgTestBasic1BeginSetBinary(THandle aHandle, const char* aValueBin, uint32_t aValueBinLen, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyOpenhomeOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aValueBin;
    buf_aValueBin.Set((const TByte*)aValueBin, aValueBinLen);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSetBinary(buf_aValueBin, functor);
}

int32_t STDCALL CpProxyOpenhomeOrgTestBasic1EndSetBinary(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyOpenhomeOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestBasic1C*>(aHandle);
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

void STDCALL CpProxyOpenhomeOrgTestBasic1SyncGetBinary(THandle aHandle, char** aValueBin, uint32_t* aValueBinLen)
{
    CpProxyOpenhomeOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aValueBin;
    proxyC->SyncGetBinary(buf_aValueBin);
    *aValueBinLen = buf_aValueBin.Bytes();
    *aValueBin = buf_aValueBin.Extract();
}

void STDCALL CpProxyOpenhomeOrgTestBasic1BeginGetBinary(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyOpenhomeOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetBinary(functor);
}

int32_t STDCALL CpProxyOpenhomeOrgTestBasic1EndGetBinary(THandle aHandle, OhNetHandleAsync aAsync, char** aValueBin, uint32_t* aValueBinLen)
{
    int32_t err = 0;
    CpProxyOpenhomeOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestBasic1C*>(aHandle);
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

void STDCALL CpProxyOpenhomeOrgTestBasic1SyncToggleBool(THandle aHandle)
{
    CpProxyOpenhomeOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncToggleBool();
}

void STDCALL CpProxyOpenhomeOrgTestBasic1BeginToggleBool(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyOpenhomeOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginToggleBool(functor);
}

int32_t STDCALL CpProxyOpenhomeOrgTestBasic1EndToggleBool(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyOpenhomeOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestBasic1C*>(aHandle);
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

void STDCALL CpProxyOpenhomeOrgTestBasic1SyncWriteFile(THandle aHandle, const char* aData, const char* aFileFullName)
{
    CpProxyOpenhomeOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aData(aData);
    Brh buf_aFileFullName(aFileFullName);
    proxyC->SyncWriteFile(buf_aData, buf_aFileFullName);
}

void STDCALL CpProxyOpenhomeOrgTestBasic1BeginWriteFile(THandle aHandle, const char* aData, const char* aFileFullName, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyOpenhomeOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aData(aData);
    Brh buf_aFileFullName(aFileFullName);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginWriteFile(buf_aData, buf_aFileFullName, functor);
}

int32_t STDCALL CpProxyOpenhomeOrgTestBasic1EndWriteFile(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyOpenhomeOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestBasic1C*>(aHandle);
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

void STDCALL CpProxyOpenhomeOrgTestBasic1SyncShutdown(THandle aHandle)
{
    CpProxyOpenhomeOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncShutdown();
}

void STDCALL CpProxyOpenhomeOrgTestBasic1BeginShutdown(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyOpenhomeOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginShutdown(functor);
}

int32_t STDCALL CpProxyOpenhomeOrgTestBasic1EndShutdown(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyOpenhomeOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestBasic1C*>(aHandle);
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

void STDCALL CpProxyOpenhomeOrgTestBasic1SetPropertyVarUintChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyOpenhomeOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyVarUintChanged(functor);
}

void STDCALL CpProxyOpenhomeOrgTestBasic1SetPropertyVarIntChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyOpenhomeOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyVarIntChanged(functor);
}

void STDCALL CpProxyOpenhomeOrgTestBasic1SetPropertyVarBoolChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyOpenhomeOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyVarBoolChanged(functor);
}

void STDCALL CpProxyOpenhomeOrgTestBasic1SetPropertyVarStrChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyOpenhomeOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyVarStrChanged(functor);
}

void STDCALL CpProxyOpenhomeOrgTestBasic1SetPropertyVarBinChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyOpenhomeOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyVarBinChanged(functor);
}

void STDCALL CpProxyOpenhomeOrgTestBasic1PropertyVarUint(THandle aHandle, uint32_t* aVarUint)
{
    CpProxyOpenhomeOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyVarUint(*aVarUint);
}

void STDCALL CpProxyOpenhomeOrgTestBasic1PropertyVarInt(THandle aHandle, int32_t* aVarInt)
{
    CpProxyOpenhomeOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyVarInt(*aVarInt);
}

void STDCALL CpProxyOpenhomeOrgTestBasic1PropertyVarBool(THandle aHandle, uint32_t* aVarBool)
{
    CpProxyOpenhomeOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aVarBool = false;
    proxyC->PropertyVarBool(*(TBool*)aVarBool);
}

void STDCALL CpProxyOpenhomeOrgTestBasic1PropertyVarStr(THandle aHandle, char** aVarStr)
{
    CpProxyOpenhomeOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aVarStr;
    proxyC->PropertyVarStr(buf_aVarStr);
    *aVarStr = buf_aVarStr.Transfer();
}

void STDCALL CpProxyOpenhomeOrgTestBasic1PropertyVarBin(THandle aHandle, char** aVarBin, uint32_t* aLen)
{
    CpProxyOpenhomeOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aVarBin;
    proxyC->PropertyVarBin(buf_aVarBin);
    *aLen = buf_aVarBin.Bytes();
    *aVarBin = buf_aVarBin.Extract();
}

