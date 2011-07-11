#include <RefCounter.h>
#include <OhNetTypes.h>

using namespace OpenHome;

RefCounter::RefCounter()
    : iCounter(1)
{
}

RefCounter::~RefCounter()
{
}

void RefCounter::IncRef() const
{
    iCounter.Inc();
}

void RefCounter::DecRef() const
{
    if(iCounter.Dec() == 0) {
        delete this;
    }
}


