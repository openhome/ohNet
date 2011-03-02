 

/**
* Service Proxy for CpProxyLinnCoUkRadio1
* @module Zapp
* @class Radio
*/
	
var CpProxyLinnCoUkRadio1 = function(udn){	

	this.url = window.location.protocol + "//" + window.location.host + "/" + udn + "/linn.co.uk-Radio-1/control";  // upnp control url
	this.domain = "linn-co-uk";
	this.type = "Radio";
	this.version = "1";
	this.serviceName = "linn.co.uk-Radio-1";
	this.subscriptionId = "";  // Subscription identifier unique to each Subscription Manager 
	this.udn = udn;   // device name
	
	// Collection of service properties
	this.serviceProperties = {};
	this.serviceProperties["ChannelUri"] = new Zapp.ServiceProperty("ChannelUri");
	this.serviceProperties["ChannelMetadata"] = new Zapp.ServiceProperty("ChannelMetadata");
	this.serviceProperties["TransportState"] = new Zapp.ServiceProperty("TransportState");
	this.serviceProperties["ProtocolInfo"] = new Zapp.ServiceProperty("ProtocolInfo");
	this.serviceProperties["Id"] = new Zapp.ServiceProperty("Id");
	this.serviceProperties["IdArray"] = new Zapp.ServiceProperty("IdArray");
	this.serviceProperties["IdsMax"] = new Zapp.ServiceProperty("IdsMax");
}

ServiceRadio.kTransportStateStopped = "Stopped";
ServiceRadio.kTransportStatePlaying = "Playing";
ServiceRadio.kTransportStatePaused = "Paused";
ServiceRadio.kTransportStateBuffering = "Buffering";


/**
* Subscribes the service to the subscription manager to listen for property change events
* @method Subscribe
* @param {Function} serviceAddedFunction The function that executes once the subscription is successful
*/
CpProxyLinnCoUkRadio1.prototype.subscribe = function (serviceAddedFunction) {
    Zapp.SubscriptionManager.addService(this,serviceAddedFunction);
}


/**
* Unsubscribes the service from the subscription manager to stop listening for property change events
* @method Unsubscribe
*/
CpProxyLinnCoUkRadio1.prototype.unsubscribe = function () {
    Zapp.SubscriptionManager.removeService(this.subscriptionId);
}


	

/**
* Adds a listener to handle "ChannelUri" property change events
* @method ChannelUri_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyLinnCoUkRadio1.prototype.ChannelUri_Changed = function (stateChangedFunction) {
    this.serviceProperties.ChannelUri.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}
	

/**
* Adds a listener to handle "ChannelMetadata" property change events
* @method ChannelMetadata_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyLinnCoUkRadio1.prototype.ChannelMetadata_Changed = function (stateChangedFunction) {
    this.serviceProperties.ChannelMetadata.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}
	

/**
* Adds a listener to handle "TransportState" property change events
* @method TransportState_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyLinnCoUkRadio1.prototype.TransportState_Changed = function (stateChangedFunction) {
    this.serviceProperties.TransportState.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}
	

/**
* Adds a listener to handle "ProtocolInfo" property change events
* @method ProtocolInfo_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyLinnCoUkRadio1.prototype.ProtocolInfo_Changed = function (stateChangedFunction) {
    this.serviceProperties.ProtocolInfo.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}
	

/**
* Adds a listener to handle "Id" property change events
* @method Id_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyLinnCoUkRadio1.prototype.Id_Changed = function (stateChangedFunction) {
    this.serviceProperties.Id.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}
	

/**
* Adds a listener to handle "IdArray" property change events
* @method IdArray_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyLinnCoUkRadio1.prototype.IdArray_Changed = function (stateChangedFunction) {
    this.serviceProperties.IdArray.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readBinaryParameter(state)); 
	});
}
	

/**
* Adds a listener to handle "IdsMax" property change events
* @method IdsMax_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyLinnCoUkRadio1.prototype.IdsMax_Changed = function (stateChangedFunction) {
    this.serviceProperties.IdsMax.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* A service action to Play
* @method Play
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkRadio1.prototype.Play = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("Play", this.url, this.formattedDomain, this.type, this.version);		
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
CpProxyLinnCoUkRadio1.prototype.Pause = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("Pause", this.url, this.formattedDomain, this.type, this.version);		
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
CpProxyLinnCoUkRadio1.prototype.Stop = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("Stop", this.url, this.formattedDomain, this.type, this.version);		
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
CpProxyLinnCoUkRadio1.prototype.SeekSecondAbsolute = function(aSecond, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SeekSecondAbsolute", this.url, this.formattedDomain, this.type, this.version);		
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
CpProxyLinnCoUkRadio1.prototype.SeekSecondRelative = function(aSecond, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SeekSecondRelative", this.url, this.formattedDomain, this.type, this.version);		
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
* A service action to Channel
* @method Channel
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkRadio1.prototype.Channel = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("Channel", this.url, this.formattedDomain, this.type, this.version);		
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
* A service action to SetChannel
* @method SetChannel
* @param {String} aUri An action parameter
* @param {String} aMetadata An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkRadio1.prototype.SetChannel = function(aUri, aMetadata, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetChannel", this.url, this.formattedDomain, this.type, this.version);		
    request.writeStringParameter("aUri", aUri);
    request.writeStringParameter("aMetadata", aMetadata);
    request.send(function(result){
	
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
CpProxyLinnCoUkRadio1.prototype.ProtocolInfo = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("ProtocolInfo", this.url, this.formattedDomain, this.type, this.version);		
    request.send(function(result){
		result["aInfo"] = Zapp.SoapRequest.readStringParameter(result["aInfo"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to TransportState
* @method TransportState
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkRadio1.prototype.TransportState = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("TransportState", this.url, this.formattedDomain, this.type, this.version);		
    request.send(function(result){
		result["aState"] = Zapp.SoapRequest.readStringParameter(result["aState"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to Id
* @method Id
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkRadio1.prototype.Id = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("Id", this.url, this.formattedDomain, this.type, this.version);		
    request.send(function(result){
		result["aId"] = Zapp.SoapRequest.readIntParameter(result["aId"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to SetId
* @method SetId
* @param {Int} aId An action parameter
* @param {String} aUri An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkRadio1.prototype.SetId = function(aId, aUri, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetId", this.url, this.formattedDomain, this.type, this.version);		
    request.writeIntParameter("aId", aId);
    request.writeStringParameter("aUri", aUri);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to Read
* @method Read
* @param {Int} aId An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkRadio1.prototype.Read = function(aId, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("Read", this.url, this.formattedDomain, this.type, this.version);		
    request.writeIntParameter("aId", aId);
    request.send(function(result){
		result["aMetadata"] = Zapp.SoapRequest.readStringParameter(result["aMetadata"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to ReadList
* @method ReadList
* @param {String} aIdList An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkRadio1.prototype.ReadList = function(aIdList, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("ReadList", this.url, this.formattedDomain, this.type, this.version);		
    request.writeStringParameter("aIdList", aIdList);
    request.send(function(result){
		result["aMetadataList"] = Zapp.SoapRequest.readStringParameter(result["aMetadataList"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to IdArray
* @method IdArray
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkRadio1.prototype.IdArray = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("IdArray", this.url, this.formattedDomain, this.type, this.version);		
    request.send(function(result){
		result["aIdArrayToken"] = Zapp.SoapRequest.readIntParameter(result["aIdArrayToken"]);	
		result["aIdArray"] = Zapp.SoapRequest.readBinaryParameter(result["aIdArray"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to IdArrayChanged
* @method IdArrayChanged
* @param {Int} aIdArrayToken An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkRadio1.prototype.IdArrayChanged = function(aIdArrayToken, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("IdArrayChanged", this.url, this.formattedDomain, this.type, this.version);		
    request.writeIntParameter("aIdArrayToken", aIdArrayToken);
    request.send(function(result){
		result["aIdArrayChanged"] = Zapp.SoapRequest.readBoolParameter(result["aIdArrayChanged"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to IdsMax
* @method IdsMax
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkRadio1.prototype.IdsMax = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("IdsMax", this.url, this.formattedDomain, this.type, this.version);		
    request.send(function(result){
		result["aIdsMax"] = Zapp.SoapRequest.readIntParameter(result["aIdsMax"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}



