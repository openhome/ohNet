#ifndef HEADER_OPTIONAL
#define HEADER_OPTIONAL

#include <OpenHome/Types.h>

namespace OpenHome {

template<typename T>
class Optional
{
public:
    Optional() : iReturnPtr(NULL) {}
    Optional(T& aReturnRef) : iReturnPtr(&aReturnRef) {}
    Optional(T* aReturnPtr) : iReturnPtr(aReturnPtr) {}
    Optional(const Optional& aValue) { iReturnPtr = aValue.iReturnPtr; }
    Optional& operator=(const Optional& aValue) { iReturnPtr = aValue.iReturnPtr;  return *this; }
    Optional& operator=(T& aValue) { iReturnPtr = &aValue; return *this; }
    void Clear() { iReturnPtr = NULL; }
    TBool Ok() const { return iReturnPtr != NULL; }
    T& Unwrap() const { ASSERT(Ok()); return *iReturnPtr; }
    T* Ptr() const { return iReturnPtr; }
    operator TBool() { return Ok(); }
private:
    T* iReturnPtr;
};

} // namespace OpenHome

#endif // HEADER_OPTIONAL
