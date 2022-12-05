#ifndef HEADER_SHA
#define HEADER_SHA

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>

namespace OpenHome {

class SHA1
{
public:
    static const TUint kBlockSize = 20;
public:
    static void Compute(const Brx& aData, Bwx& aHash);
};

class SHA256
{
public:
    static const TUint kBlockSize = 32;
public:
    static void Compute(const Brx& aData, Bwx& aHash);
};

} // namespace OpenHome

#endif // HEADER_SHA