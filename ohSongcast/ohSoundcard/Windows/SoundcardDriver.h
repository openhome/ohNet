#ifndef HEADER_SOUNDCARDDRIVER
#define HEADER_SOUNDCARDDRIVER

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Net/Core/OhNet.h>
#include <Windows.h>

#include "../../Ohm.h"
#include "../../OhmSender.h"

namespace OpenHome {
namespace Net {

class OhmSenderDriverWindows : public IOhmSenderDriver
{
public:
	OhmSenderDriverWindows();

private:    
	TBool FindDriver();
	TBool InstallDriver();

	// IOhmSenderDriver
	virtual void SetEnabled(TBool aValue);
	virtual void SetEndpoint(const Endpoint& aEndpoint);
	virtual void SetActive(TBool aValue);
	virtual void SetTtl(TUint aValue);
	virtual void SetTrackPosition(TUint64 aSampleStart, TUint64 aSamplesTotal);

private:
	HANDLE iHandle;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_SOUNDCARDDRIVER

