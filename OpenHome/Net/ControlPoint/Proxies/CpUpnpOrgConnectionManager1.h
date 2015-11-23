#ifndef HEADER_UPNPORGCONNECTIONMANAGER1
#define HEADER_UPNPORGCONNECTIONMANAGER1

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Net/Core/FunctorAsync.h>
#include <OpenHome/Net/Core/CpProxy.h>

namespace OpenHome {
namespace Net {

class CpDevice;
class Action;
class PropertyBinary;
class PropertyBool;
class PropertyInt;
class PropertyString;
class PropertyUint;

class ICpProxyUpnpOrgConnectionManager1
{
public:
    virtual void SyncGetProtocolInfo(Brh& aSource, Brh& aSink) = 0;
    virtual void BeginGetProtocolInfo(FunctorAsync& aFunctor) = 0;
    virtual void EndGetProtocolInfo(IAsync& aAsync, Brh& aSource, Brh& aSink) = 0;
    virtual void SyncPrepareForConnection(const Brx& aRemoteProtocolInfo, const Brx& aPeerConnectionManager, TInt aPeerConnectionID, const Brx& aDirection, TInt& aConnectionID, TInt& aAVTransportID, TInt& aRcsID) = 0;
    virtual void BeginPrepareForConnection(const Brx& aRemoteProtocolInfo, const Brx& aPeerConnectionManager, TInt aPeerConnectionID, const Brx& aDirection, FunctorAsync& aFunctor) = 0;
    virtual void EndPrepareForConnection(IAsync& aAsync, TInt& aConnectionID, TInt& aAVTransportID, TInt& aRcsID) = 0;
    virtual void SyncConnectionComplete(TInt aConnectionID) = 0;
    virtual void BeginConnectionComplete(TInt aConnectionID, FunctorAsync& aFunctor) = 0;
    virtual void EndConnectionComplete(IAsync& aAsync) = 0;
    virtual void SyncGetCurrentConnectionIDs(Brh& aConnectionIDs) = 0;
    virtual void BeginGetCurrentConnectionIDs(FunctorAsync& aFunctor) = 0;
    virtual void EndGetCurrentConnectionIDs(IAsync& aAsync, Brh& aConnectionIDs) = 0;
    virtual void SyncGetCurrentConnectionInfo(TInt aConnectionID, TInt& aRcsID, TInt& aAVTransportID, Brh& aProtocolInfo, Brh& aPeerConnectionManager, TInt& aPeerConnectionID, Brh& aDirection, Brh& aStatus) = 0;
    virtual void BeginGetCurrentConnectionInfo(TInt aConnectionID, FunctorAsync& aFunctor) = 0;
    virtual void EndGetCurrentConnectionInfo(IAsync& aAsync, TInt& aRcsID, TInt& aAVTransportID, Brh& aProtocolInfo, Brh& aPeerConnectionManager, TInt& aPeerConnectionID, Brh& aDirection, Brh& aStatus) = 0;
    virtual void SetPropertySourceProtocolInfoChanged(Functor& aSourceProtocolInfoChanged) = 0;
    virtual void PropertySourceProtocolInfo(Brhz& aSourceProtocolInfo) const = 0;
    virtual void SetPropertySinkProtocolInfoChanged(Functor& aSinkProtocolInfoChanged) = 0;
    virtual void PropertySinkProtocolInfo(Brhz& aSinkProtocolInfo) const = 0;
    virtual void SetPropertyCurrentConnectionIDsChanged(Functor& aCurrentConnectionIDsChanged) = 0;
    virtual void PropertyCurrentConnectionIDs(Brhz& aCurrentConnectionIDs) const = 0;
};

/**
 * Proxy for upnp.org:ConnectionManager:1
 * @ingroup Proxies
 */
class CpProxyUpnpOrgConnectionManager1 : public CpProxy, public ICpProxyUpnpOrgConnectionManager1
{
public:
    /**
     * Constructor.
     *
     * Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable
     * and reporting of their changes.
     *
     * @param[in]  aDevice   The device to use
     */
    CpProxyUpnpOrgConnectionManager1(CpDevice& aDevice);
    /**
     * Destructor.
     * If any asynchronous method is in progress, this will block until they complete.
     * [Note that any methods still in progress are likely to complete with an error.]
     * Clients who have called Subscribe() do not need to call Unsubscribe() before
     * calling delete.  An unsubscribe will be triggered automatically when required.
     */
    ~CpProxyUpnpOrgConnectionManager1();

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aSource
     * @param[out] aSink
     */
    void SyncGetProtocolInfo(Brh& aSource, Brh& aSink);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndGetProtocolInfo().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginGetProtocolInfo(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aSource
     * @param[out] aSink
     */
    void EndGetProtocolInfo(IAsync& aAsync, Brh& aSource, Brh& aSink);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aRemoteProtocolInfo
     * @param[in]  aPeerConnectionManager
     * @param[in]  aPeerConnectionID
     * @param[in]  aDirection
     * @param[out] aConnectionID
     * @param[out] aAVTransportID
     * @param[out] aRcsID
     */
    void SyncPrepareForConnection(const Brx& aRemoteProtocolInfo, const Brx& aPeerConnectionManager, TInt aPeerConnectionID, const Brx& aDirection, TInt& aConnectionID, TInt& aAVTransportID, TInt& aRcsID);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndPrepareForConnection().
     *
     * @param[in] aRemoteProtocolInfo
     * @param[in] aPeerConnectionManager
     * @param[in] aPeerConnectionID
     * @param[in] aDirection
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginPrepareForConnection(const Brx& aRemoteProtocolInfo, const Brx& aPeerConnectionManager, TInt aPeerConnectionID, const Brx& aDirection, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aConnectionID
     * @param[out] aAVTransportID
     * @param[out] aRcsID
     */
    void EndPrepareForConnection(IAsync& aAsync, TInt& aConnectionID, TInt& aAVTransportID, TInt& aRcsID);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aConnectionID
     */
    void SyncConnectionComplete(TInt aConnectionID);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndConnectionComplete().
     *
     * @param[in] aConnectionID
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginConnectionComplete(TInt aConnectionID, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndConnectionComplete(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aConnectionIDs
     */
    void SyncGetCurrentConnectionIDs(Brh& aConnectionIDs);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndGetCurrentConnectionIDs().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginGetCurrentConnectionIDs(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aConnectionIDs
     */
    void EndGetCurrentConnectionIDs(IAsync& aAsync, Brh& aConnectionIDs);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aConnectionID
     * @param[out] aRcsID
     * @param[out] aAVTransportID
     * @param[out] aProtocolInfo
     * @param[out] aPeerConnectionManager
     * @param[out] aPeerConnectionID
     * @param[out] aDirection
     * @param[out] aStatus
     */
    void SyncGetCurrentConnectionInfo(TInt aConnectionID, TInt& aRcsID, TInt& aAVTransportID, Brh& aProtocolInfo, Brh& aPeerConnectionManager, TInt& aPeerConnectionID, Brh& aDirection, Brh& aStatus);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndGetCurrentConnectionInfo().
     *
     * @param[in] aConnectionID
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginGetCurrentConnectionInfo(TInt aConnectionID, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aRcsID
     * @param[out] aAVTransportID
     * @param[out] aProtocolInfo
     * @param[out] aPeerConnectionManager
     * @param[out] aPeerConnectionID
     * @param[out] aDirection
     * @param[out] aStatus
     */
    void EndGetCurrentConnectionInfo(IAsync& aAsync, TInt& aRcsID, TInt& aAVTransportID, Brh& aProtocolInfo, Brh& aPeerConnectionManager, TInt& aPeerConnectionID, Brh& aDirection, Brh& aStatus);

    /**
     * Set a callback to be run when the SourceProtocolInfo state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyUpnpOrgConnectionManager1 instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertySourceProtocolInfoChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the SinkProtocolInfo state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyUpnpOrgConnectionManager1 instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertySinkProtocolInfoChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the CurrentConnectionIDs state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyUpnpOrgConnectionManager1 instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyCurrentConnectionIDsChanged(Functor& aFunctor);

    /**
     * Query the value of the SourceProtocolInfo property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
     * to Unsubscribe().
     *
     * @param[out] aSourceProtocolInfo
     */
    void PropertySourceProtocolInfo(Brhz& aSourceProtocolInfo) const;
    /**
     * Query the value of the SinkProtocolInfo property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
     * to Unsubscribe().
     *
     * @param[out] aSinkProtocolInfo
     */
    void PropertySinkProtocolInfo(Brhz& aSinkProtocolInfo) const;
    /**
     * Query the value of the CurrentConnectionIDs property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
     * to Unsubscribe().
     *
     * @param[out] aCurrentConnectionIDs
     */
    void PropertyCurrentConnectionIDs(Brhz& aCurrentConnectionIDs) const;
private:
    void SourceProtocolInfoPropertyChanged();
    void SinkProtocolInfoPropertyChanged();
    void CurrentConnectionIDsPropertyChanged();
private:
    Action* iActionGetProtocolInfo;
    Action* iActionPrepareForConnection;
    Action* iActionConnectionComplete;
    Action* iActionGetCurrentConnectionIDs;
    Action* iActionGetCurrentConnectionInfo;
    PropertyString* iSourceProtocolInfo;
    PropertyString* iSinkProtocolInfo;
    PropertyString* iCurrentConnectionIDs;
    Functor iSourceProtocolInfoChanged;
    Functor iSinkProtocolInfoChanged;
    Functor iCurrentConnectionIDsChanged;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_UPNPORGCONNECTIONMANAGER1

