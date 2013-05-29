#ifndef HEADER_RADIO_DATABASE
#define HEADER_RADIO_DATABASE

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Media/Msg.h>

#include <array>

namespace OpenHome {
class Environment;
namespace Av {

class IRadioDatbaseObserver
{
public:
    ~IRadioDatbaseObserver() {}
    virtual void RadioDatabaseChanged() = 0;
};

class IRadioDatabaseWriter
{
public:
    virtual ~IRadioDatabaseWriter() {}
    virtual TUint MaxNumPresets() const = 0;
    virtual void BeginSetPresets() = 0;
    virtual void SetPreset(TUint aIndex, const Brx& aMetaData) = 0;
    virtual void ClearPreset(TUint aIndex) = 0;
    virtual void EndSetPresets() = 0;
};

class IRadioDatabaseReader
{
public:
    static const TUint kMaxPresets = 100;
    static const TUint kPresetIdNone = 0;
public:
    virtual void SetObserver(IRadioDatbaseObserver& aObserver) = 0;
    virtual void GetIdArray(std::array<TUint32, kMaxPresets>& aIdArray, TUint& aSeq) const = 0;
    virtual void GetPreset(TUint aIndex, TUint& aId, Bwx& aMetaData) const = 0;
    virtual TBool TryGetPresetById(TUint aId, Bwx& aMetaData) const = 0;
    virtual TBool TryGetPresetById(TUint aId, TUint aSeq, Bwx& aMetaData, TUint& aIndex) const = 0;
    virtual TBool TryGetPresetByMetaData(const Brx& aMetaData, TUint& aId) const = 0;
};

class RadioDatabase : public IRadioDatabaseWriter, public IRadioDatabaseReader
{
public:
    static const TUint kMaxPresets = 100;
    static const TUint kPresetIdNone = 0;
public:
    RadioDatabase();
    ~RadioDatabase();
    void SetPreset(TUint aIndex, const Brx& aMetaData, TUint& aId);
public: // from IRadioDatabaseReader
    void SetObserver(IRadioDatbaseObserver& aObserver);
    void GetIdArray(std::array<TUint32, kMaxPresets>& aIdArray, TUint& aSeq) const;
    void GetPreset(TUint aIndex, TUint& aId, Bwx& aMetaData) const;
    TBool TryGetPresetById(TUint aId, Bwx& aMetaData) const;
    TBool TryGetPresetById(TUint aId, TUint aSeq, Bwx& aMetaData, TUint& aIndex) const;
    TBool TryGetPresetByMetaData(const Brx& aMetaData, TUint& aId) const;
public: // from IRadioDatabaseWriter
    TUint MaxNumPresets() const;
    void BeginSetPresets();
    void SetPreset(TUint aIndex, const Brx& aMetaData);
    void ClearPreset(TUint aIndex); // FIXME - could be inlined if we care
    void EndSetPresets();
private:
    class Preset
    {
    public:
        Preset();
        void Set(TUint aId, const Brx& aMetaData);
        TUint Id() const { return iId; }
        const Brx& MetaData() const { return iMetaData; }
    private:
        TUint iId;
        Media::BwsTrackMetaData iMetaData;
    };
private:
    mutable Mutex iLock;
    IRadioDatbaseObserver* iObserver;
    Preset iPresets[kMaxPresets];
    TUint iNextId;
    TUint iSeq;
    TBool iUpdated;
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_RADIO_DATABASE
