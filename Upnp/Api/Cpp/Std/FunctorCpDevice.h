#ifndef HEADER_IFACE_DEVICECPP
#define HEADER_IFACE_DEVICECPP

#include <ZappTypes.h>
#include <stddef.h>
#include <string.h>

namespace Zapp {

class CpDeviceCpp;

class FunctorCpDeviceCpp
{
public:
    void operator()(CpDeviceCpp& aDevice) const { iThunk(*this, aDevice); }
    operator TBool() const { return (iObject!=NULL); }
    typedef TAny (FunctorCpDeviceCpp::*MemberFunction)();
    typedef TAny (*Callback)();
    FunctorCpDeviceCpp() : iObject(0) {}

    TByte iCallbackMember[sizeof(MemberFunction)];
    TAny* iObject;

protected:
    typedef void (*Thunk)(const FunctorCpDeviceCpp&, CpDeviceCpp&);
    FunctorCpDeviceCpp(Thunk aT, const TAny* aObject, const TAny* aCallback, TUint aBytes)
        : iThunk(aT)
    {
        iObject = (TAny*)aObject;
        memcpy(iCallbackMember, aCallback, aBytes);
    }

private:
    Thunk iThunk;
};

template<class Object, class MemFunc>
class MemberTranslatorCpDeviceCpp : public FunctorCpDeviceCpp
{
public:
    MemberTranslatorCpDeviceCpp(Object& aC, const MemFunc& aM) :
        FunctorCpDeviceCpp(Thunk,&aC,&aM,sizeof(MemFunc)) {}
    static void Thunk(const FunctorCpDeviceCpp& aFb, CpDeviceCpp& aDevice)
    {
        Object* object = (Object*)aFb.iObject;
        MemFunc& memFunc(*(MemFunc*)(TAny*)(aFb.iCallbackMember));
        (object->*memFunc)(aDevice);
    }
};

template<class Object, class CallType>
inline MemberTranslatorCpDeviceCpp<Object,void (CallType::*)(CpDeviceCpp&)>
MakeFunctorCpDeviceCpp(Object& aC, void(CallType::* const &aF)(CpDeviceCpp&))
    {
    typedef void(CallType::*MemFunc)(CpDeviceCpp&);
    return MemberTranslatorCpDeviceCpp<Object,MemFunc>(aC,aF);
    }

} // namespace Zapp

#endif // HEADER_IFACE_DEVICECPP
