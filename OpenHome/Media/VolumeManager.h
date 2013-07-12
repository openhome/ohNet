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
// .                            mibidB         on/off       -15..+15     --> [VolLim] --> [HW] .
// .                               |              |             |       /                      .
// .  0..100 --> [UserVol] --> [SrcOff] --> [UnityGain] --> [Balance] -+                       .
// .                                                                    \                      .
// .            where --> means SetVolume(TUint)                         --> [VolLim] --> [HW] .
//


namespace OpenHome {
namespace Media {

// fundamental interface
class IVolume
{
public:
    virtual ~IVolume();
    virtual void SetVolume(TUint aValue) = 0;
};

// translate user-visible volume setting into internal scale
class VolumeUser : public IVolume, public INonCopyable
{
public:
    VolumeUser(IVolume& aVolume);
public:  // from IVolume
    void SetVolume(TUint aValue);
private:
    IVolume& iVolume;
};

// apply source-specific volume correction
class VolumeSourceOffset : public IVolume, public INonCopyable
{
public:
    VolumeSourceOffset(IVolume& aVolume);
    void SetOffset(TUint aValue);
public:  // from IVolume
    void SetVolume(TUint aValue);
private:
    IVolume& iVolume;
    TUint iUpstreamVolume;
    TUint iSourceOffset;
};

// switch between pass-through and override with unity gain
class VolumeUnityGain : public IVolume, public INonCopyable
{
public:
    static const TUint kVolumeUnity = 80 * 1024;
public:
    VolumeUnityGain(IVolume& aVolume);
    void SetUnityGain(bool aValue);
public:  // from IVolume
    void SetVolume(TUint aValue);
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
    void SetVolume(TUint aValue);
private:
    IVolume& iLeftVolume;
    IVolume& iRightVolume;
    TUint iUpstreamVolume;
    TUint iLeftOffset;
    TUint iRightOffset;
};

// limiter: clip any excess volume
class VolumeLimiter: public IVolume, public INonCopyable
{
public:
    VolumeLimiter(IVolume& aVolume, TUint aLimit);
    // fixed operation, not parameterised
public:  // from IVolume
    void SetVolume(TUint aValue);
private:
    IVolume& iVolume;
    TUint iUpstreamVolume;
	TUint iLimit;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_VOLUME_MANAGER
