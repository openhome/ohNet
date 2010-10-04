#include <Core/CpLinnCoUkVolkano1.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Core/CpDevice.h>

using namespace Zapp;


class SyncRebootLinnCoUkVolkano1 : public SyncProxyAction
{
public:
    SyncRebootLinnCoUkVolkano1(CpProxyLinnCoUkVolkano1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkVolkano1& iService;
};

SyncRebootLinnCoUkVolkano1::SyncRebootLinnCoUkVolkano1(CpProxyLinnCoUkVolkano1& aService)
    : iService(aService)
{
}

void SyncRebootLinnCoUkVolkano1::CompleteRequest(IAsync& aAsync)
{
    iService.EndReboot(aAsync);
}


class SyncBootModeLinnCoUkVolkano1 : public SyncProxyAction
{
public:
    SyncBootModeLinnCoUkVolkano1(CpProxyLinnCoUkVolkano1& aService, Brh& aaMode);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkVolkano1& iService;
    Brh& iaMode;
};

SyncBootModeLinnCoUkVolkano1::SyncBootModeLinnCoUkVolkano1(CpProxyLinnCoUkVolkano1& aService, Brh& aaMode)
    : iService(aService)
    , iaMode(aaMode)
{
}

void SyncBootModeLinnCoUkVolkano1::CompleteRequest(IAsync& aAsync)
{
    iService.EndBootMode(aAsync, iaMode);
}


class SyncSetBootModeLinnCoUkVolkano1 : public SyncProxyAction
{
public:
    SyncSetBootModeLinnCoUkVolkano1(CpProxyLinnCoUkVolkano1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkVolkano1& iService;
};

SyncSetBootModeLinnCoUkVolkano1::SyncSetBootModeLinnCoUkVolkano1(CpProxyLinnCoUkVolkano1& aService)
    : iService(aService)
{
}

void SyncSetBootModeLinnCoUkVolkano1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetBootMode(aAsync);
}


class SyncBspTypeLinnCoUkVolkano1 : public SyncProxyAction
{
public:
    SyncBspTypeLinnCoUkVolkano1(CpProxyLinnCoUkVolkano1& aService, Brh& aaBspType);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkVolkano1& iService;
    Brh& iaBspType;
};

SyncBspTypeLinnCoUkVolkano1::SyncBspTypeLinnCoUkVolkano1(CpProxyLinnCoUkVolkano1& aService, Brh& aaBspType)
    : iService(aService)
    , iaBspType(aaBspType)
{
}

void SyncBspTypeLinnCoUkVolkano1::CompleteRequest(IAsync& aAsync)
{
    iService.EndBspType(aAsync, iaBspType);
}


class SyncUglyNameLinnCoUkVolkano1 : public SyncProxyAction
{
public:
    SyncUglyNameLinnCoUkVolkano1(CpProxyLinnCoUkVolkano1& aService, Brh& aaUglyName);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkVolkano1& iService;
    Brh& iaUglyName;
};

SyncUglyNameLinnCoUkVolkano1::SyncUglyNameLinnCoUkVolkano1(CpProxyLinnCoUkVolkano1& aService, Brh& aaUglyName)
    : iService(aService)
    , iaUglyName(aaUglyName)
{
}

void SyncUglyNameLinnCoUkVolkano1::CompleteRequest(IAsync& aAsync)
{
    iService.EndUglyName(aAsync, iaUglyName);
}


class SyncMacAddressLinnCoUkVolkano1 : public SyncProxyAction
{
public:
    SyncMacAddressLinnCoUkVolkano1(CpProxyLinnCoUkVolkano1& aService, Brh& aaMacAddress);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkVolkano1& iService;
    Brh& iaMacAddress;
};

SyncMacAddressLinnCoUkVolkano1::SyncMacAddressLinnCoUkVolkano1(CpProxyLinnCoUkVolkano1& aService, Brh& aaMacAddress)
    : iService(aService)
    , iaMacAddress(aaMacAddress)
{
}

void SyncMacAddressLinnCoUkVolkano1::CompleteRequest(IAsync& aAsync)
{
    iService.EndMacAddress(aAsync, iaMacAddress);
}


class SyncProductIdLinnCoUkVolkano1 : public SyncProxyAction
{
public:
    SyncProductIdLinnCoUkVolkano1(CpProxyLinnCoUkVolkano1& aService, Brh& aaProductNumber);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkVolkano1& iService;
    Brh& iaProductNumber;
};

SyncProductIdLinnCoUkVolkano1::SyncProductIdLinnCoUkVolkano1(CpProxyLinnCoUkVolkano1& aService, Brh& aaProductNumber)
    : iService(aService)
    , iaProductNumber(aaProductNumber)
{
}

void SyncProductIdLinnCoUkVolkano1::CompleteRequest(IAsync& aAsync)
{
    iService.EndProductId(aAsync, iaProductNumber);
}


class SyncBoardIdLinnCoUkVolkano1 : public SyncProxyAction
{
public:
    SyncBoardIdLinnCoUkVolkano1(CpProxyLinnCoUkVolkano1& aService, Brh& aaBoardNumber);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkVolkano1& iService;
    Brh& iaBoardNumber;
};

SyncBoardIdLinnCoUkVolkano1::SyncBoardIdLinnCoUkVolkano1(CpProxyLinnCoUkVolkano1& aService, Brh& aaBoardNumber)
    : iService(aService)
    , iaBoardNumber(aaBoardNumber)
{
}

void SyncBoardIdLinnCoUkVolkano1::CompleteRequest(IAsync& aAsync)
{
    iService.EndBoardId(aAsync, iaBoardNumber);
}


class SyncBoardTypeLinnCoUkVolkano1 : public SyncProxyAction
{
public:
    SyncBoardTypeLinnCoUkVolkano1(CpProxyLinnCoUkVolkano1& aService, Brh& aaBoardNumber);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkVolkano1& iService;
    Brh& iaBoardNumber;
};

SyncBoardTypeLinnCoUkVolkano1::SyncBoardTypeLinnCoUkVolkano1(CpProxyLinnCoUkVolkano1& aService, Brh& aaBoardNumber)
    : iService(aService)
    , iaBoardNumber(aaBoardNumber)
{
}

void SyncBoardTypeLinnCoUkVolkano1::CompleteRequest(IAsync& aAsync)
{
    iService.EndBoardType(aAsync, iaBoardNumber);
}


class SyncMaxBoardsLinnCoUkVolkano1 : public SyncProxyAction
{
public:
    SyncMaxBoardsLinnCoUkVolkano1(CpProxyLinnCoUkVolkano1& aService, TUint& aaMaxBoards);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkVolkano1& iService;
    TUint& iaMaxBoards;
};

SyncMaxBoardsLinnCoUkVolkano1::SyncMaxBoardsLinnCoUkVolkano1(CpProxyLinnCoUkVolkano1& aService, TUint& aaMaxBoards)
    : iService(aService)
    , iaMaxBoards(aaMaxBoards)
{
}

void SyncMaxBoardsLinnCoUkVolkano1::CompleteRequest(IAsync& aAsync)
{
    iService.EndMaxBoards(aAsync, iaMaxBoards);
}


class SyncSoftwareVersionLinnCoUkVolkano1 : public SyncProxyAction
{
public:
    SyncSoftwareVersionLinnCoUkVolkano1(CpProxyLinnCoUkVolkano1& aService, Brh& aaSoftwareVersion);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkVolkano1& iService;
    Brh& iaSoftwareVersion;
};

SyncSoftwareVersionLinnCoUkVolkano1::SyncSoftwareVersionLinnCoUkVolkano1(CpProxyLinnCoUkVolkano1& aService, Brh& aaSoftwareVersion)
    : iService(aService)
    , iaSoftwareVersion(aaSoftwareVersion)
{
}

void SyncSoftwareVersionLinnCoUkVolkano1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSoftwareVersion(aAsync, iaSoftwareVersion);
}


CpProxyLinnCoUkVolkano1::CpProxyLinnCoUkVolkano1(CpDevice& aDevice)
{
    iService = new CpiService("linn-co-uk", "Volkano", 1, aDevice.Device());
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

CpProxyLinnCoUkVolkano1::~CpProxyLinnCoUkVolkano1()
{
    delete iService;
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

void CpProxyLinnCoUkVolkano1::SyncReboot()
{
    SyncRebootLinnCoUkVolkano1 sync(*this);
    BeginReboot(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkVolkano1::BeginReboot(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionReboot, aFunctor);
    invocation->Invoke();
}

void CpProxyLinnCoUkVolkano1::EndReboot(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Reboot"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkVolkano1::SyncBootMode(Brh& aaMode)
{
    SyncBootModeLinnCoUkVolkano1 sync(*this, aaMode);
    BeginBootMode(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkVolkano1::BeginBootMode(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionBootMode, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionBootMode->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkVolkano1::EndBootMode(IAsync& aAsync, Brh& aaMode)
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

void CpProxyLinnCoUkVolkano1::SyncSetBootMode(const Brx& aaMode)
{
    SyncSetBootModeLinnCoUkVolkano1 sync(*this);
    BeginSetBootMode(aaMode, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkVolkano1::BeginSetBootMode(const Brx& aaMode, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetBootMode, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetBootMode->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aaMode));
    invocation->Invoke();
}

void CpProxyLinnCoUkVolkano1::EndSetBootMode(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetBootMode"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkVolkano1::SyncBspType(Brh& aaBspType)
{
    SyncBspTypeLinnCoUkVolkano1 sync(*this, aaBspType);
    BeginBspType(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkVolkano1::BeginBspType(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionBspType, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionBspType->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkVolkano1::EndBspType(IAsync& aAsync, Brh& aaBspType)
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

void CpProxyLinnCoUkVolkano1::SyncUglyName(Brh& aaUglyName)
{
    SyncUglyNameLinnCoUkVolkano1 sync(*this, aaUglyName);
    BeginUglyName(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkVolkano1::BeginUglyName(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionUglyName, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionUglyName->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkVolkano1::EndUglyName(IAsync& aAsync, Brh& aaUglyName)
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

void CpProxyLinnCoUkVolkano1::SyncMacAddress(Brh& aaMacAddress)
{
    SyncMacAddressLinnCoUkVolkano1 sync(*this, aaMacAddress);
    BeginMacAddress(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkVolkano1::BeginMacAddress(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionMacAddress, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionMacAddress->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkVolkano1::EndMacAddress(IAsync& aAsync, Brh& aaMacAddress)
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

void CpProxyLinnCoUkVolkano1::SyncProductId(Brh& aaProductNumber)
{
    SyncProductIdLinnCoUkVolkano1 sync(*this, aaProductNumber);
    BeginProductId(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkVolkano1::BeginProductId(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionProductId, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionProductId->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkVolkano1::EndProductId(IAsync& aAsync, Brh& aaProductNumber)
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

void CpProxyLinnCoUkVolkano1::SyncBoardId(TUint aaIndex, Brh& aaBoardNumber)
{
    SyncBoardIdLinnCoUkVolkano1 sync(*this, aaBoardNumber);
    BeginBoardId(aaIndex, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkVolkano1::BeginBoardId(TUint aaIndex, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionBoardId, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionBoardId->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaIndex));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionBoardId->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkVolkano1::EndBoardId(IAsync& aAsync, Brh& aaBoardNumber)
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

void CpProxyLinnCoUkVolkano1::SyncBoardType(TUint aaIndex, Brh& aaBoardNumber)
{
    SyncBoardTypeLinnCoUkVolkano1 sync(*this, aaBoardNumber);
    BeginBoardType(aaIndex, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkVolkano1::BeginBoardType(TUint aaIndex, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionBoardType, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionBoardType->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaIndex));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionBoardType->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkVolkano1::EndBoardType(IAsync& aAsync, Brh& aaBoardNumber)
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

void CpProxyLinnCoUkVolkano1::SyncMaxBoards(TUint& aaMaxBoards)
{
    SyncMaxBoardsLinnCoUkVolkano1 sync(*this, aaMaxBoards);
    BeginMaxBoards(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkVolkano1::BeginMaxBoards(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionMaxBoards, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionMaxBoards->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkVolkano1::EndMaxBoards(IAsync& aAsync, TUint& aaMaxBoards)
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

void CpProxyLinnCoUkVolkano1::SyncSoftwareVersion(Brh& aaSoftwareVersion)
{
    SyncSoftwareVersionLinnCoUkVolkano1 sync(*this, aaSoftwareVersion);
    BeginSoftwareVersion(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkVolkano1::BeginSoftwareVersion(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSoftwareVersion, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionSoftwareVersion->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkVolkano1::EndSoftwareVersion(IAsync& aAsync, Brh& aaSoftwareVersion)
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

