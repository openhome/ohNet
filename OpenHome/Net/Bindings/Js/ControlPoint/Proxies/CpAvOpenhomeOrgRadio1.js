 

/**
* Service Proxy for CpProxyAvOpenhomeOrgRadio1
* @module ohnet
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
    this.serviceProperties["Uri"] = new ohnet.serviceproperty("Uri","string");
    this.serviceProperties["Metadata"] = new ohnet.serviceproperty("Metadata","string");
    this.serviceProperties["TransportState"] = new ohnet.serviceproperty("TransportState","string");
    this.serviceProperties["Id"] = new ohnet.serviceproperty("Id","int");
    this.serviceProperties["IdArray"] = new ohnet.serviceproperty("IdArray","binary");
    this.serviceProperties["ChannelsMax"] = new ohnet.serviceproperty("ChannelsMax","int");
    this.serviceProperties["ProtocolInfo"] = new ohnet.serviceproperty("ProtocolInfo","string");

                        
    this.TransportStateAllowedValues = [];
    this.TransportStateAllowedValues.push("Stopped");
    this.TransportStateAllowedValues.push("Playing");
    this.TransportStateAllowedValues.push("Paused");
    this.TransportStateAllowedValues.push("Buffering");
                        
}



/**
* Subscribes the service to the subscription manager to listen for property change events
* @method Subscribe
* @param {Function} serviceAddedFunction The function that executes once the subscription is successful
*/
CpProxyAvOpenhomeOrgRadio1.prototype.subscribe = function (serviceAddedFunction) {
    ohnet.subscriptionmanager.addService(this,serviceAddedFunction);
}


/**
* Unsubscribes the service from the subscription manager to stop listening for property change events
* @method Unsubscribe
*/
CpProxyAvOpenhomeOrgRadio1.prototype.unsubscribe = function () {
    ohnet.subscriptionmanager.removeService(this.subscriptionId);
}


    

/**
* Adds a listener to handle "Uri" property change events
* @method Uri_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgRadio1.prototype.Uri_Changed = function (stateChangedFunction) {
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
CpProxyAvOpenhomeOrgRadio1.prototype.Metadata_Changed = function (stateChangedFunction) {
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
CpProxyAvOpenhomeOrgRadio1.prototype.TransportState_Changed = function (stateChangedFunction) {
    this.serviceProperties.TransportState.addListener(function (state) 
    { 
        stateChangedFunction(ohnet.soaprequest.readStringParameter(state)); 
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
        stateChangedFunction(ohnet.soaprequest.readIntParameter(state)); 
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
        stateChangedFunction(ohnet.soaprequest.readBinaryParameter(state)); 
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
        stateChangedFunction(ohnet.soaprequest.readIntParameter(state)); 
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
        stateChangedFunction(ohnet.soaprequest.readStringParameter(state)); 
    });
}


/**
* A service action to Play
* @method Play
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgRadio1.prototype.Play = function(successFunction, errorFunction){ 
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
* A service action to Pause
* @method Pause
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgRadio1.prototype.Pause = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("Pause", this.url, this.domain, this.type, this.version);     
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
* A service action to SeekSecondAbsolute
* @method SeekSecondAbsolute
* @param {Int} Value An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgRadio1.prototype.SeekSecondAbsolute = function(Value, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("SeekSecondAbsolute", this.url, this.domain, this.type, this.version);     
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
    var request = new ohnet.soaprequest("SeekSecondRelative", this.url, this.domain, this.type, this.version);     
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
    var request = new ohnet.soaprequest("Channel", this.url, this.domain, this.type, this.version);     
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
* A service action to SetChannel
* @method SetChannel
* @param {String} Uri An action parameter
* @param {String} Metadata An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgRadio1.prototype.SetChannel = function(Uri, Metadata, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("SetChannel", this.url, this.domain, this.type, this.version);     
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


/**
* A service action to Id
* @method Id
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgRadio1.prototype.Id = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("Id", this.url, this.domain, this.type, this.version);     
    request.send(function(result){
        result["Value"] = ohnet.soaprequest.readIntParameter(result["Value"]); 
    
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
    var request = new ohnet.soaprequest("SetId", this.url, this.domain, this.type, this.version);     
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
    var request = new ohnet.soaprequest("Read", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("Id", Id);
    request.send(function(result){
        result["Metadata"] = ohnet.soaprequest.readStringParameter(result["Metadata"]); 
    
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
    var request = new ohnet.soaprequest("ReadList", this.url, this.domain, this.type, this.version);     
    request.writeStringParameter("IdList", IdList);
    request.send(function(result){
        result["ChannelList"] = ohnet.soaprequest.readStringParameter(result["ChannelList"]); 
    
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
    var request = new ohnet.soaprequest("IdArray", this.url, this.domain, this.type, this.version);     
    request.send(function(result){
        result["Token"] = ohnet.soaprequest.readIntParameter(result["Token"]); 
        result["Array"] = ohnet.soaprequest.readBinaryParameter(result["Array"]); 
    
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
    var request = new ohnet.soaprequest("IdArrayChanged", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("Token", Token);
    request.send(function(result){
        result["Value"] = ohnet.soaprequest.readBoolParameter(result["Value"]); 
    
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
    var request = new ohnet.soaprequest("ChannelsMax", this.url, this.domain, this.type, this.version);     
    request.send(function(result){
        result["Value"] = ohnet.soaprequest.readIntParameter(result["Value"]); 
    
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



