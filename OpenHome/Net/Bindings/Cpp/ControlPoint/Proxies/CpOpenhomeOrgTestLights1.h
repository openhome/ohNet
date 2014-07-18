#ifndef HEADER_OPENHOMEORGTESTLIGHTS1CPP
#define HEADER_OPENHOMEORGTESTLIGHTS1CPP

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
 * Proxy for openhome.org:TestLights:1
 * @ingroup Proxies
 */
class CpProxyOpenhomeOrgTestLights1Cpp : public CpProxy
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
    CpProxyOpenhomeOrgTestLights1Cpp(CpDeviceCpp& aDevice);
    /**
     * Destructor.
     * If any asynchronous method is in progress, this will block until they complete.
     * [Note that any methods still in progress are likely to complete with an error.]
     * Clients who have called Subscribe() do not need to call Unsubscribe() before
     * calling delete.  An unsubscribe will be triggered automatically when required.
     */
    ~CpProxyOpenhomeOrgTestLights1Cpp();

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aCount
     */
    void SyncGetCount(uint32_t& aCount);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndGetCount().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginGetCount(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aCount
     */
    void EndGetCount(IAsync& aAsync, uint32_t& aCount);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aIndex
     * @param[out] aRoomName
     */
    void SyncGetRoom(uint32_t aIndex, std::string& aRoomName);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndGetRoom().
     *
     * @param[in] aIndex
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginGetRoom(uint32_t aIndex, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aRoomName
     */
    void EndGetRoom(IAsync& aAsync, std::string& aRoomName);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aIndex
     * @param[out] aFriendlyName
     */
    void SyncGetName(uint32_t aIndex, std::string& aFriendlyName);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndGetName().
     *
     * @param[in] aIndex
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginGetName(uint32_t aIndex, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aFriendlyName
     */
    void EndGetName(IAsync& aAsync, std::string& aFriendlyName);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aIndex
     * @param[out] aX
     * @param[out] aY
     * @param[out] aZ
     */
    void SyncGetPosition(uint32_t aIndex, uint32_t& aX, uint32_t& aY, uint32_t& aZ);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndGetPosition().
     *
     * @param[in] aIndex
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginGetPosition(uint32_t aIndex, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aX
     * @param[out] aY
     * @param[out] aZ
     */
    void EndGetPosition(IAsync& aAsync, uint32_t& aX, uint32_t& aY, uint32_t& aZ);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aIndex
     * @param[in]  aColor
     */
    void SyncSetColor(uint32_t aIndex, uint32_t aColor);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSetColor().
     *
     * @param[in] aIndex
     * @param[in] aColor
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSetColor(uint32_t aIndex, uint32_t aColor, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSetColor(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aIndex
     * @param[out] aColor
     */
    void SyncGetColor(uint32_t aIndex, uint32_t& aColor);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndGetColor().
     *
     * @param[in] aIndex
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginGetColor(uint32_t aIndex, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aColor
     */
    void EndGetColor(IAsync& aAsync, uint32_t& aColor);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aColor
     * @param[out] aBrightness
     * @param[out] aRed
     * @param[out] aGreen
     * @param[out] aBlue
     */
    void SyncGetColorComponents(uint32_t aColor, uint32_t& aBrightness, uint32_t& aRed, uint32_t& aGreen, uint32_t& aBlue);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndGetColorComponents().
     *
     * @param[in] aColor
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginGetColorComponents(uint32_t aColor, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aBrightness
     * @param[out] aRed
     * @param[out] aGreen
     * @param[out] aBlue
     */
    void EndGetColorComponents(IAsync& aAsync, uint32_t& aBrightness, uint32_t& aRed, uint32_t& aGreen, uint32_t& aBlue);


private:
private:
    Action* iActionGetCount;
    Action* iActionGetRoom;
    Action* iActionGetName;
    Action* iActionGetPosition;
    Action* iActionSetColor;
    Action* iActionGetColor;
    Action* iActionGetColorComponents;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_OPENHOMEORGTESTLIGHTS1CPP

