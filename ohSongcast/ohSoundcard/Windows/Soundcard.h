#ifndef HEADER_SOUNDCARD
#define HEADER_SOUNDCARD

#include <OhNetTypes.h>
#include <OhNet.h>
#include <Windows.h>

#include "../../Ohm.h"
#include "../../OhmSender.h"
#include "../ReceiverManager3.h"

////////////////////////////////////////////
// Exported C interface

#ifdef __cplusplus
extern "C" {
#endif

enum ECallbackType {
	eAdded,
	eChanged,
	eRemoved
};

enum EReceiverStatus {
	eDisconnected,
	eConnecting,
	eConnected
};

/**
 * Callback which runs to notify a change in the networked receivers
 * @ingroup Callbacks
 *
 * @param[in] aPtr      Client-specified data
 * @param[in] aType     Type of change indicated
 * @param[in] aReceiver Receiver handle
 */
typedef void (*ReceiverCallback)(void* aPtr, ECallbackType aType, THandle aReceiver);
typedef void (*SubnetCallback)(void* aPtr, ECallbackType aType, THandle aSubnet);

DllExport THandle SoundcardCreate(uint32_t aSubnet, uint32_t aChannel, uint32_t aTtl, uint32_t aMulticast, uint32_t aEnabled, uint32_t aPreset, ReceiverCallback aReceiverCallback, void* aReceiverPtr, SubnetCallback aSubnetCallback, void* aSubnetPtr);
DllExport void SoundcardSetSubnet(THandle aSoundcard, uint32_t aValue);
DllExport void SoundcardSetChannel(THandle aSoundcard, uint32_t aValue);
DllExport void SoundcardSetTtl(THandle aSoundcard, uint32_t aValue);
DllExport void SoundcardSetMulticast(THandle aSoundcard, uint32_t aValue);
DllExport void SoundcardSetEnabled(THandle aSoundcard, uint32_t aValue);
DllExport void SoundcardSetPreset(THandle aSoundcard, uint32_t aValue);
DllExport void SoundcardSetTrack(THandle aSoundcard, const char* aUri, const char* aMetadata, uint64_t aSamplesTotal, uint64_t aSampleStart);
DllExport void SoundcardSetMetatext(THandle aSoundcard, const char* aValue);
DllExport void SoundcardRefreshReceivers(THandle aSoundcard);
DllExport void SoundcardDestroy(THandle aSoundcard);

DllExport const char* ReceiverUdn(THandle aReceiver);
DllExport const char* ReceiverRoom(THandle aReceiver);
DllExport const char* ReceiverGroup(THandle aReceiver);
DllExport const char* ReceiverName(THandle aReceiver);
DllExport EReceiverStatus ReceiverStatus(THandle aReceiver);
DllExport void ReceiverPlay(THandle aReceiver);
DllExport void ReceiverStop(THandle aReceiver);
DllExport void ReceiverStandby(THandle aReceiver);
DllExport void ReceiverAddRef(THandle aReceiver);
DllExport void ReceiverRemoveRef(THandle aReceiver);

DllExport uint32_t SubnetAddress(THandle aSubnet);
DllExport const char* SubnetAdapterName(THandle aSubnet);
DllExport void SubnetAddRef(THandle aReceiver);
DllExport void SubnetRemoveRef(THandle aReceiver);

#ifdef __cplusplus
} // extern "C"
#endif

////////////////////////////////////////////

namespace OpenHome {
namespace Net {

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

class Soundcard;

class Receiver
{
	friend class Soundcard;

public:
	const TChar* Udn() const;
	const TChar* Room() const;
	const TChar* Group() const;
	const TChar* Name() const;
	EReceiverStatus Status() const;

	void Play();
	void Stop();
	void Standby();

	void AddRef();
    void RemoveRef();
    
private:
	Receiver(ReceiverManager3Receiver& aReceiver);
	~Receiver();

private:
	ReceiverManager3Receiver& iReceiver;
	Brhz iUdn;
	Brhz iRoom;
	Brhz iGroup;
	Brhz iName;
    TUint iRefCount;
};

class Subnet : public INonCopyable
{
	friend class Soundcard;

public:
	TIpAddress Address() const;
	const TChar* AdapterName() const;
	TIpAddress AdapterAddress() const;

	void AddRef();
    void RemoveRef();
    
private:
	Subnet(NetworkInterface& aAdapter);
	Subnet(TIpAddress aSubnet);
	void Attach(NetworkInterface& aAdapter);
	TBool IsAttachedTo(NetworkInterface& aAdapter);
	~Subnet();

private:
	NetworkInterface* iAdapter;
	TIpAddress iSubnet;
};

class DllExportClass Soundcard : public IReceiverManager3Handler
{
	static const TUint kMaxUdnBytes = 100;

public:
	static Soundcard* Create(TIpAddress aSubnet, TUint aChannel, TUint aTtl, TBool aMulticast, TBool aEnabled, TUint aPreset, ReceiverCallback aReceiverCallback, void* aReceiverPtr, SubnetCallback aSubnetCallback, void* aSubnetPtr);
    void SetSubnet(TIpAddress aValue);
	void SetChannel(TUint aValue);
    void SetTtl(TUint aValue);
    void SetMulticast(TBool aValue);
	void SetEnabled(TBool aValue);
	void SetPreset(TUint aValue);
    void SetTrack(const TChar* aUri, const TChar* aMetadata, TUint64 aSamplesTotal, TUint64 aSampleStart);
	void SetMetatext(const TChar* aValue);
	void RefreshReceivers();
	~Soundcard();

private:
	Soundcard(TIpAddress aSubnet, TUint aChannel, TUint aTtl, TBool aMulticast, TBool aEnabled, TUint aPreset, ReceiverCallback aReceiverCallback, void* aReceiverPtr, SubnetCallback aSubnetCallback, void* aSubnetPtr);

	void SubnetListChanged();
	TBool UpdateAdapter();

	// IReceiverManager3Handler
	virtual void ReceiverAdded(ReceiverManager3Receiver& aReceiver);
	virtual void ReceiverChanged(ReceiverManager3Receiver& aReceiver);
	virtual void ReceiverRemoved(ReceiverManager3Receiver& aReceiver);

private:
	Mutex iMutex;
	TBool iClosing;
	TIpAddress iSubnet;
	TIpAddress iAdapter;
	std::vector<Subnet*> iSubnetList;
	OhmSender* iSender;
	OhmSenderDriverWindows* iDriver;
	DvDeviceStandard* iDevice;
	ReceiverManager3* iReceiverManager;
	ReceiverCallback iReceiverCallback;
	void* iReceiverPtr;
	SubnetCallback iSubnetCallback;
	void* iSubnetPtr;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_SOUNDCARD

