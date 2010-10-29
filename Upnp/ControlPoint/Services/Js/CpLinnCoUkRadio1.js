 

/**
 * Proxy for linn.co.uk:Radio:1
 */

var ServiceRadio = function(aId){	
	this.iUrl = window.location.protocol + "//" + window.location.host + "/" + aId + "/Radio/control";
	this.iDomain = "linn.co.uk";
	if (this.iDomain == "upnp.org") {
		this.iDomain = "schemas.upnp.org";
    }
	this.iDomain = this.iDomain.replace(/\./,"-");
	this.iType = "Radio";
	this.iVersion = "1";
	
	this.iVariables = {};
			this.iVariables["Offset"] = new ServiceVariable("Offset");
		this.iVariables["Pos"] = new ServiceVariable("Pos");
		this.iVariables["ChannelUri"] = new ServiceVariable("ChannelUri");
		this.iVariables["ChannelMetadata"] = new ServiceVariable("ChannelMetadata");
		this.iVariables["TransportState"] = new ServiceVariable("TransportState");
		this.iVariables["ProtocolInfo"] = new ServiceVariable("ProtocolInfo");
		this.iVariables["Id"] = new ServiceVariable("Id");
		this.iVariables["IdArray"] = new ServiceVariable("IdArray");
		this.iVariables["IdsMax"] = new ServiceVariable("IdsMax");
		this.iVariables["IdArrayToken"] = new ServiceVariable("IdArrayToken");
		this.iVariables["IdArrayChanged"] = new ServiceVariable("IdArrayChanged");
		this.iVariables["Data"] = new ServiceVariable("Data");
}

ServiceRadio.kTransportStateStopped = "Stopped";
ServiceRadio.kTransportStatePlaying = "Playing";
ServiceRadio.kTransportStatePaused = "Paused";
ServiceRadio.kTransportStateBuffering = "Buffering";

ServiceRadio.prototype.ServiceName = function(){
	return this.iType;
}

ServiceRadio.prototype.Variables = function(){
	return this.iVariables;
}

ServiceRadio.prototype.VariableNames = function(){
	var result = [];
	for (var variable in this.iVariables){
		if (this.iVariables.hasOwnProperty(variable)){
			result[result.length] = variable;
		}
	}
	return result;
}


ServiceRadio.prototype.Play = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("Play", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceRadio.prototype.Pause = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("Pause", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceRadio.prototype.Stop = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("Stop", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceRadio.prototype.SeekSecondAbsolute = function(aSecond, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SeekSecondAbsolute", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("aSecond", aSecond);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceRadio.prototype.SeekSecondRelative = function(aSecond, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SeekSecondRelative", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("aSecond", aSecond);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceRadio.prototype.Channel = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("Channel", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aUri"] = request.ReadStringParameter(result["aUri"]);	
		result["aMetadata"] = request.ReadStringParameter(result["aMetadata"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceRadio.prototype.SetChannel = function(aUri, aMetadata, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetChannel", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteStringParameter("aUri", aUri);
    request.WriteStringParameter("aMetadata", aMetadata);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceRadio.prototype.ProtocolInfo = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("ProtocolInfo", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aInfo"] = request.ReadStringParameter(result["aInfo"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceRadio.prototype.TransportState = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("TransportState", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aState"] = request.ReadStringParameter(result["aState"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceRadio.prototype.Id = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("Id", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aId"] = request.ReadIntParameter(result["aId"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceRadio.prototype.SetId = function(aId, aUri, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetId", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("aId", aId);
    request.WriteStringParameter("aUri", aUri);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceRadio.prototype.Read = function(aId, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("Read", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("aId", aId);
    request.Send(function(result){
		result["aMetadata"] = request.ReadStringParameter(result["aMetadata"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceRadio.prototype.ReadList = function(aIdList, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("ReadList", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteStringParameter("aIdList", aIdList);
    request.Send(function(result){
		result["aMetadataList"] = request.ReadStringParameter(result["aMetadataList"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceRadio.prototype.IdArray = function(aSuccessFunction, aErrorFunction){	
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
    

ServiceRadio.prototype.IdArrayChanged = function(aIdArrayToken, aSuccessFunction, aErrorFunction){	
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
    

ServiceRadio.prototype.IdsMax = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("IdsMax", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aIdsMax"] = request.ReadIntParameter(result["aIdsMax"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    


