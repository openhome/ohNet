 

/**
* Service Proxy for linn.co.uk:Preamp:4
* @module Zapp
* @class Preamp
*/

var ServicePreamp = function(udn){	

	this.url = window.location.protocol + "//" + window.location.host + "/" + udn + "/linn.co.uk-Preamp-4/control";  // upnp control url
	this.domain = "linn.co.uk";
	if (this.domain == "upnp.org") {
		this.domain = "schemas.upnp.org";
    }
	this.domain = this.domain.replace(/\./,"-");
	this.type = "Preamp";
	this.version = "4";
	this.serviceName = "linn.co.uk-Preamp-4";
	this.subscriptionId = "";  // Subscription identifier unique to each Subscription Manager 
	this.udn = udn;   // device name
	
	// Collection of service properties
	this.serviceProperties = {};
	this.serviceProperties["Volume"] = new Zapp.ServiceProperty("Volume");
	this.serviceProperties["Mute"] = new Zapp.ServiceProperty("Mute");
	this.serviceProperties["Balance"] = new Zapp.ServiceProperty("Balance");
	this.serviceProperties["VolumeLimit"] = new Zapp.ServiceProperty("VolumeLimit");
	this.serviceProperties["StartupVolume"] = new Zapp.ServiceProperty("StartupVolume");
	this.serviceProperties["StartupVolumeEnabled"] = new Zapp.ServiceProperty("StartupVolumeEnabled");
	this.serviceProperties["typeString"] = new Zapp.ServiceProperty("typeString");
	this.serviceProperties["typeBool"] = new Zapp.ServiceProperty("typeBool");
	this.serviceProperties["typeI4"] = new Zapp.ServiceProperty("typeI4");
	this.serviceProperties["typeUi4"] = new Zapp.ServiceProperty("typeUi4");
}



/**
* Subscribes the service to the subscription manager to listen for property change events
* @method Subscribe
* @param {Function} serviceAddedFunction The function that executes once the subscription is successful
*/
ServicePreamp.prototype.subscribe = function (serviceAddedFunction) {
    Zapp.SubscriptionManager.addService(this,serviceAddedFunction);
}


/**
* Unsubscribes the service from the subscription manager to stop listening for property change events
* @method Unsubscribe
*/
ServicePreamp.prototype.unsubscribe = function () {
    Zapp.SubscriptionManager.removeService(this.subscriptionId);
}




/**
* Adds a listener to handle "Volume" property change events
* @method Volume_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServicePreamp.prototype.Volume_Changed = function (stateChangedFunction) {
    this.serviceProperties.Volume.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "Mute" property change events
* @method Mute_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServicePreamp.prototype.Mute_Changed = function (stateChangedFunction) {
    this.serviceProperties.Mute.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readBoolParameter(state)); 
	});
}


/**
* Adds a listener to handle "Balance" property change events
* @method Balance_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServicePreamp.prototype.Balance_Changed = function (stateChangedFunction) {
    this.serviceProperties.Balance.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "VolumeLimit" property change events
* @method VolumeLimit_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServicePreamp.prototype.VolumeLimit_Changed = function (stateChangedFunction) {
    this.serviceProperties.VolumeLimit.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "StartupVolume" property change events
* @method StartupVolume_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServicePreamp.prototype.StartupVolume_Changed = function (stateChangedFunction) {
    this.serviceProperties.StartupVolume.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "StartupVolumeEnabled" property change events
* @method StartupVolumeEnabled_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServicePreamp.prototype.StartupVolumeEnabled_Changed = function (stateChangedFunction) {
    this.serviceProperties.StartupVolumeEnabled.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readBoolParameter(state)); 
	});
}


/**
* Adds a listener to handle "typeString" property change events
* @method typeString_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServicePreamp.prototype.typeString_Changed = function (stateChangedFunction) {
    this.serviceProperties.typeString.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* Adds a listener to handle "typeBool" property change events
* @method typeBool_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServicePreamp.prototype.typeBool_Changed = function (stateChangedFunction) {
    this.serviceProperties.typeBool.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readBoolParameter(state)); 
	});
}


/**
* Adds a listener to handle "typeI4" property change events
* @method typeI4_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServicePreamp.prototype.typeI4_Changed = function (stateChangedFunction) {
    this.serviceProperties.typeI4.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "typeUi4" property change events
* @method typeUi4_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServicePreamp.prototype.typeUi4_Changed = function (stateChangedFunction) {
    this.serviceProperties.typeUi4.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* A service action to VolumeInc
* @method VolumeInc
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServicePreamp.prototype.VolumeInc = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("VolumeInc", this.url, this.domain, this.type, this.version);		
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
ServicePreamp.prototype.VolumeDec = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("VolumeDec", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
	
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
* @param {Int} aVolume An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServicePreamp.prototype.SetVolume = function(aVolume, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetVolume", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("aVolume", aVolume);
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
ServicePreamp.prototype.Volume = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("Volume", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["aVolume"] = Zapp.SoapRequest.readIntParameter(result["aVolume"]);	
	
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
* @param {Boolean} aMute An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServicePreamp.prototype.SetMute = function(aMute, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetMute", this.url, this.domain, this.type, this.version);		
    request.writeBoolParameter("aMute", aMute);
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
ServicePreamp.prototype.Mute = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("Mute", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["aMute"] = Zapp.SoapRequest.readBoolParameter(result["aMute"]);	
	
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
* @param {Int} aBalance An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServicePreamp.prototype.SetBalance = function(aBalance, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetBalance", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("aBalance", aBalance);
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
ServicePreamp.prototype.Balance = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("Balance", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["aBalance"] = Zapp.SoapRequest.readIntParameter(result["aBalance"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to SetVolumeLimit
* @method SetVolumeLimit
* @param {Int} aVolumeLimit An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServicePreamp.prototype.SetVolumeLimit = function(aVolumeLimit, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetVolumeLimit", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("aVolumeLimit", aVolumeLimit);
    request.send(function(result){
	
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
ServicePreamp.prototype.VolumeLimit = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("VolumeLimit", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["aVolumeLimit"] = Zapp.SoapRequest.readIntParameter(result["aVolumeLimit"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to SetStartupVolume
* @method SetStartupVolume
* @param {Int} aStartupVolume An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServicePreamp.prototype.SetStartupVolume = function(aStartupVolume, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetStartupVolume", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("aStartupVolume", aStartupVolume);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to StartupVolume
* @method StartupVolume
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServicePreamp.prototype.StartupVolume = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("StartupVolume", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["aStartupVolume"] = Zapp.SoapRequest.readIntParameter(result["aStartupVolume"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to SetStartupVolumeEnabled
* @method SetStartupVolumeEnabled
* @param {Boolean} aStartupVolumeEnabled An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServicePreamp.prototype.SetStartupVolumeEnabled = function(aStartupVolumeEnabled, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetStartupVolumeEnabled", this.url, this.domain, this.type, this.version);		
    request.writeBoolParameter("aStartupVolumeEnabled", aStartupVolumeEnabled);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to StartupVolumeEnabled
* @method StartupVolumeEnabled
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServicePreamp.prototype.StartupVolumeEnabled = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("StartupVolumeEnabled", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["aStartupVolumeEnabled"] = Zapp.SoapRequest.readBoolParameter(result["aStartupVolumeEnabled"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}



