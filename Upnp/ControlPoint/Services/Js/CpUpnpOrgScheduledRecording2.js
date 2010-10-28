 

/**
 * Proxy for upnp.org:ScheduledRecording:2
 */

var ServiceScheduledRecording = function(aId){	
	this.iUrl = window.location.protocol + "//" + window.location.host + "/" + aId + "/ScheduledRecording/control";
	this.iDomain = "upnp.org";
	if (this.iDomain == "upnp.org") {
		this.iDomain = "schemas.upnp.org";
    }
	this.iDomain = this.iDomain.replace(/\./,"-");
	this.iType = "ScheduledRecording";
	this.iVersion = "2";
	
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

ServiceScheduledRecording.prototype.ServiceName = function(){
	return this.iType;
}

ServiceScheduledRecording.prototype.Variables = function(){
	return this.iVariables;
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


ServiceScheduledRecording.prototype.GetSortCapabilities = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetSortCapabilities", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["SortCaps"] = request.ReadStringParameter(result["SortCaps"]);	
		result["SortLevelCap"] = request.ReadIntParameter(result["SortLevelCap"]);	
	
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
		result["PropertyList"] = request.ReadStringParameter(result["PropertyList"]);	
	
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
		result["PropertyInfo"] = request.ReadStringParameter(result["PropertyInfo"]);	
	
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
		result["Id"] = request.ReadIntParameter(result["Id"]);	
	
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
		result["Result"] = request.ReadStringParameter(result["Result"]);	
		result["NumberReturned"] = request.ReadIntParameter(result["NumberReturned"]);	
		result["TotalMatches"] = request.ReadIntParameter(result["TotalMatches"]);	
		result["UpdateID"] = request.ReadIntParameter(result["UpdateID"]);	
	
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
		result["Result"] = request.ReadStringParameter(result["Result"]);	
		result["NumberReturned"] = request.ReadIntParameter(result["NumberReturned"]);	
		result["TotalMatches"] = request.ReadIntParameter(result["TotalMatches"]);	
		result["UpdateID"] = request.ReadIntParameter(result["UpdateID"]);	
	
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
		result["RecordScheduleID"] = request.ReadStringParameter(result["RecordScheduleID"]);	
		result["Result"] = request.ReadStringParameter(result["Result"]);	
		result["UpdateID"] = request.ReadIntParameter(result["UpdateID"]);	
	
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
		result["Result"] = request.ReadStringParameter(result["Result"]);	
		result["UpdateID"] = request.ReadIntParameter(result["UpdateID"]);	
	
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
		result["Result"] = request.ReadStringParameter(result["Result"]);	
		result["UpdateID"] = request.ReadIntParameter(result["UpdateID"]);	
	
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
		result["RecordScheduleConflictIDList"] = request.ReadStringParameter(result["RecordScheduleConflictIDList"]);	
		result["UpdateID"] = request.ReadIntParameter(result["UpdateID"]);	
	
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
		result["RecordTaskConflictIDList"] = request.ReadStringParameter(result["RecordTaskConflictIDList"]);	
		result["UpdateID"] = request.ReadIntParameter(result["UpdateID"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    


