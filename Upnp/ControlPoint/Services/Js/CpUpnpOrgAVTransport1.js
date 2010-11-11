 

/**
 * Proxy for upnp.org:AVTransport:1
 */

var ServiceAVTransport = function(aUdn){	
	this.iUrl = window.location.protocol + "//" + window.location.host + "/" + aUdn + "/upnp.org-AVTransport-1/control";
	this.iDomain = "upnp.org";
	if (this.iDomain == "upnp.org") {
		this.iDomain = "schemas.upnp.org";
    }
	this.iDomain = this.iDomain.replace(/\./,"-");
	this.iType = "AVTransport";
	this.iVersion = "1";
	this.iServiceName = "upnp.org-AVTransport-1";
	this.iSubscriptionId = "";
	this.iUdn = aUdn;
	
	this.iVariables = {};
			this.iVariables["TransportState"] = new ServiceVariable("TransportState");
		this.iVariables["TransportStatus"] = new ServiceVariable("TransportStatus");
		this.iVariables["PlaybackStorageMedium"] = new ServiceVariable("PlaybackStorageMedium");
		this.iVariables["RecordStorageMedium"] = new ServiceVariable("RecordStorageMedium");
		this.iVariables["PossiblePlaybackStorageMedia"] = new ServiceVariable("PossiblePlaybackStorageMedia");
		this.iVariables["PossibleRecordStorageMedia"] = new ServiceVariable("PossibleRecordStorageMedia");
		this.iVariables["CurrentPlayMode"] = new ServiceVariable("CurrentPlayMode");
		this.iVariables["TransportPlaySpeed"] = new ServiceVariable("TransportPlaySpeed");
		this.iVariables["RecordMediumWriteStatus"] = new ServiceVariable("RecordMediumWriteStatus");
		this.iVariables["CurrentRecordQualityMode"] = new ServiceVariable("CurrentRecordQualityMode");
		this.iVariables["PossibleRecordQualityModes"] = new ServiceVariable("PossibleRecordQualityModes");
		this.iVariables["NumberOfTracks"] = new ServiceVariable("NumberOfTracks");
		this.iVariables["CurrentTrack"] = new ServiceVariable("CurrentTrack");
		this.iVariables["CurrentTrackDuration"] = new ServiceVariable("CurrentTrackDuration");
		this.iVariables["CurrentMediaDuration"] = new ServiceVariable("CurrentMediaDuration");
		this.iVariables["CurrentTrackMetaData"] = new ServiceVariable("CurrentTrackMetaData");
		this.iVariables["CurrentTrackURI"] = new ServiceVariable("CurrentTrackURI");
		this.iVariables["AVTransportURI"] = new ServiceVariable("AVTransportURI");
		this.iVariables["AVTransportURIMetaData"] = new ServiceVariable("AVTransportURIMetaData");
		this.iVariables["NextAVTransportURI"] = new ServiceVariable("NextAVTransportURI");
		this.iVariables["NextAVTransportURIMetaData"] = new ServiceVariable("NextAVTransportURIMetaData");
		this.iVariables["RelativeTimePosition"] = new ServiceVariable("RelativeTimePosition");
		this.iVariables["AbsoluteTimePosition"] = new ServiceVariable("AbsoluteTimePosition");
		this.iVariables["RelativeCounterPosition"] = new ServiceVariable("RelativeCounterPosition");
		this.iVariables["AbsoluteCounterPosition"] = new ServiceVariable("AbsoluteCounterPosition");
		this.iVariables["CurrentTransportActions"] = new ServiceVariable("CurrentTransportActions");
		this.iVariables["LastChange"] = new ServiceVariable("LastChange");
		this.iVariables["SeekMode"] = new ServiceVariable("SeekMode");
		this.iVariables["SeekTarget"] = new ServiceVariable("SeekTarget");
		this.iVariables["InstanceID"] = new ServiceVariable("InstanceID");
}

ServiceAVTransport.kTransportStateStopped = "STOPPED";
ServiceAVTransport.kTransportStatePlaying = "PLAYING";
ServiceAVTransport.kTransportStatusOk = "OK";
ServiceAVTransport.kTransportStatusErrorOccurred = "ERROR_OCCURRED";
ServiceAVTransport.kCurrentPlayModeNormal = "NORMAL";
ServiceAVTransport.kTransportPlaySpeed1 = "1";
ServiceAVTransport.kSeekModeTrackNr = "TRACK_NR";

ServiceAVTransport.prototype.TransportState_Changed = function (aStateChangedFunction) {
    this.Variables().TransportState.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceAVTransport.prototype.TransportStatus_Changed = function (aStateChangedFunction) {
    this.Variables().TransportStatus.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceAVTransport.prototype.PlaybackStorageMedium_Changed = function (aStateChangedFunction) {
    this.Variables().PlaybackStorageMedium.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceAVTransport.prototype.RecordStorageMedium_Changed = function (aStateChangedFunction) {
    this.Variables().RecordStorageMedium.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceAVTransport.prototype.PossiblePlaybackStorageMedia_Changed = function (aStateChangedFunction) {
    this.Variables().PossiblePlaybackStorageMedia.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceAVTransport.prototype.PossibleRecordStorageMedia_Changed = function (aStateChangedFunction) {
    this.Variables().PossibleRecordStorageMedia.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceAVTransport.prototype.CurrentPlayMode_Changed = function (aStateChangedFunction) {
    this.Variables().CurrentPlayMode.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceAVTransport.prototype.TransportPlaySpeed_Changed = function (aStateChangedFunction) {
    this.Variables().TransportPlaySpeed.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceAVTransport.prototype.RecordMediumWriteStatus_Changed = function (aStateChangedFunction) {
    this.Variables().RecordMediumWriteStatus.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceAVTransport.prototype.CurrentRecordQualityMode_Changed = function (aStateChangedFunction) {
    this.Variables().CurrentRecordQualityMode.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceAVTransport.prototype.PossibleRecordQualityModes_Changed = function (aStateChangedFunction) {
    this.Variables().PossibleRecordQualityModes.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceAVTransport.prototype.NumberOfTracks_Changed = function (aStateChangedFunction) {
    this.Variables().NumberOfTracks.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServiceAVTransport.prototype.CurrentTrack_Changed = function (aStateChangedFunction) {
    this.Variables().CurrentTrack.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServiceAVTransport.prototype.CurrentTrackDuration_Changed = function (aStateChangedFunction) {
    this.Variables().CurrentTrackDuration.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceAVTransport.prototype.CurrentMediaDuration_Changed = function (aStateChangedFunction) {
    this.Variables().CurrentMediaDuration.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceAVTransport.prototype.CurrentTrackMetaData_Changed = function (aStateChangedFunction) {
    this.Variables().CurrentTrackMetaData.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceAVTransport.prototype.CurrentTrackURI_Changed = function (aStateChangedFunction) {
    this.Variables().CurrentTrackURI.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceAVTransport.prototype.AVTransportURI_Changed = function (aStateChangedFunction) {
    this.Variables().AVTransportURI.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceAVTransport.prototype.AVTransportURIMetaData_Changed = function (aStateChangedFunction) {
    this.Variables().AVTransportURIMetaData.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceAVTransport.prototype.NextAVTransportURI_Changed = function (aStateChangedFunction) {
    this.Variables().NextAVTransportURI.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceAVTransport.prototype.NextAVTransportURIMetaData_Changed = function (aStateChangedFunction) {
    this.Variables().NextAVTransportURIMetaData.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceAVTransport.prototype.RelativeTimePosition_Changed = function (aStateChangedFunction) {
    this.Variables().RelativeTimePosition.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceAVTransport.prototype.AbsoluteTimePosition_Changed = function (aStateChangedFunction) {
    this.Variables().AbsoluteTimePosition.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceAVTransport.prototype.RelativeCounterPosition_Changed = function (aStateChangedFunction) {
    this.Variables().RelativeCounterPosition.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServiceAVTransport.prototype.AbsoluteCounterPosition_Changed = function (aStateChangedFunction) {
    this.Variables().AbsoluteCounterPosition.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServiceAVTransport.prototype.CurrentTransportActions_Changed = function (aStateChangedFunction) {
    this.Variables().CurrentTransportActions.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceAVTransport.prototype.LastChange_Changed = function (aStateChangedFunction) {
    this.Variables().LastChange.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceAVTransport.prototype.SeekMode_Changed = function (aStateChangedFunction) {
    this.Variables().SeekMode.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceAVTransport.prototype.SeekTarget_Changed = function (aStateChangedFunction) {
    this.Variables().SeekTarget.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceAVTransport.prototype.InstanceID_Changed = function (aStateChangedFunction) {
    this.Variables().InstanceID.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}

ServiceAVTransport.prototype.ServiceName = function(){
	return this.iServiceName;
}

ServiceAVTransport.prototype.Variables = function(){
	return this.iVariables;
}

ServiceAVTransport.prototype.SubscriptionId = function () {
    return this.iSubscriptionId;
}

ServiceAVTransport.prototype.SetSubscriptionId = function (value) {
    this.iSubscriptionId = value;
}

ServiceAVTransport.prototype.Udn = function () {
    return this.iUdn;
}

ServiceAVTransport.prototype.VariableNames = function(){
	var result = [];
	for (var variable in this.iVariables){
		if (this.iVariables.hasOwnProperty(variable)){
			result[result.length] = variable;
		}
	}
	return result;
}

ServiceAVTransport.prototype.Subscribe = function () {
    SubscriptionManager.AddService(this);
}

ServiceAVTransport.prototype.Unsubscribe = function () {
    SubscriptionManager.RemoveService(this.SubscriptionId());
}


ServiceAVTransport.prototype.SetAVTransportURI = function(InstanceID, CurrentURI, CurrentURIMetaData, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetAVTransportURI", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("InstanceID", InstanceID);
    request.WriteStringParameter("CurrentURI", CurrentURI);
    request.WriteStringParameter("CurrentURIMetaData", CurrentURIMetaData);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceAVTransport.prototype.SetNextAVTransportURI = function(InstanceID, NextURI, NextURIMetaData, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetNextAVTransportURI", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("InstanceID", InstanceID);
    request.WriteStringParameter("NextURI", NextURI);
    request.WriteStringParameter("NextURIMetaData", NextURIMetaData);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceAVTransport.prototype.GetMediaInfo = function(InstanceID, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetMediaInfo", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("InstanceID", InstanceID);
    request.Send(function(result){
		result["NrTracks"] = SoapRequest.ReadIntParameter(result["NrTracks"]);	
		result["MediaDuration"] = SoapRequest.ReadStringParameter(result["MediaDuration"]);	
		result["CurrentURI"] = SoapRequest.ReadStringParameter(result["CurrentURI"]);	
		result["CurrentURIMetaData"] = SoapRequest.ReadStringParameter(result["CurrentURIMetaData"]);	
		result["NextURI"] = SoapRequest.ReadStringParameter(result["NextURI"]);	
		result["NextURIMetaData"] = SoapRequest.ReadStringParameter(result["NextURIMetaData"]);	
		result["PlayMedium"] = SoapRequest.ReadStringParameter(result["PlayMedium"]);	
		result["RecordMedium"] = SoapRequest.ReadStringParameter(result["RecordMedium"]);	
		result["WriteStatus"] = SoapRequest.ReadStringParameter(result["WriteStatus"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceAVTransport.prototype.GetTransportInfo = function(InstanceID, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetTransportInfo", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("InstanceID", InstanceID);
    request.Send(function(result){
		result["CurrentTransportState"] = SoapRequest.ReadStringParameter(result["CurrentTransportState"]);	
		result["CurrentTransportStatus"] = SoapRequest.ReadStringParameter(result["CurrentTransportStatus"]);	
		result["CurrentSpeed"] = SoapRequest.ReadStringParameter(result["CurrentSpeed"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceAVTransport.prototype.GetPositionInfo = function(InstanceID, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetPositionInfo", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("InstanceID", InstanceID);
    request.Send(function(result){
		result["Track"] = SoapRequest.ReadIntParameter(result["Track"]);	
		result["TrackDuration"] = SoapRequest.ReadStringParameter(result["TrackDuration"]);	
		result["TrackMetaData"] = SoapRequest.ReadStringParameter(result["TrackMetaData"]);	
		result["TrackURI"] = SoapRequest.ReadStringParameter(result["TrackURI"]);	
		result["RelTime"] = SoapRequest.ReadStringParameter(result["RelTime"]);	
		result["AbsTime"] = SoapRequest.ReadStringParameter(result["AbsTime"]);	
		result["RelCount"] = SoapRequest.ReadIntParameter(result["RelCount"]);	
		result["AbsCount"] = SoapRequest.ReadIntParameter(result["AbsCount"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceAVTransport.prototype.GetDeviceCapabilities = function(InstanceID, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetDeviceCapabilities", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("InstanceID", InstanceID);
    request.Send(function(result){
		result["PlayMedia"] = SoapRequest.ReadStringParameter(result["PlayMedia"]);	
		result["RecMedia"] = SoapRequest.ReadStringParameter(result["RecMedia"]);	
		result["RecQualityModes"] = SoapRequest.ReadStringParameter(result["RecQualityModes"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceAVTransport.prototype.GetTransportSettings = function(InstanceID, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetTransportSettings", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("InstanceID", InstanceID);
    request.Send(function(result){
		result["PlayMode"] = SoapRequest.ReadStringParameter(result["PlayMode"]);	
		result["RecQualityMode"] = SoapRequest.ReadStringParameter(result["RecQualityMode"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceAVTransport.prototype.Stop = function(InstanceID, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("Stop", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("InstanceID", InstanceID);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceAVTransport.prototype.Play = function(InstanceID, Speed, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("Play", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("InstanceID", InstanceID);
    request.WriteStringParameter("Speed", Speed);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceAVTransport.prototype.Pause = function(InstanceID, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("Pause", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("InstanceID", InstanceID);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceAVTransport.prototype.Record = function(InstanceID, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("Record", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("InstanceID", InstanceID);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceAVTransport.prototype.Seek = function(InstanceID, Unit, Target, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("Seek", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("InstanceID", InstanceID);
    request.WriteStringParameter("Unit", Unit);
    request.WriteStringParameter("Target", Target);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceAVTransport.prototype.Next = function(InstanceID, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("Next", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("InstanceID", InstanceID);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceAVTransport.prototype.Previous = function(InstanceID, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("Previous", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("InstanceID", InstanceID);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceAVTransport.prototype.SetPlayMode = function(InstanceID, NewPlayMode, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetPlayMode", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("InstanceID", InstanceID);
    request.WriteStringParameter("NewPlayMode", NewPlayMode);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceAVTransport.prototype.SetRecordQualityMode = function(InstanceID, NewRecordQualityMode, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetRecordQualityMode", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("InstanceID", InstanceID);
    request.WriteStringParameter("NewRecordQualityMode", NewRecordQualityMode);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceAVTransport.prototype.GetCurrentTransportActions = function(InstanceID, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetCurrentTransportActions", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("InstanceID", InstanceID);
    request.Send(function(result){
		result["Actions"] = SoapRequest.ReadStringParameter(result["Actions"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}



