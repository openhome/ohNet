#include <OpenHome/Net/Private/Bonjour.h>
#include <OpenHome/Types.h>

using namespace OpenHome;
using namespace OpenHome::Net;

BonjourWebPage::BonjourWebPage(IMdnsProvider& aMdns)
    : iMdns(aMdns)
{
    iMdnsHandle = iMdns.MdnsCreateService();
}

BonjourWebPage::~BonjourWebPage()
{
    iMdns.MdnsDestroyService(iMdnsHandle);
}

void BonjourWebPage::SetEnabled(const TChar* aName, const TIpAddress& aInterface, TUint aPort, const TChar* aUri)
{
    Bws<200> info;
    iMdns.MdnsAppendTxtRecord(info, "path", aUri);
    iMdns.MdnsRegisterService(iMdnsHandle, aName, "_http._tcp", aInterface, aPort, info.PtrZ());
}

void BonjourWebPage::SetDisabled()
{
    iMdns.MdnsDeregisterService(iMdnsHandle);
}
