 

/**
 * Proxy for linn.co.uk:Product:2
 */

var ServiceProduct = function(aId){	
	this.iUrl = window.location.protocol + "//" + window.location.host + "/" + aId + "/Product/control";
	this.iDomain = "linn.co.uk";
	if (this.iDomain == "upnp.org") {
		this.iDomain = "schemas.upnp.org";
    }
	this.iDomain = this.iDomain.replace(/\./,"-");
	this.iType = "Product";
	this.iVersion = "2";
	
	this.iVariables = {};
			this.iVariables["ProductType"] = new ServiceVariable("ProductType");
		this.iVariables["ProductModel"] = new ServiceVariable("ProductModel");
		this.iVariables["ProductName"] = new ServiceVariable("ProductName");
		this.iVariables["ProductRoom"] = new ServiceVariable("ProductRoom");
		this.iVariables["ProductStandby"] = new ServiceVariable("ProductStandby");
		this.iVariables["ProductSourceIndex"] = new ServiceVariable("ProductSourceIndex");
		this.iVariables["ProductSourceType"] = new ServiceVariable("ProductSourceType");
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


ServiceProduct.prototype.Type = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("Type", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aType"] = request.ReadStringParameter(result["aType"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceProduct.prototype.Model = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("Model", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aModel"] = request.ReadStringParameter(result["aModel"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceProduct.prototype.Name = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("Name", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aName"] = request.ReadStringParameter(result["aName"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceProduct.prototype.SetName = function(aName, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetName", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteStringParameter("aName", aName);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
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
    

ServiceProduct.prototype.SourceCount = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SourceCount", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aSourceCount"] = request.ReadIntParameter(result["aSourceCount"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceProduct.prototype.SourceIndex = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SourceIndex", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aSourceIndex"] = request.ReadIntParameter(result["aSourceIndex"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceProduct.prototype.SetSourceIndex = function(aSourceIndex, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetSourceIndex", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("aSourceIndex", aSourceIndex);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceProduct.prototype.SourceType = function(aSourceIndex, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SourceType", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("aSourceIndex", aSourceIndex);
    request.Send(function(result){
		result["aSourceType"] = request.ReadStringParameter(result["aSourceType"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    


