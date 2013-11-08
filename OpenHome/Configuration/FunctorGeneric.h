#ifndef HEADER_IFACE_FUNCTORGENERIC
#define HEADER_IFACE_FUNCTORGENERIC

#include <OpenHome/OhNetTypes.h>
#include <stddef.h>
#include <string.h>

namespace OpenHome {
namespace Configuration {

typedef void (STDCALL *OhNetFunctorGeneric)(void* aPtr, void* aType);

template<class Type>
class FunctorGeneric
{
public:
    void operator()(Type& aType) const { iThunk(*this, aType); }
    operator TBool() const { return (iObject!=NULL || iCallback!=NULL); }
    typedef TAny (FunctorGeneric::*MemberFunction)();
    typedef TAny (*Callback)();
    FunctorGeneric() : iCallback(NULL), iObject(NULL) {}
    static const TUint kFudgeFactor = 2;

    union {
        OhNetFunctorGeneric iCallback;
        TByte iCallbackMember[kFudgeFactor * sizeof(MemberFunction)];
    };
    TAny* iObject;

protected:
    typedef void (*Thunk)(const FunctorGeneric&, Type&);
    FunctorGeneric(Thunk aT, const TAny* aObject, const TAny* aCallback, TUint aBytes)
        : iThunk(aT)
    {
        iObject = (TAny*)aObject;
        memcpy(iCallbackMember, aCallback, aBytes);
    }
    FunctorGeneric(Thunk aT, const TAny* aObject, OhNetFunctorGeneric aCallback)
        : iThunk(aT)
    {
        iObject = (TAny*)aObject;
        iCallback = aCallback;
    }

private:
    Thunk iThunk;
};

template<class Type, class Object, class MemFunc>
class MemberTranslatorGeneric : public FunctorGeneric<Type>
{
public:
    MemberTranslatorGeneric(Object& aC, const MemFunc& aM) :
        FunctorGeneric(Thunk,&aC,&aM,sizeof(MemFunc)) {}
    static void Thunk(const FunctorGeneric& aFb, Type& aType)
    {
        Object* object = (Object*)aFb.iObject;
        MemFunc& memFunc(*(MemFunc*)(TAny*)(aFb.iCallbackMember));
        (object->*memFunc)(aType);
    }
};

/**
 * FunctionTranslator for a C-style function pointer
 */
//template<class Type>
//class FunctionTranslatorGeneric : public FunctorGeneric<Type>
//{
//public:
//    FunctionTranslatorGeneric(void* aPtr, OhNetFunctorGeneric aCallback) :
//        FunctorGeneric(Thunk,aPtr,aCallback) {}
//    static void Thunk(const FunctorGeneric& aFb, Type& aType)
//    {
//        aFb.iCallback(aFb.iObject, &aType);
//    }
//};

/**
 * Create a FunctorGeneric around a non-const C++ member function
 */
template<class Type, class Object, class CallType>
inline MemberTranslatorGeneric<Type,Object,void (CallType::*)(Type&)>
MakeFunctorGeneric(Object& aC, void(CallType::* const &aF)(Type&))
    {
    typedef void(CallType::*MemFunc)(Type&);
    return MemberTranslatorGeneric<Type,Object,MemFunc>(aC,aF);
    }

/**
 * Create a FunctorMsg around a C-style function pointer
 */
//template<class Type>
//inline FunctionTranslatorGeneric<Type>
//MakeFunctorGenericC(void* aPtr, OhNetFunctorGeneric aCallback)
//    {
//    return FunctionTranslatorGeneric<Type>(aPtr, aCallback);
//    }

} // namespace Configuration
} // namespace OpenHome

#endif // HEADER_IFACE_FUNCTORGENERIC
