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
    void IncRef() const;
    void DecRef() const;

protected:
    virtual ~RefCounter();
    
private:
    mutable AtomicInt iCounter; 
};

} // namespace OpenHome

#endif  // HEADER_OPENHOME_REFCOUNTER
