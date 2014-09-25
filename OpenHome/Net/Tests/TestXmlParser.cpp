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
}

void TestXmlParser()
{
    Runner runner("Test XmlParser");
    runner.Add(new SuiteXmlParserBasic());
    runner.Run();
}

