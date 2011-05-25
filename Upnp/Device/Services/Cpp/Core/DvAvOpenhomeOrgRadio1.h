#ifndef HEADER_DVAVOPENHOMEORGRADIO1
#define HEADER_DVAVOPENHOMEORGRADIO1

#include <OhNetTypes.h>
#include <Buffer.h>
#include <Core/DvDevice.h>
#include <DvProvider.h>

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
class DvProviderAvOpenhomeOrgRadio1 : public DvProvider
{
public:
    virtual ~DvProviderAvOpenhomeOrgRadio1() {}
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
     * Set the value of the Id property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyId(TUint aValue);
    /**
     * Get a copy of the value of the Id property
     */
    void GetPropertyId(TUint& aValue);
    /**
     * Set the value of the IdArray property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyIdArray(const Brx& aValue);
    /**
     * Get a copy of the value of the IdArray property
     */
    void GetPropertyIdArray(Brh& aValue);
    /**
     * Set the value of the ChannelsMax property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyChannelsMax(TUint aValue);
    /**
     * Get a copy of the value of the ChannelsMax property
     */
    void GetPropertyChannelsMax(TUint& aValue);
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
    DvProviderAvOpenhomeOrgRadio1(DvDevice& aDevice);
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
    virtual void Play(IInvocationResponse& aResponse, TUint aVersion);
    /**
     * Pause action.
     *
     * Will be called when the device stack receives an invocation of the
     * Pause action for the owning device.
     * Must be implemented iff EnableActionPause was called.
     */
    virtual void Pause(IInvocationResponse& aResponse, TUint aVersion);
    /**
     * Stop action.
     *
     * Will be called when the device stack receives an invocation of the
     * Stop action for the owning device.
     * Must be implemented iff EnableActionStop was called.
     */
    virtual void Stop(IInvocationResponse& aResponse, TUint aVersion);
    /**
     * SeekSecondAbsolute action.
     *
     * Will be called when the device stack receives an invocation of the
     * SeekSecondAbsolute action for the owning device.
     * Must be implemented iff EnableActionSeekSecondAbsolute was called.
     */
    virtual void SeekSecondAbsolute(IInvocationResponse& aResponse, TUint aVersion, TUint aValue);
    /**
     * SeekSecondRelative action.
     *
     * Will be called when the device stack receives an invocation of the
     * SeekSecondRelative action for the owning device.
     * Must be implemented iff EnableActionSeekSecondRelative was called.
     */
    virtual void SeekSecondRelative(IInvocationResponse& aResponse, TUint aVersion, TInt aValue);
    /**
     * Channel action.
     *
     * Will be called when the device stack receives an invocation of the
     * Channel action for the owning device.
     * Must be implemented iff EnableActionChannel was called.
     */
    virtual void Channel(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aUri, IInvocationResponseString& aMetadata);
    /**
     * SetChannel action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetChannel action for the owning device.
     * Must be implemented iff EnableActionSetChannel was called.
     */
    virtual void SetChannel(IInvocationResponse& aResponse, TUint aVersion, const Brx& aUri, const Brx& aMetadata);
    /**
     * TransportState action.
     *
     * Will be called when the device stack receives an invocation of the
     * TransportState action for the owning device.
     * Must be implemented iff EnableActionTransportState was called.
     */
    virtual void TransportState(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aValue);
    /**
     * Id action.
     *
     * Will be called when the device stack receives an invocation of the
     * Id action for the owning device.
     * Must be implemented iff EnableActionId was called.
     */
    virtual void Id(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aValue);
    /**
     * SetId action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetId action for the owning device.
     * Must be implemented iff EnableActionSetId was called.
     */
    virtual void SetId(IInvocationResponse& aResponse, TUint aVersion, TUint aValue, const Brx& aUri);
    /**
     * Read action.
     *
     * Will be called when the device stack receives an invocation of the
     * Read action for the owning device.
     * Must be implemented iff EnableActionRead was called.
     */
    virtual void Read(IInvocationResponse& aResponse, TUint aVersion, TUint aId, IInvocationResponseString& aMetadata);
    /**
     * ReadList action.
     *
     * Will be called when the device stack receives an invocation of the
     * ReadList action for the owning device.
     * Must be implemented iff EnableActionReadList was called.
     */
    virtual void ReadList(IInvocationResponse& aResponse, TUint aVersion, const Brx& aIdList, IInvocationResponseString& aChannelList);
    /**
     * IdArray action.
     *
     * Will be called when the device stack receives an invocation of the
     * IdArray action for the owning device.
     * Must be implemented iff EnableActionIdArray was called.
     */
    virtual void IdArray(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aToken, IInvocationResponseBinary& aArray);
    /**
     * IdArrayChanged action.
     *
     * Will be called when the device stack receives an invocation of the
     * IdArrayChanged action for the owning device.
     * Must be implemented iff EnableActionIdArrayChanged was called.
     */
    virtual void IdArrayChanged(IInvocationResponse& aResponse, TUint aVersion, TUint aToken, IInvocationResponseBool& aValue);
    /**
     * ChannelsMax action.
     *
     * Will be called when the device stack receives an invocation of the
     * ChannelsMax action for the owning device.
     * Must be implemented iff EnableActionChannelsMax was called.
     */
    virtual void ChannelsMax(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aValue);
    /**
     * ProtocolInfo action.
     *
     * Will be called when the device stack receives an invocation of the
     * ProtocolInfo action for the owning device.
     * Must be implemented iff EnableActionProtocolInfo was called.
     */
    virtual void ProtocolInfo(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aValue);
private:
    DvProviderAvOpenhomeOrgRadio1();
    void DoPlay(IDviInvocation& aInvocation, TUint aVersion);
    void DoPause(IDviInvocation& aInvocation, TUint aVersion);
    void DoStop(IDviInvocation& aInvocation, TUint aVersion);
    void DoSeekSecondAbsolute(IDviInvocation& aInvocation, TUint aVersion);
    void DoSeekSecondRelative(IDviInvocation& aInvocation, TUint aVersion);
    void DoChannel(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetChannel(IDviInvocation& aInvocation, TUint aVersion);
    void DoTransportState(IDviInvocation& aInvocation, TUint aVersion);
    void DoId(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetId(IDviInvocation& aInvocation, TUint aVersion);
    void DoRead(IDviInvocation& aInvocation, TUint aVersion);
    void DoReadList(IDviInvocation& aInvocation, TUint aVersion);
    void DoIdArray(IDviInvocation& aInvocation, TUint aVersion);
    void DoIdArrayChanged(IDviInvocation& aInvocation, TUint aVersion);
    void DoChannelsMax(IDviInvocation& aInvocation, TUint aVersion);
    void DoProtocolInfo(IDviInvocation& aInvocation, TUint aVersion);
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

#endif // HEADER_DVAVOPENHOMEORGRADIO1

