#ifndef HEADER_SOUNDCARD
#define HEADER_SOUNDCARD

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Net/Core/OhNet.h>

#include "../Ohm.h"
#include "../OhmSender.h"
#include "ReceiverManager3.h"

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
typedef void (STDCALL *ReceiverCallback)(void* aPtr, ECallbackType aType, THandle aReceiver);
typedef void (STDCALL *SubnetCallback)(void* aPtr, ECallbackType aType, THandle aSubnet);

DllExport THandle STDCALL SoundcardCreate(uint32_t aSubnet, uint32_t aChannel, uint32_t aTtl, uint32_t aMulticast, uint32_t aEnabled, uint32_t aPreset, ReceiverCallback aReceiverCallback, void* aReceiverPtr, SubnetCallback aSubnetCallback, void* aSubnetPtr);
DllExport void STDCALL SoundcardSetSubnet(THandle aSoundcard, uint32_t aValue);
DllExport void STDCALL SoundcardSetChannel(THandle aSoundcard, uint32_t aValue);
DllExport void STDCALL SoundcardSetTtl(THandle aSoundcard, uint32_t aValue);
DllExport void STDCALL SoundcardSetMulticast(THandle aSoundcard, uint32_t aValue);
DllExport void STDCALL SoundcardSetEnabled(THandle aSoundcard, uint32_t aValue);
DllExport void STDCALL SoundcardSetPreset(THandle aSoundcard, uint32_t aValue);
DllExport void STDCALL SoundcardSetTrack(THandle aSoundcard, const char* aUri, const char* aMetadata, uint64_t aSamplesTotal, uint64_t aSampleStart);
DllExport void STDCALL SoundcardSetMetatext(THandle aSoundcard, const char* aValue);
DllExport void STDCALL SoundcardRefreshReceivers(THandle aSoundcard);
DllExport void STDCALL SoundcardDestroy(THandle aSoundcard);

DllExport const char* STDCALL ReceiverUdn(THandle aReceiver);
DllExport const char* STDCALL ReceiverRoom(THandle aReceiver);
DllExport const char* STDCALL ReceiverGroup(THandle aReceiver);
DllExport const char* STDCALL ReceiverName(THandle aReceiver);
DllExport EReceiverStatus STDCALL ReceiverStatus(THandle aReceiver);
DllExport void STDCALL ReceiverPlay(THandle aReceiver);
DllExport void STDCALL ReceiverStop(THandle aReceiver);
DllExport void STDCALL ReceiverStandby(THandle aReceiver);
DllExport void STDCALL ReceiverAddRef(THandle aReceiver);
DllExport void STDCALL ReceiverRemoveRef(THandle aReceiver);

DllExport uint32_t STDCALL SubnetAddress(THandle aSubnet);
DllExport const char* STDCALL SubnetAdapterName(THandle aSubnet);
DllExport void STDCALL SubnetAddRef(THandle aReceiver);
DllExport void STDCALL SubnetRemoveRef(THandle aReceiver);

#ifdef __cplusplus
} // extern "C"
#endif

////////////////////////////////////////////

namespace OpenHome {
namespace Net {

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
	Subnet(NetworkAdapter& aAdapter);
	Subnet(TIpAddress aSubnet);
	void Attach(NetworkAdapter& aAdapter);
	TBool IsAttachedTo(NetworkAdapter& aAdapter);
	~Subnet();

private:
	NetworkAdapter* iAdapter;
	TIpAddress iSubnet;
};

class DllExportClass Soundcard : public IReceiverManager3Handler
{
	static const TUint kMaxUdnBytes = 100;

public:
    // This static function is the only part of this class that is required to be implemented
    // in platform specific code
	static Soundcard* Create(TIpAddress aSubnet, TUint aChannel, TUint aTtl, TBool aMulticast, TBool aEnabled, TUint aPreset, ReceiverCallback aReceiverCallback, void* aReceiverPtr, SubnetCallback aSubnetCallback, void* aSubnetPtr);

public:
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
	Soundcard(TIpAddress aSubnet, TUint aChannel, TUint aTtl, TBool aMulticast, TBool aEnabled, TUint aPreset, ReceiverCallback aReceiverCallback, void* aReceiverPtr, SubnetCallback aSubnetCallback, void* aSubnetPtr, const Brx& aComputer, IOhmSenderDriver* aDriver);

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
	IOhmSenderDriver* iDriver;
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

