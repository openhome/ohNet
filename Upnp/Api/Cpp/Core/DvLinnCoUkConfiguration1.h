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
 * Base Device for linn.co.uk:Configuration:1
 */
class DvProviderLinnCoUkConfiguration1 : public DvProvider
{
public:
    virtual ~DvProviderLinnCoUkConfiguration1() {}
    TBool SetPropertyConfigurationXml(const Brx& aValue);
    void GetPropertyConfigurationXml(Brhz& aValue);
    TBool SetPropertyParameterXml(const Brx& aValue);
    void GetPropertyParameterXml(Brhz& aValue);
protected:
    DvProviderLinnCoUkConfiguration1(DvDevice& aDevice);
    void EnableActionConfigurationXml();
    void EnableActionParameterXml();
    void EnableActionSetParameter();
private:
    virtual void ConfigurationXml(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaConfigurationXml);
    virtual void ParameterXml(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaParameterXml);
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

