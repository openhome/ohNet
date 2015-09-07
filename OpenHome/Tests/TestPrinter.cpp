#include <memory>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/Arch.h>
#include <OpenHome/Private/Printer.h>


using namespace OpenHome;
using namespace OpenHome::TestFramework;

class SuitePrinter : public Suite
{
public:
    SuitePrinter() : Suite("Printer Log Message Tests") {}
    void Test();
};

void SuitePrinter::Test()
{
    Brn test1("Test 1 success!");
    Log::Print("Test 1 (Buffer Only): %.*s\n", PBUF(test1));
    
    Brn test2("Test 2 success!");
    Brn test2a("Test 2a success!");
    Log::Print("Test 2 (Two consecutive buffers): %.*s %.*s\n", PBUF(test2), PBUF(test2a));
    
    Brn test3("Test 3 success!");
    Log::Print("Test %d (One int then one buffer in arg list): %.*s\n", 3, PBUF(test3));
    
    Brn test4("Test 4 success");
    Log::Print("Test %d (One buffer between two other types): %.*s%c\n", 4, PBUF(test4), '!');
    
    Bws<3> test5;
    TByte byte1 = 0x00000001;
    TByte byte2 = 0x00000002;
    TByte byte3 = 0x00000003;
    
    test5.Append(byte1);
    test5.Append(byte2);
    test5.Append(byte3);
    Log::Print("Test 5 (One buffer of 3 hex values): Three hex values: %.*x\n", PBUF(test5));
    TBool trueness = true;
    TBool falseness = false;
    Log::Print("Test 6 (Bool): True is %s false is %s\n", PBOOL(trueness), PBOOL(falseness));
}

///////////////////////////////////
void TestPrinter()
{
    Runner runner("Binary Buffer Testing");
    runner.Add(new SuitePrinter());
    runner.Run();
}
