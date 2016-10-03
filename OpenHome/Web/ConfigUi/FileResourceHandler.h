#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Web/ResourceHandler.h>
#include <OpenHome/Web/WebAppFramework.h>
#include <OpenHome/Web/ConfigUi/ConfigUi.h>

namespace OpenHome {
    class FileAnsii;
namespace Web {

/**
 * A default resource handler that serves files from a posix-style filesystem.
 */
class FileResourceHandler : public ResourceHandlerBase
{
public:
    FileResourceHandler(const Brx& aRootDir, IResourceHandlerDeallocator& aDeallocator);
public: // from ResourceHandlerBase
    TUint Bytes() override;
    void Write(IWriter& aWriter) override;
    void SetResource(const Brx& aResourceTail) override;
    void Clear() override;
private:
    OpenHome::FileAnsii* iFile;
};

class LanguageResourceFileReader : public ILanguageResourceReader
{
private:
    static const TUint kMaxBufBytes = 1024;
public:
    LanguageResourceFileReader(const Brx& aRootDir);
public: // from ILanguageResourceReader
    void SetResource(const Brx& aUriTail) override;
    TBool Allocated() const override;
    void Process(const Brx& aKey, IResourceFileConsumer& aResourceConsumer) override;
private:
    Brn iRootDir;
    FileStream iFileStream;
    Srs<512> iReadBuffer;
    ReaderTextS<kMaxBufBytes> iReaderText;
    TBool iAllocated;
    mutable Mutex iLock;
};

class FileResourceHandlerFactory : public IConfigAppResourceHandlerFactory
{
private: // from IConfigAppResourceHandlerFactory
    ResourceHandlerBase* NewResourceHandler(const Brx& aRootDir, IResourceHandlerDeallocator& aDeallocator) override;
    ILanguageResourceReader* NewLanguageReader(const Brx& aResourceDir) override;
};

} // namespace Web
} // namespace OpenHome
