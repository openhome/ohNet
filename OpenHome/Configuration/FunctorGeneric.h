/* FunctorGeneric is heavily influenced by the article in http://www.tutok.sk/fastgl/callback.html
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
#ifndef HEADER_IFACE_FUNCTORGENERIC
#define HEADER_IFACE_FUNCTORGENERIC

#include <OpenHome/Types.h>
#include <stddef.h>
#include <string.h>

namespace OpenHome {
namespace Configuration {

template<class Type>
class FunctorGeneric
{
public:
    void operator()(Type aType) const { iThunk(*this, aType); }
    typedef TAny (FunctorGeneric::*MemberFunction)();
    static const TUint kFudgeFactor = 2;

    TByte iCallbackMember[kFudgeFactor * sizeof(MemberFunction)];
    TAny* iObject;

protected:
    typedef void (*Thunk)(const FunctorGeneric&, Type);
    FunctorGeneric(Thunk aT, const TAny* aObject, const TAny* aCallback, TUint aBytes)
        : iThunk(aT)
    {
        iObject = (TAny*)aObject;
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


/**
 * Create a FunctorGeneric around a non-const C++ member function
 */
template<class Type, class Object, class CallType>
inline MemberTranslatorGeneric<Type,Object,void (CallType::*)(Type)>
MakeFunctorGeneric(Object& aC, void(CallType::* const &aF)(Type))
    {
    typedef void(CallType::*MemFunc)(Type);
    return MemberTranslatorGeneric<Type,Object,MemFunc>(aC,aF);
    }

} // namespace Configuration
} // namespace OpenHome

#endif // HEADER_IFACE_FUNCTORGENERIC
