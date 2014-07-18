#include "CpAvOpenhomeOrgPlaylistManager1.h"
#include <OpenHome/Net/Core/CpDevice.h>
#include <OpenHome/Net/C/CpProxyCPrivate.h>
#include <OpenHome/Net/Core/FunctorAsync.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Net/Core/CpProxy.h>
#include <OpenHome/Net/Private/CpiService.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Net/Private/AsyncPrivate.h>
#include <OpenHome/Net/Core/CpDevice.h>
#include <OpenHome/Net/Private/CpiDevice.h>

using namespace OpenHome;
using namespace OpenHome::Net;

class CpProxyAvOpenhomeOrgPlaylistManager1C : public CpProxyC
{
public:
    CpProxyAvOpenhomeOrgPlaylistManager1C(CpDeviceC aDevice);
    ~CpProxyAvOpenhomeOrgPlaylistManager1C();
    //CpProxyAvOpenhomeOrgPlaylistManager1* Proxy() { return static_cast<CpProxyAvOpenhomeOrgPlaylistManager1*>(iProxy); }

    void SyncMetadata(Brh& aMetadata);
    void BeginMetadata(FunctorAsync& aFunctor);
    void EndMetadata(IAsync& aAsync, Brh& aMetadata);

    void SyncImagesXml(Brh& aImagesXml);
    void BeginImagesXml(FunctorAsync& aFunctor);
    void EndImagesXml(IAsync& aAsync, Brh& aImagesXml);

    void SyncPlaylistReadArray(TUint aId, Brh& aArray);
    void BeginPlaylistReadArray(TUint aId, FunctorAsync& aFunctor);
    void EndPlaylistReadArray(IAsync& aAsync, Brh& aArray);

    void SyncPlaylistReadList(const Brx& aIdList, Brh& aPlaylistList);
    void BeginPlaylistReadList(const Brx& aIdList, FunctorAsync& aFunctor);
    void EndPlaylistReadList(IAsync& aAsync, Brh& aPlaylistList);

    void SyncPlaylistRead(TUint aId, Brh& aName, Brh& aDescription, TUint& aImageId);
    void BeginPlaylistRead(TUint aId, FunctorAsync& aFunctor);
    void EndPlaylistRead(IAsync& aAsync, Brh& aName, Brh& aDescription, TUint& aImageId);

    void SyncPlaylistSetName(TUint aId, const Brx& aName);
    void BeginPlaylistSetName(TUint aId, const Brx& aName, FunctorAsync& aFunctor);
    void EndPlaylistSetName(IAsync& aAsync);

    void SyncPlaylistSetDescription(TUint aId, const Brx& aDescription);
    void BeginPlaylistSetDescription(TUint aId, const Brx& aDescription, FunctorAsync& aFunctor);
    void EndPlaylistSetDescription(IAsync& aAsync);

    void SyncPlaylistSetImageId(TUint aId, TUint aImageId);
    void BeginPlaylistSetImageId(TUint aId, TUint aImageId, FunctorAsync& aFunctor);
    void EndPlaylistSetImageId(IAsync& aAsync);

    void SyncPlaylistInsert(TUint aAfterId, const Brx& aName, const Brx& aDescription, TUint aImageId, TUint& aNewId);
    void BeginPlaylistInsert(TUint aAfterId, const Brx& aName, const Brx& aDescription, TUint aImageId, FunctorAsync& aFunctor);
    void EndPlaylistInsert(IAsync& aAsync, TUint& aNewId);

    void SyncPlaylistDeleteId(TUint aValue);
    void BeginPlaylistDeleteId(TUint aValue, FunctorAsync& aFunctor);
    void EndPlaylistDeleteId(IAsync& aAsync);

    void SyncPlaylistMove(TUint aId, TUint aAfterId);
    void BeginPlaylistMove(TUint aId, TUint aAfterId, FunctorAsync& aFunctor);
    void EndPlaylistMove(IAsync& aAsync);

    void SyncPlaylistsMax(TUint& aValue);
    void BeginPlaylistsMax(FunctorAsync& aFunctor);
    void EndPlaylistsMax(IAsync& aAsync, TUint& aValue);

    void SyncTracksMax(TUint& aValue);
    void BeginTracksMax(FunctorAsync& aFunctor);
    void EndTracksMax(IAsync& aAsync, TUint& aValue);

    void SyncPlaylistArrays(TUint& aToken, Brh& aIdArray, Brh& aTokenArray);
    void BeginPlaylistArrays(FunctorAsync& aFunctor);
    void EndPlaylistArrays(IAsync& aAsync, TUint& aToken, Brh& aIdArray, Brh& aTokenArray);

    void SyncPlaylistArraysChanged(TUint aToken, TBool& aValue);
    void BeginPlaylistArraysChanged(TUint aToken, FunctorAsync& aFunctor);
    void EndPlaylistArraysChanged(IAsync& aAsync, TBool& aValue);

    void SyncRead(TUint aId, TUint aTrackId, Brh& aMetadata);
    void BeginRead(TUint aId, TUint aTrackId, FunctorAsync& aFunctor);
    void EndRead(IAsync& aAsync, Brh& aMetadata);

    void SyncReadList(TUint aId, const Brx& aTrackIdList, Brh& aTrackList);
    void BeginReadList(TUint aId, const Brx& aTrackIdList, FunctorAsync& aFunctor);
    void EndReadList(IAsync& aAsync, Brh& aTrackList);

    void SyncInsert(TUint aId, TUint aAfterTrackId, const Brx& aMetadata, TUint& aNewTrackId);
    void BeginInsert(TUint aId, TUint aAfterTrackId, const Brx& aMetadata, FunctorAsync& aFunctor);
    void EndInsert(IAsync& aAsync, TUint& aNewTrackId);

    void SyncDeleteId(TUint aId, TUint aTrackId);
    void BeginDeleteId(TUint aId, TUint aTrackId, FunctorAsync& aFunctor);
    void EndDeleteId(IAsync& aAsync);

    void SyncDeleteAll(TUint aId);
    void BeginDeleteAll(TUint aId, FunctorAsync& aFunctor);
    void EndDeleteAll(IAsync& aAsync);

    void SetPropertyMetadataChanged(Functor& aFunctor);
    void SetPropertyImagesXmlChanged(Functor& aFunctor);
    void SetPropertyIdArrayChanged(Functor& aFunctor);
    void SetPropertyTokenArrayChanged(Functor& aFunctor);
    void SetPropertyPlaylistsMaxChanged(Functor& aFunctor);
    void SetPropertyTracksMaxChanged(Functor& aFunctor);

    void PropertyMetadata(Brhz& aMetadata) const;
    void PropertyImagesXml(Brhz& aImagesXml) const;
    void PropertyIdArray(Brh& aIdArray) const;
    void PropertyTokenArray(Brh& aTokenArray) const;
    void PropertyPlaylistsMax(TUint& aPlaylistsMax) const;
    void PropertyTracksMax(TUint& aTracksMax) const;
private:
    void MetadataPropertyChanged();
    void ImagesXmlPropertyChanged();
    void IdArrayPropertyChanged();
    void TokenArrayPropertyChanged();
    void PlaylistsMaxPropertyChanged();
    void TracksMaxPropertyChanged();
private:
    Mutex iLock;
    Action* iActionMetadata;
    Action* iActionImagesXml;
    Action* iActionPlaylistReadArray;
    Action* iActionPlaylistReadList;
    Action* iActionPlaylistRead;
    Action* iActionPlaylistSetName;
    Action* iActionPlaylistSetDescription;
    Action* iActionPlaylistSetImageId;
    Action* iActionPlaylistInsert;
    Action* iActionPlaylistDeleteId;
    Action* iActionPlaylistMove;
    Action* iActionPlaylistsMax;
    Action* iActionTracksMax;
    Action* iActionPlaylistArrays;
    Action* iActionPlaylistArraysChanged;
    Action* iActionRead;
    Action* iActionReadList;
    Action* iActionInsert;
    Action* iActionDeleteId;
    Action* iActionDeleteAll;
    PropertyString* iMetadata;
    PropertyString* iImagesXml;
    PropertyBinary* iIdArray;
    PropertyBinary* iTokenArray;
    PropertyUint* iPlaylistsMax;
    PropertyUint* iTracksMax;
    Functor iMetadataChanged;
    Functor iImagesXmlChanged;
    Functor iIdArrayChanged;
    Functor iTokenArrayChanged;
    Functor iPlaylistsMaxChanged;
    Functor iTracksMaxChanged;
};


class SyncMetadataAvOpenhomeOrgPlaylistManager1C : public SyncProxyAction
{
public:
    SyncMetadataAvOpenhomeOrgPlaylistManager1C(CpProxyAvOpenhomeOrgPlaylistManager1C& aProxy, Brh& aMetadata);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncMetadataAvOpenhomeOrgPlaylistManager1C() {};
private:
    CpProxyAvOpenhomeOrgPlaylistManager1C& iService;
    Brh& iMetadata;
};

SyncMetadataAvOpenhomeOrgPlaylistManager1C::SyncMetadataAvOpenhomeOrgPlaylistManager1C(CpProxyAvOpenhomeOrgPlaylistManager1C& aProxy, Brh& aMetadata)
    : iService(aProxy)
    , iMetadata(aMetadata)
{
}

void SyncMetadataAvOpenhomeOrgPlaylistManager1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndMetadata(aAsync, iMetadata);
}


class SyncImagesXmlAvOpenhomeOrgPlaylistManager1C : public SyncProxyAction
{
public:
    SyncImagesXmlAvOpenhomeOrgPlaylistManager1C(CpProxyAvOpenhomeOrgPlaylistManager1C& aProxy, Brh& aImagesXml);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncImagesXmlAvOpenhomeOrgPlaylistManager1C() {};
private:
    CpProxyAvOpenhomeOrgPlaylistManager1C& iService;
    Brh& iImagesXml;
};

SyncImagesXmlAvOpenhomeOrgPlaylistManager1C::SyncImagesXmlAvOpenhomeOrgPlaylistManager1C(CpProxyAvOpenhomeOrgPlaylistManager1C& aProxy, Brh& aImagesXml)
    : iService(aProxy)
    , iImagesXml(aImagesXml)
{
}

void SyncImagesXmlAvOpenhomeOrgPlaylistManager1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndImagesXml(aAsync, iImagesXml);
}


class SyncPlaylistReadArrayAvOpenhomeOrgPlaylistManager1C : public SyncProxyAction
{
public:
    SyncPlaylistReadArrayAvOpenhomeOrgPlaylistManager1C(CpProxyAvOpenhomeOrgPlaylistManager1C& aProxy, Brh& aArray);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncPlaylistReadArrayAvOpenhomeOrgPlaylistManager1C() {};
private:
    CpProxyAvOpenhomeOrgPlaylistManager1C& iService;
    Brh& iArray;
};

SyncPlaylistReadArrayAvOpenhomeOrgPlaylistManager1C::SyncPlaylistReadArrayAvOpenhomeOrgPlaylistManager1C(CpProxyAvOpenhomeOrgPlaylistManager1C& aProxy, Brh& aArray)
    : iService(aProxy)
    , iArray(aArray)
{
}

void SyncPlaylistReadArrayAvOpenhomeOrgPlaylistManager1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndPlaylistReadArray(aAsync, iArray);
}


class SyncPlaylistReadListAvOpenhomeOrgPlaylistManager1C : public SyncProxyAction
{
public:
    SyncPlaylistReadListAvOpenhomeOrgPlaylistManager1C(CpProxyAvOpenhomeOrgPlaylistManager1C& aProxy, Brh& aPlaylistList);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncPlaylistReadListAvOpenhomeOrgPlaylistManager1C() {};
private:
    CpProxyAvOpenhomeOrgPlaylistManager1C& iService;
    Brh& iPlaylistList;
};

SyncPlaylistReadListAvOpenhomeOrgPlaylistManager1C::SyncPlaylistReadListAvOpenhomeOrgPlaylistManager1C(CpProxyAvOpenhomeOrgPlaylistManager1C& aProxy, Brh& aPlaylistList)
    : iService(aProxy)
    , iPlaylistList(aPlaylistList)
{
}

void SyncPlaylistReadListAvOpenhomeOrgPlaylistManager1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndPlaylistReadList(aAsync, iPlaylistList);
}


class SyncPlaylistReadAvOpenhomeOrgPlaylistManager1C : public SyncProxyAction
{
public:
    SyncPlaylistReadAvOpenhomeOrgPlaylistManager1C(CpProxyAvOpenhomeOrgPlaylistManager1C& aProxy, Brh& aName, Brh& aDescription, TUint& aImageId);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncPlaylistReadAvOpenhomeOrgPlaylistManager1C() {};
private:
    CpProxyAvOpenhomeOrgPlaylistManager1C& iService;
    Brh& iName;
    Brh& iDescription;
    TUint& iImageId;
};

SyncPlaylistReadAvOpenhomeOrgPlaylistManager1C::SyncPlaylistReadAvOpenhomeOrgPlaylistManager1C(CpProxyAvOpenhomeOrgPlaylistManager1C& aProxy, Brh& aName, Brh& aDescription, TUint& aImageId)
    : iService(aProxy)
    , iName(aName)
    , iDescription(aDescription)
    , iImageId(aImageId)
{
}

void SyncPlaylistReadAvOpenhomeOrgPlaylistManager1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndPlaylistRead(aAsync, iName, iDescription, iImageId);
}


class SyncPlaylistSetNameAvOpenhomeOrgPlaylistManager1C : public SyncProxyAction
{
public:
    SyncPlaylistSetNameAvOpenhomeOrgPlaylistManager1C(CpProxyAvOpenhomeOrgPlaylistManager1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncPlaylistSetNameAvOpenhomeOrgPlaylistManager1C() {};
private:
    CpProxyAvOpenhomeOrgPlaylistManager1C& iService;
};

SyncPlaylistSetNameAvOpenhomeOrgPlaylistManager1C::SyncPlaylistSetNameAvOpenhomeOrgPlaylistManager1C(CpProxyAvOpenhomeOrgPlaylistManager1C& aProxy)
    : iService(aProxy)
{
}

void SyncPlaylistSetNameAvOpenhomeOrgPlaylistManager1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndPlaylistSetName(aAsync);
}


class SyncPlaylistSetDescriptionAvOpenhomeOrgPlaylistManager1C : public SyncProxyAction
{
public:
    SyncPlaylistSetDescriptionAvOpenhomeOrgPlaylistManager1C(CpProxyAvOpenhomeOrgPlaylistManager1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncPlaylistSetDescriptionAvOpenhomeOrgPlaylistManager1C() {};
private:
    CpProxyAvOpenhomeOrgPlaylistManager1C& iService;
};

SyncPlaylistSetDescriptionAvOpenhomeOrgPlaylistManager1C::SyncPlaylistSetDescriptionAvOpenhomeOrgPlaylistManager1C(CpProxyAvOpenhomeOrgPlaylistManager1C& aProxy)
    : iService(aProxy)
{
}

void SyncPlaylistSetDescriptionAvOpenhomeOrgPlaylistManager1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndPlaylistSetDescription(aAsync);
}


class SyncPlaylistSetImageIdAvOpenhomeOrgPlaylistManager1C : public SyncProxyAction
{
public:
    SyncPlaylistSetImageIdAvOpenhomeOrgPlaylistManager1C(CpProxyAvOpenhomeOrgPlaylistManager1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncPlaylistSetImageIdAvOpenhomeOrgPlaylistManager1C() {};
private:
    CpProxyAvOpenhomeOrgPlaylistManager1C& iService;
};

SyncPlaylistSetImageIdAvOpenhomeOrgPlaylistManager1C::SyncPlaylistSetImageIdAvOpenhomeOrgPlaylistManager1C(CpProxyAvOpenhomeOrgPlaylistManager1C& aProxy)
    : iService(aProxy)
{
}

void SyncPlaylistSetImageIdAvOpenhomeOrgPlaylistManager1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndPlaylistSetImageId(aAsync);
}


class SyncPlaylistInsertAvOpenhomeOrgPlaylistManager1C : public SyncProxyAction
{
public:
    SyncPlaylistInsertAvOpenhomeOrgPlaylistManager1C(CpProxyAvOpenhomeOrgPlaylistManager1C& aProxy, TUint& aNewId);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncPlaylistInsertAvOpenhomeOrgPlaylistManager1C() {};
private:
    CpProxyAvOpenhomeOrgPlaylistManager1C& iService;
    TUint& iNewId;
};

SyncPlaylistInsertAvOpenhomeOrgPlaylistManager1C::SyncPlaylistInsertAvOpenhomeOrgPlaylistManager1C(CpProxyAvOpenhomeOrgPlaylistManager1C& aProxy, TUint& aNewId)
    : iService(aProxy)
    , iNewId(aNewId)
{
}

void SyncPlaylistInsertAvOpenhomeOrgPlaylistManager1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndPlaylistInsert(aAsync, iNewId);
}


class SyncPlaylistDeleteIdAvOpenhomeOrgPlaylistManager1C : public SyncProxyAction
{
public:
    SyncPlaylistDeleteIdAvOpenhomeOrgPlaylistManager1C(CpProxyAvOpenhomeOrgPlaylistManager1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncPlaylistDeleteIdAvOpenhomeOrgPlaylistManager1C() {};
private:
    CpProxyAvOpenhomeOrgPlaylistManager1C& iService;
};

SyncPlaylistDeleteIdAvOpenhomeOrgPlaylistManager1C::SyncPlaylistDeleteIdAvOpenhomeOrgPlaylistManager1C(CpProxyAvOpenhomeOrgPlaylistManager1C& aProxy)
    : iService(aProxy)
{
}

void SyncPlaylistDeleteIdAvOpenhomeOrgPlaylistManager1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndPlaylistDeleteId(aAsync);
}


class SyncPlaylistMoveAvOpenhomeOrgPlaylistManager1C : public SyncProxyAction
{
public:
    SyncPlaylistMoveAvOpenhomeOrgPlaylistManager1C(CpProxyAvOpenhomeOrgPlaylistManager1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncPlaylistMoveAvOpenhomeOrgPlaylistManager1C() {};
private:
    CpProxyAvOpenhomeOrgPlaylistManager1C& iService;
};

SyncPlaylistMoveAvOpenhomeOrgPlaylistManager1C::SyncPlaylistMoveAvOpenhomeOrgPlaylistManager1C(CpProxyAvOpenhomeOrgPlaylistManager1C& aProxy)
    : iService(aProxy)
{
}

void SyncPlaylistMoveAvOpenhomeOrgPlaylistManager1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndPlaylistMove(aAsync);
}


class SyncPlaylistsMaxAvOpenhomeOrgPlaylistManager1C : public SyncProxyAction
{
public:
    SyncPlaylistsMaxAvOpenhomeOrgPlaylistManager1C(CpProxyAvOpenhomeOrgPlaylistManager1C& aProxy, TUint& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncPlaylistsMaxAvOpenhomeOrgPlaylistManager1C() {};
private:
    CpProxyAvOpenhomeOrgPlaylistManager1C& iService;
    TUint& iValue;
};

SyncPlaylistsMaxAvOpenhomeOrgPlaylistManager1C::SyncPlaylistsMaxAvOpenhomeOrgPlaylistManager1C(CpProxyAvOpenhomeOrgPlaylistManager1C& aProxy, TUint& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncPlaylistsMaxAvOpenhomeOrgPlaylistManager1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndPlaylistsMax(aAsync, iValue);
}


class SyncTracksMaxAvOpenhomeOrgPlaylistManager1C : public SyncProxyAction
{
public:
    SyncTracksMaxAvOpenhomeOrgPlaylistManager1C(CpProxyAvOpenhomeOrgPlaylistManager1C& aProxy, TUint& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncTracksMaxAvOpenhomeOrgPlaylistManager1C() {};
private:
    CpProxyAvOpenhomeOrgPlaylistManager1C& iService;
    TUint& iValue;
};

SyncTracksMaxAvOpenhomeOrgPlaylistManager1C::SyncTracksMaxAvOpenhomeOrgPlaylistManager1C(CpProxyAvOpenhomeOrgPlaylistManager1C& aProxy, TUint& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncTracksMaxAvOpenhomeOrgPlaylistManager1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndTracksMax(aAsync, iValue);
}


class SyncPlaylistArraysAvOpenhomeOrgPlaylistManager1C : public SyncProxyAction
{
public:
    SyncPlaylistArraysAvOpenhomeOrgPlaylistManager1C(CpProxyAvOpenhomeOrgPlaylistManager1C& aProxy, TUint& aToken, Brh& aIdArray, Brh& aTokenArray);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncPlaylistArraysAvOpenhomeOrgPlaylistManager1C() {};
private:
    CpProxyAvOpenhomeOrgPlaylistManager1C& iService;
    TUint& iToken;
    Brh& iIdArray;
    Brh& iTokenArray;
};

SyncPlaylistArraysAvOpenhomeOrgPlaylistManager1C::SyncPlaylistArraysAvOpenhomeOrgPlaylistManager1C(CpProxyAvOpenhomeOrgPlaylistManager1C& aProxy, TUint& aToken, Brh& aIdArray, Brh& aTokenArray)
    : iService(aProxy)
    , iToken(aToken)
    , iIdArray(aIdArray)
    , iTokenArray(aTokenArray)
{
}

void SyncPlaylistArraysAvOpenhomeOrgPlaylistManager1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndPlaylistArrays(aAsync, iToken, iIdArray, iTokenArray);
}


class SyncPlaylistArraysChangedAvOpenhomeOrgPlaylistManager1C : public SyncProxyAction
{
public:
    SyncPlaylistArraysChangedAvOpenhomeOrgPlaylistManager1C(CpProxyAvOpenhomeOrgPlaylistManager1C& aProxy, TBool& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncPlaylistArraysChangedAvOpenhomeOrgPlaylistManager1C() {};
private:
    CpProxyAvOpenhomeOrgPlaylistManager1C& iService;
    TBool& iValue;
};

SyncPlaylistArraysChangedAvOpenhomeOrgPlaylistManager1C::SyncPlaylistArraysChangedAvOpenhomeOrgPlaylistManager1C(CpProxyAvOpenhomeOrgPlaylistManager1C& aProxy, TBool& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncPlaylistArraysChangedAvOpenhomeOrgPlaylistManager1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndPlaylistArraysChanged(aAsync, iValue);
}


class SyncReadAvOpenhomeOrgPlaylistManager1C : public SyncProxyAction
{
public:
    SyncReadAvOpenhomeOrgPlaylistManager1C(CpProxyAvOpenhomeOrgPlaylistManager1C& aProxy, Brh& aMetadata);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncReadAvOpenhomeOrgPlaylistManager1C() {};
private:
    CpProxyAvOpenhomeOrgPlaylistManager1C& iService;
    Brh& iMetadata;
};

SyncReadAvOpenhomeOrgPlaylistManager1C::SyncReadAvOpenhomeOrgPlaylistManager1C(CpProxyAvOpenhomeOrgPlaylistManager1C& aProxy, Brh& aMetadata)
    : iService(aProxy)
    , iMetadata(aMetadata)
{
}

void SyncReadAvOpenhomeOrgPlaylistManager1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndRead(aAsync, iMetadata);
}


class SyncReadListAvOpenhomeOrgPlaylistManager1C : public SyncProxyAction
{
public:
    SyncReadListAvOpenhomeOrgPlaylistManager1C(CpProxyAvOpenhomeOrgPlaylistManager1C& aProxy, Brh& aTrackList);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncReadListAvOpenhomeOrgPlaylistManager1C() {};
private:
    CpProxyAvOpenhomeOrgPlaylistManager1C& iService;
    Brh& iTrackList;
};

SyncReadListAvOpenhomeOrgPlaylistManager1C::SyncReadListAvOpenhomeOrgPlaylistManager1C(CpProxyAvOpenhomeOrgPlaylistManager1C& aProxy, Brh& aTrackList)
    : iService(aProxy)
    , iTrackList(aTrackList)
{
}

void SyncReadListAvOpenhomeOrgPlaylistManager1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndReadList(aAsync, iTrackList);
}


class SyncInsertAvOpenhomeOrgPlaylistManager1C : public SyncProxyAction
{
public:
    SyncInsertAvOpenhomeOrgPlaylistManager1C(CpProxyAvOpenhomeOrgPlaylistManager1C& aProxy, TUint& aNewTrackId);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncInsertAvOpenhomeOrgPlaylistManager1C() {};
private:
    CpProxyAvOpenhomeOrgPlaylistManager1C& iService;
    TUint& iNewTrackId;
};

SyncInsertAvOpenhomeOrgPlaylistManager1C::SyncInsertAvOpenhomeOrgPlaylistManager1C(CpProxyAvOpenhomeOrgPlaylistManager1C& aProxy, TUint& aNewTrackId)
    : iService(aProxy)
    , iNewTrackId(aNewTrackId)
{
}

void SyncInsertAvOpenhomeOrgPlaylistManager1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndInsert(aAsync, iNewTrackId);
}


class SyncDeleteIdAvOpenhomeOrgPlaylistManager1C : public SyncProxyAction
{
public:
    SyncDeleteIdAvOpenhomeOrgPlaylistManager1C(CpProxyAvOpenhomeOrgPlaylistManager1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncDeleteIdAvOpenhomeOrgPlaylistManager1C() {};
private:
    CpProxyAvOpenhomeOrgPlaylistManager1C& iService;
};

SyncDeleteIdAvOpenhomeOrgPlaylistManager1C::SyncDeleteIdAvOpenhomeOrgPlaylistManager1C(CpProxyAvOpenhomeOrgPlaylistManager1C& aProxy)
    : iService(aProxy)
{
}

void SyncDeleteIdAvOpenhomeOrgPlaylistManager1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndDeleteId(aAsync);
}


class SyncDeleteAllAvOpenhomeOrgPlaylistManager1C : public SyncProxyAction
{
public:
    SyncDeleteAllAvOpenhomeOrgPlaylistManager1C(CpProxyAvOpenhomeOrgPlaylistManager1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncDeleteAllAvOpenhomeOrgPlaylistManager1C() {};
private:
    CpProxyAvOpenhomeOrgPlaylistManager1C& iService;
};

SyncDeleteAllAvOpenhomeOrgPlaylistManager1C::SyncDeleteAllAvOpenhomeOrgPlaylistManager1C(CpProxyAvOpenhomeOrgPlaylistManager1C& aProxy)
    : iService(aProxy)
{
}

void SyncDeleteAllAvOpenhomeOrgPlaylistManager1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndDeleteAll(aAsync);
}

CpProxyAvOpenhomeOrgPlaylistManager1C::CpProxyAvOpenhomeOrgPlaylistManager1C(CpDeviceC aDevice)
    : CpProxyC("av-openhome-org", "PlaylistManager", 1, *reinterpret_cast<CpiDevice*>(aDevice))
    , iLock("MPCS")
{
    OpenHome::Net::Parameter* param;

    iActionMetadata = new Action("Metadata");
    param = new OpenHome::Net::ParameterString("Metadata");
    iActionMetadata->AddOutputParameter(param);

    iActionImagesXml = new Action("ImagesXml");
    param = new OpenHome::Net::ParameterString("ImagesXml");
    iActionImagesXml->AddOutputParameter(param);

    iActionPlaylistReadArray = new Action("PlaylistReadArray");
    param = new OpenHome::Net::ParameterUint("Id");
    iActionPlaylistReadArray->AddInputParameter(param);
    param = new OpenHome::Net::ParameterBinary("Array");
    iActionPlaylistReadArray->AddOutputParameter(param);

    iActionPlaylistReadList = new Action("PlaylistReadList");
    param = new OpenHome::Net::ParameterString("IdList");
    iActionPlaylistReadList->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("PlaylistList");
    iActionPlaylistReadList->AddOutputParameter(param);

    iActionPlaylistRead = new Action("PlaylistRead");
    param = new OpenHome::Net::ParameterUint("Id");
    iActionPlaylistRead->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Name");
    iActionPlaylistRead->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("Description");
    iActionPlaylistRead->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("ImageId");
    iActionPlaylistRead->AddOutputParameter(param);

    iActionPlaylistSetName = new Action("PlaylistSetName");
    param = new OpenHome::Net::ParameterUint("Id");
    iActionPlaylistSetName->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Name");
    iActionPlaylistSetName->AddInputParameter(param);

    iActionPlaylistSetDescription = new Action("PlaylistSetDescription");
    param = new OpenHome::Net::ParameterUint("Id");
    iActionPlaylistSetDescription->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Description");
    iActionPlaylistSetDescription->AddInputParameter(param);

    iActionPlaylistSetImageId = new Action("PlaylistSetImageId");
    param = new OpenHome::Net::ParameterUint("Id");
    iActionPlaylistSetImageId->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("ImageId");
    iActionPlaylistSetImageId->AddInputParameter(param);

    iActionPlaylistInsert = new Action("PlaylistInsert");
    param = new OpenHome::Net::ParameterUint("AfterId");
    iActionPlaylistInsert->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Name");
    iActionPlaylistInsert->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Description");
    iActionPlaylistInsert->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("ImageId");
    iActionPlaylistInsert->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("NewId");
    iActionPlaylistInsert->AddOutputParameter(param);

    iActionPlaylistDeleteId = new Action("PlaylistDeleteId");
    param = new OpenHome::Net::ParameterUint("Value");
    iActionPlaylistDeleteId->AddInputParameter(param);

    iActionPlaylistMove = new Action("PlaylistMove");
    param = new OpenHome::Net::ParameterUint("Id");
    iActionPlaylistMove->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("AfterId");
    iActionPlaylistMove->AddInputParameter(param);

    iActionPlaylistsMax = new Action("PlaylistsMax");
    param = new OpenHome::Net::ParameterUint("Value");
    iActionPlaylistsMax->AddOutputParameter(param);

    iActionTracksMax = new Action("TracksMax");
    param = new OpenHome::Net::ParameterUint("Value");
    iActionTracksMax->AddOutputParameter(param);

    iActionPlaylistArrays = new Action("PlaylistArrays");
    param = new OpenHome::Net::ParameterUint("Token");
    iActionPlaylistArrays->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterBinary("IdArray");
    iActionPlaylistArrays->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterBinary("TokenArray");
    iActionPlaylistArrays->AddOutputParameter(param);

    iActionPlaylistArraysChanged = new Action("PlaylistArraysChanged");
    param = new OpenHome::Net::ParameterUint("Token");
    iActionPlaylistArraysChanged->AddInputParameter(param);
    param = new OpenHome::Net::ParameterBool("Value");
    iActionPlaylistArraysChanged->AddOutputParameter(param);

    iActionRead = new Action("Read");
    param = new OpenHome::Net::ParameterUint("Id");
    iActionRead->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("TrackId");
    iActionRead->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Metadata");
    iActionRead->AddOutputParameter(param);

    iActionReadList = new Action("ReadList");
    param = new OpenHome::Net::ParameterUint("Id");
    iActionReadList->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("TrackIdList");
    iActionReadList->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("TrackList");
    iActionReadList->AddOutputParameter(param);

    iActionInsert = new Action("Insert");
    param = new OpenHome::Net::ParameterUint("Id");
    iActionInsert->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("AfterTrackId");
    iActionInsert->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Metadata");
    iActionInsert->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("NewTrackId");
    iActionInsert->AddOutputParameter(param);

    iActionDeleteId = new Action("DeleteId");
    param = new OpenHome::Net::ParameterUint("Id");
    iActionDeleteId->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("TrackId");
    iActionDeleteId->AddInputParameter(param);

    iActionDeleteAll = new Action("DeleteAll");
    param = new OpenHome::Net::ParameterUint("Id");
    iActionDeleteAll->AddInputParameter(param);

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgPlaylistManager1C::MetadataPropertyChanged);
    iMetadata = new PropertyString(reinterpret_cast<CpiDevice*>(aDevice)->GetCpStack().Env(), "Metadata", functor);
    AddProperty(iMetadata);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgPlaylistManager1C::ImagesXmlPropertyChanged);
    iImagesXml = new PropertyString(reinterpret_cast<CpiDevice*>(aDevice)->GetCpStack().Env(), "ImagesXml", functor);
    AddProperty(iImagesXml);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgPlaylistManager1C::IdArrayPropertyChanged);
    iIdArray = new PropertyBinary(reinterpret_cast<CpiDevice*>(aDevice)->GetCpStack().Env(), "IdArray", functor);
    AddProperty(iIdArray);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgPlaylistManager1C::TokenArrayPropertyChanged);
    iTokenArray = new PropertyBinary(reinterpret_cast<CpiDevice*>(aDevice)->GetCpStack().Env(), "TokenArray", functor);
    AddProperty(iTokenArray);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgPlaylistManager1C::PlaylistsMaxPropertyChanged);
    iPlaylistsMax = new PropertyUint(reinterpret_cast<CpiDevice*>(aDevice)->GetCpStack().Env(), "PlaylistsMax", functor);
    AddProperty(iPlaylistsMax);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgPlaylistManager1C::TracksMaxPropertyChanged);
    iTracksMax = new PropertyUint(reinterpret_cast<CpiDevice*>(aDevice)->GetCpStack().Env(), "TracksMax", functor);
    AddProperty(iTracksMax);
}

CpProxyAvOpenhomeOrgPlaylistManager1C::~CpProxyAvOpenhomeOrgPlaylistManager1C()
{
    DestroyService();
    delete iActionMetadata;
    delete iActionImagesXml;
    delete iActionPlaylistReadArray;
    delete iActionPlaylistReadList;
    delete iActionPlaylistRead;
    delete iActionPlaylistSetName;
    delete iActionPlaylistSetDescription;
    delete iActionPlaylistSetImageId;
    delete iActionPlaylistInsert;
    delete iActionPlaylistDeleteId;
    delete iActionPlaylistMove;
    delete iActionPlaylistsMax;
    delete iActionTracksMax;
    delete iActionPlaylistArrays;
    delete iActionPlaylistArraysChanged;
    delete iActionRead;
    delete iActionReadList;
    delete iActionInsert;
    delete iActionDeleteId;
    delete iActionDeleteAll;
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::SyncMetadata(Brh& aMetadata)
{
    SyncMetadataAvOpenhomeOrgPlaylistManager1C sync(*this, aMetadata);
    BeginMetadata(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::BeginMetadata(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionMetadata, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionMetadata->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::EndMetadata(IAsync& aAsync, Brh& aMetadata)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Metadata"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aMetadata);
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::SyncImagesXml(Brh& aImagesXml)
{
    SyncImagesXmlAvOpenhomeOrgPlaylistManager1C sync(*this, aImagesXml);
    BeginImagesXml(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::BeginImagesXml(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionImagesXml, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionImagesXml->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::EndImagesXml(IAsync& aAsync, Brh& aImagesXml)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("ImagesXml"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aImagesXml);
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::SyncPlaylistReadArray(TUint aId, Brh& aArray)
{
    SyncPlaylistReadArrayAvOpenhomeOrgPlaylistManager1C sync(*this, aArray);
    BeginPlaylistReadArray(aId, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::BeginPlaylistReadArray(TUint aId, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionPlaylistReadArray, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionPlaylistReadArray->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aId));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionPlaylistReadArray->OutputParameters();
    invocation->AddOutput(new ArgumentBinary(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::EndPlaylistReadArray(IAsync& aAsync, Brh& aArray)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("PlaylistReadArray"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    ((ArgumentBinary*)invocation.OutputArguments()[index++])->TransferTo(aArray);
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::SyncPlaylistReadList(const Brx& aIdList, Brh& aPlaylistList)
{
    SyncPlaylistReadListAvOpenhomeOrgPlaylistManager1C sync(*this, aPlaylistList);
    BeginPlaylistReadList(aIdList, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::BeginPlaylistReadList(const Brx& aIdList, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionPlaylistReadList, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionPlaylistReadList->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aIdList));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionPlaylistReadList->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::EndPlaylistReadList(IAsync& aAsync, Brh& aPlaylistList)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("PlaylistReadList"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aPlaylistList);
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::SyncPlaylistRead(TUint aId, Brh& aName, Brh& aDescription, TUint& aImageId)
{
    SyncPlaylistReadAvOpenhomeOrgPlaylistManager1C sync(*this, aName, aDescription, aImageId);
    BeginPlaylistRead(aId, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::BeginPlaylistRead(TUint aId, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionPlaylistRead, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionPlaylistRead->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aId));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionPlaylistRead->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::EndPlaylistRead(IAsync& aAsync, Brh& aName, Brh& aDescription, TUint& aImageId)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("PlaylistRead"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aName);
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aDescription);
    aImageId = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::SyncPlaylistSetName(TUint aId, const Brx& aName)
{
    SyncPlaylistSetNameAvOpenhomeOrgPlaylistManager1C sync(*this);
    BeginPlaylistSetName(aId, aName, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::BeginPlaylistSetName(TUint aId, const Brx& aName, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionPlaylistSetName, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionPlaylistSetName->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aId));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aName));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::EndPlaylistSetName(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("PlaylistSetName"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::SyncPlaylistSetDescription(TUint aId, const Brx& aDescription)
{
    SyncPlaylistSetDescriptionAvOpenhomeOrgPlaylistManager1C sync(*this);
    BeginPlaylistSetDescription(aId, aDescription, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::BeginPlaylistSetDescription(TUint aId, const Brx& aDescription, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionPlaylistSetDescription, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionPlaylistSetDescription->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aId));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aDescription));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::EndPlaylistSetDescription(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("PlaylistSetDescription"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::SyncPlaylistSetImageId(TUint aId, TUint aImageId)
{
    SyncPlaylistSetImageIdAvOpenhomeOrgPlaylistManager1C sync(*this);
    BeginPlaylistSetImageId(aId, aImageId, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::BeginPlaylistSetImageId(TUint aId, TUint aImageId, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionPlaylistSetImageId, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionPlaylistSetImageId->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aId));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aImageId));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::EndPlaylistSetImageId(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("PlaylistSetImageId"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::SyncPlaylistInsert(TUint aAfterId, const Brx& aName, const Brx& aDescription, TUint aImageId, TUint& aNewId)
{
    SyncPlaylistInsertAvOpenhomeOrgPlaylistManager1C sync(*this, aNewId);
    BeginPlaylistInsert(aAfterId, aName, aDescription, aImageId, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::BeginPlaylistInsert(TUint aAfterId, const Brx& aName, const Brx& aDescription, TUint aImageId, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionPlaylistInsert, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionPlaylistInsert->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aAfterId));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aName));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aDescription));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aImageId));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionPlaylistInsert->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::EndPlaylistInsert(IAsync& aAsync, TUint& aNewId)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("PlaylistInsert"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aNewId = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::SyncPlaylistDeleteId(TUint aValue)
{
    SyncPlaylistDeleteIdAvOpenhomeOrgPlaylistManager1C sync(*this);
    BeginPlaylistDeleteId(aValue, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::BeginPlaylistDeleteId(TUint aValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionPlaylistDeleteId, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionPlaylistDeleteId->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aValue));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::EndPlaylistDeleteId(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("PlaylistDeleteId"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::SyncPlaylistMove(TUint aId, TUint aAfterId)
{
    SyncPlaylistMoveAvOpenhomeOrgPlaylistManager1C sync(*this);
    BeginPlaylistMove(aId, aAfterId, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::BeginPlaylistMove(TUint aId, TUint aAfterId, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionPlaylistMove, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionPlaylistMove->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aId));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aAfterId));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::EndPlaylistMove(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("PlaylistMove"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::SyncPlaylistsMax(TUint& aValue)
{
    SyncPlaylistsMaxAvOpenhomeOrgPlaylistManager1C sync(*this, aValue);
    BeginPlaylistsMax(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::BeginPlaylistsMax(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionPlaylistsMax, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionPlaylistsMax->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::EndPlaylistsMax(IAsync& aAsync, TUint& aValue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("PlaylistsMax"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aValue = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::SyncTracksMax(TUint& aValue)
{
    SyncTracksMaxAvOpenhomeOrgPlaylistManager1C sync(*this, aValue);
    BeginTracksMax(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::BeginTracksMax(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionTracksMax, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionTracksMax->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::EndTracksMax(IAsync& aAsync, TUint& aValue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("TracksMax"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aValue = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::SyncPlaylistArrays(TUint& aToken, Brh& aIdArray, Brh& aTokenArray)
{
    SyncPlaylistArraysAvOpenhomeOrgPlaylistManager1C sync(*this, aToken, aIdArray, aTokenArray);
    BeginPlaylistArrays(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::BeginPlaylistArrays(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionPlaylistArrays, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionPlaylistArrays->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentBinary(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentBinary(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::EndPlaylistArrays(IAsync& aAsync, TUint& aToken, Brh& aIdArray, Brh& aTokenArray)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("PlaylistArrays"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aToken = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    ((ArgumentBinary*)invocation.OutputArguments()[index++])->TransferTo(aIdArray);
    ((ArgumentBinary*)invocation.OutputArguments()[index++])->TransferTo(aTokenArray);
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::SyncPlaylistArraysChanged(TUint aToken, TBool& aValue)
{
    SyncPlaylistArraysChangedAvOpenhomeOrgPlaylistManager1C sync(*this, aValue);
    BeginPlaylistArraysChanged(aToken, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::BeginPlaylistArraysChanged(TUint aToken, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionPlaylistArraysChanged, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionPlaylistArraysChanged->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aToken));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionPlaylistArraysChanged->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::EndPlaylistArraysChanged(IAsync& aAsync, TBool& aValue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("PlaylistArraysChanged"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aValue = ((ArgumentBool*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::SyncRead(TUint aId, TUint aTrackId, Brh& aMetadata)
{
    SyncReadAvOpenhomeOrgPlaylistManager1C sync(*this, aMetadata);
    BeginRead(aId, aTrackId, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::BeginRead(TUint aId, TUint aTrackId, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionRead, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionRead->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aId));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aTrackId));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionRead->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::EndRead(IAsync& aAsync, Brh& aMetadata)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Read"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aMetadata);
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::SyncReadList(TUint aId, const Brx& aTrackIdList, Brh& aTrackList)
{
    SyncReadListAvOpenhomeOrgPlaylistManager1C sync(*this, aTrackList);
    BeginReadList(aId, aTrackIdList, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::BeginReadList(TUint aId, const Brx& aTrackIdList, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionReadList, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionReadList->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aId));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aTrackIdList));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionReadList->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::EndReadList(IAsync& aAsync, Brh& aTrackList)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("ReadList"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aTrackList);
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::SyncInsert(TUint aId, TUint aAfterTrackId, const Brx& aMetadata, TUint& aNewTrackId)
{
    SyncInsertAvOpenhomeOrgPlaylistManager1C sync(*this, aNewTrackId);
    BeginInsert(aId, aAfterTrackId, aMetadata, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::BeginInsert(TUint aId, TUint aAfterTrackId, const Brx& aMetadata, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionInsert, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionInsert->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aId));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aAfterTrackId));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aMetadata));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionInsert->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::EndInsert(IAsync& aAsync, TUint& aNewTrackId)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Insert"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aNewTrackId = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::SyncDeleteId(TUint aId, TUint aTrackId)
{
    SyncDeleteIdAvOpenhomeOrgPlaylistManager1C sync(*this);
    BeginDeleteId(aId, aTrackId, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::BeginDeleteId(TUint aId, TUint aTrackId, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionDeleteId, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionDeleteId->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aId));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aTrackId));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::EndDeleteId(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("DeleteId"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::SyncDeleteAll(TUint aId)
{
    SyncDeleteAllAvOpenhomeOrgPlaylistManager1C sync(*this);
    BeginDeleteAll(aId, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::BeginDeleteAll(TUint aId, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionDeleteAll, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionDeleteAll->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aId));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::EndDeleteAll(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("DeleteAll"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::SetPropertyMetadataChanged(Functor& aFunctor)
{
    iLock.Wait();
    iMetadataChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::SetPropertyImagesXmlChanged(Functor& aFunctor)
{
    iLock.Wait();
    iImagesXmlChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::SetPropertyIdArrayChanged(Functor& aFunctor)
{
    iLock.Wait();
    iIdArrayChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::SetPropertyTokenArrayChanged(Functor& aFunctor)
{
    iLock.Wait();
    iTokenArrayChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::SetPropertyPlaylistsMaxChanged(Functor& aFunctor)
{
    iLock.Wait();
    iPlaylistsMaxChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::SetPropertyTracksMaxChanged(Functor& aFunctor)
{
    iLock.Wait();
    iTracksMaxChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::PropertyMetadata(Brhz& aMetadata) const
{
    AutoMutex a(GetPropertyReadLock());
    ASSERT(IsSubscribed());
    aMetadata.Set(iMetadata->Value());
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::PropertyImagesXml(Brhz& aImagesXml) const
{
    AutoMutex a(GetPropertyReadLock());
    ASSERT(IsSubscribed());
    aImagesXml.Set(iImagesXml->Value());
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::PropertyIdArray(Brh& aIdArray) const
{
    AutoMutex a(GetPropertyReadLock());
    ASSERT(IsSubscribed());
    aIdArray.Set(iIdArray->Value());
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::PropertyTokenArray(Brh& aTokenArray) const
{
    AutoMutex a(GetPropertyReadLock());
    ASSERT(IsSubscribed());
    aTokenArray.Set(iTokenArray->Value());
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::PropertyPlaylistsMax(TUint& aPlaylistsMax) const
{
    AutoMutex a(GetPropertyReadLock());
    ASSERT(IsSubscribed());
    aPlaylistsMax = iPlaylistsMax->Value();
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::PropertyTracksMax(TUint& aTracksMax) const
{
    AutoMutex a(GetPropertyReadLock());
    ASSERT(IsSubscribed());
    aTracksMax = iTracksMax->Value();
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::MetadataPropertyChanged()
{
    ReportEvent(iMetadataChanged);
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::ImagesXmlPropertyChanged()
{
    ReportEvent(iImagesXmlChanged);
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::IdArrayPropertyChanged()
{
    ReportEvent(iIdArrayChanged);
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::TokenArrayPropertyChanged()
{
    ReportEvent(iTokenArrayChanged);
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::PlaylistsMaxPropertyChanged()
{
    ReportEvent(iPlaylistsMaxChanged);
}

void CpProxyAvOpenhomeOrgPlaylistManager1C::TracksMaxPropertyChanged()
{
    ReportEvent(iTracksMaxChanged);
}


THandle STDCALL CpProxyAvOpenhomeOrgPlaylistManager1Create(CpDeviceC aDevice)
{
    return new CpProxyAvOpenhomeOrgPlaylistManager1C(aDevice);
}

void STDCALL CpProxyAvOpenhomeOrgPlaylistManager1Destroy(THandle aHandle)
{
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    delete proxyC;
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylistManager1SyncMetadata(THandle aHandle, char** aMetadata)
{
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aMetadata;
    int32_t err = 0;
    try {
        proxyC->SyncMetadata(buf_aMetadata);
        *aMetadata = buf_aMetadata.Extract();
    }
    catch (ProxyError& ) {
        err = -1;
        *aMetadata = NULL;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgPlaylistManager1BeginMetadata(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginMetadata(functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylistManager1EndMetadata(THandle aHandle, OhNetHandleAsync aAsync, char** aMetadata)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aMetadata;
    *aMetadata = NULL;
    try {
        proxyC->EndMetadata(*async, buf_aMetadata);
        *aMetadata = buf_aMetadata.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylistManager1SyncImagesXml(THandle aHandle, char** aImagesXml)
{
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aImagesXml;
    int32_t err = 0;
    try {
        proxyC->SyncImagesXml(buf_aImagesXml);
        *aImagesXml = buf_aImagesXml.Extract();
    }
    catch (ProxyError& ) {
        err = -1;
        *aImagesXml = NULL;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgPlaylistManager1BeginImagesXml(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginImagesXml(functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylistManager1EndImagesXml(THandle aHandle, OhNetHandleAsync aAsync, char** aImagesXml)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aImagesXml;
    *aImagesXml = NULL;
    try {
        proxyC->EndImagesXml(*async, buf_aImagesXml);
        *aImagesXml = buf_aImagesXml.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylistManager1SyncPlaylistReadArray(THandle aHandle, uint32_t aId, char** aArray, uint32_t* aArrayLen)
{
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aArray;
    int32_t err = 0;
    try {
        proxyC->SyncPlaylistReadArray(aId, buf_aArray);
        *aArrayLen = buf_aArray.Bytes();
        *aArray = buf_aArray.Extract();
    }
    catch (ProxyError& ) {
        err = -1;
        *aArrayLen = 0;
        *aArray = NULL;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgPlaylistManager1BeginPlaylistReadArray(THandle aHandle, uint32_t aId, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginPlaylistReadArray(aId, functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylistManager1EndPlaylistReadArray(THandle aHandle, OhNetHandleAsync aAsync, char** aArray, uint32_t* aArrayLen)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aArray;
    *aArray = NULL;
    *aArrayLen = 0;
    try {
        proxyC->EndPlaylistReadArray(*async, buf_aArray);
        *aArrayLen = buf_aArray.Bytes();
        *aArray = buf_aArray.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylistManager1SyncPlaylistReadList(THandle aHandle, const char* aIdList, char** aPlaylistList)
{
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aIdList(aIdList);
    Brh buf_aPlaylistList;
    int32_t err = 0;
    try {
        proxyC->SyncPlaylistReadList(buf_aIdList, buf_aPlaylistList);
        *aPlaylistList = buf_aPlaylistList.Extract();
    }
    catch (ProxyError& ) {
        err = -1;
        *aPlaylistList = NULL;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgPlaylistManager1BeginPlaylistReadList(THandle aHandle, const char* aIdList, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aIdList(aIdList);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginPlaylistReadList(buf_aIdList, functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylistManager1EndPlaylistReadList(THandle aHandle, OhNetHandleAsync aAsync, char** aPlaylistList)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aPlaylistList;
    *aPlaylistList = NULL;
    try {
        proxyC->EndPlaylistReadList(*async, buf_aPlaylistList);
        *aPlaylistList = buf_aPlaylistList.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylistManager1SyncPlaylistRead(THandle aHandle, uint32_t aId, char** aName, char** aDescription, uint32_t* aImageId)
{
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aName;
    Brh buf_aDescription;
    int32_t err = 0;
    try {
        proxyC->SyncPlaylistRead(aId, buf_aName, buf_aDescription, *aImageId);
        *aName = buf_aName.Extract();
        *aDescription = buf_aDescription.Extract();
    }
    catch (ProxyError& ) {
        err = -1;
        *aName = NULL;
        *aDescription = NULL;
        *aImageId = 0;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgPlaylistManager1BeginPlaylistRead(THandle aHandle, uint32_t aId, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginPlaylistRead(aId, functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylistManager1EndPlaylistRead(THandle aHandle, OhNetHandleAsync aAsync, char** aName, char** aDescription, uint32_t* aImageId)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aName;
    *aName = NULL;
    Brh buf_aDescription;
    *aDescription = NULL;
    try {
        proxyC->EndPlaylistRead(*async, buf_aName, buf_aDescription, *aImageId);
        *aName = buf_aName.Extract();
        *aDescription = buf_aDescription.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylistManager1SyncPlaylistSetName(THandle aHandle, uint32_t aId, const char* aName)
{
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aName(aName);
    int32_t err = 0;
    try {
        proxyC->SyncPlaylistSetName(aId, buf_aName);
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgPlaylistManager1BeginPlaylistSetName(THandle aHandle, uint32_t aId, const char* aName, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aName(aName);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginPlaylistSetName(aId, buf_aName, functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylistManager1EndPlaylistSetName(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndPlaylistSetName(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylistManager1SyncPlaylistSetDescription(THandle aHandle, uint32_t aId, const char* aDescription)
{
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aDescription(aDescription);
    int32_t err = 0;
    try {
        proxyC->SyncPlaylistSetDescription(aId, buf_aDescription);
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgPlaylistManager1BeginPlaylistSetDescription(THandle aHandle, uint32_t aId, const char* aDescription, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aDescription(aDescription);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginPlaylistSetDescription(aId, buf_aDescription, functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylistManager1EndPlaylistSetDescription(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndPlaylistSetDescription(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylistManager1SyncPlaylistSetImageId(THandle aHandle, uint32_t aId, uint32_t aImageId)
{
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncPlaylistSetImageId(aId, aImageId);
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgPlaylistManager1BeginPlaylistSetImageId(THandle aHandle, uint32_t aId, uint32_t aImageId, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginPlaylistSetImageId(aId, aImageId, functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylistManager1EndPlaylistSetImageId(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndPlaylistSetImageId(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylistManager1SyncPlaylistInsert(THandle aHandle, uint32_t aAfterId, const char* aName, const char* aDescription, uint32_t aImageId, uint32_t* aNewId)
{
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aName(aName);
    Brh buf_aDescription(aDescription);
    int32_t err = 0;
    try {
        proxyC->SyncPlaylistInsert(aAfterId, buf_aName, buf_aDescription, aImageId, *aNewId);
    }
    catch (ProxyError& ) {
        err = -1;
        *aNewId = 0;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgPlaylistManager1BeginPlaylistInsert(THandle aHandle, uint32_t aAfterId, const char* aName, const char* aDescription, uint32_t aImageId, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aName(aName);
    Brh buf_aDescription(aDescription);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginPlaylistInsert(aAfterId, buf_aName, buf_aDescription, aImageId, functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylistManager1EndPlaylistInsert(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aNewId)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndPlaylistInsert(*async, *aNewId);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylistManager1SyncPlaylistDeleteId(THandle aHandle, uint32_t aValue)
{
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncPlaylistDeleteId(aValue);
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgPlaylistManager1BeginPlaylistDeleteId(THandle aHandle, uint32_t aValue, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginPlaylistDeleteId(aValue, functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylistManager1EndPlaylistDeleteId(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndPlaylistDeleteId(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylistManager1SyncPlaylistMove(THandle aHandle, uint32_t aId, uint32_t aAfterId)
{
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncPlaylistMove(aId, aAfterId);
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgPlaylistManager1BeginPlaylistMove(THandle aHandle, uint32_t aId, uint32_t aAfterId, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginPlaylistMove(aId, aAfterId, functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylistManager1EndPlaylistMove(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndPlaylistMove(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylistManager1SyncPlaylistsMax(THandle aHandle, uint32_t* aValue)
{
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncPlaylistsMax(*aValue);
    }
    catch (ProxyError& ) {
        err = -1;
        *aValue = 0;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgPlaylistManager1BeginPlaylistsMax(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginPlaylistsMax(functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylistManager1EndPlaylistsMax(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aValue)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndPlaylistsMax(*async, *aValue);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylistManager1SyncTracksMax(THandle aHandle, uint32_t* aValue)
{
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncTracksMax(*aValue);
    }
    catch (ProxyError& ) {
        err = -1;
        *aValue = 0;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgPlaylistManager1BeginTracksMax(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginTracksMax(functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylistManager1EndTracksMax(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aValue)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndTracksMax(*async, *aValue);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylistManager1SyncPlaylistArrays(THandle aHandle, uint32_t* aToken, char** aIdArray, uint32_t* aIdArrayLen, char** aTokenArray, uint32_t* aTokenArrayLen)
{
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aIdArray;
    Brh buf_aTokenArray;
    int32_t err = 0;
    try {
        proxyC->SyncPlaylistArrays(*aToken, buf_aIdArray, buf_aTokenArray);
        *aIdArrayLen = buf_aIdArray.Bytes();
        *aIdArray = buf_aIdArray.Extract();
        *aTokenArrayLen = buf_aTokenArray.Bytes();
        *aTokenArray = buf_aTokenArray.Extract();
    }
    catch (ProxyError& ) {
        err = -1;
        *aToken = 0;
        *aIdArrayLen = 0;
        *aIdArray = NULL;
        *aTokenArrayLen = 0;
        *aTokenArray = NULL;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgPlaylistManager1BeginPlaylistArrays(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginPlaylistArrays(functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylistManager1EndPlaylistArrays(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aToken, char** aIdArray, uint32_t* aIdArrayLen, char** aTokenArray, uint32_t* aTokenArrayLen)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aIdArray;
    *aIdArray = NULL;
    *aIdArrayLen = 0;
    Brh buf_aTokenArray;
    *aTokenArray = NULL;
    *aTokenArrayLen = 0;
    try {
        proxyC->EndPlaylistArrays(*async, *aToken, buf_aIdArray, buf_aTokenArray);
        *aIdArrayLen = buf_aIdArray.Bytes();
        *aIdArray = buf_aIdArray.Extract();
        *aTokenArrayLen = buf_aTokenArray.Bytes();
        *aTokenArray = buf_aTokenArray.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylistManager1SyncPlaylistArraysChanged(THandle aHandle, uint32_t aToken, uint32_t* aValue)
{
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    TBool Value;
    int32_t err = 0;
    try {
        proxyC->SyncPlaylistArraysChanged(aToken, Value);
        *aValue = Value? 1 : 0;
    }
    catch (ProxyError& ) {
        err = -1;
        *aValue = false;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgPlaylistManager1BeginPlaylistArraysChanged(THandle aHandle, uint32_t aToken, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginPlaylistArraysChanged(aToken, functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylistManager1EndPlaylistArraysChanged(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aValue)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    TBool Value;
    try {
        proxyC->EndPlaylistArraysChanged(*async, Value);
        *aValue = Value? 1 : 0;
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylistManager1SyncRead(THandle aHandle, uint32_t aId, uint32_t aTrackId, char** aMetadata)
{
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aMetadata;
    int32_t err = 0;
    try {
        proxyC->SyncRead(aId, aTrackId, buf_aMetadata);
        *aMetadata = buf_aMetadata.Extract();
    }
    catch (ProxyError& ) {
        err = -1;
        *aMetadata = NULL;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgPlaylistManager1BeginRead(THandle aHandle, uint32_t aId, uint32_t aTrackId, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginRead(aId, aTrackId, functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylistManager1EndRead(THandle aHandle, OhNetHandleAsync aAsync, char** aMetadata)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aMetadata;
    *aMetadata = NULL;
    try {
        proxyC->EndRead(*async, buf_aMetadata);
        *aMetadata = buf_aMetadata.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylistManager1SyncReadList(THandle aHandle, uint32_t aId, const char* aTrackIdList, char** aTrackList)
{
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aTrackIdList(aTrackIdList);
    Brh buf_aTrackList;
    int32_t err = 0;
    try {
        proxyC->SyncReadList(aId, buf_aTrackIdList, buf_aTrackList);
        *aTrackList = buf_aTrackList.Extract();
    }
    catch (ProxyError& ) {
        err = -1;
        *aTrackList = NULL;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgPlaylistManager1BeginReadList(THandle aHandle, uint32_t aId, const char* aTrackIdList, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aTrackIdList(aTrackIdList);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginReadList(aId, buf_aTrackIdList, functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylistManager1EndReadList(THandle aHandle, OhNetHandleAsync aAsync, char** aTrackList)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aTrackList;
    *aTrackList = NULL;
    try {
        proxyC->EndReadList(*async, buf_aTrackList);
        *aTrackList = buf_aTrackList.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylistManager1SyncInsert(THandle aHandle, uint32_t aId, uint32_t aAfterTrackId, const char* aMetadata, uint32_t* aNewTrackId)
{
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aMetadata(aMetadata);
    int32_t err = 0;
    try {
        proxyC->SyncInsert(aId, aAfterTrackId, buf_aMetadata, *aNewTrackId);
    }
    catch (ProxyError& ) {
        err = -1;
        *aNewTrackId = 0;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgPlaylistManager1BeginInsert(THandle aHandle, uint32_t aId, uint32_t aAfterTrackId, const char* aMetadata, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aMetadata(aMetadata);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginInsert(aId, aAfterTrackId, buf_aMetadata, functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylistManager1EndInsert(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aNewTrackId)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndInsert(*async, *aNewTrackId);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylistManager1SyncDeleteId(THandle aHandle, uint32_t aId, uint32_t aTrackId)
{
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncDeleteId(aId, aTrackId);
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgPlaylistManager1BeginDeleteId(THandle aHandle, uint32_t aId, uint32_t aTrackId, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginDeleteId(aId, aTrackId, functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylistManager1EndDeleteId(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndDeleteId(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylistManager1SyncDeleteAll(THandle aHandle, uint32_t aId)
{
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncDeleteAll(aId);
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgPlaylistManager1BeginDeleteAll(THandle aHandle, uint32_t aId, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginDeleteAll(aId, functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgPlaylistManager1EndDeleteAll(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndDeleteAll(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgPlaylistManager1SetPropertyMetadataChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyMetadataChanged(functor);
}

void STDCALL CpProxyAvOpenhomeOrgPlaylistManager1SetPropertyImagesXmlChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyImagesXmlChanged(functor);
}

void STDCALL CpProxyAvOpenhomeOrgPlaylistManager1SetPropertyIdArrayChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyIdArrayChanged(functor);
}

void STDCALL CpProxyAvOpenhomeOrgPlaylistManager1SetPropertyTokenArrayChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyTokenArrayChanged(functor);
}

void STDCALL CpProxyAvOpenhomeOrgPlaylistManager1SetPropertyPlaylistsMaxChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyPlaylistsMaxChanged(functor);
}

void STDCALL CpProxyAvOpenhomeOrgPlaylistManager1SetPropertyTracksMaxChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyTracksMaxChanged(functor);
}

void STDCALL CpProxyAvOpenhomeOrgPlaylistManager1PropertyMetadata(THandle aHandle, char** aMetadata)
{
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aMetadata;
    proxyC->PropertyMetadata(buf_aMetadata);
    *aMetadata = buf_aMetadata.Transfer();
}

void STDCALL CpProxyAvOpenhomeOrgPlaylistManager1PropertyImagesXml(THandle aHandle, char** aImagesXml)
{
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aImagesXml;
    proxyC->PropertyImagesXml(buf_aImagesXml);
    *aImagesXml = buf_aImagesXml.Transfer();
}

void STDCALL CpProxyAvOpenhomeOrgPlaylistManager1PropertyIdArray(THandle aHandle, char** aIdArray, uint32_t* aLen)
{
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aIdArray;
    proxyC->PropertyIdArray(buf_aIdArray);
    *aLen = buf_aIdArray.Bytes();
    *aIdArray = buf_aIdArray.Extract();
}

void STDCALL CpProxyAvOpenhomeOrgPlaylistManager1PropertyTokenArray(THandle aHandle, char** aTokenArray, uint32_t* aLen)
{
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aTokenArray;
    proxyC->PropertyTokenArray(buf_aTokenArray);
    *aLen = buf_aTokenArray.Bytes();
    *aTokenArray = buf_aTokenArray.Extract();
}

void STDCALL CpProxyAvOpenhomeOrgPlaylistManager1PropertyPlaylistsMax(THandle aHandle, uint32_t* aPlaylistsMax)
{
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyPlaylistsMax(*aPlaylistsMax);
}

void STDCALL CpProxyAvOpenhomeOrgPlaylistManager1PropertyTracksMax(THandle aHandle, uint32_t* aTracksMax)
{
    CpProxyAvOpenhomeOrgPlaylistManager1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgPlaylistManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyTracksMax(*aTracksMax);
}

