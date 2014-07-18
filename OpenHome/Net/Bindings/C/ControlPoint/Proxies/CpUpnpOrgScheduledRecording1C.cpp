#include "CpUpnpOrgScheduledRecording1.h"
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

class CpProxyUpnpOrgScheduledRecording1C : public CpProxyC
{
public:
    CpProxyUpnpOrgScheduledRecording1C(CpDeviceC aDevice);
    ~CpProxyUpnpOrgScheduledRecording1C();
    //CpProxyUpnpOrgScheduledRecording1* Proxy() { return static_cast<CpProxyUpnpOrgScheduledRecording1*>(iProxy); }

    void SyncGetSortCapabilities(Brh& aSortCaps, TUint& aSortLevelCap);
    void BeginGetSortCapabilities(FunctorAsync& aFunctor);
    void EndGetSortCapabilities(IAsync& aAsync, Brh& aSortCaps, TUint& aSortLevelCap);

    void SyncGetPropertyList(const Brx& aDataTypeID, Brh& aPropertyList);
    void BeginGetPropertyList(const Brx& aDataTypeID, FunctorAsync& aFunctor);
    void EndGetPropertyList(IAsync& aAsync, Brh& aPropertyList);

    void SyncGetAllowedValues(const Brx& aDataTypeID, const Brx& aFilter, Brh& aPropertyInfo);
    void BeginGetAllowedValues(const Brx& aDataTypeID, const Brx& aFilter, FunctorAsync& aFunctor);
    void EndGetAllowedValues(IAsync& aAsync, Brh& aPropertyInfo);

    void SyncGetStateUpdateID(TUint& aId);
    void BeginGetStateUpdateID(FunctorAsync& aFunctor);
    void EndGetStateUpdateID(IAsync& aAsync, TUint& aId);

    void SyncBrowseRecordSchedules(const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID);
    void BeginBrowseRecordSchedules(const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, FunctorAsync& aFunctor);
    void EndBrowseRecordSchedules(IAsync& aAsync, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID);

    void SyncBrowseRecordTasks(const Brx& aRecordScheduleID, const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID);
    void BeginBrowseRecordTasks(const Brx& aRecordScheduleID, const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, FunctorAsync& aFunctor);
    void EndBrowseRecordTasks(IAsync& aAsync, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID);

    void SyncCreateRecordSchedule(const Brx& aElements, Brh& aRecordScheduleID, Brh& aResult, TUint& aUpdateID);
    void BeginCreateRecordSchedule(const Brx& aElements, FunctorAsync& aFunctor);
    void EndCreateRecordSchedule(IAsync& aAsync, Brh& aRecordScheduleID, Brh& aResult, TUint& aUpdateID);

    void SyncDeleteRecordSchedule(const Brx& aRecordScheduleID);
    void BeginDeleteRecordSchedule(const Brx& aRecordScheduleID, FunctorAsync& aFunctor);
    void EndDeleteRecordSchedule(IAsync& aAsync);

    void SyncGetRecordSchedule(const Brx& aRecordScheduleID, const Brx& aFilter, Brh& aResult, TUint& aUpdateID);
    void BeginGetRecordSchedule(const Brx& aRecordScheduleID, const Brx& aFilter, FunctorAsync& aFunctor);
    void EndGetRecordSchedule(IAsync& aAsync, Brh& aResult, TUint& aUpdateID);

    void SyncEnableRecordSchedule(const Brx& aRecordScheduleID);
    void BeginEnableRecordSchedule(const Brx& aRecordScheduleID, FunctorAsync& aFunctor);
    void EndEnableRecordSchedule(IAsync& aAsync);

    void SyncDisableRecordSchedule(const Brx& aRecordScheduleID);
    void BeginDisableRecordSchedule(const Brx& aRecordScheduleID, FunctorAsync& aFunctor);
    void EndDisableRecordSchedule(IAsync& aAsync);

    void SyncDeleteRecordTask(const Brx& aRecordTaskID);
    void BeginDeleteRecordTask(const Brx& aRecordTaskID, FunctorAsync& aFunctor);
    void EndDeleteRecordTask(IAsync& aAsync);

    void SyncGetRecordTask(const Brx& aRecordTaskID, const Brx& aFilter, Brh& aResult, TUint& aUpdateID);
    void BeginGetRecordTask(const Brx& aRecordTaskID, const Brx& aFilter, FunctorAsync& aFunctor);
    void EndGetRecordTask(IAsync& aAsync, Brh& aResult, TUint& aUpdateID);

    void SyncEnableRecordTask(const Brx& aRecordTaskID);
    void BeginEnableRecordTask(const Brx& aRecordTaskID, FunctorAsync& aFunctor);
    void EndEnableRecordTask(IAsync& aAsync);

    void SyncDisableRecordTask(const Brx& aRecordTaskID);
    void BeginDisableRecordTask(const Brx& aRecordTaskID, FunctorAsync& aFunctor);
    void EndDisableRecordTask(IAsync& aAsync);

    void SyncResetRecordTask(const Brx& aRecordTaskID);
    void BeginResetRecordTask(const Brx& aRecordTaskID, FunctorAsync& aFunctor);
    void EndResetRecordTask(IAsync& aAsync);

    void SyncGetRecordScheduleConflicts(const Brx& aRecordScheduleID, Brh& aRecordScheduleConflictIDList, TUint& aUpdateID);
    void BeginGetRecordScheduleConflicts(const Brx& aRecordScheduleID, FunctorAsync& aFunctor);
    void EndGetRecordScheduleConflicts(IAsync& aAsync, Brh& aRecordScheduleConflictIDList, TUint& aUpdateID);

    void SyncGetRecordTaskConflicts(const Brx& aRecordTaskID, Brh& aRecordTaskConflictIDList, TUint& aUpdateID);
    void BeginGetRecordTaskConflicts(const Brx& aRecordTaskID, FunctorAsync& aFunctor);
    void EndGetRecordTaskConflicts(IAsync& aAsync, Brh& aRecordTaskConflictIDList, TUint& aUpdateID);

    void SetPropertyLastChangeChanged(Functor& aFunctor);

    void PropertyLastChange(Brhz& aLastChange) const;
private:
    void LastChangePropertyChanged();
private:
    Mutex iLock;
    Action* iActionGetSortCapabilities;
    Action* iActionGetPropertyList;
    Action* iActionGetAllowedValues;
    Action* iActionGetStateUpdateID;
    Action* iActionBrowseRecordSchedules;
    Action* iActionBrowseRecordTasks;
    Action* iActionCreateRecordSchedule;
    Action* iActionDeleteRecordSchedule;
    Action* iActionGetRecordSchedule;
    Action* iActionEnableRecordSchedule;
    Action* iActionDisableRecordSchedule;
    Action* iActionDeleteRecordTask;
    Action* iActionGetRecordTask;
    Action* iActionEnableRecordTask;
    Action* iActionDisableRecordTask;
    Action* iActionResetRecordTask;
    Action* iActionGetRecordScheduleConflicts;
    Action* iActionGetRecordTaskConflicts;
    PropertyString* iLastChange;
    Functor iLastChangeChanged;
};


class SyncGetSortCapabilitiesUpnpOrgScheduledRecording1C : public SyncProxyAction
{
public:
    SyncGetSortCapabilitiesUpnpOrgScheduledRecording1C(CpProxyUpnpOrgScheduledRecording1C& aProxy, Brh& aSortCaps, TUint& aSortLevelCap);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetSortCapabilitiesUpnpOrgScheduledRecording1C() {};
private:
    CpProxyUpnpOrgScheduledRecording1C& iService;
    Brh& iSortCaps;
    TUint& iSortLevelCap;
};

SyncGetSortCapabilitiesUpnpOrgScheduledRecording1C::SyncGetSortCapabilitiesUpnpOrgScheduledRecording1C(CpProxyUpnpOrgScheduledRecording1C& aProxy, Brh& aSortCaps, TUint& aSortLevelCap)
    : iService(aProxy)
    , iSortCaps(aSortCaps)
    , iSortLevelCap(aSortLevelCap)
{
}

void SyncGetSortCapabilitiesUpnpOrgScheduledRecording1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetSortCapabilities(aAsync, iSortCaps, iSortLevelCap);
}


class SyncGetPropertyListUpnpOrgScheduledRecording1C : public SyncProxyAction
{
public:
    SyncGetPropertyListUpnpOrgScheduledRecording1C(CpProxyUpnpOrgScheduledRecording1C& aProxy, Brh& aPropertyList);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetPropertyListUpnpOrgScheduledRecording1C() {};
private:
    CpProxyUpnpOrgScheduledRecording1C& iService;
    Brh& iPropertyList;
};

SyncGetPropertyListUpnpOrgScheduledRecording1C::SyncGetPropertyListUpnpOrgScheduledRecording1C(CpProxyUpnpOrgScheduledRecording1C& aProxy, Brh& aPropertyList)
    : iService(aProxy)
    , iPropertyList(aPropertyList)
{
}

void SyncGetPropertyListUpnpOrgScheduledRecording1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetPropertyList(aAsync, iPropertyList);
}


class SyncGetAllowedValuesUpnpOrgScheduledRecording1C : public SyncProxyAction
{
public:
    SyncGetAllowedValuesUpnpOrgScheduledRecording1C(CpProxyUpnpOrgScheduledRecording1C& aProxy, Brh& aPropertyInfo);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetAllowedValuesUpnpOrgScheduledRecording1C() {};
private:
    CpProxyUpnpOrgScheduledRecording1C& iService;
    Brh& iPropertyInfo;
};

SyncGetAllowedValuesUpnpOrgScheduledRecording1C::SyncGetAllowedValuesUpnpOrgScheduledRecording1C(CpProxyUpnpOrgScheduledRecording1C& aProxy, Brh& aPropertyInfo)
    : iService(aProxy)
    , iPropertyInfo(aPropertyInfo)
{
}

void SyncGetAllowedValuesUpnpOrgScheduledRecording1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetAllowedValues(aAsync, iPropertyInfo);
}


class SyncGetStateUpdateIDUpnpOrgScheduledRecording1C : public SyncProxyAction
{
public:
    SyncGetStateUpdateIDUpnpOrgScheduledRecording1C(CpProxyUpnpOrgScheduledRecording1C& aProxy, TUint& aId);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetStateUpdateIDUpnpOrgScheduledRecording1C() {};
private:
    CpProxyUpnpOrgScheduledRecording1C& iService;
    TUint& iId;
};

SyncGetStateUpdateIDUpnpOrgScheduledRecording1C::SyncGetStateUpdateIDUpnpOrgScheduledRecording1C(CpProxyUpnpOrgScheduledRecording1C& aProxy, TUint& aId)
    : iService(aProxy)
    , iId(aId)
{
}

void SyncGetStateUpdateIDUpnpOrgScheduledRecording1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetStateUpdateID(aAsync, iId);
}


class SyncBrowseRecordSchedulesUpnpOrgScheduledRecording1C : public SyncProxyAction
{
public:
    SyncBrowseRecordSchedulesUpnpOrgScheduledRecording1C(CpProxyUpnpOrgScheduledRecording1C& aProxy, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncBrowseRecordSchedulesUpnpOrgScheduledRecording1C() {};
private:
    CpProxyUpnpOrgScheduledRecording1C& iService;
    Brh& iResult;
    TUint& iNumberReturned;
    TUint& iTotalMatches;
    TUint& iUpdateID;
};

SyncBrowseRecordSchedulesUpnpOrgScheduledRecording1C::SyncBrowseRecordSchedulesUpnpOrgScheduledRecording1C(CpProxyUpnpOrgScheduledRecording1C& aProxy, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID)
    : iService(aProxy)
    , iResult(aResult)
    , iNumberReturned(aNumberReturned)
    , iTotalMatches(aTotalMatches)
    , iUpdateID(aUpdateID)
{
}

void SyncBrowseRecordSchedulesUpnpOrgScheduledRecording1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndBrowseRecordSchedules(aAsync, iResult, iNumberReturned, iTotalMatches, iUpdateID);
}


class SyncBrowseRecordTasksUpnpOrgScheduledRecording1C : public SyncProxyAction
{
public:
    SyncBrowseRecordTasksUpnpOrgScheduledRecording1C(CpProxyUpnpOrgScheduledRecording1C& aProxy, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncBrowseRecordTasksUpnpOrgScheduledRecording1C() {};
private:
    CpProxyUpnpOrgScheduledRecording1C& iService;
    Brh& iResult;
    TUint& iNumberReturned;
    TUint& iTotalMatches;
    TUint& iUpdateID;
};

SyncBrowseRecordTasksUpnpOrgScheduledRecording1C::SyncBrowseRecordTasksUpnpOrgScheduledRecording1C(CpProxyUpnpOrgScheduledRecording1C& aProxy, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID)
    : iService(aProxy)
    , iResult(aResult)
    , iNumberReturned(aNumberReturned)
    , iTotalMatches(aTotalMatches)
    , iUpdateID(aUpdateID)
{
}

void SyncBrowseRecordTasksUpnpOrgScheduledRecording1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndBrowseRecordTasks(aAsync, iResult, iNumberReturned, iTotalMatches, iUpdateID);
}


class SyncCreateRecordScheduleUpnpOrgScheduledRecording1C : public SyncProxyAction
{
public:
    SyncCreateRecordScheduleUpnpOrgScheduledRecording1C(CpProxyUpnpOrgScheduledRecording1C& aProxy, Brh& aRecordScheduleID, Brh& aResult, TUint& aUpdateID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncCreateRecordScheduleUpnpOrgScheduledRecording1C() {};
private:
    CpProxyUpnpOrgScheduledRecording1C& iService;
    Brh& iRecordScheduleID;
    Brh& iResult;
    TUint& iUpdateID;
};

SyncCreateRecordScheduleUpnpOrgScheduledRecording1C::SyncCreateRecordScheduleUpnpOrgScheduledRecording1C(CpProxyUpnpOrgScheduledRecording1C& aProxy, Brh& aRecordScheduleID, Brh& aResult, TUint& aUpdateID)
    : iService(aProxy)
    , iRecordScheduleID(aRecordScheduleID)
    , iResult(aResult)
    , iUpdateID(aUpdateID)
{
}

void SyncCreateRecordScheduleUpnpOrgScheduledRecording1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndCreateRecordSchedule(aAsync, iRecordScheduleID, iResult, iUpdateID);
}


class SyncDeleteRecordScheduleUpnpOrgScheduledRecording1C : public SyncProxyAction
{
public:
    SyncDeleteRecordScheduleUpnpOrgScheduledRecording1C(CpProxyUpnpOrgScheduledRecording1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncDeleteRecordScheduleUpnpOrgScheduledRecording1C() {};
private:
    CpProxyUpnpOrgScheduledRecording1C& iService;
};

SyncDeleteRecordScheduleUpnpOrgScheduledRecording1C::SyncDeleteRecordScheduleUpnpOrgScheduledRecording1C(CpProxyUpnpOrgScheduledRecording1C& aProxy)
    : iService(aProxy)
{
}

void SyncDeleteRecordScheduleUpnpOrgScheduledRecording1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndDeleteRecordSchedule(aAsync);
}


class SyncGetRecordScheduleUpnpOrgScheduledRecording1C : public SyncProxyAction
{
public:
    SyncGetRecordScheduleUpnpOrgScheduledRecording1C(CpProxyUpnpOrgScheduledRecording1C& aProxy, Brh& aResult, TUint& aUpdateID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetRecordScheduleUpnpOrgScheduledRecording1C() {};
private:
    CpProxyUpnpOrgScheduledRecording1C& iService;
    Brh& iResult;
    TUint& iUpdateID;
};

SyncGetRecordScheduleUpnpOrgScheduledRecording1C::SyncGetRecordScheduleUpnpOrgScheduledRecording1C(CpProxyUpnpOrgScheduledRecording1C& aProxy, Brh& aResult, TUint& aUpdateID)
    : iService(aProxy)
    , iResult(aResult)
    , iUpdateID(aUpdateID)
{
}

void SyncGetRecordScheduleUpnpOrgScheduledRecording1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetRecordSchedule(aAsync, iResult, iUpdateID);
}


class SyncEnableRecordScheduleUpnpOrgScheduledRecording1C : public SyncProxyAction
{
public:
    SyncEnableRecordScheduleUpnpOrgScheduledRecording1C(CpProxyUpnpOrgScheduledRecording1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncEnableRecordScheduleUpnpOrgScheduledRecording1C() {};
private:
    CpProxyUpnpOrgScheduledRecording1C& iService;
};

SyncEnableRecordScheduleUpnpOrgScheduledRecording1C::SyncEnableRecordScheduleUpnpOrgScheduledRecording1C(CpProxyUpnpOrgScheduledRecording1C& aProxy)
    : iService(aProxy)
{
}

void SyncEnableRecordScheduleUpnpOrgScheduledRecording1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndEnableRecordSchedule(aAsync);
}


class SyncDisableRecordScheduleUpnpOrgScheduledRecording1C : public SyncProxyAction
{
public:
    SyncDisableRecordScheduleUpnpOrgScheduledRecording1C(CpProxyUpnpOrgScheduledRecording1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncDisableRecordScheduleUpnpOrgScheduledRecording1C() {};
private:
    CpProxyUpnpOrgScheduledRecording1C& iService;
};

SyncDisableRecordScheduleUpnpOrgScheduledRecording1C::SyncDisableRecordScheduleUpnpOrgScheduledRecording1C(CpProxyUpnpOrgScheduledRecording1C& aProxy)
    : iService(aProxy)
{
}

void SyncDisableRecordScheduleUpnpOrgScheduledRecording1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndDisableRecordSchedule(aAsync);
}


class SyncDeleteRecordTaskUpnpOrgScheduledRecording1C : public SyncProxyAction
{
public:
    SyncDeleteRecordTaskUpnpOrgScheduledRecording1C(CpProxyUpnpOrgScheduledRecording1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncDeleteRecordTaskUpnpOrgScheduledRecording1C() {};
private:
    CpProxyUpnpOrgScheduledRecording1C& iService;
};

SyncDeleteRecordTaskUpnpOrgScheduledRecording1C::SyncDeleteRecordTaskUpnpOrgScheduledRecording1C(CpProxyUpnpOrgScheduledRecording1C& aProxy)
    : iService(aProxy)
{
}

void SyncDeleteRecordTaskUpnpOrgScheduledRecording1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndDeleteRecordTask(aAsync);
}


class SyncGetRecordTaskUpnpOrgScheduledRecording1C : public SyncProxyAction
{
public:
    SyncGetRecordTaskUpnpOrgScheduledRecording1C(CpProxyUpnpOrgScheduledRecording1C& aProxy, Brh& aResult, TUint& aUpdateID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetRecordTaskUpnpOrgScheduledRecording1C() {};
private:
    CpProxyUpnpOrgScheduledRecording1C& iService;
    Brh& iResult;
    TUint& iUpdateID;
};

SyncGetRecordTaskUpnpOrgScheduledRecording1C::SyncGetRecordTaskUpnpOrgScheduledRecording1C(CpProxyUpnpOrgScheduledRecording1C& aProxy, Brh& aResult, TUint& aUpdateID)
    : iService(aProxy)
    , iResult(aResult)
    , iUpdateID(aUpdateID)
{
}

void SyncGetRecordTaskUpnpOrgScheduledRecording1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetRecordTask(aAsync, iResult, iUpdateID);
}


class SyncEnableRecordTaskUpnpOrgScheduledRecording1C : public SyncProxyAction
{
public:
    SyncEnableRecordTaskUpnpOrgScheduledRecording1C(CpProxyUpnpOrgScheduledRecording1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncEnableRecordTaskUpnpOrgScheduledRecording1C() {};
private:
    CpProxyUpnpOrgScheduledRecording1C& iService;
};

SyncEnableRecordTaskUpnpOrgScheduledRecording1C::SyncEnableRecordTaskUpnpOrgScheduledRecording1C(CpProxyUpnpOrgScheduledRecording1C& aProxy)
    : iService(aProxy)
{
}

void SyncEnableRecordTaskUpnpOrgScheduledRecording1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndEnableRecordTask(aAsync);
}


class SyncDisableRecordTaskUpnpOrgScheduledRecording1C : public SyncProxyAction
{
public:
    SyncDisableRecordTaskUpnpOrgScheduledRecording1C(CpProxyUpnpOrgScheduledRecording1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncDisableRecordTaskUpnpOrgScheduledRecording1C() {};
private:
    CpProxyUpnpOrgScheduledRecording1C& iService;
};

SyncDisableRecordTaskUpnpOrgScheduledRecording1C::SyncDisableRecordTaskUpnpOrgScheduledRecording1C(CpProxyUpnpOrgScheduledRecording1C& aProxy)
    : iService(aProxy)
{
}

void SyncDisableRecordTaskUpnpOrgScheduledRecording1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndDisableRecordTask(aAsync);
}


class SyncResetRecordTaskUpnpOrgScheduledRecording1C : public SyncProxyAction
{
public:
    SyncResetRecordTaskUpnpOrgScheduledRecording1C(CpProxyUpnpOrgScheduledRecording1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncResetRecordTaskUpnpOrgScheduledRecording1C() {};
private:
    CpProxyUpnpOrgScheduledRecording1C& iService;
};

SyncResetRecordTaskUpnpOrgScheduledRecording1C::SyncResetRecordTaskUpnpOrgScheduledRecording1C(CpProxyUpnpOrgScheduledRecording1C& aProxy)
    : iService(aProxy)
{
}

void SyncResetRecordTaskUpnpOrgScheduledRecording1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndResetRecordTask(aAsync);
}


class SyncGetRecordScheduleConflictsUpnpOrgScheduledRecording1C : public SyncProxyAction
{
public:
    SyncGetRecordScheduleConflictsUpnpOrgScheduledRecording1C(CpProxyUpnpOrgScheduledRecording1C& aProxy, Brh& aRecordScheduleConflictIDList, TUint& aUpdateID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetRecordScheduleConflictsUpnpOrgScheduledRecording1C() {};
private:
    CpProxyUpnpOrgScheduledRecording1C& iService;
    Brh& iRecordScheduleConflictIDList;
    TUint& iUpdateID;
};

SyncGetRecordScheduleConflictsUpnpOrgScheduledRecording1C::SyncGetRecordScheduleConflictsUpnpOrgScheduledRecording1C(CpProxyUpnpOrgScheduledRecording1C& aProxy, Brh& aRecordScheduleConflictIDList, TUint& aUpdateID)
    : iService(aProxy)
    , iRecordScheduleConflictIDList(aRecordScheduleConflictIDList)
    , iUpdateID(aUpdateID)
{
}

void SyncGetRecordScheduleConflictsUpnpOrgScheduledRecording1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetRecordScheduleConflicts(aAsync, iRecordScheduleConflictIDList, iUpdateID);
}


class SyncGetRecordTaskConflictsUpnpOrgScheduledRecording1C : public SyncProxyAction
{
public:
    SyncGetRecordTaskConflictsUpnpOrgScheduledRecording1C(CpProxyUpnpOrgScheduledRecording1C& aProxy, Brh& aRecordTaskConflictIDList, TUint& aUpdateID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetRecordTaskConflictsUpnpOrgScheduledRecording1C() {};
private:
    CpProxyUpnpOrgScheduledRecording1C& iService;
    Brh& iRecordTaskConflictIDList;
    TUint& iUpdateID;
};

SyncGetRecordTaskConflictsUpnpOrgScheduledRecording1C::SyncGetRecordTaskConflictsUpnpOrgScheduledRecording1C(CpProxyUpnpOrgScheduledRecording1C& aProxy, Brh& aRecordTaskConflictIDList, TUint& aUpdateID)
    : iService(aProxy)
    , iRecordTaskConflictIDList(aRecordTaskConflictIDList)
    , iUpdateID(aUpdateID)
{
}

void SyncGetRecordTaskConflictsUpnpOrgScheduledRecording1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetRecordTaskConflicts(aAsync, iRecordTaskConflictIDList, iUpdateID);
}

CpProxyUpnpOrgScheduledRecording1C::CpProxyUpnpOrgScheduledRecording1C(CpDeviceC aDevice)
    : CpProxyC("schemas-upnp-org", "ScheduledRecording", 1, *reinterpret_cast<CpiDevice*>(aDevice))
    , iLock("MPCS")
{
    OpenHome::Net::Parameter* param;
    TChar** allowedValues;
    TUint index;

    iActionGetSortCapabilities = new Action("GetSortCapabilities");
    param = new OpenHome::Net::ParameterString("SortCaps");
    iActionGetSortCapabilities->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("SortLevelCap");
    iActionGetSortCapabilities->AddOutputParameter(param);

    iActionGetPropertyList = new Action("GetPropertyList");
    index = 0;
    allowedValues = new TChar*[3];
    allowedValues[index++] = (TChar*)"A_ARG_TYPE_RecordSchedule";
    allowedValues[index++] = (TChar*)"A_ARG_TYPE_RecordTask";
    allowedValues[index++] = (TChar*)"A_ARG_TYPE_RecordScheduleParts";
    param = new OpenHome::Net::ParameterString("DataTypeID", allowedValues, 3);
    iActionGetPropertyList->AddInputParameter(param);
    delete[] allowedValues;
    param = new OpenHome::Net::ParameterString("PropertyList");
    iActionGetPropertyList->AddOutputParameter(param);

    iActionGetAllowedValues = new Action("GetAllowedValues");
    index = 0;
    allowedValues = new TChar*[3];
    allowedValues[index++] = (TChar*)"A_ARG_TYPE_RecordSchedule";
    allowedValues[index++] = (TChar*)"A_ARG_TYPE_RecordTask";
    allowedValues[index++] = (TChar*)"A_ARG_TYPE_RecordScheduleParts";
    param = new OpenHome::Net::ParameterString("DataTypeID", allowedValues, 3);
    iActionGetAllowedValues->AddInputParameter(param);
    delete[] allowedValues;
    param = new OpenHome::Net::ParameterString("Filter");
    iActionGetAllowedValues->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("PropertyInfo");
    iActionGetAllowedValues->AddOutputParameter(param);

    iActionGetStateUpdateID = new Action("GetStateUpdateID");
    param = new OpenHome::Net::ParameterUint("Id");
    iActionGetStateUpdateID->AddOutputParameter(param);

    iActionBrowseRecordSchedules = new Action("BrowseRecordSchedules");
    param = new OpenHome::Net::ParameterString("Filter");
    iActionBrowseRecordSchedules->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("StartingIndex");
    iActionBrowseRecordSchedules->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("RequestedCount");
    iActionBrowseRecordSchedules->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("SortCriteria");
    iActionBrowseRecordSchedules->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Result");
    iActionBrowseRecordSchedules->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("NumberReturned");
    iActionBrowseRecordSchedules->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("TotalMatches");
    iActionBrowseRecordSchedules->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("UpdateID");
    iActionBrowseRecordSchedules->AddOutputParameter(param);

    iActionBrowseRecordTasks = new Action("BrowseRecordTasks");
    param = new OpenHome::Net::ParameterString("RecordScheduleID");
    iActionBrowseRecordTasks->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Filter");
    iActionBrowseRecordTasks->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("StartingIndex");
    iActionBrowseRecordTasks->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("RequestedCount");
    iActionBrowseRecordTasks->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("SortCriteria");
    iActionBrowseRecordTasks->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Result");
    iActionBrowseRecordTasks->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("NumberReturned");
    iActionBrowseRecordTasks->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("TotalMatches");
    iActionBrowseRecordTasks->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("UpdateID");
    iActionBrowseRecordTasks->AddOutputParameter(param);

    iActionCreateRecordSchedule = new Action("CreateRecordSchedule");
    param = new OpenHome::Net::ParameterString("Elements");
    iActionCreateRecordSchedule->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("RecordScheduleID");
    iActionCreateRecordSchedule->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("Result");
    iActionCreateRecordSchedule->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("UpdateID");
    iActionCreateRecordSchedule->AddOutputParameter(param);

    iActionDeleteRecordSchedule = new Action("DeleteRecordSchedule");
    param = new OpenHome::Net::ParameterString("RecordScheduleID");
    iActionDeleteRecordSchedule->AddInputParameter(param);

    iActionGetRecordSchedule = new Action("GetRecordSchedule");
    param = new OpenHome::Net::ParameterString("RecordScheduleID");
    iActionGetRecordSchedule->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Filter");
    iActionGetRecordSchedule->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Result");
    iActionGetRecordSchedule->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("UpdateID");
    iActionGetRecordSchedule->AddOutputParameter(param);

    iActionEnableRecordSchedule = new Action("EnableRecordSchedule");
    param = new OpenHome::Net::ParameterString("RecordScheduleID");
    iActionEnableRecordSchedule->AddInputParameter(param);

    iActionDisableRecordSchedule = new Action("DisableRecordSchedule");
    param = new OpenHome::Net::ParameterString("RecordScheduleID");
    iActionDisableRecordSchedule->AddInputParameter(param);

    iActionDeleteRecordTask = new Action("DeleteRecordTask");
    param = new OpenHome::Net::ParameterString("RecordTaskID");
    iActionDeleteRecordTask->AddInputParameter(param);

    iActionGetRecordTask = new Action("GetRecordTask");
    param = new OpenHome::Net::ParameterString("RecordTaskID");
    iActionGetRecordTask->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Filter");
    iActionGetRecordTask->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Result");
    iActionGetRecordTask->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("UpdateID");
    iActionGetRecordTask->AddOutputParameter(param);

    iActionEnableRecordTask = new Action("EnableRecordTask");
    param = new OpenHome::Net::ParameterString("RecordTaskID");
    iActionEnableRecordTask->AddInputParameter(param);

    iActionDisableRecordTask = new Action("DisableRecordTask");
    param = new OpenHome::Net::ParameterString("RecordTaskID");
    iActionDisableRecordTask->AddInputParameter(param);

    iActionResetRecordTask = new Action("ResetRecordTask");
    param = new OpenHome::Net::ParameterString("RecordTaskID");
    iActionResetRecordTask->AddInputParameter(param);

    iActionGetRecordScheduleConflicts = new Action("GetRecordScheduleConflicts");
    param = new OpenHome::Net::ParameterString("RecordScheduleID");
    iActionGetRecordScheduleConflicts->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("RecordScheduleConflictIDList");
    iActionGetRecordScheduleConflicts->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("UpdateID");
    iActionGetRecordScheduleConflicts->AddOutputParameter(param);

    iActionGetRecordTaskConflicts = new Action("GetRecordTaskConflicts");
    param = new OpenHome::Net::ParameterString("RecordTaskID");
    iActionGetRecordTaskConflicts->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("RecordTaskConflictIDList");
    iActionGetRecordTaskConflicts->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("UpdateID");
    iActionGetRecordTaskConflicts->AddOutputParameter(param);

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyUpnpOrgScheduledRecording1C::LastChangePropertyChanged);
    iLastChange = new PropertyString(reinterpret_cast<CpiDevice*>(aDevice)->GetCpStack().Env(), "LastChange", functor);
    AddProperty(iLastChange);
}

CpProxyUpnpOrgScheduledRecording1C::~CpProxyUpnpOrgScheduledRecording1C()
{
    DestroyService();
    delete iActionGetSortCapabilities;
    delete iActionGetPropertyList;
    delete iActionGetAllowedValues;
    delete iActionGetStateUpdateID;
    delete iActionBrowseRecordSchedules;
    delete iActionBrowseRecordTasks;
    delete iActionCreateRecordSchedule;
    delete iActionDeleteRecordSchedule;
    delete iActionGetRecordSchedule;
    delete iActionEnableRecordSchedule;
    delete iActionDisableRecordSchedule;
    delete iActionDeleteRecordTask;
    delete iActionGetRecordTask;
    delete iActionEnableRecordTask;
    delete iActionDisableRecordTask;
    delete iActionResetRecordTask;
    delete iActionGetRecordScheduleConflicts;
    delete iActionGetRecordTaskConflicts;
}

void CpProxyUpnpOrgScheduledRecording1C::SyncGetSortCapabilities(Brh& aSortCaps, TUint& aSortLevelCap)
{
    SyncGetSortCapabilitiesUpnpOrgScheduledRecording1C sync(*this, aSortCaps, aSortLevelCap);
    BeginGetSortCapabilities(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording1C::BeginGetSortCapabilities(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetSortCapabilities, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetSortCapabilities->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgScheduledRecording1C::EndGetSortCapabilities(IAsync& aAsync, Brh& aSortCaps, TUint& aSortLevelCap)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetSortCapabilities"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aSortCaps);
    aSortLevelCap = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgScheduledRecording1C::SyncGetPropertyList(const Brx& aDataTypeID, Brh& aPropertyList)
{
    SyncGetPropertyListUpnpOrgScheduledRecording1C sync(*this, aPropertyList);
    BeginGetPropertyList(aDataTypeID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording1C::BeginGetPropertyList(const Brx& aDataTypeID, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetPropertyList, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetPropertyList->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aDataTypeID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetPropertyList->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgScheduledRecording1C::EndGetPropertyList(IAsync& aAsync, Brh& aPropertyList)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetPropertyList"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aPropertyList);
}

void CpProxyUpnpOrgScheduledRecording1C::SyncGetAllowedValues(const Brx& aDataTypeID, const Brx& aFilter, Brh& aPropertyInfo)
{
    SyncGetAllowedValuesUpnpOrgScheduledRecording1C sync(*this, aPropertyInfo);
    BeginGetAllowedValues(aDataTypeID, aFilter, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording1C::BeginGetAllowedValues(const Brx& aDataTypeID, const Brx& aFilter, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetAllowedValues, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetAllowedValues->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aDataTypeID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aFilter));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetAllowedValues->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgScheduledRecording1C::EndGetAllowedValues(IAsync& aAsync, Brh& aPropertyInfo)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetAllowedValues"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aPropertyInfo);
}

void CpProxyUpnpOrgScheduledRecording1C::SyncGetStateUpdateID(TUint& aId)
{
    SyncGetStateUpdateIDUpnpOrgScheduledRecording1C sync(*this, aId);
    BeginGetStateUpdateID(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording1C::BeginGetStateUpdateID(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetStateUpdateID, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetStateUpdateID->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgScheduledRecording1C::EndGetStateUpdateID(IAsync& aAsync, TUint& aId)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetStateUpdateID"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aId = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgScheduledRecording1C::SyncBrowseRecordSchedules(const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID)
{
    SyncBrowseRecordSchedulesUpnpOrgScheduledRecording1C sync(*this, aResult, aNumberReturned, aTotalMatches, aUpdateID);
    BeginBrowseRecordSchedules(aFilter, aStartingIndex, aRequestedCount, aSortCriteria, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording1C::BeginBrowseRecordSchedules(const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionBrowseRecordSchedules, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionBrowseRecordSchedules->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aFilter));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aStartingIndex));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aRequestedCount));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aSortCriteria));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionBrowseRecordSchedules->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgScheduledRecording1C::EndBrowseRecordSchedules(IAsync& aAsync, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("BrowseRecordSchedules"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aResult);
    aNumberReturned = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aTotalMatches = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aUpdateID = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgScheduledRecording1C::SyncBrowseRecordTasks(const Brx& aRecordScheduleID, const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID)
{
    SyncBrowseRecordTasksUpnpOrgScheduledRecording1C sync(*this, aResult, aNumberReturned, aTotalMatches, aUpdateID);
    BeginBrowseRecordTasks(aRecordScheduleID, aFilter, aStartingIndex, aRequestedCount, aSortCriteria, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording1C::BeginBrowseRecordTasks(const Brx& aRecordScheduleID, const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionBrowseRecordTasks, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionBrowseRecordTasks->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aRecordScheduleID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aFilter));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aStartingIndex));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aRequestedCount));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aSortCriteria));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionBrowseRecordTasks->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgScheduledRecording1C::EndBrowseRecordTasks(IAsync& aAsync, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("BrowseRecordTasks"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aResult);
    aNumberReturned = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aTotalMatches = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aUpdateID = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgScheduledRecording1C::SyncCreateRecordSchedule(const Brx& aElements, Brh& aRecordScheduleID, Brh& aResult, TUint& aUpdateID)
{
    SyncCreateRecordScheduleUpnpOrgScheduledRecording1C sync(*this, aRecordScheduleID, aResult, aUpdateID);
    BeginCreateRecordSchedule(aElements, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording1C::BeginCreateRecordSchedule(const Brx& aElements, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionCreateRecordSchedule, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionCreateRecordSchedule->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aElements));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionCreateRecordSchedule->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgScheduledRecording1C::EndCreateRecordSchedule(IAsync& aAsync, Brh& aRecordScheduleID, Brh& aResult, TUint& aUpdateID)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("CreateRecordSchedule"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aRecordScheduleID);
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aResult);
    aUpdateID = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgScheduledRecording1C::SyncDeleteRecordSchedule(const Brx& aRecordScheduleID)
{
    SyncDeleteRecordScheduleUpnpOrgScheduledRecording1C sync(*this);
    BeginDeleteRecordSchedule(aRecordScheduleID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording1C::BeginDeleteRecordSchedule(const Brx& aRecordScheduleID, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionDeleteRecordSchedule, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionDeleteRecordSchedule->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aRecordScheduleID));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgScheduledRecording1C::EndDeleteRecordSchedule(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("DeleteRecordSchedule"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgScheduledRecording1C::SyncGetRecordSchedule(const Brx& aRecordScheduleID, const Brx& aFilter, Brh& aResult, TUint& aUpdateID)
{
    SyncGetRecordScheduleUpnpOrgScheduledRecording1C sync(*this, aResult, aUpdateID);
    BeginGetRecordSchedule(aRecordScheduleID, aFilter, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording1C::BeginGetRecordSchedule(const Brx& aRecordScheduleID, const Brx& aFilter, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetRecordSchedule, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetRecordSchedule->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aRecordScheduleID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aFilter));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetRecordSchedule->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgScheduledRecording1C::EndGetRecordSchedule(IAsync& aAsync, Brh& aResult, TUint& aUpdateID)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetRecordSchedule"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aResult);
    aUpdateID = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgScheduledRecording1C::SyncEnableRecordSchedule(const Brx& aRecordScheduleID)
{
    SyncEnableRecordScheduleUpnpOrgScheduledRecording1C sync(*this);
    BeginEnableRecordSchedule(aRecordScheduleID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording1C::BeginEnableRecordSchedule(const Brx& aRecordScheduleID, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionEnableRecordSchedule, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionEnableRecordSchedule->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aRecordScheduleID));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgScheduledRecording1C::EndEnableRecordSchedule(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("EnableRecordSchedule"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgScheduledRecording1C::SyncDisableRecordSchedule(const Brx& aRecordScheduleID)
{
    SyncDisableRecordScheduleUpnpOrgScheduledRecording1C sync(*this);
    BeginDisableRecordSchedule(aRecordScheduleID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording1C::BeginDisableRecordSchedule(const Brx& aRecordScheduleID, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionDisableRecordSchedule, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionDisableRecordSchedule->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aRecordScheduleID));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgScheduledRecording1C::EndDisableRecordSchedule(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("DisableRecordSchedule"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgScheduledRecording1C::SyncDeleteRecordTask(const Brx& aRecordTaskID)
{
    SyncDeleteRecordTaskUpnpOrgScheduledRecording1C sync(*this);
    BeginDeleteRecordTask(aRecordTaskID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording1C::BeginDeleteRecordTask(const Brx& aRecordTaskID, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionDeleteRecordTask, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionDeleteRecordTask->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aRecordTaskID));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgScheduledRecording1C::EndDeleteRecordTask(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("DeleteRecordTask"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgScheduledRecording1C::SyncGetRecordTask(const Brx& aRecordTaskID, const Brx& aFilter, Brh& aResult, TUint& aUpdateID)
{
    SyncGetRecordTaskUpnpOrgScheduledRecording1C sync(*this, aResult, aUpdateID);
    BeginGetRecordTask(aRecordTaskID, aFilter, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording1C::BeginGetRecordTask(const Brx& aRecordTaskID, const Brx& aFilter, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetRecordTask, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetRecordTask->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aRecordTaskID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aFilter));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetRecordTask->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgScheduledRecording1C::EndGetRecordTask(IAsync& aAsync, Brh& aResult, TUint& aUpdateID)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetRecordTask"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aResult);
    aUpdateID = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgScheduledRecording1C::SyncEnableRecordTask(const Brx& aRecordTaskID)
{
    SyncEnableRecordTaskUpnpOrgScheduledRecording1C sync(*this);
    BeginEnableRecordTask(aRecordTaskID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording1C::BeginEnableRecordTask(const Brx& aRecordTaskID, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionEnableRecordTask, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionEnableRecordTask->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aRecordTaskID));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgScheduledRecording1C::EndEnableRecordTask(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("EnableRecordTask"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgScheduledRecording1C::SyncDisableRecordTask(const Brx& aRecordTaskID)
{
    SyncDisableRecordTaskUpnpOrgScheduledRecording1C sync(*this);
    BeginDisableRecordTask(aRecordTaskID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording1C::BeginDisableRecordTask(const Brx& aRecordTaskID, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionDisableRecordTask, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionDisableRecordTask->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aRecordTaskID));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgScheduledRecording1C::EndDisableRecordTask(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("DisableRecordTask"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgScheduledRecording1C::SyncResetRecordTask(const Brx& aRecordTaskID)
{
    SyncResetRecordTaskUpnpOrgScheduledRecording1C sync(*this);
    BeginResetRecordTask(aRecordTaskID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording1C::BeginResetRecordTask(const Brx& aRecordTaskID, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionResetRecordTask, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionResetRecordTask->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aRecordTaskID));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgScheduledRecording1C::EndResetRecordTask(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("ResetRecordTask"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgScheduledRecording1C::SyncGetRecordScheduleConflicts(const Brx& aRecordScheduleID, Brh& aRecordScheduleConflictIDList, TUint& aUpdateID)
{
    SyncGetRecordScheduleConflictsUpnpOrgScheduledRecording1C sync(*this, aRecordScheduleConflictIDList, aUpdateID);
    BeginGetRecordScheduleConflicts(aRecordScheduleID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording1C::BeginGetRecordScheduleConflicts(const Brx& aRecordScheduleID, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetRecordScheduleConflicts, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetRecordScheduleConflicts->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aRecordScheduleID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetRecordScheduleConflicts->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgScheduledRecording1C::EndGetRecordScheduleConflicts(IAsync& aAsync, Brh& aRecordScheduleConflictIDList, TUint& aUpdateID)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetRecordScheduleConflicts"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aRecordScheduleConflictIDList);
    aUpdateID = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgScheduledRecording1C::SyncGetRecordTaskConflicts(const Brx& aRecordTaskID, Brh& aRecordTaskConflictIDList, TUint& aUpdateID)
{
    SyncGetRecordTaskConflictsUpnpOrgScheduledRecording1C sync(*this, aRecordTaskConflictIDList, aUpdateID);
    BeginGetRecordTaskConflicts(aRecordTaskID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording1C::BeginGetRecordTaskConflicts(const Brx& aRecordTaskID, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetRecordTaskConflicts, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetRecordTaskConflicts->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aRecordTaskID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetRecordTaskConflicts->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgScheduledRecording1C::EndGetRecordTaskConflicts(IAsync& aAsync, Brh& aRecordTaskConflictIDList, TUint& aUpdateID)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetRecordTaskConflicts"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aRecordTaskConflictIDList);
    aUpdateID = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgScheduledRecording1C::SetPropertyLastChangeChanged(Functor& aFunctor)
{
    iLock.Wait();
    iLastChangeChanged = aFunctor;
    iLock.Signal();
}

void CpProxyUpnpOrgScheduledRecording1C::PropertyLastChange(Brhz& aLastChange) const
{
    AutoMutex a(GetPropertyReadLock());
    ASSERT(IsSubscribed());
    aLastChange.Set(iLastChange->Value());
}

void CpProxyUpnpOrgScheduledRecording1C::LastChangePropertyChanged()
{
    ReportEvent(iLastChangeChanged);
}


THandle STDCALL CpProxyUpnpOrgScheduledRecording1Create(CpDeviceC aDevice)
{
    return new CpProxyUpnpOrgScheduledRecording1C(aDevice);
}

void STDCALL CpProxyUpnpOrgScheduledRecording1Destroy(THandle aHandle)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    delete proxyC;
}

int32_t STDCALL CpProxyUpnpOrgScheduledRecording1SyncGetSortCapabilities(THandle aHandle, char** aSortCaps, uint32_t* aSortLevelCap)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aSortCaps;
    int32_t err = 0;
    try {
        proxyC->SyncGetSortCapabilities(buf_aSortCaps, *aSortLevelCap);
        *aSortCaps = buf_aSortCaps.Extract();
    }
    catch (ProxyError& ) {
        err = -1;
        *aSortCaps = NULL;
        *aSortLevelCap = 0;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgScheduledRecording1BeginGetSortCapabilities(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetSortCapabilities(functor);
}

int32_t STDCALL CpProxyUpnpOrgScheduledRecording1EndGetSortCapabilities(THandle aHandle, OhNetHandleAsync aAsync, char** aSortCaps, uint32_t* aSortLevelCap)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aSortCaps;
    *aSortCaps = NULL;
    try {
        proxyC->EndGetSortCapabilities(*async, buf_aSortCaps, *aSortLevelCap);
        *aSortCaps = buf_aSortCaps.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyUpnpOrgScheduledRecording1SyncGetPropertyList(THandle aHandle, const char* aDataTypeID, char** aPropertyList)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aDataTypeID(aDataTypeID);
    Brh buf_aPropertyList;
    int32_t err = 0;
    try {
        proxyC->SyncGetPropertyList(buf_aDataTypeID, buf_aPropertyList);
        *aPropertyList = buf_aPropertyList.Extract();
    }
    catch (ProxyError& ) {
        err = -1;
        *aPropertyList = NULL;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgScheduledRecording1BeginGetPropertyList(THandle aHandle, const char* aDataTypeID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aDataTypeID(aDataTypeID);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetPropertyList(buf_aDataTypeID, functor);
}

int32_t STDCALL CpProxyUpnpOrgScheduledRecording1EndGetPropertyList(THandle aHandle, OhNetHandleAsync aAsync, char** aPropertyList)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aPropertyList;
    *aPropertyList = NULL;
    try {
        proxyC->EndGetPropertyList(*async, buf_aPropertyList);
        *aPropertyList = buf_aPropertyList.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyUpnpOrgScheduledRecording1SyncGetAllowedValues(THandle aHandle, const char* aDataTypeID, const char* aFilter, char** aPropertyInfo)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aDataTypeID(aDataTypeID);
    Brh buf_aFilter(aFilter);
    Brh buf_aPropertyInfo;
    int32_t err = 0;
    try {
        proxyC->SyncGetAllowedValues(buf_aDataTypeID, buf_aFilter, buf_aPropertyInfo);
        *aPropertyInfo = buf_aPropertyInfo.Extract();
    }
    catch (ProxyError& ) {
        err = -1;
        *aPropertyInfo = NULL;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgScheduledRecording1BeginGetAllowedValues(THandle aHandle, const char* aDataTypeID, const char* aFilter, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aDataTypeID(aDataTypeID);
    Brh buf_aFilter(aFilter);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetAllowedValues(buf_aDataTypeID, buf_aFilter, functor);
}

int32_t STDCALL CpProxyUpnpOrgScheduledRecording1EndGetAllowedValues(THandle aHandle, OhNetHandleAsync aAsync, char** aPropertyInfo)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aPropertyInfo;
    *aPropertyInfo = NULL;
    try {
        proxyC->EndGetAllowedValues(*async, buf_aPropertyInfo);
        *aPropertyInfo = buf_aPropertyInfo.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyUpnpOrgScheduledRecording1SyncGetStateUpdateID(THandle aHandle, uint32_t* aId)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncGetStateUpdateID(*aId);
    }
    catch (ProxyError& ) {
        err = -1;
        *aId = 0;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgScheduledRecording1BeginGetStateUpdateID(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetStateUpdateID(functor);
}

int32_t STDCALL CpProxyUpnpOrgScheduledRecording1EndGetStateUpdateID(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aId)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndGetStateUpdateID(*async, *aId);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyUpnpOrgScheduledRecording1SyncBrowseRecordSchedules(THandle aHandle, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aFilter(aFilter);
    Brh buf_aSortCriteria(aSortCriteria);
    Brh buf_aResult;
    int32_t err = 0;
    try {
        proxyC->SyncBrowseRecordSchedules(buf_aFilter, aStartingIndex, aRequestedCount, buf_aSortCriteria, buf_aResult, *aNumberReturned, *aTotalMatches, *aUpdateID);
        *aResult = buf_aResult.Extract();
    }
    catch (ProxyError& ) {
        err = -1;
        *aResult = NULL;
        *aNumberReturned = 0;
        *aTotalMatches = 0;
        *aUpdateID = 0;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgScheduledRecording1BeginBrowseRecordSchedules(THandle aHandle, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aFilter(aFilter);
    Brh buf_aSortCriteria(aSortCriteria);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginBrowseRecordSchedules(buf_aFilter, aStartingIndex, aRequestedCount, buf_aSortCriteria, functor);
}

int32_t STDCALL CpProxyUpnpOrgScheduledRecording1EndBrowseRecordSchedules(THandle aHandle, OhNetHandleAsync aAsync, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aResult;
    *aResult = NULL;
    try {
        proxyC->EndBrowseRecordSchedules(*async, buf_aResult, *aNumberReturned, *aTotalMatches, *aUpdateID);
        *aResult = buf_aResult.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyUpnpOrgScheduledRecording1SyncBrowseRecordTasks(THandle aHandle, const char* aRecordScheduleID, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordScheduleID(aRecordScheduleID);
    Brh buf_aFilter(aFilter);
    Brh buf_aSortCriteria(aSortCriteria);
    Brh buf_aResult;
    int32_t err = 0;
    try {
        proxyC->SyncBrowseRecordTasks(buf_aRecordScheduleID, buf_aFilter, aStartingIndex, aRequestedCount, buf_aSortCriteria, buf_aResult, *aNumberReturned, *aTotalMatches, *aUpdateID);
        *aResult = buf_aResult.Extract();
    }
    catch (ProxyError& ) {
        err = -1;
        *aResult = NULL;
        *aNumberReturned = 0;
        *aTotalMatches = 0;
        *aUpdateID = 0;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgScheduledRecording1BeginBrowseRecordTasks(THandle aHandle, const char* aRecordScheduleID, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordScheduleID(aRecordScheduleID);
    Brh buf_aFilter(aFilter);
    Brh buf_aSortCriteria(aSortCriteria);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginBrowseRecordTasks(buf_aRecordScheduleID, buf_aFilter, aStartingIndex, aRequestedCount, buf_aSortCriteria, functor);
}

int32_t STDCALL CpProxyUpnpOrgScheduledRecording1EndBrowseRecordTasks(THandle aHandle, OhNetHandleAsync aAsync, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aResult;
    *aResult = NULL;
    try {
        proxyC->EndBrowseRecordTasks(*async, buf_aResult, *aNumberReturned, *aTotalMatches, *aUpdateID);
        *aResult = buf_aResult.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyUpnpOrgScheduledRecording1SyncCreateRecordSchedule(THandle aHandle, const char* aElements, char** aRecordScheduleID, char** aResult, uint32_t* aUpdateID)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aElements(aElements);
    Brh buf_aRecordScheduleID;
    Brh buf_aResult;
    int32_t err = 0;
    try {
        proxyC->SyncCreateRecordSchedule(buf_aElements, buf_aRecordScheduleID, buf_aResult, *aUpdateID);
        *aRecordScheduleID = buf_aRecordScheduleID.Extract();
        *aResult = buf_aResult.Extract();
    }
    catch (ProxyError& ) {
        err = -1;
        *aRecordScheduleID = NULL;
        *aResult = NULL;
        *aUpdateID = 0;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgScheduledRecording1BeginCreateRecordSchedule(THandle aHandle, const char* aElements, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aElements(aElements);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginCreateRecordSchedule(buf_aElements, functor);
}

int32_t STDCALL CpProxyUpnpOrgScheduledRecording1EndCreateRecordSchedule(THandle aHandle, OhNetHandleAsync aAsync, char** aRecordScheduleID, char** aResult, uint32_t* aUpdateID)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aRecordScheduleID;
    *aRecordScheduleID = NULL;
    Brh buf_aResult;
    *aResult = NULL;
    try {
        proxyC->EndCreateRecordSchedule(*async, buf_aRecordScheduleID, buf_aResult, *aUpdateID);
        *aRecordScheduleID = buf_aRecordScheduleID.Extract();
        *aResult = buf_aResult.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyUpnpOrgScheduledRecording1SyncDeleteRecordSchedule(THandle aHandle, const char* aRecordScheduleID)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordScheduleID(aRecordScheduleID);
    int32_t err = 0;
    try {
        proxyC->SyncDeleteRecordSchedule(buf_aRecordScheduleID);
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgScheduledRecording1BeginDeleteRecordSchedule(THandle aHandle, const char* aRecordScheduleID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordScheduleID(aRecordScheduleID);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginDeleteRecordSchedule(buf_aRecordScheduleID, functor);
}

int32_t STDCALL CpProxyUpnpOrgScheduledRecording1EndDeleteRecordSchedule(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndDeleteRecordSchedule(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyUpnpOrgScheduledRecording1SyncGetRecordSchedule(THandle aHandle, const char* aRecordScheduleID, const char* aFilter, char** aResult, uint32_t* aUpdateID)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordScheduleID(aRecordScheduleID);
    Brh buf_aFilter(aFilter);
    Brh buf_aResult;
    int32_t err = 0;
    try {
        proxyC->SyncGetRecordSchedule(buf_aRecordScheduleID, buf_aFilter, buf_aResult, *aUpdateID);
        *aResult = buf_aResult.Extract();
    }
    catch (ProxyError& ) {
        err = -1;
        *aResult = NULL;
        *aUpdateID = 0;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgScheduledRecording1BeginGetRecordSchedule(THandle aHandle, const char* aRecordScheduleID, const char* aFilter, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordScheduleID(aRecordScheduleID);
    Brh buf_aFilter(aFilter);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetRecordSchedule(buf_aRecordScheduleID, buf_aFilter, functor);
}

int32_t STDCALL CpProxyUpnpOrgScheduledRecording1EndGetRecordSchedule(THandle aHandle, OhNetHandleAsync aAsync, char** aResult, uint32_t* aUpdateID)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aResult;
    *aResult = NULL;
    try {
        proxyC->EndGetRecordSchedule(*async, buf_aResult, *aUpdateID);
        *aResult = buf_aResult.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyUpnpOrgScheduledRecording1SyncEnableRecordSchedule(THandle aHandle, const char* aRecordScheduleID)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordScheduleID(aRecordScheduleID);
    int32_t err = 0;
    try {
        proxyC->SyncEnableRecordSchedule(buf_aRecordScheduleID);
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgScheduledRecording1BeginEnableRecordSchedule(THandle aHandle, const char* aRecordScheduleID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordScheduleID(aRecordScheduleID);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginEnableRecordSchedule(buf_aRecordScheduleID, functor);
}

int32_t STDCALL CpProxyUpnpOrgScheduledRecording1EndEnableRecordSchedule(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndEnableRecordSchedule(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyUpnpOrgScheduledRecording1SyncDisableRecordSchedule(THandle aHandle, const char* aRecordScheduleID)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordScheduleID(aRecordScheduleID);
    int32_t err = 0;
    try {
        proxyC->SyncDisableRecordSchedule(buf_aRecordScheduleID);
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgScheduledRecording1BeginDisableRecordSchedule(THandle aHandle, const char* aRecordScheduleID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordScheduleID(aRecordScheduleID);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginDisableRecordSchedule(buf_aRecordScheduleID, functor);
}

int32_t STDCALL CpProxyUpnpOrgScheduledRecording1EndDisableRecordSchedule(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndDisableRecordSchedule(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyUpnpOrgScheduledRecording1SyncDeleteRecordTask(THandle aHandle, const char* aRecordTaskID)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordTaskID(aRecordTaskID);
    int32_t err = 0;
    try {
        proxyC->SyncDeleteRecordTask(buf_aRecordTaskID);
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgScheduledRecording1BeginDeleteRecordTask(THandle aHandle, const char* aRecordTaskID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordTaskID(aRecordTaskID);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginDeleteRecordTask(buf_aRecordTaskID, functor);
}

int32_t STDCALL CpProxyUpnpOrgScheduledRecording1EndDeleteRecordTask(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndDeleteRecordTask(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyUpnpOrgScheduledRecording1SyncGetRecordTask(THandle aHandle, const char* aRecordTaskID, const char* aFilter, char** aResult, uint32_t* aUpdateID)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordTaskID(aRecordTaskID);
    Brh buf_aFilter(aFilter);
    Brh buf_aResult;
    int32_t err = 0;
    try {
        proxyC->SyncGetRecordTask(buf_aRecordTaskID, buf_aFilter, buf_aResult, *aUpdateID);
        *aResult = buf_aResult.Extract();
    }
    catch (ProxyError& ) {
        err = -1;
        *aResult = NULL;
        *aUpdateID = 0;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgScheduledRecording1BeginGetRecordTask(THandle aHandle, const char* aRecordTaskID, const char* aFilter, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordTaskID(aRecordTaskID);
    Brh buf_aFilter(aFilter);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetRecordTask(buf_aRecordTaskID, buf_aFilter, functor);
}

int32_t STDCALL CpProxyUpnpOrgScheduledRecording1EndGetRecordTask(THandle aHandle, OhNetHandleAsync aAsync, char** aResult, uint32_t* aUpdateID)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aResult;
    *aResult = NULL;
    try {
        proxyC->EndGetRecordTask(*async, buf_aResult, *aUpdateID);
        *aResult = buf_aResult.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyUpnpOrgScheduledRecording1SyncEnableRecordTask(THandle aHandle, const char* aRecordTaskID)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordTaskID(aRecordTaskID);
    int32_t err = 0;
    try {
        proxyC->SyncEnableRecordTask(buf_aRecordTaskID);
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgScheduledRecording1BeginEnableRecordTask(THandle aHandle, const char* aRecordTaskID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordTaskID(aRecordTaskID);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginEnableRecordTask(buf_aRecordTaskID, functor);
}

int32_t STDCALL CpProxyUpnpOrgScheduledRecording1EndEnableRecordTask(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndEnableRecordTask(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyUpnpOrgScheduledRecording1SyncDisableRecordTask(THandle aHandle, const char* aRecordTaskID)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordTaskID(aRecordTaskID);
    int32_t err = 0;
    try {
        proxyC->SyncDisableRecordTask(buf_aRecordTaskID);
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgScheduledRecording1BeginDisableRecordTask(THandle aHandle, const char* aRecordTaskID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordTaskID(aRecordTaskID);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginDisableRecordTask(buf_aRecordTaskID, functor);
}

int32_t STDCALL CpProxyUpnpOrgScheduledRecording1EndDisableRecordTask(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndDisableRecordTask(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyUpnpOrgScheduledRecording1SyncResetRecordTask(THandle aHandle, const char* aRecordTaskID)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordTaskID(aRecordTaskID);
    int32_t err = 0;
    try {
        proxyC->SyncResetRecordTask(buf_aRecordTaskID);
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgScheduledRecording1BeginResetRecordTask(THandle aHandle, const char* aRecordTaskID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordTaskID(aRecordTaskID);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginResetRecordTask(buf_aRecordTaskID, functor);
}

int32_t STDCALL CpProxyUpnpOrgScheduledRecording1EndResetRecordTask(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndResetRecordTask(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyUpnpOrgScheduledRecording1SyncGetRecordScheduleConflicts(THandle aHandle, const char* aRecordScheduleID, char** aRecordScheduleConflictIDList, uint32_t* aUpdateID)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordScheduleID(aRecordScheduleID);
    Brh buf_aRecordScheduleConflictIDList;
    int32_t err = 0;
    try {
        proxyC->SyncGetRecordScheduleConflicts(buf_aRecordScheduleID, buf_aRecordScheduleConflictIDList, *aUpdateID);
        *aRecordScheduleConflictIDList = buf_aRecordScheduleConflictIDList.Extract();
    }
    catch (ProxyError& ) {
        err = -1;
        *aRecordScheduleConflictIDList = NULL;
        *aUpdateID = 0;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgScheduledRecording1BeginGetRecordScheduleConflicts(THandle aHandle, const char* aRecordScheduleID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordScheduleID(aRecordScheduleID);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetRecordScheduleConflicts(buf_aRecordScheduleID, functor);
}

int32_t STDCALL CpProxyUpnpOrgScheduledRecording1EndGetRecordScheduleConflicts(THandle aHandle, OhNetHandleAsync aAsync, char** aRecordScheduleConflictIDList, uint32_t* aUpdateID)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aRecordScheduleConflictIDList;
    *aRecordScheduleConflictIDList = NULL;
    try {
        proxyC->EndGetRecordScheduleConflicts(*async, buf_aRecordScheduleConflictIDList, *aUpdateID);
        *aRecordScheduleConflictIDList = buf_aRecordScheduleConflictIDList.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyUpnpOrgScheduledRecording1SyncGetRecordTaskConflicts(THandle aHandle, const char* aRecordTaskID, char** aRecordTaskConflictIDList, uint32_t* aUpdateID)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordTaskID(aRecordTaskID);
    Brh buf_aRecordTaskConflictIDList;
    int32_t err = 0;
    try {
        proxyC->SyncGetRecordTaskConflicts(buf_aRecordTaskID, buf_aRecordTaskConflictIDList, *aUpdateID);
        *aRecordTaskConflictIDList = buf_aRecordTaskConflictIDList.Extract();
    }
    catch (ProxyError& ) {
        err = -1;
        *aRecordTaskConflictIDList = NULL;
        *aUpdateID = 0;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgScheduledRecording1BeginGetRecordTaskConflicts(THandle aHandle, const char* aRecordTaskID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordTaskID(aRecordTaskID);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetRecordTaskConflicts(buf_aRecordTaskID, functor);
}

int32_t STDCALL CpProxyUpnpOrgScheduledRecording1EndGetRecordTaskConflicts(THandle aHandle, OhNetHandleAsync aAsync, char** aRecordTaskConflictIDList, uint32_t* aUpdateID)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aRecordTaskConflictIDList;
    *aRecordTaskConflictIDList = NULL;
    try {
        proxyC->EndGetRecordTaskConflicts(*async, buf_aRecordTaskConflictIDList, *aUpdateID);
        *aRecordTaskConflictIDList = buf_aRecordTaskConflictIDList.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgScheduledRecording1SetPropertyLastChangeChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyLastChangeChanged(functor);
}

void STDCALL CpProxyUpnpOrgScheduledRecording1PropertyLastChange(THandle aHandle, char** aLastChange)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aLastChange;
    proxyC->PropertyLastChange(buf_aLastChange);
    *aLastChange = buf_aLastChange.Transfer();
}

