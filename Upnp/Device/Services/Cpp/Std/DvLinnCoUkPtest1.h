#ifndef HEADER_DVLINNCOUKPTEST1CPP
#define HEADER_DVLINNCOUKPTEST1CPP

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
 * Provider for the linn.co.uk:Ptest:1 UPnP service
 * @ingroup Providers
 */
class DvProviderLinnCoUkPtest1Cpp : public DvProvider
{
public:
    virtual ~DvProviderLinnCoUkPtest1Cpp() {}
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderLinnCoUkPtest1Cpp(DvDeviceStd& aDevice);
    /**
     * Signal that the action TestComPort is supported.
     * The action's availability will be published in the device's service.xml.
     * DoTestComPort must be overridden if this is called.
     */
    void EnableActionTestComPort();
    /**
     * Signal that the action LedsOn is supported.
     * The action's availability will be published in the device's service.xml.
     * DoLedsOn must be overridden if this is called.
     */
    void EnableActionLedsOn();
    /**
     * Signal that the action LedsOff is supported.
     * The action's availability will be published in the device's service.xml.
     * DoLedsOff must be overridden if this is called.
     */
    void EnableActionLedsOff();
private:
    /**
     * TestComPort action.
     *
     * Will be called when the device stack receives an invocation of the
     * TestComPort action for the owning device.
     * Must be implemented iff EnableActionTestComPort was called.
     */
    virtual void TestComPort(uint32_t aVersion, uint32_t aaPort, bool& aaResult);
    /**
     * LedsOn action.
     *
     * Will be called when the device stack receives an invocation of the
     * LedsOn action for the owning device.
     * Must be implemented iff EnableActionLedsOn was called.
     */
    virtual void LedsOn(uint32_t aVersion);
    /**
     * LedsOff action.
     *
     * Will be called when the device stack receives an invocation of the
     * LedsOff action for the owning device.
     * Must be implemented iff EnableActionLedsOff was called.
     */
    virtual void LedsOff(uint32_t aVersion);
private:
    DvProviderLinnCoUkPtest1Cpp();
    void DoTestComPort(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoLedsOn(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoLedsOff(IDviInvocation& aInvocation, uint32_t aVersion);
private:
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKPTEST1CPP

