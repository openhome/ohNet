 

/**
* Service Proxy for linn-co-uk:Ds:1
* @module Zapp
* @class Ds
*/
	
var CpProxyLinnCoUkDs1 = function(udn){	

	this.url = window.location.protocol + "//" + window.location.host + "/" + udn + "/linn-co-uk-Ds-1/control";  // upnp control url
	this.domain = "linn-co-uk";
	this.type = "Ds";
	this.version = "1";
	this.serviceName = "CpProxyLinnCoUkDs1";
	this.subscriptionId = "";  // Subscription identifier unique to each Subscription Manager 
	this.udn = udn;   // device name
	
	// Collection of service properties
	this.serviceProperties = {};
	this.serviceProperties["SupportedProtocols"] = new Zapp.ServiceProperty("SupportedProtocols");
	this.serviceProperties["TrackDuration"] = new Zapp.ServiceProperty("TrackDuration");
	this.serviceProperties["TrackBitRate"] = new Zapp.ServiceProperty("TrackBitRate");
	this.serviceProperties["TrackLossless"] = new Zapp.ServiceProperty("TrackLossless");
	this.serviceProperties["TrackBitDepth"] = new Zapp.ServiceProperty("TrackBitDepth");
	this.serviceProperties["TrackSampleRate"] = new Zapp.ServiceProperty("TrackSampleRate");
	this.serviceProperties["TrackCodecName"] = new Zapp.ServiceProperty("TrackCodecName");
	this.serviceProperties["TrackId"] = new Zapp.ServiceProperty("TrackId");
	this.serviceProperties["TransportState"] = new Zapp.ServiceProperty("TransportState");
}

ServiceDs.kTransportStatePlaying = "Playing";
ServiceDs.kTransportStatePaused = "Paused";
ServiceDs.kTransportStateStopped = "Stopped";
ServiceDs.kTransportStateBuffering = "Buffering";


/**
* Subscribes the service to the subscription manager to listen for property change events
* @method Subscribe
* @param {Function} serviceAddedFunction The function that executes once the subscription is successful
*/
CpProxyLinnCoUkDs1.prototype.subscribe = function (serviceAddedFunction) {
    Zapp.SubscriptionManager.addService(this,serviceAddedFunction);
}


/**
* Unsubscribes the service from the subscription manager to stop listening for property change events
* @method Unsubscribe
*/
CpProxyLinnCoUkDs1.prototype.unsubscribe = function () {
    Zapp.SubscriptionManager.removeService(this.subscriptionId);
}


	

/**
* Adds a listener to handle "SupportedProtocols" property change events
* @method SupportedProtocols_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyLinnCoUkDs1.prototype.SupportedProtocols_Changed = function (stateChangedFunction) {
    this.serviceProperties.SupportedProtocols.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}
	

/**
* Adds a listener to handle "TrackDuration" property change events
* @method TrackDuration_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyLinnCoUkDs1.prototype.TrackDuration_Changed = function (stateChangedFunction) {
    this.serviceProperties.TrackDuration.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}
	

/**
* Adds a listener to handle "TrackBitRate" property change events
* @method TrackBitRate_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyLinnCoUkDs1.prototype.TrackBitRate_Changed = function (stateChangedFunction) {
    this.serviceProperties.TrackBitRate.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}
	

/**
* Adds a listener to handle "TrackLossless" property change events
* @method TrackLossless_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyLinnCoUkDs1.prototype.TrackLossless_Changed = function (stateChangedFunction) {
    this.serviceProperties.TrackLossless.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readBoolParameter(state)); 
	});
}
	

/**
* Adds a listener to handle "TrackBitDepth" property change events
* @method TrackBitDepth_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyLinnCoUkDs1.prototype.TrackBitDepth_Changed = function (stateChangedFunction) {
    this.serviceProperties.TrackBitDepth.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}
	

/**
* Adds a listener to handle "TrackSampleRate" property change events
* @method TrackSampleRate_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyLinnCoUkDs1.prototype.TrackSampleRate_Changed = function (stateChangedFunction) {
    this.serviceProperties.TrackSampleRate.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}
	

/**
* Adds a listener to handle "TrackCodecName" property change events
* @method TrackCodecName_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyLinnCoUkDs1.prototype.TrackCodecName_Changed = function (stateChangedFunction) {
    this.serviceProperties.TrackCodecName.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}
	

/**
* Adds a listener to handle "TrackId" property change events
* @method TrackId_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyLinnCoUkDs1.prototype.TrackId_Changed = function (stateChangedFunction) {
    this.serviceProperties.TrackId.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}
	

/**
* Adds a listener to handle "TransportState" property change events
* @method TransportState_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyLinnCoUkDs1.prototype.TransportState_Changed = function (stateChangedFunction) {
    this.serviceProperties.TransportState.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* A service action to Play
* @method Play
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkDs1.prototype.Play = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("Play", this.url, this.domain, this.type, this.version);		
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
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkDs1.prototype.Pause = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("Pause", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
	
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
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkDs1.prototype.Stop = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("Stop", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to SeekSecondAbsolute
* @method SeekSecondAbsolute
* @param {Int} aSecond An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkDs1.prototype.SeekSecondAbsolute = function(aSecond, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SeekSecondAbsolute", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("aSecond", aSecond);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to SeekSecondRelative
* @method SeekSecondRelative
* @param {Int} aSecond An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkDs1.prototype.SeekSecondRelative = function(aSecond, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SeekSecondRelative", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("aSecond", aSecond);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to SeekTrackId
* @method SeekTrackId
* @param {Int} aTrackId An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkDs1.prototype.SeekTrackId = function(aTrackId, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SeekTrackId", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("aTrackId", aTrackId);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to SeekTrackAbsolute
* @method SeekTrackAbsolute
* @param {Int} aTrack An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkDs1.prototype.SeekTrackAbsolute = function(aTrack, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SeekTrackAbsolute", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("aTrack", aTrack);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to SeekTrackRelative
* @method SeekTrackRelative
* @param {Int} aTrack An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkDs1.prototype.SeekTrackRelative = function(aTrack, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SeekTrackRelative", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("aTrack", aTrack);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to State
* @method State
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkDs1.prototype.State = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("State", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["aTransportState"] = Zapp.SoapRequest.readStringParameter(result["aTransportState"]);	
		result["aTrackDuration"] = Zapp.SoapRequest.readIntParameter(result["aTrackDuration"]);	
		result["aTrackBitRate"] = Zapp.SoapRequest.readIntParameter(result["aTrackBitRate"]);	
		result["aTrackLossless"] = Zapp.SoapRequest.readBoolParameter(result["aTrackLossless"]);	
		result["aTrackBitDepth"] = Zapp.SoapRequest.readIntParameter(result["aTrackBitDepth"]);	
		result["aTrackSampleRate"] = Zapp.SoapRequest.readIntParameter(result["aTrackSampleRate"]);	
		result["aTrackCodecName"] = Zapp.SoapRequest.readStringParameter(result["aTrackCodecName"]);	
		result["aTrackId"] = Zapp.SoapRequest.readIntParameter(result["aTrackId"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to ProtocolInfo
* @method ProtocolInfo
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkDs1.prototype.ProtocolInfo = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("ProtocolInfo", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["aSupportedProtocols"] = Zapp.SoapRequest.readStringParameter(result["aSupportedProtocols"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}



