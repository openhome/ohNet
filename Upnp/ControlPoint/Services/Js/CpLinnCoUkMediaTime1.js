 

/**
 * Proxy for linn.co.uk:MediaTime:1
 */

var ServiceMediaTime = function(aId){	
	this.iUrl = window.location.protocol + "//" + window.location.host + "/" + aId + "/MediaTime/control";
	this.iDomain = "linn.co.uk";
	if (this.iDomain == "upnp.org") {
		this.iDomain = "schemas.upnp.org";
    }
	this.iDomain = this.iDomain.replace(/\./,"-");
	this.iType = "MediaTime";
	this.iVersion = "1";
	
	this.iVariables = {};
			this.iVariables["Seconds"] = new ServiceVariable("Seconds");
}


ServiceMediaTime.prototype.ServiceName = function(){
	return this.iType;
}

ServiceMediaTime.prototype.Variables = function(){
	return this.iVariables;
}

ServiceMediaTime.prototype.VariableNames = function(){
	var result = [];
	for (var variable in this.iVariables){
		if (this.iVariables.hasOwnProperty(variable)){
			result[result.length] = variable;
		}
	}
	return result;
}


ServiceMediaTime.prototype.Seconds = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("Seconds", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aSeconds"] = request.ReadIntParameter(result["aSeconds"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    


