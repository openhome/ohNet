#ifndef HEADER_DviDeviceC
#define HEADER_DviDeviceC

#include <Core/DvDevice.h>

namespace OpenHome {
namespace Net {

class DviDeviceC : protected IResourceManager
{
public:
	DviDeviceC(const char* aUdn);
	~DviDeviceC();
	DllExport DvDevice* Device();
	static inline DvDevice* DeviceFromHandle(DvDeviceC aHandle);
protected:
    DviDeviceC();
private:
    void WriteResource(const Brx& aUriTail, TIpAddress aInterface, std::vector<char*>& aLanguageList, IResourceWriter& aResourceWriter);
    static void STDCALL WriteResourceBegin(void* aPtr, uint32_t aTotalBytes, const char* aMimeType);
    static void STDCALL WriteResource(void* aPtr, const uint8_t* aData, uint32_t aBytes);
    static void STDCALL WriteResourceEnd(void* aPtr);
protected:
    DvDevice* iDevice;
	OhNetCallbackResourceManager iResourceManager;
	void* iCallbackArg;
	IResourceWriter* iResourceWriter;
};

class DviDeviceStandardC : public DviDeviceC
{
public:
	DviDeviceStandardC(const char* aUdn);
	DviDeviceStandardC(const char* aUdn, OhNetCallbackResourceManager aResourceManager, void* aPtr);
};

inline DvDevice* DviDeviceC::DeviceFromHandle(DvDeviceC aHandle)
{
	return reinterpret_cast<DviDeviceC*>(aHandle)->Device();
}

} // namespace Net
} // namespace OpenHome

#endif // HEADER_DviDeviceC
