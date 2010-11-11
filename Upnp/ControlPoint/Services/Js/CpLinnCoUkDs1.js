 

/**
 * Proxy for linn.co.uk:Ds:1
 */

var ServiceDs = function(aUdn){	
	this.iUrl = window.location.protocol + "//" + window.location.host + "/" + aUdn + "/linn.co.uk-Ds-1/control";
	this.iDomain = "linn.co.uk";
	if (this.iDomain == "upnp.org") {
		this.iDomain = "schemas.upnp.org";
    }
	this.iDomain = this.iDomain.replace(/\./,"-");
	this.iType = "Ds";
	this.iVersion = "1";
	this.iServiceName = "linn.co.uk-Ds-1";
	this.iSubscriptionId = "";
	this.iUdn = aUdn;
	
	this.iVariables = {};
			this.iVariables["Offset"] = new ServiceVariable("Offset");
		this.iVariables["Pos"] = new ServiceVariable("Pos");
		this.iVariables["SupportedProtocols"] = new ServiceVariable("SupportedProtocols");
		this.iVariables["TrackDuration"] = new ServiceVariable("TrackDuration");
		this.iVariables["TrackBitRate"] = new ServiceVariable("TrackBitRate");
		this.iVariables["TrackLossless"] = new ServiceVariable("TrackLossless");
		this.iVariables["TrackBitDepth"] = new ServiceVariable("TrackBitDepth");
		this.iVariables["TrackSampleRate"] = new ServiceVariable("TrackSampleRate");
		this.iVariables["TrackCodecName"] = new ServiceVariable("TrackCodecName");
		this.iVariables["TrackId"] = new ServiceVariable("TrackId");
		this.iVariables["TransportState"] = new ServiceVariable("TransportState");
}

ServiceDs.kTransportStatePlaying = "Playing";
ServiceDs.kTransportStatePaused = "Paused";
ServiceDs.kTransportStateStopped = "Stopped";
ServiceDs.kTransportStateBuffering = "Buffering";

ServiceDs.prototype.Offset_Changed = function (aStateChangedFunction) {
    this.Variables().Offset.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServiceDs.prototype.Pos_Changed = function (aStateChangedFunction) {
    this.Variables().Pos.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServiceDs.prototype.SupportedProtocols_Changed = function (aStateChangedFunction) {
    this.Variables().SupportedProtocols.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceDs.prototype.TrackDuration_Changed = function (aStateChangedFunction) {
    this.Variables().TrackDuration.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServiceDs.prototype.TrackBitRate_Changed = function (aStateChangedFunction) {
    this.Variables().TrackBitRate.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServiceDs.prototype.TrackLossless_Changed = function (aStateChangedFunction) {
    this.Variables().TrackLossless.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadBoolParameter(state)); 
	});
}
ServiceDs.prototype.TrackBitDepth_Changed = function (aStateChangedFunction) {
    this.Variables().TrackBitDepth.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServiceDs.prototype.TrackSampleRate_Changed = function (aStateChangedFunction) {
    this.Variables().TrackSampleRate.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServiceDs.prototype.TrackCodecName_Changed = function (aStateChangedFunction) {
    this.Variables().TrackCodecName.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceDs.prototype.TrackId_Changed = function (aStateChangedFunction) {
    this.Variables().TrackId.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServiceDs.prototype.TransportState_Changed = function (aStateChangedFunction) {
    this.Variables().TransportState.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}

ServiceDs.prototype.ServiceName = function(){
	return this.iServiceName;
}

ServiceDs.prototype.Variables = function(){
	return this.iVariables;
}

ServiceDs.prototype.SubscriptionId = function () {
    return this.iSubscriptionId;
}

ServiceDs.prototype.SetSubscriptionId = function (value) {
    this.iSubscriptionId = value;
}

ServiceDs.prototype.Udn = function () {
    return this.iUdn;
}

ServiceDs.prototype.VariableNames = function(){
	var result = [];
	for (var variable in this.iVariables){
		if (this.iVariables.hasOwnProperty(variable)){
			result[result.length] = variable;
		}
	}
	return result;
}

ServiceDs.prototype.Subscribe = function () {
    SubscriptionManager.AddService(this);
}

ServiceDs.prototype.Unsubscribe = function () {
    SubscriptionManager.RemoveService(this.SubscriptionId());
}


ServiceDs.prototype.Play = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("Play", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceDs.prototype.Pause = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("Pause", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceDs.prototype.Stop = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("Stop", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceDs.prototype.SeekSecondAbsolute = function(aSecond, aSuccessFunction, aErrorFunction){	
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


ServiceDs.prototype.SeekSecondRelative = function(aSecond, aSuccessFunction, aErrorFunction){	
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


ServiceDs.prototype.SeekTrackId = function(aTrackId, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SeekTrackId", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("aTrackId", aTrackId);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceDs.prototype.SeekTrackAbsolute = function(aTrack, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SeekTrackAbsolute", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("aTrack", aTrack);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceDs.prototype.SeekTrackRelative = function(aTrack, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SeekTrackRelative", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("aTrack", aTrack);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceDs.prototype.State = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("State", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aTransportState"] = SoapRequest.ReadStringParameter(result["aTransportState"]);	
		result["aTrackDuration"] = SoapRequest.ReadIntParameter(result["aTrackDuration"]);	
		result["aTrackBitRate"] = SoapRequest.ReadIntParameter(result["aTrackBitRate"]);	
		result["aTrackLossless"] = SoapRequest.ReadBoolParameter(result["aTrackLossless"]);	
		result["aTrackBitDepth"] = SoapRequest.ReadIntParameter(result["aTrackBitDepth"]);	
		result["aTrackSampleRate"] = SoapRequest.ReadIntParameter(result["aTrackSampleRate"]);	
		result["aTrackCodecName"] = SoapRequest.ReadStringParameter(result["aTrackCodecName"]);	
		result["aTrackId"] = SoapRequest.ReadIntParameter(result["aTrackId"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceDs.prototype.ProtocolInfo = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("ProtocolInfo", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aSupportedProtocols"] = SoapRequest.ReadStringParameter(result["aSupportedProtocols"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}



