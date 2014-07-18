#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/OptionParser.h>
#include <OpenHome/Types.h>
#include <OpenHome/Net/Private/Discovery.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Timer.h>
#include <OpenHome/OsWrapper.h>
#include <CpDeviceUpnp.h>
#include <OpenHome/Net/Core/FunctorCpDevice.h>
#include <Cpp/Core/CpUpnpOrgSwitchPower1.h>
#include <Cpp/Core/CpUpnpOrgDimming1.h>

#include <vector>

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::TestFramework;

class DimmableLight
{
public:
    DimmableLight(CpDevice& aDimmableLightDevice);
    ~DimmableLight();
    TBool GetTarget();
    TUint GetLoadLevelTarget();
private:
    CpProxyUpnpOrgSwitchPower1  iSwitchPower;
    CpProxyUpnpOrgDimming1      iDimming;
};

DimmableLight::DimmableLight(CpDevice& aDimmableLightDevice)
 :  iSwitchPower(aDimmableLightDevice),
    iDimming(aDimmableLightDevice)
{
}

TBool DimmableLight::GetTarget()
{
    TBool status;
    iSwitchPower.SyncGetTarget(status);
    return status;
}

TUint DimmableLight::GetLoadLevelTarget()
{
    TUint status;
    iDimming.SyncGetLoadLevelTarget(status);
    return status;
}

class DimmableLightList
{
public:
    DimmableLightList();
    ~DimmableLightList();
    void Show();

private:
    void Added(CpDevice& aDevice);
    void Removed(CpDevice& aDevice);
    
    CpDeviceList* iDeviceList;
    Mutex iMutex;
    typedef std::map<CpDevice*, DimmableLight*> DimmableMap;
    DimmableMap iMap;
    typedef std::pair<CpDevice*, DimmableLight*> DimmableEntry;
};

DimmableLightList::DimmableLightList()
 :  iMutex("dmll")
{
    FunctorCpDevice added   = MakeFunctorCpDevice(*this, &DimmableLightList::Added);
    FunctorCpDevice removed = MakeFunctorCpDevice(*this, &DimmableLightList::Removed);

    Brn domainName;
    Brn type;
    TUint ver;

    OpenHome::Net::Ssdp::ParseUrnDevice(Brn("upnp.org:device:DimmableLight:1"), domainName, type, ver);
    iDeviceList = new CpDeviceListUpnpDeviceType(domainName, type, ver, added, removed);
}

DimmableLightList::~DimmableLightList()
{
    // TODO : delete the map!
    delete iDeviceList;
}

void DimmableLightList::Added(CpDevice& aDevice)
{
    AutoMutex amtx(iMutex);
    
    DimmableLight* d = new DimmableLight(aDevice);
    
    iMap.insert(DimmableEntry(&aDevice, d));
}

void DimmableLightList::Removed(CpDevice& aDevice)
{
    AutoMutex amtx(iMutex);
    Print("removed!\n");
}

void DimmableLightList::Show()
{
    AutoMutex amtx(iMutex);
    for ( DimmableMap::iterator i = iMap.begin() ; i != iMap.end() ; i++ )
    {
        CpDevice* d = i->first;
        DimmableLight* l = i->second;
        Print(d->Udn());
        Print(" %s", (l->GetTarget() ? "on" : "off"));
        //Print(" %d%%", l->GetLoadLevelTarget());
        Print("\n");
    }
}

void OpenHome::TestFramework::Runner::Main(TInt aArgc, TChar* aArgv[], InitialisationParams* aInitParams)
{
    UpnpLibrary::Initialise(aInitParams);
    std::vector<NetworkAdapter*>* subnetList = UpnpLibrary::CreateSubnetList();
    TIpAddress subnet = (*subnetList)[0]->Subnet();
    UpnpLibrary::DestroySubnetList(subnetList);
    UpnpLibrary::StartCp(subnet);

    DimmableLightList* l = new DimmableLightList();

    if (l != NULL) {
        Blocker* blocker = new Blocker;
        blocker->Wait(aInitParams->MsearchTimeSecs());
        delete blocker;
    }

    l->Show();

    delete l;

    UpnpLibrary::Close();
}
