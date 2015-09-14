#include <OpenHome/Net/Private/CpiService.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Private/CpiDevice.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Net/Private/CpiStack.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Net/Core/CpProxy.h>
#include <OpenHome/Net/Private/Error.h>
#include <OpenHome/Net/Private/CpiSubscription.h>

#include <stdio.h>
#include <stdlib.h>

using namespace OpenHome;
using namespace OpenHome::Net;

// CpiService

CpiService::CpiService(const TChar* aDomain, const TChar* aName, TUint aVersion, CpiDevice& aDevice)
    : Service(aDevice.GetCpStack().Env(), aDomain, aName, aDevice.Version(aDomain, aName, aVersion))
    , iDevice(aDevice)
    , iLock("SRVM")
    , iPendingInvocations(0)
    , iShutdownSignal("SRVS", 0)
    , iInterrupt(false)
    , iSubscription(NULL)
{
    iDevice.AddRef();
    iDevice.GetCpStack().Env().AddObject(this);
    if (aVersion != iServiceType.Version()) {
        const Brx& serviceName = iServiceType.FullName();
        const Brx& udn = iDevice.Udn();
        LOG(kService, "CpiService: addr=%p, serviceType=%.*s, device=%.*s, presenting proxy v%u as v%u\n",
                      this, PBUF(serviceName), PBUF(udn), aVersion, iServiceType.Version());
    }
}

CpiService::~CpiService()
{
    iInterrupt = true;
    try {
        InvocationManager& invocationMgr = iDevice.GetCpStack().InvocationManager();
        invocationMgr.Interrupt(*this);
    }
    catch (NetworkError&) {}
    Unsubscribe();
    TBool wait;
    iLock.Wait();
    wait = (iPendingInvocations > 0);
    iShutdownSignal.Clear();
    iLock.Signal();
    if (wait) {
        iShutdownSignal.Wait();
    }
    Environment& env = iDevice.GetCpStack().Env();
    iDevice.RemoveRef();
    env.RemoveObject(this);
}

Invocation* CpiService::Invocation(const Action& aAction, FunctorAsync& aFunctor)
{
    iLock.Wait();
    iPendingInvocations++;
    iLock.Signal();
    InvocationManager& invocationMgr = iDevice.GetCpStack().InvocationManager();
    OpenHome::Net::Invocation* invocation = invocationMgr.Invocation();
    invocation->Set(*this, aAction, iDevice, aFunctor);
    return invocation;
}

TBool CpiService::Subscribe(IEventProcessor& aEventProcessor)
{
    ASSERT(iSubscription == NULL);
    if (iDevice.IsRemoved()) {
        return false;
    }
    iSubscription = iDevice.GetCpStack().SubscriptionManager().NewSubscription(iDevice, aEventProcessor, iServiceType);
    return true;
}

void CpiService::Unsubscribe()
{
    if (iSubscription != NULL) {
        iSubscription->Unsubscribe();
        iSubscription->RemoveRef();
        iSubscription = NULL;
    }
}

void CpiService::InvocationCompleted()
{
    TBool signal;
    iLock.Wait();
    signal = (--iPendingInvocations == 0);
    iLock.Signal();
    if (signal) {
        iShutdownSignal.Signal();
    }
}

TBool CpiService::Interrupt() const
{
    return iInterrupt;
}

CpiDevice& CpiService::Device()
{
    return iDevice;
}

TUint CpiService::Version() const
{
    return iServiceType.Version();
}

void CpiService::ListObjectDetails() const
{
    Log::Print("  CpiService: addr=%p, serviceType=", this);
    Log::Print(ServiceType().FullName());
    Log::Print(", device=");
    Log::Print(iDevice.Udn());
    if (iSubscription != NULL) {
        Log::Print(", subscribed");
    }
    Log::Print("\n");
}


// Argument

const OpenHome::Net::Parameter& Argument::Parameter() const
{
    return iParameter;
}

Argument::Argument(const OpenHome::Net::Parameter& aParameter)
    : iParameter(aParameter)
{
}

Argument::~Argument()
{
}

void Argument::ValidationFailed(const OpenHome::Net::Parameter& aParameter)
{
    Log::Print("Validation of Parameter ");
    Log::Print(aParameter.Name());
    Log::Print(" failed, asserting\n");
    ASSERTS();
}


// ArgumentString

ArgumentString::ArgumentString(const OpenHome::Net::Parameter& aParameter)
    : Argument(aParameter)
{
}

ArgumentString::ArgumentString(const OpenHome::Net::Parameter& aParameter, const Brx& aValue)
    : Argument(aParameter)
{
    try {
        aParameter.ValidateString(aValue);
        if (aValue.Bytes() > 0) {
            iValue.Set(aValue);
        }
    }
    catch (ParameterValidationError&) {
        ValidationFailed(aParameter);
    }
}

ArgumentString::~ArgumentString()
{
}

const Brx& ArgumentString::Value() const
{
    return iValue;
}

void ArgumentString::TransferTo(Brh& aBrh)
{
    iValue.TransferTo(aBrh);
}

void ArgumentString::ProcessInput(IInputArgumentProcessor& aProcessor)
{
    aProcessor.ProcessString(iValue);
}

void ArgumentString::ProcessOutput(IOutputProcessor& aProcessor, const Brx& aBuffer)
{
    aProcessor.ProcessString(aBuffer, iValue);
    iParameter.ValidateString(iValue);
}


// ArgumentInt

ArgumentInt::ArgumentInt(const OpenHome::Net::Parameter& aParameter)
    : Argument(aParameter)
    , iValue(0)
{
}

ArgumentInt::ArgumentInt(const OpenHome::Net::Parameter& aParameter, TInt aValue)
    : Argument(aParameter)
    , iValue(aValue)
{
    try {
        aParameter.ValidateInt(aValue);
    }
    catch (ParameterValidationError&) {
        ValidationFailed(aParameter);
    }
}

ArgumentInt::~ArgumentInt()
{
}

TInt ArgumentInt::Value() const
{
    return iValue;
}

void ArgumentInt::ProcessInput(IInputArgumentProcessor& aProcessor)
{
    aProcessor.ProcessInt(iValue);
}

void ArgumentInt::ProcessOutput(IOutputProcessor& aProcessor, const Brx& aBuffer)
{
    aProcessor.ProcessInt(aBuffer, iValue);
    iParameter.ValidateInt(iValue);
}


// ArgumentUint

ArgumentUint::ArgumentUint(const OpenHome::Net::Parameter& aParameter)
    : Argument(aParameter)
    , iValue(0)
{
}

ArgumentUint::ArgumentUint(const OpenHome::Net::Parameter& aParameter, TUint aValue)
    : Argument(aParameter)
    , iValue(aValue)
{
    try {
        aParameter.ValidateUint(aValue);
    }
    catch (ParameterValidationError&) {
        ValidationFailed(aParameter);
    }
}

ArgumentUint::~ArgumentUint()
{
}

TUint ArgumentUint::Value() const
{
    return iValue;
}

void ArgumentUint::ProcessInput(IInputArgumentProcessor& aProcessor)
{
    aProcessor.ProcessUint(iValue);
}

void ArgumentUint::ProcessOutput(IOutputProcessor& aProcessor, const Brx& aBuffer)
{
    aProcessor.ProcessUint(aBuffer, iValue);
    iParameter.ValidateUint(iValue);
}


// ArgumentBool

ArgumentBool::ArgumentBool(const OpenHome::Net::Parameter& aParameter)
    : Argument(aParameter)
    , iValue(false)
{
}

ArgumentBool::ArgumentBool(const OpenHome::Net::Parameter& aParameter, TBool aValue)
    : Argument(aParameter)
    , iValue(aValue)
{
    try {
        aParameter.ValidateBool(aValue);
    }
    catch (ParameterValidationError&) {
        ValidationFailed(aParameter);
    }
}

ArgumentBool::~ArgumentBool()
{
}

TBool ArgumentBool::Value() const
{
    return iValue;
}

void ArgumentBool::ProcessInput(IInputArgumentProcessor& aProcessor)
{
    aProcessor.ProcessBool(iValue);
}

void ArgumentBool::ProcessOutput(IOutputProcessor& aProcessor, const Brx& aBuffer)
{
    aProcessor.ProcessBool(aBuffer, iValue);
    iParameter.ValidateBool(iValue);
}


// ArgumentBinary

ArgumentBinary::ArgumentBinary(const OpenHome::Net::Parameter& aParameter)
    : Argument(aParameter)
{
}

ArgumentBinary::ArgumentBinary(const OpenHome::Net::Parameter& aParameter, const Brx& aValue)
    : Argument(aParameter)
{
    try {
        aParameter.ValidateBinary(aValue);
        if (aValue.Bytes() > 0) {
            iValue.Set(aValue);
        }
    }
    catch (ParameterValidationError&) {
        ValidationFailed(aParameter);
    }
}

ArgumentBinary::~ArgumentBinary()
{
}

const Brx& ArgumentBinary::Value() const
{
    return iValue;
}

void ArgumentBinary::TransferTo(Brh& aBrh)
{
    iValue.TransferTo(aBrh);
}

void ArgumentBinary::ProcessInput(IInputArgumentProcessor& aProcessor)
{
    aProcessor.ProcessBinary(iValue);
}

void ArgumentBinary::ProcessOutput(IOutputProcessor& aProcessor, const Brx& aBuffer)
{
    aProcessor.ProcessBinary(aBuffer, iValue);
    iParameter.ValidateBinary(iValue);
}


// OpenHome::Net::Invocation

void OpenHome::Net::Invocation::SignalCompleted()
{
    iCompleted = !Error();
    // log completion before running the client callback as that may transfer the content of ArgumentStrings
    if (iCompleted) {
        FunctorAsync& asyncEndHandler = iCpStack.Env().InitParams()->AsyncEndHandler();
        if (asyncEndHandler) {
            asyncEndHandler(*this);
        }
    }
    if (iFunctor){
        try {
            iFunctor(*this);
        }
        catch(ProxyError&)
        {
            FunctorAsync& asyncErrorHandler = iCpStack.Env().InitParams()->AsyncErrorHandler();
            if (asyncErrorHandler) {
                asyncErrorHandler(*this);
            }
        }
    }
    iService->InvocationCompleted();
    Clear();
    iFree.Write(this);
}

TBool OpenHome::Net::Invocation::Error() const
{
    return (iError.Level() != Error::eNone);
}

TBool OpenHome::Net::Invocation::Error(Error::ELevel& aLevel, TUint& aCode, const TChar*& aDescription) const
{
    if (iError.Level() == Error::eNone) {
        return false;
    }
    aLevel = iError.Level();
    aCode = iError.Code();
    aDescription = iError.Description();
    return true;
}

TBool OpenHome::Net::Invocation::Interrupt() const
{
    return iService->Interrupt();
}

void OpenHome::Net::Invocation::Set(CpiService& aService, const OpenHome::Net::Action& aAction, CpiDevice& aDevice, FunctorAsync& aFunctor)
{
    iService = &aService;
    iAction = &aAction;
    iDevice = &aDevice;
    iFunctor = aFunctor;
    iSequenceNumber = iCpStack.Env().SequenceNumber();
}

void OpenHome::Net::Invocation::AddInput(Argument* aArgument)
{
    iInput.push_back(aArgument);
}

void OpenHome::Net::Invocation::AddOutput(Argument* aArgument)
{
    iOutput.push_back(aArgument);
}

void OpenHome::Net::Invocation::SetError(Error::ELevel aLevel, TUint aCode, const Brx& aDescription)
{
    /* If an error is set repeatedly, assume that the first setter will have had
       access to the most accurate description */
    if (iError.Level() == Error::eNone) {
        iError.Set(aLevel, aCode, aDescription);
    }
}

void OpenHome::Net::Invocation::SetInterruptHandler(IInterruptHandler* aHandler)
{
    AutoMutex a(iLock);
    iInterruptHandler = aHandler;
    if (iInterruptHandler != NULL && iService->Interrupt()) {
        iInterruptHandler->Interrupt();
    }
}

void OpenHome::Net::Invocation::Interrupt(const Service& aService)
{
    AutoMutex a(iLock);
    if (iService == &aService && iInterruptHandler != NULL) {
        SetError(Error::eAsync, Error::eCodeInterrupted, Error::kDescriptionAsyncInterrupted);
        iInterruptHandler->Interrupt();
    }
}

const OpenHome::Net::ServiceType& OpenHome::Net::Invocation::ServiceType() const
{
    ASSERT(iService != NULL);
    return iService->ServiceType();
}

const OpenHome::Net::Action& OpenHome::Net::Invocation::Action() const
{
    ASSERT(iAction != NULL);
    return *iAction;
}

CpiDevice& OpenHome::Net::Invocation::Device()
{
    return *iDevice;
}

void OpenHome::Net::Invocation::Output(IAsyncOutput& aConsole)
{
    AutoMutex a(iLock); /* using iLock doesn't prevent logging for multiple invocations overlapping
                           Using iCpStack.Env().Mutex() causes problems though as the call to
                           ServiceType().FullName() below also uses the Environment's mutex and we
                           can't easily use a different mutex there.
                           If we later want to prevent overlapped output, it'd be best to add a
                           shared logging mutex to Environment */
    Bws<Ascii::kMaxUintStringBytes+1> buf;
    (void)Ascii::AppendDec(buf, iSequenceNumber);
    buf.PtrZ();
    aConsole.Output("SequenceNumber", (const TChar*)buf.Ptr());
    aConsole.Output("Service", (const TChar*)ServiceType().FullName().Ptr());
    aConsole.Output("Action", (const TChar*)iAction->Name().Ptr());
    TUint count = (TUint)iInput.size();
    for (TUint i=0; i<count; i++) {
        OutputArgument(aConsole, "InputArg", *(iInput[i]));
    }
    if (Error()) {
        iError.Output(aConsole);
    }
    else if (iCompleted) {
        count = (TUint)iOutput.size();
        for (TUint i=0; i<count; i++) {
            OutputArgument(aConsole, "OutputArg", *(iOutput[i]));
        }
    }
}

void OpenHome::Net::Invocation::OutputArgument(IAsyncOutput& aConsole, const TChar* aKey, const Argument& aArgument)
{
    static const TUint kMaxStackBytes = 1024;
    TChar str[kMaxStackBytes];
    TChar* bigStr = NULL;
    ASSERT(aArgument.Parameter().Name().Bytes() < kMaxStackBytes-40); // add code to support mega-names if this ever fails
    OpenHome::Net::Parameter::EType paramType = aArgument.Parameter().Type();
    if (paramType == OpenHome::Net::Parameter::eTypeRelated) {
        paramType = ((const ParameterRelated&)aArgument.Parameter()).Related().Parameter().Type();
    }
    const Brx& paramName = aArgument.Parameter().Name();
    if (paramType == OpenHome::Net::Parameter::eTypeBinary) {
        (void)sprintf(str, "%s (binary - size %lu)", paramName.Ptr(), (unsigned long)((const ArgumentBinary&)aArgument).Value().Bytes());
    }
    else if (paramType == OpenHome::Net::Parameter::eTypeString) {
        char fmt[] = "%s (%s)";
        const ArgumentString& argString = (const ArgumentString&)aArgument;
        const TUint len = paramName.Bytes() + argString.Value().Bytes() + sizeof(*fmt);
        if (len > kMaxStackBytes) {
            bigStr = new TChar[len];
            (void)sprintf(bigStr, fmt, paramName.Ptr(), argString.Value().Ptr());
        }
        else {
            (void)sprintf(str, fmt, paramName.Ptr(), argString.Value().Ptr());
        }
    }
    else {
        switch (paramType)
        {
        case OpenHome::Net::Parameter::eTypeBool:
            (void)sprintf(str, "%s (%d)", paramName.Ptr(), ((const ArgumentBool&)aArgument).Value());
            break;
        case OpenHome::Net::Parameter::eTypeInt:
            (void)sprintf(str, "%s (%lu)", paramName.Ptr(), (unsigned long)((const ArgumentInt&)aArgument).Value());
            break;
        case OpenHome::Net::Parameter::eTypeUint:
            (void)sprintf(str, "%s (%lu)", paramName.Ptr(), (unsigned long)((const ArgumentUint&)aArgument).Value());
            break;
        default:
            ASSERTS();
        }
    }

    aConsole.Output(aKey, (bigStr==NULL? str : bigStr));
    delete bigStr;
}

const OpenHome::Net::Invocation::VectorArguments& OpenHome::Net::Invocation::InputArguments() const
{
    return iInput;
}

OpenHome::Net::Invocation::VectorArguments& OpenHome::Net::Invocation::OutputArguments()
{
    return iOutput;
}

void OpenHome::Net::Invocation::SetInvoker(IInvocable& aInvocable)
{
    iInvoker = &aInvocable;
}

IInvocable& OpenHome::Net::Invocation::Invoker()
{
    ASSERT(iInvoker != NULL);
    return *iInvoker;
}

TUint OpenHome::Net::Invocation::Type() const
{
    return eInvocation;
}

OpenHome::Net::Invocation::Invocation(CpStack& aCpStack, Fifo<OpenHome::Net::Invocation*>& aFree)
    : iCpStack(aCpStack)
    , iLock("MINV")
    , iFree(aFree)
    , iService(NULL)
    , iAction(NULL)
    , iDevice(NULL)
    , iCompleted(false)
    , iInterruptHandler(NULL)
{
}

OpenHome::Net::Invocation::~Invocation()
{
}

void OpenHome::Net::Invocation::Clear()
{
    LOG(kService, "Invocation::Clear for %p\n", this);
    iLock.Wait();
    iService  = NULL;
    iAction   = NULL;
    iDevice   = NULL;
    iFunctor = FunctorAsync();
    TUint i;
    for (i=0; i<iInput.size(); i++) {
        delete iInput[i];
    }
    iInput.clear();
    for (i=0; i<iOutput.size(); i++) {
        delete iOutput[i];
    }
    iOutput.clear();
    iError.Clear();
    iCompleted = false;
    iInterruptHandler = NULL;
    iLock.Signal();
}


// Invoker

Invoker::Invoker(const TChar* aName, Fifo<Invoker*>& aFree)
    : Thread(aName)
    , iFree(aFree)
    , iInvocation(NULL)
    , iLock("MVOK")
{
}

Invoker::~Invoker()
{
    Kill();
    Join();
}

void Invoker::Invoke(Invocation* aInvocation)
{
    iLock.Wait();
    iInvocation = aInvocation;
    iLock.Signal();
    Signal();
}

void Invoker::Interrupt(const Service& aService)
{
    AutoMutex a(iLock);
    if (iInvocation != NULL) {
        iInvocation->Interrupt(aService);
    }
}

void Invoker::SetError(Error::ELevel aLevel, TUint aCode, const Brx& aDescription, const TChar* aLogStr)
{
    iInvocation->SetError(aLevel, aCode, aDescription);
    // the above error details might be ignored if an earlier (presumed more detailed) error had been set
    Error::ELevel level = Error::eNone;
    TUint code = 0;
    const TChar* desc = NULL;
    (void)iInvocation->Error(level, code, desc);
    const Brx& actionName = iInvocation->Action().Name();
    const Brx& udn = iInvocation->Device().Udn();
    LOG3(kService, kError, kTrace, "Error - %s(%s, %d, %s) - from invocation %p, on action %.*s, from device %.*s\n",
        aLogStr, Error::LevelName(level), code, (desc==NULL? "" : desc), iInvocation, PBUF(actionName), PBUF(udn));
}

void Invoker::Run()
{
    for (;;) {
        Wait();
        try {
            const Brx& actionName = iInvocation->Action().Name();
            LOG(kService, "Invoker::Run (%s %p) action %.*s\n",
                          (const TChar*)Name().Ptr(), iInvocation, PBUF(actionName));
            iInvocation->Invoker().InvokeAction(*iInvocation);
        }
        catch (HttpError&) {
            SetError(Error::eHttp, Error::kCodeUnknown, Error::kDescriptionUnknown, "Http");
        }
        catch (NetworkError&) {
            SetError(Error::eSocket, Error::kCodeUnknown, Error::kDescriptionUnknown, "Network");
        }
        catch (NetworkTimeout&) {
            SetError(Error::eSocket, Error::eCodeTimeout, Error::kDescriptionSocketTimeout, "NetworkTimeout");
        }
        catch (ReaderError&) {
            SetError(Error::eSocket, Error::kCodeUnknown, Error::kDescriptionUnknown, "Reader");
        }
        catch (WriterError&) {
            SetError(Error::eSocket, Error::kCodeUnknown, Error::kDescriptionUnknown, "Writer");
        }
        catch (ParameterValidationError&) {
            SetError(Error::eService, Error::eCodeParameterInvalid, Error::kDescriptionParameterInvalid, "Parameter");
        }
        iLock.Wait();
        iInvocation->SignalCompleted();
        iInvocation = NULL;
        iLock.Signal();
        iFree.Write(this);
    }
}


// InvocationManager

InvocationManager::InvocationManager(CpStack& aCpStack)
    : Thread("InvocationManager")
    , iCpStack(aCpStack)
    , iLock("INVM")
    , iFreeInvocations(aCpStack.Env().InitParams()->NumInvocations())
    , iWaitingInvocations(aCpStack.Env().InitParams()->NumInvocations())
    , iFreeInvokers(aCpStack.Env().InitParams()->NumActionInvokerThreads())
{
    TUint i;
    iInvokers = (Invoker**)malloc(sizeof(*iInvokers) * iCpStack.Env().InitParams()->NumActionInvokerThreads());
    for (i=0; i<iCpStack.Env().InitParams()->NumActionInvokerThreads(); i++) {
        Bws<Thread::kMaxNameBytes+1> thName;
        thName.AppendPrintf("ActionInvoker %d", i);
        thName.PtrZ();
        iInvokers[i] = new Invoker((const TChar*)thName.Ptr(), iFreeInvokers);
        iFreeInvokers.Write(iInvokers[i]);
        iInvokers[i]->Start();
    }

    for (i=0; i<iCpStack.Env().InitParams()->NumInvocations(); i++) {
        iFreeInvocations.Write(new OpenHome::Net::Invocation(iCpStack, iFreeInvocations));
    }
    iActive = true;
    Start();
}

InvocationManager::~InvocationManager()
{
    iLock.Wait();
    iActive = false;
    iLock.Signal();

    iFreeInvokers.ReadInterrupt();
    Kill();
    Join();

    TUint i;
    for (i=0; i<iCpStack.Env().InitParams()->NumActionInvokerThreads(); i++) {
        delete iInvokers[i];
    }
    free(iInvokers);

    for (i=0; i<iCpStack.Env().InitParams()->NumInvocations(); i++) {
        OpenHome::Net::Invocation* invocation = iFreeInvocations.Read();
        delete invocation;
    }
}

OpenHome::Net::Invocation* InvocationManager::Invocation()
{
    AutoMutex a(iLock);
    if (!iActive) {
        return NULL;
    }
    return iFreeInvocations.Read();
}

void InvocationManager::Invoke(OpenHome::Net::Invocation* aInvocation)
{
    FunctorAsync& asyncBeginHandler = iCpStack.Env().InitParams()->AsyncBeginHandler();
    if (asyncBeginHandler) {
        asyncBeginHandler(*aInvocation);
    }
    iWaitingInvocations.Write(aInvocation);
    Signal();
}

void InvocationManager::Interrupt(const Service& aService)
{
    const TUint numThreads = iCpStack.Env().InitParams()->NumActionInvokerThreads();
    for (TUint i=0; i<numThreads; i++) {
        iInvokers[i]->Interrupt(aService);
    }
}

void InvocationManager::Run()
{
    for (;;) {
        Wait();
        OpenHome::Net::Invocation* invocation = NULL;
        try {
            invocation = iWaitingInvocations.Read();
            if (invocation->Interrupt()) {
                // the service associated with this invocation is being deleted
                // complete it with an error immediately and process the next waiting
                invocation->SetError(Error::eAsync,
                                     Error::eCodeInterrupted,
                                     Error::kDescriptionAsyncInterrupted);
                invocation->SignalCompleted();
            }
            else {
                Invoker* invoker = iFreeInvokers.Read();
                invoker->Invoke(invocation);
            }
        }
        catch (FifoReadError&) {
            if (invocation != NULL) {
                invocation->SetError(Error::eAsync,
                                     Error::eCodeShutdown,
                                     Error::kDescriptionAsyncShutdown);
                invocation->SignalCompleted();
            }
            break;
        }
    }
}
