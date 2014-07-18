#ifndef HEADER_IFACE_DEVICECPP
#define HEADER_IFACE_DEVICECPP

#include <OpenHome/Types.h>
#include <stddef.h>
#include <string.h>

namespace OpenHome {
namespace Net {

class CpDeviceCpp;

/**
 * Callback used to pass a CpDeviceCpp.
 *
 * Typically used by CpDeviceListCpp subclasses.
 * Must be implemented using a pointer to a non-const member function.
 * @ingroup ControlPoint
 */
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
/**
 * Create a FunctorCpDeviceCpp around a non-const C++ member function
 *
 * @ingroup ControlPoint
 *
 * @param[in] aC        this pointer for the callback
 * @param[in] callback  Pointer to a non-const member function taking a CpDeviceCpp&
 *
 * @return  a FunctorCpDeviceCpp object
 */
inline MemberTranslatorCpDeviceCpp<Object,void (CallType::*)(CpDeviceCpp&)>
MakeFunctorCpDeviceCpp(Object& aC, void(CallType::* const &aF)(CpDeviceCpp&))
    {
    typedef void(CallType::*MemFunc)(CpDeviceCpp&);
    return MemberTranslatorCpDeviceCpp<Object,MemFunc>(aC,aF);
    }

} // namespace Net
} // namespace OpenHome

#endif // HEADER_IFACE_DEVICECPP
