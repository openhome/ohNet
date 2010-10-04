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

#include <ZappTypes.h>
#include <stddef.h>
#include <string.h>

namespace Zapp
{

typedef void (*ZappFunctor)(void* aPtr);

class Functor
{
public:
    void operator()() const { iThunk(*this); }
    operator TBool() const { return (iCallback || iObject); }
    typedef TAny (Functor::*MemberFunction)();
    typedef TAny (*Callback)();
    Functor() : iCallback(0), iObject(0) {}
    static const TUint kFudgeFactor = 2;

    union {
        ZappFunctor iCallback;
        TByte iCallbackMember[kFudgeFactor * sizeof(MemberFunction)];
    };
    TAny* iObject;

protected:
    typedef void (*Thunk)(const Functor&);
    Functor(Thunk aT, const TAny* aObject, const TAny* aCallback, TUint aBytes)
        : iThunk(aT)
    {
        iObject = (TAny*)aObject;
        memcpy(iCallbackMember, aCallback, aBytes);
    }
    Functor(Thunk aT, const TAny* aObject, ZappFunctor aCallback)
        : iThunk(aT)
    {
        iObject = (TAny*)aObject;
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
    MemberTranslatorC(void* aPtr, ZappFunctor aCallback) :
        Functor(Thunk,aPtr,aCallback) {}
    static void Thunk(const Functor& aFb)
    {
        ((ZappFunctor)aFb.iCallback)(aFb.iObject);
    }
};

inline MemberTranslatorC
MakeFunctor(void* aPtr, ZappFunctor aCallback)
    {
    return MemberTranslatorC(aPtr, aCallback);
    }

template<class Object, class TRT, class CallType>
inline MemberTranslator<Object,TRT (CallType::*)()>
MakeFunctor(Object& aC, TRT(CallType::* const &aF)())
    {
    typedef TRT(CallType::*MemFunc)();
    return MemberTranslator<Object,MemFunc>(aC,aF);
    }

template<class Object, class TRT, class CallType>
inline MemberTranslator<const Object,TRT (CallType::*)() const>
MakeFunctor(const Object& aC, TRT(CallType::* const &aF)() const)
    {
    typedef TRT(CallType::*MemFunc)()const;
    return MemberTranslator<const Object,MemFunc>(aC,aF);
    }

} // namespace Zapp

#endif // HEADER_FUNCTOR
