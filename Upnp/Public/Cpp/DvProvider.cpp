#include <DvProvider.h>
#include <OhNetTypes.h>
#include <Buffer.h>
#include <DviDevice.h>
#include <Printer.h>
#include <Stack.h>

using namespace OpenHome;
using namespace OpenHome::Net;

void DvProvider::PropertiesLock()
{
    iService->PropertiesLock();
    Stack::Mutex().Wait();
    iDelayPropertyUpdates = true;
    Stack::Mutex().Signal();
}

void DvProvider::PropertiesUnlock()
{
    Stack::Mutex().Wait();
    TBool report = iPropertyChanged;
    iPropertyChanged = false;
    iDelayPropertyUpdates = false;
    Stack::Mutex().Signal();
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
        TryPublishUpdate();
        return true;
    }
    return false;
}

bool DvProvider::SetPropertyUint(PropertyUint& aProperty, TUint aValue)
{
    if (aProperty.SetValue(aValue)) {
        TryPublishUpdate();
        return true;
    }
    return false;
}

bool DvProvider::SetPropertyBool(PropertyBool& aProperty, TBool aValue)
{
    if (aProperty.SetValue(aValue)) {
        TryPublishUpdate();
        return true;
    }
    return false;
}

bool DvProvider::SetPropertyString(PropertyString& aProperty, const Brx& aValue)
{
    if (aProperty.SetValue(aValue)) {
        TryPublishUpdate();
        return true;
    }
    return false;
}

bool DvProvider::SetPropertyBinary(PropertyBinary& aProperty, const Brx& aValue)
{
    if (aProperty.SetValue(aValue)) {
        TryPublishUpdate();
        return true;
    }
    return false;
}

void DvProvider::TryPublishUpdate()
{
    Stack::Mutex().Wait();
    TBool publish = !iDelayPropertyUpdates;
    if (iDelayPropertyUpdates) {
        iPropertyChanged = true;
    }
    Stack::Mutex().Signal();
    if (publish) {
        iService->PublishPropertyUpdates();
    }
}    
