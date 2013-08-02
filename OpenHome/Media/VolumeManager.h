#ifndef HEADER_VOLUME_MANAGER
#define HEADER_VOLUME_MANAGER

#include <OpenHome/Buffer.h>
#include <OpenHome/OhNetTypes.h>

#include <OpenHome/Private/Standard.h>

//
// volume elements are linearly chained and any contributing change
// propagates downstream to actual HW driver via SetVolume() calls;
// invidual volume elements have specific methods to set their contribution
//
// [defaults]     0..100                        mibidB         on/off        -15..+15    +--> [VolLim] --> [HW] .
//                   |                             |              |             |       /                       .
// 0..100 --> [VolLimitUser] --> [VolUser] --> [SrcOff] --> [UnityGain] --> [Balance] -+                        .
//                                                                                      \                       .
//            where --> means SetVolume(TUint)                                           +--> [VolLim] --> [HW] .
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

// fundamental interfaces
class IVolume
{
public:
    virtual ~IVolume();
    virtual void SetVolume(TUint aValue) = 0;
};

class IVolumeUser
{
public:
    virtual TUint UserVolume() const = 0;
};

class IBalanceUser
{
public:
    virtual ~IBalanceUser();
    virtual TInt UserBalance() const = 0;
    virtual void SetUserBalance(TInt aValue) = 0;  // -ve, 0, +ve
};

class IVolumeLimitUser
{
public:
    virtual ~IVolumeLimitUser();
    virtual TUint UserVolumeLimit() const = 0;
    virtual void SetUserVolumeLimit(TUint aValue) = 0;
};

// XXX notifications: can volume, balance, etc. change other than through UPnP?
class IVolumeManager
{
public:
    virtual ~IVolumeManager();
    virtual TUint UserVolume() const = 0;
    virtual TInt UserBalance() const = 0;
    virtual TUint UserVolumeLimit() const = 0;
    virtual void SetUserVolume(TUint aValue) = 0;
    virtual void SetUserBalance(TInt aValue) = 0;
    virtual void SetUserVolumeLimit(TUint aValue) = 0;
};

// need to extend interface, since UPnP provider holds reference to single type
// that must be able to report/change volume settings as well as knowing about limits
class IVolumeManagerLimits : public IVolumeManager
{
public:
    virtual ~IVolumeManagerLimits();
    virtual TUint MaxUserVolume() const = 0;
    virtual TUint VolumeUnity() const = 0;
    virtual TUint VolumeSteps() const = 0;
    virtual TUint VolumeMilliDbPerStep() const = 0;
    virtual TInt MaxUserBalance() const = 0;
};

// limiter (of user volume)
class VolumeLimiterUser : public IVolume, public IVolumeLimitUser, public IVolumeUser, public INonCopyable
{
public:
    VolumeLimiterUser(IVolume& aVolume, TUint aLimit);
public:  // from IVolumeLimitUser
    TUint UserVolumeLimit() const;
    void SetUserVolumeLimit(TUint aValue);
public:  // from IVolumeUser
    TUint UserVolume() const;  // sic!
public:  // from IVolume
    void SetVolume(TUint aValue);
private:
    void Changed();
private:
    IVolume& iVolume;
    TUint iUpstreamVolume;
    TUint iLimit;
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
// abstract base class
class VolumeBalanceUser : public IVolume, public IBalanceUser, public INonCopyable
{
public:
    VolumeBalanceUser(IVolume& aLeftVolume, IVolume& aRightVolume);
public:  // from IBalanceUser
    TInt UserBalance() const;
    void SetUserBalance(TInt aValue);
public:  // from IVolume
    void SetVolume(TUint aValue);
protected:
    virtual TInt LeftOffset(TInt aValue) const = 0;
    virtual TInt RightOffset(TInt aValue) const = 0;
private:
    void Changed();
private:
    IVolume& iLeftVolume;
    IVolume& iRightVolume;
    TUint iUpstreamVolume;
    TInt iUserBalance;
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

class VolumeLimiterUserDefault : public VolumeLimiterUser
{
public:
    VolumeLimiterUserDefault(IVolume& aVolume);
};

class VolumeUserDefault : public VolumeUser
{
public:
    // user volume:    [0, 100]
    static TUint MaxUserVolume();
    // system volume:  [0, 100*1024]  (i.e. steps of binary milli decibel)
    static TUint SystemVolumeFactor();
    // user volume:    [0, 100], scaled by system volume factor
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

class VolumeBalanceUserDefault : public VolumeBalanceUser
{
public:
    static TInt MinimumUserBalance();  // -15 = amplify left, attenuate right
    static TInt MaximumUserBalance();  // +15 = attenuate left, amplify right
public:
    VolumeBalanceUserDefault(IVolume& aLeftVolume, IVolume& aRightVolume);
protected:  // from VolumeBalanceUser
    TInt LeftOffset(TInt aValue) const;
    TInt RightOffset(TInt aValue) const;
private:
    static const TInt kBalanceOffsets[];
};

class VolumeLimiterDefault : public VolumeLimiter
{
public:
    static TUint MaxLimitSystemVolume();
public:
    VolumeLimiterDefault(IVolume& aVolume);
};

//
// top-level class declarations
//

// abstract base class
class VolumeManager : public IVolumeManagerLimits, public INonCopyable
{
public:
    VolumeManager(IVolume& aLeftVolHardware, IVolume& aRightVolHardware);
public:  // from IVolumeManager
    TUint UserVolume() const;
    TInt UserBalance() const;
    TUint UserVolumeLimit() const;
    void SetUserVolume(TUint aValue);
    void SetUserBalance(TInt aValue);
    void SetUserVolumeLimit(TUint aValue);
public: // from IVolumeManagerLimits
    // no generic implementation of specific values and ranges
protected:
    IVolume& iLeftVolHw;  // hardware driver ref'd, but not owned by volume manager
    IVolume& iRightVolHw;
    VolumeLimiter* iLeftVolLimit;  // elements of volume chain owned by volume manager
    VolumeLimiter* iRightVolLimit;
    VolumeBalanceUser* iVolBal;
    VolumeUnityGain* iVolUnityGain;
    VolumeSourceOffset* iVolSrcOff;
    VolumeUser* iVolUser;
    VolumeLimiterUser* iVolLimitUser;
};

// concrete class with specific value limits
class VolumeManagerDefault : public VolumeManager
{
public:
    VolumeManagerDefault(IVolume& aLeftVolHardware, IVolume& aRightVolHardware);
    ~VolumeManagerDefault();
public:  // from IVolumeManagerLimits
    TUint MaxUserVolume() const;
    TUint VolumeUnity() const;
    TUint VolumeSteps() const;
    TUint VolumeMilliDbPerStep() const;
    TInt MaxUserBalance() const;
};

//
// logging volume sink (stub implementations only)
//

class VolumeSinkLogger : public IVolume
{
public:
    VolumeSinkLogger(const TChar* aLabel);
public:  // from IVolume
    void SetVolume(TUint aValue);  // non-propagating
private:
    Bws<8> iLabel;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_VOLUME_MANAGER
