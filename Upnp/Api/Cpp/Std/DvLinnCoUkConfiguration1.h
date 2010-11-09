#ifndef HEADER_DVLINNCOUKCONFIGURATION1CPP
#define HEADER_DVLINNCOUKCONFIGURATION1CPP

#include <ZappTypes.h>
#include <Buffer.h>
#include <Std/DvDevice.h>
#include <DvProvider.h>

#include <string>

namespace Zapp {

class IDvInvocation;
class PropertyInt;
class PropertyUint;
class PropertyBool;
class PropertyString;
class PropertyBinary;

/**
 * Base Device for linn.co.uk:Configuration:1
 */
class DvProviderLinnCoUkConfiguration1Cpp : public DvProvider
{
public:
    virtual ~DvProviderLinnCoUkConfiguration1Cpp() {}
    bool SetPropertyConfigurationXml(const std::string& aValue);
    void GetPropertyConfigurationXml(std::string& aValue);
    bool SetPropertyParameterXml(const std::string& aValue);
    void GetPropertyParameterXml(std::string& aValue);
protected:
    DvProviderLinnCoUkConfiguration1Cpp(DvDeviceStd& aDevice);
    void EnableActionConfigurationXml();
    void EnableActionParameterXml();
    void EnableActionSetParameter();
private:
    virtual void ConfigurationXml(uint32_t aVersion, std::string& aaConfigurationXml);
    virtual void ParameterXml(uint32_t aVersion, std::string& aaParameterXml);
    virtual void SetParameter(uint32_t aVersion, const std::string& aaTarget, const std::string& aaName, const std::string& aaValue);
private:
    DvProviderLinnCoUkConfiguration1Cpp();
    void DoConfigurationXml(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoParameterXml(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetParameter(IDvInvocation& aInvocation, uint32_t aVersion);
private:
    PropertyString* iPropertyConfigurationXml;
    PropertyString* iPropertyParameterXml;
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKCONFIGURATION1CPP

