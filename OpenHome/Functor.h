/* Functor et al are heavily influenced by the article in http://www.tutok.sk/fastgl/callback.html
   The psuedo-code in this article was based on a header (no longer obviously
   available at tutok.sk) which included the following license:

   Permission to use, copy, modify, distribute and sell this software
   for any purpose is hereby granted without fee,
   provided that the above copyright notice appear in all copies and
   that both that copyright notice and this permission notice appear
   in supporting documentation.  Rich Hickey makes no
   representations about the suitability of this software for any
   purpose.  It is provided "as is" without express or implied warranty.
*/
#ifndef HEADER_FUNCTOR
#define HEADER_FUNCTOR

#include <OpenHome/Types.h>
#include <stddef.h>
#include <string.h>

namespace OpenHome {

typedef void (STDCALL *OhNetFunctor)(void* aPtr);

/**
 * Generic callback
 *
 * Can be implemented using either a pointer to a member function or a pointer to a static
 * or C-style function.
 * @ingroup Callbacks
 */
class Functor
{
public:
    void operator()() const { if (*this) { iThunk(*this); } }
    operator TBool() const { return (iCallback || iObject); }
    typedef TAny (Functor::*MemberFunction)();
    typedef TAny (*Callback)();
    Functor() : iCallback(0), iObject(0)
    {
        memset(iCallbackMember, 0, sizeof(iCallbackMember));
    }
    static const TUint kFudgeFactor = 2;

    bool operator==(const Functor& aOther) const
    {
        return ((iObject == aOther.iObject) &&
                (iCallback == aOther.iCallback) &&
                (!memcmp(iCallbackMember, aOther.iCallbackMember, sizeof(iCallbackMember))));
    }

    bool operator!=(const Functor& aOther) const
    {
        return !(*this == aOther);
    }

    union {
        OhNetFunctor iCallback;
        TByte iCallbackMember[kFudgeFactor * sizeof(MemberFunction)];
    };
    TAny* iObject;

protected:
    typedef void (*Thunk)(const Functor&);
    Functor(Thunk aT, const TAny* aObject, const TAny* aCallback, TUint aBytes)
        : iThunk(aT)
    {
        iObject = (TAny*)aObject;
        memset(iCallbackMember, 0, sizeof(iCallbackMember));
        memcpy(iCallbackMember, aCallback, aBytes);
    }
    Functor(Thunk aT, const TAny* aObject, OhNetFunctor aCallback)
        : iThunk(aT)
    {
        iObject = (TAny*)aObject;
        memset(iCallbackMember, 0, sizeof(iCallbackMember));
        iCallback = aCallback;
    }

private:
    Thunk iThunk;
};

template<class Object, class MemFunc>
class MemberTranslator : public Functor
{
public:
    MemberTranslator(Object& aC, const MemFunc& aM) :
        Functor(Thunk,&aC,&aM,sizeof(MemFunc)) {}
    static void Thunk(const Functor& aFb)
    {
        Object* object = (Object*)aFb.iObject;
        MemFunc& memFunc(*(MemFunc*)(TAny*)(aFb.iCallbackMember));
        (object->*memFunc)();
    }
};

class MemberTranslatorC : public Functor
{
public:
    MemberTranslatorC(void* aPtr, OhNetFunctor aCallback) :
        Functor(Thunk,aPtr,aCallback) {}
    static void Thunk(const Functor& aFb)
    {
        ((OhNetFunctor)aFb.iCallback)(aFb.iObject);
    }
};

/**
 * Create a Functor around a C-style function pointer
 *
 * @ingroup Callbacks
 *
 * @param[in] aPtr       Opaque pointer which will be passed to aCallback
 * @param[in] aCallback  Pointer to a (static or non-member) function taking a void*
 *
 * @return  a Functor object
 */
inline MemberTranslatorC
MakeFunctor(void* aPtr, OhNetFunctor aCallback)
    {
    return MemberTranslatorC(aPtr, aCallback);
    }

template<class Object, class TRT, class CallType>
/**
 * Create a Functor around a non-const C++ member function
 *
 * @ingroup Callbacks
 *
 * @param[in] aC        this pointer for the callback
 * @param[in] callback  Pointer to a non-const member function taking no arguments
 *
 * @return  a Functor object
 */
inline MemberTranslator<Object,TRT (CallType::*)()>
MakeFunctor(Object& aC, TRT(CallType::* const &aF)())
    {
    typedef TRT(CallType::*MemFunc)();
    return MemberTranslator<Object,MemFunc>(aC,aF);
    }

template<class Object, class TRT, class CallType>
/**
 * Create a Functor around a const C++ member function
 *
 * @ingroup Callbacks
 *
 * @param[in] aC        this pointer for the callback
 * @param[in] callback  Pointer to a const member function taking no arguments
 *
 * @return  a Functor object
 */
inline MemberTranslator<const Object,TRT (CallType::*)() const>
MakeFunctor(const Object& aC, TRT(CallType::* const &aF)() const)
    {
    typedef TRT(CallType::*MemFunc)()const;
    return MemberTranslator<const Object,MemFunc>(aC,aF);
    }


template<class Type>
/**
 * Generic callback with one argument
 *
 * Can be implemented using a pointer to a member function
 * @ingroup Callbacks
 */
class FunctorGeneric
{
public:
    void operator()(Type aType) const { if (*this) { iThunk(*this, aType); } }
    operator TBool() const { return (iObject!=NULL); }
    typedef TAny (FunctorGeneric::*MemberFunction)();
    static const TUint kFudgeFactor = 2;

    bool operator==(const FunctorGeneric& aOther) const
    {
        return ((iObject == aOther.iObject) &&
                (!memcmp(iCallbackMember, aOther.iCallbackMember, sizeof(iCallbackMember))));
    }

    bool operator!=(const FunctorGeneric& aOther) const
    {
        return !(*this == aOther);
    }

    FunctorGeneric() : iObject(NULL)
    {
        memset(iCallbackMember, 0 , sizeof(iCallbackMember));
    }

    TByte iCallbackMember[kFudgeFactor * sizeof(MemberFunction)];
    TAny* iObject;

protected:
    typedef void (*Thunk)(const FunctorGeneric&, Type);
    FunctorGeneric(Thunk aT, const TAny* aObject, const TAny* aCallback, TUint aBytes)
        : iThunk(aT)
    {
        iObject = (TAny*)aObject;
        memset(iCallbackMember, 0, sizeof(iCallbackMember));
        memcpy(iCallbackMember, aCallback, aBytes);
    }

private:
    Thunk iThunk;
};


template<class Type, class Object, class MemFunc>
class MemberTranslatorGeneric : public FunctorGeneric<Type>
{
public:
    MemberTranslatorGeneric(Object& aC, const MemFunc& aM) :
        FunctorGeneric<Type>(Thunk,&aC,&aM,sizeof(MemFunc)) {}
    static void Thunk(const FunctorGeneric<Type>& aFb, Type aType)
    {
        Object* object = (Object*)aFb.iObject;
        MemFunc& memFunc(*(MemFunc*)(TAny*)(aFb.iCallbackMember));
        (object->*memFunc)(aType);
    }
};

template<class Type, class Object, class CallType>
/**
 * Create a FunctorGeneric around a non-const C++ member function
 *
 * @ingroup Callbacks
 *
 * @param[in] aC        this pointer for the callback
 * @param[in] aF        Pointer to a non-const member function taking one argument
 *
 * @return  a Functor object
 */
inline MemberTranslatorGeneric<Type,Object,void (CallType::*)(Type)>
MakeFunctorGeneric(Object& aC, void(CallType::* const &aF)(Type))
    {
    typedef void(CallType::*MemFunc)(Type);
    return MemberTranslatorGeneric<Type,Object,MemFunc>(aC,aF);
    }

class AutoFunctor
{
public:
    AutoFunctor(Functor aFunctor)
        : iFunctor(aFunctor)
    {}
    ~AutoFunctor()
    {
        iFunctor();
    }
private:
    Functor iFunctor;
};

} // namespace OpenHome

#endif // HEADER_FUNCTOR
