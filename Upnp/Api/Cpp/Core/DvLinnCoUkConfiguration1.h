#ifndef HEADER_DVLINNCOUKCONFIGURATION1
#define HEADER_DVLINNCOUKCONFIGURATION1

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
 * Provider for the linn.co.uk:Configuration:1 UPnP service
 */
class DvProviderLinnCoUkConfiguration1 : public DvProvider
{
public:
    virtual ~DvProviderLinnCoUkConfiguration1() {}
    /**
     * Set the value of the ConfigurationXml property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyConfigurationXml(const Brx& aValue);
    /**
     * Get a copy of the value of the ConfigurationXml property
     */
    void GetPropertyConfigurationXml(Brhz& aValue);
    /**
     * Set the value of the ParameterXml property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyParameterXml(const Brx& aValue);
    /**
     * Get a copy of the value of the ParameterXml property
     */
    void GetPropertyParameterXml(Brhz& aValue);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderLinnCoUkConfiguration1(DvDevice& aDevice);
    /**
     * Signal that the action ConfigurationXml is supported.
     * The action's availability will be published in the device's service.xml.
     * DoConfigurationXml must be overridden if this is called.
     */
    void EnableActionConfigurationXml();
    /**
     * Signal that the action ParameterXml is supported.
     * The action's availability will be published in the device's service.xml.
     * DoParameterXml must be overridden if this is called.
     */
    void EnableActionParameterXml();
    /**
     * Signal that the action SetParameter is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetParameter must be overridden if this is called.
     */
    void EnableActionSetParameter();
private:
    /**
     * ConfigurationXml action.
     *
     * Will be called when the device stack receives an invocation of the
     * ConfigurationXml action for the owning device.
     * Must be implemented iff EnableActionConfigurationXml was called.
     */
    virtual void ConfigurationXml(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaConfigurationXml);
    /**
     * ParameterXml action.
     *
     * Will be called when the device stack receives an invocation of the
     * ParameterXml action for the owning device.
     * Must be implemented iff EnableActionParameterXml was called.
     */
    virtual void ParameterXml(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaParameterXml);
    /**
     * SetParameter action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetParameter action for the owning device.
     * Must be implemented iff EnableActionSetParameter was called.
     */
    virtual void SetParameter(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaTarget, const Brx& aaName, const Brx& aaValue);
private:
    DvProviderLinnCoUkConfiguration1();
    void DoConfigurationXml(IDviInvocation& aInvocation, TUint aVersion);
    void DoParameterXml(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetParameter(IDviInvocation& aInvocation, TUint aVersion);
private:
    PropertyString* iPropertyConfigurationXml;
    PropertyString* iPropertyParameterXml;
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKCONFIGURATION1

