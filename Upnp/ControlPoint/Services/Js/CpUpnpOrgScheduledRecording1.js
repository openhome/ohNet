 

/**
 * Proxy for upnp.org:ScheduledRecording:1
 */

var ServiceScheduledRecording = function(aUdn){	
	this.iUrl = window.location.protocol + "//" + window.location.host + "/" + aUdn + "/upnp.org-ScheduledRecording-1/control";
	this.iDomain = "upnp.org";
	if (this.iDomain == "upnp.org") {
		this.iDomain = "schemas.upnp.org";
    }
	this.iDomain = this.iDomain.replace(/\./,"-");
	this.iType = "ScheduledRecording";
	this.iVersion = "1";
	this.iServiceName = "upnp.org-ScheduledRecording-1";
	this.iSubscriptionId = "";
	this.iUdn = aUdn;
	
	this.iVariables = {};
			this.iVariables["SortCapabilities"] = new ServiceVariable("SortCapabilities");
		this.iVariables["SortLevelCapability"] = new ServiceVariable("SortLevelCapability");
		this.iVariables["StateUpdateID"] = new ServiceVariable("StateUpdateID");
		this.iVariables["LastChange"] = new ServiceVariable("LastChange");
		this.iVariables["PropertyList"] = new ServiceVariable("PropertyList");
		this.iVariables["DataTypeID"] = new ServiceVariable("DataTypeID");
		this.iVariables["ObjectID"] = new ServiceVariable("ObjectID");
		this.iVariables["ObjectIDList"] = new ServiceVariable("ObjectIDList");
		this.iVariables["PropertyInfo"] = new ServiceVariable("PropertyInfo");
		this.iVariables["Index"] = new ServiceVariable("Index");
		this.iVariables["Count"] = new ServiceVariable("Count");
		this.iVariables["SortCriteria"] = new ServiceVariable("SortCriteria");
		this.iVariables["RecordSchedule"] = new ServiceVariable("RecordSchedule");
		this.iVariables["RecordTask"] = new ServiceVariable("RecordTask");
		this.iVariables["RecordScheduleParts"] = new ServiceVariable("RecordScheduleParts");
}

ServiceScheduledRecording.kDataTypeIDAArgTypeRecordSchedule = "A_ARG_TYPE_RecordSchedule";
ServiceScheduledRecording.kDataTypeIDAArgTypeRecordTask = "A_ARG_TYPE_RecordTask";
ServiceScheduledRecording.kDataTypeIDAArgTypeRecordScheduleParts = "A_ARG_TYPE_RecordScheduleParts";

ServiceScheduledRecording.prototype.SortCapabilities_Changed = function (aStateChangedFunction) {
    this.Variables().SortCapabilities.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceScheduledRecording.prototype.SortLevelCapability_Changed = function (aStateChangedFunction) {
    this.Variables().SortLevelCapability.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServiceScheduledRecording.prototype.StateUpdateID_Changed = function (aStateChangedFunction) {
    this.Variables().StateUpdateID.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServiceScheduledRecording.prototype.LastChange_Changed = function (aStateChangedFunction) {
    this.Variables().LastChange.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceScheduledRecording.prototype.PropertyList_Changed = function (aStateChangedFunction) {
    this.Variables().PropertyList.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceScheduledRecording.prototype.DataTypeID_Changed = function (aStateChangedFunction) {
    this.Variables().DataTypeID.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceScheduledRecording.prototype.ObjectID_Changed = function (aStateChangedFunction) {
    this.Variables().ObjectID.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceScheduledRecording.prototype.ObjectIDList_Changed = function (aStateChangedFunction) {
    this.Variables().ObjectIDList.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceScheduledRecording.prototype.PropertyInfo_Changed = function (aStateChangedFunction) {
    this.Variables().PropertyInfo.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceScheduledRecording.prototype.Index_Changed = function (aStateChangedFunction) {
    this.Variables().Index.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServiceScheduledRecording.prototype.Count_Changed = function (aStateChangedFunction) {
    this.Variables().Count.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServiceScheduledRecording.prototype.SortCriteria_Changed = function (aStateChangedFunction) {
    this.Variables().SortCriteria.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceScheduledRecording.prototype.RecordSchedule_Changed = function (aStateChangedFunction) {
    this.Variables().RecordSchedule.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceScheduledRecording.prototype.RecordTask_Changed = function (aStateChangedFunction) {
    this.Variables().RecordTask.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceScheduledRecording.prototype.RecordScheduleParts_Changed = function (aStateChangedFunction) {
    this.Variables().RecordScheduleParts.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}

ServiceScheduledRecording.prototype.ServiceName = function(){
	return this.iServiceName;
}

ServiceScheduledRecording.prototype.Variables = function(){
	return this.iVariables;
}

ServiceScheduledRecording.prototype.SubscriptionId = function () {
    return this.iSubscriptionId;
}

ServiceScheduledRecording.prototype.SetSubscriptionId = function (value) {
    this.iSubscriptionId = value;
}

ServiceScheduledRecording.prototype.Udn = function () {
    return this.iUdn;
}

ServiceScheduledRecording.prototype.VariableNames = function(){
	var result = [];
	for (var variable in this.iVariables){
		if (this.iVariables.hasOwnProperty(variable)){
			result[result.length] = variable;
		}
	}
	return result;
}

ServiceScheduledRecording.prototype.Subscribe = function () {
    SubscriptionManager.AddService(this);
}

ServiceScheduledRecording.prototype.Unsubscribe = function () {
    SubscriptionManager.RemoveService(this.SubscriptionId());
}


ServiceScheduledRecording.prototype.GetSortCapabilities = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetSortCapabilities", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["SortCaps"] = SoapRequest.ReadStringParameter(result["SortCaps"]);	
		result["SortLevelCap"] = SoapRequest.ReadIntParameter(result["SortLevelCap"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceScheduledRecording.prototype.GetPropertyList = function(DataTypeID, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetPropertyList", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteStringParameter("DataTypeID", DataTypeID);
    request.Send(function(result){
		result["PropertyList"] = SoapRequest.ReadStringParameter(result["PropertyList"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceScheduledRecording.prototype.GetAllowedValues = function(DataTypeID, Filter, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetAllowedValues", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteStringParameter("DataTypeID", DataTypeID);
    request.WriteStringParameter("Filter", Filter);
    request.Send(function(result){
		result["PropertyInfo"] = SoapRequest.ReadStringParameter(result["PropertyInfo"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceScheduledRecording.prototype.GetStateUpdateID = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetStateUpdateID", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["Id"] = SoapRequest.ReadIntParameter(result["Id"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceScheduledRecording.prototype.BrowseRecordSchedules = function(Filter, StartingIndex, RequestedCount, SortCriteria, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("BrowseRecordSchedules", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteStringParameter("Filter", Filter);
    request.WriteIntParameter("StartingIndex", StartingIndex);
    request.WriteIntParameter("RequestedCount", RequestedCount);
    request.WriteStringParameter("SortCriteria", SortCriteria);
    request.Send(function(result){
		result["Result"] = SoapRequest.ReadStringParameter(result["Result"]);	
		result["NumberReturned"] = SoapRequest.ReadIntParameter(result["NumberReturned"]);	
		result["TotalMatches"] = SoapRequest.ReadIntParameter(result["TotalMatches"]);	
		result["UpdateID"] = SoapRequest.ReadIntParameter(result["UpdateID"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceScheduledRecording.prototype.BrowseRecordTasks = function(RecordScheduleID, Filter, StartingIndex, RequestedCount, SortCriteria, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("BrowseRecordTasks", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteStringParameter("RecordScheduleID", RecordScheduleID);
    request.WriteStringParameter("Filter", Filter);
    request.WriteIntParameter("StartingIndex", StartingIndex);
    request.WriteIntParameter("RequestedCount", RequestedCount);
    request.WriteStringParameter("SortCriteria", SortCriteria);
    request.Send(function(result){
		result["Result"] = SoapRequest.ReadStringParameter(result["Result"]);	
		result["NumberReturned"] = SoapRequest.ReadIntParameter(result["NumberReturned"]);	
		result["TotalMatches"] = SoapRequest.ReadIntParameter(result["TotalMatches"]);	
		result["UpdateID"] = SoapRequest.ReadIntParameter(result["UpdateID"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceScheduledRecording.prototype.CreateRecordSchedule = function(Elements, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("CreateRecordSchedule", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteStringParameter("Elements", Elements);
    request.Send(function(result){
		result["RecordScheduleID"] = SoapRequest.ReadStringParameter(result["RecordScheduleID"]);	
		result["Result"] = SoapRequest.ReadStringParameter(result["Result"]);	
		result["UpdateID"] = SoapRequest.ReadIntParameter(result["UpdateID"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceScheduledRecording.prototype.DeleteRecordSchedule = function(RecordScheduleID, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("DeleteRecordSchedule", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteStringParameter("RecordScheduleID", RecordScheduleID);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceScheduledRecording.prototype.GetRecordSchedule = function(RecordScheduleID, Filter, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetRecordSchedule", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteStringParameter("RecordScheduleID", RecordScheduleID);
    request.WriteStringParameter("Filter", Filter);
    request.Send(function(result){
		result["Result"] = SoapRequest.ReadStringParameter(result["Result"]);	
		result["UpdateID"] = SoapRequest.ReadIntParameter(result["UpdateID"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceScheduledRecording.prototype.EnableRecordSchedule = function(RecordScheduleID, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("EnableRecordSchedule", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteStringParameter("RecordScheduleID", RecordScheduleID);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceScheduledRecording.prototype.DisableRecordSchedule = function(RecordScheduleID, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("DisableRecordSchedule", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteStringParameter("RecordScheduleID", RecordScheduleID);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceScheduledRecording.prototype.DeleteRecordTask = function(RecordTaskID, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("DeleteRecordTask", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteStringParameter("RecordTaskID", RecordTaskID);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceScheduledRecording.prototype.GetRecordTask = function(RecordTaskID, Filter, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetRecordTask", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteStringParameter("RecordTaskID", RecordTaskID);
    request.WriteStringParameter("Filter", Filter);
    request.Send(function(result){
		result["Result"] = SoapRequest.ReadStringParameter(result["Result"]);	
		result["UpdateID"] = SoapRequest.ReadIntParameter(result["UpdateID"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceScheduledRecording.prototype.EnableRecordTask = function(RecordTaskID, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("EnableRecordTask", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteStringParameter("RecordTaskID", RecordTaskID);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceScheduledRecording.prototype.DisableRecordTask = function(RecordTaskID, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("DisableRecordTask", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteStringParameter("RecordTaskID", RecordTaskID);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceScheduledRecording.prototype.ResetRecordTask = function(RecordTaskID, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("ResetRecordTask", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteStringParameter("RecordTaskID", RecordTaskID);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceScheduledRecording.prototype.GetRecordScheduleConflicts = function(RecordScheduleID, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetRecordScheduleConflicts", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteStringParameter("RecordScheduleID", RecordScheduleID);
    request.Send(function(result){
		result["RecordScheduleConflictIDList"] = SoapRequest.ReadStringParameter(result["RecordScheduleConflictIDList"]);	
		result["UpdateID"] = SoapRequest.ReadIntParameter(result["UpdateID"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceScheduledRecording.prototype.GetRecordTaskConflicts = function(RecordTaskID, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetRecordTaskConflicts", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteStringParameter("RecordTaskID", RecordTaskID);
    request.Send(function(result){
		result["RecordTaskConflictIDList"] = SoapRequest.ReadStringParameter(result["RecordTaskConflictIDList"]);	
		result["UpdateID"] = SoapRequest.ReadIntParameter(result["UpdateID"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}



