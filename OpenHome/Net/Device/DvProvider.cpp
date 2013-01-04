#include <OpenHome/Net/Core/DvProvider.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Private/DviDevice.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Net/Private/Stack.h>
#include <OpenHome/Net/Private/DviStack.h>

using namespace OpenHome;
using namespace OpenHome::Net;

void DvProvider::PropertiesLock()
{
    iService->PropertiesLock();
    iDvStack.GetStack().Mutex().Wait();
    iDelayPropertyUpdates = true;
    iDvStack.GetStack().Mutex().Signal();
}

void DvProvider::PropertiesUnlock()
{
    iDvStack.GetStack().Mutex().Wait();
    TBool report = iPropertyChanged;
    iPropertyChanged = false;
    iDelayPropertyUpdates = false;
    iDvStack.GetStack().Mutex().Signal();
    iService->PropertiesUnlock();
    if (report) {
        iService->PublishPropertyUpdates();
    }
}

DvProvider::DvProvider(DviDevice& aDevice, const TChar* aDomain, const TChar* aType, TUint aVersion)
    : iDvStack(aDevice.GetDvStack())
    , iDelayPropertyUpdates(false)
    , iPropertyChanged(false)
{
    iService = new DviService(iDvStack, aDomain, aType, aVersion);
    aDevice.AddService(iService);
}

DvProvider::~DvProvider()
{
    iService->Disable();
    iService->RemoveRef();
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
    iDvStack.GetStack().Mutex().Wait();
    TBool publish = !iDelayPropertyUpdates;
    if (iDelayPropertyUpdates) {
        iPropertyChanged = true;
    }
    iDvStack.GetStack().Mutex().Signal();
    if (publish) {
        iService->PublishPropertyUpdates();
    }
}    
