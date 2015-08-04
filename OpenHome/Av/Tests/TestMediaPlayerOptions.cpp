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
    , iOptionClockPull("", "--clockpull", "Enable clock pulling")
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
    iParser.AddOption(&iOptionClockPull);
}

void TestMediaPlayerOptions::AddOption(Option* aOption)
{
    iParser.AddOption(aOption);
}

TBool TestMediaPlayerOptions::Parse(int aArgc, char* aArgv[])
{
    return iParser.Parse(aArgc, aArgv);
}

const OptionString& TestMediaPlayerOptions::Room() const
{
    return iOptionRoom;
}

const OptionString& TestMediaPlayerOptions::Name() const
{
    return iOptionName;
}

const OptionString& TestMediaPlayerOptions::Udn() const
{
    return iOptionUdn;
}

const OptionUint& TestMediaPlayerOptions::Channel() const
{
    return iOptionChannel;
}

const OptionUint& TestMediaPlayerOptions::Adapter() const
{
    return iOptionAdapter;
}

const OptionBool& TestMediaPlayerOptions::Loopback() const
{
    return iOptionLoopback;
}

const OptionString& TestMediaPlayerOptions::TuneIn() const
{
    return iOptionTuneIn;
}

const OptionString& TestMediaPlayerOptions::Tidal() const
{
    return iOptionTidal;
}

const OptionString& TestMediaPlayerOptions::Qobuz() const
{
    return iOptionQobuz;
}

const OptionString& TestMediaPlayerOptions::UserAgent() const
{
    return iOptionUserAgent;
}

const OptionBool& TestMediaPlayerOptions::ClockPull() const
{
    return iOptionClockPull;
}
