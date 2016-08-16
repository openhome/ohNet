#ifndef HEADER_DVI_PROPERTY_UPDATE_COLLECTION
#define HEADER_DVI_PROPERTY_UPDATE_COLLECTION

#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Net/Private/DviSubscription.h>

#include <map>

EXCEPTION(InvalidSid)
EXCEPTION(InvalidClientId)

namespace OpenHome {
namespace Net {

class PropertyUpdate
{
public:
    class Property
    {
    public:
        Property(const Brx& aName, const Brx& aValue);
        Property(const Brx& aName, WriterBwh& aValue);
        const Brx& Name() const;
        const Brx& Value() const;
        void TransferValueTo(Property& aDest);
    private:
        Brh iName;
        Brh iValue;
    };
public:
    PropertyUpdate(const Brx& aSid, TUint aSeqNum);
    ~PropertyUpdate();
    void Add(const Brx& aName, const Brx& aValue);
    void Add(const Brx& aName, WriterBwh& aValue);
    const Brx& Sid() const;
    TUint SeqNum() const;
    void Merge(PropertyUpdate& aPropertyUpdate);
    void Write(IWriter& aWriter);
private:
    Brh iSid;
    TUint iSeqNum;
    std::vector<Property*> iProperties;
};

class IPropertyUpdateMerger
{
public:
    virtual PropertyUpdate* MergeUpdate(PropertyUpdate* aUpdate) = 0;
};

class PropertyWriter2 : public IPropertyWriter, private INonCopyable
{
public:
    PropertyWriter2(IPropertyUpdateMerger& aMerger, const Brx& aSid, TUint aSeqNum);
    ~PropertyWriter2();
private: // IPropertyWriter
    void PropertyWriteString(const Brx& aName, const Brx& aValue);
    void PropertyWriteInt(const Brx& aName, TInt aValue);
    void PropertyWriteUint(const Brx& aName, TUint aValue);
    void PropertyWriteBool(const Brx& aName, TBool aValue);
    void PropertyWriteBinary(const Brx& aName, const Brx& aValue);
    void PropertyWriteEnd();
    void Release();
private:
    IPropertyUpdateMerger& iMerger;
    PropertyUpdate* iPropertyUpdate;
};

class PropertyUpdatesFlattened
{
public:
    PropertyUpdatesFlattened(const Brx& aClientId);
    ~PropertyUpdatesFlattened();
    const Brx& ClientId() const;
    void AddSubscription(DviSubscription* aSubscription);
    void RemoveSubscription(const Brx& aSid, TBool aExpired);
    TBool ContainsSubscription(const Brx& aSid) const;
    TBool IsEmpty() const;
    PropertyUpdate* MergeUpdate(PropertyUpdate* aUpdate);
    void SetClientSignal(Semaphore* aSem);
    void WriteUpdates(IWriter& aWriter);
private:
    Brh iClientId;
    typedef std::map<Brn,PropertyUpdate*,BufferCmp> UpdatesMap;
    UpdatesMap iUpdatesMap;
    typedef std::map<Brn,DviSubscription*,BufferCmp> SubscriptionMap;
    SubscriptionMap iSubscriptionMap;
    Semaphore* iSem;
};

class DvStack;

class DviPropertyUpdateCollection : public IPropertyWriterFactory, private IPropertyUpdateMerger
{
public:
    DviPropertyUpdateCollection(DvStack& aDvStack);
    ~DviPropertyUpdateCollection();
    void AddSubscription(const Brx& aClientId, DviSubscription* aSubscription);
    void RemoveSubscription(const Brx& aSid);
    void SetClientSignal(const Brx& aClientId, Semaphore* aSem);
    void WriteUpdates(const Brx& aClientId, IWriter& aWriter);
private:
    void RemoveSubscription(const Brx& aSid, TBool aExpired);
    PropertyUpdatesFlattened* FindByClientId(const Brx& aClientId);
    PropertyUpdatesFlattened* FindByClientId(const Brx& aClientId, TUint& aIndex);
    PropertyUpdatesFlattened* FindBySid(const Brx& aSid);
    PropertyUpdatesFlattened* FindBySid(const Brx& aSid, TUint& aIndex);
private: // IPropertyWriterFactory
    IPropertyWriter* ClaimWriter(const IDviSubscriptionUserData* aUserData, const Brx& aSid, TUint aSequenceNumber);
    void ReleaseWriter(IPropertyWriter* aWriter);
    void NotifySubscriptionCreated(const Brx& aSid);
    void NotifySubscriptionDeleted(const Brx& aSid);
    void NotifySubscriptionExpired(const Brx& aSid);
private: // IPropertyUpdateMerger
    PropertyUpdate* MergeUpdate(PropertyUpdate* aUpdate);
private:
    DvStack& iDvStack;
    Mutex iLock;
    std::vector<PropertyUpdatesFlattened*> iUpdates;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_DVI_PROPERTY_UPDATE_COLLECTION
