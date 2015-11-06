#include <OpenHome/Av/Source.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Av/Product.h>
#include <OpenHome/Media/PipelineManager.h>
#include <OpenHome/Configuration/ConfigManager.h>
#include <OpenHome/PowerManager.h>
#include <OpenHome/Private/Ascii.h>

using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Configuration;


// SourceBase

const Brn SourceBase::kKeySourceNamePrefix("Source.");
const Brn SourceBase::kKeySourceNameSuffix(".Name");

void SourceBase::GetSourceNameKey(const Brx& aName, Bwx& aBuf)
{
    aBuf.Replace(kKeySourceNamePrefix);
    aBuf.Append(aName);
    aBuf.Append(kKeySourceNameSuffix);
}

const Brx& SourceBase::SystemName() const
{
    return iSystemName;
}

const Brx& SourceBase::Type() const
{
    return iType;
}

void SourceBase::Name(Bwx& aBuf) const
{
    AutoMutex a(iLock);
    aBuf.Replace(iName);
}

TBool SourceBase::IsVisible() const
{
    return iVisible;
}

void SourceBase::Deactivate()
{
    iActive = false;
}

void SourceBase::SetVisible(TBool aVisible)
{
    iVisible = aVisible;
}

SourceBase::SourceBase(const TChar* aSystemName, const TChar* aType)
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

SourceBase::~SourceBase()
{
    if (iConfigName != nullptr) {
        iConfigName->Unsubscribe(iConfigNameSubscriptionId);
    }
    if (iConfigNameCreated) {
        delete iConfigName;
    }
}

TBool SourceBase::IsActive() const
{
    return iActive;
}

void SourceBase::DoActivate()
{
    iActive = true;
    iProduct->Activate(*this);
}

void SourceBase::Initialise(IProduct& aProduct, IConfigInitialiser& aConfigInit, IConfigManager& aConfigManagerReader, TUint aId)
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
    iConfigNameSubscriptionId = iConfigName->Subscribe(MakeFunctorConfigText(*this, &SourceBase::NameChanged));
}

void SourceBase::NameChanged(KeyValuePair<const Brx&>& aName)
{
    iLock.Wait();
    iName.Replace(aName.Value());
    iLock.Signal();
    iProduct->NotifySourceNameChanged(*this);
}


// Source

Source::Source(const TChar* aSystemName, const TChar* aType, Media::PipelineManager& aPipeline, IPowerManager& aPowerManager)
    : SourceBase(aSystemName, aType)
    , iPipeline(aPipeline)
    , iPowerManager(aPowerManager)
{
}

void Source::DoPlay()
{
    iPowerManager.StandbyDisable(eStandbyDisableUser);
    iPipeline.Play();
}
