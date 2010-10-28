 

/**
 * Proxy for linn.co.uk:Info:1
 */

var ServiceInfo = function(aId){	
	this.iUrl = window.location.protocol + "//" + window.location.host + "/" + aId + "/Info/control";
	this.iDomain = "linn.co.uk";
	if (this.iDomain == "upnp.org") {
		this.iDomain = "schemas.upnp.org";
    }
	this.iDomain = this.iDomain.replace(/\./,"-");
	this.iType = "Info";
	this.iVersion = "1";
	
	this.iVariables = {};
			this.iVariables["TrackCount"] = new ServiceVariable("TrackCount");
		this.iVariables["DetailsCount"] = new ServiceVariable("DetailsCount");
		this.iVariables["MetatextCount"] = new ServiceVariable("MetatextCount");
		this.iVariables["Uri"] = new ServiceVariable("Uri");
		this.iVariables["Metadata"] = new ServiceVariable("Metadata");
		this.iVariables["Duration"] = new ServiceVariable("Duration");
		this.iVariables["BitRate"] = new ServiceVariable("BitRate");
		this.iVariables["BitDepth"] = new ServiceVariable("BitDepth");
		this.iVariables["SampleRate"] = new ServiceVariable("SampleRate");
		this.iVariables["Lossless"] = new ServiceVariable("Lossless");
		this.iVariables["CodecName"] = new ServiceVariable("CodecName");
		this.iVariables["Metatext"] = new ServiceVariable("Metatext");
}


ServiceInfo.prototype.ServiceName = function(){
	return this.iType;
}

ServiceInfo.prototype.Variables = function(){
	return this.iVariables;
}

ServiceInfo.prototype.VariableNames = function(){
	var result = [];
	for (var variable in this.iVariables){
		if (this.iVariables.hasOwnProperty(variable)){
			result[result.length] = variable;
		}
	}
	return result;
}


ServiceInfo.prototype.Counters = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("Counters", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aTrackCount"] = request.ReadIntParameter(result["aTrackCount"]);	
		result["aDetailsCount"] = request.ReadIntParameter(result["aDetailsCount"]);	
		result["aMetatextCount"] = request.ReadIntParameter(result["aMetatextCount"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceInfo.prototype.Track = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("Track", this.iUrl, this.iDomain, this.iType, this.iVersion);		
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
    

ServiceInfo.prototype.Details = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("Details", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aDuration"] = request.ReadIntParameter(result["aDuration"]);	
		result["aBitRate"] = request.ReadIntParameter(result["aBitRate"]);	
		result["aBitDepth"] = request.ReadIntParameter(result["aBitDepth"]);	
		result["aSampleRate"] = request.ReadIntParameter(result["aSampleRate"]);	
		result["aLossless"] = request.ReadBoolParameter(result["aLossless"]);	
		result["aCodecName"] = request.ReadStringParameter(result["aCodecName"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceInfo.prototype.Metatext = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("Metatext", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aMetatext"] = request.ReadStringParameter(result["aMetatext"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    


