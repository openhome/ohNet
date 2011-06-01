#ifndef HEADER_RECEIVER_MANAGER3
#define HEADER_RECEIVER_MANAGER3

#include <OhNetTypes.h>
#include <Buffer.h>
#include <Timer.h>
#include <Exception.h>
#include <Functor.h>

#include "ReceiverManager2.h"

namespace OpenHome {
namespace Net {

class ReceiverManager3Receiver;

class IReceiverManager3Handler
{
public:
	virtual void ReceiverAdded(ReceiverManager3Receiver& aReceiver) = 0;
	virtual void ReceiverChanged(ReceiverManager3Receiver& aReceiver) = 0;
	virtual void ReceiverRemoved(ReceiverManager3Receiver& aReceiver) = 0;
	~IReceiverManager3Handler() {}
};

class ReceiverManager3;

class ReceiverManager3Receiver  : private INonCopyable
{
	friend class ReceiverManager3;

public:
	enum EStatus {
		eDisconnected,
		eConnecting,
		eConnected
	};

public:
	const Brx& Room() const;
	const Brx& Group() const;
	const Brx& Name() const;
	EStatus Status() const;

	void Play();
	void Stop();

	void AddRef();
    void RemoveRef();
    void SetUserData(void* aValue);
	void* UserData() const;

private:
	ReceiverManager3Receiver(IReceiverManager3Handler& aHandler, ReceiverManager2Receiver& aReceiver, ReceiverManager3& aManager);

	void Changed();
	void Removed();

	EStatus EvaluateStatus();

	~ReceiverManager3Receiver();

private:
	IReceiverManager3Handler& iHandler;
	ReceiverManager2Receiver& iReceiver;
	ReceiverManager3& iManager;
	EStatus iStatus;
    TUint iRefCount;
	void* iUserData;
};

class ReceiverManager3 : public IReceiverManager2Handler
{
public:
	static const TUint kMaxTransportStateBytes = 20;
	static const TUint kMaxUriBytes = 100;

public:
	ReceiverManager3(IReceiverManager3Handler& aHandler, const Brx& aUri);
	void SetUri(const Brx& aUri);
    void Refresh();
	ReceiverManager3Receiver::EStatus Status(ReceiverManager2Receiver& aReceiver);
    ~ReceiverManager3();

private:
	// IReceiverManager2Handler
	virtual void ReceiverAdded(ReceiverManager2Receiver& aReceiver);
	virtual void ReceiverChanged(ReceiverManager2Receiver& aReceiver);
	virtual void ReceiverRemoved(ReceiverManager2Receiver& aReceiver);

private:
	IReceiverManager3Handler& iHandler;
	Bws<kMaxUriBytes> iUri;
	ReceiverManager2* iReceiverManager;
};


/*
	enum EStatus {
		eOff,
		eOn,
		eListening
	};

	EStatus Status() const;
	TUint ReceiverCount() const;
	const Brx& ReceiverRoom(TUint aIndex) const;
	const Brx& ReceiverGroup(TUint aIndex) const;
	void Select(Brx& aReceiverRoom, Brx& aReceiverGroup);
*/

} // namespace Net
} // namespace OpenHome

#endif // HEADER_RECEIVER_MANAGER3

