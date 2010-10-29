 

/**
 * Proxy for linn.co.uk:Playlist:1
 */

var ServicePlaylist = function(aId){	
	this.iUrl = window.location.protocol + "//" + window.location.host + "/" + aId + "/Playlist/control";
	this.iDomain = "linn.co.uk";
	if (this.iDomain == "upnp.org") {
		this.iDomain = "schemas.upnp.org";
    }
	this.iDomain = this.iDomain.replace(/\./,"-");
	this.iType = "Playlist";
	this.iVersion = "1";
	
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


ServicePlaylist.prototype.ServiceName = function(){
	return this.iType;
}

ServicePlaylist.prototype.Variables = function(){
	return this.iVariables;
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


ServicePlaylist.prototype.Read = function(aId, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("Read", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("aId", aId);
    request.Send(function(result){
		result["aUri"] = request.ReadStringParameter(result["aUri"]);	
		result["aMetaData"] = request.ReadStringParameter(result["aMetaData"]);	
	
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
		result["aMetaDataList"] = request.ReadStringParameter(result["aMetaDataList"]);	
	
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
		result["aNewId"] = request.ReadIntParameter(result["aNewId"]);	
	
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
		result["aRepeat"] = request.ReadBoolParameter(result["aRepeat"]);	
	
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
		result["aShuffle"] = request.ReadBoolParameter(result["aShuffle"]);	
	
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
		result["aTracksMax"] = request.ReadIntParameter(result["aTracksMax"]);	
	
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
		result["aIdArrayToken"] = request.ReadIntParameter(result["aIdArrayToken"]);	
		result["aIdArray"] = request.ReadBinaryParameter(result["aIdArray"]);	
	
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
		result["aIdArrayChanged"] = request.ReadBoolParameter(result["aIdArrayChanged"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    


