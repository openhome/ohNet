#ifndef HEADER_STANDARD
#define HEADER_STANDARD

#include <OhNetTypes.h>
#include <Exception.h>

namespace OpenHome {

#define ASSERT(x)                             \
    if(!(x)) {                                \
        CallAssertHandler(__FILE__,__LINE__); \
    }

#define ASSERTS()  CallAssertHandler(__FILE__,__LINE__)

class INonCopyable
{
protected:
    INonCopyable() {}
private:
    INonCopyable(const INonCopyable &);
    void operator=(const INonCopyable &);
};

} // namespace OpenHome

#endif // HEADER_STANDARD
