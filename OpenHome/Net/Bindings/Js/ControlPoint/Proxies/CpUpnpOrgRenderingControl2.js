 

/**
* Service Proxy for CpProxySchemasUpnpOrgRenderingControl2
* @module ohNet
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
	this.serviceProperties["LastChange"] = new OhNet.ServiceProperty("LastChange","string");
}



/**
* Subscribes the service to the subscription manager to listen for property change events
* @method Subscribe
* @param {Function} serviceAddedFunction The function that executes once the subscription is successful
*/
CpProxySchemasUpnpOrgRenderingControl2.prototype.subscribe = function (serviceAddedFunction) {
    OhNet.SubscriptionManager.addService(this,serviceAddedFunction);
}


/**
* Unsubscribes the service from the subscription manager to stop listening for property change events
* @method Unsubscribe
*/
CpProxySchemasUpnpOrgRenderingControl2.prototype.unsubscribe = function () {
    OhNet.SubscriptionManager.removeService(this.subscriptionId);
}


	

/**
* Adds a listener to handle "LastChange" property change events
* @method LastChange_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxySchemasUpnpOrgRenderingControl2.prototype.LastChange_Changed = function (stateChangedFunction) {
    this.serviceProperties.LastChange.addListener(function (state) 
	{ 
		stateChangedFunction(OhNet.SoapRequest.readStringParameter(state)); 
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
	var request = new OhNet.SoapRequest("ListPresets", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("InstanceID", InstanceID);
    request.send(function(result){
		result["CurrentPresetNameList"] = OhNet.SoapRequest.readStringParameter(result["CurrentPresetNameList"]);	
	
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
	var request = new OhNet.SoapRequest("SelectPreset", this.url, this.domain, this.type, this.version);		
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
	var request = new OhNet.SoapRequest("GetBrightness", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("InstanceID", InstanceID);
    request.send(function(result){
		result["CurrentBrightness"] = OhNet.SoapRequest.readIntParameter(result["CurrentBrightness"]);	
	
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
	var request = new OhNet.SoapRequest("SetBrightness", this.url, this.domain, this.type, this.version);		
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
	var request = new OhNet.SoapRequest("GetContrast", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("InstanceID", InstanceID);
    request.send(function(result){
		result["CurrentContrast"] = OhNet.SoapRequest.readIntParameter(result["CurrentContrast"]);	
	
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
	var request = new OhNet.SoapRequest("SetContrast", this.url, this.domain, this.type, this.version);		
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
	var request = new OhNet.SoapRequest("GetSharpness", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("InstanceID", InstanceID);
    request.send(function(result){
		result["CurrentSharpness"] = OhNet.SoapRequest.readIntParameter(result["CurrentSharpness"]);	
	
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
	var request = new OhNet.SoapRequest("SetSharpness", this.url, this.domain, this.type, this.version);		
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
	var request = new OhNet.SoapRequest("GetRedVideoGain", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("InstanceID", InstanceID);
    request.send(function(result){
		result["CurrentRedVideoGain"] = OhNet.SoapRequest.readIntParameter(result["CurrentRedVideoGain"]);	
	
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
	var request = new OhNet.SoapRequest("SetRedVideoGain", this.url, this.domain, this.type, this.version);		
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
	var request = new OhNet.SoapRequest("GetGreenVideoGain", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("InstanceID", InstanceID);
    request.send(function(result){
		result["CurrentGreenVideoGain"] = OhNet.SoapRequest.readIntParameter(result["CurrentGreenVideoGain"]);	
	
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
	var request = new OhNet.SoapRequest("SetGreenVideoGain", this.url, this.domain, this.type, this.version);		
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
	var request = new OhNet.SoapRequest("GetBlueVideoGain", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("InstanceID", InstanceID);
    request.send(function(result){
		result["CurrentBlueVideoGain"] = OhNet.SoapRequest.readIntParameter(result["CurrentBlueVideoGain"]);	
	
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
	var request = new OhNet.SoapRequest("SetBlueVideoGain", this.url, this.domain, this.type, this.version);		
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
	var request = new OhNet.SoapRequest("GetRedVideoBlackLevel", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("InstanceID", InstanceID);
    request.send(function(result){
		result["CurrentRedVideoBlackLevel"] = OhNet.SoapRequest.readIntParameter(result["CurrentRedVideoBlackLevel"]);	
	
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
	var request = new OhNet.SoapRequest("SetRedVideoBlackLevel", this.url, this.domain, this.type, this.version);		
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
	var request = new OhNet.SoapRequest("GetGreenVideoBlackLevel", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("InstanceID", InstanceID);
    request.send(function(result){
		result["CurrentGreenVideoBlackLevel"] = OhNet.SoapRequest.readIntParameter(result["CurrentGreenVideoBlackLevel"]);	
	
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
	var request = new OhNet.SoapRequest("SetGreenVideoBlackLevel", this.url, this.domain, this.type, this.version);		
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
	var request = new OhNet.SoapRequest("GetBlueVideoBlackLevel", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("InstanceID", InstanceID);
    request.send(function(result){
		result["CurrentBlueVideoBlackLevel"] = OhNet.SoapRequest.readIntParameter(result["CurrentBlueVideoBlackLevel"]);	
	
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
	var request = new OhNet.SoapRequest("SetBlueVideoBlackLevel", this.url, this.domain, this.type, this.version);		
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
	var request = new OhNet.SoapRequest("GetColorTemperature", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("InstanceID", InstanceID);
    request.send(function(result){
		result["CurrentColorTemperature"] = OhNet.SoapRequest.readIntParameter(result["CurrentColorTemperature"]);	
	
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
	var request = new OhNet.SoapRequest("SetColorTemperature", this.url, this.domain, this.type, this.version);		
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
	var request = new OhNet.SoapRequest("GetHorizontalKeystone", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("InstanceID", InstanceID);
    request.send(function(result){
		result["CurrentHorizontalKeystone"] = OhNet.SoapRequest.readIntParameter(result["CurrentHorizontalKeystone"]);	
	
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
	var request = new OhNet.SoapRequest("SetHorizontalKeystone", this.url, this.domain, this.type, this.version);		
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
	var request = new OhNet.SoapRequest("GetVerticalKeystone", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("InstanceID", InstanceID);
    request.send(function(result){
		result["CurrentVerticalKeystone"] = OhNet.SoapRequest.readIntParameter(result["CurrentVerticalKeystone"]);	
	
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
	var request = new OhNet.SoapRequest("SetVerticalKeystone", this.url, this.domain, this.type, this.version);		
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
	var request = new OhNet.SoapRequest("GetMute", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("InstanceID", InstanceID);
    request.writeStringParameter("Channel", Channel);
    request.send(function(result){
		result["CurrentMute"] = OhNet.SoapRequest.readBoolParameter(result["CurrentMute"]);	
	
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
	var request = new OhNet.SoapRequest("SetMute", this.url, this.domain, this.type, this.version);		
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
	var request = new OhNet.SoapRequest("GetVolume", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("InstanceID", InstanceID);
    request.writeStringParameter("Channel", Channel);
    request.send(function(result){
		result["CurrentVolume"] = OhNet.SoapRequest.readIntParameter(result["CurrentVolume"]);	
	
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
	var request = new OhNet.SoapRequest("SetVolume", this.url, this.domain, this.type, this.version);		
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
	var request = new OhNet.SoapRequest("GetVolumeDB", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("InstanceID", InstanceID);
    request.writeStringParameter("Channel", Channel);
    request.send(function(result){
		result["CurrentVolume"] = OhNet.SoapRequest.readIntParameter(result["CurrentVolume"]);	
	
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
	var request = new OhNet.SoapRequest("SetVolumeDB", this.url, this.domain, this.type, this.version);		
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
	var request = new OhNet.SoapRequest("GetVolumeDBRange", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("InstanceID", InstanceID);
    request.writeStringParameter("Channel", Channel);
    request.send(function(result){
		result["MinValue"] = OhNet.SoapRequest.readIntParameter(result["MinValue"]);	
		result["MaxValue"] = OhNet.SoapRequest.readIntParameter(result["MaxValue"]);	
	
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
	var request = new OhNet.SoapRequest("GetLoudness", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("InstanceID", InstanceID);
    request.writeStringParameter("Channel", Channel);
    request.send(function(result){
		result["CurrentLoudness"] = OhNet.SoapRequest.readBoolParameter(result["CurrentLoudness"]);	
	
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
	var request = new OhNet.SoapRequest("SetLoudness", this.url, this.domain, this.type, this.version);		
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
	var request = new OhNet.SoapRequest("GetStateVariables", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("InstanceID", InstanceID);
    request.writeStringParameter("StateVariableList", StateVariableList);
    request.send(function(result){
		result["StateVariableValuePairs"] = OhNet.SoapRequest.readStringParameter(result["StateVariableValuePairs"]);	
	
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
	var request = new OhNet.SoapRequest("SetStateVariables", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("InstanceID", InstanceID);
    request.writeStringParameter("RenderingControlUDN", RenderingControlUDN);
    request.writeStringParameter("ServiceType", ServiceType);
    request.writeStringParameter("ServiceId", ServiceId);
    request.writeStringParameter("StateVariableValuePairs", StateVariableValuePairs);
    request.send(function(result){
		result["StateVariableList"] = OhNet.SoapRequest.readStringParameter(result["StateVariableList"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}



