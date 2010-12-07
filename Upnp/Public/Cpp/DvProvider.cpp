#include <DvProvider.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <DviDevice.h>


using namespace Zapp;

void DvProvider::PropertiesLock()
{
    iService->PropertiesLock();
    iDelayPropertyUpdates = true;
}

void DvProvider::PropertiesUnlock()
{
    TBool report = iPropertyChanged;
    iPropertyChanged = false;
    iDelayPropertyUpdates = false;
    iService->PropertiesUnlock();
    if (report) {
        iService->PublishPropertyUpdates();
    }
}

DvProvider::DvProvider(DviDevice& aDevice, const TChar* aDomain, const TChar* aType, TUint aVersion)
    : iDelayPropertyUpdates(false)
    , iPropertyChanged(false)
{
    iService = new DviService(aDomain, aType, aVersion);
    aDevice.AddService(iService); // ownership of service passed to aDevice
}

DvProvider::~DvProvider()
{
}

bool DvProvider::SetPropertyInt(PropertyInt& aProperty, TInt aValue)
{
    if (aProperty.SetValue(aValue)) {
        if (iDelayPropertyUpdates) {
            iPropertyChanged = true;
        }
        else {
            iService->PublishPropertyUpdates();
        }
        return true;
    }
    return false;
}

bool DvProvider::SetPropertyUint(PropertyUint& aProperty, TUint aValue)
{
    if (aProperty.SetValue(aValue)) {
        if (iDelayPropertyUpdates) {
            iPropertyChanged = true;
        }
        else {
            iService->PublishPropertyUpdates();
        }
        return true;
    }
    return false;
}

bool DvProvider::SetPropertyBool(PropertyBool& aProperty, TBool aValue)
{
    if (aProperty.SetValue(aValue)) {
        if (iDelayPropertyUpdates) {
            iPropertyChanged = true;
        }
        else {
            iService->PublishPropertyUpdates();
        }
        return true;
    }
    return false;
}

bool DvProvider::SetPropertyString(PropertyString& aProperty, const Brx& aValue)
{
    if (aProperty.SetValue(aValue)) {
        if (iDelayPropertyUpdates) {
            iPropertyChanged = true;
        }
        else {
            iService->PublishPropertyUpdates();
        }
        return true;
    }
    return false;
}

bool DvProvider::SetPropertyBinary(PropertyBinary& aProperty, const Brx& aValue)
{
    if (aProperty.SetValue(aValue)) {
        if (iDelayPropertyUpdates) {
            iPropertyChanged = true;
        }
        else {
            iService->PublishPropertyUpdates();
        }
        return true;
    }
    return false;
}
