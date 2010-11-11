 

/**
 * Proxy for upnp.org:ContentDirectory:1
 */

var ServiceContentDirectory = function(aUdn){	
	this.iUrl = window.location.protocol + "//" + window.location.host + "/" + aUdn + "/upnp.org-ContentDirectory-1/control";
	this.iDomain = "upnp.org";
	if (this.iDomain == "upnp.org") {
		this.iDomain = "schemas.upnp.org";
    }
	this.iDomain = this.iDomain.replace(/\./,"-");
	this.iType = "ContentDirectory";
	this.iVersion = "1";
	this.iServiceName = "upnp.org-ContentDirectory-1";
	this.iSubscriptionId = "";
	this.iUdn = aUdn;
	
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

ServiceContentDirectory.prototype.TransferIDs_Changed = function (aStateChangedFunction) {
    this.Variables().TransferIDs.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceContentDirectory.prototype.ObjectID_Changed = function (aStateChangedFunction) {
    this.Variables().ObjectID.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceContentDirectory.prototype.Result_Changed = function (aStateChangedFunction) {
    this.Variables().Result.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceContentDirectory.prototype.SearchCriteria_Changed = function (aStateChangedFunction) {
    this.Variables().SearchCriteria.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceContentDirectory.prototype.BrowseFlag_Changed = function (aStateChangedFunction) {
    this.Variables().BrowseFlag.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceContentDirectory.prototype.Filter_Changed = function (aStateChangedFunction) {
    this.Variables().Filter.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceContentDirectory.prototype.SortCriteria_Changed = function (aStateChangedFunction) {
    this.Variables().SortCriteria.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceContentDirectory.prototype.Index_Changed = function (aStateChangedFunction) {
    this.Variables().Index.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServiceContentDirectory.prototype.Count_Changed = function (aStateChangedFunction) {
    this.Variables().Count.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServiceContentDirectory.prototype.UpdateID_Changed = function (aStateChangedFunction) {
    this.Variables().UpdateID.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServiceContentDirectory.prototype.TransferID_Changed = function (aStateChangedFunction) {
    this.Variables().TransferID.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServiceContentDirectory.prototype.TransferStatus_Changed = function (aStateChangedFunction) {
    this.Variables().TransferStatus.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceContentDirectory.prototype.TransferLength_Changed = function (aStateChangedFunction) {
    this.Variables().TransferLength.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceContentDirectory.prototype.TransferTotal_Changed = function (aStateChangedFunction) {
    this.Variables().TransferTotal.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceContentDirectory.prototype.TagValueList_Changed = function (aStateChangedFunction) {
    this.Variables().TagValueList.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceContentDirectory.prototype.URI_Changed = function (aStateChangedFunction) {
    this.Variables().URI.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceContentDirectory.prototype.SearchCapabilities_Changed = function (aStateChangedFunction) {
    this.Variables().SearchCapabilities.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceContentDirectory.prototype.SortCapabilities_Changed = function (aStateChangedFunction) {
    this.Variables().SortCapabilities.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceContentDirectory.prototype.SystemUpdateID_Changed = function (aStateChangedFunction) {
    this.Variables().SystemUpdateID.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServiceContentDirectory.prototype.ContainerUpdateIDs_Changed = function (aStateChangedFunction) {
    this.Variables().ContainerUpdateIDs.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}

ServiceContentDirectory.prototype.ServiceName = function(){
	return this.iServiceName;
}

ServiceContentDirectory.prototype.Variables = function(){
	return this.iVariables;
}

ServiceContentDirectory.prototype.SubscriptionId = function () {
    return this.iSubscriptionId;
}

ServiceContentDirectory.prototype.SetSubscriptionId = function (value) {
    this.iSubscriptionId = value;
}

ServiceContentDirectory.prototype.Udn = function () {
    return this.iUdn;
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

ServiceContentDirectory.prototype.Subscribe = function () {
    SubscriptionManager.AddService(this);
}

ServiceContentDirectory.prototype.Unsubscribe = function () {
    SubscriptionManager.RemoveService(this.SubscriptionId());
}


ServiceContentDirectory.prototype.GetSearchCapabilities = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetSearchCapabilities", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["SearchCaps"] = SoapRequest.ReadStringParameter(result["SearchCaps"]);	
	
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
		result["SortCaps"] = SoapRequest.ReadStringParameter(result["SortCaps"]);	
	
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
		result["Id"] = SoapRequest.ReadIntParameter(result["Id"]);	
	
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


ServiceContentDirectory.prototype.Search = function(ContainerID, SearchCriteria, Filter, StartingIndex, RequestedCount, SortCriteria, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("Search", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteStringParameter("ContainerID", ContainerID);
    request.WriteStringParameter("SearchCriteria", SearchCriteria);
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


ServiceContentDirectory.prototype.CreateObject = function(ContainerID, Elements, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("CreateObject", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteStringParameter("ContainerID", ContainerID);
    request.WriteStringParameter("Elements", Elements);
    request.Send(function(result){
		result["ObjectID"] = SoapRequest.ReadStringParameter(result["ObjectID"]);	
		result["Result"] = SoapRequest.ReadStringParameter(result["Result"]);	
	
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
		result["TransferID"] = SoapRequest.ReadIntParameter(result["TransferID"]);	
	
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
		result["TransferID"] = SoapRequest.ReadIntParameter(result["TransferID"]);	
	
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
		result["TransferStatus"] = SoapRequest.ReadStringParameter(result["TransferStatus"]);	
		result["TransferLength"] = SoapRequest.ReadStringParameter(result["TransferLength"]);	
		result["TransferTotal"] = SoapRequest.ReadStringParameter(result["TransferTotal"]);	
	
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
		result["NewID"] = SoapRequest.ReadStringParameter(result["NewID"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}



