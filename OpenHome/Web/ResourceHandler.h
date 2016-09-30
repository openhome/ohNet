#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Fifo.h>

EXCEPTION(ResourceInvalid);

namespace OpenHome {
    class FileAnsii;
    class IWriter;
namespace Web {

class IResourceHandler
{
public:
    virtual TUint Bytes() = 0;                  // 0 => unknown size
    virtual void Write(IWriter& aWriter) = 0;   // THROWS WriterError
    virtual void Destroy() = 0;
    virtual ~IResourceHandler() {}
};

class IResourceManager
{
public:
    virtual IResourceHandler* CreateResourceHandler(const Brx& aResourceTail) = 0;  // THROWS ResourceInvalid
    virtual ~IResourceManager() {}
};

class ResourceHandlerBase;

class IResourceHandlerDeallocator
{
public:
    virtual void Deallocate(ResourceHandlerBase* aResourceHandler) = 0;
    virtual ~IResourceHandlerDeallocator() {}
};

class IResourceHandlerFactory
{
public:
    virtual ResourceHandlerBase* NewResourceHandler(const Brx& aRootDir, IResourceHandlerDeallocator& aDeallocator) = 0;
    virtual ~IResourceHandlerFactory() {}
};

class ResourceHandlerBase : public IResourceHandler
{
protected:
    ResourceHandlerBase(const Brx& aRootDir, IResourceHandlerDeallocator& aDeallocator);
public: // from IResourceHandlerReusable
    virtual TUint Bytes() = 0;
    virtual void Write(IWriter& aWriter) = 0;
    virtual void Destroy() override;
public:
    virtual void SetResource(const Brx& aResourceTail) = 0;
protected:
    virtual void Clear() = 0;
private:
    IResourceHandlerDeallocator& iDeallocator;
protected:
    OpenHome::Brh iRootDir;
};

/**
 * ResourceManager that blocks on CreateResourceHandler() call until next
 * IResourceHandler is available.
 */
class BlockingResourceManager : public IResourceManager, public IResourceHandlerDeallocator
{
public:
    BlockingResourceManager(IResourceHandlerFactory& aFactory, TUint aResourceHandlerCount, const Brx& aRootDir);
    ~BlockingResourceManager();
public: // from IResourceManager
    IResourceHandler* CreateResourceHandler(const Brx& aResourceTail) override;
private: // from IResourceHandlerDeallocator
    void Deallocate(ResourceHandlerBase* aResourceHandler) override;
private:
    Fifo<ResourceHandlerBase*> iFifo;
};

} // namespace Web
} // namespace OpenHome
