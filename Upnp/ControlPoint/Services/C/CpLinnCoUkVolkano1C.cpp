#include "CpLinnCoUkVolkano1.h"
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

class CpProxyLinnCoUkVolkano1C : public CpProxyC
{
public:
    CpProxyLinnCoUkVolkano1C(CpDeviceC aDevice);
    ~CpProxyLinnCoUkVolkano1C();
    //CpProxyLinnCoUkVolkano1* Proxy() { return static_cast<CpProxyLinnCoUkVolkano1*>(iProxy); }

    void SyncReboot();
    void BeginReboot(FunctorAsync& aFunctor);
    void EndReboot(IAsync& aAsync);

    void SyncBootMode(Brh& aaMode);
    void BeginBootMode(FunctorAsync& aFunctor);
    void EndBootMode(IAsync& aAsync, Brh& aaMode);

    void SyncSetBootMode(const Brx& aaMode);
    void BeginSetBootMode(const Brx& aaMode, FunctorAsync& aFunctor);
    void EndSetBootMode(IAsync& aAsync);

    void SyncBspType(Brh& aaBspType);
    void BeginBspType(FunctorAsync& aFunctor);
    void EndBspType(IAsync& aAsync, Brh& aaBspType);

    void SyncUglyName(Brh& aaUglyName);
    void BeginUglyName(FunctorAsync& aFunctor);
    void EndUglyName(IAsync& aAsync, Brh& aaUglyName);

    void SyncMacAddress(Brh& aaMacAddress);
    void BeginMacAddress(FunctorAsync& aFunctor);
    void EndMacAddress(IAsync& aAsync, Brh& aaMacAddress);

    void SyncProductId(Brh& aaProductNumber);
    void BeginProductId(FunctorAsync& aFunctor);
    void EndProductId(IAsync& aAsync, Brh& aaProductNumber);

    void SyncBoardId(TUint aaIndex, Brh& aaBoardNumber);
    void BeginBoardId(TUint aaIndex, FunctorAsync& aFunctor);
    void EndBoardId(IAsync& aAsync, Brh& aaBoardNumber);

    void SyncBoardType(TUint aaIndex, Brh& aaBoardNumber);
    void BeginBoardType(TUint aaIndex, FunctorAsync& aFunctor);
    void EndBoardType(IAsync& aAsync, Brh& aaBoardNumber);

    void SyncMaxBoards(TUint& aaMaxBoards);
    void BeginMaxBoards(FunctorAsync& aFunctor);
    void EndMaxBoards(IAsync& aAsync, TUint& aaMaxBoards);

    void SyncSoftwareVersion(Brh& aaSoftwareVersion);
    void BeginSoftwareVersion(FunctorAsync& aFunctor);
    void EndSoftwareVersion(IAsync& aAsync, Brh& aaSoftwareVersion);


private:
private:
    Mutex iLock;
    mutable Mutex iPropertyLock;
    Action* iActionReboot;
    Action* iActionBootMode;
    Action* iActionSetBootMode;
    Action* iActionBspType;
    Action* iActionUglyName;
    Action* iActionMacAddress;
    Action* iActionProductId;
    Action* iActionBoardId;
    Action* iActionBoardType;
    Action* iActionMaxBoards;
    Action* iActionSoftwareVersion;
};


class SyncRebootLinnCoUkVolkano1C : public SyncProxyAction
{
public:
    SyncRebootLinnCoUkVolkano1C(CpProxyLinnCoUkVolkano1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkVolkano1C& iService;
};

SyncRebootLinnCoUkVolkano1C::SyncRebootLinnCoUkVolkano1C(CpProxyLinnCoUkVolkano1C& aProxy)
    : iService(aProxy)
{
}

void SyncRebootLinnCoUkVolkano1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndReboot(aAsync);
}


class SyncBootModeLinnCoUkVolkano1C : public SyncProxyAction
{
public:
    SyncBootModeLinnCoUkVolkano1C(CpProxyLinnCoUkVolkano1C& aProxy, Brh& aaMode);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkVolkano1C& iService;
    Brh& iaMode;
};

SyncBootModeLinnCoUkVolkano1C::SyncBootModeLinnCoUkVolkano1C(CpProxyLinnCoUkVolkano1C& aProxy, Brh& aaMode)
    : iService(aProxy)
    , iaMode(aaMode)
{
}

void SyncBootModeLinnCoUkVolkano1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndBootMode(aAsync, iaMode);
}


class SyncSetBootModeLinnCoUkVolkano1C : public SyncProxyAction
{
public:
    SyncSetBootModeLinnCoUkVolkano1C(CpProxyLinnCoUkVolkano1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkVolkano1C& iService;
};

SyncSetBootModeLinnCoUkVolkano1C::SyncSetBootModeLinnCoUkVolkano1C(CpProxyLinnCoUkVolkano1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetBootModeLinnCoUkVolkano1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetBootMode(aAsync);
}


class SyncBspTypeLinnCoUkVolkano1C : public SyncProxyAction
{
public:
    SyncBspTypeLinnCoUkVolkano1C(CpProxyLinnCoUkVolkano1C& aProxy, Brh& aaBspType);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkVolkano1C& iService;
    Brh& iaBspType;
};

SyncBspTypeLinnCoUkVolkano1C::SyncBspTypeLinnCoUkVolkano1C(CpProxyLinnCoUkVolkano1C& aProxy, Brh& aaBspType)
    : iService(aProxy)
    , iaBspType(aaBspType)
{
}

void SyncBspTypeLinnCoUkVolkano1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndBspType(aAsync, iaBspType);
}


class SyncUglyNameLinnCoUkVolkano1C : public SyncProxyAction
{
public:
    SyncUglyNameLinnCoUkVolkano1C(CpProxyLinnCoUkVolkano1C& aProxy, Brh& aaUglyName);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkVolkano1C& iService;
    Brh& iaUglyName;
};

SyncUglyNameLinnCoUkVolkano1C::SyncUglyNameLinnCoUkVolkano1C(CpProxyLinnCoUkVolkano1C& aProxy, Brh& aaUglyName)
    : iService(aProxy)
    , iaUglyName(aaUglyName)
{
}

void SyncUglyNameLinnCoUkVolkano1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndUglyName(aAsync, iaUglyName);
}


class SyncMacAddressLinnCoUkVolkano1C : public SyncProxyAction
{
public:
    SyncMacAddressLinnCoUkVolkano1C(CpProxyLinnCoUkVolkano1C& aProxy, Brh& aaMacAddress);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkVolkano1C& iService;
    Brh& iaMacAddress;
};

SyncMacAddressLinnCoUkVolkano1C::SyncMacAddressLinnCoUkVolkano1C(CpProxyLinnCoUkVolkano1C& aProxy, Brh& aaMacAddress)
    : iService(aProxy)
    , iaMacAddress(aaMacAddress)
{
}

void SyncMacAddressLinnCoUkVolkano1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndMacAddress(aAsync, iaMacAddress);
}


class SyncProductIdLinnCoUkVolkano1C : public SyncProxyAction
{
public:
    SyncProductIdLinnCoUkVolkano1C(CpProxyLinnCoUkVolkano1C& aProxy, Brh& aaProductNumber);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkVolkano1C& iService;
    Brh& iaProductNumber;
};

SyncProductIdLinnCoUkVolkano1C::SyncProductIdLinnCoUkVolkano1C(CpProxyLinnCoUkVolkano1C& aProxy, Brh& aaProductNumber)
    : iService(aProxy)
    , iaProductNumber(aaProductNumber)
{
}

void SyncProductIdLinnCoUkVolkano1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndProductId(aAsync, iaProductNumber);
}


class SyncBoardIdLinnCoUkVolkano1C : public SyncProxyAction
{
public:
    SyncBoardIdLinnCoUkVolkano1C(CpProxyLinnCoUkVolkano1C& aProxy, Brh& aaBoardNumber);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkVolkano1C& iService;
    Brh& iaBoardNumber;
};

SyncBoardIdLinnCoUkVolkano1C::SyncBoardIdLinnCoUkVolkano1C(CpProxyLinnCoUkVolkano1C& aProxy, Brh& aaBoardNumber)
    : iService(aProxy)
    , iaBoardNumber(aaBoardNumber)
{
}

void SyncBoardIdLinnCoUkVolkano1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndBoardId(aAsync, iaBoardNumber);
}


class SyncBoardTypeLinnCoUkVolkano1C : public SyncProxyAction
{
public:
    SyncBoardTypeLinnCoUkVolkano1C(CpProxyLinnCoUkVolkano1C& aProxy, Brh& aaBoardNumber);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkVolkano1C& iService;
    Brh& iaBoardNumber;
};

SyncBoardTypeLinnCoUkVolkano1C::SyncBoardTypeLinnCoUkVolkano1C(CpProxyLinnCoUkVolkano1C& aProxy, Brh& aaBoardNumber)
    : iService(aProxy)
    , iaBoardNumber(aaBoardNumber)
{
}

void SyncBoardTypeLinnCoUkVolkano1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndBoardType(aAsync, iaBoardNumber);
}


class SyncMaxBoardsLinnCoUkVolkano1C : public SyncProxyAction
{
public:
    SyncMaxBoardsLinnCoUkVolkano1C(CpProxyLinnCoUkVolkano1C& aProxy, TUint& aaMaxBoards);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkVolkano1C& iService;
    TUint& iaMaxBoards;
};

SyncMaxBoardsLinnCoUkVolkano1C::SyncMaxBoardsLinnCoUkVolkano1C(CpProxyLinnCoUkVolkano1C& aProxy, TUint& aaMaxBoards)
    : iService(aProxy)
    , iaMaxBoards(aaMaxBoards)
{
}

void SyncMaxBoardsLinnCoUkVolkano1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndMaxBoards(aAsync, iaMaxBoards);
}


class SyncSoftwareVersionLinnCoUkVolkano1C : public SyncProxyAction
{
public:
    SyncSoftwareVersionLinnCoUkVolkano1C(CpProxyLinnCoUkVolkano1C& aProxy, Brh& aaSoftwareVersion);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkVolkano1C& iService;
    Brh& iaSoftwareVersion;
};

SyncSoftwareVersionLinnCoUkVolkano1C::SyncSoftwareVersionLinnCoUkVolkano1C(CpProxyLinnCoUkVolkano1C& aProxy, Brh& aaSoftwareVersion)
    : iService(aProxy)
    , iaSoftwareVersion(aaSoftwareVersion)
{
}

void SyncSoftwareVersionLinnCoUkVolkano1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSoftwareVersion(aAsync, iaSoftwareVersion);
}

CpProxyLinnCoUkVolkano1C::CpProxyLinnCoUkVolkano1C(CpDeviceC aDevice)
    : CpProxyC("linn-co-uk", "Volkano", 1, *reinterpret_cast<CpiDevice*>(aDevice))
    , iLock("MPCS")
    , iPropertyLock("MPCP")
{
    Zapp::Parameter* param;
    TChar** allowedValues;
    TUint index;

    iActionReboot = new Action("Reboot");

    iActionBootMode = new Action("BootMode");
    index = 0;
    allowedValues = new TChar*[3];
    allowedValues[index++] = (TChar*)"Main";
    allowedValues[index++] = (TChar*)"Fallback";
    allowedValues[index++] = (TChar*)"Ram";
    param = new Zapp::ParameterString("aMode", allowedValues, 3);
    iActionBootMode->AddOutputParameter(param);
    delete[] allowedValues;

    iActionSetBootMode = new Action("SetBootMode");
    index = 0;
    allowedValues = new TChar*[2];
    allowedValues[index++] = (TChar*)"Main";
    allowedValues[index++] = (TChar*)"Fallback";
    param = new Zapp::ParameterString("aMode", allowedValues, 2);
    iActionSetBootMode->AddInputParameter(param);
    delete[] allowedValues;

    iActionBspType = new Action("BspType");
    param = new Zapp::ParameterString("aBspType");
    iActionBspType->AddOutputParameter(param);

    iActionUglyName = new Action("UglyName");
    param = new Zapp::ParameterString("aUglyName");
    iActionUglyName->AddOutputParameter(param);

    iActionMacAddress = new Action("MacAddress");
    param = new Zapp::ParameterString("aMacAddress");
    iActionMacAddress->AddOutputParameter(param);

    iActionProductId = new Action("ProductId");
    param = new Zapp::ParameterString("aProductNumber");
    iActionProductId->AddOutputParameter(param);

    iActionBoardId = new Action("BoardId");
    param = new Zapp::ParameterUint("aIndex");
    iActionBoardId->AddInputParameter(param);
    param = new Zapp::ParameterString("aBoardNumber");
    iActionBoardId->AddOutputParameter(param);

    iActionBoardType = new Action("BoardType");
    param = new Zapp::ParameterUint("aIndex");
    iActionBoardType->AddInputParameter(param);
    param = new Zapp::ParameterString("aBoardNumber");
    iActionBoardType->AddOutputParameter(param);

    iActionMaxBoards = new Action("MaxBoards");
    param = new Zapp::ParameterUint("aMaxBoards");
    iActionMaxBoards->AddOutputParameter(param);

    iActionSoftwareVersion = new Action("SoftwareVersion");
    param = new Zapp::ParameterString("aSoftwareVersion");
    iActionSoftwareVersion->AddOutputParameter(param);
}

CpProxyLinnCoUkVolkano1C::~CpProxyLinnCoUkVolkano1C()
{
    delete iActionReboot;
    delete iActionBootMode;
    delete iActionSetBootMode;
    delete iActionBspType;
    delete iActionUglyName;
    delete iActionMacAddress;
    delete iActionProductId;
    delete iActionBoardId;
    delete iActionBoardType;
    delete iActionMaxBoards;
    delete iActionSoftwareVersion;
}

void CpProxyLinnCoUkVolkano1C::SyncReboot()
{
    SyncRebootLinnCoUkVolkano1C sync(*this);
    BeginReboot(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkVolkano1C::BeginReboot(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionReboot, aFunctor);
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkVolkano1C::EndReboot(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Reboot"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkVolkano1C::SyncBootMode(Brh& aaMode)
{
    SyncBootModeLinnCoUkVolkano1C sync(*this, aaMode);
    BeginBootMode(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkVolkano1C::BeginBootMode(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionBootMode, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionBootMode->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkVolkano1C::EndBootMode(IAsync& aAsync, Brh& aaMode)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("BootMode"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aaMode);
}

void CpProxyLinnCoUkVolkano1C::SyncSetBootMode(const Brx& aaMode)
{
    SyncSetBootModeLinnCoUkVolkano1C sync(*this);
    BeginSetBootMode(aaMode, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkVolkano1C::BeginSetBootMode(const Brx& aaMode, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetBootMode, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetBootMode->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aaMode));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkVolkano1C::EndSetBootMode(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetBootMode"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkVolkano1C::SyncBspType(Brh& aaBspType)
{
    SyncBspTypeLinnCoUkVolkano1C sync(*this, aaBspType);
    BeginBspType(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkVolkano1C::BeginBspType(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionBspType, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionBspType->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkVolkano1C::EndBspType(IAsync& aAsync, Brh& aaBspType)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("BspType"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aaBspType);
}

void CpProxyLinnCoUkVolkano1C::SyncUglyName(Brh& aaUglyName)
{
    SyncUglyNameLinnCoUkVolkano1C sync(*this, aaUglyName);
    BeginUglyName(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkVolkano1C::BeginUglyName(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionUglyName, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionUglyName->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkVolkano1C::EndUglyName(IAsync& aAsync, Brh& aaUglyName)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("UglyName"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aaUglyName);
}

void CpProxyLinnCoUkVolkano1C::SyncMacAddress(Brh& aaMacAddress)
{
    SyncMacAddressLinnCoUkVolkano1C sync(*this, aaMacAddress);
    BeginMacAddress(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkVolkano1C::BeginMacAddress(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionMacAddress, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionMacAddress->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkVolkano1C::EndMacAddress(IAsync& aAsync, Brh& aaMacAddress)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("MacAddress"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aaMacAddress);
}

void CpProxyLinnCoUkVolkano1C::SyncProductId(Brh& aaProductNumber)
{
    SyncProductIdLinnCoUkVolkano1C sync(*this, aaProductNumber);
    BeginProductId(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkVolkano1C::BeginProductId(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionProductId, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionProductId->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkVolkano1C::EndProductId(IAsync& aAsync, Brh& aaProductNumber)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("ProductId"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aaProductNumber);
}

void CpProxyLinnCoUkVolkano1C::SyncBoardId(TUint aaIndex, Brh& aaBoardNumber)
{
    SyncBoardIdLinnCoUkVolkano1C sync(*this, aaBoardNumber);
    BeginBoardId(aaIndex, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkVolkano1C::BeginBoardId(TUint aaIndex, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionBoardId, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionBoardId->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaIndex));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionBoardId->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkVolkano1C::EndBoardId(IAsync& aAsync, Brh& aaBoardNumber)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("BoardId"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aaBoardNumber);
}

void CpProxyLinnCoUkVolkano1C::SyncBoardType(TUint aaIndex, Brh& aaBoardNumber)
{
    SyncBoardTypeLinnCoUkVolkano1C sync(*this, aaBoardNumber);
    BeginBoardType(aaIndex, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkVolkano1C::BeginBoardType(TUint aaIndex, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionBoardType, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionBoardType->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaIndex));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionBoardType->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkVolkano1C::EndBoardType(IAsync& aAsync, Brh& aaBoardNumber)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("BoardType"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aaBoardNumber);
}

void CpProxyLinnCoUkVolkano1C::SyncMaxBoards(TUint& aaMaxBoards)
{
    SyncMaxBoardsLinnCoUkVolkano1C sync(*this, aaMaxBoards);
    BeginMaxBoards(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkVolkano1C::BeginMaxBoards(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionMaxBoards, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionMaxBoards->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkVolkano1C::EndMaxBoards(IAsync& aAsync, TUint& aaMaxBoards)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("MaxBoards"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aaMaxBoards = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyLinnCoUkVolkano1C::SyncSoftwareVersion(Brh& aaSoftwareVersion)
{
    SyncSoftwareVersionLinnCoUkVolkano1C sync(*this, aaSoftwareVersion);
    BeginSoftwareVersion(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkVolkano1C::BeginSoftwareVersion(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSoftwareVersion, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionSoftwareVersion->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkVolkano1C::EndSoftwareVersion(IAsync& aAsync, Brh& aaSoftwareVersion)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SoftwareVersion"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aaSoftwareVersion);
}


THandle CpProxyLinnCoUkVolkano1Create(CpDeviceC aDevice)
{
    return new CpProxyLinnCoUkVolkano1C(aDevice);
}

void CpProxyLinnCoUkVolkano1Destroy(THandle aHandle)
{
    CpProxyLinnCoUkVolkano1C* proxyC = reinterpret_cast<CpProxyLinnCoUkVolkano1C*>(aHandle);
    delete proxyC;
}

void CpProxyLinnCoUkVolkano1SyncReboot(THandle aHandle)
{
    CpProxyLinnCoUkVolkano1C* proxyC = reinterpret_cast<CpProxyLinnCoUkVolkano1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncReboot();
}

void CpProxyLinnCoUkVolkano1BeginReboot(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkVolkano1C* proxyC = reinterpret_cast<CpProxyLinnCoUkVolkano1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginReboot(functor);
}

int32_t CpProxyLinnCoUkVolkano1EndReboot(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkVolkano1C* proxyC = reinterpret_cast<CpProxyLinnCoUkVolkano1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndReboot(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkVolkano1SyncBootMode(THandle aHandle, char** aaMode)
{
    CpProxyLinnCoUkVolkano1C* proxyC = reinterpret_cast<CpProxyLinnCoUkVolkano1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaMode;
    proxyC->SyncBootMode(buf_aaMode);
    *aaMode = buf_aaMode.Extract();
}

void CpProxyLinnCoUkVolkano1BeginBootMode(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkVolkano1C* proxyC = reinterpret_cast<CpProxyLinnCoUkVolkano1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginBootMode(functor);
}

int32_t CpProxyLinnCoUkVolkano1EndBootMode(THandle aHandle, ZappHandleAsync aAsync, char** aaMode)
{
    int32_t err = 0;
    CpProxyLinnCoUkVolkano1C* proxyC = reinterpret_cast<CpProxyLinnCoUkVolkano1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaMode;
    *aaMode = NULL;
    try {
        proxyC->EndBootMode(*async, buf_aaMode);
        *aaMode = buf_aaMode.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkVolkano1SyncSetBootMode(THandle aHandle, const char* aaMode)
{
    CpProxyLinnCoUkVolkano1C* proxyC = reinterpret_cast<CpProxyLinnCoUkVolkano1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaMode(aaMode);
    proxyC->SyncSetBootMode(buf_aaMode);
}

void CpProxyLinnCoUkVolkano1BeginSetBootMode(THandle aHandle, const char* aaMode, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkVolkano1C* proxyC = reinterpret_cast<CpProxyLinnCoUkVolkano1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaMode(aaMode);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetBootMode(buf_aaMode, functor);
}

int32_t CpProxyLinnCoUkVolkano1EndSetBootMode(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkVolkano1C* proxyC = reinterpret_cast<CpProxyLinnCoUkVolkano1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetBootMode(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkVolkano1SyncBspType(THandle aHandle, char** aaBspType)
{
    CpProxyLinnCoUkVolkano1C* proxyC = reinterpret_cast<CpProxyLinnCoUkVolkano1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaBspType;
    proxyC->SyncBspType(buf_aaBspType);
    *aaBspType = buf_aaBspType.Extract();
}

void CpProxyLinnCoUkVolkano1BeginBspType(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkVolkano1C* proxyC = reinterpret_cast<CpProxyLinnCoUkVolkano1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginBspType(functor);
}

int32_t CpProxyLinnCoUkVolkano1EndBspType(THandle aHandle, ZappHandleAsync aAsync, char** aaBspType)
{
    int32_t err = 0;
    CpProxyLinnCoUkVolkano1C* proxyC = reinterpret_cast<CpProxyLinnCoUkVolkano1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaBspType;
    *aaBspType = NULL;
    try {
        proxyC->EndBspType(*async, buf_aaBspType);
        *aaBspType = buf_aaBspType.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkVolkano1SyncUglyName(THandle aHandle, char** aaUglyName)
{
    CpProxyLinnCoUkVolkano1C* proxyC = reinterpret_cast<CpProxyLinnCoUkVolkano1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaUglyName;
    proxyC->SyncUglyName(buf_aaUglyName);
    *aaUglyName = buf_aaUglyName.Extract();
}

void CpProxyLinnCoUkVolkano1BeginUglyName(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkVolkano1C* proxyC = reinterpret_cast<CpProxyLinnCoUkVolkano1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginUglyName(functor);
}

int32_t CpProxyLinnCoUkVolkano1EndUglyName(THandle aHandle, ZappHandleAsync aAsync, char** aaUglyName)
{
    int32_t err = 0;
    CpProxyLinnCoUkVolkano1C* proxyC = reinterpret_cast<CpProxyLinnCoUkVolkano1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaUglyName;
    *aaUglyName = NULL;
    try {
        proxyC->EndUglyName(*async, buf_aaUglyName);
        *aaUglyName = buf_aaUglyName.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkVolkano1SyncMacAddress(THandle aHandle, char** aaMacAddress)
{
    CpProxyLinnCoUkVolkano1C* proxyC = reinterpret_cast<CpProxyLinnCoUkVolkano1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaMacAddress;
    proxyC->SyncMacAddress(buf_aaMacAddress);
    *aaMacAddress = buf_aaMacAddress.Extract();
}

void CpProxyLinnCoUkVolkano1BeginMacAddress(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkVolkano1C* proxyC = reinterpret_cast<CpProxyLinnCoUkVolkano1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginMacAddress(functor);
}

int32_t CpProxyLinnCoUkVolkano1EndMacAddress(THandle aHandle, ZappHandleAsync aAsync, char** aaMacAddress)
{
    int32_t err = 0;
    CpProxyLinnCoUkVolkano1C* proxyC = reinterpret_cast<CpProxyLinnCoUkVolkano1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaMacAddress;
    *aaMacAddress = NULL;
    try {
        proxyC->EndMacAddress(*async, buf_aaMacAddress);
        *aaMacAddress = buf_aaMacAddress.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkVolkano1SyncProductId(THandle aHandle, char** aaProductNumber)
{
    CpProxyLinnCoUkVolkano1C* proxyC = reinterpret_cast<CpProxyLinnCoUkVolkano1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaProductNumber;
    proxyC->SyncProductId(buf_aaProductNumber);
    *aaProductNumber = buf_aaProductNumber.Extract();
}

void CpProxyLinnCoUkVolkano1BeginProductId(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkVolkano1C* proxyC = reinterpret_cast<CpProxyLinnCoUkVolkano1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginProductId(functor);
}

int32_t CpProxyLinnCoUkVolkano1EndProductId(THandle aHandle, ZappHandleAsync aAsync, char** aaProductNumber)
{
    int32_t err = 0;
    CpProxyLinnCoUkVolkano1C* proxyC = reinterpret_cast<CpProxyLinnCoUkVolkano1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaProductNumber;
    *aaProductNumber = NULL;
    try {
        proxyC->EndProductId(*async, buf_aaProductNumber);
        *aaProductNumber = buf_aaProductNumber.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkVolkano1SyncBoardId(THandle aHandle, uint32_t aaIndex, char** aaBoardNumber)
{
    CpProxyLinnCoUkVolkano1C* proxyC = reinterpret_cast<CpProxyLinnCoUkVolkano1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaBoardNumber;
    proxyC->SyncBoardId(aaIndex, buf_aaBoardNumber);
    *aaBoardNumber = buf_aaBoardNumber.Extract();
}

void CpProxyLinnCoUkVolkano1BeginBoardId(THandle aHandle, uint32_t aaIndex, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkVolkano1C* proxyC = reinterpret_cast<CpProxyLinnCoUkVolkano1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginBoardId(aaIndex, functor);
}

int32_t CpProxyLinnCoUkVolkano1EndBoardId(THandle aHandle, ZappHandleAsync aAsync, char** aaBoardNumber)
{
    int32_t err = 0;
    CpProxyLinnCoUkVolkano1C* proxyC = reinterpret_cast<CpProxyLinnCoUkVolkano1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaBoardNumber;
    *aaBoardNumber = NULL;
    try {
        proxyC->EndBoardId(*async, buf_aaBoardNumber);
        *aaBoardNumber = buf_aaBoardNumber.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkVolkano1SyncBoardType(THandle aHandle, uint32_t aaIndex, char** aaBoardNumber)
{
    CpProxyLinnCoUkVolkano1C* proxyC = reinterpret_cast<CpProxyLinnCoUkVolkano1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaBoardNumber;
    proxyC->SyncBoardType(aaIndex, buf_aaBoardNumber);
    *aaBoardNumber = buf_aaBoardNumber.Extract();
}

void CpProxyLinnCoUkVolkano1BeginBoardType(THandle aHandle, uint32_t aaIndex, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkVolkano1C* proxyC = reinterpret_cast<CpProxyLinnCoUkVolkano1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginBoardType(aaIndex, functor);
}

int32_t CpProxyLinnCoUkVolkano1EndBoardType(THandle aHandle, ZappHandleAsync aAsync, char** aaBoardNumber)
{
    int32_t err = 0;
    CpProxyLinnCoUkVolkano1C* proxyC = reinterpret_cast<CpProxyLinnCoUkVolkano1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaBoardNumber;
    *aaBoardNumber = NULL;
    try {
        proxyC->EndBoardType(*async, buf_aaBoardNumber);
        *aaBoardNumber = buf_aaBoardNumber.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkVolkano1SyncMaxBoards(THandle aHandle, uint32_t* aaMaxBoards)
{
    CpProxyLinnCoUkVolkano1C* proxyC = reinterpret_cast<CpProxyLinnCoUkVolkano1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncMaxBoards(*aaMaxBoards);
}

void CpProxyLinnCoUkVolkano1BeginMaxBoards(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkVolkano1C* proxyC = reinterpret_cast<CpProxyLinnCoUkVolkano1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginMaxBoards(functor);
}

int32_t CpProxyLinnCoUkVolkano1EndMaxBoards(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaMaxBoards)
{
    int32_t err = 0;
    CpProxyLinnCoUkVolkano1C* proxyC = reinterpret_cast<CpProxyLinnCoUkVolkano1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndMaxBoards(*async, *aaMaxBoards);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkVolkano1SyncSoftwareVersion(THandle aHandle, char** aaSoftwareVersion)
{
    CpProxyLinnCoUkVolkano1C* proxyC = reinterpret_cast<CpProxyLinnCoUkVolkano1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaSoftwareVersion;
    proxyC->SyncSoftwareVersion(buf_aaSoftwareVersion);
    *aaSoftwareVersion = buf_aaSoftwareVersion.Extract();
}

void CpProxyLinnCoUkVolkano1BeginSoftwareVersion(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkVolkano1C* proxyC = reinterpret_cast<CpProxyLinnCoUkVolkano1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSoftwareVersion(functor);
}

int32_t CpProxyLinnCoUkVolkano1EndSoftwareVersion(THandle aHandle, ZappHandleAsync aAsync, char** aaSoftwareVersion)
{
    int32_t err = 0;
    CpProxyLinnCoUkVolkano1C* proxyC = reinterpret_cast<CpProxyLinnCoUkVolkano1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaSoftwareVersion;
    *aaSoftwareVersion = NULL;
    try {
        proxyC->EndSoftwareVersion(*async, buf_aaSoftwareVersion);
        *aaSoftwareVersion = buf_aaSoftwareVersion.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

