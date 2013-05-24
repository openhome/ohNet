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

class RadioDatabase : public IRadioDatabaseWriter
{
public:
    static const TUint kMaxPresets = 100;
    static const TUint kPresetIdNone = 0;
public:
    RadioDatabase(IRadioDatbaseObserver& aObserver);
    ~RadioDatabase();
    void GetIdArray(std::array<TUint, kMaxPresets>& aIdArray) const;
    TUint SequenceNumber() const;
    void GetPreset(TUint aIndex, TUint& aId, Bwx& aMetaData) const;
    TBool TryGetPresetById(TUint aId, Bwx& aMetaData) const;
    TBool TryGetPresetById(TUint aId, TUint aSequenceNumber, Bwx& aMetaData, TUint& aIndex) const;
    void SetPreset(TUint aIndex, const Brx& aMetaData, TUint& aId);
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
    IRadioDatbaseObserver& iObserver;
    Preset iPresets[kMaxPresets];
    TUint iNextId;
    TUint iSeq;
    TBool iUpdated;
};

class NullRadioDatbaseObserver : public IRadioDatbaseObserver
{
private: // from IRadioDatbaseObserver
    void RadioDatabaseChanged() {}
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_RADIO_DATABASE
