#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Media/Pipeline/Msg.h>

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
    virtual void SetPreset(TUint aIndex, const Brx& aUri, const Brx& aMetaData) = 0;
    virtual void ReadPreset(TUint aIndex, Bwx& aUri, Bwx& aMetaData) = 0; // required to enable writers to check for near duplicates
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
    virtual void AddObserver(IPresetDatabaseObserver& aObserver) = 0;
    virtual void GetIdArray(std::array<TUint32, kMaxPresets>& aIdArray, TUint& aSeq) const = 0;
    virtual void GetPreset(TUint aIndex, TUint& aId, Bwx& aMetaData) const = 0;
    virtual TBool TryGetPresetById(TUint aId, Bwx& aMetaData) const = 0;
    virtual TBool TryGetPresetById(TUint aId, Bwx& aUri, Bwx& aMetaData) const = 0;
    virtual TBool TryGetPresetById(TUint aId, TUint aSeq, Bwx& aMetaData, TUint& aIndex) const = 0;
    virtual TBool TryGetPresetByMetaData(const Brx& aMetaData, TUint& aId) const = 0;

    //virtual TUint GetPresetId(TUint aPresetNumber) const = 0;
    //virtual TUint GetPresetNumber(TUint aPresetId) const = 0;
};

class PresetDatabase : public IPresetDatabaseWriter, public IPresetDatabaseReader
{
public:
    static const TUint kMaxPresets = 100;
    static const TUint kPresetIdNone = 0;
public:
    PresetDatabase();
    ~PresetDatabase();
    void SetPreset(TUint aIndex, const Brx& aUri, const Brx& aMetaData, TUint& aId);
public: // from IPresetDatabaseReader
    void AddObserver(IPresetDatabaseObserver& aObserver) override;
    void GetIdArray(std::array<TUint32, kMaxPresets>& aIdArray, TUint& aSeq) const override;
    void GetPreset(TUint aIndex, TUint& aId, Bwx& aMetaData) const override;
    TBool TryGetPresetById(TUint aId, Bwx& aMetaData) const override;
    TBool TryGetPresetById(TUint aId, Bwx& aUri, Bwx& aMetaData) const override;
    TBool TryGetPresetById(TUint aId, TUint aSeq, Bwx& aMetaData, TUint& aIndex) const override;
    TBool TryGetPresetByMetaData(const Brx& aMetaData, TUint& aId) const override;
public: // from IPresetDatabaseWriter
    TUint MaxNumPresets() const override;
    void BeginSetPresets() override;
    void SetPreset(TUint aIndex, const Brx& aUri, const Brx& aMetaData) override;
    void ReadPreset(TUint aIndex, Bwx& aUri, Bwx& aMetaData) override; // required to enable writers to check for near duplicates
    void ClearPreset(TUint aIndex) override;
    void EndSetPresets() override;
private:
    class Preset
    {
        static const TUint kMaxMetaDataBytes = 1024 * 2;
    public:
        Preset();
        void Set(TUint aId, const Brx& aUri, const Brx& aMetaData);
        TUint Id() const { return iId; }
        const Brx& Uri() const { return iUri; }
        const Brx& MetaData() const { return iMetaData; }
    private:
        TUint iId;
        Media::BwsTrackUri iUri;
        Bws<kMaxMetaDataBytes> iMetaData;
    };
private:
    mutable Mutex iLock;
    std::vector<IPresetDatabaseObserver*> iObservers;
    Preset iPresets[kMaxPresets];
    TUint iNextId;
    TUint iSeq;
    TBool iUpdated;
};

} // namespace Av
} // namespace OpenHome

