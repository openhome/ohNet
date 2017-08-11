#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Parser.h>
#include <OpenHome/Private/Uri.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Os.h>

#include <limits>

using namespace OpenHome;
using namespace OpenHome::TestFramework;

class SuiteAscii : public Suite
{
public:
    SuiteAscii() : Suite("Ascii") {}
    void Test();
};

void SuiteAscii::Test()
{
    // Hex

    TEST(Ascii::IsHex('0'));
    TEST(Ascii::IsHex('1'));
    TEST(Ascii::IsHex('2'));
    TEST(Ascii::IsHex('3'));
    TEST(Ascii::IsHex('4'));
    TEST(Ascii::IsHex('5'));
    TEST(Ascii::IsHex('6'));
    TEST(Ascii::IsHex('7'));
    TEST(Ascii::IsHex('8'));
    TEST(Ascii::IsHex('9'));
    TEST(Ascii::IsHex('A'));
    TEST(Ascii::IsHex('B'));
    TEST(Ascii::IsHex('C'));
    TEST(Ascii::IsHex('D'));
    TEST(Ascii::IsHex('E'));
    TEST(Ascii::IsHex('F'));
    TEST(Ascii::IsHex('a'));
    TEST(Ascii::IsHex('b'));
    TEST(Ascii::IsHex('c'));
    TEST(Ascii::IsHex('d'));
    TEST(Ascii::IsHex('e'));
    TEST(Ascii::IsHex('f'));
    
    TEST(!Ascii::IsHex('G'));
    TEST(!Ascii::IsHex('@'));
    TEST(!Ascii::IsHex('G'));
    TEST(!Ascii::IsHex('g'));
    TEST(!Ascii::IsHex('/'));
    TEST(!Ascii::IsHex(':'));
    
    // Digits
    
    TEST(Ascii::IsDigit('0'));
    TEST(Ascii::IsDigit('1'));
    TEST(Ascii::IsDigit('2'));
    TEST(Ascii::IsDigit('3'));
    TEST(Ascii::IsDigit('4'));
    TEST(Ascii::IsDigit('5'));
    TEST(Ascii::IsDigit('6'));
    TEST(Ascii::IsDigit('7'));
    TEST(Ascii::IsDigit('8'));
    TEST(Ascii::IsDigit('9'));
    
    TEST(!Ascii::IsWhitespace('0'));
    TEST(!Ascii::IsWhitespace('1'));
    TEST(!Ascii::IsWhitespace('2'));
    TEST(!Ascii::IsWhitespace('3'));
    TEST(!Ascii::IsWhitespace('4'));
    TEST(!Ascii::IsWhitespace('5'));
    TEST(!Ascii::IsWhitespace('6'));
    TEST(!Ascii::IsWhitespace('7'));
    TEST(!Ascii::IsWhitespace('8'));
    TEST(!Ascii::IsWhitespace('9'));
    
    TEST(!Ascii::IsAlphabetic('0'));
    TEST(!Ascii::IsAlphabetic('1'));
    TEST(!Ascii::IsAlphabetic('2'));
    TEST(!Ascii::IsAlphabetic('3'));
    TEST(!Ascii::IsAlphabetic('4'));
    TEST(!Ascii::IsAlphabetic('5'));
    TEST(!Ascii::IsAlphabetic('6'));
    TEST(!Ascii::IsAlphabetic('7'));
    TEST(!Ascii::IsAlphabetic('8'));
    TEST(!Ascii::IsAlphabetic('9'));

    TEST(!Ascii::IsUpperCase('0'));
    TEST(!Ascii::IsUpperCase('1'));
    TEST(!Ascii::IsUpperCase('2'));
    TEST(!Ascii::IsUpperCase('3'));
    TEST(!Ascii::IsUpperCase('4'));
    TEST(!Ascii::IsUpperCase('5'));
    TEST(!Ascii::IsUpperCase('6'));
    TEST(!Ascii::IsUpperCase('7'));
    TEST(!Ascii::IsUpperCase('8'));
    TEST(!Ascii::IsUpperCase('9'));
    
    TEST(!Ascii::IsLowerCase('0'));
    TEST(!Ascii::IsLowerCase('1'));
    TEST(!Ascii::IsLowerCase('2'));
    TEST(!Ascii::IsLowerCase('3'));
    TEST(!Ascii::IsLowerCase('4'));
    TEST(!Ascii::IsLowerCase('5'));
    TEST(!Ascii::IsLowerCase('6'));
    TEST(!Ascii::IsLowerCase('7'));
    TEST(!Ascii::IsLowerCase('8'));
    TEST(!Ascii::IsLowerCase('9'));
    
    // Digit boundaries
    
    TEST(!Ascii::IsDigit('/'));
    TEST(!Ascii::IsDigit(':'));
    
    TEST(!Ascii::IsWhitespace('/'));
    TEST(!Ascii::IsWhitespace(':'));
    
    TEST(!Ascii::IsAlphabetic('/'));
    TEST(!Ascii::IsAlphabetic(':'));

    TEST(!Ascii::IsUpperCase('/'));
    TEST(!Ascii::IsUpperCase(':'));
    
    TEST(!Ascii::IsLowerCase('/'));
    TEST(!Ascii::IsLowerCase(':'));
    
    // White Space
    
    TEST(!Ascii::IsDigit(0x00));
    TEST(!Ascii::IsDigit(0x01));
    TEST(!Ascii::IsDigit(0x02));
    TEST(!Ascii::IsDigit(0x03));
    TEST(!Ascii::IsDigit(0x04));
    TEST(!Ascii::IsDigit(0x05));
    TEST(!Ascii::IsDigit(0x06));
    TEST(!Ascii::IsDigit(0x07));
    TEST(!Ascii::IsDigit(0x08));
    TEST(!Ascii::IsDigit(0x09));
    TEST(!Ascii::IsDigit(0x0a));
    TEST(!Ascii::IsDigit(0x0b));
    TEST(!Ascii::IsDigit(0x0c));
    TEST(!Ascii::IsDigit(0x0d));
    TEST(!Ascii::IsDigit(0x0e));
    TEST(!Ascii::IsDigit(0x0f));
    TEST(!Ascii::IsDigit(0x10));
    TEST(!Ascii::IsDigit(0x11));
    TEST(!Ascii::IsDigit(0x12));
    TEST(!Ascii::IsDigit(0x13));
    TEST(!Ascii::IsDigit(0x14));
    TEST(!Ascii::IsDigit(0x15));
    TEST(!Ascii::IsDigit(0x16));
    TEST(!Ascii::IsDigit(0x17));
    TEST(!Ascii::IsDigit(0x18));
    TEST(!Ascii::IsDigit(0x19));
    TEST(!Ascii::IsDigit(0x1a));
    TEST(!Ascii::IsDigit(0x1b));
    TEST(!Ascii::IsDigit(0x1c));
    TEST(!Ascii::IsDigit(0x1d));
    TEST(!Ascii::IsDigit(0x1e));
    TEST(!Ascii::IsDigit(0x1f));
    TEST(!Ascii::IsDigit(0x20));
    TEST(!Ascii::IsDigit(0x21));
    
    TEST(Ascii::IsWhitespace(0x00));
    TEST(Ascii::IsWhitespace(0x01));
    TEST(Ascii::IsWhitespace(0x02));
    TEST(Ascii::IsWhitespace(0x03));
    TEST(Ascii::IsWhitespace(0x04));
    TEST(Ascii::IsWhitespace(0x05));
    TEST(Ascii::IsWhitespace(0x06));
    TEST(Ascii::IsWhitespace(0x07));
    TEST(Ascii::IsWhitespace(0x08));
    TEST(Ascii::IsWhitespace(0x09));
    TEST(Ascii::IsWhitespace(0x0a));
    TEST(Ascii::IsWhitespace(0x0b));
    TEST(Ascii::IsWhitespace(0x0c));
    TEST(Ascii::IsWhitespace(0x0d));
    TEST(Ascii::IsWhitespace(0x0e));
    TEST(Ascii::IsWhitespace(0x0f));
    TEST(Ascii::IsWhitespace(0x10));
    TEST(Ascii::IsWhitespace(0x11));
    TEST(Ascii::IsWhitespace(0x12));
    TEST(Ascii::IsWhitespace(0x13));
    TEST(Ascii::IsWhitespace(0x14));
    TEST(Ascii::IsWhitespace(0x15));
    TEST(Ascii::IsWhitespace(0x16));
    TEST(Ascii::IsWhitespace(0x17));
    TEST(Ascii::IsWhitespace(0x18));
    TEST(Ascii::IsWhitespace(0x19));
    TEST(Ascii::IsWhitespace(0x1a));
    TEST(Ascii::IsWhitespace(0x1b));
    TEST(Ascii::IsWhitespace(0x1c));
    TEST(Ascii::IsWhitespace(0x1d));
    TEST(Ascii::IsWhitespace(0x1e));
    TEST(Ascii::IsWhitespace(0x1f));
    TEST(Ascii::IsWhitespace(0x20));
    TEST(!Ascii::IsWhitespace(0x21));
    
    TEST(!Ascii::IsAlphabetic(0x00));
    TEST(!Ascii::IsAlphabetic(0x01));
    TEST(!Ascii::IsAlphabetic(0x02));
    TEST(!Ascii::IsAlphabetic(0x03));
    TEST(!Ascii::IsAlphabetic(0x04));
    TEST(!Ascii::IsAlphabetic(0x05));
    TEST(!Ascii::IsAlphabetic(0x06));
    TEST(!Ascii::IsAlphabetic(0x07));
    TEST(!Ascii::IsAlphabetic(0x08));
    TEST(!Ascii::IsAlphabetic(0x09));
    TEST(!Ascii::IsAlphabetic(0x0a));
    TEST(!Ascii::IsAlphabetic(0x0b));
    TEST(!Ascii::IsAlphabetic(0x0c));
    TEST(!Ascii::IsAlphabetic(0x0d));
    TEST(!Ascii::IsAlphabetic(0x0e));
    TEST(!Ascii::IsAlphabetic(0x0f));
    TEST(!Ascii::IsAlphabetic(0x10));
    TEST(!Ascii::IsAlphabetic(0x11));
    TEST(!Ascii::IsAlphabetic(0x12));
    TEST(!Ascii::IsAlphabetic(0x13));
    TEST(!Ascii::IsAlphabetic(0x14));
    TEST(!Ascii::IsAlphabetic(0x15));
    TEST(!Ascii::IsAlphabetic(0x16));
    TEST(!Ascii::IsAlphabetic(0x17));
    TEST(!Ascii::IsAlphabetic(0x18));
    TEST(!Ascii::IsAlphabetic(0x19));
    TEST(!Ascii::IsAlphabetic(0x1a));
    TEST(!Ascii::IsAlphabetic(0x1b));
    TEST(!Ascii::IsAlphabetic(0x1c));
    TEST(!Ascii::IsAlphabetic(0x1d));
    TEST(!Ascii::IsAlphabetic(0x1e));
    TEST(!Ascii::IsAlphabetic(0x1f));
    TEST(!Ascii::IsAlphabetic(0x20));
    TEST(!Ascii::IsAlphabetic(0x21));
    
    TEST(!Ascii::IsUpperCase(0x00));
    TEST(!Ascii::IsUpperCase(0x01));
    TEST(!Ascii::IsUpperCase(0x02));
    TEST(!Ascii::IsUpperCase(0x03));
    TEST(!Ascii::IsUpperCase(0x04));
    TEST(!Ascii::IsUpperCase(0x05));
    TEST(!Ascii::IsUpperCase(0x06));
    TEST(!Ascii::IsUpperCase(0x07));
    TEST(!Ascii::IsUpperCase(0x08));
    TEST(!Ascii::IsUpperCase(0x09));
    TEST(!Ascii::IsUpperCase(0x0a));
    TEST(!Ascii::IsUpperCase(0x0b));
    TEST(!Ascii::IsUpperCase(0x0c));
    TEST(!Ascii::IsUpperCase(0x0d));
    TEST(!Ascii::IsUpperCase(0x0e));
    TEST(!Ascii::IsUpperCase(0x0f));
    TEST(!Ascii::IsUpperCase(0x10));
    TEST(!Ascii::IsUpperCase(0x11));
    TEST(!Ascii::IsUpperCase(0x12));
    TEST(!Ascii::IsUpperCase(0x13));
    TEST(!Ascii::IsUpperCase(0x14));
    TEST(!Ascii::IsUpperCase(0x15));
    TEST(!Ascii::IsUpperCase(0x16));
    TEST(!Ascii::IsUpperCase(0x17));
    TEST(!Ascii::IsUpperCase(0x18));
    TEST(!Ascii::IsUpperCase(0x19));
    TEST(!Ascii::IsUpperCase(0x1a));
    TEST(!Ascii::IsUpperCase(0x1b));
    TEST(!Ascii::IsUpperCase(0x1c));
    TEST(!Ascii::IsUpperCase(0x1d));
    TEST(!Ascii::IsUpperCase(0x1e));
    TEST(!Ascii::IsUpperCase(0x1f));
    TEST(!Ascii::IsUpperCase(0x20));
    TEST(!Ascii::IsUpperCase(0x21));
    
    TEST(!Ascii::IsLowerCase(0x00));
    TEST(!Ascii::IsLowerCase(0x01));
    TEST(!Ascii::IsLowerCase(0x02));
    TEST(!Ascii::IsLowerCase(0x03));
    TEST(!Ascii::IsLowerCase(0x04));
    TEST(!Ascii::IsLowerCase(0x05));
    TEST(!Ascii::IsLowerCase(0x06));
    TEST(!Ascii::IsLowerCase(0x07));
    TEST(!Ascii::IsLowerCase(0x08));
    TEST(!Ascii::IsLowerCase(0x09));
    TEST(!Ascii::IsLowerCase(0x0a));
    TEST(!Ascii::IsLowerCase(0x0b));
    TEST(!Ascii::IsLowerCase(0x0c));
    TEST(!Ascii::IsLowerCase(0x0d));
    TEST(!Ascii::IsLowerCase(0x0e));
    TEST(!Ascii::IsLowerCase(0x0f));
    TEST(!Ascii::IsLowerCase(0x10));
    TEST(!Ascii::IsLowerCase(0x11));
    TEST(!Ascii::IsLowerCase(0x12));
    TEST(!Ascii::IsLowerCase(0x13));
    TEST(!Ascii::IsLowerCase(0x14));
    TEST(!Ascii::IsLowerCase(0x15));
    TEST(!Ascii::IsLowerCase(0x16));
    TEST(!Ascii::IsLowerCase(0x17));
    TEST(!Ascii::IsLowerCase(0x18));
    TEST(!Ascii::IsLowerCase(0x19));
    TEST(!Ascii::IsLowerCase(0x1a));
    TEST(!Ascii::IsLowerCase(0x1b));
    TEST(!Ascii::IsLowerCase(0x1c));
    TEST(!Ascii::IsLowerCase(0x1d));
    TEST(!Ascii::IsLowerCase(0x1e));
    TEST(!Ascii::IsLowerCase(0x1f));
    TEST(!Ascii::IsLowerCase(0x20));
    TEST(!Ascii::IsLowerCase(0x21));
    
    // Alphabet
    
    TEST(!Ascii::IsDigit('a'));
    TEST(!Ascii::IsDigit('b'));
    TEST(!Ascii::IsDigit('c'));
    TEST(!Ascii::IsDigit('d'));
    TEST(!Ascii::IsDigit('e'));
    TEST(!Ascii::IsDigit('f'));
    TEST(!Ascii::IsDigit('g'));
    TEST(!Ascii::IsDigit('h'));
    TEST(!Ascii::IsDigit('i'));
    TEST(!Ascii::IsDigit('j'));
    TEST(!Ascii::IsDigit('k'));
    TEST(!Ascii::IsDigit('l'));
    TEST(!Ascii::IsDigit('m'));
    TEST(!Ascii::IsDigit('n'));
    TEST(!Ascii::IsDigit('o'));
    TEST(!Ascii::IsDigit('p'));
    TEST(!Ascii::IsDigit('q'));
    TEST(!Ascii::IsDigit('r'));
    TEST(!Ascii::IsDigit('s'));
    TEST(!Ascii::IsDigit('t'));
    TEST(!Ascii::IsDigit('u'));
    TEST(!Ascii::IsDigit('v'));
    TEST(!Ascii::IsDigit('w'));
    TEST(!Ascii::IsDigit('x'));
    TEST(!Ascii::IsDigit('y'));
    TEST(!Ascii::IsDigit('z'));
    TEST(!Ascii::IsDigit('A'));
    TEST(!Ascii::IsDigit('B'));
    TEST(!Ascii::IsDigit('C'));
    TEST(!Ascii::IsDigit('D'));
    TEST(!Ascii::IsDigit('E'));
    TEST(!Ascii::IsDigit('F'));
    TEST(!Ascii::IsDigit('G'));
    TEST(!Ascii::IsDigit('H'));
    TEST(!Ascii::IsDigit('I'));
    TEST(!Ascii::IsDigit('J'));
    TEST(!Ascii::IsDigit('K'));
    TEST(!Ascii::IsDigit('L'));
    TEST(!Ascii::IsDigit('M'));
    TEST(!Ascii::IsDigit('N'));
    TEST(!Ascii::IsDigit('O'));
    TEST(!Ascii::IsDigit('P'));
    TEST(!Ascii::IsDigit('Q'));
    TEST(!Ascii::IsDigit('R'));
    TEST(!Ascii::IsDigit('S'));
    TEST(!Ascii::IsDigit('T'));
    TEST(!Ascii::IsDigit('U'));
    TEST(!Ascii::IsDigit('V'));
    TEST(!Ascii::IsDigit('W'));
    TEST(!Ascii::IsDigit('X'));
    TEST(!Ascii::IsDigit('Y'));
    TEST(!Ascii::IsDigit('Z'));
    
    TEST(!Ascii::IsWhitespace('a'));
    TEST(!Ascii::IsWhitespace('b'));
    TEST(!Ascii::IsWhitespace('c'));
    TEST(!Ascii::IsWhitespace('d'));
    TEST(!Ascii::IsWhitespace('e'));
    TEST(!Ascii::IsWhitespace('f'));
    TEST(!Ascii::IsWhitespace('g'));
    TEST(!Ascii::IsWhitespace('h'));
    TEST(!Ascii::IsWhitespace('i'));
    TEST(!Ascii::IsWhitespace('j'));
    TEST(!Ascii::IsWhitespace('k'));
    TEST(!Ascii::IsWhitespace('l'));
    TEST(!Ascii::IsWhitespace('m'));
    TEST(!Ascii::IsWhitespace('n'));
    TEST(!Ascii::IsWhitespace('o'));
    TEST(!Ascii::IsWhitespace('p'));
    TEST(!Ascii::IsWhitespace('q'));
    TEST(!Ascii::IsWhitespace('r'));
    TEST(!Ascii::IsWhitespace('s'));
    TEST(!Ascii::IsWhitespace('t'));
    TEST(!Ascii::IsWhitespace('u'));
    TEST(!Ascii::IsWhitespace('v'));
    TEST(!Ascii::IsWhitespace('w'));
    TEST(!Ascii::IsWhitespace('x'));
    TEST(!Ascii::IsWhitespace('y'));
    TEST(!Ascii::IsWhitespace('z'));
    TEST(!Ascii::IsWhitespace('A'));
    TEST(!Ascii::IsWhitespace('B'));
    TEST(!Ascii::IsWhitespace('C'));
    TEST(!Ascii::IsWhitespace('D'));
    TEST(!Ascii::IsWhitespace('E'));
    TEST(!Ascii::IsWhitespace('F'));
    TEST(!Ascii::IsWhitespace('G'));
    TEST(!Ascii::IsWhitespace('H'));
    TEST(!Ascii::IsWhitespace('I'));
    TEST(!Ascii::IsWhitespace('J'));
    TEST(!Ascii::IsWhitespace('K'));
    TEST(!Ascii::IsWhitespace('L'));
    TEST(!Ascii::IsWhitespace('M'));
    TEST(!Ascii::IsWhitespace('N'));
    TEST(!Ascii::IsWhitespace('O'));
    TEST(!Ascii::IsWhitespace('P'));
    TEST(!Ascii::IsWhitespace('Q'));
    TEST(!Ascii::IsWhitespace('R'));
    TEST(!Ascii::IsWhitespace('S'));
    TEST(!Ascii::IsWhitespace('T'));
    TEST(!Ascii::IsWhitespace('U'));
    TEST(!Ascii::IsWhitespace('V'));
    TEST(!Ascii::IsWhitespace('W'));
    TEST(!Ascii::IsWhitespace('X'));
    TEST(!Ascii::IsWhitespace('Y'));
    TEST(!Ascii::IsWhitespace('Z'));
    
    TEST(Ascii::IsAlphabetic('a'));
    TEST(Ascii::IsAlphabetic('b'));
    TEST(Ascii::IsAlphabetic('c'));
    TEST(Ascii::IsAlphabetic('d'));
    TEST(Ascii::IsAlphabetic('e'));
    TEST(Ascii::IsAlphabetic('f'));
    TEST(Ascii::IsAlphabetic('g'));
    TEST(Ascii::IsAlphabetic('h'));
    TEST(Ascii::IsAlphabetic('i'));
    TEST(Ascii::IsAlphabetic('j'));
    TEST(Ascii::IsAlphabetic('k'));
    TEST(Ascii::IsAlphabetic('l'));
    TEST(Ascii::IsAlphabetic('m'));
    TEST(Ascii::IsAlphabetic('n'));
    TEST(Ascii::IsAlphabetic('o'));
    TEST(Ascii::IsAlphabetic('p'));
    TEST(Ascii::IsAlphabetic('q'));
    TEST(Ascii::IsAlphabetic('r'));
    TEST(Ascii::IsAlphabetic('s'));
    TEST(Ascii::IsAlphabetic('t'));
    TEST(Ascii::IsAlphabetic('u'));
    TEST(Ascii::IsAlphabetic('v'));
    TEST(Ascii::IsAlphabetic('w'));
    TEST(Ascii::IsAlphabetic('x'));
    TEST(Ascii::IsAlphabetic('y'));
    TEST(Ascii::IsAlphabetic('z'));
    TEST(Ascii::IsAlphabetic('A'));
    TEST(Ascii::IsAlphabetic('B'));
    TEST(Ascii::IsAlphabetic('C'));
    TEST(Ascii::IsAlphabetic('D'));
    TEST(Ascii::IsAlphabetic('E'));
    TEST(Ascii::IsAlphabetic('F'));
    TEST(Ascii::IsAlphabetic('G'));
    TEST(Ascii::IsAlphabetic('H'));
    TEST(Ascii::IsAlphabetic('I'));
    TEST(Ascii::IsAlphabetic('J'));
    TEST(Ascii::IsAlphabetic('K'));
    TEST(Ascii::IsAlphabetic('L'));
    TEST(Ascii::IsAlphabetic('M'));
    TEST(Ascii::IsAlphabetic('N'));
    TEST(Ascii::IsAlphabetic('O'));
    TEST(Ascii::IsAlphabetic('P'));
    TEST(Ascii::IsAlphabetic('Q'));
    TEST(Ascii::IsAlphabetic('R'));
    TEST(Ascii::IsAlphabetic('S'));
    TEST(Ascii::IsAlphabetic('T'));
    TEST(Ascii::IsAlphabetic('U'));
    TEST(Ascii::IsAlphabetic('V'));
    TEST(Ascii::IsAlphabetic('W'));
    TEST(Ascii::IsAlphabetic('X'));
    TEST(Ascii::IsAlphabetic('Y'));
    TEST(Ascii::IsAlphabetic('Z'));
    
    TEST(Ascii::IsLowerCase('a'));
    TEST(Ascii::IsLowerCase('b'));
    TEST(Ascii::IsLowerCase('c'));
    TEST(Ascii::IsLowerCase('d'));
    TEST(Ascii::IsLowerCase('e'));
    TEST(Ascii::IsLowerCase('f'));
    TEST(Ascii::IsLowerCase('g'));
    TEST(Ascii::IsLowerCase('h'));
    TEST(Ascii::IsLowerCase('i'));
    TEST(Ascii::IsLowerCase('j'));
    TEST(Ascii::IsLowerCase('k'));
    TEST(Ascii::IsLowerCase('l'));
    TEST(Ascii::IsLowerCase('m'));
    TEST(Ascii::IsLowerCase('n'));
    TEST(Ascii::IsLowerCase('o'));
    TEST(Ascii::IsLowerCase('p'));
    TEST(Ascii::IsLowerCase('q'));
    TEST(Ascii::IsLowerCase('r'));
    TEST(Ascii::IsLowerCase('s'));
    TEST(Ascii::IsLowerCase('t'));
    TEST(Ascii::IsLowerCase('u'));
    TEST(Ascii::IsLowerCase('v'));
    TEST(Ascii::IsLowerCase('w'));
    TEST(Ascii::IsLowerCase('x'));
    TEST(Ascii::IsLowerCase('y'));
    TEST(Ascii::IsLowerCase('z'));
    TEST(!Ascii::IsLowerCase('A'));
    TEST(!Ascii::IsLowerCase('B'));
    TEST(!Ascii::IsLowerCase('C'));
    TEST(!Ascii::IsLowerCase('D'));
    TEST(!Ascii::IsLowerCase('E'));
    TEST(!Ascii::IsLowerCase('F'));
    TEST(!Ascii::IsLowerCase('G'));
    TEST(!Ascii::IsLowerCase('H'));
    TEST(!Ascii::IsLowerCase('I'));
    TEST(!Ascii::IsLowerCase('J'));
    TEST(!Ascii::IsLowerCase('K'));
    TEST(!Ascii::IsLowerCase('L'));
    TEST(!Ascii::IsLowerCase('M'));
    TEST(!Ascii::IsLowerCase('N'));
    TEST(!Ascii::IsLowerCase('O'));
    TEST(!Ascii::IsLowerCase('P'));
    TEST(!Ascii::IsLowerCase('Q'));
    TEST(!Ascii::IsLowerCase('R'));
    TEST(!Ascii::IsLowerCase('S'));
    TEST(!Ascii::IsLowerCase('T'));
    TEST(!Ascii::IsLowerCase('U'));
    TEST(!Ascii::IsLowerCase('V'));
    TEST(!Ascii::IsLowerCase('W'));
    TEST(!Ascii::IsLowerCase('X'));
    TEST(!Ascii::IsLowerCase('Y'));
    TEST(!Ascii::IsLowerCase('Z'));
    
    TEST(!Ascii::IsUpperCase('a'));
    TEST(!Ascii::IsUpperCase('b'));
    TEST(!Ascii::IsUpperCase('c'));
    TEST(!Ascii::IsUpperCase('d'));
    TEST(!Ascii::IsUpperCase('e'));
    TEST(!Ascii::IsUpperCase('f'));
    TEST(!Ascii::IsUpperCase('g'));
    TEST(!Ascii::IsUpperCase('h'));
    TEST(!Ascii::IsUpperCase('i'));
    TEST(!Ascii::IsUpperCase('j'));
    TEST(!Ascii::IsUpperCase('k'));
    TEST(!Ascii::IsUpperCase('l'));
    TEST(!Ascii::IsUpperCase('m'));
    TEST(!Ascii::IsUpperCase('n'));
    TEST(!Ascii::IsUpperCase('o'));
    TEST(!Ascii::IsUpperCase('p'));
    TEST(!Ascii::IsUpperCase('q'));
    TEST(!Ascii::IsUpperCase('r'));
    TEST(!Ascii::IsUpperCase('s'));
    TEST(!Ascii::IsUpperCase('t'));
    TEST(!Ascii::IsUpperCase('u'));
    TEST(!Ascii::IsUpperCase('v'));
    TEST(!Ascii::IsUpperCase('w'));
    TEST(!Ascii::IsUpperCase('x'));
    TEST(!Ascii::IsUpperCase('y'));
    TEST(!Ascii::IsUpperCase('z'));
    TEST(Ascii::IsUpperCase('A'));
    TEST(Ascii::IsUpperCase('B'));
    TEST(Ascii::IsUpperCase('C'));
    TEST(Ascii::IsUpperCase('D'));
    TEST(Ascii::IsUpperCase('E'));
    TEST(Ascii::IsUpperCase('F'));
    TEST(Ascii::IsUpperCase('G'));
    TEST(Ascii::IsUpperCase('H'));
    TEST(Ascii::IsUpperCase('I'));
    TEST(Ascii::IsUpperCase('J'));
    TEST(Ascii::IsUpperCase('K'));
    TEST(Ascii::IsUpperCase('L'));
    TEST(Ascii::IsUpperCase('M'));
    TEST(Ascii::IsUpperCase('N'));
    TEST(Ascii::IsUpperCase('O'));
    TEST(Ascii::IsUpperCase('P'));
    TEST(Ascii::IsUpperCase('Q'));
    TEST(Ascii::IsUpperCase('R'));
    TEST(Ascii::IsUpperCase('S'));
    TEST(Ascii::IsUpperCase('T'));
    TEST(Ascii::IsUpperCase('U'));
    TEST(Ascii::IsUpperCase('V'));
    TEST(Ascii::IsUpperCase('W'));
    TEST(Ascii::IsUpperCase('X'));
    TEST(Ascii::IsUpperCase('Y'));
    TEST(Ascii::IsUpperCase('Z'));
    
    // Alphabet boundaries

    TEST(!Ascii::IsDigit('@'));
    TEST(!Ascii::IsDigit('['));
    
    TEST(!Ascii::IsWhitespace('@'));
    TEST(!Ascii::IsWhitespace('['));
    
    TEST(!Ascii::IsAlphabetic('@'));
    TEST(!Ascii::IsAlphabetic('['));

    TEST(!Ascii::IsUpperCase('@'));
    TEST(!Ascii::IsUpperCase('['));
    
    TEST(!Ascii::IsLowerCase('@'));
    TEST(!Ascii::IsLowerCase('['));
    
    TEST(!Ascii::IsDigit('`'));
    TEST(!Ascii::IsDigit('{'));
    
    TEST(!Ascii::IsWhitespace('`'));
    TEST(!Ascii::IsWhitespace('{'));
    
    TEST(!Ascii::IsAlphabetic('`'));
    TEST(!Ascii::IsAlphabetic('{'));

    TEST(!Ascii::IsUpperCase('`'));
    TEST(!Ascii::IsUpperCase('{'));
    
    TEST(!Ascii::IsLowerCase('`'));
    TEST(!Ascii::IsLowerCase('{'));

    // Convert to Upper Case
    
    TEST(Ascii::ToUpperCase('a') == 'A');
    TEST(Ascii::ToUpperCase('b') == 'B');
    TEST(Ascii::ToUpperCase('c') == 'C');
    TEST(Ascii::ToUpperCase('d') == 'D');
    TEST(Ascii::ToUpperCase('e') == 'E');
    TEST(Ascii::ToUpperCase('f') == 'F');
    TEST(Ascii::ToUpperCase('g') == 'G');
    TEST(Ascii::ToUpperCase('h') == 'H');
    TEST(Ascii::ToUpperCase('i') == 'I');
    TEST(Ascii::ToUpperCase('j') == 'J');
    TEST(Ascii::ToUpperCase('k') == 'K');
    TEST(Ascii::ToUpperCase('l') == 'L');
    TEST(Ascii::ToUpperCase('m') == 'M');
    TEST(Ascii::ToUpperCase('n') == 'N');
    TEST(Ascii::ToUpperCase('o') == 'O');
    TEST(Ascii::ToUpperCase('p') == 'P');
    TEST(Ascii::ToUpperCase('q') == 'Q');
    TEST(Ascii::ToUpperCase('r') == 'R');
    TEST(Ascii::ToUpperCase('s') == 'S');
    TEST(Ascii::ToUpperCase('t') == 'T');
    TEST(Ascii::ToUpperCase('u') == 'U');
    TEST(Ascii::ToUpperCase('v') == 'V');
    TEST(Ascii::ToUpperCase('w') == 'W');
    TEST(Ascii::ToUpperCase('x') == 'X');
    TEST(Ascii::ToUpperCase('y') == 'Y');
    TEST(Ascii::ToUpperCase('z') == 'Z');
    TEST(Ascii::ToUpperCase('@') == '@');
    TEST(Ascii::ToUpperCase('[') == '[');
    TEST(Ascii::ToUpperCase('`') == '`');
    TEST(Ascii::ToUpperCase('{') == '{');
    TEST(Ascii::ToUpperCase(' ') == ' ');
    TEST(Ascii::ToUpperCase('1') == '1');
    TEST(Ascii::ToUpperCase('A') == 'A');
    TEST(Ascii::ToUpperCase(';') == ';');
    TEST(Ascii::ToUpperCase(0x12) == 0x12);

    // Convert to Lower Case
    
    TEST(Ascii::ToLowerCase('A') == 'a');
    TEST(Ascii::ToLowerCase('B') == 'b');
    TEST(Ascii::ToLowerCase('C') == 'c');
    TEST(Ascii::ToLowerCase('D') == 'd');
    TEST(Ascii::ToLowerCase('E') == 'e');
    TEST(Ascii::ToLowerCase('F') == 'f');
    TEST(Ascii::ToLowerCase('G') == 'g');
    TEST(Ascii::ToLowerCase('H') == 'h');
    TEST(Ascii::ToLowerCase('I') == 'i');
    TEST(Ascii::ToLowerCase('J') == 'j');
    TEST(Ascii::ToLowerCase('K') == 'k');
    TEST(Ascii::ToLowerCase('L') == 'l');
    TEST(Ascii::ToLowerCase('M') == 'm');
    TEST(Ascii::ToLowerCase('N') == 'n');
    TEST(Ascii::ToLowerCase('O') == 'o');
    TEST(Ascii::ToLowerCase('P') == 'p');
    TEST(Ascii::ToLowerCase('Q') == 'q');
    TEST(Ascii::ToLowerCase('R') == 'r');
    TEST(Ascii::ToLowerCase('S') == 's');
    TEST(Ascii::ToLowerCase('T') == 't');
    TEST(Ascii::ToLowerCase('U') == 'u');
    TEST(Ascii::ToLowerCase('V') == 'v');
    TEST(Ascii::ToLowerCase('W') == 'w');
    TEST(Ascii::ToLowerCase('X') == 'x');
    TEST(Ascii::ToLowerCase('Y') == 'y');
    TEST(Ascii::ToLowerCase('Z') == 'z');
    TEST(Ascii::ToUpperCase('@') == '@');
    TEST(Ascii::ToUpperCase('[') == '[');
    TEST(Ascii::ToUpperCase('`') == '`');
    TEST(Ascii::ToUpperCase('{') == '{');
    TEST(Ascii::ToUpperCase(' ') == ' ');
    TEST(Ascii::ToUpperCase('1') == '1');
    TEST(Ascii::ToUpperCase('A') == 'A');
    TEST(Ascii::ToUpperCase(';') == ';');
    TEST(Ascii::ToUpperCase(0x12) == 0x12);

    // Hex
    
    TEST(Ascii::HexChar(0) == '0');
    TEST(Ascii::HexChar(1) == '1');
    TEST(Ascii::HexChar(2) == '2');
    TEST(Ascii::HexChar(3) == '3');
    TEST(Ascii::HexChar(4) == '4');
    TEST(Ascii::HexChar(5) == '5');
    TEST(Ascii::HexChar(6) == '6');
    TEST(Ascii::HexChar(7) == '7');
    TEST(Ascii::HexChar(8) == '8');
    TEST(Ascii::HexChar(9) == '9');
    TEST(Ascii::HexChar(10) == 'a');
    TEST(Ascii::HexChar(11) == 'b');
    TEST(Ascii::HexChar(12) == 'c');
    TEST(Ascii::HexChar(13) == 'd');
    TEST(Ascii::HexChar(14) == 'e');
    TEST(Ascii::HexChar(15) == 'f');
    TEST_THROWS(Ascii::HexChar(16), AsciiError);
    TEST_THROWS(Ascii::HexChar(10000), AsciiError);

    TEST(Ascii::HexValue('0') == 0);
    TEST(Ascii::HexValue('1') == 1);
    TEST(Ascii::HexValue('2') == 2);
    TEST(Ascii::HexValue('3') == 3);
    TEST(Ascii::HexValue('4') == 4);
    TEST(Ascii::HexValue('5') == 5);
    TEST(Ascii::HexValue('6') == 6);
    TEST(Ascii::HexValue('7') == 7);
    TEST(Ascii::HexValue('8') == 8);
    TEST(Ascii::HexValue('9') == 9);
    TEST(Ascii::HexValue('A') == 10);
    TEST(Ascii::HexValue('B') == 11);
    TEST(Ascii::HexValue('C') == 12);
    TEST(Ascii::HexValue('D') == 13);
    TEST(Ascii::HexValue('E') == 14);
    TEST(Ascii::HexValue('F') == 15);
    TEST(Ascii::HexValue('a') == 10);
    TEST(Ascii::HexValue('b') == 11);
    TEST(Ascii::HexValue('c') == 12);
    TEST(Ascii::HexValue('d') == 13);
    TEST(Ascii::HexValue('e') == 14);
    TEST(Ascii::HexValue('f') == 15);
    
    TEST_THROWS(Ascii::HexValue('@'), AsciiError);
    TEST_THROWS(Ascii::HexValue('G'), AsciiError);
    TEST_THROWS(Ascii::HexValue('g'), AsciiError);
    TEST_THROWS(Ascii::HexValue('/'), AsciiError);
    TEST_THROWS(Ascii::HexValue(':'), AsciiError);

    // Dec
    
    TEST(Ascii::DecChar(0) == '0');
    TEST(Ascii::DecChar(1) == '1');
    TEST(Ascii::DecChar(2) == '2');
    TEST(Ascii::DecChar(3) == '3');
    TEST(Ascii::DecChar(4) == '4');
    TEST(Ascii::DecChar(5) == '5');
    TEST(Ascii::DecChar(6) == '6');
    TEST(Ascii::DecChar(7) == '7');
    TEST(Ascii::DecChar(8) == '8');
    TEST(Ascii::DecChar(9) == '9');
    TEST_THROWS(Ascii::DecChar(10), AsciiError);
    TEST_THROWS(Ascii::DecChar(10000), AsciiError);

    TEST(Ascii::DecValue('0') == 0);
    TEST(Ascii::DecValue('1') == 1);
    TEST(Ascii::DecValue('2') == 2);
    TEST(Ascii::DecValue('3') == 3);
    TEST(Ascii::DecValue('4') == 4);
    TEST(Ascii::DecValue('5') == 5);
    TEST(Ascii::DecValue('6') == 6);
    TEST(Ascii::DecValue('7') == 7);
    TEST(Ascii::DecValue('8') == 8);
    TEST(Ascii::DecValue('9') == 9);
    
    TEST_THROWS(Ascii::DecValue('@'), AsciiError);
    TEST_THROWS(Ascii::DecValue('A'), AsciiError);
    TEST_THROWS(Ascii::DecValue('b'), AsciiError);
    TEST_THROWS(Ascii::DecValue('G'), AsciiError);
    TEST_THROWS(Ascii::DecValue('g'), AsciiError);
    TEST_THROWS(Ascii::DecValue('/'), AsciiError);
    TEST_THROWS(Ascii::DecValue(':'), AsciiError);

    // Append
    
    Bws<30> test;
    
    // Signed
    
    test.Replace(Brn("TEST:"));
    TEST(Ascii::AppendDec(test, TInt(0)) == 1);
    TEST(test == Brn("TEST:0"));
    
    test.Replace(Brn("TEST:"));
    TEST(Ascii::AppendDec(test, TInt(-1)) == 2);
    TEST(test == Brn("TEST:-1"));

    test.Replace(Brn("TEST:"));
    TEST(Ascii::AppendDec(test, TInt(1)) == 1);
    TEST(test == Brn("TEST:1"));

    test.Replace(Brn("TEST:"));
    TEST(Ascii::AppendDec(test, TInt(1234567890)) == 10);
    TEST(test == Brn("TEST:1234567890"));
    
    test.Replace(Brn("TEST:"));
    TEST(Ascii::AppendDec(test, TInt(-987654321)) == 10);
    TEST(test == Brn("TEST:-987654321"));

    test.Replace(Brn("TEST:"));
    TEST(Ascii::AppendDec(test, TInt64(0)) == 1);
    TEST(test == Brn("TEST:0"));
    
    test.Replace(Brn("TEST:"));
    TEST(Ascii::AppendDec(test, TInt64(-1)) == 2);
    TEST(test == Brn("TEST:-1"));

    test.Replace(Brn("TEST:"));
    TEST(Ascii::AppendDec(test, TInt64(1)) == 1);
    TEST(test == Brn("TEST:1"));

    test.Replace(Brn("TEST:"));
    TEST(Ascii::AppendDec(test, TInt64(1234567890123456789ll)) == 19);
    TEST(test == Brn("TEST:1234567890123456789"));
    
    test.Replace(Brn("TEST:"));
    TEST(Ascii::AppendDec(test, TInt64(-1234567890123456789ll)) == 20);
    TEST(test == Brn("TEST:-1234567890123456789"));

    test.Replace(Brn("TEST:"));
    TEST(Ascii::AppendDec(test, (TInt64)std::numeric_limits<long long>::min()) == 20);
    TEST(test == Brn("TEST:-9223372036854775808"));

    // Unsigned
    
    test.Replace(Brn("TEST:"));
    TEST(Ascii::AppendDec(test, TUint(0)) == 1);
    TEST(test == Brn("TEST:0"));
    
    test.Replace(Brn("TEST:"));
    TEST(Ascii::AppendDec(test, TUint(1)) == 1);
    TEST(test == Brn("TEST:1"));

    test.Replace(Brn("TEST:"));
    TEST(Ascii::AppendDec(test, TUint(1234567890)) == 10);
    TEST(test == Brn("TEST:1234567890"));
    
    test.Replace(Brn("TEST:"));
    TEST(Ascii::AppendDec(test, TUint(987654321)) == 9);
    TEST(test == Brn("TEST:987654321"));

    test.Replace(Brn("TEST:"));
    TEST(Ascii::AppendDec(test, TUint64(0)) == 1);
    TEST(test == Brn("TEST:0"));
    
    test.Replace(Brn("TEST:"));
    TEST(Ascii::AppendDec(test, TUint64(1)) == 1);
    TEST(test == Brn("TEST:1"));

    test.Replace(Brn("TEST:"));
    TEST(Ascii::AppendDec(test, TUint64(12345678901234567890ull)) == 20);
    TEST(test == Brn("TEST:12345678901234567890"));
    
    test.Replace(Brn("TEST:"));
    TEST(Ascii::AppendDec(test, TUint64(987654321987654321ull)) == 18);
    TEST(test == Brn("TEST:987654321987654321"));

    // Hex - TUint
    
    test.Replace(Brn("TEST:"));
    TEST(Ascii::AppendHex(test, TUint(0x00000000)) == 8);
    TEST(test == Brn("TEST:00000000"));
    
    test.Replace(Brn("TEST:"));
    TEST(Ascii::AppendHex(test, TUint(0x12345678)) == 8);
    TEST(test == Brn("TEST:12345678"));

    test.Replace(Brn("TEST:"));
    TEST(Ascii::AppendHex(test, TUint(0x1234)) == 8);
    TEST(test == Brn("TEST:00001234"));

    test.Replace(Brn("TEST:"));
    TEST(Ascii::AppendHex(test, TUint(0xfedcba98)) == 8);
    TEST(test == Brn("TEST:fedcba98"));

    // Hex - TUint, trim leading zeros

    test.Replace(Brn("TEST:"));
    TEST(Ascii::AppendHexTrim(test, TUint(0x00000000)) == 1);
    TEST(test == Brn("TEST:0"));

    test.Replace(Brn("TEST:"));
    TEST(Ascii::AppendHexTrim(test, TUint(0x12345678)) == 8);
    TEST(test == Brn("TEST:12345678"));

    test.Replace(Brn("TEST:"));
    TEST(Ascii::AppendHexTrim(test, TUint(0x1234)) == 4);
    TEST(test == Brn("TEST:1234"));

    test.Replace(Brn("TEST:"));
    TEST(Ascii::AppendHexTrim(test, TUint(0xfedcba98)) == 8);
    TEST(test == Brn("TEST:fedcba98"));

    // Hex - TByte

    test.Replace(Brn("TEST:"));
    TEST(Ascii::AppendHex(test, TByte(0x00)) == 2);
    TEST(test == Brn("TEST:00"));

    test.Replace(Brn("TEST:"));
    TEST(Ascii::AppendHex(test, TByte(0xaa)) == 2);
    TEST(test == Brn("TEST:aa"));

    test.Replace(Brn("TEST:"));
    TEST(Ascii::AppendHex(test, TByte(0xf9)) == 2);
    TEST(test == Brn("TEST:f9"));
    
    test.Replace(Brn("TEST:"));
    TEST(Ascii::AppendHexPrefix(test) == 2);
    TEST(test == Brn("TEST:0x"));
    
    // Case Insensitive
    
    TEST(Ascii::CaseInsensitiveEquals('A','A'));
    TEST(Ascii::CaseInsensitiveEquals('a','A'));
    TEST(Ascii::CaseInsensitiveEquals('A','a'));
    TEST(Ascii::CaseInsensitiveEquals('a','a'));
    TEST(Ascii::CaseInsensitiveEquals('Z','Z'));
    TEST(Ascii::CaseInsensitiveEquals('z','Z'));
    TEST(Ascii::CaseInsensitiveEquals('Z','z'));
    TEST(Ascii::CaseInsensitiveEquals('z','z'));
    TEST(Ascii::CaseInsensitiveEquals('1','1'));
    TEST(Ascii::CaseInsensitiveEquals(';',';'));
    TEST(Ascii::CaseInsensitiveEquals(' ',' '));
    TEST(Ascii::CaseInsensitiveEquals('[','['));
    TEST(Ascii::CaseInsensitiveEquals(0x1b,0x1b));
    
    TUint i;
    for (i=1; i<0x100; i+=0x10) {
        if (i == 0x41 || i == 0x61) continue;
        TEST(!Ascii::CaseInsensitiveEquals('a',(TChar)i));
    }
    for (i=1; i<0x100; i+=0x10) {
        if (i == 0x41 || i == 0x61) continue;
        TEST(!Ascii::CaseInsensitiveEquals('A',(TChar)i));
    }
    
    // Contains
    
    TEST(Ascii::Contains(Brn("abcdefg"), 'a'));
    TEST(Ascii::Contains(Brn("abcdefg"), 'b'));
    TEST(Ascii::Contains(Brn("abcdefg"), 'c'));
    TEST(Ascii::Contains(Brn("abcdefg"), 'd'));
    TEST(Ascii::Contains(Brn("abcdefg"), 'e'));
    TEST(Ascii::Contains(Brn("abcdefg"), 'f'));
    TEST(Ascii::Contains(Brn("abcdefg"), 'g'));
    TEST(!Ascii::Contains(Brn("abcdefg"), 'h'));
    TEST(!Ascii::Contains(Brn("abcdefg"), 'i'));
    TEST(!Ascii::Contains(Brn("abcdefg"), 'j'));
    TEST(!Ascii::Contains(Brn("abcdefg"), 'k'));
    TEST(!Ascii::Contains(Brn("abcdefg"), 'l'));
    TEST(!Ascii::Contains(Brn("abcdefg"), 'm'));
    TEST(!Ascii::Contains(Brn("abcdefg"), 'n'));
    TEST(Ascii::Contains(Brn("abcdefg"), Brn("a")));
    TEST(Ascii::Contains(Brn("abcdefg"), Brn("ab")));
    TEST(Ascii::Contains(Brn("abcdefg"), Brn("abcdefg")));
    TEST(Ascii::Contains(Brn("abcdefg"), Brn("b")));
    TEST(Ascii::Contains(Brn("abcdefg"), Brn("bc")));
    TEST(Ascii::Contains(Brn("abcdefg"), Brn("bcdefg")));
    TEST(!Ascii::Contains(Brn("abcdefg"), Brn("h")));
    TEST(!Ascii::Contains(Brn("abcdefg"), Brn("abcdefgh")));
    
    TEST(Ascii::ContainsWhitespace(Brn(" A  collection   of words ")));
    TEST(Ascii::ContainsWhitespace(Brn("A  collection   of words ")));
    TEST(Ascii::ContainsWhitespace(Brn("Acollection   of words ")));
    TEST(Ascii::ContainsWhitespace(Brn("Acollectionof words ")));
    TEST(Ascii::ContainsWhitespace(Brn("Acollectionofwords ")));
    TEST(!Ascii::ContainsWhitespace(Brn("Acollectionofwords")));
    
    // IndexOf
    TEST(Ascii::IndexOf(Brn("abcdefg"), 'a') == 0);
    TEST(Ascii::IndexOf(Brn("abcdefg"), 'b') == 1);
    TEST(Ascii::IndexOf(Brn("abcdefg"), 'c') == 2);
    TEST(Ascii::IndexOf(Brn("abcdefg"), 'd') == 3);
    TEST(Ascii::IndexOf(Brn("abcdefg"), 'e') == 4);
    TEST(Ascii::IndexOf(Brn("abcdefg"), 'f') == 5);
    TEST(Ascii::IndexOf(Brn("abcdefg"), 'g') == 6);
    TEST(Ascii::IndexOf(Brn("abcdefg"), 'h') == 7);
    TEST(Ascii::IndexOf(Brn("abcdefg"), 'i') == 7);
    TEST(Ascii::IndexOf(Brn("abcdefg"), 'j') == 7);
    TEST(Ascii::IndexOf(Brn("abcdefg"), 'k') == 7);
    TEST(Ascii::IndexOf(Brn("abcdefg"), 'l') == 7);
    TEST(Ascii::IndexOf(Brn("abcdefg"), 'm') == 7);
    TEST(Ascii::IndexOf(Brn("abcdefg"), 'n') == 7);

    // Trim
    
    TEST(Ascii::Trim(Brn("   A bit of text   ")) == Brn("A bit of text"));
    TEST(Ascii::Trim(Brn("A bit of text   ")) == Brn("A bit of text"));
    TEST(Ascii::Trim(Brn("   A bit of text")) == Brn("A bit of text"));
    TEST(Ascii::Trim(Brn("A bit of text")) == Brn("A bit of text"));
    TEST(Ascii::Trim(Brn("   A   ")) == Brn("A"));
    TEST(Ascii::Trim(Brn("A      ")) == Brn("A"));
    TEST(Ascii::Trim(Brn("      A")) == Brn("A"));
    TEST(Ascii::Trim(Brn("       ")) == Brn(""));
    
    // Int
    
    TEST(Ascii::Int(Brn("1234567890")) == 1234567890);
    TEST(Ascii::Int(Brn("   1234567890   ")) == 1234567890);
    TEST(Ascii::Int(Brn("-1234567890")) == -1234567890);
    TEST(Ascii::Int(Brn("-1234567890  ")) == -1234567890);
    TEST(Ascii::Int(Brn("0")) == 0);
    TEST(Ascii::Int(Brn("  0000")) == 0);
    TEST(Ascii::Int(Brn("-0000 ")) == 0);
    TEST_THROWS(Ascii::Int(Brn("-00 00 ")), AsciiError);
    TEST_THROWS(Ascii::Int(Brn("  123 45")), AsciiError);
    TEST_THROWS(Ascii::Int(Brn("  123.45")), AsciiError);
    TEST_THROWS(Ascii::Int(Brn("1-")), AsciiError);
    TEST_THROWS(Ascii::Int(Brn("-")), AsciiError);
    TEST_THROWS(Ascii::Int(Brn("")), AsciiError);
    
    TEST(Ascii::Int64(Brn("1234567890123456789")) == 1234567890123456789ll);
    TEST(Ascii::Int64(Brn("   1234567890123456789   ")) == 1234567890123456789ll);
    TEST(Ascii::Int64(Brn("-1234567890123456789")) == -1234567890123456789ll);
    TEST(Ascii::Int64(Brn("-1234567890123456789  ")) == -1234567890123456789ll);
    TEST(Ascii::Int64(Brn("0")) == 0);
    TEST(Ascii::Int64(Brn("  0000")) == 0);
    TEST(Ascii::Int64(Brn("-0000 ")) == 0);
    TEST_THROWS(Ascii::Int64(Brn("-00 00 ")), AsciiError);
    TEST_THROWS(Ascii::Int64(Brn("  123 45")), AsciiError);
    TEST_THROWS(Ascii::Int64(Brn("  123.45")), AsciiError);
    TEST_THROWS(Ascii::Int64(Brn("1-")), AsciiError);
    TEST_THROWS(Ascii::Int64(Brn("-")), AsciiError);
    TEST_THROWS(Ascii::Int64(Brn("")), AsciiError);

    // Uint
    
    TEST(Ascii::Uint(Brn("1234567890")) == 1234567890);
    TEST(Ascii::Uint(Brn("   1234567890   ")) == 1234567890);
    TEST(Ascii::Uint(Brn("0")) == 0);
    TEST(Ascii::Uint(Brn("  0000")) == 0);
    TEST_THROWS(Ascii::Uint(Brn("-0000 ")), AsciiError);
    TEST_THROWS(Ascii::Uint(Brn("00 00 ")), AsciiError);
    TEST_THROWS(Ascii::Uint(Brn("  123 45")), AsciiError);
    TEST_THROWS(Ascii::Uint(Brn("  123.45")), AsciiError);
    TEST_THROWS(Ascii::Uint(Brn("-1")), AsciiError);
    TEST_THROWS(Ascii::Uint(Brn("-")), AsciiError);
    TEST_THROWS(Ascii::Uint(Brn("")), AsciiError);

    TEST(Ascii::Uint64(Brn("12345678901234567890")) == 12345678901234567890ull);
    TEST(Ascii::Uint64(Brn("   12345678901234567890   ")) == 12345678901234567890ull);
    TEST(Ascii::Uint64(Brn("0")) == 0);
    TEST(Ascii::Uint64(Brn("  0000")) == 0);
    TEST_THROWS(Ascii::Uint64(Brn("-0000 ")), AsciiError);
    TEST_THROWS(Ascii::Uint64(Brn("00 00 ")), AsciiError);
    TEST_THROWS(Ascii::Uint64(Brn("  123 45")), AsciiError);
    TEST_THROWS(Ascii::Uint64(Brn("  123.45")), AsciiError);
    TEST_THROWS(Ascii::Uint64(Brn("-1")), AsciiError);
    TEST_THROWS(Ascii::Uint64(Brn("-")), AsciiError);
    TEST_THROWS(Ascii::Uint64(Brn("")), AsciiError);

    // UintHex

    TEST(Ascii::UintHex(Brn("0")) == 0);
    TEST(Ascii::UintHex(Brn("1")) == 1);
    TEST(Ascii::UintHex(Brn("01")) == 1);
    TEST(Ascii::UintHex(Brn("10")) == 16);
    TEST(Ascii::UintHex(Brn("11")) == 17);

    TEST(Ascii::UintHex(Brn("1234abcd")) == 0x1234abcd); // full width hex uint32
    TEST_THROWS(Ascii::UintHex(Brn("112345678")), AsciiError); // too long
    TEST_THROWS(Ascii::UintHex(Brn("invalid")), AsciiError); // non-hex chars
}   
    
class SuiteParser : public Suite
{
public:
    SuiteParser() : Suite("Parser") {}
    void Test();
};

void SuiteParser::Test()
{
    Brn test1("A collection   of     words separated   by spaces");
    Parser parser(test1);
    TEST(!parser.Finished());
    TEST(parser.Next(' ') == Brn("A"));
    TEST(!parser.Finished());
    TEST(parser.Next() == Brn("collection"));
    TEST(!parser.Finished());
    TEST(parser.Next(' ') == Brn("of"));
    TEST(!parser.Finished());
    TEST(parser.Next() == Brn("words"));
    TEST(!parser.Finished());
    TEST(parser.Next(' ') == Brn("separated"));
    TEST(!parser.Finished());
    TEST(parser.Next() == Brn("by"));
    TEST(!parser.Finished());
    TEST(parser.Next(' ') == Brn("spaces"));
    TEST(parser.Finished());
    TEST(parser.Next() == Brn(""));
    TEST(parser.Finished());
    
    Brn test2("a:list  :   of    : items:separated:by::colons:");
    parser.Set(test2);
    TEST(!parser.Finished());
    TEST(parser.Next(':') == Brn("a"));
    TEST(!parser.Finished());
    TEST(parser.Next(':') == Brn("list"));
    TEST(!parser.Finished());
    TEST(parser.Next(':') == Brn("of"));
    TEST(!parser.Finished());
    TEST(parser.Next('y') == Brn("items:separated:b"));
    TEST(!parser.Finished());
    TEST(parser.Next(':') == Brn(""));
    TEST(!parser.Finished());
    TEST(parser.Next(':') == Brn(""));
    TEST(!parser.Finished());
    TEST(parser.Next(':') == Brn("colons"));
    TEST(parser.Finished());
    TEST(parser.Next(' ') == Brn(""));
    TEST(parser.Finished());
    
    parser.Restart();
    TEST(!parser.Finished());
    TEST(parser.Remaining() == Brn("a:list  :   of    : items:separated:by::colons:"));
    TEST(parser.Next(':') == Brn("a"));
    TEST(parser.Remaining() == Brn("list  :   of    : items:separated:by::colons:"));
    TEST(parser.Next(':') == Brn("list"));
    TEST(parser.Remaining() == Brn("   of    : items:separated:by::colons:"));
    TEST(parser.Next(':') == Brn("of"));
    TEST(parser.Remaining() == Brn(" items:separated:by::colons:"));
    TEST(parser.Next(':') == Brn("items"));
    TEST(parser.Remaining() == Brn("separated:by::colons:"));
    TEST(parser.Next(':') == Brn("separated"));
    TEST(parser.Remaining() == Brn("by::colons:"));
    TEST(parser.Next(':') == Brn("by"));
    TEST(parser.Remaining() == Brn(":colons:"));
    TEST(parser.Next(':') == Brn(""));
    TEST(parser.Remaining() == Brn("colons:"));
    TEST(parser.Next(':') == Brn("colons"));
    TEST(parser.Remaining() == Brn(""));
}


class SuiteUri : public Suite
{
public:
    SuiteUri() : Suite("Uri tests") {}
    void Test();
};

void SuiteUri::Test()
{
    TUint i;
    Uri* uri = new Uri();

    // Scheme tests
    {
    // no scheme
    Brn uriStringFail1("noschemedelimiter");
    TEST_THROWS(uri->Replace(uriStringFail1); (void)uri, UriError);

    // zero length scheme
    Brn uriStringFail2(":noschemeuri");
    TEST_THROWS(uri->Replace(uriStringFail2); (void)uri, UriError);

    Bws<128> uriString("testscheme://testhost:123/testpath");
    Bws<32> uriScheme("testscheme");

    // First character of scheme must be alpha - start from 0x21 (first 33
    // chars are considered whitespace and will be trimmed by the Parser)
    for(i=33 ; i<128 ; i++) {
        uriString[0] = (TByte)i;
        uriScheme[0] = (TByte)i;
        if (Ascii::IsAlphabetic((TChar)i)) {
            uri->Replace(uriString);
            TEST(uri->Scheme() == uriScheme);
        }
        else {
            TEST_THROWS(uri->Replace(uriString); (void)uri, UriError);
        }
    }
    uriString[0] = 't';
    uriScheme[0] = 't';

    // Other characters of scheme must be alpha, digit, +, - or .
    for(i=0 ; i<128 ; i++) {
        uriString[1] = (TByte)i;
        uriScheme[1] = (TByte)i;
        if (Ascii::IsAlphabetic((TChar)i) || Ascii::IsDigit((TChar)i) || i == '+' || i == '-' || i == '.') {
            uri->Replace(uriString);
            TEST(uri->Scheme() == uriScheme);
        }
        else if (i == ':') {
            // skip this case - this inserts a new scheme delimiter
            continue;
        }
        else {
            TEST_THROWS(uri->Replace(uriString); (void)uri, UriError);
        }
    }
    uriString[1] = 'e';
    uriScheme[1] = 'e';

    // First character after scheme delimiter must be a '/'
    for(i=0 ; i<128 ; i++) {
        uriString[11] = (TByte)i;
        if (i == '/') {
            uri->Replace(uriString);
            (void)uri;
            TEST(1==1);
        }
        else {
            TEST_THROWS(uri->Replace(uriString); (void)uri, UriError);
        }
    }
    uriString[11] = '/';

    // nothing after scheme
    Brn uriSchemeOnlyFail1("testscheme:");
    TEST_THROWS(uri->Replace(uriSchemeOnlyFail1); (void)uri, UriError);
    }


    // Authority tests
    {
    // No authority not supported
    Bws<128> uriAuthFail1("testscheme:/");
    Bws<128> uriAuthFail2("testscheme:/testpath");
    TEST_THROWS(uri->Replace(uriAuthFail1); (void)uri, UriError);
    TEST_THROWS(uri->Replace(uriAuthFail2); (void)uri, UriError);
    // UserInfo not supported
    Bws<128> uriUserInfoFail1("testscheme://testuser@testhost");
    Bws<128> uriUserInfoFail2("testscheme://testuser@testhost:123");
    Bws<128> uriUserInfoFail3("testscheme://testuser@testhost/testpath");
    Bws<128> uriUserInfoFail4("testscheme://testuser@testhost:123/testpath");
    TEST_THROWS(uri->Replace(uriUserInfoFail1); (void)uri, UriError);
    TEST_THROWS(uri->Replace(uriUserInfoFail2); (void)uri, UriError);
    TEST_THROWS(uri->Replace(uriUserInfoFail3); (void)uri, UriError);
    TEST_THROWS(uri->Replace(uriUserInfoFail4); (void)uri, UriError);
    // No host
    Bws<128> uriHostFail1("testscheme://");
    Bws<128> uriHostFail2("testscheme://:123");
    Bws<128> uriHostFail3("testscheme:///testpath");
    Bws<128> uriHostFail4("testscheme://:123/testpath");
    TEST_THROWS(uri->Replace(uriHostFail1); (void)uri, UriError);
    TEST_THROWS(uri->Replace(uriHostFail2); (void)uri, UriError);
    TEST_THROWS(uri->Replace(uriHostFail3); (void)uri, UriError);
    TEST_THROWS(uri->Replace(uriHostFail4); (void)uri, UriError);
    // No port
    Bws<128> uriPortFail1("testscheme://testhost:");
    Bws<128> uriPortFail2("testscheme://testhost:/testpath");
    TEST_THROWS(uri->Replace(uriPortFail1); (void)uri, UriError);
    TEST_THROWS(uri->Replace(uriPortFail2); (void)uri, UriError);

    // Host tests
    {
    Bws<128> uriString("testscheme://testhost:123/testpath");
    Bws<32> uriHost("testhost");

    // Host can contain alpha, digit, '-' or '.' or '_'
    for(i=0 ; i<128 ; i++) {
        uriString[14] = (TByte)i;
        uriHost[1] = (TByte)i;
        if (Ascii::IsAlphabetic((TChar)i) || Ascii::IsDigit((TChar)i) || i == '-' || i == '.' || i == '_') {
            uri->Replace(uriString);
            TEST(uri->Host() == uriHost);
        }
        else if (i == '/' || i == '#' || i == '?') {
            // skip this case - adds a new authority, query or fragment delimiter
            continue;
        }
        else {
            TEST_THROWS(uri->Replace(uriString); (void)uri, UriError);
        }
    }
    uriString[14] = 'e';
    }

    // Port tests
    {
    Bws<128> uriString("testscheme://testhost:123/testpath");
    for(i=0 ; i<128 ; i++) {
        uriString[23] = (TByte)i;
        if (Ascii::IsDigit((TChar)i)) {
            uri->Replace(uriString);
            TEST(uri->Port() == (TInt)(103 + (i - '0')*10));
        }
        else if (i == '/' || i == '#' || i == '?') {
            // skip this case - adds a new authority, query or fragment delimiter
            continue;
        }
        else {
            TEST_THROWS(uri->Replace(uriString); (void)uri, UriError);
        }
    }
    uriString[23] = '2';

    uriString.Replace("testscheme://testhost/testpath");
    uri->Replace(uriString);
    TEST(uri->Port() == -1);
    }
    }

    // Path tests
    {
    Brn uriNoPathString1("testscheme://testhost:123");
    Brn uriNoPathString2("testscheme://testhost:123/");
    Uri* uriNoPath1 = new Uri(uriNoPathString1);
    Uri* uriNoPath2 = new Uri(uriNoPathString2);
    TEST(uriNoPath1->Path() == Brn("/"));
    TEST(uriNoPath2->Path() == Brn("/"));
    delete uriNoPath1;
    delete uriNoPath2;

    // Relative path tests:
    // Nicked from the examples at http://www.webreference.com/html/tutorial2/3.html
    Brn root("http://WebReference.com/html/");
#define REL_TEST(relativeUri,expectedAbsoluteUri) \
    do { \
        TEST(Uri(root, Brn(relativeUri)).AbsoluteUri() == Brn(expectedAbsoluteUri)); \
    } \
    while(0)

    REL_TEST("about.html",         "http://WebReference.com/html/about.html");
    REL_TEST("tutorial1/",         "http://WebReference.com/html/tutorial1/");
    REL_TEST("tutorial1/2.html",   "http://WebReference.com/html/tutorial1/2.html");
    REL_TEST("/",                  "http://WebReference.com/");
    REL_TEST("//www.internet.com/", "http://www.internet.com/");
    REL_TEST("/experts/",          "http://WebReference.com/experts/");
    REL_TEST("../",                "http://WebReference.com/");
    REL_TEST("../experts/",        "http://WebReference.com/experts/");
    REL_TEST("../../../",          "http://WebReference.com/"); // fails, throws UriError
    REL_TEST("./",                 "http://WebReference.com/html/");
    REL_TEST("./about.html",       "http://WebReference.com/html/about.html");
#undef REL_TEST

    Bws<128> uriString("testscheme://testhost:123/testpath");
    Bws<32> uriPath("/testpath");
    for(i=0 ; i<128 ; i++) {
        uriString[30] = (TByte)i;
        uriPath[5] = (TByte)i;
        if (i == '%' || i == '#' || i == '?' || Uri::IsExcluded((TChar)i)) {
            // skip this as escaping, queries and fragments are tested below
            continue;
        }
        else if (i == '/' || i == ';' || i == ':' || i == '@' ||
            i == '&' || i == '=' || i == '+' || i == '$' ||
            i == ',' || Uri::IsUnreserved((TChar)i)) {
            uri->Replace(uriString);
            TEST(uri->Path() == uriPath);
        }
        else {
            TEST_THROWS(uri->Replace(uriString); (void)uri, UriError);
        }
    }
    uriString[30] = 'p';
    uriPath[5] = 'p';

    // escaping - test that excluded characters get escaped
    for(i=0 ; i<128 ; i++) {
        uriString[30] = (TByte)i;
        if (i == '#' || i == '?') {
            // skip this as queries and fragments are tested below
            continue;
        }
        else if (Uri::IsExcluded((TChar)i)) {
            // a character that gets escaped
            uriPath.Replace("/test");
            uriPath.Append("%");
            Ascii::AppendHex(uriPath, (TByte)i);
            uriPath.Append("ath");
            uri->Replace(uriString);
            TEST(uri->Path() == uriPath);
        }
        else if (i == '/' || i == ';' || i == ':' || i == '@' ||
            i == '&' || i == '=' || i == '+' || i == '$' ||
            i == ',' || Uri::IsUnreserved((TChar)i)) {
            // a normal character that does not get escaped
            uriPath.Replace("/testpath");
            uriPath[5] = (TByte)i;
            uri->Replace(uriString);
            TEST(uri->Path() == uriPath);
        }
        else {
            // This should not happen - 3 branches above should cover all
            TEST(0==1);
        }
    }
    uriString[30] = 'p';
    uriPath.Replace("/testpath");

    // escaping - already escaped characters don't get re-escaped
    uriString[29] = '%';
    uriPath[4] = '%';
    uriString[30] = 'a';
    uriPath[5] = 'a';
    for(i=0 ; i<128 ; i++) {
        uriString[31] = (TByte)i;
        if (i == '#' || i == '?') {
            // skip this as queries and fragments are tested below
            continue;
        }
        else if (Ascii::IsHex((TChar)i)) {
            // an already escaped string
            uriPath.Replace("/tes%aath");
            uriPath[6] = (TByte)i;
            uri->Replace(uriString);
            TEST(uri->Path() == uriPath);
        }
        else if (Uri::IsExcluded((TChar)i)) {
            // Not an escape sequence, so the original '%' gets escaped as well
            // as this character
            uriPath.Replace("/tes%25a");
            uriPath.Append("%");
            Ascii::AppendHex(uriPath, (TByte)i);
            uriPath.Append("th");
            uri->Replace(uriString);
            TEST(uri->Path() == uriPath);
        }
        else if (i == '/' || i == ';' || i == ':' || i == '@' ||
            i == '&' || i == '=' || i == '+' || i == '$' ||
            i == ',' || Uri::IsUnreserved((TChar)i)) {
            // Not an escape sequence, but only the original '%' gets escaped
            uriPath.Replace("/tes%25aath");
            uriPath[8] = (TByte)i;
            uri->Replace(uriString);
            TEST(uri->Path() == uriPath);
        }
    }
    }

    // Fragment and query tests
    {
    Brn uriFragString1("testscheme://testhost:123/testpath#");
    uri->Replace(uriFragString1);
    TEST(uri->AbsoluteUri() == Brn("testscheme://testhost:123/testpath"));
    TEST(uri->Scheme() == Brn("testscheme"));
    TEST(uri->Host() == Brn("testhost"));
    TEST(uri->Port() == 123);
    TEST(uri->Authority() == Brn("testhost:123"));
    TEST(uri->Path() == Brn("/testpath"));
    TEST(uri->Query() == Brn(""));
    TEST(uri->PathAndQuery() == Brn("/testpath"));
    TEST(uri->Fragment() == Brn(""));
    }

    {
    Brn uriFragString2("testscheme://testhost:123/testpath#testfragment");
    uri->Replace(uriFragString2);
    TEST(uri->AbsoluteUri() == Brn("testscheme://testhost:123/testpath%23testfragment"));
    TEST(uri->Scheme() == Brn("testscheme"));
    TEST(uri->Host() == Brn("testhost"));
    TEST(uri->Port() == 123);
    TEST(uri->Authority() == Brn("testhost:123"));
    TEST(uri->Path() == Brn("/testpath"));
    TEST(uri->Query() == Brn(""));
    TEST(uri->PathAndQuery() == Brn("/testpath"));
    TEST(uri->Fragment() == Brn("%23testfragment"));
    }

    {
    Brn uriQueryString1("testscheme://testhost:123/testpath?");
    uri->Replace(uriQueryString1);
    TEST(uri->AbsoluteUri() == Brn("testscheme://testhost:123/testpath"));
    TEST(uri->Scheme() == Brn("testscheme"));
    TEST(uri->Host() == Brn("testhost"));
    TEST(uri->Port() == 123);
    TEST(uri->Authority() == Brn("testhost:123"));
    TEST(uri->Path() == Brn("/testpath"));
    TEST(uri->Query() == Brn(""));
    TEST(uri->PathAndQuery() == Brn("/testpath"));
    TEST(uri->Fragment() == Brn(""));
    }

    {
    Brn uriQueryString2("testscheme://testhost:123/testpath?testquery");
    uri->Replace(uriQueryString2);
    TEST(uri->AbsoluteUri() == Brn("testscheme://testhost:123/testpath?testquery"));
    TEST(uri->Scheme() == Brn("testscheme"));
    TEST(uri->Host() == Brn("testhost"));
    TEST(uri->Port() == 123);
    TEST(uri->Authority() == Brn("testhost:123"));
    TEST(uri->Path() == Brn("/testpath"));
    TEST(uri->Query() == Brn("?testquery"));
    TEST(uri->PathAndQuery() == Brn("/testpath?testquery"));
    TEST(uri->Fragment() == Brn(""));
    }

    {
    Brn uriQueryFragString("testscheme://testhost:123/testpath?testquery#testfragment");
    uri->Replace(uriQueryFragString);
    TEST(uri->AbsoluteUri() == Brn("testscheme://testhost:123/testpath?testquery%23testfragment"));
    TEST(uri->Scheme() == Brn("testscheme"));
    TEST(uri->Host() == Brn("testhost"));
    TEST(uri->Port() == 123);
    TEST(uri->Authority() == Brn("testhost:123"));
    TEST(uri->Path() == Brn("/testpath"));
    TEST(uri->Query() == Brn("?testquery"));
    TEST(uri->PathAndQuery() == Brn("/testpath?testquery"));
    TEST(uri->Fragment() == Brn("%23testfragment"));
    }

    // Length tests
    {
    Bws<1100> uriString;
    uriString.Replace("testscheme://testhost:123/testpath?testquery#testfragment");  // 59 (# -> %23)
    for(TUint j=0 ; j<19 ; j++) {
        uriString.Append("12345678901234567890123456789012345678901234567890"); // + 19*50 = 1009
    }
    uriString.Append("123456789012345");  // + 15 = 1024
    uri->Replace(uriString);
    TEST(1==1);
    uriString.Append("0");  // + 1 = 1025
    
    TEST_THROWS(uri->Replace(uriString), UriError);

    // No fragment
    uriString.Replace("testscheme://testhost:123/testpath?testquery");  // 44
    for(TUint k=0 ; k<19 ; k++) {
        uriString.Append("12345678901234567890123456789012345678901234567890"); // + 19*50 = 994
    }
    uriString.Append("123456789012345678901234567890"); // + 30 = 1024

    uri->Replace(uriString);
    TEST(1==1);
    uriString.Append("0");  // + 1 = 1025
    TEST_THROWS(uri->Replace(uriString), UriError);

    // No fragment or query
    uriString.Replace("testscheme://testhost:123/testpath");  // 34
    for(TUint l=0 ; l<19 ; l++) {
        uriString.Append("12345678901234567890123456789012345678901234567890"); // + 19*50 = 984
    }
    uriString.Append("1234567890123456789012345678901234567890"); // + 40 = 1024

    uri->Replace(uriString);
    TEST(1==1);
    uriString.Append("0");  // + 1 = 1025
    TEST_THROWS(uri->Replace(uriString), UriError);

    // No fragment or query or port
    uriString.Replace("testscheme://testhost/testpath");  // 30
    for(TUint m=0 ; m<19 ; m++) {
        uriString.Append("12345678901234567890123456789012345678901234567890"); // + 19*50 = 980
    }
    uriString.Append("12345678901234567890123456789012345678901234"); // + 44 = 1024

    uri->Replace(uriString);
    TEST(1==1);
    uriString.Append("0");  // + 1 = 1025

    TEST_THROWS(uri->Replace(uriString), UriError);
    }

    delete uri;
}

class SuiteSwap : public Suite
{
public:
    SuiteSwap() : Suite("Test endian swapping"), iCalls(0) {}
    void Test();
private:
    TUint16 Get16(TUint16 aValue) { iCalls++; return aValue; }
    TUint32 Get32(TUint32 aValue) { iCalls++; return aValue; }
    TBool CheckCalls() { TUint calls = iCalls; iCalls = 0 ; return calls == 1; }
private:
    TUint iCalls;
};

void SuiteSwap::Test()
{
    // Test endianness swapping functions

    volatile TUint64 num64 = 0x123456789ABCDEF0ull;
    TEST(SwapEndian32((TUint32)num64) == 0xF0DEBC9A);
    TEST(SwapEndian16((TUint16)num64) == 0xF0DE);

    volatile TUint32 num32 = 0x12345678ul;
    TEST(SwapEndian32(num32) == 0x78563412);
    TEST(SwapEndian16((TUint16)num32) == 0x7856);

    volatile TUint16 num16 = 0x1234;
    TEST(SwapEndian32(num16) == 0x34120000);
    TEST(SwapEndian16(num16) == 0x3412);

    // Previous implementations of Swap* were evaluating the
    // argument multiple times, which might be unexected.
    // Check that it's fixed.

    volatile TUint32 n0 = 0x12345678ul;
    TEST(SwapEndian32(Get32(n0)) == 0x78563412);
    TEST(CheckCalls());

    volatile TUint16 n1 = 0x1234;
    TEST(SwapEndian16(Get16(n1)) == 0x3412);
    TEST(CheckCalls());
}


class SuiteUnicode : public Suite
{
public:
    SuiteUnicode() : Suite("Test utf8 encoding") {}
    void Test();
};

void SuiteUnicode::Test()
{
    Bws<6> buf;

    // test the byte count
    Converter::ToUtf8(0x01, buf); // buffer
    TEST(buf.Bytes()==1);

    Converter::ToUtf8(0x7f, buf);
    TEST(buf.Bytes()==1);
    Converter::ToUtf8(0x80, buf);
    TEST(buf.Bytes()==2);

    Converter::ToUtf8(0x7ff, buf);
    TEST(buf.Bytes()==2);
    Converter::ToUtf8(0x800, buf);
    TEST(buf.Bytes()==3);

    Converter::ToUtf8(0xffff, buf);
    TEST(buf.Bytes()==3);
    Converter::ToUtf8(0x10000, buf);
    TEST(buf.Bytes()==4);

    Converter::ToUtf8(0x1fffff, buf);
    TEST(buf.Bytes()==4);
    Converter::ToUtf8(0x200000, buf);
    TEST(buf.Bytes()==5);

    Converter::ToUtf8(0x3ffffff, buf);
    TEST(buf.Bytes()==5);
    //

    // test the values
    // 1 byte
    Converter::ToUtf8(0x01, buf);
    TEST(buf[0]==0x01);
    Converter::ToUtf8(0x7f, buf);
    TEST(buf[0]==0x7f);

    // 2 bytes
    Converter::ToUtf8(0x577, buf);
    TEST(buf[0]==0xd5);
    TEST(buf[1]==0xb7);

    // 3 bytes
    Converter::ToUtf8(0x1234, buf);
    TEST(buf[0]==0xe1);
    TEST(buf[1]==0x88);
    TEST(buf[2]==0xb4);


    //// 4 bytes
    Converter::ToUtf8(0x15678, buf);
    TEST(buf[0]==0xf0);
    TEST(buf[1]==0x95);
    TEST(buf[2]==0x99);
    TEST(buf[3]==0xb8);

    // 5 bytes
    Converter::ToUtf8(0x29abcde, buf);
    TEST(buf[0]==0xfa);
    TEST(buf[1]==0xa6);
    TEST(buf[2]==0xab);
    TEST(buf[3]==0xb3);
    TEST(buf[4]==0x9e);

    // 6 bytes
    Converter::ToUtf8(0x5f012345, buf);
    TEST(buf[0]==0xfd);
    TEST(buf[1]==0x9f);
    TEST(buf[2]==0x80);
    TEST(buf[3]==0x92);
    TEST(buf[4]==0x8d);
    TEST(buf[5]==0x85);
}


void TestTextUtils()
{
    Runner runner("Ascii System");
    runner.Add(new SuiteAscii());
    runner.Add(new SuiteParser());
    runner.Add(new SuiteUri());
    runner.Add(new SuiteSwap());
    runner.Add(new SuiteUnicode());
    runner.Run();
}
