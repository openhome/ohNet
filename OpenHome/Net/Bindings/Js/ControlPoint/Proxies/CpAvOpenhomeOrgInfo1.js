 

/**
* Service Proxy for CpProxyAvOpenhomeOrgInfo1
* @module ohnet
* @class Info
*/
    
var CpProxyAvOpenhomeOrgInfo1 = function(udn){ 

    this.url = window.location.protocol + "//" + window.location.host + "/" + udn + "/av.openhome.org-Info-1/control";  // upnp control url
    this.domain = "av-openhome-org";
    this.type = "Info";
    this.version = "1";
    this.serviceName = "av.openhome.org-Info-1";
    this.subscriptionId = "";  // Subscription identifier unique to each Subscription Manager 
    this.udn = udn;   // device name
    
    // Collection of service properties
    this.serviceProperties = {};
    this.serviceProperties["TrackCount"] = new ohnet.serviceproperty("TrackCount","int");
    this.serviceProperties["DetailsCount"] = new ohnet.serviceproperty("DetailsCount","int");
    this.serviceProperties["MetatextCount"] = new ohnet.serviceproperty("MetatextCount","int");
    this.serviceProperties["Uri"] = new ohnet.serviceproperty("Uri","string");
    this.serviceProperties["Metadata"] = new ohnet.serviceproperty("Metadata","string");
    this.serviceProperties["Duration"] = new ohnet.serviceproperty("Duration","int");
    this.serviceProperties["BitRate"] = new ohnet.serviceproperty("BitRate","int");
    this.serviceProperties["BitDepth"] = new ohnet.serviceproperty("BitDepth","int");
    this.serviceProperties["SampleRate"] = new ohnet.serviceproperty("SampleRate","int");
    this.serviceProperties["Lossless"] = new ohnet.serviceproperty("Lossless","bool");
    this.serviceProperties["CodecName"] = new ohnet.serviceproperty("CodecName","string");
    this.serviceProperties["Metatext"] = new ohnet.serviceproperty("Metatext","string");

                                                                            
}



/**
* Subscribes the service to the subscription manager to listen for property change events
* @method Subscribe
* @param {Function} serviceAddedFunction The function that executes once the subscription is successful
*/
CpProxyAvOpenhomeOrgInfo1.prototype.subscribe = function (serviceAddedFunction) {
    ohnet.subscriptionmanager.addService(this,serviceAddedFunction);
}


/**
* Unsubscribes the service from the subscription manager to stop listening for property change events
* @method Unsubscribe
*/
CpProxyAvOpenhomeOrgInfo1.prototype.unsubscribe = function () {
    ohnet.subscriptionmanager.removeService(this.subscriptionId);
}


    

/**
* Adds a listener to handle "TrackCount" property change events
* @method TrackCount_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgInfo1.prototype.TrackCount_Changed = function (stateChangedFunction) {
    this.serviceProperties.TrackCount.addListener(function (state) 
    { 
        stateChangedFunction(ohnet.soaprequest.readIntParameter(state)); 
    });
}
    

/**
* Adds a listener to handle "DetailsCount" property change events
* @method DetailsCount_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgInfo1.prototype.DetailsCount_Changed = function (stateChangedFunction) {
    this.serviceProperties.DetailsCount.addListener(function (state) 
    { 
        stateChangedFunction(ohnet.soaprequest.readIntParameter(state)); 
    });
}
    

/**
* Adds a listener to handle "MetatextCount" property change events
* @method MetatextCount_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgInfo1.prototype.MetatextCount_Changed = function (stateChangedFunction) {
    this.serviceProperties.MetatextCount.addListener(function (state) 
    { 
        stateChangedFunction(ohnet.soaprequest.readIntParameter(state)); 
    });
}
    

/**
* Adds a listener to handle "Uri" property change events
* @method Uri_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgInfo1.prototype.Uri_Changed = function (stateChangedFunction) {
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
CpProxyAvOpenhomeOrgInfo1.prototype.Metadata_Changed = function (stateChangedFunction) {
    this.serviceProperties.Metadata.addListener(function (state) 
    { 
        stateChangedFunction(ohnet.soaprequest.readStringParameter(state)); 
    });
}
    

/**
* Adds a listener to handle "Duration" property change events
* @method Duration_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgInfo1.prototype.Duration_Changed = function (stateChangedFunction) {
    this.serviceProperties.Duration.addListener(function (state) 
    { 
        stateChangedFunction(ohnet.soaprequest.readIntParameter(state)); 
    });
}
    

/**
* Adds a listener to handle "BitRate" property change events
* @method BitRate_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgInfo1.prototype.BitRate_Changed = function (stateChangedFunction) {
    this.serviceProperties.BitRate.addListener(function (state) 
    { 
        stateChangedFunction(ohnet.soaprequest.readIntParameter(state)); 
    });
}
    

/**
* Adds a listener to handle "BitDepth" property change events
* @method BitDepth_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgInfo1.prototype.BitDepth_Changed = function (stateChangedFunction) {
    this.serviceProperties.BitDepth.addListener(function (state) 
    { 
        stateChangedFunction(ohnet.soaprequest.readIntParameter(state)); 
    });
}
    

/**
* Adds a listener to handle "SampleRate" property change events
* @method SampleRate_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgInfo1.prototype.SampleRate_Changed = function (stateChangedFunction) {
    this.serviceProperties.SampleRate.addListener(function (state) 
    { 
        stateChangedFunction(ohnet.soaprequest.readIntParameter(state)); 
    });
}
    

/**
* Adds a listener to handle "Lossless" property change events
* @method Lossless_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgInfo1.prototype.Lossless_Changed = function (stateChangedFunction) {
    this.serviceProperties.Lossless.addListener(function (state) 
    { 
        stateChangedFunction(ohnet.soaprequest.readBoolParameter(state)); 
    });
}
    

/**
* Adds a listener to handle "CodecName" property change events
* @method CodecName_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgInfo1.prototype.CodecName_Changed = function (stateChangedFunction) {
    this.serviceProperties.CodecName.addListener(function (state) 
    { 
        stateChangedFunction(ohnet.soaprequest.readStringParameter(state)); 
    });
}
    

/**
* Adds a listener to handle "Metatext" property change events
* @method Metatext_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgInfo1.prototype.Metatext_Changed = function (stateChangedFunction) {
    this.serviceProperties.Metatext.addListener(function (state) 
    { 
        stateChangedFunction(ohnet.soaprequest.readStringParameter(state)); 
    });
}


/**
* A service action to Counters
* @method Counters
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgInfo1.prototype.Counters = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("Counters", this.url, this.domain, this.type, this.version);     
    request.send(function(result){
        result["TrackCount"] = ohnet.soaprequest.readIntParameter(result["TrackCount"]); 
        result["DetailsCount"] = ohnet.soaprequest.readIntParameter(result["DetailsCount"]); 
        result["MetatextCount"] = ohnet.soaprequest.readIntParameter(result["MetatextCount"]); 
    
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
CpProxyAvOpenhomeOrgInfo1.prototype.Track = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("Track", this.url, this.domain, this.type, this.version);     
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
* A service action to Details
* @method Details
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgInfo1.prototype.Details = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("Details", this.url, this.domain, this.type, this.version);     
    request.send(function(result){
        result["Duration"] = ohnet.soaprequest.readIntParameter(result["Duration"]); 
        result["BitRate"] = ohnet.soaprequest.readIntParameter(result["BitRate"]); 
        result["BitDepth"] = ohnet.soaprequest.readIntParameter(result["BitDepth"]); 
        result["SampleRate"] = ohnet.soaprequest.readIntParameter(result["SampleRate"]); 
        result["Lossless"] = ohnet.soaprequest.readBoolParameter(result["Lossless"]); 
        result["CodecName"] = ohnet.soaprequest.readStringParameter(result["CodecName"]); 
    
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
CpProxyAvOpenhomeOrgInfo1.prototype.Metatext = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("Metatext", this.url, this.domain, this.type, this.version);     
    request.send(function(result){
        result["Value"] = ohnet.soaprequest.readStringParameter(result["Value"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}



