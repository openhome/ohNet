#ifndef HEADER_OPENHOME_REFCOUNTER
#define HEADER_OPENHOME_REFCOUNTER

#include <OpenHome/Private/Standard.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Thread.h>

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
