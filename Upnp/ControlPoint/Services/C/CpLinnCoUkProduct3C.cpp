#include "CpLinnCoUkProduct3.h"
#include <Core/CpDevice.h>
#include <C/CpProxyCPrivate.h>
#include <FunctorAsync.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <Exception.h>
#include <Functor.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Core/CpDevice.h>

using namespace Zapp;

class CpProxyLinnCoUkProduct3C : public CpProxyC
{
public:
    CpProxyLinnCoUkProduct3C(CpDeviceC aDevice);
    ~CpProxyLinnCoUkProduct3C();
    //CpProxyLinnCoUkProduct3* Proxy() { return static_cast<CpProxyLinnCoUkProduct3*>(iProxy); }

    void SyncType(Brh& aaType);
    void BeginType(FunctorAsync& aFunctor);
    void EndType(IAsync& aAsync, Brh& aaType);

    void SyncModel(Brh& aaModel);
    void BeginModel(FunctorAsync& aFunctor);
    void EndModel(IAsync& aAsync, Brh& aaModel);

    void SyncName(Brh& aaName);
    void BeginName(FunctorAsync& aFunctor);
    void EndName(IAsync& aAsync, Brh& aaName);

    void SyncSetName(const Brx& aaName);
    void BeginSetName(const Brx& aaName, FunctorAsync& aFunctor);
    void EndSetName(IAsync& aAsync);

    void SyncRoom(Brh& aaRoom);
    void BeginRoom(FunctorAsync& aFunctor);
    void EndRoom(IAsync& aAsync, Brh& aaRoom);

    void SyncSetRoom(const Brx& aaRoom);
    void BeginSetRoom(const Brx& aaRoom, FunctorAsync& aFunctor);
    void EndSetRoom(IAsync& aAsync);

    void SyncStandby(TBool& aaStandby);
    void BeginStandby(FunctorAsync& aFunctor);
    void EndStandby(IAsync& aAsync, TBool& aaStandby);

    void SyncSetStandby(TBool aaStandby);
    void BeginSetStandby(TBool aaStandby, FunctorAsync& aFunctor);
    void EndSetStandby(IAsync& aAsync);

    void SyncSourceCount(TUint& aaSourceCount);
    void BeginSourceCount(FunctorAsync& aFunctor);
    void EndSourceCount(IAsync& aAsync, TUint& aaSourceCount);

    void SyncSourceXml(Brh& aaSourceXml);
    void BeginSourceXml(FunctorAsync& aFunctor);
    void EndSourceXml(IAsync& aAsync, Brh& aaSourceXml);

    void SyncSourceIndex(TUint& aaSourceIndex);
    void BeginSourceIndex(FunctorAsync& aFunctor);
    void EndSourceIndex(IAsync& aAsync, TUint& aaSourceIndex);

    void SyncSetSourceIndex(TUint aaSourceIndex);
    void BeginSetSourceIndex(TUint aaSourceIndex, FunctorAsync& aFunctor);
    void EndSetSourceIndex(IAsync& aAsync);

    void SyncSetSourceIndexByName(const Brx& aaSourceName);
    void BeginSetSourceIndexByName(const Brx& aaSourceName, FunctorAsync& aFunctor);
    void EndSetSourceIndexByName(IAsync& aAsync);

    void SyncSetStartupSourceIndexByName(const Brx& aaSourceName);
    void BeginSetStartupSourceIndexByName(const Brx& aaSourceName, FunctorAsync& aFunctor);
    void EndSetStartupSourceIndexByName(IAsync& aAsync);

    void SyncStartupSourceIndex(TUint& aaSourceIndex);
    void BeginStartupSourceIndex(FunctorAsync& aFunctor);
    void EndStartupSourceIndex(IAsync& aAsync, TUint& aaSourceIndex);

    void SyncSetStartupSourceIndex(TUint aaSourceIndex);
    void BeginSetStartupSourceIndex(TUint aaSourceIndex, FunctorAsync& aFunctor);
    void EndSetStartupSourceIndex(IAsync& aAsync);

    void SyncStartupSourceEnabled(TBool& aaStartupSourceEnabled);
    void BeginStartupSourceEnabled(FunctorAsync& aFunctor);
    void EndStartupSourceEnabled(IAsync& aAsync, TBool& aaStartupSourceEnabled);

    void SyncSetStartupSourceEnabled(TBool aaStartupSourceEnabled);
    void BeginSetStartupSourceEnabled(TBool aaStartupSourceEnabled, FunctorAsync& aFunctor);
    void EndSetStartupSourceEnabled(IAsync& aAsync);

    void SyncSourceSystemName(TUint aaSourceIndex, Brh& aaSourceName);
    void BeginSourceSystemName(TUint aaSourceIndex, FunctorAsync& aFunctor);
    void EndSourceSystemName(IAsync& aAsync, Brh& aaSourceName);

    void SyncSourceName(TUint aaSourceIndex, Brh& aaSourceName);
    void BeginSourceName(TUint aaSourceIndex, FunctorAsync& aFunctor);
    void EndSourceName(IAsync& aAsync, Brh& aaSourceName);

    void SyncSetSourceName(TUint aaSourceIndex, const Brx& aaSourceName);
    void BeginSetSourceName(TUint aaSourceIndex, const Brx& aaSourceName, FunctorAsync& aFunctor);
    void EndSetSourceName(IAsync& aAsync);

    void SyncSourceType(TUint aaSourceIndex, Brh& aaSourceType);
    void BeginSourceType(TUint aaSourceIndex, FunctorAsync& aFunctor);
    void EndSourceType(IAsync& aAsync, Brh& aaSourceType);

    void SyncSourceVisible(TUint aaSourceIndex, TBool& aaSourceVisible);
    void BeginSourceVisible(TUint aaSourceIndex, FunctorAsync& aFunctor);
    void EndSourceVisible(IAsync& aAsync, TBool& aaSourceVisible);

    void SyncSetSourceVisible(TUint aaSourceIndex, TBool aaSourceVisible);
    void BeginSetSourceVisible(TUint aaSourceIndex, TBool aaSourceVisible, FunctorAsync& aFunctor);
    void EndSetSourceVisible(IAsync& aAsync);

    void SetPropertyProductTypeChanged(Functor& aFunctor);
    void SetPropertyProductModelChanged(Functor& aFunctor);
    void SetPropertyProductNameChanged(Functor& aFunctor);
    void SetPropertyProductRoomChanged(Functor& aFunctor);
    void SetPropertyProductStandbyChanged(Functor& aFunctor);
    void SetPropertyProductSourceIndexChanged(Functor& aFunctor);
    void SetPropertyProductSourceCountChanged(Functor& aFunctor);
    void SetPropertyProductSourceXmlChanged(Functor& aFunctor);
    void SetPropertyStartupSourceIndexChanged(Functor& aFunctor);
    void SetPropertyStartupSourceEnabledChanged(Functor& aFunctor);
    void SetPropertyProductAnySourceNameChanged(Functor& aFunctor);
    void SetPropertyProductAnySourceVisibleChanged(Functor& aFunctor);
    void SetPropertyProductAnySourceTypeChanged(Functor& aFunctor);

    void PropertyProductType(Brhz& aProductType) const;
    void PropertyProductModel(Brhz& aProductModel) const;
    void PropertyProductName(Brhz& aProductName) const;
    void PropertyProductRoom(Brhz& aProductRoom) const;
    void PropertyProductStandby(TBool& aProductStandby) const;
    void PropertyProductSourceIndex(TUint& aProductSourceIndex) const;
    void PropertyProductSourceCount(TUint& aProductSourceCount) const;
    void PropertyProductSourceXml(Brhz& aProductSourceXml) const;
    void PropertyStartupSourceIndex(TUint& aStartupSourceIndex) const;
    void PropertyStartupSourceEnabled(TBool& aStartupSourceEnabled) const;
    void PropertyProductAnySourceName(TUint& aProductAnySourceName) const;
    void PropertyProductAnySourceVisible(TUint& aProductAnySourceVisible) const;
    void PropertyProductAnySourceType(TUint& aProductAnySourceType) const;
private:
    void ProductTypePropertyChanged();
    void ProductModelPropertyChanged();
    void ProductNamePropertyChanged();
    void ProductRoomPropertyChanged();
    void ProductStandbyPropertyChanged();
    void ProductSourceIndexPropertyChanged();
    void ProductSourceCountPropertyChanged();
    void ProductSourceXmlPropertyChanged();
    void StartupSourceIndexPropertyChanged();
    void StartupSourceEnabledPropertyChanged();
    void ProductAnySourceNamePropertyChanged();
    void ProductAnySourceVisiblePropertyChanged();
    void ProductAnySourceTypePropertyChanged();
private:
    Mutex iLock;
    Action* iActionType;
    Action* iActionModel;
    Action* iActionName;
    Action* iActionSetName;
    Action* iActionRoom;
    Action* iActionSetRoom;
    Action* iActionStandby;
    Action* iActionSetStandby;
    Action* iActionSourceCount;
    Action* iActionSourceXml;
    Action* iActionSourceIndex;
    Action* iActionSetSourceIndex;
    Action* iActionSetSourceIndexByName;
    Action* iActionSetStartupSourceIndexByName;
    Action* iActionStartupSourceIndex;
    Action* iActionSetStartupSourceIndex;
    Action* iActionStartupSourceEnabled;
    Action* iActionSetStartupSourceEnabled;
    Action* iActionSourceSystemName;
    Action* iActionSourceName;
    Action* iActionSetSourceName;
    Action* iActionSourceType;
    Action* iActionSourceVisible;
    Action* iActionSetSourceVisible;
    PropertyString* iProductType;
    PropertyString* iProductModel;
    PropertyString* iProductName;
    PropertyString* iProductRoom;
    PropertyBool* iProductStandby;
    PropertyUint* iProductSourceIndex;
    PropertyUint* iProductSourceCount;
    PropertyString* iProductSourceXml;
    PropertyUint* iStartupSourceIndex;
    PropertyBool* iStartupSourceEnabled;
    PropertyUint* iProductAnySourceName;
    PropertyUint* iProductAnySourceVisible;
    PropertyUint* iProductAnySourceType;
    Functor iProductTypeChanged;
    Functor iProductModelChanged;
    Functor iProductNameChanged;
    Functor iProductRoomChanged;
    Functor iProductStandbyChanged;
    Functor iProductSourceIndexChanged;
    Functor iProductSourceCountChanged;
    Functor iProductSourceXmlChanged;
    Functor iStartupSourceIndexChanged;
    Functor iStartupSourceEnabledChanged;
    Functor iProductAnySourceNameChanged;
    Functor iProductAnySourceVisibleChanged;
    Functor iProductAnySourceTypeChanged;
};


class SyncTypeLinnCoUkProduct3C : public SyncProxyAction
{
public:
    SyncTypeLinnCoUkProduct3C(CpProxyLinnCoUkProduct3C& aProxy, Brh& aaType);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3C& iService;
    Brh& iaType;
};

SyncTypeLinnCoUkProduct3C::SyncTypeLinnCoUkProduct3C(CpProxyLinnCoUkProduct3C& aProxy, Brh& aaType)
    : iService(aProxy)
    , iaType(aaType)
{
}

void SyncTypeLinnCoUkProduct3C::CompleteRequest(IAsync& aAsync)
{
    iService.EndType(aAsync, iaType);
}


class SyncModelLinnCoUkProduct3C : public SyncProxyAction
{
public:
    SyncModelLinnCoUkProduct3C(CpProxyLinnCoUkProduct3C& aProxy, Brh& aaModel);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3C& iService;
    Brh& iaModel;
};

SyncModelLinnCoUkProduct3C::SyncModelLinnCoUkProduct3C(CpProxyLinnCoUkProduct3C& aProxy, Brh& aaModel)
    : iService(aProxy)
    , iaModel(aaModel)
{
}

void SyncModelLinnCoUkProduct3C::CompleteRequest(IAsync& aAsync)
{
    iService.EndModel(aAsync, iaModel);
}


class SyncNameLinnCoUkProduct3C : public SyncProxyAction
{
public:
    SyncNameLinnCoUkProduct3C(CpProxyLinnCoUkProduct3C& aProxy, Brh& aaName);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3C& iService;
    Brh& iaName;
};

SyncNameLinnCoUkProduct3C::SyncNameLinnCoUkProduct3C(CpProxyLinnCoUkProduct3C& aProxy, Brh& aaName)
    : iService(aProxy)
    , iaName(aaName)
{
}

void SyncNameLinnCoUkProduct3C::CompleteRequest(IAsync& aAsync)
{
    iService.EndName(aAsync, iaName);
}


class SyncSetNameLinnCoUkProduct3C : public SyncProxyAction
{
public:
    SyncSetNameLinnCoUkProduct3C(CpProxyLinnCoUkProduct3C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3C& iService;
};

SyncSetNameLinnCoUkProduct3C::SyncSetNameLinnCoUkProduct3C(CpProxyLinnCoUkProduct3C& aProxy)
    : iService(aProxy)
{
}

void SyncSetNameLinnCoUkProduct3C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetName(aAsync);
}


class SyncRoomLinnCoUkProduct3C : public SyncProxyAction
{
public:
    SyncRoomLinnCoUkProduct3C(CpProxyLinnCoUkProduct3C& aProxy, Brh& aaRoom);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3C& iService;
    Brh& iaRoom;
};

SyncRoomLinnCoUkProduct3C::SyncRoomLinnCoUkProduct3C(CpProxyLinnCoUkProduct3C& aProxy, Brh& aaRoom)
    : iService(aProxy)
    , iaRoom(aaRoom)
{
}

void SyncRoomLinnCoUkProduct3C::CompleteRequest(IAsync& aAsync)
{
    iService.EndRoom(aAsync, iaRoom);
}


class SyncSetRoomLinnCoUkProduct3C : public SyncProxyAction
{
public:
    SyncSetRoomLinnCoUkProduct3C(CpProxyLinnCoUkProduct3C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3C& iService;
};

SyncSetRoomLinnCoUkProduct3C::SyncSetRoomLinnCoUkProduct3C(CpProxyLinnCoUkProduct3C& aProxy)
    : iService(aProxy)
{
}

void SyncSetRoomLinnCoUkProduct3C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetRoom(aAsync);
}


class SyncStandbyLinnCoUkProduct3C : public SyncProxyAction
{
public:
    SyncStandbyLinnCoUkProduct3C(CpProxyLinnCoUkProduct3C& aProxy, TBool& aaStandby);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3C& iService;
    TBool& iaStandby;
};

SyncStandbyLinnCoUkProduct3C::SyncStandbyLinnCoUkProduct3C(CpProxyLinnCoUkProduct3C& aProxy, TBool& aaStandby)
    : iService(aProxy)
    , iaStandby(aaStandby)
{
}

void SyncStandbyLinnCoUkProduct3C::CompleteRequest(IAsync& aAsync)
{
    iService.EndStandby(aAsync, iaStandby);
}


class SyncSetStandbyLinnCoUkProduct3C : public SyncProxyAction
{
public:
    SyncSetStandbyLinnCoUkProduct3C(CpProxyLinnCoUkProduct3C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3C& iService;
};

SyncSetStandbyLinnCoUkProduct3C::SyncSetStandbyLinnCoUkProduct3C(CpProxyLinnCoUkProduct3C& aProxy)
    : iService(aProxy)
{
}

void SyncSetStandbyLinnCoUkProduct3C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetStandby(aAsync);
}


class SyncSourceCountLinnCoUkProduct3C : public SyncProxyAction
{
public:
    SyncSourceCountLinnCoUkProduct3C(CpProxyLinnCoUkProduct3C& aProxy, TUint& aaSourceCount);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3C& iService;
    TUint& iaSourceCount;
};

SyncSourceCountLinnCoUkProduct3C::SyncSourceCountLinnCoUkProduct3C(CpProxyLinnCoUkProduct3C& aProxy, TUint& aaSourceCount)
    : iService(aProxy)
    , iaSourceCount(aaSourceCount)
{
}

void SyncSourceCountLinnCoUkProduct3C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSourceCount(aAsync, iaSourceCount);
}


class SyncSourceXmlLinnCoUkProduct3C : public SyncProxyAction
{
public:
    SyncSourceXmlLinnCoUkProduct3C(CpProxyLinnCoUkProduct3C& aProxy, Brh& aaSourceXml);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3C& iService;
    Brh& iaSourceXml;
};

SyncSourceXmlLinnCoUkProduct3C::SyncSourceXmlLinnCoUkProduct3C(CpProxyLinnCoUkProduct3C& aProxy, Brh& aaSourceXml)
    : iService(aProxy)
    , iaSourceXml(aaSourceXml)
{
}

void SyncSourceXmlLinnCoUkProduct3C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSourceXml(aAsync, iaSourceXml);
}


class SyncSourceIndexLinnCoUkProduct3C : public SyncProxyAction
{
public:
    SyncSourceIndexLinnCoUkProduct3C(CpProxyLinnCoUkProduct3C& aProxy, TUint& aaSourceIndex);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3C& iService;
    TUint& iaSourceIndex;
};

SyncSourceIndexLinnCoUkProduct3C::SyncSourceIndexLinnCoUkProduct3C(CpProxyLinnCoUkProduct3C& aProxy, TUint& aaSourceIndex)
    : iService(aProxy)
    , iaSourceIndex(aaSourceIndex)
{
}

void SyncSourceIndexLinnCoUkProduct3C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSourceIndex(aAsync, iaSourceIndex);
}


class SyncSetSourceIndexLinnCoUkProduct3C : public SyncProxyAction
{
public:
    SyncSetSourceIndexLinnCoUkProduct3C(CpProxyLinnCoUkProduct3C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3C& iService;
};

SyncSetSourceIndexLinnCoUkProduct3C::SyncSetSourceIndexLinnCoUkProduct3C(CpProxyLinnCoUkProduct3C& aProxy)
    : iService(aProxy)
{
}

void SyncSetSourceIndexLinnCoUkProduct3C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetSourceIndex(aAsync);
}


class SyncSetSourceIndexByNameLinnCoUkProduct3C : public SyncProxyAction
{
public:
    SyncSetSourceIndexByNameLinnCoUkProduct3C(CpProxyLinnCoUkProduct3C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3C& iService;
};

SyncSetSourceIndexByNameLinnCoUkProduct3C::SyncSetSourceIndexByNameLinnCoUkProduct3C(CpProxyLinnCoUkProduct3C& aProxy)
    : iService(aProxy)
{
}

void SyncSetSourceIndexByNameLinnCoUkProduct3C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetSourceIndexByName(aAsync);
}


class SyncSetStartupSourceIndexByNameLinnCoUkProduct3C : public SyncProxyAction
{
public:
    SyncSetStartupSourceIndexByNameLinnCoUkProduct3C(CpProxyLinnCoUkProduct3C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3C& iService;
};

SyncSetStartupSourceIndexByNameLinnCoUkProduct3C::SyncSetStartupSourceIndexByNameLinnCoUkProduct3C(CpProxyLinnCoUkProduct3C& aProxy)
    : iService(aProxy)
{
}

void SyncSetStartupSourceIndexByNameLinnCoUkProduct3C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetStartupSourceIndexByName(aAsync);
}


class SyncStartupSourceIndexLinnCoUkProduct3C : public SyncProxyAction
{
public:
    SyncStartupSourceIndexLinnCoUkProduct3C(CpProxyLinnCoUkProduct3C& aProxy, TUint& aaSourceIndex);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3C& iService;
    TUint& iaSourceIndex;
};

SyncStartupSourceIndexLinnCoUkProduct3C::SyncStartupSourceIndexLinnCoUkProduct3C(CpProxyLinnCoUkProduct3C& aProxy, TUint& aaSourceIndex)
    : iService(aProxy)
    , iaSourceIndex(aaSourceIndex)
{
}

void SyncStartupSourceIndexLinnCoUkProduct3C::CompleteRequest(IAsync& aAsync)
{
    iService.EndStartupSourceIndex(aAsync, iaSourceIndex);
}


class SyncSetStartupSourceIndexLinnCoUkProduct3C : public SyncProxyAction
{
public:
    SyncSetStartupSourceIndexLinnCoUkProduct3C(CpProxyLinnCoUkProduct3C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3C& iService;
};

SyncSetStartupSourceIndexLinnCoUkProduct3C::SyncSetStartupSourceIndexLinnCoUkProduct3C(CpProxyLinnCoUkProduct3C& aProxy)
    : iService(aProxy)
{
}

void SyncSetStartupSourceIndexLinnCoUkProduct3C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetStartupSourceIndex(aAsync);
}


class SyncStartupSourceEnabledLinnCoUkProduct3C : public SyncProxyAction
{
public:
    SyncStartupSourceEnabledLinnCoUkProduct3C(CpProxyLinnCoUkProduct3C& aProxy, TBool& aaStartupSourceEnabled);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3C& iService;
    TBool& iaStartupSourceEnabled;
};

SyncStartupSourceEnabledLinnCoUkProduct3C::SyncStartupSourceEnabledLinnCoUkProduct3C(CpProxyLinnCoUkProduct3C& aProxy, TBool& aaStartupSourceEnabled)
    : iService(aProxy)
    , iaStartupSourceEnabled(aaStartupSourceEnabled)
{
}

void SyncStartupSourceEnabledLinnCoUkProduct3C::CompleteRequest(IAsync& aAsync)
{
    iService.EndStartupSourceEnabled(aAsync, iaStartupSourceEnabled);
}


class SyncSetStartupSourceEnabledLinnCoUkProduct3C : public SyncProxyAction
{
public:
    SyncSetStartupSourceEnabledLinnCoUkProduct3C(CpProxyLinnCoUkProduct3C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3C& iService;
};

SyncSetStartupSourceEnabledLinnCoUkProduct3C::SyncSetStartupSourceEnabledLinnCoUkProduct3C(CpProxyLinnCoUkProduct3C& aProxy)
    : iService(aProxy)
{
}

void SyncSetStartupSourceEnabledLinnCoUkProduct3C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetStartupSourceEnabled(aAsync);
}


class SyncSourceSystemNameLinnCoUkProduct3C : public SyncProxyAction
{
public:
    SyncSourceSystemNameLinnCoUkProduct3C(CpProxyLinnCoUkProduct3C& aProxy, Brh& aaSourceName);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3C& iService;
    Brh& iaSourceName;
};

SyncSourceSystemNameLinnCoUkProduct3C::SyncSourceSystemNameLinnCoUkProduct3C(CpProxyLinnCoUkProduct3C& aProxy, Brh& aaSourceName)
    : iService(aProxy)
    , iaSourceName(aaSourceName)
{
}

void SyncSourceSystemNameLinnCoUkProduct3C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSourceSystemName(aAsync, iaSourceName);
}


class SyncSourceNameLinnCoUkProduct3C : public SyncProxyAction
{
public:
    SyncSourceNameLinnCoUkProduct3C(CpProxyLinnCoUkProduct3C& aProxy, Brh& aaSourceName);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3C& iService;
    Brh& iaSourceName;
};

SyncSourceNameLinnCoUkProduct3C::SyncSourceNameLinnCoUkProduct3C(CpProxyLinnCoUkProduct3C& aProxy, Brh& aaSourceName)
    : iService(aProxy)
    , iaSourceName(aaSourceName)
{
}

void SyncSourceNameLinnCoUkProduct3C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSourceName(aAsync, iaSourceName);
}


class SyncSetSourceNameLinnCoUkProduct3C : public SyncProxyAction
{
public:
    SyncSetSourceNameLinnCoUkProduct3C(CpProxyLinnCoUkProduct3C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3C& iService;
};

SyncSetSourceNameLinnCoUkProduct3C::SyncSetSourceNameLinnCoUkProduct3C(CpProxyLinnCoUkProduct3C& aProxy)
    : iService(aProxy)
{
}

void SyncSetSourceNameLinnCoUkProduct3C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetSourceName(aAsync);
}


class SyncSourceTypeLinnCoUkProduct3C : public SyncProxyAction
{
public:
    SyncSourceTypeLinnCoUkProduct3C(CpProxyLinnCoUkProduct3C& aProxy, Brh& aaSourceType);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3C& iService;
    Brh& iaSourceType;
};

SyncSourceTypeLinnCoUkProduct3C::SyncSourceTypeLinnCoUkProduct3C(CpProxyLinnCoUkProduct3C& aProxy, Brh& aaSourceType)
    : iService(aProxy)
    , iaSourceType(aaSourceType)
{
}

void SyncSourceTypeLinnCoUkProduct3C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSourceType(aAsync, iaSourceType);
}


class SyncSourceVisibleLinnCoUkProduct3C : public SyncProxyAction
{
public:
    SyncSourceVisibleLinnCoUkProduct3C(CpProxyLinnCoUkProduct3C& aProxy, TBool& aaSourceVisible);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3C& iService;
    TBool& iaSourceVisible;
};

SyncSourceVisibleLinnCoUkProduct3C::SyncSourceVisibleLinnCoUkProduct3C(CpProxyLinnCoUkProduct3C& aProxy, TBool& aaSourceVisible)
    : iService(aProxy)
    , iaSourceVisible(aaSourceVisible)
{
}

void SyncSourceVisibleLinnCoUkProduct3C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSourceVisible(aAsync, iaSourceVisible);
}


class SyncSetSourceVisibleLinnCoUkProduct3C : public SyncProxyAction
{
public:
    SyncSetSourceVisibleLinnCoUkProduct3C(CpProxyLinnCoUkProduct3C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3C& iService;
};

SyncSetSourceVisibleLinnCoUkProduct3C::SyncSetSourceVisibleLinnCoUkProduct3C(CpProxyLinnCoUkProduct3C& aProxy)
    : iService(aProxy)
{
}

void SyncSetSourceVisibleLinnCoUkProduct3C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetSourceVisible(aAsync);
}

CpProxyLinnCoUkProduct3C::CpProxyLinnCoUkProduct3C(CpDeviceC aDevice)
    : CpProxyC("linn-co-uk", "Product", 3, *reinterpret_cast<CpiDevice*>(aDevice))
    , iLock("MPCS")
{
    Zapp::Parameter* param;

    iActionType = new Action("Type");
    param = new Zapp::ParameterString("aType");
    iActionType->AddOutputParameter(param);

    iActionModel = new Action("Model");
    param = new Zapp::ParameterString("aModel");
    iActionModel->AddOutputParameter(param);

    iActionName = new Action("Name");
    param = new Zapp::ParameterString("aName");
    iActionName->AddOutputParameter(param);

    iActionSetName = new Action("SetName");
    param = new Zapp::ParameterString("aName");
    iActionSetName->AddInputParameter(param);

    iActionRoom = new Action("Room");
    param = new Zapp::ParameterString("aRoom");
    iActionRoom->AddOutputParameter(param);

    iActionSetRoom = new Action("SetRoom");
    param = new Zapp::ParameterString("aRoom");
    iActionSetRoom->AddInputParameter(param);

    iActionStandby = new Action("Standby");
    param = new Zapp::ParameterBool("aStandby");
    iActionStandby->AddOutputParameter(param);

    iActionSetStandby = new Action("SetStandby");
    param = new Zapp::ParameterBool("aStandby");
    iActionSetStandby->AddInputParameter(param);

    iActionSourceCount = new Action("SourceCount");
    param = new Zapp::ParameterUint("aSourceCount");
    iActionSourceCount->AddOutputParameter(param);

    iActionSourceXml = new Action("SourceXml");
    param = new Zapp::ParameterString("aSourceXml");
    iActionSourceXml->AddOutputParameter(param);

    iActionSourceIndex = new Action("SourceIndex");
    param = new Zapp::ParameterUint("aSourceIndex");
    iActionSourceIndex->AddOutputParameter(param);

    iActionSetSourceIndex = new Action("SetSourceIndex");
    param = new Zapp::ParameterUint("aSourceIndex");
    iActionSetSourceIndex->AddInputParameter(param);

    iActionSetSourceIndexByName = new Action("SetSourceIndexByName");
    param = new Zapp::ParameterString("aSourceName");
    iActionSetSourceIndexByName->AddInputParameter(param);

    iActionSetStartupSourceIndexByName = new Action("SetStartupSourceIndexByName");
    param = new Zapp::ParameterString("aSourceName");
    iActionSetStartupSourceIndexByName->AddInputParameter(param);

    iActionStartupSourceIndex = new Action("StartupSourceIndex");
    param = new Zapp::ParameterUint("aSourceIndex");
    iActionStartupSourceIndex->AddOutputParameter(param);

    iActionSetStartupSourceIndex = new Action("SetStartupSourceIndex");
    param = new Zapp::ParameterUint("aSourceIndex");
    iActionSetStartupSourceIndex->AddInputParameter(param);

    iActionStartupSourceEnabled = new Action("StartupSourceEnabled");
    param = new Zapp::ParameterBool("aStartupSourceEnabled");
    iActionStartupSourceEnabled->AddOutputParameter(param);

    iActionSetStartupSourceEnabled = new Action("SetStartupSourceEnabled");
    param = new Zapp::ParameterBool("aStartupSourceEnabled");
    iActionSetStartupSourceEnabled->AddInputParameter(param);

    iActionSourceSystemName = new Action("SourceSystemName");
    param = new Zapp::ParameterUint("aSourceIndex");
    iActionSourceSystemName->AddInputParameter(param);
    param = new Zapp::ParameterString("aSourceName");
    iActionSourceSystemName->AddOutputParameter(param);

    iActionSourceName = new Action("SourceName");
    param = new Zapp::ParameterUint("aSourceIndex");
    iActionSourceName->AddInputParameter(param);
    param = new Zapp::ParameterString("aSourceName");
    iActionSourceName->AddOutputParameter(param);

    iActionSetSourceName = new Action("SetSourceName");
    param = new Zapp::ParameterUint("aSourceIndex");
    iActionSetSourceName->AddInputParameter(param);
    param = new Zapp::ParameterString("aSourceName");
    iActionSetSourceName->AddInputParameter(param);

    iActionSourceType = new Action("SourceType");
    param = new Zapp::ParameterUint("aSourceIndex");
    iActionSourceType->AddInputParameter(param);
    param = new Zapp::ParameterString("aSourceType");
    iActionSourceType->AddOutputParameter(param);

    iActionSourceVisible = new Action("SourceVisible");
    param = new Zapp::ParameterUint("aSourceIndex");
    iActionSourceVisible->AddInputParameter(param);
    param = new Zapp::ParameterBool("aSourceVisible");
    iActionSourceVisible->AddOutputParameter(param);

    iActionSetSourceVisible = new Action("SetSourceVisible");
    param = new Zapp::ParameterUint("aSourceIndex");
    iActionSetSourceVisible->AddInputParameter(param);
    param = new Zapp::ParameterBool("aSourceVisible");
    iActionSetSourceVisible->AddInputParameter(param);

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProduct3C::ProductTypePropertyChanged);
    iProductType = new PropertyString("ProductType", functor);
    AddProperty(iProductType);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProduct3C::ProductModelPropertyChanged);
    iProductModel = new PropertyString("ProductModel", functor);
    AddProperty(iProductModel);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProduct3C::ProductNamePropertyChanged);
    iProductName = new PropertyString("ProductName", functor);
    AddProperty(iProductName);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProduct3C::ProductRoomPropertyChanged);
    iProductRoom = new PropertyString("ProductRoom", functor);
    AddProperty(iProductRoom);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProduct3C::ProductStandbyPropertyChanged);
    iProductStandby = new PropertyBool("ProductStandby", functor);
    AddProperty(iProductStandby);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProduct3C::ProductSourceIndexPropertyChanged);
    iProductSourceIndex = new PropertyUint("ProductSourceIndex", functor);
    AddProperty(iProductSourceIndex);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProduct3C::ProductSourceCountPropertyChanged);
    iProductSourceCount = new PropertyUint("ProductSourceCount", functor);
    AddProperty(iProductSourceCount);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProduct3C::ProductSourceXmlPropertyChanged);
    iProductSourceXml = new PropertyString("ProductSourceXml", functor);
    AddProperty(iProductSourceXml);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProduct3C::StartupSourceIndexPropertyChanged);
    iStartupSourceIndex = new PropertyUint("StartupSourceIndex", functor);
    AddProperty(iStartupSourceIndex);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProduct3C::StartupSourceEnabledPropertyChanged);
    iStartupSourceEnabled = new PropertyBool("StartupSourceEnabled", functor);
    AddProperty(iStartupSourceEnabled);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProduct3C::ProductAnySourceNamePropertyChanged);
    iProductAnySourceName = new PropertyUint("ProductAnySourceName", functor);
    AddProperty(iProductAnySourceName);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProduct3C::ProductAnySourceVisiblePropertyChanged);
    iProductAnySourceVisible = new PropertyUint("ProductAnySourceVisible", functor);
    AddProperty(iProductAnySourceVisible);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProduct3C::ProductAnySourceTypePropertyChanged);
    iProductAnySourceType = new PropertyUint("ProductAnySourceType", functor);
    AddProperty(iProductAnySourceType);
}

CpProxyLinnCoUkProduct3C::~CpProxyLinnCoUkProduct3C()
{
    DestroyService();
    delete iActionType;
    delete iActionModel;
    delete iActionName;
    delete iActionSetName;
    delete iActionRoom;
    delete iActionSetRoom;
    delete iActionStandby;
    delete iActionSetStandby;
    delete iActionSourceCount;
    delete iActionSourceXml;
    delete iActionSourceIndex;
    delete iActionSetSourceIndex;
    delete iActionSetSourceIndexByName;
    delete iActionSetStartupSourceIndexByName;
    delete iActionStartupSourceIndex;
    delete iActionSetStartupSourceIndex;
    delete iActionStartupSourceEnabled;
    delete iActionSetStartupSourceEnabled;
    delete iActionSourceSystemName;
    delete iActionSourceName;
    delete iActionSetSourceName;
    delete iActionSourceType;
    delete iActionSourceVisible;
    delete iActionSetSourceVisible;
}

void CpProxyLinnCoUkProduct3C::SyncType(Brh& aaType)
{
    SyncTypeLinnCoUkProduct3C sync(*this, aaType);
    BeginType(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3C::BeginType(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionType, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionType->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkProduct3C::EndType(IAsync& aAsync, Brh& aaType)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Type"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aaType);
}

void CpProxyLinnCoUkProduct3C::SyncModel(Brh& aaModel)
{
    SyncModelLinnCoUkProduct3C sync(*this, aaModel);
    BeginModel(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3C::BeginModel(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionModel, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionModel->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkProduct3C::EndModel(IAsync& aAsync, Brh& aaModel)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Model"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aaModel);
}

void CpProxyLinnCoUkProduct3C::SyncName(Brh& aaName)
{
    SyncNameLinnCoUkProduct3C sync(*this, aaName);
    BeginName(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3C::BeginName(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionName, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionName->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkProduct3C::EndName(IAsync& aAsync, Brh& aaName)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Name"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aaName);
}

void CpProxyLinnCoUkProduct3C::SyncSetName(const Brx& aaName)
{
    SyncSetNameLinnCoUkProduct3C sync(*this);
    BeginSetName(aaName, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3C::BeginSetName(const Brx& aaName, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetName, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetName->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aaName));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkProduct3C::EndSetName(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetName"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkProduct3C::SyncRoom(Brh& aaRoom)
{
    SyncRoomLinnCoUkProduct3C sync(*this, aaRoom);
    BeginRoom(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3C::BeginRoom(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionRoom, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionRoom->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkProduct3C::EndRoom(IAsync& aAsync, Brh& aaRoom)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Room"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aaRoom);
}

void CpProxyLinnCoUkProduct3C::SyncSetRoom(const Brx& aaRoom)
{
    SyncSetRoomLinnCoUkProduct3C sync(*this);
    BeginSetRoom(aaRoom, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3C::BeginSetRoom(const Brx& aaRoom, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetRoom, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetRoom->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aaRoom));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkProduct3C::EndSetRoom(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetRoom"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkProduct3C::SyncStandby(TBool& aaStandby)
{
    SyncStandbyLinnCoUkProduct3C sync(*this, aaStandby);
    BeginStandby(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3C::BeginStandby(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionStandby, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionStandby->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkProduct3C::EndStandby(IAsync& aAsync, TBool& aaStandby)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Standby"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aaStandby = ((ArgumentBool*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyLinnCoUkProduct3C::SyncSetStandby(TBool aaStandby)
{
    SyncSetStandbyLinnCoUkProduct3C sync(*this);
    BeginSetStandby(aaStandby, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3C::BeginSetStandby(TBool aaStandby, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetStandby, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetStandby->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aaStandby));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkProduct3C::EndSetStandby(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetStandby"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkProduct3C::SyncSourceCount(TUint& aaSourceCount)
{
    SyncSourceCountLinnCoUkProduct3C sync(*this, aaSourceCount);
    BeginSourceCount(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3C::BeginSourceCount(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSourceCount, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionSourceCount->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkProduct3C::EndSourceCount(IAsync& aAsync, TUint& aaSourceCount)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SourceCount"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aaSourceCount = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyLinnCoUkProduct3C::SyncSourceXml(Brh& aaSourceXml)
{
    SyncSourceXmlLinnCoUkProduct3C sync(*this, aaSourceXml);
    BeginSourceXml(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3C::BeginSourceXml(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSourceXml, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionSourceXml->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkProduct3C::EndSourceXml(IAsync& aAsync, Brh& aaSourceXml)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SourceXml"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aaSourceXml);
}

void CpProxyLinnCoUkProduct3C::SyncSourceIndex(TUint& aaSourceIndex)
{
    SyncSourceIndexLinnCoUkProduct3C sync(*this, aaSourceIndex);
    BeginSourceIndex(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3C::BeginSourceIndex(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSourceIndex, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionSourceIndex->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkProduct3C::EndSourceIndex(IAsync& aAsync, TUint& aaSourceIndex)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SourceIndex"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aaSourceIndex = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyLinnCoUkProduct3C::SyncSetSourceIndex(TUint aaSourceIndex)
{
    SyncSetSourceIndexLinnCoUkProduct3C sync(*this);
    BeginSetSourceIndex(aaSourceIndex, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3C::BeginSetSourceIndex(TUint aaSourceIndex, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetSourceIndex, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetSourceIndex->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaSourceIndex));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkProduct3C::EndSetSourceIndex(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetSourceIndex"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkProduct3C::SyncSetSourceIndexByName(const Brx& aaSourceName)
{
    SyncSetSourceIndexByNameLinnCoUkProduct3C sync(*this);
    BeginSetSourceIndexByName(aaSourceName, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3C::BeginSetSourceIndexByName(const Brx& aaSourceName, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetSourceIndexByName, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetSourceIndexByName->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aaSourceName));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkProduct3C::EndSetSourceIndexByName(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetSourceIndexByName"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkProduct3C::SyncSetStartupSourceIndexByName(const Brx& aaSourceName)
{
    SyncSetStartupSourceIndexByNameLinnCoUkProduct3C sync(*this);
    BeginSetStartupSourceIndexByName(aaSourceName, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3C::BeginSetStartupSourceIndexByName(const Brx& aaSourceName, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetStartupSourceIndexByName, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetStartupSourceIndexByName->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aaSourceName));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkProduct3C::EndSetStartupSourceIndexByName(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetStartupSourceIndexByName"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkProduct3C::SyncStartupSourceIndex(TUint& aaSourceIndex)
{
    SyncStartupSourceIndexLinnCoUkProduct3C sync(*this, aaSourceIndex);
    BeginStartupSourceIndex(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3C::BeginStartupSourceIndex(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionStartupSourceIndex, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionStartupSourceIndex->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkProduct3C::EndStartupSourceIndex(IAsync& aAsync, TUint& aaSourceIndex)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("StartupSourceIndex"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aaSourceIndex = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyLinnCoUkProduct3C::SyncSetStartupSourceIndex(TUint aaSourceIndex)
{
    SyncSetStartupSourceIndexLinnCoUkProduct3C sync(*this);
    BeginSetStartupSourceIndex(aaSourceIndex, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3C::BeginSetStartupSourceIndex(TUint aaSourceIndex, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetStartupSourceIndex, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetStartupSourceIndex->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaSourceIndex));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkProduct3C::EndSetStartupSourceIndex(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetStartupSourceIndex"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkProduct3C::SyncStartupSourceEnabled(TBool& aaStartupSourceEnabled)
{
    SyncStartupSourceEnabledLinnCoUkProduct3C sync(*this, aaStartupSourceEnabled);
    BeginStartupSourceEnabled(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3C::BeginStartupSourceEnabled(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionStartupSourceEnabled, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionStartupSourceEnabled->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkProduct3C::EndStartupSourceEnabled(IAsync& aAsync, TBool& aaStartupSourceEnabled)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("StartupSourceEnabled"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aaStartupSourceEnabled = ((ArgumentBool*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyLinnCoUkProduct3C::SyncSetStartupSourceEnabled(TBool aaStartupSourceEnabled)
{
    SyncSetStartupSourceEnabledLinnCoUkProduct3C sync(*this);
    BeginSetStartupSourceEnabled(aaStartupSourceEnabled, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3C::BeginSetStartupSourceEnabled(TBool aaStartupSourceEnabled, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetStartupSourceEnabled, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetStartupSourceEnabled->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aaStartupSourceEnabled));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkProduct3C::EndSetStartupSourceEnabled(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetStartupSourceEnabled"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkProduct3C::SyncSourceSystemName(TUint aaSourceIndex, Brh& aaSourceName)
{
    SyncSourceSystemNameLinnCoUkProduct3C sync(*this, aaSourceName);
    BeginSourceSystemName(aaSourceIndex, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3C::BeginSourceSystemName(TUint aaSourceIndex, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSourceSystemName, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSourceSystemName->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaSourceIndex));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionSourceSystemName->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkProduct3C::EndSourceSystemName(IAsync& aAsync, Brh& aaSourceName)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SourceSystemName"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aaSourceName);
}

void CpProxyLinnCoUkProduct3C::SyncSourceName(TUint aaSourceIndex, Brh& aaSourceName)
{
    SyncSourceNameLinnCoUkProduct3C sync(*this, aaSourceName);
    BeginSourceName(aaSourceIndex, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3C::BeginSourceName(TUint aaSourceIndex, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSourceName, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSourceName->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaSourceIndex));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionSourceName->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkProduct3C::EndSourceName(IAsync& aAsync, Brh& aaSourceName)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SourceName"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aaSourceName);
}

void CpProxyLinnCoUkProduct3C::SyncSetSourceName(TUint aaSourceIndex, const Brx& aaSourceName)
{
    SyncSetSourceNameLinnCoUkProduct3C sync(*this);
    BeginSetSourceName(aaSourceIndex, aaSourceName, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3C::BeginSetSourceName(TUint aaSourceIndex, const Brx& aaSourceName, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetSourceName, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetSourceName->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaSourceIndex));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aaSourceName));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkProduct3C::EndSetSourceName(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetSourceName"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkProduct3C::SyncSourceType(TUint aaSourceIndex, Brh& aaSourceType)
{
    SyncSourceTypeLinnCoUkProduct3C sync(*this, aaSourceType);
    BeginSourceType(aaSourceIndex, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3C::BeginSourceType(TUint aaSourceIndex, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSourceType, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSourceType->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaSourceIndex));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionSourceType->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkProduct3C::EndSourceType(IAsync& aAsync, Brh& aaSourceType)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SourceType"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aaSourceType);
}

void CpProxyLinnCoUkProduct3C::SyncSourceVisible(TUint aaSourceIndex, TBool& aaSourceVisible)
{
    SyncSourceVisibleLinnCoUkProduct3C sync(*this, aaSourceVisible);
    BeginSourceVisible(aaSourceIndex, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3C::BeginSourceVisible(TUint aaSourceIndex, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSourceVisible, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSourceVisible->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaSourceIndex));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionSourceVisible->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkProduct3C::EndSourceVisible(IAsync& aAsync, TBool& aaSourceVisible)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SourceVisible"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aaSourceVisible = ((ArgumentBool*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyLinnCoUkProduct3C::SyncSetSourceVisible(TUint aaSourceIndex, TBool aaSourceVisible)
{
    SyncSetSourceVisibleLinnCoUkProduct3C sync(*this);
    BeginSetSourceVisible(aaSourceIndex, aaSourceVisible, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3C::BeginSetSourceVisible(TUint aaSourceIndex, TBool aaSourceVisible, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetSourceVisible, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetSourceVisible->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaSourceIndex));
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aaSourceVisible));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkProduct3C::EndSetSourceVisible(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetSourceVisible"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkProduct3C::SetPropertyProductTypeChanged(Functor& aFunctor)
{
    iLock.Wait();
    iProductTypeChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkProduct3C::SetPropertyProductModelChanged(Functor& aFunctor)
{
    iLock.Wait();
    iProductModelChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkProduct3C::SetPropertyProductNameChanged(Functor& aFunctor)
{
    iLock.Wait();
    iProductNameChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkProduct3C::SetPropertyProductRoomChanged(Functor& aFunctor)
{
    iLock.Wait();
    iProductRoomChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkProduct3C::SetPropertyProductStandbyChanged(Functor& aFunctor)
{
    iLock.Wait();
    iProductStandbyChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkProduct3C::SetPropertyProductSourceIndexChanged(Functor& aFunctor)
{
    iLock.Wait();
    iProductSourceIndexChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkProduct3C::SetPropertyProductSourceCountChanged(Functor& aFunctor)
{
    iLock.Wait();
    iProductSourceCountChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkProduct3C::SetPropertyProductSourceXmlChanged(Functor& aFunctor)
{
    iLock.Wait();
    iProductSourceXmlChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkProduct3C::SetPropertyStartupSourceIndexChanged(Functor& aFunctor)
{
    iLock.Wait();
    iStartupSourceIndexChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkProduct3C::SetPropertyStartupSourceEnabledChanged(Functor& aFunctor)
{
    iLock.Wait();
    iStartupSourceEnabledChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkProduct3C::SetPropertyProductAnySourceNameChanged(Functor& aFunctor)
{
    iLock.Wait();
    iProductAnySourceNameChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkProduct3C::SetPropertyProductAnySourceVisibleChanged(Functor& aFunctor)
{
    iLock.Wait();
    iProductAnySourceVisibleChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkProduct3C::SetPropertyProductAnySourceTypeChanged(Functor& aFunctor)
{
    iLock.Wait();
    iProductAnySourceTypeChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkProduct3C::PropertyProductType(Brhz& aProductType) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aProductType.Set(iProductType->Value());
    PropertyReadUnlock();
}

void CpProxyLinnCoUkProduct3C::PropertyProductModel(Brhz& aProductModel) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aProductModel.Set(iProductModel->Value());
    PropertyReadUnlock();
}

void CpProxyLinnCoUkProduct3C::PropertyProductName(Brhz& aProductName) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aProductName.Set(iProductName->Value());
    PropertyReadUnlock();
}

void CpProxyLinnCoUkProduct3C::PropertyProductRoom(Brhz& aProductRoom) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aProductRoom.Set(iProductRoom->Value());
    PropertyReadUnlock();
}

void CpProxyLinnCoUkProduct3C::PropertyProductStandby(TBool& aProductStandby) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aProductStandby = iProductStandby->Value();
    PropertyReadUnlock();
}

void CpProxyLinnCoUkProduct3C::PropertyProductSourceIndex(TUint& aProductSourceIndex) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aProductSourceIndex = iProductSourceIndex->Value();
    PropertyReadUnlock();
}

void CpProxyLinnCoUkProduct3C::PropertyProductSourceCount(TUint& aProductSourceCount) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aProductSourceCount = iProductSourceCount->Value();
    PropertyReadUnlock();
}

void CpProxyLinnCoUkProduct3C::PropertyProductSourceXml(Brhz& aProductSourceXml) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aProductSourceXml.Set(iProductSourceXml->Value());
    PropertyReadUnlock();
}

void CpProxyLinnCoUkProduct3C::PropertyStartupSourceIndex(TUint& aStartupSourceIndex) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aStartupSourceIndex = iStartupSourceIndex->Value();
    PropertyReadUnlock();
}

void CpProxyLinnCoUkProduct3C::PropertyStartupSourceEnabled(TBool& aStartupSourceEnabled) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aStartupSourceEnabled = iStartupSourceEnabled->Value();
    PropertyReadUnlock();
}

void CpProxyLinnCoUkProduct3C::PropertyProductAnySourceName(TUint& aProductAnySourceName) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aProductAnySourceName = iProductAnySourceName->Value();
    PropertyReadUnlock();
}

void CpProxyLinnCoUkProduct3C::PropertyProductAnySourceVisible(TUint& aProductAnySourceVisible) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aProductAnySourceVisible = iProductAnySourceVisible->Value();
    PropertyReadUnlock();
}

void CpProxyLinnCoUkProduct3C::PropertyProductAnySourceType(TUint& aProductAnySourceType) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aProductAnySourceType = iProductAnySourceType->Value();
    PropertyReadUnlock();
}

void CpProxyLinnCoUkProduct3C::ProductTypePropertyChanged()
{
    ReportEvent(iProductTypeChanged);
}

void CpProxyLinnCoUkProduct3C::ProductModelPropertyChanged()
{
    ReportEvent(iProductModelChanged);
}

void CpProxyLinnCoUkProduct3C::ProductNamePropertyChanged()
{
    ReportEvent(iProductNameChanged);
}

void CpProxyLinnCoUkProduct3C::ProductRoomPropertyChanged()
{
    ReportEvent(iProductRoomChanged);
}

void CpProxyLinnCoUkProduct3C::ProductStandbyPropertyChanged()
{
    ReportEvent(iProductStandbyChanged);
}

void CpProxyLinnCoUkProduct3C::ProductSourceIndexPropertyChanged()
{
    ReportEvent(iProductSourceIndexChanged);
}

void CpProxyLinnCoUkProduct3C::ProductSourceCountPropertyChanged()
{
    ReportEvent(iProductSourceCountChanged);
}

void CpProxyLinnCoUkProduct3C::ProductSourceXmlPropertyChanged()
{
    ReportEvent(iProductSourceXmlChanged);
}

void CpProxyLinnCoUkProduct3C::StartupSourceIndexPropertyChanged()
{
    ReportEvent(iStartupSourceIndexChanged);
}

void CpProxyLinnCoUkProduct3C::StartupSourceEnabledPropertyChanged()
{
    ReportEvent(iStartupSourceEnabledChanged);
}

void CpProxyLinnCoUkProduct3C::ProductAnySourceNamePropertyChanged()
{
    ReportEvent(iProductAnySourceNameChanged);
}

void CpProxyLinnCoUkProduct3C::ProductAnySourceVisiblePropertyChanged()
{
    ReportEvent(iProductAnySourceVisibleChanged);
}

void CpProxyLinnCoUkProduct3C::ProductAnySourceTypePropertyChanged()
{
    ReportEvent(iProductAnySourceTypeChanged);
}


THandle CpProxyLinnCoUkProduct3Create(CpDeviceC aDevice)
{
    return new CpProxyLinnCoUkProduct3C(aDevice);
}

void CpProxyLinnCoUkProduct3Destroy(THandle aHandle)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    delete proxyC;
}

void CpProxyLinnCoUkProduct3SyncType(THandle aHandle, char** aaType)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaType;
    proxyC->SyncType(buf_aaType);
    *aaType = buf_aaType.Extract();
}

void CpProxyLinnCoUkProduct3BeginType(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginType(functor);
}

int32_t CpProxyLinnCoUkProduct3EndType(THandle aHandle, ZappHandleAsync aAsync, char** aaType)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaType;
    *aaType = NULL;
    try {
        proxyC->EndType(*async, buf_aaType);
        *aaType = buf_aaType.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProduct3SyncModel(THandle aHandle, char** aaModel)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaModel;
    proxyC->SyncModel(buf_aaModel);
    *aaModel = buf_aaModel.Extract();
}

void CpProxyLinnCoUkProduct3BeginModel(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginModel(functor);
}

int32_t CpProxyLinnCoUkProduct3EndModel(THandle aHandle, ZappHandleAsync aAsync, char** aaModel)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaModel;
    *aaModel = NULL;
    try {
        proxyC->EndModel(*async, buf_aaModel);
        *aaModel = buf_aaModel.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProduct3SyncName(THandle aHandle, char** aaName)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaName;
    proxyC->SyncName(buf_aaName);
    *aaName = buf_aaName.Extract();
}

void CpProxyLinnCoUkProduct3BeginName(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginName(functor);
}

int32_t CpProxyLinnCoUkProduct3EndName(THandle aHandle, ZappHandleAsync aAsync, char** aaName)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaName;
    *aaName = NULL;
    try {
        proxyC->EndName(*async, buf_aaName);
        *aaName = buf_aaName.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProduct3SyncSetName(THandle aHandle, const char* aaName)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaName(aaName);
    proxyC->SyncSetName(buf_aaName);
}

void CpProxyLinnCoUkProduct3BeginSetName(THandle aHandle, const char* aaName, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaName(aaName);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetName(buf_aaName, functor);
}

int32_t CpProxyLinnCoUkProduct3EndSetName(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetName(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProduct3SyncRoom(THandle aHandle, char** aaRoom)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaRoom;
    proxyC->SyncRoom(buf_aaRoom);
    *aaRoom = buf_aaRoom.Extract();
}

void CpProxyLinnCoUkProduct3BeginRoom(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginRoom(functor);
}

int32_t CpProxyLinnCoUkProduct3EndRoom(THandle aHandle, ZappHandleAsync aAsync, char** aaRoom)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaRoom;
    *aaRoom = NULL;
    try {
        proxyC->EndRoom(*async, buf_aaRoom);
        *aaRoom = buf_aaRoom.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProduct3SyncSetRoom(THandle aHandle, const char* aaRoom)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaRoom(aaRoom);
    proxyC->SyncSetRoom(buf_aaRoom);
}

void CpProxyLinnCoUkProduct3BeginSetRoom(THandle aHandle, const char* aaRoom, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaRoom(aaRoom);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetRoom(buf_aaRoom, functor);
}

int32_t CpProxyLinnCoUkProduct3EndSetRoom(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetRoom(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProduct3SyncStandby(THandle aHandle, uint32_t* aaStandby)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aaStandby = 0;
    proxyC->SyncStandby(*(TBool*)aaStandby);
}

void CpProxyLinnCoUkProduct3BeginStandby(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginStandby(functor);
}

int32_t CpProxyLinnCoUkProduct3EndStandby(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaStandby)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    *aaStandby = 0;
    try {
        proxyC->EndStandby(*async, *(TBool*)aaStandby);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProduct3SyncSetStandby(THandle aHandle, uint32_t aaStandby)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSetStandby((aaStandby==0? false : true));
}

void CpProxyLinnCoUkProduct3BeginSetStandby(THandle aHandle, uint32_t aaStandby, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetStandby((aaStandby==0? false : true), functor);
}

int32_t CpProxyLinnCoUkProduct3EndSetStandby(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetStandby(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProduct3SyncSourceCount(THandle aHandle, uint32_t* aaSourceCount)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSourceCount(*aaSourceCount);
}

void CpProxyLinnCoUkProduct3BeginSourceCount(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSourceCount(functor);
}

int32_t CpProxyLinnCoUkProduct3EndSourceCount(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaSourceCount)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSourceCount(*async, *aaSourceCount);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProduct3SyncSourceXml(THandle aHandle, char** aaSourceXml)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaSourceXml;
    proxyC->SyncSourceXml(buf_aaSourceXml);
    *aaSourceXml = buf_aaSourceXml.Extract();
}

void CpProxyLinnCoUkProduct3BeginSourceXml(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSourceXml(functor);
}

int32_t CpProxyLinnCoUkProduct3EndSourceXml(THandle aHandle, ZappHandleAsync aAsync, char** aaSourceXml)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaSourceXml;
    *aaSourceXml = NULL;
    try {
        proxyC->EndSourceXml(*async, buf_aaSourceXml);
        *aaSourceXml = buf_aaSourceXml.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProduct3SyncSourceIndex(THandle aHandle, uint32_t* aaSourceIndex)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSourceIndex(*aaSourceIndex);
}

void CpProxyLinnCoUkProduct3BeginSourceIndex(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSourceIndex(functor);
}

int32_t CpProxyLinnCoUkProduct3EndSourceIndex(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaSourceIndex)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSourceIndex(*async, *aaSourceIndex);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProduct3SyncSetSourceIndex(THandle aHandle, uint32_t aaSourceIndex)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSetSourceIndex(aaSourceIndex);
}

void CpProxyLinnCoUkProduct3BeginSetSourceIndex(THandle aHandle, uint32_t aaSourceIndex, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetSourceIndex(aaSourceIndex, functor);
}

int32_t CpProxyLinnCoUkProduct3EndSetSourceIndex(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetSourceIndex(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProduct3SyncSetSourceIndexByName(THandle aHandle, const char* aaSourceName)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaSourceName(aaSourceName);
    proxyC->SyncSetSourceIndexByName(buf_aaSourceName);
}

void CpProxyLinnCoUkProduct3BeginSetSourceIndexByName(THandle aHandle, const char* aaSourceName, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaSourceName(aaSourceName);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetSourceIndexByName(buf_aaSourceName, functor);
}

int32_t CpProxyLinnCoUkProduct3EndSetSourceIndexByName(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetSourceIndexByName(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProduct3SyncSetStartupSourceIndexByName(THandle aHandle, const char* aaSourceName)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaSourceName(aaSourceName);
    proxyC->SyncSetStartupSourceIndexByName(buf_aaSourceName);
}

void CpProxyLinnCoUkProduct3BeginSetStartupSourceIndexByName(THandle aHandle, const char* aaSourceName, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaSourceName(aaSourceName);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetStartupSourceIndexByName(buf_aaSourceName, functor);
}

int32_t CpProxyLinnCoUkProduct3EndSetStartupSourceIndexByName(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetStartupSourceIndexByName(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProduct3SyncStartupSourceIndex(THandle aHandle, uint32_t* aaSourceIndex)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncStartupSourceIndex(*aaSourceIndex);
}

void CpProxyLinnCoUkProduct3BeginStartupSourceIndex(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginStartupSourceIndex(functor);
}

int32_t CpProxyLinnCoUkProduct3EndStartupSourceIndex(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaSourceIndex)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndStartupSourceIndex(*async, *aaSourceIndex);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProduct3SyncSetStartupSourceIndex(THandle aHandle, uint32_t aaSourceIndex)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSetStartupSourceIndex(aaSourceIndex);
}

void CpProxyLinnCoUkProduct3BeginSetStartupSourceIndex(THandle aHandle, uint32_t aaSourceIndex, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetStartupSourceIndex(aaSourceIndex, functor);
}

int32_t CpProxyLinnCoUkProduct3EndSetStartupSourceIndex(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetStartupSourceIndex(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProduct3SyncStartupSourceEnabled(THandle aHandle, uint32_t* aaStartupSourceEnabled)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aaStartupSourceEnabled = 0;
    proxyC->SyncStartupSourceEnabled(*(TBool*)aaStartupSourceEnabled);
}

void CpProxyLinnCoUkProduct3BeginStartupSourceEnabled(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginStartupSourceEnabled(functor);
}

int32_t CpProxyLinnCoUkProduct3EndStartupSourceEnabled(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaStartupSourceEnabled)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    *aaStartupSourceEnabled = 0;
    try {
        proxyC->EndStartupSourceEnabled(*async, *(TBool*)aaStartupSourceEnabled);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProduct3SyncSetStartupSourceEnabled(THandle aHandle, uint32_t aaStartupSourceEnabled)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSetStartupSourceEnabled((aaStartupSourceEnabled==0? false : true));
}

void CpProxyLinnCoUkProduct3BeginSetStartupSourceEnabled(THandle aHandle, uint32_t aaStartupSourceEnabled, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetStartupSourceEnabled((aaStartupSourceEnabled==0? false : true), functor);
}

int32_t CpProxyLinnCoUkProduct3EndSetStartupSourceEnabled(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetStartupSourceEnabled(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProduct3SyncSourceSystemName(THandle aHandle, uint32_t aaSourceIndex, char** aaSourceName)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaSourceName;
    proxyC->SyncSourceSystemName(aaSourceIndex, buf_aaSourceName);
    *aaSourceName = buf_aaSourceName.Extract();
}

void CpProxyLinnCoUkProduct3BeginSourceSystemName(THandle aHandle, uint32_t aaSourceIndex, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSourceSystemName(aaSourceIndex, functor);
}

int32_t CpProxyLinnCoUkProduct3EndSourceSystemName(THandle aHandle, ZappHandleAsync aAsync, char** aaSourceName)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaSourceName;
    *aaSourceName = NULL;
    try {
        proxyC->EndSourceSystemName(*async, buf_aaSourceName);
        *aaSourceName = buf_aaSourceName.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProduct3SyncSourceName(THandle aHandle, uint32_t aaSourceIndex, char** aaSourceName)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaSourceName;
    proxyC->SyncSourceName(aaSourceIndex, buf_aaSourceName);
    *aaSourceName = buf_aaSourceName.Extract();
}

void CpProxyLinnCoUkProduct3BeginSourceName(THandle aHandle, uint32_t aaSourceIndex, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSourceName(aaSourceIndex, functor);
}

int32_t CpProxyLinnCoUkProduct3EndSourceName(THandle aHandle, ZappHandleAsync aAsync, char** aaSourceName)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaSourceName;
    *aaSourceName = NULL;
    try {
        proxyC->EndSourceName(*async, buf_aaSourceName);
        *aaSourceName = buf_aaSourceName.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProduct3SyncSetSourceName(THandle aHandle, uint32_t aaSourceIndex, const char* aaSourceName)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaSourceName(aaSourceName);
    proxyC->SyncSetSourceName(aaSourceIndex, buf_aaSourceName);
}

void CpProxyLinnCoUkProduct3BeginSetSourceName(THandle aHandle, uint32_t aaSourceIndex, const char* aaSourceName, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaSourceName(aaSourceName);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetSourceName(aaSourceIndex, buf_aaSourceName, functor);
}

int32_t CpProxyLinnCoUkProduct3EndSetSourceName(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetSourceName(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProduct3SyncSourceType(THandle aHandle, uint32_t aaSourceIndex, char** aaSourceType)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaSourceType;
    proxyC->SyncSourceType(aaSourceIndex, buf_aaSourceType);
    *aaSourceType = buf_aaSourceType.Extract();
}

void CpProxyLinnCoUkProduct3BeginSourceType(THandle aHandle, uint32_t aaSourceIndex, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSourceType(aaSourceIndex, functor);
}

int32_t CpProxyLinnCoUkProduct3EndSourceType(THandle aHandle, ZappHandleAsync aAsync, char** aaSourceType)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaSourceType;
    *aaSourceType = NULL;
    try {
        proxyC->EndSourceType(*async, buf_aaSourceType);
        *aaSourceType = buf_aaSourceType.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProduct3SyncSourceVisible(THandle aHandle, uint32_t aaSourceIndex, uint32_t* aaSourceVisible)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aaSourceVisible = 0;
    proxyC->SyncSourceVisible(aaSourceIndex, *(TBool*)aaSourceVisible);
}

void CpProxyLinnCoUkProduct3BeginSourceVisible(THandle aHandle, uint32_t aaSourceIndex, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSourceVisible(aaSourceIndex, functor);
}

int32_t CpProxyLinnCoUkProduct3EndSourceVisible(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaSourceVisible)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    *aaSourceVisible = 0;
    try {
        proxyC->EndSourceVisible(*async, *(TBool*)aaSourceVisible);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProduct3SyncSetSourceVisible(THandle aHandle, uint32_t aaSourceIndex, uint32_t aaSourceVisible)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSetSourceVisible(aaSourceIndex, (aaSourceVisible==0? false : true));
}

void CpProxyLinnCoUkProduct3BeginSetSourceVisible(THandle aHandle, uint32_t aaSourceIndex, uint32_t aaSourceVisible, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetSourceVisible(aaSourceIndex, (aaSourceVisible==0? false : true), functor);
}

int32_t CpProxyLinnCoUkProduct3EndSetSourceVisible(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetSourceVisible(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProduct3SetPropertyProductTypeChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyProductTypeChanged(functor);
}

void CpProxyLinnCoUkProduct3SetPropertyProductModelChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyProductModelChanged(functor);
}

void CpProxyLinnCoUkProduct3SetPropertyProductNameChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyProductNameChanged(functor);
}

void CpProxyLinnCoUkProduct3SetPropertyProductRoomChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyProductRoomChanged(functor);
}

void CpProxyLinnCoUkProduct3SetPropertyProductStandbyChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyProductStandbyChanged(functor);
}

void CpProxyLinnCoUkProduct3SetPropertyProductSourceIndexChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyProductSourceIndexChanged(functor);
}

void CpProxyLinnCoUkProduct3SetPropertyProductSourceCountChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyProductSourceCountChanged(functor);
}

void CpProxyLinnCoUkProduct3SetPropertyProductSourceXmlChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyProductSourceXmlChanged(functor);
}

void CpProxyLinnCoUkProduct3SetPropertyStartupSourceIndexChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyStartupSourceIndexChanged(functor);
}

void CpProxyLinnCoUkProduct3SetPropertyStartupSourceEnabledChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyStartupSourceEnabledChanged(functor);
}

void CpProxyLinnCoUkProduct3SetPropertyProductAnySourceNameChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyProductAnySourceNameChanged(functor);
}

void CpProxyLinnCoUkProduct3SetPropertyProductAnySourceVisibleChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyProductAnySourceVisibleChanged(functor);
}

void CpProxyLinnCoUkProduct3SetPropertyProductAnySourceTypeChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyProductAnySourceTypeChanged(functor);
}

void CpProxyLinnCoUkProduct3PropertyProductType(THandle aHandle, char** aProductType)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aProductType;
    proxyC->PropertyProductType(buf_aProductType);
    *aProductType = buf_aProductType.Transfer();
}

void CpProxyLinnCoUkProduct3PropertyProductModel(THandle aHandle, char** aProductModel)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aProductModel;
    proxyC->PropertyProductModel(buf_aProductModel);
    *aProductModel = buf_aProductModel.Transfer();
}

void CpProxyLinnCoUkProduct3PropertyProductName(THandle aHandle, char** aProductName)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aProductName;
    proxyC->PropertyProductName(buf_aProductName);
    *aProductName = buf_aProductName.Transfer();
}

void CpProxyLinnCoUkProduct3PropertyProductRoom(THandle aHandle, char** aProductRoom)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aProductRoom;
    proxyC->PropertyProductRoom(buf_aProductRoom);
    *aProductRoom = buf_aProductRoom.Transfer();
}

void CpProxyLinnCoUkProduct3PropertyProductStandby(THandle aHandle, uint32_t* aProductStandby)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aProductStandby = false;
    proxyC->PropertyProductStandby(*(TBool*)aProductStandby);
}

void CpProxyLinnCoUkProduct3PropertyProductSourceIndex(THandle aHandle, uint32_t* aProductSourceIndex)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyProductSourceIndex(*aProductSourceIndex);
}

void CpProxyLinnCoUkProduct3PropertyProductSourceCount(THandle aHandle, uint32_t* aProductSourceCount)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyProductSourceCount(*aProductSourceCount);
}

void CpProxyLinnCoUkProduct3PropertyProductSourceXml(THandle aHandle, char** aProductSourceXml)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aProductSourceXml;
    proxyC->PropertyProductSourceXml(buf_aProductSourceXml);
    *aProductSourceXml = buf_aProductSourceXml.Transfer();
}

void CpProxyLinnCoUkProduct3PropertyStartupSourceIndex(THandle aHandle, uint32_t* aStartupSourceIndex)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyStartupSourceIndex(*aStartupSourceIndex);
}

void CpProxyLinnCoUkProduct3PropertyStartupSourceEnabled(THandle aHandle, uint32_t* aStartupSourceEnabled)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aStartupSourceEnabled = false;
    proxyC->PropertyStartupSourceEnabled(*(TBool*)aStartupSourceEnabled);
}

void CpProxyLinnCoUkProduct3PropertyProductAnySourceName(THandle aHandle, uint32_t* aProductAnySourceName)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyProductAnySourceName(*aProductAnySourceName);
}

void CpProxyLinnCoUkProduct3PropertyProductAnySourceVisible(THandle aHandle, uint32_t* aProductAnySourceVisible)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyProductAnySourceVisible(*aProductAnySourceVisible);
}

void CpProxyLinnCoUkProduct3PropertyProductAnySourceType(THandle aHandle, uint32_t* aProductAnySourceType)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyProductAnySourceType(*aProductAnySourceType);
}

