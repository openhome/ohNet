#ifndef HEADER_IFACE_DVINVOCATION
#define HEADER_IFACE_DVINVOCATION

#include <ZappTypes.h>

namespace Zapp {

typedef void (*ZappFunctorDvInvocation)(void* aPtr, void* aInvocation, TUint aVersion);
class IDvInvocation;

class FunctorDvInvocation
{
public:
    void operator()(IDvInvocation& aInvocation, TUint aVersion) const { iThunk(*this, aInvocation, aVersion); }
    operator TBool() const { return (iObject!=NULL || iCallback!=NULL); }
    typedef TAny (FunctorDvInvocation::*MemberFunction)();
    typedef TAny (*Callback)();
    FunctorDvInvocation() : iCallback(NULL), iObject(NULL) {}
    static const TUint kFudgeFactor = 2;

    union {
        ZappFunctorDvInvocation iCallback;
        TByte iCallbackMember[kFudgeFactor * sizeof(MemberFunction)];
    };
    TAny* iObject;

protected:
    typedef void (*Thunk)(const FunctorDvInvocation&, IDvInvocation&, TUint);
    FunctorDvInvocation(Thunk aT, const TAny* aObject, const TAny* aCallback, TUint aBytes)
        : iThunk(aT)
    {
        iObject = (TAny*)aObject;
        memcpy(iCallbackMember, aCallback, aBytes);
    }
    FunctorDvInvocation(Thunk aT, const TAny* aObject, ZappFunctorDvInvocation aCallback)
        : iThunk(aT)
    {
        iObject = (TAny*)aObject;
        iCallback = aCallback;
    }

private:
    Thunk iThunk;
};

template<class Object, class MemFunc>
class MemberTranslatorDvInvocation : public FunctorDvInvocation
{
public:
    MemberTranslatorDvInvocation(Object& aC, const MemFunc& aM) :
        FunctorDvInvocation(Thunk,&aC,&aM,sizeof(MemFunc)) {}
    static void Thunk(const FunctorDvInvocation& aFb, IDvInvocation& aInvocation, TUint aVersion)
    {
        Object* object = (Object*)aFb.iObject;
        MemFunc& memFunc(*(MemFunc*)(TAny*)(aFb.iCallbackMember));
        (object->*memFunc)(aInvocation, aVersion);
    }
};

template<class Object, class CallType>
inline MemberTranslatorDvInvocation<Object,void (CallType::*)(IDvInvocation&, TUint)>
MakeFunctorDvInvocation(Object& aC, void(CallType::* const &aF)(IDvInvocation&, TUint))
    {
    typedef void(CallType::*MemFunc)(IDvInvocation&, TUint);
    return MemberTranslatorDvInvocation<Object,MemFunc>(aC,aF);
    }

} // namespace Zapp

#endif // HEADER_IFACE_DVINVOCATION
