#ifndef HEADER_IFACE_DEVICE
#define HEADER_IFACE_DEVICE

#include <ZappTypes.h>
#include <stddef.h>
#include <string.h>

namespace Zapp {

class CpDevice;

class FunctorCpDevice
{
public:
    void operator()(CpDevice& aDevice) const { iThunk(*this, aDevice); }
    operator TBool() const { return (iObject!=NULL); }
    typedef TAny (FunctorCpDevice::*MemberFunction)();
    typedef TAny (*Callback)();
    FunctorCpDevice() : iObject(0) {}
    static const TUint kFudgeFactor = 2;

    TByte iCallbackMember[kFudgeFactor * sizeof(MemberFunction)];
    TAny* iObject;

protected:
    typedef void (*Thunk)(const FunctorCpDevice&, CpDevice&);
    FunctorCpDevice(Thunk aT, const TAny* aObject, const TAny* aCallback, TUint aBytes)
        : iThunk(aT)
    {
        iObject = (TAny*)aObject;
        memcpy(iCallbackMember, aCallback, aBytes);
    }

private:
    Thunk iThunk;
};

template<class Object, class MemFunc>
class MemberTranslatorCpDevice : public FunctorCpDevice
{
public:
    MemberTranslatorCpDevice(Object& aC, const MemFunc& aM) :
        FunctorCpDevice(Thunk,&aC,&aM,sizeof(MemFunc)) {}
    static void Thunk(const FunctorCpDevice& aFb, CpDevice& aDevice)
    {
        Object* object = (Object*)aFb.iObject;
        MemFunc& memFunc(*(MemFunc*)(TAny*)(aFb.iCallbackMember));
        (object->*memFunc)(aDevice);
    }
};

template<class Object, class CallType>
inline MemberTranslatorCpDevice<Object,void (CallType::*)(CpDevice&)>
MakeFunctorCpDevice(Object& aC, void(CallType::* const &aF)(CpDevice&))
    {
    typedef void(CallType::*MemFunc)(CpDevice&);
    return MemberTranslatorCpDevice<Object,MemFunc>(aC,aF);
    }

} // namespace Zapp

#endif // HEADER_IFACE_DEVICE
