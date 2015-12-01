#ifndef HEADER_AVOPENHOMEORGPRODUCT1CPP
#define HEADER_AVOPENHOMEORGPRODUCT1CPP

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
class ICpProxyAvOpenhomeOrgProduct1Cpp : public ICpProxy
{
public:
    virtual void SyncManufacturer(std::string& aName, std::string& aInfo, std::string& aUrl, std::string& aImageUri) = 0;
    virtual void BeginManufacturer(FunctorAsync& aFunctor) = 0;
    virtual void EndManufacturer(IAsync& aAsync, std::string& aName, std::string& aInfo, std::string& aUrl, std::string& aImageUri) = 0;
    virtual void SyncModel(std::string& aName, std::string& aInfo, std::string& aUrl, std::string& aImageUri) = 0;
    virtual void BeginModel(FunctorAsync& aFunctor) = 0;
    virtual void EndModel(IAsync& aAsync, std::string& aName, std::string& aInfo, std::string& aUrl, std::string& aImageUri) = 0;
    virtual void SyncProduct(std::string& aRoom, std::string& aName, std::string& aInfo, std::string& aUrl, std::string& aImageUri) = 0;
    virtual void BeginProduct(FunctorAsync& aFunctor) = 0;
    virtual void EndProduct(IAsync& aAsync, std::string& aRoom, std::string& aName, std::string& aInfo, std::string& aUrl, std::string& aImageUri) = 0;
    virtual void SyncStandby(bool& aValue) = 0;
    virtual void BeginStandby(FunctorAsync& aFunctor) = 0;
    virtual void EndStandby(IAsync& aAsync, bool& aValue) = 0;
    virtual void SyncSetStandby(bool aValue) = 0;
    virtual void BeginSetStandby(bool aValue, FunctorAsync& aFunctor) = 0;
    virtual void EndSetStandby(IAsync& aAsync) = 0;
    virtual void SyncSourceCount(uint32_t& aValue) = 0;
    virtual void BeginSourceCount(FunctorAsync& aFunctor) = 0;
    virtual void EndSourceCount(IAsync& aAsync, uint32_t& aValue) = 0;
    virtual void SyncSourceXml(std::string& aValue) = 0;
    virtual void BeginSourceXml(FunctorAsync& aFunctor) = 0;
    virtual void EndSourceXml(IAsync& aAsync, std::string& aValue) = 0;
    virtual void SyncSourceIndex(uint32_t& aValue) = 0;
    virtual void BeginSourceIndex(FunctorAsync& aFunctor) = 0;
    virtual void EndSourceIndex(IAsync& aAsync, uint32_t& aValue) = 0;
    virtual void SyncSetSourceIndex(uint32_t aValue) = 0;
    virtual void BeginSetSourceIndex(uint32_t aValue, FunctorAsync& aFunctor) = 0;
    virtual void EndSetSourceIndex(IAsync& aAsync) = 0;
    virtual void SyncSetSourceIndexByName(const std::string& aValue) = 0;
    virtual void BeginSetSourceIndexByName(const std::string& aValue, FunctorAsync& aFunctor) = 0;
    virtual void EndSetSourceIndexByName(IAsync& aAsync) = 0;
    virtual void SyncSource(uint32_t aIndex, std::string& aSystemName, std::string& aType, std::string& aName, bool& aVisible) = 0;
    virtual void BeginSource(uint32_t aIndex, FunctorAsync& aFunctor) = 0;
    virtual void EndSource(IAsync& aAsync, std::string& aSystemName, std::string& aType, std::string& aName, bool& aVisible) = 0;
    virtual void SyncAttributes(std::string& aValue) = 0;
    virtual void BeginAttributes(FunctorAsync& aFunctor) = 0;
    virtual void EndAttributes(IAsync& aAsync, std::string& aValue) = 0;
    virtual void SyncSourceXmlChangeCount(uint32_t& aValue) = 0;
    virtual void BeginSourceXmlChangeCount(FunctorAsync& aFunctor) = 0;
    virtual void EndSourceXmlChangeCount(IAsync& aAsync, uint32_t& aValue) = 0;
    virtual void SetPropertyManufacturerNameChanged(Functor& aManufacturerNameChanged) = 0;
    virtual void PropertyManufacturerName(std::string& aManufacturerName) const = 0;
    virtual void SetPropertyManufacturerInfoChanged(Functor& aManufacturerInfoChanged) = 0;
    virtual void PropertyManufacturerInfo(std::string& aManufacturerInfo) const = 0;
    virtual void SetPropertyManufacturerUrlChanged(Functor& aManufacturerUrlChanged) = 0;
    virtual void PropertyManufacturerUrl(std::string& aManufacturerUrl) const = 0;
    virtual void SetPropertyManufacturerImageUriChanged(Functor& aManufacturerImageUriChanged) = 0;
    virtual void PropertyManufacturerImageUri(std::string& aManufacturerImageUri) const = 0;
    virtual void SetPropertyModelNameChanged(Functor& aModelNameChanged) = 0;
    virtual void PropertyModelName(std::string& aModelName) const = 0;
    virtual void SetPropertyModelInfoChanged(Functor& aModelInfoChanged) = 0;
    virtual void PropertyModelInfo(std::string& aModelInfo) const = 0;
    virtual void SetPropertyModelUrlChanged(Functor& aModelUrlChanged) = 0;
    virtual void PropertyModelUrl(std::string& aModelUrl) const = 0;
    virtual void SetPropertyModelImageUriChanged(Functor& aModelImageUriChanged) = 0;
    virtual void PropertyModelImageUri(std::string& aModelImageUri) const = 0;
    virtual void SetPropertyProductRoomChanged(Functor& aProductRoomChanged) = 0;
    virtual void PropertyProductRoom(std::string& aProductRoom) const = 0;
    virtual void SetPropertyProductNameChanged(Functor& aProductNameChanged) = 0;
    virtual void PropertyProductName(std::string& aProductName) const = 0;
    virtual void SetPropertyProductInfoChanged(Functor& aProductInfoChanged) = 0;
    virtual void PropertyProductInfo(std::string& aProductInfo) const = 0;
    virtual void SetPropertyProductUrlChanged(Functor& aProductUrlChanged) = 0;
    virtual void PropertyProductUrl(std::string& aProductUrl) const = 0;
    virtual void SetPropertyProductImageUriChanged(Functor& aProductImageUriChanged) = 0;
    virtual void PropertyProductImageUri(std::string& aProductImageUri) const = 0;
    virtual void SetPropertyStandbyChanged(Functor& aStandbyChanged) = 0;
    virtual void PropertyStandby(bool& aStandby) const = 0;
    virtual void SetPropertySourceIndexChanged(Functor& aSourceIndexChanged) = 0;
    virtual void PropertySourceIndex(uint32_t& aSourceIndex) const = 0;
    virtual void SetPropertySourceCountChanged(Functor& aSourceCountChanged) = 0;
    virtual void PropertySourceCount(uint32_t& aSourceCount) const = 0;
    virtual void SetPropertySourceXmlChanged(Functor& aSourceXmlChanged) = 0;
    virtual void PropertySourceXml(std::string& aSourceXml) const = 0;
    virtual void SetPropertyAttributesChanged(Functor& aAttributesChanged) = 0;
    virtual void PropertyAttributes(std::string& aAttributes) const = 0;
};

/**
 * Proxy for av.openhome.org:Product:1
 * @ingroup Proxies
 */
class CpProxyAvOpenhomeOrgProduct1Cpp : public ICpProxyAvOpenhomeOrgProduct1Cpp
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
    CpProxyAvOpenhomeOrgProduct1Cpp(CpDeviceCpp& aDevice);
    /**
     * Destructor.
     * If any asynchronous method is in progress, this will block until they complete.
     * [Note that any methods still in progress are likely to complete with an error.]
     * Clients who have called Subscribe() do not need to call Unsubscribe() before
     * calling delete.  An unsubscribe will be triggered automatically when required.
     */
    ~CpProxyAvOpenhomeOrgProduct1Cpp();

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aName
     * @param[out] aInfo
     * @param[out] aUrl
     * @param[out] aImageUri
     */
    void SyncManufacturer(std::string& aName, std::string& aInfo, std::string& aUrl, std::string& aImageUri);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndManufacturer().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginManufacturer(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aName
     * @param[out] aInfo
     * @param[out] aUrl
     * @param[out] aImageUri
     */
    void EndManufacturer(IAsync& aAsync, std::string& aName, std::string& aInfo, std::string& aUrl, std::string& aImageUri);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aName
     * @param[out] aInfo
     * @param[out] aUrl
     * @param[out] aImageUri
     */
    void SyncModel(std::string& aName, std::string& aInfo, std::string& aUrl, std::string& aImageUri);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndModel().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginModel(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aName
     * @param[out] aInfo
     * @param[out] aUrl
     * @param[out] aImageUri
     */
    void EndModel(IAsync& aAsync, std::string& aName, std::string& aInfo, std::string& aUrl, std::string& aImageUri);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aRoom
     * @param[out] aName
     * @param[out] aInfo
     * @param[out] aUrl
     * @param[out] aImageUri
     */
    void SyncProduct(std::string& aRoom, std::string& aName, std::string& aInfo, std::string& aUrl, std::string& aImageUri);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndProduct().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginProduct(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aRoom
     * @param[out] aName
     * @param[out] aInfo
     * @param[out] aUrl
     * @param[out] aImageUri
     */
    void EndProduct(IAsync& aAsync, std::string& aRoom, std::string& aName, std::string& aInfo, std::string& aUrl, std::string& aImageUri);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aValue
     */
    void SyncStandby(bool& aValue);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndStandby().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginStandby(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aValue
     */
    void EndStandby(IAsync& aAsync, bool& aValue);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aValue
     */
    void SyncSetStandby(bool aValue);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSetStandby().
     *
     * @param[in] aValue
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSetStandby(bool aValue, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSetStandby(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aValue
     */
    void SyncSourceCount(uint32_t& aValue);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSourceCount().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSourceCount(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aValue
     */
    void EndSourceCount(IAsync& aAsync, uint32_t& aValue);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aValue
     */
    void SyncSourceXml(std::string& aValue);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSourceXml().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSourceXml(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aValue
     */
    void EndSourceXml(IAsync& aAsync, std::string& aValue);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aValue
     */
    void SyncSourceIndex(uint32_t& aValue);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSourceIndex().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSourceIndex(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aValue
     */
    void EndSourceIndex(IAsync& aAsync, uint32_t& aValue);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aValue
     */
    void SyncSetSourceIndex(uint32_t aValue);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSetSourceIndex().
     *
     * @param[in] aValue
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSetSourceIndex(uint32_t aValue, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSetSourceIndex(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aValue
     */
    void SyncSetSourceIndexByName(const std::string& aValue);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSetSourceIndexByName().
     *
     * @param[in] aValue
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSetSourceIndexByName(const std::string& aValue, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSetSourceIndexByName(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aIndex
     * @param[out] aSystemName
     * @param[out] aType
     * @param[out] aName
     * @param[out] aVisible
     */
    void SyncSource(uint32_t aIndex, std::string& aSystemName, std::string& aType, std::string& aName, bool& aVisible);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSource().
     *
     * @param[in] aIndex
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSource(uint32_t aIndex, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aSystemName
     * @param[out] aType
     * @param[out] aName
     * @param[out] aVisible
     */
    void EndSource(IAsync& aAsync, std::string& aSystemName, std::string& aType, std::string& aName, bool& aVisible);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aValue
     */
    void SyncAttributes(std::string& aValue);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndAttributes().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginAttributes(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aValue
     */
    void EndAttributes(IAsync& aAsync, std::string& aValue);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aValue
     */
    void SyncSourceXmlChangeCount(uint32_t& aValue);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSourceXmlChangeCount().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSourceXmlChangeCount(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aValue
     */
    void EndSourceXmlChangeCount(IAsync& aAsync, uint32_t& aValue);

    /**
     * Set a callback to be run when the ManufacturerName state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgProduct1Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyManufacturerNameChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the ManufacturerInfo state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgProduct1Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyManufacturerInfoChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the ManufacturerUrl state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgProduct1Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyManufacturerUrlChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the ManufacturerImageUri state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgProduct1Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyManufacturerImageUriChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the ModelName state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgProduct1Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyModelNameChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the ModelInfo state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgProduct1Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyModelInfoChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the ModelUrl state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgProduct1Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyModelUrlChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the ModelImageUri state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgProduct1Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyModelImageUriChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the ProductRoom state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgProduct1Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyProductRoomChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the ProductName state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgProduct1Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyProductNameChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the ProductInfo state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgProduct1Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyProductInfoChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the ProductUrl state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgProduct1Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyProductUrlChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the ProductImageUri state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgProduct1Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyProductImageUriChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the Standby state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgProduct1Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyStandbyChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the SourceIndex state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgProduct1Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertySourceIndexChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the SourceCount state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgProduct1Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertySourceCountChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the SourceXml state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgProduct1Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertySourceXmlChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the Attributes state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgProduct1Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyAttributesChanged(Functor& aFunctor);

    /**
     * Query the value of the ManufacturerName property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
     * to Unsubscribe().
     *
     * @param[out] aManufacturerName
     */
    void PropertyManufacturerName(std::string& aManufacturerName) const;
    /**
     * Query the value of the ManufacturerInfo property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
     * to Unsubscribe().
     *
     * @param[out] aManufacturerInfo
     */
    void PropertyManufacturerInfo(std::string& aManufacturerInfo) const;
    /**
     * Query the value of the ManufacturerUrl property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
     * to Unsubscribe().
     *
     * @param[out] aManufacturerUrl
     */
    void PropertyManufacturerUrl(std::string& aManufacturerUrl) const;
    /**
     * Query the value of the ManufacturerImageUri property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
     * to Unsubscribe().
     *
     * @param[out] aManufacturerImageUri
     */
    void PropertyManufacturerImageUri(std::string& aManufacturerImageUri) const;
    /**
     * Query the value of the ModelName property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
     * to Unsubscribe().
     *
     * @param[out] aModelName
     */
    void PropertyModelName(std::string& aModelName) const;
    /**
     * Query the value of the ModelInfo property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
     * to Unsubscribe().
     *
     * @param[out] aModelInfo
     */
    void PropertyModelInfo(std::string& aModelInfo) const;
    /**
     * Query the value of the ModelUrl property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
     * to Unsubscribe().
     *
     * @param[out] aModelUrl
     */
    void PropertyModelUrl(std::string& aModelUrl) const;
    /**
     * Query the value of the ModelImageUri property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
     * to Unsubscribe().
     *
     * @param[out] aModelImageUri
     */
    void PropertyModelImageUri(std::string& aModelImageUri) const;
    /**
     * Query the value of the ProductRoom property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
     * to Unsubscribe().
     *
     * @param[out] aProductRoom
     */
    void PropertyProductRoom(std::string& aProductRoom) const;
    /**
     * Query the value of the ProductName property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
     * to Unsubscribe().
     *
     * @param[out] aProductName
     */
    void PropertyProductName(std::string& aProductName) const;
    /**
     * Query the value of the ProductInfo property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
     * to Unsubscribe().
     *
     * @param[out] aProductInfo
     */
    void PropertyProductInfo(std::string& aProductInfo) const;
    /**
     * Query the value of the ProductUrl property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
     * to Unsubscribe().
     *
     * @param[out] aProductUrl
     */
    void PropertyProductUrl(std::string& aProductUrl) const;
    /**
     * Query the value of the ProductImageUri property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
     * to Unsubscribe().
     *
     * @param[out] aProductImageUri
     */
    void PropertyProductImageUri(std::string& aProductImageUri) const;
    /**
     * Query the value of the Standby property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
     * to Unsubscribe().
     *
     * @param[out] aStandby
     */
    void PropertyStandby(bool& aStandby) const;
    /**
     * Query the value of the SourceIndex property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
     * to Unsubscribe().
     *
     * @param[out] aSourceIndex
     */
    void PropertySourceIndex(uint32_t& aSourceIndex) const;
    /**
     * Query the value of the SourceCount property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
     * to Unsubscribe().
     *
     * @param[out] aSourceCount
     */
    void PropertySourceCount(uint32_t& aSourceCount) const;
    /**
     * Query the value of the SourceXml property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
     * to Unsubscribe().
     *
     * @param[out] aSourceXml
     */
    void PropertySourceXml(std::string& aSourceXml) const;
    /**
     * Query the value of the Attributes property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
     * to Unsubscribe().
     *
     * @param[out] aAttributes
     */
    void PropertyAttributes(std::string& aAttributes) const;
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
    void ManufacturerNamePropertyChanged();
    void ManufacturerInfoPropertyChanged();
    void ManufacturerUrlPropertyChanged();
    void ManufacturerImageUriPropertyChanged();
    void ModelNamePropertyChanged();
    void ModelInfoPropertyChanged();
    void ModelUrlPropertyChanged();
    void ModelImageUriPropertyChanged();
    void ProductRoomPropertyChanged();
    void ProductNamePropertyChanged();
    void ProductInfoPropertyChanged();
    void ProductUrlPropertyChanged();
    void ProductImageUriPropertyChanged();
    void StandbyPropertyChanged();
    void SourceIndexPropertyChanged();
    void SourceCountPropertyChanged();
    void SourceXmlPropertyChanged();
    void AttributesPropertyChanged();
private:
    Action* iActionManufacturer;
    Action* iActionModel;
    Action* iActionProduct;
    Action* iActionStandby;
    Action* iActionSetStandby;
    Action* iActionSourceCount;
    Action* iActionSourceXml;
    Action* iActionSourceIndex;
    Action* iActionSetSourceIndex;
    Action* iActionSetSourceIndexByName;
    Action* iActionSource;
    Action* iActionAttributes;
    Action* iActionSourceXmlChangeCount;
    PropertyString* iManufacturerName;
    PropertyString* iManufacturerInfo;
    PropertyString* iManufacturerUrl;
    PropertyString* iManufacturerImageUri;
    PropertyString* iModelName;
    PropertyString* iModelInfo;
    PropertyString* iModelUrl;
    PropertyString* iModelImageUri;
    PropertyString* iProductRoom;
    PropertyString* iProductName;
    PropertyString* iProductInfo;
    PropertyString* iProductUrl;
    PropertyString* iProductImageUri;
    PropertyBool* iStandby;
    PropertyUint* iSourceIndex;
    PropertyUint* iSourceCount;
    PropertyString* iSourceXml;
    PropertyString* iAttributes;
    Functor iManufacturerNameChanged;
    Functor iManufacturerInfoChanged;
    Functor iManufacturerUrlChanged;
    Functor iManufacturerImageUriChanged;
    Functor iModelNameChanged;
    Functor iModelInfoChanged;
    Functor iModelUrlChanged;
    Functor iModelImageUriChanged;
    Functor iProductRoomChanged;
    Functor iProductNameChanged;
    Functor iProductInfoChanged;
    Functor iProductUrlChanged;
    Functor iProductImageUriChanged;
    Functor iStandbyChanged;
    Functor iSourceIndexChanged;
    Functor iSourceCountChanged;
    Functor iSourceXmlChanged;
    Functor iAttributesChanged;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_AVOPENHOMEORGPRODUCT1CPP

