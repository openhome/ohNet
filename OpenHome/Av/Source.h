#ifndef HEADER_SOURCE
#define HEADER_SOURCE

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Media/InfoProvider.h>
#include <OpenHome/Configuration/ConfigManager.h>

namespace OpenHome {
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
    virtual const Brx& Name() const = 0;
    virtual TBool IsVisible() const = 0;
    virtual void Activate() = 0;
    virtual void Deactivate() = 0;
    virtual void SetVisible(TBool aVisible) = 0;
    virtual void PipelineStopped() = 0;
private:
    virtual void Initialise(IProduct& aProduct, Configuration::IConfigManagerInitialiser& aConfigInit, Configuration::IConfigManagerReader& aConfigManagerReader, TUint aId) = 0;
};

class Source : public ISource/*, protected IInfoProvider*/
{
private:
    static const TUint kMaxSourceTypeBytes = 20;
    static const TUint kMaxSourceIndexDigits = 2; // assume a source count of 0..99 is reasonable
    static const OpenHome::Brn kSourceNameKeyPrefix;
    static const OpenHome::Brn kSourceNameKeySuffix;
protected: // from ISource
    const Brx& SystemName() const;
    const Brx& Type() const;
    const Brx& Name() const;
    TBool IsVisible() const;
    void Deactivate();
    void SetVisible(TBool aVisible);
protected:
    Source(const TChar* aSystemName, const TChar* aType);
    ~Source();
    TBool IsActive() const;
    void DoActivate();
private: // from ISource
    void Initialise(IProduct& aProduct, Configuration::IConfigManagerInitialiser& aConfigInit, Configuration::IConfigManagerReader& aConfigManagerReader, TUint aId);
private:
    void NameChanged(Configuration::KeyValuePair<const Brx&>& aName);
protected:
    TBool iActive;
private:
    Mutex iLock;
    Brn iSystemName;
    Brn iType;
    Bws<kMaxSourceNameBytes> iName;
    TBool iVisible;

    IProduct* iProduct;
    Configuration::ConfigText* iConfigName;
    TUint iConfigNameSubscriptionId;
    TBool iConfigNameCreated;
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_SOURCE
