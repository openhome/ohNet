#ifndef HEADER_MUTE_MANAGER
#define HEADER_MUTE_MANAGER

#include <OpenHome/OhNetTypes.h>

#include <OpenHome/Private/Thread.h>  // Mutex

#include <vector>

namespace OpenHome {
namespace Media {

// element interface
class IMute
{
public:
    virtual ~IMute();
    virtual void Mute() = 0;
    virtual void Unmute() = 0;
};

// reference-counting base class (does not own wrapped IMute element)
class MuteCounted : public IMute, public INonCopyable
{
public:
    MuteCounted(IMute& aMute);

public:  // from IMute
    void Mute();
    void Unmute();

private:
    IMute& iMute;
    TUint iCount;
};

// collection does not own individual IMute elements
class MuteCollection : public IMute
{
public:
    MuteCollection();
    void Add(IMute& aMute);

public:  // from IMute
    void Mute();
    void Unmute();

private:
    std::vector<IMute*> iMuteChain;
};

// dummy mute element
// generic code may expect lookup of particular mute by name to succeed
// even when hardware does not actually provide capability
class MuteNull : public IMute
{
public:  // from IMute
    void Mute();
    void Unmute();
};

// manager interface
class IMuteManager
{
public:
    virtual ~IMuteManager();
    virtual IMute& Find(const TChar* aName) const = 0;
};

// concrete manager (for loose coupling in generic code)
// does not own individual IMute elements
class MuteSafe;

class MuteManager : public IMuteManager
{
public:
    MuteManager();
    ~MuteManager();
    // only directly constructed objects must be registered,
    // i.e. do not Add() anything returned by Find()
    void Add(const TChar* aName, IMute& aMute);
public:  // from IMuteManager
    IMute& Find(const TChar* aName) const;

private:
    std::vector<MuteSafe*> iMuteCollection;
    mutable Mutex iMutex;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_MUTE_MANAGER
