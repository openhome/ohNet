#ifndef HEADER_DVLINNCOUKPROXYMANAGER1
#define HEADER_DVLINNCOUKPROXYMANAGER1

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
 * Base Device for linn.co.uk:ProxyManager:1
 */
class DvProviderLinnCoUkProxyManager1 : public DvProvider
{
public:
    virtual ~DvProviderLinnCoUkProxyManager1() {}
    TBool SetPropertyKontrolProductConnected(const Brx& aValue);
    void GetPropertyKontrolProductConnected(Brhz& aValue);
    TBool SetPropertyKontrolProductComPort(TUint aValue);
    void GetPropertyKontrolProductComPort(TUint& aValue);
    TBool SetPropertyDiscPlayerConnected(const Brx& aValue);
    void GetPropertyDiscPlayerConnected(Brhz& aValue);
    TBool SetPropertyDiscPlayerComPort(TUint aValue);
    void GetPropertyDiscPlayerComPort(TUint& aValue);
protected:
    DvProviderLinnCoUkProxyManager1(DvDevice& aDevice);
    void EnableActionKontrolProductConnected();
    void EnableActionSetKontrolProductConnected();
    void EnableActionKontrolProductComPort();
    void EnableActionSetKontrolProductComPort();
    void EnableActionDiscPlayerConnected();
    void EnableActionSetDiscPlayerConnected();
    void EnableActionDiscPlayerComPort();
    void EnableActionSetDiscPlayerComPort();
    void EnableActionTestKontrolProductConnection();
    void EnableActionTestDiscPlayerConnection();
private:
    virtual void KontrolProductConnected(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaConnected);
    virtual void SetKontrolProductConnected(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaConnected);
    virtual void KontrolProductComPort(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaPort);
    virtual void SetKontrolProductComPort(IInvocationResponse& aResponse, TUint aVersion, TUint aaConnected);
    virtual void DiscPlayerConnected(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaConnected);
    virtual void SetDiscPlayerConnected(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaConnected);
    virtual void DiscPlayerComPort(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaPort);
    virtual void SetDiscPlayerComPort(IInvocationResponse& aResponse, TUint aVersion, TUint aaConnected);
    virtual void TestKontrolProductConnection(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaResult);
    virtual void TestDiscPlayerConnection(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaResult);
private:
    DvProviderLinnCoUkProxyManager1();
    void DoKontrolProductConnected(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetKontrolProductConnected(IDviInvocation& aInvocation, TUint aVersion);
    void DoKontrolProductComPort(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetKontrolProductComPort(IDviInvocation& aInvocation, TUint aVersion);
    void DoDiscPlayerConnected(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetDiscPlayerConnected(IDviInvocation& aInvocation, TUint aVersion);
    void DoDiscPlayerComPort(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetDiscPlayerComPort(IDviInvocation& aInvocation, TUint aVersion);
    void DoTestKontrolProductConnection(IDviInvocation& aInvocation, TUint aVersion);
    void DoTestDiscPlayerConnection(IDviInvocation& aInvocation, TUint aVersion);
private:
    PropertyString* iPropertyKontrolProductConnected;
    PropertyUint* iPropertyKontrolProductComPort;
    PropertyString* iPropertyDiscPlayerConnected;
    PropertyUint* iPropertyDiscPlayerComPort;
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKPROXYMANAGER1

