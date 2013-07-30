#ifndef HEADER_VOLUME_MANAGER
#define HEADER_VOLUME_MANAGER

#include <OpenHome/OhNetTypes.h>

#include <OpenHome/Private/Standard.h>

//
// volume elements are linearly chained and any contributing change
// propagates downstream to actual HW driver via SetVolume() calls;
// invidual volume elements have specific methods to set their contribution
//
// [defaults]                mibidB         on/off        -15..+15    +--> [VolLim] --> [HW] .
//                              |              |             |       /                       .
// 0..100 --> [UserVol] --> [SrcOff] --> [UnityGain] --> [Balance] -+                        .
//                                                                   \                       .
//            where --> means SetVolume(TUint)                        +--> [VolLim] --> [HW] .
//
// for best audio performance, SetVolume() for volume propagation and Set*() for parameter
// adjustment, respectively, should not supply the same value in consecutive calls
// (i.e. invocations should always signal genuine change)
//
// client code is free to choose an appropriate scale factor for converting from user
// to system volume and must apply this consistently whenever volume offsets, etc.
// are supplied in invocations;  classes are provided that encapsulate sensible
// default factors and value ranges
//

namespace OpenHome {
namespace Media {

//
// generic class declarations
//

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
    VolumeUser(IVolume& aVolume, TUint aScaleFactor);
    // fixed operation, not dynamically parameterised
public:  // from IVolume
    void SetVolume(TUint aValue);
private:
    IVolume& iVolume;
    TUint iScaleFactor;
};

// apply source-specific volume correction
class VolumeSourceOffset : public IVolume, public INonCopyable
{
public:
    VolumeSourceOffset(IVolume& aVolume);
    void SetOffset(TUint aValue);  // system volume
public:  // from IVolume
    void SetVolume(TUint aValue);
private:
    void Changed();
private:
    IVolume& iVolume;
    TUint iUpstreamVolume;
    TUint iSourceOffset;
};

// switch between pass-through and override with unity gain
class VolumeUnityGain : public IVolume, public INonCopyable
{
public:
    VolumeUnityGain(IVolume& aVolume, TUint aUnityGainSystemValue);
    void SetUnityGain(bool aValue);
public:  // from IVolume
    void SetVolume(TUint aValue);
private:
    void Changed();
private:
    IVolume& iVolume;
    TUint iUnityGainSystemVolume;
    TUint iUpstreamVolume;
    bool iEnabled;
};

// balance: fan out = 2 (XXX generalise for multichannel)
class VolumeBalance : public IVolume, public INonCopyable
{
public:
    VolumeBalance(IVolume& aLeftVolume, IVolume& aRightVolume);
    void SetBalance(TInt aLeftOffset, TInt aRightOffset);
public:  // from IVolume
    void SetVolume(TUint aValue);
private:
    void Changed();
private:
    IVolume& iLeftVolume;
    IVolume& iRightVolume;
    TUint iUpstreamVolume;
    TInt iLeftOffset;
    TInt iRightOffset;
};

// limiter: clip any excess volume
class VolumeLimiter: public IVolume, public INonCopyable
{
public:
    VolumeLimiter(IVolume& aVolume, TUint aLimit);  // system volume
    // fixed operation, not dynamically parameterised
public:  // from IVolume
    void SetVolume(TUint aValue);
private:
    void Changed();
private:
    IVolume& iVolume;
    TUint iUpstreamVolume;
    TUint iLimit;
};

//
// class declarations with default factors and value ranges
//

class VolumeUserDefault : public VolumeUser
{
public:
    // system volume:  [0, 100*1024]  (i.e. steps of binary milli decibel)
    static TUint SystemVolumeFactor();
    // user volume:    [0, 100]
    static TUint MaxSystemVolume();
public:
    VolumeUserDefault(IVolume& aVolume);
};

class VolumeUnityGainDefault : public VolumeUnityGain
{
public:
    static TUint UnityGainSystemVolume();
public:
    VolumeUnityGainDefault(IVolume& aVolume);
};

class VolumeBalanceUserDefault : public IVolume
{
public:
    static TInt MinimumUserBalance();  // -15 = amplify left, attenuate right
    static TInt MaximumUserBalance();  // +15 = attenuate left, amplify right
public:
    VolumeBalanceUserDefault(IVolume& aLeftVolume, IVolume& aRightVolume);
    void SetBalance(TInt aValue);
public:  // from IVolume
    void SetVolume(TUint aValue);
private:
    static const TInt kBalanceOffsets[];
private:
    VolumeBalance iVolumeBalance;
};

class VolumeLimiterDefault : public VolumeLimiter
{
public:
    static TUint MaxLimitSystemVolume();
public:
    VolumeLimiterDefault(IVolume& aVolume);
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_VOLUME_MANAGER
