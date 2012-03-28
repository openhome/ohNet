 

/**
* Service Proxy for CpProxySchemasUpnpOrgConnectionManager1
* @module ohnet
* @class ConnectionManager
*/
    
var CpProxySchemasUpnpOrgConnectionManager1 = function(udn){ 

    this.url = window.location.protocol + "//" + window.location.host + "/" + udn + "/upnp.org-ConnectionManager-1/control";  // upnp control url
    this.domain = "schemas-upnp-org";
    this.type = "ConnectionManager";
    this.version = "1";
    this.serviceName = "upnp.org-ConnectionManager-1";
    this.subscriptionId = "";  // Subscription identifier unique to each Subscription Manager 
    this.udn = udn;   // device name
    
    // Collection of service properties
    this.serviceProperties = {};
    this.serviceProperties["SourceProtocolInfo"] = new ohnet.serviceproperty("SourceProtocolInfo","string");
    this.serviceProperties["SinkProtocolInfo"] = new ohnet.serviceproperty("SinkProtocolInfo","string");
    this.serviceProperties["CurrentConnectionIDs"] = new ohnet.serviceproperty("CurrentConnectionIDs","string");

                      
}



/**
* Subscribes the service to the subscription manager to listen for property change events
* @method Subscribe
* @param {Function} serviceAddedFunction The function that executes once the subscription is successful
*/
CpProxySchemasUpnpOrgConnectionManager1.prototype.subscribe = function (serviceAddedFunction) {
    ohnet.subscriptionmanager.addService(this,serviceAddedFunction);
}


/**
* Unsubscribes the service from the subscription manager to stop listening for property change events
* @method Unsubscribe
*/
CpProxySchemasUpnpOrgConnectionManager1.prototype.unsubscribe = function () {
    ohnet.subscriptionmanager.removeService(this.subscriptionId);
}


    

/**
* Adds a listener to handle "SourceProtocolInfo" property change events
* @method SourceProtocolInfo_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxySchemasUpnpOrgConnectionManager1.prototype.SourceProtocolInfo_Changed = function (stateChangedFunction) {
    this.serviceProperties.SourceProtocolInfo.addListener(function (state) 
    { 
        stateChangedFunction(ohnet.soaprequest.readStringParameter(state)); 
    });
}
    

/**
* Adds a listener to handle "SinkProtocolInfo" property change events
* @method SinkProtocolInfo_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxySchemasUpnpOrgConnectionManager1.prototype.SinkProtocolInfo_Changed = function (stateChangedFunction) {
    this.serviceProperties.SinkProtocolInfo.addListener(function (state) 
    { 
        stateChangedFunction(ohnet.soaprequest.readStringParameter(state)); 
    });
}
    

/**
* Adds a listener to handle "CurrentConnectionIDs" property change events
* @method CurrentConnectionIDs_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxySchemasUpnpOrgConnectionManager1.prototype.CurrentConnectionIDs_Changed = function (stateChangedFunction) {
    this.serviceProperties.CurrentConnectionIDs.addListener(function (state) 
    { 
        stateChangedFunction(ohnet.soaprequest.readStringParameter(state)); 
    });
}


/**
* A service action to GetProtocolInfo
* @method GetProtocolInfo
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgConnectionManager1.prototype.GetProtocolInfo = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("GetProtocolInfo", this.url, this.domain, this.type, this.version);     
    request.send(function(result){
        result["Source"] = ohnet.soaprequest.readStringParameter(result["Source"]); 
        result["Sink"] = ohnet.soaprequest.readStringParameter(result["Sink"]); 
    
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
CpProxySchemasUpnpOrgConnectionManager1.prototype.PrepareForConnection = function(RemoteProtocolInfo, PeerConnectionManager, PeerConnectionID, Direction, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("PrepareForConnection", this.url, this.domain, this.type, this.version);     
    request.writeStringParameter("RemoteProtocolInfo", RemoteProtocolInfo);
    request.writeStringParameter("PeerConnectionManager", PeerConnectionManager);
    request.writeIntParameter("PeerConnectionID", PeerConnectionID);
    request.writeStringParameter("Direction", Direction);
    request.send(function(result){
        result["ConnectionID"] = ohnet.soaprequest.readIntParameter(result["ConnectionID"]); 
        result["AVTransportID"] = ohnet.soaprequest.readIntParameter(result["AVTransportID"]); 
        result["RcsID"] = ohnet.soaprequest.readIntParameter(result["RcsID"]); 
    
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
CpProxySchemasUpnpOrgConnectionManager1.prototype.ConnectionComplete = function(ConnectionID, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("ConnectionComplete", this.url, this.domain, this.type, this.version);     
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
CpProxySchemasUpnpOrgConnectionManager1.prototype.GetCurrentConnectionIDs = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("GetCurrentConnectionIDs", this.url, this.domain, this.type, this.version);     
    request.send(function(result){
        result["ConnectionIDs"] = ohnet.soaprequest.readStringParameter(result["ConnectionIDs"]); 
    
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
CpProxySchemasUpnpOrgConnectionManager1.prototype.GetCurrentConnectionInfo = function(ConnectionID, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("GetCurrentConnectionInfo", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("ConnectionID", ConnectionID);
    request.send(function(result){
        result["RcsID"] = ohnet.soaprequest.readIntParameter(result["RcsID"]); 
        result["AVTransportID"] = ohnet.soaprequest.readIntParameter(result["AVTransportID"]); 
        result["ProtocolInfo"] = ohnet.soaprequest.readStringParameter(result["ProtocolInfo"]); 
        result["PeerConnectionManager"] = ohnet.soaprequest.readStringParameter(result["PeerConnectionManager"]); 
        result["PeerConnectionID"] = ohnet.soaprequest.readIntParameter(result["PeerConnectionID"]); 
        result["Direction"] = ohnet.soaprequest.readStringParameter(result["Direction"]); 
        result["Status"] = ohnet.soaprequest.readStringParameter(result["Status"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}



