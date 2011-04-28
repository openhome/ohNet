#ifndef HEADER_SOUNDCARD
#define HEADER_SOUNDCARD

#include <ZappTypes.h>
#include <Buffer.h>
#include <Timer.h>
#include <Exception.h>
#include <Windows.h>

#include "../../Library/Ohm.h"
#include "../../Library/OhmSender.h"

namespace Zapp {

class OhmSenderDriverWindows : public IOhmSenderDriver
{
public:
	OhmSenderDriverWindows();
private:    
	// IOhmSenderDriver
	virtual void SetEnabled(TBool aValue);
	virtual void SetEndpoint(const Endpoint& aEndpoint);
	virtual void SetActive(TBool aValue);
	virtual void SetTtl(TUint aValue);
	virtual void SetTrackPosition(TUint64 aSampleStart, TUint64 aSamplesTotal);
private:
	HANDLE iHandle;
};

class DllExportClass Soundcard
{
	static const TUint kMaxUdnBytes = 100;

public:
	DllExport static Soundcard* Create(const TChar* aName, TUint aChannel, TIpAddress aInterface, TUint aTtl, TBool aMulticast, TBool aEnabled);
	DllExport void SetName(const TChar* aValue);
	DllExport void SetChannel(TUint aValue);
    DllExport void SetInterface(TIpAddress aValue);
    DllExport void SetTtl(TUint aValue);
    DllExport void SetMulticast(TBool aValue);
	DllExport void SetEnabled(TBool aValue);
    DllExport void SetTrack(const TChar* aUri, const TChar* aMetadata, TUint64 aSamplesTotal, TUint64 aSampleStart);
	DllExport void SetMetatext(const TChar* aValue);
	DllExport ~Soundcard();

private:
	Soundcard(const TChar* aName, TUint aChannel, TIpAddress aInterface, TUint aTtl, TBool aMulticast, TBool aEnabled);

private:
	OhmSender* iSender;
	OhmSenderDriverWindows* iDriver;
	DvDeviceStandard* iDevice;
};

} // namespace Zapp

#endif // HEADER_SOUNDCARD

