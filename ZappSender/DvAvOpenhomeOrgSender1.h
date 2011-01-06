#ifndef HEADER_DVAVOPENHOMEORGSENDER1
#define HEADER_DVAVOPENHOMEORGSENDER1

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
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyPresentationUrl(const Brx& aValue);
    /**
     * Get a copy of the value of the PresentationUrl property
     */
    void GetPropertyPresentationUrl(Brhz& aValue);
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
     * Set the value of the Audio property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyAudio(TBool aValue);
    /**
     * Get a copy of the value of the Audio property
     */
    void GetPropertyAudio(TBool& aValue);
    /**
     * Set the value of the Status property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyStatus(const Brx& aValue);
    /**
     * Get a copy of the value of the Status property
     */
    void GetPropertyStatus(Brhz& aValue);
    /**
     * Set the value of the Attributes property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyAttributes(const Brx& aValue);
    /**
     * Get a copy of the value of the Attributes property
     */
    void GetPropertyAttributes(Brhz& aValue);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderAvOpenhomeOrgSender1(DvDevice& aDevice);
    /**
     * Signal that the action PresentationUrl is supported.
     * The action's availability will be published in the device's service.xml.
     * DoPresentationUrl must be overridden if this is called.
     */
    void EnableActionPresentationUrl();
    /**
     * Signal that the action Metadata is supported.
     * The action's availability will be published in the device's service.xml.
     * DoMetadata must be overridden if this is called.
     */
    void EnableActionMetadata();
    /**
     * Signal that the action Audio is supported.
     * The action's availability will be published in the device's service.xml.
     * DoAudio must be overridden if this is called.
     */
    void EnableActionAudio();
    /**
     * Signal that the action Status is supported.
     * The action's availability will be published in the device's service.xml.
     * DoStatus must be overridden if this is called.
     */
    void EnableActionStatus();
    /**
     * Signal that the action Attributes is supported.
     * The action's availability will be published in the device's service.xml.
     * DoAttributes must be overridden if this is called.
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
    virtual void PresentationUrl(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aValue);
    /**
     * Metadata action.
     *
     * Will be called when the device stack receives an invocation of the
     * Metadata action for the owning device.
     * Must be implemented iff EnableActionMetadata was called.
     */
    virtual void Metadata(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aValue);
    /**
     * Audio action.
     *
     * Will be called when the device stack receives an invocation of the
     * Audio action for the owning device.
     * Must be implemented iff EnableActionAudio was called.
     */
    virtual void Audio(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aValue);
    /**
     * Status action.
     *
     * Will be called when the device stack receives an invocation of the
     * Status action for the owning device.
     * Must be implemented iff EnableActionStatus was called.
     */
    virtual void Status(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aValue);
    /**
     * Attributes action.
     *
     * Will be called when the device stack receives an invocation of the
     * Attributes action for the owning device.
     * Must be implemented iff EnableActionAttributes was called.
     */
    virtual void Attributes(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aValue);
private:
    DvProviderAvOpenhomeOrgSender1();
    void DoPresentationUrl(IDviInvocation& aInvocation, TUint aVersion);
    void DoMetadata(IDviInvocation& aInvocation, TUint aVersion);
    void DoAudio(IDviInvocation& aInvocation, TUint aVersion);
    void DoStatus(IDviInvocation& aInvocation, TUint aVersion);
    void DoAttributes(IDviInvocation& aInvocation, TUint aVersion);
private:
    PropertyString* iPropertyPresentationUrl;
    PropertyString* iPropertyMetadata;
    PropertyBool* iPropertyAudio;
    PropertyString* iPropertyStatus;
    PropertyString* iPropertyAttributes;
};

} // namespace Zapp

#endif // HEADER_DVAVOPENHOMEORGSENDER1

