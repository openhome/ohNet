#ifndef HEADER_PRESET_DATABASE
#define HEADER_PRESET_DATABASE

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Media/Msg.h>

#include <array>

namespace OpenHome {
class Environment;
namespace Av {

class IPresetDatabaseObserver
{
public:
    ~IPresetDatabaseObserver() {}
    virtual void PresetDatabaseChanged() = 0;
};

class IPresetDatabaseWriter
{
public:
    virtual ~IPresetDatabaseWriter() {}
    virtual TUint MaxNumPresets() const = 0;
    virtual void BeginSetPresets() = 0;
    virtual void SetPreset(TUint aIndex, const Brx& aMetaData) = 0;
    virtual void ClearPreset(TUint aIndex) = 0;
    virtual void EndSetPresets() = 0;
};

class IPresetDatabaseReader
{
public:
    static const TUint kMaxPresets = 100;
    static const TUint kPresetIdNone = 0;
public:
    virtual ~IPresetDatabaseReader() {}
    virtual void SetObserver(IPresetDatabaseObserver& aObserver) = 0;
    virtual void GetIdArray(std::array<TUint32, kMaxPresets>& aIdArray, TUint& aSeq) const = 0;
    virtual void GetPreset(TUint aIndex, TUint& aId, Bwx& aMetaData) const = 0;
    virtual TBool TryGetPresetById(TUint aId, Bwx& aMetaData) const = 0;
    virtual TBool TryGetPresetById(TUint aId, TUint aSeq, Bwx& aMetaData, TUint& aIndex) const = 0;
    virtual TBool TryGetPresetByMetaData(const Brx& aMetaData, TUint& aId) const = 0;
};

class PresetDatabase : public IPresetDatabaseWriter, public IPresetDatabaseReader
{
public:
    static const TUint kMaxPresets = 100;
    static const TUint kPresetIdNone = 0;
public:
    PresetDatabase();
    ~PresetDatabase();
    void SetPreset(TUint aIndex, const Brx& aMetaData, TUint& aId);
public: // from IPresetDatabaseReader
    void SetObserver(IPresetDatabaseObserver& aObserver);
    void GetIdArray(std::array<TUint32, kMaxPresets>& aIdArray, TUint& aSeq) const;
    void GetPreset(TUint aIndex, TUint& aId, Bwx& aMetaData) const;
    TBool TryGetPresetById(TUint aId, Bwx& aMetaData) const;
    TBool TryGetPresetById(TUint aId, TUint aSeq, Bwx& aMetaData, TUint& aIndex) const;
    TBool TryGetPresetByMetaData(const Brx& aMetaData, TUint& aId) const;
public: // from IPresetDatabaseWriter
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
    IPresetDatabaseObserver* iObserver;
    Preset iPresets[kMaxPresets];
    TUint iNextId;
    TUint iSeq;
    TBool iUpdated;
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_PRESET_DATABASE
