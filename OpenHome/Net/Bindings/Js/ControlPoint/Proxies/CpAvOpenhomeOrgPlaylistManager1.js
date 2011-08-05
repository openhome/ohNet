 

/**
* Service Proxy for CpProxyAvOpenhomeOrgPlaylistManager1
* @module ohNet
* @class PlaylistManager
*/
	
var CpProxyAvOpenhomeOrgPlaylistManager1 = function(udn){	

	this.url = window.location.protocol + "//" + window.location.host + "/" + udn + "/av.openhome.org-PlaylistManager-1/control";  // upnp control url
	this.domain = "av-openhome-org";
	this.type = "PlaylistManager";
	this.version = "1";
	this.serviceName = "av.openhome.org-PlaylistManager-1";
	this.subscriptionId = "";  // Subscription identifier unique to each Subscription Manager 
	this.udn = udn;   // device name
	
	// Collection of service properties
	this.serviceProperties = {};
	this.serviceProperties["Metadata"] = new OhNet.ServiceProperty("Metadata","string");
	this.serviceProperties["ImagesXml"] = new OhNet.ServiceProperty("ImagesXml","string");
	this.serviceProperties["IdArray"] = new OhNet.ServiceProperty("IdArray","binary");
	this.serviceProperties["TokenArray"] = new OhNet.ServiceProperty("TokenArray","binary");
	this.serviceProperties["PlaylistsMax"] = new OhNet.ServiceProperty("PlaylistsMax","int");
	this.serviceProperties["TracksMax"] = new OhNet.ServiceProperty("TracksMax","int");
}



/**
* Subscribes the service to the subscription manager to listen for property change events
* @method Subscribe
* @param {Function} serviceAddedFunction The function that executes once the subscription is successful
*/
CpProxyAvOpenhomeOrgPlaylistManager1.prototype.subscribe = function (serviceAddedFunction) {
    OhNet.SubscriptionManager.addService(this,serviceAddedFunction);
}


/**
* Unsubscribes the service from the subscription manager to stop listening for property change events
* @method Unsubscribe
*/
CpProxyAvOpenhomeOrgPlaylistManager1.prototype.unsubscribe = function () {
    OhNet.SubscriptionManager.removeService(this.subscriptionId);
}


	

/**
* Adds a listener to handle "Metadata" property change events
* @method Metadata_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgPlaylistManager1.prototype.Metadata_Changed = function (stateChangedFunction) {
    this.serviceProperties.Metadata.addListener(function (state) 
	{ 
		stateChangedFunction(OhNet.SoapRequest.readStringParameter(state)); 
	});
}
	

/**
* Adds a listener to handle "ImagesXml" property change events
* @method ImagesXml_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgPlaylistManager1.prototype.ImagesXml_Changed = function (stateChangedFunction) {
    this.serviceProperties.ImagesXml.addListener(function (state) 
	{ 
		stateChangedFunction(OhNet.SoapRequest.readStringParameter(state)); 
	});
}
	

/**
* Adds a listener to handle "IdArray" property change events
* @method IdArray_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgPlaylistManager1.prototype.IdArray_Changed = function (stateChangedFunction) {
    this.serviceProperties.IdArray.addListener(function (state) 
	{ 
		stateChangedFunction(OhNet.SoapRequest.readBinaryParameter(state)); 
	});
}
	

/**
* Adds a listener to handle "TokenArray" property change events
* @method TokenArray_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgPlaylistManager1.prototype.TokenArray_Changed = function (stateChangedFunction) {
    this.serviceProperties.TokenArray.addListener(function (state) 
	{ 
		stateChangedFunction(OhNet.SoapRequest.readBinaryParameter(state)); 
	});
}
	

/**
* Adds a listener to handle "PlaylistsMax" property change events
* @method PlaylistsMax_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgPlaylistManager1.prototype.PlaylistsMax_Changed = function (stateChangedFunction) {
    this.serviceProperties.PlaylistsMax.addListener(function (state) 
	{ 
		stateChangedFunction(OhNet.SoapRequest.readIntParameter(state)); 
	});
}
	

/**
* Adds a listener to handle "TracksMax" property change events
* @method TracksMax_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgPlaylistManager1.prototype.TracksMax_Changed = function (stateChangedFunction) {
    this.serviceProperties.TracksMax.addListener(function (state) 
	{ 
		stateChangedFunction(OhNet.SoapRequest.readIntParameter(state)); 
	});
}


/**
* A service action to Metadata
* @method Metadata
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgPlaylistManager1.prototype.Metadata = function(successFunction, errorFunction){	
	var request = new OhNet.SoapRequest("Metadata", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["Metadata"] = OhNet.SoapRequest.readStringParameter(result["Metadata"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to ImagesXml
* @method ImagesXml
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgPlaylistManager1.prototype.ImagesXml = function(successFunction, errorFunction){	
	var request = new OhNet.SoapRequest("ImagesXml", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["ImagesXml"] = OhNet.SoapRequest.readStringParameter(result["ImagesXml"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to PlaylistReadArray
* @method PlaylistReadArray
* @param {Int} Id An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgPlaylistManager1.prototype.PlaylistReadArray = function(Id, successFunction, errorFunction){	
	var request = new OhNet.SoapRequest("PlaylistReadArray", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("Id", Id);
    request.send(function(result){
		result["Array"] = OhNet.SoapRequest.readBinaryParameter(result["Array"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to PlaylistReadMetadata
* @method PlaylistReadMetadata
* @param {String} IdList An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgPlaylistManager1.prototype.PlaylistReadMetadata = function(IdList, successFunction, errorFunction){	
	var request = new OhNet.SoapRequest("PlaylistReadMetadata", this.url, this.domain, this.type, this.version);		
    request.writeStringParameter("IdList", IdList);
    request.send(function(result){
		result["Metadata"] = OhNet.SoapRequest.readStringParameter(result["Metadata"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to PlaylistRead
* @method PlaylistRead
* @param {Int} Id An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgPlaylistManager1.prototype.PlaylistRead = function(Id, successFunction, errorFunction){	
	var request = new OhNet.SoapRequest("PlaylistRead", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("Id", Id);
    request.send(function(result){
		result["Name"] = OhNet.SoapRequest.readStringParameter(result["Name"]);	
		result["Description"] = OhNet.SoapRequest.readStringParameter(result["Description"]);	
		result["ImageId"] = OhNet.SoapRequest.readIntParameter(result["ImageId"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to PlaylistUpdate
* @method PlaylistUpdate
* @param {Int} Id An action parameter
* @param {String} Name An action parameter
* @param {String} Description An action parameter
* @param {Int} ImageId An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgPlaylistManager1.prototype.PlaylistUpdate = function(Id, Name, Description, ImageId, successFunction, errorFunction){	
	var request = new OhNet.SoapRequest("PlaylistUpdate", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("Id", Id);
    request.writeStringParameter("Name", Name);
    request.writeStringParameter("Description", Description);
    request.writeIntParameter("ImageId", ImageId);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to PlaylistInsert
* @method PlaylistInsert
* @param {Int} AfterId An action parameter
* @param {String} Name An action parameter
* @param {String} Description An action parameter
* @param {Int} ImageId An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgPlaylistManager1.prototype.PlaylistInsert = function(AfterId, Name, Description, ImageId, successFunction, errorFunction){	
	var request = new OhNet.SoapRequest("PlaylistInsert", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("AfterId", AfterId);
    request.writeStringParameter("Name", Name);
    request.writeStringParameter("Description", Description);
    request.writeIntParameter("ImageId", ImageId);
    request.send(function(result){
		result["NewId"] = OhNet.SoapRequest.readIntParameter(result["NewId"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to PlaylistDeleteId
* @method PlaylistDeleteId
* @param {Int} Value An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgPlaylistManager1.prototype.PlaylistDeleteId = function(Value, successFunction, errorFunction){	
	var request = new OhNet.SoapRequest("PlaylistDeleteId", this.url, this.domain, this.type, this.version);		
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
* A service action to PlaylistsMax
* @method PlaylistsMax
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgPlaylistManager1.prototype.PlaylistsMax = function(successFunction, errorFunction){	
	var request = new OhNet.SoapRequest("PlaylistsMax", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["Value"] = OhNet.SoapRequest.readIntParameter(result["Value"]);	
	
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
CpProxyAvOpenhomeOrgPlaylistManager1.prototype.TracksMax = function(successFunction, errorFunction){	
	var request = new OhNet.SoapRequest("TracksMax", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["Value"] = OhNet.SoapRequest.readIntParameter(result["Value"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to PlaylistArrays
* @method PlaylistArrays
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgPlaylistManager1.prototype.PlaylistArrays = function(successFunction, errorFunction){	
	var request = new OhNet.SoapRequest("PlaylistArrays", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["Token"] = OhNet.SoapRequest.readIntParameter(result["Token"]);	
		result["IdArray"] = OhNet.SoapRequest.readBinaryParameter(result["IdArray"]);	
		result["TokenArray"] = OhNet.SoapRequest.readBinaryParameter(result["TokenArray"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to PlaylistArraysChanged
* @method PlaylistArraysChanged
* @param {Int} Token An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgPlaylistManager1.prototype.PlaylistArraysChanged = function(Token, successFunction, errorFunction){	
	var request = new OhNet.SoapRequest("PlaylistArraysChanged", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("Token", Token);
    request.send(function(result){
		result["Value"] = OhNet.SoapRequest.readBoolParameter(result["Value"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to Read
* @method Read
* @param {Int} Id An action parameter
* @param {Int} TrackId An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgPlaylistManager1.prototype.Read = function(Id, TrackId, successFunction, errorFunction){	
	var request = new OhNet.SoapRequest("Read", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("Id", Id);
    request.writeIntParameter("TrackId", TrackId);
    request.send(function(result){
		result["Metadata"] = OhNet.SoapRequest.readStringParameter(result["Metadata"]);	
	
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
* @param {Int} Id An action parameter
* @param {String} TrackIdList An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgPlaylistManager1.prototype.ReadList = function(Id, TrackIdList, successFunction, errorFunction){	
	var request = new OhNet.SoapRequest("ReadList", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("Id", Id);
    request.writeStringParameter("TrackIdList", TrackIdList);
    request.send(function(result){
		result["TrackList"] = OhNet.SoapRequest.readStringParameter(result["TrackList"]);	
	
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
* @param {Int} Id An action parameter
* @param {Int} AfterTrackId An action parameter
* @param {String} Udn An action parameter
* @param {String} MetadataId An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgPlaylistManager1.prototype.Insert = function(Id, AfterTrackId, Udn, MetadataId, successFunction, errorFunction){	
	var request = new OhNet.SoapRequest("Insert", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("Id", Id);
    request.writeIntParameter("AfterTrackId", AfterTrackId);
    request.writeStringParameter("Udn", Udn);
    request.writeStringParameter("MetadataId", MetadataId);
    request.send(function(result){
		result["NewTrackId"] = OhNet.SoapRequest.readIntParameter(result["NewTrackId"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to DeleteId
* @method DeleteId
* @param {Int} TrackId An action parameter
* @param {Int} Value An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgPlaylistManager1.prototype.DeleteId = function(TrackId, Value, successFunction, errorFunction){	
	var request = new OhNet.SoapRequest("DeleteId", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("TrackId", TrackId);
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
* A service action to DeleteAll
* @method DeleteAll
* @param {Int} TrackId An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgPlaylistManager1.prototype.DeleteAll = function(TrackId, successFunction, errorFunction){	
	var request = new OhNet.SoapRequest("DeleteAll", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("TrackId", TrackId);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}



