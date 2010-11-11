 

/**
 * Proxy for linn.co.uk:Radio:1
 */

var ServiceRadio = function(aUdn){	
	this.iUrl = window.location.protocol + "//" + window.location.host + "/" + aUdn + "/linn.co.uk-Radio-1/control";
	this.iDomain = "linn.co.uk";
	if (this.iDomain == "upnp.org") {
		this.iDomain = "schemas.upnp.org";
    }
	this.iDomain = this.iDomain.replace(/\./,"-");
	this.iType = "Radio";
	this.iVersion = "1";
	this.iServiceName = "linn.co.uk-Radio-1";
	this.iSubscriptionId = "";
	this.iUdn = aUdn;
	
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

ServiceRadio.prototype.Offset_Changed = function (aStateChangedFunction) {
    this.Variables().Offset.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServiceRadio.prototype.Pos_Changed = function (aStateChangedFunction) {
    this.Variables().Pos.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServiceRadio.prototype.ChannelUri_Changed = function (aStateChangedFunction) {
    this.Variables().ChannelUri.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceRadio.prototype.ChannelMetadata_Changed = function (aStateChangedFunction) {
    this.Variables().ChannelMetadata.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceRadio.prototype.TransportState_Changed = function (aStateChangedFunction) {
    this.Variables().TransportState.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceRadio.prototype.ProtocolInfo_Changed = function (aStateChangedFunction) {
    this.Variables().ProtocolInfo.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceRadio.prototype.Id_Changed = function (aStateChangedFunction) {
    this.Variables().Id.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServiceRadio.prototype.IdArray_Changed = function (aStateChangedFunction) {
    this.Variables().IdArray.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadBinaryParameter(state)); 
	});
}
ServiceRadio.prototype.IdsMax_Changed = function (aStateChangedFunction) {
    this.Variables().IdsMax.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServiceRadio.prototype.IdArrayToken_Changed = function (aStateChangedFunction) {
    this.Variables().IdArrayToken.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServiceRadio.prototype.IdArrayChanged_Changed = function (aStateChangedFunction) {
    this.Variables().IdArrayChanged.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadBoolParameter(state)); 
	});
}
ServiceRadio.prototype.Data_Changed = function (aStateChangedFunction) {
    this.Variables().Data.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}

ServiceRadio.prototype.ServiceName = function(){
	return this.iServiceName;
}

ServiceRadio.prototype.Variables = function(){
	return this.iVariables;
}

ServiceRadio.prototype.SubscriptionId = function () {
    return this.iSubscriptionId;
}

ServiceRadio.prototype.SetSubscriptionId = function (value) {
    this.iSubscriptionId = value;
}

ServiceRadio.prototype.Udn = function () {
    return this.iUdn;
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

ServiceRadio.prototype.Subscribe = function () {
    SubscriptionManager.AddService(this);
}

ServiceRadio.prototype.Unsubscribe = function () {
    SubscriptionManager.RemoveService(this.SubscriptionId());
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
		result["aUri"] = SoapRequest.ReadStringParameter(result["aUri"]);	
		result["aMetadata"] = SoapRequest.ReadStringParameter(result["aMetadata"]);	
	
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
		result["aInfo"] = SoapRequest.ReadStringParameter(result["aInfo"]);	
	
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
		result["aState"] = SoapRequest.ReadStringParameter(result["aState"]);	
	
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
		result["aId"] = SoapRequest.ReadIntParameter(result["aId"]);	
	
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
		result["aMetadata"] = SoapRequest.ReadStringParameter(result["aMetadata"]);	
	
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
		result["aMetadataList"] = SoapRequest.ReadStringParameter(result["aMetadataList"]);	
	
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
		result["aIdArrayToken"] = SoapRequest.ReadIntParameter(result["aIdArrayToken"]);	
		result["aIdArray"] = SoapRequest.ReadBinaryParameter(result["aIdArray"]);	
	
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
		result["aIdArrayChanged"] = SoapRequest.ReadBoolParameter(result["aIdArrayChanged"]);	
	
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
		result["aIdsMax"] = SoapRequest.ReadIntParameter(result["aIdsMax"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}



