 

/**
* Service Proxy for CpProxyAvOpenhomeOrgReceiver1
* @module ohnet
* @class Receiver
*/
    
var CpProxyAvOpenhomeOrgReceiver1 = function(udn){ 

    this.url = window.location.protocol + "//" + window.location.host + "/" + udn + "/av.openhome.org-Receiver-1/control";  // upnp control url
    this.domain = "av-openhome-org";
    this.type = "Receiver";
    this.version = "1";
    this.serviceName = "av.openhome.org-Receiver-1";
    this.subscriptionId = "";  // Subscription identifier unique to each Subscription Manager 
    this.udn = udn;   // device name
    
    // Collection of service properties
    this.serviceProperties = {};
    this.serviceProperties["Uri"] = new ohnet.serviceproperty("Uri","string");
    this.serviceProperties["Metadata"] = new ohnet.serviceproperty("Metadata","string");
    this.serviceProperties["TransportState"] = new ohnet.serviceproperty("TransportState","string");
    this.serviceProperties["ProtocolInfo"] = new ohnet.serviceproperty("ProtocolInfo","string");

                        
    this.TransportStateAllowedValues = [];
    this.TransportStateAllowedValues.push("Stopped");
    this.TransportStateAllowedValues.push("Playing");
    this.TransportStateAllowedValues.push("Waiting");
    this.TransportStateAllowedValues.push("Buffering");
      
}



/**
* Subscribes the service to the subscription manager to listen for property change events
* @method Subscribe
* @param {Function} serviceAddedFunction The function that executes once the subscription is successful
*/
CpProxyAvOpenhomeOrgReceiver1.prototype.subscribe = function (serviceAddedFunction) {
    ohnet.subscriptionmanager.addService(this,serviceAddedFunction);
}


/**
* Unsubscribes the service from the subscription manager to stop listening for property change events
* @method Unsubscribe
*/
CpProxyAvOpenhomeOrgReceiver1.prototype.unsubscribe = function () {
    ohnet.subscriptionmanager.removeService(this.subscriptionId);
}


    

/**
* Adds a listener to handle "Uri" property change events
* @method Uri_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgReceiver1.prototype.Uri_Changed = function (stateChangedFunction) {
    this.serviceProperties.Uri.addListener(function (state) 
    { 
        stateChangedFunction(ohnet.soaprequest.readStringParameter(state)); 
    });
}
    

/**
* Adds a listener to handle "Metadata" property change events
* @method Metadata_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgReceiver1.prototype.Metadata_Changed = function (stateChangedFunction) {
    this.serviceProperties.Metadata.addListener(function (state) 
    { 
        stateChangedFunction(ohnet.soaprequest.readStringParameter(state)); 
    });
}
    

/**
* Adds a listener to handle "TransportState" property change events
* @method TransportState_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgReceiver1.prototype.TransportState_Changed = function (stateChangedFunction) {
    this.serviceProperties.TransportState.addListener(function (state) 
    { 
        stateChangedFunction(ohnet.soaprequest.readStringParameter(state)); 
    });
}
    

/**
* Adds a listener to handle "ProtocolInfo" property change events
* @method ProtocolInfo_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgReceiver1.prototype.ProtocolInfo_Changed = function (stateChangedFunction) {
    this.serviceProperties.ProtocolInfo.addListener(function (state) 
    { 
        stateChangedFunction(ohnet.soaprequest.readStringParameter(state)); 
    });
}


/**
* A service action to Play
* @method Play
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgReceiver1.prototype.Play = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("Play", this.url, this.domain, this.type, this.version);     
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
CpProxyAvOpenhomeOrgReceiver1.prototype.Stop = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("Stop", this.url, this.domain, this.type, this.version);     
    request.send(function(result){
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to SetSender
* @method SetSender
* @param {String} Uri An action parameter
* @param {String} Metadata An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgReceiver1.prototype.SetSender = function(Uri, Metadata, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("SetSender", this.url, this.domain, this.type, this.version);     
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
* A service action to Sender
* @method Sender
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgReceiver1.prototype.Sender = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("Sender", this.url, this.domain, this.type, this.version);     
    request.send(function(result){
        result["Uri"] = ohnet.soaprequest.readStringParameter(result["Uri"]); 
        result["Metadata"] = ohnet.soaprequest.readStringParameter(result["Metadata"]); 
    
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
CpProxyAvOpenhomeOrgReceiver1.prototype.ProtocolInfo = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("ProtocolInfo", this.url, this.domain, this.type, this.version);     
    request.send(function(result){
        result["Value"] = ohnet.soaprequest.readStringParameter(result["Value"]); 
    
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
CpProxyAvOpenhomeOrgReceiver1.prototype.TransportState = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("TransportState", this.url, this.domain, this.type, this.version);     
    request.send(function(result){
        result["Value"] = ohnet.soaprequest.readStringParameter(result["Value"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}



