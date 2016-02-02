#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Media/InfoProvider.h>
#include <OpenHome/Configuration/ConfigManager.h>

namespace OpenHome {
    class IPowerManager;
namespace Media {
    class PipelineManager;
}
namespace Av {

class IProduct;

class ISource
{
    friend class Product;
public:
    static const TUint kMaxSystemNameBytes = 20;
    static const TUint kMaxSourceNameBytes = 20;
    static const TUint kMaxSourceTypeBytes = 20;
    static const TUint kMaxAttributesBytes = 100;
public:
    virtual ~ISource() {}
    virtual const Brx& SystemName() const = 0;
    virtual const Brx& Type() const = 0;
    virtual void Name(Bwx& aBuf) const = 0;
    virtual TBool IsVisible() const = 0;
    virtual void Activate() = 0;
    virtual void Deactivate() = 0;
    virtual void SetVisible(TBool aVisible) = 0;
    virtual void StandbyEnabled() = 0;
    virtual void PipelineStopped() = 0;
private:
    virtual void Initialise(IProduct& aProduct, Configuration::IConfigInitialiser& aConfigInit, Configuration::IConfigManager& aConfigManagerReader, TUint aId) = 0;
};

class SourceBase : public ISource
{
private:
    static const TUint kMaxSourceTypeBytes = 20;
    static const TUint kMaxSourceIndexDigits = 2; // assume a source count of 0..99 is reasonable
    static const OpenHome::Brn kKeySourceNamePrefix;
    static const OpenHome::Brn kKeySourceNameSuffix;
    static const OpenHome::Brn kKeySourceVisibleSuffix;
public:
    static const TUint kConfigValSourceInvisible;
    static const TUint kConfigValSourceVisible;
    static const TUint kKeySourceNameMaxBytes = 40;
    static void GetSourceNameKey(const Brx& aSystemName, Bwx& aBuf);
    static void GetSourceVisibleKey(const Brx& aSystemName, Bwx& aBuf);
protected: // from ISource
    const Brx& SystemName() const override;
    const Brx& Type() const override;
    void Name(Bwx& aBuf) const override;
    TBool IsVisible() const override;
    void Deactivate() override;
    void SetVisible(TBool aVisible) override;
protected:
    SourceBase(const Brx& aSystemName, const TChar* aType);
    ~SourceBase();
    TBool IsActive() const;
    void DoActivate();
private: // from ISource
    void Initialise(IProduct& aProduct, Configuration::IConfigInitialiser& aConfigInit, Configuration::IConfigManager& aConfigManagerReader, TUint aId) override;
private:
    static void GetSourceKey(const Brx& aSystemName, const Brx& aSuffix, Bwx& aBuf);
    void NameChanged(Configuration::KeyValuePair<const Brx&>& aName);
    void VisibleChanged(Configuration::KeyValuePair<TUint>& aKvp);
protected:
    TBool iActive;
private:
    mutable Mutex iLock;
    Bws<kMaxSystemNameBytes> iSystemName;
    Brn iType;
    Bws<kMaxSourceNameBytes> iName;
    TBool iVisible;

    IProduct* iProduct;
    Configuration::ConfigText* iConfigName;
    Configuration::ConfigChoice* iConfigVisible;
    TUint iConfigNameSubscriptionId;
    TUint iConfigVisibleSubscriptionId;
    TBool iConfigNameCreated;
    TBool iConfigVisibleCreated;
};

class Source : public SourceBase
{
protected:
    Source(const Brx& aSystemName, const TChar* aType, Media::PipelineManager& aPipeline, IPowerManager& aPowerManager);
    void DoPlay();
protected:
    Media::PipelineManager& iPipeline;
private:
    IPowerManager& iPowerManager;
};

} // namespace Av
} // namespace OpenHome

