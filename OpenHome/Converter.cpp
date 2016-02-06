#include <OpenHome/Private/Converter.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Stream.h>

using namespace OpenHome;

void Converter::ToXmlEscaped(IWriter& aWriter, TByte aValue)
{
    switch (aValue) {
    case '<':
        aWriter.Write(Brn("&lt;"));
        break;
    case '>':
        aWriter.Write(Brn("&gt;"));
        break;
    case '&':
        aWriter.Write(Brn("&amp;"));
        break;
    case '\'':
        aWriter.Write(Brn("&apos;"));
        break;
    case '\"':
        aWriter.Write(Brn("&quot;"));
        break;
    default:
        aWriter.Write(aValue);
        break;
    }
}

TBool Converter::IsMultiByteChar(TByte aChar, TUint& aBytes)
{
    TBool multiByte = true;
    if ((aChar & 0xF0) == 0xF0) {
        aBytes = 4;
    }
    else if ((aChar & 0xE0) == 0xE0) {
        aBytes = 3;
    }
    else if ((aChar & 0xC0) == 0xC0) {
        aBytes = 2;
    }
    else {
        multiByte = false;
    }
    return multiByte;
}

void Converter::ToXmlEscaped(IWriter& aWriter, const Brx& aValue)
{
    TUint utf8CharBytesRemaining = 0;
    for(TUint i = 0; i < aValue.Bytes(); ++i) {
        TByte ch = aValue[i];
        if (utf8CharBytesRemaining == 0) {
            TUint bytes;
            if (IsMultiByteChar(ch, bytes)) {
                utf8CharBytesRemaining = bytes;
            }
        }
        if (utf8CharBytesRemaining > 0) {
            utf8CharBytesRemaining--;
            aWriter.Write(ch);
        }
        else {
            ToXmlEscaped(aWriter, aValue[i]);
        }
    }
}

static const TByte kBase64[64] = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
        'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
        'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
        'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
        'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
        'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
        'w', 'x', 'y', 'z', '0', '1', '2', '3',
        '4', '5', '6', '7', '8', '9', '+', '/'
};

static const TByte kDecode64[256] = {
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3e, 0xff, 0xff, 0xff, 0x3f, // + /
        0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, // 0 - 9 =
        0xff, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, // A - O
        0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0xff, 0xff, 0xff, 0xff, 0xff, // P - Z
        0xff, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, // a - o
        0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f, 0x30, 0x31, 0x32, 0x33, 0xff, 0xff, 0xff, 0xff, 0xff, // p - z
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
};

void Converter::ToBase64(IWriter& aWriter, const Brx& aValue)
{
    TUint b = 0;
    TByte block[3];
    const TByte* p = aValue.Ptr();
    const TByte* end = p + aValue.Bytes();
    TByte enc[4];
    Brn encBuf(enc, sizeof(enc));

    while (p < end) {
        block[b++] = *p++;
        if (b == 3) {
            TByte index0 = block[0] >> 2;
            TByte index1 = (block[0] & 0x03) << 4 | block[1] >> 4;
            TByte index2 = (block[1] & 0x0f) << 2 | block[2] >> 6;
            TByte index3 = (block[2] & 0x3f);

            enc[0] = kBase64[index0];
            enc[1] = kBase64[index1];
            enc[2] = kBase64[index2];
            enc[3] = kBase64[index3];
            aWriter.Write(encBuf);

            b = 0;
        }
    }

    if (b == 1) {
        TByte index0 = block[0] >> 2;
        TByte index1 = (block[0] & 0x03) << 4;
        enc[0] = kBase64[index0];
        enc[1] = kBase64[index1];
        enc[2] = '=';
        enc[3] = '=';
        aWriter.Write(encBuf);
    }
    else if (b == 2) {
        TByte index0 = block[0] >> 2;
        TByte index1 = (block[0] & 0x03) << 4 | block[1] >> 4;
        TByte index2 = (block[1] & 0x0f) << 2;
        enc[0] = kBase64[index0];
        enc[1] = kBase64[index1];
        enc[2] = kBase64[index2];
        enc[3] = '=';
        aWriter.Write(encBuf);
    }
}

void Converter::FromBase64(Bwx& aValue)
{
    TUint b = 0;
    TByte block[4];
    TByte* dest = const_cast<TByte*>(aValue.Ptr());
    const TByte* p = dest;
    const TByte* end = p + aValue.Bytes();

    for (; p < end; p++) {

        TByte d = kDecode64[*p];
        if (d > 64) {
            continue;
        }
        block[b++] = d;
        if (b >= 4) {
            *dest++ = block[0] << 2 | block[1] >> 4;
            *dest++ = block[1] << 4 | block[2] >> 2;
            *dest++ = block[2] << 6 | block[3];
            b = 0;
        }
    }

    if (b > 1) {
        *dest++ = block[0] << 2 | block[1] >> 4;
    }
    if (b > 2) {
        *dest++ = block[1] << 4 | block[2] >> 2;
    }

    aValue.SetBytes(dest - aValue.Ptr());
}

void Converter::FromXmlEscaped(Bwx& aValue)
{
    TUint j = 0;
    TUint bytes = aValue.Bytes();
    TUint utf8CharBytesRemaining = 0;

    for (TUint i = 0; i < bytes; i++) {
        TByte ch = aValue[i];
        if (utf8CharBytesRemaining == 0) {
            TUint multibytes = 0;
            if (IsMultiByteChar(ch, multibytes)) {
                utf8CharBytesRemaining = multibytes;
            }
        }
        if (utf8CharBytesRemaining > 0) {
            utf8CharBytesRemaining--;
            aValue[j++] = aValue[i];
            continue;
        }

        if (aValue[i] != '&') {
            aValue[j++] = aValue[i];
            continue;
        }
        if (++i < bytes) {
            if (aValue[i] == 'l') {
                if (++i < bytes) {
                    if (aValue[i] == 't') {
                        if (++i < bytes) {
                            if (aValue[i] == ';') {
                                aValue[j++] = '<';
                                continue;
                            }
                        }
                    }
                }
            }
            else if (aValue[i] == 'g') {
                if (++i < bytes) {
                    if (aValue[i] == 't') {
                        if (++i < bytes) {
                            if (aValue[i] == ';') {
                                aValue[j++] = '>';
                                continue;
                            }
                        }
                    }
                }
            }
            else if (aValue[i] == 'a') {
                if (++i < bytes) {
                    if (aValue[i] == 'm') {
                        if (++i < bytes) {
                            if (aValue[i] == 'p') {
                                if (++i < bytes) {
                                    if (aValue[i] == ';') {
                                        aValue[j++] = '&';
                                        continue;
                                    }
                                }
                            }
                        }
                    }
                    else if (aValue[i] == 'p') {
                        if (++i < bytes) {
                            if (aValue[i] == 'o') {
                                if (++i < bytes) {
                                    if (aValue[i] == 's') {
                                        if (++i < bytes) {
                                            if (aValue[i] == ';') {
                                                aValue[j++] = '\'';
                                                continue;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else if (aValue[i] == 'q') {
                if (++i < bytes) {
                    if (aValue[i] == 'u') {
                        if (++i < bytes) {
                            if (aValue[i] == 'o') {
                                if (++i < bytes) {
                                    if (aValue[i] == 't') {
                                        if (++i < bytes) {
                                            if (aValue[i] == ';') {
                                                aValue[j++] = '\"';
                                                continue;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    aValue.SetBytes(j);
}

TUint64 Converter::BeUint64At(const Brx& aBuf, TUint aIndex)
{
    TUint64 val = 0;
    for (TInt i=sizeof(val)-1; i>=0; i--) {
        TUint64 byte = aBuf[aIndex++];
        val += byte << (i*8);
    }
    return val;
}

TUint32 Converter::BeUint32At(const Brx& aBuf, TUint aIndex)
{
    TUint b[4];
    for (TUint i=0; i<4; i++) {
        b[i] = aBuf[aIndex++];
    }
    return ((b[0] << 24) | (b[1] << 16) | (b[2] << 8) | b[3]);
}

TUint16 Converter::BeUint16At(const Brx& aBuf, TUint aIndex)
{
    TUint b[2];
    for (TUint i=0; i<2; i++) {
        b[i] = aBuf[aIndex++];
    }
    return (TUint16)((b[0] << 8) | b[1]);
}

TUint32 Converter::LeUint32At(const Brx& aBuf, TUint aIndex)
{
    TUint b[4];
    for (TUint i=0; i<4; i++) {
        b[i] = aBuf[aIndex++];
    }
    return ((b[3] << 24) | (b[2] << 16) | (b[1] << 8) | b[0]);
}

TUint16 Converter::LeUint16At(const Brx& aBuf, TUint aIndex)
{
    TUint b[2];
    for (TUint i=0; i<2; i++) {
        b[i] = aBuf[aIndex++];
    }
    return (TUint16)((b[1] << 8) | b[0]);
}
