#include <OpenHome/Av/Source.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Av/Product.h>

using namespace OpenHome;
using namespace OpenHome::Av;

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

void Source::Deactivate()
{
    iActive = false;
}

void Source::SetVisible(TBool aVisible)
{
    iVisible = aVisible;
}

Source::Source(const TChar* aSystemName, const TChar* aType)
    : iActive(false)
    , iSystemName(aSystemName)
    , iType(aType)
    , iName(aSystemName)
    , iVisible(true)
    , iProduct(NULL)
{
}

TBool Source::IsActive() const
{
    return iActive;
}

void Source::DoActivate()
{
    iActive = true;
    iProduct->Activate(*this);
}

void Source::Initialise(IProduct& aProduct)
{
    iProduct = &aProduct;
}
