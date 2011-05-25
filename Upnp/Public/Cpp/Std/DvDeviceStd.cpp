#include <Std/DvDevice.h>
#include <OsTypes.h>
#include <DviDevice.h>
#include <Core/DvDevice.h>
#include <Buffer.h>

#include <string>

using namespace OpenHome::Net;

// DvDeviceStd

DvDeviceStd::DvDeviceStd(const std::string& aUdn)
{
    Brn buf((const TByte*)aUdn.c_str(), (TUint)aUdn.length());
    iDevice = new DviDevice(buf);
    SetUdn(aUdn);
}
    
DvDeviceStd::DvDeviceStd()
    : iDevice(NULL)
{
}
    
DvDeviceStd::~DvDeviceStd()
{
    iDevice->Destroy();
}
    
void DvDeviceStd::SetUdn(const std::string& aUdn)
{
    iUdn.assign(aUdn);
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

void DvDeviceStd::SetXmlExtension(const TChar* aXml)
{
    iDevice->SetXmlExtension(aXml);
}


// DvDeviceStdStandard

DvDeviceStdStandard::DvDeviceStdStandard(const std::string& aUdn)
{
    Brn buf((const TByte*)aUdn.c_str(), (TUint)aUdn.length());
    iDevice = new DviDeviceStandard(buf);
    SetUdn(aUdn);
    iResourceManager = NULL;
}

DvDeviceStdStandard::DvDeviceStdStandard(const std::string& aUdn, IResourceManagerStd& aResourceManager)
{
    iResourceManager = &aResourceManager;
    Brn buf((const TByte*)aUdn.c_str(), (TUint)aUdn.length());
    iDevice = new DviDeviceStandard(buf, *this);
    SetUdn(aUdn);
}
    
void DvDeviceStdStandard::WriteResource(const Brx& aUriTail, TIpAddress aInterface, IResourceWriter& aResourceWriter)
{
    std::string uriTail((const char*)aUriTail.Ptr(), aUriTail.Bytes());
    ASSERT(iResourceManager != NULL);
    iResourceManager->WriteResource(uriTail, aInterface, aResourceWriter);
}    
