#ifndef HEADER_DVLINNCOUKCONFIGURATION1
#define HEADER_DVLINNCOUKCONFIGURATION1

#include <ZappTypes.h>
#include <Buffer.h>
#include <Core/DvDevice.h>
#include <DvService.h>

namespace Zapp {

class PropertyInt;
class PropertyUint;
class PropertyBool;
class PropertyString;
class PropertyBinary;

/**
 * Base Device for linn.co.uk:Configuration:1
 */
class DvServiceLinnCoUkConfiguration1 : public DvService
{
public:
    virtual ~DvServiceLinnCoUkConfiguration1() {}
    void SetPropertyConfigurationXml(const Brx& aValue);
    void GetPropertyConfigurationXml(Brhz& aValue);
    void SetPropertyParameterXml(const Brx& aValue);
    void GetPropertyParameterXml(Brhz& aValue);
protected:
    DvServiceLinnCoUkConfiguration1(DvDevice& aDevice);
    void EnableActionConfigurationXml();
    void EnableActionParameterXml();
    void EnableActionSetParameter();
private:
    virtual void ConfigurationXml(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaConfigurationXml);
    virtual void ParameterXml(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaParameterXml);
    virtual void SetParameter(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaTarget, const Brx& aaName, const Brx& aaValue);
private:
    DvServiceLinnCoUkConfiguration1();
    void DoConfigurationXml(IDvInvocation& aInvocation, TUint aVersion);
    void DoParameterXml(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetParameter(IDvInvocation& aInvocation, TUint aVersion);
private:
    PropertyString* iPropertyConfigurationXml;
    PropertyString* iPropertyParameterXml;
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKCONFIGURATION1

