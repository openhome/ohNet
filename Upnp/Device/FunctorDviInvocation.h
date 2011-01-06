#ifndef HEADER_IFACE_DVIINVOCATION
#define HEADER_IFACE_DVIINVOCATION

#include <ZappTypes.h>

namespace Zapp {

class IDviInvocation;
typedef void (*ZappFunctorDviInvocation)(void* aPtr, IDviInvocation* aInvocation, TUint aVersion);

class FunctorDviInvocation
{
public:
    void operator()(IDviInvocation& aInvocation, TUint aVersion) const { iThunk(*this, aInvocation, aVersion); }
    operator TBool() const { return (iObject!=NULL || iCallback!=NULL); }
    typedef TAny (FunctorDviInvocation::*MemberFunction)();
    typedef TAny (*Callback)();
    FunctorDviInvocation() : iCallback(NULL), iObject(NULL) {}
    static const TUint kFudgeFactor = 2;

    union {
        ZappFunctorDviInvocation iCallback;
        TByte iCallbackMember[kFudgeFactor * sizeof(MemberFunction)];
    };
    TAny* iObject;

protected:
    typedef void (*Thunk)(const FunctorDviInvocation&, IDviInvocation&, TUint);
    FunctorDviInvocation(Thunk aT, const TAny* aObject, const TAny* aCallback, TUint aBytes)
        : iThunk(aT)
    {
        iObject = (TAny*)aObject;
        memcpy(iCallbackMember, aCallback, aBytes);
    }
    FunctorDviInvocation(Thunk aT, const TAny* aObject, ZappFunctorDviInvocation aCallback)
        : iThunk(aT)
    {
        iObject = (TAny*)aObject;
        iCallback = aCallback;
    }

private:
    Thunk iThunk;
};

template<class Object, class MemFunc>
class MemberTranslatorDviInvocation : public FunctorDviInvocation
{
public:
    MemberTranslatorDviInvocation(Object& aC, const MemFunc& aM) :
        FunctorDviInvocation(Thunk,&aC,&aM,sizeof(MemFunc)) {}
    static void Thunk(const FunctorDviInvocation& aFb, IDviInvocation& aInvocation, TUint aVersion)
    {
        Object* object = (Object*)aFb.iObject;
        MemFunc& memFunc(*(MemFunc*)(TAny*)(aFb.iCallbackMember));
        (object->*memFunc)(aInvocation, aVersion);
    }
};

class FunctionTranslatorDviInvocation : public FunctorDviInvocation
{
public:
    FunctionTranslatorDviInvocation(void* aPtr, ZappFunctorDviInvocation aCallback) :
        FunctorDviInvocation(Thunk,aPtr,aCallback) {}
    static void Thunk(const FunctorDviInvocation& aFb, IDviInvocation& aInvocation, TUint aVersion)
    {
        ((ZappFunctorDviInvocation)aFb.iCallback)(aFb.iObject, &aInvocation, aVersion);
    }
};

template<class Object, class CallType>
inline MemberTranslatorDviInvocation<Object,void (CallType::*)(IDviInvocation&, TUint)>
MakeFunctorDviInvocation(Object& aC, void(CallType::* const &aF)(IDviInvocation&, TUint))
    {
    typedef void(CallType::*MemFunc)(IDviInvocation&, TUint);
    return MemberTranslatorDviInvocation<Object,MemFunc>(aC,aF);
    }

inline FunctionTranslatorDviInvocation
MakeFunctorDviInvocation(void* aPtr, ZappFunctorDviInvocation aCallback)
    {
    return FunctionTranslatorDviInvocation(aPtr, aCallback);
    }

} // namespace Zapp

#endif // HEADER_IFACE_DVIINVOCATION
