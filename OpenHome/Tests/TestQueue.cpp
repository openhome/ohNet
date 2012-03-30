#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/Queue.h>

using namespace OpenHome;
using namespace OpenHome::TestFramework;

class ByteEntry : public QueueSortedEntry
{
    friend class ByteQueue;
public:
    ByteEntry(TByte aValue) { iValue = aValue; }
private:
    TByte iValue;
};

class ByteQueue : public QueueSorted<ByteEntry>
{
public:
    TBool CheckHead(TBool aChanged, ByteEntry& aEntry);
private:
    virtual void HeadChanged(QueueSortedEntry& aEntry);
    virtual TInt Compare(QueueSortedEntry& aEntry1, QueueSortedEntry& aEntry2);
private:
    TBool iChanged;
    ByteEntry* iEntry;
};

void ByteQueue::HeadChanged(QueueSortedEntry& aEntry)
{
    iChanged = true;
    iEntry = &(ByteEntry&)aEntry;
}

TInt ByteQueue::Compare(QueueSortedEntry& aEntry1, QueueSortedEntry& aEntry2)
{
    return (Entry(aEntry1).iValue - Entry(aEntry2).iValue);
}

TBool ByteQueue::CheckHead(TBool aChanged, ByteEntry& aEntry)
{
    TBool result = (iChanged == aChanged && iEntry == &aEntry);
    iChanged = false;
    return (result);
}

class SuiteQueueBasic : public Suite
{
public:
    SuiteQueueBasic() : Suite("Basic Queue testing") {}
    void Test();
};

void SuiteQueueBasic::Test()
{
    ByteEntry a('a');
    ByteEntry b('b');
    ByteEntry c('c');
    ByteEntry d('d');
    ByteEntry e('e');
    ByteEntry f('f');
    ByteEntry g('g');
    ByteEntry h('h');
    ByteEntry i('i');
    
    ByteQueue queue;
    
    TEST(queue.IsEmpty());
    queue.Add(a);
    TEST(queue.CheckHead(true, a));
    TEST(!queue.IsEmpty());
    TEST(&queue.RemoveHead() == &a);
    TEST(queue.IsEmpty());
    TEST(queue.CheckHead(false, a));
    
    queue.Add(a);
    TEST(queue.CheckHead(true, a));
    queue.Add(b);
    TEST(queue.CheckHead(false, a));
    queue.Add(c);
    TEST(queue.CheckHead(false, a));
    queue.Add(d);
    TEST(queue.CheckHead(false, a));
    queue.Add(e);
    TEST(queue.CheckHead(false, a));
    queue.Add(f);
    TEST(queue.CheckHead(false, a));
    queue.Add(g);
    TEST(queue.CheckHead(false, a));
    queue.Add(h);
    TEST(queue.CheckHead(false, a));
    queue.Add(i);
    TEST(queue.CheckHead(false, a));
    TEST(!queue.IsEmpty());
    TEST(&queue.RemoveHead() == &a);
    TEST(!queue.IsEmpty());
    TEST(queue.CheckHead(true, b));
    TEST(&queue.RemoveHead() == &b);
    TEST(!queue.IsEmpty());
    TEST(queue.CheckHead(true, c));
    TEST(&queue.RemoveHead() == &c);
    TEST(!queue.IsEmpty());
    TEST(queue.CheckHead(true, d));
    TEST(&queue.RemoveHead() == &d);
    TEST(!queue.IsEmpty());
    TEST(queue.CheckHead(true, e));
    TEST(&queue.RemoveHead() == &e);
    TEST(!queue.IsEmpty());
    TEST(queue.CheckHead(true, f));
    TEST(&queue.RemoveHead() == &f);
    TEST(!queue.IsEmpty());
    TEST(queue.CheckHead(true, g));
    TEST(&queue.RemoveHead() == &g);
    TEST(!queue.IsEmpty());
    TEST(queue.CheckHead(true, h));
    TEST(&queue.RemoveHead() == &h);
    TEST(!queue.IsEmpty());
    TEST(queue.CheckHead(true, i));
    TEST(&queue.RemoveHead() == &i);
    TEST(queue.IsEmpty());
    TEST(queue.CheckHead(false, i));
    
    queue.Add(i);
    TEST(queue.CheckHead(true, i));
    queue.Add(h);
    TEST(queue.CheckHead(true, h));
    queue.Add(g);
    TEST(queue.CheckHead(true, g));
    queue.Add(f);
    TEST(queue.CheckHead(true, f));
    queue.Add(e);
    TEST(queue.CheckHead(true, e));
    queue.Add(d);
    TEST(queue.CheckHead(true, d));
    queue.Add(c);
    TEST(queue.CheckHead(true, c));
    queue.Add(b);
    TEST(queue.CheckHead(true, b));
    queue.Add(a);
    TEST(queue.CheckHead(true, a));

    TEST(!queue.IsEmpty());
    TEST(&queue.RemoveHead() == &a);
    TEST(!queue.IsEmpty());
    TEST(queue.CheckHead(true, b));
    TEST(&queue.RemoveHead() == &b);
    TEST(!queue.IsEmpty());
    TEST(queue.CheckHead(true, c));
    TEST(&queue.RemoveHead() == &c);
    TEST(!queue.IsEmpty());
    TEST(queue.CheckHead(true, d));
    TEST(&queue.RemoveHead() == &d);
    TEST(!queue.IsEmpty());
    TEST(queue.CheckHead(true, e));
    TEST(&queue.RemoveHead() == &e);
    TEST(!queue.IsEmpty());
    TEST(queue.CheckHead(true, f));
    TEST(&queue.RemoveHead() == &f);
    TEST(!queue.IsEmpty());
    TEST(queue.CheckHead(true, g));
    TEST(&queue.RemoveHead() == &g);
    TEST(!queue.IsEmpty());
    TEST(queue.CheckHead(true, h));
    TEST(&queue.RemoveHead() == &h);
    TEST(!queue.IsEmpty());
    TEST(queue.CheckHead(true, i));
    TEST(&queue.RemoveHead() == &i);
    TEST(queue.IsEmpty());
    TEST(queue.CheckHead(false, i));
    
    queue.Add(h);
    TEST(queue.CheckHead(true, h));
    queue.Add(d);
    TEST(queue.CheckHead(true, d));
    queue.Add(b);
    TEST(queue.CheckHead(true, b));
    queue.Add(g);
    TEST(queue.CheckHead(false, b));
    queue.Add(c);
    TEST(queue.CheckHead(false, b));
    queue.Add(a);
    TEST(queue.CheckHead(true, a));
    queue.Add(f);
    TEST(queue.CheckHead(false, a));
    queue.Add(i);
    TEST(queue.CheckHead(false, a));
    queue.Add(e);
    TEST(queue.CheckHead(false, a));

    TEST(!queue.IsEmpty());
    TEST(&queue.RemoveHead() == &a);
    TEST(!queue.IsEmpty());
    TEST(queue.CheckHead(true, b));
    TEST(&queue.RemoveHead() == &b);
    TEST(!queue.IsEmpty());
    TEST(queue.CheckHead(true, c));
    TEST(&queue.RemoveHead() == &c);
    TEST(!queue.IsEmpty());
    TEST(queue.CheckHead(true, d));
    TEST(&queue.RemoveHead() == &d);
    TEST(!queue.IsEmpty());
    TEST(queue.CheckHead(true, e));
    TEST(&queue.RemoveHead() == &e);
    TEST(!queue.IsEmpty());
    TEST(queue.CheckHead(true, f));
    TEST(&queue.RemoveHead() == &f);
    TEST(!queue.IsEmpty());
    TEST(queue.CheckHead(true, g));
    TEST(&queue.RemoveHead() == &g);
    TEST(!queue.IsEmpty());
    TEST(queue.CheckHead(true, h));
    TEST(&queue.RemoveHead() == &h);
    TEST(!queue.IsEmpty());
    TEST(queue.CheckHead(true, i));
    TEST(&queue.RemoveHead() == &i);
    TEST(queue.IsEmpty());
    TEST(queue.CheckHead(false, i));
    
    // Test removing
    
    queue.Add(a);
    TEST(queue.CheckHead(true, a));
    queue.Add(b);
    TEST(queue.CheckHead(false, a));
    queue.Add(c);
    TEST(queue.CheckHead(false, a));
    queue.Add(d);
    TEST(queue.CheckHead(false, a));
    queue.Add(e);
    TEST(queue.CheckHead(false, a));
    queue.Add(f);
    TEST(queue.CheckHead(false, a));
    queue.Add(g);
    TEST(queue.CheckHead(false, a));
    queue.Add(h);
    TEST(queue.CheckHead(false, a));
    queue.Add(i);
    TEST(queue.CheckHead(false, a));
    TEST(!queue.IsEmpty());
    queue.Remove(a);
    TEST(queue.CheckHead(true, b));
    queue.Remove(d);
    queue.Remove(c);
    queue.Remove(d);
    queue.Remove(c);
    queue.Remove(d);
    queue.Remove(c);
    TEST(queue.CheckHead(false, b));
    TEST(&queue.RemoveHead() == &b);
    TEST(queue.CheckHead(true, e));
    queue.Remove(f);
    TEST(queue.CheckHead(false, e));
    queue.Remove(g);
    TEST(queue.CheckHead(false, e));
    queue.Remove(h);
    TEST(queue.CheckHead(false, e));
    queue.Remove(i);
    TEST(&queue.RemoveHead() == &e);
    TEST(queue.CheckHead(false, e));
    TEST(queue.IsEmpty());
}

class SuiteQueueRemove : public Suite
{
public:
    SuiteQueueRemove() : Suite("Queue remove testing") {}
    void Test();
};

void SuiteQueueRemove::Test()
{
    ByteEntry a('a');
    ByteEntry b('b');
    ByteEntry c('c');
    ByteEntry d('d');
    ByteEntry e('e');
    ByteEntry f('f');
    ByteEntry g('g');
    ByteEntry h('h');
    ByteEntry i('i');
    
    ByteQueue queue;
    
    queue.Add(a);
    TEST(queue.CheckHead(true, a));
    queue.Add(b);
    TEST(queue.CheckHead(false, a));
    queue.Add(c);
    TEST(queue.CheckHead(false, a));
    queue.Add(d);
    TEST(queue.CheckHead(false, a));
    queue.Add(e);
    TEST(queue.CheckHead(false, a));
    queue.Add(f);
    TEST(queue.CheckHead(false, a));
    queue.Add(g);
    TEST(queue.CheckHead(false, a));
    queue.Add(h);
    TEST(queue.CheckHead(false, a));
    queue.Add(i);
    TEST(queue.CheckHead(false, a));
    TEST(!queue.IsEmpty());
    queue.Remove(a);
    TEST(queue.CheckHead(true, b));
    queue.Remove(d);
    queue.Remove(c);
    queue.Remove(d);
    queue.Remove(c);
    queue.Remove(d);
    queue.Remove(c);
    TEST(queue.CheckHead(false, b));
    TEST(&queue.RemoveHead() == &b);
    TEST(queue.CheckHead(true, e));
    queue.Remove(f);
    TEST(queue.CheckHead(false, e));
    queue.Remove(g);
    TEST(queue.CheckHead(false, e));
    queue.Remove(h);
    TEST(queue.CheckHead(false, e));
    queue.Remove(i);
    TEST(&queue.RemoveHead() == &e);
    TEST(queue.CheckHead(false, e));
    TEST(queue.IsEmpty());
}

void TestQueue()
{
    Runner runner("Queue testing\n");
    runner.Add(new SuiteQueueBasic());
    runner.Add(new SuiteQueueRemove());
    runner.Run();
}
