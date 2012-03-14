#ifndef HEADER_TOPOLOGY
#define HEADER_TOPOLOGY

#include <OpenHome/Private/Standard.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Fifo.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Net/Core/CpDevice.h>

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
    enum EStandby {
        eOn,
        eMixed,
        eOff
    };

public:
    // Functions that must be called from IHouseHandler callback thread

    virtual void AddRef() = 0;
    virtual void RemoveRef() = 0;
    virtual EStandby Standby() const = 0;
    virtual const Brx& Name() const = 0;
    virtual TUint SourceCount() const = 0;
    virtual const Brx& SourceName(TUint aIndex) const = 0;
    virtual const Brx& SourceType(TUint aIndex) const = 0;
    virtual const Brx& SourceGroup(TUint aIndex) const = 0;
    virtual CpDevice& SourceDevice(TUint aIndex) const = 0;
    virtual const Brx& CurrentSourceName() const = 0;
    virtual const Brx& CurrentSourceType() const = 0;
    virtual const Brx& CurrentSourceGroup() const = 0;
    virtual CpDevice& CurrentSourceDevice() const = 0;
    virtual TBool HasVolumeControl() const = 0;
    virtual CpDevice& VolumeDevice() const = 0;
    virtual void SetUserData(void* aValue) = 0;
    virtual void* UserData() const = 0;
    virtual ~IRoom() {}

    // Functions that must NOT be called from IHouseHandler callback thread

    virtual void SetStandby(TBool aValue) = 0;
    virtual void SetSourceIndex(TUint aIndex) = 0;

};

class IHouseHandler : private INonCopyable
{
public:
    virtual void RoomAdded(IRoom& aRoom) = 0;
    virtual void RoomChanged(IRoom& aRoom) = 0;
    virtual void RoomRemoved(IRoom& aRoom) = 0;
    virtual void RoomStandbyChanged(IRoom& aRoom) = 0;
    virtual void RoomSourceChanged(IRoom& aRoom) = 0;
    virtual void RoomVolumeControlChanged(IRoom& aRoom) = 0;
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
