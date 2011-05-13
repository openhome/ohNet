// Auomated test for complex topology layers

#include <TestFramework.h>
#include <OptionParser.h>
#include <ZappTypes.h>
#include <Discovery.h>
#include <Thread.h>
#include <Timer.h>
#include <OsWrapper.h>
#include "CpTopology3.h"

using namespace Zapp;
using namespace Zapp::TestFramework;


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
    void Add(const Brx& aName, const Brx& aType);
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

void TestRoom::Add(const Brx& aName, const Brx& aType)
{
    iNames[iCount].Replace(aName);
    iTypes[iCount++].Replace(aType);
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

class TestTopology3Handler : public ICpTopology3Handler
{
    static const TUint kMaxFifoSlots = 100;
    
public:
    TestTopology3Handler();
    TBool CheckRoomAdded(const TestRoom& aRoom);
    TBool CheckRoomSourceListChanged(const TestRoom& aRoom);
    TBool CheckRoomRemoved(const TestRoom& aRoom);
    TBool CheckComplete();
    
private:
	virtual void RoomAdded(CpTopology3Room& aRoom);
	virtual void RoomStandbyChanged(CpTopology3Room& aRoom);
	virtual void RoomSourceIndexChanged(CpTopology3Room& aRoom);
	virtual void RoomSourceListChanged(CpTopology3Room& aRoom);
	virtual void RoomVolumeChanged(CpTopology3Room& aRoom);
	virtual void RoomMuteChanged(CpTopology3Room& aRoom);
	virtual void RoomRemoved(CpTopology3Room& aRoom);
	
    void Add(const Brx& aType, const Brx& aValue, const Brx& aInfo);
    TBool Check(const Brx& aType, const Brx& aValue, const Brx& aInfo);
    
private:
    Fifo<TestEntry*> iFifo;
};

TestTopology3Handler::TestTopology3Handler()
    : iFifo(kMaxFifoSlots)
{
}

TBool TestTopology3Handler::CheckRoomAdded(const TestRoom& aRoom)
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

TBool TestTopology3Handler::CheckRoomSourceListChanged(const TestRoom& aRoom)
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

TBool TestTopology3Handler::CheckRoomRemoved(const TestRoom& aRoom)
{
    return (Check(Brn("Removed"), aRoom.Name(), Brx::Empty()));
}

TBool TestTopology3Handler::CheckComplete()
{
    if (iFifo.SlotsUsed() == 0) {
        return (true);
    }
    
    Print("TOO MUCH\n");
    return (false);
}

void TestTopology3Handler::Add(const Brx& aType, const Brx& aValue, const Brx& aInfo)
{   TestEntry* entry = new TestEntry(aType, aValue, aInfo);
    entry->Print("I"); 
    iFifo.Write(entry);
}

TBool TestTopology3Handler::Check(const Brx& aType, const Brx& aValue, const Brx& aInfo)
{
    TestEntry* entry = iFifo.Read();
    TBool result = entry->Check(aType, aValue, aInfo);
    delete (entry);
    return (result);
}

void TestTopology3Handler::RoomAdded(CpTopology3Room& aRoom)
{
    Bws<10> count;
    
    Ascii::AppendDec(count, aRoom.SourceCount());
    
    Add(Brn("Added"), aRoom.Name(), count);
    
    for (TUint i = 0; i < aRoom.SourceCount(); i++) {
        Add(Brn("Source"), aRoom.SourceName(i), aRoom.SourceType(i));
    }
}

void TestTopology3Handler::RoomStandbyChanged(CpTopology3Room& aRoom)
{
    Add(Brn("Standby"), aRoom.Name(), aRoom.Standby() ? Brn("Y") : Brn("N"));
}

void TestTopology3Handler::RoomSourceIndexChanged(CpTopology3Room& aRoom)
{
    Bws<10> index;
    
    Ascii::AppendDec(index, aRoom.SourceIndex());
    
    Add(Brn("Index"), aRoom.Name(), index);
}

void TestTopology3Handler::RoomSourceListChanged(CpTopology3Room& aRoom)
{
    Bws<10> count;
    
    Ascii::AppendDec(count, aRoom.SourceCount());
    
    Add(Brn("List"), aRoom.Name(), count);
    
    for (TUint i = 0; i < aRoom.SourceCount(); i++) {
        Add(Brn("Source"), aRoom.SourceName(i), aRoom.SourceType(i));
    }
}

void TestTopology3Handler::RoomVolumeChanged(CpTopology3Room& aRoom)
{
    Bws<10> volume;
    
    Ascii::AppendDec(volume, aRoom.Volume());
    
    Add(Brn("Volume"), aRoom.Name(), volume);
}

void TestTopology3Handler::RoomMuteChanged(CpTopology3Room& aRoom)
{
    Add(Brn("Mute"), aRoom.Name(), aRoom.Mute() ? Brn("Y") : Brn("N"));
}

void TestTopology3Handler::RoomRemoved(CpTopology3Room& aRoom)
{
    Add(Brn("Removed"), aRoom.Name(), Brx::Empty());
}

void Zapp::TestFramework::Runner::Main(TInt aArgc, TChar* aArgv[], InitialisationParams* aInitParams)
{
    // Debug::SetLevel(Debug::kTopology);
    // Debug::SetLevel(Debug::kAll);

    TestTopology3Handler handler3;

    ICpTopology2Handler* handler2;
    
    CpTopology3* topology = new CpTopology3(handler3, &handler2);

    delete topology;
}
