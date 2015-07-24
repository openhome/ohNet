#include <OpenHome/Media/MuteManager.h>
#include <OpenHome/Buffer.h>

#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Standard.h>

using namespace OpenHome;
using namespace OpenHome::Media;

//
// reference-counting base class
//

// XXX thread-safety for MuteCounted
//
// implicit assumption:  not in fact used directly by client, but always
//     (a) part of collection (see below);  or
//     (b) directly reg'd w/ MuteManager (and hence silently wrapped in MuteSafe)
MuteCounted::MuteCounted(IMute& aMute)
    : iMute(aMute)
    , iCount(0)
{
}

void MuteCounted::Mute()
{
    // XXX integer overflow (unlikely)
    ++iCount;
    if (1 == iCount) {
        iMute.Mute();
    }
}

void MuteCounted::Unmute()
{
    ASSERT(iCount > 0);  // integer underflow: programmer error
    --iCount;
    if (0 == iCount) {
        iMute.Unmute();
    }
}

//
// collection
//

MuteCollection::MuteCollection()
    : iMuteChain()
{
}

//
// XXX thread-safety for MuteCollection
//
// individual elements will NOT be wrapped in MuteSafe (hidden impl)
// implicit assumption:  collection built up at start-up and never changed after first use
// Add():  implicit assumption that each collection is built up by single thread?!
// Mute()/Unmute():  implicit assumption that collection is reg'd (and wrapped) by MuteManager?!
//     if so: wrapped collection will acquire lock and complete traversal w/o intervening ops
void MuteCollection::Add(IMute& aMute)
{
    iMuteChain.push_back(&aMute);
}

void MuteCollection::Mute()
{
    for (TUint i = 0; i < iMuteChain.size(); ++i) {
        iMuteChain[i]->Mute();
    }
}

void MuteCollection::Unmute()
{
    for (TInt i = iMuteChain.size() - 1; i >= 0; --i) {
        iMuteChain[i]->Unmute();
    }
}

//
// dummy mute element
//

MuteNull::MuteNull()
    : iObserver(nullptr)
    , iMuted(false)
{
    // NOP
}

// XXX not thread-safe
void MuteNull::Mute()
{
    TBool changed = (iMuted != true);
    iMuted = true;
    if (changed && (iObserver != nullptr)) {
        iObserver->MuteChanged(iMuted);
    }
}

// XXX not thread-safe
void MuteNull::Unmute()
{
    TBool changed = (iMuted != false);
    iMuted = false;
    if (changed && (iObserver != nullptr)) {
        iObserver->MuteChanged(iMuted);
    }
}

void MuteNull::SetObserver(IMuteObserver& aObserver)
{
    iObserver = &aObserver;
}

//
// manager
//

namespace OpenHome {
namespace Media {

// (subsystem) concurrency control wrapper (implementation detail of MuteManager)
class MuteSafe : public IMute
{
public:
    MuteSafe(const TChar* aName, IMute& aMute, Mutex& aMutex);
    const Brx& Name() const;

public:  // from IMute
    void Mute();
    void Unmute();

private:
    Mutex& iMutex;  // non-recursive
    IMute& iMute;
    Bws<32> iName;
};

MuteSafe::MuteSafe(const TChar* aName, IMute& aMute, Mutex& aMutex)
    : iMutex(aMutex)
    , iMute(aMute)
{
    iName.Replace(aName);
}

const Brx& MuteSafe::Name() const
{
    return iName;
}

void MuteSafe::Mute()
{
    AutoMutex mutex(iMutex);
    iMute.Mute();
}

void MuteSafe::Unmute()
{
    AutoMutex mutex(iMutex);
    iMute.Unmute();
}

} // namespace Media
} // namespace OpenHome

// concrete manager
MuteManager::MuteManager()
    : iMuteCollection()
    , iMutex("MUTE")
{
}

MuteManager::~MuteManager()
{
    while (!iMuteCollection.empty()) {
        delete iMuteCollection.back();
        iMuteCollection.pop_back();
    }
}

// XXX implicit assumption:  aMute not already wrapped in MuteSafe
void MuteManager::Add(const TChar* aName, IMute& aMute)
{
    AutoMutex mutex(iMutex);
    // clients expected to invoke this only at start-up time,
    // so no concerns over dynamic memory allocation
    iMuteCollection.push_back(new MuteSafe(aName, aMute, iMutex));
}

IMute& MuteManager::Find(const TChar* aName) const
{
    AutoMutex mutex(iMutex);

    IMute* mute = nullptr;

    for (TUint i = 0; i < iMuteCollection.size(); ++i) {
        if (iMuteCollection[i]->Name() == Brn(aName)) {
            // do not unwrap, since implicit locking desired
            mute = iMuteCollection[i];
            break;
        }
    }

    ASSERT(mute != nullptr);

    return (*mute);
}
