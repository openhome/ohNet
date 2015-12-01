#ifndef HEADER_UPNPORGCONNECTIONMANAGER1CPP
#define HEADER_UPNPORGCONNECTIONMANAGER1CPP

#include <OpenHome/Types.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Net/Core/FunctorAsync.h>
#include <OpenHome/Net/Core/CpProxy.h>

#include <string>

namespace OpenHome {
namespace Net {

class CpDeviceCpp;
class Action;
class PropertyBinary;
class PropertyBool;
class PropertyInt;
class PropertyString;
class PropertyUint;
class CpProxy;
class ICpProxyUpnpOrgConnectionManager1Cpp : public ICpProxy
{
public:
    virtual void SyncGetProtocolInfo(std::string& aSource, std::string& aSink) = 0;
    virtual void BeginGetProtocolInfo(FunctorAsync& aFunctor) = 0;
    virtual void EndGetProtocolInfo(IAsync& aAsync, std::string& aSource, std::string& aSink) = 0;
    virtual void SyncPrepareForConnection(const std::string& aRemoteProtocolInfo, const std::string& aPeerConnectionManager, int32_t aPeerConnectionID, const std::string& aDirection, int32_t& aConnectionID, int32_t& aAVTransportID, int32_t& aRcsID) = 0;
    virtual void BeginPrepareForConnection(const std::string& aRemoteProtocolInfo, const std::string& aPeerConnectionManager, int32_t aPeerConnectionID, const std::string& aDirection, FunctorAsync& aFunctor) = 0;
    virtual void EndPrepareForConnection(IAsync& aAsync, int32_t& aConnectionID, int32_t& aAVTransportID, int32_t& aRcsID) = 0;
    virtual void SyncConnectionComplete(int32_t aConnectionID) = 0;
    virtual void BeginConnectionComplete(int32_t aConnectionID, FunctorAsync& aFunctor) = 0;
    virtual void EndConnectionComplete(IAsync& aAsync) = 0;
    virtual void SyncGetCurrentConnectionIDs(std::string& aConnectionIDs) = 0;
    virtual void BeginGetCurrentConnectionIDs(FunctorAsync& aFunctor) = 0;
    virtual void EndGetCurrentConnectionIDs(IAsync& aAsync, std::string& aConnectionIDs) = 0;
    virtual void SyncGetCurrentConnectionInfo(int32_t aConnectionID, int32_t& aRcsID, int32_t& aAVTransportID, std::string& aProtocolInfo, std::string& aPeerConnectionManager, int32_t& aPeerConnectionID, std::string& aDirection, std::string& aStatus) = 0;
    virtual void BeginGetCurrentConnectionInfo(int32_t aConnectionID, FunctorAsync& aFunctor) = 0;
    virtual void EndGetCurrentConnectionInfo(IAsync& aAsync, int32_t& aRcsID, int32_t& aAVTransportID, std::string& aProtocolInfo, std::string& aPeerConnectionManager, int32_t& aPeerConnectionID, std::string& aDirection, std::string& aStatus) = 0;
    virtual void SetPropertySourceProtocolInfoChanged(Functor& aSourceProtocolInfoChanged) = 0;
    virtual void PropertySourceProtocolInfo(std::string& aSourceProtocolInfo) const = 0;
    virtual void SetPropertySinkProtocolInfoChanged(Functor& aSinkProtocolInfoChanged) = 0;
    virtual void PropertySinkProtocolInfo(std::string& aSinkProtocolInfo) const = 0;
    virtual void SetPropertyCurrentConnectionIDsChanged(Functor& aCurrentConnectionIDsChanged) = 0;
    virtual void PropertyCurrentConnectionIDs(std::string& aCurrentConnectionIDs) const = 0;
};

/**
 * Proxy for upnp.org:ConnectionManager:1
 * @ingroup Proxies
 */
class CpProxyUpnpOrgConnectionManager1Cpp : public ICpProxyUpnpOrgConnectionManager1Cpp
{
public:
    /**
     * Constructor.
     *
     * Use iCpProxy::[Un]Subscribe() to enable/disable querying of state variable
     * and reporting of their changes.
     *
     * @param[in]  aDevice   The device to use
     */
    CpProxyUpnpOrgConnectionManager1Cpp(CpDeviceCpp& aDevice);
    /**
     * Destructor.
     * If any asynchronous method is in progress, this will block until they complete.
     * [Note that any methods still in progress are likely to complete with an error.]
     * Clients who have called Subscribe() do not need to call Unsubscribe() before
     * calling delete.  An unsubscribe will be triggered automatically when required.
     */
    ~CpProxyUpnpOrgConnectionManager1Cpp();

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aSource
     * @param[out] aSink
     */
    void SyncGetProtocolInfo(std::string& aSource, std::string& aSink);
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
    void EndGetProtocolInfo(IAsync& aAsync, std::string& aSource, std::string& aSink);

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
    void SyncPrepareForConnection(const std::string& aRemoteProtocolInfo, const std::string& aPeerConnectionManager, int32_t aPeerConnectionID, const std::string& aDirection, int32_t& aConnectionID, int32_t& aAVTransportID, int32_t& aRcsID);
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
    void BeginPrepareForConnection(const std::string& aRemoteProtocolInfo, const std::string& aPeerConnectionManager, int32_t aPeerConnectionID, const std::string& aDirection, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aConnectionID
     * @param[out] aAVTransportID
     * @param[out] aRcsID
     */
    void EndPrepareForConnection(IAsync& aAsync, int32_t& aConnectionID, int32_t& aAVTransportID, int32_t& aRcsID);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aConnectionID
     */
    void SyncConnectionComplete(int32_t aConnectionID);
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
    void BeginConnectionComplete(int32_t aConnectionID, FunctorAsync& aFunctor);
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
    void SyncGetCurrentConnectionIDs(std::string& aConnectionIDs);
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
    void EndGetCurrentConnectionIDs(IAsync& aAsync, std::string& aConnectionIDs);

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
    void SyncGetCurrentConnectionInfo(int32_t aConnectionID, int32_t& aRcsID, int32_t& aAVTransportID, std::string& aProtocolInfo, std::string& aPeerConnectionManager, int32_t& aPeerConnectionID, std::string& aDirection, std::string& aStatus);
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
    void BeginGetCurrentConnectionInfo(int32_t aConnectionID, FunctorAsync& aFunctor);
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
    void EndGetCurrentConnectionInfo(IAsync& aAsync, int32_t& aRcsID, int32_t& aAVTransportID, std::string& aProtocolInfo, std::string& aPeerConnectionManager, int32_t& aPeerConnectionID, std::string& aDirection, std::string& aStatus);

    /**
     * Set a callback to be run when the SourceProtocolInfo state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyUpnpOrgConnectionManager1Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertySourceProtocolInfoChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the SinkProtocolInfo state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyUpnpOrgConnectionManager1Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertySinkProtocolInfoChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the CurrentConnectionIDs state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyUpnpOrgConnectionManager1Cpp instance will not overlap.
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
    void PropertySourceProtocolInfo(std::string& aSourceProtocolInfo) const;
    /**
     * Query the value of the SinkProtocolInfo property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
     * to Unsubscribe().
     *
     * @param[out] aSinkProtocolInfo
     */
    void PropertySinkProtocolInfo(std::string& aSinkProtocolInfo) const;
    /**
     * Query the value of the CurrentConnectionIDs property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
     * to Unsubscribe().
     *
     * @param[out] aCurrentConnectionIDs
     */
    void PropertyCurrentConnectionIDs(std::string& aCurrentConnectionIDs) const;
    /**
    * This function exposes the Subscribe() function of the iCpProxy member variable
    */
    void Subscribe();
    /**
    * This function exposes the Unsubscribe() function of the iCpProxy member variable
    */
    void Unsubscribe();
    /**
    * This function exposes the SetPropertyChanged() function of the iCpProxy member variable
    */
    void SetPropertyChanged(Functor& aFunctor);
    /**
    * This function exposes the SetPropertyInitialEvent() function of the iCpProxy member variable
    */
    void SetPropertyInitialEvent(Functor& aFunctor);
    /**
    * This function exposes the AddProperty() function of the iCpProxy member variable
    */
    void AddProperty(Property* aProperty);
    /**
    * This function exposes DestroyService() function of the iCpProxy member variable
    */
    void DestroyService();
    /**
    * This function exposes the REportEvent() function of the iCpProxy member variable
    */
    void ReportEvent(Functor aFunctor);
    /**
    * This function exposes the Version() function of the iCpProxy member variable
    */
    TUint Version() const;
private:
    CpProxy iCpProxy;
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

#endif // HEADER_UPNPORGCONNECTIONMANAGER1CPP

