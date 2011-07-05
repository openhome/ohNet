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
    void IncRef();
    void DecRef();

protected:
    virtual ~RefCounter();
    
private:
    AtomicInt iCounter; 
};

} // namespace OpenHome

#endif  // HEADER_OPENHOME_REFCOUNTER
