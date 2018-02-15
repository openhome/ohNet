#ifndef HEADER_BONJOUR
#define HEADER_BONJOUR

#include <OpenHome/Buffer.h>
#include <OpenHome/Types.h>
#include <OpenHome/Private/Standard.h>


namespace OpenHome {
namespace Net {

class IMdnsDeviceListener;

class IMdnsProvider
{
public:
    virtual ~IMdnsProvider() {}
    virtual void MdnsSetHostName(const TChar* aName) = 0;
    virtual TUint MdnsCreateService() = 0;
    virtual void MdnsDestroyService(TUint aHandle) = 0;
    virtual void MdnsAppendTxtRecord(Bwx& aBuffer, const TChar* aKey, const TChar* aValue) = 0;
    virtual void MdnsRegisterService(TUint aHandle, const TChar* aName, const TChar* aType, TIpAddress aInterface, TUint aPort, const TChar* aInfo) = 0;
    virtual void MdnsDeregisterService(TUint aHandle) = 0;
    virtual void AddMdnsDeviceListener(IMdnsDeviceListener* aListener) = 0;
    virtual void FindDevices(const TChar* aServiceName) = 0;
};
    
class BonjourWebPage : INonCopyable
{
public:
    BonjourWebPage(IMdnsProvider& aMdns);
    ~BonjourWebPage();
    void SetEnabled(const TChar* aName, TIpAddress aInterface, TUint aPort, const TChar* aUri);
    void SetDisabled();
private:
    IMdnsProvider& iMdns;
    TUint iMdnsHandle;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_BONJOUR
