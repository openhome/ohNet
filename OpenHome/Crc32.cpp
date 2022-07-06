#include <OpenHome/Private/Crc32.h>

#include <OpenHome/Private/Printer.h>

using namespace OpenHome;

std::vector<TUint> Crc32TableInitialiser::InitialiseTable(TUint32 aPolynomial)
{
    std::vector<TUint32> table;
    for (TUint i = 0; i < 256; i++) {
        TUint32 entry = i;
        for (TUint j = 0; j < 8; j++) {
            if ((entry & 1) == 1) {
                entry = (entry >> 1) ^ aPolynomial;
            }
            else {
                entry = entry >> 1;
            }
        }
        table.push_back(entry);
    }
    return table;
}


// Crc32

TUint32 Crc32::Compute(const Brx& aBuffer)
{
    TUint32 crc = kDefaultSeed;
    std::vector<TUint32> table = Crc32TableInitialiser::InitialiseTable(kDefaultPolynomial);

    for (TUint i = 0; i < aBuffer.Bytes(); i++) {
        crc = (crc >> 8) ^ table[(aBuffer[i] ^ crc) & 0xff];
    }
    return ~crc;
}

TUint32 Crc32::Compute(const Brx& aBuffer, TUint32 aSeed)
{
    TUint32 crc = aSeed;
    std::vector<TUint32> table = Crc32TableInitialiser::InitialiseTable(kDefaultPolynomial);

    for (TUint i = 0; i < aBuffer.Bytes(); i++) {
        crc = (crc >> 8) ^ table[(aBuffer[i] ^ crc) & 0xff];
    }
    return ~crc;
}

TUint32 Crc32::Compute(IReader& aReader)
{
    TUint32 crc = kDefaultSeed;
    std::vector<TUint32> table = Crc32TableInitialiser::InitialiseTable(kDefaultPolynomial);

    try {
        for (;;) {
            Brn buf = aReader.Read(kDefaultReadBytes);
            for (TUint i = 0; i < buf.Bytes(); i++) {
                crc = (crc >> 8) ^ table[(buf[i] ^ crc) & 0xff];
            }
        }
    }
    catch (ReaderError&) {}
    return ~crc;
}

TUint32 Crc32::Compute(IReader& aReader, TUint32 aSeed)
{
    TUint32 crc = aSeed;
    std::vector<TUint32> table = Crc32TableInitialiser::InitialiseTable(kDefaultPolynomial);

    try {
        for (;;) {
            Brn buf = aReader.Read(kDefaultReadBytes);
            for (TUint i = 0; i < buf.Bytes(); i++) {
                crc = (crc >> 8) ^ table[(buf[i] ^ crc) & 0xff];
            }
        }
    }
    catch (ReaderError&) {}
    return ~crc;
}


// Crc32Generator

Crc32Generator::Crc32Generator(TUint aSeed)
    : iCrc32(aSeed)
    , iFinished(false)
{
    iTable = Crc32TableInitialiser::InitialiseTable(Crc32::kDefaultPolynomial);
}

Crc32Generator::Crc32Generator(const Brx& aBuffer, TUint aSeed)
    : Crc32Generator(aSeed)
{
    Append(aBuffer);
}

void Crc32Generator::Append(const Brx& aBuffer)
{
    if (iFinished) {
        THROW(CrcGenerationFinished);
    }

    for (TUint i = 0; i < aBuffer.Bytes(); i++) {
        iCrc32 = (iCrc32 >> 8) ^ iTable[(aBuffer[i] ^ iCrc32) & 0xff];
    }
}

TUint32 Crc32Generator::Result()
{
    iFinished = true;
    return ~iCrc32;
}
