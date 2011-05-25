#ifndef HEADER_TOPOLOGY
#define HEADER_TOPOLOGY

#include <Standard.h>
#include <OhNetTypes.h>
#include <Fifo.h>
#include <Thread.h>
#include <Core/CpDevice.h>

#include <vector>
#include <list>

namespace OpenHome {
namespace Net {

class IHouse : private INonCopyable
{
public:
    virtual void Refresh() = 0;
    virtual ~IHouse() {}
};

class IRoom : private INonCopyable
{
public:
    virtual void AddRef() = 0;
    virtual void RemoveRef() = 0;
    virtual TBool Standby() const = 0;
    virtual void SetStandby(TBool aValue) = 0;
    virtual const Brx& Name() const = 0;
    virtual TUint SourceCount() const = 0;
    virtual const Brx& SourceName(TUint aIndex) const = 0;
    virtual const Brx& SourceType(TUint aIndex) const = 0;
    virtual CpDevice& SourceDevice(TUint aIndex) const = 0;
    virtual TUint SourceIndex() const = 0;
    virtual void SetSourceIndex(TUint aIndex) = 0;
    virtual TBool HasVolumeControl() const = 0;
    virtual TUint VolumeMax() const = 0;
    virtual TUint VolumeUnity() const = 0;
    virtual TUint VolumeSteps() const = 0;
    virtual TUint VolumeMilliDbPerStep() const = 0;
    virtual TUint FadeMax() const = 0;
    virtual TUint BalanceMax() const = 0;
    virtual TUint VolumeLimit() const = 0;
    virtual TUint Volume() const = 0;
    virtual void SetVolume(TUint aValue) = 0;
    virtual void VolumeInc() = 0;
    virtual void VolumeDec() = 0;
    virtual TInt Balance() const = 0;
    virtual void SetBalance(TInt aValue) = 0;
    virtual void BalanceInc() = 0;
    virtual void BalanceDec() = 0;
    virtual TInt Fade() const = 0;
    virtual void SetFade(TInt aValue) = 0;
    virtual void FadeInc() = 0;
    virtual void FadeDec() = 0;
    virtual TBool Mute() const = 0;
    virtual void SetMute(TBool aValue) = 0;
    virtual void SetUserData(void* aValue) = 0;
    virtual void* UserData() const = 0;
    virtual ~IRoom() {}
};

class IHouseHandler : private INonCopyable
{
public:
    virtual void RoomAdded(IRoom& aRoom) = 0;
    virtual void RoomChanged(IRoom& aRoom) = 0;
    virtual void RoomRemoved(IRoom& aRoom) = 0;
    virtual void RoomStandbyChanged(IRoom& aRoom) = 0;
    virtual void RoomSourceIndexChanged(IRoom& aRoom) = 0;
    virtual void RoomVolumeLimitChanged(IRoom& aRoom) = 0;
    virtual void RoomVolumeChanged(IRoom& aRoom) = 0;
    virtual void RoomBalanceChanged(IRoom& aRoom) = 0;
    virtual void RoomFadeChanged(IRoom& aRoom) = 0;
    virtual void RoomMuteChanged(IRoom& aRoom) = 0;
    virtual ~IHouseHandler() {}
};

class House : private INonCopyable
{
public:
    House(IHouseHandler& aHandler);
    void Refresh();
    ~House();
private:
    IHouse* iHouse;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_TOPOLOGY
