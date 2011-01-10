#ifndef HEADER_DVAVOPENHOMEORGRECEIVER1
#define HEADER_DVAVOPENHOMEORGRECEIVER1

#include <ZappTypes.h>
#include <Buffer.h>
#include <Core/DvDevice.h>
#include <DvProvider.h>

namespace Zapp {

class IDviInvocation;
class PropertyInt;
class PropertyUint;
class PropertyBool;
class PropertyString;
class PropertyBinary;

/**
 * Provider for the av.openhome.org:Receiver:1 UPnP service
 * @ingroup Providers
 */
class DvProviderAvOpenhomeOrgReceiver1 : public DvProvider
{
public:
    virtual ~DvProviderAvOpenhomeOrgReceiver1() {}
    /**
     * Set the value of the Uri property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyUri(const Brx& aValue);
    /**
     * Get a copy of the value of the Uri property
     */
    void GetPropertyUri(Brhz& aValue);
    /**
     * Set the value of the Metadata property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyMetadata(const Brx& aValue);
    /**
     * Get a copy of the value of the Metadata property
     */
    void GetPropertyMetadata(Brhz& aValue);
    /**
     * Set the value of the TransportState property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyTransportState(const Brx& aValue);
    /**
     * Get a copy of the value of the TransportState property
     */
    void GetPropertyTransportState(Brhz& aValue);
    /**
     * Set the value of the ProtocolInfo property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyProtocolInfo(const Brx& aValue);
    /**
     * Get a copy of the value of the ProtocolInfo property
     */
    void GetPropertyProtocolInfo(Brhz& aValue);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderAvOpenhomeOrgReceiver1(DvDevice& aDevice);
    /**
     * Signal that the action Play is supported.
     * The action's availability will be published in the device's service.xml.
     * DoPlay must be overridden if this is called.
     */
    void EnableActionPlay();
    /**
     * Signal that the action Stop is supported.
     * The action's availability will be published in the device's service.xml.
     * DoStop must be overridden if this is called.
     */
    void EnableActionStop();
    /**
     * Signal that the action SetSender is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetSender must be overridden if this is called.
     */
    void EnableActionSetSender();
    /**
     * Signal that the action Sender is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSender must be overridden if this is called.
     */
    void EnableActionSender();
    /**
     * Signal that the action ProtocolInfo is supported.
     * The action's availability will be published in the device's service.xml.
     * DoProtocolInfo must be overridden if this is called.
     */
    void EnableActionProtocolInfo();
    /**
     * Signal that the action TransportState is supported.
     * The action's availability will be published in the device's service.xml.
     * DoTransportState must be overridden if this is called.
     */
    void EnableActionTransportState();
private:
    /**
     * Play action.
     *
     * Will be called when the device stack receives an invocation of the
     * Play action for the owning device.
     * Must be implemented iff EnableActionPlay was called.
     */
    virtual void Play(IInvocationResponse& aResponse, TUint aVersion);
    /**
     * Stop action.
     *
     * Will be called when the device stack receives an invocation of the
     * Stop action for the owning device.
     * Must be implemented iff EnableActionStop was called.
     */
    virtual void Stop(IInvocationResponse& aResponse, TUint aVersion);
    /**
     * SetSender action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetSender action for the owning device.
     * Must be implemented iff EnableActionSetSender was called.
     */
    virtual void SetSender(IInvocationResponse& aResponse, TUint aVersion, const Brx& aUri, const Brx& aMetadata);
    /**
     * Sender action.
     *
     * Will be called when the device stack receives an invocation of the
     * Sender action for the owning device.
     * Must be implemented iff EnableActionSender was called.
     */
    virtual void Sender(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aUri, IInvocationResponseString& aMetadata);
    /**
     * ProtocolInfo action.
     *
     * Will be called when the device stack receives an invocation of the
     * ProtocolInfo action for the owning device.
     * Must be implemented iff EnableActionProtocolInfo was called.
     */
    virtual void ProtocolInfo(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aValue);
    /**
     * TransportState action.
     *
     * Will be called when the device stack receives an invocation of the
     * TransportState action for the owning device.
     * Must be implemented iff EnableActionTransportState was called.
     */
    virtual void TransportState(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aValue);
private:
    DvProviderAvOpenhomeOrgReceiver1();
    void DoPlay(IDviInvocation& aInvocation, TUint aVersion);
    void DoStop(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetSender(IDviInvocation& aInvocation, TUint aVersion);
    void DoSender(IDviInvocation& aInvocation, TUint aVersion);
    void DoProtocolInfo(IDviInvocation& aInvocation, TUint aVersion);
    void DoTransportState(IDviInvocation& aInvocation, TUint aVersion);
private:
    PropertyString* iPropertyUri;
    PropertyString* iPropertyMetadata;
    PropertyString* iPropertyTransportState;
    PropertyString* iPropertyProtocolInfo;
};

} // namespace Zapp

#endif // HEADER_DVAVOPENHOMEORGRECEIVER1

