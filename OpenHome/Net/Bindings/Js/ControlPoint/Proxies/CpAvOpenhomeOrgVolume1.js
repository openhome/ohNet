 

/**
* Service Proxy for CpProxyAvOpenhomeOrgVolume1
* @module ohnet
* @class Volume
*/
    
var CpProxyAvOpenhomeOrgVolume1 = function(udn){ 

    this.url = window.location.protocol + "//" + window.location.host + "/" + udn + "/av.openhome.org-Volume-1/control";  // upnp control url
    this.domain = "av-openhome-org";
    this.type = "Volume";
    this.version = "1";
    this.serviceName = "av.openhome.org-Volume-1";
    this.subscriptionId = "";  // Subscription identifier unique to each Subscription Manager 
    this.udn = udn;   // device name
    
    // Collection of service properties
    this.serviceProperties = {};
    this.serviceProperties["Volume"] = new ohnet.serviceproperty("Volume","int");
    this.serviceProperties["Mute"] = new ohnet.serviceproperty("Mute","bool");
    this.serviceProperties["Balance"] = new ohnet.serviceproperty("Balance","int");
    this.serviceProperties["Fade"] = new ohnet.serviceproperty("Fade","int");
    this.serviceProperties["VolumeLimit"] = new ohnet.serviceproperty("VolumeLimit","int");
    this.serviceProperties["VolumeMax"] = new ohnet.serviceproperty("VolumeMax","int");
    this.serviceProperties["VolumeUnity"] = new ohnet.serviceproperty("VolumeUnity","int");
    this.serviceProperties["VolumeSteps"] = new ohnet.serviceproperty("VolumeSteps","int");
    this.serviceProperties["VolumeMilliDbPerStep"] = new ohnet.serviceproperty("VolumeMilliDbPerStep","int");
    this.serviceProperties["BalanceMax"] = new ohnet.serviceproperty("BalanceMax","int");
    this.serviceProperties["FadeMax"] = new ohnet.serviceproperty("FadeMax","int");

                                                                      
}



/**
* Subscribes the service to the subscription manager to listen for property change events
* @method Subscribe
* @param {Function} serviceAddedFunction The function that executes once the subscription is successful
*/
CpProxyAvOpenhomeOrgVolume1.prototype.subscribe = function (serviceAddedFunction) {
    ohnet.subscriptionmanager.addService(this,serviceAddedFunction);
}


/**
* Unsubscribes the service from the subscription manager to stop listening for property change events
* @method Unsubscribe
*/
CpProxyAvOpenhomeOrgVolume1.prototype.unsubscribe = function () {
    ohnet.subscriptionmanager.removeService(this.subscriptionId);
}


    

/**
* Adds a listener to handle "Volume" property change events
* @method Volume_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgVolume1.prototype.Volume_Changed = function (stateChangedFunction) {
    this.serviceProperties.Volume.addListener(function (state) 
    { 
        stateChangedFunction(ohnet.soaprequest.readIntParameter(state)); 
    });
}
    

/**
* Adds a listener to handle "Mute" property change events
* @method Mute_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgVolume1.prototype.Mute_Changed = function (stateChangedFunction) {
    this.serviceProperties.Mute.addListener(function (state) 
    { 
        stateChangedFunction(ohnet.soaprequest.readBoolParameter(state)); 
    });
}
    

/**
* Adds a listener to handle "Balance" property change events
* @method Balance_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgVolume1.prototype.Balance_Changed = function (stateChangedFunction) {
    this.serviceProperties.Balance.addListener(function (state) 
    { 
        stateChangedFunction(ohnet.soaprequest.readIntParameter(state)); 
    });
}
    

/**
* Adds a listener to handle "Fade" property change events
* @method Fade_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgVolume1.prototype.Fade_Changed = function (stateChangedFunction) {
    this.serviceProperties.Fade.addListener(function (state) 
    { 
        stateChangedFunction(ohnet.soaprequest.readIntParameter(state)); 
    });
}
    

/**
* Adds a listener to handle "VolumeLimit" property change events
* @method VolumeLimit_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgVolume1.prototype.VolumeLimit_Changed = function (stateChangedFunction) {
    this.serviceProperties.VolumeLimit.addListener(function (state) 
    { 
        stateChangedFunction(ohnet.soaprequest.readIntParameter(state)); 
    });
}
    

/**
* Adds a listener to handle "VolumeMax" property change events
* @method VolumeMax_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgVolume1.prototype.VolumeMax_Changed = function (stateChangedFunction) {
    this.serviceProperties.VolumeMax.addListener(function (state) 
    { 
        stateChangedFunction(ohnet.soaprequest.readIntParameter(state)); 
    });
}
    

/**
* Adds a listener to handle "VolumeUnity" property change events
* @method VolumeUnity_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgVolume1.prototype.VolumeUnity_Changed = function (stateChangedFunction) {
    this.serviceProperties.VolumeUnity.addListener(function (state) 
    { 
        stateChangedFunction(ohnet.soaprequest.readIntParameter(state)); 
    });
}
    

/**
* Adds a listener to handle "VolumeSteps" property change events
* @method VolumeSteps_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgVolume1.prototype.VolumeSteps_Changed = function (stateChangedFunction) {
    this.serviceProperties.VolumeSteps.addListener(function (state) 
    { 
        stateChangedFunction(ohnet.soaprequest.readIntParameter(state)); 
    });
}
    

/**
* Adds a listener to handle "VolumeMilliDbPerStep" property change events
* @method VolumeMilliDbPerStep_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgVolume1.prototype.VolumeMilliDbPerStep_Changed = function (stateChangedFunction) {
    this.serviceProperties.VolumeMilliDbPerStep.addListener(function (state) 
    { 
        stateChangedFunction(ohnet.soaprequest.readIntParameter(state)); 
    });
}
    

/**
* Adds a listener to handle "BalanceMax" property change events
* @method BalanceMax_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgVolume1.prototype.BalanceMax_Changed = function (stateChangedFunction) {
    this.serviceProperties.BalanceMax.addListener(function (state) 
    { 
        stateChangedFunction(ohnet.soaprequest.readIntParameter(state)); 
    });
}
    

/**
* Adds a listener to handle "FadeMax" property change events
* @method FadeMax_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgVolume1.prototype.FadeMax_Changed = function (stateChangedFunction) {
    this.serviceProperties.FadeMax.addListener(function (state) 
    { 
        stateChangedFunction(ohnet.soaprequest.readIntParameter(state)); 
    });
}


/**
* A service action to Characteristics
* @method Characteristics
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgVolume1.prototype.Characteristics = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("Characteristics", this.url, this.domain, this.type, this.version);     
    request.send(function(result){
        result["VolumeMax"] = ohnet.soaprequest.readIntParameter(result["VolumeMax"]); 
        result["VolumeUnity"] = ohnet.soaprequest.readIntParameter(result["VolumeUnity"]); 
        result["VolumeSteps"] = ohnet.soaprequest.readIntParameter(result["VolumeSteps"]); 
        result["VolumeMilliDbPerStep"] = ohnet.soaprequest.readIntParameter(result["VolumeMilliDbPerStep"]); 
        result["BalanceMax"] = ohnet.soaprequest.readIntParameter(result["BalanceMax"]); 
        result["FadeMax"] = ohnet.soaprequest.readIntParameter(result["FadeMax"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to SetVolume
* @method SetVolume
* @param {Int} Value An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgVolume1.prototype.SetVolume = function(Value, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("SetVolume", this.url, this.domain, this.type, this.version);     
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
* A service action to VolumeInc
* @method VolumeInc
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgVolume1.prototype.VolumeInc = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("VolumeInc", this.url, this.domain, this.type, this.version);     
    request.send(function(result){
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to VolumeDec
* @method VolumeDec
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgVolume1.prototype.VolumeDec = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("VolumeDec", this.url, this.domain, this.type, this.version);     
    request.send(function(result){
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to Volume
* @method Volume
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgVolume1.prototype.Volume = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("Volume", this.url, this.domain, this.type, this.version);     
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
* A service action to SetBalance
* @method SetBalance
* @param {Int} Value An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgVolume1.prototype.SetBalance = function(Value, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("SetBalance", this.url, this.domain, this.type, this.version);     
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
* A service action to BalanceInc
* @method BalanceInc
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgVolume1.prototype.BalanceInc = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("BalanceInc", this.url, this.domain, this.type, this.version);     
    request.send(function(result){
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to BalanceDec
* @method BalanceDec
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgVolume1.prototype.BalanceDec = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("BalanceDec", this.url, this.domain, this.type, this.version);     
    request.send(function(result){
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to Balance
* @method Balance
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgVolume1.prototype.Balance = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("Balance", this.url, this.domain, this.type, this.version);     
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
* A service action to SetFade
* @method SetFade
* @param {Int} Value An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgVolume1.prototype.SetFade = function(Value, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("SetFade", this.url, this.domain, this.type, this.version);     
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
* A service action to FadeInc
* @method FadeInc
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgVolume1.prototype.FadeInc = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("FadeInc", this.url, this.domain, this.type, this.version);     
    request.send(function(result){
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to FadeDec
* @method FadeDec
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgVolume1.prototype.FadeDec = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("FadeDec", this.url, this.domain, this.type, this.version);     
    request.send(function(result){
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to Fade
* @method Fade
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgVolume1.prototype.Fade = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("Fade", this.url, this.domain, this.type, this.version);     
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
* A service action to SetMute
* @method SetMute
* @param {Boolean} Value An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgVolume1.prototype.SetMute = function(Value, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("SetMute", this.url, this.domain, this.type, this.version);     
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
* A service action to Mute
* @method Mute
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgVolume1.prototype.Mute = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("Mute", this.url, this.domain, this.type, this.version);     
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
* A service action to VolumeLimit
* @method VolumeLimit
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgVolume1.prototype.VolumeLimit = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("VolumeLimit", this.url, this.domain, this.type, this.version);     
    request.send(function(result){
        result["Value"] = ohnet.soaprequest.readIntParameter(result["Value"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}



