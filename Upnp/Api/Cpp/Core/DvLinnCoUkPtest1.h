#ifndef HEADER_DVLINNCOUKPTEST1
#define HEADER_DVLINNCOUKPTEST1

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
 * Provider for the linn.co.uk:Ptest:1 UPnP service
 */
class DvProviderLinnCoUkPtest1 : public DvProvider
{
public:
    virtual ~DvProviderLinnCoUkPtest1() {}
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderLinnCoUkPtest1(DvDevice& aDevice);
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
    virtual void TestComPort(IInvocationResponse& aResponse, TUint aVersion, TUint aaPort, IInvocationResponseBool& aaResult);
    /**
     * LedsOn action.
     *
     * Will be called when the device stack receives an invocation of the
     * LedsOn action for the owning device.
     * Must be implemented iff EnableActionLedsOn was called.
     */
    virtual void LedsOn(IInvocationResponse& aResponse, TUint aVersion);
    /**
     * LedsOff action.
     *
     * Will be called when the device stack receives an invocation of the
     * LedsOff action for the owning device.
     * Must be implemented iff EnableActionLedsOff was called.
     */
    virtual void LedsOff(IInvocationResponse& aResponse, TUint aVersion);
private:
    DvProviderLinnCoUkPtest1();
    void DoTestComPort(IDviInvocation& aInvocation, TUint aVersion);
    void DoLedsOn(IDviInvocation& aInvocation, TUint aVersion);
    void DoLedsOff(IDviInvocation& aInvocation, TUint aVersion);
private:
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKPTEST1

