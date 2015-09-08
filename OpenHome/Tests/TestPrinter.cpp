#include <memory>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/Arch.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/FunctorMsg.h>

using namespace OpenHome;
using namespace OpenHome::TestFramework;

class SuitePrinter : public Suite
{
public:
    SuitePrinter() : Suite("Printer Log Message Tests") {}
    void Test();
};



class MessageCheck
{
public:
    MessageCheck(const Brx& aExpected);
public:
    FunctorMsg& GetFunctor() const;
    TBool Check() const;
    void Compare(const char* aMsg); 
private:
    Brn iExpected;
    TBool iMatch;
};


MessageCheck::MessageCheck(const Brx& aExpected)
    : iExpected(aExpected)
    , iMatch(false)
{
}

void MessageCheck::Compare(const char* aMsg)
{
    Brn msg(aMsg);
    iMatch = (msg == iExpected) ? true : false;
}
  
TBool MessageCheck::Check() const
{
    return iMatch;
}

    
void SuitePrinter::Test()
{
    MessageCheck Test1Check(Brn("Test 1 (Buffer Only): Test 1 success!\n")); 
    FunctorMsg test1Functor = MakeFunctorMsg(Test1Check, &MessageCheck::Compare);
    Log::SwapOutput(test1Functor);
    Brn test1("Test 1 success!");
    Log::Print("Test 1 (Buffer Only): %.*s\n", PBUF(test1));
    TEST(Test1Check.Check());
    
    
    MessageCheck Test2Check(Brn("Test 2 (Two consecutive buffers): Test 2 success! Test 2a success!\n")); 
    FunctorMsg test2Functor = MakeFunctorMsg(Test2Check, &MessageCheck::Compare);
    Log::SwapOutput(test2Functor);
    Brn test2("Test 2 success!");
    Brn test2a("Test 2a success!");
    Log::Print("Test 2 (Two consecutive buffers): %.*s %.*s\n", PBUF(test2), PBUF(test2a));
    TEST(Test2Check.Check());
    
    MessageCheck Test3Check(Brn("Test 3 (One int then one buffer in arg list): Test 3 success!\n")); 
    FunctorMsg test3Functor = MakeFunctorMsg(Test3Check, &MessageCheck::Compare);
    Log::SwapOutput(test3Functor);
    Brn test3("Test 3 success!");
    Log::Print("Test %d (One int then one buffer in arg list): %.*s\n", 3, PBUF(test3));
    TEST(Test3Check.Check());
    
    MessageCheck Test4Check(Brn("Test 4 (One buffer between two other types): Test 4 success!\n")); 
    FunctorMsg test4Functor = MakeFunctorMsg(Test4Check, &MessageCheck::Compare);
    Log::SwapOutput(test4Functor);
    Brn test4("Test 4 success");
    Log::Print("Test %d (One buffer between two other types): %.*s%c\n", 4, PBUF(test4), '!');
    TEST(Test4Check.Check());
    
    MessageCheck Test5Check(Brn("Test 5 (One buffer of 3 hex values): Three hex values: 0x41 0x42 0x43\n")); 
    FunctorMsg test5Functor = MakeFunctorMsg(Test5Check, &MessageCheck::Compare);
    Log::SwapOutput(test5Functor);
    Brn test5("ABC");
    Bws<30> test5hex;
    Ascii::AppendHex(test5hex, test5);
    Log::Print("Test 5 (One buffer of 3 hex values): Three hex values: %.*s\n", PBUF(test5hex));
    TEST(Test5Check.Check());

    MessageCheck Test6Check(Brn("Test 6 (Bool): True is true false is false\n")); 
    FunctorMsg test6Functor = MakeFunctorMsg(Test6Check, &MessageCheck::Compare);
    Log::SwapOutput(test6Functor);
    TBool trueness = true;
    TBool falseness = false;
    Log::Print("Test 6 (Bool): True is %s false is %s\n", PBool(trueness), PBool(falseness));
    TEST(Test6Check.Check());
    
    MessageCheck Test7Check(Brn("Test 7 (custom Bool): True is on false is off\n")); 
    FunctorMsg test7Functor = MakeFunctorMsg(Test7Check, &MessageCheck::Compare);
    Log::SwapOutput(test7Functor);
    Log::Print("Test 7 (custom Bool): True is %s false is %s\n", PBool(trueness, "on", "off"), PBool(falseness, "on", "off"));
    TEST(Test7Check.Check());
}

///////////////////////////////////
void TestPrinter()
{
    Runner runner("Binary Buffer Testing");
    runner.Add(new SuitePrinter());
    runner.Run();
}
