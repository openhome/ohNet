 

/**
 * Proxy for linn.co.uk:Configuration:1
 */

var ServiceConfiguration = function(aId){	
	this.iUrl = window.location.protocol + "//" + window.location.host + "/" + aId + "/Configuration/control";
	this.iDomain = "linn.co.uk";
	if (this.iDomain == "upnp.org") {
		this.iDomain = "schemas.upnp.org";
    }
	this.iDomain = this.iDomain.replace(/\./,"-");
	this.iType = "Configuration";
	this.iVersion = "1";
	
	this.iVariables = {};
			this.iVariables["ConfigurationXml"] = new ServiceVariable("ConfigurationXml");
		this.iVariables["ParameterXml"] = new ServiceVariable("ParameterXml");
		this.iVariables["Target"] = new ServiceVariable("Target");
		this.iVariables["Name"] = new ServiceVariable("Name");
		this.iVariables["Value"] = new ServiceVariable("Value");
}


ServiceConfiguration.prototype.ServiceName = function(){
	return this.iType;
}

ServiceConfiguration.prototype.Variables = function(){
	return this.iVariables;
}

ServiceConfiguration.prototype.VariableNames = function(){
	var result = [];
	for (var variable in this.iVariables){
		if (this.iVariables.hasOwnProperty(variable)){
			result[result.length] = variable;
		}
	}
	return result;
}


ServiceConfiguration.prototype.ConfigurationXml = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("ConfigurationXml", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aConfigurationXml"] = request.ReadStringParameter(result["aConfigurationXml"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceConfiguration.prototype.ParameterXml = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("ParameterXml", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aParameterXml"] = request.ReadStringParameter(result["aParameterXml"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceConfiguration.prototype.SetParameter = function(aTarget, aName, aValue, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetParameter", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteStringParameter("aTarget", aTarget);
    request.WriteStringParameter("aName", aName);
    request.WriteStringParameter("aValue", aValue);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    


