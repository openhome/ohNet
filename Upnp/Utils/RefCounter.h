#ifndef HEADER_OPENHOME_REFCOUNTER
#define HEADER_OPENHOME_REFCOUNTER

#include <Standard.h>
#include <OhNetTypes.h>
#include <Thread.h>

namespace OpenHome {

class RefCounter
{
public:
    RefCounter();
    virtual ~RefCounter();
    void IncRef();
    void DecRef();

private:
    AtomicInt iCounter; 
};

} // namespace OpenHome

#endif  // HEADER_OPENHOME_REFCOUNTER
