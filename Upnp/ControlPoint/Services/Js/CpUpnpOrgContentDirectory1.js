 

/**
 * Proxy for upnp.org:ContentDirectory:1
 */

var ServiceContentDirectory = function(aId){	
	this.iUrl = window.location.protocol + "//" + window.location.host + "/" + aId + "/ContentDirectory/control";
	this.iDomain = "upnp.org";
	if (this.iDomain == "upnp.org") {
		this.iDomain = "schemas.upnp.org";
    }
	this.iDomain = this.iDomain.replace(/\./,"-");
	this.iType = "ContentDirectory";
	this.iVersion = "1";
	
	this.iVariables = {};
			this.iVariables["TransferIDs"] = new ServiceVariable("TransferIDs");
		this.iVariables["ObjectID"] = new ServiceVariable("ObjectID");
		this.iVariables["Result"] = new ServiceVariable("Result");
		this.iVariables["SearchCriteria"] = new ServiceVariable("SearchCriteria");
		this.iVariables["BrowseFlag"] = new ServiceVariable("BrowseFlag");
		this.iVariables["Filter"] = new ServiceVariable("Filter");
		this.iVariables["SortCriteria"] = new ServiceVariable("SortCriteria");
		this.iVariables["Index"] = new ServiceVariable("Index");
		this.iVariables["Count"] = new ServiceVariable("Count");
		this.iVariables["UpdateID"] = new ServiceVariable("UpdateID");
		this.iVariables["TransferID"] = new ServiceVariable("TransferID");
		this.iVariables["TransferStatus"] = new ServiceVariable("TransferStatus");
		this.iVariables["TransferLength"] = new ServiceVariable("TransferLength");
		this.iVariables["TransferTotal"] = new ServiceVariable("TransferTotal");
		this.iVariables["TagValueList"] = new ServiceVariable("TagValueList");
		this.iVariables["URI"] = new ServiceVariable("URI");
		this.iVariables["SearchCapabilities"] = new ServiceVariable("SearchCapabilities");
		this.iVariables["SortCapabilities"] = new ServiceVariable("SortCapabilities");
		this.iVariables["SystemUpdateID"] = new ServiceVariable("SystemUpdateID");
		this.iVariables["ContainerUpdateIDs"] = new ServiceVariable("ContainerUpdateIDs");
}

ServiceContentDirectory.kBrowseFlagBrowseMetadata = "BrowseMetadata";
ServiceContentDirectory.kBrowseFlagBrowseDirectChildren = "BrowseDirectChildren";
ServiceContentDirectory.kTransferStatusCompleted = "COMPLETED";
ServiceContentDirectory.kTransferStatusError = "ERROR";
ServiceContentDirectory.kTransferStatusInProgress = "IN_PROGRESS";
ServiceContentDirectory.kTransferStatusStopped = "STOPPED";

ServiceContentDirectory.prototype.ServiceName = function(){
	return this.iType;
}

ServiceContentDirectory.prototype.Variables = function(){
	return this.iVariables;
}

ServiceContentDirectory.prototype.VariableNames = function(){
	var result = [];
	for (var variable in this.iVariables){
		if (this.iVariables.hasOwnProperty(variable)){
			result[result.length] = variable;
		}
	}
	return result;
}


ServiceContentDirectory.prototype.GetSearchCapabilities = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetSearchCapabilities", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["SearchCaps"] = request.ReadStringParameter(result["SearchCaps"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceContentDirectory.prototype.GetSortCapabilities = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetSortCapabilities", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["SortCaps"] = request.ReadStringParameter(result["SortCaps"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceContentDirectory.prototype.GetSystemUpdateID = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetSystemUpdateID", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["Id"] = request.ReadIntParameter(result["Id"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceContentDirectory.prototype.Browse = function(ObjectID, BrowseFlag, Filter, StartingIndex, RequestedCount, SortCriteria, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("Browse", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteStringParameter("ObjectID", ObjectID);
    request.WriteStringParameter("BrowseFlag", BrowseFlag);
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
    

ServiceContentDirectory.prototype.Search = function(ContainerID, SearchCriteria, Filter, StartingIndex, RequestedCount, SortCriteria, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("Search", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteStringParameter("ContainerID", ContainerID);
    request.WriteStringParameter("SearchCriteria", SearchCriteria);
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
    

ServiceContentDirectory.prototype.CreateObject = function(ContainerID, Elements, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("CreateObject", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteStringParameter("ContainerID", ContainerID);
    request.WriteStringParameter("Elements", Elements);
    request.Send(function(result){
		result["ObjectID"] = request.ReadStringParameter(result["ObjectID"]);	
		result["Result"] = request.ReadStringParameter(result["Result"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceContentDirectory.prototype.DestroyObject = function(ObjectID, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("DestroyObject", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteStringParameter("ObjectID", ObjectID);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceContentDirectory.prototype.UpdateObject = function(ObjectID, CurrentTagValue, NewTagValue, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("UpdateObject", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteStringParameter("ObjectID", ObjectID);
    request.WriteStringParameter("CurrentTagValue", CurrentTagValue);
    request.WriteStringParameter("NewTagValue", NewTagValue);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceContentDirectory.prototype.ImportResource = function(SourceURI, DestinationURI, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("ImportResource", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteStringParameter("SourceURI", SourceURI);
    request.WriteStringParameter("DestinationURI", DestinationURI);
    request.Send(function(result){
		result["TransferID"] = request.ReadIntParameter(result["TransferID"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceContentDirectory.prototype.ExportResource = function(SourceURI, DestinationURI, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("ExportResource", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteStringParameter("SourceURI", SourceURI);
    request.WriteStringParameter("DestinationURI", DestinationURI);
    request.Send(function(result){
		result["TransferID"] = request.ReadIntParameter(result["TransferID"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceContentDirectory.prototype.StopTransferResource = function(TransferID, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("StopTransferResource", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("TransferID", TransferID);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceContentDirectory.prototype.GetTransferProgress = function(TransferID, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetTransferProgress", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("TransferID", TransferID);
    request.Send(function(result){
		result["TransferStatus"] = request.ReadStringParameter(result["TransferStatus"]);	
		result["TransferLength"] = request.ReadStringParameter(result["TransferLength"]);	
		result["TransferTotal"] = request.ReadStringParameter(result["TransferTotal"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceContentDirectory.prototype.DeleteResource = function(ResourceURI, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("DeleteResource", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteStringParameter("ResourceURI", ResourceURI);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceContentDirectory.prototype.CreateReference = function(ContainerID, ObjectID, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("CreateReference", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteStringParameter("ContainerID", ContainerID);
    request.WriteStringParameter("ObjectID", ObjectID);
    request.Send(function(result){
		result["NewID"] = request.ReadStringParameter(result["NewID"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    


