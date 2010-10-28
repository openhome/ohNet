 

/**
 * Proxy for linn.co.uk:Ptest:1
 */

var ServicePtest = function(aId){	
	this.iUrl = window.location.protocol + "//" + window.location.host + "/" + aId + "/Ptest/control";
	this.iDomain = "linn.co.uk";
	if (this.iDomain == "upnp.org") {
		this.iDomain = "schemas.upnp.org";
    }
	this.iDomain = this.iDomain.replace(/\./,"-");
	this.iType = "Ptest";
	this.iVersion = "1";
	
	this.iVariables = {};
			this.iVariables["Bool"] = new ServiceVariable("Bool");
		this.iVariables["ComPort"] = new ServiceVariable("ComPort");
}


ServicePtest.prototype.ServiceName = function(){
	return this.iType;
}

ServicePtest.prototype.Variables = function(){
	return this.iVariables;
}

ServicePtest.prototype.VariableNames = function(){
	var result = [];
	for (var variable in this.iVariables){
		if (this.iVariables.hasOwnProperty(variable)){
			result[result.length] = variable;
		}
	}
	return result;
}


ServicePtest.prototype.TestComPort = function(aPort, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("TestComPort", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("aPort", aPort);
    request.Send(function(result){
		result["aResult"] = request.ReadBoolParameter(result["aResult"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServicePtest.prototype.LedsOn = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("LedsOn", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServicePtest.prototype.LedsOff = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("LedsOff", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    


