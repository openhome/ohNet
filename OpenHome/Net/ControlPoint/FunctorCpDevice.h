#ifndef HEADER_IFACE_DEVICE
#define HEADER_IFACE_DEVICE

#include <OpenHome/Types.h>
#include <stddef.h>
#include <string.h>

namespace OpenHome {
namespace Net {

class CpDevice;

/**
 * Callback used to pass a CpDevice.
 *
 * Typically used by CpDeviceList subclasses.
 * Must be implemented using a pointer to a non-const member function.
 * @ingroup ControlPoint
 */
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
/**
 * Create a FunctorCpDevice around a non-const C++ member function
 *
 * @ingroup ControlPoint
 *
 * @param[in] aC        this pointer for the callback
 * @param[in] callback  Pointer to a non-const member function taking a CpDevice&
 *
 * @return  a FunctorCpDevice object
 */
inline MemberTranslatorCpDevice<Object,void (CallType::*)(CpDevice&)>
MakeFunctorCpDevice(Object& aC, void(CallType::* const &aF)(CpDevice&))
    {
    typedef void(CallType::*MemFunc)(CpDevice&);
    return MemberTranslatorCpDevice<Object,MemFunc>(aC,aF);
    }

} // namespace Net
} // namespace OpenHome

#endif // HEADER_IFACE_DEVICE
