#ifndef HEADER_IFACE_ASYNC
#define HEADER_IFACE_ASYNC

#include <ZappTypes.h>
#include <stddef.h>
#include <string.h>

namespace Zapp {

class IAsyncOutput
{
public:
    virtual void Output(const TChar* aKey, const TChar* aValue) = 0;
};

class IAsync
{
public:
    virtual void Output(IAsyncOutput& aConsole) = 0;
};

typedef void (*ZappFunctorAsync)(void* aPtr, IAsync* aAsync);

class FunctorAsync
{
public:
    void operator()(IAsync& aAsync) const { iThunk(*this, aAsync); }
    operator TBool() const { return (iObject!=NULL || iCallback!=NULL); }
    typedef TAny (FunctorAsync::*MemberFunction)();
    typedef TAny (*Callback)();
    FunctorAsync() : iCallback(NULL), iObject(NULL) {}
    static const TUint kFudgeFactor = 2;

    union {
        ZappFunctorAsync iCallback;
        TByte iCallbackMember[kFudgeFactor * sizeof(MemberFunction)];
    };
    TAny* iObject;

protected:
    typedef void (*Thunk)(const FunctorAsync&, IAsync&);
    FunctorAsync(Thunk aT, const TAny* aObject, const TAny* aCallback, TUint aBytes)
        : iThunk(aT)
    {
        iObject = (TAny*)aObject;
        memcpy(iCallbackMember, aCallback, aBytes);
    }
    FunctorAsync(Thunk aT, const TAny* aObject, ZappFunctorAsync aCallback)
        : iThunk(aT)
    {
        iObject = (TAny*)aObject;
        iCallback = aCallback;
    }

private:
    Thunk iThunk;
};

template<class Object, class MemFunc>
class MemberTranslatorAsync : public FunctorAsync
{
public:
    MemberTranslatorAsync(Object& aC, const MemFunc& aM) :
        FunctorAsync(Thunk,&aC,&aM,sizeof(MemFunc)) {}
    static void Thunk(const FunctorAsync& aFb, IAsync& aAsync)
    {
        Object* object = (Object*)aFb.iObject;
        MemFunc& memFunc(*(MemFunc*)(TAny*)(aFb.iCallbackMember));
        (object->*memFunc)(aAsync);
    }
};

class FunctionTranslatorAsync : public FunctorAsync
{
public:
    FunctionTranslatorAsync(void* aPtr, ZappFunctorAsync aCallback) :
        FunctorAsync(Thunk,aPtr,aCallback) {}
    static void Thunk(const FunctorAsync& aFb, IAsync& aAsync)
    {
        ((ZappFunctorAsync)aFb.iCallback)(aFb.iObject, &aAsync);
    }
};

template<class Object, class CallType>
inline MemberTranslatorAsync<Object,void (CallType::*)(IAsync&)>
MakeFunctorAsync(Object& aC, void(CallType::* const &aF)(IAsync&))
    {
    typedef void(CallType::*MemFunc)(IAsync&);
    return MemberTranslatorAsync<Object,MemFunc>(aC,aF);
    }


inline FunctionTranslatorAsync
MakeFunctorAsync(void* aPtr, ZappFunctorAsync aCallback)
    {
    return FunctionTranslatorAsync(aPtr, aCallback);
    }

} // namespace Zapp

#endif // HEADER_IFACE_ASYNC
