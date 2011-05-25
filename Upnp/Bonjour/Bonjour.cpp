#include <Bonjour.h>
#include <OhNetTypes.h>
#include <Buffer.h>

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

void BonjourWebPage::SetEnabled(const TChar* aName, TIpAddress aInterface, TUint aPort, const TChar* aUri)
{
    TChar info[200];
    iMdns.MdnsAppendTxtRecord(info, 200, "path", aUri);
    iMdns.MdnsRegisterService(iMdnsHandle, aName, "_http._tcp", aInterface, aPort, info);
}

void BonjourWebPage::SetDisabled()
{
    iMdns.MdnsDeregisterService(iMdnsHandle);
}
