#ifndef HEADER_VOLUME_MANAGER
#define HEADER_VOLUME_MANAGER

#include <OpenHome/OhNetTypes.h>

#include <OpenHome/Private/Standard.h>

//
// user balance:   [-15, +15]
// user volume:    [0, 100]
// system volume:  [0, 100*1024]
//
// volume elements are linearly chained and any contributing change
// propagates downstream to actual HW driver via SetVolume() calls;
// invidual volume elements have specific methods to set their contribution
//
// .   0..100        mibidB         on/off       -15..+15    --> [VolLim] --> [HW] .
// .     |             |              |             |       /                      .
// . [UserVol] --> [SrcOff] --> [UnityGain] --> [Balance] -+                       .
// .                                                        \                      .
// . where --> means SetVolume(TUint)                        --> [VolLim] --> [HW] .
//


namespace OpenHome {
namespace Media {

// fundamental interface
class IVolume
{
public:
    virtual ~IVolume();
    // steps of binary milli decibel (2^-10 dB)
    // by def (Linn):  80 * 2^10 mibidB := 0 dB = unity gain
    virtual void SetVolume(TUint amibidB) = 0;
};

// translate user-visible volume setting into internal scale
class VolumeUser : public IVolume, public INonCopyable
{
public:
    VolumeUser(IVolume& aVolume);
    void SetUserVolume(TUint aUserVolume);  // [0..100]
public:  // from IVolume
    void SetVolume(TUint amibidB);
private:
    IVolume& iVolume;
    TUint iUpstreamVolume;
    TUint iUserVolume_mibidB;
};

// apply source-specific volume correction
class VolumeSourceOffset : public IVolume, public INonCopyable
{
public:
    VolumeSourceOffset(IVolume& aVolume);
    void SetOffset(TUint amibidB);  // system units
public:  // from IVolume
    void SetVolume(TUint amibidB);
private:
    IVolume& iVolume;
    TUint iUpstreamVolume;
    TUint iSourceOffset;
};

// switch between pass-through and override with unity gain
class VolumeUnityGain : public IVolume, public INonCopyable
{
public:
    static const TUint skVolumeUnity = 80 * (1 << 10);
public:
    VolumeUnityGain(IVolume& aVolume);
    void SetUnityGain(bool aEnabled);  // on/off
public:  // from IVolume
    void SetVolume(TUint amibidB);
private:
    IVolume& iVolume;
    TUint iUpstreamVolume;
    bool iEnabled;
};

// balance: fan out = 2 (XXX generalise for multichannel)
class VolumeBalance : public IVolume, public INonCopyable
{
public:
    VolumeBalance(IVolume& aLeftVolume, IVolume& aRightVolume);
    void SetBalance(TInt aUserBalance);  // [-15..+15]
public:  // from IVolume
    void SetVolume(TUint amibidB);
private:
    IVolume& iLeftVolume;
    IVolume& iRightVolume;
    TUint iUpstreamVolume;
    TUint iLeftBalance_mibidB;
    TUint iRightBalance_mibidB;
};

// limiter: clip any excess volume
class VolumeLimiter: public IVolume, public INonCopyable
{
public:
    static const TUint skVolumeMax = 100 * (1 << 10);
public:
    VolumeLimiter(IVolume& aVolume);
    // fixed operation, not parameterised
public:  // from IVolume
    void SetVolume(TUint amibidB);
private:
    IVolume& iVolume;
    TUint iUpstreamVolume;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_VOLUME_MANAGER
