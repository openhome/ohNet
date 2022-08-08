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

    // Unfound tag should throw XmlError
    TEST_THROWS(XmlParserBasic::Find("unfindable", xmlBuffer), XmlError);

    // Test TChar and Brn interfaces.
    TEST(XmlParserBasic::Find("thing", xmlBuffer) == Brn("hidden goodies"));
    TEST(XmlParserBasic::Find(Brn("thing"), xmlBuffer) == Brn("hidden goodies"));

    // Get inner tag and check
    Brn inner = XmlParserBasic::Find("inner", xmlBuffer);

    TEST(inner == Brn(
        "<person name=\"alpha\" age=\"21\">"        \
            "<thing>hidden goodies</thing>"         \
        "</person>"                                 \
        "<person name=\"beta\" age=\"34\"/>"));

    // Find attrubute on person 'alpha'
    TEST(XmlParserBasic::FindAttribute("person", "name", inner) == Brn("alpha"));

    Brn remaining;
    TEST(XmlParserBasic::Find("person", inner, remaining) == Brn(
        "<thing>hidden goodies</thing>"));

    TEST(remaining == Brn(
        "<person name=\"beta\" age=\"34\"/>"));

    TEST(XmlParserBasic::FindAttribute("person", "name", remaining) == Brn("beta"));
    TEST(XmlParserBasic::FindAttribute("person", "age",  remaining) == Brn("34"));


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
    TEST(XmlParserBasic::Element("person", xmlBuffer) == personTag);
    TEST(XmlParserBasic::Element("person", xmlBuffer, remaining) == personTag);

    TEST(XmlParserBasic::Element(Brn("thing"), xmlBuffer, remaining) == Brn("<thing>hidden goodies</thing>"));
    TEST(XmlParserBasic::Element(Brn("inner"), xmlBuffer, remaining) == innerTag);
    TEST(XmlParserBasic::Element(Brn("inner"), xmlBuffer) == innerTag);


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

