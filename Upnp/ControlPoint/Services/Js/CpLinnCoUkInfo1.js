 

/**
* Service Proxy for linn.co.uk:Info:1
* @module Zapp
* @title Info
*/

var ServiceInfo = function(udn){	

	this.url = window.location.protocol + "//" + window.location.host + "/" + udn + "/linn.co.uk-Info-1/control";  // upnp control url
	this.domain = "linn.co.uk";
	if (this.domain == "upnp.org") {
		this.domain = "schemas.upnp.org";
    }
	this.domain = this.domain.replace(/\./,"-");
	this.type = "Info";
	this.version = "1";
	this.serviceName = "linn.co.uk-Info-1";
	this.subscriptionId = "";  // Subscription identifier unique to each Subscription Manager 
	this.udn = udn;   // device name
	
	// Collection of service properties
	this.serviceProperties = {};
	this.serviceProperties["TrackCount"] = new Zapp.ServiceProperty("TrackCount");
	this.serviceProperties["DetailsCount"] = new Zapp.ServiceProperty("DetailsCount");
	this.serviceProperties["MetatextCount"] = new Zapp.ServiceProperty("MetatextCount");
	this.serviceProperties["Uri"] = new Zapp.ServiceProperty("Uri");
	this.serviceProperties["Metadata"] = new Zapp.ServiceProperty("Metadata");
	this.serviceProperties["Duration"] = new Zapp.ServiceProperty("Duration");
	this.serviceProperties["BitRate"] = new Zapp.ServiceProperty("BitRate");
	this.serviceProperties["BitDepth"] = new Zapp.ServiceProperty("BitDepth");
	this.serviceProperties["SampleRate"] = new Zapp.ServiceProperty("SampleRate");
	this.serviceProperties["Lossless"] = new Zapp.ServiceProperty("Lossless");
	this.serviceProperties["CodecName"] = new Zapp.ServiceProperty("CodecName");
	this.serviceProperties["Metatext"] = new Zapp.ServiceProperty("Metatext");
}



/**
* Subscribes the service to the subscription manager to listen for property change events
* @method Subscribed
* @param {Function} serviceAddedFunction The function that executes once the subscription is successful
*/
ServiceInfo.prototype.subscribe = function (serviceAddedFunction) {
    Zapp.SubscriptionManager.addService(this,serviceAddedFunction);
}


/**
* Unsubscribes the service from the subscription manager to stop listening for property change events
* @method Subscribed
* @param {Function} serviceAddedFunction The function that executes once the subscription is successful
*/
ServiceInfo.prototype.unsubscribe = function () {
    Zapp.SubscriptionManager.removeService(this.subscriptionId);
}




/**
* Adds a listener to handle "TrackCount" property change events
* @method TrackCount_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceInfo.prototype.TrackCount_Changed = function (stateChangedFunction) {
    this.serviceProperties.TrackCount.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "DetailsCount" property change events
* @method DetailsCount_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceInfo.prototype.DetailsCount_Changed = function (stateChangedFunction) {
    this.serviceProperties.DetailsCount.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "MetatextCount" property change events
* @method MetatextCount_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceInfo.prototype.MetatextCount_Changed = function (stateChangedFunction) {
    this.serviceProperties.MetatextCount.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "Uri" property change events
* @method Uri_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceInfo.prototype.Uri_Changed = function (stateChangedFunction) {
    this.serviceProperties.Uri.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* Adds a listener to handle "Metadata" property change events
* @method Metadata_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceInfo.prototype.Metadata_Changed = function (stateChangedFunction) {
    this.serviceProperties.Metadata.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* Adds a listener to handle "Duration" property change events
* @method Duration_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceInfo.prototype.Duration_Changed = function (stateChangedFunction) {
    this.serviceProperties.Duration.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "BitRate" property change events
* @method BitRate_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceInfo.prototype.BitRate_Changed = function (stateChangedFunction) {
    this.serviceProperties.BitRate.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "BitDepth" property change events
* @method BitDepth_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceInfo.prototype.BitDepth_Changed = function (stateChangedFunction) {
    this.serviceProperties.BitDepth.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "SampleRate" property change events
* @method SampleRate_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceInfo.prototype.SampleRate_Changed = function (stateChangedFunction) {
    this.serviceProperties.SampleRate.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "Lossless" property change events
* @method Lossless_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceInfo.prototype.Lossless_Changed = function (stateChangedFunction) {
    this.serviceProperties.Lossless.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readBoolParameter(state)); 
	});
}


/**
* Adds a listener to handle "CodecName" property change events
* @method CodecName_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceInfo.prototype.CodecName_Changed = function (stateChangedFunction) {
    this.serviceProperties.CodecName.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* Adds a listener to handle "Metatext" property change events
* @method Metatext_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceInfo.prototype.Metatext_Changed = function (stateChangedFunction) {
    this.serviceProperties.Metatext.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* A service action to Counters
* @method Counters
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceInfo.prototype.Counters = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("Counters", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["aTrackCount"] = Zapp.SoapRequest.readIntParameter(result["aTrackCount"]);	
		result["aDetailsCount"] = Zapp.SoapRequest.readIntParameter(result["aDetailsCount"]);	
		result["aMetatextCount"] = Zapp.SoapRequest.readIntParameter(result["aMetatextCount"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to Track
* @method Track
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceInfo.prototype.Track = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("Track", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["aUri"] = Zapp.SoapRequest.readStringParameter(result["aUri"]);	
		result["aMetadata"] = Zapp.SoapRequest.readStringParameter(result["aMetadata"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to Details
* @method Details
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceInfo.prototype.Details = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("Details", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["aDuration"] = Zapp.SoapRequest.readIntParameter(result["aDuration"]);	
		result["aBitRate"] = Zapp.SoapRequest.readIntParameter(result["aBitRate"]);	
		result["aBitDepth"] = Zapp.SoapRequest.readIntParameter(result["aBitDepth"]);	
		result["aSampleRate"] = Zapp.SoapRequest.readIntParameter(result["aSampleRate"]);	
		result["aLossless"] = Zapp.SoapRequest.readBoolParameter(result["aLossless"]);	
		result["aCodecName"] = Zapp.SoapRequest.readStringParameter(result["aCodecName"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to Metatext
* @method Metatext
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceInfo.prototype.Metatext = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("Metatext", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["aMetatext"] = Zapp.SoapRequest.readStringParameter(result["aMetatext"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}



