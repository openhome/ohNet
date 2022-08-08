#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Stream.h>
#include <vector>

namespace OpenHome {

class Crc32
{
private:
    static const TUint32 kDefaultPolynomial = 0xedb88320;
    static const TUint32 kDefaultSeed = 0xffffffff;
    static const TUint kDefaultReadBytes = 2048;
public:
    static TUint32 Compute(const Brx& aBuffer);
    static TUint32 Compute(const Brx& aBuffer, TUint32 aSeed);
    static TUint32 Compute(IReader& aReader);
    static TUint32 Compute(IReader& aReader, TUint32 aSeed);
private:
    static std::vector<TUint32> InitialiseTable(TUint32 aPolynomial);
};

}