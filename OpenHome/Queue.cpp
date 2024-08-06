#include <OpenHome/Private/Queue.h>

using namespace OpenHome;

// QueueBase

QueueBase::QueueBase()
: iHead(0), iCount(0)
{
}

TUint QueueBase::Count() const
{
    return iCount;
}

void QueueBase::DoAdd(QueueEntryBase* aEntry)
{
    aEntry->iPrev = 0;
    aEntry->iNext = iHead;
    aEntry->iQueue = this;
    if (iHead) {
        iHead->iPrev = aEntry;
    }
    iHead = aEntry;
    iCount++;
}

// Add all the items on this queue to the end of the other queue and delete them from this

void QueueBase::DoMoveAllTo(QueueBase& aQueue)
{
    QueueEntryBase* entry = aQueue.iHead;
    if (entry) { // that queue has items
        while (entry->iNext) { // find end of that queue
            entry = entry->iNext;
        }
        entry->iNext = iHead; // add the whole of this queue to the end of that queue
        if (iHead) { // there were some added from this queue, so...
            iHead->iPrev = entry; // fix up the back link
        }
    }
    else { // that queue is empty
        aQueue.iHead = iHead;
    }

    while(iHead) { // assign all items to their new queue
        iHead->iQueue = &aQueue;
        iHead = iHead->iNext;
    }

    iHead = 0;
    aQueue.iCount += iCount;
    iCount = 0;
}

QueueEntryBase& QueueBase::DoMoveHeadTo(QueueBase& aQueue)
{
    QueueEntryBase* entry = iHead;
    if (entry) {
        iHead = entry->iNext;
        if (iHead) {
            iHead->iPrev = 0;
        }
        iCount--;
        aQueue.DoAdd(entry);
        return *entry;
    }

    THROW(QueueEmpty);
}

void QueueEntryBase::DoMoveTo(QueueBase& aQueue)
{
    if (iNext) {
        iNext->iPrev = iPrev;
    }
    if (iPrev) {
        iPrev->iNext = iNext;
    }
    else { // was at the head of the chain
        iQueue->iHead = iNext;
    }

    iQueue->iCount--;
    iPrev = 0;
    iNext = aQueue.iHead;
    iQueue = &aQueue;
    if (aQueue.iHead) {
        aQueue.iHead->iPrev = this;
    }

    aQueue.iHead = this;
    aQueue.iCount++;
}

QueueBase::~QueueBase()
{
    while (iHead) {
        QueueEntryBase* entry = iHead;
        iHead = entry->iNext;
        delete (entry);
    }
}

// QueueSortedEntry

QueueSortedEntry::QueueSortedEntry()
: iNext(0), iPrev(0)
{
}

QueueSortedEntry& QueueSortedEntry::Next()
{
    ASSERT(iNext);
    return (*iNext);
}

QueueSortedEntry& QueueSortedEntry::Prev()
{
    ASSERT(iPrev);
    return (*iPrev);
}

void QueueSortedEntry::AddBefore(QueueSortedEntry& aEntry)
{
    ASSERT(!iPrev && !iNext);
    iPrev = aEntry.iPrev;
    iNext = &aEntry;
    iPrev->iNext = this;
    iNext->iPrev = this;
}

void QueueSortedEntry::Remove()
{
    ASSERT(iPrev && iNext);
    iPrev->iNext = iNext;
    iNext->iPrev = iPrev;
    iNext = 0;
    iPrev = 0;
}

void QueueSortedEntry::SetNext(QueueSortedEntry& aEntry)
{
    iNext = &aEntry;
}

void QueueSortedEntry::SetPrev(QueueSortedEntry& aEntry)
{
    iPrev = &aEntry;
}


// QueueSortedEntryHead

QueueSortedEntryHead::QueueSortedEntryHead()
{
}

// QueueSortedEntryTail

QueueSortedEntryTail::QueueSortedEntryTail()
{
}

// QueueSorted

QueueSortedBase::QueueSortedBase() : iMutex("QSBM")
{
    iHead.SetNext(iTail);
    iTail.SetPrev(iHead);
}

TBool QueueSortedBase::IsEmpty()
{
    return IsTail(iHead.Next());
}

TBool QueueSortedBase::IsTail(QueueSortedEntry& aEntry) const
{
    return (&aEntry == &iTail);
}

void QueueSortedBase::DoAdd(QueueSortedEntry& aEntry)
{
    iMutex.Wait();

    if (aEntry.iPrev || aEntry.iNext) {
        iMutex.Signal();
        ASSERTS();
    }

    QueueSortedEntry* head1 = &iHead.Next();
    QueueSortedEntry* ptr = &iHead.Next();
    for (;;) {
        if (ptr == &iTail || Compare(aEntry, *ptr) <= 0) {
            break;
        }
        ptr = &ptr->Next();
    }

    aEntry.AddBefore(*ptr);
    QueueSortedEntry* head2 = &iHead.Next();
    if (head1 != head2) {
        HeadChanged(*head2);
    }

    iMutex.Signal();
}

void QueueSortedBase::DoRemove(QueueSortedEntry& aEntry)
{
    iMutex.Wait();

    if (aEntry.iPrev || aEntry.iNext) { // ignore if already removed
        QueueSortedEntry* head1 = &iHead.Next();
        aEntry.Remove();
        QueueSortedEntry* head2 = &iHead.Next();
        if (head1 != head2) {
            HeadChanged(*head2);
        }
    }

    iMutex.Signal();
}

QueueSortedEntry& QueueSortedBase::DoRemoveHead()
{
    iMutex.Wait();

    QueueSortedEntry* ptr = &iHead.Next();
    if (ptr == &iTail) {
        iMutex.Signal();
        ASSERTS();
    }
    ptr->Remove();
    if (!IsEmpty()) {
        HeadChanged(iHead.Next());
    }

    iMutex.Signal();

    return *ptr;
}

void QueueSortedBase::HeadChanged(QueueSortedEntry& /*aEntry*/)
{
}

QueueSortedBase::~QueueSortedBase()
{
}
