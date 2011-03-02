 

/**
* Service Proxy for CpProxyLinnCoUkPlaylist1
* @module Zapp
* @class Playlist
*/
	
var CpProxyLinnCoUkPlaylist1 = function(udn){	

	this.url = window.location.protocol + "//" + window.location.host + "/" + udn + "/linn.co.uk-Playlist-1/control";  // upnp control url
	this.domain = "linn-co-uk";
	this.type = "Playlist";
	this.version = "1";
	this.serviceName = "linn.co.uk-Playlist-1";
	this.subscriptionId = "";  // Subscription identifier unique to each Subscription Manager 
	this.udn = udn;   // device name
	
	// Collection of service properties
	this.serviceProperties = {};
	this.serviceProperties["IdArray"] = new Zapp.ServiceProperty("IdArray");
	this.serviceProperties["Repeat"] = new Zapp.ServiceProperty("Repeat");
	this.serviceProperties["Shuffle"] = new Zapp.ServiceProperty("Shuffle");
	this.serviceProperties["TracksMax"] = new Zapp.ServiceProperty("TracksMax");
}



/**
* Subscribes the service to the subscription manager to listen for property change events
* @method Subscribe
* @param {Function} serviceAddedFunction The function that executes once the subscription is successful
*/
CpProxyLinnCoUkPlaylist1.prototype.subscribe = function (serviceAddedFunction) {
    Zapp.SubscriptionManager.addService(this,serviceAddedFunction);
}


/**
* Unsubscribes the service from the subscription manager to stop listening for property change events
* @method Unsubscribe
*/
CpProxyLinnCoUkPlaylist1.prototype.unsubscribe = function () {
    Zapp.SubscriptionManager.removeService(this.subscriptionId);
}


	

/**
* Adds a listener to handle "IdArray" property change events
* @method IdArray_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyLinnCoUkPlaylist1.prototype.IdArray_Changed = function (stateChangedFunction) {
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
CpProxyLinnCoUkPlaylist1.prototype.Repeat_Changed = function (stateChangedFunction) {
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
CpProxyLinnCoUkPlaylist1.prototype.Shuffle_Changed = function (stateChangedFunction) {
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
CpProxyLinnCoUkPlaylist1.prototype.TracksMax_Changed = function (stateChangedFunction) {
    this.serviceProperties.TracksMax.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* A service action to Read
* @method Read
* @param {Int} aId An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkPlaylist1.prototype.Read = function(aId, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("Read", this.url, this.formattedDomain, this.type, this.version);		
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
CpProxyLinnCoUkPlaylist1.prototype.ReadList = function(aIdList, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("ReadList", this.url, this.formattedDomain, this.type, this.version);		
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
CpProxyLinnCoUkPlaylist1.prototype.Insert = function(aAfterId, aUri, aMetaData, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("Insert", this.url, this.formattedDomain, this.type, this.version);		
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
CpProxyLinnCoUkPlaylist1.prototype.Delete = function(aId, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("Delete", this.url, this.formattedDomain, this.type, this.version);		
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
CpProxyLinnCoUkPlaylist1.prototype.DeleteAll = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("DeleteAll", this.url, this.formattedDomain, this.type, this.version);		
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
CpProxyLinnCoUkPlaylist1.prototype.SetRepeat = function(aRepeat, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetRepeat", this.url, this.formattedDomain, this.type, this.version);		
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
CpProxyLinnCoUkPlaylist1.prototype.Repeat = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("Repeat", this.url, this.formattedDomain, this.type, this.version);		
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
CpProxyLinnCoUkPlaylist1.prototype.SetShuffle = function(aShuffle, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetShuffle", this.url, this.formattedDomain, this.type, this.version);		
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
CpProxyLinnCoUkPlaylist1.prototype.Shuffle = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("Shuffle", this.url, this.formattedDomain, this.type, this.version);		
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
CpProxyLinnCoUkPlaylist1.prototype.TracksMax = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("TracksMax", this.url, this.formattedDomain, this.type, this.version);		
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
CpProxyLinnCoUkPlaylist1.prototype.IdArray = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("IdArray", this.url, this.formattedDomain, this.type, this.version);		
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
CpProxyLinnCoUkPlaylist1.prototype.IdArrayChanged = function(aIdArrayToken, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("IdArrayChanged", this.url, this.formattedDomain, this.type, this.version);		
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



