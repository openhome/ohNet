 

/**
* Service Proxy for upnp.org:ScheduledRecording:2
* @module Zapp
* @class ScheduledRecording
*/

var ServiceScheduledRecording = function(udn){	

	this.url = window.location.protocol + "//" + window.location.host + "/" + udn + "/upnp.org-ScheduledRecording-2/control";  // upnp control url
	this.domain = "upnp.org";
	if (this.domain == "upnp.org") {
		this.domain = "schemas.upnp.org";
    }
	this.domain = this.domain.replace(/\./,"-");
	this.type = "ScheduledRecording";
	this.version = "2";
	this.serviceName = "upnp.org-ScheduledRecording-2";
	this.subscriptionId = "";  // Subscription identifier unique to each Subscription Manager 
	this.udn = udn;   // device name
	
	// Collection of service properties
	this.serviceProperties = {};
	this.serviceProperties["SortCapabilities"] = new Zapp.ServiceProperty("SortCapabilities");
	this.serviceProperties["SortLevelCapability"] = new Zapp.ServiceProperty("SortLevelCapability");
	this.serviceProperties["StateUpdateID"] = new Zapp.ServiceProperty("StateUpdateID");
	this.serviceProperties["LastChange"] = new Zapp.ServiceProperty("LastChange");
	this.serviceProperties["PropertyList"] = new Zapp.ServiceProperty("PropertyList");
	this.serviceProperties["DataTypeID"] = new Zapp.ServiceProperty("DataTypeID");
	this.serviceProperties["ObjectID"] = new Zapp.ServiceProperty("ObjectID");
	this.serviceProperties["ObjectIDList"] = new Zapp.ServiceProperty("ObjectIDList");
	this.serviceProperties["PropertyInfo"] = new Zapp.ServiceProperty("PropertyInfo");
	this.serviceProperties["Index"] = new Zapp.ServiceProperty("Index");
	this.serviceProperties["Count"] = new Zapp.ServiceProperty("Count");
	this.serviceProperties["SortCriteria"] = new Zapp.ServiceProperty("SortCriteria");
	this.serviceProperties["RecordSchedule"] = new Zapp.ServiceProperty("RecordSchedule");
	this.serviceProperties["RecordTask"] = new Zapp.ServiceProperty("RecordTask");
	this.serviceProperties["RecordScheduleParts"] = new Zapp.ServiceProperty("RecordScheduleParts");
}

ServiceScheduledRecording.kDataTypeIDAArgTypeRecordSchedule = "A_ARG_TYPE_RecordSchedule";
ServiceScheduledRecording.kDataTypeIDAArgTypeRecordTask = "A_ARG_TYPE_RecordTask";
ServiceScheduledRecording.kDataTypeIDAArgTypeRecordScheduleParts = "A_ARG_TYPE_RecordScheduleParts";


/**
* Subscribes the service to the subscription manager to listen for property change events
* @method Subscribe
* @param {Function} serviceAddedFunction The function that executes once the subscription is successful
*/
ServiceScheduledRecording.prototype.subscribe = function (serviceAddedFunction) {
    Zapp.SubscriptionManager.addService(this,serviceAddedFunction);
}


/**
* Unsubscribes the service from the subscription manager to stop listening for property change events
* @method Unsubscribe
*/
ServiceScheduledRecording.prototype.unsubscribe = function () {
    Zapp.SubscriptionManager.removeService(this.subscriptionId);
}




/**
* Adds a listener to handle "SortCapabilities" property change events
* @method SortCapabilities_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceScheduledRecording.prototype.SortCapabilities_Changed = function (stateChangedFunction) {
    this.serviceProperties.SortCapabilities.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* Adds a listener to handle "SortLevelCapability" property change events
* @method SortLevelCapability_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceScheduledRecording.prototype.SortLevelCapability_Changed = function (stateChangedFunction) {
    this.serviceProperties.SortLevelCapability.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "StateUpdateID" property change events
* @method StateUpdateID_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceScheduledRecording.prototype.StateUpdateID_Changed = function (stateChangedFunction) {
    this.serviceProperties.StateUpdateID.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "LastChange" property change events
* @method LastChange_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceScheduledRecording.prototype.LastChange_Changed = function (stateChangedFunction) {
    this.serviceProperties.LastChange.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* Adds a listener to handle "PropertyList" property change events
* @method PropertyList_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceScheduledRecording.prototype.PropertyList_Changed = function (stateChangedFunction) {
    this.serviceProperties.PropertyList.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* Adds a listener to handle "DataTypeID" property change events
* @method DataTypeID_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceScheduledRecording.prototype.DataTypeID_Changed = function (stateChangedFunction) {
    this.serviceProperties.DataTypeID.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* Adds a listener to handle "ObjectID" property change events
* @method ObjectID_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceScheduledRecording.prototype.ObjectID_Changed = function (stateChangedFunction) {
    this.serviceProperties.ObjectID.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* Adds a listener to handle "ObjectIDList" property change events
* @method ObjectIDList_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceScheduledRecording.prototype.ObjectIDList_Changed = function (stateChangedFunction) {
    this.serviceProperties.ObjectIDList.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* Adds a listener to handle "PropertyInfo" property change events
* @method PropertyInfo_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceScheduledRecording.prototype.PropertyInfo_Changed = function (stateChangedFunction) {
    this.serviceProperties.PropertyInfo.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* Adds a listener to handle "Index" property change events
* @method Index_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceScheduledRecording.prototype.Index_Changed = function (stateChangedFunction) {
    this.serviceProperties.Index.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "Count" property change events
* @method Count_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceScheduledRecording.prototype.Count_Changed = function (stateChangedFunction) {
    this.serviceProperties.Count.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "SortCriteria" property change events
* @method SortCriteria_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceScheduledRecording.prototype.SortCriteria_Changed = function (stateChangedFunction) {
    this.serviceProperties.SortCriteria.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* Adds a listener to handle "RecordSchedule" property change events
* @method RecordSchedule_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceScheduledRecording.prototype.RecordSchedule_Changed = function (stateChangedFunction) {
    this.serviceProperties.RecordSchedule.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* Adds a listener to handle "RecordTask" property change events
* @method RecordTask_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceScheduledRecording.prototype.RecordTask_Changed = function (stateChangedFunction) {
    this.serviceProperties.RecordTask.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* Adds a listener to handle "RecordScheduleParts" property change events
* @method RecordScheduleParts_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceScheduledRecording.prototype.RecordScheduleParts_Changed = function (stateChangedFunction) {
    this.serviceProperties.RecordScheduleParts.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* A service action to GetSortCapabilities
* @method GetSortCapabilities
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceScheduledRecording.prototype.GetSortCapabilities = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("GetSortCapabilities", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["SortCaps"] = Zapp.SoapRequest.readStringParameter(result["SortCaps"]);	
		result["SortLevelCap"] = Zapp.SoapRequest.readIntParameter(result["SortLevelCap"]);	
	
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
ServiceScheduledRecording.prototype.GetPropertyList = function(DataTypeID, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("GetPropertyList", this.url, this.domain, this.type, this.version);		
    request.writeStringParameter("DataTypeID", DataTypeID);
    request.send(function(result){
		result["PropertyList"] = Zapp.SoapRequest.readStringParameter(result["PropertyList"]);	
	
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
ServiceScheduledRecording.prototype.GetAllowedValues = function(DataTypeID, Filter, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("GetAllowedValues", this.url, this.domain, this.type, this.version);		
    request.writeStringParameter("DataTypeID", DataTypeID);
    request.writeStringParameter("Filter", Filter);
    request.send(function(result){
		result["PropertyInfo"] = Zapp.SoapRequest.readStringParameter(result["PropertyInfo"]);	
	
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
ServiceScheduledRecording.prototype.GetStateUpdateID = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("GetStateUpdateID", this.url, this.domain, this.type, this.version);		
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
* A service action to BrowseRecordSchedules
* @method BrowseRecordSchedules
* @param {String} Filter An action parameter
* @param {Int} StartingIndex An action parameter
* @param {Int} RequestedCount An action parameter
* @param {String} SortCriteria An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceScheduledRecording.prototype.BrowseRecordSchedules = function(Filter, StartingIndex, RequestedCount, SortCriteria, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("BrowseRecordSchedules", this.url, this.domain, this.type, this.version);		
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
ServiceScheduledRecording.prototype.BrowseRecordTasks = function(RecordScheduleID, Filter, StartingIndex, RequestedCount, SortCriteria, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("BrowseRecordTasks", this.url, this.domain, this.type, this.version);		
    request.writeStringParameter("RecordScheduleID", RecordScheduleID);
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
* A service action to CreateRecordSchedule
* @method CreateRecordSchedule
* @param {String} Elements An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceScheduledRecording.prototype.CreateRecordSchedule = function(Elements, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("CreateRecordSchedule", this.url, this.domain, this.type, this.version);		
    request.writeStringParameter("Elements", Elements);
    request.send(function(result){
		result["RecordScheduleID"] = Zapp.SoapRequest.readStringParameter(result["RecordScheduleID"]);	
		result["Result"] = Zapp.SoapRequest.readStringParameter(result["Result"]);	
		result["UpdateID"] = Zapp.SoapRequest.readIntParameter(result["UpdateID"]);	
	
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
ServiceScheduledRecording.prototype.DeleteRecordSchedule = function(RecordScheduleID, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("DeleteRecordSchedule", this.url, this.domain, this.type, this.version);		
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
ServiceScheduledRecording.prototype.GetRecordSchedule = function(RecordScheduleID, Filter, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("GetRecordSchedule", this.url, this.domain, this.type, this.version);		
    request.writeStringParameter("RecordScheduleID", RecordScheduleID);
    request.writeStringParameter("Filter", Filter);
    request.send(function(result){
		result["Result"] = Zapp.SoapRequest.readStringParameter(result["Result"]);	
		result["UpdateID"] = Zapp.SoapRequest.readIntParameter(result["UpdateID"]);	
	
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
ServiceScheduledRecording.prototype.EnableRecordSchedule = function(RecordScheduleID, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("EnableRecordSchedule", this.url, this.domain, this.type, this.version);		
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
ServiceScheduledRecording.prototype.DisableRecordSchedule = function(RecordScheduleID, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("DisableRecordSchedule", this.url, this.domain, this.type, this.version);		
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
ServiceScheduledRecording.prototype.DeleteRecordTask = function(RecordTaskID, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("DeleteRecordTask", this.url, this.domain, this.type, this.version);		
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
ServiceScheduledRecording.prototype.GetRecordTask = function(RecordTaskID, Filter, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("GetRecordTask", this.url, this.domain, this.type, this.version);		
    request.writeStringParameter("RecordTaskID", RecordTaskID);
    request.writeStringParameter("Filter", Filter);
    request.send(function(result){
		result["Result"] = Zapp.SoapRequest.readStringParameter(result["Result"]);	
		result["UpdateID"] = Zapp.SoapRequest.readIntParameter(result["UpdateID"]);	
	
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
ServiceScheduledRecording.prototype.EnableRecordTask = function(RecordTaskID, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("EnableRecordTask", this.url, this.domain, this.type, this.version);		
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
ServiceScheduledRecording.prototype.DisableRecordTask = function(RecordTaskID, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("DisableRecordTask", this.url, this.domain, this.type, this.version);		
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
ServiceScheduledRecording.prototype.ResetRecordTask = function(RecordTaskID, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("ResetRecordTask", this.url, this.domain, this.type, this.version);		
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
ServiceScheduledRecording.prototype.GetRecordScheduleConflicts = function(RecordScheduleID, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("GetRecordScheduleConflicts", this.url, this.domain, this.type, this.version);		
    request.writeStringParameter("RecordScheduleID", RecordScheduleID);
    request.send(function(result){
		result["RecordScheduleConflictIDList"] = Zapp.SoapRequest.readStringParameter(result["RecordScheduleConflictIDList"]);	
		result["UpdateID"] = Zapp.SoapRequest.readIntParameter(result["UpdateID"]);	
	
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
ServiceScheduledRecording.prototype.GetRecordTaskConflicts = function(RecordTaskID, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("GetRecordTaskConflicts", this.url, this.domain, this.type, this.version);		
    request.writeStringParameter("RecordTaskID", RecordTaskID);
    request.send(function(result){
		result["RecordTaskConflictIDList"] = Zapp.SoapRequest.readStringParameter(result["RecordTaskConflictIDList"]);	
		result["UpdateID"] = Zapp.SoapRequest.readIntParameter(result["UpdateID"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}



