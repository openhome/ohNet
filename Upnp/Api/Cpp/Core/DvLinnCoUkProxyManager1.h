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
 * Provider for the linn.co.uk:ProxyManager:1 UPnP service
 */
class DvProviderLinnCoUkProxyManager1 : public DvProvider
{
public:
    virtual ~DvProviderLinnCoUkProxyManager1() {}
    /**
     * Set the value of the KontrolProductConnected property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyKontrolProductConnected(const Brx& aValue);
    /**
     * Get a copy of the value of the KontrolProductConnected property
     */
    void GetPropertyKontrolProductConnected(Brhz& aValue);
    /**
     * Set the value of the KontrolProductComPort property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyKontrolProductComPort(TUint aValue);
    /**
     * Get a copy of the value of the KontrolProductComPort property
     */
    void GetPropertyKontrolProductComPort(TUint& aValue);
    /**
     * Set the value of the DiscPlayerConnected property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyDiscPlayerConnected(const Brx& aValue);
    /**
     * Get a copy of the value of the DiscPlayerConnected property
     */
    void GetPropertyDiscPlayerConnected(Brhz& aValue);
    /**
     * Set the value of the DiscPlayerComPort property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyDiscPlayerComPort(TUint aValue);
    /**
     * Get a copy of the value of the DiscPlayerComPort property
     */
    void GetPropertyDiscPlayerComPort(TUint& aValue);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderLinnCoUkProxyManager1(DvDevice& aDevice);
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
    virtual void KontrolProductConnected(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaConnected);
    /**
     * SetKontrolProductConnected action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetKontrolProductConnected action for the owning device.
     * Must be implemented iff EnableActionSetKontrolProductConnected was called.
     */
    virtual void SetKontrolProductConnected(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaConnected);
    /**
     * KontrolProductComPort action.
     *
     * Will be called when the device stack receives an invocation of the
     * KontrolProductComPort action for the owning device.
     * Must be implemented iff EnableActionKontrolProductComPort was called.
     */
    virtual void KontrolProductComPort(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaPort);
    /**
     * SetKontrolProductComPort action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetKontrolProductComPort action for the owning device.
     * Must be implemented iff EnableActionSetKontrolProductComPort was called.
     */
    virtual void SetKontrolProductComPort(IInvocationResponse& aResponse, TUint aVersion, TUint aaConnected);
    /**
     * DiscPlayerConnected action.
     *
     * Will be called when the device stack receives an invocation of the
     * DiscPlayerConnected action for the owning device.
     * Must be implemented iff EnableActionDiscPlayerConnected was called.
     */
    virtual void DiscPlayerConnected(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaConnected);
    /**
     * SetDiscPlayerConnected action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetDiscPlayerConnected action for the owning device.
     * Must be implemented iff EnableActionSetDiscPlayerConnected was called.
     */
    virtual void SetDiscPlayerConnected(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaConnected);
    /**
     * DiscPlayerComPort action.
     *
     * Will be called when the device stack receives an invocation of the
     * DiscPlayerComPort action for the owning device.
     * Must be implemented iff EnableActionDiscPlayerComPort was called.
     */
    virtual void DiscPlayerComPort(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaPort);
    /**
     * SetDiscPlayerComPort action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetDiscPlayerComPort action for the owning device.
     * Must be implemented iff EnableActionSetDiscPlayerComPort was called.
     */
    virtual void SetDiscPlayerComPort(IInvocationResponse& aResponse, TUint aVersion, TUint aaConnected);
    /**
     * TestKontrolProductConnection action.
     *
     * Will be called when the device stack receives an invocation of the
     * TestKontrolProductConnection action for the owning device.
     * Must be implemented iff EnableActionTestKontrolProductConnection was called.
     */
    virtual void TestKontrolProductConnection(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaResult);
    /**
     * TestDiscPlayerConnection action.
     *
     * Will be called when the device stack receives an invocation of the
     * TestDiscPlayerConnection action for the owning device.
     * Must be implemented iff EnableActionTestDiscPlayerConnection was called.
     */
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

