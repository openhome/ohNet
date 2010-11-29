 

/**
* Service Proxy for linn.co.uk:Playlist:1
* @module Zapp
* @class Playlist
*/

var ServicePlaylist = function(udn){	

	this.url = window.location.protocol + "//" + window.location.host + "/" + udn + "/linn.co.uk-Playlist-1/control";  // upnp control url
	this.domain = "linn.co.uk";
	if (this.domain == "upnp.org") {
		this.domain = "schemas.upnp.org";
    }
	this.domain = this.domain.replace(/\./,"-");
	this.type = "Playlist";
	this.version = "1";
	this.serviceName = "linn.co.uk-Playlist-1";
	this.subscriptionId = "";  // Subscription identifier unique to each Subscription Manager 
	this.udn = udn;   // device name
	
	// Collection of service properties
	this.serviceProperties = {};
	this.serviceProperties["Id"] = new Zapp.ServiceProperty("Id");
	this.serviceProperties["Data"] = new Zapp.ServiceProperty("Data");
	this.serviceProperties["IdArray"] = new Zapp.ServiceProperty("IdArray");
	this.serviceProperties["Repeat"] = new Zapp.ServiceProperty("Repeat");
	this.serviceProperties["Shuffle"] = new Zapp.ServiceProperty("Shuffle");
	this.serviceProperties["TracksMax"] = new Zapp.ServiceProperty("TracksMax");
	this.serviceProperties["IdArrayToken"] = new Zapp.ServiceProperty("IdArrayToken");
	this.serviceProperties["IdArrayChanged"] = new Zapp.ServiceProperty("IdArrayChanged");
}



/**
* Subscribes the service to the subscription manager to listen for property change events
* @method Subscribe
* @param {Function} serviceAddedFunction The function that executes once the subscription is successful
*/
ServicePlaylist.prototype.subscribe = function (serviceAddedFunction) {
    Zapp.SubscriptionManager.addService(this,serviceAddedFunction);
}


/**
* Unsubscribes the service from the subscription manager to stop listening for property change events
* @method Unsubscribe
*/
ServicePlaylist.prototype.unsubscribe = function () {
    Zapp.SubscriptionManager.removeService(this.subscriptionId);
}




/**
* Adds a listener to handle "Id" property change events
* @method Id_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServicePlaylist.prototype.Id_Changed = function (stateChangedFunction) {
    this.serviceProperties.Id.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "Data" property change events
* @method Data_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServicePlaylist.prototype.Data_Changed = function (stateChangedFunction) {
    this.serviceProperties.Data.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* Adds a listener to handle "IdArray" property change events
* @method IdArray_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServicePlaylist.prototype.IdArray_Changed = function (stateChangedFunction) {
    this.serviceProperties.IdArray.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readBinaryParameter(state)); 
	});
}


/**
* Adds a listener to handle "Repeat" property change events
* @method Repeat_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServicePlaylist.prototype.Repeat_Changed = function (stateChangedFunction) {
    this.serviceProperties.Repeat.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readBoolParameter(state)); 
	});
}


/**
* Adds a listener to handle "Shuffle" property change events
* @method Shuffle_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServicePlaylist.prototype.Shuffle_Changed = function (stateChangedFunction) {
    this.serviceProperties.Shuffle.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readBoolParameter(state)); 
	});
}


/**
* Adds a listener to handle "TracksMax" property change events
* @method TracksMax_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServicePlaylist.prototype.TracksMax_Changed = function (stateChangedFunction) {
    this.serviceProperties.TracksMax.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "IdArrayToken" property change events
* @method IdArrayToken_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServicePlaylist.prototype.IdArrayToken_Changed = function (stateChangedFunction) {
    this.serviceProperties.IdArrayToken.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "IdArrayChanged" property change events
* @method IdArrayChanged_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServicePlaylist.prototype.IdArrayChanged_Changed = function (stateChangedFunction) {
    this.serviceProperties.IdArrayChanged.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readBoolParameter(state)); 
	});
}


/**
* A service action to Read
* @method Read
* @param {Int} aId An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServicePlaylist.prototype.Read = function(aId, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("Read", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("aId", aId);
    request.send(function(result){
		result["aUri"] = Zapp.SoapRequest.readStringParameter(result["aUri"]);	
		result["aMetaData"] = Zapp.SoapRequest.readStringParameter(result["aMetaData"]);	
	
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
* @param {String} aIdList An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServicePlaylist.prototype.ReadList = function(aIdList, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("ReadList", this.url, this.domain, this.type, this.version);		
    request.writeStringParameter("aIdList", aIdList);
    request.send(function(result){
		result["aMetaDataList"] = Zapp.SoapRequest.readStringParameter(result["aMetaDataList"]);	
	
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
* @param {Int} aAfterId An action parameter
* @param {String} aUri An action parameter
* @param {String} aMetaData An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServicePlaylist.prototype.Insert = function(aAfterId, aUri, aMetaData, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("Insert", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("aAfterId", aAfterId);
    request.writeStringParameter("aUri", aUri);
    request.writeStringParameter("aMetaData", aMetaData);
    request.send(function(result){
		result["aNewId"] = Zapp.SoapRequest.readIntParameter(result["aNewId"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to Delete
* @method Delete
* @param {Int} aId An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServicePlaylist.prototype.Delete = function(aId, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("Delete", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("aId", aId);
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
ServicePlaylist.prototype.DeleteAll = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("DeleteAll", this.url, this.domain, this.type, this.version);		
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
* @param {Boolean} aRepeat An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServicePlaylist.prototype.SetRepeat = function(aRepeat, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetRepeat", this.url, this.domain, this.type, this.version);		
    request.writeBoolParameter("aRepeat", aRepeat);
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
ServicePlaylist.prototype.Repeat = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("Repeat", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["aRepeat"] = Zapp.SoapRequest.readBoolParameter(result["aRepeat"]);	
	
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
* @param {Boolean} aShuffle An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServicePlaylist.prototype.SetShuffle = function(aShuffle, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetShuffle", this.url, this.domain, this.type, this.version);		
    request.writeBoolParameter("aShuffle", aShuffle);
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
ServicePlaylist.prototype.Shuffle = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("Shuffle", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["aShuffle"] = Zapp.SoapRequest.readBoolParameter(result["aShuffle"]);	
	
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
ServicePlaylist.prototype.TracksMax = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("TracksMax", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["aTracksMax"] = Zapp.SoapRequest.readIntParameter(result["aTracksMax"]);	
	
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
ServicePlaylist.prototype.IdArray = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("IdArray", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["aIdArrayToken"] = Zapp.SoapRequest.readIntParameter(result["aIdArrayToken"]);	
		result["aIdArray"] = Zapp.SoapRequest.readBinaryParameter(result["aIdArray"]);	
	
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
* @param {Int} aIdArrayToken An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServicePlaylist.prototype.IdArrayChanged = function(aIdArrayToken, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("IdArrayChanged", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("aIdArrayToken", aIdArrayToken);
    request.send(function(result){
		result["aIdArrayChanged"] = Zapp.SoapRequest.readBoolParameter(result["aIdArrayChanged"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}



