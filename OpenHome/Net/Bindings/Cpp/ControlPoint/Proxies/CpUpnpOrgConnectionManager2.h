#ifndef HEADER_UPNPORGCONNECTIONMANAGER2CPP
#define HEADER_UPNPORGCONNECTIONMANAGER2CPP

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

/**
 * Proxy for upnp.org:ConnectionManager:2
 * @ingroup Proxies
 */
class CpProxyUpnpOrgConnectionManager2Cpp : public CpProxy
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
    CpProxyUpnpOrgConnectionManager2Cpp(CpDeviceCpp& aDevice);
    /**
     * Destructor.
     * If any asynchronous method is in progress, this will block until they complete.
     * [Note that any methods still in progress are likely to complete with an error.]
     * Clients who have called Subscribe() do not need to call Unsubscribe() before
     * calling delete.  An unsubscribe will be triggered automatically when required.
     */
    ~CpProxyUpnpOrgConnectionManager2Cpp();

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
     * CpProxyUpnpOrgConnectionManager2Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertySourceProtocolInfoChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the SinkProtocolInfo state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyUpnpOrgConnectionManager2Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertySinkProtocolInfoChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the CurrentConnectionIDs state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyUpnpOrgConnectionManager2Cpp instance will not overlap.
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

#endif // HEADER_UPNPORGCONNECTIONMANAGER2CPP

