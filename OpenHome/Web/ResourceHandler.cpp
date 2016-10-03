#include <OpenHome/Web/ResourceHandler.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Private/Printer.h>

using namespace OpenHome;
using namespace OpenHome::Web;


// ResourceHandlerBase

ResourceHandlerBase::ResourceHandlerBase(const Brx& aRootDir, IResourceHandlerDeallocator& aDeallocator)
    : iRootDir(aRootDir)
    , iDeallocator(aDeallocator)
{
}

void ResourceHandlerBase::Destroy()
{
    Clear();
    iDeallocator.Deallocate(this);
}


// BlockingResourceManager

BlockingResourceManager::BlockingResourceManager(IResourceHandlerFactory& aFactory, TUint aResourceHandlerCount, const Brx& aRootDir)
    : iFifo(aResourceHandlerCount)
{
    for (TUint i=0; i<aResourceHandlerCount; i++) {
        iFifo.Write(aFactory.NewResourceHandler(aRootDir, *this));
    }
}

BlockingResourceManager::~BlockingResourceManager()
{
    ASSERT(iFifo.SlotsFree() == 0); // All resource handlers must have been returned.
    while (iFifo.SlotsUsed() > 0) {
        auto p = iFifo.Read();
        delete p;
    }
}

IResourceHandler* BlockingResourceManager::CreateResourceHandler(const Brx& aResourceTail)
{
    auto p = iFifo.Read();
    try {
        p->SetResource(aResourceTail);
        return p;
    }
    catch (ResourceInvalid&) {
        iFifo.Write(p);
        throw;
    }
}

void BlockingResourceManager::Deallocate(ResourceHandlerBase* aResourceHandler)
{
    iFifo.Write(aResourceHandler);
}
