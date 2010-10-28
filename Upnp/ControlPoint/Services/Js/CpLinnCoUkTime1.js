 

/**
 * Proxy for linn.co.uk:Time:1
 */

var ServiceTime = function(aId){	
	this.iUrl = window.location.protocol + "//" + window.location.host + "/" + aId + "/Time/control";
	this.iDomain = "linn.co.uk";
	if (this.iDomain == "upnp.org") {
		this.iDomain = "schemas.upnp.org";
    }
	this.iDomain = this.iDomain.replace(/\./,"-");
	this.iType = "Time";
	this.iVersion = "1";
	
	this.iVariables = {};
			this.iVariables["TrackCount"] = new ServiceVariable("TrackCount");
		this.iVariables["Duration"] = new ServiceVariable("Duration");
		this.iVariables["Seconds"] = new ServiceVariable("Seconds");
}


ServiceTime.prototype.ServiceName = function(){
	return this.iType;
}

ServiceTime.prototype.Variables = function(){
	return this.iVariables;
}

ServiceTime.prototype.VariableNames = function(){
	var result = [];
	for (var variable in this.iVariables){
		if (this.iVariables.hasOwnProperty(variable)){
			result[result.length] = variable;
		}
	}
	return result;
}


ServiceTime.prototype.Time = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("Time", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aTrackCount"] = request.ReadIntParameter(result["aTrackCount"]);	
		result["aDuration"] = request.ReadIntParameter(result["aDuration"]);	
		result["aSeconds"] = request.ReadIntParameter(result["aSeconds"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    


