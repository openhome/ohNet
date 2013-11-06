#include <OpenHome/Av/Songcast/OhmTimestamp.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/OsWrapper.h>
#include <OpenHome/Private/Env.h>

using namespace OpenHome;
using namespace OpenHome::Av;

// DefaultTimestamper

DefaultTimestamper::DefaultTimestamper(Environment& aEnv)
    : iEnv(aEnv)
{
}

TUint DefaultTimestamper::Timestamp(TUint aFrame)
{
    return Os::TimeInMs(iEnv.OsCtx());
}
