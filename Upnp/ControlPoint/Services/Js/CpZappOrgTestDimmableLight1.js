 

/**
 * Proxy for zapp.org:TestDimmableLight:1
 */

var ServiceTestDimmableLight = function(aId){	
	this.iUrl = window.location.protocol + "//" + window.location.host + "/" + aId + "/TestDimmableLight/control";
	this.iDomain = "zapp.org";
	if (this.iDomain == "upnp.org") {
		this.iDomain = "schemas.upnp.org";
    }
	this.iDomain = this.iDomain.replace(/\./,"-");
	this.iType = "TestDimmableLight";
	this.iVersion = "1";
	
	this.iVariables = {};
			this.iVariables["A_ARG_Level"] = new ServiceVariable("A_ARG_Level");
}


ServiceTestDimmableLight.prototype.ServiceName = function(){
	return this.iType;
}

ServiceTestDimmableLight.prototype.Variables = function(){
	return this.iVariables;
}

ServiceTestDimmableLight.prototype.VariableNames = function(){
	var result = [];
	for (var variable in this.iVariables){
		if (this.iVariables.hasOwnProperty(variable)){
			result[result.length] = variable;
		}
	}
	return result;
}


ServiceTestDimmableLight.prototype.GetLevel = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetLevel", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["Level"] = request.ReadIntParameter(result["Level"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceTestDimmableLight.prototype.SetLevel = function(Level, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetLevel", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("Level", Level);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    


