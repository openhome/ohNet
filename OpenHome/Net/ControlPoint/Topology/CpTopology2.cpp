#include "CpTopology2.h"

#include <OpenHome/Private/Debug.h>
#include <OpenHome/Private/Parser.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Net/Private/XmlParser.h>

using namespace OpenHome;
using namespace OpenHome::Net;

// CpTopology2Source

CpTopology2Source::CpTopology2Source(const Brx& aName, const Brx& aType, TBool aVisible)
    : iName(aName)
    , iType(aType)
    , iVisible(aVisible)
{
}

const Brx& CpTopology2Source::Name() const
{
    return (iName);
}

const Brx& CpTopology2Source::Type() const
{
    return (iType);
}

TBool CpTopology2Source::Visible() const
{
    return (iVisible);
}
    
void CpTopology2Source::Update(const Brx& aName, const Brx& aType, TBool aVisible)
{
    iName.Replace(aName);
    iType.Replace(aType);
    iVisible = aVisible;
}

// CpTopology2Group

CpTopology2Group::CpTopology2Group(CpDevice& aDevice, ICpTopology2GroupHandler& aHandler, TBool aStandby, const Brx& aRoom, const Brx& aName, TUint aSourceIndex, TBool aHasVolumeControl)
    : iDevice(aDevice)
    , iHandler(aHandler)
    , iStandby(aStandby)
    , iRoom(aRoom)
    , iName(aName)
    , iSourceIndex(aSourceIndex)
    , iHasVolumeControl(aHasVolumeControl)
    , iUserData(0)
    , iRefCount(1)
{
    if (&iDevice != 0) {  // device with zero address used by test code
        iDevice.AddRef();
    }
}

CpTopology2Group::~CpTopology2Group()
{
    if (&iDevice != 0) { // device with zero address used by test code
        iDevice.RemoveRef();
    }

    for (size_t i=0; i<iSourceList.size(); i++) {
        delete iSourceList[i];
    }
    iSourceList.clear();
}

void CpTopology2Group::AddSource(const Brx& aName, const Brx& aType, TBool aVisible)
{
    iSourceList.push_back(new CpTopology2Source(aName, aType, aVisible));
}

void CpTopology2Group::UpdateRoom(const Brx& aValue)
{
    iRoom.Replace(aValue);
}

void CpTopology2Group::UpdateName(const Brx& aValue)
{
    iName.Replace(aValue);
}

void CpTopology2Group::UpdateSourceIndex(TUint aValue)
{
    iSourceIndex = aValue;
}

void CpTopology2Group::UpdateStandby(TBool aValue)
{
    iStandby = aValue;
}

void CpTopology2Group::UpdateSource(TUint aIndex, const Brx& aName, const Brx& aType, TBool aVisible)
{
    iSourceList[aIndex]->Update(aName, aType, aVisible);
}

void CpTopology2Group::AddRef()
{
    iRefCount++;
}

void CpTopology2Group::RemoveRef()
{
    if (--iRefCount == 0) {
        delete this;
    }
}

CpDevice& CpTopology2Group::Device() const
{
    return (iDevice);
}

TUint CpTopology2Group::SourceCount() const
{
    return ((TUint)iSourceList.size());
}

TUint CpTopology2Group::SourceIndex() const
{
    return (iSourceIndex);
}

TBool CpTopology2Group::Standby() const
{
    return (iStandby);
}

void CpTopology2Group::SetSourceIndex(TUint aIndex)
{
    ASSERT(aIndex < iSourceList.size());
    iHandler.SetSourceIndex(aIndex);
}

void CpTopology2Group::SetStandby(TBool aValue)
{
    iHandler.SetStandby(aValue);
}

const Brx& CpTopology2Group::Room() const
{
    return (iRoom);
}

const Brx& CpTopology2Group::Name() const
{
    return (iName);
}

const Brx& CpTopology2Group::SourceName(TUint aIndex) const
{
    return (iSourceList[aIndex]->Name());
}

const Brx& CpTopology2Group::SourceType(TUint aIndex) const
{
    return (iSourceList[aIndex]->Type());
}

TBool CpTopology2Group::SourceVisible(TUint aIndex) const
{
    return (iSourceList[aIndex]->Visible());
}

TBool CpTopology2Group::HasVolumeControl() const
{
    return (iHasVolumeControl);
}

void CpTopology2Group::SetUserData(void* aValue)
{
    iUserData = aValue;
}

void* CpTopology2Group::UserData() const
{
    return (iUserData);
}

// CpTopology2Device

CpTopology2Device::CpTopology2Device(CpDevice& aDevice)
    : iDevice(aDevice)
{
    iDevice.AddRef();
}
    
TBool CpTopology2Device::IsAttachedTo(CpDevice& aDevice)
{
    return (iDevice.Udn() == aDevice.Udn());
}

CpTopology2Device::~CpTopology2Device()
{
    iDevice.RemoveRef();
}
    
// CpTopology2Product

CpTopology2Product::CpTopology2Product(CpDevice& aDevice, ICpTopology2Handler& aHandler)
    : CpTopology2Device(aDevice)
    , iHandler(aHandler)
    , iServiceProduct(0)
    , iGroup(0)
{
    iFunctorSetSourceIndex = MakeFunctorAsync(*this, &CpTopology2Product::CallbackSetSourceIndex);
    iFunctorSetStandby = MakeFunctorAsync(*this, &CpTopology2Product::CallbackSetStandby);

    iServiceProduct = new CpProxyAvOpenhomeOrgProduct1(iDevice);

    Functor functorInitial = MakeFunctor(*this, &CpTopology2Product::EventProductInitialEvent);

    iServiceProduct->SetPropertyInitialEvent(functorInitial);

    iServiceProduct->Subscribe();
}

CpTopology2Product::~CpTopology2Product()
{
    LOG(kTopology, "CpTopology2Product::~CpTopology2Product\n");

    delete (iServiceProduct);
    
    if (iGroup != 0) {
        iHandler.GroupRemoved(*iGroup);
        iGroup->RemoveRef();
    }
}

void CpTopology2Product::EventProductInitialEvent()
{
    Functor functorRoom = MakeFunctor(*this, &CpTopology2Product::EventProductRoomChanged);
    Functor functorName = MakeFunctor(*this, &CpTopology2Product::EventProductNameChanged);
    Functor functorStandby = MakeFunctor(*this, &CpTopology2Product::EventProductStandbyChanged);
    Functor functorSourceIndex = MakeFunctor(*this, &CpTopology2Product::EventProductSourceIndexChanged);
    Functor functorSourceXml = MakeFunctor(*this, &CpTopology2Product::EventProductSourceXmlChanged);

    iServiceProduct->SetPropertyProductRoomChanged(functorRoom);    
    iServiceProduct->SetPropertyProductNameChanged(functorName);    
    iServiceProduct->SetPropertyStandbyChanged(functorStandby); 
    iServiceProduct->SetPropertySourceIndexChanged(functorSourceIndex); 
    iServiceProduct->SetPropertySourceXmlChanged(functorSourceXml);
      
    TBool hasVolumeControl = false;

    Brhz attributes;

    iServiceProduct->PropertyAttributes(attributes);

    Parser parser(attributes);
    
    for (;;) {
        Brn attribute = parser.Next();
        
        if (attribute.Bytes() == 0) {
            break;
        }
        
        if (attribute == Brn("Volume")) {
            hasVolumeControl = true;
            break;
        }
    }
    
    Brhz room;
    Brhz name;
    TUint sourceIndex;
    TBool standby;
    Brhz xml;
    
    iServiceProduct->PropertyProductRoom(room);
    iServiceProduct->PropertyProductName(name);
    iServiceProduct->PropertySourceIndex(sourceIndex);
    iServiceProduct->PropertyStandby(standby);
    iServiceProduct->PropertySourceXml(xml);
    
    iGroup = new CpTopology2Group(iDevice, *this, standby, room, name, sourceIndex, hasVolumeControl);
    
    ProcessSourceXml(xml, true);
    
    iHandler.GroupAdded(*iGroup);
}

/*  Example source xml

    <SourceList>
        <Source>
            <Name>Playlist</Name>
            <Type>Playlist</Type>
            <Visible>1</Visible>
        </Source>
        <Source>
            <Name>Radio</Name>
            <Type>Radio</Type>
            <Visible>1</Visible>
        </Source>
    </SourceList>
*/

void CpTopology2Product::ProcessSourceXml(const Brx& aXml, TBool aInitial)
{
    TUint count = 0;

    TBool updated = false;
    
    try {
        Brn sourceList = XmlParserBasic::Find("SourceList", aXml);

        for (;;) {
            Brn source = XmlParserBasic::Find("Source", sourceList, sourceList);
            Brn name = XmlParserBasic::Find("Name", source);
            Brn type = XmlParserBasic::Find("Type", source);
            Brn visible = XmlParserBasic::Find("Visible", source);
            
            TBool vis = false;
            
            if (visible == Brn("true")) {
                vis = true;
            }
            
            if (aInitial) {
                iGroup->AddSource(name, type, vis);
            }
            else {
                iGroup->UpdateSource(count, name, type, vis);
                updated = true;
            }

            count++;
        }
    }
    catch (XmlError) {
    }
    
    if (updated) {
        iHandler.GroupSourceListChanged(*iGroup);
    }
}

void CpTopology2Product::EventProductRoomChanged()
{
    LOG(kTopology, "CpTopology2::EventProductRoomChanged ");
    LOG(kTopology, iGroup->Room());
    LOG(kTopology, ":");
    LOG(kTopology, iGroup->Name());
    LOG(kTopology, "\n");

    Brhz room;
    iServiceProduct->PropertyProductRoom(room);
    
    iHandler.GroupRemoved(*iGroup);
    iGroup->UpdateRoom(room);
    iHandler.GroupAdded(*iGroup);
}
    
void CpTopology2Product::EventProductNameChanged()
{
    LOG(kTopology, "CpTopology2::EventProductNameChanged ");
    LOG(kTopology, iGroup->Room());
    LOG(kTopology, ":");
    LOG(kTopology, iGroup->Name());
    LOG(kTopology, "\n");

    Brhz name;
    iServiceProduct->PropertyProductName(name);
    
    iHandler.GroupRemoved(*iGroup);
    iGroup->UpdateName(name);
    iHandler.GroupAdded(*iGroup);
}

void CpTopology2Product::EventProductStandbyChanged()
{
    LOG(kTopology, "CpTopology2::EventProductStandbyChanged ");
    LOG(kTopology, iGroup->Room());
    LOG(kTopology, ":");
    LOG(kTopology, iGroup->Name());
    LOG(kTopology, "\n");

    TBool standby;
    iServiceProduct->PropertyStandby(standby);
    
    iGroup->UpdateStandby(standby);
    iHandler.GroupStandbyChanged(*iGroup);
}
    
void CpTopology2Product::EventProductSourceIndexChanged()
{
    LOG(kTopology, "CpTopology2::EventProductSourceIndexChanged ");
    LOG(kTopology, iGroup->Room());
    LOG(kTopology, ":");
    LOG(kTopology, iGroup->Name());
    LOG(kTopology, "\n");

    TUint sourceIndex;
    iServiceProduct->PropertySourceIndex(sourceIndex);
    
    iGroup->UpdateSourceIndex(sourceIndex);
    iHandler.GroupSourceIndexChanged(*iGroup);
}
    
void CpTopology2Product::EventProductSourceXmlChanged()
{
    LOG(kTopology, "CpTopology2::EventProductSourceXmlChanged ");
    LOG(kTopology, iGroup->Room());
    LOG(kTopology, ":");
    LOG(kTopology, iGroup->Name());
    LOG(kTopology, "\n");

    Brhz xml;
    
    iServiceProduct->PropertySourceXml(xml);

    ProcessSourceXml(xml, false);   
}   

void CpTopology2Product::SetSourceIndex(TUint aIndex)
{
    iServiceProduct->BeginSetSourceIndex(aIndex, iFunctorSetSourceIndex);
}

void CpTopology2Product::CallbackSetSourceIndex(IAsync& aAsync)
{
    iServiceProduct->EndSetSourceIndex(aAsync);
}
    
void CpTopology2Product::SetStandby(TBool aValue)
{
    iServiceProduct->BeginSetStandby(aValue, iFunctorSetStandby);
}

void CpTopology2Product::CallbackSetStandby(IAsync& aAsync)
{
    iServiceProduct->EndSetStandby(aAsync);
}

// CpTopology2Job

CpTopology2Job::CpTopology2Job(ICpTopology2Handler& aHandler)
{
    iHandler = &aHandler;
    iGroup = 0;
}
    
void CpTopology2Job::Set(CpTopology2Group& aGroup, ICpTopology2HandlerFunction aFunction)
{
    iGroup = &aGroup;
    iFunction = aFunction;
    iGroup->AddRef();
}

void CpTopology2Job::Execute()
{
    if (iGroup) {
        (iHandler->*iFunction)(*iGroup);
        iGroup->RemoveRef();
        iGroup = 0;
    }
    else {
        THROW(ThreadKill);
    }
}

// CpTopology2

CpTopology2::CpTopology2(ICpTopology2Handler& aHandler)
    : iFree(kMaxJobCount)
    , iReady(kMaxJobCount)
{
    for (TUint i = 0; i < kMaxJobCount; i++) {
        iFree.Write(new CpTopology2Job(aHandler));
    }
    
    iTopology1 = new CpTopology1(*this);
    
    iThread = new ThreadFunctor("TOP2", MakeFunctor(*this, &CpTopology2::Run));
    iThread->Start();
}

CpTopology2::~CpTopology2()
{
    LOG(kTopology, "CpTopology2::~CpTopology2\n");

    delete (iTopology1);
    
    LOG(kTopology, "CpTopology2::~CpTopology2 deleted layer 1\n");

    std::vector<CpTopology2Device*>::iterator it = iDeviceList.begin();

    while (it != iDeviceList.end()) {
        delete (*it);
        it++;
    }   

    LOG(kTopology, "CpTopology2::~CpTopology2 deleted devices\n");

    iReady.Write(iFree.Read()); // this null job causes the thread to complete

    delete (iThread);
    
    LOG(kTopology, "CpTopology2::~CpTopology2 deleted thread\n");

    for (TUint i = 0; i < kMaxJobCount; i++) {
        delete (iFree.Read());
    }

    LOG(kTopology, "CpTopology2::~CpTopology2 deleted jobs\n");
}
    
void CpTopology2::Refresh()
{
    iTopology1->Refresh();
}

// ICpTopology1Handler
    
void CpTopology2::ProductAdded(CpDevice& aDevice)
{
    iDeviceList.push_back(new CpTopology2Product(aDevice, *this));
}

void CpTopology2::ProductRemoved(CpDevice& aDevice)
{
    DeviceRemoved(aDevice);
}

void CpTopology2::DeviceRemoved(CpDevice& aDevice)
{
    std::vector<CpTopology2Device*>::iterator it = iDeviceList.begin();

    while (it != iDeviceList.end()) {
        if ((*it)->IsAttachedTo(aDevice)) {
            LOG(kTopology, "CpTopology2::ProductRemoved found\n");
            delete (*it);
            iDeviceList.erase(it);
            break;
        }
        it++;
    }   
}

// ICpTopology1Handler

void CpTopology2::GroupAdded(CpTopology2Group& aGroup)
{
    LOG(kTopology, "CpTopology2::GroupAdded ");
    LOG(kTopology, aGroup.Room());
    LOG(kTopology, ":");
    LOG(kTopology, aGroup.Name());
    LOG(kTopology, "\n");

    CpTopology2Job* job = iFree.Read();
    job->Set(aGroup, &ICpTopology2Handler::GroupAdded);
    iReady.Write(job);
}

void CpTopology2::GroupStandbyChanged(CpTopology2Group& aGroup)
{
    LOG(kTopology, "CpTopology2::GroupStandbyChanged ");
    LOG(kTopology, aGroup.Room());
    LOG(kTopology, ":");
    LOG(kTopology, aGroup.Name());
    LOG(kTopology, "\n");

    CpTopology2Job* job = iFree.Read();
    job->Set(aGroup, &ICpTopology2Handler::GroupStandbyChanged);
    iReady.Write(job);
}

void CpTopology2::GroupSourceIndexChanged(CpTopology2Group& aGroup)
{
    LOG(kTopology, "CpTopology2::GroupSourceIndexChanged ");
    LOG(kTopology, aGroup.Room());
    LOG(kTopology, ":");
    LOG(kTopology, aGroup.Name());
    LOG(kTopology, "\n");

    CpTopology2Job* job = iFree.Read();
    job->Set(aGroup, &ICpTopology2Handler::GroupSourceIndexChanged);
    iReady.Write(job);
}

void CpTopology2::GroupSourceListChanged(CpTopology2Group& aGroup)
{
    LOG(kTopology, "CpTopology2::GroupSourceListChanged ");
    LOG(kTopology, aGroup.Room());
    LOG(kTopology, ":");
    LOG(kTopology, aGroup.Name());
    LOG(kTopology, "\n");

    CpTopology2Job* job = iFree.Read();
    job->Set(aGroup, &ICpTopology2Handler::GroupSourceListChanged);
    iReady.Write(job);
}

void CpTopology2::GroupRemoved(CpTopology2Group& aGroup)
{
    LOG(kTopology, "CpTopology2::GroupRemoved ");
    LOG(kTopology, aGroup.Room());
    LOG(kTopology, ":");
    LOG(kTopology, aGroup.Name());
    LOG(kTopology, "\n");

    CpTopology2Job* job = iFree.Read();
    job->Set(aGroup, &ICpTopology2Handler::GroupRemoved);
    iReady.Write(job);
}

void CpTopology2::Run()
{
    LOG(kTopology, "CpTopology2::Run Started\n");

    for (;;)
    {
        LOG(kTopology, "CpTopology2::Run wait for job\n");

        CpTopology2Job* job = iReady.Read();
        
        LOG(kTopology, "CpTopology2::Run execute job\n");

        try {
            job->Execute();
            iFree.Write(job);
        }
        catch (ThreadKill)
        {
            iFree.Write(job);
            break;
        }
    }

    LOG(kTopology, "CpTopology2::Run Exiting\n");
}
