 

/**
* Service Proxy for CpProxyAvOpenhomeOrgPlaylist1
* @module ohnet
* @class Playlist
*/
    
var CpProxyAvOpenhomeOrgPlaylist1 = function(udn){ 

    this.url = window.location.protocol + "//" + window.location.host + "/" + udn + "/av.openhome.org-Playlist-1/control";  // upnp control url
    this.domain = "av-openhome-org";
    this.type = "Playlist";
    this.version = "1";
    this.serviceName = "av.openhome.org-Playlist-1";
    this.subscriptionId = "";  // Subscription identifier unique to each Subscription Manager 
    this.udn = udn;   // device name
    
    // Collection of service properties
    this.serviceProperties = {};
    this.serviceProperties["TransportState"] = new ohnet.serviceproperty("TransportState","string");
    this.serviceProperties["Repeat"] = new ohnet.serviceproperty("Repeat","bool");
    this.serviceProperties["Shuffle"] = new ohnet.serviceproperty("Shuffle","bool");
    this.serviceProperties["Id"] = new ohnet.serviceproperty("Id","int");
    this.serviceProperties["IdArray"] = new ohnet.serviceproperty("IdArray","binary");
    this.serviceProperties["TracksMax"] = new ohnet.serviceproperty("TracksMax","int");
    this.serviceProperties["ProtocolInfo"] = new ohnet.serviceproperty("ProtocolInfo","string");

            
    this.TransportStateAllowedValues = [];
    this.TransportStateAllowedValues.push("Playing");
    this.TransportStateAllowedValues.push("Paused");
    this.TransportStateAllowedValues.push("Stopped");
    this.TransportStateAllowedValues.push("Buffering");
                                    
}



/**
* Subscribes the service to the subscription manager to listen for property change events
* @method Subscribe
* @param {Function} serviceAddedFunction The function that executes once the subscription is successful
*/
CpProxyAvOpenhomeOrgPlaylist1.prototype.subscribe = function (serviceAddedFunction) {
    ohnet.subscriptionmanager.addService(this,serviceAddedFunction);
}


/**
* Unsubscribes the service from the subscription manager to stop listening for property change events
* @method Unsubscribe
*/
CpProxyAvOpenhomeOrgPlaylist1.prototype.unsubscribe = function () {
    ohnet.subscriptionmanager.removeService(this.subscriptionId);
}


    

/**
* Adds a listener to handle "TransportState" property change events
* @method TransportState_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgPlaylist1.prototype.TransportState_Changed = function (stateChangedFunction) {
    this.serviceProperties.TransportState.addListener(function (state) 
    { 
        stateChangedFunction(ohnet.soaprequest.readStringParameter(state)); 
    });
}
    

/**
* Adds a listener to handle "Repeat" property change events
* @method Repeat_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgPlaylist1.prototype.Repeat_Changed = function (stateChangedFunction) {
    this.serviceProperties.Repeat.addListener(function (state) 
    { 
        stateChangedFunction(ohnet.soaprequest.readBoolParameter(state)); 
    });
}
    

/**
* Adds a listener to handle "Shuffle" property change events
* @method Shuffle_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgPlaylist1.prototype.Shuffle_Changed = function (stateChangedFunction) {
    this.serviceProperties.Shuffle.addListener(function (state) 
    { 
        stateChangedFunction(ohnet.soaprequest.readBoolParameter(state)); 
    });
}
    

/**
* Adds a listener to handle "Id" property change events
* @method Id_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgPlaylist1.prototype.Id_Changed = function (stateChangedFunction) {
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
CpProxyAvOpenhomeOrgPlaylist1.prototype.IdArray_Changed = function (stateChangedFunction) {
    this.serviceProperties.IdArray.addListener(function (state) 
    { 
        stateChangedFunction(ohnet.soaprequest.readBinaryParameter(state)); 
    });
}
    

/**
* Adds a listener to handle "TracksMax" property change events
* @method TracksMax_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgPlaylist1.prototype.TracksMax_Changed = function (stateChangedFunction) {
    this.serviceProperties.TracksMax.addListener(function (state) 
    { 
        stateChangedFunction(ohnet.soaprequest.readIntParameter(state)); 
    });
}
    

/**
* Adds a listener to handle "ProtocolInfo" property change events
* @method ProtocolInfo_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgPlaylist1.prototype.ProtocolInfo_Changed = function (stateChangedFunction) {
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
CpProxyAvOpenhomeOrgPlaylist1.prototype.Play = function(successFunction, errorFunction){ 
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
CpProxyAvOpenhomeOrgPlaylist1.prototype.Pause = function(successFunction, errorFunction){ 
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
CpProxyAvOpenhomeOrgPlaylist1.prototype.Stop = function(successFunction, errorFunction){ 
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
* A service action to Next
* @method Next
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgPlaylist1.prototype.Next = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("Next", this.url, this.domain, this.type, this.version);     
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
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgPlaylist1.prototype.Previous = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("Previous", this.url, this.domain, this.type, this.version);     
    request.send(function(result){
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to SetRepeat
* @method SetRepeat
* @param {Boolean} Value An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgPlaylist1.prototype.SetRepeat = function(Value, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("SetRepeat", this.url, this.domain, this.type, this.version);     
    request.writeBoolParameter("Value", Value);
    request.send(function(result){
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to Repeat
* @method Repeat
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgPlaylist1.prototype.Repeat = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("Repeat", this.url, this.domain, this.type, this.version);     
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
* A service action to SetShuffle
* @method SetShuffle
* @param {Boolean} Value An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgPlaylist1.prototype.SetShuffle = function(Value, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("SetShuffle", this.url, this.domain, this.type, this.version);     
    request.writeBoolParameter("Value", Value);
    request.send(function(result){
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to Shuffle
* @method Shuffle
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgPlaylist1.prototype.Shuffle = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("Shuffle", this.url, this.domain, this.type, this.version);     
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
* A service action to SeekSecondAbsolute
* @method SeekSecondAbsolute
* @param {Int} Value An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgPlaylist1.prototype.SeekSecondAbsolute = function(Value, successFunction, errorFunction){ 
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
CpProxyAvOpenhomeOrgPlaylist1.prototype.SeekSecondRelative = function(Value, successFunction, errorFunction){ 
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
* A service action to SeekId
* @method SeekId
* @param {Int} Value An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgPlaylist1.prototype.SeekId = function(Value, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("SeekId", this.url, this.domain, this.type, this.version);     
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
* A service action to SeekIndex
* @method SeekIndex
* @param {Int} Value An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgPlaylist1.prototype.SeekIndex = function(Value, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("SeekIndex", this.url, this.domain, this.type, this.version);     
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
* A service action to TransportState
* @method TransportState
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgPlaylist1.prototype.TransportState = function(successFunction, errorFunction){ 
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
CpProxyAvOpenhomeOrgPlaylist1.prototype.Id = function(successFunction, errorFunction){ 
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
* A service action to Read
* @method Read
* @param {Int} Id An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgPlaylist1.prototype.Read = function(Id, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("Read", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("Id", Id);
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
* A service action to ReadList
* @method ReadList
* @param {String} IdList An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgPlaylist1.prototype.ReadList = function(IdList, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("ReadList", this.url, this.domain, this.type, this.version);     
    request.writeStringParameter("IdList", IdList);
    request.send(function(result){
        result["TrackList"] = ohnet.soaprequest.readStringParameter(result["TrackList"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to Insert
* @method Insert
* @param {Int} AfterId An action parameter
* @param {String} Uri An action parameter
* @param {String} Metadata An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgPlaylist1.prototype.Insert = function(AfterId, Uri, Metadata, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("Insert", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("AfterId", AfterId);
    request.writeStringParameter("Uri", Uri);
    request.writeStringParameter("Metadata", Metadata);
    request.send(function(result){
        result["NewId"] = ohnet.soaprequest.readIntParameter(result["NewId"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to DeleteId
* @method DeleteId
* @param {Int} Value An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgPlaylist1.prototype.DeleteId = function(Value, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("DeleteId", this.url, this.domain, this.type, this.version);     
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
* A service action to DeleteAll
* @method DeleteAll
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgPlaylist1.prototype.DeleteAll = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("DeleteAll", this.url, this.domain, this.type, this.version);     
    request.send(function(result){
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to TracksMax
* @method TracksMax
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgPlaylist1.prototype.TracksMax = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("TracksMax", this.url, this.domain, this.type, this.version);     
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
* A service action to IdArray
* @method IdArray
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgPlaylist1.prototype.IdArray = function(successFunction, errorFunction){ 
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
CpProxyAvOpenhomeOrgPlaylist1.prototype.IdArrayChanged = function(Token, successFunction, errorFunction){ 
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
* A service action to ProtocolInfo
* @method ProtocolInfo
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgPlaylist1.prototype.ProtocolInfo = function(successFunction, errorFunction){ 
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



