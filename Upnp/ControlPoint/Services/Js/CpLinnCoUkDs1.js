 

/**
 * Proxy for linn.co.uk:Ds:1
 */

var ServiceDs = function(aId){	
	this.iUrl = window.location.protocol + "//" + window.location.host + "/" + aId + "/Ds/control";
	this.iDomain = "linn.co.uk";
	if (this.iDomain == "upnp.org") {
		this.iDomain = "schemas.upnp.org";
    }
	this.iDomain = this.iDomain.replace(/\./,"-");
	this.iType = "Ds";
	this.iVersion = "1";
	
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

ServiceDs.prototype.ServiceName = function(){
	return this.iType;
}

ServiceDs.prototype.Variables = function(){
	return this.iVariables;
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
		result["aTransportState"] = request.ReadStringParameter(result["aTransportState"]);	
		result["aTrackDuration"] = request.ReadIntParameter(result["aTrackDuration"]);	
		result["aTrackBitRate"] = request.ReadIntParameter(result["aTrackBitRate"]);	
		result["aTrackLossless"] = request.ReadBoolParameter(result["aTrackLossless"]);	
		result["aTrackBitDepth"] = request.ReadIntParameter(result["aTrackBitDepth"]);	
		result["aTrackSampleRate"] = request.ReadIntParameter(result["aTrackSampleRate"]);	
		result["aTrackCodecName"] = request.ReadStringParameter(result["aTrackCodecName"]);	
		result["aTrackId"] = request.ReadIntParameter(result["aTrackId"]);	
	
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
		result["aSupportedProtocols"] = request.ReadStringParameter(result["aSupportedProtocols"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    


