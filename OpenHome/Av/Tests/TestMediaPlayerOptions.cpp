#include <OpenHome/Av/Tests/TestMediaPlayer.h>
#include <OpenHome/Private/OptionParser.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Av::Test;

TestMediaPlayerOptions::TestMediaPlayerOptions()
    : iOptionRoom("-r", "--room", Brn(""), "room the Product service will report")
    , iOptionName("-n", "--name", Brn("SoftPlayer"), "Product name")
    , iOptionUdn("-u", "--udn", Brn(""), "Udn (optional - one will be generated if this is left blank)")
    , iOptionChannel("-c", "--channel", 0, "[0..65535] sender channel")
    , iOptionAdapter("-a", "--adapter", 0, "[adapter] index of network adapter to use")
    , iOptionLoopback("-l", "--loopback", "Use loopback adapter")
    , iOptionTuneIn("-t", "--tunein", Brn(""), "TuneIn partner id")
    , iOptionTidal("", "--tidal", Brn(""), "Tidal token")
    , iOptionQobuz("", "--qobuz", Brn(""), "app_id:app_secret")
    , iOptionUserAgent("", "--useragent", Brn(""), "User Agent (for HTTP requests)")
{
    iParser.AddOption(&iOptionRoom);
    iParser.AddOption(&iOptionName);
    iParser.AddOption(&iOptionUdn);
    iParser.AddOption(&iOptionChannel);
    iParser.AddOption(&iOptionAdapter);
    iParser.AddOption(&iOptionLoopback);
    iParser.AddOption(&iOptionTuneIn);
    iParser.AddOption(&iOptionTidal);
    iParser.AddOption(&iOptionQobuz);
    iParser.AddOption(&iOptionUserAgent);
}

void TestMediaPlayerOptions::AddOption(Option* aOption)
{
    iParser.AddOption(aOption);
}

TBool TestMediaPlayerOptions::Parse(int aArgc, char* aArgv[])
{
    return iParser.Parse(aArgc, aArgv);
}

OptionString& TestMediaPlayerOptions::Room()
{
    return iOptionRoom;
}

OptionString& TestMediaPlayerOptions::Name()
{
    return iOptionName;
}

OptionString& TestMediaPlayerOptions::Udn()
{
    return iOptionUdn;
}

OptionUint& TestMediaPlayerOptions::Channel()
{
    return iOptionChannel;
}

OptionUint& TestMediaPlayerOptions::Adapter()
{
    return iOptionAdapter;
}

OptionBool& TestMediaPlayerOptions::Loopback()
{
    return iOptionLoopback;
}

OptionString& TestMediaPlayerOptions::TuneIn()
{
    return iOptionTuneIn;
}

OptionString& TestMediaPlayerOptions::Tidal()
{
    return iOptionTidal;
}

OptionString& TestMediaPlayerOptions::Qobuz()
{
    return iOptionQobuz;
}

OptionString& TestMediaPlayerOptions::UserAgent()
{
    return iOptionUserAgent;
}
