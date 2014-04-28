#ifndef HEADER_PIPELINE_URIPROVIDER_REPEATER
#define HEADER_PIPELINE_URIPROVIDER_REPEATER

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Media/Msg.h>
#include <OpenHome/Media/Filler.h>

namespace OpenHome {
namespace Av {

class UriProviderRepeater : public Media::UriProvider
{
public:
    UriProviderRepeater(const TChar* aMode, Media::TrackFactory& aTrackFactory);
    ~UriProviderRepeater();
    Media::Track* SetTrack(const Brx& aUri, const Brx& aMetaData, TBool aPullable);
    void SetTrack(Media::Track* aTrack);
public: // from UriProvider // FIXME - should these be private?
    void Begin(TUint aTrackId);
    void BeginLater(TUint aTrackId);
    Media::EStreamPlay GetNext(Media::Track*& aTrack);
    TUint CurrentTrackId() const;
    TBool MoveNext();
    TBool MovePrevious();
private:
    void DoBegin(TUint aTrackId, TBool aLater);
    TBool MoveCursor();
private:
    mutable Mutex iLock;
    Media::TrackFactory& iTrackFactory;
    Media::Track* iTrack;
    TBool iRetrieved;
    TBool iPlayLater;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_URIPROVIDER_REPEATER
