#include "CpTopology2.h"

#include <Debug.h>
#include <Parser.h>
#include <Ascii.h>
#include <XmlParser.h>

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

CpTopology2Group::CpTopology2Group(CpDevice& aDevice, ICpTopology2GroupHandler& aHandler, TBool aStandby, const Brx& aRoom, const Brx& aName, TUint aSourceIndex, TUint aVolumeMax, TUint aVolumeUnity, TUint aVolumeSteps, TUint aVolumeMilliDbPerStep, TUint aBalanceMax, TUint aFadeMax, TUint aVolumeLimit, TUint aVolume, TInt aBalance, TUint aFade, TBool aMute)
	: iDevice(aDevice)
	, iHandler(aHandler)
	, iStandby(aStandby)
	, iRoom(aRoom)
	, iName(aName)
	, iSourceIndex(aSourceIndex)
	, iHasVolumeControl(true)
	, iVolumeMax(aVolumeMax)
	, iVolumeUnity(aVolumeUnity)
	, iVolumeSteps(aVolumeSteps)
	, iVolumeMilliDbPerStep(aVolumeMilliDbPerStep)
	, iBalanceMax(aBalanceMax)
	, iFadeMax(aFadeMax)
	, iVolumeLimit(aVolumeLimit)
	, iVolume(aVolume)
	, iBalance(aBalance)
	, iFade(aFade)
	, iMute(aMute)
	, iUserData(0)
	, iRefCount(1)
{
}

CpTopology2Group::CpTopology2Group(CpDevice& aDevice, ICpTopology2GroupHandler& aHandler, TBool aStandby, const Brx& aRoom, const Brx& aName, TUint aSourceIndex)
    : iDevice(aDevice)
    , iHandler(aHandler)
    , iStandby(aStandby)
    , iRoom(aRoom)
    , iName(aName)
    , iSourceIndex(aSourceIndex)
    , iHasVolumeControl(false)
    , iVolumeMax(0)
    , iVolumeUnity(0)
    , iVolumeSteps(0)
    , iVolumeMilliDbPerStep(0)
    , iBalanceMax(0)
    , iFadeMax(0)
    , iVolumeLimit(0)
    , iVolume(0)
    , iBalance(0)
    , iFade(0)
    , iMute(0)
    , iUserData(0)
    , iRefCount(1)
{
}

CpTopology2Group::~CpTopology2Group()
{
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

void CpTopology2Group::UpdateVolumeLimit(TUint aValue)
{
    iVolumeLimit = aValue;
}

void CpTopology2Group::UpdateVolume(TUint aValue)
{
	iVolume = aValue;
}

void CpTopology2Group::UpdateBalance(TInt aValue)
{
    iBalance = aValue;
}

void CpTopology2Group::UpdateFade(TInt aValue)
{
    iFade = aValue;
}

void CpTopology2Group::UpdateMute(TBool aValue)
{
	iMute = aValue;
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

TUint CpTopology2Group::VolumeMax() const
{
    ASSERT(iHasVolumeControl);
    return (iVolumeMax);
}

TUint CpTopology2Group::VolumeUnity() const
{
    ASSERT(iHasVolumeControl);
    return (iVolumeUnity);
}

TUint CpTopology2Group::VolumeSteps() const
{
    ASSERT(iHasVolumeControl);
    return (iVolumeSteps);
}

TUint CpTopology2Group::VolumeMilliDbPerStep() const
{
    ASSERT(iHasVolumeControl);
    return (iVolumeMilliDbPerStep);
}

TUint CpTopology2Group::BalanceMax() const
{
    ASSERT(iHasVolumeControl);
    return (iBalanceMax);
}

TUint CpTopology2Group::FadeMax() const
{
    ASSERT(iHasVolumeControl);
    return (iFadeMax);
}

TUint CpTopology2Group::VolumeLimit() const
{
    ASSERT(iHasVolumeControl);
    return (iVolumeLimit);
}

TUint CpTopology2Group::Volume() const
{
    ASSERT(iHasVolumeControl);
    return (iVolume);
}

void CpTopology2Group::SetVolume(TUint aValue)
{
    ASSERT(iHasVolumeControl);
    iHandler.SetVolume(aValue);
}

void CpTopology2Group::VolumeInc()
{
    ASSERT(iHasVolumeControl);
    iHandler.VolumeInc();
}

void CpTopology2Group::VolumeDec()
{
    ASSERT(iHasVolumeControl);
    iHandler.VolumeDec();
}

TInt CpTopology2Group::Balance() const
{
    return (iBalance);
}

void CpTopology2Group::SetBalance(TInt aValue)
{
    ASSERT(iHasVolumeControl);
    iHandler.SetBalance(aValue);
}

void CpTopology2Group::BalanceInc()
{
    ASSERT(iHasVolumeControl);
    iHandler.BalanceInc();
}

void CpTopology2Group::BalanceDec()
{
    ASSERT(iHasVolumeControl);
    iHandler.BalanceDec();
}

TInt CpTopology2Group::Fade() const
{
    ASSERT(iHasVolumeControl);
    return (iFade);
}

void CpTopology2Group::SetFade(TInt aValue)
{
    ASSERT(iHasVolumeControl);
    iHandler.SetFade(aValue);
}

void CpTopology2Group::FadeInc()
{
    ASSERT(iHasVolumeControl);
    iHandler.FadeInc();
}

void CpTopology2Group::FadeDec()
{
    ASSERT(iHasVolumeControl);
    iHandler.FadeDec();
}

TBool CpTopology2Group::Mute() const
{
    ASSERT(iHasVolumeControl);
    return (iMute);
}

void CpTopology2Group::SetMute(TBool aValue)
{
    ASSERT(iHasVolumeControl);
    iHandler.SetMute(aValue);
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
    //iDevice.AddRef();
}
	
TBool CpTopology2Device::IsAttachedTo(CpDevice& aDevice)
{
	return (iDevice.Udn() == aDevice.Udn());
}

CpTopology2Device::~CpTopology2Device()
{
    //iDevice.RemoveRef();
}
	
// CpTopology2Product

CpTopology2Product::CpTopology2Product(CpDevice& aDevice, ICpTopology2Handler& aHandler)
    : CpTopology2Device(aDevice)
    , iHandler(aHandler)
    , iServiceProduct(0)
    , iServiceVolume(0)
    , iGroup(0)
{
    iFunctorSetSourceIndex = MakeFunctorAsync(*this, &CpTopology2Product::CallbackSetSourceIndex);

    iFunctorSetStandby = MakeFunctorAsync(*this, &CpTopology2Product::CallbackSetStandby);

    iFunctorSetVolume = MakeFunctorAsync(*this, &CpTopology2Product::CallbackSetVolume);
    iFunctorVolumeInc = MakeFunctorAsync(*this, &CpTopology2Product::CallbackVolumeInc);
    iFunctorVolumeDec = MakeFunctorAsync(*this, &CpTopology2Product::CallbackVolumeDec);

    iFunctorSetBalance = MakeFunctorAsync(*this, &CpTopology2Product::CallbackSetBalance);
    iFunctorBalanceInc = MakeFunctorAsync(*this, &CpTopology2Product::CallbackBalanceInc);
    iFunctorBalanceDec = MakeFunctorAsync(*this, &CpTopology2Product::CallbackBalanceDec);

    iFunctorSetFade = MakeFunctorAsync(*this, &CpTopology2Product::CallbackSetFade);
    iFunctorFadeInc = MakeFunctorAsync(*this, &CpTopology2Product::CallbackFadeInc);
    iFunctorFadeDec = MakeFunctorAsync(*this, &CpTopology2Product::CallbackFadeDec);

    iFunctorSetMute = MakeFunctorAsync(*this, &CpTopology2Product::CallbackSetMute);

	iServiceProduct = new CpProxyAvOpenhomeOrgProduct1(iDevice);

	Functor functorInitial = MakeFunctor(*this, &CpTopology2Product::EventProductInitialEvent);

    iServiceProduct->SetPropertyInitialEvent(functorInitial);

	iServiceProduct->Subscribe();
}

CpTopology2Product::~CpTopology2Product()
{
	delete (iServiceProduct);
	delete (iServiceVolume);
	
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
      
	Brhz attributes;

	iServiceProduct->PropertyAttributes(attributes);

    Parser parser(attributes);
    
    for (;;) {
        Brn attribute = parser.Next();
        
        if (attribute.Bytes() == 0) {
            break;
        }
        
        if (attribute == Brn("Volume")) {
            iServiceVolume = new CpProxyAvOpenhomeOrgVolume1(iDevice);
            Functor functorInitial = MakeFunctor(*this, &CpTopology2Product::EventPreampInitialEvent);
            iServiceVolume->SetPropertyInitialEvent(functorInitial);    
            iServiceVolume->Subscribe();
            return;
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
	
	iGroup = new CpTopology2Group(iDevice, *this, standby, room, name, sourceIndex);
	
	ProcessSourceXml(xml, true);
	
	iHandler.GroupAdded(*iGroup);
}

void CpTopology2Product::EventPreampInitialEvent()
{
    Functor functorVolumeLimit = MakeFunctor(*this, &CpTopology2Product::EventPreampVolumeLimitChanged);
    Functor functorVolume = MakeFunctor(*this, &CpTopology2Product::EventPreampVolumeChanged);
    Functor functorBalance = MakeFunctor(*this, &CpTopology2Product::EventPreampBalanceChanged);
    Functor functorFade = MakeFunctor(*this, &CpTopology2Product::EventPreampFadeChanged);
    Functor functorMute = MakeFunctor(*this, &CpTopology2Product::EventPreampMuteChanged);
    iServiceVolume->SetPropertyVolumeChanged(functorVolume);    
    iServiceVolume->SetPropertyMuteChanged(functorMute);    

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
	
    TUint volumeMax;
    TUint volumeUnity;
    TUint volumeSteps;
    TUint volumeMilliDbPerStep;
    TUint balanceMax;
    TUint fadeMax;
    TUint volumeLimit; 
    TUint volume;
    TInt balance;
    TInt fade;
    TBool mute;
    
    iServiceVolume->PropertyVolumeMax(volumeMax);
    iServiceVolume->PropertyVolumeUnity(volumeUnity);
    iServiceVolume->PropertyVolumeSteps(volumeSteps);
    iServiceVolume->PropertyVolumeMilliDbPerStep(volumeMilliDbPerStep);
    iServiceVolume->PropertyBalanceMax(balanceMax);
    iServiceVolume->PropertyFadeMax(fadeMax);
    iServiceVolume->PropertyVolumeLimit(volumeLimit);
	iServiceVolume->PropertyVolume(volume);
    iServiceVolume->PropertyBalance(balance);
    iServiceVolume->PropertyFade(fade);
	iServiceVolume->PropertyMute(mute);

	iGroup = new CpTopology2Group(iDevice, *this, standby, room, name, sourceIndex, volumeMax, volumeUnity, volumeSteps, volumeMilliDbPerStep, balanceMax, fadeMax, volumeLimit, volume, balance, fade, mute);
	
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

void CpTopology2Product::EventPreampVolumeLimitChanged()
{
    LOG(kTopology, "CpTopology2::EventVolumeLimitChanged ");
    LOG(kTopology, iGroup->Room());
    LOG(kTopology, ":");
    LOG(kTopology, iGroup->Name());
    LOG(kTopology, "\n");

    TUint volumeLimit;
    iServiceVolume->PropertyVolume(volumeLimit);

    iGroup->UpdateVolumeLimit(volumeLimit);
    iHandler.GroupVolumeLimitChanged(*iGroup);
}   

void CpTopology2Product::EventPreampVolumeChanged()
{
    LOG(kTopology, "CpTopology2::EventVolumeChanged ");
    LOG(kTopology, iGroup->Room());
    LOG(kTopology, ":");
    LOG(kTopology, iGroup->Name());
    LOG(kTopology, "\n");

	TUint volume;
	iServiceVolume->PropertyVolume(volume);

	iGroup->UpdateVolume(volume);
	iHandler.GroupVolumeChanged(*iGroup);
}	

void CpTopology2Product::EventPreampBalanceChanged()
{
    LOG(kTopology, "CpTopology2::EventBalanceChanged ");
    LOG(kTopology, iGroup->Room());
    LOG(kTopology, ":");
    LOG(kTopology, iGroup->Name());
    LOG(kTopology, "\n");

    TInt balance;
    iServiceVolume->PropertyBalance(balance);

    iGroup->UpdateBalance(balance);
    iHandler.GroupBalanceChanged(*iGroup);
}   

void CpTopology2Product::EventPreampFadeChanged()
{
    LOG(kTopology, "CpTopology2::EventFadeChanged ");
    LOG(kTopology, iGroup->Room());
    LOG(kTopology, ":");
    LOG(kTopology, iGroup->Name());
    LOG(kTopology, "\n");

    TInt fade;
    iServiceVolume->PropertyFade(fade);

    iGroup->UpdateFade(fade);
    iHandler.GroupFadeChanged(*iGroup);
}   

void CpTopology2Product::EventPreampMuteChanged()
{
    LOG(kTopology, "CpTopology2::EventMuteChanged ");
    LOG(kTopology, iGroup->Room());
    LOG(kTopology, ":");
    LOG(kTopology, iGroup->Name());
    LOG(kTopology, "\n");

	TBool mute;
	iServiceVolume->PropertyMute(mute);

	iGroup->UpdateMute(mute);
	iHandler.GroupMuteChanged(*iGroup);
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

void CpTopology2Product::SetVolume(TUint aValue)
{
	iServiceVolume->BeginSetVolume(aValue, iFunctorSetVolume);
}

void CpTopology2Product::CallbackSetVolume(IAsync& aAsync)
{
	iServiceVolume->EndSetVolume(aAsync);
}		

void CpTopology2Product::VolumeInc()
{
    iServiceVolume->BeginVolumeInc(iFunctorVolumeInc);
}

void CpTopology2Product::CallbackVolumeInc(IAsync& aAsync)
{
    iServiceVolume->EndVolumeInc(aAsync);
}       

void CpTopology2Product::VolumeDec()
{
    iServiceVolume->BeginVolumeDec(iFunctorVolumeDec);
}

void CpTopology2Product::CallbackVolumeDec(IAsync& aAsync)
{
    iServiceVolume->EndVolumeDec(aAsync);
}       

void CpTopology2Product::SetBalance(TInt aValue)
{
    iServiceVolume->BeginSetBalance(aValue, iFunctorSetBalance);
}

void CpTopology2Product::CallbackSetBalance(IAsync& aAsync)
{
    iServiceVolume->EndSetBalance(aAsync);
}       

void CpTopology2Product::BalanceInc()
{
    iServiceVolume->BeginVolumeInc(iFunctorBalanceInc);
}

void CpTopology2Product::CallbackBalanceInc(IAsync& aAsync)
{
    iServiceVolume->EndBalanceInc(aAsync);
}       

void CpTopology2Product::BalanceDec()
{
    iServiceVolume->BeginBalanceInc(iFunctorBalanceDec);
}

void CpTopology2Product::CallbackBalanceDec(IAsync& aAsync)
{
    iServiceVolume->EndBalanceDec(aAsync);
}       

void CpTopology2Product::SetFade(TInt aValue)
{
    iServiceVolume->BeginSetFade(aValue, iFunctorSetFade);
}

void CpTopology2Product::CallbackSetFade(IAsync& aAsync)
{
    iServiceVolume->EndSetFade(aAsync);
}       

void CpTopology2Product::FadeInc()
{
    iServiceVolume->BeginFadeInc(iFunctorFadeInc);
}

void CpTopology2Product::CallbackFadeInc(IAsync& aAsync)
{
    iServiceVolume->EndFadeInc(aAsync);
}       

void CpTopology2Product::FadeDec()
{
    iServiceVolume->BeginFadeInc(iFunctorFadeDec);
}

void CpTopology2Product::CallbackFadeDec(IAsync& aAsync)
{
    iServiceVolume->EndFadeDec(aAsync);
}       

void CpTopology2Product::SetMute(TBool aValue)
{
	iServiceVolume->BeginSetMute(aValue, iFunctorSetVolume);
}

void CpTopology2Product::CallbackSetMute(IAsync& aAsync)
{
	iServiceVolume->EndSetMute(aAsync);
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
    delete (iTopology1);
    
    std::vector<CpTopology2Device*>::iterator it = iDeviceList.begin();

    while (it != iDeviceList.end()) {
        delete (*it);
        it++;
    }   

	iReady.Write(iFree.Read());

	delete (iThread);
	
	for (TUint i = 0; i < kMaxJobCount; i++) {
		delete (iFree.Read());
	}
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

void CpTopology2::GroupVolumeLimitChanged(CpTopology2Group& aGroup)
{
    LOG(kTopology, "CpTopology2::GroupVolumeLimitChanged ");
    LOG(kTopology, aGroup.Room());
    LOG(kTopology, ":");
    LOG(kTopology, aGroup.Name());
    LOG(kTopology, "\n");

    CpTopology2Job* job = iFree.Read();
    job->Set(aGroup, &ICpTopology2Handler::GroupVolumeLimitChanged);
    iReady.Write(job);
}

void CpTopology2::GroupVolumeChanged(CpTopology2Group& aGroup)
{
    LOG(kTopology, "CpTopology2::GroupVolumeChanged ");
    LOG(kTopology, aGroup.Room());
    LOG(kTopology, ":");
    LOG(kTopology, aGroup.Name());
    LOG(kTopology, "\n");

	CpTopology2Job* job = iFree.Read();
	job->Set(aGroup, &ICpTopology2Handler::GroupVolumeChanged);
	iReady.Write(job);
}

void CpTopology2::GroupBalanceChanged(CpTopology2Group& aGroup)
{
    LOG(kTopology, "CpTopology2::GroupBalanceChanged ");
    LOG(kTopology, aGroup.Room());
    LOG(kTopology, ":");
    LOG(kTopology, aGroup.Name());
    LOG(kTopology, "\n");

    CpTopology2Job* job = iFree.Read();
    job->Set(aGroup, &ICpTopology2Handler::GroupBalanceChanged);
    iReady.Write(job);
}

void CpTopology2::GroupFadeChanged(CpTopology2Group& aGroup)
{
    LOG(kTopology, "CpTopology2::GroupFadeChanged ");
    LOG(kTopology, aGroup.Room());
    LOG(kTopology, ":");
    LOG(kTopology, aGroup.Name());
    LOG(kTopology, "\n");

    CpTopology2Job* job = iFree.Read();
    job->Set(aGroup, &ICpTopology2Handler::GroupFadeChanged);
    iReady.Write(job);
}

void CpTopology2::GroupMuteChanged(CpTopology2Group& aGroup)
{
    LOG(kTopology, "CpTopology2::GroupMuteChanged ");
    LOG(kTopology, aGroup.Room());
    LOG(kTopology, ":");
    LOG(kTopology, aGroup.Name());
    LOG(kTopology, "\n");

	CpTopology2Job* job = iFree.Read();
	job->Set(aGroup, &ICpTopology2Handler::GroupMuteChanged);
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
