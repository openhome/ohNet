#include <OpenHome/Private/Crc32.h>

#include <OpenHome/Private/Printer.h>

using namespace OpenHome;

TUint32 Crc32::Compute(const Brx& aBuffer)
{
    TUint32 crc = kDefaultSeed;
    std::vector<TUint32> table = InitialiseTable(kDefaultPolynomial);

    for (TUint i = 0; i < aBuffer.Bytes(); i++) {
        crc = (crc >> 8) ^ table[(aBuffer[i] ^ crc) & 0xff];
    }
    return ~crc;
}

TUint32 Crc32::Compute(const Brx& aBuffer, TUint32 aSeed)
{
    TUint32 crc = aSeed;
    std::vector<TUint32> table = InitialiseTable(kDefaultPolynomial);

    for (TUint i = 0; i < aBuffer.Bytes(); i++) {
        crc = (crc >> 8) ^ table[(aBuffer[i] ^ crc) & 0xff];
    }
    return ~crc;
}

TUint32 Crc32::Compute(IReader& aReader)
{
    TUint32 crc = kDefaultSeed;
    std::vector<TUint32> table = InitialiseTable(kDefaultPolynomial);

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
    std::vector<TUint32> table = InitialiseTable(kDefaultPolynomial);

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

std::vector<TUint> Crc32::InitialiseTable(TUint32 aPolynomial)
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