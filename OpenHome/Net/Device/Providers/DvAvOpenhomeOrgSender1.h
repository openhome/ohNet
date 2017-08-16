#ifndef HEADER_DVAVOPENHOMEORGSENDER1
#define HEADER_DVAVOPENHOMEORGSENDER1

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Core/DvDevice.h>
#include <OpenHome/Net/Core/DvProvider.h>

namespace OpenHome {
namespace Net {

class DviDevice;
class IDviInvocation;
class PropertyInt;
class PropertyUint;
class PropertyBool;
class PropertyString;
class PropertyBinary;

/**
 * Provider for the av.openhome.org:Sender:1 UPnP service
 * @ingroup Providers
 */
class DvProviderAvOpenhomeOrgSender1 : public DvProvider
{
public:
    virtual ~DvProviderAvOpenhomeOrgSender1() {}
    /**
     * Set the value of the PresentationUrl property
     *
     * Can only be called if EnablePropertyPresentationUrl has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyPresentationUrl(const Brx& aValue);
    /**
     * Get a copy of the value of the PresentationUrl property
     *
     * Can only be called if EnablePropertyPresentationUrl has previously been called.
     */
    void GetPropertyPresentationUrl(Brhz& aValue);
    /**
     * Output the value of the PresentationUrl property without an intermediate copy.
     *
     * Can only be called if EnablePropertyPresentationUrl has previously been called.
     */
    void WritePropertyPresentationUrl(IWriter& aWriter);
    /**
     * Set the value of the Metadata property
     *
     * Can only be called if EnablePropertyMetadata has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyMetadata(const Brx& aValue);
    /**
     * Get a copy of the value of the Metadata property
     *
     * Can only be called if EnablePropertyMetadata has previously been called.
     */
    void GetPropertyMetadata(Brhz& aValue);
    /**
     * Output the value of the Metadata property without an intermediate copy.
     *
     * Can only be called if EnablePropertyMetadata has previously been called.
     */
    void WritePropertyMetadata(IWriter& aWriter);
    /**
     * Set the value of the Audio property
     *
     * Can only be called if EnablePropertyAudio has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyAudio(TBool aValue);
    /**
     * Get a copy of the value of the Audio property
     *
     * Can only be called if EnablePropertyAudio has previously been called.
     */
    void GetPropertyAudio(TBool& aValue);
    /**
     * Set the value of the Status property
     *
     * Can only be called if EnablePropertyStatus has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyStatus(const Brx& aValue);
    /**
     * Get a copy of the value of the Status property
     *
     * Can only be called if EnablePropertyStatus has previously been called.
     */
    void GetPropertyStatus(Brhz& aValue);
    /**
     * Output the value of the Status property without an intermediate copy.
     *
     * Can only be called if EnablePropertyStatus has previously been called.
     */
    void WritePropertyStatus(IWriter& aWriter);
    /**
     * Set the value of the Attributes property
     *
     * Can only be called if EnablePropertyAttributes has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyAttributes(const Brx& aValue);
    /**
     * Get a copy of the value of the Attributes property
     *
     * Can only be called if EnablePropertyAttributes has previously been called.
     */
    void GetPropertyAttributes(Brhz& aValue);
    /**
     * Output the value of the Attributes property without an intermediate copy.
     *
     * Can only be called if EnablePropertyAttributes has previously been called.
     */
    void WritePropertyAttributes(IWriter& aWriter);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderAvOpenhomeOrgSender1(DvDevice& aDevice);
    /**
     * Constructor.  Not for external use.
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderAvOpenhomeOrgSender1(DviDevice& aDevice);
    /**
     * Enable the PresentationUrl property.
     */
    void EnablePropertyPresentationUrl();
    /**
     * Enable the Metadata property.
     */
    void EnablePropertyMetadata();
    /**
     * Enable the Audio property.
     */
    void EnablePropertyAudio();
    /**
     * Enable the Status property.
     */
    void EnablePropertyStatus();
    /**
     * Enable the Attributes property.
     */
    void EnablePropertyAttributes();
    /**
     * Signal that the action PresentationUrl is supported.
     * The action's availability will be published in the device's service.xml.
     * PresentationUrl must be overridden if this is called.
     */
    void EnableActionPresentationUrl();
    /**
     * Signal that the action Metadata is supported.
     * The action's availability will be published in the device's service.xml.
     * Metadata must be overridden if this is called.
     */
    void EnableActionMetadata();
    /**
     * Signal that the action Audio is supported.
     * The action's availability will be published in the device's service.xml.
     * Audio must be overridden if this is called.
     */
    void EnableActionAudio();
    /**
     * Signal that the action Status is supported.
     * The action's availability will be published in the device's service.xml.
     * Status must be overridden if this is called.
     */
    void EnableActionStatus();
    /**
     * Signal that the action Attributes is supported.
     * The action's availability will be published in the device's service.xml.
     * Attributes must be overridden if this is called.
     */
    void EnableActionAttributes();
private:
    /**
     * PresentationUrl action.
     *
     * Will be called when the device stack receives an invocation of the
     * PresentationUrl action for the owning device.
     * Must be implemented iff EnableActionPresentationUrl was called.
     */
    virtual void PresentationUrl(IDvInvocation& aInvocation, IDvInvocationResponseString& aValue);
    /**
     * Metadata action.
     *
     * Will be called when the device stack receives an invocation of the
     * Metadata action for the owning device.
     * Must be implemented iff EnableActionMetadata was called.
     */
    virtual void Metadata(IDvInvocation& aInvocation, IDvInvocationResponseString& aValue);
    /**
     * Audio action.
     *
     * Will be called when the device stack receives an invocation of the
     * Audio action for the owning device.
     * Must be implemented iff EnableActionAudio was called.
     */
    virtual void Audio(IDvInvocation& aInvocation, IDvInvocationResponseBool& aValue);
    /**
     * Status action.
     *
     * Will be called when the device stack receives an invocation of the
     * Status action for the owning device.
     * Must be implemented iff EnableActionStatus was called.
     */
    virtual void Status(IDvInvocation& aInvocation, IDvInvocationResponseString& aValue);
    /**
     * Attributes action.
     *
     * Will be called when the device stack receives an invocation of the
     * Attributes action for the owning device.
     * Must be implemented iff EnableActionAttributes was called.
     */
    virtual void Attributes(IDvInvocation& aInvocation, IDvInvocationResponseString& aValue);
private:
    DvProviderAvOpenhomeOrgSender1();
    void Construct();
    void DoPresentationUrl(IDviInvocation& aInvocation);
    void DoMetadata(IDviInvocation& aInvocation);
    void DoAudio(IDviInvocation& aInvocation);
    void DoStatus(IDviInvocation& aInvocation);
    void DoAttributes(IDviInvocation& aInvocation);
private:
    PropertyString* iPropertyPresentationUrl;
    PropertyString* iPropertyMetadata;
    PropertyBool* iPropertyAudio;
    PropertyString* iPropertyStatus;
    PropertyString* iPropertyAttributes;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_DVAVOPENHOMEORGSENDER1

