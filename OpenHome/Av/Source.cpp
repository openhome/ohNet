#include <OpenHome/Av/Source.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>

using namespace OpenHome;
using namespace OpenHome::Av;

Source::~Source()
{
}

const Brx& Source::SystemName() const
{
    return iSystemName;
}

const Brx& Source::Type() const
{
    return iType;
}

const Brx& Source::Name() const
{
    return iName;
}

TBool Source::IsVisible() const
{
    return iVisible;
}

Source::Source(const TChar* aSystemName, const TChar* aType)
    : iSystemName(aSystemName)
    , iType(aType)
    , iName(aSystemName)
    , iVisible(true)
{
}
