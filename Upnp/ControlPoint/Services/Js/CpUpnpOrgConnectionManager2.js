 

/**
* Service Proxy for upnp.org:ConnectionManager:2
* @module Zapp
* @title ConnectionManager
*/

var ServiceConnectionManager = function(udn){	

	this.url = window.location.protocol + "//" + window.location.host + "/" + udn + "/upnp.org-ConnectionManager-2/control";  // upnp control url
	this.domain = "upnp.org";
	if (this.domain == "upnp.org") {
		this.domain = "schemas.upnp.org";
    }
	this.domain = this.domain.replace(/\./,"-");
	this.type = "ConnectionManager";
	this.version = "2";
	this.serviceName = "upnp.org-ConnectionManager-2";
	this.subscriptionId = "";  // Subscription identifier unique to each Subscription Manager 
	this.udn = udn;   // device name
	
	// Collection of service properties
	this.serviceProperties = {};
	this.serviceProperties["SourceProtocolInfo"] = new Zapp.ServiceProperty("SourceProtocolInfo");
	this.serviceProperties["SinkProtocolInfo"] = new Zapp.ServiceProperty("SinkProtocolInfo");
	this.serviceProperties["CurrentConnectionIDs"] = new Zapp.ServiceProperty("CurrentConnectionIDs");
	this.serviceProperties["ConnectionStatus"] = new Zapp.ServiceProperty("ConnectionStatus");
	this.serviceProperties["ConnectionManager"] = new Zapp.ServiceProperty("ConnectionManager");
	this.serviceProperties["Direction"] = new Zapp.ServiceProperty("Direction");
	this.serviceProperties["ProtocolInfo"] = new Zapp.ServiceProperty("ProtocolInfo");
	this.serviceProperties["ConnectionID"] = new Zapp.ServiceProperty("ConnectionID");
	this.serviceProperties["AVTransportID"] = new Zapp.ServiceProperty("AVTransportID");
	this.serviceProperties["RcsID"] = new Zapp.ServiceProperty("RcsID");
}

ServiceConnectionManager.kConnectionStatusOk = "OK";
ServiceConnectionManager.kConnectionStatusContentFormatMismatch = "ContentFormatMismatch";
ServiceConnectionManager.kConnectionStatusInsufficientBandwidth = "InsufficientBandwidth";
ServiceConnectionManager.kConnectionStatusUnreliableChannel = "UnreliableChannel";
ServiceConnectionManager.kConnectionStatusUnknown = "Unknown";
ServiceConnectionManager.kDirectionInput = "Input";
ServiceConnectionManager.kDirectionOutput = "Output";


/**
* Subscribes the service to the subscription manager to listen for property change events
* @method Subscribed
* @param {Function} serviceAddedFunction The function that executes once the subscription is successful
*/
ServiceConnectionManager.prototype.subscribe = function (serviceAddedFunction) {
    Zapp.SubscriptionManager.addService(this,serviceAddedFunction);
}


/**
* Unsubscribes the service from the subscription manager to stop listening for property change events
* @method Subscribed
* @param {Function} serviceAddedFunction The function that executes once the subscription is successful
*/
ServiceConnectionManager.prototype.unsubscribe = function () {
    Zapp.SubscriptionManager.removeService(this.subscriptionId);
}




/**
* Adds a listener to handle "SourceProtocolInfo" property change events
* @method SourceProtocolInfo_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceConnectionManager.prototype.SourceProtocolInfo_Changed = function (stateChangedFunction) {
    this.serviceProperties.SourceProtocolInfo.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* Adds a listener to handle "SinkProtocolInfo" property change events
* @method SinkProtocolInfo_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceConnectionManager.prototype.SinkProtocolInfo_Changed = function (stateChangedFunction) {
    this.serviceProperties.SinkProtocolInfo.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* Adds a listener to handle "CurrentConnectionIDs" property change events
* @method CurrentConnectionIDs_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceConnectionManager.prototype.CurrentConnectionIDs_Changed = function (stateChangedFunction) {
    this.serviceProperties.CurrentConnectionIDs.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* Adds a listener to handle "ConnectionStatus" property change events
* @method ConnectionStatus_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceConnectionManager.prototype.ConnectionStatus_Changed = function (stateChangedFunction) {
    this.serviceProperties.ConnectionStatus.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* Adds a listener to handle "ConnectionManager" property change events
* @method ConnectionManager_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceConnectionManager.prototype.ConnectionManager_Changed = function (stateChangedFunction) {
    this.serviceProperties.ConnectionManager.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* Adds a listener to handle "Direction" property change events
* @method Direction_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceConnectionManager.prototype.Direction_Changed = function (stateChangedFunction) {
    this.serviceProperties.Direction.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* Adds a listener to handle "ProtocolInfo" property change events
* @method ProtocolInfo_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceConnectionManager.prototype.ProtocolInfo_Changed = function (stateChangedFunction) {
    this.serviceProperties.ProtocolInfo.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* Adds a listener to handle "ConnectionID" property change events
* @method ConnectionID_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceConnectionManager.prototype.ConnectionID_Changed = function (stateChangedFunction) {
    this.serviceProperties.ConnectionID.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "AVTransportID" property change events
* @method AVTransportID_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceConnectionManager.prototype.AVTransportID_Changed = function (stateChangedFunction) {
    this.serviceProperties.AVTransportID.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "RcsID" property change events
* @method RcsID_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceConnectionManager.prototype.RcsID_Changed = function (stateChangedFunction) {
    this.serviceProperties.RcsID.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* A service action to GetProtocolInfo
* @method GetProtocolInfo
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceConnectionManager.prototype.GetProtocolInfo = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("GetProtocolInfo", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["Source"] = Zapp.SoapRequest.readStringParameter(result["Source"]);	
		result["Sink"] = Zapp.SoapRequest.readStringParameter(result["Sink"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to PrepareForConnection
* @method PrepareForConnection
* @param {String} RemoteProtocolInfo An action parameter
* @param {String} PeerConnectionManager An action parameter
* @param {Int} PeerConnectionID An action parameter
* @param {String} Direction An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceConnectionManager.prototype.PrepareForConnection = function(RemoteProtocolInfo, PeerConnectionManager, PeerConnectionID, Direction, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("PrepareForConnection", this.url, this.domain, this.type, this.version);		
    request.writeStringParameter("RemoteProtocolInfo", RemoteProtocolInfo);
    request.writeStringParameter("PeerConnectionManager", PeerConnectionManager);
    request.writeIntParameter("PeerConnectionID", PeerConnectionID);
    request.writeStringParameter("Direction", Direction);
    request.send(function(result){
		result["ConnectionID"] = Zapp.SoapRequest.readIntParameter(result["ConnectionID"]);	
		result["AVTransportID"] = Zapp.SoapRequest.readIntParameter(result["AVTransportID"]);	
		result["RcsID"] = Zapp.SoapRequest.readIntParameter(result["RcsID"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to ConnectionComplete
* @method ConnectionComplete
* @param {Int} ConnectionID An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceConnectionManager.prototype.ConnectionComplete = function(ConnectionID, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("ConnectionComplete", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("ConnectionID", ConnectionID);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to GetCurrentConnectionIDs
* @method GetCurrentConnectionIDs
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceConnectionManager.prototype.GetCurrentConnectionIDs = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("GetCurrentConnectionIDs", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["ConnectionIDs"] = Zapp.SoapRequest.readStringParameter(result["ConnectionIDs"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to GetCurrentConnectionInfo
* @method GetCurrentConnectionInfo
* @param {Int} ConnectionID An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceConnectionManager.prototype.GetCurrentConnectionInfo = function(ConnectionID, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("GetCurrentConnectionInfo", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("ConnectionID", ConnectionID);
    request.send(function(result){
		result["RcsID"] = Zapp.SoapRequest.readIntParameter(result["RcsID"]);	
		result["AVTransportID"] = Zapp.SoapRequest.readIntParameter(result["AVTransportID"]);	
		result["ProtocolInfo"] = Zapp.SoapRequest.readStringParameter(result["ProtocolInfo"]);	
		result["PeerConnectionManager"] = Zapp.SoapRequest.readStringParameter(result["PeerConnectionManager"]);	
		result["PeerConnectionID"] = Zapp.SoapRequest.readIntParameter(result["PeerConnectionID"]);	
		result["Direction"] = Zapp.SoapRequest.readStringParameter(result["Direction"]);	
		result["Status"] = Zapp.SoapRequest.readStringParameter(result["Status"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}



