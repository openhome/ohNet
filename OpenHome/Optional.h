#pragma once

#include <OpenHome/Types.h>

namespace OpenHome {

template<typename T>
class Optional
{
public:
    Optional() : iReturnPtr(nullptr) {}
    Optional(T& aReturnRef) : iReturnPtr(&aReturnRef) {}
    Optional(T* aReturnPtr) : iReturnPtr(aReturnPtr) {}
    TBool Ok() const { return iReturnPtr != nullptr; }
    T& Unwrap() const { ASSERT(Ok()); return *iReturnPtr; }
    T* Ptr() const { return iReturnPtr; }
private:
    T* iReturnPtr;
};

} // namespace OpenHome
