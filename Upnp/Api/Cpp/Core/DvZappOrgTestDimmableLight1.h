#ifndef HEADER_DVZAPPORGTESTDIMMABLELIGHT1
#define HEADER_DVZAPPORGTESTDIMMABLELIGHT1

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
 * Base Device for zapp.org:TestDimmableLight:1
 */
class DvProviderZappOrgTestDimmableLight1 : public DvProvider
{
public:
    virtual ~DvProviderZappOrgTestDimmableLight1() {}
    TBool SetPropertyA_ARG_Level(TUint aValue);
    void GetPropertyA_ARG_Level(TUint& aValue);
protected:
    DvProviderZappOrgTestDimmableLight1(DvDevice& aDevice);
    void EnableActionGetLevel();
    void EnableActionSetLevel();
private:
    virtual void GetLevel(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aLevel);
    virtual void SetLevel(IInvocationResponse& aResponse, TUint aVersion, TUint aLevel);
private:
    DvProviderZappOrgTestDimmableLight1();
    void DoGetLevel(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetLevel(IDviInvocation& aInvocation, TUint aVersion);
private:
    PropertyUint* iPropertyA_ARG_Level;
};

} // namespace Zapp

#endif // HEADER_DVZAPPORGTESTDIMMABLELIGHT1

