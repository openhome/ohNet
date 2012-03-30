// Auomated test for complex topology layers

#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/OptionParser.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Net/Private/Discovery.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Timer.h>
#include <OpenHome/OsWrapper.h>
#include "CpTopology4.h"

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::TestFramework;


class TestCpDevice : public CpDevice
{
public:
    TestCpDevice();
};

class TestDevice : public ICpTopology2GroupHandler
{
public:
    virtual void SetSourceIndex(TUint aIndex);
    virtual void SetStandby(TBool aValue);
};

void TestDevice::SetSourceIndex(TUint /* aIndex */)
{
}

void TestDevice::SetStandby(TBool /* aValue */)
{
}

class TestEntry
{
public:
    TestEntry(const Brx& aType, const Brx& aValue, const Brx& aInfo);
    TBool Check(const Brx& aType, const Brx& aValue, const Brx& aInfo);
    void Print(const TChar* aPrefix) const;
private:
    Bws<100> iType;
    Bws<100> iValue;
    Bws<100> iInfo;
};

TestEntry::TestEntry(const Brx& aType, const Brx& aValue, const Brx& aInfo)
    : iType(aType)
    , iValue(aValue)
    , iInfo(aInfo)
{
}

TBool TestEntry::Check(const Brx& aType, const Brx& aValue, const Brx& aInfo)
{
    if (iType == aType) {
        if (iValue == aValue) {
            if (iInfo == aInfo) {
                return (true);
            }
        }
    }
    
    TestEntry expected(aType, aValue, aInfo);
    
    expected.Print("E");
    
    ASSERTS();
    
    return (false);
}

void TestEntry::Print(const TChar* aPrefix) const
{
    ::Print(aPrefix);
    ::Print(" ");
    ::Print(iType);
    ::Print(":");
    ::Print(iValue);
    ::Print(":");
    ::Print(iInfo);
    ::Print("\n");
}

class TestRoom
{
public:
    TestRoom(const Brx& aName);
    void AddSource(const Brx& aName, const Brx& aType, TBool aDiscard);
    const Brx& Name() const;
    TUint SourceCount() const;
    const Brx& SourceName(TUint aIndex) const;
    const Brx& SourceType(TUint aIndex) const;
private:
    Bws<100> iName;
    TUint iCount;
    Bws<100> iNames[100];
    Bws<100> iTypes[100];
};

TestRoom::TestRoom(const Brx& aName)
    : iName(aName)
    , iCount(0)
{
}

void TestRoom::AddSource(const Brx& aName, const Brx& aType, TBool aVisible)
{
    if (aVisible) {
        iNames[iCount].Replace(aName);
        iTypes[iCount++].Replace(aType);
    }
}

const Brx& TestRoom::Name() const
{
    return (iName);
}

TUint TestRoom::SourceCount() const
{
    return (iCount);
}

const Brx& TestRoom::SourceName(TUint aIndex) const
{
    return (iNames[aIndex]);
}

const Brx& TestRoom::SourceType(TUint aIndex) const
{
    return (iTypes[aIndex]);
}

class TestTopology4Handler : public ICpTopology4Handler
{
    static const TUint kMaxFifoSlots = 100;
    
public:
    TestTopology4Handler();
    TBool CheckRoomAdded(const TestRoom& aRoom);
    TBool CheckRoomChanged(const TestRoom& aRoom);
    TBool CheckRoomRemoved(const TestRoom& aRoom);
    TBool CheckRoomSourceChanged(const TestRoom& aRoom, const Brx& aName);
	TBool CheckVolumeControl(const TestRoom& aRoom, TBool aValue);
    TBool CheckComplete();
    
private:
    virtual void RoomAdded(CpTopology4Room& aRoom);
    virtual void RoomChanged(CpTopology4Room& aRoom);
    virtual void RoomRemoved(CpTopology4Room& aRoom);
    virtual void RoomStandbyChanged(CpTopology4Room& aRoom);
    virtual void RoomSourceChanged(CpTopology4Room& aRoom);
    virtual void RoomVolumeControlChanged(CpTopology4Room& aRoom);
	virtual void RoomVolumeChanged(CpTopology4Room& aRoom);
	virtual void RoomMuteChanged(CpTopology4Room& aRoom);
	virtual void RoomVolumeLimitChanged(CpTopology4Room& aRoom);
    
    void Add(const Brx& aType, const Brx& aValue, const Brx& aInfo);
    TBool Check(const Brx& aType, const Brx& aValue, const Brx& aInfo);
    
private:
    Fifo<TestEntry*> iFifo;
};

TestTopology4Handler::TestTopology4Handler()
    : iFifo(kMaxFifoSlots)
{
}

TBool TestTopology4Handler::CheckRoomAdded(const TestRoom& aRoom)
{
    Bws<10> count;
    
    Ascii::AppendDec(count, aRoom.SourceCount());
    
    if (!Check(Brn("Added"), aRoom.Name(), count)) {
        return (false);
    }
    
    for (TUint i = 0; i < aRoom.SourceCount(); i++) {
        if (!Check(Brn("Source"), aRoom.SourceName(i), aRoom.SourceType(i))) {
            return (false);
        }
    }
    
    return (true);
}

TBool TestTopology4Handler::CheckRoomChanged(const TestRoom& aRoom)
{
    Bws<10> count;
    
    Ascii::AppendDec(count, aRoom.SourceCount());
    
    if (!Check(Brn("List"), aRoom.Name(), count)) {
        return (false);
    }
    
    for (TUint i = 0; i < aRoom.SourceCount(); i++) {
        if (!Check(Brn("Source"), aRoom.SourceName(i), aRoom.SourceType(i))) {
            return (false);
        }
    }
    
    return (true);
}

TBool TestTopology4Handler::CheckRoomRemoved(const TestRoom& aRoom)
{
    return (Check(Brn("Removed"), aRoom.Name(), Brx::Empty()));
}

TBool TestTopology4Handler::CheckRoomSourceChanged(const TestRoom& aRoom, const Brx& aName)
{
    return (Check(Brn("Change"), aRoom.Name(), aName));
}

TBool TestTopology4Handler::CheckVolumeControl(const TestRoom& aRoom, TBool aValue)
{
	return (Check(Brn("Volume Control"), aRoom.Name(), aValue ? Brn("Yes") : Brn("No")));
}

TBool TestTopology4Handler::CheckComplete()
{
    if (iFifo.SlotsUsed() == 0) {
        return (true);
    }
    
    Print("TOO MUCH\n");
    return (false);
}

void TestTopology4Handler::Add(const Brx& aType, const Brx& aValue, const Brx& aInfo)
{   TestEntry* entry = new TestEntry(aType, aValue, aInfo);
    entry->Print("I"); 
    iFifo.Write(entry);
}

TBool TestTopology4Handler::Check(const Brx& aType, const Brx& aValue, const Brx& aInfo)
{
    TestEntry* entry = iFifo.Read();
    entry->Print("O");
    TBool result = entry->Check(aType, aValue, aInfo);
    delete (entry);
    return (result);
}

void TestTopology4Handler::RoomAdded(CpTopology4Room& aRoom)
{
    Bws<10> count;
    
    Ascii::AppendDec(count, aRoom.SourceCount());
    
    Add(Brn("Added"), aRoom.Name(), count);
    
    for (TUint i = 0; i < aRoom.SourceCount(); i++) {
        Add(Brn("Source"), aRoom.SourceName(i), aRoom.SourceType(i));
    }
}

void TestTopology4Handler::RoomChanged(CpTopology4Room& aRoom)
{
    Bws<10> count;
    
    Ascii::AppendDec(count, aRoom.SourceCount());
    
    Add(Brn("List"), aRoom.Name(), count);
    
    for (TUint i = 0; i < aRoom.SourceCount(); i++) {
        Add(Brn("Source"), aRoom.SourceName(i), aRoom.SourceType(i));
    }
}

void TestTopology4Handler::RoomRemoved(CpTopology4Room& aRoom)
{
    Add(Brn("Removed"), aRoom.Name(), Brx::Empty());
}

void TestTopology4Handler::RoomStandbyChanged(CpTopology4Room& aRoom)
{
    Bws<10> standby;

    switch(aRoom.Standby()) {
    case CpTopology4Room::eOff:
        standby.Replace(Brn("Off"));
        break;
    case CpTopology4Room::eMixed:
        standby.Replace(Brn("Mixed"));
        break;
    case CpTopology4Room::eOn:
        standby.Replace(Brn("On"));
        break;
    }

    Add(Brn("Standby"), aRoom.Name(), standby);
}

void TestTopology4Handler::RoomSourceChanged(CpTopology4Room& aRoom)
{
    Add(Brn("Change"), aRoom.Name(), aRoom.CurrentSourceName());
}

void TestTopology4Handler::RoomVolumeControlChanged(CpTopology4Room& aRoom)
{
    Add(Brn("Volume Control"), aRoom.Name(), aRoom.HasVolumeControl() ? Brn("Yes") : Brn("No"));
}

void TestTopology4Handler::RoomVolumeChanged(CpTopology4Room& aRoom)
{
	Bws<Ascii::kMaxUintStringBytes> buffer;
	Ascii::AppendDec(buffer, aRoom.Volume());
    Print(buffer);
    Add(Brn("Volume"), aRoom.Name(), buffer);
}

void TestTopology4Handler::RoomMuteChanged(CpTopology4Room& aRoom)
{
    Add(Brn("Mute"), aRoom.Name(), aRoom.Mute() ? Brn("Yes") : Brn("No"));
}

void TestTopology4Handler::RoomVolumeLimitChanged(CpTopology4Room& aRoom)
{
	Bws<Ascii::kMaxUintStringBytes> buffer;
	Ascii::AppendDec(buffer, aRoom.VolumeLimit());
    Print(buffer);
    Add(Brn("Volume Limit"), aRoom.Name(), buffer);
}

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], InitialisationParams* aInitParams)
{
    UpnpLibrary::Initialise(aInitParams);

    // Debug::SetLevel(Debug::kTopology);
    // Debug::SetLevel(Debug::kAll);

    TestDevice device;
    TestTopology4Handler handler4;
    
    ICpTopology3Handler* handler3 = NULL;

    CpTopology4* topology4 = new CpTopology4(handler4, &handler3);

    Print("Test 1\n");
    Print("Add and remove 1\n");
    
    CpDevice* cpdevice = 0;
    
    CpTopology2Group* group1x = new CpTopology2Group(*cpdevice, device, false, Brn("Kitchen"), Brn("Majik DS-I"), 0, false);
	CpTopology3Group* group1 = new CpTopology3Group(*group1x, *handler3);
    
    group1x->AddSource(Brn("Playlist"), Brn("Playlist"), true);
    group1x->AddSource(Brn("Radio"), Brn("Radio"), true);
    group1x->AddSource(Brn("Songcast"), Brn("Receiver"), true);
    group1x->AddSource(Brn("UpnpAv"), Brn("UpnpAv"), false);
    group1x->AddSource(Brn("Analog1"), Brn("Analog"), true);
    group1x->AddSource(Brn("Analog2"), Brn("Analog"), true);
    group1x->AddSource(Brn("Analog3"), Brn("Analog"), true);
    group1x->AddSource(Brn("Phono"), Brn("Analog"), true);
    group1x->AddSource(Brn("Front Aux"), Brn("Analog"), true);
    group1x->AddSource(Brn("Spdif1"), Brn("Digital"), true);
    group1x->AddSource(Brn("Spdif2"), Brn("Digital"), true);
    group1x->AddSource(Brn("Spdif3"), Brn("Digital"), true);
    group1x->AddSource(Brn("Toslink1"), Brn("Digital"), true);
    group1x->AddSource(Brn("Toslink2"), Brn("Digital"), true);
    group1x->AddSource(Brn("Toslink3"), Brn("Digital"), true);
    
    TestRoom* room1 = new TestRoom(Brn("Kitchen"));
    room1->AddSource(Brn("Playlist"), Brn("Playlist"), true);
    room1->AddSource(Brn("Radio"), Brn("Radio"), true);
    room1->AddSource(Brn("Songcast"), Brn("Receiver"), true);
    room1->AddSource(Brn("UpnpAv"), Brn("UpnpAv"), false);
    room1->AddSource(Brn("Analog1"), Brn("Analog"), true);
    room1->AddSource(Brn("Analog2"), Brn("Analog"), true);
    room1->AddSource(Brn("Analog3"), Brn("Analog"), true);
    room1->AddSource(Brn("Phono"), Brn("Analog"), true);
    room1->AddSource(Brn("Front Aux"), Brn("Analog"), true);
    room1->AddSource(Brn("Spdif1"), Brn("Digital"), true);
    room1->AddSource(Brn("Spdif2"), Brn("Digital"), true);
    room1->AddSource(Brn("Spdif3"), Brn("Digital"), true);
    room1->AddSource(Brn("Toslink1"), Brn("Digital"), true);
    room1->AddSource(Brn("Toslink2"), Brn("Digital"), true);
    room1->AddSource(Brn("Toslink3"), Brn("Digital"), true);

    handler3->GroupAdded(*group1);
    handler4.CheckRoomAdded(*room1);
	//handler4.CheckVolumeControl(*room1, true);
    
    handler3->GroupRemoved(*group1);
    handler4.CheckRoomRemoved(*room1);

    Print("Test 2\n");
    Print("Add 1, add 2\n");

    CpTopology2Group* group2x = new CpTopology2Group(*cpdevice, device, false, Brn("Kitchen"), Brn("Phono"), 0, false);
	CpTopology3Group* group2 = new CpTopology3Group(*group2x, *handler3);
    
    group2x->AddSource(Brn("Playlist"), Brn("Playlist"), true);
    group2x->AddSource(Brn("Radio"), Brn("Radio"), true);
    group2x->AddSource(Brn("Songcast"), Brn("Receiver"), true);
    group2x->AddSource(Brn("UpnpAv"), Brn("UpnpAv"), false);
    group2x->AddSource(Brn("Analog1"), Brn("Analog"), true);
    group2x->AddSource(Brn("Analog2"), Brn("Analog"), true);
    group2x->AddSource(Brn("Analog3"), Brn("Analog"), true);
    group2x->AddSource(Brn("Phono"), Brn("Analog"), true);
    group2x->AddSource(Brn("Front Aux"), Brn("Analog"), true);
    group2x->AddSource(Brn("Spdif1"), Brn("Digital"), true);
    group2x->AddSource(Brn("Spdif2"), Brn("Digital"), true);
    group2x->AddSource(Brn("Spdif3"), Brn("Digital"), true);
    group2x->AddSource(Brn("Toslink1"), Brn("Digital"), true);
    group2x->AddSource(Brn("Toslink2"), Brn("Digital"), true);
    group2x->AddSource(Brn("Toslink3"), Brn("Digital"), true);
    
    TestRoom* room2 = new TestRoom(Brn("Kitchen"));
    room2->AddSource(Brn("Playlist"), Brn("Playlist"), true);
    room2->AddSource(Brn("Radio"), Brn("Radio"), true);
    room2->AddSource(Brn("Songcast"), Brn("Receiver"), true);
    room2->AddSource(Brn("UpnpAv"), Brn("UpnpAv"), false);
    room2->AddSource(Brn("Analog1"), Brn("Analog"), true);
    room2->AddSource(Brn("Analog2"), Brn("Analog"), true);
    room2->AddSource(Brn("Analog3"), Brn("Analog"), true);
    room2->AddSource(Brn("Phono"), Brn("Analog"), true);
    room2->AddSource(Brn("Front Aux"), Brn("Analog"), true);
    room2->AddSource(Brn("Spdif1"), Brn("Digital"), true);
    room2->AddSource(Brn("Spdif2"), Brn("Digital"), true);
    room2->AddSource(Brn("Spdif3"), Brn("Digital"), true);
    room2->AddSource(Brn("Toslink1"), Brn("Digital"), true);
    room2->AddSource(Brn("Toslink2"), Brn("Digital"), true);
    room2->AddSource(Brn("Toslink3"), Brn("Digital"), true);

    TestRoom* room1and2 = new TestRoom(Brn("Kitchen"));
    room1and2->AddSource(Brn("Playlist"), Brn("Playlist"), true);
    room1and2->AddSource(Brn("Radio"), Brn("Radio"), true);
    room1and2->AddSource(Brn("Songcast"), Brn("Receiver"), true);
    room1and2->AddSource(Brn("UpnpAv"), Brn("UpnpAv"), false);
    room1and2->AddSource(Brn("Analog1"), Brn("Analog"), true);
    room1and2->AddSource(Brn("Analog2"), Brn("Analog"), true);
    room1and2->AddSource(Brn("Analog3"), Brn("Analog"), true);
    // START room1and2->AddSource(Brn("Phono"), Brn("Analog"), true);
    room1and2->AddSource(Brn("Playlist"), Brn("Playlist"), true);
    room1and2->AddSource(Brn("Radio"), Brn("Radio"), true);
    room1and2->AddSource(Brn("Songcast"), Brn("Receiver"), true);
    room1and2->AddSource(Brn("UpnpAv"), Brn("UpnpAv"), false);
    room1and2->AddSource(Brn("Analog1"), Brn("Analog"), true);
    room1and2->AddSource(Brn("Analog2"), Brn("Analog"), true);
    room1and2->AddSource(Brn("Analog3"), Brn("Analog"), true);
    room1and2->AddSource(Brn("Phono"), Brn("Analog"), true);
    room1and2->AddSource(Brn("Front Aux"), Brn("Analog"), true);
    room1and2->AddSource(Brn("Spdif1"), Brn("Digital"), true);
    room1and2->AddSource(Brn("Spdif2"), Brn("Digital"), true);
    room1and2->AddSource(Brn("Spdif3"), Brn("Digital"), true);
    room1and2->AddSource(Brn("Toslink1"), Brn("Digital"), true);
    room1and2->AddSource(Brn("Toslink2"), Brn("Digital"), true);
    room1and2->AddSource(Brn("Toslink3"), Brn("Digital"), true);
    // END
    room1and2->AddSource(Brn("Front Aux"), Brn("Analog"), true);
    room1and2->AddSource(Brn("Spdif1"), Brn("Digital"), true);
    room1and2->AddSource(Brn("Spdif2"), Brn("Digital"), true);
    room1and2->AddSource(Brn("Spdif3"), Brn("Digital"), true);
    room1and2->AddSource(Brn("Toslink1"), Brn("Digital"), true);
    room1and2->AddSource(Brn("Toslink2"), Brn("Digital"), true);
    room1and2->AddSource(Brn("Toslink3"), Brn("Digital"), true);

    handler3->GroupAdded(*group1);
    handler3->GroupAdded(*group2);
    handler4.CheckRoomAdded(*room1);
	//handler4.CheckVolumeControl(*room1, true);
    handler4.CheckRoomChanged(*room1and2);

    Print("Test 3\n");
    Print("Remove 2\n");

    handler3->GroupRemoved(*group2);
    handler4.CheckRoomChanged(*room1);

    Print("Test 4\n");
    Print("Add 2\n");

    handler3->GroupAdded(*group2);
    handler4.CheckRoomChanged(*room1and2);

    Print("Test 5\n");
    Print("Remove 1\n");

    handler3->GroupRemoved(*group1);
	//handler4.CheckVolumeControl(*room2, false);
    handler4.CheckRoomSourceChanged(*room2, Brn("Playlist"));
    handler4.CheckRoomChanged(*room2);

    Print("Test 6\n");
    Print("Add 1\n");

    handler3->GroupAdded(*group1);
	//handler4.CheckVolumeControl(*room1and2, true);
    handler4.CheckRoomSourceChanged(*room1and2, Brn("Playlist"));
    handler4.CheckRoomChanged(*room1and2);

    Print("Test 7\n");
    Print("Remove 1 and 2\n");

    handler3->GroupRemoved(*group1);
    handler3->GroupRemoved(*group2);
	//handler4.CheckVolumeControl(*room1, false);
    handler4.CheckRoomSourceChanged(*room2, Brn("Playlist"));
    handler4.CheckRoomChanged(*room2);
    handler4.CheckRoomRemoved(*room1);

    delete group1;
    delete group1x;
    delete group2;
    delete group2x;

    delete room1;
    delete room2;
    delete room1and2;

    delete topology4;

    UpnpLibrary::Close();
}
