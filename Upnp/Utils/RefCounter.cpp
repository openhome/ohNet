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

void RefCounter::IncRef()
{
    iCounter.Inc();
}

void RefCounter::DecRef()
{
    if(iCounter.Dec() == 0) {
        delete this;
    }
}


