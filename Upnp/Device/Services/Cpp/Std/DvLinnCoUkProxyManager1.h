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
 * Provider for the linn.co.uk:ProxyManager:1 UPnP service
 * @ingroup Providers
 */
class DvProviderLinnCoUkProxyManager1Cpp : public DvProvider
{
public:
    virtual ~DvProviderLinnCoUkProxyManager1Cpp() {}
    /**
     * Set the value of the KontrolProductConnected property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyKontrolProductConnected(const std::string& aValue);
    /**
     * Get a copy of the value of the KontrolProductConnected property
     */
    void GetPropertyKontrolProductConnected(std::string& aValue);
    /**
     * Set the value of the KontrolProductComPort property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyKontrolProductComPort(uint32_t aValue);
    /**
     * Get a copy of the value of the KontrolProductComPort property
     */
    void GetPropertyKontrolProductComPort(uint32_t& aValue);
    /**
     * Set the value of the DiscPlayerConnected property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyDiscPlayerConnected(const std::string& aValue);
    /**
     * Get a copy of the value of the DiscPlayerConnected property
     */
    void GetPropertyDiscPlayerConnected(std::string& aValue);
    /**
     * Set the value of the DiscPlayerComPort property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyDiscPlayerComPort(uint32_t aValue);
    /**
     * Get a copy of the value of the DiscPlayerComPort property
     */
    void GetPropertyDiscPlayerComPort(uint32_t& aValue);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderLinnCoUkProxyManager1Cpp(DvDeviceStd& aDevice);
    /**
     * Signal that the action KontrolProductConnected is supported.
     * The action's availability will be published in the device's service.xml.
     * DoKontrolProductConnected must be overridden if this is called.
     */
    void EnableActionKontrolProductConnected();
    /**
     * Signal that the action SetKontrolProductConnected is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetKontrolProductConnected must be overridden if this is called.
     */
    void EnableActionSetKontrolProductConnected();
    /**
     * Signal that the action KontrolProductComPort is supported.
     * The action's availability will be published in the device's service.xml.
     * DoKontrolProductComPort must be overridden if this is called.
     */
    void EnableActionKontrolProductComPort();
    /**
     * Signal that the action SetKontrolProductComPort is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetKontrolProductComPort must be overridden if this is called.
     */
    void EnableActionSetKontrolProductComPort();
    /**
     * Signal that the action DiscPlayerConnected is supported.
     * The action's availability will be published in the device's service.xml.
     * DoDiscPlayerConnected must be overridden if this is called.
     */
    void EnableActionDiscPlayerConnected();
    /**
     * Signal that the action SetDiscPlayerConnected is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetDiscPlayerConnected must be overridden if this is called.
     */
    void EnableActionSetDiscPlayerConnected();
    /**
     * Signal that the action DiscPlayerComPort is supported.
     * The action's availability will be published in the device's service.xml.
     * DoDiscPlayerComPort must be overridden if this is called.
     */
    void EnableActionDiscPlayerComPort();
    /**
     * Signal that the action SetDiscPlayerComPort is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetDiscPlayerComPort must be overridden if this is called.
     */
    void EnableActionSetDiscPlayerComPort();
    /**
     * Signal that the action TestKontrolProductConnection is supported.
     * The action's availability will be published in the device's service.xml.
     * DoTestKontrolProductConnection must be overridden if this is called.
     */
    void EnableActionTestKontrolProductConnection();
    /**
     * Signal that the action TestDiscPlayerConnection is supported.
     * The action's availability will be published in the device's service.xml.
     * DoTestDiscPlayerConnection must be overridden if this is called.
     */
    void EnableActionTestDiscPlayerConnection();
private:
    /**
     * KontrolProductConnected action.
     *
     * Will be called when the device stack receives an invocation of the
     * KontrolProductConnected action for the owning device.
     * Must be implemented iff EnableActionKontrolProductConnected was called.
     */
    virtual void KontrolProductConnected(uint32_t aVersion, std::string& aaConnected);
    /**
     * SetKontrolProductConnected action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetKontrolProductConnected action for the owning device.
     * Must be implemented iff EnableActionSetKontrolProductConnected was called.
     */
    virtual void SetKontrolProductConnected(uint32_t aVersion, const std::string& aaConnected);
    /**
     * KontrolProductComPort action.
     *
     * Will be called when the device stack receives an invocation of the
     * KontrolProductComPort action for the owning device.
     * Must be implemented iff EnableActionKontrolProductComPort was called.
     */
    virtual void KontrolProductComPort(uint32_t aVersion, uint32_t& aaPort);
    /**
     * SetKontrolProductComPort action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetKontrolProductComPort action for the owning device.
     * Must be implemented iff EnableActionSetKontrolProductComPort was called.
     */
    virtual void SetKontrolProductComPort(uint32_t aVersion, uint32_t aaConnected);
    /**
     * DiscPlayerConnected action.
     *
     * Will be called when the device stack receives an invocation of the
     * DiscPlayerConnected action for the owning device.
     * Must be implemented iff EnableActionDiscPlayerConnected was called.
     */
    virtual void DiscPlayerConnected(uint32_t aVersion, std::string& aaConnected);
    /**
     * SetDiscPlayerConnected action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetDiscPlayerConnected action for the owning device.
     * Must be implemented iff EnableActionSetDiscPlayerConnected was called.
     */
    virtual void SetDiscPlayerConnected(uint32_t aVersion, const std::string& aaConnected);
    /**
     * DiscPlayerComPort action.
     *
     * Will be called when the device stack receives an invocation of the
     * DiscPlayerComPort action for the owning device.
     * Must be implemented iff EnableActionDiscPlayerComPort was called.
     */
    virtual void DiscPlayerComPort(uint32_t aVersion, uint32_t& aaPort);
    /**
     * SetDiscPlayerComPort action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetDiscPlayerComPort action for the owning device.
     * Must be implemented iff EnableActionSetDiscPlayerComPort was called.
     */
    virtual void SetDiscPlayerComPort(uint32_t aVersion, uint32_t aaConnected);
    /**
     * TestKontrolProductConnection action.
     *
     * Will be called when the device stack receives an invocation of the
     * TestKontrolProductConnection action for the owning device.
     * Must be implemented iff EnableActionTestKontrolProductConnection was called.
     */
    virtual void TestKontrolProductConnection(uint32_t aVersion, bool& aaResult);
    /**
     * TestDiscPlayerConnection action.
     *
     * Will be called when the device stack receives an invocation of the
     * TestDiscPlayerConnection action for the owning device.
     * Must be implemented iff EnableActionTestDiscPlayerConnection was called.
     */
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

