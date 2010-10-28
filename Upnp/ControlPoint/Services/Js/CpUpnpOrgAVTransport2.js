 

/**
 * Proxy for upnp.org:AVTransport:2
 */

var ServiceAVTransport = function(aId){	
	this.iUrl = window.location.protocol + "//" + window.location.host + "/" + aId + "/AVTransport/control";
	this.iDomain = "upnp.org";
	if (this.iDomain == "upnp.org") {
		this.iDomain = "schemas.upnp.org";
    }
	this.iDomain = this.iDomain.replace(/\./,"-");
	this.iType = "AVTransport";
	this.iVersion = "2";
	
	this.iVariables = {};
			this.iVariables["TransportState"] = new ServiceVariable("TransportState");
		this.iVariables["TransportStatus"] = new ServiceVariable("TransportStatus");
		this.iVariables["CurrentMediaCategory"] = new ServiceVariable("CurrentMediaCategory");
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
		this.iVariables["DRMState"] = new ServiceVariable("DRMState");
		this.iVariables["SeekMode"] = new ServiceVariable("SeekMode");
		this.iVariables["SeekTarget"] = new ServiceVariable("SeekTarget");
		this.iVariables["InstanceID"] = new ServiceVariable("InstanceID");
		this.iVariables["DeviceUDN"] = new ServiceVariable("DeviceUDN");
		this.iVariables["ServiceType"] = new ServiceVariable("ServiceType");
		this.iVariables["ServiceID"] = new ServiceVariable("ServiceID");
		this.iVariables["StateVariableValuePairs"] = new ServiceVariable("StateVariableValuePairs");
		this.iVariables["StateVariableList"] = new ServiceVariable("StateVariableList");
}

ServiceAVTransport.kTransportStateStopped = "STOPPED";
ServiceAVTransport.kTransportStatePlaying = "PLAYING";
ServiceAVTransport.kTransportStatusOk = "OK";
ServiceAVTransport.kTransportStatusErrorOccurred = "ERROR_OCCURRED";
ServiceAVTransport.kCurrentMediaCategoryNoMedia = "NO_MEDIA";
ServiceAVTransport.kCurrentMediaCategoryTrackAware = "TRACK_AWARE";
ServiceAVTransport.kCurrentMediaCategoryTrackUnaware = "TRACK_UNAWARE";
ServiceAVTransport.kCurrentPlayModeNormal = "NORMAL";
ServiceAVTransport.kTransportPlaySpeed1 = "1";
ServiceAVTransport.kDRMStateOk = "OK";
ServiceAVTransport.kSeekModeTrackNr = "TRACK_NR";

ServiceAVTransport.prototype.ServiceName = function(){
	return this.iType;
}

ServiceAVTransport.prototype.Variables = function(){
	return this.iVariables;
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
		result["NrTracks"] = request.ReadIntParameter(result["NrTracks"]);	
		result["MediaDuration"] = request.ReadStringParameter(result["MediaDuration"]);	
		result["CurrentURI"] = request.ReadStringParameter(result["CurrentURI"]);	
		result["CurrentURIMetaData"] = request.ReadStringParameter(result["CurrentURIMetaData"]);	
		result["NextURI"] = request.ReadStringParameter(result["NextURI"]);	
		result["NextURIMetaData"] = request.ReadStringParameter(result["NextURIMetaData"]);	
		result["PlayMedium"] = request.ReadStringParameter(result["PlayMedium"]);	
		result["RecordMedium"] = request.ReadStringParameter(result["RecordMedium"]);	
		result["WriteStatus"] = request.ReadStringParameter(result["WriteStatus"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceAVTransport.prototype.GetMediaInfo_Ext = function(InstanceID, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetMediaInfo_Ext", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("InstanceID", InstanceID);
    request.Send(function(result){
		result["CurrentType"] = request.ReadStringParameter(result["CurrentType"]);	
		result["NrTracks"] = request.ReadIntParameter(result["NrTracks"]);	
		result["MediaDuration"] = request.ReadStringParameter(result["MediaDuration"]);	
		result["CurrentURI"] = request.ReadStringParameter(result["CurrentURI"]);	
		result["CurrentURIMetaData"] = request.ReadStringParameter(result["CurrentURIMetaData"]);	
		result["NextURI"] = request.ReadStringParameter(result["NextURI"]);	
		result["NextURIMetaData"] = request.ReadStringParameter(result["NextURIMetaData"]);	
		result["PlayMedium"] = request.ReadStringParameter(result["PlayMedium"]);	
		result["RecordMedium"] = request.ReadStringParameter(result["RecordMedium"]);	
		result["WriteStatus"] = request.ReadStringParameter(result["WriteStatus"]);	
	
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
		result["CurrentTransportState"] = request.ReadStringParameter(result["CurrentTransportState"]);	
		result["CurrentTransportStatus"] = request.ReadStringParameter(result["CurrentTransportStatus"]);	
		result["CurrentSpeed"] = request.ReadStringParameter(result["CurrentSpeed"]);	
	
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
		result["Track"] = request.ReadIntParameter(result["Track"]);	
		result["TrackDuration"] = request.ReadStringParameter(result["TrackDuration"]);	
		result["TrackMetaData"] = request.ReadStringParameter(result["TrackMetaData"]);	
		result["TrackURI"] = request.ReadStringParameter(result["TrackURI"]);	
		result["RelTime"] = request.ReadStringParameter(result["RelTime"]);	
		result["AbsTime"] = request.ReadStringParameter(result["AbsTime"]);	
		result["RelCount"] = request.ReadIntParameter(result["RelCount"]);	
		result["AbsCount"] = request.ReadIntParameter(result["AbsCount"]);	
	
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
		result["PlayMedia"] = request.ReadStringParameter(result["PlayMedia"]);	
		result["RecMedia"] = request.ReadStringParameter(result["RecMedia"]);	
		result["RecQualityModes"] = request.ReadStringParameter(result["RecQualityModes"]);	
	
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
		result["PlayMode"] = request.ReadStringParameter(result["PlayMode"]);	
		result["RecQualityMode"] = request.ReadStringParameter(result["RecQualityMode"]);	
	
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
		result["Actions"] = request.ReadStringParameter(result["Actions"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceAVTransport.prototype.GetDRMState = function(InstanceID, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetDRMState", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("InstanceID", InstanceID);
    request.Send(function(result){
		result["CurrentDRMState"] = request.ReadStringParameter(result["CurrentDRMState"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceAVTransport.prototype.GetStateVariables = function(InstanceID, StateVariableList, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetStateVariables", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("InstanceID", InstanceID);
    request.WriteStringParameter("StateVariableList", StateVariableList);
    request.Send(function(result){
		result["StateVariableValuePairs"] = request.ReadStringParameter(result["StateVariableValuePairs"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceAVTransport.prototype.SetStateVariables = function(InstanceID, AVTransportUDN, ServiceType, ServiceId, StateVariableValuePairs, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetStateVariables", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("InstanceID", InstanceID);
    request.WriteStringParameter("AVTransportUDN", AVTransportUDN);
    request.WriteStringParameter("ServiceType", ServiceType);
    request.WriteStringParameter("ServiceId", ServiceId);
    request.WriteStringParameter("StateVariableValuePairs", StateVariableValuePairs);
    request.Send(function(result){
		result["StateVariableList"] = request.ReadStringParameter(result["StateVariableList"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    


