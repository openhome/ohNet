 

/**
* Service Proxy for linn.co.uk:Jukebox:1
* @module Zapp
* @title Jukebox
*/

var ServiceJukebox = function(udn){	

	this.url = window.location.protocol + "//" + window.location.host + "/" + udn + "/linn.co.uk-Jukebox-1/control";  // upnp control url
	this.domain = "linn.co.uk";
	if (this.domain == "upnp.org") {
		this.domain = "schemas.upnp.org";
    }
	this.domain = this.domain.replace(/\./,"-");
	this.type = "Jukebox";
	this.version = "1";
	this.serviceName = "linn.co.uk-Jukebox-1";
	this.subscriptionId = "";  // Subscription identifier unique to each Subscription Manager 
	this.udn = udn;   // device name
	
	// Collection of service properties
	this.serviceProperties = {};
	this.serviceProperties["MetaData"] = new Zapp.ServiceProperty("MetaData");
	this.serviceProperties["CurrentPreset"] = new Zapp.ServiceProperty("CurrentPreset");
	this.serviceProperties["PresetPrefix"] = new Zapp.ServiceProperty("PresetPrefix");
	this.serviceProperties["AlbumArtFileName"] = new Zapp.ServiceProperty("AlbumArtFileName");
}



/**
* Subscribes the service to the subscription manager to listen for property change events
* @method Subscribed
* @param {Function} serviceAddedFunction The function that executes once the subscription is successful
*/
ServiceJukebox.prototype.subscribe = function (serviceAddedFunction) {
    Zapp.SubscriptionManager.addService(this,serviceAddedFunction);
}


/**
* Unsubscribes the service from the subscription manager to stop listening for property change events
* @method Subscribed
* @param {Function} serviceAddedFunction The function that executes once the subscription is successful
*/
ServiceJukebox.prototype.unsubscribe = function () {
    Zapp.SubscriptionManager.removeService(this.subscriptionId);
}




/**
* Adds a listener to handle "MetaData" property change events
* @method MetaData_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceJukebox.prototype.MetaData_Changed = function (stateChangedFunction) {
    this.serviceProperties.MetaData.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* Adds a listener to handle "CurrentPreset" property change events
* @method CurrentPreset_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceJukebox.prototype.CurrentPreset_Changed = function (stateChangedFunction) {
    this.serviceProperties.CurrentPreset.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "PresetPrefix" property change events
* @method PresetPrefix_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceJukebox.prototype.PresetPrefix_Changed = function (stateChangedFunction) {
    this.serviceProperties.PresetPrefix.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* Adds a listener to handle "AlbumArtFileName" property change events
* @method AlbumArtFileName_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceJukebox.prototype.AlbumArtFileName_Changed = function (stateChangedFunction) {
    this.serviceProperties.AlbumArtFileName.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* A service action to SetPresetPrefix
* @method SetPresetPrefix
* @param {String} aUri An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceJukebox.prototype.SetPresetPrefix = function(aUri, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetPresetPrefix", this.url, this.domain, this.type, this.version);		
    request.writeStringParameter("aUri", aUri);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to PresetPrefix
* @method PresetPrefix
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceJukebox.prototype.PresetPrefix = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("PresetPrefix", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["aUri"] = Zapp.SoapRequest.readStringParameter(result["aUri"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to SetAlbumArtFileName
* @method SetAlbumArtFileName
* @param {String} aName An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceJukebox.prototype.SetAlbumArtFileName = function(aName, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetAlbumArtFileName", this.url, this.domain, this.type, this.version);		
    request.writeStringParameter("aName", aName);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to AlbumArtFileName
* @method AlbumArtFileName
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceJukebox.prototype.AlbumArtFileName = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("AlbumArtFileName", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["aName"] = Zapp.SoapRequest.readStringParameter(result["aName"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to SetCurrentPreset
* @method SetCurrentPreset
* @param {Int} aPreset An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceJukebox.prototype.SetCurrentPreset = function(aPreset, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetCurrentPreset", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("aPreset", aPreset);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to CurrentPreset
* @method CurrentPreset
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceJukebox.prototype.CurrentPreset = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("CurrentPreset", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["aPreset"] = Zapp.SoapRequest.readIntParameter(result["aPreset"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to PresetMetaData
* @method PresetMetaData
* @param {Int} aPreset An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceJukebox.prototype.PresetMetaData = function(aPreset, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("PresetMetaData", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("aPreset", aPreset);
    request.send(function(result){
		result["aMetaData"] = Zapp.SoapRequest.readStringParameter(result["aMetaData"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to LoadManifest
* @method LoadManifest
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceJukebox.prototype.LoadManifest = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("LoadManifest", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["aTotalPresets"] = Zapp.SoapRequest.readIntParameter(result["aTotalPresets"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}



