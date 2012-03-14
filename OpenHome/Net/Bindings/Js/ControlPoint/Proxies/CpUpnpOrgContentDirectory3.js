 

/**
* Service Proxy for CpProxySchemasUpnpOrgContentDirectory3
* @module ohnet
* @class ContentDirectory
*/
    
var CpProxySchemasUpnpOrgContentDirectory3 = function(udn){ 

    this.url = window.location.protocol + "//" + window.location.host + "/" + udn + "/upnp.org-ContentDirectory-3/control";  // upnp control url
    this.domain = "schemas-upnp-org";
    this.type = "ContentDirectory";
    this.version = "3";
    this.serviceName = "upnp.org-ContentDirectory-3";
    this.subscriptionId = "";  // Subscription identifier unique to each Subscription Manager 
    this.udn = udn;   // device name
    
    // Collection of service properties
    this.serviceProperties = {};
    this.serviceProperties["SystemUpdateID"] = new ohnet.serviceproperty("SystemUpdateID","int");
    this.serviceProperties["ContainerUpdateIDs"] = new ohnet.serviceproperty("ContainerUpdateIDs","string");
    this.serviceProperties["LastChange"] = new ohnet.serviceproperty("LastChange","string");
    this.serviceProperties["TransferIDs"] = new ohnet.serviceproperty("TransferIDs","string");

                            
}



/**
* Subscribes the service to the subscription manager to listen for property change events
* @method Subscribe
* @param {Function} serviceAddedFunction The function that executes once the subscription is successful
*/
CpProxySchemasUpnpOrgContentDirectory3.prototype.subscribe = function (serviceAddedFunction) {
    ohnet.subscriptionmanager.addService(this,serviceAddedFunction);
}


/**
* Unsubscribes the service from the subscription manager to stop listening for property change events
* @method Unsubscribe
*/
CpProxySchemasUpnpOrgContentDirectory3.prototype.unsubscribe = function () {
    ohnet.subscriptionmanager.removeService(this.subscriptionId);
}


    

/**
* Adds a listener to handle "SystemUpdateID" property change events
* @method SystemUpdateID_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxySchemasUpnpOrgContentDirectory3.prototype.SystemUpdateID_Changed = function (stateChangedFunction) {
    this.serviceProperties.SystemUpdateID.addListener(function (state) 
    { 
        stateChangedFunction(ohnet.soaprequest.readIntParameter(state)); 
    });
}
    

/**
* Adds a listener to handle "ContainerUpdateIDs" property change events
* @method ContainerUpdateIDs_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxySchemasUpnpOrgContentDirectory3.prototype.ContainerUpdateIDs_Changed = function (stateChangedFunction) {
    this.serviceProperties.ContainerUpdateIDs.addListener(function (state) 
    { 
        stateChangedFunction(ohnet.soaprequest.readStringParameter(state)); 
    });
}
    

/**
* Adds a listener to handle "LastChange" property change events
* @method LastChange_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxySchemasUpnpOrgContentDirectory3.prototype.LastChange_Changed = function (stateChangedFunction) {
    this.serviceProperties.LastChange.addListener(function (state) 
    { 
        stateChangedFunction(ohnet.soaprequest.readStringParameter(state)); 
    });
}
    

/**
* Adds a listener to handle "TransferIDs" property change events
* @method TransferIDs_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxySchemasUpnpOrgContentDirectory3.prototype.TransferIDs_Changed = function (stateChangedFunction) {
    this.serviceProperties.TransferIDs.addListener(function (state) 
    { 
        stateChangedFunction(ohnet.soaprequest.readStringParameter(state)); 
    });
}


/**
* A service action to GetSearchCapabilities
* @method GetSearchCapabilities
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgContentDirectory3.prototype.GetSearchCapabilities = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("GetSearchCapabilities", this.url, this.domain, this.type, this.version);     
    request.send(function(result){
        result["SearchCaps"] = ohnet.soaprequest.readStringParameter(result["SearchCaps"]); 
    
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
CpProxySchemasUpnpOrgContentDirectory3.prototype.GetSortCapabilities = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("GetSortCapabilities", this.url, this.domain, this.type, this.version);     
    request.send(function(result){
        result["SortCaps"] = ohnet.soaprequest.readStringParameter(result["SortCaps"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to GetSortExtensionCapabilities
* @method GetSortExtensionCapabilities
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgContentDirectory3.prototype.GetSortExtensionCapabilities = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("GetSortExtensionCapabilities", this.url, this.domain, this.type, this.version);     
    request.send(function(result){
        result["SortExtensionCaps"] = ohnet.soaprequest.readStringParameter(result["SortExtensionCaps"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to GetFeatureList
* @method GetFeatureList
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgContentDirectory3.prototype.GetFeatureList = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("GetFeatureList", this.url, this.domain, this.type, this.version);     
    request.send(function(result){
        result["FeatureList"] = ohnet.soaprequest.readStringParameter(result["FeatureList"]); 
    
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
CpProxySchemasUpnpOrgContentDirectory3.prototype.GetSystemUpdateID = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("GetSystemUpdateID", this.url, this.domain, this.type, this.version);     
    request.send(function(result){
        result["Id"] = ohnet.soaprequest.readIntParameter(result["Id"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to GetServiceResetToken
* @method GetServiceResetToken
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgContentDirectory3.prototype.GetServiceResetToken = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("GetServiceResetToken", this.url, this.domain, this.type, this.version);     
    request.send(function(result){
        result["ResetToken"] = ohnet.soaprequest.readStringParameter(result["ResetToken"]); 
    
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
CpProxySchemasUpnpOrgContentDirectory3.prototype.Browse = function(ObjectID, BrowseFlag, Filter, StartingIndex, RequestedCount, SortCriteria, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("Browse", this.url, this.domain, this.type, this.version);     
    request.writeStringParameter("ObjectID", ObjectID);
    request.writeStringParameter("BrowseFlag", BrowseFlag);
    request.writeStringParameter("Filter", Filter);
    request.writeIntParameter("StartingIndex", StartingIndex);
    request.writeIntParameter("RequestedCount", RequestedCount);
    request.writeStringParameter("SortCriteria", SortCriteria);
    request.send(function(result){
        result["Result"] = ohnet.soaprequest.readStringParameter(result["Result"]); 
        result["NumberReturned"] = ohnet.soaprequest.readIntParameter(result["NumberReturned"]); 
        result["TotalMatches"] = ohnet.soaprequest.readIntParameter(result["TotalMatches"]); 
        result["UpdateID"] = ohnet.soaprequest.readIntParameter(result["UpdateID"]); 
    
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
CpProxySchemasUpnpOrgContentDirectory3.prototype.Search = function(ContainerID, SearchCriteria, Filter, StartingIndex, RequestedCount, SortCriteria, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("Search", this.url, this.domain, this.type, this.version);     
    request.writeStringParameter("ContainerID", ContainerID);
    request.writeStringParameter("SearchCriteria", SearchCriteria);
    request.writeStringParameter("Filter", Filter);
    request.writeIntParameter("StartingIndex", StartingIndex);
    request.writeIntParameter("RequestedCount", RequestedCount);
    request.writeStringParameter("SortCriteria", SortCriteria);
    request.send(function(result){
        result["Result"] = ohnet.soaprequest.readStringParameter(result["Result"]); 
        result["NumberReturned"] = ohnet.soaprequest.readIntParameter(result["NumberReturned"]); 
        result["TotalMatches"] = ohnet.soaprequest.readIntParameter(result["TotalMatches"]); 
        result["UpdateID"] = ohnet.soaprequest.readIntParameter(result["UpdateID"]); 
    
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
CpProxySchemasUpnpOrgContentDirectory3.prototype.CreateObject = function(ContainerID, Elements, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("CreateObject", this.url, this.domain, this.type, this.version);     
    request.writeStringParameter("ContainerID", ContainerID);
    request.writeStringParameter("Elements", Elements);
    request.send(function(result){
        result["ObjectID"] = ohnet.soaprequest.readStringParameter(result["ObjectID"]); 
        result["Result"] = ohnet.soaprequest.readStringParameter(result["Result"]); 
    
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
CpProxySchemasUpnpOrgContentDirectory3.prototype.DestroyObject = function(ObjectID, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("DestroyObject", this.url, this.domain, this.type, this.version);     
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
CpProxySchemasUpnpOrgContentDirectory3.prototype.UpdateObject = function(ObjectID, CurrentTagValue, NewTagValue, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("UpdateObject", this.url, this.domain, this.type, this.version);     
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
* A service action to MoveObject
* @method MoveObject
* @param {String} ObjectID An action parameter
* @param {String} NewParentID An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgContentDirectory3.prototype.MoveObject = function(ObjectID, NewParentID, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("MoveObject", this.url, this.domain, this.type, this.version);     
    request.writeStringParameter("ObjectID", ObjectID);
    request.writeStringParameter("NewParentID", NewParentID);
    request.send(function(result){
        result["NewObjectID"] = ohnet.soaprequest.readStringParameter(result["NewObjectID"]); 
    
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
CpProxySchemasUpnpOrgContentDirectory3.prototype.ImportResource = function(SourceURI, DestinationURI, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("ImportResource", this.url, this.domain, this.type, this.version);     
    request.writeStringParameter("SourceURI", SourceURI);
    request.writeStringParameter("DestinationURI", DestinationURI);
    request.send(function(result){
        result["TransferID"] = ohnet.soaprequest.readIntParameter(result["TransferID"]); 
    
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
CpProxySchemasUpnpOrgContentDirectory3.prototype.ExportResource = function(SourceURI, DestinationURI, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("ExportResource", this.url, this.domain, this.type, this.version);     
    request.writeStringParameter("SourceURI", SourceURI);
    request.writeStringParameter("DestinationURI", DestinationURI);
    request.send(function(result){
        result["TransferID"] = ohnet.soaprequest.readIntParameter(result["TransferID"]); 
    
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
CpProxySchemasUpnpOrgContentDirectory3.prototype.DeleteResource = function(ResourceURI, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("DeleteResource", this.url, this.domain, this.type, this.version);     
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
* A service action to StopTransferResource
* @method StopTransferResource
* @param {Int} TransferID An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgContentDirectory3.prototype.StopTransferResource = function(TransferID, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("StopTransferResource", this.url, this.domain, this.type, this.version);     
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
CpProxySchemasUpnpOrgContentDirectory3.prototype.GetTransferProgress = function(TransferID, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("GetTransferProgress", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("TransferID", TransferID);
    request.send(function(result){
        result["TransferStatus"] = ohnet.soaprequest.readStringParameter(result["TransferStatus"]); 
        result["TransferLength"] = ohnet.soaprequest.readStringParameter(result["TransferLength"]); 
        result["TransferTotal"] = ohnet.soaprequest.readStringParameter(result["TransferTotal"]); 
    
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
CpProxySchemasUpnpOrgContentDirectory3.prototype.CreateReference = function(ContainerID, ObjectID, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("CreateReference", this.url, this.domain, this.type, this.version);     
    request.writeStringParameter("ContainerID", ContainerID);
    request.writeStringParameter("ObjectID", ObjectID);
    request.send(function(result){
        result["NewID"] = ohnet.soaprequest.readStringParameter(result["NewID"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to FreeFormQuery
* @method FreeFormQuery
* @param {String} ContainerID An action parameter
* @param {Int} CDSView An action parameter
* @param {String} QueryRequest An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgContentDirectory3.prototype.FreeFormQuery = function(ContainerID, CDSView, QueryRequest, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("FreeFormQuery", this.url, this.domain, this.type, this.version);     
    request.writeStringParameter("ContainerID", ContainerID);
    request.writeIntParameter("CDSView", CDSView);
    request.writeStringParameter("QueryRequest", QueryRequest);
    request.send(function(result){
        result["QueryResult"] = ohnet.soaprequest.readStringParameter(result["QueryResult"]); 
        result["UpdateID"] = ohnet.soaprequest.readIntParameter(result["UpdateID"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to GetFreeFormQueryCapabilities
* @method GetFreeFormQueryCapabilities
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgContentDirectory3.prototype.GetFreeFormQueryCapabilities = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("GetFreeFormQueryCapabilities", this.url, this.domain, this.type, this.version);     
    request.send(function(result){
        result["FFQCapabilities"] = ohnet.soaprequest.readStringParameter(result["FFQCapabilities"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}



