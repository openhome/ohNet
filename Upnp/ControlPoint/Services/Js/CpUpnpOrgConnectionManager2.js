 

/**
* Service Proxy for CpProxySchemasUpnpOrgConnectionManager2
* @module ohNet
* @class ConnectionManager
*/
	
var CpProxySchemasUpnpOrgConnectionManager2 = function(udn){	

	this.url = window.location.protocol + "//" + window.location.host + "/" + udn + "/upnp.org-ConnectionManager-2/control";  // upnp control url
	this.domain = "schemas-upnp-org";
	this.type = "ConnectionManager";
	this.version = "2";
	this.serviceName = "upnp.org-ConnectionManager-2";
	this.subscriptionId = "";  // Subscription identifier unique to each Subscription Manager 
	this.udn = udn;   // device name
	
	// Collection of service properties
	this.serviceProperties = {};
	this.serviceProperties["SourceProtocolInfo"] = new OhNet.ServiceProperty("SourceProtocolInfo","string");
	this.serviceProperties["SinkProtocolInfo"] = new OhNet.ServiceProperty("SinkProtocolInfo","string");
	this.serviceProperties["CurrentConnectionIDs"] = new OhNet.ServiceProperty("CurrentConnectionIDs","string");
}



/**
* Subscribes the service to the subscription manager to listen for property change events
* @method Subscribe
* @param {Function} serviceAddedFunction The function that executes once the subscription is successful
*/
CpProxySchemasUpnpOrgConnectionManager2.prototype.subscribe = function (serviceAddedFunction) {
    OhNet.SubscriptionManager.addService(this,serviceAddedFunction);
}


/**
* Unsubscribes the service from the subscription manager to stop listening for property change events
* @method Unsubscribe
*/
CpProxySchemasUpnpOrgConnectionManager2.prototype.unsubscribe = function () {
    OhNet.SubscriptionManager.removeService(this.subscriptionId);
}


	

/**
* Adds a listener to handle "SourceProtocolInfo" property change events
* @method SourceProtocolInfo_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxySchemasUpnpOrgConnectionManager2.prototype.SourceProtocolInfo_Changed = function (stateChangedFunction) {
    this.serviceProperties.SourceProtocolInfo.addListener(function (state) 
	{ 
		stateChangedFunction(OhNet.SoapRequest.readStringParameter(state)); 
	});
}
	

/**
* Adds a listener to handle "SinkProtocolInfo" property change events
* @method SinkProtocolInfo_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxySchemasUpnpOrgConnectionManager2.prototype.SinkProtocolInfo_Changed = function (stateChangedFunction) {
    this.serviceProperties.SinkProtocolInfo.addListener(function (state) 
	{ 
		stateChangedFunction(OhNet.SoapRequest.readStringParameter(state)); 
	});
}
	

/**
* Adds a listener to handle "CurrentConnectionIDs" property change events
* @method CurrentConnectionIDs_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxySchemasUpnpOrgConnectionManager2.prototype.CurrentConnectionIDs_Changed = function (stateChangedFunction) {
    this.serviceProperties.CurrentConnectionIDs.addListener(function (state) 
	{ 
		stateChangedFunction(OhNet.SoapRequest.readStringParameter(state)); 
	});
}


/**
* A service action to GetProtocolInfo
* @method GetProtocolInfo
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgConnectionManager2.prototype.GetProtocolInfo = function(successFunction, errorFunction){	
	var request = new OhNet.SoapRequest("GetProtocolInfo", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["Source"] = OhNet.SoapRequest.readStringParameter(result["Source"]);	
		result["Sink"] = OhNet.SoapRequest.readStringParameter(result["Sink"]);	
	
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
CpProxySchemasUpnpOrgConnectionManager2.prototype.PrepareForConnection = function(RemoteProtocolInfo, PeerConnectionManager, PeerConnectionID, Direction, successFunction, errorFunction){	
	var request = new OhNet.SoapRequest("PrepareForConnection", this.url, this.domain, this.type, this.version);		
    request.writeStringParameter("RemoteProtocolInfo", RemoteProtocolInfo);
    request.writeStringParameter("PeerConnectionManager", PeerConnectionManager);
    request.writeIntParameter("PeerConnectionID", PeerConnectionID);
    request.writeStringParameter("Direction", Direction);
    request.send(function(result){
		result["ConnectionID"] = OhNet.SoapRequest.readIntParameter(result["ConnectionID"]);	
		result["AVTransportID"] = OhNet.SoapRequest.readIntParameter(result["AVTransportID"]);	
		result["RcsID"] = OhNet.SoapRequest.readIntParameter(result["RcsID"]);	
	
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
CpProxySchemasUpnpOrgConnectionManager2.prototype.ConnectionComplete = function(ConnectionID, successFunction, errorFunction){	
	var request = new OhNet.SoapRequest("ConnectionComplete", this.url, this.domain, this.type, this.version);		
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
CpProxySchemasUpnpOrgConnectionManager2.prototype.GetCurrentConnectionIDs = function(successFunction, errorFunction){	
	var request = new OhNet.SoapRequest("GetCurrentConnectionIDs", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["ConnectionIDs"] = OhNet.SoapRequest.readStringParameter(result["ConnectionIDs"]);	
	
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
CpProxySchemasUpnpOrgConnectionManager2.prototype.GetCurrentConnectionInfo = function(ConnectionID, successFunction, errorFunction){	
	var request = new OhNet.SoapRequest("GetCurrentConnectionInfo", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("ConnectionID", ConnectionID);
    request.send(function(result){
		result["RcsID"] = OhNet.SoapRequest.readIntParameter(result["RcsID"]);	
		result["AVTransportID"] = OhNet.SoapRequest.readIntParameter(result["AVTransportID"]);	
		result["ProtocolInfo"] = OhNet.SoapRequest.readStringParameter(result["ProtocolInfo"]);	
		result["PeerConnectionManager"] = OhNet.SoapRequest.readStringParameter(result["PeerConnectionManager"]);	
		result["PeerConnectionID"] = OhNet.SoapRequest.readIntParameter(result["PeerConnectionID"]);	
		result["Direction"] = OhNet.SoapRequest.readStringParameter(result["Direction"]);	
		result["Status"] = OhNet.SoapRequest.readStringParameter(result["Status"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}



