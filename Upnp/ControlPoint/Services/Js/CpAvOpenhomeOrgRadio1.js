 

/**
* Service Proxy for CpProxyAvOpenhomeOrgRadio1
* @module Zapp
* @class Radio
*/
	
var CpProxyAvOpenhomeOrgRadio1 = function(udn){	

	this.url = window.location.protocol + "//" + window.location.host + "/" + udn + "/av.openhome.org-Radio-1/control";  // upnp control url
	this.domain = "av-openhome-org";
	this.type = "Radio";
	this.version = "1";
	this.serviceName = "av.openhome.org-Radio-1";
	this.subscriptionId = "";  // Subscription identifier unique to each Subscription Manager 
	this.udn = udn;   // device name
	
	// Collection of service properties
	this.serviceProperties = {};
	this.serviceProperties["Uri"] = new Zapp.ServiceProperty("Uri","string");
	this.serviceProperties["Metadata"] = new Zapp.ServiceProperty("Metadata","string");
	this.serviceProperties["TransportState"] = new Zapp.ServiceProperty("TransportState","string");
	this.serviceProperties["Id"] = new Zapp.ServiceProperty("Id","int");
	this.serviceProperties["IdArray"] = new Zapp.ServiceProperty("IdArray","binary");
	this.serviceProperties["ChannelsMax"] = new Zapp.ServiceProperty("ChannelsMax","int");
	this.serviceProperties["ProtocolInfo"] = new Zapp.ServiceProperty("ProtocolInfo","string");
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
CpProxyAvOpenhomeOrgRadio1.prototype.subscribe = function (serviceAddedFunction) {
    Zapp.SubscriptionManager.addService(this,serviceAddedFunction);
}


/**
* Unsubscribes the service from the subscription manager to stop listening for property change events
* @method Unsubscribe
*/
CpProxyAvOpenhomeOrgRadio1.prototype.unsubscribe = function () {
    Zapp.SubscriptionManager.removeService(this.subscriptionId);
}


	

/**
* Adds a listener to handle "Uri" property change events
* @method Uri_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgRadio1.prototype.Uri_Changed = function (stateChangedFunction) {
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
CpProxyAvOpenhomeOrgRadio1.prototype.Metadata_Changed = function (stateChangedFunction) {
    this.serviceProperties.Metadata.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}
	

/**
* Adds a listener to handle "TransportState" property change events
* @method TransportState_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgRadio1.prototype.TransportState_Changed = function (stateChangedFunction) {
    this.serviceProperties.TransportState.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}
	

/**
* Adds a listener to handle "Id" property change events
* @method Id_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgRadio1.prototype.Id_Changed = function (stateChangedFunction) {
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
CpProxyAvOpenhomeOrgRadio1.prototype.IdArray_Changed = function (stateChangedFunction) {
    this.serviceProperties.IdArray.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readBinaryParameter(state)); 
	});
}
	

/**
* Adds a listener to handle "ChannelsMax" property change events
* @method ChannelsMax_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgRadio1.prototype.ChannelsMax_Changed = function (stateChangedFunction) {
    this.serviceProperties.ChannelsMax.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}
	

/**
* Adds a listener to handle "ProtocolInfo" property change events
* @method ProtocolInfo_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgRadio1.prototype.ProtocolInfo_Changed = function (stateChangedFunction) {
    this.serviceProperties.ProtocolInfo.addListener(function (state) 
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
CpProxyAvOpenhomeOrgRadio1.prototype.Play = function(successFunction, errorFunction){	
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
CpProxyAvOpenhomeOrgRadio1.prototype.Pause = function(successFunction, errorFunction){	
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
CpProxyAvOpenhomeOrgRadio1.prototype.Stop = function(successFunction, errorFunction){	
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
* @param {Int} Value An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgRadio1.prototype.SeekSecondAbsolute = function(Value, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SeekSecondAbsolute", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("Value", Value);
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
* @param {Int} Value An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgRadio1.prototype.SeekSecondRelative = function(Value, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SeekSecondRelative", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("Value", Value);
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
CpProxyAvOpenhomeOrgRadio1.prototype.Channel = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("Channel", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["Uri"] = Zapp.SoapRequest.readStringParameter(result["Uri"]);	
		result["Metadata"] = Zapp.SoapRequest.readStringParameter(result["Metadata"]);	
	
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
* @param {String} Uri An action parameter
* @param {String} Metadata An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgRadio1.prototype.SetChannel = function(Uri, Metadata, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetChannel", this.url, this.domain, this.type, this.version);		
    request.writeStringParameter("Uri", Uri);
    request.writeStringParameter("Metadata", Metadata);
    request.send(function(result){
	
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
CpProxyAvOpenhomeOrgRadio1.prototype.TransportState = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("TransportState", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["Value"] = Zapp.SoapRequest.readStringParameter(result["Value"]);	
	
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
CpProxyAvOpenhomeOrgRadio1.prototype.Id = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("Id", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["Value"] = Zapp.SoapRequest.readIntParameter(result["Value"]);	
	
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
* @param {Int} Value An action parameter
* @param {String} Uri An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgRadio1.prototype.SetId = function(Value, Uri, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetId", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("Value", Value);
    request.writeStringParameter("Uri", Uri);
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
* @param {Int} Id An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgRadio1.prototype.Read = function(Id, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("Read", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("Id", Id);
    request.send(function(result){
		result["Metadata"] = Zapp.SoapRequest.readStringParameter(result["Metadata"]);	
	
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
* @param {String} IdList An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgRadio1.prototype.ReadList = function(IdList, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("ReadList", this.url, this.domain, this.type, this.version);		
    request.writeStringParameter("IdList", IdList);
    request.send(function(result){
		result["ChannelList"] = Zapp.SoapRequest.readStringParameter(result["ChannelList"]);	
	
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
CpProxyAvOpenhomeOrgRadio1.prototype.IdArray = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("IdArray", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["Token"] = Zapp.SoapRequest.readIntParameter(result["Token"]);	
		result["Array"] = Zapp.SoapRequest.readBinaryParameter(result["Array"]);	
	
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
* @param {Int} Token An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgRadio1.prototype.IdArrayChanged = function(Token, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("IdArrayChanged", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("Token", Token);
    request.send(function(result){
		result["Value"] = Zapp.SoapRequest.readBoolParameter(result["Value"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to ChannelsMax
* @method ChannelsMax
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgRadio1.prototype.ChannelsMax = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("ChannelsMax", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["Value"] = Zapp.SoapRequest.readIntParameter(result["Value"]);	
	
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
CpProxyAvOpenhomeOrgRadio1.prototype.ProtocolInfo = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("ProtocolInfo", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["Value"] = Zapp.SoapRequest.readStringParameter(result["Value"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}



