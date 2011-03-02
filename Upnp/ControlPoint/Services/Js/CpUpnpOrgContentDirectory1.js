 

/**
* Service Proxy for CpProxySchemasUpnpOrgContentDirectory1
* @module Zapp
* @class ContentDirectory
*/
	
var CpProxySchemasUpnpOrgContentDirectory1 = function(udn){	

	this.url = window.location.protocol + "//" + window.location.host + "/" + udn + "/upnp.org-ContentDirectory-1/control";  // upnp control url
	this.domain = "schemas-upnp-org";
	this.type = "ContentDirectory";
	this.version = "1";
	this.serviceName = "upnp.org-ContentDirectory-1";
	this.subscriptionId = "";  // Subscription identifier unique to each Subscription Manager 
	this.udn = udn;   // device name
	
	// Collection of service properties
	this.serviceProperties = {};
	this.serviceProperties["TransferIDs"] = new Zapp.ServiceProperty("TransferIDs");
	this.serviceProperties["SystemUpdateID"] = new Zapp.ServiceProperty("SystemUpdateID");
	this.serviceProperties["ContainerUpdateIDs"] = new Zapp.ServiceProperty("ContainerUpdateIDs");
}



/**
* Subscribes the service to the subscription manager to listen for property change events
* @method Subscribe
* @param {Function} serviceAddedFunction The function that executes once the subscription is successful
*/
CpProxySchemasUpnpOrgContentDirectory1.prototype.subscribe = function (serviceAddedFunction) {
    Zapp.SubscriptionManager.addService(this,serviceAddedFunction);
}


/**
* Unsubscribes the service from the subscription manager to stop listening for property change events
* @method Unsubscribe
*/
CpProxySchemasUpnpOrgContentDirectory1.prototype.unsubscribe = function () {
    Zapp.SubscriptionManager.removeService(this.subscriptionId);
}


	

/**
* Adds a listener to handle "TransferIDs" property change events
* @method TransferIDs_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxySchemasUpnpOrgContentDirectory1.prototype.TransferIDs_Changed = function (stateChangedFunction) {
    this.serviceProperties.TransferIDs.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}
	

/**
* Adds a listener to handle "SystemUpdateID" property change events
* @method SystemUpdateID_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxySchemasUpnpOrgContentDirectory1.prototype.SystemUpdateID_Changed = function (stateChangedFunction) {
    this.serviceProperties.SystemUpdateID.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}
	

/**
* Adds a listener to handle "ContainerUpdateIDs" property change events
* @method ContainerUpdateIDs_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxySchemasUpnpOrgContentDirectory1.prototype.ContainerUpdateIDs_Changed = function (stateChangedFunction) {
    this.serviceProperties.ContainerUpdateIDs.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* A service action to GetSearchCapabilities
* @method GetSearchCapabilities
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgContentDirectory1.prototype.GetSearchCapabilities = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("GetSearchCapabilities", this.url, this.formattedDomain, this.type, this.version);		
    request.send(function(result){
		result["SearchCaps"] = Zapp.SoapRequest.readStringParameter(result["SearchCaps"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to GetSortCapabilities
* @method GetSortCapabilities
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgContentDirectory1.prototype.GetSortCapabilities = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("GetSortCapabilities", this.url, this.formattedDomain, this.type, this.version);		
    request.send(function(result){
		result["SortCaps"] = Zapp.SoapRequest.readStringParameter(result["SortCaps"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to GetSystemUpdateID
* @method GetSystemUpdateID
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgContentDirectory1.prototype.GetSystemUpdateID = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("GetSystemUpdateID", this.url, this.formattedDomain, this.type, this.version);		
    request.send(function(result){
		result["Id"] = Zapp.SoapRequest.readIntParameter(result["Id"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to Browse
* @method Browse
* @param {String} ObjectID An action parameter
* @param {String} BrowseFlag An action parameter
* @param {String} Filter An action parameter
* @param {Int} StartingIndex An action parameter
* @param {Int} RequestedCount An action parameter
* @param {String} SortCriteria An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgContentDirectory1.prototype.Browse = function(ObjectID, BrowseFlag, Filter, StartingIndex, RequestedCount, SortCriteria, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("Browse", this.url, this.formattedDomain, this.type, this.version);		
    request.writeStringParameter("ObjectID", ObjectID);
    request.writeStringParameter("BrowseFlag", BrowseFlag);
    request.writeStringParameter("Filter", Filter);
    request.writeIntParameter("StartingIndex", StartingIndex);
    request.writeIntParameter("RequestedCount", RequestedCount);
    request.writeStringParameter("SortCriteria", SortCriteria);
    request.send(function(result){
		result["Result"] = Zapp.SoapRequest.readStringParameter(result["Result"]);	
		result["NumberReturned"] = Zapp.SoapRequest.readIntParameter(result["NumberReturned"]);	
		result["TotalMatches"] = Zapp.SoapRequest.readIntParameter(result["TotalMatches"]);	
		result["UpdateID"] = Zapp.SoapRequest.readIntParameter(result["UpdateID"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to Search
* @method Search
* @param {String} ContainerID An action parameter
* @param {String} SearchCriteria An action parameter
* @param {String} Filter An action parameter
* @param {Int} StartingIndex An action parameter
* @param {Int} RequestedCount An action parameter
* @param {String} SortCriteria An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgContentDirectory1.prototype.Search = function(ContainerID, SearchCriteria, Filter, StartingIndex, RequestedCount, SortCriteria, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("Search", this.url, this.formattedDomain, this.type, this.version);		
    request.writeStringParameter("ContainerID", ContainerID);
    request.writeStringParameter("SearchCriteria", SearchCriteria);
    request.writeStringParameter("Filter", Filter);
    request.writeIntParameter("StartingIndex", StartingIndex);
    request.writeIntParameter("RequestedCount", RequestedCount);
    request.writeStringParameter("SortCriteria", SortCriteria);
    request.send(function(result){
		result["Result"] = Zapp.SoapRequest.readStringParameter(result["Result"]);	
		result["NumberReturned"] = Zapp.SoapRequest.readIntParameter(result["NumberReturned"]);	
		result["TotalMatches"] = Zapp.SoapRequest.readIntParameter(result["TotalMatches"]);	
		result["UpdateID"] = Zapp.SoapRequest.readIntParameter(result["UpdateID"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to CreateObject
* @method CreateObject
* @param {String} ContainerID An action parameter
* @param {String} Elements An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgContentDirectory1.prototype.CreateObject = function(ContainerID, Elements, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("CreateObject", this.url, this.formattedDomain, this.type, this.version);		
    request.writeStringParameter("ContainerID", ContainerID);
    request.writeStringParameter("Elements", Elements);
    request.send(function(result){
		result["ObjectID"] = Zapp.SoapRequest.readStringParameter(result["ObjectID"]);	
		result["Result"] = Zapp.SoapRequest.readStringParameter(result["Result"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to DestroyObject
* @method DestroyObject
* @param {String} ObjectID An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgContentDirectory1.prototype.DestroyObject = function(ObjectID, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("DestroyObject", this.url, this.formattedDomain, this.type, this.version);		
    request.writeStringParameter("ObjectID", ObjectID);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to UpdateObject
* @method UpdateObject
* @param {String} ObjectID An action parameter
* @param {String} CurrentTagValue An action parameter
* @param {String} NewTagValue An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgContentDirectory1.prototype.UpdateObject = function(ObjectID, CurrentTagValue, NewTagValue, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("UpdateObject", this.url, this.formattedDomain, this.type, this.version);		
    request.writeStringParameter("ObjectID", ObjectID);
    request.writeStringParameter("CurrentTagValue", CurrentTagValue);
    request.writeStringParameter("NewTagValue", NewTagValue);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to ImportResource
* @method ImportResource
* @param {String} SourceURI An action parameter
* @param {String} DestinationURI An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgContentDirectory1.prototype.ImportResource = function(SourceURI, DestinationURI, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("ImportResource", this.url, this.formattedDomain, this.type, this.version);		
    request.writeStringParameter("SourceURI", SourceURI);
    request.writeStringParameter("DestinationURI", DestinationURI);
    request.send(function(result){
		result["TransferID"] = Zapp.SoapRequest.readIntParameter(result["TransferID"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to ExportResource
* @method ExportResource
* @param {String} SourceURI An action parameter
* @param {String} DestinationURI An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgContentDirectory1.prototype.ExportResource = function(SourceURI, DestinationURI, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("ExportResource", this.url, this.formattedDomain, this.type, this.version);		
    request.writeStringParameter("SourceURI", SourceURI);
    request.writeStringParameter("DestinationURI", DestinationURI);
    request.send(function(result){
		result["TransferID"] = Zapp.SoapRequest.readIntParameter(result["TransferID"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to StopTransferResource
* @method StopTransferResource
* @param {Int} TransferID An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgContentDirectory1.prototype.StopTransferResource = function(TransferID, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("StopTransferResource", this.url, this.formattedDomain, this.type, this.version);		
    request.writeIntParameter("TransferID", TransferID);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to GetTransferProgress
* @method GetTransferProgress
* @param {Int} TransferID An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgContentDirectory1.prototype.GetTransferProgress = function(TransferID, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("GetTransferProgress", this.url, this.formattedDomain, this.type, this.version);		
    request.writeIntParameter("TransferID", TransferID);
    request.send(function(result){
		result["TransferStatus"] = Zapp.SoapRequest.readStringParameter(result["TransferStatus"]);	
		result["TransferLength"] = Zapp.SoapRequest.readStringParameter(result["TransferLength"]);	
		result["TransferTotal"] = Zapp.SoapRequest.readStringParameter(result["TransferTotal"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to DeleteResource
* @method DeleteResource
* @param {String} ResourceURI An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgContentDirectory1.prototype.DeleteResource = function(ResourceURI, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("DeleteResource", this.url, this.formattedDomain, this.type, this.version);		
    request.writeStringParameter("ResourceURI", ResourceURI);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to CreateReference
* @method CreateReference
* @param {String} ContainerID An action parameter
* @param {String} ObjectID An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgContentDirectory1.prototype.CreateReference = function(ContainerID, ObjectID, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("CreateReference", this.url, this.formattedDomain, this.type, this.version);		
    request.writeStringParameter("ContainerID", ContainerID);
    request.writeStringParameter("ObjectID", ObjectID);
    request.send(function(result){
		result["NewID"] = Zapp.SoapRequest.readStringParameter(result["NewID"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}



