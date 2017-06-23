#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Media/Filler.h>
#include <OpenHome/Private/Thread.h>

namespace OpenHome {
namespace Scd {

class UriProviderScd : public Media::UriProvider
{
    static const Brn kCommandUri;
public:
    UriProviderScd(Media::TrackFactory& aTrackFactory);
    ~UriProviderScd();
    void Reset();
private: // UriProvider
    void Begin(TUint aTrackId) override;
    void BeginLater(TUint aTrackId) override;
    Media::EStreamPlay GetNext(Media::Track*& aTrack) override;
    TUint CurrentTrackId() const override;
    void MoveNext() override;
    void MovePrevious() override;
    void MoveTo(const Brx& aCommand) override;
private:
    Media::TrackFactory& iTrackFactory;
    mutable Mutex iLock;
    Media::Track* iTrack;
    Media::EStreamPlay iCanPlay;
};

} // namespace Scd
} // namespace OpenHome
