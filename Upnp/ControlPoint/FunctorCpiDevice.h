#ifndef HEADER_IFACE_CPIDEVICE
#define HEADER_IFACE_CPIDEVICE

#include <ZappTypes.h>
#include <stddef.h>
#include <string.h>

namespace Zapp {

class CpiDevice;
typedef void (*ZappFunctorDevice)(void* aPtr, CpiDevice* aDevice);

class FunctorCpiDevice
{
public:
    void operator()(CpiDevice& aDevice) const { iThunk(*this, aDevice); }
    operator TBool() const { return (iObject!=NULL || iCallback!=NULL); }
    typedef TAny (FunctorCpiDevice::*MemberFunction)();
    typedef TAny (*Callback)();
    FunctorCpiDevice() : iCallback(NULL), iObject(NULL) {}
    static const TUint kFudgeFactor = 2;

    union {
        ZappFunctorDevice iCallback;
        TByte iCallbackMember[kFudgeFactor * sizeof(MemberFunction)];
    };
    TAny* iObject;

protected:
    typedef void (*Thunk)(const FunctorCpiDevice&, CpiDevice&);
    FunctorCpiDevice(Thunk aT, const TAny* aObject, const TAny* aCallback, TUint aBytes)
        : iThunk(aT)
    {
        iObject = (TAny*)aObject;
        memcpy(iCallbackMember, aCallback, aBytes);
    }
    FunctorCpiDevice(Thunk aT, const TAny* aObject, ZappFunctorDevice aCallback)
        : iThunk(aT)
    {
        iObject = (TAny*)aObject;
        iCallback = aCallback;
    }

private:
    Thunk iThunk;
};

template<class Object, class MemFunc>
class MemberTranslatorCpiDevice : public FunctorCpiDevice
{
public:
    MemberTranslatorCpiDevice(Object& aC, const MemFunc& aM) :
        FunctorCpiDevice(Thunk,&aC,&aM,sizeof(MemFunc)) {}
    static void Thunk(const FunctorCpiDevice& aFb, CpiDevice& aDevice)
    {
        Object* object = (Object*)aFb.iObject;
        MemFunc& memFunc(*(MemFunc*)(TAny*)(aFb.iCallbackMember));
        (object->*memFunc)(aDevice);
    }
};

class FunctionTranslatorCpiDevice : public FunctorCpiDevice
{
public:
    FunctionTranslatorCpiDevice(void* aPtr, ZappFunctorDevice aCallback) :
        FunctorCpiDevice(Thunk,aPtr,aCallback) {}
    static void Thunk(const FunctorCpiDevice& aFb, CpiDevice& aDevice)
    {
        aFb.iCallback(aFb.iObject, &aDevice);
    }
};

template<class Object, class CallType>
inline MemberTranslatorCpiDevice<Object,void (CallType::*)(CpiDevice&)>
MakeFunctorCpiDevice(Object& aC, void(CallType::* const &aF)(CpiDevice&))
    {
    typedef void(CallType::*MemFunc)(CpiDevice&);
    return MemberTranslatorCpiDevice<Object,MemFunc>(aC,aF);
    }

inline FunctionTranslatorCpiDevice
MakeFunctorCpiDeviceC(void* aPtr, ZappFunctorDevice aCallback)
    {
    return FunctionTranslatorCpiDevice(aPtr, aCallback);
    }

} // namespace Zapp

#endif // HEADER_IFACE_CPIDEVICE
