#ifndef HEADER_IFACE_MSG
#define HEADER_IFACE_MSG

#include <OpenHome/Types.h>
#include <stddef.h>
#include <string.h>

namespace OpenHome {

typedef void (STDCALL *OhNetFunctorMsg)(void* aPtr, const char* aMsg);

/**
 * Callback used to pass a message (a nul-terminated const char*).
 *
 * Typically used for debug logging.
 * Can be implemented using either a pointer to a member function or a pointer to a static
 * or C-style function.
 * @ingroup Callbacks
 */
class FunctorMsg
{
public:
    void operator()(const char* aMsg) const { if (*this) { iThunk(*this, aMsg); } }
    operator TBool() const { return (iObject!=NULL || iCallback!=NULL); }
    typedef TAny (FunctorMsg::*MemberFunction)();
    typedef TAny (*Callback)();
    FunctorMsg() : iCallback(NULL), iObject(NULL) {}
    static const TUint kFudgeFactor = 2;

    union {
        OhNetFunctorMsg iCallback;
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
    FunctorMsg(Thunk aT, const TAny* aObject, OhNetFunctorMsg aCallback)
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
    FunctionTranslatorMsg(void* aPtr, OhNetFunctorMsg aCallback) :
        FunctorMsg(Thunk,aPtr,aCallback) {}
    static void Thunk(const FunctorMsg& aFb, const char* aMsg)
    {
        aFb.iCallback(aFb.iObject, aMsg);
    }
};

template<class Object, class CallType>
/**
 * Create a FunctorMsg around a non-const C++ member function
 *
 * @ingroup Callbacks
 *
 * @param[in] aC        this pointer for the callback
 * @param[in] callback  Pointer to a non-const member function taking a const char*
 *
 * @return  a FunctorMsg object
 */
inline MemberTranslatorMsg<Object,void (CallType::*)(const char*)>
MakeFunctorMsg(Object& aC, void(CallType::* const &aF)(const char*))
    {
    typedef void(CallType::*MemFunc)(const char*);
    return MemberTranslatorMsg<Object,MemFunc>(aC,aF);
    }

/**
 * Create a FunctorMsg around a C-style function pointer
 *
 * @ingroup Callbacks
 *
 * @param[in] aPtr       Opaque pointer which will be passed to aCallback
 * @param[in] aCallback  Pointer to a (static or non-member) function taking a void* and const char*
 *
 * @return  a FunctorMsg object
 */
inline FunctionTranslatorMsg
MakeFunctorMsgC(void* aPtr, OhNetFunctorMsg aCallback)
    {
    return FunctionTranslatorMsg(aPtr, aCallback);
    }

} // namespace OpenHome

#endif // HEADER_IFACE_MSG
