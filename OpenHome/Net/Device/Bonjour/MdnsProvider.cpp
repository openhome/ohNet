#include <OpenHome/Net/Private/MdnsProvider.h>
#include <OpenHome/Types.h>

using namespace OpenHome;
using namespace OpenHome::Net;

MdnsProvider::MdnsProvider(Environment& aStack, const TChar* aHost, TBool aRequiresMdnsCache)
    : iPlatform(aStack, aHost, aRequiresMdnsCache)
{
}

MdnsProvider::~MdnsProvider()
{
}

void MdnsProvider::MdnsSetHostName(const TChar* aName)
{
    iPlatform.SetHostName(aName);
}

TUint MdnsProvider::MdnsCreateService()
{
#ifdef DEFINE_WINDOWS_UNIVERSAL
    return 0;
#else
    return iPlatform.CreateService();
#endif
}

void MdnsProvider::MdnsDestroyService(TUint aHandle)
{
    iPlatform.DeregisterService(aHandle);
}

void MdnsProvider::MdnsAppendTxtRecord(Bwx& aBuffer, const TChar* aKey, const TChar* aValue)
{
    iPlatform.AppendTxtRecord(aBuffer, aKey, aValue);
}

void MdnsProvider::MdnsRegisterService(TUint aHandle, const TChar* aName, const TChar* aType, const TIpAddress& aInterface, TUint aPort, const TChar* aInfo)
{
    iPlatform.RegisterService(aHandle, aName, aType, aInterface, aPort, aInfo);
}

void MdnsProvider::MdnsDeregisterService(TUint aHandle)
{
    iPlatform.DeregisterService(aHandle);
}

void MdnsProvider::FindDevices(const TChar* aServiceName)
{
    iPlatform.FindDevices(aServiceName);
}

void MdnsProvider::AddMdnsDeviceListener(IMdnsDeviceListener* aListener)
{
    iPlatform.AddMdnsDeviceListener(aListener);
}
