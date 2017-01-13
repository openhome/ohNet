#include <OpenHome/Net/Private/DviPropertyUpdateCollection.h>
#include <OpenHome/Net/Private/DviServerWebSocket.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Net/Private/DviSubscription.h>
#include <OpenHome/Net/Private/DviService.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Net/Private/DviStack.h>

using namespace OpenHome;
using namespace OpenHome::Net;

static void WriteTag(IWriter& aWriter, const Brx& aTag, const Brx& aValue)
{
    aWriter.Write('<');
    aWriter.Write(aTag);
    aWriter.Write('>');
    aWriter.Write(aValue);
    aWriter.Write('<');
    aWriter.Write('/');
    aWriter.Write(aTag);
    aWriter.Write('>');
}


// PropertyUpdate

PropertyUpdate::Property::Property(const Brx& aName, const Brx& aValue)
    : iName(aName)
    , iValue(aValue)
{
}

PropertyUpdate::Property::Property(const Brx& aName, WriterBwh& aValue)
    : iName(aName)
{
    aValue.TransferTo(iValue);
}

const Brx& PropertyUpdate::Property::Name() const
{
    return iName;
}

const Brx& PropertyUpdate::Property::Value() const
{
    return iValue;
}

void PropertyUpdate::Property::TransferValueTo(Property& aDest)
{
    iValue.TransferTo(aDest.iValue);
}

PropertyUpdate::PropertyUpdate(const Brx& aSid, TUint aSeqNum)
    : iSid(aSid)
    , iSeqNum(aSeqNum)
{
}

PropertyUpdate::~PropertyUpdate()
{
    for (TUint i=0; i<(TUint)iProperties.size(); i++) {
        delete iProperties[i];
    }
}

void PropertyUpdate::Add(const Brx& aName, const Brx& aValue)
{
    iProperties.push_back(new Property(aName, aValue));
}

void PropertyUpdate::Add(const Brx& aName, WriterBwh& aValue)
{
    iProperties.push_back(new Property(aName, aValue));
}

const Brx& PropertyUpdate::Sid() const
{
    return iSid;
}

TUint PropertyUpdate::SeqNum() const
{
    return iSeqNum;
}

void PropertyUpdate::Merge(PropertyUpdate& aPropertyUpdate)
{
    if (aPropertyUpdate.iProperties.size() == 0) {
        return;
    }
    ASSERT(iSid == aPropertyUpdate.Sid());
    ASSERT(iSeqNum < aPropertyUpdate.SeqNum());
    iSeqNum = aPropertyUpdate.SeqNum();
    for (TInt i=(TInt)aPropertyUpdate.iProperties.size() - 1; i >= 0; i--) {
        TBool found = false;
        Property* srcProp = aPropertyUpdate.iProperties[i];
        for (TUint j=0; j<iProperties.size(); j++) {
            Property* destProp = iProperties[j];
            if (destProp->Name() == srcProp->Name()) {
                srcProp->TransferValueTo(*destProp);
                found = true;
                break;
            }
        }
        if (!found) {
            iProperties.push_back(srcProp);
            aPropertyUpdate.iProperties.erase(aPropertyUpdate.iProperties.begin() + i);
        }
    }
}

void PropertyUpdate::Write(IWriter& aWriter)
{
    aWriter.Write('<');
    aWriter.Write(WebSocket::kTagSubscription);
    aWriter.Write('>');
    WriteTag(aWriter, WebSocket::kTagMethod, WebSocket::kMethodPropertyUpdate);
    WriteTag(aWriter, WebSocket::kTagSid, iSid);
    Bws<Ascii::kMaxUintStringBytes> seq;
    (void)Ascii::AppendDec(seq, iSeqNum);
    WriteTag(aWriter, WebSocket::kTagSeq, seq);
    aWriter.Write(Brn("<e:propertyset xmlns:e=\"urn:schemas-upnp-org:event-1-0\">"));
    for (TUint i=0; i<(TUint)iProperties.size(); i++) {
        PropertyWriter::WriteVariable(aWriter, iProperties[i]->Name(), iProperties[i]->Value());
    }
    aWriter.Write(Brn("</e:propertyset>"));
    aWriter.Write('<');
    aWriter.Write('/');
    aWriter.Write(WebSocket::kTagSubscription);
    aWriter.Write('>');
}


// PropertyWriter2

PropertyWriter2::PropertyWriter2(IPropertyUpdateMerger& aMerger, const Brx& aSid, TUint aSeqNum)
    : iMerger(aMerger)
{
    iPropertyUpdate = new PropertyUpdate(aSid, aSeqNum);
}

PropertyWriter2::~PropertyWriter2()
{
    delete iPropertyUpdate;
}

void PropertyWriter2::PropertyWriteString(const Brx& aName, const Brx& aValue)
{
    WriterBwh writer(1024);
    Converter::ToXmlEscaped(writer, aValue);
    iPropertyUpdate->Add(aName, writer);
}

void PropertyWriter2::PropertyWriteInt(const Brx& aName, TInt aValue)
{
    Bws<Ascii::kMaxIntStringBytes> buf;
    (void)Ascii::AppendDec(buf, aValue);
    iPropertyUpdate->Add(aName, buf);
}

void PropertyWriter2::PropertyWriteUint(const Brx& aName, TUint aValue)
{
    Bws<Ascii::kMaxUintStringBytes> buf;
    (void)Ascii::AppendDec(buf, aValue);
    iPropertyUpdate->Add(aName, buf);
}

void PropertyWriter2::PropertyWriteBool(const Brx& aName, TBool aValue)
{
    PropertyWriteUint(aName, (aValue? 1 : 0));
}

void PropertyWriter2::PropertyWriteBinary(const Brx& aName, const Brx& aValue)
{
    WriterBwh writer(1024);
    Converter::ToBase64(writer, aValue);
    iPropertyUpdate->Add(aName, writer);
}

void PropertyWriter2::PropertyWriteEnd()
{
    iPropertyUpdate = iMerger.MergeUpdate(iPropertyUpdate);
}

void PropertyWriter2::Release()
{
    delete this;
}

   
// PropertyUpdatesFlattened

PropertyUpdatesFlattened::PropertyUpdatesFlattened(const Brx& aClientId)
    : iClientId(aClientId)
    , iSem(NULL)
{
}

PropertyUpdatesFlattened::~PropertyUpdatesFlattened()
{
    UpdatesMap::iterator it = iUpdatesMap.begin();
    while (it != iUpdatesMap.end()) {
        delete it->second;
        it++;
    }
    // don't clear iSubscriptionMap.  Assume the subscriptions will already have been cleared.
    /*SubscriptionMap::iterator it2 = iSubscriptionMap.begin();
    while (it2 != iSubscriptionMap.end()) {
        DviSubscription* subscription = it2->second;
        subscription->Service()->RemoveSubscription(subscription->Sid());
        it2++;
    }*/
}

const Brx& PropertyUpdatesFlattened::ClientId() const
{
    return iClientId;
}

void PropertyUpdatesFlattened::AddSubscription(DviSubscription* aSubscription)
{
    Brn buf(aSubscription->Sid());
    iSubscriptionMap.insert(std::pair<Brn,DviSubscription*>(buf, aSubscription));
}

void PropertyUpdatesFlattened::RemoveSubscription(const Brx& aSid, TBool aExpired)
{
    Brn sid(aSid);
    SubscriptionMap::iterator it = iSubscriptionMap.find(sid);
    if (it != iSubscriptionMap.end()) {
        // remove any pending updates for this subscription too
        UpdatesMap::iterator it2 = iUpdatesMap.find(sid);
        if (it2 != iUpdatesMap.end()) {
            delete it2->second;
            iUpdatesMap.erase(it2);
        }
        DviSubscription* subscription = it->second;
        iSubscriptionMap.erase(it);
        if (!aExpired) {
            subscription->Remove();
        }
    }
}

TBool PropertyUpdatesFlattened::ContainsSubscription(const Brx& aSid) const
{
    Brn sid(aSid);
    return (iSubscriptionMap.find(sid) != iSubscriptionMap.end());
}

TBool PropertyUpdatesFlattened::IsEmpty() const
{
    return (iSubscriptionMap.size() == 0);
}

PropertyUpdate* PropertyUpdatesFlattened::MergeUpdate(PropertyUpdate* aUpdate)
{
    PropertyUpdate* ret = aUpdate;
    Brn sid(aUpdate->Sid());
    UpdatesMap::iterator it = iUpdatesMap.find(sid);
    if (it == iUpdatesMap.end()) {
        iUpdatesMap.insert(std::pair<Brn,PropertyUpdate*>(sid, aUpdate));
        ret = NULL;
    }
    else {
        it->second->Merge(*aUpdate);
    }
    if (iSem != NULL) {
        iSem->Signal();
        iSem = NULL;
    }
    return ret;
}

void PropertyUpdatesFlattened::SetClientSignal(Semaphore* aSem)
{
    iSem = aSem;
    if (iSem != NULL && iUpdatesMap.size() > 0) {
        iSem->Signal();
        iSem = NULL;
    }
}

void PropertyUpdatesFlattened::WriteUpdates(IWriter& aWriter)
{
    aWriter.Write(Brn("<root>"));
    UpdatesMap::iterator it = iUpdatesMap.begin();
    while (it != iUpdatesMap.end()) {
        it->second->Write(aWriter);
        delete it->second;
        it++;
    }
    iUpdatesMap.clear();
    aWriter.Write(Brn("</root>"));
}


// DviPropertyUpdateCollection

DviPropertyUpdateCollection::DviPropertyUpdateCollection(DvStack& aDvStack)
    : iDvStack(aDvStack)
    , iLock("MPUC")
{
}

DviPropertyUpdateCollection::~DviPropertyUpdateCollection()
{
    // we rely on DviPropertyUpdateCollection being deleted after DviSubscriptionManager
    // ...this means we can assume that all subscriptions have already been deleted
    // ...so we can destroy our remaining objects without worrying about publisher threads being in the process of writing updates
    for (TUint i=0; i<(TUint)iUpdates.size(); i++) {
        delete iUpdates[i];
    }
}

void DviPropertyUpdateCollection::AddSubscription(const Brx& aClientId, DviSubscription* aSubscription)
{
    AutoMutex a(iLock);
    PropertyUpdatesFlattened* updates = FindByClientId(aClientId);
    if (updates == NULL) {
        updates = new PropertyUpdatesFlattened(aClientId);
        iUpdates.push_back(updates);
    }
    updates->AddSubscription(aSubscription);
}

void DviPropertyUpdateCollection::RemoveSubscription(const Brx& aSid)
{
    RemoveSubscription(aSid, false);
}

void DviPropertyUpdateCollection::RemoveSubscription(const Brx& aSid, TBool aExpired)
{
    AutoMutex a(iLock);
    TUint index;
    PropertyUpdatesFlattened* updates = FindBySid(aSid, index);
    if (updates == NULL) {
        THROW(InvalidSid);
    }
    updates->RemoveSubscription(aSid, aExpired);
    if (updates->IsEmpty()) {
        delete updates;
        iUpdates.erase(iUpdates.begin() + index);
    }
}

void DviPropertyUpdateCollection::SetClientSignal(const Brx& aClientId, Semaphore* aSem)
{
    AutoMutex a(iLock);
    PropertyUpdatesFlattened* updates = FindByClientId(aClientId);
    if (updates == NULL) {
        THROW(InvalidClientId);
    }
    updates->SetClientSignal(aSem);
}

void DviPropertyUpdateCollection::WriteUpdates(const Brx& aClientId, IWriter& aWriter)
{
    AutoMutex a(iLock);
    PropertyUpdatesFlattened* updates = FindByClientId(aClientId);
    if (updates == NULL) {
        THROW(InvalidClientId);
    }
    updates->WriteUpdates(aWriter);
}

PropertyUpdatesFlattened* DviPropertyUpdateCollection::FindByClientId(const Brx& aClientId)
{
    TUint ignore;
    return FindByClientId(aClientId, ignore);
}

PropertyUpdatesFlattened* DviPropertyUpdateCollection::FindByClientId(const Brx& aClientId, TUint& aIndex)
{
    // assumes called with iLock held
    for (TUint i=0; i<(TUint)iUpdates.size(); i++) {
        PropertyUpdatesFlattened* updates = iUpdates[i];
        if (updates->ClientId() == aClientId) {
            aIndex = i;
            return updates;
        }
    }
    aIndex = 0xffffffff;
    return NULL;
}

PropertyUpdatesFlattened* DviPropertyUpdateCollection::FindBySid(const Brx& aSid)
{
    TUint ignore;
    return FindBySid(aSid, ignore);
}

PropertyUpdatesFlattened* DviPropertyUpdateCollection::FindBySid(const Brx& aSid, TUint& aIndex)
{
    // assumes called with iLock held
    for (TUint i=0; i<(TUint)iUpdates.size(); i++) {
        PropertyUpdatesFlattened* updates = iUpdates[i];
        if (updates->ContainsSubscription(aSid)) {
            aIndex = i;
            return updates;
        }
    }
    aIndex = 0xffffffff;
    return NULL;
}

IPropertyWriter* DviPropertyUpdateCollection::ClaimWriter(const IDviSubscriptionUserData* /*aUserData*/, const Brx& aSid, TUint aSequenceNumber)
{
    AutoMutex a(iLock);
    if (FindBySid(aSid) != NULL) {
        return new PropertyWriter2(*this, aSid, aSequenceNumber);
    }
    return NULL;
}

void DviPropertyUpdateCollection::ReleaseWriter(IPropertyWriter* aWriter)
{
    delete aWriter;
}

void DviPropertyUpdateCollection::NotifySubscriptionCreated(const Brx& /*aSid*/)
{
}

void DviPropertyUpdateCollection::NotifySubscriptionDeleted(const Brx& /*aSid*/)
{
}

void DviPropertyUpdateCollection::NotifySubscriptionExpired(const Brx& aSid)
{
    try {
        // We'll get here after a call to RemoveSubscription.
        // ...and calling it again will cause a recursive lock.
        // use of Timer::IsInManagerThread is nasty.  We have no way of knowing that this'll only be called recursively or in a timer callback.
        // Note that this also turns out to be a handy way of avoiding problems inside ~DviPropertyUpdateCollection
        if (Timer::IsInManagerThread(iDvStack.Env())) {
            RemoveSubscription(aSid, true);
        }
    }
    catch (InvalidSid&) { }
}

void DviPropertyUpdateCollection::LogUserData(IWriter& /*aWriter*/, const IDviSubscriptionUserData& /*aUserData*/)
{
}

PropertyUpdate* DviPropertyUpdateCollection::MergeUpdate(PropertyUpdate* aUpdate)
{
    AutoMutex a(iLock);
    PropertyUpdatesFlattened* updates = FindBySid(aUpdate->Sid());
    if (updates == NULL) {
        delete aUpdate;
        return NULL;
    }
    return updates->MergeUpdate(aUpdate);
}
