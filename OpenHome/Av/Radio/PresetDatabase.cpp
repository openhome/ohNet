#include <OpenHome/Av/Radio/PresetDatabase.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Media/Pipeline/Msg.h>

#include <array>

using namespace OpenHome;
using namespace OpenHome::Av;

// PresetDatabase

PresetDatabase::PresetDatabase()
    : iLock("RADB")
    , iNextId(kPresetIdNone + 1)
    , iSeq(0)
    , iUpdated(false)
{
}

PresetDatabase::~PresetDatabase()
{
}

void PresetDatabase::AddObserver(IPresetDatabaseObserver& aObserver)
{
    iObservers.push_back(&aObserver);
}

void PresetDatabase::GetIdArray(std::array<TUint32, kMaxPresets>& aIdArray, TUint& aSeq) const
{
    iLock.Wait();
    for (TUint i=0; i<kMaxPresets; i++) {
        aIdArray[i] = (TUint32)iPresets[i].Id();
    }
    aSeq = iSeq;
    iLock.Signal();
}

void PresetDatabase::GetPreset(TUint aIndex, TUint& aId, Bwx& aMetaData) const
{
    ASSERT(aIndex < kMaxPresets);
    iLock.Wait();
    const Preset& preset = iPresets[aIndex];
    aId = preset.Id();
    aMetaData.Replace(preset.MetaData());
    iLock.Signal();
}

TUint PresetDatabase::GetPresetId(TUint aPresetNumber) const
{
	if (aPresetNumber == 0 || aPresetNumber > kMaxPresets) {
		return kPresetIdNone;
	}
	TUint id;
	TUint index = aPresetNumber - 1;

	iLock.Wait();
	const Preset& preset = iPresets[index];
	id = preset.Id();
	iLock.Signal();

	return id;
}

TUint PresetDatabase::GetPresetNumber(TUint aPresetId) const
{
	AutoMutex a(iLock);
	for (TUint i=0; i<kMaxPresets; i++) {
		if (iPresets[i].Id() == aPresetId) {
			return (i+1);
		}
	}
	return kPresetIdNone;
}

TBool PresetDatabase::TryGetPresetById(TUint aId, Bwx& aMetaData) const
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

TBool PresetDatabase::TryGetPresetById(TUint aId, Bwx& aUri, Bwx& aMetaData) const
{
    AutoMutex a(iLock);
    for (TUint i=0; i<kMaxPresets; i++) {
        if (iPresets[i].Id() == aId) {
            aUri.Replace(iPresets[i].Uri());
            aMetaData.Replace(iPresets[i].MetaData());
            return true;
        }
    }
    return false;
}

TBool PresetDatabase::TryGetPresetById(TUint aId, TUint aSeq, Bwx& aMetaData, TUint& aIndex) const
{
    AutoMutex a(iLock);
    if (iSeq != aSeq) {
        return TryGetPresetById(aId, aMetaData);
    }
    for (TUint i=aIndex; i<kMaxPresets; i++) {
        if (iPresets[i].Id() == aId) {
            aMetaData.Replace(iPresets[i].MetaData());
            aIndex = i;
            return true;
        }
    }
    for (TUint i=0; i<aIndex; i++) {
        if (iPresets[i].Id() == aId) {
            aMetaData.Replace(iPresets[i].MetaData());
            aIndex = i;
            return true;
        }
    }
    return false;
}

TBool PresetDatabase::TryGetPresetByMetaData(const Brx& aMetaData, TUint& aId) const
{
    // FIXME - this could be pretty slow
    aId = kPresetIdNone;
    AutoMutex a(iLock);
    for (TUint i=0; i<kMaxPresets; i++) {
        if (iPresets[i].MetaData() == aMetaData) {
            aId = iPresets[i].Id();
            return true;
        }
    }
    return false;
}

void PresetDatabase::SetPreset(TUint aIndex, const Brx& aUri, const Brx& aMetaData, TUint& aId)
{
    iLock.Wait();
    Preset& preset = iPresets[aIndex];
    aId = preset.Id();
    if (preset.MetaData() != aMetaData) {
        if (aMetaData == Brx::Empty()) {
            aId = kPresetIdNone;
        }
        else {
            aId = iNextId++;
        }
        preset.Set(aId, aUri, aMetaData);
        iSeq++;
        iUpdated = true;
    }
    iLock.Signal();
}

TUint PresetDatabase::MaxNumPresets() const
{
    return kMaxPresets;
}

void PresetDatabase::BeginSetPresets()
{
}

void PresetDatabase::SetPreset(TUint aIndex, const Brx& aUri, const Brx& aMetaData)
{
    TUint ignore;
    SetPreset(aIndex, aUri, aMetaData, ignore);
}

void PresetDatabase::ReadPreset(TUint aIndex, Bwx& aUri, Bwx& aMetaData)
{
    ASSERT(aIndex < kMaxPresets);
    aUri.Replace(iPresets[aIndex].Uri());
    aMetaData.Replace(iPresets[aIndex].MetaData());
}

void PresetDatabase::ClearPreset(TUint aIndex)
{
    (void)SetPreset(aIndex, Brx::Empty(), Brx::Empty());
}

void PresetDatabase::EndSetPresets()
{
    iLock.Wait();
    const TBool updated = iUpdated;
    iUpdated = false;
    iLock.Signal();
    if (updated) {
        for (auto it=iObservers.begin(); it!=iObservers.end(); ++it) {
            (*it)->PresetDatabaseChanged();
        }
    }
}


// PresetDatabase::Preset

PresetDatabase::Preset::Preset()
    : iId(kPresetIdNone)
{
}

void PresetDatabase::Preset::Set(TUint aId, const Brx& aUri, const Brx& aMetaData)
{
    iId = aId;
    iUri.Replace(aUri);
    Brn metaData(aMetaData);
    if (metaData.Bytes() > iMetaData.MaxBytes()) {
        metaData.Split(iMetaData.MaxBytes());
    }
    iMetaData.Replace(metaData);
}
