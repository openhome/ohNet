#ifndef HEADER_DVAVOPENHOMEORGRADIO1CPP
#define HEADER_DVAVOPENHOMEORGRADIO1CPP

#include <OhNetTypes.h>
#include <Buffer.h>
#include <Std/DvDevice.h>
#include <DvProvider.h>

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
     * Set the value of the Id property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyId(uint32_t aValue);
    /**
     * Get a copy of the value of the Id property
     */
    void GetPropertyId(uint32_t& aValue);
    /**
     * Set the value of the IdArray property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyIdArray(const std::string& aValue);
    /**
     * Get a copy of the value of the IdArray property
     */
    void GetPropertyIdArray(std::string& aValue);
    /**
     * Set the value of the ChannelsMax property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyChannelsMax(uint32_t aValue);
    /**
     * Get a copy of the value of the ChannelsMax property
     */
    void GetPropertyChannelsMax(uint32_t& aValue);
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
    DvProviderAvOpenhomeOrgRadio1Cpp(DvDeviceStd& aDevice);
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
    virtual void Play(uint32_t aVersion);
    /**
     * Pause action.
     *
     * Will be called when the device stack receives an invocation of the
     * Pause action for the owning device.
     * Must be implemented iff EnableActionPause was called.
     */
    virtual void Pause(uint32_t aVersion);
    /**
     * Stop action.
     *
     * Will be called when the device stack receives an invocation of the
     * Stop action for the owning device.
     * Must be implemented iff EnableActionStop was called.
     */
    virtual void Stop(uint32_t aVersion);
    /**
     * SeekSecondAbsolute action.
     *
     * Will be called when the device stack receives an invocation of the
     * SeekSecondAbsolute action for the owning device.
     * Must be implemented iff EnableActionSeekSecondAbsolute was called.
     */
    virtual void SeekSecondAbsolute(uint32_t aVersion, uint32_t aValue);
    /**
     * SeekSecondRelative action.
     *
     * Will be called when the device stack receives an invocation of the
     * SeekSecondRelative action for the owning device.
     * Must be implemented iff EnableActionSeekSecondRelative was called.
     */
    virtual void SeekSecondRelative(uint32_t aVersion, int32_t aValue);
    /**
     * Channel action.
     *
     * Will be called when the device stack receives an invocation of the
     * Channel action for the owning device.
     * Must be implemented iff EnableActionChannel was called.
     */
    virtual void Channel(uint32_t aVersion, std::string& aUri, std::string& aMetadata);
    /**
     * SetChannel action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetChannel action for the owning device.
     * Must be implemented iff EnableActionSetChannel was called.
     */
    virtual void SetChannel(uint32_t aVersion, const std::string& aUri, const std::string& aMetadata);
    /**
     * TransportState action.
     *
     * Will be called when the device stack receives an invocation of the
     * TransportState action for the owning device.
     * Must be implemented iff EnableActionTransportState was called.
     */
    virtual void TransportState(uint32_t aVersion, std::string& aValue);
    /**
     * Id action.
     *
     * Will be called when the device stack receives an invocation of the
     * Id action for the owning device.
     * Must be implemented iff EnableActionId was called.
     */
    virtual void Id(uint32_t aVersion, uint32_t& aValue);
    /**
     * SetId action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetId action for the owning device.
     * Must be implemented iff EnableActionSetId was called.
     */
    virtual void SetId(uint32_t aVersion, uint32_t aValue, const std::string& aUri);
    /**
     * Read action.
     *
     * Will be called when the device stack receives an invocation of the
     * Read action for the owning device.
     * Must be implemented iff EnableActionRead was called.
     */
    virtual void Read(uint32_t aVersion, uint32_t aId, std::string& aMetadata);
    /**
     * ReadList action.
     *
     * Will be called when the device stack receives an invocation of the
     * ReadList action for the owning device.
     * Must be implemented iff EnableActionReadList was called.
     */
    virtual void ReadList(uint32_t aVersion, const std::string& aIdList, std::string& aChannelList);
    /**
     * IdArray action.
     *
     * Will be called when the device stack receives an invocation of the
     * IdArray action for the owning device.
     * Must be implemented iff EnableActionIdArray was called.
     */
    virtual void IdArray(uint32_t aVersion, uint32_t& aToken, std::string& aArray);
    /**
     * IdArrayChanged action.
     *
     * Will be called when the device stack receives an invocation of the
     * IdArrayChanged action for the owning device.
     * Must be implemented iff EnableActionIdArrayChanged was called.
     */
    virtual void IdArrayChanged(uint32_t aVersion, uint32_t aToken, bool& aValue);
    /**
     * ChannelsMax action.
     *
     * Will be called when the device stack receives an invocation of the
     * ChannelsMax action for the owning device.
     * Must be implemented iff EnableActionChannelsMax was called.
     */
    virtual void ChannelsMax(uint32_t aVersion, uint32_t& aValue);
    /**
     * ProtocolInfo action.
     *
     * Will be called when the device stack receives an invocation of the
     * ProtocolInfo action for the owning device.
     * Must be implemented iff EnableActionProtocolInfo was called.
     */
    virtual void ProtocolInfo(uint32_t aVersion, std::string& aValue);
private:
    DvProviderAvOpenhomeOrgRadio1Cpp();
    void DoPlay(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoPause(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoStop(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSeekSecondAbsolute(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSeekSecondRelative(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoChannel(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetChannel(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoTransportState(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoId(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetId(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoRead(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoReadList(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoIdArray(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoIdArrayChanged(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoChannelsMax(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoProtocolInfo(IDviInvocation& aInvocation, uint32_t aVersion);
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

