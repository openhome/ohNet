#include <OpenHome/Media/MimeTypeList.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Standard.h>

#include <vector>

using namespace OpenHome;
using namespace OpenHome::Media;

MimeTypeList::MimeTypeList()
    : iStarted(false)
{
}

TBool MimeTypeList::Contains(const TChar* aMimeType) const
{
    Brn mimeType(aMimeType);
    for (auto it=iMimeTypes.begin(); it!=iMimeTypes.end(); ++it) {
        if (*it == mimeType) {
            return true;
        }
    }
    return false;
}

void MimeTypeList::AddUpnpProtocolInfoObserver(FunctorGeneric<const Brx&> aCallback)
{
    ASSERT(!iStarted);
    ASSERT(aCallback);
    iUpnpProtocolInfoObservers.push_back(aCallback);
}

void MimeTypeList::Start()
{
    ASSERT(!iStarted);
    iStarted = true;
    if (iUpnpProtocolInfoObservers.size() == 0) {
        return;
    }
    TBool firstItem = true;
    WriterBwh writer(256);
    for (auto it=iMimeTypes.begin(); it!=iMimeTypes.end(); ++it) {
        if (firstItem) {
            firstItem = false;
        }
        else {
            writer.Write(',');
        }
        writer.Write("http-get:*:");
        writer.Write(*it);
        writer.Write(":*");
    }
    // FIXME - temporary bodge until Kazoo stops checking Tidal/Qobuz support via ProtocolInfo
    writer.Write(",tidalhifi.com:*:*:*");
    writer.Write(",qobuz.com:*:*:*");
    //
    writer.TransferTo(iUpnpProtocolInfo);

    for (auto it=iUpnpProtocolInfoObservers.begin(); it!=iUpnpProtocolInfoObservers.end(); ++it) {
        (*it)(iUpnpProtocolInfo);
    }
}

void MimeTypeList::Add(const TChar* aMimeType)
{
    if (Contains(aMimeType)) {
        return;
    }
    Brn mimeType(aMimeType);
    iMimeTypes.push_back(mimeType);
}
