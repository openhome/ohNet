#ifndef HEADER_SOUNDCARD
#define HEADER_SOUNDCARD

#include <ZappTypes.h>
#include <Buffer.h>
#include <Timer.h>
#include <Exception.h>
#include <Windows.h>

#include "../../Ohm.h"
#include "../../OhmSender.h"

#ifdef __cplusplus
extern "C" {
#endif

DllExport THandle SoundcardCreate(const char* aName, uint32_t aChannel, uint32_t aInterface, uint32_t aTtl, uint32_t aMulticast, uint32_t aEnabled, uint32_t aPreset);
DllExport void SoundcardSetName(THandle aSoundcard, const char* aValue);
DllExport void SoundcardSetChannel(THandle aSoundcard, uint32_t aValue);
DllExport void SoundcardSetInterface(THandle aSoundcard, uint32_t aValue);
DllExport void SoundcardSetTtl(THandle aSoundcard, uint32_t aValue);
DllExport void SoundcardSetMulticast(THandle aSoundcard, uint32_t aValue);
DllExport void SoundcardSetEnabled(THandle aSoundcard, uint32_t aValue);
DllExport void SoundcardSetTrack(THandle aSoundcard, const char* aUri, const char* aMetadata, uint64_t aSamplesTotal, uint64_t aSampleStart);
DllExport void SoundcardSetMetatext(THandle aSoundcard, const char* aValue);
DllExport void SoundcardDestroy(THandle aSoundcard);

#ifdef __cplusplus
} // extern "C"
#endif

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
	DllExport static Soundcard* Create(const TChar* aName, TUint aChannel, TIpAddress aInterface, TUint aTtl, TBool aMulticast, TBool aEnabled, TUint aPreset);
	DllExport void SetName(const TChar* aValue);
	DllExport void SetChannel(TUint aValue);
    DllExport void SetInterface(TIpAddress aValue);
    DllExport void SetTtl(TUint aValue);
    DllExport void SetMulticast(TBool aValue);
	DllExport void SetEnabled(TBool aValue);
    DllExport void SetTrack(const TChar* aUri, const TChar* aMetadata, TUint64 aSamplesTotal, TUint64 aSampleStart);
	DllExport void SetMetatext(const TChar* aValue);
	DllExport void SetPreset(TUint aValue);
	DllExport ~Soundcard();

private:
	Soundcard(const TChar* aName, TUint aChannel, TIpAddress aInterface, TUint aTtl, TBool aMulticast, TBool aEnabled, TUint aPreset);

private:
	OhmSender* iSender;
	OhmSenderDriverWindows* iDriver;
	DvDeviceStandard* iDevice;
};

} // namespace Zapp

#endif // HEADER_SOUNDCARD

