#ifndef MEDIAPLAYER_UTILS_H
#define MEDIAPLAYER_UTILS_H

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Media/VolumeManager.h>
#include <OpenHome/Media/MuteManager.h>

namespace OpenHome {
namespace Media {

class VolumeProfileDummy : public IVolumeProfile
{
public: // from IVolumeProfile
    TUint MaxVolume() const override;
    TUint VolumeUnity() const override;
    TUint VolumeSteps() const override;
    TUint VolumeMilliDbPerStep() const override;
    TInt MaxBalance() const override;
};

class VolumePrinter : public IVolume
{
public: // from IVolume
    void SetVolume(TUint aVolume) override;
};

class BalancePrinter : public IBalance
{
public: // from IBalance
    void SetBalance(TInt aBalance) override;
};

class MutePrinter : public IMute
{
public: // from IMute
    void Mute() override;
    void Unmute() override;
};

} // namespace Media
} // namespace OpenHome

#endif // MEDIAPLAYER_UTILS_H

