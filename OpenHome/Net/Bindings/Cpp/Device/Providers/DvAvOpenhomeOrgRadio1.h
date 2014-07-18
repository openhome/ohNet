#ifndef HEADER_DVAVOPENHOMEORGRADIO1CPP
#define HEADER_DVAVOPENHOMEORGRADIO1CPP

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Cpp/DvDevice.h>
#include <OpenHome/Net/Core/DvProvider.h>
#include <OpenHome/Net/Cpp/DvInvocation.h>

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
 * Provider for the av.openhome.org:Radio:1 UPnP service
 * @ingroup Providers
 */
class DvProviderAvOpenhomeOrgRadio1Cpp : public DvProvider
{
public:
    virtual ~DvProviderAvOpenhomeOrgRadio1Cpp() {}
    /**
     * Set the value of the Uri property
     *
     * Can only be called if EnablePropertyUri has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyUri(const std::string& aValue);
    /**
     * Get a copy of the value of the Uri property
     *
     * Can only be called if EnablePropertyUri has previously been called.
     */
    void GetPropertyUri(std::string& aValue);
    /**
     * Set the value of the Metadata property
     *
     * Can only be called if EnablePropertyMetadata has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyMetadata(const std::string& aValue);
    /**
     * Get a copy of the value of the Metadata property
     *
     * Can only be called if EnablePropertyMetadata has previously been called.
     */
    void GetPropertyMetadata(std::string& aValue);
    /**
     * Set the value of the TransportState property
     *
     * Can only be called if EnablePropertyTransportState has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyTransportState(const std::string& aValue);
    /**
     * Get a copy of the value of the TransportState property
     *
     * Can only be called if EnablePropertyTransportState has previously been called.
     */
    void GetPropertyTransportState(std::string& aValue);
    /**
     * Set the value of the Id property
     *
     * Can only be called if EnablePropertyId has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyId(uint32_t aValue);
    /**
     * Get a copy of the value of the Id property
     *
     * Can only be called if EnablePropertyId has previously been called.
     */
    void GetPropertyId(uint32_t& aValue);
    /**
     * Set the value of the IdArray property
     *
     * Can only be called if EnablePropertyIdArray has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyIdArray(const std::string& aValue);
    /**
     * Get a copy of the value of the IdArray property
     *
     * Can only be called if EnablePropertyIdArray has previously been called.
     */
    void GetPropertyIdArray(std::string& aValue);
    /**
     * Set the value of the ChannelsMax property
     *
     * Can only be called if EnablePropertyChannelsMax has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyChannelsMax(uint32_t aValue);
    /**
     * Get a copy of the value of the ChannelsMax property
     *
     * Can only be called if EnablePropertyChannelsMax has previously been called.
     */
    void GetPropertyChannelsMax(uint32_t& aValue);
    /**
     * Set the value of the ProtocolInfo property
     *
     * Can only be called if EnablePropertyProtocolInfo has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyProtocolInfo(const std::string& aValue);
    /**
     * Get a copy of the value of the ProtocolInfo property
     *
     * Can only be called if EnablePropertyProtocolInfo has previously been called.
     */
    void GetPropertyProtocolInfo(std::string& aValue);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderAvOpenhomeOrgRadio1Cpp(DvDeviceStd& aDevice);
    /**
     * Enable the Uri property.
     */
    void EnablePropertyUri();
    /**
     * Enable the Metadata property.
     */
    void EnablePropertyMetadata();
    /**
     * Enable the TransportState property.
     */
    void EnablePropertyTransportState();
    /**
     * Enable the Id property.
     */
    void EnablePropertyId();
    /**
     * Enable the IdArray property.
     */
    void EnablePropertyIdArray();
    /**
     * Enable the ChannelsMax property.
     */
    void EnablePropertyChannelsMax();
    /**
     * Enable the ProtocolInfo property.
     */
    void EnablePropertyProtocolInfo();
    /**
     * Signal that the action Play is supported.
     * The action's availability will be published in the device's service.xml.
     * Play must be overridden if this is called.
     */
    void EnableActionPlay();
    /**
     * Signal that the action Pause is supported.
     * The action's availability will be published in the device's service.xml.
     * Pause must be overridden if this is called.
     */
    void EnableActionPause();
    /**
     * Signal that the action Stop is supported.
     * The action's availability will be published in the device's service.xml.
     * Stop must be overridden if this is called.
     */
    void EnableActionStop();
    /**
     * Signal that the action SeekSecondAbsolute is supported.
     * The action's availability will be published in the device's service.xml.
     * SeekSecondAbsolute must be overridden if this is called.
     */
    void EnableActionSeekSecondAbsolute();
    /**
     * Signal that the action SeekSecondRelative is supported.
     * The action's availability will be published in the device's service.xml.
     * SeekSecondRelative must be overridden if this is called.
     */
    void EnableActionSeekSecondRelative();
    /**
     * Signal that the action Channel is supported.
     * The action's availability will be published in the device's service.xml.
     * Channel must be overridden if this is called.
     */
    void EnableActionChannel();
    /**
     * Signal that the action SetChannel is supported.
     * The action's availability will be published in the device's service.xml.
     * SetChannel must be overridden if this is called.
     */
    void EnableActionSetChannel();
    /**
     * Signal that the action TransportState is supported.
     * The action's availability will be published in the device's service.xml.
     * TransportState must be overridden if this is called.
     */
    void EnableActionTransportState();
    /**
     * Signal that the action Id is supported.
     * The action's availability will be published in the device's service.xml.
     * Id must be overridden if this is called.
     */
    void EnableActionId();
    /**
     * Signal that the action SetId is supported.
     * The action's availability will be published in the device's service.xml.
     * SetId must be overridden if this is called.
     */
    void EnableActionSetId();
    /**
     * Signal that the action Read is supported.
     * The action's availability will be published in the device's service.xml.
     * Read must be overridden if this is called.
     */
    void EnableActionRead();
    /**
     * Signal that the action ReadList is supported.
     * The action's availability will be published in the device's service.xml.
     * ReadList must be overridden if this is called.
     */
    void EnableActionReadList();
    /**
     * Signal that the action IdArray is supported.
     * The action's availability will be published in the device's service.xml.
     * IdArray must be overridden if this is called.
     */
    void EnableActionIdArray();
    /**
     * Signal that the action IdArrayChanged is supported.
     * The action's availability will be published in the device's service.xml.
     * IdArrayChanged must be overridden if this is called.
     */
    void EnableActionIdArrayChanged();
    /**
     * Signal that the action ChannelsMax is supported.
     * The action's availability will be published in the device's service.xml.
     * ChannelsMax must be overridden if this is called.
     */
    void EnableActionChannelsMax();
    /**
     * Signal that the action ProtocolInfo is supported.
     * The action's availability will be published in the device's service.xml.
     * ProtocolInfo must be overridden if this is called.
     */
    void EnableActionProtocolInfo();
private:
    /**
     * Play action.
     *
     * Will be called when the device stack receives an invocation of the
     * Play action for the owning device.
     * Must be implemented iff EnableActionPlay was called.
     */
    virtual void Play(IDvInvocationStd& aInvocation);
    /**
     * Pause action.
     *
     * Will be called when the device stack receives an invocation of the
     * Pause action for the owning device.
     * Must be implemented iff EnableActionPause was called.
     */
    virtual void Pause(IDvInvocationStd& aInvocation);
    /**
     * Stop action.
     *
     * Will be called when the device stack receives an invocation of the
     * Stop action for the owning device.
     * Must be implemented iff EnableActionStop was called.
     */
    virtual void Stop(IDvInvocationStd& aInvocation);
    /**
     * SeekSecondAbsolute action.
     *
     * Will be called when the device stack receives an invocation of the
     * SeekSecondAbsolute action for the owning device.
     * Must be implemented iff EnableActionSeekSecondAbsolute was called.
     */
    virtual void SeekSecondAbsolute(IDvInvocationStd& aInvocation, uint32_t aValue);
    /**
     * SeekSecondRelative action.
     *
     * Will be called when the device stack receives an invocation of the
     * SeekSecondRelative action for the owning device.
     * Must be implemented iff EnableActionSeekSecondRelative was called.
     */
    virtual void SeekSecondRelative(IDvInvocationStd& aInvocation, int32_t aValue);
    /**
     * Channel action.
     *
     * Will be called when the device stack receives an invocation of the
     * Channel action for the owning device.
     * Must be implemented iff EnableActionChannel was called.
     */
    virtual void Channel(IDvInvocationStd& aInvocation, std::string& aUri, std::string& aMetadata);
    /**
     * SetChannel action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetChannel action for the owning device.
     * Must be implemented iff EnableActionSetChannel was called.
     */
    virtual void SetChannel(IDvInvocationStd& aInvocation, const std::string& aUri, const std::string& aMetadata);
    /**
     * TransportState action.
     *
     * Will be called when the device stack receives an invocation of the
     * TransportState action for the owning device.
     * Must be implemented iff EnableActionTransportState was called.
     */
    virtual void TransportState(IDvInvocationStd& aInvocation, std::string& aValue);
    /**
     * Id action.
     *
     * Will be called when the device stack receives an invocation of the
     * Id action for the owning device.
     * Must be implemented iff EnableActionId was called.
     */
    virtual void Id(IDvInvocationStd& aInvocation, uint32_t& aValue);
    /**
     * SetId action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetId action for the owning device.
     * Must be implemented iff EnableActionSetId was called.
     */
    virtual void SetId(IDvInvocationStd& aInvocation, uint32_t aValue, const std::string& aUri);
    /**
     * Read action.
     *
     * Will be called when the device stack receives an invocation of the
     * Read action for the owning device.
     * Must be implemented iff EnableActionRead was called.
     */
    virtual void Read(IDvInvocationStd& aInvocation, uint32_t aId, std::string& aMetadata);
    /**
     * ReadList action.
     *
     * Will be called when the device stack receives an invocation of the
     * ReadList action for the owning device.
     * Must be implemented iff EnableActionReadList was called.
     */
    virtual void ReadList(IDvInvocationStd& aInvocation, const std::string& aIdList, std::string& aChannelList);
    /**
     * IdArray action.
     *
     * Will be called when the device stack receives an invocation of the
     * IdArray action for the owning device.
     * Must be implemented iff EnableActionIdArray was called.
     */
    virtual void IdArray(IDvInvocationStd& aInvocation, uint32_t& aToken, std::string& aArray);
    /**
     * IdArrayChanged action.
     *
     * Will be called when the device stack receives an invocation of the
     * IdArrayChanged action for the owning device.
     * Must be implemented iff EnableActionIdArrayChanged was called.
     */
    virtual void IdArrayChanged(IDvInvocationStd& aInvocation, uint32_t aToken, bool& aValue);
    /**
     * ChannelsMax action.
     *
     * Will be called when the device stack receives an invocation of the
     * ChannelsMax action for the owning device.
     * Must be implemented iff EnableActionChannelsMax was called.
     */
    virtual void ChannelsMax(IDvInvocationStd& aInvocation, uint32_t& aValue);
    /**
     * ProtocolInfo action.
     *
     * Will be called when the device stack receives an invocation of the
     * ProtocolInfo action for the owning device.
     * Must be implemented iff EnableActionProtocolInfo was called.
     */
    virtual void ProtocolInfo(IDvInvocationStd& aInvocation, std::string& aValue);
private:
    DvProviderAvOpenhomeOrgRadio1Cpp();
    void DoPlay(IDviInvocation& aInvocation);
    void DoPause(IDviInvocation& aInvocation);
    void DoStop(IDviInvocation& aInvocation);
    void DoSeekSecondAbsolute(IDviInvocation& aInvocation);
    void DoSeekSecondRelative(IDviInvocation& aInvocation);
    void DoChannel(IDviInvocation& aInvocation);
    void DoSetChannel(IDviInvocation& aInvocation);
    void DoTransportState(IDviInvocation& aInvocation);
    void DoId(IDviInvocation& aInvocation);
    void DoSetId(IDviInvocation& aInvocation);
    void DoRead(IDviInvocation& aInvocation);
    void DoReadList(IDviInvocation& aInvocation);
    void DoIdArray(IDviInvocation& aInvocation);
    void DoIdArrayChanged(IDviInvocation& aInvocation);
    void DoChannelsMax(IDviInvocation& aInvocation);
    void DoProtocolInfo(IDviInvocation& aInvocation);
private:
    PropertyString* iPropertyUri;
    PropertyString* iPropertyMetadata;
    PropertyString* iPropertyTransportState;
    PropertyUint* iPropertyId;
    PropertyBinary* iPropertyIdArray;
    PropertyUint* iPropertyChannelsMax;
    PropertyString* iPropertyProtocolInfo;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_DVAVOPENHOMEORGRADIO1CPP

