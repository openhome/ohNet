#ifndef HEADER_IFACE_MSG
#define HEADER_IFACE_MSG

#include <ZappTypes.h>
#include <stddef.h>
#include <string.h>

namespace Zapp {

typedef void (*ZappFunctorMsg)(void* aPtr, const char* aMsg);

class FunctorMsg
{
public:
    void operator()(const char* aMsg) const { iThunk(*this, aMsg); }
    operator TBool() const { return (iObject!=NULL || iCallback!=NULL); }
    typedef TAny (FunctorMsg::*MemberFunction)();
    typedef TAny (*Callback)();
    FunctorMsg() : iCallback(NULL), iObject(NULL) {}
    static const TUint kFudgeFactor = 2;

    union {
        ZappFunctorMsg iCallback;
        TByte iCallbackMember[kFudgeFactor * sizeof(MemberFunction)];
    };
    TAny* iObject;

protected:
    typedef void (*Thunk)(const FunctorMsg&, const char*);
    FunctorMsg(Thunk aT, const TAny* aObject, const TAny* aCallback, TUint aBytes)
        : iThunk(aT)
    {
        iObject = (TAny*)aObject;
        memcpy(iCallbackMember, aCallback, aBytes);
    }
    FunctorMsg(Thunk aT, const TAny* aObject, ZappFunctorMsg aCallback)
        : iThunk(aT)
    {
        iObject = (TAny*)aObject;
        iCallback = aCallback;
    }

private:
    Thunk iThunk;
};

template<class Object, class MemFunc>
class MemberTranslatorMsg : public FunctorMsg
{
public:
    MemberTranslatorMsg(Object& aC, const MemFunc& aM) :
        FunctorMsg(Thunk,&aC,&aM,sizeof(MemFunc)) {}
    static void Thunk(const FunctorMsg& aFb, const char* aMsg)
    {
        Object* object = (Object*)aFb.iObject;
        MemFunc& memFunc(*(MemFunc*)(TAny*)(aFb.iCallbackMember));
        (object->*memFunc)(aMsg);
    }
};

class FunctionTranslatorMsg : public FunctorMsg
{
public:
    FunctionTranslatorMsg(void* aPtr, ZappFunctorMsg aCallback) :
        FunctorMsg(Thunk,aPtr,aCallback) {}
    static void Thunk(const FunctorMsg& aFb, const char* aMsg)
    {
        aFb.iCallback(aFb.iObject, aMsg);
    }
};

template<class Object, class CallType>
inline MemberTranslatorMsg<Object,void (CallType::*)(const char*)>
MakeFunctorMsg(Object& aC, void(CallType::* const &aF)(const char*))
    {
    typedef void(CallType::*MemFunc)(const char*);
    return MemberTranslatorMsg<Object,MemFunc>(aC,aF);
    }

inline FunctionTranslatorMsg
MakeFunctorMsgC(void* aPtr, ZappFunctorMsg aCallback)
    {
    return FunctionTranslatorMsg(aPtr, aCallback);
    }

} // namespace Zapp

#endif // HEADER_IFACE_MSG
