#ifndef HEADER_MIMETYPE_LIST
#define HEADER_MIMETYPE_LIST

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Functor.h>

#include <vector>

namespace OpenHome {
namespace Media {

class IMimeTypeList
{
public:
    virtual ~IMimeTypeList() {}
    /**
     * Register a single MIME type as supported.  May be called multiple times.
     *
     * @param[in] aMimeType      MIME type.  Must remain valid for the duration of the program.
     */
    virtual void Add(const TChar* aMimeType) = 0;
};

class MimeTypeList : public IMimeTypeList
{
public:
    MimeTypeList();
    TBool Contains(const TChar* aMimeType) const;
    void AddUpnpProtocolInfoObserver(FunctorGeneric<const Brx&> aCallback);
    void Start();
public: // from IMimeTypeList
    void Add(const TChar* aMimeType) override;
private:
    std::vector<Brn> iMimeTypes;
    std::vector<FunctorGeneric<const Brx&>> iUpnpProtocolInfoObservers;
    Brh iUpnpProtocolInfo;
    TBool iStarted;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_MIMETYPE_LIST
