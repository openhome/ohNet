#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/Filler.h>
#include <OpenHome/Private/Thread.h>

namespace OpenHome {
namespace Av {

class IPresetDatabaseReaderTrack;

class UriProviderRadio : public Media::UriProvider
{
    static const Brn kCommandId;
public:
    UriProviderRadio(Media::TrackFactory& aTrackFactory, IPresetDatabaseReaderTrack& aDbReader);
    ~UriProviderRadio();
    Media::Track* SetTrack(const Brx& aUri, const Brx& aMetaData);
protected: // from UriProvider
    void Begin(TUint aTrackId) override;
    void BeginLater(TUint aTrackId) override;
    Media::EStreamPlay GetNext(Media::Track*& aTrack) override;
    TUint CurrentTrackId() const override;
    TBool MoveNext() override;
    TBool MovePrevious() override;
    TBool MoveTo(const Brx& aCommand) override;
private:
    void DoBegin(TUint aTrackId, TBool aLater);
private:
    mutable Mutex iLock;
    Media::TrackFactory& iTrackFactory;
    IPresetDatabaseReaderTrack& iDbReader;
    Media::Track* iTrack;
    TBool iIgnoreNext;
    TBool iPlayLater;
};

} // namespace Av
} // namespace OpenHome
