#ifndef HEADER_SOURCE
#define HEADER_SOURCE

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Av/InfoProvider.h>

namespace OpenHome {
namespace Av {

class Source : protected IInfoProvider
{
public:
    static const TUint kMaxSystemNameBytes = 20;
    static const TUint kMaxSourceNameBytes = 20;
    static const TUint kMaxSourceTypeBytes = 20;
    static const TUint kMaxAttributesBytes = 100;
public:
    virtual ~Source();
    const Brx& SystemName() const;
    const Brx& Type() const;
    const Brx& Name() const;
    TBool IsVisible() const;
    virtual void Enable() = 0;
    virtual void Disable() = 0;
    // ?? protected void QueryInfo(const Brx& aQuery, IWriter& aWriter);
protected:
    Source(const TChar* aSystemName, const TChar* aType);
private:
    Brn iSystemName;
    Brn iType;
    Bws<kMaxSourceNameBytes> iName;
    TBool iVisible;
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_SOURCE
