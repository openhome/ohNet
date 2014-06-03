#include "CpAvOpenhomeOrgPlaylist1.h"
#include <OpenHome/Net/Core/CpProxy.h>
#include <OpenHome/Net/Private/CpiService.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Net/Private/AsyncPrivate.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Cpp/CpDevice.h>
#include <OpenHome/Net/Private/CpiDevice.h>

#include <string>

using namespace OpenHome;
using namespace OpenHome::Net;


class SyncPlayAvOpenhomeOrgPlaylist1Cpp : public SyncProxyAction
{
public:
    SyncPlayAvOpenhomeOrgPlaylist1Cpp(CpProxyAvOpenhomeOrgPlaylist1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncPlayAvOpenhomeOrgPlaylist1Cpp() {}
private:
    CpProxyAvOpenhomeOrgPlaylist1Cpp& iService;
};

SyncPlayAvOpenhomeOrgPlaylist1Cpp::SyncPlayAvOpenhomeOrgPlaylist1Cpp(CpProxyAvOpenhomeOrgPlaylist1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncPlayAvOpenhomeOrgPlaylist1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndPlay(aAsync);
}


class SyncPauseAvOpenhomeOrgPlaylist1Cpp : public SyncProxyAction
{
public:
    SyncPauseAvOpenhomeOrgPlaylist1Cpp(CpProxyAvOpenhomeOrgPlaylist1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncPauseAvOpenhomeOrgPlaylist1Cpp() {}
private:
    CpProxyAvOpenhomeOrgPlaylist1Cpp& iService;
};

SyncPauseAvOpenhomeOrgPlaylist1Cpp::SyncPauseAvOpenhomeOrgPlaylist1Cpp(CpProxyAvOpenhomeOrgPlaylist1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncPauseAvOpenhomeOrgPlaylist1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndPause(aAsync);
}


class SyncStopAvOpenhomeOrgPlaylist1Cpp : public SyncProxyAction
{
public:
    SyncStopAvOpenhomeOrgPlaylist1Cpp(CpProxyAvOpenhomeOrgPlaylist1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncStopAvOpenhomeOrgPlaylist1Cpp() {}
private:
    CpProxyAvOpenhomeOrgPlaylist1Cpp& iService;
};

SyncStopAvOpenhomeOrgPlaylist1Cpp::SyncStopAvOpenhomeOrgPlaylist1Cpp(CpProxyAvOpenhomeOrgPlaylist1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncStopAvOpenhomeOrgPlaylist1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndStop(aAsync);
}


class SyncNextAvOpenhomeOrgPlaylist1Cpp : public SyncProxyAction
{
public:
    SyncNextAvOpenhomeOrgPlaylist1Cpp(CpProxyAvOpenhomeOrgPlaylist1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncNextAvOpenhomeOrgPlaylist1Cpp() {}
private:
    CpProxyAvOpenhomeOrgPlaylist1Cpp& iService;
};

SyncNextAvOpenhomeOrgPlaylist1Cpp::SyncNextAvOpenhomeOrgPlaylist1Cpp(CpProxyAvOpenhomeOrgPlaylist1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncNextAvOpenhomeOrgPlaylist1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndNext(aAsync);
}


class SyncPreviousAvOpenhomeOrgPlaylist1Cpp : public SyncProxyAction
{
public:
    SyncPreviousAvOpenhomeOrgPlaylist1Cpp(CpProxyAvOpenhomeOrgPlaylist1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncPreviousAvOpenhomeOrgPlaylist1Cpp() {}
private:
    CpProxyAvOpenhomeOrgPlaylist1Cpp& iService;
};

SyncPreviousAvOpenhomeOrgPlaylist1Cpp::SyncPreviousAvOpenhomeOrgPlaylist1Cpp(CpProxyAvOpenhomeOrgPlaylist1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncPreviousAvOpenhomeOrgPlaylist1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndPrevious(aAsync);
}


class SyncSetRepeatAvOpenhomeOrgPlaylist1Cpp : public SyncProxyAction
{
public:
    SyncSetRepeatAvOpenhomeOrgPlaylist1Cpp(CpProxyAvOpenhomeOrgPlaylist1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetRepeatAvOpenhomeOrgPlaylist1Cpp() {}
private:
    CpProxyAvOpenhomeOrgPlaylist1Cpp& iService;
};

SyncSetRepeatAvOpenhomeOrgPlaylist1Cpp::SyncSetRepeatAvOpenhomeOrgPlaylist1Cpp(CpProxyAvOpenhomeOrgPlaylist1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncSetRepeatAvOpenhomeOrgPlaylist1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetRepeat(aAsync);
}


class SyncRepeatAvOpenhomeOrgPlaylist1Cpp : public SyncProxyAction
{
public:
    SyncRepeatAvOpenhomeOrgPlaylist1Cpp(CpProxyAvOpenhomeOrgPlaylist1Cpp& aProxy, bool& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncRepeatAvOpenhomeOrgPlaylist1Cpp() {}
private:
    CpProxyAvOpenhomeOrgPlaylist1Cpp& iService;
    bool& iValue;
};

SyncRepeatAvOpenhomeOrgPlaylist1Cpp::SyncRepeatAvOpenhomeOrgPlaylist1Cpp(CpProxyAvOpenhomeOrgPlaylist1Cpp& aProxy, bool& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncRepeatAvOpenhomeOrgPlaylist1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndRepeat(aAsync, iValue);
}


class SyncSetShuffleAvOpenhomeOrgPlaylist1Cpp : public SyncProxyAction
{
public:
    SyncSetShuffleAvOpenhomeOrgPlaylist1Cpp(CpProxyAvOpenhomeOrgPlaylist1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetShuffleAvOpenhomeOrgPlaylist1Cpp() {}
private:
    CpProxyAvOpenhomeOrgPlaylist1Cpp& iService;
};

SyncSetShuffleAvOpenhomeOrgPlaylist1Cpp::SyncSetShuffleAvOpenhomeOrgPlaylist1Cpp(CpProxyAvOpenhomeOrgPlaylist1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncSetShuffleAvOpenhomeOrgPlaylist1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetShuffle(aAsync);
}


class SyncShuffleAvOpenhomeOrgPlaylist1Cpp : public SyncProxyAction
{
public:
    SyncShuffleAvOpenhomeOrgPlaylist1Cpp(CpProxyAvOpenhomeOrgPlaylist1Cpp& aProxy, bool& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncShuffleAvOpenhomeOrgPlaylist1Cpp() {}
private:
    CpProxyAvOpenhomeOrgPlaylist1Cpp& iService;
    bool& iValue;
};

SyncShuffleAvOpenhomeOrgPlaylist1Cpp::SyncShuffleAvOpenhomeOrgPlaylist1Cpp(CpProxyAvOpenhomeOrgPlaylist1Cpp& aProxy, bool& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncShuffleAvOpenhomeOrgPlaylist1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndShuffle(aAsync, iValue);
}


class SyncSeekSecondAbsoluteAvOpenhomeOrgPlaylist1Cpp : public SyncProxyAction
{
public:
    SyncSeekSecondAbsoluteAvOpenhomeOrgPlaylist1Cpp(CpProxyAvOpenhomeOrgPlaylist1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSeekSecondAbsoluteAvOpenhomeOrgPlaylist1Cpp() {}
private:
    CpProxyAvOpenhomeOrgPlaylist1Cpp& iService;
};

SyncSeekSecondAbsoluteAvOpenhomeOrgPlaylist1Cpp::SyncSeekSecondAbsoluteAvOpenhomeOrgPlaylist1Cpp(CpProxyAvOpenhomeOrgPlaylist1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncSeekSecondAbsoluteAvOpenhomeOrgPlaylist1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSeekSecondAbsolute(aAsync);
}


class SyncSeekSecondRelativeAvOpenhomeOrgPlaylist1Cpp : public SyncProxyAction
{
public:
    SyncSeekSecondRelativeAvOpenhomeOrgPlaylist1Cpp(CpProxyAvOpenhomeOrgPlaylist1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSeekSecondRelativeAvOpenhomeOrgPlaylist1Cpp() {}
private:
    CpProxyAvOpenhomeOrgPlaylist1Cpp& iService;
};

SyncSeekSecondRelativeAvOpenhomeOrgPlaylist1Cpp::SyncSeekSecondRelativeAvOpenhomeOrgPlaylist1Cpp(CpProxyAvOpenhomeOrgPlaylist1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncSeekSecondRelativeAvOpenhomeOrgPlaylist1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSeekSecondRelative(aAsync);
}


class SyncSeekIdAvOpenhomeOrgPlaylist1Cpp : public SyncProxyAction
{
public:
    SyncSeekIdAvOpenhomeOrgPlaylist1Cpp(CpProxyAvOpenhomeOrgPlaylist1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSeekIdAvOpenhomeOrgPlaylist1Cpp() {}
private:
    CpProxyAvOpenhomeOrgPlaylist1Cpp& iService;
};

SyncSeekIdAvOpenhomeOrgPlaylist1Cpp::SyncSeekIdAvOpenhomeOrgPlaylist1Cpp(CpProxyAvOpenhomeOrgPlaylist1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncSeekIdAvOpenhomeOrgPlaylist1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSeekId(aAsync);
}


class SyncSeekIndexAvOpenhomeOrgPlaylist1Cpp : public SyncProxyAction
{
public:
    SyncSeekIndexAvOpenhomeOrgPlaylist1Cpp(CpProxyAvOpenhomeOrgPlaylist1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSeekIndexAvOpenhomeOrgPlaylist1Cpp() {}
private:
    CpProxyAvOpenhomeOrgPlaylist1Cpp& iService;
};

SyncSeekIndexAvOpenhomeOrgPlaylist1Cpp::SyncSeekIndexAvOpenhomeOrgPlaylist1Cpp(CpProxyAvOpenhomeOrgPlaylist1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncSeekIndexAvOpenhomeOrgPlaylist1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSeekIndex(aAsync);
}


class SyncTransportStateAvOpenhomeOrgPlaylist1Cpp : public SyncProxyAction
{
public:
    SyncTransportStateAvOpenhomeOrgPlaylist1Cpp(CpProxyAvOpenhomeOrgPlaylist1Cpp& aProxy, std::string& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncTransportStateAvOpenhomeOrgPlaylist1Cpp() {}
private:
    CpProxyAvOpenhomeOrgPlaylist1Cpp& iService;
    std::string& iValue;
};

SyncTransportStateAvOpenhomeOrgPlaylist1Cpp::SyncTransportStateAvOpenhomeOrgPlaylist1Cpp(CpProxyAvOpenhomeOrgPlaylist1Cpp& aProxy, std::string& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncTransportStateAvOpenhomeOrgPlaylist1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndTransportState(aAsync, iValue);
}


class SyncIdAvOpenhomeOrgPlaylist1Cpp : public SyncProxyAction
{
public:
    SyncIdAvOpenhomeOrgPlaylist1Cpp(CpProxyAvOpenhomeOrgPlaylist1Cpp& aProxy, uint32_t& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncIdAvOpenhomeOrgPlaylist1Cpp() {}
private:
    CpProxyAvOpenhomeOrgPlaylist1Cpp& iService;
    uint32_t& iValue;
};

SyncIdAvOpenhomeOrgPlaylist1Cpp::SyncIdAvOpenhomeOrgPlaylist1Cpp(CpProxyAvOpenhomeOrgPlaylist1Cpp& aProxy, uint32_t& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncIdAvOpenhomeOrgPlaylist1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndId(aAsync, iValue);
}


class SyncReadAvOpenhomeOrgPlaylist1Cpp : public SyncProxyAction
{
public:
    SyncReadAvOpenhomeOrgPlaylist1Cpp(CpProxyAvOpenhomeOrgPlaylist1Cpp& aProxy, std::string& aUri, std::string& aMetadata);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncReadAvOpenhomeOrgPlaylist1Cpp() {}
private:
    CpProxyAvOpenhomeOrgPlaylist1Cpp& iService;
    std::string& iUri;
    std::string& iMetadata;
};

SyncReadAvOpenhomeOrgPlaylist1Cpp::SyncReadAvOpenhomeOrgPlaylist1Cpp(CpProxyAvOpenhomeOrgPlaylist1Cpp& aProxy, std::string& aUri, std::string& aMetadata)
    : iService(aProxy)
    , iUri(aUri)
    , iMetadata(aMetadata)
{
}

void SyncReadAvOpenhomeOrgPlaylist1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndRead(aAsync, iUri, iMetadata);
}


class SyncReadListAvOpenhomeOrgPlaylist1Cpp : public SyncProxyAction
{
public:
    SyncReadListAvOpenhomeOrgPlaylist1Cpp(CpProxyAvOpenhomeOrgPlaylist1Cpp& aProxy, std::string& aTrackList);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncReadListAvOpenhomeOrgPlaylist1Cpp() {}
private:
    CpProxyAvOpenhomeOrgPlaylist1Cpp& iService;
    std::string& iTrackList;
};

SyncReadListAvOpenhomeOrgPlaylist1Cpp::SyncReadListAvOpenhomeOrgPlaylist1Cpp(CpProxyAvOpenhomeOrgPlaylist1Cpp& aProxy, std::string& aTrackList)
    : iService(aProxy)
    , iTrackList(aTrackList)
{
}

void SyncReadListAvOpenhomeOrgPlaylist1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndReadList(aAsync, iTrackList);
}


class SyncInsertAvOpenhomeOrgPlaylist1Cpp : public SyncProxyAction
{
public:
    SyncInsertAvOpenhomeOrgPlaylist1Cpp(CpProxyAvOpenhomeOrgPlaylist1Cpp& aProxy, uint32_t& aNewId);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncInsertAvOpenhomeOrgPlaylist1Cpp() {}
private:
    CpProxyAvOpenhomeOrgPlaylist1Cpp& iService;
    uint32_t& iNewId;
};

SyncInsertAvOpenhomeOrgPlaylist1Cpp::SyncInsertAvOpenhomeOrgPlaylist1Cpp(CpProxyAvOpenhomeOrgPlaylist1Cpp& aProxy, uint32_t& aNewId)
    : iService(aProxy)
    , iNewId(aNewId)
{
}

void SyncInsertAvOpenhomeOrgPlaylist1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndInsert(aAsync, iNewId);
}


class SyncDeleteIdAvOpenhomeOrgPlaylist1Cpp : public SyncProxyAction
{
public:
    SyncDeleteIdAvOpenhomeOrgPlaylist1Cpp(CpProxyAvOpenhomeOrgPlaylist1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncDeleteIdAvOpenhomeOrgPlaylist1Cpp() {}
private:
    CpProxyAvOpenhomeOrgPlaylist1Cpp& iService;
};

SyncDeleteIdAvOpenhomeOrgPlaylist1Cpp::SyncDeleteIdAvOpenhomeOrgPlaylist1Cpp(CpProxyAvOpenhomeOrgPlaylist1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncDeleteIdAvOpenhomeOrgPlaylist1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndDeleteId(aAsync);
}


class SyncDeleteAllAvOpenhomeOrgPlaylist1Cpp : public SyncProxyAction
{
public:
    SyncDeleteAllAvOpenhomeOrgPlaylist1Cpp(CpProxyAvOpenhomeOrgPlaylist1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncDeleteAllAvOpenhomeOrgPlaylist1Cpp() {}
private:
    CpProxyAvOpenhomeOrgPlaylist1Cpp& iService;
};

SyncDeleteAllAvOpenhomeOrgPlaylist1Cpp::SyncDeleteAllAvOpenhomeOrgPlaylist1Cpp(CpProxyAvOpenhomeOrgPlaylist1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncDeleteAllAvOpenhomeOrgPlaylist1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndDeleteAll(aAsync);
}


class SyncTracksMaxAvOpenhomeOrgPlaylist1Cpp : public SyncProxyAction
{
public:
    SyncTracksMaxAvOpenhomeOrgPlaylist1Cpp(CpProxyAvOpenhomeOrgPlaylist1Cpp& aProxy, uint32_t& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncTracksMaxAvOpenhomeOrgPlaylist1Cpp() {}
private:
    CpProxyAvOpenhomeOrgPlaylist1Cpp& iService;
    uint32_t& iValue;
};

SyncTracksMaxAvOpenhomeOrgPlaylist1Cpp::SyncTracksMaxAvOpenhomeOrgPlaylist1Cpp(CpProxyAvOpenhomeOrgPlaylist1Cpp& aProxy, uint32_t& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncTracksMaxAvOpenhomeOrgPlaylist1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndTracksMax(aAsync, iValue);
}


class SyncIdArrayAvOpenhomeOrgPlaylist1Cpp : public SyncProxyAction
{
public:
    SyncIdArrayAvOpenhomeOrgPlaylist1Cpp(CpProxyAvOpenhomeOrgPlaylist1Cpp& aProxy, uint32_t& aToken, std::string& aArray);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncIdArrayAvOpenhomeOrgPlaylist1Cpp() {}
private:
    CpProxyAvOpenhomeOrgPlaylist1Cpp& iService;
    uint32_t& iToken;
    std::string& iArray;
};

SyncIdArrayAvOpenhomeOrgPlaylist1Cpp::SyncIdArrayAvOpenhomeOrgPlaylist1Cpp(CpProxyAvOpenhomeOrgPlaylist1Cpp& aProxy, uint32_t& aToken, std::string& aArray)
    : iService(aProxy)
    , iToken(aToken)
    , iArray(aArray)
{
}

void SyncIdArrayAvOpenhomeOrgPlaylist1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndIdArray(aAsync, iToken, iArray);
}


class SyncIdArrayChangedAvOpenhomeOrgPlaylist1Cpp : public SyncProxyAction
{
public:
    SyncIdArrayChangedAvOpenhomeOrgPlaylist1Cpp(CpProxyAvOpenhomeOrgPlaylist1Cpp& aProxy, bool& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncIdArrayChangedAvOpenhomeOrgPlaylist1Cpp() {}
private:
    CpProxyAvOpenhomeOrgPlaylist1Cpp& iService;
    bool& iValue;
};

SyncIdArrayChangedAvOpenhomeOrgPlaylist1Cpp::SyncIdArrayChangedAvOpenhomeOrgPlaylist1Cpp(CpProxyAvOpenhomeOrgPlaylist1Cpp& aProxy, bool& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncIdArrayChangedAvOpenhomeOrgPlaylist1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndIdArrayChanged(aAsync, iValue);
}


class SyncProtocolInfoAvOpenhomeOrgPlaylist1Cpp : public SyncProxyAction
{
public:
    SyncProtocolInfoAvOpenhomeOrgPlaylist1Cpp(CpProxyAvOpenhomeOrgPlaylist1Cpp& aProxy, std::string& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncProtocolInfoAvOpenhomeOrgPlaylist1Cpp() {}
private:
    CpProxyAvOpenhomeOrgPlaylist1Cpp& iService;
    std::string& iValue;
};

SyncProtocolInfoAvOpenhomeOrgPlaylist1Cpp::SyncProtocolInfoAvOpenhomeOrgPlaylist1Cpp(CpProxyAvOpenhomeOrgPlaylist1Cpp& aProxy, std::string& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncProtocolInfoAvOpenhomeOrgPlaylist1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndProtocolInfo(aAsync, iValue);
}


CpProxyAvOpenhomeOrgPlaylist1Cpp::CpProxyAvOpenhomeOrgPlaylist1Cpp(CpDeviceCpp& aDevice)
    : CpProxy("av-openhome-org", "Playlist", 1, aDevice.Device())
{
    OpenHome::Net::Parameter* param;
    TChar** allowedValues;
    TUint index;

    iActionPlay = new Action("Play");

    iActionPause = new Action("Pause");

    iActionStop = new Action("Stop");

    iActionNext = new Action("Next");

    iActionPrevious = new Action("Previous");

    iActionSetRepeat = new Action("SetRepeat");
    param = new OpenHome::Net::ParameterBool("Value");
    iActionSetRepeat->AddInputParameter(param);

    iActionRepeat = new Action("Repeat");
    param = new OpenHome::Net::ParameterBool("Value");
    iActionRepeat->AddOutputParameter(param);

    iActionSetShuffle = new Action("SetShuffle");
    param = new OpenHome::Net::ParameterBool("Value");
    iActionSetShuffle->AddInputParameter(param);

    iActionShuffle = new Action("Shuffle");
    param = new OpenHome::Net::ParameterBool("Value");
    iActionShuffle->AddOutputParameter(param);

    iActionSeekSecondAbsolute = new Action("SeekSecondAbsolute");
    param = new OpenHome::Net::ParameterUint("Value");
    iActionSeekSecondAbsolute->AddInputParameter(param);

    iActionSeekSecondRelative = new Action("SeekSecondRelative");
    param = new OpenHome::Net::ParameterInt("Value");
    iActionSeekSecondRelative->AddInputParameter(param);

    iActionSeekId = new Action("SeekId");
    param = new OpenHome::Net::ParameterUint("Value");
    iActionSeekId->AddInputParameter(param);

    iActionSeekIndex = new Action("SeekIndex");
    param = new OpenHome::Net::ParameterUint("Value");
    iActionSeekIndex->AddInputParameter(param);

    iActionTransportState = new Action("TransportState");
    index = 0;
    allowedValues = new TChar*[4];
    allowedValues[index++] = (TChar*)"Playing";
    allowedValues[index++] = (TChar*)"Paused";
    allowedValues[index++] = (TChar*)"Stopped";
    allowedValues[index++] = (TChar*)"Buffering";
    param = new OpenHome::Net::ParameterString("Value", allowedValues, 4);
    iActionTransportState->AddOutputParameter(param);
    delete[] allowedValues;

    iActionId = new Action("Id");
    param = new OpenHome::Net::ParameterUint("Value");
    iActionId->AddOutputParameter(param);

    iActionRead = new Action("Read");
    param = new OpenHome::Net::ParameterUint("Id");
    iActionRead->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Uri");
    iActionRead->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("Metadata");
    iActionRead->AddOutputParameter(param);

    iActionReadList = new Action("ReadList");
    param = new OpenHome::Net::ParameterString("IdList");
    iActionReadList->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("TrackList");
    iActionReadList->AddOutputParameter(param);

    iActionInsert = new Action("Insert");
    param = new OpenHome::Net::ParameterUint("AfterId");
    iActionInsert->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Uri");
    iActionInsert->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Metadata");
    iActionInsert->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("NewId");
    iActionInsert->AddOutputParameter(param);

    iActionDeleteId = new Action("DeleteId");
    param = new OpenHome::Net::ParameterUint("Value");
    iActionDeleteId->AddInputParameter(param);

    iActionDeleteAll = new Action("DeleteAll");

    iActionTracksMax = new Action("TracksMax");
    param = new OpenHome::Net::ParameterUint("Value");
    iActionTracksMax->AddOutputParameter(param);

    iActionIdArray = new Action("IdArray");
    param = new OpenHome::Net::ParameterUint("Token");
    iActionIdArray->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterBinary("Array");
    iActionIdArray->AddOutputParameter(param);

    iActionIdArrayChanged = new Action("IdArrayChanged");
    param = new OpenHome::Net::ParameterUint("Token");
    iActionIdArrayChanged->AddInputParameter(param);
    param = new OpenHome::Net::ParameterBool("Value");
    iActionIdArrayChanged->AddOutputParameter(param);

    iActionProtocolInfo = new Action("ProtocolInfo");
    param = new OpenHome::Net::ParameterString("Value");
    iActionProtocolInfo->AddOutputParameter(param);

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgPlaylist1Cpp::TransportStatePropertyChanged);
    iTransportState = new PropertyString(aDevice.Device().GetCpStack().Env(), "TransportState", functor);
    AddProperty(iTransportState);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgPlaylist1Cpp::RepeatPropertyChanged);
    iRepeat = new PropertyBool(aDevice.Device().GetCpStack().Env(), "Repeat", functor);
    AddProperty(iRepeat);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgPlaylist1Cpp::ShufflePropertyChanged);
    iShuffle = new PropertyBool(aDevice.Device().GetCpStack().Env(), "Shuffle", functor);
    AddProperty(iShuffle);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgPlaylist1Cpp::IdPropertyChanged);
    iId = new PropertyUint(aDevice.Device().GetCpStack().Env(), "Id", functor);
    AddProperty(iId);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgPlaylist1Cpp::IdArrayPropertyChanged);
    iIdArray = new PropertyBinary(aDevice.Device().GetCpStack().Env(), "IdArray", functor);
    AddProperty(iIdArray);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgPlaylist1Cpp::TracksMaxPropertyChanged);
    iTracksMax = new PropertyUint(aDevice.Device().GetCpStack().Env(), "TracksMax", functor);
    AddProperty(iTracksMax);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgPlaylist1Cpp::ProtocolInfoPropertyChanged);
    iProtocolInfo = new PropertyString(aDevice.Device().GetCpStack().Env(), "ProtocolInfo", functor);
    AddProperty(iProtocolInfo);
}

CpProxyAvOpenhomeOrgPlaylist1Cpp::~CpProxyAvOpenhomeOrgPlaylist1Cpp()
{
    DestroyService();
    delete iActionPlay;
    delete iActionPause;
    delete iActionStop;
    delete iActionNext;
    delete iActionPrevious;
    delete iActionSetRepeat;
    delete iActionRepeat;
    delete iActionSetShuffle;
    delete iActionShuffle;
    delete iActionSeekSecondAbsolute;
    delete iActionSeekSecondRelative;
    delete iActionSeekId;
    delete iActionSeekIndex;
    delete iActionTransportState;
    delete iActionId;
    delete iActionRead;
    delete iActionReadList;
    delete iActionInsert;
    delete iActionDeleteId;
    delete iActionDeleteAll;
    delete iActionTracksMax;
    delete iActionIdArray;
    delete iActionIdArrayChanged;
    delete iActionProtocolInfo;
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::SyncPlay()
{
    SyncPlayAvOpenhomeOrgPlaylist1Cpp sync(*this);
    BeginPlay(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::BeginPlay(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionPlay, aFunctor);
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::EndPlay(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Play"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::SyncPause()
{
    SyncPauseAvOpenhomeOrgPlaylist1Cpp sync(*this);
    BeginPause(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::BeginPause(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionPause, aFunctor);
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::EndPause(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Pause"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::SyncStop()
{
    SyncStopAvOpenhomeOrgPlaylist1Cpp sync(*this);
    BeginStop(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::BeginStop(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionStop, aFunctor);
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::EndStop(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Stop"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::SyncNext()
{
    SyncNextAvOpenhomeOrgPlaylist1Cpp sync(*this);
    BeginNext(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::BeginNext(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionNext, aFunctor);
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::EndNext(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Next"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::SyncPrevious()
{
    SyncPreviousAvOpenhomeOrgPlaylist1Cpp sync(*this);
    BeginPrevious(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::BeginPrevious(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionPrevious, aFunctor);
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::EndPrevious(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Previous"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::SyncSetRepeat(bool aValue)
{
    SyncSetRepeatAvOpenhomeOrgPlaylist1Cpp sync(*this);
    BeginSetRepeat(aValue, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::BeginSetRepeat(bool aValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetRepeat, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetRepeat->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aValue));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::EndSetRepeat(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetRepeat"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::SyncRepeat(bool& aValue)
{
    SyncRepeatAvOpenhomeOrgPlaylist1Cpp sync(*this, aValue);
    BeginRepeat(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::BeginRepeat(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionRepeat, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionRepeat->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::EndRepeat(IAsync& aAsync, bool& aValue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Repeat"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aValue = ((ArgumentBool*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::SyncSetShuffle(bool aValue)
{
    SyncSetShuffleAvOpenhomeOrgPlaylist1Cpp sync(*this);
    BeginSetShuffle(aValue, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::BeginSetShuffle(bool aValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetShuffle, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetShuffle->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aValue));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::EndSetShuffle(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetShuffle"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::SyncShuffle(bool& aValue)
{
    SyncShuffleAvOpenhomeOrgPlaylist1Cpp sync(*this, aValue);
    BeginShuffle(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::BeginShuffle(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionShuffle, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionShuffle->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::EndShuffle(IAsync& aAsync, bool& aValue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Shuffle"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aValue = ((ArgumentBool*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::SyncSeekSecondAbsolute(uint32_t aValue)
{
    SyncSeekSecondAbsoluteAvOpenhomeOrgPlaylist1Cpp sync(*this);
    BeginSeekSecondAbsolute(aValue, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::BeginSeekSecondAbsolute(uint32_t aValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSeekSecondAbsolute, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSeekSecondAbsolute->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aValue));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::EndSeekSecondAbsolute(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SeekSecondAbsolute"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::SyncSeekSecondRelative(int32_t aValue)
{
    SyncSeekSecondRelativeAvOpenhomeOrgPlaylist1Cpp sync(*this);
    BeginSeekSecondRelative(aValue, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::BeginSeekSecondRelative(int32_t aValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSeekSecondRelative, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSeekSecondRelative->InputParameters();
    invocation->AddInput(new ArgumentInt(*inParams[inIndex++], aValue));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::EndSeekSecondRelative(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SeekSecondRelative"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::SyncSeekId(uint32_t aValue)
{
    SyncSeekIdAvOpenhomeOrgPlaylist1Cpp sync(*this);
    BeginSeekId(aValue, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::BeginSeekId(uint32_t aValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSeekId, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSeekId->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aValue));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::EndSeekId(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SeekId"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::SyncSeekIndex(uint32_t aValue)
{
    SyncSeekIndexAvOpenhomeOrgPlaylist1Cpp sync(*this);
    BeginSeekIndex(aValue, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::BeginSeekIndex(uint32_t aValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSeekIndex, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSeekIndex->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aValue));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::EndSeekIndex(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SeekIndex"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::SyncTransportState(std::string& aValue)
{
    SyncTransportStateAvOpenhomeOrgPlaylist1Cpp sync(*this, aValue);
    BeginTransportState(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::BeginTransportState(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionTransportState, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionTransportState->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::EndTransportState(IAsync& aAsync, std::string& aValue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("TransportState"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aValue.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::SyncId(uint32_t& aValue)
{
    SyncIdAvOpenhomeOrgPlaylist1Cpp sync(*this, aValue);
    BeginId(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::BeginId(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionId, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionId->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::EndId(IAsync& aAsync, uint32_t& aValue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Id"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aValue = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::SyncRead(uint32_t aId, std::string& aUri, std::string& aMetadata)
{
    SyncReadAvOpenhomeOrgPlaylist1Cpp sync(*this, aUri, aMetadata);
    BeginRead(aId, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::BeginRead(uint32_t aId, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionRead, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionRead->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aId));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionRead->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::EndRead(IAsync& aAsync, std::string& aUri, std::string& aMetadata)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Read"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aUri.assign((const char*)val.Ptr(), val.Bytes());
    }
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aMetadata.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::SyncReadList(const std::string& aIdList, std::string& aTrackList)
{
    SyncReadListAvOpenhomeOrgPlaylist1Cpp sync(*this, aTrackList);
    BeginReadList(aIdList, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::BeginReadList(const std::string& aIdList, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionReadList, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionReadList->InputParameters();
    {
        Brn buf((const TByte*)aIdList.c_str(), (TUint)aIdList.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionReadList->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::EndReadList(IAsync& aAsync, std::string& aTrackList)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("ReadList"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aTrackList.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::SyncInsert(uint32_t aAfterId, const std::string& aUri, const std::string& aMetadata, uint32_t& aNewId)
{
    SyncInsertAvOpenhomeOrgPlaylist1Cpp sync(*this, aNewId);
    BeginInsert(aAfterId, aUri, aMetadata, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::BeginInsert(uint32_t aAfterId, const std::string& aUri, const std::string& aMetadata, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionInsert, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionInsert->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aAfterId));
    {
        Brn buf((const TByte*)aUri.c_str(), (TUint)aUri.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aMetadata.c_str(), (TUint)aMetadata.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionInsert->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::EndInsert(IAsync& aAsync, uint32_t& aNewId)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Insert"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aNewId = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::SyncDeleteId(uint32_t aValue)
{
    SyncDeleteIdAvOpenhomeOrgPlaylist1Cpp sync(*this);
    BeginDeleteId(aValue, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::BeginDeleteId(uint32_t aValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionDeleteId, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionDeleteId->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aValue));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::EndDeleteId(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("DeleteId"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::SyncDeleteAll()
{
    SyncDeleteAllAvOpenhomeOrgPlaylist1Cpp sync(*this);
    BeginDeleteAll(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::BeginDeleteAll(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionDeleteAll, aFunctor);
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::EndDeleteAll(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("DeleteAll"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::SyncTracksMax(uint32_t& aValue)
{
    SyncTracksMaxAvOpenhomeOrgPlaylist1Cpp sync(*this, aValue);
    BeginTracksMax(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::BeginTracksMax(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionTracksMax, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionTracksMax->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::EndTracksMax(IAsync& aAsync, uint32_t& aValue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("TracksMax"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aValue = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::SyncIdArray(uint32_t& aToken, std::string& aArray)
{
    SyncIdArrayAvOpenhomeOrgPlaylist1Cpp sync(*this, aToken, aArray);
    BeginIdArray(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::BeginIdArray(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionIdArray, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionIdArray->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentBinary(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::EndIdArray(IAsync& aAsync, uint32_t& aToken, std::string& aArray)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("IdArray"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aToken = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aArray.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::SyncIdArrayChanged(uint32_t aToken, bool& aValue)
{
    SyncIdArrayChangedAvOpenhomeOrgPlaylist1Cpp sync(*this, aValue);
    BeginIdArrayChanged(aToken, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::BeginIdArrayChanged(uint32_t aToken, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionIdArrayChanged, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionIdArrayChanged->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aToken));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionIdArrayChanged->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::EndIdArrayChanged(IAsync& aAsync, bool& aValue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("IdArrayChanged"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aValue = ((ArgumentBool*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::SyncProtocolInfo(std::string& aValue)
{
    SyncProtocolInfoAvOpenhomeOrgPlaylist1Cpp sync(*this, aValue);
    BeginProtocolInfo(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::BeginProtocolInfo(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionProtocolInfo, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionProtocolInfo->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::EndProtocolInfo(IAsync& aAsync, std::string& aValue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("ProtocolInfo"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aValue.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::SetPropertyTransportStateChanged(Functor& aFunctor)
{
    iLock->Wait();
    iTransportStateChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::SetPropertyRepeatChanged(Functor& aFunctor)
{
    iLock->Wait();
    iRepeatChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::SetPropertyShuffleChanged(Functor& aFunctor)
{
    iLock->Wait();
    iShuffleChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::SetPropertyIdChanged(Functor& aFunctor)
{
    iLock->Wait();
    iIdChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::SetPropertyIdArrayChanged(Functor& aFunctor)
{
    iLock->Wait();
    iIdArrayChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::SetPropertyTracksMaxChanged(Functor& aFunctor)
{
    iLock->Wait();
    iTracksMaxChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::SetPropertyProtocolInfoChanged(Functor& aFunctor)
{
    iLock->Wait();
    iProtocolInfoChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::PropertyTransportState(std::string& aTransportState) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iTransportState->Value();
    aTransportState.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::PropertyRepeat(bool& aRepeat) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aRepeat = iRepeat->Value();
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::PropertyShuffle(bool& aShuffle) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aShuffle = iShuffle->Value();
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::PropertyId(uint32_t& aId) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aId = iId->Value();
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::PropertyIdArray(std::string& aIdArray) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iIdArray->Value();
    aIdArray.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::PropertyTracksMax(uint32_t& aTracksMax) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aTracksMax = iTracksMax->Value();
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::PropertyProtocolInfo(std::string& aProtocolInfo) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iProtocolInfo->Value();
    aProtocolInfo.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::TransportStatePropertyChanged()
{
    ReportEvent(iTransportStateChanged);
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::RepeatPropertyChanged()
{
    ReportEvent(iRepeatChanged);
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::ShufflePropertyChanged()
{
    ReportEvent(iShuffleChanged);
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::IdPropertyChanged()
{
    ReportEvent(iIdChanged);
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::IdArrayPropertyChanged()
{
    ReportEvent(iIdArrayChanged);
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::TracksMaxPropertyChanged()
{
    ReportEvent(iTracksMaxChanged);
}

void CpProxyAvOpenhomeOrgPlaylist1Cpp::ProtocolInfoPropertyChanged()
{
    ReportEvent(iProtocolInfoChanged);
}

