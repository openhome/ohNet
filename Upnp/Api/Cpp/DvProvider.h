#ifndef HEADER_DVSERVICE
#define HEADER_DVSERVICE

#include <ZappTypes.h>
#include <Buffer.h>
#include <DviDevice.h>

namespace Zapp {

class DviService;
class PropertyInt;
class PropertyUint;
class PropertyBool;
class PropertyString;
class PropertyBinary;

/**
 * Base class for a service provider.
 *
 * Derivations will typically be by service-specific auto-generated code which will
 * offer 0..n actions and 0..n properties.
 */
class DllExportClass DvProvider
{
public:
    /**
     * Lock the provider's vector of properties, blocking publication of property updates
     *
     * This is not necessary when updating a single property but is used by providers that have
     * >1 properties whose values are related.  Without locking, updates to some properties may
     * be published, leaving related properties in their old (now incompatible) states.
     *
     * Every call to this must be followed by (exactly) one call to PropertiesUnlock().
     */
    void PropertiesLock();
    /**
     * Unlock the provider's vector of properties, allowing publication of property updates.
     *
     * This must only be called following a call to PropertiesLock().
     */
    void PropertiesUnlock();
protected:
    DllExport DvProvider(DviDevice& aDevice, const TChar* aDomain, const TChar* aType, TUint aVersion);
    DllExport virtual ~DvProvider();
    /**
     * Utility function which updates the value of a PropertyInt. (Not intended for external use)
     *
     * If the property value has changed and the properties are not locked (PropertiesLock()
     * called more recently than PropertiesUnlock()), publication of an update is scheduled.
     *
     * Throws ParameterValidationError if the property has a range of allowed values and
     * the new value is not in this range
     *
     * @return  true if the property's value has changed (aValue was different to the previous value)
     */
    DllExport bool SetPropertyInt(PropertyInt& aProperty, TInt aValue);
    /**
     * Utility function which updates the value of a PropertyUint. (Not intended for external use)
     *
     * If the property value has changed and the properties are not locked (PropertiesLock()
     * called more recently than PropertiesUnlock()), publication of an update is scheduled.
     *
     * Throws ParameterValidationError if the property has a range of allowed values and
     * the new value is not in this range
     *
     * @return  true if the property's value has changed (aValue was different to the previous value)
     */
    DllExport bool SetPropertyUint(PropertyUint& aProperty, TUint aValue);
    /**
     * Utility function which updates the value of a PropertyBool. (Not intended for external use)
     *
     * If the property value has changed and the properties are not locked (PropertiesLock()
     * called more recently than PropertiesUnlock()), publication of an update is scheduled.
     *
     * @return  true if the property's value has changed (aValue was different to the previous value)
     */
    DllExport bool SetPropertyBool(PropertyBool& aProperty, TBool aValue);
    /**
     * Utility function which updates the value of a PropertyString. (Not intended for external use)
     *
     * If the property value has changed and the properties are not locked (PropertiesLock()
     * called more recently than PropertiesUnlock()), publication of an update is scheduled.
     *
     * Throws ParameterValidationError if the property has a set of allowed values and
     * the new value is not in this set
     *
     * @return  true if the property's value has changed (aValue was different to the previous value)
     */
    DllExport bool SetPropertyString(PropertyString& aProperty, const Brx& aValue);
    /**
     * Utility function which updates the value of a PropertyBinary. (Not intended for external use)
     *
     * If the property value has changed and the properties are not locked (PropertiesLock()
     * called more recently than PropertiesUnlock()), publication of an update is scheduled.
     *
     * Throws ParameterValidationError if the property has a set of allowed values and
     * the new value is not in this set
     *
     * @return  true if the property's value has changed (aValue was different to the previous value)
     */
    DllExport bool SetPropertyBinary(PropertyBinary& aProperty, const Brx& aValue);
protected:
    DviService* iService;
private:
    TBool iDelayPropertyUpdates;
    TBool iPropertyChanged;
};

} // namespace Zapp

#endif // HEADER_DVSERVICE

