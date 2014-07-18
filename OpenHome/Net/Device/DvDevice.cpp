#include <OpenHome/Net/Core/DvDevice.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Private/DviDevice.h>

using namespace OpenHome;
using namespace OpenHome::Net;

// DvDevice

DvDevice::DvDevice(DvStack& aDvStack, const Brx& aUdn)
{
    iDevice = new DviDevice(aDvStack, aUdn);
}

DvDevice::DvDevice()
    : iDevice(NULL)
{
}

DvDevice::~DvDevice()
{
    if (iDevice != NULL) {
        iDevice->Destroy();
    }
}

DviDevice& DvDevice::Device()
{
    return *iDevice;
}    

const Brx& DvDevice::Udn() const
{
    return iDevice->Udn();
}

TBool DvDevice::Enabled() const
{
    return iDevice->Enabled();
}

void DvDevice::SetEnabled()
{
    iDevice->SetEnabled();
}

void DvDevice::SetDisabled(Functor aCompleted)
{
    iDevice->SetDisabled(aCompleted);
}

void DvDevice::GetAttribute(const TChar* aKey, const TChar** aValue) const
{
    iDevice->GetAttribute(aKey, aValue);
}

void DvDevice::SetAttribute(const TChar* aKey, const TChar* aValue)
{
    iDevice->SetAttribute(aKey, aValue);
}


// DvDeviceStandard

DvDeviceStandard::DvDeviceStandard(DvStack& aDvStack, const Brx& aUdn)
{
    iDevice = new DviDeviceStandard(aDvStack, aUdn);
}

DvDeviceStandard::DvDeviceStandard(DvStack& aDvStack, const Brx& aUdn, IResourceManager& aResourceManager)
{
    iDevice = new DviDeviceStandard(aDvStack, aUdn, aResourceManager);
}

void DvDeviceStandard::GetResourceManagerUri(const NetworkAdapter& aAdapter, Brh& aUri)
{
    iDevice->GetResourceManagerUri(aAdapter, aUri);
}
