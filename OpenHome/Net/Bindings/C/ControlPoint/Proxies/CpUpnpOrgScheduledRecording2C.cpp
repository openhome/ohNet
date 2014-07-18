#include "CpUpnpOrgScheduledRecording2.h"
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

class CpProxyUpnpOrgScheduledRecording2C : public CpProxyC
{
public:
    CpProxyUpnpOrgScheduledRecording2C(CpDeviceC aDevice);
    ~CpProxyUpnpOrgScheduledRecording2C();
    //CpProxyUpnpOrgScheduledRecording2* Proxy() { return static_cast<CpProxyUpnpOrgScheduledRecording2*>(iProxy); }

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


class SyncGetSortCapabilitiesUpnpOrgScheduledRecording2C : public SyncProxyAction
{
public:
    SyncGetSortCapabilitiesUpnpOrgScheduledRecording2C(CpProxyUpnpOrgScheduledRecording2C& aProxy, Brh& aSortCaps, TUint& aSortLevelCap);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetSortCapabilitiesUpnpOrgScheduledRecording2C() {};
private:
    CpProxyUpnpOrgScheduledRecording2C& iService;
    Brh& iSortCaps;
    TUint& iSortLevelCap;
};

SyncGetSortCapabilitiesUpnpOrgScheduledRecording2C::SyncGetSortCapabilitiesUpnpOrgScheduledRecording2C(CpProxyUpnpOrgScheduledRecording2C& aProxy, Brh& aSortCaps, TUint& aSortLevelCap)
    : iService(aProxy)
    , iSortCaps(aSortCaps)
    , iSortLevelCap(aSortLevelCap)
{
}

void SyncGetSortCapabilitiesUpnpOrgScheduledRecording2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetSortCapabilities(aAsync, iSortCaps, iSortLevelCap);
}


class SyncGetPropertyListUpnpOrgScheduledRecording2C : public SyncProxyAction
{
public:
    SyncGetPropertyListUpnpOrgScheduledRecording2C(CpProxyUpnpOrgScheduledRecording2C& aProxy, Brh& aPropertyList);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetPropertyListUpnpOrgScheduledRecording2C() {};
private:
    CpProxyUpnpOrgScheduledRecording2C& iService;
    Brh& iPropertyList;
};

SyncGetPropertyListUpnpOrgScheduledRecording2C::SyncGetPropertyListUpnpOrgScheduledRecording2C(CpProxyUpnpOrgScheduledRecording2C& aProxy, Brh& aPropertyList)
    : iService(aProxy)
    , iPropertyList(aPropertyList)
{
}

void SyncGetPropertyListUpnpOrgScheduledRecording2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetPropertyList(aAsync, iPropertyList);
}


class SyncGetAllowedValuesUpnpOrgScheduledRecording2C : public SyncProxyAction
{
public:
    SyncGetAllowedValuesUpnpOrgScheduledRecording2C(CpProxyUpnpOrgScheduledRecording2C& aProxy, Brh& aPropertyInfo);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetAllowedValuesUpnpOrgScheduledRecording2C() {};
private:
    CpProxyUpnpOrgScheduledRecording2C& iService;
    Brh& iPropertyInfo;
};

SyncGetAllowedValuesUpnpOrgScheduledRecording2C::SyncGetAllowedValuesUpnpOrgScheduledRecording2C(CpProxyUpnpOrgScheduledRecording2C& aProxy, Brh& aPropertyInfo)
    : iService(aProxy)
    , iPropertyInfo(aPropertyInfo)
{
}

void SyncGetAllowedValuesUpnpOrgScheduledRecording2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetAllowedValues(aAsync, iPropertyInfo);
}


class SyncGetStateUpdateIDUpnpOrgScheduledRecording2C : public SyncProxyAction
{
public:
    SyncGetStateUpdateIDUpnpOrgScheduledRecording2C(CpProxyUpnpOrgScheduledRecording2C& aProxy, TUint& aId);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetStateUpdateIDUpnpOrgScheduledRecording2C() {};
private:
    CpProxyUpnpOrgScheduledRecording2C& iService;
    TUint& iId;
};

SyncGetStateUpdateIDUpnpOrgScheduledRecording2C::SyncGetStateUpdateIDUpnpOrgScheduledRecording2C(CpProxyUpnpOrgScheduledRecording2C& aProxy, TUint& aId)
    : iService(aProxy)
    , iId(aId)
{
}

void SyncGetStateUpdateIDUpnpOrgScheduledRecording2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetStateUpdateID(aAsync, iId);
}


class SyncBrowseRecordSchedulesUpnpOrgScheduledRecording2C : public SyncProxyAction
{
public:
    SyncBrowseRecordSchedulesUpnpOrgScheduledRecording2C(CpProxyUpnpOrgScheduledRecording2C& aProxy, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncBrowseRecordSchedulesUpnpOrgScheduledRecording2C() {};
private:
    CpProxyUpnpOrgScheduledRecording2C& iService;
    Brh& iResult;
    TUint& iNumberReturned;
    TUint& iTotalMatches;
    TUint& iUpdateID;
};

SyncBrowseRecordSchedulesUpnpOrgScheduledRecording2C::SyncBrowseRecordSchedulesUpnpOrgScheduledRecording2C(CpProxyUpnpOrgScheduledRecording2C& aProxy, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID)
    : iService(aProxy)
    , iResult(aResult)
    , iNumberReturned(aNumberReturned)
    , iTotalMatches(aTotalMatches)
    , iUpdateID(aUpdateID)
{
}

void SyncBrowseRecordSchedulesUpnpOrgScheduledRecording2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndBrowseRecordSchedules(aAsync, iResult, iNumberReturned, iTotalMatches, iUpdateID);
}


class SyncBrowseRecordTasksUpnpOrgScheduledRecording2C : public SyncProxyAction
{
public:
    SyncBrowseRecordTasksUpnpOrgScheduledRecording2C(CpProxyUpnpOrgScheduledRecording2C& aProxy, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncBrowseRecordTasksUpnpOrgScheduledRecording2C() {};
private:
    CpProxyUpnpOrgScheduledRecording2C& iService;
    Brh& iResult;
    TUint& iNumberReturned;
    TUint& iTotalMatches;
    TUint& iUpdateID;
};

SyncBrowseRecordTasksUpnpOrgScheduledRecording2C::SyncBrowseRecordTasksUpnpOrgScheduledRecording2C(CpProxyUpnpOrgScheduledRecording2C& aProxy, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID)
    : iService(aProxy)
    , iResult(aResult)
    , iNumberReturned(aNumberReturned)
    , iTotalMatches(aTotalMatches)
    , iUpdateID(aUpdateID)
{
}

void SyncBrowseRecordTasksUpnpOrgScheduledRecording2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndBrowseRecordTasks(aAsync, iResult, iNumberReturned, iTotalMatches, iUpdateID);
}


class SyncCreateRecordScheduleUpnpOrgScheduledRecording2C : public SyncProxyAction
{
public:
    SyncCreateRecordScheduleUpnpOrgScheduledRecording2C(CpProxyUpnpOrgScheduledRecording2C& aProxy, Brh& aRecordScheduleID, Brh& aResult, TUint& aUpdateID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncCreateRecordScheduleUpnpOrgScheduledRecording2C() {};
private:
    CpProxyUpnpOrgScheduledRecording2C& iService;
    Brh& iRecordScheduleID;
    Brh& iResult;
    TUint& iUpdateID;
};

SyncCreateRecordScheduleUpnpOrgScheduledRecording2C::SyncCreateRecordScheduleUpnpOrgScheduledRecording2C(CpProxyUpnpOrgScheduledRecording2C& aProxy, Brh& aRecordScheduleID, Brh& aResult, TUint& aUpdateID)
    : iService(aProxy)
    , iRecordScheduleID(aRecordScheduleID)
    , iResult(aResult)
    , iUpdateID(aUpdateID)
{
}

void SyncCreateRecordScheduleUpnpOrgScheduledRecording2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndCreateRecordSchedule(aAsync, iRecordScheduleID, iResult, iUpdateID);
}


class SyncDeleteRecordScheduleUpnpOrgScheduledRecording2C : public SyncProxyAction
{
public:
    SyncDeleteRecordScheduleUpnpOrgScheduledRecording2C(CpProxyUpnpOrgScheduledRecording2C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncDeleteRecordScheduleUpnpOrgScheduledRecording2C() {};
private:
    CpProxyUpnpOrgScheduledRecording2C& iService;
};

SyncDeleteRecordScheduleUpnpOrgScheduledRecording2C::SyncDeleteRecordScheduleUpnpOrgScheduledRecording2C(CpProxyUpnpOrgScheduledRecording2C& aProxy)
    : iService(aProxy)
{
}

void SyncDeleteRecordScheduleUpnpOrgScheduledRecording2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndDeleteRecordSchedule(aAsync);
}


class SyncGetRecordScheduleUpnpOrgScheduledRecording2C : public SyncProxyAction
{
public:
    SyncGetRecordScheduleUpnpOrgScheduledRecording2C(CpProxyUpnpOrgScheduledRecording2C& aProxy, Brh& aResult, TUint& aUpdateID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetRecordScheduleUpnpOrgScheduledRecording2C() {};
private:
    CpProxyUpnpOrgScheduledRecording2C& iService;
    Brh& iResult;
    TUint& iUpdateID;
};

SyncGetRecordScheduleUpnpOrgScheduledRecording2C::SyncGetRecordScheduleUpnpOrgScheduledRecording2C(CpProxyUpnpOrgScheduledRecording2C& aProxy, Brh& aResult, TUint& aUpdateID)
    : iService(aProxy)
    , iResult(aResult)
    , iUpdateID(aUpdateID)
{
}

void SyncGetRecordScheduleUpnpOrgScheduledRecording2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetRecordSchedule(aAsync, iResult, iUpdateID);
}


class SyncEnableRecordScheduleUpnpOrgScheduledRecording2C : public SyncProxyAction
{
public:
    SyncEnableRecordScheduleUpnpOrgScheduledRecording2C(CpProxyUpnpOrgScheduledRecording2C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncEnableRecordScheduleUpnpOrgScheduledRecording2C() {};
private:
    CpProxyUpnpOrgScheduledRecording2C& iService;
};

SyncEnableRecordScheduleUpnpOrgScheduledRecording2C::SyncEnableRecordScheduleUpnpOrgScheduledRecording2C(CpProxyUpnpOrgScheduledRecording2C& aProxy)
    : iService(aProxy)
{
}

void SyncEnableRecordScheduleUpnpOrgScheduledRecording2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndEnableRecordSchedule(aAsync);
}


class SyncDisableRecordScheduleUpnpOrgScheduledRecording2C : public SyncProxyAction
{
public:
    SyncDisableRecordScheduleUpnpOrgScheduledRecording2C(CpProxyUpnpOrgScheduledRecording2C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncDisableRecordScheduleUpnpOrgScheduledRecording2C() {};
private:
    CpProxyUpnpOrgScheduledRecording2C& iService;
};

SyncDisableRecordScheduleUpnpOrgScheduledRecording2C::SyncDisableRecordScheduleUpnpOrgScheduledRecording2C(CpProxyUpnpOrgScheduledRecording2C& aProxy)
    : iService(aProxy)
{
}

void SyncDisableRecordScheduleUpnpOrgScheduledRecording2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndDisableRecordSchedule(aAsync);
}


class SyncDeleteRecordTaskUpnpOrgScheduledRecording2C : public SyncProxyAction
{
public:
    SyncDeleteRecordTaskUpnpOrgScheduledRecording2C(CpProxyUpnpOrgScheduledRecording2C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncDeleteRecordTaskUpnpOrgScheduledRecording2C() {};
private:
    CpProxyUpnpOrgScheduledRecording2C& iService;
};

SyncDeleteRecordTaskUpnpOrgScheduledRecording2C::SyncDeleteRecordTaskUpnpOrgScheduledRecording2C(CpProxyUpnpOrgScheduledRecording2C& aProxy)
    : iService(aProxy)
{
}

void SyncDeleteRecordTaskUpnpOrgScheduledRecording2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndDeleteRecordTask(aAsync);
}


class SyncGetRecordTaskUpnpOrgScheduledRecording2C : public SyncProxyAction
{
public:
    SyncGetRecordTaskUpnpOrgScheduledRecording2C(CpProxyUpnpOrgScheduledRecording2C& aProxy, Brh& aResult, TUint& aUpdateID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetRecordTaskUpnpOrgScheduledRecording2C() {};
private:
    CpProxyUpnpOrgScheduledRecording2C& iService;
    Brh& iResult;
    TUint& iUpdateID;
};

SyncGetRecordTaskUpnpOrgScheduledRecording2C::SyncGetRecordTaskUpnpOrgScheduledRecording2C(CpProxyUpnpOrgScheduledRecording2C& aProxy, Brh& aResult, TUint& aUpdateID)
    : iService(aProxy)
    , iResult(aResult)
    , iUpdateID(aUpdateID)
{
}

void SyncGetRecordTaskUpnpOrgScheduledRecording2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetRecordTask(aAsync, iResult, iUpdateID);
}


class SyncEnableRecordTaskUpnpOrgScheduledRecording2C : public SyncProxyAction
{
public:
    SyncEnableRecordTaskUpnpOrgScheduledRecording2C(CpProxyUpnpOrgScheduledRecording2C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncEnableRecordTaskUpnpOrgScheduledRecording2C() {};
private:
    CpProxyUpnpOrgScheduledRecording2C& iService;
};

SyncEnableRecordTaskUpnpOrgScheduledRecording2C::SyncEnableRecordTaskUpnpOrgScheduledRecording2C(CpProxyUpnpOrgScheduledRecording2C& aProxy)
    : iService(aProxy)
{
}

void SyncEnableRecordTaskUpnpOrgScheduledRecording2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndEnableRecordTask(aAsync);
}


class SyncDisableRecordTaskUpnpOrgScheduledRecording2C : public SyncProxyAction
{
public:
    SyncDisableRecordTaskUpnpOrgScheduledRecording2C(CpProxyUpnpOrgScheduledRecording2C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncDisableRecordTaskUpnpOrgScheduledRecording2C() {};
private:
    CpProxyUpnpOrgScheduledRecording2C& iService;
};

SyncDisableRecordTaskUpnpOrgScheduledRecording2C::SyncDisableRecordTaskUpnpOrgScheduledRecording2C(CpProxyUpnpOrgScheduledRecording2C& aProxy)
    : iService(aProxy)
{
}

void SyncDisableRecordTaskUpnpOrgScheduledRecording2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndDisableRecordTask(aAsync);
}


class SyncResetRecordTaskUpnpOrgScheduledRecording2C : public SyncProxyAction
{
public:
    SyncResetRecordTaskUpnpOrgScheduledRecording2C(CpProxyUpnpOrgScheduledRecording2C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncResetRecordTaskUpnpOrgScheduledRecording2C() {};
private:
    CpProxyUpnpOrgScheduledRecording2C& iService;
};

SyncResetRecordTaskUpnpOrgScheduledRecording2C::SyncResetRecordTaskUpnpOrgScheduledRecording2C(CpProxyUpnpOrgScheduledRecording2C& aProxy)
    : iService(aProxy)
{
}

void SyncResetRecordTaskUpnpOrgScheduledRecording2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndResetRecordTask(aAsync);
}


class SyncGetRecordScheduleConflictsUpnpOrgScheduledRecording2C : public SyncProxyAction
{
public:
    SyncGetRecordScheduleConflictsUpnpOrgScheduledRecording2C(CpProxyUpnpOrgScheduledRecording2C& aProxy, Brh& aRecordScheduleConflictIDList, TUint& aUpdateID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetRecordScheduleConflictsUpnpOrgScheduledRecording2C() {};
private:
    CpProxyUpnpOrgScheduledRecording2C& iService;
    Brh& iRecordScheduleConflictIDList;
    TUint& iUpdateID;
};

SyncGetRecordScheduleConflictsUpnpOrgScheduledRecording2C::SyncGetRecordScheduleConflictsUpnpOrgScheduledRecording2C(CpProxyUpnpOrgScheduledRecording2C& aProxy, Brh& aRecordScheduleConflictIDList, TUint& aUpdateID)
    : iService(aProxy)
    , iRecordScheduleConflictIDList(aRecordScheduleConflictIDList)
    , iUpdateID(aUpdateID)
{
}

void SyncGetRecordScheduleConflictsUpnpOrgScheduledRecording2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetRecordScheduleConflicts(aAsync, iRecordScheduleConflictIDList, iUpdateID);
}


class SyncGetRecordTaskConflictsUpnpOrgScheduledRecording2C : public SyncProxyAction
{
public:
    SyncGetRecordTaskConflictsUpnpOrgScheduledRecording2C(CpProxyUpnpOrgScheduledRecording2C& aProxy, Brh& aRecordTaskConflictIDList, TUint& aUpdateID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetRecordTaskConflictsUpnpOrgScheduledRecording2C() {};
private:
    CpProxyUpnpOrgScheduledRecording2C& iService;
    Brh& iRecordTaskConflictIDList;
    TUint& iUpdateID;
};

SyncGetRecordTaskConflictsUpnpOrgScheduledRecording2C::SyncGetRecordTaskConflictsUpnpOrgScheduledRecording2C(CpProxyUpnpOrgScheduledRecording2C& aProxy, Brh& aRecordTaskConflictIDList, TUint& aUpdateID)
    : iService(aProxy)
    , iRecordTaskConflictIDList(aRecordTaskConflictIDList)
    , iUpdateID(aUpdateID)
{
}

void SyncGetRecordTaskConflictsUpnpOrgScheduledRecording2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetRecordTaskConflicts(aAsync, iRecordTaskConflictIDList, iUpdateID);
}

CpProxyUpnpOrgScheduledRecording2C::CpProxyUpnpOrgScheduledRecording2C(CpDeviceC aDevice)
    : CpProxyC("schemas-upnp-org", "ScheduledRecording", 2, *reinterpret_cast<CpiDevice*>(aDevice))
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
    functor = MakeFunctor(*this, &CpProxyUpnpOrgScheduledRecording2C::LastChangePropertyChanged);
    iLastChange = new PropertyString(reinterpret_cast<CpiDevice*>(aDevice)->GetCpStack().Env(), "LastChange", functor);
    AddProperty(iLastChange);
}

CpProxyUpnpOrgScheduledRecording2C::~CpProxyUpnpOrgScheduledRecording2C()
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

void CpProxyUpnpOrgScheduledRecording2C::SyncGetSortCapabilities(Brh& aSortCaps, TUint& aSortLevelCap)
{
    SyncGetSortCapabilitiesUpnpOrgScheduledRecording2C sync(*this, aSortCaps, aSortLevelCap);
    BeginGetSortCapabilities(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording2C::BeginGetSortCapabilities(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetSortCapabilities, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetSortCapabilities->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgScheduledRecording2C::EndGetSortCapabilities(IAsync& aAsync, Brh& aSortCaps, TUint& aSortLevelCap)
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

void CpProxyUpnpOrgScheduledRecording2C::SyncGetPropertyList(const Brx& aDataTypeID, Brh& aPropertyList)
{
    SyncGetPropertyListUpnpOrgScheduledRecording2C sync(*this, aPropertyList);
    BeginGetPropertyList(aDataTypeID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording2C::BeginGetPropertyList(const Brx& aDataTypeID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgScheduledRecording2C::EndGetPropertyList(IAsync& aAsync, Brh& aPropertyList)
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

void CpProxyUpnpOrgScheduledRecording2C::SyncGetAllowedValues(const Brx& aDataTypeID, const Brx& aFilter, Brh& aPropertyInfo)
{
    SyncGetAllowedValuesUpnpOrgScheduledRecording2C sync(*this, aPropertyInfo);
    BeginGetAllowedValues(aDataTypeID, aFilter, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording2C::BeginGetAllowedValues(const Brx& aDataTypeID, const Brx& aFilter, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgScheduledRecording2C::EndGetAllowedValues(IAsync& aAsync, Brh& aPropertyInfo)
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

void CpProxyUpnpOrgScheduledRecording2C::SyncGetStateUpdateID(TUint& aId)
{
    SyncGetStateUpdateIDUpnpOrgScheduledRecording2C sync(*this, aId);
    BeginGetStateUpdateID(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording2C::BeginGetStateUpdateID(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetStateUpdateID, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetStateUpdateID->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgScheduledRecording2C::EndGetStateUpdateID(IAsync& aAsync, TUint& aId)
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

void CpProxyUpnpOrgScheduledRecording2C::SyncBrowseRecordSchedules(const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID)
{
    SyncBrowseRecordSchedulesUpnpOrgScheduledRecording2C sync(*this, aResult, aNumberReturned, aTotalMatches, aUpdateID);
    BeginBrowseRecordSchedules(aFilter, aStartingIndex, aRequestedCount, aSortCriteria, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording2C::BeginBrowseRecordSchedules(const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgScheduledRecording2C::EndBrowseRecordSchedules(IAsync& aAsync, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID)
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

void CpProxyUpnpOrgScheduledRecording2C::SyncBrowseRecordTasks(const Brx& aRecordScheduleID, const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID)
{
    SyncBrowseRecordTasksUpnpOrgScheduledRecording2C sync(*this, aResult, aNumberReturned, aTotalMatches, aUpdateID);
    BeginBrowseRecordTasks(aRecordScheduleID, aFilter, aStartingIndex, aRequestedCount, aSortCriteria, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording2C::BeginBrowseRecordTasks(const Brx& aRecordScheduleID, const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgScheduledRecording2C::EndBrowseRecordTasks(IAsync& aAsync, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID)
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

void CpProxyUpnpOrgScheduledRecording2C::SyncCreateRecordSchedule(const Brx& aElements, Brh& aRecordScheduleID, Brh& aResult, TUint& aUpdateID)
{
    SyncCreateRecordScheduleUpnpOrgScheduledRecording2C sync(*this, aRecordScheduleID, aResult, aUpdateID);
    BeginCreateRecordSchedule(aElements, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording2C::BeginCreateRecordSchedule(const Brx& aElements, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgScheduledRecording2C::EndCreateRecordSchedule(IAsync& aAsync, Brh& aRecordScheduleID, Brh& aResult, TUint& aUpdateID)
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

void CpProxyUpnpOrgScheduledRecording2C::SyncDeleteRecordSchedule(const Brx& aRecordScheduleID)
{
    SyncDeleteRecordScheduleUpnpOrgScheduledRecording2C sync(*this);
    BeginDeleteRecordSchedule(aRecordScheduleID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording2C::BeginDeleteRecordSchedule(const Brx& aRecordScheduleID, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionDeleteRecordSchedule, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionDeleteRecordSchedule->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aRecordScheduleID));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgScheduledRecording2C::EndDeleteRecordSchedule(IAsync& aAsync)
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

void CpProxyUpnpOrgScheduledRecording2C::SyncGetRecordSchedule(const Brx& aRecordScheduleID, const Brx& aFilter, Brh& aResult, TUint& aUpdateID)
{
    SyncGetRecordScheduleUpnpOrgScheduledRecording2C sync(*this, aResult, aUpdateID);
    BeginGetRecordSchedule(aRecordScheduleID, aFilter, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording2C::BeginGetRecordSchedule(const Brx& aRecordScheduleID, const Brx& aFilter, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgScheduledRecording2C::EndGetRecordSchedule(IAsync& aAsync, Brh& aResult, TUint& aUpdateID)
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

void CpProxyUpnpOrgScheduledRecording2C::SyncEnableRecordSchedule(const Brx& aRecordScheduleID)
{
    SyncEnableRecordScheduleUpnpOrgScheduledRecording2C sync(*this);
    BeginEnableRecordSchedule(aRecordScheduleID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording2C::BeginEnableRecordSchedule(const Brx& aRecordScheduleID, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionEnableRecordSchedule, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionEnableRecordSchedule->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aRecordScheduleID));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgScheduledRecording2C::EndEnableRecordSchedule(IAsync& aAsync)
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

void CpProxyUpnpOrgScheduledRecording2C::SyncDisableRecordSchedule(const Brx& aRecordScheduleID)
{
    SyncDisableRecordScheduleUpnpOrgScheduledRecording2C sync(*this);
    BeginDisableRecordSchedule(aRecordScheduleID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording2C::BeginDisableRecordSchedule(const Brx& aRecordScheduleID, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionDisableRecordSchedule, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionDisableRecordSchedule->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aRecordScheduleID));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgScheduledRecording2C::EndDisableRecordSchedule(IAsync& aAsync)
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

void CpProxyUpnpOrgScheduledRecording2C::SyncDeleteRecordTask(const Brx& aRecordTaskID)
{
    SyncDeleteRecordTaskUpnpOrgScheduledRecording2C sync(*this);
    BeginDeleteRecordTask(aRecordTaskID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording2C::BeginDeleteRecordTask(const Brx& aRecordTaskID, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionDeleteRecordTask, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionDeleteRecordTask->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aRecordTaskID));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgScheduledRecording2C::EndDeleteRecordTask(IAsync& aAsync)
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

void CpProxyUpnpOrgScheduledRecording2C::SyncGetRecordTask(const Brx& aRecordTaskID, const Brx& aFilter, Brh& aResult, TUint& aUpdateID)
{
    SyncGetRecordTaskUpnpOrgScheduledRecording2C sync(*this, aResult, aUpdateID);
    BeginGetRecordTask(aRecordTaskID, aFilter, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording2C::BeginGetRecordTask(const Brx& aRecordTaskID, const Brx& aFilter, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgScheduledRecording2C::EndGetRecordTask(IAsync& aAsync, Brh& aResult, TUint& aUpdateID)
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

void CpProxyUpnpOrgScheduledRecording2C::SyncEnableRecordTask(const Brx& aRecordTaskID)
{
    SyncEnableRecordTaskUpnpOrgScheduledRecording2C sync(*this);
    BeginEnableRecordTask(aRecordTaskID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording2C::BeginEnableRecordTask(const Brx& aRecordTaskID, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionEnableRecordTask, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionEnableRecordTask->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aRecordTaskID));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgScheduledRecording2C::EndEnableRecordTask(IAsync& aAsync)
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

void CpProxyUpnpOrgScheduledRecording2C::SyncDisableRecordTask(const Brx& aRecordTaskID)
{
    SyncDisableRecordTaskUpnpOrgScheduledRecording2C sync(*this);
    BeginDisableRecordTask(aRecordTaskID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording2C::BeginDisableRecordTask(const Brx& aRecordTaskID, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionDisableRecordTask, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionDisableRecordTask->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aRecordTaskID));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgScheduledRecording2C::EndDisableRecordTask(IAsync& aAsync)
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

void CpProxyUpnpOrgScheduledRecording2C::SyncResetRecordTask(const Brx& aRecordTaskID)
{
    SyncResetRecordTaskUpnpOrgScheduledRecording2C sync(*this);
    BeginResetRecordTask(aRecordTaskID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording2C::BeginResetRecordTask(const Brx& aRecordTaskID, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionResetRecordTask, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionResetRecordTask->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aRecordTaskID));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgScheduledRecording2C::EndResetRecordTask(IAsync& aAsync)
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

void CpProxyUpnpOrgScheduledRecording2C::SyncGetRecordScheduleConflicts(const Brx& aRecordScheduleID, Brh& aRecordScheduleConflictIDList, TUint& aUpdateID)
{
    SyncGetRecordScheduleConflictsUpnpOrgScheduledRecording2C sync(*this, aRecordScheduleConflictIDList, aUpdateID);
    BeginGetRecordScheduleConflicts(aRecordScheduleID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording2C::BeginGetRecordScheduleConflicts(const Brx& aRecordScheduleID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgScheduledRecording2C::EndGetRecordScheduleConflicts(IAsync& aAsync, Brh& aRecordScheduleConflictIDList, TUint& aUpdateID)
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

void CpProxyUpnpOrgScheduledRecording2C::SyncGetRecordTaskConflicts(const Brx& aRecordTaskID, Brh& aRecordTaskConflictIDList, TUint& aUpdateID)
{
    SyncGetRecordTaskConflictsUpnpOrgScheduledRecording2C sync(*this, aRecordTaskConflictIDList, aUpdateID);
    BeginGetRecordTaskConflicts(aRecordTaskID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording2C::BeginGetRecordTaskConflicts(const Brx& aRecordTaskID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgScheduledRecording2C::EndGetRecordTaskConflicts(IAsync& aAsync, Brh& aRecordTaskConflictIDList, TUint& aUpdateID)
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

void CpProxyUpnpOrgScheduledRecording2C::SetPropertyLastChangeChanged(Functor& aFunctor)
{
    iLock.Wait();
    iLastChangeChanged = aFunctor;
    iLock.Signal();
}

void CpProxyUpnpOrgScheduledRecording2C::PropertyLastChange(Brhz& aLastChange) const
{
    AutoMutex a(GetPropertyReadLock());
    ASSERT(IsSubscribed());
    aLastChange.Set(iLastChange->Value());
}

void CpProxyUpnpOrgScheduledRecording2C::LastChangePropertyChanged()
{
    ReportEvent(iLastChangeChanged);
}


THandle STDCALL CpProxyUpnpOrgScheduledRecording2Create(CpDeviceC aDevice)
{
    return new CpProxyUpnpOrgScheduledRecording2C(aDevice);
}

void STDCALL CpProxyUpnpOrgScheduledRecording2Destroy(THandle aHandle)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
    delete proxyC;
}

int32_t STDCALL CpProxyUpnpOrgScheduledRecording2SyncGetSortCapabilities(THandle aHandle, char** aSortCaps, uint32_t* aSortLevelCap)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
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

void STDCALL CpProxyUpnpOrgScheduledRecording2BeginGetSortCapabilities(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetSortCapabilities(functor);
}

int32_t STDCALL CpProxyUpnpOrgScheduledRecording2EndGetSortCapabilities(THandle aHandle, OhNetHandleAsync aAsync, char** aSortCaps, uint32_t* aSortLevelCap)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgScheduledRecording2SyncGetPropertyList(THandle aHandle, const char* aDataTypeID, char** aPropertyList)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
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

void STDCALL CpProxyUpnpOrgScheduledRecording2BeginGetPropertyList(THandle aHandle, const char* aDataTypeID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aDataTypeID(aDataTypeID);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetPropertyList(buf_aDataTypeID, functor);
}

int32_t STDCALL CpProxyUpnpOrgScheduledRecording2EndGetPropertyList(THandle aHandle, OhNetHandleAsync aAsync, char** aPropertyList)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgScheduledRecording2SyncGetAllowedValues(THandle aHandle, const char* aDataTypeID, const char* aFilter, char** aPropertyInfo)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
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

void STDCALL CpProxyUpnpOrgScheduledRecording2BeginGetAllowedValues(THandle aHandle, const char* aDataTypeID, const char* aFilter, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aDataTypeID(aDataTypeID);
    Brh buf_aFilter(aFilter);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetAllowedValues(buf_aDataTypeID, buf_aFilter, functor);
}

int32_t STDCALL CpProxyUpnpOrgScheduledRecording2EndGetAllowedValues(THandle aHandle, OhNetHandleAsync aAsync, char** aPropertyInfo)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgScheduledRecording2SyncGetStateUpdateID(THandle aHandle, uint32_t* aId)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
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

void STDCALL CpProxyUpnpOrgScheduledRecording2BeginGetStateUpdateID(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetStateUpdateID(functor);
}

int32_t STDCALL CpProxyUpnpOrgScheduledRecording2EndGetStateUpdateID(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aId)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgScheduledRecording2SyncBrowseRecordSchedules(THandle aHandle, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
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

void STDCALL CpProxyUpnpOrgScheduledRecording2BeginBrowseRecordSchedules(THandle aHandle, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aFilter(aFilter);
    Brh buf_aSortCriteria(aSortCriteria);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginBrowseRecordSchedules(buf_aFilter, aStartingIndex, aRequestedCount, buf_aSortCriteria, functor);
}

int32_t STDCALL CpProxyUpnpOrgScheduledRecording2EndBrowseRecordSchedules(THandle aHandle, OhNetHandleAsync aAsync, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgScheduledRecording2SyncBrowseRecordTasks(THandle aHandle, const char* aRecordScheduleID, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
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

void STDCALL CpProxyUpnpOrgScheduledRecording2BeginBrowseRecordTasks(THandle aHandle, const char* aRecordScheduleID, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordScheduleID(aRecordScheduleID);
    Brh buf_aFilter(aFilter);
    Brh buf_aSortCriteria(aSortCriteria);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginBrowseRecordTasks(buf_aRecordScheduleID, buf_aFilter, aStartingIndex, aRequestedCount, buf_aSortCriteria, functor);
}

int32_t STDCALL CpProxyUpnpOrgScheduledRecording2EndBrowseRecordTasks(THandle aHandle, OhNetHandleAsync aAsync, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgScheduledRecording2SyncCreateRecordSchedule(THandle aHandle, const char* aElements, char** aRecordScheduleID, char** aResult, uint32_t* aUpdateID)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
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

void STDCALL CpProxyUpnpOrgScheduledRecording2BeginCreateRecordSchedule(THandle aHandle, const char* aElements, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aElements(aElements);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginCreateRecordSchedule(buf_aElements, functor);
}

int32_t STDCALL CpProxyUpnpOrgScheduledRecording2EndCreateRecordSchedule(THandle aHandle, OhNetHandleAsync aAsync, char** aRecordScheduleID, char** aResult, uint32_t* aUpdateID)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgScheduledRecording2SyncDeleteRecordSchedule(THandle aHandle, const char* aRecordScheduleID)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
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

void STDCALL CpProxyUpnpOrgScheduledRecording2BeginDeleteRecordSchedule(THandle aHandle, const char* aRecordScheduleID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordScheduleID(aRecordScheduleID);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginDeleteRecordSchedule(buf_aRecordScheduleID, functor);
}

int32_t STDCALL CpProxyUpnpOrgScheduledRecording2EndDeleteRecordSchedule(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgScheduledRecording2SyncGetRecordSchedule(THandle aHandle, const char* aRecordScheduleID, const char* aFilter, char** aResult, uint32_t* aUpdateID)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
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

void STDCALL CpProxyUpnpOrgScheduledRecording2BeginGetRecordSchedule(THandle aHandle, const char* aRecordScheduleID, const char* aFilter, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordScheduleID(aRecordScheduleID);
    Brh buf_aFilter(aFilter);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetRecordSchedule(buf_aRecordScheduleID, buf_aFilter, functor);
}

int32_t STDCALL CpProxyUpnpOrgScheduledRecording2EndGetRecordSchedule(THandle aHandle, OhNetHandleAsync aAsync, char** aResult, uint32_t* aUpdateID)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgScheduledRecording2SyncEnableRecordSchedule(THandle aHandle, const char* aRecordScheduleID)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
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

void STDCALL CpProxyUpnpOrgScheduledRecording2BeginEnableRecordSchedule(THandle aHandle, const char* aRecordScheduleID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordScheduleID(aRecordScheduleID);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginEnableRecordSchedule(buf_aRecordScheduleID, functor);
}

int32_t STDCALL CpProxyUpnpOrgScheduledRecording2EndEnableRecordSchedule(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgScheduledRecording2SyncDisableRecordSchedule(THandle aHandle, const char* aRecordScheduleID)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
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

void STDCALL CpProxyUpnpOrgScheduledRecording2BeginDisableRecordSchedule(THandle aHandle, const char* aRecordScheduleID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordScheduleID(aRecordScheduleID);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginDisableRecordSchedule(buf_aRecordScheduleID, functor);
}

int32_t STDCALL CpProxyUpnpOrgScheduledRecording2EndDisableRecordSchedule(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgScheduledRecording2SyncDeleteRecordTask(THandle aHandle, const char* aRecordTaskID)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
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

void STDCALL CpProxyUpnpOrgScheduledRecording2BeginDeleteRecordTask(THandle aHandle, const char* aRecordTaskID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordTaskID(aRecordTaskID);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginDeleteRecordTask(buf_aRecordTaskID, functor);
}

int32_t STDCALL CpProxyUpnpOrgScheduledRecording2EndDeleteRecordTask(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgScheduledRecording2SyncGetRecordTask(THandle aHandle, const char* aRecordTaskID, const char* aFilter, char** aResult, uint32_t* aUpdateID)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
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

void STDCALL CpProxyUpnpOrgScheduledRecording2BeginGetRecordTask(THandle aHandle, const char* aRecordTaskID, const char* aFilter, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordTaskID(aRecordTaskID);
    Brh buf_aFilter(aFilter);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetRecordTask(buf_aRecordTaskID, buf_aFilter, functor);
}

int32_t STDCALL CpProxyUpnpOrgScheduledRecording2EndGetRecordTask(THandle aHandle, OhNetHandleAsync aAsync, char** aResult, uint32_t* aUpdateID)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgScheduledRecording2SyncEnableRecordTask(THandle aHandle, const char* aRecordTaskID)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
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

void STDCALL CpProxyUpnpOrgScheduledRecording2BeginEnableRecordTask(THandle aHandle, const char* aRecordTaskID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordTaskID(aRecordTaskID);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginEnableRecordTask(buf_aRecordTaskID, functor);
}

int32_t STDCALL CpProxyUpnpOrgScheduledRecording2EndEnableRecordTask(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgScheduledRecording2SyncDisableRecordTask(THandle aHandle, const char* aRecordTaskID)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
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

void STDCALL CpProxyUpnpOrgScheduledRecording2BeginDisableRecordTask(THandle aHandle, const char* aRecordTaskID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordTaskID(aRecordTaskID);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginDisableRecordTask(buf_aRecordTaskID, functor);
}

int32_t STDCALL CpProxyUpnpOrgScheduledRecording2EndDisableRecordTask(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgScheduledRecording2SyncResetRecordTask(THandle aHandle, const char* aRecordTaskID)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
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

void STDCALL CpProxyUpnpOrgScheduledRecording2BeginResetRecordTask(THandle aHandle, const char* aRecordTaskID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordTaskID(aRecordTaskID);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginResetRecordTask(buf_aRecordTaskID, functor);
}

int32_t STDCALL CpProxyUpnpOrgScheduledRecording2EndResetRecordTask(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgScheduledRecording2SyncGetRecordScheduleConflicts(THandle aHandle, const char* aRecordScheduleID, char** aRecordScheduleConflictIDList, uint32_t* aUpdateID)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
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

void STDCALL CpProxyUpnpOrgScheduledRecording2BeginGetRecordScheduleConflicts(THandle aHandle, const char* aRecordScheduleID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordScheduleID(aRecordScheduleID);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetRecordScheduleConflicts(buf_aRecordScheduleID, functor);
}

int32_t STDCALL CpProxyUpnpOrgScheduledRecording2EndGetRecordScheduleConflicts(THandle aHandle, OhNetHandleAsync aAsync, char** aRecordScheduleConflictIDList, uint32_t* aUpdateID)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgScheduledRecording2SyncGetRecordTaskConflicts(THandle aHandle, const char* aRecordTaskID, char** aRecordTaskConflictIDList, uint32_t* aUpdateID)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
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

void STDCALL CpProxyUpnpOrgScheduledRecording2BeginGetRecordTaskConflicts(THandle aHandle, const char* aRecordTaskID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordTaskID(aRecordTaskID);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetRecordTaskConflicts(buf_aRecordTaskID, functor);
}

int32_t STDCALL CpProxyUpnpOrgScheduledRecording2EndGetRecordTaskConflicts(THandle aHandle, OhNetHandleAsync aAsync, char** aRecordTaskConflictIDList, uint32_t* aUpdateID)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
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

void STDCALL CpProxyUpnpOrgScheduledRecording2SetPropertyLastChangeChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyLastChangeChanged(functor);
}

void STDCALL CpProxyUpnpOrgScheduledRecording2PropertyLastChange(THandle aHandle, char** aLastChange)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aLastChange;
    proxyC->PropertyLastChange(buf_aLastChange);
    *aLastChange = buf_aLastChange.Transfer();
}

