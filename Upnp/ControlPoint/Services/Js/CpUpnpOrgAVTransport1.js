 

/**
* Service Proxy for upnp.org:AVTransport:1
* @module Zapp
* @class AVTransport
*/

var ServiceAVTransport = function(udn){	

	this.url = window.location.protocol + "//" + window.location.host + "/" + udn + "/upnp.org-AVTransport-1/control";  // upnp control url
	this.domain = "upnp.org";
	if (this.domain == "upnp.org") {
		this.domain = "schemas.upnp.org";
    }
	this.domain = this.domain.replace(/\./,"-");
	this.type = "AVTransport";
	this.version = "1";
	this.serviceName = "upnp.org-AVTransport-1";
	this.subscriptionId = "";  // Subscription identifier unique to each Subscription Manager 
	this.udn = udn;   // device name
	
	// Collection of service properties
	this.serviceProperties = {};
	this.serviceProperties["TransportState"] = new Zapp.ServiceProperty("TransportState");
	this.serviceProperties["TransportStatus"] = new Zapp.ServiceProperty("TransportStatus");
	this.serviceProperties["PlaybackStorageMedium"] = new Zapp.ServiceProperty("PlaybackStorageMedium");
	this.serviceProperties["RecordStorageMedium"] = new Zapp.ServiceProperty("RecordStorageMedium");
	this.serviceProperties["PossiblePlaybackStorageMedia"] = new Zapp.ServiceProperty("PossiblePlaybackStorageMedia");
	this.serviceProperties["PossibleRecordStorageMedia"] = new Zapp.ServiceProperty("PossibleRecordStorageMedia");
	this.serviceProperties["CurrentPlayMode"] = new Zapp.ServiceProperty("CurrentPlayMode");
	this.serviceProperties["TransportPlaySpeed"] = new Zapp.ServiceProperty("TransportPlaySpeed");
	this.serviceProperties["RecordMediumWriteStatus"] = new Zapp.ServiceProperty("RecordMediumWriteStatus");
	this.serviceProperties["CurrentRecordQualityMode"] = new Zapp.ServiceProperty("CurrentRecordQualityMode");
	this.serviceProperties["PossibleRecordQualityModes"] = new Zapp.ServiceProperty("PossibleRecordQualityModes");
	this.serviceProperties["NumberOfTracks"] = new Zapp.ServiceProperty("NumberOfTracks");
	this.serviceProperties["CurrentTrack"] = new Zapp.ServiceProperty("CurrentTrack");
	this.serviceProperties["CurrentTrackDuration"] = new Zapp.ServiceProperty("CurrentTrackDuration");
	this.serviceProperties["CurrentMediaDuration"] = new Zapp.ServiceProperty("CurrentMediaDuration");
	this.serviceProperties["CurrentTrackMetaData"] = new Zapp.ServiceProperty("CurrentTrackMetaData");
	this.serviceProperties["CurrentTrackURI"] = new Zapp.ServiceProperty("CurrentTrackURI");
	this.serviceProperties["AVTransportURI"] = new Zapp.ServiceProperty("AVTransportURI");
	this.serviceProperties["AVTransportURIMetaData"] = new Zapp.ServiceProperty("AVTransportURIMetaData");
	this.serviceProperties["NextAVTransportURI"] = new Zapp.ServiceProperty("NextAVTransportURI");
	this.serviceProperties["NextAVTransportURIMetaData"] = new Zapp.ServiceProperty("NextAVTransportURIMetaData");
	this.serviceProperties["RelativeTimePosition"] = new Zapp.ServiceProperty("RelativeTimePosition");
	this.serviceProperties["AbsoluteTimePosition"] = new Zapp.ServiceProperty("AbsoluteTimePosition");
	this.serviceProperties["RelativeCounterPosition"] = new Zapp.ServiceProperty("RelativeCounterPosition");
	this.serviceProperties["AbsoluteCounterPosition"] = new Zapp.ServiceProperty("AbsoluteCounterPosition");
	this.serviceProperties["CurrentTransportActions"] = new Zapp.ServiceProperty("CurrentTransportActions");
	this.serviceProperties["LastChange"] = new Zapp.ServiceProperty("LastChange");
	this.serviceProperties["SeekMode"] = new Zapp.ServiceProperty("SeekMode");
	this.serviceProperties["SeekTarget"] = new Zapp.ServiceProperty("SeekTarget");
	this.serviceProperties["InstanceID"] = new Zapp.ServiceProperty("InstanceID");
}

ServiceAVTransport.kTransportStateStopped = "STOPPED";
ServiceAVTransport.kTransportStatePlaying = "PLAYING";
ServiceAVTransport.kTransportStatusOk = "OK";
ServiceAVTransport.kTransportStatusErrorOccurred = "ERROR_OCCURRED";
ServiceAVTransport.kCurrentPlayModeNormal = "NORMAL";
ServiceAVTransport.kTransportPlaySpeed1 = "1";
ServiceAVTransport.kSeekModeTrackNr = "TRACK_NR";


/**
* Subscribes the service to the subscription manager to listen for property change events
* @method Subscribe
* @param {Function} serviceAddedFunction The function that executes once the subscription is successful
*/
ServiceAVTransport.prototype.subscribe = function (serviceAddedFunction) {
    Zapp.SubscriptionManager.addService(this,serviceAddedFunction);
}


/**
* Unsubscribes the service from the subscription manager to stop listening for property change events
* @method Unsubscribe
*/
ServiceAVTransport.prototype.unsubscribe = function () {
    Zapp.SubscriptionManager.removeService(this.subscriptionId);
}




/**
* Adds a listener to handle "TransportState" property change events
* @method TransportState_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceAVTransport.prototype.TransportState_Changed = function (stateChangedFunction) {
    this.serviceProperties.TransportState.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* Adds a listener to handle "TransportStatus" property change events
* @method TransportStatus_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceAVTransport.prototype.TransportStatus_Changed = function (stateChangedFunction) {
    this.serviceProperties.TransportStatus.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* Adds a listener to handle "PlaybackStorageMedium" property change events
* @method PlaybackStorageMedium_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceAVTransport.prototype.PlaybackStorageMedium_Changed = function (stateChangedFunction) {
    this.serviceProperties.PlaybackStorageMedium.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* Adds a listener to handle "RecordStorageMedium" property change events
* @method RecordStorageMedium_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceAVTransport.prototype.RecordStorageMedium_Changed = function (stateChangedFunction) {
    this.serviceProperties.RecordStorageMedium.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* Adds a listener to handle "PossiblePlaybackStorageMedia" property change events
* @method PossiblePlaybackStorageMedia_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceAVTransport.prototype.PossiblePlaybackStorageMedia_Changed = function (stateChangedFunction) {
    this.serviceProperties.PossiblePlaybackStorageMedia.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* Adds a listener to handle "PossibleRecordStorageMedia" property change events
* @method PossibleRecordStorageMedia_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceAVTransport.prototype.PossibleRecordStorageMedia_Changed = function (stateChangedFunction) {
    this.serviceProperties.PossibleRecordStorageMedia.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* Adds a listener to handle "CurrentPlayMode" property change events
* @method CurrentPlayMode_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceAVTransport.prototype.CurrentPlayMode_Changed = function (stateChangedFunction) {
    this.serviceProperties.CurrentPlayMode.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* Adds a listener to handle "TransportPlaySpeed" property change events
* @method TransportPlaySpeed_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceAVTransport.prototype.TransportPlaySpeed_Changed = function (stateChangedFunction) {
    this.serviceProperties.TransportPlaySpeed.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* Adds a listener to handle "RecordMediumWriteStatus" property change events
* @method RecordMediumWriteStatus_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceAVTransport.prototype.RecordMediumWriteStatus_Changed = function (stateChangedFunction) {
    this.serviceProperties.RecordMediumWriteStatus.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* Adds a listener to handle "CurrentRecordQualityMode" property change events
* @method CurrentRecordQualityMode_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceAVTransport.prototype.CurrentRecordQualityMode_Changed = function (stateChangedFunction) {
    this.serviceProperties.CurrentRecordQualityMode.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* Adds a listener to handle "PossibleRecordQualityModes" property change events
* @method PossibleRecordQualityModes_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceAVTransport.prototype.PossibleRecordQualityModes_Changed = function (stateChangedFunction) {
    this.serviceProperties.PossibleRecordQualityModes.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* Adds a listener to handle "NumberOfTracks" property change events
* @method NumberOfTracks_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceAVTransport.prototype.NumberOfTracks_Changed = function (stateChangedFunction) {
    this.serviceProperties.NumberOfTracks.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "CurrentTrack" property change events
* @method CurrentTrack_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceAVTransport.prototype.CurrentTrack_Changed = function (stateChangedFunction) {
    this.serviceProperties.CurrentTrack.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "CurrentTrackDuration" property change events
* @method CurrentTrackDuration_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceAVTransport.prototype.CurrentTrackDuration_Changed = function (stateChangedFunction) {
    this.serviceProperties.CurrentTrackDuration.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* Adds a listener to handle "CurrentMediaDuration" property change events
* @method CurrentMediaDuration_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceAVTransport.prototype.CurrentMediaDuration_Changed = function (stateChangedFunction) {
    this.serviceProperties.CurrentMediaDuration.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* Adds a listener to handle "CurrentTrackMetaData" property change events
* @method CurrentTrackMetaData_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceAVTransport.prototype.CurrentTrackMetaData_Changed = function (stateChangedFunction) {
    this.serviceProperties.CurrentTrackMetaData.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* Adds a listener to handle "CurrentTrackURI" property change events
* @method CurrentTrackURI_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceAVTransport.prototype.CurrentTrackURI_Changed = function (stateChangedFunction) {
    this.serviceProperties.CurrentTrackURI.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* Adds a listener to handle "AVTransportURI" property change events
* @method AVTransportURI_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceAVTransport.prototype.AVTransportURI_Changed = function (stateChangedFunction) {
    this.serviceProperties.AVTransportURI.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* Adds a listener to handle "AVTransportURIMetaData" property change events
* @method AVTransportURIMetaData_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceAVTransport.prototype.AVTransportURIMetaData_Changed = function (stateChangedFunction) {
    this.serviceProperties.AVTransportURIMetaData.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* Adds a listener to handle "NextAVTransportURI" property change events
* @method NextAVTransportURI_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceAVTransport.prototype.NextAVTransportURI_Changed = function (stateChangedFunction) {
    this.serviceProperties.NextAVTransportURI.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* Adds a listener to handle "NextAVTransportURIMetaData" property change events
* @method NextAVTransportURIMetaData_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceAVTransport.prototype.NextAVTransportURIMetaData_Changed = function (stateChangedFunction) {
    this.serviceProperties.NextAVTransportURIMetaData.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* Adds a listener to handle "RelativeTimePosition" property change events
* @method RelativeTimePosition_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceAVTransport.prototype.RelativeTimePosition_Changed = function (stateChangedFunction) {
    this.serviceProperties.RelativeTimePosition.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* Adds a listener to handle "AbsoluteTimePosition" property change events
* @method AbsoluteTimePosition_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceAVTransport.prototype.AbsoluteTimePosition_Changed = function (stateChangedFunction) {
    this.serviceProperties.AbsoluteTimePosition.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* Adds a listener to handle "RelativeCounterPosition" property change events
* @method RelativeCounterPosition_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceAVTransport.prototype.RelativeCounterPosition_Changed = function (stateChangedFunction) {
    this.serviceProperties.RelativeCounterPosition.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "AbsoluteCounterPosition" property change events
* @method AbsoluteCounterPosition_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceAVTransport.prototype.AbsoluteCounterPosition_Changed = function (stateChangedFunction) {
    this.serviceProperties.AbsoluteCounterPosition.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "CurrentTransportActions" property change events
* @method CurrentTransportActions_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceAVTransport.prototype.CurrentTransportActions_Changed = function (stateChangedFunction) {
    this.serviceProperties.CurrentTransportActions.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* Adds a listener to handle "LastChange" property change events
* @method LastChange_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceAVTransport.prototype.LastChange_Changed = function (stateChangedFunction) {
    this.serviceProperties.LastChange.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* Adds a listener to handle "SeekMode" property change events
* @method SeekMode_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceAVTransport.prototype.SeekMode_Changed = function (stateChangedFunction) {
    this.serviceProperties.SeekMode.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* Adds a listener to handle "SeekTarget" property change events
* @method SeekTarget_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceAVTransport.prototype.SeekTarget_Changed = function (stateChangedFunction) {
    this.serviceProperties.SeekTarget.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* Adds a listener to handle "InstanceID" property change events
* @method InstanceID_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceAVTransport.prototype.InstanceID_Changed = function (stateChangedFunction) {
    this.serviceProperties.InstanceID.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* A service action to SetAVTransportURI
* @method SetAVTransportURI
* @param {Int} InstanceID An action parameter
* @param {String} CurrentURI An action parameter
* @param {String} CurrentURIMetaData An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceAVTransport.prototype.SetAVTransportURI = function(InstanceID, CurrentURI, CurrentURIMetaData, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetAVTransportURI", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("InstanceID", InstanceID);
    request.writeStringParameter("CurrentURI", CurrentURI);
    request.writeStringParameter("CurrentURIMetaData", CurrentURIMetaData);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to SetNextAVTransportURI
* @method SetNextAVTransportURI
* @param {Int} InstanceID An action parameter
* @param {String} NextURI An action parameter
* @param {String} NextURIMetaData An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceAVTransport.prototype.SetNextAVTransportURI = function(InstanceID, NextURI, NextURIMetaData, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetNextAVTransportURI", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("InstanceID", InstanceID);
    request.writeStringParameter("NextURI", NextURI);
    request.writeStringParameter("NextURIMetaData", NextURIMetaData);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to GetMediaInfo
* @method GetMediaInfo
* @param {Int} InstanceID An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceAVTransport.prototype.GetMediaInfo = function(InstanceID, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("GetMediaInfo", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("InstanceID", InstanceID);
    request.send(function(result){
		result["NrTracks"] = Zapp.SoapRequest.readIntParameter(result["NrTracks"]);	
		result["MediaDuration"] = Zapp.SoapRequest.readStringParameter(result["MediaDuration"]);	
		result["CurrentURI"] = Zapp.SoapRequest.readStringParameter(result["CurrentURI"]);	
		result["CurrentURIMetaData"] = Zapp.SoapRequest.readStringParameter(result["CurrentURIMetaData"]);	
		result["NextURI"] = Zapp.SoapRequest.readStringParameter(result["NextURI"]);	
		result["NextURIMetaData"] = Zapp.SoapRequest.readStringParameter(result["NextURIMetaData"]);	
		result["PlayMedium"] = Zapp.SoapRequest.readStringParameter(result["PlayMedium"]);	
		result["RecordMedium"] = Zapp.SoapRequest.readStringParameter(result["RecordMedium"]);	
		result["WriteStatus"] = Zapp.SoapRequest.readStringParameter(result["WriteStatus"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to GetTransportInfo
* @method GetTransportInfo
* @param {Int} InstanceID An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceAVTransport.prototype.GetTransportInfo = function(InstanceID, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("GetTransportInfo", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("InstanceID", InstanceID);
    request.send(function(result){
		result["CurrentTransportState"] = Zapp.SoapRequest.readStringParameter(result["CurrentTransportState"]);	
		result["CurrentTransportStatus"] = Zapp.SoapRequest.readStringParameter(result["CurrentTransportStatus"]);	
		result["CurrentSpeed"] = Zapp.SoapRequest.readStringParameter(result["CurrentSpeed"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to GetPositionInfo
* @method GetPositionInfo
* @param {Int} InstanceID An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceAVTransport.prototype.GetPositionInfo = function(InstanceID, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("GetPositionInfo", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("InstanceID", InstanceID);
    request.send(function(result){
		result["Track"] = Zapp.SoapRequest.readIntParameter(result["Track"]);	
		result["TrackDuration"] = Zapp.SoapRequest.readStringParameter(result["TrackDuration"]);	
		result["TrackMetaData"] = Zapp.SoapRequest.readStringParameter(result["TrackMetaData"]);	
		result["TrackURI"] = Zapp.SoapRequest.readStringParameter(result["TrackURI"]);	
		result["RelTime"] = Zapp.SoapRequest.readStringParameter(result["RelTime"]);	
		result["AbsTime"] = Zapp.SoapRequest.readStringParameter(result["AbsTime"]);	
		result["RelCount"] = Zapp.SoapRequest.readIntParameter(result["RelCount"]);	
		result["AbsCount"] = Zapp.SoapRequest.readIntParameter(result["AbsCount"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to GetDeviceCapabilities
* @method GetDeviceCapabilities
* @param {Int} InstanceID An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceAVTransport.prototype.GetDeviceCapabilities = function(InstanceID, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("GetDeviceCapabilities", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("InstanceID", InstanceID);
    request.send(function(result){
		result["PlayMedia"] = Zapp.SoapRequest.readStringParameter(result["PlayMedia"]);	
		result["RecMedia"] = Zapp.SoapRequest.readStringParameter(result["RecMedia"]);	
		result["RecQualityModes"] = Zapp.SoapRequest.readStringParameter(result["RecQualityModes"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to GetTransportSettings
* @method GetTransportSettings
* @param {Int} InstanceID An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceAVTransport.prototype.GetTransportSettings = function(InstanceID, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("GetTransportSettings", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("InstanceID", InstanceID);
    request.send(function(result){
		result["PlayMode"] = Zapp.SoapRequest.readStringParameter(result["PlayMode"]);	
		result["RecQualityMode"] = Zapp.SoapRequest.readStringParameter(result["RecQualityMode"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to Stop
* @method Stop
* @param {Int} InstanceID An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceAVTransport.prototype.Stop = function(InstanceID, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("Stop", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("InstanceID", InstanceID);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to Play
* @method Play
* @param {Int} InstanceID An action parameter
* @param {String} Speed An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceAVTransport.prototype.Play = function(InstanceID, Speed, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("Play", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("InstanceID", InstanceID);
    request.writeStringParameter("Speed", Speed);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to Pause
* @method Pause
* @param {Int} InstanceID An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceAVTransport.prototype.Pause = function(InstanceID, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("Pause", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("InstanceID", InstanceID);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to Record
* @method Record
* @param {Int} InstanceID An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceAVTransport.prototype.Record = function(InstanceID, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("Record", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("InstanceID", InstanceID);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to Seek
* @method Seek
* @param {Int} InstanceID An action parameter
* @param {String} Unit An action parameter
* @param {String} Target An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceAVTransport.prototype.Seek = function(InstanceID, Unit, Target, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("Seek", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("InstanceID", InstanceID);
    request.writeStringParameter("Unit", Unit);
    request.writeStringParameter("Target", Target);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to Next
* @method Next
* @param {Int} InstanceID An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceAVTransport.prototype.Next = function(InstanceID, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("Next", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("InstanceID", InstanceID);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to Previous
* @method Previous
* @param {Int} InstanceID An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceAVTransport.prototype.Previous = function(InstanceID, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("Previous", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("InstanceID", InstanceID);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to SetPlayMode
* @method SetPlayMode
* @param {Int} InstanceID An action parameter
* @param {String} NewPlayMode An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceAVTransport.prototype.SetPlayMode = function(InstanceID, NewPlayMode, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetPlayMode", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("InstanceID", InstanceID);
    request.writeStringParameter("NewPlayMode", NewPlayMode);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to SetRecordQualityMode
* @method SetRecordQualityMode
* @param {Int} InstanceID An action parameter
* @param {String} NewRecordQualityMode An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceAVTransport.prototype.SetRecordQualityMode = function(InstanceID, NewRecordQualityMode, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetRecordQualityMode", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("InstanceID", InstanceID);
    request.writeStringParameter("NewRecordQualityMode", NewRecordQualityMode);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to GetCurrentTransportActions
* @method GetCurrentTransportActions
* @param {Int} InstanceID An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceAVTransport.prototype.GetCurrentTransportActions = function(InstanceID, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("GetCurrentTransportActions", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("InstanceID", InstanceID);
    request.send(function(result){
		result["Actions"] = Zapp.SoapRequest.readStringParameter(result["Actions"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}



