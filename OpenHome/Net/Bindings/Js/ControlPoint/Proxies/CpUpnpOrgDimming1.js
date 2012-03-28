 

/**
* Service Proxy for CpProxySchemasUpnpOrgDimming1
* @module ohnet
* @class Dimming
*/
    
var CpProxySchemasUpnpOrgDimming1 = function(udn){ 

    this.url = window.location.protocol + "//" + window.location.host + "/" + udn + "/upnp.org-Dimming-1/control";  // upnp control url
    this.domain = "schemas-upnp-org";
    this.type = "Dimming";
    this.version = "1";
    this.serviceName = "upnp.org-Dimming-1";
    this.subscriptionId = "";  // Subscription identifier unique to each Subscription Manager 
    this.udn = udn;   // device name
    
    // Collection of service properties
    this.serviceProperties = {};
    this.serviceProperties["LoadLevelStatus"] = new ohnet.serviceproperty("LoadLevelStatus","int");
    this.serviceProperties["StepDelta"] = new ohnet.serviceproperty("StepDelta","int");
    this.serviceProperties["RampRate"] = new ohnet.serviceproperty("RampRate","int");
    this.serviceProperties["IsRamping"] = new ohnet.serviceproperty("IsRamping","bool");
    this.serviceProperties["RampPaused"] = new ohnet.serviceproperty("RampPaused","bool");

                                  
}



/**
* Subscribes the service to the subscription manager to listen for property change events
* @method Subscribe
* @param {Function} serviceAddedFunction The function that executes once the subscription is successful
*/
CpProxySchemasUpnpOrgDimming1.prototype.subscribe = function (serviceAddedFunction) {
    ohnet.subscriptionmanager.addService(this,serviceAddedFunction);
}


/**
* Unsubscribes the service from the subscription manager to stop listening for property change events
* @method Unsubscribe
*/
CpProxySchemasUpnpOrgDimming1.prototype.unsubscribe = function () {
    ohnet.subscriptionmanager.removeService(this.subscriptionId);
}


    

/**
* Adds a listener to handle "LoadLevelStatus" property change events
* @method LoadLevelStatus_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxySchemasUpnpOrgDimming1.prototype.LoadLevelStatus_Changed = function (stateChangedFunction) {
    this.serviceProperties.LoadLevelStatus.addListener(function (state) 
    { 
        stateChangedFunction(ohnet.soaprequest.readIntParameter(state)); 
    });
}
    

/**
* Adds a listener to handle "StepDelta" property change events
* @method StepDelta_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxySchemasUpnpOrgDimming1.prototype.StepDelta_Changed = function (stateChangedFunction) {
    this.serviceProperties.StepDelta.addListener(function (state) 
    { 
        stateChangedFunction(ohnet.soaprequest.readIntParameter(state)); 
    });
}
    

/**
* Adds a listener to handle "RampRate" property change events
* @method RampRate_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxySchemasUpnpOrgDimming1.prototype.RampRate_Changed = function (stateChangedFunction) {
    this.serviceProperties.RampRate.addListener(function (state) 
    { 
        stateChangedFunction(ohnet.soaprequest.readIntParameter(state)); 
    });
}
    

/**
* Adds a listener to handle "IsRamping" property change events
* @method IsRamping_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxySchemasUpnpOrgDimming1.prototype.IsRamping_Changed = function (stateChangedFunction) {
    this.serviceProperties.IsRamping.addListener(function (state) 
    { 
        stateChangedFunction(ohnet.soaprequest.readBoolParameter(state)); 
    });
}
    

/**
* Adds a listener to handle "RampPaused" property change events
* @method RampPaused_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxySchemasUpnpOrgDimming1.prototype.RampPaused_Changed = function (stateChangedFunction) {
    this.serviceProperties.RampPaused.addListener(function (state) 
    { 
        stateChangedFunction(ohnet.soaprequest.readBoolParameter(state)); 
    });
}


/**
* A service action to SetLoadLevelTarget
* @method SetLoadLevelTarget
* @param {Int} newLoadlevelTarget An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgDimming1.prototype.SetLoadLevelTarget = function(newLoadlevelTarget, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("SetLoadLevelTarget", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("newLoadlevelTarget", newLoadlevelTarget);
    request.send(function(result){
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to GetLoadLevelTarget
* @method GetLoadLevelTarget
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgDimming1.prototype.GetLoadLevelTarget = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("GetLoadLevelTarget", this.url, this.domain, this.type, this.version);     
    request.send(function(result){
        result["GetLoadlevelTarget"] = ohnet.soaprequest.readIntParameter(result["GetLoadlevelTarget"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to GetLoadLevelStatus
* @method GetLoadLevelStatus
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgDimming1.prototype.GetLoadLevelStatus = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("GetLoadLevelStatus", this.url, this.domain, this.type, this.version);     
    request.send(function(result){
        result["retLoadlevelStatus"] = ohnet.soaprequest.readIntParameter(result["retLoadlevelStatus"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to SetOnEffectLevel
* @method SetOnEffectLevel
* @param {Int} newOnEffectLevel An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgDimming1.prototype.SetOnEffectLevel = function(newOnEffectLevel, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("SetOnEffectLevel", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("newOnEffectLevel", newOnEffectLevel);
    request.send(function(result){
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to SetOnEffect
* @method SetOnEffect
* @param {String} newOnEffect An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgDimming1.prototype.SetOnEffect = function(newOnEffect, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("SetOnEffect", this.url, this.domain, this.type, this.version);     
    request.writeStringParameter("newOnEffect", newOnEffect);
    request.send(function(result){
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to GetOnEffectParameters
* @method GetOnEffectParameters
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgDimming1.prototype.GetOnEffectParameters = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("GetOnEffectParameters", this.url, this.domain, this.type, this.version);     
    request.send(function(result){
        result["retOnEffect"] = ohnet.soaprequest.readStringParameter(result["retOnEffect"]); 
        result["retOnEffectLevel"] = ohnet.soaprequest.readIntParameter(result["retOnEffectLevel"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to StepUp
* @method StepUp
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgDimming1.prototype.StepUp = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("StepUp", this.url, this.domain, this.type, this.version);     
    request.send(function(result){
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to StepDown
* @method StepDown
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgDimming1.prototype.StepDown = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("StepDown", this.url, this.domain, this.type, this.version);     
    request.send(function(result){
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to StartRampUp
* @method StartRampUp
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgDimming1.prototype.StartRampUp = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("StartRampUp", this.url, this.domain, this.type, this.version);     
    request.send(function(result){
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to StartRampDown
* @method StartRampDown
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgDimming1.prototype.StartRampDown = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("StartRampDown", this.url, this.domain, this.type, this.version);     
    request.send(function(result){
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to StopRamp
* @method StopRamp
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgDimming1.prototype.StopRamp = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("StopRamp", this.url, this.domain, this.type, this.version);     
    request.send(function(result){
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to StartRampToLevel
* @method StartRampToLevel
* @param {Int} newLoadLevelTarget An action parameter
* @param {Int} newRampTime An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgDimming1.prototype.StartRampToLevel = function(newLoadLevelTarget, newRampTime, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("StartRampToLevel", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("newLoadLevelTarget", newLoadLevelTarget);
    request.writeIntParameter("newRampTime", newRampTime);
    request.send(function(result){
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to SetStepDelta
* @method SetStepDelta
* @param {Int} newStepDelta An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgDimming1.prototype.SetStepDelta = function(newStepDelta, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("SetStepDelta", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("newStepDelta", newStepDelta);
    request.send(function(result){
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to GetStepDelta
* @method GetStepDelta
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgDimming1.prototype.GetStepDelta = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("GetStepDelta", this.url, this.domain, this.type, this.version);     
    request.send(function(result){
        result["retStepDelta"] = ohnet.soaprequest.readIntParameter(result["retStepDelta"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to SetRampRate
* @method SetRampRate
* @param {Int} newRampRate An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgDimming1.prototype.SetRampRate = function(newRampRate, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("SetRampRate", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("newRampRate", newRampRate);
    request.send(function(result){
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to GetRampRate
* @method GetRampRate
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgDimming1.prototype.GetRampRate = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("GetRampRate", this.url, this.domain, this.type, this.version);     
    request.send(function(result){
        result["retRampRate"] = ohnet.soaprequest.readIntParameter(result["retRampRate"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to PauseRamp
* @method PauseRamp
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgDimming1.prototype.PauseRamp = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("PauseRamp", this.url, this.domain, this.type, this.version);     
    request.send(function(result){
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to ResumeRamp
* @method ResumeRamp
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgDimming1.prototype.ResumeRamp = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("ResumeRamp", this.url, this.domain, this.type, this.version);     
    request.send(function(result){
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to GetIsRamping
* @method GetIsRamping
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgDimming1.prototype.GetIsRamping = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("GetIsRamping", this.url, this.domain, this.type, this.version);     
    request.send(function(result){
        result["retIsRamping"] = ohnet.soaprequest.readBoolParameter(result["retIsRamping"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to GetRampPaused
* @method GetRampPaused
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgDimming1.prototype.GetRampPaused = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("GetRampPaused", this.url, this.domain, this.type, this.version);     
    request.send(function(result){
        result["retRampPaused"] = ohnet.soaprequest.readBoolParameter(result["retRampPaused"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to GetRampTime
* @method GetRampTime
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgDimming1.prototype.GetRampTime = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("GetRampTime", this.url, this.domain, this.type, this.version);     
    request.send(function(result){
        result["retRampTime"] = ohnet.soaprequest.readIntParameter(result["retRampTime"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}



