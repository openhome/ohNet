 

/**
 * Proxy for upnp.org:SwitchPower:1
 */

var ServiceSwitchPower = function(aId){	
	this.iUrl = window.location.protocol + "//" + window.location.host + "/" + aId + "/SwitchPower/control";
	this.iDomain = "upnp.org";
	if (this.iDomain == "upnp.org") {
		this.iDomain = "schemas.upnp.org";
    }
	this.iDomain = this.iDomain.replace(/\./,"-");
	this.iType = "SwitchPower";
	this.iVersion = "1";
	
	this.iVariables = {};
			this.iVariables["Target"] = new ServiceVariable("Target");
		this.iVariables["Status"] = new ServiceVariable("Status");
}


ServiceSwitchPower.prototype.ServiceName = function(){
	return this.iType;
}

ServiceSwitchPower.prototype.Variables = function(){
	return this.iVariables;
}

ServiceSwitchPower.prototype.VariableNames = function(){
	var result = [];
	for (var variable in this.iVariables){
		if (this.iVariables.hasOwnProperty(variable)){
			result[result.length] = variable;
		}
	}
	return result;
}


ServiceSwitchPower.prototype.SetTarget = function(newTargetValue, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetTarget", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteBoolParameter("newTargetValue", newTargetValue);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceSwitchPower.prototype.GetTarget = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetTarget", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["RetTargetValue"] = request.ReadBoolParameter(result["RetTargetValue"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceSwitchPower.prototype.GetStatus = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetStatus", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["ResultStatus"] = request.ReadBoolParameter(result["ResultStatus"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    


