#include <OpenHome/Av/Source.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Av/Product.h>
#include <OpenHome/Configuration/ConfigManager.h>
#include <OpenHome/Private/Ascii.h>

using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Configuration;


const Brn Source::kSourceNameKeyPrefix("Source.");
const Brn Source::kSourceNameKeySuffix(".Name");

const Brx& Source::SystemName() const
{
    return iSystemName;
}

const Brx& Source::Type() const
{
    return iType;
}

const Brx& Source::Name() const
{
    return iName;
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
    , iProduct(NULL)
    , iConfigName(NULL)
    , iConfigNameSubscriptionId(ConfigVal<const Brx&>::kSubscriptionIdInvalid)
    , iConfigNameCreated(false)
{
}

Source::~Source()
{
    if (iConfigName != NULL) {
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

void Source::Initialise(IProduct& aProduct, IConfigManagerInitialiser& aConfigInit, IConfigManagerReader& aConfigManagerReader, TUint aId)
{
    const TUint maxKeyBytes = kSourceNameKeyPrefix.Bytes() + kMaxSourceIndexDigits + kSourceNameKeySuffix.Bytes();
    iProduct = &aProduct;
    Bwh key(maxKeyBytes);
    key.Replace(kSourceNameKeyPrefix);
    Ascii::AppendDec(key, aId);
    key.Append(kSourceNameKeySuffix);
    if (aConfigManagerReader.HasText(key)) {
        iConfigName = &aConfigManagerReader.GetText(key);
        iConfigNameCreated = false;
    } else {
        iConfigName = new ConfigText(aConfigInit, key, maxKeyBytes, iName);
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
