#ifndef HEADER_DVLINNCOUKPROXYMANAGER1
#define HEADER_DVLINNCOUKPROXYMANAGER1

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
 * Base Device for linn.co.uk:ProxyManager:1
 */
class DvServiceLinnCoUkProxyManager1 : public DvService
{
public:
    virtual ~DvServiceLinnCoUkProxyManager1() {}
    void SetPropertyKontrolProductConnected(const Brx& aValue);
    void GetPropertyKontrolProductConnected(Brhz& aValue);
    void SetPropertyKontrolProductComPort(TUint aValue);
    void GetPropertyKontrolProductComPort(TUint& aValue);
    void SetPropertyDiscPlayerConnected(const Brx& aValue);
    void GetPropertyDiscPlayerConnected(Brhz& aValue);
    void SetPropertyDiscPlayerComPort(TUint aValue);
    void GetPropertyDiscPlayerComPort(TUint& aValue);
protected:
    DvServiceLinnCoUkProxyManager1(DvDevice& aDevice);
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
    DvServiceLinnCoUkProxyManager1();
    void DoKontrolProductConnected(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetKontrolProductConnected(IDvInvocation& aInvocation, TUint aVersion);
    void DoKontrolProductComPort(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetKontrolProductComPort(IDvInvocation& aInvocation, TUint aVersion);
    void DoDiscPlayerConnected(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetDiscPlayerConnected(IDvInvocation& aInvocation, TUint aVersion);
    void DoDiscPlayerComPort(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetDiscPlayerComPort(IDvInvocation& aInvocation, TUint aVersion);
    void DoTestKontrolProductConnection(IDvInvocation& aInvocation, TUint aVersion);
    void DoTestDiscPlayerConnection(IDvInvocation& aInvocation, TUint aVersion);
private:
    PropertyString* iPropertyKontrolProductConnected;
    PropertyUint* iPropertyKontrolProductComPort;
    PropertyString* iPropertyDiscPlayerConnected;
    PropertyUint* iPropertyDiscPlayerComPort;
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKPROXYMANAGER1

