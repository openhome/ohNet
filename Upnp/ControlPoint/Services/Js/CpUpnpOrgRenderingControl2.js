 

/**
* Service Proxy for upnp.org:RenderingControl:2
* @module Zapp
* @title RenderingControl
*/

var ServiceRenderingControl = function(udn){	

	this.url = window.location.protocol + "//" + window.location.host + "/" + udn + "/upnp.org-RenderingControl-2/control";  // upnp control url
	this.domain = "upnp.org";
	if (this.domain == "upnp.org") {
		this.domain = "schemas.upnp.org";
    }
	this.domain = this.domain.replace(/\./,"-");
	this.type = "RenderingControl";
	this.version = "2";
	this.serviceName = "upnp.org-RenderingControl-2";
	this.subscriptionId = "";  // Subscription identifier unique to each Subscription Manager 
	this.udn = udn;   // device name
	
	// Collection of service properties
	this.serviceProperties = {};
	this.serviceProperties["LastChange"] = new Zapp.ServiceProperty("LastChange");
	this.serviceProperties["PresetNameList"] = new Zapp.ServiceProperty("PresetNameList");
	this.serviceProperties["Brightness"] = new Zapp.ServiceProperty("Brightness");
	this.serviceProperties["Contrast"] = new Zapp.ServiceProperty("Contrast");
	this.serviceProperties["Sharpness"] = new Zapp.ServiceProperty("Sharpness");
	this.serviceProperties["RedVideoGain"] = new Zapp.ServiceProperty("RedVideoGain");
	this.serviceProperties["GreenVideoGain"] = new Zapp.ServiceProperty("GreenVideoGain");
	this.serviceProperties["BlueVideoGain"] = new Zapp.ServiceProperty("BlueVideoGain");
	this.serviceProperties["RedVideoBlackLevel"] = new Zapp.ServiceProperty("RedVideoBlackLevel");
	this.serviceProperties["GreenVideoBlackLevel"] = new Zapp.ServiceProperty("GreenVideoBlackLevel");
	this.serviceProperties["BlueVideoBlackLevel"] = new Zapp.ServiceProperty("BlueVideoBlackLevel");
	this.serviceProperties["ColorTemperature"] = new Zapp.ServiceProperty("ColorTemperature");
	this.serviceProperties["HorizontalKeystone"] = new Zapp.ServiceProperty("HorizontalKeystone");
	this.serviceProperties["VerticalKeystone"] = new Zapp.ServiceProperty("VerticalKeystone");
	this.serviceProperties["Mute"] = new Zapp.ServiceProperty("Mute");
	this.serviceProperties["Volume"] = new Zapp.ServiceProperty("Volume");
	this.serviceProperties["VolumeDB"] = new Zapp.ServiceProperty("VolumeDB");
	this.serviceProperties["Loudness"] = new Zapp.ServiceProperty("Loudness");
	this.serviceProperties["Channel"] = new Zapp.ServiceProperty("Channel");
	this.serviceProperties["InstanceID"] = new Zapp.ServiceProperty("InstanceID");
	this.serviceProperties["PresetName"] = new Zapp.ServiceProperty("PresetName");
	this.serviceProperties["DeviceUDN"] = new Zapp.ServiceProperty("DeviceUDN");
	this.serviceProperties["ServiceType"] = new Zapp.ServiceProperty("ServiceType");
	this.serviceProperties["ServiceID"] = new Zapp.ServiceProperty("ServiceID");
	this.serviceProperties["StateVariableValuePairs"] = new Zapp.ServiceProperty("StateVariableValuePairs");
	this.serviceProperties["StateVariableList"] = new Zapp.ServiceProperty("StateVariableList");
}

ServiceRenderingControl.kChannelMaster = "Master";
ServiceRenderingControl.kPresetNameFactoryDefaults = "FactoryDefaults";


/**
* Subscribes the service to the subscription manager to listen for property change events
* @method Subscribed
* @param {Function} serviceAddedFunction The function that executes once the subscription is successful
*/
ServiceRenderingControl.prototype.subscribe = function (serviceAddedFunction) {
    Zapp.SubscriptionManager.addService(this,serviceAddedFunction);
}


/**
* Unsubscribes the service from the subscription manager to stop listening for property change events
* @method Subscribed
* @param {Function} serviceAddedFunction The function that executes once the subscription is successful
*/
ServiceRenderingControl.prototype.unsubscribe = function () {
    Zapp.SubscriptionManager.removeService(this.subscriptionId);
}




/**
* Adds a listener to handle "LastChange" property change events
* @method LastChange_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceRenderingControl.prototype.LastChange_Changed = function (stateChangedFunction) {
    this.serviceProperties.LastChange.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* Adds a listener to handle "PresetNameList" property change events
* @method PresetNameList_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceRenderingControl.prototype.PresetNameList_Changed = function (stateChangedFunction) {
    this.serviceProperties.PresetNameList.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* Adds a listener to handle "Brightness" property change events
* @method Brightness_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceRenderingControl.prototype.Brightness_Changed = function (stateChangedFunction) {
    this.serviceProperties.Brightness.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "Contrast" property change events
* @method Contrast_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceRenderingControl.prototype.Contrast_Changed = function (stateChangedFunction) {
    this.serviceProperties.Contrast.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "Sharpness" property change events
* @method Sharpness_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceRenderingControl.prototype.Sharpness_Changed = function (stateChangedFunction) {
    this.serviceProperties.Sharpness.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "RedVideoGain" property change events
* @method RedVideoGain_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceRenderingControl.prototype.RedVideoGain_Changed = function (stateChangedFunction) {
    this.serviceProperties.RedVideoGain.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "GreenVideoGain" property change events
* @method GreenVideoGain_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceRenderingControl.prototype.GreenVideoGain_Changed = function (stateChangedFunction) {
    this.serviceProperties.GreenVideoGain.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "BlueVideoGain" property change events
* @method BlueVideoGain_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceRenderingControl.prototype.BlueVideoGain_Changed = function (stateChangedFunction) {
    this.serviceProperties.BlueVideoGain.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "RedVideoBlackLevel" property change events
* @method RedVideoBlackLevel_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceRenderingControl.prototype.RedVideoBlackLevel_Changed = function (stateChangedFunction) {
    this.serviceProperties.RedVideoBlackLevel.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "GreenVideoBlackLevel" property change events
* @method GreenVideoBlackLevel_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceRenderingControl.prototype.GreenVideoBlackLevel_Changed = function (stateChangedFunction) {
    this.serviceProperties.GreenVideoBlackLevel.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "BlueVideoBlackLevel" property change events
* @method BlueVideoBlackLevel_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceRenderingControl.prototype.BlueVideoBlackLevel_Changed = function (stateChangedFunction) {
    this.serviceProperties.BlueVideoBlackLevel.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "ColorTemperature" property change events
* @method ColorTemperature_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceRenderingControl.prototype.ColorTemperature_Changed = function (stateChangedFunction) {
    this.serviceProperties.ColorTemperature.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "HorizontalKeystone" property change events
* @method HorizontalKeystone_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceRenderingControl.prototype.HorizontalKeystone_Changed = function (stateChangedFunction) {
    this.serviceProperties.HorizontalKeystone.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "VerticalKeystone" property change events
* @method VerticalKeystone_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceRenderingControl.prototype.VerticalKeystone_Changed = function (stateChangedFunction) {
    this.serviceProperties.VerticalKeystone.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "Mute" property change events
* @method Mute_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceRenderingControl.prototype.Mute_Changed = function (stateChangedFunction) {
    this.serviceProperties.Mute.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readBoolParameter(state)); 
	});
}


/**
* Adds a listener to handle "Volume" property change events
* @method Volume_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceRenderingControl.prototype.Volume_Changed = function (stateChangedFunction) {
    this.serviceProperties.Volume.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "VolumeDB" property change events
* @method VolumeDB_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceRenderingControl.prototype.VolumeDB_Changed = function (stateChangedFunction) {
    this.serviceProperties.VolumeDB.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "Loudness" property change events
* @method Loudness_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceRenderingControl.prototype.Loudness_Changed = function (stateChangedFunction) {
    this.serviceProperties.Loudness.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readBoolParameter(state)); 
	});
}


/**
* Adds a listener to handle "Channel" property change events
* @method Channel_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceRenderingControl.prototype.Channel_Changed = function (stateChangedFunction) {
    this.serviceProperties.Channel.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* Adds a listener to handle "InstanceID" property change events
* @method InstanceID_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceRenderingControl.prototype.InstanceID_Changed = function (stateChangedFunction) {
    this.serviceProperties.InstanceID.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "PresetName" property change events
* @method PresetName_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceRenderingControl.prototype.PresetName_Changed = function (stateChangedFunction) {
    this.serviceProperties.PresetName.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* Adds a listener to handle "DeviceUDN" property change events
* @method DeviceUDN_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceRenderingControl.prototype.DeviceUDN_Changed = function (stateChangedFunction) {
    this.serviceProperties.DeviceUDN.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* Adds a listener to handle "ServiceType" property change events
* @method ServiceType_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceRenderingControl.prototype.ServiceType_Changed = function (stateChangedFunction) {
    this.serviceProperties.ServiceType.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* Adds a listener to handle "ServiceID" property change events
* @method ServiceID_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceRenderingControl.prototype.ServiceID_Changed = function (stateChangedFunction) {
    this.serviceProperties.ServiceID.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* Adds a listener to handle "StateVariableValuePairs" property change events
* @method StateVariableValuePairs_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceRenderingControl.prototype.StateVariableValuePairs_Changed = function (stateChangedFunction) {
    this.serviceProperties.StateVariableValuePairs.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* Adds a listener to handle "StateVariableList" property change events
* @method StateVariableList_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceRenderingControl.prototype.StateVariableList_Changed = function (stateChangedFunction) {
    this.serviceProperties.StateVariableList.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* A service action to ListPresets
* @method ListPresets
* @param {Int} InstanceID An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceRenderingControl.prototype.ListPresets = function(InstanceID, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("ListPresets", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("InstanceID", InstanceID);
    request.send(function(result){
		result["CurrentPresetNameList"] = Zapp.SoapRequest.readStringParameter(result["CurrentPresetNameList"]);	
	
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
ServiceRenderingControl.prototype.SelectPreset = function(InstanceID, PresetName, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SelectPreset", this.url, this.domain, this.type, this.version);		
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
ServiceRenderingControl.prototype.GetBrightness = function(InstanceID, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("GetBrightness", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("InstanceID", InstanceID);
    request.send(function(result){
		result["CurrentBrightness"] = Zapp.SoapRequest.readIntParameter(result["CurrentBrightness"]);	
	
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
ServiceRenderingControl.prototype.SetBrightness = function(InstanceID, DesiredBrightness, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetBrightness", this.url, this.domain, this.type, this.version);		
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
ServiceRenderingControl.prototype.GetContrast = function(InstanceID, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("GetContrast", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("InstanceID", InstanceID);
    request.send(function(result){
		result["CurrentContrast"] = Zapp.SoapRequest.readIntParameter(result["CurrentContrast"]);	
	
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
ServiceRenderingControl.prototype.SetContrast = function(InstanceID, DesiredContrast, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetContrast", this.url, this.domain, this.type, this.version);		
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
ServiceRenderingControl.prototype.GetSharpness = function(InstanceID, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("GetSharpness", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("InstanceID", InstanceID);
    request.send(function(result){
		result["CurrentSharpness"] = Zapp.SoapRequest.readIntParameter(result["CurrentSharpness"]);	
	
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
ServiceRenderingControl.prototype.SetSharpness = function(InstanceID, DesiredSharpness, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetSharpness", this.url, this.domain, this.type, this.version);		
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
ServiceRenderingControl.prototype.GetRedVideoGain = function(InstanceID, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("GetRedVideoGain", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("InstanceID", InstanceID);
    request.send(function(result){
		result["CurrentRedVideoGain"] = Zapp.SoapRequest.readIntParameter(result["CurrentRedVideoGain"]);	
	
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
ServiceRenderingControl.prototype.SetRedVideoGain = function(InstanceID, DesiredRedVideoGain, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetRedVideoGain", this.url, this.domain, this.type, this.version);		
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
ServiceRenderingControl.prototype.GetGreenVideoGain = function(InstanceID, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("GetGreenVideoGain", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("InstanceID", InstanceID);
    request.send(function(result){
		result["CurrentGreenVideoGain"] = Zapp.SoapRequest.readIntParameter(result["CurrentGreenVideoGain"]);	
	
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
ServiceRenderingControl.prototype.SetGreenVideoGain = function(InstanceID, DesiredGreenVideoGain, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetGreenVideoGain", this.url, this.domain, this.type, this.version);		
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
ServiceRenderingControl.prototype.GetBlueVideoGain = function(InstanceID, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("GetBlueVideoGain", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("InstanceID", InstanceID);
    request.send(function(result){
		result["CurrentBlueVideoGain"] = Zapp.SoapRequest.readIntParameter(result["CurrentBlueVideoGain"]);	
	
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
ServiceRenderingControl.prototype.SetBlueVideoGain = function(InstanceID, DesiredBlueVideoGain, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetBlueVideoGain", this.url, this.domain, this.type, this.version);		
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
ServiceRenderingControl.prototype.GetRedVideoBlackLevel = function(InstanceID, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("GetRedVideoBlackLevel", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("InstanceID", InstanceID);
    request.send(function(result){
		result["CurrentRedVideoBlackLevel"] = Zapp.SoapRequest.readIntParameter(result["CurrentRedVideoBlackLevel"]);	
	
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
ServiceRenderingControl.prototype.SetRedVideoBlackLevel = function(InstanceID, DesiredRedVideoBlackLevel, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetRedVideoBlackLevel", this.url, this.domain, this.type, this.version);		
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
ServiceRenderingControl.prototype.GetGreenVideoBlackLevel = function(InstanceID, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("GetGreenVideoBlackLevel", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("InstanceID", InstanceID);
    request.send(function(result){
		result["CurrentGreenVideoBlackLevel"] = Zapp.SoapRequest.readIntParameter(result["CurrentGreenVideoBlackLevel"]);	
	
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
ServiceRenderingControl.prototype.SetGreenVideoBlackLevel = function(InstanceID, DesiredGreenVideoBlackLevel, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetGreenVideoBlackLevel", this.url, this.domain, this.type, this.version);		
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
ServiceRenderingControl.prototype.GetBlueVideoBlackLevel = function(InstanceID, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("GetBlueVideoBlackLevel", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("InstanceID", InstanceID);
    request.send(function(result){
		result["CurrentBlueVideoBlackLevel"] = Zapp.SoapRequest.readIntParameter(result["CurrentBlueVideoBlackLevel"]);	
	
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
ServiceRenderingControl.prototype.SetBlueVideoBlackLevel = function(InstanceID, DesiredBlueVideoBlackLevel, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetBlueVideoBlackLevel", this.url, this.domain, this.type, this.version);		
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
ServiceRenderingControl.prototype.GetColorTemperature = function(InstanceID, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("GetColorTemperature", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("InstanceID", InstanceID);
    request.send(function(result){
		result["CurrentColorTemperature"] = Zapp.SoapRequest.readIntParameter(result["CurrentColorTemperature"]);	
	
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
ServiceRenderingControl.prototype.SetColorTemperature = function(InstanceID, DesiredColorTemperature, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetColorTemperature", this.url, this.domain, this.type, this.version);		
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
ServiceRenderingControl.prototype.GetHorizontalKeystone = function(InstanceID, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("GetHorizontalKeystone", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("InstanceID", InstanceID);
    request.send(function(result){
		result["CurrentHorizontalKeystone"] = Zapp.SoapRequest.readIntParameter(result["CurrentHorizontalKeystone"]);	
	
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
ServiceRenderingControl.prototype.SetHorizontalKeystone = function(InstanceID, DesiredHorizontalKeystone, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetHorizontalKeystone", this.url, this.domain, this.type, this.version);		
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
ServiceRenderingControl.prototype.GetVerticalKeystone = function(InstanceID, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("GetVerticalKeystone", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("InstanceID", InstanceID);
    request.send(function(result){
		result["CurrentVerticalKeystone"] = Zapp.SoapRequest.readIntParameter(result["CurrentVerticalKeystone"]);	
	
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
ServiceRenderingControl.prototype.SetVerticalKeystone = function(InstanceID, DesiredVerticalKeystone, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetVerticalKeystone", this.url, this.domain, this.type, this.version);		
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
ServiceRenderingControl.prototype.GetMute = function(InstanceID, Channel, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("GetMute", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("InstanceID", InstanceID);
    request.writeStringParameter("Channel", Channel);
    request.send(function(result){
		result["CurrentMute"] = Zapp.SoapRequest.readBoolParameter(result["CurrentMute"]);	
	
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
ServiceRenderingControl.prototype.SetMute = function(InstanceID, Channel, DesiredMute, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetMute", this.url, this.domain, this.type, this.version);		
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
ServiceRenderingControl.prototype.GetVolume = function(InstanceID, Channel, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("GetVolume", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("InstanceID", InstanceID);
    request.writeStringParameter("Channel", Channel);
    request.send(function(result){
		result["CurrentVolume"] = Zapp.SoapRequest.readIntParameter(result["CurrentVolume"]);	
	
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
ServiceRenderingControl.prototype.SetVolume = function(InstanceID, Channel, DesiredVolume, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetVolume", this.url, this.domain, this.type, this.version);		
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
ServiceRenderingControl.prototype.GetVolumeDB = function(InstanceID, Channel, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("GetVolumeDB", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("InstanceID", InstanceID);
    request.writeStringParameter("Channel", Channel);
    request.send(function(result){
		result["CurrentVolume"] = Zapp.SoapRequest.readIntParameter(result["CurrentVolume"]);	
	
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
ServiceRenderingControl.prototype.SetVolumeDB = function(InstanceID, Channel, DesiredVolume, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetVolumeDB", this.url, this.domain, this.type, this.version);		
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
ServiceRenderingControl.prototype.GetVolumeDBRange = function(InstanceID, Channel, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("GetVolumeDBRange", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("InstanceID", InstanceID);
    request.writeStringParameter("Channel", Channel);
    request.send(function(result){
		result["MinValue"] = Zapp.SoapRequest.readIntParameter(result["MinValue"]);	
		result["MaxValue"] = Zapp.SoapRequest.readIntParameter(result["MaxValue"]);	
	
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
ServiceRenderingControl.prototype.GetLoudness = function(InstanceID, Channel, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("GetLoudness", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("InstanceID", InstanceID);
    request.writeStringParameter("Channel", Channel);
    request.send(function(result){
		result["CurrentLoudness"] = Zapp.SoapRequest.readBoolParameter(result["CurrentLoudness"]);	
	
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
ServiceRenderingControl.prototype.SetLoudness = function(InstanceID, Channel, DesiredLoudness, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetLoudness", this.url, this.domain, this.type, this.version);		
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
ServiceRenderingControl.prototype.GetStateVariables = function(InstanceID, StateVariableList, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("GetStateVariables", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("InstanceID", InstanceID);
    request.writeStringParameter("StateVariableList", StateVariableList);
    request.send(function(result){
		result["StateVariableValuePairs"] = Zapp.SoapRequest.readStringParameter(result["StateVariableValuePairs"]);	
	
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
ServiceRenderingControl.prototype.SetStateVariables = function(InstanceID, RenderingControlUDN, ServiceType, ServiceId, StateVariableValuePairs, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetStateVariables", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("InstanceID", InstanceID);
    request.writeStringParameter("RenderingControlUDN", RenderingControlUDN);
    request.writeStringParameter("ServiceType", ServiceType);
    request.writeStringParameter("ServiceId", ServiceId);
    request.writeStringParameter("StateVariableValuePairs", StateVariableValuePairs);
    request.send(function(result){
		result["StateVariableList"] = Zapp.SoapRequest.readStringParameter(result["StateVariableList"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}



