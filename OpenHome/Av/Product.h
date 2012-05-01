#ifndef HEADER_PRODUCT
#define HEADER_PRODUCT

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Net/Core/DvDevice.h>

#include <vector>

EXCEPTION(AvSourceNotFound);

namespace OpenHome {
namespace Av {

class IInfoProvider // move elsewhere?
{
public:
    virtual void QueryInfo(const Brx& aQuery, IWriter& aWriter) = 0;
};

class IReadStore;
class Source;
class ProviderProduct;

class Product : /*public IInfoProvider, */private INonCopyable
{
public:
    static const TUint kMaxNameBytes = 20;
    static const TUint kMaxRoomBytes = 20;
public:
    Product(Net::DvDevice& aDevice, IReadStore& aReadStore);
    ~Product();
    void Start();
    void AddSource(Source* aSource);
    void GetManufacturerDetails(Brn& aName, Brn& aInfo, Brn& aUrl, Brn& aImageUri);
    void GetModelDetails(Brn& aName, Brn& aInfo, Brn& aUrl, Brn& aImageUri);
    void GetProductDetails(Bwx& aRoom, Bwx& aName, Brn& aInfo, Brn& aImageUri);
    // Standby [g|s]etter tbd
    TUint SourceCount() const;
    TUint CurrentSourceIndex() const;
    //void GetSourceListAsXml(Brh& aXml); // move into provider
    void SetCurrentSource(TUint aIndex);
    void SetCurrentSource(const Brx& aName);
    void GetSourceDetails(TUint aIndex, Bwx& aSystemName, Bwx& aType, Bwx& aName, TBool& aVisible);
    //void Attributes tbd
    TUint SourceXmlChangeCount();
private:
    Net::DvDevice& iDevice; // do we need to store this?
    IReadStore& iReadStore;
    Mutex iLock;
    ProviderProduct* iProviderProduct;
    std::vector<Source*> iSources;
    TBool iStarted;
    TUint iCurrentSource;
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_PRODUCT
