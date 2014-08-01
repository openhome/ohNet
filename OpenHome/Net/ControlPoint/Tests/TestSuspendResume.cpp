#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/OptionParser.h>
#include <OpenHome/Types.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/OsWrapper.h>
#include <OpenHome/Net/Core/CpDeviceUpnp.h>
#include <OpenHome/Net/Core/FunctorCpDevice.h>
#include <OpenHome/Net/Core/CpAvOpenhomeOrgProduct1.h>
#include <OpenHome/Net/Core/CpAvOpenhomeOrgSender1.h>

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::TestFramework;

class DeviceListLogger
{
protected:
    DeviceListLogger(const TChar* aType);
    ~DeviceListLogger();
    void PrintDeviceInfo(const char* aPrologue, const CpDevice& aDevice);
    void Add(CpDevice& aDevice, CpProxy* aProxy);
    void Remove(CpDevice& aDevice);
private:
    void Empty();
private:
    class Proxy
    {
    public:
        Proxy(CpDevice& aDevice, CpProxy* aProxy)
            : iDevice(&aDevice)
            , iProxy(aProxy)
        {}
    public:
        CpDevice* iDevice;
        CpProxy* iProxy;
    };
private:
    Mutex iLock;
    const TChar* iType;
    std::vector<Proxy> iProxies;
};

class DeviceListProduct : public DeviceListLogger
{
public:
    DeviceListProduct(const TChar* aType);
    void Added(CpDevice& aDevice);
    void Removed(CpDevice& aDevice);
};

class DeviceListSender : public DeviceListLogger
{
public:
    DeviceListSender(const TChar* aType);
    void Added(CpDevice& aDevice);
    void Removed(CpDevice& aDevice);
};


DeviceListLogger::DeviceListLogger(const TChar* aType)
    : iLock("DLLM")
    , iType(aType)
{
}

DeviceListLogger::~DeviceListLogger()
{
    for (std::vector<Proxy>::iterator it = iProxies.begin(); it != iProxies.end(); ++it) {
        delete (*it).iProxy;
    }
}

void DeviceListLogger::PrintDeviceInfo(const char* aPrologue, const CpDevice& aDevice)
{
    iLock.Wait();
    Print("%s %s: ", aPrologue, iType);
    Brh val;
    aDevice.GetAttribute("Upnp.FriendlyName", val);
    Print(val);
    Print(", ");
    aDevice.GetAttribute("Upnp.Location", val);
    Print(val);
    Print("\n");
    iLock.Signal();
}

void DeviceListLogger::Add(CpDevice& aDevice, CpProxy* aProxy)
{
    PrintDeviceInfo("+", aDevice);
    Functor functor = MakeFunctor(*this, &DeviceListLogger::Empty);
    aProxy->SetPropertyInitialEvent(functor);
    aProxy->Subscribe();
    Proxy proxy(aDevice, aProxy);
    iProxies.push_back(proxy);
}

void DeviceListLogger::Remove(CpDevice& aDevice)
{
    const Brx& udn = aDevice.Udn();
    for (std::vector<Proxy>::iterator it = iProxies.begin(); it != iProxies.end(); ++it) {
        if ((*it).iDevice->Udn() == udn) {
            PrintDeviceInfo("-", aDevice);
            delete (*it).iProxy;
            iProxies.erase(it);
            break;
        }
    }
}

void DeviceListLogger::Empty()
{
}


DeviceListProduct::DeviceListProduct(const TChar* aType)
    : DeviceListLogger(aType)
{
}

void DeviceListProduct::Added(CpDevice& aDevice)
{
    Add(aDevice, new CpProxyAvOpenhomeOrgProduct1(aDevice));
}

void DeviceListProduct::Removed(CpDevice& aDevice)
{
    Remove(aDevice);
}


DeviceListSender::DeviceListSender(const TChar* aType)
    : DeviceListLogger(aType)
{
}

void DeviceListSender::Added(CpDevice& aDevice)
{
    Add(aDevice, new CpProxyAvOpenhomeOrgSender1(aDevice));
}

void DeviceListSender::Removed(CpDevice& aDevice)
{
    Remove(aDevice);
}


void OpenHome::TestFramework::Runner::Main(TInt aArgc, TChar* aArgv[], Net::InitialisationParams* aInitParams)
{
    OptionParser parser;
    OptionUint adapter("-a", "--adapter", 0, "Index of network adapter to use");
    parser.AddOption(&adapter);
    std::vector<Brn> args = OptionParser::ConvertArgs(aArgc, aArgv);
    if (!parser.Parse(args, true) || parser.HelpDisplayed()) {
        return;
    }

    Library* lib = new Library(aInitParams);
    Debug::SetLevel(Debug::kTrace | Debug::kEvent);
    std::vector<NetworkAdapter*>* subnetList = lib->CreateSubnetList();
    TIpAddress subnet = (*subnetList)[adapter.Value()]->Subnet();
    Library::DestroySubnetList(subnetList);
    CpStack* cpStack = lib->StartCp(subnet);

    std::vector<CpDeviceList*> deviceLists;
    DeviceListProduct* productList = new DeviceListProduct("Product");
    DeviceListSender* senderList = new DeviceListSender("Sender");

    FunctorCpDevice added = MakeFunctorCpDevice(*productList, &DeviceListProduct::Added);
    FunctorCpDevice removed = MakeFunctorCpDevice(*productList, &DeviceListProduct::Removed);
    deviceLists.push_back(new CpDeviceListUpnpServiceType(*cpStack, Brn("av.openhome.org"), Brn("Product"), 1, added, removed));

    added = MakeFunctorCpDevice(*senderList, &DeviceListSender::Added);
    removed = MakeFunctorCpDevice(*senderList, &DeviceListSender::Removed);
    deviceLists.push_back(new CpDeviceListUpnpServiceType(*cpStack, Brn("av.openhome.org"), Brn("Sender"), 1, added, removed));

    TBool quit = false;
    do {
        int ch = getchar();
        switch (ch)
        {
        case 'q':
            quit = true;
            break;
        case 'r':
            lib->NotifyResumed();
            break;
        case 's':
            lib->NotifySuspended();
            break;
        default:
            break;
        }
    } while (!quit);

    for (auto it=deviceLists.begin(); it!=deviceLists.end(); ++it) {
        delete *it;
    }
    delete productList;
    delete senderList;
    delete lib;
}
