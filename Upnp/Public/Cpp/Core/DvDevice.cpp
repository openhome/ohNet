#include <Core/DvDevice.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <DviDevice.h>

using namespace Zapp;

DvDevice::DvDevice(const Brx& aUdn)
{
    iDevice = new DviDevice(aUdn);
}

DvDevice::DvDevice(const Brx& aUdn, IResourceManager& aResourceManager)
{
    iDevice = new DviDevice(aUdn, aResourceManager);
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
