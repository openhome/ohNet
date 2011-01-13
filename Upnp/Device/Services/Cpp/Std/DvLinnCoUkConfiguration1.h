#ifndef HEADER_DVLINNCOUKCONFIGURATION1CPP
#define HEADER_DVLINNCOUKCONFIGURATION1CPP

#include <ZappTypes.h>
#include <Buffer.h>
#include <Std/DvDevice.h>
#include <DvProvider.h>

#include <string>

namespace Zapp {

class IDviInvocation;
class PropertyInt;
class PropertyUint;
class PropertyBool;
class PropertyString;
class PropertyBinary;

/**
 * Provider for the linn.co.uk:Configuration:1 UPnP service
 * @ingroup Providers
 */
class DvProviderLinnCoUkConfiguration1Cpp : public DvProvider
{
public:
    virtual ~DvProviderLinnCoUkConfiguration1Cpp() {}
    /**
     * Set the value of the ConfigurationXml property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyConfigurationXml(const std::string& aValue);
    /**
     * Get a copy of the value of the ConfigurationXml property
     */
    void GetPropertyConfigurationXml(std::string& aValue);
    /**
     * Set the value of the ParameterXml property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyParameterXml(const std::string& aValue);
    /**
     * Get a copy of the value of the ParameterXml property
     */
    void GetPropertyParameterXml(std::string& aValue);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderLinnCoUkConfiguration1Cpp(DvDeviceStd& aDevice);
    /**
     * Signal that the action ConfigurationXml is supported.
     * The action's availability will be published in the device's service.xml.
     * ConfigurationXml must be overridden if this is called.
     */
    void EnableActionConfigurationXml();
    /**
     * Signal that the action ParameterXml is supported.
     * The action's availability will be published in the device's service.xml.
     * ParameterXml must be overridden if this is called.
     */
    void EnableActionParameterXml();
    /**
     * Signal that the action SetParameter is supported.
     * The action's availability will be published in the device's service.xml.
     * SetParameter must be overridden if this is called.
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
    virtual void ConfigurationXml(uint32_t aVersion, std::string& aaConfigurationXml);
    /**
     * ParameterXml action.
     *
     * Will be called when the device stack receives an invocation of the
     * ParameterXml action for the owning device.
     * Must be implemented iff EnableActionParameterXml was called.
     */
    virtual void ParameterXml(uint32_t aVersion, std::string& aaParameterXml);
    /**
     * SetParameter action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetParameter action for the owning device.
     * Must be implemented iff EnableActionSetParameter was called.
     */
    virtual void SetParameter(uint32_t aVersion, const std::string& aaTarget, const std::string& aaName, const std::string& aaValue);
private:
    DvProviderLinnCoUkConfiguration1Cpp();
    void DoConfigurationXml(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoParameterXml(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetParameter(IDviInvocation& aInvocation, uint32_t aVersion);
private:
    PropertyString* iPropertyConfigurationXml;
    PropertyString* iPropertyParameterXml;
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKCONFIGURATION1CPP

