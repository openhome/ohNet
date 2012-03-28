 

/**
* Service Proxy for CpProxySchemasUpnpOrgRenderingControl2
* @module ohnet
* @class RenderingControl
*/
    
var CpProxySchemasUpnpOrgRenderingControl2 = function(udn){ 

    this.url = window.location.protocol + "//" + window.location.host + "/" + udn + "/upnp.org-RenderingControl-2/control";  // upnp control url
    this.domain = "schemas-upnp-org";
    this.type = "RenderingControl";
    this.version = "2";
    this.serviceName = "upnp.org-RenderingControl-2";
    this.subscriptionId = "";  // Subscription identifier unique to each Subscription Manager 
    this.udn = udn;   // device name
    
    // Collection of service properties
    this.serviceProperties = {};
    this.serviceProperties["LastChange"] = new ohnet.serviceproperty("LastChange","string");

          
}



/**
* Subscribes the service to the subscription manager to listen for property change events
* @method Subscribe
* @param {Function} serviceAddedFunction The function that executes once the subscription is successful
*/
CpProxySchemasUpnpOrgRenderingControl2.prototype.subscribe = function (serviceAddedFunction) {
    ohnet.subscriptionmanager.addService(this,serviceAddedFunction);
}


/**
* Unsubscribes the service from the subscription manager to stop listening for property change events
* @method Unsubscribe
*/
CpProxySchemasUpnpOrgRenderingControl2.prototype.unsubscribe = function () {
    ohnet.subscriptionmanager.removeService(this.subscriptionId);
}


    

/**
* Adds a listener to handle "LastChange" property change events
* @method LastChange_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxySchemasUpnpOrgRenderingControl2.prototype.LastChange_Changed = function (stateChangedFunction) {
    this.serviceProperties.LastChange.addListener(function (state) 
    { 
        stateChangedFunction(ohnet.soaprequest.readStringParameter(state)); 
    });
}


/**
* A service action to ListPresets
* @method ListPresets
* @param {Int} InstanceID An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgRenderingControl2.prototype.ListPresets = function(InstanceID, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("ListPresets", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("InstanceID", InstanceID);
    request.send(function(result){
        result["CurrentPresetNameList"] = ohnet.soaprequest.readStringParameter(result["CurrentPresetNameList"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to SelectPreset
* @method SelectPreset
* @param {Int} InstanceID An action parameter
* @param {String} PresetName An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgRenderingControl2.prototype.SelectPreset = function(InstanceID, PresetName, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("SelectPreset", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("InstanceID", InstanceID);
    request.writeStringParameter("PresetName", PresetName);
    request.send(function(result){
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to GetBrightness
* @method GetBrightness
* @param {Int} InstanceID An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgRenderingControl2.prototype.GetBrightness = function(InstanceID, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("GetBrightness", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("InstanceID", InstanceID);
    request.send(function(result){
        result["CurrentBrightness"] = ohnet.soaprequest.readIntParameter(result["CurrentBrightness"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to SetBrightness
* @method SetBrightness
* @param {Int} InstanceID An action parameter
* @param {Int} DesiredBrightness An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgRenderingControl2.prototype.SetBrightness = function(InstanceID, DesiredBrightness, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("SetBrightness", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("InstanceID", InstanceID);
    request.writeIntParameter("DesiredBrightness", DesiredBrightness);
    request.send(function(result){
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to GetContrast
* @method GetContrast
* @param {Int} InstanceID An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgRenderingControl2.prototype.GetContrast = function(InstanceID, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("GetContrast", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("InstanceID", InstanceID);
    request.send(function(result){
        result["CurrentContrast"] = ohnet.soaprequest.readIntParameter(result["CurrentContrast"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to SetContrast
* @method SetContrast
* @param {Int} InstanceID An action parameter
* @param {Int} DesiredContrast An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgRenderingControl2.prototype.SetContrast = function(InstanceID, DesiredContrast, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("SetContrast", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("InstanceID", InstanceID);
    request.writeIntParameter("DesiredContrast", DesiredContrast);
    request.send(function(result){
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to GetSharpness
* @method GetSharpness
* @param {Int} InstanceID An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgRenderingControl2.prototype.GetSharpness = function(InstanceID, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("GetSharpness", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("InstanceID", InstanceID);
    request.send(function(result){
        result["CurrentSharpness"] = ohnet.soaprequest.readIntParameter(result["CurrentSharpness"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to SetSharpness
* @method SetSharpness
* @param {Int} InstanceID An action parameter
* @param {Int} DesiredSharpness An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgRenderingControl2.prototype.SetSharpness = function(InstanceID, DesiredSharpness, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("SetSharpness", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("InstanceID", InstanceID);
    request.writeIntParameter("DesiredSharpness", DesiredSharpness);
    request.send(function(result){
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to GetRedVideoGain
* @method GetRedVideoGain
* @param {Int} InstanceID An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgRenderingControl2.prototype.GetRedVideoGain = function(InstanceID, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("GetRedVideoGain", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("InstanceID", InstanceID);
    request.send(function(result){
        result["CurrentRedVideoGain"] = ohnet.soaprequest.readIntParameter(result["CurrentRedVideoGain"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to SetRedVideoGain
* @method SetRedVideoGain
* @param {Int} InstanceID An action parameter
* @param {Int} DesiredRedVideoGain An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgRenderingControl2.prototype.SetRedVideoGain = function(InstanceID, DesiredRedVideoGain, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("SetRedVideoGain", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("InstanceID", InstanceID);
    request.writeIntParameter("DesiredRedVideoGain", DesiredRedVideoGain);
    request.send(function(result){
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to GetGreenVideoGain
* @method GetGreenVideoGain
* @param {Int} InstanceID An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgRenderingControl2.prototype.GetGreenVideoGain = function(InstanceID, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("GetGreenVideoGain", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("InstanceID", InstanceID);
    request.send(function(result){
        result["CurrentGreenVideoGain"] = ohnet.soaprequest.readIntParameter(result["CurrentGreenVideoGain"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to SetGreenVideoGain
* @method SetGreenVideoGain
* @param {Int} InstanceID An action parameter
* @param {Int} DesiredGreenVideoGain An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgRenderingControl2.prototype.SetGreenVideoGain = function(InstanceID, DesiredGreenVideoGain, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("SetGreenVideoGain", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("InstanceID", InstanceID);
    request.writeIntParameter("DesiredGreenVideoGain", DesiredGreenVideoGain);
    request.send(function(result){
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to GetBlueVideoGain
* @method GetBlueVideoGain
* @param {Int} InstanceID An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgRenderingControl2.prototype.GetBlueVideoGain = function(InstanceID, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("GetBlueVideoGain", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("InstanceID", InstanceID);
    request.send(function(result){
        result["CurrentBlueVideoGain"] = ohnet.soaprequest.readIntParameter(result["CurrentBlueVideoGain"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to SetBlueVideoGain
* @method SetBlueVideoGain
* @param {Int} InstanceID An action parameter
* @param {Int} DesiredBlueVideoGain An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgRenderingControl2.prototype.SetBlueVideoGain = function(InstanceID, DesiredBlueVideoGain, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("SetBlueVideoGain", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("InstanceID", InstanceID);
    request.writeIntParameter("DesiredBlueVideoGain", DesiredBlueVideoGain);
    request.send(function(result){
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to GetRedVideoBlackLevel
* @method GetRedVideoBlackLevel
* @param {Int} InstanceID An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgRenderingControl2.prototype.GetRedVideoBlackLevel = function(InstanceID, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("GetRedVideoBlackLevel", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("InstanceID", InstanceID);
    request.send(function(result){
        result["CurrentRedVideoBlackLevel"] = ohnet.soaprequest.readIntParameter(result["CurrentRedVideoBlackLevel"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to SetRedVideoBlackLevel
* @method SetRedVideoBlackLevel
* @param {Int} InstanceID An action parameter
* @param {Int} DesiredRedVideoBlackLevel An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgRenderingControl2.prototype.SetRedVideoBlackLevel = function(InstanceID, DesiredRedVideoBlackLevel, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("SetRedVideoBlackLevel", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("InstanceID", InstanceID);
    request.writeIntParameter("DesiredRedVideoBlackLevel", DesiredRedVideoBlackLevel);
    request.send(function(result){
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to GetGreenVideoBlackLevel
* @method GetGreenVideoBlackLevel
* @param {Int} InstanceID An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgRenderingControl2.prototype.GetGreenVideoBlackLevel = function(InstanceID, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("GetGreenVideoBlackLevel", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("InstanceID", InstanceID);
    request.send(function(result){
        result["CurrentGreenVideoBlackLevel"] = ohnet.soaprequest.readIntParameter(result["CurrentGreenVideoBlackLevel"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to SetGreenVideoBlackLevel
* @method SetGreenVideoBlackLevel
* @param {Int} InstanceID An action parameter
* @param {Int} DesiredGreenVideoBlackLevel An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgRenderingControl2.prototype.SetGreenVideoBlackLevel = function(InstanceID, DesiredGreenVideoBlackLevel, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("SetGreenVideoBlackLevel", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("InstanceID", InstanceID);
    request.writeIntParameter("DesiredGreenVideoBlackLevel", DesiredGreenVideoBlackLevel);
    request.send(function(result){
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to GetBlueVideoBlackLevel
* @method GetBlueVideoBlackLevel
* @param {Int} InstanceID An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgRenderingControl2.prototype.GetBlueVideoBlackLevel = function(InstanceID, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("GetBlueVideoBlackLevel", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("InstanceID", InstanceID);
    request.send(function(result){
        result["CurrentBlueVideoBlackLevel"] = ohnet.soaprequest.readIntParameter(result["CurrentBlueVideoBlackLevel"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to SetBlueVideoBlackLevel
* @method SetBlueVideoBlackLevel
* @param {Int} InstanceID An action parameter
* @param {Int} DesiredBlueVideoBlackLevel An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgRenderingControl2.prototype.SetBlueVideoBlackLevel = function(InstanceID, DesiredBlueVideoBlackLevel, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("SetBlueVideoBlackLevel", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("InstanceID", InstanceID);
    request.writeIntParameter("DesiredBlueVideoBlackLevel", DesiredBlueVideoBlackLevel);
    request.send(function(result){
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to GetColorTemperature
* @method GetColorTemperature
* @param {Int} InstanceID An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgRenderingControl2.prototype.GetColorTemperature = function(InstanceID, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("GetColorTemperature", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("InstanceID", InstanceID);
    request.send(function(result){
        result["CurrentColorTemperature"] = ohnet.soaprequest.readIntParameter(result["CurrentColorTemperature"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to SetColorTemperature
* @method SetColorTemperature
* @param {Int} InstanceID An action parameter
* @param {Int} DesiredColorTemperature An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgRenderingControl2.prototype.SetColorTemperature = function(InstanceID, DesiredColorTemperature, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("SetColorTemperature", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("InstanceID", InstanceID);
    request.writeIntParameter("DesiredColorTemperature", DesiredColorTemperature);
    request.send(function(result){
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to GetHorizontalKeystone
* @method GetHorizontalKeystone
* @param {Int} InstanceID An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgRenderingControl2.prototype.GetHorizontalKeystone = function(InstanceID, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("GetHorizontalKeystone", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("InstanceID", InstanceID);
    request.send(function(result){
        result["CurrentHorizontalKeystone"] = ohnet.soaprequest.readIntParameter(result["CurrentHorizontalKeystone"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to SetHorizontalKeystone
* @method SetHorizontalKeystone
* @param {Int} InstanceID An action parameter
* @param {Int} DesiredHorizontalKeystone An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgRenderingControl2.prototype.SetHorizontalKeystone = function(InstanceID, DesiredHorizontalKeystone, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("SetHorizontalKeystone", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("InstanceID", InstanceID);
    request.writeIntParameter("DesiredHorizontalKeystone", DesiredHorizontalKeystone);
    request.send(function(result){
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to GetVerticalKeystone
* @method GetVerticalKeystone
* @param {Int} InstanceID An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgRenderingControl2.prototype.GetVerticalKeystone = function(InstanceID, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("GetVerticalKeystone", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("InstanceID", InstanceID);
    request.send(function(result){
        result["CurrentVerticalKeystone"] = ohnet.soaprequest.readIntParameter(result["CurrentVerticalKeystone"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to SetVerticalKeystone
* @method SetVerticalKeystone
* @param {Int} InstanceID An action parameter
* @param {Int} DesiredVerticalKeystone An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgRenderingControl2.prototype.SetVerticalKeystone = function(InstanceID, DesiredVerticalKeystone, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("SetVerticalKeystone", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("InstanceID", InstanceID);
    request.writeIntParameter("DesiredVerticalKeystone", DesiredVerticalKeystone);
    request.send(function(result){
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to GetMute
* @method GetMute
* @param {Int} InstanceID An action parameter
* @param {String} Channel An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgRenderingControl2.prototype.GetMute = function(InstanceID, Channel, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("GetMute", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("InstanceID", InstanceID);
    request.writeStringParameter("Channel", Channel);
    request.send(function(result){
        result["CurrentMute"] = ohnet.soaprequest.readBoolParameter(result["CurrentMute"]); 
    
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
* @param {Int} InstanceID An action parameter
* @param {String} Channel An action parameter
* @param {Boolean} DesiredMute An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgRenderingControl2.prototype.SetMute = function(InstanceID, Channel, DesiredMute, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("SetMute", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("InstanceID", InstanceID);
    request.writeStringParameter("Channel", Channel);
    request.writeBoolParameter("DesiredMute", DesiredMute);
    request.send(function(result){
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to GetVolume
* @method GetVolume
* @param {Int} InstanceID An action parameter
* @param {String} Channel An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgRenderingControl2.prototype.GetVolume = function(InstanceID, Channel, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("GetVolume", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("InstanceID", InstanceID);
    request.writeStringParameter("Channel", Channel);
    request.send(function(result){
        result["CurrentVolume"] = ohnet.soaprequest.readIntParameter(result["CurrentVolume"]); 
    
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
* @param {Int} InstanceID An action parameter
* @param {String} Channel An action parameter
* @param {Int} DesiredVolume An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgRenderingControl2.prototype.SetVolume = function(InstanceID, Channel, DesiredVolume, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("SetVolume", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("InstanceID", InstanceID);
    request.writeStringParameter("Channel", Channel);
    request.writeIntParameter("DesiredVolume", DesiredVolume);
    request.send(function(result){
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to GetVolumeDB
* @method GetVolumeDB
* @param {Int} InstanceID An action parameter
* @param {String} Channel An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgRenderingControl2.prototype.GetVolumeDB = function(InstanceID, Channel, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("GetVolumeDB", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("InstanceID", InstanceID);
    request.writeStringParameter("Channel", Channel);
    request.send(function(result){
        result["CurrentVolume"] = ohnet.soaprequest.readIntParameter(result["CurrentVolume"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to SetVolumeDB
* @method SetVolumeDB
* @param {Int} InstanceID An action parameter
* @param {String} Channel An action parameter
* @param {Int} DesiredVolume An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgRenderingControl2.prototype.SetVolumeDB = function(InstanceID, Channel, DesiredVolume, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("SetVolumeDB", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("InstanceID", InstanceID);
    request.writeStringParameter("Channel", Channel);
    request.writeIntParameter("DesiredVolume", DesiredVolume);
    request.send(function(result){
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to GetVolumeDBRange
* @method GetVolumeDBRange
* @param {Int} InstanceID An action parameter
* @param {String} Channel An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgRenderingControl2.prototype.GetVolumeDBRange = function(InstanceID, Channel, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("GetVolumeDBRange", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("InstanceID", InstanceID);
    request.writeStringParameter("Channel", Channel);
    request.send(function(result){
        result["MinValue"] = ohnet.soaprequest.readIntParameter(result["MinValue"]); 
        result["MaxValue"] = ohnet.soaprequest.readIntParameter(result["MaxValue"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to GetLoudness
* @method GetLoudness
* @param {Int} InstanceID An action parameter
* @param {String} Channel An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgRenderingControl2.prototype.GetLoudness = function(InstanceID, Channel, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("GetLoudness", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("InstanceID", InstanceID);
    request.writeStringParameter("Channel", Channel);
    request.send(function(result){
        result["CurrentLoudness"] = ohnet.soaprequest.readBoolParameter(result["CurrentLoudness"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to SetLoudness
* @method SetLoudness
* @param {Int} InstanceID An action parameter
* @param {String} Channel An action parameter
* @param {Boolean} DesiredLoudness An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgRenderingControl2.prototype.SetLoudness = function(InstanceID, Channel, DesiredLoudness, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("SetLoudness", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("InstanceID", InstanceID);
    request.writeStringParameter("Channel", Channel);
    request.writeBoolParameter("DesiredLoudness", DesiredLoudness);
    request.send(function(result){
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to GetStateVariables
* @method GetStateVariables
* @param {Int} InstanceID An action parameter
* @param {String} StateVariableList An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgRenderingControl2.prototype.GetStateVariables = function(InstanceID, StateVariableList, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("GetStateVariables", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("InstanceID", InstanceID);
    request.writeStringParameter("StateVariableList", StateVariableList);
    request.send(function(result){
        result["StateVariableValuePairs"] = ohnet.soaprequest.readStringParameter(result["StateVariableValuePairs"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to SetStateVariables
* @method SetStateVariables
* @param {Int} InstanceID An action parameter
* @param {String} RenderingControlUDN An action parameter
* @param {String} ServiceType An action parameter
* @param {String} ServiceId An action parameter
* @param {String} StateVariableValuePairs An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgRenderingControl2.prototype.SetStateVariables = function(InstanceID, RenderingControlUDN, ServiceType, ServiceId, StateVariableValuePairs, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("SetStateVariables", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("InstanceID", InstanceID);
    request.writeStringParameter("RenderingControlUDN", RenderingControlUDN);
    request.writeStringParameter("ServiceType", ServiceType);
    request.writeStringParameter("ServiceId", ServiceId);
    request.writeStringParameter("StateVariableValuePairs", StateVariableValuePairs);
    request.send(function(result){
        result["StateVariableList"] = ohnet.soaprequest.readStringParameter(result["StateVariableList"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}



