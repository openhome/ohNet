#ifndef HEADER_QUEUE
#define HEADER_QUEUE

#include <OpenHome/Private/Standard.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Private/Thread.h>

EXCEPTION(QueueEmpty)

namespace OpenHome {

// Derive a queueable class T from QueueEntry<T>
//
// Then use Queue<T> or QueueLight<T> to create either a thread safe or a non-thread safe queue
//
// The queue interface is designed to ensure that every queue entry, once created, is always
// in a queue, it is mereley moved from one queue to another.
// 
// Queue destructors delete their entries
//
// Queue Lock and Unlock functions are public so that the number of entries in a system
// of queues can be reliably counted: lock the queues, count their entries, unlock them again

class QueueBase;
class QueueSystemBase;

class QueueEntryBase : public INonCopyable
{
    friend class QueueBase;
    friend class QueueSystemBase;
public:
    void DoMoveTo(QueueBase& aQueue);
private:
    QueueBase* iQueue;
    QueueEntryBase* iPrev;
    QueueEntryBase* iNext;
};

template <class T> class Queue;

template <class T> class QueueEntry : public QueueEntryBase
{
public:
    void MoveTo(Queue<T>& aQueue) { DoMoveTo(aQueue); }
};

class QueueBase : public QueueEntry<QueueBase>
{
    friend class QueueEntryBase;
public:
    TUint Count() const;
protected:
    QueueBase();
    void DoAdd(QueueEntryBase* aEntry);
    void DoMoveAllTo(QueueBase& aQueue);
    QueueEntryBase& DoMoveHeadTo(QueueBase& aQueue);
    ~QueueBase();
private:
    QueueEntryBase* iHead;
    TUint iCount;
};

template <class T> class Queue : public QueueBase
{
public:
    void Add(QueueEntry<T>* aEntry) { DoAdd(aEntry); }
    void MoveAllTo(Queue<T>& aQueue) { DoMoveAllTo(aQueue); }
    T& MoveHeadTo(Queue<T>& aQueue) { return ((T&)DoMoveHeadTo(aQueue)); }
};

// Sorted queues

class QueueSortedEntry : public INonCopyable
{
    friend class QueueSortedBase;
protected:
    QueueSortedEntry();
    QueueSortedEntry& Next();
    QueueSortedEntry& Prev();
    void AddBefore(QueueSortedEntry& aEntry);
    void Remove();
    void SetNext(QueueSortedEntry& aEntry);
    void SetPrev(QueueSortedEntry& aEntry);
protected:
    QueueSortedEntry* iNext;
    QueueSortedEntry* iPrev;
};

class QueueSortedEntryHead : public QueueSortedEntry
{
    friend class QueueSortedBase;
protected:
    QueueSortedEntryHead();
};

class QueueSortedEntryTail : public QueueSortedEntry
{
    friend class QueueSortedBase;
protected:
    QueueSortedEntryTail();
};

class QueueSortedBase : public INonCopyable
{
public:
    TBool IsEmpty();
    virtual ~QueueSortedBase();
protected:
    QueueSortedBase();
    void DoAdd(QueueSortedEntry& aEntry);
    void DoRemove(QueueSortedEntry& aEntry);
    QueueSortedEntry& DoRemoveHead();
    TBool IsTail(QueueSortedEntry& aEntry) const;
private:
    virtual void HeadChanged(QueueSortedEntry& aEntry) = 0;
    virtual TInt Compare(QueueSortedEntry& aEntry1, QueueSortedEntry& aEntry2) = 0;
private:
    Mutex iMutex;
    QueueSortedEntryHead iHead;
    QueueSortedEntryTail iTail;
};

// Templated on QueueSortedEntry type

template <class T> class QueueSorted : public QueueSortedBase
{
public:
    void Add(T& aEntry) { DoAdd(aEntry); }
    void Remove(T& aEntry) { DoRemove(aEntry); }
    T& RemoveHead() { return ((T&)DoRemoveHead()); }
protected:
    T& Entry(QueueSortedEntry& aEntry) { return ((T&)aEntry); }
};

} // namespace OpenHome

#endif // HEADER_QUEUE
