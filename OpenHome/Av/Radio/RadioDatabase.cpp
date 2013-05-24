#include <OpenHome/Av/Radio/RadioDatabase.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Media/Msg.h>

#include <array>

using namespace OpenHome;
using namespace OpenHome::Av;

// RadioDatabase

RadioDatabase::RadioDatabase(IRadioDatbaseObserver& aObserver)
    : iLock("RADB")
    , iObserver(aObserver)
    , iNextId(kPresetIdNone + 1)
    , iSeq(0)
    , iUpdated(false)
{
}

RadioDatabase::~RadioDatabase()
{
}

void RadioDatabase::GetIdArray(std::array<TUint, kMaxPresets>& aIdArray) const
{
    iLock.Wait();
    for (TUint i=0; i<kMaxPresets; i++) {
        aIdArray[i] = iPresets[i].Id();
    }
    iLock.Signal();
}

TUint RadioDatabase::SequenceNumber() const
{
    return iSeq;
}

void RadioDatabase::GetPreset(TUint aIndex, TUint& aId, Bwx& aMetaData) const
{
    ASSERT(aIndex < kMaxPresets);
    iLock.Wait();
    const Preset& preset = iPresets[aIndex];
    aId = preset.Id();
    aMetaData.Replace(preset.MetaData());
    iLock.Signal();
}

TBool RadioDatabase::TryGetPresetById(TUint aId, Bwx& aMetaData) const
{
    AutoMutex a(iLock);
    for (TUint i=0; i<kMaxPresets; i++) {
        if (iPresets[i].Id() == aId) {
            aMetaData.Replace(iPresets[i].MetaData());
            return true;
        }
    }
    return false;
}

TBool RadioDatabase::TryGetPresetById(TUint aId, TUint aSequenceNumber, Bwx& aMetaData, TUint& aIndex) const
{
    AutoMutex a(iLock);
    if (iSeq != aSequenceNumber) {
        return TryGetPresetById(aId, aMetaData);
    }
    for (TUint i=aIndex+1; i<kMaxPresets; i++) {
        if (iPresets[i].Id() == aId) {
            aMetaData.Replace(iPresets[i].MetaData());
            aIndex = i;
            return true;
        }
    }
    return false;
}

void RadioDatabase::SetPreset(TUint aIndex, const Brx& aMetaData, TUint& aId)
{
    iLock.Wait();
    Preset& preset = iPresets[aIndex];
    aId = preset.Id();
    if (preset.MetaData() != aMetaData) {
        aId = iNextId++;
        preset.Set(aId, aMetaData);
        iSeq++;
    }
    iLock.Signal();
}

TUint RadioDatabase::MaxNumPresets() const
{
    return kMaxPresets;
}

void RadioDatabase::BeginSetPresets()
{
}

void RadioDatabase::SetPreset(TUint aIndex, const Brx& aMetaData)
{
    TUint ignore;
    SetPreset(aIndex, aMetaData, ignore);
}

void RadioDatabase::ClearPreset(TUint aIndex)
{
    (void)SetPreset(aIndex, Brx::Empty());
}

void RadioDatabase::EndSetPresets()
{
    iLock.Wait();
    const TBool updated = iUpdated;
    iUpdated = false;
    iLock.Signal();
    if (updated) {
        iObserver.RadioDatabaseChanged();
    }
}


// RadioDatabase::Preset

RadioDatabase::Preset::Preset()
    : iId(kPresetIdNone)
{
}

void RadioDatabase::Preset::Set(TUint aId, const Brx& aMetaData)
{
    iId = aId;
    Brn metaData(aMetaData);
    if (metaData.Bytes() > iMetaData.MaxBytes()) {
        metaData.Split(iMetaData.MaxBytes());
    }
    iMetaData.Replace(metaData);
}
