#ifndef HEADER_SONGCASTING_DRIVER
#define HEADER_SONGCASTING_DRIVER

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Private/DviStack.h>
#include <OpenHome/Net/Core/DvDevice.h>
#include <OpenHome/Media/Msg.h>
#include <OpenHome/Media/DriverSongcastSender.h>

namespace OpenHome {
namespace Media {

class SimpleSongcastingDriver
{
public:
    static const TUint kMaxDriverJiffies = Jiffies::kJiffiesPerMs * 5;
public:
    SimpleSongcastingDriver(Net::DvStack& aDvStack, IPipelineElementUpstream& aPipeline, TIpAddress aAdapter, const Brx& aSenderUdn, const TChar* aSenderFriendlyName, TUint aSenderChannel);
    ~SimpleSongcastingDriver();
private:
    Net::DvDevice* iDevice;
    DriverSongcastSender* iDriver;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_SONGCASTING_DRIVER
