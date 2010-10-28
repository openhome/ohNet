 

/**
 * Proxy for linn.co.uk:Debug:2
 */

var ServiceDebug = function(aId){	
	this.iUrl = window.location.protocol + "//" + window.location.host + "/" + aId + "/Debug/control";
	this.iDomain = "linn.co.uk";
	if (this.iDomain == "upnp.org") {
		this.iDomain = "schemas.upnp.org";
    }
	this.iDomain = this.iDomain.replace(/\./,"-");
	this.iType = "Debug";
	this.iVersion = "2";
	
	this.iVariables = {};
			this.iVariables["TUint"] = new ServiceVariable("TUint");
		this.iVariables["Address"] = new ServiceVariable("Address");
		this.iVariables["Data"] = new ServiceVariable("Data");
}


ServiceDebug.prototype.ServiceName = function(){
	return this.iType;
}

ServiceDebug.prototype.Variables = function(){
	return this.iVariables;
}

ServiceDebug.prototype.VariableNames = function(){
	var result = [];
	for (var variable in this.iVariables){
		if (this.iVariables.hasOwnProperty(variable)){
			result[result.length] = variable;
		}
	}
	return result;
}


ServiceDebug.prototype.SetDebugLevel = function(aDebugLevel, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetDebugLevel", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("aDebugLevel", aDebugLevel);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceDebug.prototype.DebugLevel = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("DebugLevel", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aDebugLevel"] = request.ReadIntParameter(result["aDebugLevel"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceDebug.prototype.MemWrite = function(aMemAddress, aMemData, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("MemWrite", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("aMemAddress", aMemAddress);
    request.WriteBinaryParameter("aMemData", aMemData);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    


