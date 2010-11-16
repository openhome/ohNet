#ifndef HEADER_DVLINNCOUKPROXYMANAGER1CPP
#define HEADER_DVLINNCOUKPROXYMANAGER1CPP

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
 * Base Device for linn.co.uk:ProxyManager:1
 */
class DvProviderLinnCoUkProxyManager1Cpp : public DvProvider
{
public:
    virtual ~DvProviderLinnCoUkProxyManager1Cpp() {}
    bool SetPropertyKontrolProductConnected(const std::string& aValue);
    void GetPropertyKontrolProductConnected(std::string& aValue);
    bool SetPropertyKontrolProductComPort(uint32_t aValue);
    void GetPropertyKontrolProductComPort(uint32_t& aValue);
    bool SetPropertyDiscPlayerConnected(const std::string& aValue);
    void GetPropertyDiscPlayerConnected(std::string& aValue);
    bool SetPropertyDiscPlayerComPort(uint32_t aValue);
    void GetPropertyDiscPlayerComPort(uint32_t& aValue);
protected:
    DvProviderLinnCoUkProxyManager1Cpp(DvDeviceStd& aDevice);
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
    virtual void KontrolProductConnected(uint32_t aVersion, std::string& aaConnected);
    virtual void SetKontrolProductConnected(uint32_t aVersion, const std::string& aaConnected);
    virtual void KontrolProductComPort(uint32_t aVersion, uint32_t& aaPort);
    virtual void SetKontrolProductComPort(uint32_t aVersion, uint32_t aaConnected);
    virtual void DiscPlayerConnected(uint32_t aVersion, std::string& aaConnected);
    virtual void SetDiscPlayerConnected(uint32_t aVersion, const std::string& aaConnected);
    virtual void DiscPlayerComPort(uint32_t aVersion, uint32_t& aaPort);
    virtual void SetDiscPlayerComPort(uint32_t aVersion, uint32_t aaConnected);
    virtual void TestKontrolProductConnection(uint32_t aVersion, bool& aaResult);
    virtual void TestDiscPlayerConnection(uint32_t aVersion, bool& aaResult);
private:
    DvProviderLinnCoUkProxyManager1Cpp();
    void DoKontrolProductConnected(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetKontrolProductConnected(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoKontrolProductComPort(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetKontrolProductComPort(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoDiscPlayerConnected(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetDiscPlayerConnected(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoDiscPlayerComPort(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetDiscPlayerComPort(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoTestKontrolProductConnection(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoTestDiscPlayerConnection(IDviInvocation& aInvocation, uint32_t aVersion);
private:
    PropertyString* iPropertyKontrolProductConnected;
    PropertyUint* iPropertyKontrolProductComPort;
    PropertyString* iPropertyDiscPlayerConnected;
    PropertyUint* iPropertyDiscPlayerComPort;
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKPROXYMANAGER1CPP

