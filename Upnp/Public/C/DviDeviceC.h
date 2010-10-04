#ifndef HEADER_DviDeviceC
#define HEADER_DviDeviceC

#include <Core/DvDevice.h>

namespace Zapp {

class DviDeviceC : private IResourceManager
{
public:
	DviDeviceC(const char* aUdn);
	DviDeviceC(const char* aUdn, ZappCallbackResourceManager aResourceManager, void* aPtr);
	~DviDeviceC();
	DllExport DvDevice* Device();
	static inline DvDevice* DeviceFromHandle(DvDeviceC aHandle);
private:
    void WriteResource(const Brx& aUriTail, TIpAddress aInterface, IResourceWriter& aResourceWriter);
    static void WriteResourceBegin(void* aPtr, uint32_t aTotalBytes, const char* aMimeType);
    static void WriteResource(void* aPtr, const uint8_t* aData, uint32_t aBytes);
    static void WriteResourceEnd(void* aPtr);
private:
	DvDevice* iDevice;
	ZappCallbackResourceManager iResourceManager;
	void* iCallbackArg;
	IResourceWriter* iResourceWriter;
};

inline DvDevice* DviDeviceC::DeviceFromHandle(DvDeviceC aHandle)
{
	return reinterpret_cast<DviDeviceC*>(aHandle)->Device();
}

} // namespace Zapp

#endif // HEADER_DviDeviceC
