#ifndef HEADER_IFACE_ASYNC
#define HEADER_IFACE_ASYNC

#include <OpenHome/Types.h>
#include <stddef.h>
#include <string.h>

namespace OpenHome {
namespace Net {

class IAsyncOutput
{
public:
    virtual void Output(const TChar* aKey, const TChar* aValue) = 0;
    virtual ~IAsyncOutput() {}
};

class IAsync
{
public:
    virtual void Output(IAsyncOutput& aConsole) = 0;
    virtual ~IAsync() {}
};

typedef void (STDCALL *OhNetFunctorAsync)(void* aPtr, IAsync* aAsync);

/**
 * Callback used to indicate that an asynchronous operation has completed
 *
 * Most commonly used during action invocation in proxies.
 * Can be implemented using either a pointer to a member function or a pointer to a static
 * or C-style function.
 * @ingroup Callbacks
 */
class FunctorAsync
{
public:
    void operator()(IAsync& aAsync) const { if (*this) { iThunk(*this, aAsync); } }
    operator TBool() const { return (iObject!=NULL || iCallback!=NULL); }
    typedef TAny (FunctorAsync::*MemberFunction)();
    typedef TAny (*Callback)();
    FunctorAsync() : iCallback(NULL), iObject(NULL) {}
    static const TUint kFudgeFactor = 2;

    union {
        OhNetFunctorAsync iCallback;
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
    FunctorAsync(Thunk aT, const TAny* aObject, OhNetFunctorAsync aCallback)
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
    FunctionTranslatorAsync(void* aPtr, OhNetFunctorAsync aCallback) :
        FunctorAsync(Thunk,aPtr,aCallback) {}
    static void Thunk(const FunctorAsync& aFb, IAsync& aAsync)
    {
        ((OhNetFunctorAsync)aFb.iCallback)(aFb.iObject, &aAsync);
    }
};

template<class Object, class CallType>
/**
 * Create a FunctorAsync around a non-const C++ member function
 *
 * @ingroup Callbacks
 *
 * @param[in] aC        this pointer for the callback
 * @param[in] callback  Pointer to a non-const member function taking an IAsync&
 *
 * @return  a FunctorAsync object
 */
inline MemberTranslatorAsync<Object,void (CallType::*)(IAsync&)>
MakeFunctorAsync(Object& aC, void(CallType::* const &aF)(IAsync&))
    {
    typedef void(CallType::*MemFunc)(IAsync&);
    return MemberTranslatorAsync<Object,MemFunc>(aC,aF);
    }

/**
 * Create a FunctorAsync around a C-style function pointer
 *
 * @ingroup Callbacks
 *
 * @param[in] aPtr       Opaque pointer which will be passed to aCallback
 * @param[in] aCallback  Pointer to a (static or non-member) function taking a void* and IAsync&
 *
 * @return  a FunctorAsync object
 */
inline FunctionTranslatorAsync
MakeFunctorAsync(void* aPtr, OhNetFunctorAsync aCallback)
    {
    return FunctionTranslatorAsync(aPtr, aCallback);
    }

} // namespace Net
} // namespace OpenHome

#endif // HEADER_IFACE_ASYNC
