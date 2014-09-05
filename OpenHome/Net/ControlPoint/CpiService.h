/**
 * Control Point representation and invocation of services
 *
 * This module is independent of the protocol being used.
 * It assumes that each service comprises a number of actions, each of which has 0..n
 * input and output parameters.  A particular invocation of an action creates an argument
 * per parameter.
 */

#ifndef HEADER_CPISERVICE
#define HEADER_CPISERVICE

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/CpiDevice.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Fifo.h>
#include <OpenHome/Private/Timer.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Net/Private/AsyncPrivate.h>
#include <OpenHome/Net/Private/Error.h>
#include <OpenHome/Net/Core/OhNet.h>
#include <OpenHome/Net/Private/CpiStack.h>

#include <vector>
#include <map>

namespace OpenHome {
namespace Net {

class Invocation;
class CpiSubscription;
class IInvocable;
class IEventProcessor;

/**
 * Service.  Specific to a single device.
 *
 * A service does not claim a reference to a device.  It is assumed that the owner
 * of the service will also own a device reference and will ensure that the service
 * is destroyed before the device reference is released.
 */
class DllExportClass CpiService : public OpenHome::Net::Service, private IStackObject
{
public:
    DllExport CpiService(const TChar* aDomain, const TChar* aName, TUint aVersion, CpiDevice& aDevice);

    /**
     * Destructor.  Will block until any pending invocations complete.
     * Any pending invocations are likely to complete with errors.
     */
    DllExport ~CpiService();
    
    // !!!! Refresh (refresh iSubscription)

    /**
     * Returns an invocation instance, setup for this service and the specific
     * action/observer/data.
     *
     * The stack uses a fixed pool of invocations.  If no invocation is available,
     * this function will block until one becomes available.
     *
     * The callback will run when the invocation completes.  The invocation will
     * be cleared when the callback returns so any output arguments of interest
     * may need to be copied/transferred.  Once Invoke() is called on the invocation
     * the callback is guaranteed to be called.
     */
    DllExport OpenHome::Net::Invocation* Invocation(const Action& aAction, FunctorAsync& aFunctor);

    /**
     * Subscribe to updates on properties for this Service
     * Callbacks for changes in a given Property are set on the Property.
     * [see AddProperty()]
     * Note that subscription is asynchronous.  There is no formal notification that
     * it has completed but clients can infer this by setting a callback using
     * CpProxy::SetPropertyChanged().  The next callback after a call to Subscribe()
     * implies that a subscription has completed
     * It is safe to delete a Service while a subscription is in progress.
     * Returns true if a subscription request was queued or false if it couldn't be queued.
     */
    TBool Subscribe(IEventProcessor& aEventProcessor);

    /**
     * Unsubscribe to updates on properties for this Service
     * Callbacks on properties will no longer run.
     * Note that unsubscription is asynchronous so it is possible that update
     * callbacks will continue to be received for a brief period after calling
     * this.
     * It is safe to delete a Service when an unsubscription is in progress.
     */
    void Unsubscribe();

    /**
     * Used by Invocation.  Not intended for use by other classes.
     */
    void InvocationCompleted();

    /**
     * Query whether invocations of actions on this service should be interrupted.
     *
     * If this returns true, invocations will probably complete quickly but with an error.
     */
    TBool Interrupt() const;

    /**
     * Return the device this service operates on.
     */
    CpiDevice& Device();

    /**
     * Query the version of the service.
     */
    TUint Version() const;
private:
    void Renew();
private: // from IStackObject
    void ListObjectDetails() const;
private:
    CpiDevice& iDevice;
    OpenHome::Mutex iLock;
    TUint iPendingInvocations;
    Semaphore iShutdownSignal;
    TBool iInterrupt;
    CpiSubscription* iSubscription;
};

/**
 * Used by a device to write input arguments in the form expected by the
 * protocol being used
 */
class IInputArgumentProcessor
{
public:
    virtual void ProcessString(const Brx& aVal) = 0;
    virtual void ProcessInt(TInt aVal) = 0;
    virtual void ProcessUint(TUint aVal) = 0;
    virtual void ProcessBool(TBool aVal) = 0;
    virtual void ProcessBinary(const Brx& aVal) = 0;
};

/**
 * (Action) Argument
 *
 * One Argument will be created per [in/out]put Parameter for the Action
 * Input parameters should construct arguments using the (Parameter, Val) constructor.
 * Output parameters should construct arguments using only the parameter and should
 * read the value when the invocation completes.
 */
class Argument : public INonCopyable
{
public:
    virtual ~Argument();
    virtual void ProcessInput(IInputArgumentProcessor& aProcessor) = 0;
    virtual void ProcessOutput(IOutputProcessor& aProcessor, const Brx& aBuffer) = 0;
    const OpenHome::Net::Parameter& Parameter() const;
protected:
    Argument(const OpenHome::Net::Parameter& aParameter);
    void ValidationFailed(const OpenHome::Net::Parameter& aParameter);
protected:
    const OpenHome::Net::Parameter& iParameter;
};

/**
 * String argument.  Output buffers will be nul terminated.
 */
class DllExportClass ArgumentString : public Argument
{
public:
    DllExport ArgumentString(const OpenHome::Net::Parameter& aParameter); // for output params
    DllExport ArgumentString(const OpenHome::Net::Parameter& aParameter, const Brx& aValue); // for input params
    DllExport ~ArgumentString();
    DllExport const Brx& Value() const;
    DllExport void TransferTo(Brh& aBrh);
    void ProcessInput(IInputArgumentProcessor& aProcessor);
    void ProcessOutput(IOutputProcessor& aProcessor, const Brx& aBuffer);
private:
    Brhz iValue;
};

/**
 * Integer argument
 */
class DllExportClass ArgumentInt : public Argument
{
public:
    DllExport ArgumentInt(const OpenHome::Net::Parameter& aParameter);
    DllExport ArgumentInt(const OpenHome::Net::Parameter& aParameter, TInt aValue);
    DllExport ~ArgumentInt();
    DllExport TInt Value() const;
    void ProcessInput(IInputArgumentProcessor& aProcessor);
    void ProcessOutput(IOutputProcessor& aProcessor, const Brx& aBuffer);
private:
    TInt iValue;
};

/**
 * Unsigned integer argument
 */
class DllExportClass ArgumentUint : public Argument
{
public:
    DllExport ArgumentUint(const OpenHome::Net::Parameter& aParameter);
    DllExport ArgumentUint(const OpenHome::Net::Parameter& aParameter, TUint aValue);
    DllExport ~ArgumentUint();
    DllExport TUint Value() const;
    void ProcessInput(IInputArgumentProcessor& aProcessor);
    void ProcessOutput(IOutputProcessor& aProcessor, const Brx& aBuffer);
private:
    TUint iValue;
};

/**
 * Boolean arguments
 */
class DllExportClass ArgumentBool : public Argument
{
public:
    DllExport ArgumentBool(const OpenHome::Net::Parameter& aParameter);
    DllExport ArgumentBool(const OpenHome::Net::Parameter& aParameter, TBool aValue);
    DllExport ~ArgumentBool();
    DllExport TBool Value() const;
    void ProcessInput(IInputArgumentProcessor& aProcessor);
    void ProcessOutput(IOutputProcessor& aProcessor, const Brx& aBuffer);
private:
    TBool iValue;
};

/**
 * Binary argument.  Similar to ArgumentString but output will not be nul terminated
 */
class DllExportClass ArgumentBinary : public Argument
{
public:
    DllExport ArgumentBinary(const OpenHome::Net::Parameter& aParameter);
    DllExport ArgumentBinary(const OpenHome::Net::Parameter& aParameter, const Brx& aValue);
    DllExport ~ArgumentBinary();
    DllExport const Brx& Value() const;
    DllExport void TransferTo(Brh& aBrh);
    void ProcessInput(IInputArgumentProcessor& aProcessor);
    void ProcessOutput(IOutputProcessor& aProcessor, const Brx& aBuffer);
private:
    Brh iValue;
};

/**
 * Callback used to interrupt an active operation
 * CpDevices should implement this interface.
 */
class IInterruptHandler
{
public:
    /**
     * Signal that the operation should be interrupted.
     * This function does not need to wait until the operation stops.
     */
    virtual void Interrupt() = 0;
};

/**
 * Used to invoke an Action with particular Arguments on a Service
 *
 * Control point side clients must not create new Invocation instances or delete instances
 * returned by Service::GetInvocation() or passed to their invocation completed callback.
 *
 * Normal use will be
 * - create (possibly allocating) any data required in the callback
 * - use Service::GetInvocation() to retrieve a pointer from an existing pool
 *      the invocation will have Service and Action name set automatically
 *      the invocation will have the client-specified callback and data set automatically
 * - create one Argument-derived class for each InputParameter on the action
 *      these arguments must have their values set (i.e. use the c'tor taking two params)
 * - call AddInput() for each of these arguments
 * - create one Argument-derived class for each OutputParameter on the action
 *      these arguments should not have their values set (i.e. use the c'tor taking one param)
 * - call AddOutput() for each of these arguments
 * - call IInvocable::QueueInvocation()
 * ....
 * - The invocation completed callback will run.  Invocation::Error() will be
 *      true if the invocation failed.  If no error occurred, each member of
 *      OutputArguments() will be set.
 */
class DllExportClass Invocation : public Async
{
public:
    /**
     * Intended for internal use only
     */
    void SignalCompleted();

    /**
     * Returns true if the invocation failed; false if it successed
     *
     * The Completed() callback will still be called if an invocation fails.  It should
     * not attempt to access OutputArguments() if it failed but must free any user data.
     */
    DllExport TBool Error() const;

    /**
     * Returns true if the invocation failed; false if it successed
     *
     * The Completed() callback will still be called if an invocation fails.  It should
     * not attempt to access OutputArguments() if it failed but must free any user data.
     *
     * All args are output only and will only be set if the function returns true.
     */
    DllExport TBool Error(Error::ELevel& aLevel, TUint& aCode, const TChar*& aDescription) const;

    /**
     * Intended for internal use only
     */
    TBool Interrupt() const;

    /**
     * Intended for internal use only
     */
    void Set(CpiService& aService, const OpenHome::Net::Action& aAction, CpiDevice& aDevice, FunctorAsync& aFunctor);

    /**
     * Add an input argument, passing ownership of aArgument
     *
     * aArgument should have a value set (i.e. used the c'tor taking two params)
     */
    DllExport void AddInput(Argument* aArgument);

    /**
     * Add an output argument, passing ownership of aArgument
     *
     * aArgument should not have a value set (i.e. used the c'tor taking one param)
     */
    DllExport void AddOutput(Argument* aArgument);

    /**
     * Set error details on this invocation.
     *
     * The Completed() callback will assume that the invocation failed.
     * Intended for use by CpiDevice-derived classes.
     */
    void SetError(Error::ELevel aLevel, TUint aCode, const Brx& aDescription);

    /**
     * Set the handler for interrupting this invocation
     */
    void SetInterruptHandler(IInterruptHandler* aHandler);

    /**
     * Signal that this invocation should be interrupted if its Action is a member of aService
     * Intended for internal use only
     */
    void Interrupt(const Service& aService);

    const OpenHome::Net::ServiceType& ServiceType() const;
    DllExport const OpenHome::Net::Action& Action() const;
    CpiDevice& Device();

    /**
     * Log details of this invocation + error status
     */
    void Output(IAsyncOutput& aConsole);

    typedef std::vector<Argument*> VectorArguments;
    /**
     * Return a vector of input arguments (one per input parameter for the Action)
     *
     * This can be called by any client but is assumed to be of interest to devices only
     */
    const VectorArguments& InputArguments() const;

    /**
     * Return a vector of output arguments (one per output parameter for the Action)
     *
     * This is assumed to be of interest to the device and the Completed() callback
     */
    DllExport VectorArguments& OutputArguments();

    void SetInvoker(IInvocable& aInvocable);
    IInvocable& Invoker();
private:
    Invocation(CpStack& aCpStack, Fifo<OpenHome::Net::Invocation*>& aFree);
    Invocation& operator=(const Invocation& aInvocation);
    ~Invocation();
    void Clear();
    static void OutputArgument(IAsyncOutput& aConsole, const TChar* aKey, const Argument& aArgument);
    virtual TUint Type() const;
private:
    CpStack& iCpStack;
    OpenHome::Mutex iLock;
    Fifo<OpenHome::Net::Invocation*>& iFree;
    CpiService* iService;
    const OpenHome::Net::Action* iAction;
    CpiDevice* iDevice;
    FunctorAsync iFunctor;
    TUint iSequenceNumber;
    OpenHome::Net::Error iError;
    TBool iCompleted;
    VectorArguments iInput;
    VectorArguments iOutput;
    IInterruptHandler* iInterruptHandler;
    IInvocable* iInvoker;
private:
    friend class InvocationManager;
};

/**
 * Dedicated thread which processes action invocations
 *
 * Intended for internal use only
 */
class Invoker : public Thread
{
public:
    Invoker(const TChar* aName, Fifo<Invoker*>& aFree);
    ~Invoker();

    /**
     * Signal that aInvocation should be invoked
     */
    void Invoke(Invocation* aInvocation);
    
    /**
     * Interrupt any current invocation if its action is a member of aService
     */
    void Interrupt(const Service& aService);
private:
    void SetError(Error::ELevel aLevel, TUint aCode, const Brx& aDescription, const TChar* aLogStr);
    void Run();
private:
    Fifo<Invoker*>& iFree;
    Invocation* iInvocation;
    OpenHome::Mutex iLock;
};

/**
 * Singleton which manages the pools of Invocation and Invoker instances
 */
class InvocationManager : public Thread
{
    friend class CpiService;
public:
    InvocationManager(CpStack& aCpStack);
    ~InvocationManager();
    void Invoke(OpenHome::Net::Invocation* aInvocation);
    void Interrupt(const Service& aService);
private:
    OpenHome::Net::Invocation* Invocation();
    void Run();
private:
    CpStack& iCpStack;
    OpenHome::Mutex iLock;
    Fifo<OpenHome::Net::Invocation*> iFreeInvocations;
    Fifo<OpenHome::Net::Invocation*> iWaitingInvocations;
    Fifo<Invoker*> iFreeInvokers;
    Invoker** iInvokers;
    TBool iActive;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_CPISERVICE
