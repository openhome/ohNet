 

/**
* Service Proxy for CpProxySchemasUpnpOrgScheduledRecording2
* @module ohNet
* @class ScheduledRecording
*/
	
var CpProxySchemasUpnpOrgScheduledRecording2 = function(udn){	

	this.url = window.location.protocol + "//" + window.location.host + "/" + udn + "/upnp.org-ScheduledRecording-2/control";  // upnp control url
	this.domain = "schemas-upnp-org";
	this.type = "ScheduledRecording";
	this.version = "2";
	this.serviceName = "upnp.org-ScheduledRecording-2";
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
CpProxySchemasUpnpOrgScheduledRecording2.prototype.subscribe = function (serviceAddedFunction) {
    OhNet.SubscriptionManager.addService(this,serviceAddedFunction);
}


/**
* Unsubscribes the service from the subscription manager to stop listening for property change events
* @method Unsubscribe
*/
CpProxySchemasUpnpOrgScheduledRecording2.prototype.unsubscribe = function () {
    OhNet.SubscriptionManager.removeService(this.subscriptionId);
}


	

/**
* Adds a listener to handle "LastChange" property change events
* @method LastChange_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxySchemasUpnpOrgScheduledRecording2.prototype.LastChange_Changed = function (stateChangedFunction) {
    this.serviceProperties.LastChange.addListener(function (state) 
	{ 
		stateChangedFunction(OhNet.SoapRequest.readStringParameter(state)); 
	});
}


/**
* A service action to GetSortCapabilities
* @method GetSortCapabilities
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgScheduledRecording2.prototype.GetSortCapabilities = function(successFunction, errorFunction){	
	var request = new OhNet.SoapRequest("GetSortCapabilities", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["SortCaps"] = OhNet.SoapRequest.readStringParameter(result["SortCaps"]);	
		result["SortLevelCap"] = OhNet.SoapRequest.readIntParameter(result["SortLevelCap"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to GetPropertyList
* @method GetPropertyList
* @param {String} DataTypeID An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgScheduledRecording2.prototype.GetPropertyList = function(DataTypeID, successFunction, errorFunction){	
	var request = new OhNet.SoapRequest("GetPropertyList", this.url, this.domain, this.type, this.version);		
    request.writeStringParameter("DataTypeID", DataTypeID);
    request.send(function(result){
		result["PropertyList"] = OhNet.SoapRequest.readStringParameter(result["PropertyList"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to GetAllowedValues
* @method GetAllowedValues
* @param {String} DataTypeID An action parameter
* @param {String} Filter An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgScheduledRecording2.prototype.GetAllowedValues = function(DataTypeID, Filter, successFunction, errorFunction){	
	var request = new OhNet.SoapRequest("GetAllowedValues", this.url, this.domain, this.type, this.version);		
    request.writeStringParameter("DataTypeID", DataTypeID);
    request.writeStringParameter("Filter", Filter);
    request.send(function(result){
		result["PropertyInfo"] = OhNet.SoapRequest.readStringParameter(result["PropertyInfo"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to GetStateUpdateID
* @method GetStateUpdateID
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgScheduledRecording2.prototype.GetStateUpdateID = function(successFunction, errorFunction){	
	var request = new OhNet.SoapRequest("GetStateUpdateID", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["Id"] = OhNet.SoapRequest.readIntParameter(result["Id"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to BrowseRecordSchedules
* @method BrowseRecordSchedules
* @param {String} Filter An action parameter
* @param {Int} StartingIndex An action parameter
* @param {Int} RequestedCount An action parameter
* @param {String} SortCriteria An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgScheduledRecording2.prototype.BrowseRecordSchedules = function(Filter, StartingIndex, RequestedCount, SortCriteria, successFunction, errorFunction){	
	var request = new OhNet.SoapRequest("BrowseRecordSchedules", this.url, this.domain, this.type, this.version);		
    request.writeStringParameter("Filter", Filter);
    request.writeIntParameter("StartingIndex", StartingIndex);
    request.writeIntParameter("RequestedCount", RequestedCount);
    request.writeStringParameter("SortCriteria", SortCriteria);
    request.send(function(result){
		result["Result"] = OhNet.SoapRequest.readStringParameter(result["Result"]);	
		result["NumberReturned"] = OhNet.SoapRequest.readIntParameter(result["NumberReturned"]);	
		result["TotalMatches"] = OhNet.SoapRequest.readIntParameter(result["TotalMatches"]);	
		result["UpdateID"] = OhNet.SoapRequest.readIntParameter(result["UpdateID"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to BrowseRecordTasks
* @method BrowseRecordTasks
* @param {String} RecordScheduleID An action parameter
* @param {String} Filter An action parameter
* @param {Int} StartingIndex An action parameter
* @param {Int} RequestedCount An action parameter
* @param {String} SortCriteria An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgScheduledRecording2.prototype.BrowseRecordTasks = function(RecordScheduleID, Filter, StartingIndex, RequestedCount, SortCriteria, successFunction, errorFunction){	
	var request = new OhNet.SoapRequest("BrowseRecordTasks", this.url, this.domain, this.type, this.version);		
    request.writeStringParameter("RecordScheduleID", RecordScheduleID);
    request.writeStringParameter("Filter", Filter);
    request.writeIntParameter("StartingIndex", StartingIndex);
    request.writeIntParameter("RequestedCount", RequestedCount);
    request.writeStringParameter("SortCriteria", SortCriteria);
    request.send(function(result){
		result["Result"] = OhNet.SoapRequest.readStringParameter(result["Result"]);	
		result["NumberReturned"] = OhNet.SoapRequest.readIntParameter(result["NumberReturned"]);	
		result["TotalMatches"] = OhNet.SoapRequest.readIntParameter(result["TotalMatches"]);	
		result["UpdateID"] = OhNet.SoapRequest.readIntParameter(result["UpdateID"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to CreateRecordSchedule
* @method CreateRecordSchedule
* @param {String} Elements An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgScheduledRecording2.prototype.CreateRecordSchedule = function(Elements, successFunction, errorFunction){	
	var request = new OhNet.SoapRequest("CreateRecordSchedule", this.url, this.domain, this.type, this.version);		
    request.writeStringParameter("Elements", Elements);
    request.send(function(result){
		result["RecordScheduleID"] = OhNet.SoapRequest.readStringParameter(result["RecordScheduleID"]);	
		result["Result"] = OhNet.SoapRequest.readStringParameter(result["Result"]);	
		result["UpdateID"] = OhNet.SoapRequest.readIntParameter(result["UpdateID"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to DeleteRecordSchedule
* @method DeleteRecordSchedule
* @param {String} RecordScheduleID An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgScheduledRecording2.prototype.DeleteRecordSchedule = function(RecordScheduleID, successFunction, errorFunction){	
	var request = new OhNet.SoapRequest("DeleteRecordSchedule", this.url, this.domain, this.type, this.version);		
    request.writeStringParameter("RecordScheduleID", RecordScheduleID);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to GetRecordSchedule
* @method GetRecordSchedule
* @param {String} RecordScheduleID An action parameter
* @param {String} Filter An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgScheduledRecording2.prototype.GetRecordSchedule = function(RecordScheduleID, Filter, successFunction, errorFunction){	
	var request = new OhNet.SoapRequest("GetRecordSchedule", this.url, this.domain, this.type, this.version);		
    request.writeStringParameter("RecordScheduleID", RecordScheduleID);
    request.writeStringParameter("Filter", Filter);
    request.send(function(result){
		result["Result"] = OhNet.SoapRequest.readStringParameter(result["Result"]);	
		result["UpdateID"] = OhNet.SoapRequest.readIntParameter(result["UpdateID"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to EnableRecordSchedule
* @method EnableRecordSchedule
* @param {String} RecordScheduleID An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgScheduledRecording2.prototype.EnableRecordSchedule = function(RecordScheduleID, successFunction, errorFunction){	
	var request = new OhNet.SoapRequest("EnableRecordSchedule", this.url, this.domain, this.type, this.version);		
    request.writeStringParameter("RecordScheduleID", RecordScheduleID);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to DisableRecordSchedule
* @method DisableRecordSchedule
* @param {String} RecordScheduleID An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgScheduledRecording2.prototype.DisableRecordSchedule = function(RecordScheduleID, successFunction, errorFunction){	
	var request = new OhNet.SoapRequest("DisableRecordSchedule", this.url, this.domain, this.type, this.version);		
    request.writeStringParameter("RecordScheduleID", RecordScheduleID);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to DeleteRecordTask
* @method DeleteRecordTask
* @param {String} RecordTaskID An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgScheduledRecording2.prototype.DeleteRecordTask = function(RecordTaskID, successFunction, errorFunction){	
	var request = new OhNet.SoapRequest("DeleteRecordTask", this.url, this.domain, this.type, this.version);		
    request.writeStringParameter("RecordTaskID", RecordTaskID);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to GetRecordTask
* @method GetRecordTask
* @param {String} RecordTaskID An action parameter
* @param {String} Filter An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgScheduledRecording2.prototype.GetRecordTask = function(RecordTaskID, Filter, successFunction, errorFunction){	
	var request = new OhNet.SoapRequest("GetRecordTask", this.url, this.domain, this.type, this.version);		
    request.writeStringParameter("RecordTaskID", RecordTaskID);
    request.writeStringParameter("Filter", Filter);
    request.send(function(result){
		result["Result"] = OhNet.SoapRequest.readStringParameter(result["Result"]);	
		result["UpdateID"] = OhNet.SoapRequest.readIntParameter(result["UpdateID"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to EnableRecordTask
* @method EnableRecordTask
* @param {String} RecordTaskID An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgScheduledRecording2.prototype.EnableRecordTask = function(RecordTaskID, successFunction, errorFunction){	
	var request = new OhNet.SoapRequest("EnableRecordTask", this.url, this.domain, this.type, this.version);		
    request.writeStringParameter("RecordTaskID", RecordTaskID);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to DisableRecordTask
* @method DisableRecordTask
* @param {String} RecordTaskID An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgScheduledRecording2.prototype.DisableRecordTask = function(RecordTaskID, successFunction, errorFunction){	
	var request = new OhNet.SoapRequest("DisableRecordTask", this.url, this.domain, this.type, this.version);		
    request.writeStringParameter("RecordTaskID", RecordTaskID);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to ResetRecordTask
* @method ResetRecordTask
* @param {String} RecordTaskID An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgScheduledRecording2.prototype.ResetRecordTask = function(RecordTaskID, successFunction, errorFunction){	
	var request = new OhNet.SoapRequest("ResetRecordTask", this.url, this.domain, this.type, this.version);		
    request.writeStringParameter("RecordTaskID", RecordTaskID);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to GetRecordScheduleConflicts
* @method GetRecordScheduleConflicts
* @param {String} RecordScheduleID An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgScheduledRecording2.prototype.GetRecordScheduleConflicts = function(RecordScheduleID, successFunction, errorFunction){	
	var request = new OhNet.SoapRequest("GetRecordScheduleConflicts", this.url, this.domain, this.type, this.version);		
    request.writeStringParameter("RecordScheduleID", RecordScheduleID);
    request.send(function(result){
		result["RecordScheduleConflictIDList"] = OhNet.SoapRequest.readStringParameter(result["RecordScheduleConflictIDList"]);	
		result["UpdateID"] = OhNet.SoapRequest.readIntParameter(result["UpdateID"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to GetRecordTaskConflicts
* @method GetRecordTaskConflicts
* @param {String} RecordTaskID An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgScheduledRecording2.prototype.GetRecordTaskConflicts = function(RecordTaskID, successFunction, errorFunction){	
	var request = new OhNet.SoapRequest("GetRecordTaskConflicts", this.url, this.domain, this.type, this.version);		
    request.writeStringParameter("RecordTaskID", RecordTaskID);
    request.send(function(result){
		result["RecordTaskConflictIDList"] = OhNet.SoapRequest.readStringParameter(result["RecordTaskConflictIDList"]);	
		result["UpdateID"] = OhNet.SoapRequest.readIntParameter(result["UpdateID"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}



