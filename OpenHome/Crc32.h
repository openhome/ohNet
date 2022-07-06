#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Exception.h>
#include <vector>

EXCEPTION(CrcGenerationFinished);

namespace OpenHome {

class Crc32TableInitialiser
{
public:
    static std::vector<TUint32> InitialiseTable(TUint32 aPolynomial);
};

class Crc32
{
public:
    static const TUint32 kDefaultPolynomial = 0xedb88320;
    static const TUint32 kDefaultSeed = 0xffffffff;
    static const TUint kDefaultReadBytes = 2048;
public:
    static TUint32 Compute(const Brx& aBuffer);
    static TUint32 Compute(const Brx& aBuffer, TUint32 aSeed);
    static TUint32 Compute(IReader& aReader);
    static TUint32 Compute(IReader& aReader, TUint32 aSeed);    
};

class Crc32Generator
{
public:
    Crc32Generator(TUint aSeed = Crc32::kDefaultSeed);
    Crc32Generator(const Brx& aBuffer, TUint aSeed = Crc32::kDefaultSeed);
public:
    void Append(const Brx& aBuffer);
    TUint32 Result();
private:
    TUint32 iCrc32;
    TBool iFinished;
    std::vector<TUint32> iTable;
};

}