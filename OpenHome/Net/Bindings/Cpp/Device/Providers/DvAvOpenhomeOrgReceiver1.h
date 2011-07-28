#ifndef HEADER_DVAVOPENHOMEORGRECEIVER1CPP
#define HEADER_DVAVOPENHOMEORGRECEIVER1CPP

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Cpp/DvDevice.h>
#include <OpenHome/Net/Core/DvProvider.h>

#include <string>

namespace OpenHome {
namespace Net {

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
class DvProviderAvOpenhomeOrgReceiver1Cpp : public DvProvider
{
public:
    virtual ~DvProviderAvOpenhomeOrgReceiver1Cpp() {}
    /**
     * Set the value of the Uri property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyUri(const std::string& aValue);
    /**
     * Get a copy of the value of the Uri property
     */
    void GetPropertyUri(std::string& aValue);
    /**
     * Set the value of the Metadata property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyMetadata(const std::string& aValue);
    /**
     * Get a copy of the value of the Metadata property
     */
    void GetPropertyMetadata(std::string& aValue);
    /**
     * Set the value of the TransportState property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyTransportState(const std::string& aValue);
    /**
     * Get a copy of the value of the TransportState property
     */
    void GetPropertyTransportState(std::string& aValue);
    /**
     * Set the value of the ProtocolInfo property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyProtocolInfo(const std::string& aValue);
    /**
     * Get a copy of the value of the ProtocolInfo property
     */
    void GetPropertyProtocolInfo(std::string& aValue);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderAvOpenhomeOrgReceiver1Cpp(DvDeviceStd& aDevice);
    /**
     * Signal that the action Play is supported.
     * The action's availability will be published in the device's service.xml.
     * Play must be overridden if this is called.
     */
    void EnableActionPlay();
    /**
     * Signal that the action Stop is supported.
     * The action's availability will be published in the device's service.xml.
     * Stop must be overridden if this is called.
     */
    void EnableActionStop();
    /**
     * Signal that the action SetSender is supported.
     * The action's availability will be published in the device's service.xml.
     * SetSender must be overridden if this is called.
     */
    void EnableActionSetSender();
    /**
     * Signal that the action Sender is supported.
     * The action's availability will be published in the device's service.xml.
     * Sender must be overridden if this is called.
     */
    void EnableActionSender();
    /**
     * Signal that the action ProtocolInfo is supported.
     * The action's availability will be published in the device's service.xml.
     * ProtocolInfo must be overridden if this is called.
     */
    void EnableActionProtocolInfo();
    /**
     * Signal that the action TransportState is supported.
     * The action's availability will be published in the device's service.xml.
     * TransportState must be overridden if this is called.
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
    virtual void Play(uint32_t aVersion);
    /**
     * Stop action.
     *
     * Will be called when the device stack receives an invocation of the
     * Stop action for the owning device.
     * Must be implemented iff EnableActionStop was called.
     */
    virtual void Stop(uint32_t aVersion);
    /**
     * SetSender action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetSender action for the owning device.
     * Must be implemented iff EnableActionSetSender was called.
     */
    virtual void SetSender(uint32_t aVersion, const std::string& aUri, const std::string& aMetadata);
    /**
     * Sender action.
     *
     * Will be called when the device stack receives an invocation of the
     * Sender action for the owning device.
     * Must be implemented iff EnableActionSender was called.
     */
    virtual void Sender(uint32_t aVersion, std::string& aUri, std::string& aMetadata);
    /**
     * ProtocolInfo action.
     *
     * Will be called when the device stack receives an invocation of the
     * ProtocolInfo action for the owning device.
     * Must be implemented iff EnableActionProtocolInfo was called.
     */
    virtual void ProtocolInfo(uint32_t aVersion, std::string& aValue);
    /**
     * TransportState action.
     *
     * Will be called when the device stack receives an invocation of the
     * TransportState action for the owning device.
     * Must be implemented iff EnableActionTransportState was called.
     */
    virtual void TransportState(uint32_t aVersion, std::string& aValue);
private:
    DvProviderAvOpenhomeOrgReceiver1Cpp();
    void DoPlay(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoStop(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetSender(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSender(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoProtocolInfo(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoTransportState(IDviInvocation& aInvocation, uint32_t aVersion);
private:
    PropertyString* iPropertyUri;
    PropertyString* iPropertyMetadata;
    PropertyString* iPropertyTransportState;
    PropertyString* iPropertyProtocolInfo;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_DVAVOPENHOMEORGRECEIVER1CPP

