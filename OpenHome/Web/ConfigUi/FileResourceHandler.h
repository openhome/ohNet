#pragma once

#include <OpenHome/Web/WebAppFramework.h>
#include <OpenHome/Web/ConfigUi/ConfigUi.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>

namespace OpenHome {
    class FileAnsii;
namespace Web {

// FIXME - file handling should eventually be replaced with a cross-platform
// resource handling layer. This currently only works on posix-style filesystems.
// FIXME - make this thread aware
// - could state of Allocated() be changed while a (thread-safe) ResourceManager is inspecting it?
class FileResourceHandler : public IResourceHandler
{
public:
    FileResourceHandler(const OpenHome::Brx& aRootDir);
public : // from IResourceHandler
    TBool Allocated() override;
    void SetResource(const OpenHome::Brx& aUri) override;
    TUint Bytes() override;
    void Write(OpenHome::IWriter& aWriter) override;
    void Destroy() override;
private:
    void SetMimeType(const OpenHome::Brx& aUri);
private:
    OpenHome::Brh iRootDir;
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
    void Process(IResourceFileConsumer& aResourceConsumer) override;
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
    IResourceHandler* NewResourceHandler(const Brx& aResourceDir) override;
    ILanguageResourceReader* NewLanguageReader(const Brx& aResourceDir) override;
};

} // namespace Web
} // namespace OpenHome
