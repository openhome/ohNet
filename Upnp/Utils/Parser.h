#ifndef HEADER_ASCII_PARSER
#define HEADER_ASCII_PARSER

#include <Standard.h>
#include <ZappTypes.h>
#include <Buffer.h>

namespace Zapp
{

class Parser
{
public:
    Parser();
    Parser(const Brx& aBuffer);
    void Set(const Brx& aBuffer);
    TBool Finished() const; // no more bytes left to parse
    Brn Next(); // delimiter = ' '
    Brn NextLine(); // delimiter = line ending ('\r' or '\n')
    Brn NextToEnd(); // no delimiter: remaing bytes from current parser location trimmed at start and end
    Brn Next(TByte aDelimiter);
    Brn NextNoTrim(TByte aDelimiter);
    Brn NextNth(TUint aNth, TByte aDelimiter); //get the Nth token in a delimited string
    void Restart(); // start from beginning of buffer
    TChar At(TInt aOffset); // relative to current position
    void  Back(TUint aOffset); // relative to current position
    void  Forward(TUint aOffset); // relative to current position
    Brn Remaining(); // all remaing bytes from current parser location
    TUint Index() const { return iIndex; }
private:
    Brn iBuffer;
    TUint iIndex;
};

} // namespace Zapp

#endif // HEADER_ASCII_PARSER
