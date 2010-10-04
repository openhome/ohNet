#include <Std/DvDevice.h>
#include <OsTypes.h>
#include <DviDevice.h>
#include <Core/DvDevice.h>
#include <Buffer.h>

#include <string>

using namespace Zapp;


DvDeviceStd::DvDeviceStd(const std::string& aUdn)
{
    Brn buf((const TByte*)aUdn.c_str(), aUdn.length());
    iDevice = new DviDevice(buf);
    iUdn.assign(aUdn);
    iResourceManager = NULL;
}
    
DvDeviceStd::DvDeviceStd(const std::string& aUdn, IResourceManagerStd& aResourceManager)
{
    Brn buf((const TByte*)aUdn.c_str(), aUdn.length());
    iDevice = new DviDevice(buf, *this);
    iUdn.assign(aUdn);
    iResourceManager = &aResourceManager;
}
    
DvDeviceStd::~DvDeviceStd()
{
    iDevice->Destroy();
}
    
DviDevice& DvDeviceStd::Device()
{
    return *iDevice;
}
    
const std::string& DvDeviceStd::Udn() const
{
    return iUdn;
}
    
TBool DvDeviceStd::Enabled() const
{
    return iDevice->Enabled();
}
    
void DvDeviceStd::SetEnabled()
{
    iDevice->SetEnabled();
}
    
void DvDeviceStd::SetDisabled(Functor aCompleted)
{
    iDevice->SetDisabled(aCompleted);
}
    
void DvDeviceStd::GetAttribute(const char* aKey, const char** aValue) const
{
    iDevice->GetAttribute(aKey, aValue);
}
    
void DvDeviceStd::SetAttribute(const char* aKey, const char* aValue)
{
    iDevice->SetAttribute(aKey, aValue);
}
    
void DvDeviceStd::WriteResource(const Brx& aUriTail, TIpAddress aInterface, IResourceWriter& aResourceWriter)
{
    std::string uriTail((const char*)aUriTail.Ptr(), aUriTail.Bytes());
    ASSERT(iResourceManager != NULL);
    iResourceManager->WriteResource(uriTail, aInterface, aResourceWriter);
}    
