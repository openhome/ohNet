#include <OpenHome/Av/Source.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Av/Product.h>
#include <OpenHome/Configuration/ConfigManager.h>
#include <OpenHome/Private/Ascii.h>

using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Configuration;


const Brn Source::kKeySourceNamePrefix("Source.");
const Brn Source::kKeySourceNameSuffix(".Name");

void Source::GetSourceNameKey(const Brx& aName, Bwx& aBuf)
{
    aBuf.Replace(kKeySourceNamePrefix);
    aBuf.Append(aName);
    aBuf.Append(kKeySourceNameSuffix);
}

const Brx& Source::SystemName() const
{
    return iSystemName;
}

const Brx& Source::Type() const
{
    return iType;
}

void Source::Name(Bwx& aBuf) const
{
    AutoMutex a(iLock);
    aBuf.Replace(iName);
}

TBool Source::IsVisible() const
{
    return iVisible;
}

void Source::Deactivate()
{
    iActive = false;
}

void Source::SetVisible(TBool aVisible)
{
    iVisible = aVisible;
}

Source::Source(const TChar* aSystemName, const TChar* aType)
    : iActive(false)
    , iLock("SRCM")
    , iSystemName(aSystemName)
    , iType(aType)
    , iName(aSystemName)
    , iVisible(true)
    , iProduct(nullptr)
    , iConfigName(nullptr)
    , iConfigNameSubscriptionId(IConfigManager::kSubscriptionIdInvalid)
    , iConfigNameCreated(false)
{
}

Source::~Source()
{
    if (iConfigName != nullptr) {
        iConfigName->Unsubscribe(iConfigNameSubscriptionId);
    }
    if (iConfigNameCreated) {
        delete iConfigName;
    }
}

TBool Source::IsActive() const
{
    return iActive;
}

void Source::DoActivate()
{
    iActive = true;
    iProduct->Activate(*this);
}

void Source::Initialise(IProduct& aProduct, IConfigInitialiser& aConfigInit, IConfigManager& aConfigManagerReader, TUint aId)
{
    iProduct = &aProduct;
    Bws<kKeySourceNameMaxBytes> key;
    Bws<Ascii::kMaxUintStringBytes> id;
    Ascii::AppendDec(id, aId);
    GetSourceNameKey(id, key);
    if (aConfigManagerReader.HasText(key)) {
        iConfigName = &aConfigManagerReader.GetText(key);
        iConfigNameCreated = false;
    } else {
        iConfigName = new ConfigText(aConfigInit, key, ISource::kMaxSourceNameBytes, iName);
        iConfigNameCreated = true;
    }
    iConfigNameSubscriptionId = iConfigName->Subscribe(MakeFunctorConfigText(*this, &Source::NameChanged));
}

void Source::NameChanged(KeyValuePair<const Brx&>& aName)
{
    iLock.Wait();
    iName.Replace(aName.Value());
    iLock.Signal();
    iProduct->NotifySourceNameChanged(*this);
}
