#include <Parser.h>
#include <Ascii.h>

using namespace Zapp;

// Class Parser

Parser::Parser() : iBuffer(Brx::Empty()), iIndex(0)
{
}

Parser::Parser(const Brx& aBuffer) : iBuffer(aBuffer), iIndex(0)
{
}

void Parser::Set(const Brx& aBuffer)
{
    iBuffer.Set(aBuffer);
    iIndex = 0;
}

TBool Parser::Finished() const
{
    return (iIndex == iBuffer.Bytes());
}

void Parser::Restart()
{
    iIndex = 0;
}


TChar Parser::At(TInt aOffset)
{
    return (iBuffer[iIndex + aOffset]);
}


void Parser::Back(TUint aOffset)
{
    ASSERT(aOffset <= iIndex);
    iIndex -= aOffset;
}

void Parser::Forward(TUint aOffset)
{
    iIndex += aOffset;
    ASSERT(iIndex <= iBuffer.Bytes());
}

Brn Parser::Remaining()
{
    return(iBuffer.Split(iIndex));
}

/// Collect the segment of ASCII text from the current position
/// up to the next delimiter, or the end of the buffer, removing
/// any whitespace at the start and the end.
/// Advance the current position to one character after the delimiter.

Brn Parser::Next(TByte aDelimiter)
{
    TUint start = iIndex;

    TUint bytes = iBuffer.Bytes();

    while (start < bytes) {
        if (!Ascii::IsWhitespace(iBuffer[start])) {
            break;
        }
        start++;
    }

    if (start == bytes) {
        iIndex = start;
        return (Brn::Empty());
    }

    TUint extra = 1;

    TUint delimiter = start;

    while (delimiter < bytes) {
        if (iBuffer[delimiter] == aDelimiter) {
            break;
        }
        delimiter++;
    }

    if (delimiter == bytes) {
        extra = 0;
    }

    TUint length = delimiter - start;

    TUint end = delimiter;

    while (length > 0) {
        if (!Ascii::IsWhitespace(iBuffer[--end])) {
            end++;
            break;
        }
        length--;
    }

    iIndex = delimiter + extra; // go one past delimiter if not end of buffer

    return(iBuffer.Split(start, end - start));
}

Brn Parser::Next()
{
    return(Next(' '));
}

Brn Parser::NextNth(TUint aNth, TByte aDelimiter)// find the Nth token using the given delimiter
{
    while(--aNth > 0)
    {
        Next(aDelimiter);
    }
    
    return(Next(aDelimiter));
}

Brn Parser::NextNoTrim(TByte aDelimiter)
{
    TUint start = iIndex;

    TUint bytes = iBuffer.Bytes();

    if (start == bytes) {
        iIndex = start;
        return (Brn::Empty());
    }

    TUint extra = 1;

    TUint delimiter = start;

    while (delimiter < bytes) {
        if (iBuffer[delimiter] == aDelimiter) {
            break;
        }
        delimiter++;
    }

    if (delimiter == bytes) {
        extra = 0;
    }

    TUint end = delimiter;

    iIndex = delimiter + extra; // go one past delimiter if not end of buffer

    return(iBuffer.Split(start, end - start));
}

Brn Parser::NextLine()
{
    TUint start = iIndex;

    TUint bytes = iBuffer.Bytes();

    while (start < bytes) { // white space before data
        if (!Ascii::IsWhitespace(iBuffer[start])) {
            break;
        }
        start++;
    }

    if (start == bytes) {
        iIndex = start;
        return (Brn::Empty());
    }

    TUint delimiter = start;

    while (delimiter < bytes) {
        if (Ascii::IsLineEnding(iBuffer[delimiter])) {
            break;
        }
        delimiter++;
    }

    TUint length = delimiter - start;

    TUint end = delimiter;

    while (length > 0) { // white space after data and before line ending
        if (!Ascii::IsWhitespace(iBuffer[--end])) {
            end++;
            break;
        }
        length--;
    }
    
    while (delimiter < bytes) { // white space after line ending
        if (!Ascii::IsWhitespace(iBuffer[delimiter])) {
            break;
        }
        delimiter++;
    }

    iIndex = delimiter; // no extra required as we are always parsing for whitespace (line endings)

    return(iBuffer.Split(start, end - start));
}

Brn Parser::NextToEnd()
{
    TUint start = iIndex;

    TUint bytes = iBuffer.Bytes();

    while (start < bytes) {
        if (!Ascii::IsWhitespace(iBuffer[start])) {
            break;
        }
        start++;
    }

    if (start == bytes) {
        iIndex = start;
        return (Brn::Empty());
    }

    TUint delimiter = bytes; // skip to end

    TUint length = delimiter - start;

    TUint end = delimiter;

    while (length > 0) {
        if (!Ascii::IsWhitespace(iBuffer[--end])) {
            end++;
            break;
        }
        length--;
    }

    iIndex = delimiter;

    return(iBuffer.Split(start, end - start));
}
