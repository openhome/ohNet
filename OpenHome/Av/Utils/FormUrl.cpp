#include <OpenHome/Av/Utils/FormUrl.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Ascii.h>

using namespace OpenHome;
using namespace OpenHome::Av;

void FormUrl::Encode(IWriter& aWriter, const Brx& aSrc)
{ // static
    const TUint bytes = aSrc.Bytes();
    for (TUint i=0; i<bytes; i++) {
        TChar ch = aSrc[i];
        if (Ascii::IsAlphabetic(ch) || Ascii::IsDigit(ch)) {
            aWriter.Write(ch);
        }
        else if (ch == ' ') {
            aWriter.Write('+');
        }
        else {
            aWriter.Write('%');
            WriterAscii writerAscii(aWriter);
            writerAscii.WriteHex(static_cast<TByte>(ch));
        }
    }
}
