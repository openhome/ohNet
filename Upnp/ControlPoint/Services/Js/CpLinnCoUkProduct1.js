 

/**
 * Proxy for linn.co.uk:Product:1
 */

var ServiceProduct = function(aId){	
	this.iUrl = window.location.protocol + "//" + window.location.host + "/" + aId + "/Product/control";
	this.iDomain = "linn.co.uk";
	if (this.iDomain == "upnp.org") {
		this.iDomain = "schemas.upnp.org";
    }
	this.iDomain = this.iDomain.replace(/\./,"-");
	this.iType = "Product";
	this.iVersion = "1";
	
	this.iVariables = {};
			this.iVariables["Room"] = new ServiceVariable("Room");
		this.iVariables["Standby"] = new ServiceVariable("Standby");
}


ServiceProduct.prototype.ServiceName = function(){
	return this.iType;
}

ServiceProduct.prototype.Variables = function(){
	return this.iVariables;
}

ServiceProduct.prototype.VariableNames = function(){
	var result = [];
	for (var variable in this.iVariables){
		if (this.iVariables.hasOwnProperty(variable)){
			result[result.length] = variable;
		}
	}
	return result;
}


ServiceProduct.prototype.Room = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("Room", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aRoom"] = request.ReadStringParameter(result["aRoom"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceProduct.prototype.SetRoom = function(aRoom, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetRoom", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteStringParameter("aRoom", aRoom);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceProduct.prototype.Standby = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("Standby", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aStandby"] = request.ReadBoolParameter(result["aStandby"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceProduct.prototype.SetStandby = function(aStandby, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetStandby", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteBoolParameter("aStandby", aStandby);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    


