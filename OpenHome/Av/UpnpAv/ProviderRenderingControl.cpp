#include <OpenHome/Av/UpnpAv/ProviderRenderingControl.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <Generated/DvUpnpOrgRenderingControl1.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Av/FaultCode.h>
#include <OpenHome/Net/Core/DvInvocationResponse.h>
#include <OpenHome/Av/VolumeManager.h>

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::Av;

// For a MediaRenderer device with no ConnectionManager.PrepareForConnection()
// action, the only valid InstanceID is 0
static const TUint kInstanceId = 0;

static const TInt kInvalidInstanceIdCode = 702;
static const Brn kInvalidInstanceIdMsg("Invalid InstanceID");
static const TInt kInvalidChannelCode = 402;
static const Brn kInvalidChannelMsg("Argument[Channel] contains a value that is not in the AllowedValueList");
static const TUint kInvalidPresetNameCode = 701;
static const Brn KInvalidPresetNameMsg("Argument[PresetName] is invalid");
static const TInt kActionNotSupportedCode = 801;
static const Brn  kActionNotSupportedMsg("Action not supported");
static const TInt kInvalidVolumeCode = 811;
static const Brn  kInvalidVolumeMsg("Volume invalid");

const Brn ProviderRenderingControl::kChannelMaster("Master");
const Brn ProviderRenderingControl::kPresetNameFactoryDefaults("FactoryDefaults");

ProviderRenderingControl::ProviderRenderingControl(Net::DvDevice& aDevice, Environment& aEnv, IVolumeManager& aVolumeManager)
    : DvProviderUpnpOrgRenderingControl1(aDevice)
    , iLock("PVRC")
    , iVolume(aVolumeManager)
    , iVolumeCurrent(0)
    , iVolumeMax(aVolumeManager.VolumeMax())
    , iVolumeUnity(aVolumeManager.VolumeUnity())
    , iVolumeMilliDbPerStep(aVolumeManager.VolumeMilliDbPerStep())
    , iUserMute(aVolumeManager)
    , iMuted(true)
    , iModerationTimerStarted(false)
{
    ASSERT(aVolumeManager.VolumeStep() == 1); // RenderingControl service mandates a step of 1
    iModerationTimer = new Timer(aEnv, MakeFunctor(*this, &ProviderRenderingControl::ModerationTimerExpired), "ProviderRenderingControl");

    EnablePropertyLastChange();

    EnableActionListPresets();
    EnableActionSelectPreset();
    EnableActionGetMute();
    EnableActionSetMute();
    EnableActionGetVolume();
    EnableActionSetVolume();
    EnableActionGetVolumeDB();
    EnableActionSetVolumeDB();
    EnableActionGetVolumeDBRange();

    UpdateVolumeDb();
    UpdateLastChange(); // ensure iLastChange is set before aDevice could be enabled

    aVolumeManager.AddObserver(static_cast<IVolumeObserver&>(*this));
    aVolumeManager.AddObserver(static_cast<Media::IMuteObserver&>(*this));
}

ProviderRenderingControl::~ProviderRenderingControl()
{
    delete iModerationTimer;
}

void ProviderRenderingControl::ListPresets(IDvInvocation& aInvocation, TUint aInstanceID, IDvInvocationResponseString& aCurrentPresetNameList)
{
    if (aInstanceID != kInstanceId) {
        aInvocation.Error(kInvalidInstanceIdCode, kInvalidInstanceIdMsg);
    }
    aInvocation.StartResponse();
    aCurrentPresetNameList.Write(kPresetNameFactoryDefaults);
    aCurrentPresetNameList.WriteFlush();
    aInvocation.EndResponse();
}

void ProviderRenderingControl::SelectPreset(IDvInvocation& aInvocation, TUint aInstanceID, const Brx& aPresetName)
{
    if (aInstanceID != kInstanceId) {
        aInvocation.Error(kInvalidInstanceIdCode, kInvalidInstanceIdMsg);
    }
    if (aPresetName != kPresetNameFactoryDefaults) {
        aInvocation.Error(kInvalidPresetNameCode, KInvalidPresetNameMsg);
    }
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderRenderingControl::GetMute(IDvInvocation& aInvocation, TUint aInstanceID, const Brx& aChannel, IDvInvocationResponseBool& aCurrentMute)
{
    if (aInstanceID != kInstanceId) {
        aInvocation.Error(kInvalidInstanceIdCode, kInvalidInstanceIdMsg);
    }
    if (aChannel != kChannelMaster) {
        aInvocation.Error(kInvalidChannelCode, kInvalidChannelMsg);
    }
    aInvocation.StartResponse();
    {
        AutoMutex _(iLock);
        aCurrentMute.Write(iMuted);
    }
    aInvocation.EndResponse();
}

void ProviderRenderingControl::SetMute(IDvInvocation& aInvocation, TUint aInstanceID, const Brx& aChannel, TBool aDesiredMute)
{
    if (aInstanceID != kInstanceId) {
        aInvocation.Error(kInvalidInstanceIdCode, kInvalidInstanceIdMsg);
    }
    if (aChannel != kChannelMaster) {
        aInvocation.Error(kInvalidChannelCode, kInvalidChannelMsg);
    }
    try {
        if (aDesiredMute) {
            iUserMute.Mute();
        }
        else {
            iUserMute.Unmute();
        }
    }
    catch (MuteNotSupported&) {
        aInvocation.Error(kActionNotSupportedCode, kActionNotSupportedMsg);
    }
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderRenderingControl::GetVolume(IDvInvocation& aInvocation, TUint aInstanceID, const Brx& aChannel, IDvInvocationResponseUint& aCurrentVolume)
{
    if (aInstanceID != kInstanceId) {
        aInvocation.Error(kInvalidInstanceIdCode, kInvalidInstanceIdMsg);
    }
    if (aChannel != kChannelMaster) {
        aInvocation.Error(kInvalidChannelCode, kInvalidChannelMsg);
    }
    aInvocation.StartResponse();
    {
        AutoMutex _(iLock);
        aCurrentVolume.Write(iVolumeCurrent);
    }
    aInvocation.EndResponse();
}

void ProviderRenderingControl::SetVolume(IDvInvocation& aInvocation, TUint aInstanceID, const Brx& aChannel, TUint aDesiredVolume)
{
    if (aInstanceID != kInstanceId) {
        aInvocation.Error(kInvalidInstanceIdCode, kInvalidInstanceIdMsg);
    }
    if (aChannel != kChannelMaster) {
        aInvocation.Error(kInvalidChannelCode, kInvalidChannelMsg);
    }
    try {
        aDesiredVolume = (aDesiredVolume * iVolumeMax) / kVolumeReportedSteps;
        iVolume.SetVolume(aDesiredVolume);
    }
    catch (VolumeOutOfRange&) {
        aInvocation.Error(kInvalidVolumeCode, kInvalidVolumeMsg);
    }
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderRenderingControl::GetVolumeDB(IDvInvocation& aInvocation, TUint aInstanceID, const Brx& aChannel, IDvInvocationResponseInt& aCurrentVolume)
{
    if (aInstanceID != kInstanceId) {
        aInvocation.Error(kInvalidInstanceIdCode, kInvalidInstanceIdMsg);
    }
    if (aChannel != kChannelMaster) {
        aInvocation.Error(kInvalidChannelCode, kInvalidChannelMsg);
    }
    aInvocation.StartResponse();
    {
        AutoMutex _(iLock);
        aCurrentVolume.Write(iVolumeDb);
    }
    aInvocation.EndResponse();
}

void ProviderRenderingControl::SetVolumeDB(IDvInvocation& aInvocation, TUint aInstanceID, const Brx& aChannel, TInt aDesiredVolume)
{
    if (aInstanceID != kInstanceId) {
        aInvocation.Error(kInvalidInstanceIdCode, kInvalidInstanceIdMsg);
    }
    if (aChannel != kChannelMaster) {
        aInvocation.Error(kInvalidChannelCode, kInvalidChannelMsg);
    }
    // aDesiredVolume gives deviation from unity in units of 1/256 db
    const TUint vol = iVolumeUnity + (aDesiredVolume / 256);
    try {
        iVolume.SetVolume(vol);
    }
    catch (VolumeOutOfRange&) {
        aInvocation.Error(kInvalidVolumeCode, kInvalidVolumeMsg);
    }
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderRenderingControl::GetVolumeDBRange(IDvInvocation& aInvocation, TUint aInstanceID, const Brx& aChannel, IDvInvocationResponseInt& aMinValue, IDvInvocationResponseInt& aMaxValue)
{
    if (aInstanceID != kInstanceId) {
        aInvocation.Error(kInvalidInstanceIdCode, kInvalidInstanceIdMsg);
    }
    if (aChannel != kChannelMaster) {
        aInvocation.Error(kInvalidChannelCode, kInvalidChannelMsg);
    }
    aInvocation.StartResponse();
    TInt min = -1 * (TInt)iVolumeUnity;
    min *= (256 * iVolumeMilliDbPerStep) / 1024;
    const TInt max = ((iVolumeMax - iVolumeUnity) * 256 * iVolumeMilliDbPerStep) / 1024;
    aMinValue.Write(min);
    aMaxValue.Write(max);
    aInvocation.EndResponse();
}

void ProviderRenderingControl::VolumeChanged(TUint aVolume)
{
    AutoMutex _(iLock);
    iVolumeCurrent = (aVolume * kVolumeReportedSteps) / iVolumeMax;
    UpdateVolumeDb();
    ScheduleUpdate();
}

void ProviderRenderingControl::MuteChanged(TBool aValue)
{
    AutoMutex _(iLock);
    iMuted = aValue;
    ScheduleUpdate();
}

void ProviderRenderingControl::UpdateVolumeDb()
{
    iVolumeDb = iVolumeCurrent - iVolumeUnity;
    iVolumeDb *= (256 * iVolumeMilliDbPerStep) / 1024;
}

void ProviderRenderingControl::ScheduleUpdate()
{
    // must be called with iLock held
    if (!iModerationTimerStarted) {
        iModerationTimer->FireIn(kEventModerationMs);
        iModerationTimerStarted = true;
    }
}

void ProviderRenderingControl::ModerationTimerExpired()
{
    iLock.Wait();
    iModerationTimerStarted = false;
    UpdateLastChange();
    iLock.Signal();
}

void ProviderRenderingControl::UpdateLastChange()
{
    // Header
    iLastChange.Replace("<Event xmlns=\"urn:schemas-upnp-org:metadata-1-0/RCS/\">\n");
    iLastChange.Append("    <InstanceID val=\"");
    Ascii::AppendDec(iLastChange, kInstanceId);
    iLastChange.Append("\">\n");

    // PresetNameList
    iLastChange.Append("        <PresetNameList val=\"");
    iLastChange.Append(kPresetNameFactoryDefaults);
    iLastChange.Append("\"/>\n");

    // Mute
    iLastChange.Append("        <Mute channel= \"");
    iLastChange.Append(kChannelMaster);
    iLastChange.Append("\" val=\"");
    AppendInt(iMuted? 1 : 0);
    iLastChange.Append("\"/>\n");

    // Volume
    iLastChange.Append("        <Volume channel= \"");
    iLastChange.Append(kChannelMaster);
    iLastChange.Append("\" val=\"");
    AppendInt(iVolumeCurrent);
    iLastChange.Append("\"/>\n");

    // VolumeDB
    iLastChange.Append("        <VolumeDB val=\"");
    AppendInt(iVolumeDb);
    iLastChange.Append("\"/>\n");

    // End
    iLastChange.Append("    </InstanceID>\n</Event>\n");

    (void)SetPropertyLastChange(iLastChange);
}

void ProviderRenderingControl::AppendInt(TInt aValue)
{
    Bws<Ascii::kMaxIntStringBytes> intBuf;
    (void)Ascii::AppendDec(intBuf, aValue);
    iLastChange.Append(intBuf);
}
