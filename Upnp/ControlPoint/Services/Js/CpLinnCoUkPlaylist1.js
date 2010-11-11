 

/**
 * Proxy for linn.co.uk:Playlist:1
 */

var ServicePlaylist = function(aUdn){	
	this.iUrl = window.location.protocol + "//" + window.location.host + "/" + aUdn + "/linn.co.uk-Playlist-1/control";
	this.iDomain = "linn.co.uk";
	if (this.iDomain == "upnp.org") {
		this.iDomain = "schemas.upnp.org";
    }
	this.iDomain = this.iDomain.replace(/\./,"-");
	this.iType = "Playlist";
	this.iVersion = "1";
	this.iServiceName = "linn.co.uk-Playlist-1";
	this.iSubscriptionId = "";
	this.iUdn = aUdn;
	
	this.iVariables = {};
			this.iVariables["Id"] = new ServiceVariable("Id");
		this.iVariables["Data"] = new ServiceVariable("Data");
		this.iVariables["IdArray"] = new ServiceVariable("IdArray");
		this.iVariables["Repeat"] = new ServiceVariable("Repeat");
		this.iVariables["Shuffle"] = new ServiceVariable("Shuffle");
		this.iVariables["TracksMax"] = new ServiceVariable("TracksMax");
		this.iVariables["IdArrayToken"] = new ServiceVariable("IdArrayToken");
		this.iVariables["IdArrayChanged"] = new ServiceVariable("IdArrayChanged");
}


ServicePlaylist.prototype.Id_Changed = function (aStateChangedFunction) {
    this.Variables().Id.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServicePlaylist.prototype.Data_Changed = function (aStateChangedFunction) {
    this.Variables().Data.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServicePlaylist.prototype.IdArray_Changed = function (aStateChangedFunction) {
    this.Variables().IdArray.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadBinaryParameter(state)); 
	});
}
ServicePlaylist.prototype.Repeat_Changed = function (aStateChangedFunction) {
    this.Variables().Repeat.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadBoolParameter(state)); 
	});
}
ServicePlaylist.prototype.Shuffle_Changed = function (aStateChangedFunction) {
    this.Variables().Shuffle.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadBoolParameter(state)); 
	});
}
ServicePlaylist.prototype.TracksMax_Changed = function (aStateChangedFunction) {
    this.Variables().TracksMax.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServicePlaylist.prototype.IdArrayToken_Changed = function (aStateChangedFunction) {
    this.Variables().IdArrayToken.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServicePlaylist.prototype.IdArrayChanged_Changed = function (aStateChangedFunction) {
    this.Variables().IdArrayChanged.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadBoolParameter(state)); 
	});
}

ServicePlaylist.prototype.ServiceName = function(){
	return this.iServiceName;
}

ServicePlaylist.prototype.Variables = function(){
	return this.iVariables;
}

ServicePlaylist.prototype.SubscriptionId = function () {
    return this.iSubscriptionId;
}

ServicePlaylist.prototype.SetSubscriptionId = function (value) {
    this.iSubscriptionId = value;
}

ServicePlaylist.prototype.Udn = function () {
    return this.iUdn;
}

ServicePlaylist.prototype.VariableNames = function(){
	var result = [];
	for (var variable in this.iVariables){
		if (this.iVariables.hasOwnProperty(variable)){
			result[result.length] = variable;
		}
	}
	return result;
}

ServicePlaylist.prototype.Subscribe = function () {
    SubscriptionManager.AddService(this);
}

ServicePlaylist.prototype.Unsubscribe = function () {
    SubscriptionManager.RemoveService(this.SubscriptionId());
}


ServicePlaylist.prototype.Read = function(aId, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("Read", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("aId", aId);
    request.Send(function(result){
		result["aUri"] = SoapRequest.ReadStringParameter(result["aUri"]);	
		result["aMetaData"] = SoapRequest.ReadStringParameter(result["aMetaData"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServicePlaylist.prototype.ReadList = function(aIdList, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("ReadList", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteStringParameter("aIdList", aIdList);
    request.Send(function(result){
		result["aMetaDataList"] = SoapRequest.ReadStringParameter(result["aMetaDataList"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServicePlaylist.prototype.Insert = function(aAfterId, aUri, aMetaData, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("Insert", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("aAfterId", aAfterId);
    request.WriteStringParameter("aUri", aUri);
    request.WriteStringParameter("aMetaData", aMetaData);
    request.Send(function(result){
		result["aNewId"] = SoapRequest.ReadIntParameter(result["aNewId"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServicePlaylist.prototype.Delete = function(aId, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("Delete", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("aId", aId);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServicePlaylist.prototype.DeleteAll = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("DeleteAll", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServicePlaylist.prototype.SetRepeat = function(aRepeat, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetRepeat", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteBoolParameter("aRepeat", aRepeat);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServicePlaylist.prototype.Repeat = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("Repeat", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aRepeat"] = SoapRequest.ReadBoolParameter(result["aRepeat"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServicePlaylist.prototype.SetShuffle = function(aShuffle, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetShuffle", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteBoolParameter("aShuffle", aShuffle);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServicePlaylist.prototype.Shuffle = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("Shuffle", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aShuffle"] = SoapRequest.ReadBoolParameter(result["aShuffle"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServicePlaylist.prototype.TracksMax = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("TracksMax", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aTracksMax"] = SoapRequest.ReadIntParameter(result["aTracksMax"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServicePlaylist.prototype.IdArray = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("IdArray", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aIdArrayToken"] = SoapRequest.ReadIntParameter(result["aIdArrayToken"]);	
		result["aIdArray"] = SoapRequest.ReadBinaryParameter(result["aIdArray"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServicePlaylist.prototype.IdArrayChanged = function(aIdArrayToken, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("IdArrayChanged", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("aIdArrayToken", aIdArrayToken);
    request.Send(function(result){
		result["aIdArrayChanged"] = SoapRequest.ReadBoolParameter(result["aIdArrayChanged"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}



