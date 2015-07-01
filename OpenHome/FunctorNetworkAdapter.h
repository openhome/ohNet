#ifndef HEADER_IFACE_NETWORKADAPTER
#define HEADER_IFACE_NETWORKADAPTER

#include <OpenHome/Types.h>
#include <stddef.h>
#include <string.h>

namespace OpenHome {

class NetworkAdapter;
typedef void (STDCALL *OhNetFunctorNetworkAdapter)(void* aPtr, NetworkAdapter* aAdapter);

class FunctorNetworkAdapter
{
public:
    void operator()(NetworkAdapter& aAdapter) const { if (*this) { iThunk(*this, aAdapter); } }
    operator TBool() const { return (iObject!=NULL || iCallback!=NULL); }
    typedef TAny (FunctorNetworkAdapter::*MemberFunction)();
    typedef TAny (*Callback)();
    FunctorNetworkAdapter() : iCallback(NULL), iObject(NULL) {}
    static const TUint kFudgeFactor = 2;

    union {
        OhNetFunctorNetworkAdapter iCallback;
        TByte iCallbackMember[kFudgeFactor * sizeof(MemberFunction)];
    };
    TAny* iObject;

protected:
    typedef void (*Thunk)(const FunctorNetworkAdapter&, NetworkAdapter&);
    FunctorNetworkAdapter(Thunk aT, const TAny* aObject, const TAny* aCallback, TUint aBytes)
        : iThunk(aT)
    {
        iObject = (TAny*)aObject;
        memcpy(iCallbackMember, aCallback, aBytes);
    }
    FunctorNetworkAdapter(Thunk aT, const TAny* aObject, OhNetFunctorNetworkAdapter aCallback)
        : iThunk(aT)
    {
        iObject = (TAny*)aObject;
        iCallback = aCallback;
    }

private:
    Thunk iThunk;
};

template<class Object, class MemFunc>
class MemberTranslatorNetworkAdapter : public FunctorNetworkAdapter
{
public:
    MemberTranslatorNetworkAdapter(Object& aC, const MemFunc& aM) :
        FunctorNetworkAdapter(Thunk,&aC,&aM,sizeof(MemFunc)) {}
    static void Thunk(const FunctorNetworkAdapter& aFb, NetworkAdapter& aAdapter)
    {
        Object* object = (Object*)aFb.iObject;
        MemFunc& memFunc(*(MemFunc*)(TAny*)(aFb.iCallbackMember));
        (object->*memFunc)(aAdapter);
    }
};

class FunctionTranslatorNetworkAdapter : public FunctorNetworkAdapter
{
public:
    FunctionTranslatorNetworkAdapter(void* aPtr, OhNetFunctorNetworkAdapter aCallback) :
        FunctorNetworkAdapter(Thunk,aPtr,aCallback) {}
    static void Thunk(const FunctorNetworkAdapter& aFb, NetworkAdapter& aAdapter)
    {
        aFb.iCallback(aFb.iObject, &aAdapter);
    }
};

template<class Object, class CallType>
inline MemberTranslatorNetworkAdapter<Object,void (CallType::*)(NetworkAdapter&)>
MakeFunctorNetworkAdapter(Object& aC, void(CallType::* const &aF)(NetworkAdapter&))
    {
    typedef void(CallType::*MemFunc)(NetworkAdapter&);
    return MemberTranslatorNetworkAdapter<Object,MemFunc>(aC,aF);
    }

inline FunctionTranslatorNetworkAdapter
MakeFunctorNetworkAdapter(void* aPtr, OhNetFunctorNetworkAdapter aCallback)
    {
    return FunctionTranslatorNetworkAdapter(aPtr, aCallback);
    }

} // namespace OpenHome

#endif // HEADER_IFACE_NETWORKADAPTER
