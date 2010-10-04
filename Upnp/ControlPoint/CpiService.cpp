#include <CpiService.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <CpiDevice.h>
#include <Stack.h>
#include <CpiStack.h>
#include <Debug.h>
#include <CpProxy.h>
#include <Error.h>
#include <CpiSubscription.h>

#include <stdio.h>
#include <stdlib.h>

using namespace Zapp;

// CpiService

CpiService::CpiService(const TChar* aDomain, const TChar* aName, TUint aVersion, CpiDevice& aDevice)
    : Service(aDomain, aName, aVersion)
    , iDevice(aDevice)
    , iLock("SRVM")
    , iPendingInvocations(0)
    , iShutdownSignal("SRVS", 0)
    , iInterrupt(false)
    , iSubscription(NULL)
{
	iDevice.AddRef();
}

CpiService::~CpiService()
{
    iInterrupt = true;
    try {
        InvocationManager::Interrupt(*this);
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
	iDevice.RemoveRef();
	PropertyMap::iterator it = iProperties.begin();
    while (it != iProperties.end()) {
        delete it->second;
        it->second = NULL;
        it++;
    }
}

void CpiService::AddProperty(Property* aProperty)
{
    ASSERT(aProperty != NULL);
    Brn name(aProperty->Parameter().Name());
    iProperties.insert(std::pair<Brn,Property*>(name, aProperty));
}

void CpiService::SetPropertyChanged(Functor& aFunctor)
{
    iPropertyChanged = aFunctor;
}

Invocation* CpiService::Invocation(const Action& aAction, FunctorAsync& aFunctor)
{
    iLock.Wait();
    iPendingInvocations++;
    iLock.Signal();
    Zapp::Invocation* invocation = InvocationManager::Invocation();
    invocation->Set(*this, aAction, iDevice, aFunctor);
    return invocation;
}

void CpiService::Subscribe()
{
    ASSERT(iSubscription == NULL);
    iSubscription = SubscriptionManager::NewSubscription(iDevice, iServiceType, iProperties, iPropertyChanged);
}

void CpiService::Unsubscribe()
{
    if (iSubscription != NULL) {
        iSubscription->Unsubscribe();
        iSubscription->StopUpdates();
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


// Argument

const Zapp::Parameter& Argument::Parameter() const
{
    return iParameter;
}

Argument::Argument(const Zapp::Parameter& aParameter)
    : iParameter(aParameter)
{
}

Argument::~Argument()
{
}

void Argument::ValidationFailed(const Zapp::Parameter& aParameter)
{
    Log::Print("Validation of Parameter ");
    Log::Print(aParameter.Name());
    Log::Print(" failed, asserting\n");
    ASSERTS();
}


// ArgumentString

ArgumentString::ArgumentString(const Zapp::Parameter& aParameter)
    : Argument(aParameter)
{
}

ArgumentString::ArgumentString(const Zapp::Parameter& aParameter, const Brx& aValue)
    : Argument(aParameter)
{
    try {
        aParameter.ValidateString(aValue);
        iValue.Set(aValue);
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

ArgumentInt::ArgumentInt(const Zapp::Parameter& aParameter)
    : Argument(aParameter)
    , iValue(0)
{
}

ArgumentInt::ArgumentInt(const Zapp::Parameter& aParameter, TInt aValue)
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

ArgumentUint::ArgumentUint(const Zapp::Parameter& aParameter)
    : Argument(aParameter)
    , iValue(0)
{
}

ArgumentUint::ArgumentUint(const Zapp::Parameter& aParameter, TUint aValue)
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

ArgumentBool::ArgumentBool(const Zapp::Parameter& aParameter)
    : Argument(aParameter)
    , iValue(false)
{
}

ArgumentBool::ArgumentBool(const Zapp::Parameter& aParameter, TBool aValue)
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

ArgumentBinary::ArgumentBinary(const Zapp::Parameter& aParameter)
    : Argument(aParameter)
{
}

ArgumentBinary::ArgumentBinary(const Zapp::Parameter& aParameter, const Brx& aValue)
    : Argument(aParameter)
{
    try {
        aParameter.ValidateBinary(aValue);
        iValue.Set(aValue);
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


// Zapp::Invocation

void Zapp::Invocation::Invoke()
{
    FunctorAsync& asyncBeginHandler = Stack::InitParams().AsyncBeginHandler();
    if (asyncBeginHandler) {
        asyncBeginHandler(*this);
    }
    InvocationManager::Invoke(this);
}

void Zapp::Invocation::SignalCompleted()
{
    iCompleted = !Error();
    // log completion before running the client callback as that may transfer the content of ArgumentStrings
    if (iCompleted) {
        FunctorAsync& asyncEndHandler = Stack::InitParams().AsyncEndHandler();
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
            FunctorAsync& asyncErrorHandler = Stack::InitParams().AsyncErrorHandler();
            if (asyncErrorHandler) {
                asyncErrorHandler(*this);
            }
        }
    }
    iService->InvocationCompleted();
    Clear();
    iFree.Write(this);
}

TBool Zapp::Invocation::Error() const
{
    return (iError.Level() != Error::eNone);
}

TBool Zapp::Invocation::Interrupt() const
{
    return iService->Interrupt();
}

void Zapp::Invocation::Set(CpiService& aService, const Zapp::Action& aAction, CpiDevice& aDevice, FunctorAsync& aFunctor)
{
    iService = &aService;
    iAction = &aAction;
    iDevice = &aDevice;
    iFunctor = aFunctor;
    iSequenceNumber = Stack::SequenceNumber();
}

void Zapp::Invocation::AddInput(Argument* aArgument)
{
    iInput.push_back(aArgument);
}

void Zapp::Invocation::AddOutput(Argument* aArgument)
{
    iOutput.push_back(aArgument);
}

void Zapp::Invocation::SetError(Error::ELevel aLevel, TUint aCode, const Brx& aDescription)
{
    /* If an error is set repeatedly, assume that the first setter will have had
       access to the most accurate description */
    if (iError.Level() == Error::eNone) {
        iError.Set(aLevel, aCode, aDescription);
    }
}

void Zapp::Invocation::SetInterruptHandler(IInterruptHandler* aHandler)
{
    AutoMutex a(iLock);
    iInterruptHandler = aHandler;
    if (iInterruptHandler != NULL && iService->Interrupt()) {
        iInterruptHandler->Interrupt();
    }
}

void Zapp::Invocation::Interrupt(const Service& aService)
{
    AutoMutex a(iLock);
    if (iService == &aService && iInterruptHandler != NULL) {
        SetError(Error::eAsync, Error::eCodeInterrupted, Error::kDescriptionAsyncInterrupted);
        iInterruptHandler->Interrupt();
    }
}

const Zapp::ServiceType& Zapp::Invocation::ServiceType() const
{
    ASSERT(iService != NULL);
    return iService->ServiceType();
}

const Zapp::Action& Zapp::Invocation::Action() const
{
    ASSERT(iAction != NULL);
    return *iAction;
}

CpiDevice& Zapp::Invocation::Device()
{
    return *iDevice;
}

void Zapp::Invocation::Output(IAsyncOutput& aConsole)
{
    AutoMutex a(iLock); /* using iLock doesn't prevent logging for multiple invocations overlapping
						   Using Stack::Mutex() causes problems though as the call to
						   ServiceType().FullName() below also uses the Stack's mutex and we can't
						   easily use a different mutex there.
						   If we later want to prevent overlapped output, it'd be best to add a
						   shared logging mutex to Stack */
    Bws<Ascii::kMaxUintStringBytes+1> buf;
    (void)Ascii::AppendDec(buf, iSequenceNumber);
    buf.PtrZ();
    aConsole.Output("SequenceNumber", (const TChar*)buf.Ptr());
    aConsole.Output("Service", (const TChar*)ServiceType().FullName().Ptr());
    aConsole.Output("Action", (const TChar*)iAction->Name().Ptr());
    TUint count = iInput.size();
    for (TUint i=0; i<count; i++) {
        OutputArgument(aConsole, "InputArg", *(iInput[i]));
    }
    if (Error()) {
        iError.Output(aConsole);
    }
    else if (iCompleted) {
        count = iOutput.size();
        for (TUint i=0; i<count; i++) {
            OutputArgument(aConsole, "OutputArg", *(iOutput[i]));
        }
    }
}

void Zapp::Invocation::OutputArgument(IAsyncOutput& aConsole, const TChar* aKey, const Argument& aArgument)
{
    static const TUint kMaxStackBytes = 1024;
    TChar str[kMaxStackBytes];
    TChar* bigStr = NULL;
    ASSERT(aArgument.Parameter().Name().Bytes() < kMaxStackBytes-40); // add code to support mega-names if this ever fails
    Zapp::Parameter::EType paramType = aArgument.Parameter().Type();
	if (paramType == Zapp::Parameter::eTypeRelated) {
		paramType = ((const ParameterRelated&)aArgument.Parameter()).Related().Parameter().Type();
	}
    const Brx& paramName = aArgument.Parameter().Name();
    if (paramType == Zapp::Parameter::eTypeBinary) {
        (void)sprintf(str, "%s (binary - size %u)", paramName.Ptr(), ((const ArgumentBinary&)aArgument).Value().Bytes());
    }
    else if (paramType == Zapp::Parameter::eTypeString) {
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
        case Zapp::Parameter::eTypeBool:
            (void)sprintf(str, "%s (%d)", paramName.Ptr(), ((const ArgumentBool&)aArgument).Value());
            break;
        case Zapp::Parameter::eTypeInt:
            (void)sprintf(str, "%s (%d)", paramName.Ptr(), ((const ArgumentInt&)aArgument).Value());
            break;
        case Zapp::Parameter::eTypeUint:
            (void)sprintf(str, "%s (%u)", paramName.Ptr(), ((const ArgumentUint&)aArgument).Value());
            break;
        default:
            ASSERTS();
        }
    }

    aConsole.Output(aKey, (bigStr==NULL? str : bigStr));
    delete bigStr;
}

const Zapp::Invocation::VectorArguments& Zapp::Invocation::InputArguments() const
{
    return iInput;
}

Zapp::Invocation::VectorArguments& Zapp::Invocation::OutputArguments()
{
    return iOutput;
}

TUint Zapp::Invocation::Type() const
{
    return eInvocation;
}

Zapp::Invocation::Invocation(Fifo<Zapp::Invocation*>& aFree)
    : iLock("MINV")
    , iFree(aFree)
    , iService(NULL)
    , iAction(NULL)
    , iDevice(NULL)
    , iCompleted(false)
    , iInterruptHandler(NULL)
{
}

Zapp::Invocation::~Invocation()
{
}

void Zapp::Invocation::Clear()
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

#ifdef DEFINE_TRACE
void Invoker::LogError(const TChar* aErr)
#else
void Invoker::LogError(const TChar* /*aErr*/)
#endif
{
    LOG2(kService, kError, "Error - %s - from invocation %p, ", aErr, iInvocation);
    LOG2(kService, kError, iInvocation->Action().Name());
    LOG2(kService, kError, "\n");
}

void Invoker::Run()
{
    for (;;) {
        Wait();
        try {
            LOG(kService, "Invoker::Run (%s %p) action ",
                          (const TChar*)Name().Ptr(), iInvocation);
            LOG(kService, iInvocation->Action().Name());
            LOG(kService, "\n");
            iInvocation->Device().Invoke(*iInvocation);
        }
        catch (HttpError&) {
            iInvocation->SetError(Error::eHttp, Error::kCodeUnknown,
                                  Error::kDescriptionUnknown);
            LogError("Http");
        }
        catch (NetworkError&) {
            iInvocation->SetError(Error::eSocket, Error::kCodeUnknown,
                                  Error::kDescriptionUnknown);
            LogError("Network");
        }
        catch (NetworkTimeout&) {
            iInvocation->SetError(Error::eSocket, Error::eCodeTimeout,
                                  Error::kDescriptionSocketTimeout);
            LogError("NetworkTimeout");
        }
        catch (ReaderError&) {
            iInvocation->SetError(Error::eSocket, Error::kCodeUnknown,
                                  Error::kDescriptionUnknown);
            LogError("Reader");
        }
        catch (WriterError&) {
            iInvocation->SetError(Error::eSocket, Error::kCodeUnknown,
                                  Error::kDescriptionUnknown);
            LogError("Writer");
        }
        catch (ParameterValidationError&) {
            iInvocation->SetError(Error::eService, Error::eCodeParameterInvalid,
                                  Error::kDescriptionParameterInvalid);
            LogError("Parameter");
        }
        iLock.Wait();
        iInvocation->SignalCompleted();
        iInvocation = NULL;
        iLock.Signal();
        iFree.Write(this);
    }
}


// InvocationManager

InvocationManager::InvocationManager()
    : Thread("INVM")
    , iLock("INVM")
    , iOutputLock("OUTM")
    , iFreeInvocations(Stack::InitParams().NumInvocations())
    , iWaitingInvocations(Stack::InitParams().NumInvocations())
    , iFreeInvokers(Stack::InitParams().NumActionInvokerThreads())
{
    TUint i;
    TChar thName[5] = "INV ";
#ifndef _WIN32
    ASSERT(Stack::InitParams().NumActionInvokerThreads() <= 9);
#endif
    iInvokers = (Invoker**)malloc(sizeof(*iInvokers) * Stack::InitParams().NumActionInvokerThreads());
    for (i=0; i<Stack::InitParams().NumActionInvokerThreads(); i++) {
        thName[3] = (TChar)('0'+i);
        iInvokers[i] = new Invoker(&thName[0], iFreeInvokers);
        iFreeInvokers.Write(iInvokers[i]);
        iInvokers[i]->Start();
    }

    for (i=0; i<Stack::InitParams().NumInvocations(); i++) {
        iFreeInvocations.Write(new Zapp::Invocation(iFreeInvocations));
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
    for (i=0; i<Stack::InitParams().NumActionInvokerThreads(); i++) {
        delete iInvokers[i];
    }
    free(iInvokers);

    for (i=0; i<Stack::InitParams().NumInvocations(); i++) {
        Zapp::Invocation* invocation = iFreeInvocations.Read();
        delete invocation;
    }
}

Zapp::Invocation* InvocationManager::Invocation()
{
    InvocationManager& self = Self();
    AutoMutex a(self.iLock);
    if (!self.iActive) {
        return NULL;
    }
    Zapp::Invocation* invocation = self.iFreeInvocations.Read();
    return invocation;
}

void InvocationManager::Invoke(Zapp::Invocation* aInvocation)
{
    InvocationManager& self = Self();
    self.iWaitingInvocations.Write(aInvocation);
    self.Signal();
}

void InvocationManager::Interrupt(const Service& aService)
{
    InvocationManager& self = Self();
    for (TUint i=0; i<Stack::InitParams().NumActionInvokerThreads(); i++) {
        self.iInvokers[i]->Interrupt(aService);
    }
}

InvocationManager& InvocationManager::Self()
{
    return CpiStack::InvocationManager();
}

void InvocationManager::Run()
{
    for (;;) {
        Wait();
        Zapp::Invocation* invocation = NULL;
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
