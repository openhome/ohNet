#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Net/Private/XmlParser.h>

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Net;

class SuiteXmlParserBasic : public Suite
{
public:
    SuiteXmlParserBasic() : Suite("Basic tests") {}
    void Test();
};

void SuiteXmlParserBasic::Test()
{
    const TChar data[] =
        "<outer>"                                           \
            "<inner>"                                       \
                "<person name=\"alpha\" age=\"21\">"        \
                    "<thing>"                               \
                        "hidden goodies"                    \
                    "</thing>"                              \
                "</person>"                                 \
                "<person name=\"beta\" age=\"34\"/>"        \
            "</inner>"                                      \
        "</outer>";

    Brn xmlBuffer(data);
    Brn result;

    // Unfound tag should throw XmlError
    TEST_THROWS(XmlParserBasic::Find("unfindable", xmlBuffer), XmlError);
    TEST(XmlParserBasic::TryFind("unfindable", xmlBuffer, result) == false);

    // Test TChar and Brn interfaces.
    TEST(XmlParserBasic::Find("thing", xmlBuffer) == Brn("hidden goodies"));
    TEST(XmlParserBasic::Find(Brn("thing"), xmlBuffer) == Brn("hidden goodies"));

    TEST(XmlParserBasic::TryFind("thing", xmlBuffer, result));
    TEST(result == Brn("hidden goodies"));

    TEST(XmlParserBasic::TryFind(Brn("thing"), xmlBuffer, result));
    TEST(result == Brn("hidden goodies"));

    // Get inner tag and check
    Brn inner = XmlParserBasic::Find("inner", xmlBuffer);

    TEST(XmlParserBasic::TryFind("inner", xmlBuffer, result));
    TEST(result == inner);

    TEST(inner == Brn(
        "<person name=\"alpha\" age=\"21\">"        \
            "<thing>hidden goodies</thing>"         \
        "</person>"                                 \
        "<person name=\"beta\" age=\"34\"/>"));

    // Find attrubute on person 'alpha'
    TEST(XmlParserBasic::FindAttribute("person", "name", inner) == Brn("alpha"));

    TEST(XmlParserBasic::TryFindAttribute("person", "name", inner, result));
    TEST(result == Brn("alpha"));

    Brn remaining;
    Brn tryRemaining;

    TEST(XmlParserBasic::Find("person", inner, remaining) == Brn(
        "<thing>hidden goodies</thing>"));

    TEST(remaining == Brn(
        "<person name=\"beta\" age=\"34\"/>"));

    TEST(XmlParserBasic::TryFind("person", inner, tryRemaining, result));
    TEST(result == Brn("<thing>hidden goodies</thing>"));
    TEST(tryRemaining == remaining);

    TEST(XmlParserBasic::FindAttribute("person", "name", remaining) == Brn("beta"));
    TEST(XmlParserBasic::FindAttribute("person", "age",  remaining) == Brn("34"));

    TEST(XmlParserBasic::TryFindAttribute("person", "name", tryRemaining, result));
    TEST(result == Brn("beta"));

    TEST(XmlParserBasic::TryFindAttribute("person", "age", tryRemaining, result));
    TEST(result == Brn("34"));


    // Retrieving full tags

    Brn personTag(
        "<person name=\"alpha\" age=\"21\">"        \
            "<thing>hidden goodies</thing>"         \
        "</person>");                              \

    Brn innerTag(
            "<inner>"                                       \
                "<person name=\"alpha\" age=\"21\">"        \
                    "<thing>"                               \
                        "hidden goodies"                    \
                    "</thing>"                              \
                "</person>"                                 \
                "<person name=\"beta\" age=\"34\"/>"        \
            "</inner>");


    TEST(XmlParserBasic::Element(Brn("person"), xmlBuffer) == personTag);
    TEST(XmlParserBasic::Element(Brn("person"), xmlBuffer, remaining) == personTag);

    TEST(XmlParserBasic::TryGetElement(Brn("person"), xmlBuffer, result));
    TEST(result == personTag);

    TEST(XmlParserBasic::TryGetElement(Brn("person"), xmlBuffer, tryRemaining, result));
    TEST(result == personTag);

    TEST(XmlParserBasic::Element(Brn("thing"), xmlBuffer, remaining) == Brn("<thing>hidden goodies</thing>"));
    TEST(XmlParserBasic::Element(Brn("inner"), xmlBuffer, remaining) == innerTag);
    TEST(XmlParserBasic::Element(Brn("inner"), xmlBuffer) == innerTag);

    TEST(XmlParserBasic::TryGetElement(Brn("thing"), xmlBuffer, tryRemaining, result));
    TEST(result == Brn("<thing>hidden goodies</thing>"));

    TEST(XmlParserBasic::TryGetElement(Brn("inner"), xmlBuffer, tryRemaining, result));
    TEST(result == innerTag);

    TEST(XmlParserBasic::TryGetElement(Brn("inner"), xmlBuffer, result));
    TEST(result == innerTag);


    // Test iterating through XML/ getting Next() tag

    // When taking full xmlBuffer as input, we should get the full xml returned
    Brn tag;
    Brn next = XmlParserBasic::Next(xmlBuffer, tag, remaining);
    TEST(tag == Brn("outer"));
    TEST(next == xmlBuffer);
    TEST(remaining.Bytes() == 0);


    // When we're missing a closing tag, we should get the next complete block of xml
    Brn innerTagWithoutClose(
            "<inner>"                                       \
                "<person name=\"alpha\" age=\"21\">"        \
                    "<thing>"                               \
                        "hidden goodies"                    \
                    "</thing>"                              \
                "</person>");
    
    next = XmlParserBasic::Next(innerTagWithoutClose, tag, remaining);

    TEST(tag == Brn("person"));
    TEST(next == personTag);
    TEST(remaining.Bytes() == 0);
}

void TestXmlParser()
{
    Runner runner("Test XmlParser");
    runner.Add(new SuiteXmlParserBasic());
    runner.Run();
}

