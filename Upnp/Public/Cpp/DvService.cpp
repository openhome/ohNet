#include <DvService.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <DviDevice.h>


using namespace Zapp;

void DvService::PropertiesLock()
{
    iService->PropertiesLock();
    iDelayPropertyUpdates = true;
}

void DvService::PropertiesUnlock()
{
    TBool report = iPropertyChanged;
    iPropertyChanged = false;
    iDelayPropertyUpdates = false;
    iService->PropertiesUnlock();
    if (report) {
        iService->PublishPropertyUpdates();
    }
}

DvService::DvService(DviDevice& aDevice, const TChar* aDomain, const TChar* aType, TUint aVersion)
    : iDelayPropertyUpdates(false)
    , iPropertyChanged(false)
{
    iService = new DviService(aDomain, aType, aVersion);
    aDevice.AddService(iService); // ownership of service passed to aDevice
}

DvService::~DvService()
{
}

void DvService::SetPropertyInt(PropertyInt& aProperty, TInt aValue)
{
    if (aProperty.SetValue(aValue)) {
        if (iDelayPropertyUpdates) {
            iPropertyChanged = true;
        }
        else {
            iService->PublishPropertyUpdates();
        }
    }
}

void DvService::SetPropertyUint(PropertyUint& aProperty, TUint aValue)
{
    if (aProperty.SetValue(aValue)) {
        if (iDelayPropertyUpdates) {
            iPropertyChanged = true;
        }
        else {
            iService->PublishPropertyUpdates();
        }
    }
}

void DvService::SetPropertyBool(PropertyBool& aProperty, TBool aValue)
{
    if (aProperty.SetValue(aValue)) {
        if (iDelayPropertyUpdates) {
            iPropertyChanged = true;
        }
        else {
            iService->PublishPropertyUpdates();
        }
    }
}

void DvService::SetPropertyString(PropertyString& aProperty, const Brx& aValue)
{
    if (aProperty.SetValue(aValue)) {
        if (iDelayPropertyUpdates) {
            iPropertyChanged = true;
        }
        else {
            iService->PublishPropertyUpdates();
        }
    }
}

void DvService::SetPropertyBinary(PropertyBinary& aProperty, const Brx& aValue)
{
    if (aProperty.SetValue(aValue)) {
        if (iDelayPropertyUpdates) {
            iPropertyChanged = true;
        }
        else {
            iService->PublishPropertyUpdates();
        }
    }
}
