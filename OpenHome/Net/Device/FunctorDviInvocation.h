#ifndef HEADER_IFACE_DVIINVOCATION
#define HEADER_IFACE_DVIINVOCATION

#include <OpenHome/Types.h>

namespace OpenHome {
namespace Net {

class IDviInvocation;
typedef void (STDCALL *OhNetFunctorDviInvocation)(void* aPtr, IDviInvocation* aInvocation);

class FunctorDviInvocation
{
public:
    void operator()(IDviInvocation& aInvocation) const { iThunk(*this, aInvocation); }
    operator TBool() const { return (iObject!=NULL || iCallback!=NULL); }
    typedef TAny (FunctorDviInvocation::*MemberFunction)();
    typedef TAny (*Callback)();
    FunctorDviInvocation() : iCallback(NULL), iObject(NULL) {}
    static const TUint kFudgeFactor = 2;

    union {
        OhNetFunctorDviInvocation iCallback;
        TByte iCallbackMember[kFudgeFactor * sizeof(MemberFunction)];
    };
    TAny* iObject;

protected:
    typedef void (*Thunk)(const FunctorDviInvocation&, IDviInvocation&);
    FunctorDviInvocation(Thunk aT, const TAny* aObject, const TAny* aCallback, TUint aBytes)
        : iThunk(aT)
    {
        iObject = (TAny*)aObject;
        memcpy(iCallbackMember, aCallback, aBytes);
    }
    FunctorDviInvocation(Thunk aT, const TAny* aObject, OhNetFunctorDviInvocation aCallback)
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
    static void Thunk(const FunctorDviInvocation& aFb, IDviInvocation& aInvocation)
    {
        Object* object = (Object*)aFb.iObject;
        MemFunc& memFunc(*(MemFunc*)(TAny*)(aFb.iCallbackMember));
        (object->*memFunc)(aInvocation);
    }
};

class FunctionTranslatorDviInvocation : public FunctorDviInvocation
{
public:
    FunctionTranslatorDviInvocation(void* aPtr, OhNetFunctorDviInvocation aCallback) :
        FunctorDviInvocation(Thunk,aPtr,aCallback) {}
    static void Thunk(const FunctorDviInvocation& aFb, IDviInvocation& aInvocation)
    {
        ((OhNetFunctorDviInvocation)aFb.iCallback)(aFb.iObject, &aInvocation);
    }
};

template<class Object, class CallType>
inline MemberTranslatorDviInvocation<Object,void (CallType::*)(IDviInvocation&)>
MakeFunctorDviInvocation(Object& aC, void(CallType::* const &aF)(IDviInvocation&))
    {
    typedef void(CallType::*MemFunc)(IDviInvocation&);
    return MemberTranslatorDviInvocation<Object,MemFunc>(aC,aF);
    }

inline FunctionTranslatorDviInvocation
MakeFunctorDviInvocation(void* aPtr, OhNetFunctorDviInvocation aCallback)
    {
    return FunctionTranslatorDviInvocation(aPtr, aCallback);
    }

} // namespace Net
} // namespace OpenHome

#endif // HEADER_IFACE_DVIINVOCATION
